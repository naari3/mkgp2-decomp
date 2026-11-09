# anchor-addi-object-boundary candidates (detect only)

Near misses where the target forms `addi rX, <anchor>, N` for an N that our build never forms. By regalloc_patterns 40 each such N is the first byte of a real object in the pool: split the pool object there and index it directly. "ours only" = offsets we form and the target does not (a base + constant written by hand). Heuristic: the anchor is the base register with the most distinct offsets; a saved pointer to a big struct looks the same, so check the function.

| fn | TU | % | anchor reg | target-only offsets | ours-only offsets |
| --- | --- | --- | --- | --- | --- |
| `ranking_display` | game/ranking_display | 96.10 | r30 | 0x34 |  |
| `fn_801E32C8` | game/fn_801DEF94 | 92.67 | r31 | 0x24 | 0x34, 0x6c |
| `fn_801B7EF8` | game/fn_801B7EF8 | 91.87 | r31 | 0xc, 0x1c |  |
| `fn_8022BFA8` | game/EnemyFaceDraw | 88.04 | r31 | 0x444 |  |
