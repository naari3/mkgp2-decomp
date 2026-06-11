#!/usr/bin/env python3
# In-TU experiment #2: ShadowBB fixed at decl (e, off, i); sweep GetMaxSpeed
# wrapper forms x its own helper decl perms.
import os, re, subprocess, itertools
import importlib.util
spec = importlib.util.spec_from_file_location("intu", os.path.join(os.path.dirname(os.path.abspath(__file__)), "run_mrsr_intu.py"))
intu = importlib.util.module_from_spec(spec); spec.loader.exec_module(intu)

HELPER2_TPL = """static inline float KartItem_CalcKeySpeed2(KartMovementSpeedView *mv) {
    DECLS
    float keySpeed;

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

WRAPPERS = {
"a": """#pragma exceptions off
float KartItem_GetMaxSpeedWithBonus(KartItemOpsView *self) { /* 0x8004F040 size:0xB8 */
    KartMovementSpeedView *mv = self->movement;
    float max = lbl_806D2770 * KartItem_CalcKeySpeed2(mv);
    max = max * (lbl_806D26FC + mv->coinBonus);
    return max;
}
#pragma exceptions reset
""",
"b": """#pragma exceptions off
float KartItem_GetMaxSpeedWithBonus(KartItemOpsView *self) { /* 0x8004F040 size:0xB8 */
    KartMovementSpeedView *mv = self->movement;
    return lbl_806D2770 * KartItem_CalcKeySpeed2(mv) * (lbl_806D26FC + mv->coinBonus);
}
#pragma exceptions reset
""",
"c": """#pragma exceptions off
float KartItem_GetMaxSpeedWithBonus(KartItemOpsView *self) { /* 0x8004F040 size:0xB8 */
    KartMovementSpeedView *mv = self->movement;
    float max = KartItem_CalcKeySpeed2(mv);
    max = lbl_806D2770 * max;
    max = max * (lbl_806D26FC + mv->coinBonus);
    return max;
}
#pragma exceptions reset
""",
}

def build_tu2(decl_perm, wform):
    src = intu.build_tu(("e", "off", "i"))  # ShadowBB solved form
    src = src.replace("asm void KartItem_GetMaxSpeedWithBonus(void);",
                      "float KartItem_GetMaxSpeedWithBonus(KartItemOpsView *self);")
    m = re.search(r"asm void KartItem_GetMaxSpeedWithBonus\(void\) \{.*?\n\}\n", src, re.S)
    helper = HELPER2_TPL.replace("DECLS", "\n    ".join(intu.DECLS[d] for d in decl_perm))
    src = src[:m.start()] + helper + "\n" + WRAPPERS[wform] + src[m.end():]
    return src

def trial2(decl_perm, wform):
    tag = f"gm_{'_'.join(decl_perm)}_w{wform}"
    src = build_tu2(decl_perm, wform)
    tmp = os.path.join(intu.WT, "tu_test2.c")
    open(tmp, "w", encoding="utf-8").write(src)
    obj = os.path.join(intu.WT, "tu_test2.o")
    asm = os.path.join(intu.WT, "tu_test2.s")
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
        if not m:
            print(tag, fname, "NOFN"); continue
        got = intu.norm(m.group(1))
        want = [l.rstrip("\n") for l in open(os.path.join(intu.HERE, tfile)) if l.strip()]
        ndiff = sum(1 for a, b in zip(got, want) if a != b) + abs(len(got) - len(want))
        print(f"{tag}\t{fname[:20]}\tdiff={ndiff}\tlen={len(got)}/{len(want)}")
        if 0 < ndiff <= 12 and fname.startswith("KartItem_Get"):
            for k, (a, b) in enumerate(zip(got, want)):
                if a != b: print(f"    [{k:3}] got: {a:42} want: {b}")

if __name__ == "__main__":
    for perm in itertools.permutations(["off", "e", "i"]):
        trial2(perm, "a")
