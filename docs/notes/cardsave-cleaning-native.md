# cardsave-cleaning-native

Source: Codex worker c15_a33_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 740 B.

CardSave_Tick_PollCleaningResult history has only its original extraction commit 135e4e5 (game: complete card and BiribiriLand units), with no recorded C attempt or specific parking blocker. Target-specific docs/notes search found no prior note. Existing include/game/Sci2CardReceipt.h contains exact Sci2Card_SetFailCode inline. Reusing it and pragma exceptions on/reset yields exact text and EH; outer status local declarations status3/status2/status1 produce stack offsets 0xB/0xC/0xD for call arguments status1/status2/status3, while helper locals occupy 0x8/0x9/0xA. Existing configure extab_padding recipe can remain unchanged.
