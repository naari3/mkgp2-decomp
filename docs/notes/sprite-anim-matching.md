# sprite-anim-matching

Source: Codex worker c8_s30_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 384 B.

fn_801A0E54 reaches native text/extab/extabindex 100% when the scale is written as literal 255.0f and integer addition keeps the converted value on the left. Declaring the scale as an extern constant caused CSE to retain its FPR across clamp blocks, omitting three target lfs instructions. Existing postprocess_sdata2.py maps the literal to shared lbl_806D97E0. Affine concat float temporary followed by a six-element float copy loop reproduces target temporary stores much better than scalar copies or aggregate assignment.

## c14_u4_20261106
Source: Codex worker c14_u4_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u4: fn_8019FA30 improves 94.67669 to 97.23684. Explicit nextId pointer and sorted-before-ids declaration recover exact 1064-byte function size, stack array locations, extab/index 100%. Extract only resource drawing loop as static inline with cached color/alpha arguments: all floating-point instruction/register residuals disappear and main pointer homes become target r23/r24/r25. Remaining integer walker/count/color webs and opacity branch split persist; whole DrawLayers inline extraction exceeds compiler inline budget and regresses. Three approaches exhausted, retained NonMatching, full fallback-linked DOL SHA-1 OK; no native gain.

## c14_u10_20261106
Source: Codex worker c14_u10_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u10: fn_8019F5BC improves94.41053->95.77193 with sorted-before-ids stack declaration, explicit append cursor, and separate RotateX/RotateY inline helpers preserving cos-before-sin. Removes extra array-base instruction (source1144->1140 target size), extab remains87.5/index improves100. Residual target frame4C0/save r17 vs source4B0/save r18 and widespread GPR/FPR web partition. Folding trig calls directly into return expressions changes evaluation order and regresses90.26667. Singleton stays NonMatching; fallback full DOL SHA-1 exact.
