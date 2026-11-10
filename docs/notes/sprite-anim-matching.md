# sprite-anim-matching

Source: Codex worker c8_s30_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 384 B.

fn_801A0E54 reaches native text/extab/extabindex 100% when the scale is written as literal 255.0f and integer addition keeps the converted value on the left. Declaring the scale as an extern constant caused CSE to retain its FPR across clamp blocks, omitting three target lfs instructions. Existing postprocess_sdata2.py maps the literal to shared lbl_806D97E0. Affine concat float temporary followed by a six-element float copy loop reproduces target temporary stores much better than scalar copies or aggregate assignment.

## c14_u4_20261106
Source: Codex worker c14_u4_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u4: fn_8019FA30 improves 94.67669 to 97.23684. Explicit nextId pointer and sorted-before-ids declaration recover exact 1064-byte function size, stack array locations, extab/index 100%. Extract only resource drawing loop as static inline with cached color/alpha arguments: all floating-point instruction/register residuals disappear and main pointer homes become target r23/r24/r25. Remaining integer walker/count/color webs and opacity branch split persist; whole DrawLayers inline extraction exceeds compiler inline budget and regresses. Three approaches exhausted, retained NonMatching, full fallback-linked DOL SHA-1 OK; no native gain.

## c14_u10_20261106
Source: Codex worker c14_u10_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u10: fn_8019F5BC improves94.41053->95.77193 with sorted-before-ids stack declaration, explicit append cursor, and separate RotateX/RotateY inline helpers preserving cos-before-sin. Removes extra array-base instruction (source1144->1140 target size), extab remains87.5/index improves100. Residual target frame4C0/save r17 vs source4B0/save r18 and widespread GPR/FPR web partition. Folding trig calls directly into return expressions changes evaluation order and regresses90.26667. Singleton stays NonMatching; fallback full DOL SHA-1 exact.

## c14_u18_20261106
Source: Codex worker c14_u18_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u18: fn_801A0004 94.11644 -> 94.404106 via private inline Rotate and Scale helpers. Scale parameter evaluation restores target scaleY-before-scaleX loads. Translate helper is byte-invariant; Scale-only hybrid reaches94.19863. Main residual is FPR scratch graph (source f30-f31 save / 0x90 frame vs target f29-f31 / 0xA0), with final scaling products and zero/one homes differing. Single function remains NonMatching; native gain0; fallback full DOL SHA-1 exact. Three structural approaches used.

## c19_u132_20261107
Source: Codex worker c19_u132_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u132 retry fn_8019FA30 97.23684->97.44361: independent layerIndex for drawing instead of reusing collection/sorting i makes count exact r30 and reduces mismatched target rows70->62. Text1064/extab8/index12 unchanged; retain NonMatching. Unique-layer search inline helper97.23684 only changes volatile search homes; declaration refinement placing layerIndex before arrays97.23684; short-color child-drawing inline wrapper is instruction-invariant97.44361. All probes archived build/w. Residual sorted/index homes r31/r29 vs targetr15/r31, scan/search homes, base/output color partition and resource-only opacity copy. No applicable singleton/pool rescue or single-fn split. Coordinator full build target SHA-1 OK, zero native gain.

## c21_u114_20261108
Source: Codex worker c21_u114_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u114 fn_8019F5BC retry: separate ScaleTranslate(value,scale,translation) inline with double magnitude=__fabs(scale), return value*(float)magnitude+translation improves95.77193->95.8421/1140 B. Restores separate first-sine rounded value f0, fabs destination f3, product operand f0 and frsp source f3; all other formatted instructions unchanged. Named rotation return local is invariant; sorting-only inline regresses95.61404 (rank volatile r10, ids walker r18). H1 retained NonMatching, EH87.5/index100; target frame4C0/save r17 versus source4B0/r18 and broad argument/coordinate/color register partition remain. No pool/singleton/A/B rescue. Coordinator full build exit0/DOL SHA-1 exact; zero native gain.

## c22_u117_20261109
Source: Codex worker c22_u117_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u117 fn_8019FA30 97.44361->98.38346: keep adjusted opacity as int aa and explicitly narrow assignment with (short)(opacity+f->alphaOffset). This differs from c18 aa-only helper-parameter probe: changing the CALLER local removes the resource-only r9->r18 copy, restores recursive opacity move and makes the control-flow layout exact. Text1064/extab8/index12 exact sizes; FP exact. All-color integer carriers97.74436, combined preparation inline96.2406/1080B, actual short RGBA args97.89474; reverted. Remaining61 rows are GPR homes and collection output stack-base materialization. Single-fn NonMatching; no A/B/pool/singleton rescue. Coordinator full build exit0,target DOL SHA1 exact; zero native gain.

## c22_u136_20261109
Source: Codex worker c22_u136_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u136 fn8019F5BC95.8421->97.052635/1140B; extab87.5->100/index100. Replace selected f=&frames[last];f-> accesses with frames[last].field throughout transform and output:96.50877, restores selected offsetr23/pointerr17/ordinalr22, frame4C0/saver17 and exact7ACA0000EH. This succeeds where merely naming an explicit byte offset (c18) was invariant. Move nextId=ids from declaration to after initialization loop:97.052635, restores ids baser0/countreg11 and improves initialization schedule. Reversing base-color declarations is instruction-invariant. Remaining67 objdiff rows mixed GPR/FPR/schedule: inputf24-f29 vsf23-f28, selected coordinate/cos/px homes, base color partition, collection/search scratch and append-cursor rematerialization. No pool/singleton/A/B rescue. Keep improved NonMatching draft. Full coordinator fallback DOL SHA1ea30f3b1 exact; zero native gain.

