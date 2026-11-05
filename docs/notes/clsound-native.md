# clsound-native

Source: Codex worker c7_s24_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 488 B.

ClSound_PlayBgmStream 0x80190B3C (488 B): native C matches GC/1.3.2 with exceptions and use_lmw_stmw on. Inline unsigned-char StopBgm(id, resources) reproduces the redundant initialization check; declare local const ClBgmFiles* files and assign resources+0x3D1C before files[id].right. Repeated casts to table[id] fold 0x3D20 into the load (97.28689%); named files pointer matches 100%. Full source-linked DOL SHA-1 verified. Spatial functions 801913B0/80192F04 remain at 95.03597%/97.39286%; explicit listener base keeps r30 but adds a move and generates mr at offset-zero rather than target addi 0.
