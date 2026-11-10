import subprocess,json
T='build/GNLJ82/obj/game/SetCourseParams.o';B='build/GNLJ82/src/game/SetCourseParams.o'
nm=subprocess.run(['build/binutils/powerpc-eabi-nm',T],capture_output=True,text=True).stdout
fns=[l.split()[2] for l in nm.splitlines() if len(l.split())==3 and l.split()[1] in 'Tt']
r=subprocess.run(['build/tools/objdiff-cli','diff','-1',T,'-2',B,'-o','-',fns[0]],capture_output=True,text=True)
d=json.loads(r.stdout); n=0
for s in d['left']['symbols']:
    if s.get('name') in fns:
        if s.get('match_percent')!=100: print(s['name'],s.get('match_percent'))
        else: n+=1
print(n,'of',len(fns),'at 100')
