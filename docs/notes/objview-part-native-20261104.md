# objview / map-effect parts (anon_80197130) — 2026-11-04

Source: Codex worker cx_a3_objview_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

## Native (source-linked, text/EH/data exact)
- fn_80198F84 (812B): representing the nearest-driver position as a by-value aggregate copy reproduces the temporary stack slot; plain `char` tracking/hit fields give signed compares without extsb.
- fn_801992B0 (1608B): named local vector copies passed to pointer ABIs reproduce the stack layout; compiler-generated 32-byte jump table matches (automatic local jump-table symbol name differs, relocations/data equal). The ground-advance return value is intentionally unused, as in the target.

## Honest NonMatching (kept as native drafts, budget exhausted)
- fn_80197130 99.68% / fn_80197F24 99.57%: native C++ scoped GXChannel lifetime, EH equal; residual GPR reuse / FPR assignment (F24: second-loop count/stride registers swapped; explicit stride trial worse).
- fn_801980C8 99.73%: writable random tables must be declared without `const` (moved index stores before indexed float loads, 93.90% → 99.73%); residual FPR identities.
- fn_80198ABC 99.74%: an explicit no-op `case 2` in the first inner switch is required to keep one branch and match text/EH lengths; residual FPR identities in height/lift clamps (named float intermediates did not move them).
- fn_80197D20 95.92% (worker-side bridged measurement): real derived C++ part constructor with `new`; resource-pool base/address scheduling differs. The worker's ad-hoc `configure.py` hook that rewrote build.ninja to inject llvm-objcopy renames was NOT accepted (non-standard tooling); a future attempt should use per-TU entries in `tools/extab_user_renames.json` (see cpp-ctor-retrofit-mangled-bridge.md). Without that bridge its object-level objdiff reads lower; it is NonMatching either way.
- fn_801972E0 (2468B) and fn_801987C4 (760B, part ctor with EH actions): not attempted (time), still in auto blobs.

## anon_8018F100 objview/zprobe singletons (cxb_b3, 2026-11-04)
- fn_80190064 (712B) native exact: carry the attribute value from the loop condition into the body (removes a redundant reload); shared reset helper for attribute setup.
- Honest NonMatching (3 approaches each unless noted): fn_8018F1E0 98.50% (literal FP constants beat extern constants; residual self/sid register identity), fn_8018F614 94.76% (2 approaches; real derived C++ part ctor with `new`, EH exact; base-vptr/address scheduling differs), fn_8018F8A8 98.91%, fn_8018FC24 97.19% (declaration order / destination-first expression best), fn_801903D0 98.98% (native `new` table entries; extra address-register copy). Per-TU bridges for the two C++ TUs are in tools/extab_user_renames.json.

## cxc_u6_objview186_20261105
Source: Codex worker cxc_u6_objview186_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

801869F8/80187084/80187410 operate on a two-element 0x54-byte path state: joints[4], points, count/index, three control vectors, t, position and yaw. 80187084 advances quadratic interpolation and heading; 801869F8 performs culling/rotation and two HSD render passes. Native drafts and residuals are in this batch HANDOFF. C++ ctor 80187410 emits exact owned extab with canonical base destructor and guarded clNormal3D new.

## c4_t1_objview_20261105
Source: Codex worker c4_t1_objview_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1224 B.

c4_t1_objview_20261105: fn_80198ABC promoted native1224B. Scalar float literals (0,11,0.2,1,-0.1,2,0.05,5) instead of extern const objects resolve height/lift clamp FP identities; existing sdata2 postprocessor bridges constants, all text/EH/index100 and source-linked DOL SHA1 OK. Inline clamp parameterization is a no-op. fn_801980C8 remains99.72938: literal constants and integer-index helper return both leave identical15 FP operand residuals; moving arithmetic inside helpers does not fix homes and adds factor1 multiply. All C8 experiments reverted.

