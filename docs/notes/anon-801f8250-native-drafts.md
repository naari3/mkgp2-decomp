# anon-801f8250-native-drafts

Source: Codex worker cxc_u10_f8250_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

801F8404 and 801F8728 naturally produce the exact primary DESTROYLOCAL EH action for a 32-byte float quad with inline empty destructor bridged to dtor_801F8214. Direct ctor drafts preserve exact target function sizes; FP allocation remains unmatched. 801F8A34 local is canonical ResCtrl, glyph walker is object-relative +0x24, and advances at +0x22C accumulate before each glyph including spaces/newlines. No source-closed claim; do not retry without a new structural hypothesis.

## c5_s17_fn801f8668_20261105
Source: Codex worker c5_s17_fn801f8668_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1108 B.

fn_801F8668 matches with a const byte-pointer view of canonical DrawTables801F plus offsets A0/100/C0; this prevents redundant descriptor-address rematerialization. Same form does not solve fn_801F894C: offset zero generates an extra base copy and mr instead of target addi-zero. Typed inline helper also leaves original residual.

## c5_s16_anon8021f088_20261105
Source: Codex worker c5_s16_anon8021f088_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 392 B.

F8404: source-private DrawQuad8404 using named double fabs results before float narrowing restores initial product/fabs scheduling; ordering dx before sinPart improves text 97.05882 -> 98.59477. Remaining construction FP colors and first depth vertex y/z f1/f3 swap; exact size 612 and owned EH 100%, stays NonMatching.

## c14_u2_20261106
Source: Codex worker c14_u2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u2: fn_801F8250 typed local pointer fmt = tables->mixedDepthFmt (or mixedFmt), then fmt += offset improves measured object 94.86239 to 96.33028 with owned EH 100%. Residual is only shift/base schedule in both branches: target slwi r0,r30,4 then addi r4,r31,field; source reverses those independent instructions. Byte-scaled offset declared before base and reversed pointer-add operands both emit identical code. Kept typed local form; no source-closed conclusion. Single-function TU cannot rescue an exact subset.

## c14_u7_20261106
Source: Codex worker c14_u7_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u7: fn_801F8A34 improves 94.60199 -> 98.1592. Named local TextDraw801F* instead of parameter-cast macro plus counter initialization before sin/cos restores all target GPR homes. Block-local font width reused for normalAdvance and factor*width restores f1 load + fmr f28,f1 in both font branches. Remaining body glyph lhz is CSE-eliminated, compare and FP schedule differ; primary text800 vs804 B. Fully indexed glyph traversal regresses97.860695, reverted. Singleton remains NonMatching; full fallback-linked DOL SHA-1 OK. Three hypotheses exhausted; no source-closed claim.

## c16_u63_20261106
Source: Codex worker c16_u63_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u63: fn_801F95A0 79.20588 -> 93.23529 under existing GC/2.6 flags. ID-taking inline ReleaseGlyph with table lookup inside helper gives target add r3/table/index then lwz +4 rather than folded addi+lwzx. Flatten outer loop helper; named TextDraw801F local from void* entry plus for-scoped counter restores early table lis r4 and counter r28. Remaining self/cursor r30/r29 versus target r29/r30 and prologue schedule. Owned 136B size/EH unchanged, extab/index 100%. Three structural hypotheses exhausted; no source-closed claim.

## c18_u24_20261107
Source: Codex worker c18_u24_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u24: fn_801F8404 fresh98.59477 ->98.66013 by extracting dy/wx/center-offset/corner stores as inline DrawQuad8404::SetCorners(d,w,h,sinPart,cosPart,dx). Text612B, primary EH24/index12 all exact after append-only @127/@128 bridges; original bridges preserved. Two-Edge projected-half-extent aggregate regresses98.496735; const-reference x/y depth writer regresses97.61438; both reverted. Final residual: constructor FP register homes at +44..C8 and first depth vertex Y/Z f1/f3 swap (+198/+19C/+1A8/+1B0). Weak dtor instructions unchanged. Only one primary function, so mechanism B unavailable; no singleton/base-pool unlock. Three approaches exhausted. No flags/splits/data changes, no full build requested; remains honest NM, zero native gain.

