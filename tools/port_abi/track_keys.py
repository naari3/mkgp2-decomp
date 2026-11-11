#!/usr/bin/env python3
"""Find joint animation tracks written as `unsigned int x[2n]`; --fix makes them `TrackKey x[n]`.

    python3 tools/port_abi/track_keys.py [--fix]

Shape: pairs of (frame << 16, float bits), frames rising, the last pair
0xFFFF0000, 0.  The reader (StepTrack in JointTracks.cpp and its copies) takes
the frame as a 16-bit value, which a word array gives only on a big-endian
machine.  Declarations of the same name in other files are retyped too.
"""
import glob, re, sys
sys.path.insert(0, 'tools')
from autodata import fmt_float

DEF = re.compile(r'^((?:extern "C" |extern |static |const )*)(?:unsigned int|unk32|u32) (\w+)\[(\d*)\] = \{([^{};]*)\};', re.M)
fix = '--fix' in sys.argv
files = sorted(glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.cpp', recursive=True) + glob.glob('src/**/*.inc', recursive=True) + glob.glob('include/**/*.h', recursive=True))
text = {f: open(f, encoding='utf-8', errors='replace').read() for f in files}
names, skipped = {}, []


def rows_of(body):
    try: w = [int(x, 0) for x in body.replace('\n', ' ').split(',') if x.strip()]
    except ValueError: return None
    if len(w) < 2 or len(w) % 2 or w[-2:] != [0xFFFF0000, 0]: return None
    rows, last = [], -1
    for i in range(0, len(w) - 2, 2):
        if w[i] & 0xFFFF or (w[i] >> 16) >= 0x8000 or (w[i] >> 16) < last: return None
        last = w[i] >> 16
        t = fmt_float(w[i + 1])
        if t is None: return False
        rows.append('{ %d, 0, %s }' % (last, t))
    return rows + ['{ -1, 0, 0.0f }']


for f in files:
    def rep(m):
        r = rows_of(m.group(4))
        if r is None: return m.group(0)
        if r is False:
            skipped.append(m.group(2)); return m.group(0)
        names[m.group(2)] = f
        return '%sTrackKey %s[%d] = { %s };' % (m.group(1), m.group(2), len(r), ', '.join(r))
    new = DEF.sub(rep, text[f])
    if new != text[f]: text[f] = new
print('%d tracks in %d files; %d skipped (a value is not a finite float): %s' % (len(names), len(set(names.values())), len(skipped), ' '.join(skipped[:8])))
if fix and names:
    decl = re.compile(r'^((?:extern "C" |extern |static |const )*)(?:unsigned int|unk32|u32|char|unsigned char) (\w+)(\[\d*\]);', re.M)
    for f in files:
        t = decl.sub(lambda m: '%sTrackKey %s%s;' % (m.group(1) if 'const' in m.group(1) else m.group(1) + 'const ', m.group(2), m.group(3)) if m.group(2) in names else m.group(0), text[f])
        if 'TrackKey ' in t and 'game/types/TrackKey.h' not in t and 'JointTracksPrivate.h' not in t and not f.endswith('TrackKey.h'):
            k = re.search(r'^(?:extern|static|const|#include|typedef)\b', t, re.M)
            k = k.start() if k else 0
            t = t[:k] + '#include "game/types/TrackKey.h"\n' + t[k:]
        if t != open(f, encoding='utf-8', errors='replace').read(): open(f, 'w').write(t)
