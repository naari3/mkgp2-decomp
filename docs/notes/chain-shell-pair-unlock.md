# chain-shell-pair-unlock

Source: Codex worker c21_u17_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2600 B.

c21_u17: full private ChainShellPairState payload with timers[4] at+4, groundY+14, tetherScale+18, anchorOffset+34 and children[2]+5C, replacing all three raw cursor loops with sub->children[i], fixes all 12 tail cursor/counter r30/r31 operand swaps. First hypothesis99.89231->100%, text2600/data40/extab8/index12. Prior narrow pointer-array projection and canonical parent typing were insufficient; aggregate member indexing is the winning lever, analogous to c20_u80 DualSpawn. No pool/split/EH-map/compiler-flag changes. Matching flip verified by coordinator full DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65, actual main.elf source input and all four owned ELF ranges byte-equal original DOL. Gain1fn/2600B.
