# jump-distance-update-retrofit

Source: Codex worker c11_a17_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c11_a17: inline camera and timer helpers improved native candidate 92.36429 -> 98.28571%. Final candidate has exact automatic 8-byte owned extab but text is 1664 vs target 1680. Camera stack locals and FP scheduling remain. At 0x80212348 global transition pointer is loaded, then cmplwi/bne/li 0 before Tick at 0x80212358. A no-op null test would reproduce that redundant target sequence but is forbidden by retrofit contract; no such test was introduced. Original assembly retained exactly; draft disabled in same TU.
