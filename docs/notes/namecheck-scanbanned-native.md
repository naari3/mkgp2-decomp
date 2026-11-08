# namecheck-scanbanned-native

Source: Codex worker c14_u14_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u14: NameCheck_ScanBannedWords 80099CE4 singleton remains NonMatching. Measured baseline94.1674 ->95.0458 using explicit enclosing found/j symbol-membership loops at three sites instead of value-argument contains. Global flag-return helper worsens93.50; pointer-argument contains_at restores target load placement but scores93.90676 due result copies. Retained text7316 vs target7336, EH8 exact/index12 91.66667 due length. First group/extraction helper registers, wcscpy pool base lifetime, first strstr compare/move, at_boundary pointer/count copies and split-run initialization remain. Three approaches exhausted. Full fallback-linked DOL SHA-1 verified; no native gain.

## c19_u12_20261107
Source: Codex worker c19_u12_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 176 B.

c19_u12: measured95.0458 ->95.400215 retained by introducing local cursor in extract_one/extract_two, keeping input position parameter unchanged. This resolves all extraction-local volatile register homes: target region+90..374 now differs only in 11 loads using enclosing sets r25 vs r29. Reordered extractor formal parameters is byte invariant95.0458. Explicit delimiter pointer walker + target-role local declaration order on improved draft regresses95.19847, discarded. Native size remains7316 vs7336, EH100/index91.66667. No pool ranges taken, singleton getter not present. One function precludes B split. Full coordinator build exit0/SHA1OK; honest NonMatching, native gain0. Prior c18 evidence is archive/c18_u128, not c18_u12.

## c20_u12_20261108
Source: Codex worker c20_u12_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u12: measured95.400215 ->96.493454 by replacing COLLECT_RUN shadowed NameBool found initializer with assignment to the enclosing found. Genuine reuse improves repeated split-run flag webs/scheduling; text remains7316 vs target7336, extab100/index91.66667. Separate local traversal cursors in contains_at/at_boundary are byte invariant95.400215. Branch-local duplicated at_boundary calls on best draft regress92.95583/7548B (traversal is duplicated rather than target-tail merged). All attempts saved under build/w. Pool analysis: anchor80318270 begins unrelated float/numeric tables; prefix through80320960 spans0x86f0 bytes, dictionary/table/debug data also used by out-of-claim CardName, so ownership/merge not changed. Same root-base/sets/group/delimiter homes, first strstr mr., folded boundary count/cursor copies and digit addressing residuals remain. Three hypotheses exhausted; one-function TU has no B cut. Coordinator full build exit0/SHA1OK; NonMatching, native gain0.

## c21_p40_20261108
Source: Codex worker c21_p40_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p40: baseline recompile 96.493454; reusing unsigned group for the two disjoint set/delimiter loops gives96.49891 (kept), inline digits accessor invariant96.49891, first strstr result via next/open branch lifetime regresses96.335335. Text7316/7336, extab100/index91.66667. Pool audit UNOWNED is stale: Matching RaceData_8009BEF4.c owns8031B7C0..8032061C, overlapping suggested80318270..80320604. Did not touch that owner. Need coordinator data transfer/ownership coordination, also auto tables/debug through80320960; no B cut for singleton. Full coordinator build exit0/SHA1OK, source_input false, native gain0.
