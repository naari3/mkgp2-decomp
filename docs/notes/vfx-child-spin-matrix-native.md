# vfx-child-spin-matrix-native

Source: Codex worker c15_a17_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 256 B.

VfxEffect_UpdateChildSpinMatrix_Helper (0x800C7F38, 256 B) converts directly to natural C using world[4][4], spin[4][4], a float pulse = (float)sin(effect angle), and the canonical DrawEffectAccess macros/prototypes. Constants in target: angle increments 0.17453289031982422f and 0.5235986709594727f, translation z=-3.2f, pulse scale=0.05f*pulse+1.0f. Existing compiler flags already enable C++ exceptions, so deleting manual extab objects yields exact compiler EH without pragmas or config changes. First approach gives text/extab/extabindex 100%. History b7e0b00c introduced the asm scaffold without a documented C mismatch rationale; 49d81e64 only renamed sin. No TU-specific parking note found in docs/notes.
