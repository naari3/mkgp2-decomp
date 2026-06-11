// Phase 2f-2: frida entry-point scaffold for observing the CW 1.3.2 colorer.
//
// STATUS: STARTING POINT, NOT VERIFIED. The register-coloring *listing* dump in
// mwcceppc.exe 1.3.2 is stubbed (emit fn 0x4ffdb0 == single RET), so the visit
// order cannot be read from any built-in dump. The only remaining way to observe
// the colorer's web visit order is to instrument the coloring functions directly.
// This file records the confirmed entry points so a follow-up batch can attach a
// real reader without re-doing the static analysis.
//
// Confirmed by Ghidra (image base 0x400000; these are VAs):
//   0x5077b0  RegisterColoring driver (Coloring.c). Per-class outer loop over
//             DAT_005e931f = 0..4 (register class). For each class with live webs
//             it calls FUN_00579cf0 (color step) in a while loop until done.
//   0x579cf0  per-class color step: FUN_005797a0(build) FUN_00579e50 FUN_0057a640
//             FUN_0057a1f0(coalesce union-find) FUN_00579fe0(adjacency)
//             FUN_00579d50. The select/assign that writes the physical reg into
//             each web is reached from here (assign instr not yet pinned down).
//   0x57abd0  spill handling (FUN_0057ae00/0057af40/0057aff0/0057b100).
//
// Key globals (VAs, .bss):
//   0x5e87b0  DAT_005e87b0  head of the web/temp list (singly linked: *p == next;
//             p[5] -> node chain; p[6] -> interference node chain; p[7] -> index).
//   0x5e931f  DAT_005e931f  current register class index being colored (0..4).
//             class 4 == GPR (the case with the most special-casing), class 3,2
//             also handled; FP class is among these (TODO confirm which index).
//   0x5e87d0  DAT_005e87d0  adjacency-node array for the current class.
//   0x5e8a7c  (&DAT_005e8a7c)[class]  web count for the class.
//
// TODO for the follow-up:
//   1. Pin the exact store that writes the chosen physical register number into a
//      web (single-step FUN_005077b0's inner FUN_00507a30/FUN_00507900 path, or
//      diff the web struct before/after FUN_00579cf0 for the byte that becomes the
//      home reg). The colorer-result reg also ends up in the IR operand used by the
//      'mr rDst,rSrc' emit that alloc_run.py already reads -- so the web struct
//      field can be cross-checked against the known final assignment.
//   2. Once the reg field offset is known, hook FUN_00579cf0 onLeave and walk
//      DAT_005e87b0, emitting (web_index p[7], reg field, source name if present)
//      in list order == the order the model needs.
//
// Usage (once completed): frida -f mwcceppc_priv.exe <args> -l frida_colorer_probe.js
// Run against the PRIVATE copy only.

const BASE = Module.getBaseAddress('mwcceppc_priv.exe') || Module.getBaseAddress('mwcceppc.exe');
function va(addr) { return BASE.add(addr - 0x400000); }

const FUN_color_step = va(0x579cf0);
const DAT_web_list   = va(0x5e87b0);
const DAT_class      = va(0x5e931f);

console.log('[frida] base=' + BASE + ' color_step=' + FUN_color_step);

Interceptor.attach(FUN_color_step, {
  onLeave: function () {
    const cls = Memory.readU8(DAT_class);
    let p = Memory.readPointer(DAT_web_list);
    let order = [];
    let guard = 0;
    while (!p.isNull() && guard++ < 4096) {
      const idx = Memory.readU32(p.add(7 * 4));   // p[7] web index
      // NOTE: reg field offset UNKNOWN -- placeholder dump of first 0x20 bytes so
      // the follow-up can eyeball which byte changed to the home reg.
      order.push('idx=' + idx);
      p = Memory.readPointer(p);                   // *p == next
    }
    console.log('[color_step done] class=' + cls + ' webs(list order)=' + order.join(' '));
  }
});
