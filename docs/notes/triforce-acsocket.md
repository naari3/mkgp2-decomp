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
