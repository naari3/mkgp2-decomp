# itemselectallowed-retrofit

Source: Codex worker c15_u75_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Fresh direct GC/1.3.2 compile starts 90.13693% (948B). Separate normalized roundInCup from original round and decrement cup before normalization improves 92.06224% at same948B with extab100/index91.66667. Global table accessor/explicit output pointer/nonconst aggregate regresses90.78008%976B; slot loop stays rolled604B52.365147%. Residual original round r30 vs target volatile r5 then r28 and output pointer r28 vs r30; missing table-base +0 materializations and cup/round address scheduling remain. Singleton stays NonMatching; full fallback SHA1 OK.
