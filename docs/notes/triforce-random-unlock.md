# triforce-random-unlock

Source: Codex worker c16_u41_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 8 B.

c16_u41: GC/1.2.5n original nonvolatile seed already emits target reload pattern; volatile adds two extra loads per generator. Swapping multiply/add operands leaves baseline assembly unchanged. Explicit u64 random intermediate changes frame and product registers (fn B8 56.86%, fn 864 88.29%); reverted because another function regressed. Mechanism B isolates setter as native 8B; generators remain original percentages. Target seed split 806D0C18..806D0C20 includes 4 zero bytes at 806D0C1C..20 beyond emitted u32. Likely trailing alignment, not established second semantic field; no padding object added. Data stays in NonMatching TU.

## c17_u4_20261107
Source: Codex worker c17_u4_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u4: GC/1.2.5n production command, -O4,p -inline noauto. Both assigned functions present. Named u64 product followed by product >>= 32 and result + min fixes fn_802867B8 final add operand order: 88.25581 -> 88.48837; fn_80286864 unchanged 84.80769. Next-first u64 accumulator improves second to 88.28846 but first drops 68.023254 and frame sizes diverge; reject. Next returning u64 increases both frames by 8 and regresses both. Unsigned local flag does not merge separate zero with ret. Remaining differences are GPR allocation and adde/li scheduling around 64-bit arithmetic. Seed .sdata target8/source4 gap at 806D0C1C remains, no filler. No native gain; full fallback-linked SHA-1 OK.
