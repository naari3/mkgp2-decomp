#!/usr/bin/env python3
# In-TU experiment #3: GetMaxSpeed helper takes KartItemOpsView* (param merges
# with wrapper self), mv as helper local in the decl slot. Sweep 4-local perms.
import os, re, subprocess, itertools
import importlib.util
spec = importlib.util.spec_from_file_location("intu", os.path.join(os.path.dirname(os.path.abspath(__file__)), "run_mrsr_intu.py"))
intu = importlib.util.module_from_spec(spec); spec.loader.exec_module(intu)

HELPER_TPL = """static inline float KartItem_CalcKeySpeed2(KartItemOpsView *self) {
    DECLS
    float keySpeed;

    mv = self->movement;
    keySpeed = lbl_806D26EC;
    for (i = 0, off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < lbl_806D26FC) {
            keySpeed = mv->table[mv->tableIdx].pairs[i].value;
            break;
        }
    }
    if (mv->capFlag == 1) {
        if (keySpeed >= lbl_806D276C) {
            keySpeed = lbl_806D276C;
        }
    }
    return keySpeed;
}
"""

WRAPPER = """#pragma exceptions off
float KartItem_GetMaxSpeedWithBonus(KartItemOpsView *self) { /* 0x8004F040 size:0xB8 */
    KartMovementSpeedView *mv = self->movement;
    float max = lbl_806D2770 * KartItem_CalcKeySpeed2(self);
    max = max * (lbl_806D26FC + mv->coinBonus);
    return max;
}
#pragma exceptions reset
"""

DECLS = {"i": "int i;", "off": "int off;", "e": "SpeedTableEntry *e;",
         "mv": "KartMovementSpeedView *mv;"}

def trial3(decl_perm):
    tag = "gm3_" + "_".join(decl_perm)
    src = intu.build_tu(("e", "off", "i"))
    src = src.replace("asm void KartItem_GetMaxSpeedWithBonus(void);",
                      "float KartItem_GetMaxSpeedWithBonus(KartItemOpsView *self);")
    m = re.search(r"asm void KartItem_GetMaxSpeedWithBonus\(void\) \{.*?\n\}\n", src, re.S)
    helper = HELPER_TPL.replace("DECLS", "\n    ".join(DECLS[d] for d in decl_perm))
    src = src[:m.start()] + helper + "\n" + WRAPPER + src[m.end():]
    tmp = os.path.join(intu.WT, "tu_test3.c")
    open(tmp, "w", encoding="utf-8").write(src)
    obj = os.path.join(intu.WT, "tu_test3.o")
    asm = os.path.join(intu.WT, "tu_test3.s")
    for p in (obj, asm):
        if os.path.exists(p): os.remove(p)
    r = subprocess.run([intu.CC] + intu.FLAGS + ["-c", tmp, "-o", obj],
                       capture_output=True, text=True, cwd=intu.WT, timeout=180)
    if r.returncode != 0:
        print(tag, "CFAIL", (r.stdout + r.stderr)[:300]); return
    subprocess.run([intu.DTK, "elf", "disasm", obj, asm], capture_output=True, cwd=intu.WT, timeout=120)
    t = open(asm, encoding="utf-8").read()
    for fname, tfile in (("KartItem_GetMaxSpeedWithBonus", "target_getmaxspeed.txt"),
                         ("KartItem_UpdateShadowBillboardAndViewport", "target_shadowbb.txt")):
        m = re.search(r"\.fn %s, global(.*?)\.endfn" % fname, t, re.S)
        got = intu.norm(m.group(1))
        want = [l.rstrip("\n") for l in open(os.path.join(intu.HERE, tfile)) if l.strip()]
        ndiff = sum(1 for a, b in zip(got, want) if a != b) + abs(len(got) - len(want))
        print(f"{tag}\t{fname[:20]}\tdiff={ndiff}\tlen={len(got)}/{len(want)}")
        if 0 < ndiff <= 8 and fname.startswith("KartItem_Get"):
            for k, (a, b) in enumerate(zip(got, want)):
                if a != b: print(f"    [{k:3}] got: {a:42} want: {b}")

if __name__ == "__main__":
    for perm in itertools.permutations(["off", "mv", "i", "e"]):
        trial3(perm)
