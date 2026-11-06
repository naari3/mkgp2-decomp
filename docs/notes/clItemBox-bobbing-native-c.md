# clItemBox-bobbing-native-c

Source: Codex worker c15_a11_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 172 B.

Bobbing 0x8005E924 converts directly to natural C in one approach. phase += 0.01f; wave = (float)sin((float)(0.017453292519943295 * (360.0f * phase))); height = 3.0f + baseHeight; height += 0.6f * (3.0f * wave); wrap phase at 1.0f; rotation += 1.0f/60.0f; return 1. Explicit float rounding of the double radians product reproduces frsp before sin. pragma exceptions on/reset replaces manual extab/index with identical generated sections. Original introduction commit 3132b07 contains only the asm body, with no explanation of a prior C blocker; subsequent 49d81e6 only renames sin. Targeted notes search found no prior Bobbing-specific explanation.
