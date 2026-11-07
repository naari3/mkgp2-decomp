# cxc-u9-small-native

Source: Codex worker cxc_u9_small_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 6 fn / 2488 B.

801F6918: declare i,pal,num,out in that order for r31/r30/r29/r28, invH before invW for f2/f3. UV start expressions need named accumulator followed by *= to retain f0*inverse operand order. 8024932C: inline member setters for the two fn_801DAEC0 flags emit li r0 AFTER each getter call; direct/subscript field assignment hoists li into callee-saved r29. Real MI ctor plus canonical FlowSceneHost/SceneBase bridge emits exact primary EH; one extra weak base destructor is emitted. 802494E0: resource declared before int activation local reproduces r29/r28; bool adds clrlwi and changes allocation. 8023F790 first-pass switch source with canonical faders matches 784 text +32 jump table +EH.

## cxc_u9_small_20261105
Source: Codex worker cxc_u9_small_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 6 fn / 2488 B.

Resume 1: source-only .sdata2 sections must be included in validation, even when target text/EH report 100%. PaletteBufferCtor unsigned conversion generated 8 bytes; postprocess_sdata2 renamed the symbol to UND but kept the physical data section. Original lbl_806DA700 was unowned in auto pool. Fix is split ownership of 806DA700..806DA708 plus per-TU @19 -> global:lbl_806DA700. Direct objdiff now text/EH/index/sdata2100%; coordinator DOL SHA-1 rerun pending.

## c17_u44_20261107
Source: Codex worker c17_u44_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 616 B.

c17_u44: RankDispControls split at 0x802494BC rescues fn_802494BC (24 B) and fn_802494D4 (12 B) unchanged as Matching game/RankDispControls_tail.c. Existing C destructor thunk fn_802494B4 stays NonMatching: target subi+b versus 36-byte LR-saving C wrapper plus extra EH. No source-only loadable sections in tail. Full service DOL SHA-1 ea30f3b1 OK; main.elf exact addresses/bytes and source link input verified.
