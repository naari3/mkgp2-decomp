# sprite-voice-native

Source: Codex worker cxc_u15_a1714_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 5128 B.

All four extab entries are simple 8-byte records with no actions. Hoist voice table pointers into inline selector locals and use flat character + id*13 indexing to reproduce target scheduling. VoiceQueue_Push return declaration must be unsigned char to avoid clrlwi after calls and obtain the target OSTime register pair. Default objdiff penalizes adjacent low-word symbols versus high-word+4 even when all ELF bytes and resolved relocation addresses are identical. See worker evidence and full-build SHA-1 before accepting.