## c22_u175_20261109
Source: Codex worker c22_u175_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u175: Individual static inline float-returning cosine/sine wrappers improve fn_801A0004 direct94.404106->94.678085, restoring angle f31/cosine f30. Exactly eight operands change to their target registers, six rows become fully exact and two partially improve; all other formatted instructions unchanged. Source568 versus target584, EH87.5/index91.66667 unchanged. Double cosine local83.66438/572B changes conversion/scheduling; explicit two-row temporary and nested copy loops34.5/756B add instructions. Both rejected, trig-wrapper best retained. Residual target f29-f31/frameA0 versus source f30-f31/frame90 plus initial zero/one/x and final scale scratch graph remains, scoped diff rows74->68. No pool/singleton/A/B rescue, native gain0. No full-build request; flags/ranges unchanged.

## c23_u14_20261109
Source: Codex worker c23_u14_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u14_20261109: fn_8019F5BC 97.052635 -> 97.49123, 1140B, extab/index100. Natural SpriteAnim_Cos/Sin(float)->float wrappers around double libm calls restore all six incoming float homes and saved coordinate/cosine FPRs; 67->44 aligned differing formatted rows. Both helper boundaries needed (cos-only97.08772). Named helper return results and named sineY product invariant. Supplied shapesweep Id_f scaffold97.43158/46rows not retained; named caller coordinate temps97.063156, frame-taking rotate helpers97.052635, coordinate accessors96.98245. Remaining GPR input/cursor/search/base-color partitions plus four first-sine/fabs volatile FPR rows. No pool/singleton/A/B rescue. Retained NonMatching; full coordinator fallback DOL SHA1 exact; native gain0.

## c23_u120_20261109
Source: Codex worker c23_u120_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u120: isolate only paired ids/sorted sentinel initialization as static inline InitLayers. fn_8019FA30 98.38346->98.43985%,1064B,EH/index100,59 differing rows (was61). Collection append cursor is now target r10; initializer remains exactly same instructions. Supplied mwccdbg root sorted base remains r31 vs targetr15. Per-layer DrawLayer extraction still fails inline budget (caller456/helper676;38.796993%), explicit id/order pointer sentinel walk93.1391%; both discarded. Retained H1 honest NonMatching, no pool/singleton/A/B rescue. Full coordinator all_source/report/DOL build exit0,target SHA1 exact; native gain0.

## c23_u166_20261109
Source: Codex worker c23_u166_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1072 B.

c23_u166: fn801A0004 94.678085->95.92466. TU-private Dot2(ax,ay,bx,by) plus Add(translation,product) in Compose restores source584B/146insns, target frameA0/savef29-f31, extab/index100. BOTH helper boundaries needed: Add-only94.16438/568B, Dot-only92.45206/568B (previous c21 dot-only failure does not cover this combination). Caller-owned scratch array is invariant94.678085; two-row identity initialization51.027397/684B rejected. Final remaining80 aligned rows are exclusively FPR identities; all146 opcodes/order, GPRs, stack accesses, branches and relocation operands match. Baseline68 aligned rows included missing saves/frame mismatch; new score reflects structural/EH improvement, not monotonic per-row register improvement. One-function TU remains NM; no A/B/pool/singleton rescue. Coordinator full build exit0/fallbackDOL SHA1ea30f3b1 exact; native gain0. All attempts in build/w.

## c25_u74_20261110
Source: Codex worker c25_u74_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 2388 B.

c25_u74: nested double-return SpriteAnim_Magnitude(float)->__fabs(scale), called from ScaleTranslate, improves fn_8019F5BC97.666664->97.73684 (1140B,EH/index100), removing all four first-sine/fabs FPR differences. ?24 nested-inline-level explains temporary creation after ScaleTranslate parameters. Full collection helper95.6807 (index91.66667) and distinct sampling layerIndex97.47369 rejected. Final40 aligned rows all GPR identities/prologue copies. No A/B/pool/singleton rescue; native gain0. No full build requested (flags/ranges unchanged).

## c25_u103_20261110
Source: Codex worker c25_u103_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u103: named caller float x, assigned after identity initialization immediately before translation transform fill, improves fn_801A0004 95.92466->96.9863 (584B,extab/index100). Same early load before identity regresses91.58904 through scheduling. Final146 opcodes/order and all non-FPR operands exact;62 FPR-only rows versus80 initially. Compose wrapper invariant; Dot2 pointer-out82.863014/index91.66667 rejected. No A/B rescue or native gain.

## c26_u40_20261110
Source: Codex worker c26_u40_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c26_u40: fn_8019F5BC 97.73684 -> 97.789474%, 1140B/EH100/index100. Sentinel init only in SpriteAnim_InitLayers (same helper as sibling fn_8019FA30) removes initialization lifetime from shared i and restores append cursor r10; 40 -> 38 aligned formatted diff rows. Named red int carrier after explicit short cast is invariant. Explicit named search pointer + dedicated collection counter gets target collection GPR homes but adds address rematerialization/step schedule differences, 97.13333%; pointer reuse in initializer 93.45263%, rejected. Compiler mechanism: CInline_Expand makes inline locals frontend temps, IRO_SplitLifetimes splits reused outer i; named/temp coalescing restriction in InterferenceGraph.c coalescenodes (mwcc_internals, patterns 46/57/89). Three approaches, no unlock; retained NonMatching. No full-build request, flags/ranges unchanged.
