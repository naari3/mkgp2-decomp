# CW 1.3.2 fp register allocation order tied to declaration order

Observed in KartMovement_SetPosition @ 0x8019A4A0 (batch_text_8019a4a0_kartmove_setpos).

## Rule

CW 1.3.2 with `-O4,p -fp hardware -inline auto` assigns floating-point registers (f0, f1, f2, ...) to local `float` declarators in **declaration order**, not in use-first order.

A single comma-list declarator (`float a, b, c;`) and three separate declarators (`float a; float b; float c;`) behave the same way: the LEFT-MOST / TOP-MOST identifier gets f0, the next gets f1, etc.

## Implication for matching

When the target asm uses high-numbered fp regs first (e.g. f2 for the variable accessed first in source), the temp must be declared LAST in its own group. Example:

```c
// produces f0=x, f1=y, f2=z
float x, y, z;

// produces f0=z, f1=y, f2=x   <-- matches target with x=f2
float z, y, x;
```

## Empirical evidence

KartMovement_SetPosition stores `pos->x` to offsets 0x88, 0x40 (and optionally 0x4C). Target asm:

```
lfs f2, 0x0(r4)   ; x -> f2
lfs f1, 0x4(r4)   ; y -> f1
lfs f0, 0x8(r4)   ; z -> f0
```

With `float x, y, z; x = pos->x; y = pos->y; z = pos->z;` CW produced the inverse coloring (x=f0, y=f1, z=f2), matching 97.5%. Changing the decl to `float z, y, x;` (assignments and uses unchanged) flipped the coloring to match (100%, SHA-1 OK).

## When to apply

- Vec3 / matrix copies where the target asm clearly uses fp regs in reverse decl order.
- Diff symptoms: identical instruction count and addressing, but the bottom 5 bits of the fp register field differ across all 3 floats.

Combined with strategic interleaving (e.g. deferring the last load until after the first store) this idiom can pin both regalloc and scheduler down with no other compiler-flag dance.

## Same rule for GPRs (int / pointer locals)

The decl-order coloring rule also applies to general-purpose registers (r3-r10 range), not just fp regs. Observed in `ItemSelect_AddSlotItem` @ 0x80060D80 (batch_text_80060d40_itemselect).

Target asm: `cursor=r6, mode=r7, i=r8`. Required source decl order:

```c
SlotEntry *cursor;
int mode;
int i;
```

Reordering to `int mode; SlotEntry *cursor; int i;` flipped to `mode=r6, cursor=r7, i=r8` and broke SHA-1.

Mixing types (pointer + int + int) in the decl list does not change the rule — first-declared identifier gets the lowest GPR number in the allocation pool.

### Diff symptom (GPR variant)

Identical instruction count and addressing, but register numbers in `r` fields differ by a consistent offset across the affected variables. Reorder the decl list to match the target's register order.

## c3_n5_bomb_20261105
Source: Codex worker c3_n5_bomb_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 4140 B.

BombExplosion_UpdateShockwaveVfx final-ring scalar reuse across two blocks created f30/f31/f29 webs; block-local lim,h,t,sy declarations produce the exact target f27/f28/f29 and sy reuse f27. KartItemTrail_4Phase period-table const declaration caused read scheduling across self stores and lwzu; non-const extern restored exact text and all owned EH.

## c5_s6_hudmanagerdisp_20261105
Source: Codex worker c5_s6_hudmanagerdisp_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 656 B.

Waypoint_FindNearest 80046680: assigning dx = dx*dx + dy*dy + dz*dz; return PathCursor_sqrtf(dx); in both private distance helpers produces exact text/EH. Returning sqrt(expression) used dz register for result; two-step dx accumulation fixes result register but changes intermediate FMADD destination. One full-expression assignment preserves scratch intermediate and coalesces result into dx. No shared header changed.

## c6_nt3_8017b1c0_20261105
Source: Codex worker c6_nt3_8017b1c0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 528 B.

fn_801866DC (528 B): a local const char *messages = lbl_80376F60 preserves r31 diagnostic pool base; global lbl_80677E18[i].desc/offset indexing removes the pointer walker/stride-sum register swap. Combined result text/extab/extabindex 100%, source-linked full DOL SHA-1 OK.

## c6_nt6_kartmove_20261105
Source: Codex worker c6_nt6_kartmove_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 312 B.

KartMovement speed methods 80199A84/80199B10 require GC/2.7 to sink the leaf prologue. In-place Newton-root update produces exact f4 result; returning through a separate inline root result web yielded 97% register-only residue. Both owned EH/index sections and actual source-linked ELF addresses verified. C15C has exact owned EH/index and primary size, but FP expression-temp identities remain despite scalar declaration probes; left NonMatching.

## c7_s5_20261105
Source: Codex worker c7_s5_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 2664 B.

Stats_PacketStats_UI (8006830C): ratio0=zero; then four ascending assignment chains ratio1=...=ratio8=zero, ratio9=...=ratio16=zero, ratio17=...=ratio24=zero, ratio25=...=ratio32=zero reproduce target zero-case scheduling. Independent scalar zero assignments and one chain of all 33 produce different scheduling despite identical semantics. Entry-local table base restores r30 and exact prologue; canonical TestMenuPage.h works. Text/extab/extabindex 100%, source-linked full DOL SHA-1 OK.

## c7_s14_20261105
Source: Codex worker c7_s14_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 844 B.

