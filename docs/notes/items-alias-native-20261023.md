
## Items alias ownership (claim #180, 2026-10-23)

Actual target groups each contain one owned function. 0x803159B8 is 60 integer slot IDs; 0x80315AA8 has size 0x4E0, exactly 104 rows {source,ownedIndex,result}; 0x803FED28 is six character-indexed pointers. Items +0xB4 contains 60 owned-slot bytes and +0xF0 the alias ownership bytes. Player character is signed byte g_playerData+0x1B8. No global data was recreated. The simple 104-row loop naturally compiles to target four-way unroll (CTR 26), including the unusual unused counter increment 3; no handwritten unroll needed.

Trial 1 shared Resolve inline helper: 97.71579% / 97.757065%, extra merged early-return and register differences. Trial 2 direct exported Resolve body plus inline clone, pointer-before-counter increment, signed alias flags: 97.26316% / 98.418076%. Trial 3 declarations row/item/index: 98.89474% / 99.37853%, solves principal volatile register identity. First source 0x180 vs target 0x17C retains extra row-base -> walker mr (coalescer class); second source 0x2C0 vs target 0x2C4 folds repeated signed-byte extension. Three-trial bound reached: do not repeat declaration permutations or same flags without new structural evidence.

Native C++ and automatic EH only. EH bytes 4008000000000000 exact; index 91.66667 from 0x2C0 vs 0x2C4. No data sections owned. Both remain NonMatching and main.elf links build/GNLJ82/obj/game/Items.o fallback. Full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 after final all_source/progress/report/ok actual exit 0; genuine gain zero.
