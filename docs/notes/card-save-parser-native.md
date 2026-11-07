# card-save-parser-native

Source: Codex worker c18_u89_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u89: CardSaveData_Parser 8008FA2C/1864B improves report97.023605->97.72103 (objdiff96.35408->97.07296), owned extab8/index12 both100. Only modeled declaration reorder in five existing blocks retained. Shared whole-function loop locals95.377686/1856B; shared indices+table with block-local cursor94.71245/1856B; reusable inline DecodeByteMatrix96.49356/1860B: all reverted due text/size/EH-index regression. Residual name/unlock/selection/counter homes, award scratch rotation and loop scheduling. Single-function TU cannot use mechanism B. No pool/symbol/flag/EH changes; fallback-linked SHA-1 OK, no native gain.
