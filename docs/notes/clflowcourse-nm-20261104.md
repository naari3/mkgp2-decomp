# clFlowCourse (cxb_b1, 2026-11-04) — honest NonMatching drafts

Source: Codex worker cxb_b1_flowcourse_20261104 (gpt-6.1-sol/medium) + coordinator acceptance. 0 native functions.

- 4-fn reversed-extab group (Dtor D0C30 99.62% exact size, Init D0EE0 96.56% 1864B vs 1852B, fn_801D161C 104B switch 100% text but must stay in the NM group TU, fn_801D1684 97.89% exact size) kept as one NonMatching TU (clFlowCourse.cpp). Residuals: register identities in `selected % 2` / reverse-offset computation (Dtor); constructor init model (ordinary virtual-owner model best of 3: inline prepared base 95.80%, preview init wrapper 96.24%); alpha composition (1684).
- Update CF360 81.70% (6048B vs 6352B, first full state-machine draft with real C++ new guards) in clFlowCourse_Update.cpp.
- Next attempt needs new evidence (pooled data-base reconstruction for Init, Update structure), not register permutation.

## c3_u20_flowcourse_20261105
Source: Codex worker c3_u20_flowcourse_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c3_u20: separate Update states 98/99 (target has duplicate scroll and arrow bodies) improves 81.70 -> 89.64%. Retain CourseUpdateData pointer across calls and read arrow X/Y before storing -> 93.16%. Inline SetSpritePosition avoids alias-induced owner reloads; word unsigned Test return, explicit state branches and cached banner/pulse pointers -> 95.6291% (6328 vs target 6352). EH 95.83333%, index 91.66667%; alpha registers, array-subobject base materialization, pulse branches, remote icon webs remain. Init retained CourseData pointer/mapIds pointer and same setter -> 98.0432% (1860 vs1852), EH91.31579%. Explicit vptr rewrite leaves redundant store and was rejected. Dtor declaration ordering no-op, ternary worsens; fader alpha-first declaration no-op, mask/or worsens. All restored. Four-function EH reversal prevents B; both remain NM.

## c18_u117_20261107
Source: Codex worker c18_u117_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u117: Update 95.6291 -> 99.25315, exact 6352B; EH72/index12/rodata1452 all100. Define the original pool as separate file-static tables rather than a CourseUpdateData aggregate: MWCC then emits the target base+0x42C arrow, base+0x41C animation and base+0x3FC icon accesses. Recover rodata8039B990..8039BF3C; globalize/bridge motionCurves -> clFlowCourse_Update_rodata_8039B990 and add local table symbols. Split checked/unchecked pulse helpers to avoid duplicate null guards. PulseAlpha inline with two direct returns preserves target branch polarity, separate conversion slots and common final store. Arrow Y-before-X declaration fixes repeated FPR pairs. Position-by-value and union RGBA byte setter spill; countdown early-return helper is invariant; direct icon writes worsen alias reloads. Remaining countdown branch/color/interpolation/remote-icon register residuals block singleton TU; no B subset and no native gain. Full fallback DOL SHA-1 OK.

## c18_u55_20261107
Source: Codex worker c18_u55_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u55: no native gain; canonical SINGLETON_INSTANCE preserves all scores. Dtor inline remainder/offset helper invariant 99.62209, offset-only helper 96.15116, commuted sum 99.593025. Fader common helper and packed-before-shade invariant 97.89474; union-channel write 92.10526. Init preview helper 97.166306; mixed zero literals improve float load order but cannot be retained because postprocess_sdata2 maps anonymous zero to lbl_806D9F50 (215.0f) when primary instruction offsets differ. Its implementation currently selects by relocation offset without the byte-value sanity check described in its docstring. No tools changes made. Pool 8049B1E0..8049B3C8 and current TU jump tables B448..B4A8 cannot form a single contiguous owned range because intervening other-TU tables are already split. Reversed EH group still prevents B.

## c19_u2_20261107
Source: Codex worker c19_u2_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u2: Update99.25315->99.61587, exact6352B and owned EH72/index12/rodata1452/data64 all100. Correct lbl806D184C/D signed-byte declarations; carry field20 snapshot past one-case switch. Switch emits target beq+b rather than if bne and fixes jump-table data. Initialize remote opacity before Show, pass same value as z and reuse for alpha: removes extra fmr and restores exact size/index. Declare remote opacity before x to fix f3/f4 pair. Scope/declaration changes do not move remote i/walker, round/extra or interpolation scratch GPRs. Unsigned-byte packing wrapper invariant; scalar packed-color class mask/or expands rlwimi to three ops, rejected. Remaining62 arg rows and one load scheduling pair. Six hypotheses exhausted; honest singleton NonMatching, zero native gain. Full fallback DOL SHA1 exact.

## c19_u30_20261107
Source: Codex worker c19_u30_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 1848 B.

c19_u30: fader fn801D1684 improves97.89474->98.210526, exact380B, by extracting signed alpha conversions into separate FadeAlpha(timer)/FadeOutAlpha(timer) value-returning inline helpers. Alpha result home becomes target r4. Remaining34 arg rows: packed colorr0 vs targetr5, shader5 vs targetr0, conversion xoris/storer4 vs targetr0. Added shade helper and parameterized packed-color application invariant; reverted. Dtor remainder-only helper, ApplyRoundOffset after remainder, unsigned offset all invariant99.62209. Init map-base-before-selection and external-zero getter invariant98.0432/1860B. All other funcs/section scores/sizes unchanged; retained alpha helpers only. No legal contiguous pool claim (other TUs between B3C8 and B448); reversed four-function EH blocks B. WholeTU honestNM, no nativegain; full coordinator fallback DOL SHA1ea30f3b1 exact.