## c5_s21_fn801807e0_20261105
Source: Codex worker c5_s21_fn801807e0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c5_s21: inline extraction of only the position-interpolation loop as MorphBlend(MorphNode*,int,float) improves fn_8018F1E0 98.50282 -> 98.98305 while preserving 708B and exact EH/index. Still NonMatching: self/side r27/r28 swap and inner address/stride colors remain. Whole-node helper and widened side/index scopes are worse. Path186 index-first pointer helper and wrapped-integer-return helper are byte-identical negative probes. Menu direct clear / column-zero before clear are byte-identical negatives. Table global-direct loses hoist; reference retains extra base copy; later base initialization worsens zero scheduling. All failed variants reverted.

## c5_s22_fn8018f614_20261105
Source: Codex worker c5_s22_fn8018f614_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 384 B.

c5_s22: fn_8018FC24 matches 384B text plus 8B extab and 12B index by replacing external 360.0f constant uses with literals and extracting UpdateUV(Wave*) with local declarations src,dst,i and fu,fv. Phase FP registers and loop index/stride/pointer homes become exact. Coordinator full build SHA-1 OK, source .o on main.elf edge. fn_80197130 scene declaration after particle pointer resolves scene r30 reuse; per-TU typed GXChannel ctor/dtor bridge fixes EH and call relocations, leaving f30/f31 height-width swap. fn_8018F614 pairs-before-name declarations fix those homes; base-vptr scheduling remains.

## c5_s23_fn80197f24_20261105
Source: Codex worker c5_s23_fn80197f24_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 816 B.

c5_s23: fn_80197F24 reaches exact 420-byte text and 24/12-byte EH/index by passing the outer item-loop int i by reference to inline DrawParticles. This preserves count r29/stride r30 across both loops. Per-TU GXChannel ctor/dtor bridges required. Full source-linked DOL SHA-1 OK.

## c14_u26_20261106
Source: Codex worker c14_u26_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 556 B.

c14_u26: fn_8018D0F4 556B promoted native. Null-first inline Child/Next accessors restore target branch arm order (93.66907 ->99.568344). Plain float literals restore angle FP homes; direct o->angle += 1.0f restores field-before-constant load order. All text/extab8/index12 100%, existing TU flag Matching, source main.elf edge and full DOL SHA-1 verified. No split, EH bridge, data ownership or header edits.

## c14_u50_20261106
Source: Codex worker c14_u50_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u50: fn_8018DAD0 remains NonMatching, 91.69401 ->94.49527. Writable random tables fix random-factor/position load-store scheduling. Typed aggregate table view improves addressing versus char-pointer offsets but still folds per-type table bases into index+offset. Inline array-pointer helpers do not prevent folding; float literals slightly worsen scheduling. Residual table-base shape, factor FP homes, and final-loop GPR reuse; 3 hypotheses used, no native gain.

## c14_u53_20261106
Source: Codex worker c14_u53_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u53: fn_801972E0 correct writable random tables lbl_80495994/lbl_80495A94 (.data) removes const-driven scheduling divergence: 91.0859 ->99.88655, exact text size2468/extab8/index12. Only enabled flag r30/r28 at +34/+140 and final-loop li r30,0 versus mr r30,r28 at +7CC remain. Reusing outer loop i reproduces shared zero but swaps other homes; p reuse 99.70827, decl order unchanged. Inline UpdateParticles with index pointer 99.71637 leaves pointer/stride r29/r30 swap; explicit stride99.700165. All loop probes reverted. Honest NonMatching retained; no new native functions.

## c16_u17_20261106
Source: Codex worker c16_u17_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u17: fn_80187410 fresh87.502396->89.88039 via small CopyPoint(dst,src) inline helper. Three control copies remain scalar exact; final position copy now loads paths[i] once rather than three times, reducing852->836B and index100. Owned EH52B100. Initializer helper folds indexed stores, whole loop exceeds auto inline budget. Remaining def/stride r30/r31 exchange, point index/count scratch homes and pre-store loads; NonMatching, no native gain.

## c16_u122_20261106
Source: Codex worker c16_u122_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 432 B.

c16_u122: fn_80197130 reaches exact432B text/extab24/index12 by replacing external constants lbl_806D95E8/EC/F0/F4 with float literals 0.5f, 0.01745329238474369f, 0.0f, 0.1f. Baseline only four FP operands differed: height f31/width f30 versus target f30/f31. Existing GXChannel lifetime and typed bridge remain unchanged. Matching promotion source-linked on main.elf edge and coordinator full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified. No split/data/header/EH bridge edits.

