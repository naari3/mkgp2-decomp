# triforce-acsocket

Source: Codex worker c3_u14_acsocket_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 12 fn / 3040 B.

acSelect target captures exOff/wrOff/rdOff before null-pointer short-circuit checks. wrResult/exResult precede sem/k declarations to reproduce register reuse; sign-bit result test produces rlwinm rather than signed cmpwi. The parser delimiter must be a named const char object in sdata2; unqualified string literals otherwise emit sdata. The 23-function range has no extab/extabindex constraint and can be split at all function boundaries. Shared BSS remains target fallback in acsocket_nm7.c. Further missing addi-zero address operations likely require the original helper shape; accumulator and pointer-offset variants did not reproduce them.

## c14_u13_20261106
Source: Codex worker c14_u13_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

acInetAddr: static inline clear-and-return helper (u8* p=BufPtr(0); memset(p,0,0x40); return p;) used before memcpy retains staging buffer in r27 and reproduces target buffer address/move shape. Objdiff improves 93.60274 to 95.61644. Source stays 288 vs target 292 bytes; addi-zero in board offset address and related load/add scheduling remain. Local pointer alone gives 95.20548. Aggregate first-member and pointer-typed base experiments still fold zero offset; no flags changed.

## c14_u19_20261106
Source: Codex worker c14_u19_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u19: acModifyMyIPaddr measured baseline 93.38461% (assignment 94.03%). Retaining a buffer pointer across memset/strlen/memcpy using a paired inline buffer/offset getter improves to 95.25641%. Source text remains 308 B versus target 312 B: target has addi r29,r5,0 and uses offset r29, source folds add and assigns offset r25. BufDev(k,0) alone and byte-pointer offset arithmetic do not preserve the zero add; no register permutations tried. NonMatching remains; full build SHA-1 OK, fallback source_input false.

## c16_u5_20261106
Source: Codex worker c16_u5_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u5: acBind inline GetSocketBuffer(n,&off) plus ClearBindBuffer(k,&off), retaining returned pointer through memcpy, improves 95.21176 to 96.76471%. Source stays 336 vs 340 B; target zero add at 0x80292688 still folded, and helper out-parameter changes register partition. Independent offset getters and native aggregate buffer views do not reproduce acAccept separate base+offset calculations (89.27928, 88.15315, 78.03603 vs 89.4955 baseline); acAccept restored unchanged. No flags/splits changed, NonMatching retained, full coordinator build DOL SHA-1 OK, zero native gain.

## c17_u24_20261107
Source: Codex worker c17_u24_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u24: acsocket_nm7 remains NonMatching, native gain 0. Fresh direct objdiff: fn_80292D18 89.23881 -> 96.268654 by static inline ReceiveBuffer(dst,off,mis,&al); it restores off/dst/len homes and early aligned-offset calculation. Remaining selected-buffer direct r27 versus target short-lived r4 plus late save, rounded-end add association, source 264 vs target268. InitSocket inline helper called four times improves initializer34.037384 ->73.76636 and restores target428B/frame10/save r31, but signed loop backedge versus target CTR16 and scratch scheduling remain. Natural for unrolls8, single-helper do/while56.093456. Poll explicit return capture invariant; descriptor helper swaps socket/semaphore homes; completion helper adds branch. ReadResponse per-case scopes, target declaration ordering and inline ReadSocketAddress do not improve baseline. BSS remains original 94.11732%: AcState currently combines target header and socket array; no new padding/storage changes. Final full fallback DOL SHA1 exact.

## c18_u121_20261107
Source: Codex worker c18_u121_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 44 B.

c18_u121: acConnect 95.62366 -> 96.344086 by inline ClearConnectBuffer(k,&off): capture base=k->bufAddr, buf=BufPtr(0), *off=base+State.bufOff; memset(buf,0,0x40); return buf. Caller retains returned buf through memcpy. This restores target off r24 / buf r25 and removes bounce address rematerialization before memcpy. Source remains 368 versus target 372 bytes: target addi r24,r5,0 at 8029243C absent; State/Buf address scratch r3/r4 and loaded bufAddr/bufOff r0/r5 swapped; add/mr schedule differs. Optional-output generic getter retains stack-pointer null check/spill (85.129036); aggregate pair get/clear returns emit stack copies (80.02151). Both rejected. NonMatching retained, full fallback DOL SHA-1 exact; no native gain, no range/flag changes.

