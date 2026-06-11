"""Generic label+reg normalized verify of a probe .c against target."""
import io, re, subprocess, sys, difflib
sys.path.insert(0, "tmp")
from cpp_probe_run import extract_fn, CFLAGS, MWCC, DTK
probe = sys.argv[1]
subprocess.run([MWCC] + CFLAGS + ["-lang=c", "-c", probe, "-o", "tmp/_va.o"],
               capture_output=True, text=True, check=True)
subprocess.run([DTK, "elf", "disasm", "tmp/_va.o", "tmp/_va.s"], capture_output=True, text=True, check=True)
_, target = extract_fn(io.open("tmp/target_tu_full.s", encoding="utf-8").read(), "KartItem_OnKartHit")
_, mine = extract_fn(io.open("tmp/_va.s", encoding="utf-8").read(), "OnKartHit")
def mask(i): return re.sub(r"\bf\d+\b", "F", re.sub(r"\br\d+\b", "R", i))
nt, nm = [mask(r) for r in target], [mask(r) for r in mine]
print(f"target rows={len(nt)} mine rows={len(nm)}")
sm = difflib.SequenceMatcher(a=nt, b=nm, autojunk=False)
print(f"label+reg normalized similarity: {sm.ratio()*100:.4f}%")
diffs = 0
for op, a1, a2, b1, b2 in sm.get_opcodes():
    if op == "equal": continue
    for k in range(max(a2-a1, b2-b1)):
        lt = target[a1+k] if a1+k < a2 else "---"
        rt = mine[b1+k] if b1+k < b2 else "---"
        lm = mask(lt) if lt!="---" else "-"
        rm_ = mask(rt) if rt!="---" else "-"
        if lm != rm_:
            diffs += 1
            print(f"  DIFF [{a1+k}] {lt:34s} || {rt}")
print(f"\ngenuine instruction/structure diffs: {diffs}")
# homes
h = {}
for ins in mine[:14]:
    m = re.match(r"mr (r\d+), r3$", ins);  h["self"]=m.group(1) if m else h.get("self")
    m = re.match(r"mr (r\d+), r4$", ins);  h["victim"]=m.group(1) if m else h.get("victim")
print(f"self={h.get('self')} victim={h.get('victim')} (target self=r30 victim=r31)")
