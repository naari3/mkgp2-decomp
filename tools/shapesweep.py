#!/usr/bin/env python3
"""shapesweep.py: guided search over the *source shape* of one function.

For register-allocation-only near misses where pragmas, decl order and
statement order (pragmasweep / stmtsweep / autopipe) are exhausted. The
function body is parsed into C expression trees and rewritten by mechanical,
semantics-preserving (or float-reassociating) moves:

  wrap    a OP b      -> Op_T(a, b)          inline helper (args are evaluated
          a OP b      -> OpR_T(b, a)         right to left, so the two orders
                                             give the operands different vregs)
  wrap2   a OP b      -> OpL_T(a, b)         helper layered on another helper
  id      e           -> Id_T(e)             identity inline (extra temp)
  hoist   e           -> tN (new local, assigned just before the statement;
                         declared at the front or the back of the decl block)
  accum   x = l OP r  -> x = l; x = x OP r;  (and x = r; x = l OP x;)
  unvar   T x = e; ... x ...  -> ... e ...   (single-use local substituted)
  expand  Helper(a, b) -> its `return expr;` body, for static inline helpers
                         of the TU
  swap    a OP b      -> b OP a              commutative ops
  assoc   (a OP b) OP c <-> a OP (b OP c)    + and *
  declswap            adjacent top-of-function declarations / declarators

Search is a beam search: every round, every state in the beam is expanded by
all single moves (or a random --sample of them), each variant is compiled
(scratch copy next to the source, as pragmasweep does) and scored by diff
lines against the target (pragmasweep scoring: 0 = match). Ties are broken by
mwccdbg (tools/mwccdbg.py): the colouring position of the first virtual
register whose machine register differs from the target (later = better) and
the number of mismatching vregs. --dbg K runs the debugger on the K best tied
states per round (about 8 s each, one at a time); --dbg 0 turns it off.

    python3 -I tools/shapesweep.py game/kartmove/carobject fn_8019EB9C \\
        [--start notes/x.cpp] [--pragma 'opt_propagation off'] [--cc 2.6] \\
        [--beam 8] [--rounds 12] [--sample 200] [--moves wrap,id,hoist,...] \\
        [--dbg 2] [-j 4] [--apply]

Run from the repo root after a build. --start FILE replaces the function's
definition with FILE's (a full definition, optionally preceded by helpers) as
the starting point. Nothing is written to src/ unless --apply (claim the TU
first). The best source is written to /tmp/shapesweep/<fn>.best.<ext> and a
JSON log of every scored variant to /tmp/shapesweep/<fn>.log.jsonl.
"""
from __future__ import annotations

import argparse, copy, hashlib, json, os, random, re, shlex, subprocess, sys, time
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pragmasweep as ps  # noqa: E402

TMP = '/tmp/shapesweep'

# --------------------------------------------------------------------------
# tokenizer / parser / printer for C expressions

TOK = re.compile(r'''\s*(?:
  (?P<num>0[xX][0-9a-fA-F]+[uUlL]*|\d+\.\d*(?:[eE][-+]?\d+)?[fFlL]?|\.\d+(?:[eE][-+]?\d+)?[fFlL]?|\d+(?:[eE][-+]?\d+)?[fFuUlL]*)
 |(?P<id>~?[A-Za-z_]\w*(?:\s*::\s*~?[A-Za-z_]\w*)*)
 |(?P<str>"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*')
 |(?P<op>->|\+\+|--|<<=|>>=|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/%&|^]=|[-+*/%&|^~!<>=?:,.()\[\]{};])
)''', re.X)

BIN = {'*': 13, '/': 13, '%': 13, '+': 12, '-': 12, '<<': 11, '>>': 11,
       '<': 10, '<=': 10, '>': 10, '>=': 10, '==': 9, '!=': 9,
       '&': 8, '^': 7, '|': 6, '&&': 5, '||': 4}
ASG = {'=', '+=', '-=', '*=', '/=', '%=', '<<=', '>>=', '&=', '|=', '^='}
QUALS = {'const', 'volatile', 'unsigned', 'signed', 'struct', 'register', 'static', 'union', 'enum', 'class'}
KEYWORDS = {'return', 'if', 'else', 'for', 'while', 'do', 'switch', 'case', 'default', 'break',
            'continue', 'goto', 'sizeof', 'new', 'delete', 'throw', 'this', 'true', 'false'}
SCALAR = {'float': 'float', 'f32': 'float', 'double': 'double', 'f64': 'double',
          'int': 'int', 's32': 'int', 'long': 'int', 'u32': 'u32', 'unsigned': 'u32',
          's16': 's16', 'u16': 'u16', 's8': 's8', 'u8': 'u8', 'char': 's8', 'short': 's16',
          'bool': 'int', 'BOOL': 'int'}
OPNAME = {'+': 'Add', '-': 'Sub', '*': 'Mul', '/': 'Div', '%': 'Mod', '&': 'And', '|': 'Or',
          '^': 'Xor', '<<': 'Shl', '>>': 'Shr'}
COMMUTATIVE = {'+', '*', '&', '|', '^', '==', '!='}


def tokenize(s):
    out, i = [], 0
    while i < len(s):
        if s[i:].strip() == '':
            break
        m = TOK.match(s, i)
        if not m or m.end() == i:
            raise SyntaxError(s[i:i + 20])
        k = m.lastgroup
        out.append((k, re.sub(r'\s+', '', m.group(k))))
        i = m.end()
    return out


class N:
    __slots__ = ('k', 'op', 'kids', 't')

    def __init__(self, k, op=None, kids=(), t=None):
        self.k, self.op, self.kids, self.t = k, op, list(kids), t


class Parser:
    def __init__(self, toks, types):
        self.t, self.i, self.types = toks, 0, types

    def peek(self, o=0):
        j = self.i + o
        return self.t[j][1] if j < len(self.t) else None

    def kind(self, o=0):
        j = self.i + o
        return self.t[j][0] if j < len(self.t) else None

    def next(self):
        self.i += 1
        return self.t[self.i - 1][1]

    def expect(self, x):
        if self.peek() != x:
            raise SyntaxError(f'expected {x} got {self.peek()}')
        self.next()

    def done(self):
        return self.i >= len(self.t)

    def expr(self):
        return self.assign()

    def assign(self):
        l = self.tern()
        if self.peek() in ASG:
            op = self.next()
            return N('asg', op, [l, self.assign()])
        return l

    def tern(self):
        c = self.binary(4)
        if self.peek() == '?':
            self.next()
            a = self.assign()
            self.expect(':')
            return N('tern', None, [c, a, self.tern()])
        return c

    def binary(self, minp):
        l = self.unary()
        while True:
            op = self.peek()
            p = BIN.get(op) if self.kind() == 'op' else None
            if p is None or p < minp:
                return l
            self.next()
            l = N('bin', op, [l, self.binary(p + 1)])

    def is_cast(self):
        if self.peek() != '(':
            return False
        j, words = self.i + 1, []
        while j < len(self.t) and self.t[j][1] != ')':
            k, v = self.t[j]
            if k == 'id' or v in ('*', '&'):
                words.append(v)
            else:
                return False
            j += 1
        if not words or j >= len(self.t):
            return False
        first = next((w for w in words if w not in QUALS), None)
        return first is not None and (first in SCALAR or first in self.types or words[-1] in ('*', '&')
                                      or any(w in QUALS for w in words))

    def raw_paren(self):
        depth, out = 0, []
        while True:
            v = self.next()
            if v == '(':
                depth += 1
                if depth == 1:
                    continue
            elif v == ')':
                depth -= 1
                if depth == 0:
                    return ' '.join(out).replace(' *', '*').replace('* ', '*')
            out.append(v)

    def unary(self):
        op = self.peek()
        if self.kind() == 'op' and op in ('-', '+', '!', '~', '*', '&', '++', '--'):
            self.next()
            return N('un', op, [self.unary()])
        if op == 'sizeof':
            self.next()
            if self.peek() == '(':
                return N('atom', t='sizeof(' + self.raw_paren() + ')')
            return N('un', 'sizeof ', [self.unary()])
        if self.is_cast():
            ty = self.raw_paren()
            return N('cast', None, [self.unary()], t=ty)
        return self.postfix()

    def postfix(self):
        e = self.primary()
        while True:
            v = self.peek()
            if v == '[':
                self.next()
                i = self.expr()
                self.expect(']')
                e = N('idx', None, [e, i])
            elif v == '(':
                self.next()
                args = []
                if self.peek() != ')':
                    while True:
                        args.append(self.assign())
                        if self.peek() == ',':
                            self.next()
                            continue
                        break
                self.expect(')')
                e = N('call', None, [e] + args)
            elif v in ('->', '.'):
                self.next()
                if self.kind() != 'id':
                    raise SyntaxError('member')
                e = N('mem', v, [e], t=self.next())
            elif v in ('++', '--'):
                self.next()
                e = N('post', v, [e])
            else:
                return e

    def primary(self):
        k = self.kind()
        if k in ('num', 'id', 'str'):
            v = self.next()
            if v in KEYWORDS - {'this', 'true', 'false'}:
                raise SyntaxError(v)
            return N('atom', t=v)
        if self.peek() == '(':
            self.next()
            e = self.expr()
            if self.peek() == ',':  # comma expression: keep it raw-ish
                raise SyntaxError('comma')
            self.expect(')')
            return e
        raise SyntaxError(f'primary {self.peek()}')


