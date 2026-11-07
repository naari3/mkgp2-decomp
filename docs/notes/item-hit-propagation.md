# item-hit-propagation

Source: Codex worker c16_u2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Observed: unsigned slot-kind <=3 || kind==6 exactly reproduces the target outer gate. Canonical static inline classifier alone is byte-identical to prior macro. Final C object remains 8 bytes short per function: missing duplicate inner-switch exit and effect-bus reload, with shifted classifier scratch registers. Explicit case 0 changes decision tree; C++ island plus explicit ignored states regresses. Do not repeat these probes.

## c19_u187_20261107
Source: Codex worker c19_u187_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u187: const HitDriver* classifier parameter plus const HitEffectBus* local and const protected-test parameter restores the target effect-bus reload and all classifier scratch-register identities, improving94.52381/96.11487 to99.04762/99.324326. Both now exactly one4B branch short (target800DB008/800DB248), with all other normalized instruction operands identical. Empty-default placement before case1 invariant. Unsigned outer switch still produces signed cmpwi tree and regresses94.46667/96.074326; reverted. Best const-interface source retained NonMatching. Next investigation should target real switch control-flow shape only; pointer lifetime/register residual solved.
