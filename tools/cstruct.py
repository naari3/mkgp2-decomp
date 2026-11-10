#!/usr/bin/env python3
"""Small C declaration reader: struct/union/typedef/enum layouts for 32-bit PowerPC EABI.

Used by tools/autodata.py to turn a blob into a struct initialiser. It reads
preprocessed C or C++ (mwcc -E) or a plain header, keeps file-scope typedefs, tagged
and untagged structs, unions and enum constants, and computes offsets the way
Metrowerks does with `-align powerpc -enum int` (scalars aligned to their size,
double and long long to 8, struct to its widest member). Anything it does not
understand (bitfields, base classes, virtual functions, sizeof in a dimension) marks
that one type as unsupported; other types in the file still work.

  python3 tools/cstruct.py FILE.c TypeName      # print the layout (FILE is preprocessed with the TU's flags)
"""
import os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

TOKEN = re.compile(r'''
    (?P<ws>\s+|//[^\n]*|/\*.*?\*/)
  | (?P<pp>^[ \t]*\#[^\n]*(?:\\\n[^\n]*)*)
  | (?P<str>L?"(?:\\.|[^"\\])*"|L?'(?:\\.|[^'\\])*')
  | (?P<num>0[xX][0-9a-fA-F]+[uUlL]*|\d+\.\d*(?:[eE][+-]?\d+)?[fFlL]?|\d+[uUlL]*)
  | (?P<id>[A-Za-z_]\w*)
  | (?P<op>::|->|<<|>>|[{}()\[\];,*=:&<>~!+\-/%^|?.])
''', re.X | re.S | re.M)

BASE = {
    'char': ('char', 1), 'signed char': ('schar', 1), 'unsigned char': ('uchar', 1), 'bool': ('uchar', 1),
    'short': ('short', 2), 'unsigned short': ('ushort', 2), 'wchar_t': ('ushort', 2),
    'int': ('int', 4), 'unsigned int': ('uint', 4), 'long': ('int', 4), 'unsigned long': ('uint', 4),
    'long long': ('llong', 8), 'unsigned long long': ('ullong', 8),
    'float': ('float', 4), 'double': ('double', 8), 'long double': ('double', 8), 'void': ('void', 0),
}
SPELL = {'char': 'char', 'schar': 'signed char', 'uchar': 'unsigned char', 'short': 'short', 'ushort': 'unsigned short',
         'int': 'int', 'uint': 'unsigned int', 'llong': 'long long', 'ullong': 'unsigned long long',
         'float': 'float', 'double': 'double', 'void': 'void'}
QUAL = {'const', 'volatile', 'static', 'extern', 'register', 'inline', 'mutable', '__inline', 'restrict', '__restrict', 'typename'}
WORDS = {'signed', 'unsigned', 'short', 'long', 'char', 'int', 'float', 'double', 'void', 'bool', 'wchar_t'}


class Unsupported(Exception):
    pass


class Type:
    """kind: scalar(name) | ptr(target text) | array(elem, n) | struct(fields, union) | bad(reason)"""
    def __init__(self, kind, **kw):
        self.kind = kind
        self.__dict__.update(kw)

    def size_align(self):
        k = self.kind
        if k == 'scalar': return self.size, max(1, self.size)
        if k == 'ptr': return 4, 4
        if k == 'array':
            s, a = self.elem.size_align()
            return s * self.n, a
        if k == 'struct':
            self.layout()
            return self.size, self.align
        raise Unsupported(getattr(self, 'reason', 'unsupported type'))

    def layout(self):
        if getattr(self, '_done', False): return
        if getattr(self, '_busy', False): raise Unsupported('recursive struct')
        self._busy = True
        off, al, big = 0, 1, 0
        out = []
        for name, t in self.members:
            s, a = t.size_align()
            if self.union:
                out.append((name, t, 0)); big = max(big, s)
            else:
                off = (off + a - 1) // a * a
                out.append((name, t, off)); off += s
            al = max(al, a)
        size = big if self.union else off
        self.size = (size + al - 1) // al * al
        self.align = al
        self.fields = out
        self._busy = False
        self._done = True


