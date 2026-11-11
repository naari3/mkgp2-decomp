#!/usr/bin/env python3
"""Rewrite byte data written as an array of words.

    python3 tools/port_abi/word_bytes.py [--words] FILE NAME_REGEX

`unsigned int x[n] = { 0x25732573, ... }` whose readers take bytes (text with
non-ASCII characters, bitmaps, printer escape sequences) becomes
`unsigned char x[4n] = { 0x25, 0x73, ... }`.  `int` and `short` arrays are
taken too (docs/notes/port_abi.md, request 39).  With --words the array stays an
array of words and each word is written TEXT_WORD(0x25, 0x73, 0x25, 0x73)
(include/game/types/text_word.h): use it where the byte array changes the
object (alignment, section).  Check the object hash after either.
"""
import re, sys
a = [x for x in sys.argv[1:] if x != '--words']
words = '--words' in sys.argv
f, pat = a
s = open(f, encoding='utf-8').read()
DEF = re.compile(r'^(?:/\* (?:decl|element type)[^\n]*\*/\n)*((?:extern "C" |extern |static |const )*)(unsigned int|unk32|u32|int|short|unsigned short) (' + pat + r')\[(\d*)\] = \{([^{};]*)\};', re.M)
n = 0


def rep(m):
    global n
    try: w = [int(x, 0) for x in m.group(5).replace('\n', ' ').split(',') if x.strip()]
    except ValueError: return m.group(0)
    n += 1
    width = 2 if 'short' in m.group(2) else 4
    w = [x & ((1 << 8 * width) - 1) for x in w]
    if words:
        return '%s%s %s[%s] = { %s };' % (m.group(1), m.group(2), m.group(3), m.group(4), ', '.join('TEXT_WORD(0x%02X, 0x%02X, 0x%02X, 0x%02X)' % tuple(x.to_bytes(4, 'big')) for x in w))
    bs = b''.join(x.to_bytes(width, 'big') for x in w)
    return '%sunsigned char %s[%d] = { %s };' % (m.group(1), m.group(3), len(bs), ', '.join('0x%02X' % b for b in bs))


t = DEF.sub(rep, s)
if words and n and 'text_word.h' not in t: t = '#include "game/types/text_word.h"\n' + t
open(f, 'w').write(t)
print('%s: %d arrays' % (f, n))
