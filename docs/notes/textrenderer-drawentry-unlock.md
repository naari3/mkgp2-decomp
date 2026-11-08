# textrenderer-drawentry-unlock

Source: Codex worker c19_u159_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 28 fn / 2992 B.

c19 retry: cache unsigned int cellHeight then cellWidth locals in glyph block, compute cellWidth first, reuse these values in geometry and s/t endpoints. Text 98.70192->98.84615 with exact832B/EH8/index12, fixes four scratch-register rows (50->46). Redundant texS/texT aliases unnecessary and removed. All-sites font/scale inline accessors and texture-binding-only inline extraction both byte-invariant. No singleton or base-register pool accesses. Saved loop/context partition still wrong; single function prevents B. Retained clean cached dimension draft.

## c21_u103_20261108
Source: Codex worker c21_u103_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 832 B.

c21_u103: current main ac376730 already inherits bc31b3a6 natural declaration/statement-order match, despite stale assignment 98.85%. Fresh production compile verifies text832/EH8/index12 all100. Flip only configure Object to Matching; coordinator service req2 exit0 DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. main.elf edge uses src object, no fallback; linked game files2479->2480. Native +1fn/+832B; no source/split/data/header/bridge changes.
