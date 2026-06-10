# CW section-relative string addressing: define the strings in the TU (2026-06-10)

Observed while matching game/MemoryManager_Alloc.cpp (MemoryManager_AllocTagged @ 0x8003ADFC, batch_text_8003adfc_memmgr_alloc).

Symptom: target asm caches a .rodata string-pool base in a callee-saved reg (`lis r5, lbl_802E9D90@ha; addi r31, r5, lbl_802E9D90@l` directly in the prologue) and addresses each string as a raw immediate offset, including the offset-0 form `addi r5, r31, 0x0`. No C source form using EXTERN declarations reproduces this:

- `extern char lbl[]` + `lbl + 0x20` per-use: per-use lis/addi reloc pairs, no CSE.
- `char *strs = lbl;` local: `mr r5, r31` instead of `addi r5, r31, 0x0`; decl before other locals also emits the @l add into a temp + `mr r31, temp`.
- struct pointer / C++ reference / `strs[0]` row indexing: all fold the +0 to `mr`.

Fix: the strings belong to the original TU itself. DEFINE them as named const char arrays in the TU (`extern "C" const char lbl_802E9D90[0x20] = "...";` etc.) and reference them directly. CW 1.3.2 addresses its own .rodata section-relatively (`...rodata.0` + addend): with 4+ uses across calls it CSEs the section base into a callee-saved reg in the prologue and lowers every use as `addi rD, rBase, off` - keeping `+0x0` - while functions with single uses rematerialize per-symbol lis/addi pairs (exactly the mixed pattern in MemoryManager_AllocTagged vs MemoryManager_Free).

Wiring: the TU takes a `.rodata start:0x802E9D90 end:0x802E9DF8` split range; symbols.txt objects are resized/added to match the per-string array objects (lbl_802E9D90 0x1F->0x20 absorbing dtk's gap byte, lbl_802E9DB0 0x20->0x10 split into lbl_802E9DB0 + new lbl_802E9DC0, lbl_802E9DD0 0xE8->0x18 with new lbl_802E9DE8; remainder 0x802E9DF8.. returns to the auto rodata blob). Cross-TU refs (MemoryManager_TimedFree.cpp externs lbl_802E9DB0/lbl_802E9DD0) still resolve because the definitions are extern "C" globals. objdiff 100.0 on .text, extab, extabindex and .rodata; SHA-1 OK.

Likely applies to the rest of the MemoryManager family: FUN_8003b120 (0x8003B120) and Alloc (0x8003B1FC) also load r31 = lbl_802E9D90 and index the same pool (offsets 0x40+: "operator new[]", "broken ..." messages at 0x802E9DF8..0x802E9EB8). When matching those, extend/transfer pool ownership accordingly.
