cd /home/user/mkgp2-decomp && python3 /tmp/claude-0/z/sm/merge.py 2>/dev/null
python3 - <<'P'
import json
for n in ('tools/extab_user_renames.json','tools/extab_order.json'):
    R=json.load(open(n)); R.pop('src/game/SetCourseParams.c',None)
    json.dump(R,open(n,'w'),indent=2); open(n,'a').write('\n')
P
rm -f build/GNLJ82/src/game/SetCourseParams.o
ninja build/GNLJ82/src/game/SetCourseParams.o 2>&1 | grep -v "WARN\|^\[" | sed -n 3,30p | cut -c1-250
python3 /tmp/claude-0/z/sm/mkjson.py >/dev/null && rm -f build/GNLJ82/src/game/SetCourseParams.o && ninja build/GNLJ82/src/game/SetCourseParams.o 2>&1 | grep -v WARN | tail -1; python3 /tmp/claude-0/z/sm/all.py
