# vfxeffect-child-vis-scale-native

Source: Codex worker c15_a19_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 268 B.

VfxEffect_UpdateChildVisScale_Helper 0x800C7D80 (268 B) matches in direct C with the canonical DrawEffectAccess.h macros and Vec. Ordinary 0.05f, 1.0f, 0.1f, 0.0f, 2.0f and 2.2f literals yield exact FP allocation; extern const versions of the same labels yielded 98.80597% with only FP register differences. Remove the manual EH objects: existing -Cpp_exceptions on emits exact 8-byte extab and 12-byte extabindex. No configure changes needed. Full build SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.
