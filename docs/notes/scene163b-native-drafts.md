# scene163b-native-drafts

Source: Codex worker cxc_u13_scene163b_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

801654E0 is a real scene constructor with SceneRoot destructor dtor_8007D0D4 and nested panel base destructor dtor_801419C8. Debug cases 0..11 are in switch-table order. Case 2 writes three blocks of eight bytes at playerData+0x1BA, comparing inner index 0..7 to value on every block. Explicit zero assignments (ascending field order) and a post-call conditional expression for count reproduce target. Explicit word-pair copying reaches 99.94582% with all EH/data exact, but pair scratch ordering remains unresolved; reversed local declarations do not move it. Native drafts use three structural approaches per function; no impossibility claim.

## c3_n3_scene16_20261105
Source: Codex worker c3_n3_scene16_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 5568 B.

2026-11-05 c3_n3_scene16: fn_801654E0 matched via DebugEntry163 = {pair, int, pair, int, float} with implicit operator= (8-byte sub-struct copies give the lwz pair scratch order); the TU needs DATA_ALIGN4_TUS. fn_80163EF4 matched by using float literals (0.0f / 1.0f / (1.0f / 60.0f) / 60.0f) instead of extern const lbl_806D88xx. fn_80164614 97.10%: the remaining residual is CW TU-pooled rodata addressing (addi r0,r29,0x44c rematerialized), which a char* or struct overlay of Scene_80164614_rodata_80369798 cannot reproduce.

## c18_u87_20261107
Source: Codex worker c18_u87_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u87: Owner-approved real TU constant pool ownership resolves the c3 pooled-addressing residual for fn_80164614. Adding .rodata 0x80369798..0x80369D78 and real float/entry/string/Vec constants reproduces base+0x44c rematerialization; pool symbols all 100%, .rodata 100%. Text improves 97.09633 to 98.6315 but remains NM: const entry.character cached across calls, DVD size/buffer register swap, constant-one hoisting, late enemy webs. Casting through mutable local/per-access pointers worsens (96.0/97.59939); external table linkage and generic const character inline accessor are invariant (98.48624 before pool split). Full coordinator build req2 SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65, fallback input, native gain zero. No filler objects or source-closed claim.

## c19_u37_20261107
Source: Codex worker c19_u37_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u37: baseline/final98.6315 invariant after correcting DVD start/length to canonical unsigned32 and ItemSelect_GetSlotItemId return to actual int. Mutable table definition changes cached-character code but moves 96B into data (132B total), text96.489296/2636B, rodata93.50474; discarded. DVD buffer declaration before size is invariant. Three approaches exhausted below99; single-function TU remainsNM, no native gain. Only private-header semantic type corrections retained; complete final objdiff JSON equals baseline.

## c20_u26_20261108
Source: Codex worker c20_u26_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u26: fn_80164614 98.6315 -> 98.66208% by fixing a real missing argument: canonical DVDLoad_WaitIfSamePage(unsigned int offset) must receive file.start. Old declaration was void(void). Corrected to int(unsigned int), plus RecordOpStart unsigned offset. This recovers exact target DVD bounds scratch lwz r4,length / lwz r3,start / subi r25,r4,1 / add r25,r3,r25 / bl wait. Whole race-init inline helper is invariant; direct enemy global arguments regress97.133026 because MWCC puts GetEnemyParam before global loads. Retained minimal semantic fix, all other section scores unchanged. Still2620/2616B and one function; NM, native gain0, full fallback DOL SHA1 exact.
