import json,subprocess,re
O='build/GNLJ82/src/game/SetCourseParams.o'
K='src/game/SetCourseParams.c'
W='/tmp/claude-0/z/sm/'
files=open(W+'files.txt').read().split()
eto=json.load(open(W+'eto.json'))
ren=json.load(open(W+'ren.json'))
# dedupe (eto.py read merged obj too)
seen=set(); etbs=[]
for s,f in eto['etbsyms']:
    if f not in seen: seen.add(f); etbs.append((s,f))
etbs.sort(key=lambda x:int(x[0][5:],16))
fn2etb={f:s for s,f in etbs}
# extabindex order = text order
order=['RankSlot_AppendOrUpdate','VSMode_SeedRandomItemSequence','SetCourseParams','PlayerData_ApplyItemUnlockById','PlayerData_GetUnlockedItemIdByIndex_U8','PlayerData_ResetForFlow','RaceFlow_ResetState_FullColdInit','ProcessSystemTick','RaceContext_Dtor','RaceContext_InitDefaults','RaceContext_EnsureSingleton','dtor_8009DCE0','KartDriverArray_StaticCtor']
fn2eti={f:'@eti_%08X'%(0x80022190+12*i) for i,f in enumerate(order)}
r=subprocess.run(['build/binutils/powerpc-eabi-objdump','-r','-j','extabindex',O],capture_output=True,text=True).stdout
m={}
alias={'KartDriverArray_StaticCtor__Fv':'KartDriverArray_StaticCtor'}
sec=0;last=-1
for l in r.splitlines():
    p=l.split()
    if len(p)==3 and p[1]=='R_PPC_ADDR32':
        off=int(p[0],16)
        if off%12==0: fn=alias.get(p[2],p[2])
        elif off%12==8:
            etb=p[2]
            if etb.startswith('@'):
                eti='@%d'%(int(etb[1:])+1)
                m[etb]=fn2etb[fn]; m[eti]=fn2eti[fn]
            else:
                m[etb]=fn2etb[fn]; m[etb.replace('extab_','extabindex_')]=fn2eti[fn]
            print(fn,etb,fn2etb[fn],fn2eti[fn])
m.update(ren)
m.update({"__nw__FUl":"Alloc","__ct__15RaceContext_p13Fv":"RaceContext_InitDefaults"})
R=json.load(open('tools/extab_user_renames.json'))
for f in files: R.pop('src/'+f,None)
R[K]=m
json.dump(R,open('tools/extab_user_renames.json','w'),indent=2); open('tools/extab_user_renames.json','a').write('\n')
Od=json.load(open('tools/extab_order.json'))
for f in files: Od.pop('src/'+f,None)
Od[K]={'extab':[f for s,f in etbs],'extabindex':order}
json.dump(Od,open('tools/extab_order.json','w'),indent=2); open('tools/extab_order.json','a').write('\n')
