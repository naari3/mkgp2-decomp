# asm2c-lessons

Source: Codex worker c10_ou_asm2c_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 9 fn / 4220 B.

MWCC GC/2.6 -Cpp_exceptions: a function that destroys a member whose class has an IMPLICIT (compiler-generated) destructor is deferred to the end of the TU .text. Declare the dtors (even `~X() {}`) to keep definition order. `x >= N` after `x += 1` without reload comes from `if ((x += 1.0f) >= N)`. rlwnm r0,1,cntlzw,31,31 is `v <= 0` as bool.

## c11_oaa_asm2c_20261106
Source: Codex worker c11_oaa_asm2c_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 10 fn / 5924 B.

RaceHud_80147470 (c11): extern "C" deleting dtors with `throw()` reproduce the SPECIFICATION extab + __unexpected island without mangled names. A double `cmplwi;beq;beq` before a virtual delete is `if (p) delete p;`. A const .rodata table must be declared `extern const` - it changed FPR numbering (its load is no longer ordered after float stores). postprocess_sdata2 maps each anonymous literal by its FIRST reloc: equal-valued constants that the target keeps in separate per-function labels need extern const labels in all but the first (address-order) user; the int->float magic double cannot be handled that way (fn_80149E44 blocked). The colour insert `li r,-0x100; rlwimi r,a,0,24,31` is GC/2.x only; GC/1.3.2 gives clrlwi/oris/ori. CW auto-inlines a small earlier extern "C" function into a later caller; `#pragma auto_inline off/reset` around the CALLEE definition keeps the bl.
