# docs/wip: near-miss drafts and working notes

Best attempts and investigation notes for functions that are not matched yet
(or were matched later). Moved here on 2026-11-09 from the Claude project's
shared folder (`/mnt/project-files/wip`, `notes`, `r1-drafts`), where only
naari3's Claude threads could see them. `docs/gave_up.md`, `docs/reports/*` and
`docs/thread_tips.md` point at these files.

Nothing here is built: these are whole-TU drafts (`.c`/`.cpp`), patches/diffs
against main of the day they were written (`.patch`/`.diff`, may need a 3-way
apply), or notes (`.md`/`.txt`). File names usually carry the best score
(`_99.71`, `_3lines`, `_1insn` = diff lines left).

Layout:

- top level and `<topic>/`: drafts from rounds 2-3 (asm->C, TU merges, takeover leftovers).
  `asm-a/` = asm->C thread A, `r2/` = R2 range thread, `onmoko_pragma_hints/` and
  `onkarthit_ap*/` = 2026-11-08 takeover leftovers, `clsound_merge/` = clsound TU merge WIP.
- `notes/`: older per-range notes and drafts (`r1/`, `r4/`, `r4_wip/`, `shard1-3/` permuter
  shards, `gaveup-retry/`, `fn_8019EB9C/` regalloc study with its search scripts,
  `leftover_survey.md`, `nonmatching_r1-3.md`, `onmoko_takeover_20261108.txt`,
  `card/` magnetic card format research + `mkgp2card.py` tool).
- `r1-drafts/`: round-1 drafts.
- `setup/`: `Gecko_ExceptionPPC.wip.cpp` (runtime EH draft), `probe.s`.

Add new drafts here (not in the shared folder), in a topic subdirectory, and
mention them in `docs/gave_up.md` when you park a function.
