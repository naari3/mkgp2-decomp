# banana-trio-spawner-native

Source: Codex worker c17_u86_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 724 B.

c17_u86: BananaTrioSpawner 800E0B10 baseline text99.14365 (720 vs724B), EH8 exact/index91.66667. Missing target branch800E0B74 comes from an explicit completed phase case2:break before case0, improving99.69613 and exact724B/index100. Moving default alone is invariant. Residual f0/f1 exchange800E0C80..0CA8 resolves with native1.0f in blend upper clamp only; postprocess_sdata2 maps it to lbl_806D5BB8. All text724/EH8/index12 are100, flag Matching. Source object in main.elf edge, target function bytes exact, full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No split/EH bridge/padding changes.
