
import json, subprocess, sys, re, os

def build_and_diff(tag):
    r = subprocess.run(['ninja','build/GNLJ82/src/game/auto_ONKARTHIT_block.o'], capture_output=True, text=True)
    if r.returncode != 0:
        print(tag, 'COMPILE FAIL'); print(r.stdout[-2000:]); print(r.stderr[-2000:]); return None
    r = subprocess.run([os.path.join('build','tools','objdiff-cli.exe'),'diff','-1','build/GNLJ82/obj/game/auto_ONKARTHIT_block.o','-2','build/GNLJ82/src/game/auto_ONKARTHIT_block.o','-o','tmp_hie.json','--format','json'], capture_output=True, text=True)
    d = json.load(open('tmp_hie.json'))
    def get(side):
        for s in d[side]['symbols']:
            if s.get('name')=='CarObject_HandleItemEffect': return s
    L=get('left'); R=get('right')
    li=L['instructions']; ri=R['instructions']
    base=0x8004F858
    nd=0; rows=[]
    for i,(a,b) in enumerate(zip(li,ri)):
        fa=a['instruction']['formatted']; fb=b['instruction']['formatted']
        if fa!=fb:
            nd+=1
            rows.append((hex(base+i*4), fa, fb))
    if len(li)!=len(ri): nd += abs(len(li)-len(ri))
    # find handled reg at read site
    hreg=None
    for addr,fa,fb in rows:
        if addr=='0x8004ffac': hreg=fb
    print(f'{tag}: pct={R.get("match_percent"):.4f} diff_rows={nd} len={len(li)}/{len(ri)} read_site={hreg}')
    for x in rows[:12]: print('  ', x[0], '| T:', x[1], ' || M:', x[2])
    return nd

if __name__=='__main__':
    build_and_diff(sys.argv[1] if len(sys.argv)>1 else 'probe')