## c18_u120_20261107
Source: Codex worker c18_u120_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u120: acInetAddr paired CPU/board getter plus ClearInetBuf(k,&off) improves 95.61644 to95.821915, still288 vs292B. Writing *off=k->bufAddr+*off restores target operand/load order. Target +0x80 addi r26,r5,0 remains folded; target mr-before-add is source add-before-mr. Cursor reserve variant95.753426; optional-null output retains branch/stack home71.49315; native by-value CPU/board descriptor spills66.21918. Three structural approaches exhausted; no flags/data/splits changed, no split rescue or native gain.

## c19_u261_20261107
Source: Codex worker c19_u261_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 588 B.

c19_u261: acReadResponse 98.82653 ->100 via complete-body static inline ReadResponse wrapper and case-local declarations ordered addr,len,base,lenOff,n in both branches. Wrapper alone99.38776; mixed case declaration order makes case22 exact but leaves two swapped pairs in case1; same target order in case1 closes both. Mechanism B isolates acPollResponse+acReadResponse (0x80292E24..0x80293070) as Matching acsocket_m8.c; source-linked +2 fn/+588B, full DOL SHA1 exact. Initializer explicit 16-batch outer counter generates target CTR16, improves measured73.76636 ->81.46729 before split,81.98131 after split; ready/limit hoisting and scratch scheduling remain. Receive PrepareReceive out-parameter helper, whole-body helper, signed-offset probe all invariant96.268654; original kept. Combined BSS remains fallback94.11732. No data/header/tool changes.

## c19_u283_20261107
Source: Codex worker c19_u283_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u283: whole-body static inline Accept wrapper improves acAccept 89.4955 -> 89.90991%, source remains436 vs444B. It restores byte-swap input r6 and socket buffer base r5, but shifts callee-saved homes (sem r29 vsr31, lenOff r31 vsr28, addrOff r24 vsr29). Typed length/address member projections and pointer-typed board address locals are invariant. acBind pointer-offset+base-first, whole-body helper, typed projection probes fail to improve96.76471%; original retained336 vs340B. Missing addi0/separate base adds persist; no exact subset, no flag/split changes, no native gain. Final source compile/postprocess and objdiff verified. No new full build requested; existing fallback baseline SHA1 exact.

## c19_u287_20261107
Source: Codex worker c19_u287_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u287: acConnect 96.344086 ->96.72043 via C++ reference-output GetConnectBuffer(n,off) nested in ClearConnectBuffer(k,off), capture base first; #pragma cplusplus on after existing C header, extern C exported acConnect. Fixes State/Buf scratches and bufAddr/bufOff load homes; missing addi r24,r5,0 plus add/mr ordering remain (368 vs372B). Complete-body Connect wrapper95.69892 swaps sem/socket saved homes; void helper with CPU+board reference outputs96.50538 swaps high-address scratches. Three structural hypotheses exhausted. No flag/range/header/data changes. Singleton TU remains NonMatching, no B cut/native gain; coordinator full fallback DOL SHA1 exact.

## c19_u298_20261107
Source: Codex worker c19_u298_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u298: acInetAddr 95.821915 ->97.26028 via board-side u8* address carried through paired getter/clear helper, plus whole-body static inline InetAddr/public wrapper. Pointer draft alone96.78082; pointer projection converted back to u32 in getter95.821915; C++ integer reference-output variant baseline-identical95.821915. Wrapper restores State r28/string r29; board offset r27 vs targetr26 and CPU buffer r26 vs targetr27 remain. Zero addi still missing; source288 vs target292B, li r5,0x40 scheduled early and add operands differ. Three structural approaches exhausted, best C retained, no flag/range/data/header changes or native gain. Archived c14/c18 drafts are under archive/<batch>/worker.patch and HANDOFF.raw.md, not archive/drafts.

## c21_u166_20261108
Source: Codex worker c21_u166_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u166: existing opt_lifetimes-off draft measures97.09677 but is forbidden in this lane; removed. Natural baseline96.72043/368B. Board offset u8*& with off=(u8*)State.bufOff+n and off+=base gives97.043015/368B without codegen pragma, retained consistent with acsocket_nm3. Casting back for integer addition returns96.72043 exactly. ClearConnectBuffer directly as memcpy destination is byte-invariant96.72043. Returning memset result instead of saved buffer loses two copies/saved staging pointer,96.43011/360B. Target addi r24,r5,0 absent in every probe; higher pointer score has 22 aligned rows of saved-register cycle vs four baseline rows. No pool/static ownership cause: zero add source is runtime-loaded bufOff. Single function prohibits B. All attempts under build/w/c21_u166. No config/range/header edits, no full service request; baseline fallback DOL hash rechecked exact, zero native gain.