def prec(n):
    return {'bin': lambda: BIN[n.op], 'tern': lambda: 3, 'asg': lambda: 2, 'un': lambda: 14,
            'cast': lambda: 14}.get(n.k, lambda: 16 if n.k == 'atom' else 15)()


def pr(n):
    k = n.k
    if k == 'atom':
        return n.t
    if k == 'mem':
        return wrap(n.kids[0], 15) + n.op + n.t
    if k == 'idx':
        return wrap(n.kids[0], 15) + '[' + pr(n.kids[1]) + ']'
    if k == 'call':
        return wrap(n.kids[0], 15) + '(' + ', '.join(pr(a) for a in n.kids[1:]) + ')'
    if k == 'post':
        return wrap(n.kids[0], 15) + n.op
    if k == 'un':
        s = wrap(n.kids[0], 14)
        return n.op + (' ' if s[:1] == n.op[-1:] else '') + s
    if k == 'cast':
        return '(' + n.t + ')' + wrap(n.kids[0], 14)
    if k == 'bin':
        p = BIN[n.op]
        return wrap(n.kids[0], p) + ' ' + n.op + ' ' + wrap(n.kids[1], p + 1)
    if k == 'tern':
        return wrap(n.kids[0], 4) + ' ? ' + pr(n.kids[1]) + ' : ' + wrap(n.kids[2], 3)
    if k == 'asg':
        return wrap(n.kids[0], 3) + ' ' + n.op + ' ' + wrap(n.kids[1], 2)
    raise ValueError(k)


def wrap(n, p):
    s = pr(n)
    return '(' + s + ')' if prec(n) < p else s


def parse_expr(s, types):
    p = Parser(tokenize(s), types)
    e = p.expr()
    if not p.done():
        raise SyntaxError('trailing ' + str(p.peek()))
    return e


# --------------------------------------------------------------------------
# statements

CTRL = re.compile(r'^\s*(if|else|for|while|do|switch|case|default|goto|break|continue|\{|\}|#)\b|^\s*[{}#]')


def split_top(s, sep):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '([{':
            depth += 1
        elif ch in ')]}':
            depth -= 1
        if ch == sep and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += ch
    out.append(cur)
    return out


def parse_decl(s, types):
    """'float x = e, *p;' -> {'k': 'decl', 'ty': 'float', 'vars': [[name, stars, arr, init]]} or None."""
    toks = tokenize(s)
    i, ty = 0, []
    while i < len(toks) and toks[i][0] == 'id' and toks[i][1] in QUALS:
        ty.append(toks[i][1])
        i += 1
    if i >= len(toks) or toks[i][0] != 'id' or toks[i][1] in KEYWORDS:
        return None
    ty.append(toks[i][1])
    i += 1
    # C: two identifiers in a row, or Ident * Ident at statement start, is a declaration
    j = i
    while j < len(toks) and toks[j][1] in ('*', '&'):
        j += 1
    if j >= len(toks) or toks[j][0] != 'id' or toks[j][1] in KEYWORDS:
        return None
    if j == i and ty[-1] not in SCALAR and ty[-1] not in types and len(ty) == 1:
        # `a b` is still a declaration in C; accept it
        pass
    rest = s
    # cut the type prefix textually
    m = re.match(r'\s*((?:(?:' + '|'.join(QUALS) + r')\s+)*[A-Za-z_][\w:]*)', s)
    rest = s[m.end():]
    vars_ = []
    for piece in split_top(rest, ','):
        mm = re.match(r'\s*([*&\s]*)([A-Za-z_]\w*)((?:\s*\[[^\]]*\])*)\s*(?:=(.*))?$', piece, re.S)
        if not mm:
            return None
        init = parse_expr(mm.group(4), types) if mm.group(4) is not None else None
        vars_.append([mm.group(2), mm.group(1).replace(' ', ''), mm.group(3).replace(' ', ''), init])
    return {'k': 'decl', 'ty': m.group(1), 'vars': vars_}


def parse_stmt(s, types):
    s = s.strip()
    if not s:
        return None
    if s == 'return' or s.startswith('return ') or s.startswith('return('):
        e = s[6:].strip()
        return {'k': 'ret', 'e': parse_expr(e, types) if e else None}
    try:
        d = parse_decl(s, types)
        if d:
            return d
    except SyntaxError:
        pass
    return {'k': 'expr', 'e': parse_expr(s, types)}


IFLINE = re.compile(r'^\s*if\s*\((.*)\)\s*(\{?)\s*$')


def parse_body(body, types):
    """List of statements: dicts with 'ind' and either parsed fields or 'raw'."""
    out = []
    for line in body.split('\n'):
        ind = line[:len(line) - len(line.lstrip())]
        st = line.strip()
        m = IFLINE.match(line)
        if m and '//' not in st and '/*' not in st:
            try:
                out.append({'k': 'if', 'ind': ind, 'e': parse_expr(m.group(1), types), 'tail': m.group(2)})
                continue
            except SyntaxError:
                pass
        if (not st or CTRL.match(line) or '//' in st or '/*' in st or not st.endswith(';')
                or '{' in st or '}' in st):
            out.append({'k': 'raw', 'text': line})
            continue
        pieces = [p for p in split_top(st, ';')]
        if pieces[-1].strip() != '':
            out.append({'k': 'raw', 'text': line})
            continue
        parsed = []
        try:
            for p in pieces[:-1]:
                x = parse_stmt(p, types)
                if x:
                    x['ind'] = ind
                    parsed.append(x)
        except SyntaxError:
            out.append({'k': 'raw', 'text': line})
            continue
        out.extend(parsed)
    return out


def render_stmt(s):
    k = s['k']
    if k == 'raw':
        return s['text']
    if k == 'if':
        return s['ind'] + 'if (' + pr(s['e']) + ')' + (' ' + s['tail'] if s['tail'] else '')
    if k == 'ret':
        return s['ind'] + 'return' + (' ' + pr(s['e']) if s['e'] else '') + ';'
    if k == 'expr':
        return s['ind'] + pr(s['e']) + ';'
    vs = []
    for name, stars, arr, init in s['vars']:
        vs.append(stars + name + arr + (' = ' + pr(init) if init is not None else ''))
    return s['ind'] + s['ty'] + ' ' + ', '.join(vs) + ';'


