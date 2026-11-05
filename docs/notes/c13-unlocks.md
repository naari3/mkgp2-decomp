# c13-unlocks

Source: Codex worker c13_u2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u2: FigureLabel explicit int label=table[cup]; label += second==1 ? 8:0; return label; prevents outer +8 reassociation and improves fn_801C64DC 98.181816 ->99.93507, exact616B/EH8/index12. Residual add destination r5 vs targetr4 at801C66F8 and dependent addi801C66FC. Narrow return adds unwanted extension; unsigned32 and named complete sum are baseline-invariant. Singleton retained NonMatching; full fallback DOL SHA-1 OK.
