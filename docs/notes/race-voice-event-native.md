# race-voice-event-native

Source: Codex worker c6_nt2_801a9d58_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2332 B.

fn_801ACC18 (0x801ACC18, 0x91C) matches GC/1.3.2 with Cpp_exceptions on and use_lmw_stmw on. Its 8-byte extab is a plain save record. The 0x68 race-entry view needs an unsigned participant byte at +0x31 and an item pointer at +0x40. A cast of the older padded entry type changed address-temporary allocation; a full typed declaration matched. The elapsed-time test is an early return on < threshold (>= introduced cror and mishandled NaN equivalence). Separate timestamp symbols lbl_806D17A0/high and lbl_806D17A4/low avoid objdiff relocation aliases. Linked DOL SHA-1 verified after source promotion.