def stmt_exprs(s):
    """(container, index) slots holding the statement's expression roots."""
    if s['k'] in ('ret', 'expr', 'if') and s['e'] is not None:
        return [(s, 'e')]
    if s['k'] == 'decl':
        return [(v, 3) for v in s['vars'] if v[3] is not None]
    return []


def get_slot(c, i):
    return c[i]


def set_slot(c, i, v):
    c[i] = v


# --------------------------------------------------------------------------
# types

MEMBER_DECL = re.compile(r'^\s*(?:(?:const|volatile|unsigned|signed|struct|union|enum|static|mutable)\s+)*'
                         r'([A-Za-z_]\w*)\s+((?:[*&]*\s*[A-Za-z_]\w*(?:\s*\[[^\]]*\])*\s*,\s*)*[*&]*\s*[A-Za-z_]\w*(?:\s*\[[^\]]*\])*)\s*;', re.M)
TYPEDEF = re.compile(r'\btypedef\b[^;{]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*;|\b(?:struct|class|union|enum)\s+([A-Za-z_]\w*)')


def includes(path, text, ipaths, seen):
    for inc in re.findall(r'^\s*#\s*include\s*"([^"]+)"', text, re.M):
        for base in [os.path.dirname(path)] + ipaths:
            p = os.path.normpath(os.path.join(base, inc))
            if os.path.exists(p):
                if p not in seen:
                    seen.add(p)
                    try:
                        includes(p, open(p, errors='replace').read(), ipaths, seen)
                    except OSError:
                        pass
                break
    return seen


STRUCT_HEAD = re.compile(r'\b(?:typedef\s+)?(?:struct|class|union)\s+([A-Za-z_]\w*)?\s*(?::[^{;]*)?\{')


def brace_end(t, i):
    depth = 1
    while i < len(t) and depth:
        if t[i] == '{':
            depth += 1
        elif t[i] == '}':
            depth -= 1
        i += 1
    return i


class TypeInfo:
    def __init__(self, src, text, cmd):
        ipaths = re.findall(r'-i (\S+)', cmd)
        files = [src] + sorted(includes(src, text, ipaths, set()))
        self.types = set(SCALAR)
        self.fields = {}    # field name -> {(base, level)} over every struct
        self.sfields = {}   # struct name -> {field: (base, level)}
        self.rets = {}      # function name -> return type (base, level)
        for f in files:
            t = text if f == src else open(f, errors='replace').read()
            t = re.sub(r'/\*.*?\*/|//[^\n]*', '', t, flags=re.S)
            for m in TYPEDEF.finditer(t):
                self.types.add(m.group(1) or m.group(2))
            for m in STRUCT_HEAD.finditer(t):
                e = brace_end(t, m.end())
                body = t[m.end():e - 1]
                name = m.group(1)
                tail = re.match(r'\s*([A-Za-z_]\w*)\s*;', t[e:])
                if not name and tail and m.group(0).startswith('typedef'):
                    name = tail.group(1)
                if not name:
                    continue
                # only the struct's own level (drop nested bodies)
                flat = re.sub(r'\{[^{}]*\}', ';', body)
                d = self.sfields.setdefault(name, {})
                for fn, bl in self.members(flat):
                    d[fn] = bl
            for fn, bl in self.members(t):
                self.fields.setdefault(fn, set()).add(bl)
            for m in re.finditer(r'^\s*(?:static\s+|inline\s+|extern\s+)*(?:const\s+)?([A-Za-z_]\w*)\s*([*&]*)\s*([A-Za-z_]\w*)\s*\([^;{)]*\)\s*[;{]', t, re.M):
                if m.group(1) not in KEYWORDS:
                    self.rets.setdefault(m.group(3), (m.group(1), m.group(2).count('*')))

    @staticmethod
    def members(t):
        for m in MEMBER_DECL.finditer(t):
            base = m.group(1)
            if base in KEYWORDS or base in ('return', 'typedef'):
                continue
            for d in m.group(2).split(','):
                dm = re.match(r'\s*([*&]*)\s*([A-Za-z_]\w*)((?:\s*\[[^\]]*\])*)', d)
                if dm:
                    yield dm.group(2), (base, dm.group(1).count('*') + dm.group(3).count('['))

    def field(self, name, owner=None):
        if owner and owner in self.sfields and name in self.sfields[owner]:
            return self.sfields[owner][name]
        s = self.fields.get(name)
        if s and len(s) == 1:
            return next(iter(s))
        return None


def env_of(sig, stmts):
    env = {}
    for prm in split_top(sig, ','):
        prm = re.sub(r'=.*', '', prm).strip()
        m = re.match(r'((?:(?:const|volatile|unsigned|signed|struct)\s+)*)([A-Za-z_][\w:]*)\s*([*&\s]*)\s*([A-Za-z_]\w*)((?:\[[^\]]*\])*)$', prm)
        if m:
            env[m.group(4)] = (m.group(2), m.group(3).count('*') + m.group(5).count('['))
    for s in stmts:
        if s['k'] == 'decl':
            base = s['ty'].split()[-1]
            for name, stars, arr, _ in s['vars']:
                env[name] = (base, stars.count('*') + arr.count('['))
    return env


def typeof(n, env, ti, helpers):
    k = n.k
    if k == 'atom':
        t = n.t
        if re.match(r'^(\d+\.\d*|\.\d+|\d+[eE])', t) or (re.match(r'^\d', t) and t[-1] in 'fF' and not t.startswith('0x')):
            return ('float', 0) if t[-1] in 'fF' else ('double', 0)
        if re.match(r'^\d|^0x', t):
            return ('int', 0)
        return env.get(t)
    if k == 'mem':
        b = typeof(n.kids[0], env, ti, helpers)
        own = b[0] if b and b[1] == (1 if n.op == '->' else 0) else None
        return ti.field(n.t, own)
    if k == 'idx':
        b = typeof(n.kids[0], env, ti, helpers)
        return (b[0], b[1] - 1) if b and b[1] > 0 else None
    if k == 'un':
        b = typeof(n.kids[0], env, ti, helpers)
        if not b:
            return None
        if n.op == '*':
            return (b[0], b[1] - 1) if b[1] > 0 else None
        if n.op == '&':
            return (b[0], b[1] + 1)
        if n.op == '!':
            return ('int', 0)
        return b
    if k == 'cast':
        w = n.t.replace('*', ' * ').split()
        base = [x for x in w if x not in QUALS and x != '*']
        return (base[-1], w.count('*')) if base else None
    if k == 'call':
        f = n.kids[0]
        if f.k == 'atom' and f.t in helpers:
            return (helpers[f.t][0], 0)
        if f.k == 'atom':
            return ti.rets.get(f.t)
        return None
    if k == 'bin':
        if n.op in ('<', '<=', '>', '>=', '==', '!=', '&&', '||'):
            return ('int', 0)
        a = typeof(n.kids[0], env, ti, helpers)
        b = typeof(n.kids[1], env, ti, helpers)
        if a and a[1] > 0:
            return a if n.op in '+-' and not (b and b[1] > 0) else (('int', 0) if b and b[1] > 0 else None)
        if b and b[1] > 0:
            return b if n.op == '+' else None
        ca = SCALAR.get(a[0]) if a else None
        cb = SCALAR.get(b[0]) if b else None
        for fl in ('double', 'float'):
            if fl in (ca, cb):
                return (fl, 0)
        if ca and cb:
            return ('u32', 0) if 'u32' in (ca, cb) else ('int', 0)
        return None
    if k == 'tern':
        return typeof(n.kids[1], env, ti, helpers) or typeof(n.kids[2], env, ti, helpers)
    return None


def scalar_name(t):
    """Type name to use for a helper/temporary of type t, or None if not scalar."""
    if not t or t[1] != 0 or t[0] not in SCALAR:
        return None
    return t[0]


# --------------------------------------------------------------------------
# state, nodes and moves

