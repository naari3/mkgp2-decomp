# itemselectallowed-retrofit

Source: Codex worker c15_u75_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Fresh direct GC/1.3.2 compile starts 90.13693% (948B). Separate normalized roundInCup from original round and decrement cup before normalization improves 92.06224% at same948B with extab100/index91.66667. Global table accessor/explicit output pointer/nonconst aggregate regresses90.78008%976B; slot loop stays rolled604B52.365147%. Residual original round r30 vs target volatile r5 then r28 and output pointer r28 vs r30; missing table-base +0 materializations and cup/round address scheduling remain. Singleton stays NonMatching; full fallback SHA1 OK.

## c21_p48_20261108
Source: Codex worker c21_p48_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 964 B.

c21_p48: baseline97.510376/964B had only three opening instructions scheduled late (output pointer materialization, round load, first compare). Explicit pointer/round snapshot did not move this schedule (97.26141). Replace global const ItemSelectionDefaults copy with local int selected[3] literal initializer {0x3D,0x2B,0x39}, removing explicit defaults global: compiler emits the original pooled initializer with exact bytes and all text/EH/rodata become100. Existing pool ownership803DC378..803DC530 already sufficient. Existing opt_propagation off retained. PromotedMatching; main.elf source edge and symbol8023C8B0/964 verified; coordinator build service DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact.
