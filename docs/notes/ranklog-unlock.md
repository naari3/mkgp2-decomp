# ranklog-unlock

Source: Codex worker c3_u6_ranklog_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RankLog is a single indivisible reversed-EH group (DTK cut at 800A8208 rejected). Correct format extern sizes 5 and 7 restore SDA21. PackedWords requires byte packing for target words 1BA/1BE/1C2/1C6/1CA/1CE. Real C++ synthesized PlayerData assignment remains out of line at default flags; memberwise native C copy improves InitStartRace substantially but register-pressure scheduling remains. No ASM/manual EH/padding used.
