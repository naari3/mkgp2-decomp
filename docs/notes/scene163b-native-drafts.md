# scene163b-native-drafts

Source: Codex worker cxc_u13_scene163b_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

801654E0 is a real scene constructor with SceneRoot destructor dtor_8007D0D4 and nested panel base destructor dtor_801419C8. Debug cases 0..11 are in switch-table order. Case 2 writes three blocks of eight bytes at playerData+0x1BA, comparing inner index 0..7 to value on every block. Explicit zero assignments (ascending field order) and a post-call conditional expression for count reproduce target. Explicit word-pair copying reaches 99.94582% with all EH/data exact, but pair scratch ordering remains unresolved; reversed local declarations do not move it. Native drafts use three structural approaches per function; no impossibility claim.
