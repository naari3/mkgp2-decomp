# itemalias-native-retrofit

Source: Codex worker c15_a14_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 184 B.

ItemAlias_HitRemapLookup 800D7540 (184 B): old 3ada6b3 asm park was attributed to displacement CSE. A static inline index finder written as for(i=0;i<155;i++) if(id==g_itemAliasTable[i][1]) return i; return 0; reproduces the target five-way unroll and +0x10 loads with inline pointer increments. This mirrors the now-native ItemAliasTable_LookupSlotIndex. Compose it with a generic bounds-checked source-at-index helper (upper bound 155, zero on out-of-range). Explicit pointer walking in the finder gives identical size but swapped r4/r5 webs and final increment scheduling (94.565216%). Array indexing yields 100% for all 360 TU text bytes. Full coordinator link/DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No configuration, symbols, split, shared header, data, or EH changes.
