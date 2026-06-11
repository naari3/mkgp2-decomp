#!/usr/bin/env python3
# In-TU experiment: replace ShadowBB asm body with helper-inline C, compile the
# real TU with production flags, diff the fn against target_shadowbb.txt.
import os, re, subprocess, sys, itertools

ROOT = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp"
WTROOT = os.path.join(ROOT, ".worktrees", "batch_research_mrsrinit_phase2c")
HERE = os.path.join(WTROOT, "tools", "compiler_probe")
WT = os.path.join(HERE, "tmp_mrsr")
DTK = os.path.join(ROOT, "build", "tools", "dtk.exe")
CC = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")
TU = os.path.join(WTROOT, "src", "game", "auto_ONKARTHIT_block.c")

FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "on", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on", "-W", "off",
    "-i", os.path.join(WTROOT, "include"),
    "-i", os.path.join(ROOT, "build", "GNLJ82", "include"),
    "-DBUILD_VERSION=0", "-DVERSION_GNLJ82", "-DNDEBUG=1",
]

HELPER_TPL = """static inline float KartItem_CalcKeySpeedFromTable(KartMovementSpeedView *mv) {
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

CBODY = """#pragma exceptions off
void KartItem_UpdateShadowBillboardAndViewport(KartItemOpsView *self, int arg2, int arg3) { /* 0x8004EDD4 size:0x204 */
    KartMovementSpeedView *mv;
    ItemBusFlagsView *bus;
    void *bb;
    float keySpeed;
    float ratio;
    float sel;
    unsigned char b;

    if (ItemStateGuard_IsActive(self->stateBlock->guard) == 1) {
        ShadowBillboard_StepSimple(self->billboard, arg2, arg3);
    } else {
        mv = self->movement;
        keySpeed = KartItem_CalcKeySpeedFromTable(mv);
        ratio = Saturate_Double(KartMovement_CalcSpeedWithCoinBonus(mv, 0) / (lbl_806D2770 * keySpeed), lbl_806D26EC, lbl_806D26FC);
        bus = self->ownerDriver->itemBus;
        sel = *(volatile const float *)&lbl_806D26EC; /* volatile cast defeats the 26EC load CSE */
        if ((bus->flags & 0x0000200000000000ULL) == 0) {
            b = 0;
        } else {
            b = 1;
        }
        if (b == 1) {
            sel = lbl_806D2708;
        }
        bb = self->billboard;
        ShadowBillboard_SetTargetSaturation(bb, Saturate_Double(sel + (float)self->coinCountC8 / lbl_806D27B0, lbl_806D26EC, ratio + sel));
        ShadowBillboard_Tick(self->billboard, arg2, arg3);
        SceneRender_SetViewportRect(g_raceCamera,
            self->movement->transform[12], self->movement->transform[13], self->movement->transform[14],
            self->movement->transform[8], self->movement->transform[9], self->movement->transform[10]);
    }
}
#pragma exceptions reset
"""

DECLS = {"i": "int i;", "off": "int off;", "e": "SpeedTableEntry *e;"}


def build_tu(decl_perm):
    src = open(TU, encoding="utf-8").read()
    # replace fwd decl
    src = src.replace("asm void KartItem_UpdateShadowBillboardAndViewport(void);",
                      "void KartItem_UpdateShadowBillboardAndViewport(KartItemOpsView *self, int arg2, int arg3);")
    # replace asm body
    m = re.search(r"asm void KartItem_UpdateShadowBillboardAndViewport\(void\) \{.*?\n\}\n", src, re.S)
    helper = HELPER_TPL.replace("DECLS", "\n    ".join(DECLS[d] for d in decl_perm))
    src = src[:m.start()] + helper + "\n" + CBODY + src[m.end():]
    return src


def norm(body):
    out = []
    for line in body.splitlines():
        line = line.strip()
        if re.match(r"^\.L_\w+:", line):
            out.append("LABEL")
            continue
        im = re.match(r"^/\*.*?\*/\s+(\S+)\s*(.*)$", line)
        if not im:
            continue
        mn, ops = im.group(1), im.group(2)
        ops = re.sub(r"\.L_\w+", "L", ops)
        ops = re.sub(r"(\w+)@sda21\(r0\)", r"\1(r2)", ops)
        ops = ops.replace("@sda21", "")
        out.append((mn + " " + ops).strip())
    return out


def trial(decl_perm, tag):
    src = build_tu(decl_perm)
    tmp = os.path.join(WT, "tu_test.c")
    open(tmp, "w", encoding="utf-8").write(src)
    obj = os.path.join(WT, "tu_test.o")
    asm = os.path.join(WT, "tu_test.s")
    for p in (obj, asm):
        if os.path.exists(p):
            os.remove(p)
    r = subprocess.run([CC] + FLAGS + ["-c", tmp, "-o", obj],
                       capture_output=True, text=True, cwd=WT, timeout=180)
    if r.returncode != 0:
        print(tag, "CFAIL", (r.stdout + r.stderr)[:400])
        return None
    subprocess.run([DTK, "elf", "disasm", obj, asm], capture_output=True, cwd=WT, timeout=120)
    t = open(asm, encoding="utf-8").read()
    m = re.search(r"\.fn KartItem_UpdateShadowBillboardAndViewport, global(.*?)\.endfn", t, re.S)
    if not m:
        print(tag, "NOFN")
        return None
    got = norm(m.group(1))
    want = [l.rstrip("\n") for l in open(os.path.join(HERE, "target_shadowbb.txt")) if l.strip()]
    # normalize target sda21 form: target uses sym(r2) already
    ndiff = sum(1 for a, b in zip(got, want) if a != b) + abs(len(got) - len(want))
    print(f"{tag}\tdiff={ndiff}\tlen={len(got)}/{len(want)}")
    if 0 < ndiff <= 16:
        for k, (a, b) in enumerate(zip(got, want)):
            if a != b:
                print(f"    [{k:3}] got: {a:44} want: {b}")
    return ndiff


if __name__ == "__main__":
    for perm in itertools.permutations(["off", "e", "i"]):
        trial(perm, "decl_" + "_".join(perm))
