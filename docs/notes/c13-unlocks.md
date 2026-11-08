# c13-unlocks

Source: Codex worker c13_u2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u2: FigureLabel explicit int label=table[cup]; label += second==1 ? 8:0; return label; prevents outer +8 reassociation and improves fn_801C64DC 98.181816 ->99.93507, exact616B/EH8/index12. Residual add destination r5 vs targetr4 at801C66F8 and dependent addi801C66FC. Narrow return adds unwanted extension; unsigned32 and named complete sum are baseline-invariant. Singleton retained NonMatching; full fallback DOL SHA-1 OK.

## c21_u104_20261108
Source: Codex worker c21_u104_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 616 B.

c21_u104 resolves801C64DC99.93507->100 via inferred FigureLabelId enum return: int label=table[cup]; int page=second==1?8:0; return(FigureLabelId)(label+page). Enum conversion preserves separate table/page sum result r4 and final+8; no codegen pragma. Table8039B218 contains signed halfwords0x1EA2..0x1EA9; page/completion variants use blocks of8. Exact616B/EH8/index12; Matching/source-linked main.elf range checked; service request1 SHAea30f3b1 OK. Narrow short plus unsigned store-boundary cast adds extension99.318184; four older/newer compiler checks and lifetime/CSE/dead diagnostics invariant; propagation-off regresses92.22078. No split/pool/bridge changes.