## c17_u35_20261107
Source: Codex worker c17_u35_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 1832 B.

c17_u35: fn_80197D20/516B promoted native. The external char-pointer resource-base local caused extra mr and wrong prologue/vptr scheduling (bridged 95.92248%). Direct typed external pool members lose the hoist (90.209305%). Reconstructing original native bounds[2][5] and exact-sized class/base/delete/create/model strings at 8037DA90..8037DB74 makes CW emit one pooled rodata base and exact offsets, including addi r4,r30,0. Split old lbl_8037DB28 size50 into 1D-byte delete string, 1D-byte create string at DB48, and C-byte model string at DB68. Leave DB74..DB78 alignment in auto rodata; no filler needed. Per-TU ctor/vtable/callee/base-dtor and @102/@103 bridges restore all text516/EH88/index12/rodata228 object sections100. Matching source edge, all four main.elf ranges, and full DOL SHA-1 verified.

## c17_u70_20261107
Source: Codex worker c17_u70_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 748 B.

c17_u70: fn_80187084 native748B exact. Residual was 15 scratch GPR operands in three wrapped point lookups (index r0 vs target r3). Copy+lookup inline helper is byte invariant. Passing points/count/index separately puts count in target r0 but hoists points load and leaves index r4 (96.39037). CyclicPoint(Path186 *path,int count,int index), with wrap using count then return &path->points[index], defers storage load and produces exact index r3/count r0 in all three sites. All text748/extab8/index12 100%; Matching promotion, source main.elf edge and address/size, full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified. No shared header/EH bridge/data/split changes.

## c17_u100_20261107
Source: Codex worker c17_u100_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 648 B.

c17_u100: fn_801903D0 promoted native648B. Existing extern byte-block local produced extra base copy and first-site mr. Reconstruct eleven file-static geometry arrays (47 records of Vec3f[4], int flags, two reserved int fields) at803785F8..803790FC. Direct array references let CW manage one shared rodata base, giving target addi r31 and addi r4,r31,0. All text648/EH184/index12/rodata2820 objdiff100, original final4-byte alignment gap remains unowned, no filler. Existing ctor/new/delete bridges unchanged. Matching source main.elf edge, all four linked ranges exact, full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. One structural approach; prior direct-extern/reference dead ends not repeated.

## c17_u102_20261107
Source: Codex worker c17_u102_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 852 B.

c17_u102: fn_801807E0 exact852B via TU-local shared inline DrawBorderFrame(TextBuffer&,int x,int y,int lines), owning both row/column loops and line draw. Baseline98.96713 had two extra li r0,0 before clear; direct clear/order probes from c5 were known negatives. Row-only helper removes both loads but changes row homes (99.248825); row reference is invariant. Whole-frame helper leaves pure row/column swaps; declare col before row to get exact registers and text/extab8/index12 all100. Matching promotion source-linked at801807E0/852B and full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified. No split/data/EH bridge/shared-header changes.

## c18_u126_20261107
Source: Codex worker c18_u126_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u126: fn_801987C4 fresh94.5 ->99.552635%,760B exact, EH88/index12/rodata464 all100. Reconstruct original placements[2]/[4], shared origin Vec3 and exact-sized type/message/resource strings in own .rodata8037DB78..8037DD48; split DB78 and packed DC04 symbol into native objects. Native pool restores target hoisted base r31 and vptr scheduling (c13 direct extern pool probes could not). Indexed positions[i] restores missing walker copy. Remaining16 GPR operands are resource r28 vs targetr27 and positions/loop indexr27 vs targetr28. Reversed resource/position declarations invariant; member entry-loop helper fixes early homes but regresses loop and zero sharing; scoped loop indices regress; caller-index-by-reference helper returns same99.552635. Retain simple indexed NonMatching draft; one fn cannot split. Full coordinator build DOL SHA1 exact. Zero vector DBD8 is real shared origin used by fn801980C8, no filler.

## c18_u113_20261107
Source: Codex worker c18_u113_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 448 B.