## c18_u93_20261107
Source: Codex worker c18_u93_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u93: fn_801F8728 improves96.71533->98.32117 with private DrawQuad8728. Double fabs products preserved before float narrowing repair initial multiply/load schedule. Project(d,w,h, reference outputs) and SetCorners(d,double-to-float args) boundaries alter FP homes; zero-angle dx=zero; sinPart=dx changes constant coalescing and yields best draft. Three hypotheses exhausted. Primary548B and owned24B EH/12B index payloads exact; extra weak dtor adds60B text/8B EH/12B index. Add-only __dt__12DrawQuad8728Fv->dtor_801F8214 bridge. Remaining construction FP colors + first depth vertex Y/Z f1/f3 swap. One function prevents B rescue; no singleton or base-pool opportunity. Honest NonMatching retained; full fallback-linked DOL SHA1 exact, zero native gain.

## c18_u193_20261107
Source: Codex worker c18_u193_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 1284 B.

c18_u193: fn_801F7F50 improves supplied98.98305 to99.12429 at708B. Descriptor-taking inline DrawPositionDepth7F50(x,y,const DrawDesc801F*) loads z inside helper then calls canonical FIFO writer; this fixes all first depth vertex Y/Z f1/f3 swaps and entire body after+CC becomes exact. Retained sinPart=w*sine before dx=h*sine (+0x70/+0x74 matches target order), measured99.0113 alone here despite c17 invariant report. Full projected-corner helper98.98305, literals98.92655, moving float declarations before fabs invariant, post-projection corner helper98.870056 all rejected. Remaining21 rows are constructor FP homes+44..C8 only. Owned24B EH/index12 bytes and normalized relocations exact; whole85.71429/66.66667 due extra weak dtor. Singleton prevents B; no base-pool/singleton mechanism applies. Honest NM best draft retained. Final coordinator all_source/full fallback-linked build exit0 DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65, native gain0.

## c19_u168_20261107
Source: Codex worker c19_u168_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 804 B.

c19_u168 unlocks fn_801F8A34 98.1592->100%,804B: sentinel access via *(unsigned short*)((char*)walker+offsetof(TextDraw801F,glyphs)) while body retains walker->glyphs[0]. Distinct address-expression provenance prevents body-load CSE without c18 mixed-index extra iterator, restoring target lhz+compare/FP schedule and EH PC264/index324. Canonical offsetof remains byte-identical. Add-only owned @81->@etb_80017688,@82->@eti_8002906C bridges, Matching flag. Final named sections/text/owned EH100; extra weak ResCtrl dtor discarded. Actual main.elf fn801F8A34/804, source edge present/fallback absent; full coordinator DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Native gain1/804. No data/range/shared-header changes.

## c19_u144_20261107
Source: Codex worker c19_u144_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u144: current shared DrawQuadScaled801FPrivate.h freshly compiles fn801F7F50 at99.129944/708B, with initial height loads before width, unlike c18 dedicated header. Direct named double fabs restores initial target width-first schedule but scores99.12429; scaled-extent helper99.067795; four-component projection aggregate98.89831; scalar Set(x,y,anchorX,anchorY,angle,w,h)92.51412; w/h reuse for cosine products99.067795. All reverted. Exact primary EH24/index12 with exact raw relocation names, extra weak destructor remains. No DrawQuad rodata reference in target7F50, so neighboring pool merge does not address residual. One primary function prevents B; no native gain. No full build requested because no retained edits.

## c19_u217_20261107
Source: Codex worker c19_u217_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u217 fn801F8728 current shared-constructor baseline98.875916 ->98.985405 by TU-private copy changing ONLY nonzero-angle half multiplier lbl806DA714 to literal0.5f. ScaledExtent inline and double-dimensions aggregate both98.868614, rejected despite repairing first4 load rows. All-literal98.948906 has @121 literal/EH alias collision and is rejected; keep zero/literalcos refs external. Remaining22 constructor rows+1C..C8, drawing body+CC onward exact. Primary548B, owned EH24/index12 exact; weak dtor unchanged. Single function preventsB; no descriptor-pool addressing in target, no merge rationale. Original DOL confirms cos zero-angle constant806DA734=-0.5. Full coordinator fallback linkSHAea30f3b1 exact; native gain0.

