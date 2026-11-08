# CW section-relative string addressing: define the strings in the TU (2026-06-10)

Observed while matching game/MemoryManager_Alloc.cpp (MemoryManager_AllocTagged @ 0x8003ADFC, batch_text_8003adfc_memmgr_alloc).

Symptom: target asm caches a .rodata string-pool base in a callee-saved reg (`lis r5, lbl_802E9D90@ha; addi r31, r5, lbl_802E9D90@l` directly in the prologue) and addresses each string as a raw immediate offset, including the offset-0 form `addi r5, r31, 0x0`. No C source form using EXTERN declarations reproduces this:

- `extern char lbl[]` + `lbl + 0x20` per-use: per-use lis/addi reloc pairs, no CSE.
- `char *strs = lbl;` local: `mr r5, r31` instead of `addi r5, r31, 0x0`; decl before other locals also emits the @l add into a temp + `mr r31, temp`.
- struct pointer / C++ reference / `strs[0]` row indexing: all fold the +0 to `mr`.

Fix: the strings belong to the original TU itself. DEFINE them as named const char arrays in the TU (`extern "C" const char lbl_802E9D90[0x20] = "...";` etc.) and reference them directly. CW 1.3.2 addresses its own .rodata section-relatively (`...rodata.0` + addend): with 4+ uses across calls it CSEs the section base into a callee-saved reg in the prologue and lowers every use as `addi rD, rBase, off` - keeping `+0x0` - while functions with single uses rematerialize per-symbol lis/addi pairs (exactly the mixed pattern in MemoryManager_AllocTagged vs MemoryManager_Free).

Wiring: the TU takes a `.rodata start:0x802E9D90 end:0x802E9DF8` split range; symbols.txt objects are resized/added to match the per-string array objects (lbl_802E9D90 0x1F->0x20 absorbing dtk's gap byte, lbl_802E9DB0 0x20->0x10 split into lbl_802E9DB0 + new lbl_802E9DC0, lbl_802E9DD0 0xE8->0x18 with new lbl_802E9DE8; remainder 0x802E9DF8.. returns to the auto rodata blob). Cross-TU refs (MemoryManager_TimedFree.cpp externs lbl_802E9DB0/lbl_802E9DD0) still resolve because the definitions are extern "C" globals. objdiff 100.0 on .text, extab, extabindex and .rodata; SHA-1 OK.

Likely applies to the rest of the MemoryManager family: FUN_8003b120 (0x8003B120) and Alloc (0x8003B1FC) also load r31 = lbl_802E9D90 and index the same pool (offsets 0x40+: "operator new[]", "broken ..." messages at 0x802E9DF8..0x802E9EB8). When matching those, extend/transfer pool ownership accordingly.

## c7_s16_20261105
Source: Codex worker c7_s16_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 388 B.

fn_80170544: owning the genuine clKPThunder string arrays 8036E118..8036E21C restores exact native ctor text and EH. Leave 8036E21C..8036E220 to ordinary fallback alignment; no zero filler required. Objdiff .rodata can report 99.6139% because string-length symbols omit per-array padding even though both ELF .rodata sections are exactly 260 identical bytes. Full source-linked DOL SHA-1 and actual 80170544/388 range verified.

## c19_u120_20261107
Source: Codex worker c19_u120_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u120 fn8016FE44: targeted declaration int alphaA,alphaB BEFORE RenderJoint*a,*b (assign later) fixes every saved GPR home,98.25085->99.2. Named selected int alpha and normalized float opacity before direct color call fixes compare scratch r3,99.2339. ABI-identical private declaration Object_SetColorAlphaOnly(model,float,int) and corresponding call fixes final lir4 scheduling/byte conversion scratch,99.94576. Retained1180B/EH8/index12 all owned EH exact after add-only @134/@135 bridges. Score normalizes stack offsets:16 raw instruction arg differences remain, frame50 vs60 and conversion spills18/20 vs20/28/30. Input-conversion SparkProgress inline helper also leaves stack unchanged and collides cookie@136 with oldEH bridge. Byte local alpha removes target call moves; signedlong invariant. Six hypotheses exhausted. One function, no B; remainsNM with full fallback SHA1exact,zero native gain.

## c21_u59_20261108
Source: Codex worker c21_u59_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1180 B.

c21_u59 fn8016FE44 resolves99.94576->100 naturally: replace scalar inline Clamp01 with #define Clamp01(value) ((value)<0.0f ?0.0f : ((value)>1.0f ?1.0f :(value))). Pure (float)(timer-delay)/60.0f arguments repeat in macro source, and emitted code exactly matches target including all16 previously stubborn conversion-stack operands/frame0x60. Likely the duplicated input conversions create distinct scratch storage before CSE; that allocation explanation is inference, but exact code is observed. No manual scratch, padding, optimization pragmas, pool ranges or EH map edits. All1180B text/EH8/index12 exact; Matching source-linked full DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; actual main.elf1180B range checked. Prior alpha continuation, int-double-float, output-reference helper and C frontend probes did not fix slots. Current macro callers have no side effects.
