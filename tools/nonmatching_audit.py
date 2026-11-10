#!/usr/bin/env python3
"""Equivalence audit for a NON_MATCHING C side (docs/nonmatching_c.md).

usage: tools/nonmatching_audit.py UNIT FN      (run tools/nonmatching_check.py UNIT first)

Percentages do not say whether the C does the same thing. This compares what
is independent of register allocation and scheduling between the target
function and the -DNON_MATCHING build of it:
  - the sequence of calls (direct call targets in order, count of indirect calls),
  - how often each (store opcode, offset) pair occurs outside the stack frame,
  - how often each compare / mask-test shape occurs.
Every reported difference needs an explanation (an unrolled loop, a strength-
reduced pointer, a switch laid out differently) or a fix. A missing or extra
call, a store with another width or an extra xoris (signed int->float where
the target has none: usually an undeclared function returning int) is a bug.
"""
import sys,re,difflib,os,collections
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
import nonmatching_check as n
src=n.resolve(sys.argv[1]); fn=sys.argv[2]
t=n.fn_text(n.BUILD+'/obj/'+os.path.splitext(src)[0][4:]+'.o',fn,'target')
m=n.fn_text(n.OUTROOT+'/'+os.path.splitext(src)[0]+'.o',fn,'mine')
def calls(L): return [x.split()[1] for x in L if x.startswith(('bl ','bctrl','blrl')) and len(x.split())>1 and not x.split()[1].startswith(('_savegpr','_restgpr','_savefpr','_restfpr'))]+[]
a,b=calls(t),calls(m)
print('calls target %d mine %d'%(len(a),len(b)))
for l in difflib.unified_diff(a,b,'target','mine',lineterm='',n=1): print(l)
def ind(L): return sum(1 for x in L if x.startswith(('bctrl','blrl')))
print('indirect calls',ind(t),ind(m))
def stores(L):
    c=collections.Counter()
    for x in L:
        mm=re.match(r'(st[bhw]u?|stfs|stfd|sth|stmw)x?\s+\S+,\s*(-?0x[0-9a-f]+|-?\d+)\((r\d+)\)',x)
        if mm and mm.group(3)!='r1': c[(mm.group(1),int(mm.group(2),0))]+=1
    return c
sa,sb=stores(t),stores(m)
d={k:(sa[k],sb[k]) for k in set(sa)|set(sb) if sa[k]!=sb[k]}
print('non-stack store (op,offset) count differences:',len(d))
for k in sorted(d): print('  ',k[0],hex(k[1]),'target',d[k][0],'mine',d[k][1])
def cmps(L): return collections.Counter(re.sub(r'\br\d+\b','R',re.sub(r'\bf\d+\b','F',x)) for x in L if x.startswith(('cmp','fcmp','andi.','rlwinm.','clrlwi.','and.','or.','xor')))
ca,cb=cmps(t),cmps(m)
d={k:(ca[k],cb[k]) for k in set(ca)|set(cb) if ca[k]!=cb[k]}
print('compare differences:',len(d))
for k in sorted(d): print('  ',k,'target',d[k][0],'mine',d[k][1])
