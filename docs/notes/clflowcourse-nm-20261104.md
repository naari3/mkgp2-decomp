# clFlowCourse (cxb_b1, 2026-11-04) — honest NonMatching drafts

Source: Codex worker cxb_b1_flowcourse_20261104 (gpt-6.1-sol/medium) + coordinator acceptance. 0 native functions.

- 4-fn reversed-extab group (Dtor D0C30 99.62% exact size, Init D0EE0 96.56% 1864B vs 1852B, fn_801D161C 104B switch 100% text but must stay in the NM group TU, fn_801D1684 97.89% exact size) kept as one NonMatching TU (clFlowCourse.cpp). Residuals: register identities in `selected % 2` / reverse-offset computation (Dtor); constructor init model (ordinary virtual-owner model best of 3: inline prepared base 95.80%, preview init wrapper 96.24%); alpha composition (1684).
- Update CF360 81.70% (6048B vs 6352B, first full state-machine draft with real C++ new guards) in clFlowCourse_Update.cpp.
- Next attempt needs new evidence (pooled data-base reconstruction for Init, Update structure), not register permutation.

## c3_u20_flowcourse_20261105
Source: Codex worker c3_u20_flowcourse_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c3_u20: separate Update states 98/99 (target has duplicate scroll and arrow bodies) improves 81.70 -> 89.64%. Retain CourseUpdateData pointer across calls and read arrow X/Y before storing -> 93.16%. Inline SetSpritePosition avoids alias-induced owner reloads; word unsigned Test return, explicit state branches and cached banner/pulse pointers -> 95.6291% (6328 vs target 6352). EH 95.83333%, index 91.66667%; alpha registers, array-subobject base materialization, pulse branches, remote icon webs remain. Init retained CourseData pointer/mapIds pointer and same setter -> 98.0432% (1860 vs1852), EH91.31579%. Explicit vptr rewrite leaves redundant store and was rejected. Dtor declaration ordering no-op, ternary worsens; fader alpha-first declaration no-op, mask/or worsens. All restored. Four-function EH reversal prevents B; both remain NM.