## c20_u1_20261108
Source: Codex worker c20_u1_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u1: Update99.61587->99.67255,6352B; EH72/index12/rodata1452/data64 all100. Extract entire remote-icon for loop to static inline UpdateRemoteIcons(CourseFlow*): recovers target i=r29/walker=r28 (prior direct-loop scope/declaration probes could not). In new helper declare x before opacity a to recover exact f4/f3; opposite order yields99.6442. Remaining48 arg rows plus selection-load scheduling pair: alpha packing, round/reverse and interpolation scratch homes, role-cmp operands and remote layout/pool temporaries. Nested ShowRemoteIcon helper and verified255.0f literal invariant. By-value single-word color wrapper spills/frame60; masked alpha expands rlwimi as prior c19. Six hypotheses exhausted; singleton stays NM, zero native gain. Full fallback DOL SHA1 exact.

## c21_u26_20261108
Source: Codex worker c21_u26_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u26: natural fader100 by unsigned int alpha=FadeAlpha/FadeOutAlpha(timer), retaining signed float-to-int helper conversion; removes inherited opt_common_subs off. Byte alpha regresses94.21; common setter remains99.1579. Init fresh98.0432->98.302376 with 0.0f in final map/field12C/Pulse arguments and1.0f Pulse scales. Explicit own aliases @228->extern:lbl806D9EE0,@229->extern:lbl806D9EDC bypass known unsafe offset-based literal mapping; verify raw anonymous IDs after future edits (bytes00000000/3F800000). Remaining Init target1852/source1860 is pool/vptr anchor and map selection/index GPRs, no FPR residual. Dtor invariant99.62209. Four-function reversal blocks B; neighbouring pool owners outside claim block A merge. Full fallback DOL SHA1ea30f3b1 exact; zero native gain.

## c21_p12_20261108
Source: Codex worker c21_p12_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p12: clFlowCourse_Update 99.782745 -> 99.90869%, exact 6352B, all owned non-text sections 100%. In state 1, spell InputState *input = CourseInput(); self->selection += input->dir; rather than self->selection += CourseInput()->dir;. This keeps the selection lwz after the second defensive singleton getter branch and removes the sole scheduling pair. Remaining 20 rows are GPR arguments in round/reverse, interpolation conversion/index, and remote role/layout/icon addressing. Unsigned round+offset locals, complete round helper, signed-long remote role, and selective reverse-offset helper invariant. Ternary offset generates branchless code and regresses. Existing pooled rodata ownership is already fully recovered; no new ownership work or B split applies. Full fallback coordinator DOL SHA-1 exact; zero native gain.

## c22_u1_20261109
Source: Codex worker c22_u1_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u1: Update99.90869->99.914986%,6352B; all owned non-text sections100. TU-private CourseRecvSlot models observed byte0 flags and byte5 courseFlags; typed PcbSlot_GetByIndex return plus HasRole(int) const/Selection() const fixes target cmpw r0,r27 at801D0B18 (previous r27,r0). Retained. Reversing equality operands, signed-long round/offset, inline parameter round accumulator and full interpolation helper are invariant. Time-only interpolation helper swaps FPRs and regresses99.880356. Pool8039B990..8039BF3C already owned and defined in target order, no ownership changes. Remaining19 GPR operand rows: round/reverse, interpolation r4/r5 conversion/index, remote layout r6/r3 and icon-offset r7/r6. Six hypotheses exhausted; singleton NonMatching, no B subset/native gain. Full coordinator fallback DOL SHA1ea30f3b1 exact.

## c23_u20_20261109
Source: Codex worker c23_u20_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u20: Update stays99.914986/6352B, all owned nontext100. Pool already owned/defined; one function means no B subset. Seven compiled variants in six families: signed-long remainder expression invariant; interpolation computed-argument helper invariant; actual SetCourseParams return int corrected (retained, emitted instructions identical); CourseLayout coordinate members99.90869 (extra FPR swap), reference-return lookup invariant; native CourseFlow::Update member+bridge invariant (all experimental header/bridge edits restored); reverse-offset accumulator99.91184, sum/store destination moves to r5 but input cycle stays. Remaining19 operand rows unchanged. No full build requested, existing coordinator baseline hash checked. No native gain.

## c25_u2_20261110
Source: Codex worker c25_u2_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u2: merged TU pool audit already resolved; all nine definitions present. PulseAlpha first branch reads extern const float lbl_806D9F30, fade-out retains literal0.125f: direct Update99.85201->99.874054; report final99.892944, size6352 unchanged. Removes five FPR rows +1688..169C, all other symbol/section scores unchanged. Both extern branches fix ten FPR rows (99.896095) but shift anonymous IDs and lower Init; kept only build/w/c25/attempt3_pulse_extern.cpp. Layout address before timer conversion invariant; nested layout accessor leaves remote regs invariant, shifts labels; distributed round conditional produces mr/addi and regresses Dtor97.52907. No safe B partition established due pooled-data ownership and reversed tail EH. Full coordinator build exit0 SHA1ea30f3b1 OK. No native gain.
