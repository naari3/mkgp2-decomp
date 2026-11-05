# item-state-native

Source: Codex worker c11_a5_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 1868 B.

c11_a5: BananaTriple_OnImpactTick 800E8ACC/480B, StuckOnDriverTick 800E8818/692B and OnchiSpeaker_State2_Flight 800EE620/696B all natural C text/EH/index100. Reuse objview/item_state_private.h Item and Vec3. Unsigned reason-byte comparisons need explicit (int)(unsigned char) promotion to produce cmpwi without extsb. Vec3 by-value GroundTypeAt and AddNormalizedXZ calls produce target caller copies. Explicit empty case1 retains switch branch shape. Flight owns compiler-generated 10-entry .data switch table80421638..80421660 in its existing TU; no bridge or manual data required. Full source-linked DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.