class State:
    def __init__(self, stmts, helpers, ntemp=0, hist=()):
        self.stmts, self.helpers, self.ntemp, self.hist = stmts, helpers, ntemp, tuple(hist)

    def clone(self):
        return State(copy.deepcopy(self.stmts), dict(self.helpers), self.ntemp, self.hist)


def walk(n, path=(), cond=False, lval=False):
    """Yield (node, path, under_conditional, is_lvalue)."""
    yield n, path, cond, lval
    for i, c in enumerate(n.kids):
        c_cond = cond or (n.k == 'tern' and i > 0) or (n.k == 'bin' and n.op in ('&&', '||') and i > 0)
        c_lval = (n.k == 'asg' and i == 0) or (n.k == 'un' and n.op in ('&', '++', '--')) or n.k == 'post' \
            or (n.k == 'call' and i == 0) or (lval and n.k in ('mem', 'idx') and i == 0)
        yield from walk(c, path + (i,), c_cond, c_lval)


def node_at(root, path):
    for i in path:
        root = root.kids[i]
    return root


def replace_at(slot, path, new):
    c, i = slot
    if not path:
        c[i] = new
        return
    p = node_at(c[i], path[:-1])
    p.kids[path[-1]] = new


def all_nodes(st):
    for si, s in enumerate(st.stmts):
        for xi, (c, i) in enumerate(stmt_exprs(s)):
            for n, path, cond, lval in walk(c[i]):
                yield si, xi, n, path, cond, lval


def slot(st, si, xi):
    return stmt_exprs(st.stmts[si])[xi]


def tsuffix(t):
    return {'float': 'f', 'double': 'd', 'int': 'i', 'u32': 'u'}.get(t, re.sub(r'\W', '', t))


def add_helper(st, kind, op, t):
    s = tsuffix(t)
    if kind == 'id':
        name = f'Id_{s}'
        code = f'static inline {t} {name}({t} a) {{ return a; }}'
    elif kind == 'fwd':
        name = f'{OPNAME[op]}_{s}'
        code = f'static inline {t} {name}({t} a, {t} b) {{ return a {op} b; }}'
    elif kind == 'rev':
        name = f'{OPNAME[op]}R_{s}'
        code = f'static inline {t} {name}({t} b, {t} a) {{ return a {op} b; }}'
    elif kind == 'loc':
        name = f'{OPNAME[op]}V_{s}'
        code = f'static inline {t} {name}({t} a, {t} b) {{ {t} r = a {op} b; return r; }}'
    else:  # layered
        inner = add_helper(st, 'fwd', op, t)
        name = f'{OPNAME[op]}L_{s}'
        code = f'static inline {t} {name}({t} a, {t} b) {{ return {inner}(a, b); }}'
    st.helpers[name] = (t, code)
    return name


def uses(st, name, skip=None):
    cnt = 0
    for si, s in enumerate(st.stmts):
        if s['k'] == 'raw':
            cnt += len(re.findall(r'\b' + re.escape(name) + r'\b', s['text']))
            continue
        for c, i in stmt_exprs(s):
            for n, _, _, _ in walk(c[i]):
                if n.k == 'atom' and n.t == name and (si, n) != skip:
                    cnt += 1
    return cnt


def decl_front(st):
    """Index range of the leading declaration block."""
    i = 0
    while i < len(st.stmts) and st.stmts[i]['k'] in ('raw',) and not st.stmts[i]['text'].strip():
        i += 1
    a = i
    while i < len(st.stmts) and st.stmts[i]['k'] == 'decl':
        i += 1
    return a, i


def first_ind(st):
    inds = [s['ind'] for s in st.stmts if s['k'] != 'raw']
    return min(inds, key=len) if inds else '    '


class Ctx:
    def __init__(self, ti, sig, inlines, cpp):
        self.ti, self.sig, self.inlines, self.cpp = ti, sig, inlines, cpp


