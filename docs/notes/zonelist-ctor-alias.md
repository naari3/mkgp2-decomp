# zonelist-ctor-alias

Source: Codex worker c7_oe_asm2c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 820 B.

BoxZone/QuadZone ctors (0x80123674 / 0x801238EC): the target schedules src float loads across stores to this (no-alias behaviour). CW 1.3.2 in C++ mode only reorders when both pointers are __restrict; a restrict src alone, a const& param, a mem-init list, a base ctor taking src, and #pragma opt_pointer_analysis do not change it. QuadZone natural C is 91.1%, with everything except this ordering matching. Tick (clMiyoshiCardCreate): if/ternary tails get `li r3,-2` hoisted; only a switch avoids the hoist.
