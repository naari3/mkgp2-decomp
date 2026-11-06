# cardtask-printjob-state-vector

Source: Codex worker c15_a2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 48 B.

CardTaskPrintJob_InitStateVector (0x8008F5A4, 48 B): plain C aggregate assignment of a three-word callback followed by two zero fields matches GC/1.3.2 exactly on first attempt. Existing source history consists only of 0268420 (game: match CardTask state vector init), which introduced the asm directly; no prior C attempt or parking rationale was found in that history or targeted docs/notes search. Native gain 1 fn / 48 B. Full coordinator build service SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.
