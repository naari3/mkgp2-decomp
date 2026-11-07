# textrenderer-drawentry-unlock

Source: Codex worker c19_u159_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 28 fn / 2992 B.

c19 retry: cache unsigned int cellHeight then cellWidth locals in glyph block, compute cellWidth first, reuse these values in geometry and s/t endpoints. Text 98.70192->98.84615 with exact832B/EH8/index12, fixes four scratch-register rows (50->46). Redundant texS/texT aliases unnecessary and removed. All-sites font/scale inline accessors and texture-binding-only inline extraction both byte-invariant. No singleton or base-register pool accesses. Saved loop/context partition still wrong; single function prevents B. Retained clean cached dimension draft.
