# frame-update-native

Source: Codex worker c19_u244_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u244: FrameUpdate baseline92.93378/600B has a verified missing second argument: fn_80288210 consumes r4 as working-backup pointer, but compiled baseline leaves accel calibration in r4. Retain corrected fn_80288210(0,&lbl_80598A60) plus typed calibration-capture helper; final92.27152/604B, extab100/index100, NonMatching. This intentional text fuzzy decrease repairs call semantics. Canonical BackupShadowCopy with GC1.3.2 gives83.57616 (same as prior c16 despite compiler-family change); pointer-parameter copy helper byte-invariant. Main residual remains pre-call retained r31/r14 versus target fresh r16; no further declaration permutations attempted. Original best fuzzy source and all probes saved build/w. No A/B unlock; final fallback-linked DOL SHA exact.