def _moves(st, ctx, allowed):
    """Yield (label, fn, si, xi, path); node-level fns accept base= (apply to another state)."""
    env = env_of(ctx.sig, st.stmts)
    H = st.helpers
    for si, xi, n, path, cond, lval in list(all_nodes(st)):
        if lval:
            continue
        t = typeof(n, env, ctx.ti, H)
        tn = scalar_name(t)
        if n.k == 'bin' and n.op in OPNAME and tn:
            for kind in ('fwd', 'rev', 'lay', 'loc'):
                if ('wrap' if kind in ('fwd', 'rev') else 'wrap2') not in allowed:
                    continue

                def f(si=si, xi=xi, path=path, kind=kind, tn=tn, base=None):
                    s2 = (base or st).clone()
                    nn = node_at(get_slot(*slot(s2, si, xi)), path)
                    name = add_helper(s2, kind, nn.op, tn)
                    a, b = nn.kids
                    args = [b, a] if kind == 'rev' else [a, b]
                    replace_at(slot(s2, si, xi), path, N('call', None, [N('atom', t=name)] + args))
                    return s2
                yield (f'wrap-{kind} {pr(n)[:40]}', f, si, xi, path)
        if n.k == 'mem' and n.op == '->' and tn and 'getter' in allowed:
            bt = typeof(n.kids[0], env, ctx.ti, H)
            if bt and bt[1] == 1 and re.match(r'^[A-Za-z_]\w*$', bt[0]):
                def f(si=si, xi=xi, path=path, tn=tn, bt=bt, base=None):
                    s2 = (base or st).clone()
                    nn = node_at(get_slot(*slot(s2, si, xi)), path)
                    name = f'Get_{bt[0]}_{nn.t}'
                    s2.helpers[name] = (tn, f'static inline {tn} {name}(const {bt[0]} *p) {{ return p->{nn.t}; }}')
                    replace_at(slot(s2, si, xi), path, N('call', None, [N('atom', t=name), nn.kids[0]]))
                    return s2
                yield (f'getter {pr(n)[:40]}', f, si, xi, path)
        if n.k == 'bin' and n.op in COMMUTATIVE and 'swap' in allowed:
            def f(si=si, xi=xi, path=path, base=None):
                s2 = (base or st).clone()
                nn = node_at(get_slot(*slot(s2, si, xi)), path)
                nn.kids.reverse()
                return s2
            yield (f'swap {pr(n)[:40]}', f, si, xi, path)
        if n.k == 'bin' and n.op in ('+', '*') and 'assoc' in allowed and t and t[1] == 0:
            l, r = n.kids
            if l.k == 'bin' and l.op == n.op:
                def f(si=si, xi=xi, path=path, base=None):
                    s2 = (base or st).clone()
                    nn = node_at(get_slot(*slot(s2, si, xi)), path)
                    (a, b), c = nn.kids[0].kids, nn.kids[1]
                    replace_at(slot(s2, si, xi), path, N('bin', nn.op, [a, N('bin', nn.op, [b, c])]))
                    return s2
                yield (f'assoc-r {pr(n)[:40]}', f, si, xi, path)
            if r.k == 'bin' and r.op == n.op:
                def f(si=si, xi=xi, path=path, base=None):
                    s2 = (base or st).clone()
                    nn = node_at(get_slot(*slot(s2, si, xi)), path)
                    a, (b, c) = nn.kids[0], nn.kids[1].kids
                    replace_at(slot(s2, si, xi), path, N('bin', nn.op, [N('bin', nn.op, [a, b]), c]))
                    return s2
                yield (f'assoc-l {pr(n)[:40]}', f, si, xi, path)
        if tn and n.k != 'atom' and 'id' in allowed and not (n.k == 'call' and n.kids[0].k == 'atom' and n.kids[0].t.startswith('Id_')):
            def f(si=si, xi=xi, path=path, tn=tn, base=None):
                s2 = (base or st).clone()
                nn = node_at(get_slot(*slot(s2, si, xi)), path)
                name = add_helper(s2, 'id', None, tn)
                replace_at(slot(s2, si, xi), path, N('call', None, [N('atom', t=name), nn]))
                return s2
            yield (f'id {pr(n)[:40]}', f, si, xi, path)
        lit_or_global = n.k == 'atom' and (re.match(r'^[\d.]', n.t) or (n.t not in env and re.match(r'^[A-Za-z_]\w*$', n.t)))
        if tn and (n.k != 'atom' or lit_or_global) and not cond and 'hoist' in allowed and path != ():
            for where in ('front', 'back'):
                def f(si=si, xi=xi, path=path, tn=tn, where=where, base=None):
                    s2 = (base or st).clone()
                    nn = node_at(get_slot(*slot(s2, si, xi)), path)
                    name = f't{s2.ntemp}'
                    s2.ntemp += 1
                    replace_at(slot(s2, si, xi), path, N('atom', t=name))
                    ind = s2.stmts[si]['ind']
                    s2.stmts.insert(si, {'k': 'expr', 'ind': ind, 'e': N('asg', '=', [N('atom', t=name), nn])})
                    a, b = decl_front(s2)
                    d = {'k': 'decl', 'ind': first_ind(s2), 'ty': tn, 'vars': [[name, '', '', None]]}
                    s2.stmts.insert(a if where == 'front' else b, d)
                    return s2
                yield (f'hoist-{where} {pr(n)[:40]}', f, si, xi, path)
        if n.k == 'call' and n.kids[0].k == 'atom' and n.kids[0].t in ctx.inlines and 'expand' in allowed:
            params, body = ctx.inlines[n.kids[0].t]
            if len(params) == len(n.kids) - 1:
                def f(si=si, xi=xi, path=path, params=params, body=body, base=None):
                    s2 = (base or st).clone()
                    nn = node_at(get_slot(*slot(s2, si, xi)), path)
                    args = dict(zip(params, nn.kids[1:]))
                    e = copy.deepcopy(body)

                    def sub(x):
                        if x.k == 'atom' and x.t in args:
                            return copy.deepcopy(args[x.t])
                        x.kids = [sub(c) for c in x.kids]
                        return x
                    replace_at(slot(s2, si, xi), path, sub(e))
                    return s2
                yield (f'expand {n.kids[0].t}', f, si, xi, path)

    # statement-level moves
    for si, s in enumerate(st.stmts):
        # accum: x = l OP r  ->  x = l; x = x OP r;
        tgt = None
        if s['k'] == 'expr' and s['e'].k == 'asg' and s['e'].op == '=' and s['e'].kids[0].k == 'atom':
            tgt, rhs = s['e'].kids[0].t, s['e'].kids[1]
        elif s['k'] == 'decl' and len(s['vars']) == 1 and s['vars'][0][3] is not None and not s['vars'][0][1]:
            tgt, rhs = s['vars'][0][0], s['vars'][0][3]
        if tgt and any(y.k == 'atom' and y.t == tgt for y, _, _, _ in walk(rhs)):
            tgt = None  # x = f(x): splitting would clobber x
        if tgt and 'accum' in allowed and rhs.k in ('bin', 'call') and (rhs.k == 'call' or rhs.op in OPNAME):
            # x = E(c, ...)  ->  x = c; x = E(x, ...)   for each non-atom operand c
            for ci in range(1 if rhs.k == 'call' else 0, len(rhs.kids)):
                if rhs.kids[ci].k == 'atom':
                    continue

                def f(si=si, ci=ci, tgt=tgt):
                    s2 = st.clone()
                    x = s2.stmts[si]
                    r = x['e'].kids[1] if x['k'] == 'expr' else x['vars'][0][3]
                    keep = r.kids[ci]
                    r.kids[ci] = N('atom', t=tgt)
                    if x['k'] == 'expr':
                        x['e'].kids[1] = keep
                    else:
                        x['vars'][0][3] = keep
                    s2.stmts.insert(si + 1, {'k': 'expr', 'ind': x['ind'],
                                             'e': N('asg', '=', [N('atom', t=tgt), r])})
                    return s2
                yield (f'accum{ci} {tgt}', f, None, None, None)
        # unvar: single-use local substituted into its use
        if tgt and 'unvar' in allowed and uses(st, tgt) == (2 if s['k'] == 'expr' else 1):
            later = [j for j in range(si + 1, len(st.stmts)) if st.stmts[j]['k'] != 'raw'
                     and any(nn.k == 'atom' and nn.t == tgt for c, i in stmt_exprs(st.stmts[j]) for nn, _, _, _ in walk(c[i]))]
            if later:
                def f(si=si, tgt=tgt, j=later[0]):
                    s2 = st.clone()
                    x = s2.stmts[si]
                    r = x['e'].kids[1] if x['k'] == 'expr' else x['vars'][0][3]
                    for c, i in stmt_exprs(s2.stmts[j]):
                        def sub(y):
                            if y.k == 'atom' and y.t == tgt:
                                return r
                            y.kids = [sub(z) for z in y.kids]
                            return y
                        c[i] = sub(c[i])
                    if x['k'] == 'decl':
                        del s2.stmts[si]
                    else:
                        del s2.stmts[si]
                        for d in s2.stmts:
                            if d['k'] == 'decl':
                                d['vars'] = [v for v in d['vars'] if v[0] != tgt]
                        s2.stmts = [d for d in s2.stmts if not (d['k'] == 'decl' and not d['vars'])]
                    return s2
                yield (f'unvar {tgt}', f, None, None, None)
    if 'setter' in allowed:
        yield from setter_moves(st, ctx, env)
    if 'declswap' in allowed:
        a, b = decl_front(st)
        for i in range(a, b):
            d = st.stmts[i]
            for j in range(len(d['vars']) - 1):
                def f(i=i, j=j):
                    s2 = st.clone()
                    v = s2.stmts[i]['vars']
                    v[j], v[j + 1] = v[j + 1], v[j]
                    return s2
                yield (f'declswap {d["vars"][j][0]}/{d["vars"][j + 1][0]}', f, None, None, None)
            if i + 1 < b:
                def f(i=i):
                    s2 = st.clone()
                    s2.stmts[i], s2.stmts[i + 1] = s2.stmts[i + 1], s2.stmts[i]
                    return s2
                yield (f'declswap #{i - a}', f, None, None, None)


def setter_moves(st, ctx, env):
    """p->f1 = e1; p->f2 = e2; ... (2-4 consecutive stores through one pointer)
    -> Set(p, e..) inline with every parameter order (args evaluate right to left)."""
    import itertools
    i = 0
    while i < len(st.stmts):
        j = i
        base = None
        while j < len(st.stmts) and j - i < 4:
            x = st.stmts[j]
            if not (x['k'] == 'expr' and x['e'].k == 'asg' and x['e'].op == '=' and x['e'].kids[0].k == 'mem'
                    and x['e'].kids[0].op == '->' and x['e'].kids[0].kids[0].k == 'atom'):
                break
            b = x['e'].kids[0].kids[0].t
            if base is None:
                base = b
            elif b != base:
                break
            j += 1
        if j - i >= 2:
            bt = env.get(base)
            fields = [st.stmts[k]['e'].kids[0].t for k in range(i, j)]
            tys = [scalar_name(ctx.ti.field(fl, bt[0] if bt else None)) for fl in fields]
            if bt and bt[1] == 1 and all(tys) and len(set(fields)) == len(fields):
                n = j - i
                for perm in itertools.permutations(range(n)):
                    def f(i=i, j=j, perm=perm, bt=bt, fields=fields, tys=tys, base=base):
                        s2 = st.clone()
                        vals = [s2.stmts[k]['e'].kids[1] for k in range(i, j)]
                        tag = ''.join(str(q) for q in perm)
                        name = f'Set_{bt[0]}_{"".join(fl[:2] for fl in fields)}_{tag}'
                        params = ', '.join(f'{tys[q]} a{q}' for q in perm)
                        body = ' '.join(f'p->{fields[q]} = a{q};' for q in range(n))
                        s2.helpers[name] = ('void', f'static inline void {name}({bt[0]} *p, {params}) {{ {body} }}')
                        call = N('call', None, [N('atom', t=name), N('atom', t=base)] + [vals[q] for q in perm])
                        ind = s2.stmts[i]['ind']
                        s2.stmts[i:j] = [{'k': 'expr', 'ind': ind, 'e': call}]
                        return s2
                    yield (f'setter {base}->{",".join(fields)} order {perm}', f, None, None, None)
            i = j
        else:
            i += 1


