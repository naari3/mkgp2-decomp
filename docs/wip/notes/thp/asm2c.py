# asm2c.py file.s startlabel endlabel 'r23=in,r27=q,...'  -> CW asm body
import sys,re
lines=open(sys.argv[1]).read().split('\n'); a,b=sys.argv[2],sys.argv[3]
m=dict(x.split('=') for x in sys.argv[4].split(',')) if len(sys.argv)>4 and sys.argv[4] else {}
on=False
for l in lines:
    if l.startswith(a+':') or l==a: on=True
    if on and (l.startswith(b+':') or l==b): break
    if not on: continue
    l=re.sub(r'\.L_([0-9A-F]+)',r'_L\1',l)
    l=re.sub(r'\bqr(\d)\b',r'\1',l)
    l=re.sub(r'\b(r\d+)\b',lambda g:m.get(g.group(1),g.group(1)),l)
    l=re.sub(r'\b(f\d+)\b',lambda g:m.get(g.group(1),g.group(1)),l)
    print(('    ' if l.endswith(':') else '        ')+l)
