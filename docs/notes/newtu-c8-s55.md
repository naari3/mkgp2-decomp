# newtu-c8-s55

Source: Codex worker c8_s55_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_801F52A8 has a compiler-generated 16-entry switch table at 0x804E545C..0x804E549C. A correct pointer-return signature for fn_801F98CC yields direct calls and exact text size/EH/table. Current canonical MenuModeLane_private.h discards the getter return; no shared edit was made. Register-only item-selection residual persists after local declaration and inline-helper variants. fn_801F27B4 copies two 0xA8-byte member-method table defaults at lbl_804E4C28 offsets 0x380->0x428 and 0x4D0->0x578; target .ctors registration is at 0x802E8930.

## c16_u137_20261106
Source: Codex worker c16_u137_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1980 B.

c16_u137: fn_801F52A8 unlocked 99.62626 -> 100% by changing unsigned int backward to bool in cases 13,14,15. Relational result type changes player/direction and down/held/constant register partitions to target. Text1980/data64/extab8/index12 all exact. TU requires existing DATA_ALIGN4_TUS entry game/fn_801F52A8 when promoted: without it full native link grows DOL .data 0x20; with alignment rescue source-linked DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.

## c17_u11_20261107
Source: Codex worker c17_u11_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1016 B.

c17_u11: DebugOverlay_RaceConfig 801F4EB0/1016B fresh objdiff58.8937 ->100 by defining its original shared .rodata803BE6C0..803BED88 and .data804E53B0..804E5430 as genuine float/string/pointer arrays. External pool arithmetic and typed foreign aggregate views rematerialize addresses; visible definitions let GC/1.3.2 hold rodata=r31, data=r30, self=r29 and item result=r28, reproducing every instruction. Export C++ const labels explicitly for fallback consumers. Real string sizes plus implicit four-byte alignment suffice; no filler or DATA_ALIGN4 entry. Text/EH8/index12/rodata1736/data128 all100; source ELF801F4EB0 size1016 and pool endpoints checked; full native DOL SHA-1 exact. +1 native function/1016B.
