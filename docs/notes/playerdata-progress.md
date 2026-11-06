# playerdata-progress

Source: Codex worker c14_u38_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_801D670C: splitting self+(cc-1)*32+index into two sequential pointer adjustments fixes target add r0,r3,r0 / add r3,r0,r4 address shape, improving 92.708336 to 94.166664 under GC/2.6. True matrix subscripting folds row subtraction into 0x48 displacement (target 0x68), worsening match. Nested positive guards and index inline helper do not recover target upper-bound ble-over-blr; result stays bgtlr. Single 96-byte target function stays NonMatching (source 92 bytes).
