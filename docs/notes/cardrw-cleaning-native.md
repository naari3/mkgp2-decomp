# cardrw-cleaning-native

Source: Codex worker c15_a46_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1032 B.

CardRW_CleaningTest_Page 0x8006F200..0x8006F608 converts naturally with #pragma cplusplus on, #pragma use_lmw_stmw on, canonical TestMenuPage.h InputPlayer/MenuItem declarations, and a private CleaningPage layout. Existing flags already enable C++ exceptions. Remove manual extab/index and let MWCC emit them. Response locals declared c,b,a produce address setup &a=r1+8, &b=r1+9, &c=r1+10 in the target order; an array places bytes correctly but schedules pointer setup r5,r6,r4. Inline item loop reproduces r27 table, r28 selection, r30 index. History contains only original all-asm extraction commit 2d1f38a5 and no documented native-C blocker; targeted docs/notes search found no CleaningTest note. Full coordinator build service request 1 verified the expected DOL SHA-1.