## c19_u200_20261107
Source: Codex worker c19_u200_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u200 fresh baseline98.99346 (packet stale98.66013) ->99.09151 by private DrawQuad8404 copy of current shared DrawQuad7F50, replacing only the two lbl_806DA714 factor reads with0.5f literals. Existing sdata2 postprocessor remaps @136 to SHN_UNDEF lbl_806DA714, +5C SDA21/addend0 confirmed;4 unreferenced compiler literal bytes remain in raw object. All drawing-body rows from+CC onward exact, including first depth vertex. Residual22 rows: constructor width/height load order+1C..28 and FP homes through+C8. Extent-input helper invariant98.99346; separate fabs-double/narrowed locals98.98693 restore width-first loads but regress homes, combined literal98.888885; rejected. All-literal variant99.05882 collides with preexisting @137 EH bridge, rejected; keep mixed constants only. GC2.6 invariant. Owned612B primary text size/EH24/index12 exact sizes and EH100, weak dtor60B unchanged. Singleton TU has no B subset; no singleton-manager or rodata-base residual to unlock A/neighbor merge. No flags/splits/data ownership/shared headers/bridge changes; final coordinator fallback-linked DOL SHA1ea30f3b1 OK, native gain0.

## c20_u105_20261108
Source: Codex worker c20_u105_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 2328 B.

c20_u105 unlocks fn801F7F50 at 100% /708B. Fresh f4d4873-based source starts99.920906, six initial load/narrowing rows remain. TU-private constructor computes named double width=__fabs(d->width*d->scaleX), height=__fabs(d->height*d->scaleY) directly before w/h narrowing: width-first load schedule restored but f5/f6 swapped,99.830505. Declare h before w (all other locals unchanged) fixes swap and gives100. Add-only @133->etb80017618/@134->eti8002900C in existing key, keep historical bridges. Matching flag; no shared header/data/split edits. Owned text/EH/index100; raw EH/index and all4 text+1 EH+2 index relocations exact. Full coordinator build exit0 DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; main.elf801F7F50/708 bytes equal original DOL; source edge present/fallback absent. Native gain1/708.

## c20_u121_20261108
Source: Codex worker c20_u121_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u121 fn801F8404 fresh99.09151->99.48366 by natural declaration order w,h,top,left,sinPart,wx,dx,right,bottom,cosPart,dy, WITHOUT opt_common_subs pragma from gave_up hint. Fourteen constructor diff rows remain: initial width/height load ordering and narrowed height/cosine/dy/Y FPR homes; body+CC onward exact. Distinct fabs temporaries99.281044 restore width-first loads but regress later homes; extent reuse98.92811; inline rotation reference outputs99.28758; direct fabs cast97.84314; double raw products99.24837 and @137 literal/EH collision. All rejected. Only one header declaration line retained. Primary612B/ownedEH24/index12 exact sizes, owned EH raw bytes and relocs100. No singleton/pool ownership or B subset; remainsNM. Coordinator full fallback DOL SHA1ea30f3b1 exact; native gain0.

## c20_u156_20261108
Source: Codex worker c20_u156_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 3648 B.

c20_u156 fn801F8728 improves98.985405->99.423355 by ONLY private declaration order w,h,top,left,sinPart,wx,dx,right,bottom,cosPart,dy; no opt_common_subs pragma. 14 constructor rows remain: four initial width/height loads and narrowed-height/cosine/dy/Y FPR homes through+A0. Direct named fabs doubles+h-before-w fixes initial loads but99.19708; external half invariant; SetCorners(d,w,h) on best is instruction-invariant99.423355. All rejected; best one-line header edit retained. Primary548B/EH24/index12 exact sizes, ownedEH/index100 and drawing body+CC onward exact. 7F50 matched family source has existing opt_common_subs off, not copied under no-fakematch contract. No base-pool/singleton residual or B subset. Full coordinator fallback DOL SHA1ea30f3b1 exact; zero native gain.
