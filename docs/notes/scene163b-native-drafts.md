# scene163b-native-drafts

Source: Codex worker cxc_u13_scene163b_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

801654E0 is a real scene constructor with SceneRoot destructor dtor_8007D0D4 and nested panel base destructor dtor_801419C8. Debug cases 0..11 are in switch-table order. Case 2 writes three blocks of eight bytes at playerData+0x1BA, comparing inner index 0..7 to value on every block. Explicit zero assignments (ascending field order) and a post-call conditional expression for count reproduce target. Explicit word-pair copying reaches 99.94582% with all EH/data exact, but pair scratch ordering remains unresolved; reversed local declarations do not move it. Native drafts use three structural approaches per function; no impossibility claim.

## c3_n3_scene16_20261105
Source: Codex worker c3_n3_scene16_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 5568 B.

2026-11-05 c3_n3_scene16: fn_801654E0 matched via DebugEntry163 = {pair, int, pair, int, float} with implicit operator= (8-byte sub-struct copies give the lwz pair scratch order); the TU needs DATA_ALIGN4_TUS. fn_80163EF4 matched by using float literals (0.0f / 1.0f / (1.0f / 60.0f) / 60.0f) instead of extern const lbl_806D88xx. fn_80164614 97.10%: the remaining residual is CW TU-pooled rodata addressing (addi r0,r29,0x44c rematerialized), which a char* or struct overlay of lbl_80369798 cannot reproduce.