def skeleton(n):
    if n.k == 'atom':
        return 'A'
    return '(' + n.k + (n.op or '') + (n.t if n.k == 'mem' else '') + ' ' + ' '.join(skeleton(c) for c in n.kids) + ')'


def moves(st, ctx, allowed):
    """Yield (label, fn) where fn() returns a new State or None. With 'sym',
    a node move is also offered applied at the same place in every statement
    with the same expression skeleton (x/y/z component triples)."""
    groups = {}
    for si, s in enumerate(st.stmts):
        ex = stmt_exprs(s)
        if len(ex) == 1:
            groups.setdefault(skeleton(ex[0][0][ex[0][1]]), []).append(si)
    done = set()
    for label, f, si, xi, path in _moves(st, ctx, allowed):
        yield label, f, si
        if si is None or 'sym' not in allowed:
            continue
        ex = stmt_exprs(st.stmts[si])
        if len(ex) != 1:
            continue
        sib = groups.get(skeleton(ex[0][0][ex[0][1]]), [])
        kind = label.split()[0]
        if len(sib) < 2 or kind.startswith('hoist') or (kind, path, tuple(sib)) in done:
            continue
        done.add((kind, path, tuple(sib)))

        def g(f=f, sib=sib):
            s2 = None
            for sj in sib:
                s2 = f(si=sj, base=s2)
            return s2
        yield (f'sym-{label} x{len(sib)}', g, si)


def find_inlines(text, types):
    """static inline helpers whose body is a single `return expr;`."""
    out = {}
    for m in re.finditer(r'(?:static\s+)?inline\s+[^;{()]*?\b(\w+)\s*\(([^)]*)\)\s*\{\s*return\s+([^;]*);\s*\}', text):
        params = []
        for p in split_top(m.group(2), ','):
            v = re.findall(r'[A-Za-z_]\w*', p)
            if v and v != ['void']:
                params.append(v[-1])
        try:
            out[m.group(1)] = (params, parse_expr(m.group(3), types))
        except SyntaxError:
            pass
    return out


# --------------------------------------------------------------------------
# rendering / scoring

class Sweep:
    def __init__(self, a):
        self.a = a
        self.u = ps.Unit(a.unit)
        self.text = self.u.text
        self.cpp = self.u.ext != '.c'
        if getattr(a, 'start_tu', None):
            self.text = open(a.start_tu).read()
        if a.start:
            self.text = self.splice_start(open(a.start).read())
        self.u.text = self.text
        d, self.sym = self.u.resolve(a.fn, a.demangled)
        if not d:
            sys.exit('definition not found')
        self.d = d
        ls, bs, be = d
        self.head = self.text[ls:bs]
        self.sig = self.head[self.head.find('(') + 1:self.head.rfind(')')]
        self.ti = TypeInfo(self.u.src, self.text, self.u.cmd)
        body = self.text[bs:be - 1]
        stmts = parse_body(body, self.ti.types)
        self.ctx = Ctx(self.ti, self.sig, find_inlines(self.text[:ls], self.ti.types), self.cpp)
        self.init = State(stmts, {})
        self.cc = a.cc or self.u.cc
        self.cache = {}
        self.dbgcache = {}
        os.makedirs(TMP, exist_ok=True)
        self.log = open(f'{TMP}/{a.fn}.log.jsonl', 'a')

    def splice_start(self, start):
        """Replace the current definition of fn (and nothing else) by start's text."""
        d, _ = ps.Unit.resolve(self.u, self.a.fn, self.a.demangled)
        if not d:
            sys.exit('definition not found (for --start)')
        ls, bs, be = d
        return self.text[:ls] + start.rstrip() + '\n' + self.text[be:]

    def func_text(self, st):
        ls, bs, be = self.d
        helpers = ''.join(code + '\n' for _, (t, code) in sorted(st.helpers.items(), key=lambda kv: ('L_' in kv[0], kv[0])))
        body = '\n'.join(render_stmt(s) for s in st.stmts)
        return helpers + self.head + body + '}'

    def render(self, st):
        ls, bs, be = self.d
        f = self.func_text(st)
        if self.a.pragma:
            f = '#pragma push\n' + ''.join(f'#pragma {p}\n' for p in self.a.pragma) + f + '\n#pragma pop'
        return self.text[:ls] + f + self.text[be:]

    def stmt_lines(self, st):
        """1-based source line of each statement in the rendered TU."""
        txt = self.render(st)
        ls = self.d[0]
        f = self.func_text(st)
        pre = txt[:txt.index(f)] if f in txt else self.text[:ls]
        start = pre.count('\n') + 1 + (f.count('\n') - '\n'.join(render_stmt(x) for x in st.stmts).count('\n'))
        out, ln = [], start
        for x in st.stmts:
            out.append(ln)
            ln += render_stmt(x).count('\n') + 1
        return out

    def score(self, text, wk):
        h = hashlib.sha1(text.encode()).hexdigest()
        if h in self.cache:
            return self.cache[h]
        s = self.u.compile_score(text, self.a.fn, self.cc, wk)
        self.cache[h] = s
        return s

    # ---- mwccdbg tie-break
    def dbg_key(self, text):
        h = hashlib.sha1(text.encode()).hexdigest()
        if h in self.dbgcache:
            return self.dbgcache[h]
        k = dbg_analyze(self.u, text, self.sym or self.a.fn, self.a.fn, self.cc)
        self.dbgcache[h] = k
        return k


def dbg_analyze(u, text, sym, fn, cc):
    """(-first_mismatch_position, n_mismatching_vregs) from mwccdbg, or (0, 999)."""
    try:
        import mwccdbg as md
    except ImportError:
        return (0, 999, None)
    out = os.path.join(TMP, 'dbg')
    os.makedirs(out, exist_ok=True)
    sp = os.path.join(os.path.dirname(os.path.abspath(u.src)), f'.shapesweep_dbg{u.ext}')
    open(sp, 'w').write(text)
    try:
        o = os.path.join(out, 'ours')
        os.makedirs(o, exist_ok=True)
        c = re.sub(r'GC/[^/]+/mwcceppc', f'GC/{cc}/mwcceppc', u.cmd)
        c = re.sub(r'-c \S+ -o \S+', f'-c {sp} -o {o}', c)
        subprocess.run(c, shell=True, capture_output=True)
        objs = [os.path.join(o, x) for x in os.listdir(o) if x.endswith('.o')]
        if not objs:
            return (0, 999, None)
        ours = max(objs, key=os.path.getmtime)
        toks = shlex.split(u.cmd)
        i = next(k for k, t in enumerate(toks) if t.endswith('mwcceppc.exe'))
        toks = toks[i:]
        m = re.search(r'GC/([^/]+)/mwcceppc\.exe', toks[0])
        sup = md.TO_SUPPORTED.get(cc if cc else m.group(1))
        if not sup:
            return (0, 999, None)
        toks[0] = re.sub(r'GC/[^/]+/', f'GC/{sup}/', toks[0])
        ci = toks.index('-c')
        toks[ci + 1] = sp
        oi = toks.index('-o')
        toks[oi + 1] = os.path.join(out, 'dbg.o')
        toks[oi:oi] = ['-sym', 'on']
        if '-MMD' in toks:
            toks.remove('-MMD')
        res = md.analyze(toks, sym, ours, f'build/GNLJ82/obj/{u.obj}.o', out_dir=out)
    finally:
        try:
            os.remove(sp)
        except OSError:
            pass
    if res is None:
        return (0, 999, None)
    bad = [r for r in res if r['bad']]
    if not bad:  # diff not explained by vregs (stand-in compiler or opcode diffs): no signal
        return (0, 999, None)
    first = min((r['pos'] for r in bad), default=10**4)
    nbad = len(bad)
    line = None
    if bad:
        m = re.match(r'\s*(\d+)', min(bad, key=lambda r: r['pos'])['where'])
        line = int(m.group(1)) if m else None
    return (-first, nbad, line)