RumbleUpdate 80169A14 / shutdown 80169C44: fn_801DAEC0()->inline_member_setter(r->out[ch]) exactly reproduces saved argument temporary r29/r30; free inline setter and explicit assignment temp leave r30/r31 splits. Shutdown genuine inline destructor + delete removes extra incoming pointer move and preserves duplicate null branches. Verified source-linked 844B with full DOL SHA-1 OK.

## c7_s27_20261105
Source: Codex worker c7_s27_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1484 B.

fn_8019618C: external named zero in the facing compare let CW retain it in f2 through an inlined free-slot scan, deleting the target later zero load (99.690025%, -4 B). Using literal 0.0f only for the facing compare leaves the assignment using the named external. Standard postprocess_sdata2 maps the compiler literal to lbl_806D9570; all text/EH becomes exact. Coordinator full link and DOL SHA-1 passed, with both lbl_806D9570 symbols SHN_UNDEF and no retained extra constant.

## c7_s6_20261105
Source: Codex worker c7_s6_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1596 B.

DrawNamCamImage 8007CC9C: y,x,s0,t0,s1,t1,aspect declaration order yields target fp31..fp26 homes; declaring FIFO temporaries z,negX,negY and assigning negX=-x; z=externalDepth; negY=-y reproduces f1/f0/f2 exact scratch assignment. KartItem rear-target unsigned-char inline helper if ((flags & mask)==0) return 0; return 1 reproduces target branch-over-branch boolean island where direct bool initialization does not.

## c8_s50_20261105
Source: Codex worker c8_s50_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 3080 B.

c8_s50: AI_UpdateItemEffects matches 2628B text plus EH/data by declaring catalog before category. fn_801DEC74 matches 452B using explicit persistent ring pointer and separate lookup result before remainder/index calculation. fn_801E68B4 real member-function model restores target self/incoming/item/bus GPR allocation and exact primary EH; free-function model had reversed GPR priority. Residual length f3/f4 scratch allocation remains NonMatching.

## c9_L7_20261106
Source: Codex worker c9_L7_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

KartMovement_PhysicsStep direct reconstruction: declaring yawTurn, turn, grip in this order places them in f29, f28, f27, matching the target; declaring grip, turn, yawTurn swaps f27/f29. PlainDot uses distinct product statements to prevent FMA after inline expansion; fp_contract off on the helper alone did not prevent caller fusion. Inline return-by-value Vec3 helpers materialized extra copy temporaries and worsened this function; canonical direct InitVec construction was closer.

## c10_u3_20261106
Source: Codex worker c10_u3_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

PathManager_UpdateAll 8003B6C4 (c10_u3_20261106): draft improved 98.89709 to 99.20515, kept NonMatching. Explicit shared manager cursor in final loop removes duplicate induction pointer and restores exact text5908/extab8/index12 sizes (EH/index100%). Declaring dx,dy,dz then evaluating dy,dx,dz matches FP arithmetic homes while x/y pointer-load order remains reversed. Declaring ranking scan before slot/candidate fixes candidate r3 / scan r4. Display-loop r24/r25, rank/limit and final loop GPR identities plus final NORMAL argument scheduling remain. Inline search helper was neutral; capturing inputs before the lap condition hoisted loads and worsened the match. No native gain; full fallback build SHA-1 OK.

## c10_u15_20261106
Source: Codex worker c10_u15_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u15 LakituStart_UpdateCountdown 8003D360: shared function-scope unsigned loop index declared before camera changes camera r30 to target r29, improving 98.489586 to 98.510414 while all section sizes and EH remain exact. Explicit pointer cursor loops add mr instructions; inline HideCountdown(model) caches model and adds saved r28/moves, worsening text. FP named-scalar declaration reorder changes output reuse but does not recover side/forward homes; leave singleton NonMatching. Full fallback DOL SHA-1 OK.

## c10_u16_20261106
Source: Codex worker c10_u16_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u16: OptionMenuDraw fn_8015A6E4 draft declared get_title_name_global() without its actual RankLog* argument. Mirroring established GetRankLog inline accessor and passing the result restores singleton r3 load/check and removes prohibited null self-assignment. positions-before-count/i declarations fix loop r27/r28. Best text97.46809, size1880 and EH100; remaining FP scratch/shared coordinate and indexed-access residuals. Full literal conversion97.43617; selective literals can break CSE (+4B). Remains NonMatching; full fallback SHA-1 OK.

## c10_u18_20261106
Source: Codex worker c10_u18_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1852 B.

DebugOverlay_Dispatch 8002BE18: case 9 accumulator residual f30 vs f28 (99.61123%) resolves by separating case 9 accumulated/drawTime locals from case 1 other/draw with a lexical case block. Text1852/data56/extab8/index12 all 100%; Matching source-input full link DOL SHA-1 OK. One hypothesis; no codegen pragma or filler.

## c10_u23_20261106
Source: Codex worker c10_u23_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u23: fn_8023A148 improved 98.08068 -> 99.1687 by replacing return-value ternary clamp helpers with direct in-place conditional assignments. Restored exact text1636/extab8/index12 sizes; EH/index100%. Reference-parameter in-place helpers emit same output as direct conditionals. Targeted explicit declarations for bounds/title-color/conversion locals did not change remaining scratch register allocations. Singleton kept NonMatching; full fallback DOL SHA-1 OK.
