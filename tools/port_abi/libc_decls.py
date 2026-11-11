#!/usr/bin/env python3
"""List declarations of C library functions that differ from the standard prototype.

    python3 tools/port_abi/libc_decls.py [--fix] [paths...]     (default: src/game include/game)

`extern double atan2(float y, float x);` costs nothing on PowerPC (float and
double arguments travel in the same register) and breaks a 32-bit x86 host:
the caller pushes 4 bytes per argument, libm reads 8.  The same goes for a
wrong return type or an empty parameter list.  --fix rewrites the declaration
to the prototype below, keeping `extern` / `extern "C"`; check the object
hashes afterwards and put back any unit that changes (docs/notes/port_abi.md,
"Library prototypes").  Only one-line declarations are seen; pointer types
are not compared with each other (any pointer is passed the same way), and
the wcs* functions are left out (wchar_t is unsigned short in this game).
"""
import glob, os, re, sys

STD = {
    'sin': 'double sin(double)', 'cos': 'double cos(double)', 'tan': 'double tan(double)',
    'asin': 'double asin(double)', 'acos': 'double acos(double)', 'atan': 'double atan(double)',
    'atan2': 'double atan2(double, double)', 'sqrt': 'double sqrt(double)', 'pow': 'double pow(double, double)',
    'fmod': 'double fmod(double, double)', 'floor': 'double floor(double)', 'ceil': 'double ceil(double)',
    'fabs': 'double fabs(double)', 'exp': 'double exp(double)', 'log': 'double log(double)',
    'sinf': 'float sinf(float)', 'cosf': 'float cosf(float)', 'tanf': 'float tanf(float)',
    'acosf': 'float acosf(float)', 'atan2f': 'float atan2f(float, float)', 'sqrtf': 'float sqrtf(float)',
    'strlen': 'unsigned long strlen(const char *)', 'strcpy': 'char *strcpy(char *, const char *)',
    'strncpy': 'char *strncpy(char *, const char *, unsigned long)', 'strcat': 'char *strcat(char *, const char *)',
    'strcmp': 'int strcmp(const char *, const char *)', 'strncmp': 'int strncmp(const char *, const char *, unsigned long)',
    'strchr': 'char *strchr(const char *, int)', 'strrchr': 'char *strrchr(const char *, int)',
    'strstr': 'char *strstr(const char *, const char *)',
    'memcpy': 'void *memcpy(void *, const void *, unsigned long)', 'memmove': 'void *memmove(void *, const void *, unsigned long)',
    'memset': 'void *memset(void *, int, unsigned long)', 'memcmp': 'int memcmp(const void *, const void *, unsigned long)',
    'rand': 'int rand(void)', 'srand': 'void srand(unsigned int)', 'abs': 'int abs(int)', 'atoi': 'int atoi(const char *)',
    'sprintf': 'int sprintf(char *, const char *, ...)', 'snprintf': 'int snprintf(char *, unsigned long, const char *, ...)',
    'printf': 'int printf(const char *, ...)', 'vsprintf': 'int vsprintf(char *, const char *, va_list)',
    'vsnprintf': 'int vsnprintf(char *, unsigned long, const char *, va_list)',
}
SAME = {'size_t': 'ul', 'unsigned long': 'ul', 'unsigned int': 'ul', 'unsigned': 'ul', 'u32': 'ul', 'unsigned long int': 'ul', 'long unsigned int': 'ul',
        'int': 'i', 's32': 'i', 'signed int': 'i', 'long': 'i', 'f32': 'float', 'f64': 'double', '__va_list_struct *': 'va_list', 'struct __va_list_struct *': 'va_list'}
DECL = re.compile(r'^([ \t]*)((?:extern\s+)?(?:"C"\s+)?)((?:const\s+)?(?:unsigned\s+|signed\s+)?\w+(?:\s+int)?[\s\*]+)(%s)\s*\(([^()]*)\)\s*;' % '|'.join(STD), re.M)


def norm_type(t):
    t = re.sub(r'\s+', ' ', t.replace('*', ' * ')).strip()
    t = re.sub(r' ?\* ?', ' *', t).replace('* *', '**')
    t = re.sub(r'\bregister\b|\brestrict\b|__restrict', '', t).strip()
    c = 'const ' if t.startswith('const ') else ''
    b = t[len(c):]
    stars = b[len(b.rstrip('* ')):].replace(' ', '')
    b = b.rstrip('* ').strip()
    if stars: return 'ptr'   # any pointer is passed the same way
    return SAME.get(b, b)


def norm_params(p):
    p = p.strip()
    if p in ('', 'void'): return [] if p == 'void' else None
    out = []
    for a in p.split(','):
        a = a.strip()
        if a == '...': out.append('...'); continue
        a = re.sub(r'\[\]$', '*', a)
        m = re.match(r'^(.*?[\s\*])(\w+)$', a)
        if m and m.group(2) not in ('int', 'char', 'long', 'float', 'double', 'short', 'unsigned', 'void', 'size_t', 'va_list', 'wchar_t') and m.group(1).strip() not in ('const', 'unsigned', 'signed', 'struct', 'const unsigned', 'const struct'):
            a = m.group(1)
        out.append(norm_type(a))
    return out


def canon(name):
    m = re.match(r'^(.*?)(\w+)\((.*)\)$', STD[name])
    return norm_type(m.group(1)), norm_params(m.group(3))


fix = '--fix' in sys.argv
paths = [a for a in sys.argv[1:] if a != '--fix'] or ['src/game', 'include/game']
files = []
for p in paths:
    if os.path.isdir(p):
        for e in ('c', 'cpp', 'h', 'inc'): files += glob.glob(p + '/**/*.' + e, recursive=True)
    else: files.append(p)
n = 0
for f in sorted(set(files)):
    s = open(f, encoding='utf-8', errors='replace').read()
    def rep(m):
        global n
        name = m.group(4)
        if m.group(3).strip() in ('return', 'else', 'case', 'goto'): return m.group(0)
        want = canon(name)
        got = (norm_type(m.group(3)), norm_params(m.group(5)))
        if got == want: return m.group(0)
        n += 1
        print('%s:%d: %s' % (f, s.count('\n', 0, m.start()) + 1, ' '.join(m.group(0).split())))
        return m.group(1) + m.group(2) + STD[name] + ';'
    t = DECL.sub(rep, s)
    if fix and t != s: open(f, 'w').write(t)
print('%d declarations differ from the standard prototype' % n)
