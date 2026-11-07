# GameTestTopMenu_Page-native

Source: Codex worker c17_u71_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 648 B.

GameTestTopMenu_Page 80073878/648B becomes exact with canonical TestPage_DrawItems for cabinet-2 and a separate indexed inline DrawStandardItems helper for the standard table. Original shared explicit pointer walker emitted extra mr r28,r0. Cabinet-only helper fixes that path but perturbs standard-loop homes. Extracting both variants removes extra instruction; compute standard selection inside its helper and declare int i before int selected to resolve the remaining r30/r31 swap. Reuse canonical TestMenuPage.h MenuItem/InputPlayer::Pressed. Text648/extab8/index12 all100; existing Cpp_exceptions on suffices, no bridge/split/data changes. Matching source edge, ELF80073878 size648, full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified.
