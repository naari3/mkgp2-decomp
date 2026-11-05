# voice-pool-addressing

Source: Codex worker c7_oc_801a6538_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Voice module TU (0x801A....) used MWCC data pooling: .data tables addressed as lbl_80496C38+off and local array initialisers as lbl_803810A8+0x2C18.. (r30/r31 loaded at function entry). Extern struct + local base pointers reproduce the entry hoist and most code; members that the original treated as separate pooled globals (g_voicePlayCountTable at +0x1534, goal lines at +0xF8C) still fold differently. Local `short list[N] = {...}` inside a loop leaves a hoisted dead temp copy plus an in-loop copy; reproduced with a declared outer copy plus per-iteration struct assignment, with declaration order controlling stack slots. (u16)(v - 0x26A) <= 1 reproduces subi/clrlwi 16/cmplwi range check.
