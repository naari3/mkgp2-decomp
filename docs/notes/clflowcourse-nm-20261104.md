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

c18_u117: Update 95.6291 -> 99.25315, exact 6352B; EH72/index12/rodata1452 all100. Define the original pool as separate file-static tables rather than a CourseUpdateData aggregate: MWCC then emits the target base+0x42C arrow, base+0x41C animation and base+0x3FC icon accesses. Recover rodata8039B990..8039BF3C; globalize/bridge motionCurves -> lbl_8039B990 and add local table symbols. Split checked/unchecked pulse helpers to avoid duplicate null guards. PulseAlpha inline with two direct returns preserves target branch polarity, separate conversion slots and common final store. Arrow Y-before-X declaration fixes repeated FPR pairs. Position-by-value and union RGBA byte setter spill; countdown early-return helper is invariant; direct icon writes worsen alias reloads. Remaining countdown branch/color/interpolation/remote-icon register residuals block singleton TU; no B subset and no native gain. Full fallback DOL SHA-1 OK.

## c18_u55_20261107
Source: Codex worker c18_u55_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u55: no native gain; canonical SINGLETON_INSTANCE preserves all scores. Dtor inline remainder/offset helper invariant 99.62209, offset-only helper 96.15116, commuted sum 99.593025. Fader common helper and packed-before-shade invariant 97.89474; union-channel write 92.10526. Init preview helper 97.166306; mixed zero literals improve float load order but cannot be retained because postprocess_sdata2 maps anonymous zero to lbl_806D9F50 (215.0f) when primary instruction offsets differ. Its implementation currently selects by relocation offset without the byte-value sanity check described in its docstring. No tools changes made. Pool 8049B1E0..8049B3C8 and current TU jump tables B448..B4A8 cannot form a single contiguous owned range because intervening other-TU tables are already split. Reversed EH group still prevents B.

## c19_u2_20261107
Source: Codex worker c19_u2_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u2: Update99.25315->99.61587, exact6352B and owned EH72/index12/rodata1452/data64 all100. Correct lbl806D184C/D signed-byte declarations; carry field20 snapshot past one-case switch. Switch emits target beq+b rather than if bne and fixes jump-table data. Initialize remote opacity before Show, pass same value as z and reuse for alpha: removes extra fmr and restores exact size/index. Declare remote opacity before x to fix f3/f4 pair. Scope/declaration changes do not move remote i/walker, round/extra or interpolation scratch GPRs. Unsigned-byte packing wrapper invariant; scalar packed-color class mask/or expands rlwimi to three ops, rejected. Remaining62 arg rows and one load scheduling pair. Six hypotheses exhausted; honest singleton NonMatching, zero native gain. Full fallback DOL SHA1 exact.

## c19_u30_20261107
Source: Codex worker c19_u30_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 1848 B.

c19_u30: fader fn801D1684 improves97.89474->98.210526, exact380B, by extracting signed alpha conversions into separate FadeAlpha(timer)/FadeOutAlpha(timer) value-returning inline helpers. Alpha result home becomes target r4. Remaining34 arg rows: packed colorr0 vs targetr5, shader5 vs targetr0, conversion xoris/storer4 vs targetr0. Added shade helper and parameterized packed-color application invariant; reverted. Dtor remainder-only helper, ApplyRoundOffset after remainder, unsigned offset all invariant99.62209. Init map-base-before-selection and external-zero getter invariant98.0432/1860B. All other funcs/section scores/sizes unchanged; retained alpha helpers only. No legal contiguous pool claim (other TUs between B3C8 and B448); reversed four-function EH blocks B. WholeTU honestNM, no nativegain; full coordinator fallback DOL SHA1ea30f3b1 exact.
