# pcbcomm-compute-c16-u22-20261106

Source: Codex worker c16_u22_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Fresh production compile of untouched PCBCommCompute.c at base c63dabfc measures text 87.11573%, extab 100%, index 91.66667%; target 2212 B, source 2204 B. Trivial output/peer base inline accessors produce identical code. Factoring readiness scan into nontrivial PeersReady helper corrects initialization position and yields 87.486435% without size/EH changes. Indexed traversal worsens to 83.110306%; reverted. Remaining first-peer pointer folding, two-stage output add and register identity differ. Retained NonMatching; no native gain.
