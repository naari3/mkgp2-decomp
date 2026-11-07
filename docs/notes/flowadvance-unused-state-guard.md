# flowadvance-unused-state-guard

Source: Codex worker c17_u28_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 36 B.

FlowAdvance1C fn_80246478 (80246478..80246484) is a state-6 early-return stub. A discarded inline IsFinished(self) expression compiles to blr (33.333332%). Using the existing state test as an early-return guard preserves lwz r0,0x1c(r3); cmpwi r0,6; blr under the normal GC/1.3.2 flags, yielding 100% text for the whole 36-byte TU. No EH/data/split changes needed. Source-linked full DOL SHA-1 exact.