c18_u113: fn_8018F614 unlocks 448B. Taking .rodata 80378210..80378524 into the TU as separate exact-size static strings and Pair[3] arrays restores original compiler-managed pool base r6/r30 and base-vtable address/store scheduling, resolving c5 prologue residual. Direct native array references are essential; external base-plus-offset spelling did not represent pool ownership. Split merged symbols at 803782DC/803783C4/803784AC and ctor log 80378504. Export external resource/RTTI/destructor-log strings with six per-TU global: bridges. Loop update cursor+=8,i++ fixes final instruction-order swap. All owned text448/EH88/index12/rodata788 100%; source main.elf edge and actual original-address ranges verified; full DOL SHA-1 exact. No padding objects; final 3-byte string alignment arises naturally, next 4-byte auto gap stays outside owned range.

## c18_u137_20261107
Source: Codex worker c18_u137_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u137: fn_801972E0 improves99.88655->99.95138%,2468B,EH8/index12 all100. Whole final-loop static inline UpdateParticles(o,motion), unlike c16 per-particle-body helper, fixes saved enabled r28 and shared-zero initialization but swaps final count/stride. Explicit byte offset with stride-first init/increment leaves only4 operands at+7D4/+964/+968/+96C (source count r30/stride r28 vs target count r28/stride r30); retained higher NonMatching draft. Camera-motion boundary worsens stack/vector layout; saved-flag/count reuse fixes early flag but swaps pointer/count; helper q/j reverse and by-value start index worsen pointer homes; caller stride by reference regresses early flag/scene. Six hypotheses including refinements; no singleton defensive getter or shared base constant-pool residual here. One function prevents B rescue; no flag/split/data changes or new full-build request.

## c18_u192_20261107
Source: Codex worker c18_u192_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u192: fn_8018F1E0 improves98.98305->99.77401%, unchanged708B/EH8/index12. New BlendVector(dst,b,a,blend), with already-resolved vector pointers, fixes both inner stride homes (c17 MorphVertex(n,side,i,blend) was invariant); right-to-left b/a argument order restores source load order. New MorphSides(n,angles) owns only the two-side loop, leaving phase setup and flush calls outside, and fixes selfr28/sider27 (c5 whole-node helper was worse). Remaining eight rows solely first input a=r5/dst=r4 vs targetr4/r5. Reverse local decls and destination pointer by address invariant; returned struct732B regresses; MorphInput(n,index,side) accessor regresses stride homes. Best two-helper NonMatching draft retained; no A/B rescue for single function, no flags/splits/data changes. Coordinator final full build SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact; zero native gain.

## c18_u212_20261107
Source: Codex worker c18_u212_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u212 fn_8018DAD0 improves94.49527->99.936905,1268B. Own native rodata80377F70..80378018: three bubble resource strings, six float[3] parameter arrays, joint string, actual zero nearest-position Vec3. Direct array references fix c14 folded offset addressing, factor FP homes, and text size. Split lbl80377F98 into exact18-byte string and six12-byte arrays; name origin8037800C. Whole final-loop static inline UpdateParticles(Owner*) fixes particle/count homes. Only stride r30 vs targetr26 remains at+400/+408/+4C4. Separate block indices99.432175; explicit local stride99.589905; helper offset param99.905365; caller count pointer99.589905. Keep best NonMatching; all EH/index/rodata100; fallback full coordinator DOL SHA1 OK. No B possible for singleton TU.

## c18_u237_20261107
Source: Codex worker c18_u237_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u237 fn_80187410 improves fresh89.88039->99.80861%,836B. Native rodata80377030..803772DC (two Vec3f arrays, eight joint strings, Path186Def[2], type/assertion/log/model strings) restores base/vptr homes and original pre-store joint/definition loads. Split packed 771C4/77260 symbols and export native static labels via per-TU global bridges. Separate count/index CyclicPoint and explicit independent byte-offset loop fix all saved GPRs. Remaining six operands only in first two lookups: mulli scratch r0 vs targetr3, points r3 vs targetr4, add operands. Scope decls and reversed accessor parameter order do not solve scratch homes. Text99.80861/EH52/index12/rodata684 all other sections100; no native gain, single-function TU remains NonMatching. Final coordinator full build SHA1 exact; no filler objects.