def scalar(kind):
    size = {'char': 1, 'schar': 1, 'uchar': 1, 'short': 2, 'ushort': 2, 'int': 4, 'uint': 4, 'llong': 8, 'ullong': 8,
            'float': 4, 'double': 8, 'void': 0}[kind]
    return Type('scalar', name=kind, size=size)


class Parser:
    def __init__(self, text):
        self.toks = [(m.lastgroup, m.group()) for m in TOKEN.finditer(text) if m.lastgroup not in ('ws', 'pp')]
        self.i = 0
        self.typedefs = {}     # name -> Type
        self.tags = {}         # struct/union tag -> Type
        self.enums = {}        # constant -> int
        self.enum_names = set()
        self.order = []        # names in definition order
        self.run()

    # -- token helpers
    def peek(self, k=0):
        j = self.i + k
        return self.toks[j][1] if j < len(self.toks) else None

    def next(self):
        t = self.peek(); self.i += 1; return t

    def skip_balanced(self, open_, close):
        depth = 0
        while self.i < len(self.toks):
            t = self.next()
            if t == open_: depth += 1
            elif t == close:
                depth -= 1
                if depth == 0: return

    def skip_statement(self):
        """Skip to the end of a file-scope declaration or function definition."""
        while self.i < len(self.toks):
            t = self.peek()
            if t == ';': self.i += 1; return
            if t == '{':
                self.skip_balanced('{', '}')
                if self.peek() == ';': self.i += 1
                return
            if t == '(': self.skip_balanced('(', ')'); continue
            if t == '}': return
            self.i += 1

    # -- top level
    def run(self):
        while self.i < len(self.toks):
            t = self.peek()
            if t == 'extern' and (self.peek(1) or '').startswith('"') and self.peek(2) == '{':
                self.i += 3; continue
            if t == 'namespace':
                j = self.i + 1
                while j < len(self.toks) and self.toks[j][1] not in ('{', ';'): j += 1
                self.i = j + 1; continue
            if t in ('}', ';'): self.i += 1; continue
            if t == 'template':
                self.i += 1
                if self.peek() == '<': self.skip_angle()
                self.skip_statement(); continue
            start = self.i
            try:
                if t == 'typedef':
                    self.i += 1
                    base = self.spec()
                    self.declarators(base, typedef=True)
                    if self.peek() == ';': self.i += 1
                    else: self.i = start; self.skip_statement()
                    continue
                if t in ('struct', 'union', 'class', 'enum'):
                    # definition only when a body follows the optional tag
                    j = self.i + 1
                    if self.toks[j][0] == 'id': j += 1
                    if j < len(self.toks) and self.toks[j][1] in ('{', ':'):
                        self.spec()
                        if self.peek() == ';': self.i += 1; continue
                        self.skip_statement(); continue
            except (Unsupported, IndexError, TypeError):
                self.i = start
            self.skip_statement()

    def skip_angle(self):
        depth = 0
        while self.i < len(self.toks):
            t = self.next()
            if t == '<': depth += 1
            elif t == '>':
                depth -= 1
                if depth == 0: return

    # -- declaration specifiers
    def spec(self):
        words = []
        got = None
        while True:
            t = self.peek()
            if t in QUAL: self.i += 1; continue
            if t in ('struct', 'union', 'class'):
                got = self.struct(); continue
            if t == 'enum':
                got = self.enum(); continue
            if t in WORDS: words.append(self.next()); continue
            if got is None and not words and self.toks[self.i][0] == 'id' and t in self.typedefs:
                got = self.typedefs[self.next()]; continue
            if got is None and not words and self.toks[self.i][0] == 'id' and t in self.enum_names:
                self.i += 1; got = scalar('int'); continue
            break
        if got is not None: return got
        if not words: raise Unsupported('unknown type ' + str(self.peek()))
        return scalar(self.words_kind(words))

    @staticmethod
    def words_kind(words):
        w = [x for x in words if x != 'int' or len(words) == 1 or set(words) <= {'int', 'signed', 'unsigned'}]
        uns = 'unsigned' in w; sig = 'signed' in w
        core = [x for x in w if x not in ('unsigned', 'signed')]
        if core.count('long') == 2: return 'ullong' if uns else 'llong'
        if 'double' in core: return 'double'
        if 'float' in core: return 'float'
        if 'void' in core: return 'void'
        if 'bool' in core: return 'uchar'
        if 'wchar_t' in core: return 'ushort'
        if 'char' in core: return 'uchar' if uns else ('schar' if sig else 'char')
        if 'short' in core: return 'ushort' if uns else 'short'
        return 'uint' if uns else 'int'

    def enum(self):
        self.i += 1
        if self.toks[self.i][0] == 'id' and self.peek() != '{':
            self.enum_names.add(self.next())
        if self.peek() == '{':
            self.i += 1
            val = 0
            while self.peek() != '}':
                name = self.next()
                if self.peek() == '=':
                    self.i += 1
                    expr = []
                    depth = 0
                    while not (depth == 0 and self.peek() in (',', '}')):
                        t = self.next()
                        if t == '(': depth += 1
                        if t == ')': depth -= 1
                        expr.append(t)
                    val = self.const(expr)
                self.enums[name] = val
                val += 1
                if self.peek() == ',': self.i += 1
            self.i += 1
        return scalar('int')

    def const(self, toks):
        s = ' '.join(str(self.enums.get(t, t)) for t in toks)
        s = re.sub(r'(?<=[0-9a-fA-F])[uUlL]+\b', '', s)
        if not re.fullmatch(r'[0-9a-fA-FxX\s()+\-*/%<>|&^~]*', s): raise Unsupported('dimension ' + s)
        try:
            return int(eval(s.replace('/', '//'), {'__builtins__': {}}))
        except Exception:
            raise Unsupported('dimension ' + s)

    def struct(self):
        kw = self.next()
        tag = None
        if self.toks[self.i][0] == 'id': tag = self.next()
        if self.peek() == ':':    # base classes: not a plain data layout
            while self.peek() != '{': self.i += 1
            self.skip_balanced('{', '}')
            t = Type('bad', reason='%s has a base class' % tag)
            if tag: self.tags[tag] = t; self.typedefs.setdefault(tag, t)
            return t
        if self.peek() != '{':
            if tag in self.tags: return self.tags[tag]
            t = Type('struct', members=[], union=(kw == 'union'), tag=tag, incomplete=True)
            self.tags[tag] = t
            self.typedefs.setdefault(tag, t)   # C++: the tag is a type name
            return t
        self.i += 1
        t = self.tags.get(tag) if tag and getattr(self.tags.get(tag), 'incomplete', False) else None
        if t is None: t = Type('struct', members=[], union=(kw == 'union'), tag=tag)
        t.incomplete = False
        t.union = (kw == 'union')
        if tag:
            self.tags[tag] = t
            self.typedefs.setdefault(tag, t)
            self.order.append(tag)
        bad = None
        members = []
        while self.peek() != '}':
            if self.peek() is None: raise Unsupported('unterminated struct')
            if self.peek() in ('public', 'private', 'protected') and self.peek(1) == ':':
                self.i += 2; continue
            start = self.i
            try:
                if self.peek() in ('virtual', 'friend', 'template', 'operator', 'typedef', 'using', '~', 'explicit'):
                    if self.peek() == 'virtual': bad = 'virtual function'
                    raise Unsupported('member function')
                base = self.spec()
                if self.peek() == ';' and base.kind == 'struct' and not getattr(base, 'tag', None):
                    members.append((None, base)); self.i += 1; continue   # anonymous struct/union member
                for name, ty in self.declarators(base, typedef=False, member=True):
                    members.append((name, ty))
                if self.peek() != ';': raise Unsupported('member function')
                self.i += 1
            except Unsupported as e:
                if 'bitfield' in str(e) or 'dimension' in str(e): bad = str(e)
                self.i = start
                # a method or something else that takes no storage: skip it
                while self.peek() not in (';', '{', '}', None):
                    if self.peek() == '(': self.skip_balanced('(', ')')
                    else: self.i += 1
                if self.peek() == '{':
                    self.skip_balanced('{', '}')
                    if self.peek() == ';': self.i += 1
                elif self.peek() == ';': self.i += 1
        self.i += 1
        if bad:
            t.kind = 'bad'; t.reason = '%s: %s' % (tag or 'struct', bad)
        t.members = members
        return t

    def declarators(self, base, typedef, member=False):
        out = []
        while True:
            ty = base
            stars = 0
            while self.peek() in ('*', 'const', 'volatile', '&', '__restrict', 'restrict'):
                if self.next() in ('*', '&'): stars += 1
            name = None
            if self.peek() == '(':      # function pointer or parenthesised declarator
                self.skip_balanced('(', ')')
                # name is the last identifier inside the first parentheses
                j = self.i - 1
                depth = 0
                inner = []
                while j >= 0:
                    t = self.toks[j][1]
                    if t == ')': depth += 1
                    elif t == '(':
                        depth -= 1
                        if depth == 0: break
                    inner.append(self.toks[j])
                    j -= 1
                ids = [v for k, v in reversed(inner) if k == 'id' and v not in QUAL]
                dims = [v for k, v in reversed(inner) if k == 'num']
                name = ids[-1] if ids else None
                if self.peek() == '(': self.skip_balanced('(', ')')
                ty = Type('ptr', target='function')
                for d in dims: ty = Type('array', elem=ty, n=int(d, 0))
            else:
                if self.i < len(self.toks) and self.toks[self.i][0] == 'id':
                    name = self.next()
                if stars: ty = Type('ptr', target=describe(base))
                for _ in range(max(0, stars - 1)): ty = Type('ptr', target='pointer')
                if self.peek() == '(':
                    raise Unsupported('function declaration')
                dims = []
                while self.peek() == '[':
                    self.i += 1
                    expr = []
                    while self.peek() != ']': expr.append(self.next())
                    self.i += 1
                    dims.append(self.const(expr) if expr else 0)
                for d in reversed(dims): ty = Type('array', elem=ty, n=d)
                if self.peek() == ':':
                    raise Unsupported('bitfield')
            if self.peek() == '=':   # default value / initialiser: not a layout we follow
                raise Unsupported('initialiser')
            if typedef and name:
                self.typedefs[name] = ty
                if ty.kind == 'struct' and not getattr(ty, 'tag', None) and not getattr(ty, 'tdname', None):
                    ty.tdname = name
                self.order.append(name)
            out.append((name, ty))
            if self.peek() == ',': self.i += 1; continue
            return out


