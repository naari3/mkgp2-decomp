# sprite-anim-matching

Source: Codex worker c8_s30_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 384 B.

fn_801A0E54 reaches native text/extab/extabindex 100% when the scale is written as literal 255.0f and integer addition keeps the converted value on the left. Declaring the scale as an extern constant caused CSE to retain its FPR across clamp blocks, omitting three target lfs instructions. Existing postprocess_sdata2.py maps the literal to shared lbl_806D97E0. Affine concat float temporary followed by a six-element float copy loop reproduces target temporary stores much better than scalar copies or aggregate assignment.
