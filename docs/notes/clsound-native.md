# clsound-native

Source: Codex worker c7_s24_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 488 B.

ClSound_PlayBgmStream 0x80190B3C (488 B): native C matches GC/1.3.2 with exceptions and use_lmw_stmw on. Inline unsigned-char StopBgm(id, resources) reproduces the redundant initialization check; declare local const ClBgmFiles* files and assign resources+0x3D1C before files[id].right. Repeated casts to table[id] fold 0x3D20 into the load (97.28689%); named files pointer matches 100%. Full source-linked DOL SHA-1 verified. Spatial functions 801913B0/80192F04 remain at 95.03597%/97.39286%; explicit listener base keeps r30 but adds a move and generates mr at offset-zero rather than target addi 0.

## c10_u22_20261106
Source: Codex worker c10_u22_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u22: fn_80190D24 fresh C compile 96.70644%/1660 B (assignment report 97.62%). Inline adjacent-entry SwapQueued(index), with local a/b pointers and a struct tmp, restores 1676 B and exact extab/index, reaches 98.324585%. Named gain/level/setting floats improve to 98.40811%, gain f0 and final multiply operand order exact. Queue GPR homes and predecessor copy scheduling plus FP bias/intermediate product homes remain. C++ struct copy trial reaches weighted 98.81384% but drops three tmp stack stores, shrinks frame 0x50->0x40 and text to 1664 B; rejected. Kept NonMatching; fallback full DOL SHA-1 OK; no native gain.

## c14_u49_20261106
Source: Codex worker c14_u49_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u49: ClSound_InitSoundSystem prebuilt objdiff baseline 91.298134% (assignment report 91.78%). Removing LoadSoundFile pathname local and recomputing strings+offset removes a call-crossing register and restores target 0x120 frame/r26-r31 saves, 94.26087% text and exact extab. Typed ResetEvents/PrepareEffects/ResetStreams inline boundaries give 94.29192%, but subobject addresses still fold. Byte-array workspace and signed length delta yield identical residual and were discarded. Retained typed C NonMatching, 1912 vs target 1932 bytes; bases r30/r31 swapped, file-end add/sub association, subobject address materialization, ARInit result shuffle remain. Single function prevents rescue B. Full fallback DOL SHA-1 OK.
