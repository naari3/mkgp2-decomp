# ItemSelect refill/setup/update (anon_802386E0, cxb_r1, 2026-11-04)

Source: Codex worker cxb_r1_itemsel386_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

- fn_80238980 setup (1052B) native exact incl. 24B automatic DELETEPOINTER extab + extabindex: genuine `new TextManager`, per-TU ctor bridge to TexMgr_Init, `-Cpp_exceptions on` + lmw/stmw. In the four-text-manager loop declare `int i` before the explicit cursor (i=r29, cursor=r28); the reversed declaration leaves a pure r28/r29 swap at 99.79%.
- Honest NonMatching after 3 approaches: fn_802386E0 refill 91.79% (direct scalar 77.38%, explicit layout pointers/top-tested wait 90.15%), fn_80238D9C update 87.94%.

## c15_u68_20261106
Source: Codex worker c15_u68_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c15_u68: direct fresh baseline91.791664 (assignment report93.13). Adding void *playerData argument to CompleteChoice, passing g_playerData, and capturing caller playerData=g_playerData restores two distinct hoisted pointer webs, r22-r31 saves, exact672B size and extab8/index12 at100%. Text93.9881 remains NM. Localizing helper layout/resources91.89286; whole-loop helper exceeds inline threshold; item-table pointer-argument helper is invariant. Residual table base +C0 folding, self/resources/x/y/choice/player-data register homes, choice count/zero scheduling and position scratch homes. No legal singleton split; fallback full DOL SHA1OK.

## c16_u19_20261106
Source: Codex worker c16_u19_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u19: fn_80238D9C baseline87.93535/1840B ->90.24354/1856B. Caller playerData snapshot plus separate SelectChoice pointer parameter restores hoisted caller global web; helper global still rematerializes after grid getter. Explicit float slide temporary, even with existing fp_contract pragma unchanged, restores target separate multiply/add where inline return expression fused. Bitwise alpha insert gives clrlwi/oris/ori (target li/rlwimi). Byte-stride GridItem plus resources argument improves small amount; target subarray-base materialization and GPR cycles remain. Automatic owned extab28/index12 now100; jump table0 due branch offsets. Singleton stays NonMatching; fallback full DOL SHA1 exact.

## c19_u112_20261107
Source: Codex worker c19_u112_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 12 fn / 2920 B.

c19_u112: fresh90.24354->90.37285 with shared int index/explicit self-based cursor across three disjoint tail sprite loops. Counter reaches targetr22; cursorr23 still targetr24. Size1856/EH28/index12 unchanged100,data0. Native __rlwimi alpha precedent restores packing and raises90.706894 but source1852 shifts EH (96.42857/index91.66667), rejected by section-regression rule; nested signed-short ChoiceResource helper invariant. Archived c17u57 best95.70905 depends on pool803DC0C0..803DC2C0 now owned by out-of-scope ItemSelectChoiceUpdate.cpp, so not replayed. One function prevents B; honestNM, full coordinator fallback SHA1ea30f3b1exact; no native gain.

## c19_u239_20261107
Source: Codex worker c19_u239_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u239: fresh baseline93.9881 (assignment94.7); static inline SetRefillPosition(sprite,x,y) fixes position scratch at802388E0..F8 and raises94.10714, exact672B/EH8/index12. Self local plus target-ranked x/y/resources declarations and early nextCount temporary are both invariant; reverted those probes. Remaining callee GPR webs, two +C0 table-base folds and choice count/zero scheduling. Pool803DC0C0..803DC2C0 is already owned by out-of-scope ItemSelectChoiceUpdate.cpp and was not touched. Singleton staysNM; no B cut; coordinator fallback DOL SHA1exact; zero native gain.

## c21_u129_20261108
Source: Codex worker c21_u129_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u129: fresh90.37285->93.32758,1856B,owned jump table/EH/index100. Inline intro directly into update, share column i with tail loops and hoist row before i:91.13793. Move playerData=g_playerData into SelectChoice as unsigned-char pointer local before selected/timer writes and Reload, removing argument:92.86423,1860B. This restores target intro register partition AND helper global hoist/player/slot/choice/resource webs. GC/2.6 then emits natural li-256/rlwimi,removes4B,and restores size/EH plus all jump-table destinations100. Retained configure mw_version=GC/2.6. Remaining pool bases fold because pool belongs to out-of-claim ChoiceUpdate; caller player/column/row,alpha/fade and tail counter/cursor homes differ. No A promotion/B cut; full service SHA1 exact,+0 native.

## c21_p58_20261108
Source: Codex worker c21_p58_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p58: fresh direct baseline93.32758 ->93.780174 (report93.99354),1856B,data28/EH28/index12 all100. Reuse existing row/i across intro, selected coordinates and tail loops93.34914; move choice load inside held==1 then test selected/done93.780174, fixes held-before-choice load and caller playerData r27. FadeFraction(int,float) helper93.11207 with nontext regression, reverted. Remaining external pool subobject bases, column/row swap, fade scratch/alpha and tail counter/cursor GPRs. Pool803DC0C0..803DC2C0 owned by outside-claim ChoiceUpdate. Contiguous minimum merge80238D9C..8023B1A8 spans8TUs, not just Update+ChoiceUpdate; includes Dtor,State_Init,fn9D6C,fnA148,ItemGridState_Init,ChoiceStep. No A/B promotion; service fallback DOL SHA1 exact; no native gain.
