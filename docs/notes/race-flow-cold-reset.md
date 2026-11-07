# race-flow-cold-reset

Source: Codex worker c19_u234_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u234: byte-addressed pool base plus bank=base+0x20000 retains bank r30 across initial memset/fn_801D7610 calls, improving 89.97151 to 90.0 (source 1380 ->1372 B, target1404). Target score loop writes eight words from805D2938 and overlaps first entry at805D2948; old four-element struct array is indexed out of bounds. Union overlay alone is byte-invariant. Integer-address pool is invariant to byte-pointer pool. Independent entry/rank bases and cup/round reloads still absent; shared BSS already belongs to SetCourseParams.c, so no ownership transfer attempted. Keep NM, no native gain.
