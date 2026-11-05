# newtu-c7-s7

Source: Codex worker c7_s7_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1096 B.

TCPListen_Poll has state 8 -> close then state 9, state 0 -> return 0. Holding acSocket return in a local and comparing the local reproduces compare-before-store and separate field reloads. Native C matches 1096 text bytes and all EH/data. AssocTree_FreeAll has 4 expanded traversal levels with depth-dependent allocator inlining; explicit C expansion matches structure but tree/node homes r30/r31 are reversed (99.02892%). Large inline helper approach was not inlined and did not improve the residue.
