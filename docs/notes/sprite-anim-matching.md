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