## c19_u26_20261107
Source: Codex worker c19_u26_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2468 B.

c19_u26: fn_801972E0 unlocks2468B from99.95138. Existing explicit-stride UpdateParticles helper declares offset,q,j; reverse to j,q,offset to make final count r28/stride r30 exact (99.975685, only initialization differs), then initialize j=0 before offset=0 while retaining offset-first increment expression. All text2468/EH8/index12 reach100, no other semantic/codegen changes. Long offset probe invariant and reverted. Existing EH suffices, no pool/singleton/header/split/bridge edits. Matching source edge and actual linked ranges verified; coordinator full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 OK. Native gain1fn/2468B.

## c19_u75_20261107
Source: Codex worker c19_u75_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 300 B.

c19_u75 fn_801869F8: named HSD_JObj *joint reused for guarded Z setters and render translation captures moves self to r31 and visibility base to r28, improving98.97375->99.51074. Extract only X/Y swing update to static inline SwingPath186 (retain reload p->joint[1] after X) gives99.749405. Declare Path186 *p before int i gives99.8926 with exact1676B/EH8/index12. Nine remaining rows are final-pass path r27 versus targetr26. Bool visible invariant; joint-before-path and assigning every post-call joint reload to joint invariant. No singleton/pool/A/B rescue applies. Retained improved honest NonMatching; full coordinator fallback-linked DOL SHA1 exact; native gain0.

## c19_u138_20261107
Source: Codex worker c19_u138_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 760 B.

c19_u138: fn_801987C4 unlocks760B from99.552635. Declare reused int i BEFORE resource and positions in constructor; this fixes all16 resource r28/positions+counter r27 vs target r27/r28 operand differences. Prior reversing pointer declarations alone was invariant because loop-index/placement web coalescing controls ranks. const void* descriptor probe invariant and reverted. Existing native pool and C++ EH bridges unchanged. Text760/EH88/index12/rodata464 all100, Matching source main.elf edge and function address/size verified; full coordinator DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact. No range/header/bridge edits or filler.

## c19_u237_20261107
Source: Codex worker c19_u237_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 688 B.

c19_u237: fn_801967F0 unlocks688B from fresh92.808136. Native static ParticleEmitter[7] and seven exact-sized type/log/resource strings in own rodata8037D888..8037D9E0 restore early pool base r29, vptr scheduling and direction stride r28 (97.60465). One constructor-scope int i reused across both loops fixes li/mr age-loop setup and gives text100. Partition packed D950 symbol into strings atD950/D970/D990/D9A8/D9C4; eight global: bridges export static native labels. All section objdiff100, full linked text/EH/index/rodata ranges exact and DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Native gain1fn/688B; no fillers. Last string endsD9DE; normal link alignment provides final2 bytes throughD9E0.

## c20_u41_20261108
Source: Codex worker c20_u41_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1676 B.

c20_u41 fn_801869F8 unlocks99.8926->100%/1676B by separating final render pass into const Path186 *renderPath; original p remains used by first two loops. Resolves all nine final-path r27 vs targetr26 operands without other instruction changes. Const indexed accessor at all lookups99.09308 and explicit final byte-offset99.463005 regress; narrow transform-only helper invariant99.8926. Text/extab8/index12 all100, Matching flag promoted; source main.elf edge and actual 801869F8/1676,80011C38/8,80026CE4/12 ranges exact. Coordinator full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No ranges/data/headers/bridges changed; native gain1/1676.

## c20_u114_20261108
Source: Codex worker c20_u114_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u114: commit87bd0412 improved F8A8 loop ordering but accidentally deleted cur=n, causing undefined behavior and a 840B source object versus844B target. Restore cur=n: valid draft99.05213%,EH8/index12 both100; relative to old valid98.90995%, loop tail now exact. Only remaining schedule is initial mr r31,r27 before two stack-base addi instead of after. Explicit byte offset is invariant; aggregate -1/NULL initializers do not move scheduling and add pool refs; whole allocation/bind/cleanup helper exceeds inline threshold. Retain one-line semantic correction, flagNonMatching, zero native gain. Full fallback DOL SHA1 exact. No singleton/pool/A/B rescue applicable.