## c21_u187_20261108
Source: Codex worker c21_u187_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u187: acAccept89.90991 ->94.675674 via byte-pointer board arithmetic (b+4)+State.bufOff; restores separate +4 and two base additions. In inline Accept, local order lenOff,addrOff,k,sem then improves96.11712, all saved-register homes exact (sem31,k30,addr29,len28). Final b is u8*. Pointer output offsets invariant96.11712. Residual target addi r28,r4,0 at80292810 folded, null second zero li becomes mr, li r4,0 scheduled late; source440 vs444B. acBind pointer grouping/pointer-output probes invariant96.76471, baseline restored byte-identically. Runtime bufOff source excludes static pool ownership cause. No config/split/data/header edits, no native subset or full build request; baseline fallback DOL hash exact. Attempts under build/w/c21_u187.

## c21_u191_20261108
Source: Codex worker c21_u191_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u191: initializer fn_80293070 81.98131 ->82.71028 by complete-body static inline InitSockets plus exported ABI wrapper. InitSocket ready parameter is byte-invariant81.98131; H2 GC/2.0 and2.6 both82.71028, production1.3.2 retained. Source432 versus target428: ready1 and limit63 remain rematerialized inside CTR16, State/index/comparison/multiply scratch homes and scheduling differ. regswap_classify reports r0/reg+other/multi/after_call/load,81 differing aligned rows. No pool ownership residual, single function prevents B. No flag/range/header/data edits or native gain; existing fallback DOL SHA1 exact.

## c22_u161_20261109
Source: Codex worker c22_u161_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u161: acConnect97.043015 ->97.849464 by returning board pointer from ClearConnectBuffer and passing CPU staging pointer as reference output. Restores argument/State saved homes, reduces six-cycle22 diff rows to CPU/board r24/r25 swap8 rows; still368 vs target372B, missing runtime bufOff addi-zero. Proper pointer base + integer displacement probe96.344086; combined stage/copy/DMA helper invariant97.043015; directed buf-before-off decl refinement invariant97.849464. Best H3 retained. No pool ownership cause, missing functions, data/range/config changes or native gain. Exact object compile/postprocess verified; fallback baseline hash exact, no service request. All probes build/w/c22_u161.

## c23_u147_20261109
Source: Codex worker c23_u147_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u147: acBind96.76471 ->97.64706 by ClearBindBuffer returning board byte pointer with CPU staging pointer output; capture bufAddr before getter, GetSocketBuffer off as u8**. Params/socket/sem/State homes exact; CPUr24/boardr25 swapped versus targetr25/r24, runtime bufOff addi-zero still missing;336 vs340B,8 aligned rows. Integer return variant96.411766 restores saved homes and narrows to4 rows but lower score. Nested offset getter invariant; CPU-local/output-after-clear refinement invariant. acAccept staging helper extraction and unsigned-int offset locals both byte-invariant96.11712; stopped after2. No pool ownership cause, no A/B native subset, no config/data/range/shared edits; only improved NonMatching source retained. Probes under build/w/c23_u147.

## c25_u98_20261110
Source: Codex worker c25_u98_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u98: acAccept96.11712 ->96.60361 by lifting lenOff/addrOff from inline Accept into acAccept named locals, declared addrOff then lenOff, passed as C pointer outputs. Restores NULL li/li and target saved homes. Initial reverse declaration96.24324. Caller-owned offsets plus AcceptBuffer member projection96.46847; C++ ref outputs invariant96.60361. Missing runtime bufOff addi0 and resulting r4 lifetime/schedule persist;440 vs444B. acBind unsigned-int board address and both-address-output probes invariant97.64706, stopped after two. TU .text97.05612; no A/B exact subset, no flags/ranges/header/data changes. Existing fallback DOL rehash exact; no service request.

## c26_u76_20261110
Source: Codex worker c26_u76_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c26_u76: fn_80292D18 improves96.268654->99.850746 with p=(u8*)(void*)ReceiveBuffer(...) (rule76 cast-keeps-copy-of-cse-temp) plus rounded end ((len+off)+0x1F) (rule84 three-term-sum-grouping-rotation). Now target268B and exact all but addi/add source operands: ours off+31 then len, target len+31 then off. H3 pointer sum and H4 size inline revert93.1194; H5 named expanded buffer98.283585 adds branch-local mr; H6 signed offset invariant99.850746. BSS94.11732 unchanged. All drafts/JSON build/w/c26_u76. NonMatching, no native gain.
