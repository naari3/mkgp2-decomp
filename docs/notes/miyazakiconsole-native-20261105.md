# miyazakiconsole-native-20261105

Source: Codex worker cxc_u8_miyazaki17e_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 424 B.

fn_8017FD68: original function is a new-derived-mode factory, not just a free C initializer. Use canonical DemoRoot base, an 8-byte derived MiyazakiMode with an undefined key virtual, pass lbl_80376220 as ctor argument from outside new to preserve r30 across allocation, and inline ConsoleDisplay::Enable() instead of directly storing through a byte pointer: the inline method prevents li 1 being hoisted to r30 across fn_801DAEC0. Native text424/extab44/extabindex12 all100. Other six drafts retained NonMatching with per-function evidence; no asm/manual EH. DVD umbrella header pulls unavailable stdarg.h in this game recipe, so a private ABI view mirrors DVDDir and DVDDirEntry.

## c16_u115_20261106
Source: Codex worker c16_u115_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_8017F538 c16 retry: baseline11 register-only rows. Inline AddBankNames(Menu*) restores nine-item loop index r31 with no extra move, improves99.823845->99.85095; bank menu/walker remain swapped and numbered/stream menu pointers retain opposite r31/r29 homes. Explicit walker adds mr; helpers owning menu creation shift allocation globally and regress99.47154. Single function remains NonMatching; no B rescue. No c4-specific findings found in existing docs or scoped source commit history.

## c18_u234_20261107
Source: Codex worker c18_u234_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u234 retry fn_8017EC90: owning rodata 80376220..80376E10 as actual native integer/float tables and separate strings fixes both table addressing sequences: addi r3,r31,57C; slwi; lwzx replaces folded slwi/add/lwz57C. Fresh baseline91.48402 improves95.45662. Cursor/footer arithmetic reassociation remains. Unsigned locals invariant; reference-mutating row helper regresses94.77169, reverted. Existing data/EH100; newly owned rodata99.95089 solely for3 trailing alignment bytes at80376E0D..80376E10 after clSceneInterface. No filler added. Ten pool R_NONE metadata differences still affect object score despite matching immediate/addressing opcode bytes. Single function stays NM; final coordinator fallback DOL SHA1 exact.

## c20_u47_20261108
Source: Codex worker c20_u47_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u47 fn8017F538 improves99.85095->99.8916/1476B by ListStreamFiles(Menu *&m,const char *s) assigning creation to a dedicated block-local streamMenu output. All three stream receiver rows at8017F8F0/90C/9C0 now targetr29; every other instruction unchanged. Shared stream/character selection fixes stream but shifts character tor30 (99.71545); restricting output lifetime preserves original character local. BankMenuBuilder member helper98.69919 adds4B; explicit byte induction invariant; all-case menu reuse99.57995; independent per-case menus99.44444. All rejected probes archived. Seven residual rows: bank menu/walkerr29/r30 vs targetr30/r29, numbered receiverr29 vs targetr31. Data48/EH8/index12 all100; no config/pool/bridge changes. Single function staysNM; coordinator full fallback DOL SHA1ea30f3b1 exact; native gain0.

## c20_u138_20261108
Source: Codex worker c20_u138_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 3648 B.

c20_u138: fn8017EFFC 99.902435->100 by correcting fn801915DC prototype to unsigned char(int), matching its real lbz-return callee. This alone changes LR/r28 restore scheduling to target; both other functions stay100. Whole-menu helper changes loop homes, title helper invariant; GC1.3.2r/1.3 regress. Flip merged EC90 TU Matching with DATA_ALIGN4_TUS entry (data begins804918C4); first link grew section12 by32B, second full DOL SHA1 exact. All assigned ELF text2216/EH24/index36/data148/rodata3056 ranges identical, including three linker-generated trailing rodata alignment bytes; no filler. Native gain3fn/2216B, newly exact492B. Default pool R_NONE metadata differs but normalized objdiff/report text100. No split, symbol, shared-header or EH-map edits.
