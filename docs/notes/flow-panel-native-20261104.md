# FlowPanel / attract join input (anon_801D9A2C, cxb_r2, 2026-11-04)

Source: Codex worker cxb_r2_flowpanel9a_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

Direct control-flow reconstruction using canonical InputState/GetInput and TestMenuPage InputPlayer. Extended only two virtual slots privately. Correct unsigned 32-bit return for slot 0x2C yields exact cmplwi. Native .text 680 B, extab 8 B, index 12 B all 100%; main.elf build edge selects source object. Coordinator actual link/SHA-1 verification pending. Native constructor and new ResCtrl/GlyphText loops; canonical ResCtrl and GlyphText types. Shared loop index first draft 95.11628%; independent loop indices and corrected FP declaration order 95.639534%. Two final index-declaration/initialization probes were byte invariant; stopped under no-new-information rule. First synthetic walker/index registers swap vs target, adding a separate zero initialization and shifting action PCs; second allocation loop and trailing stores agree. No manual EH. Three structural approaches: scalar OR color, byte-channel union with staged fade calculation, bitfield-channel union with literal fade input. Final retained text 97.061066%; allocation web and control flow agree, but FP scratch identities and union color spills differ. Peak 97.23283% variant discarded because repeated float literal postprocessing mapped 15.0 to the 1.0 symbol; retained external 15.0 and zero references correct that. Stop at approach limit; no asm/manual EH.

## c4_t4_noko_20261105
Source: Codex worker c4_t4_noko_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c4_t4: Scalar unsigned color initialized 0xFFFFFF00, OR with (unsigned char)(int)(lbl_806DA1EC*t), improves Update from 97.061066 to 98.20611 and reduces primary text 1064 to 1056 bytes (target 1048). Owned EH remains 95.83333/index 91.66667 due length/PC deltas. Residual clrlwi+or versus rlwimi at both fade colors and FP scratch identities. Explicit scalar masks, union bitfield OR, and RGB-field initialization were worse. No Matching flip/native gain.

## c5_s5_flowpanelctor_20261105
Source: Codex worker c5_s5_flowpanelctor_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c5_s5: Explicit first-loop FlowPanel cursor (advance sizeof(ResCtrl*) while writing cursor->icons[0]) fixes first-loop walker/index homes r30/r31, improving 95.639534 to 96.04651. Remaining initial zero web uses r4 rather than shared r31 and source remains +4 bytes. Explicit index zero reuse and member initializer list are byte invariant. Automatic EH remains 95%/index91.66667; no Matching flip or native gain.

## c18_u41_20261107
Source: Codex worker c18_u41_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1048 B.

c18_u41: fn_801D9B70 unlocks 98.20611->100% with existing presentation-family __rlwimi(0xFFFFFF00,(int)(255*t),0,24,31) packing, removing both clrlwi+or extra instructions. Preserve mixed constant provenance: fade-in ((float)timer-8.0f)*lbl_806DA1E8 with literal1 clamp; fade-out1.0f-timer/lbl_806DA1F0 with literal0 clamp. All-external fade-in changes FP webs adversely; explicit elapsed/fraction intermediates are byte-invariant. Typed union setter spills. Existing real new PanelSprite and EH bridge suffice. text1048/extab24/index12 all100; Matching source object at801D9B70/1048 and owned ELF bytes exact, full DOL SHA-1ea30f3b1 OK. No split/data/header/EH-map changes, native gain1fn1048B.