# --------------------------------------------------------------------------
# search

ALL_MOVES = ['wrap', 'wrap2', 'id', 'hoist', 'accum', 'unvar', 'expand', 'swap', 'assoc', 'declswap', 'sym',
             'getter', 'setter']
# fn_8019EB9C review (11-09): MWCC canonicalises commutative operand order and
# macro expansion removes the inline-argument vreg ordering, so for diffs that
# are register numbers only, use just the vreg-order moves.
REG_ONLY_MOVES = ['wrap', 'wrap2', 'id', 'hoist', 'accum', 'unvar', 'declswap', 'sym', 'getter', 'setter']


def reg_only(fn, sym=None, ms=None):
    """True when the variant just scored by worker 0 (its disassembly ms) has
    exactly the target's opcode sequence."""
    T = ps.target_body(fn)
    ms = ms or f'{ps.TMP}/w{os.getpid()}_0/m.s'
    if not T or not os.path.exists(ms):
        return False
    B = ps.norm_body(ms, fn) or (ps.norm_body(ms, sym) if sym else None)
    if not B or len(B) != len(T):
        return False
    return all(a.split()[0] == b.split()[0] for a, b in zip(T, B) if a.split() and b.split())


def search(sw, a):
    rnd = random.Random(a.seed)
    init_text = sw.render(sw.init)
    s0 = sw.score(init_text, 0)
    if a.moves:
        allowed = set(a.moves.split(','))
    else:
        ro = reg_only(a.fn, sw.sym)
        allowed = set(REG_ONLY_MOVES if ro else ALL_MOVES)
        print(f'[shapesweep] diff is {"register numbers only" if ro else "not register-only"}: '
              f'{len(allowed)} move kinds', flush=True)
        if getattr(a, 'reg_only', False) and not ro and s0 != 0:
            sw.skipped = 'not register-only'
            return s0, (s0, (0, 999, None), sw.init, init_text)
    print(f'[shapesweep] {a.unit} {a.fn} GC/{sw.cc} {" ".join(a.pragma or [])}: start {s0} diff lines', flush=True)
    beam = [(s0, sw.dbg_key(init_text) if a.dbg else (0, 999, None), sw.init, init_text)]
    if a.dbg:
        print(f'[shapesweep] mwccdbg start: {beam[0][1][1]} mismatching vregs, first at colouring #{-beam[0][1][0]}, line {beam[0][1][2]}', flush=True)
    best = beam[0]
    stale = 0
    seen = {hashlib.sha1(init_text.encode()).hexdigest()}
    total = 0
    t0 = time.time()
    for rnd_i in range(a.rounds):
        cands = []
        for _, k, st, _ in beam:
            if len(st.hist) >= a.max_depth:
                continue
            focus = set()
            if len(k) > 2 and k[2]:
                lines = sw.stmt_lines(st)
                focus = {i for i, l in enumerate(lines) if l == k[2]}
            for label, f, si in moves(st, sw.ctx, allowed):
                cands.append((0 if si in focus else 1, rnd.random(), st, label, f))
        # moves on the statement that defines the first diverging vreg first
        cands.sort(key=lambda c: (c[0], c[1]))
        cands = [c[2:] for c in cands]
        new = []
        for st, label, f in cands:
            if len(new) >= a.sample:
                break
            try:
                s2 = f()
            except Exception as e:  # a move that does not apply here
                continue
            if s2 is None:
                continue
            s2.hist = st.hist + (label,)
            txt = sw.render(s2)
            h = hashlib.sha1(txt.encode()).hexdigest()
            if h in seen:
                continue
            seen.add(h)
            new.append((s2, txt))
        if not new:
            print('[shapesweep] no new variants', flush=True)
            break

        def run(item, _ids=iter(range(10**9))):
            s2, txt = item
            return sw.score(txt, ps.worker_id())
        with ThreadPoolExecutor(a.jobs, initializer=ps._init_worker) as ex:
            sc = list(ex.map(run, new))
        total += len(new)
        for (s2, txt), s in zip(new, sc):
            sw.log.write(json.dumps({'fn': a.fn, 'score': s, 'hist': list(s2.hist)}) + '\n')
        pool = beam + [(s, (0, 999, None), s2, txt) for (s2, txt), s in zip(new, sc) if s < 10**6]
        pool.sort(key=lambda r: (r[0], len(r[2].hist)))
        # mwccdbg tie-break among the best-scored states
        if a.dbg and pool and pool[0][0] > 0:
            # mwccdbg is the primary key among the states within --dbg-slack
            # diff lines of the best: fewer mismatching vregs, first one later
            top, seen_t = [], set()
            for r in pool:
                if r[0] > pool[0][0] + a.dbg_slack or len(top) >= a.dbg:
                    break
                if r[3] not in seen_t:
                    seen_t.add(r[3])
                    top.append(r)
            keyed = [(r[0], sw.dbg_key(r[3]), r[2], r[3]) for r in top]
            ids = {id(r[2]) for r in top}
            rest = [r for r in pool if id(r[2]) not in ids]
            keyed.sort(key=lambda r: (r[1][1], r[1][0], r[0], len(r[2].hist)))
            pool = keyed + rest
        # diversity: at most a.beam distinct texts, and not all children of one parent
        nb, seen_txt, uniq = [], set(), []
        for r in pool:
            if r[3] not in seen_txt:
                seen_txt.add(r[3])
                uniq.append(r)
        # elite part (best scores, then fewer moves) + explore part: random
        # picks among the next 4*beam, so a worse intermediate shape that a
        # second move could fix is not always thrown away
        ne = max(1, int(round(a.beam * (1 - a.explore))))
        nb = uniq[:ne]
        rest = uniq[ne:ne + 4 * a.beam]
        nb += rnd.sample(rest, min(len(rest), a.beam - ne))
        beam = nb
        if beam[0][0] < best[0] or (beam[0][0] == best[0] and beam[0][1][:2] < best[1][:2]):
            best = beam[0]
            stale = 0
        else:
            stale += 1
        print(f'[shapesweep] round {rnd_i + 1}: {len(new)} variants, best {best[0]} '
              f'{"dbg " + str(best[1]) + " " if a.dbg else ""}'
              f'({total} total, {time.time() - t0:.0f}s) via {" | ".join(best[2].hist) or "-"}', flush=True)
        if best[0] == 0 or stale >= a.patience:
            break
        if a.minutes and time.time() - t0 > a.minutes * 60:
            print('[shapesweep] time budget used up', flush=True)
            break
    return s0, best


