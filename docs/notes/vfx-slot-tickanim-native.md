# vfx-slot-tickanim-native

Source: Codex worker c15_a21_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 400 B.

VfxSlot_TickAnim 0x800B013C/400B: first natural C hypothesis matches text400/extab8/index12 all100%. Original TU was generated asm in 610b1871 (game: complete VfxSlot unit); no prior C draft or specific blocker was recorded in that history or targeted VfxSlot notes. Nested signed-char mode/state switches with explicit no-op state1/default preserve dispatch shape. Frame restart uses static inline guarded SetAnimFrame mirroring src/game/VfxSlot_SetAnim.c; this yields the repeated effect null check as ordinary generic helper semantics. pragma exceptions on/reset generates owned EH automatically with unchanged TU flags. Full coordinator service SHA-1 exact and source object confirmed in main.elf input. No config, split, symbol or rename-table changes.