def describe(t):
    if t.kind == 'scalar': return SPELL[t.name]
    if t.kind == 'struct': return getattr(t, 'tag', None) or getattr(t, 'tdname', None) or 'struct'
    if t.kind == 'ptr': return t.target + ' *'
    if t.kind == 'array': return describe(t.elem)
    return '?'


def leaves(t, off=0, path=''):
    """Flat list of (offset, size, kind, path): kind = scalar name | 'ptr'."""
    k = t.kind
    if k == 'scalar':
        return [(off, t.size, t.name, path)]
    if k == 'ptr':
        return [(off, 4, 'ptr', path)]
    if k == 'array':
        s, _ = t.elem.size_align()
        out = []
        for i in range(t.n): out += leaves(t.elem, off + i * s, '%s[%d]' % (path, i))
        return out
    if k == 'struct':
        t.layout()
        if t.union:
            n, ft, fo = t.fields[0]
            return leaves(ft, off, path + '.' + (n or ''))
        out = []
        for n, ft, fo in t.fields: out += leaves(ft, off + fo, path + '.' + (n or ''))
        return out
    raise Unsupported(getattr(t, 'reason', 'unsupported type'))


def signature(t):
    """Layout fingerprint: two types with the same signature initialise the same bytes the same way."""
    s, a = t.size_align()
    return (s, tuple((o, z, k) for o, z, k, _ in leaves(t)))


