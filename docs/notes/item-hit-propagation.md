# item-hit-propagation

Source: Codex worker c16_u2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Observed: unsigned slot-kind <=3 || kind==6 exactly reproduces the target outer gate. Canonical static inline classifier alone is byte-identical to prior macro. Final C object remains 8 bytes short per function: missing duplicate inner-switch exit and effect-bus reload, with shifted classifier scratch registers. Explicit case 0 changes decision tree; C++ island plus explicit ignored states regresses. Do not repeat these probes.
