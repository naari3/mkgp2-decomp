# StrPcb_Init / Shutdown / EnsureInstance (0x80038288..0x80038778) — parked

Draft: StrPcb_Lifetime.draft.cpp (C++ class with StrPcbScratch member @0x68,
StrPcbStopwatch local; renames __ct__6StrPcbFi->StrPcb_Init,
__dt__13StrPcbScratchFv->dtor_8003871C, __dt__15StrPcbStopwatchFv->dtor_8002F978;
needs -use_lmw_stmw on and absorbing StrPcb_GetInstance.c).

Status: GetInstance/EnsureInstance/dtor_8003871C 100%, Shutdown 94.5%, Init 82%.

Blockers:
- Init keeps one base register for StrPcb_Init_bss_80598100 (tx/rx) + 0x400 (packet) + 0x40C (log):
  in the original those buffers were file-local statics of one big StrPcb TU
  (0x80036E7C..0x80038778 incl. StrPcb_Tick/Control/Commands). With extern
  globals CW rematerializes lis/addi per use. Real fix = merge all StrPcb TUs into
  one C++ TU with static buffers (needs StrPcb_WaitForState1 matched first).
- The inline Stopwatch dtor emits a weak copy in this TU (real one is in HeapStats).
- Shutdown: pcb gets copied r6->r31 and `delete` re-checks null; target has neither.
