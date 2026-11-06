# clItemBox-popout-native

Source: Codex worker c15_a9_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 164 B.

PopOut at 0x8005E9D0 converts directly to C with timer += 1.0f/60.0f; height = 3.0f*(float)sin((float)(0.017453292519943295*(90.0f*timer)))+baseHeight; scale=timer; rotation+=0.0125f; clamp scale to 1 and return 1 when timer>=1, otherwise return 0. Explicit float rounding of radians is visible as frsp before sin. #pragma exceptions on/reset emits exact 8-byte extab and 12-byte index under unchanged GC/1.3.2 flags. First hypothesis reached 100% for 164-byte text and both EH sections. History 3132b07 introduced only extracted asm with no documented specific C blocker; 49d81e64 only renamed the math call. Targeted search of docs/notes for PopOut/clItemBox/8005E9D0 found no parking explanation.