def c_definition(t, name, done, out, indent=''):
    """Append C text defining struct type `t` as `name` (builtin member types; nested structs first)."""
    if name in done: return
    done.add(name)
    t.layout()
    lines = []
    for n, ft, fo in t.fields:
        lines.append('    ' + member_decl(ft, n or ('anon_%X' % fo), done, out))
    kw = 'union' if t.union else 'struct'
    out.append('typedef %s %s {\n%s\n} %s;' % (kw, name, '\n'.join(lines), name))


def member_decl(t, name, done, out):
    dims = ''
    while t.kind == 'array':
        dims += '[%d]' % t.n; t = t.elem
    if t.kind == 'scalar': return '%s %s%s;' % (SPELL[t.name], name, dims)
    if t.kind == 'ptr':
        tgt = t.target
        base = tgt if tgt in SPELL.values() else 'void'
        note = '' if base != 'void' or tgt == 'void' else '   /* %s * */' % tgt
        return '%s *%s%s;%s' % (base, name, dims, note)
    if t.kind == 'struct':
        sub = getattr(t, 'tag', None) or getattr(t, 'tdname', None)
        if not sub: raise Unsupported('anonymous nested struct')
        c_definition(t, sub, done, out)
        return '%s %s%s;' % (sub, name, dims)
    raise Unsupported(getattr(t, 'reason', 'unsupported member'))


