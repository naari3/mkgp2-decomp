# ItemObject_Tick_Kind29_LightAttachment

Source: Codex worker c15_u54_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Remeasured original 95.57522% with exact production compile/postprocess command. Scalar zero-target interpolation must pass through a general static inline helper returning a*t+b*(1-t); direct 0.0f*t is folded away. This makes 0x800E0598..0x800E05B4 exact and raises function to 97.10177%. Remaining curve loop differs structurally: target fixed curve base + byte index + branch-local add; source has two pointer recurrences. Whole-loop helper, segment helper and independent time cursor did not reproduce target. Final source 896 B, target 904 B; extab payload exact, extabindex differs in size word. No TU split/native gain possible with this one-function TU.