def cmd_batch(a):
    """Sweep every near miss in NonMatching TUs (report.json), unattended.
    Never writes src/: a match is saved to OUT/hits/FN.<ext> (full TU) and
    FN.fn.txt (the function + helpers) for a claim-first landing by hand."""
    import importlib.util
    spec = importlib.util.spec_from_file_location('autopipe_mod', os.path.join(os.path.dirname(__file__), 'autopipe.py'))
    ap = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(ap)
    out = a.out
    os.makedirs(out + '/hits', exist_ok=True)
    who = os.environ.get('MKGP2_THREAD', 'shapesweep')
    res_path = f'{out}/results_{who}.jsonl'
    done = set()
    for f in os.listdir(out):
        if f.startswith('results') and f.endswith('.jsonl'):
            for l in open(os.path.join(out, f)):
                try:
                    r = json.loads(l)
                    done.add((r['obj'], r['fn']))
                except (ValueError, KeyError):
                    pass
    claimed = set()
    if a.claims:
        claimed = {l.strip() for l in open(a.claims) if l.strip() and not l.startswith('#')}
    a.min, a.max_size = a.min_pct, a.max_size
    cands = [c for c in ap.candidates(a) if c[0] < a.max_pct]
    if a.only:
        keep = set(a.only.split(','))
        cands = [c for c in cands if c[2] in keep]
    for pct, obj, fn, size, dm in cands:
        if (obj, fn) in done and not a.only and not a.retry:
            continue
        src = next((f'src/{obj}{e}' for e in ('.c', '.cpp', '.cp') if os.path.exists(f'src/{obj}{e}')), None)
        if not src or src in claimed or obj in claimed:
            continue
        if os.path.exists(os.path.join(out, 'STOP')):
            print('[shapesweep] STOP file, exiting')
            return
        b = argparse.Namespace(**vars(a))
        b.unit, b.fn, b.demangled, b.start = obj, fn, dm if dm and '::' in (dm or '') else None, None
        b.start_tu = None
        # chain after autopipe99: start from its best pragma/cc/decl/stmt source
        import glob as _g
        bests = []
        for pth in _g.glob(f'{a.chain}/{fn}_*'):
            mm = re.match(r'.*_([\d.]+)_GC([\w.]+)\.\w+$', pth)
            if mm:
                bests.append((float(mm.group(1)), mm.group(2), pth))
        if bests:
            _, b.cc, b.start_tu = max(bests)
        qid = ap.q_claim(fn, obj, pct)
        if qid is None:
            print(f'[shapesweep] {fn}: queue item held by someone else, skipped', flush=True)
            continue
        t0 = time.time()
        rec = {'obj': obj, 'fn': fn, 'pct': pct, 'size': size, 'start_tu': b.start_tu}
        try:
            sw = Sweep(b)
            s0, best = search(sw, b)
            rec.update(start=s0, best=best[0], moves=list(best[2].hist))
            if getattr(sw, 'skipped', None):
                rec['skipped'] = sw.skipped
            if best[0] == 0 and s0 != 0:
                open(f'{out}/hits/{fn}{sw.u.ext}', 'w').write(best[3])
                open(f'{out}/hits/{fn}.fn.txt', 'w').write(sw.func_text(best[2]) + '\n')
                print(f'[shapesweep] HIT {fn}: saved to {out}/hits/', flush=True)
        except SystemExit as e:
            rec['error'] = str(e)
        except Exception as e:  # keep the batch going
            rec['error'] = f'{type(e).__name__}: {e}'
        rec['secs'] = int(time.time() - t0)
        rec['t'] = time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())
        with open(res_path, 'a') as f:
            f.write(json.dumps(rec) + '\n')
        try:
            if rec.get('best') == 0 or rec.get('skipped') or rec.get('error'):
                ap.q_close(qid, 'release', '')
            else:
                ap.q_close(qid, 'park', f'shapesweep: {rec.get("start")} -> {rec.get("best")} lines '
                           f'({" | ".join(rec.get("moves", []))[:200]})')
        except Exception as e:
            print(f'[shapesweep] queue close failed: {e}', flush=True)
        print(f'[shapesweep] {fn} {pct}%: {rec.get("start")} -> {rec.get("best")} {rec.get("error", "")}', flush=True)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0],
                                 formatter_class=argparse.RawDescriptionHelpFormatter, epilog=__doc__)
    ap.add_argument('unit', help='object path as in configure.py without extension, e.g. game/kartmove/carobject')
    ap.add_argument('fn', help='target symbol')
    ap.add_argument('--demangled', help='Class::Method if the def is not found by symbol name')
    ap.add_argument('--start', help='file with a replacement definition to start from')
    ap.add_argument('--pragma', action='append', help="e.g. 'opt_propagation off' (repeatable)")
    ap.add_argument('--cc', help='compiler version (default: the TU\'s)')
    ap.add_argument('--moves', help='comma list, default all: ' + ','.join(ALL_MOVES))
    ap.add_argument('--beam', type=int, default=8)
    ap.add_argument('--rounds', type=int, default=12)
    ap.add_argument('--sample', type=int, default=300, help='max new variants per round')
    ap.add_argument('--max-depth', type=int, default=10, help='max moves stacked on one state')
    ap.add_argument('--patience', type=int, default=3, help='stop after N rounds without improvement')
    ap.add_argument('--dbg', type=int, default=0, help='mwccdbg tie-break on the K best tied states per round')
    ap.add_argument('--dbg-slack', type=int, default=4, help='diff-line slack for the mwccdbg-ranked set')
    ap.add_argument('--start-tu', help='full TU source to start from (e.g. setup/autopipe99/best/FN_PCT_GCcc.cpp)')
    ap.add_argument('--explore', type=float, default=0.4, help='fraction of the beam picked at random from the runners-up')
    ap.add_argument('--seed', type=int, default=1)
    ap.add_argument('-j', '--jobs', type=int, default=4)
    ap.add_argument('--apply', action='store_true', help='write the best variant into src/ when it matches')
    ap.add_argument('--show', action='store_true', help='parse, print the starting function and the move list, exit')
    ap.add_argument('--minutes', type=float, default=0, help='time budget per function (0 = none)')
    if len(sys.argv) > 1 and sys.argv[1] == 'batch':
        bp = argparse.ArgumentParser(prog='shapesweep.py batch')
        bp.add_argument('batch')
        bp.add_argument('--min-pct', type=float, default=99.0)
        bp.add_argument('--max-pct', type=float, default=100.0)
        bp.add_argument('--max-size', type=int, default=2000)
        bp.add_argument('--only', help='comma list of fns')
        bp.add_argument('--retry', action='store_true', help='ignore earlier results')
        bp.add_argument('--reg-only', action='store_true', help='only functions whose opcodes already match')
        bp.add_argument('--chain', default='/mnt/project-files/setup/autopipe99/best',
                        help='start from FN_PCT_GCcc.<ext> full-TU files found here')
        bp.add_argument('--claims', help='file of claimed TU paths (src/... or obj) to skip')
        bp.add_argument('--out', default='/mnt/project-files/setup/shapesweep')
        for k, v in (('--beam', 6), ('--rounds', 8), ('--sample', 200), ('--max-depth', 8), ('--patience', 2),
                     ('--dbg', 0), ('--seed', 1), ('-j', 4), ('--minutes', 6.0), ('--explore', 0.4), ('--dbg-slack', 4)):
            bp.add_argument(k, type=type(v), default=v, **({'dest': 'jobs'} if k == '-j' else {}))
        bp.add_argument('--moves')
        bp.add_argument('--pragma', action='append')
        bp.add_argument('--cc')
        return cmd_batch(bp.parse_args())
    a = ap.parse_args()
    sw = Sweep(a)
    if a.show:
        print(sw.func_text(sw.init))
        for label, _, _ in moves(sw.init, sw.ctx, set(a.moves.split(',')) if a.moves else set(ALL_MOVES)):
            print('  move:', label)
        return
    s0, best = search(sw, a)
    ext = sw.u.ext
    bp = f'{TMP}/{a.fn}.best{ext}'
    open(bp, 'w').write(best[3])
    print(f'\n[shapesweep] {a.fn}: {s0} -> {best[0]} diff lines; moves: {" | ".join(best[2].hist) or "-"}')
    print(sw.func_text(best[2]))
    print(f'best TU source: {bp}')
    if a.apply and best[0] == 0:
        open(sw.u.src, 'w').write(best[3])
        print(f'applied to {sw.u.src}')


if __name__ == '__main__':
    main()
