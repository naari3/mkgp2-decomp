# namecheck-scanbanned-native

Source: Codex worker c14_u14_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u14: NameCheck_ScanBannedWords 80099CE4 singleton remains NonMatching. Measured baseline94.1674 ->95.0458 using explicit enclosing found/j symbol-membership loops at three sites instead of value-argument contains. Global flag-return helper worsens93.50; pointer-argument contains_at restores target load placement but scores93.90676 due result copies. Retained text7316 vs target7336, EH8 exact/index12 91.66667 due length. First group/extraction helper registers, wcscpy pool base lifetime, first strstr compare/move, at_boundary pointer/count copies and split-run initialization remain. Three approaches exhausted. Full fallback-linked DOL SHA-1 verified; no native gain.

## c19_u12_20261107
Source: Codex worker c19_u12_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 176 B.

c19_u12: measured95.0458 ->95.400215 retained by introducing local cursor in extract_one/extract_two, keeping input position parameter unchanged. This resolves all extraction-local volatile register homes: target region+90..374 now differs only in 11 loads using enclosing sets r25 vs r29. Reordered extractor formal parameters is byte invariant95.0458. Explicit delimiter pointer walker + target-role local declaration order on improved draft regresses95.19847, discarded. Native size remains7316 vs7336, EH100/index91.66667. No pool ranges taken, singleton getter not present. One function precludes B split. Full coordinator build exit0/SHA1OK; honest NonMatching, native gain0. Prior c18 evidence is archive/c18_u128, not c18_u12.
