# miyazakiconsole-native-20261105

Source: Codex worker cxc_u8_miyazaki17e_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 424 B.

fn_8017FD68: original function is a new-derived-mode factory, not just a free C initializer. Use canonical DemoRoot base, an 8-byte derived MiyazakiMode with an undefined key virtual, pass lbl_80376220 as ctor argument from outside new to preserve r30 across allocation, and inline ConsoleDisplay::Enable() instead of directly storing through a byte pointer: the inline method prevents li 1 being hoisted to r30 across fn_801DAEC0. Native text424/extab44/extabindex12 all100. Other six drafts retained NonMatching with per-function evidence; no asm/manual EH. DVD umbrella header pulls unavailable stdarg.h in this game recipe, so a private ABI view mirrors DVDDir and DVDDirEntry.

## c16_u115_20261106
Source: Codex worker c16_u115_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_8017F538 c16 retry: baseline11 register-only rows. Inline AddBankNames(Menu*) restores nine-item loop index r31 with no extra move, improves99.823845->99.85095; bank menu/walker remain swapped and numbered/stream menu pointers retain opposite r31/r29 homes. Explicit walker adds mr; helpers owning menu creation shift allocation globally and regress99.47154. Single function remains NonMatching; no B rescue. No c4-specific findings found in existing docs or scoped source commit history.

## c18_u234_20261107
Source: Codex worker c18_u234_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u234 retry fn_8017EC90: owning rodata 80376220..80376E10 as actual native integer/float tables and separate strings fixes both table addressing sequences: addi r3,r31,57C; slwi; lwzx replaces folded slwi/add/lwz57C. Fresh baseline91.48402 improves95.45662. Cursor/footer arithmetic reassociation remains. Unsigned locals invariant; reference-mutating row helper regresses94.77169, reverted. Existing data/EH100; newly owned rodata99.95089 solely for3 trailing alignment bytes at80376E0D..80376E10 after clSceneInterface. No filler added. Ten pool R_NONE metadata differences still affect object score despite matching immediate/addressing opcode bytes. Single function stays NM; final coordinator fallback DOL SHA1 exact.
