# collision-file-fixup-native

Source: Codex worker c15_a3_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 72 B.

c15_a3_20261106: CollisionFile_FixupPointers 0x80035220 (72 bytes) promoted from asm to natural C under unchanged GC/1.3.2 flags. Preserve second_offset = offset + 8 and advance offset += 0x10 before reloading the table and fixing its second field. This gives loop offset r5 and saved second offset r6, resolving the prior swapped pair. Assign the loop-test load to unsigned first and reuse first + file_base for the first-field store to avoid an extra body lwzx. Exact .text 100%, no owned EH/data sections, coordinator full source-linked DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Prior history: 003cc69 parked six C variants with r5/r6 swapped.
