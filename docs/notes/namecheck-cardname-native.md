# namecheck-cardname-native

Source: Codex worker c15_u20_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c15_u20: NameCheck_CardName 80099994 singleton improves text 99.31604 to 99.81132 (848 bytes, extab8/index12 exact) by obtaining converted-table pointers via static inline const unsigned short *NameCheck_ConversionTable(const char *base,int offset). Direct destination-address indexed expressions regress95.10849 by losing preloop base loads. Code-unit load accessor on top of table accessor regresses98.72642. Residual in both conversion loops is only destination-table pointer r5 versus target r4 and current code unit r4 versus target r5 (eight instruction operands). Keep NonMatching after three hypotheses; full fallback-linked DOL SHA-1 OK. No mechanism B cut exists for one function.