_PP = {}


def preprocess(src):
    """Preprocessed text of a source file under src/ (its own compile command with -E), '' on failure."""
    if src in _PP: return _PP[src]
    rel = os.path.relpath(os.path.join(ROOT, src), os.path.join(ROOT, 'src'))
    o = os.path.join('build', 'GNLJ82', 'src', os.path.splitext(rel)[0] + '.o')
    cmds = subprocess.run(['ninja', '-t', 'commands', o], cwd=ROOT, capture_output=True, text=True).stdout.strip().splitlines()
    text = ''
    if cmds:
        cmd = cmds[-1].split(' && ')[0]
        cmd = re.sub(r' -MMD', '', cmd)
        cmd = re.sub(r' -c (\S+) -o \S+$', r' -E \1', cmd)
        r = subprocess.run(cmd, shell=True, cwd=ROOT, capture_output=True, text=True, errors='replace')
        if r.returncode == 0: text = r.stdout
    _PP[src] = text
    return text


_PARSED = {}


def parse_file(src):
    if src not in _PARSED:
        text = preprocess(src) if src.startswith('src' + os.sep) or src.startswith('src/') else ''
        if not text:
            text = open(os.path.join(ROOT, src), encoding='utf-8', errors='replace').read()
        _PARSED[src] = Parser(text)
    return _PARSED[src]


def find_type(src, name):
    p = parse_file(src)
    t = p.typedefs.get(name) or p.tags.get(name)
    if t is None or getattr(t, 'incomplete', False): return None
    return t


def main():
    src, name = sys.argv[1], sys.argv[2]
    t = find_type(src, name)
    if t is None: sys.exit('no type %s in %s' % (name, src))
    s, a = t.size_align()
    print('%s: size 0x%X align %d' % (name, s, a))
    for o, z, k, p in leaves(t): print('  +0x%03X %-7s %s' % (o, k, p))
    out = []
    if t.kind == 'struct':
        c_definition(t, name, set(), out)
        print('\n\n'.join(out))


if __name__ == '__main__':
    main()
