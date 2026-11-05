# auto_800A8F4C_block

Source: Codex worker c9_oo_asm2c_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 564 B.

auto_800A8F4C_block is C++-origin (WarpZone ctor with Vec edge[4]). Remaining asm bodies need C++ semantics: local Vec objects kept in memory with frsp-forwarded loads (Find*/CheckEntry/CalcExitPosition), ctor-specific loop addressing (CalcEdgeVectors), new/delete EH actions (GetOrCreate/Cleanup). In C only an alias pointer local reproduces the kept-in-memory Vec (rejected). Converting manual .extab_user entries to CW auto-emission works with an add-only tools/extab_order.json key (extab keeps declared order; extabindex address order).
