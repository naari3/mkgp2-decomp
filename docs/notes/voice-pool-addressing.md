# voice-pool-addressing

Source: Codex worker c7_oc_801a6538_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Voice module TU (0x801A....) used MWCC data pooling: .data tables addressed as lbl_80496C38+off and local array initialisers as lbl_803810A8+0x2C18.. (r30/r31 loaded at function entry). Extern struct + local base pointers reproduce the entry hoist and most code; members that the original treated as separate pooled globals (g_voicePlayCountTable at +0x1534, goal lines at +0xF8C) still fold differently. Local `short list[N] = {...}` inside a loop leaves a hoisted dead temp copy plus an in-loop copy; reproduced with a declared outer copy plus per-iteration struct assignment, with declaration order controlling stack slots. (u16)(v - 0x26A) <= 1 reproduces subi/clrlwi 16/cmplwi range check.

## c10_u2_20261106
Source: Codex worker c10_u2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u2: fn_801A6538 literal 1000.0f divisor removes undesired saved f31 and makes simple owned extab exact. Final time guard must be !(elapsed >= 12 threshold) to retain target cror/bne unordered semantics; previous < form omitted cror. Fresh baseline 97.25574%, retained 97.65049% (6096 vs 6100 B), index section 91.66667%. Inline clip/goal accessors do not preserve pooled subtable bases (97.65705%, discarded); open-coded spin loop worsens to 97.530495% (discarded). TU stays NonMatching, source_input false; full coordinator DOL SHA-1 passes.
