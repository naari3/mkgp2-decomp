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

## c10_u25_20261106
Source: Codex worker c10_u25_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u25: AI_CalcGPTargetSpeed 801EA6F0 improves 99.06593 to 99.34066 with TU-local numeric-literal SetSpeed/InitialSpeed helpers and lap declared before rank in inline LapBonus (assign rank before lap). Initial-speed FP scratch instructions and lap rank/lap register homes become exact. Rank-follow helper extraction fails auto-inline and regresses to 46.008244; reverted. Residual cup/round arg-home coalescing, scan volatile register homes, FollowBonus conversion/multiplier FP homes, and final render rank r25/r26. Single function retained NonMatching; full coordinator build SHA-1 OK, no native gain.

## c10_u26_20261106
Source: Codex worker c10_u26_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u26: fn_8019C15C improves 99.67836 to99.9269 by direct compression = corner->y - h with literal-zero compares and direct v194.y += lbl_806D96D4 plus literal-zero clamp. Removes scalar z/cy/one/value webs; suspension/clamp instruction identities become exact. Inline CopyUp worsens zero/up FP homes; real InitVec ctor shifts stack slots/EH. Residual only initial uy=f0 vs target f2 / ux=f2 vs target f0 (five instructions). Keep named increment: literal1.0f anonymous @116 collides with existing per-TU EH rename. Remains NonMatching; source objdiff owned EH/index100 and fallback full DOL SHA-1 OK.

## c11_a1_20261106
Source: Codex worker c11_a1_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 32 B.

AssocTree_Init80089C08: direct header initialization with restrict on tree and flags exactly matches32 B under unchangedGC/1.3.2 flags. Cached flag before stores allocates flagr5/zeror4 and changes instruction order; direct restricted field assignments permit lir5;lbzr4;stwr5;addir0 sequence. Full source-linked build SHA-1 OK.

## c12_u10_20261106
Source: Codex worker c12_u10_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 600 B.

fn_801E68B4 600B: by-value inline sqrt helper left squared-length/result f3 vs target f4 and Newton half constant f4 vs f3 (99.53333%). Compute squared length into caller float length, then pass by reference to void in-place helper; replacing return result with value=result resolves all FPR identities at 100% with unchanged instructions/EH. Existing weak Vec3c destructor bridge discards extra 8B EH/12B index at link. Matching source edge and full DOL SHA-1 verified.

## c12_u17_20261106
Source: Codex worker c12_u17_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c12_u17: DriveBehavior_HandleWpType case11 literal constants restore phase-update FP scratch homes, improving 99.210526 to 99.5614 under unchanged GC/1.3.2 flags. Explicit named matrix outputs and named amplitude/bias/inverse-wave components each compile identically to the literal version. Remaining eight post-sin FP register differences; singleton stays NonMatching. All owned data/EH100%; fallback full DOL SHA-1 OK.

## c12_u20_20261106
Source: Codex worker c12_u20_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c12_u20 fn_80243464: numeric literals in ratio/x/scale and x bounds improve text 99.14286 to 99.40476, EH8/index12 exact. Target x f2/scale f1 vs emitted f1/f0 remain. Combining multiply/add initializers worsens to 99.04762; explicit scale,x,ratio declarations with external constants are baseline-byte-invariant. Singleton stays NonMatching; no new native gain.

## c13_u4_20261106
Source: Codex worker c13_u4_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u4 PairTracking 801E9A84 improves 97.92254 to99.47183. TU-local literal speed helpers eliminate all FP scratch differences. Target-derived reverse inline declaration order fixes ctrl/record and full distance scan; ctrl != other fixes cmplw order. Remaining initial kart-offset, cup/param/round and lap rank/lap GPR identities. Flattening PairSpeed to main else grows frame50->60 and drops95.93662, reverted. Three approaches; singleton retained NonMatching; full fallback SHA-1 OK.

## c13_u22_20261106
Source: Codex worker c13_u22_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u22: KartPhysics_UpdateSmoothing 801EFFA4: declare yaw before pitch but define pitch then yaw, and use a distinct pitchDelta rather than reassigning yaw delta. This makes the final 0x801F04C4..0x801F0578 adjustment block exact, improving 96.88312 to 97.181816 with unchanged 1540B and exact EH. Matrix operand reversal in a local inline helper was byte-identical; preloading row components shrank/unrolled differently (1344B, 81.56364), rejected. Singleton remains NonMatching.

## c13_u24_20261106
Source: Codex worker c13_u24_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u24: Collision setup 802090F0/80209138 scalar inline SetVector(Vec*,float x,float y,float z) improves 97.77778/96.666664 to98.333336/98.888885 under unchanged GC/2.6. Remaining first-function pos.z/rot.y/rot.z FPR identities and second-function pos.x/pos.y f4/f5 swap. Explicit caller scalar snapshots regress; by-value Vec helper adds stack/GPR copies/EH; helper parameter x/y swap and helper named scalar declarations are invariant. TU stays NonMatching, no native gain. Full fallback-linked DOL SHA-1 OK.

## c13_u26_20261106
Source: Codex worker c13_u26_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

PointList constructor 8016C94C improves96.65873->99.15873 with independent copy/diagnostic loop indices (i,k) under unchanged GC1.3.2 flags. Direct delta field stores regress91.82539; named dz/dx before Set optimize to original96.65873. Literal zero in Set is text-neutral and adds unused sdata2, removed. Final text504/EH8/index12 sizes unchanged, EH/index100. Remaining reversed x/z argument evaluation, mr vs li copy-offset initialization, print indexr26 vs targetr25. Singleton stays NM; full fallback DOL SHA-1 OK.

## c13_u36_20261106
Source: Codex worker c13_u36_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u36: KartMovement_PhysicsStep 8019CD30 improves 95.86947 to 96.40763 by moving yaw subtraction into each field2fc/field2fd branch and retaining a named correction product in the else branch. Shared outer correction merges branch tails and removes target separate yaw load/sub/store. Copy-initializing all InitVec snapshots worsens 88.84199; default-constructed displacement component writes alter EH. Literal zero at throttle compare restores missing target reload but worsens other scratch webs; literal quantization/blend also below retained best. Singleton stays NonMatching, unchanged EH scores, full fallback DOL SHA-1 OK.

## c13_u39_20261106
Source: Codex worker c13_u39_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 300 B.

c13_u39: fn_801F6D58 300B texture-rectangle setter reaches exact text/EH under unchanged GC/1.3.2. Numeric literals 1.0f/0.5f restore constant homes and fmuls operand order (95.8 -> 96.666664). Declare float x,y,h before assigning h=height; y=y; x=x to restore target x=f3/h=f9 and dependent arithmetic scheduling (100%). Existing canonical SpriteTex header unchanged. Existing Matching flag promotion needs no bridge or split edits; full source-linked DOL SHA-1 OK.

## c14_u5_20261106
Source: Codex worker c14_u5_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 400 B.

ZlibInflate_BufferToBuffer 0x800AB958 (400B, GC/1.3.2): assigning next_out before avail_out at both setup/reset sites improves 94.65 ->95.05. Declaring local input after remain/out and setting input=src+8, instead of mutating the src parameter, restores input=r29/dst=r28 and initialization scheduling, reaching exact text/extab/extabindex. Canonical z_stream header adoption preserves exact output. Matching promotion verified source-linked with full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.

## c14_u33_20261106
Source: Codex worker c14_u33_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 356 B.

c14_u33: GameModeBase_FrameUpdate 800A07EC 93.4375 ->100 by established GetRankLog inline accessor; caller-local null assignment had changed the r0/r3 web. GameModeBase_Dtor 800A086C 99.47369 ->100 with signed remaining byte at playerData+198 and inline member decrement. Free unsigned-byte decrement helper was neutral. Both text356/EH16/index24 exact; Matching source edge and ELF addresses verified, full DOL SHA-1 OK. Prior register-allocator dead end was missing inline/type structure.

## c14_u48_20261106
Source: Codex worker c14_u48_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u48 KartPhysics_ApplyCollisionForce 801EDFEC: move squared magnitude inside vector-length inline helper and use literal sqrt constants to restore target f4/half f3/three f2 allocation. Native PhysicsCollisionVec offset declared first, pragma exceptions on around function, and own per-TU destructor/name bridge generate exact 24-byte EH (PC1A0, local28) and index12 without manual tables. Text91.8125 ->93.85714, same896B. Plain nonvolatile push/callVec reduces848B and regresses92.07143; reverted. Angle/push FP homes and scheduling remain; singleton NM, fallback fullSHA1OK, zero native gain.

## c15_a44_20261106
Source: Codex worker c15_a44_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 940 B.

c15_a44: clFlowItemSelect_Update 801CBD58 (940 B) native exact under unchanged GC/1.3.2 flags. if (++self->intro >= 9) avoids an extra reload versus increment then separate compare. Declare alpha before y to obtain y=f1/alpha=f0. Separate animation-loop cursor gets r28 while shared cursor used r31. Existing TU anonymous-symbol rename behavior collided with literal IDs (@77 float210 mapped to clFlowItemSelect_Update_data_806CFE18 and @80 decrement mapped to lbl_806D9DB0); named external float labels avoid collisions without editing rename keys. Compiler-emitted conversion double is postprocessed to lbl_806D9DC8. Owned text/EH/index 100 and source-linked full SHA1 OK. History had only extracted asm and relocation repair, with no explicit reason for prior C parking.

## c15_u9_20261106
Source: Codex worker c15_u9_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 464 B.

ItemObject_CheckKartCollision 800D78FC: named extern constants in k*(const*scale), even after swapping outer operands, produced fmuls f29,f4,f1 and f28,f4,f0. Literal expressions (10.0f*scale)*k and (40.0f*scale)*k produce exact target f29,f1,f4 and f28,f0,f4. Standard sdata2 postprocess maps literals to lbl_806D5A84/88. All text/EH exact, source-input full DOL SHA-1 OK. Separate radius assignments with *=k worsened intermediate FP register allocation.

## c15_u29_20261106
Source: Codex worker c15_u29_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 152 B.

c15_u29_20261106: ItemUnlockGridResolve fn_8023D710 (152B) reaches exact GC/1.3.2 text/EH by removing manual inner entry cursor and using lbl_803E56B0[row][column]. Original explicit inner cursor plus synthesized outer row pointer had r30/r31 exchanged (98.947365%). Explicit outer pointer restores homes but emits an extra initialization mr (96.97369%); pure two-dimensional indexing produces both strength-reduced cursors with exact homes and no extra instructions. Existing Matching promotion source-linked; full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.

## c15_u34_20261106
Source: Codex worker c15_u34_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 452 B.

Item_SpawnHitBurstParticles 800FD784: removing the z temporary and directly nesting Rand_RangeFloat with named extern zero args caused zero to be held across the random call in a saved FPR. Literal 0.0f args instead restore target post-call lfs/fmr and remove extra fmr; sdata2 postprocess maps the literal to lbl_806D63F8. Declaring count before signedKind resolves their r28/r29 swap. Combined text452/EH8/index12 exact and full source-linked DOL SHA-1 OK.

## c16_u6_20261106
Source: Codex worker c16_u6_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u6 HomingMarkerUpdate fn_80172948: fresh text89.37534/2920B, EH100. Complete inline scalar setter SetScalar(scale,rotation,red,green,blue,alpha), called by existing pointer wrappers, improves89.83424 without size/EH changes. Nested color-only scalar helper89.73836; explicit named channel locals invariant89.37534. Residual scratch FP allocation and interpolation/blend scheduling; singleton stays NonMatching, no B cut. Coordinator full fallback DOL SHA1 OK; zero native gain.

## c16_u44_20261106
Source: Codex worker c16_u44_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u44: fn_8019ADF4 separate scalar xx/yy/zz product statements in two lengths and dot prevent contraction across each expression; restores target652B and EH/index100%, improves83.993866 to87.533745. Normalize/Length helper factoring restores target root spill order10/8/c but adds volatile loads and changes FPR webs (77.74233%). GC2.7 regression77.21472%; retain GC1.3.2. Remaining early prologue, FP homes/scheduling and root slots; singleton NonMatching, fallback full SHA-1 OK.

## c16_u108_20261106
Source: Codex worker c16_u108_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u108: DrawEffect_KartWheel_TripleChildUpdate 800C2AAC (900B) improves99.844444->99.91111 by replacing m=offs[i]*len; Scale(k*(childScale*m)) with len=offs[i]*len; len=childScale*len; Scale(k*len). Offset/childScale load homes become exact, leaving multiply result f2 vs target f1 and associated operand order at800C2C88/8C. Named m compound multiply and inline offset*inverse helper each99.86667; neither exact. EH8/index12 exact, singleton remains NonMatching; full fallback DOL SHA1 OK. Do not repeat these three source shapes.

## c17_u13_20261107
Source: Codex worker c17_u13_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u13 fn_8019A9BC: sequential accumulator shared across matrix inner iterations plus out[index+col], index+=4 restores target two-row unroll/slwi/stfsx. A nine-scalar inline SetRotation groups quaternion calculations before matrix stores; with lifted-Y arithmetic before multiplication recovers exact1080B/frame110 and primary24B EH bytes, fresh61.533333 ->94.155556. Caching source matrix rows enables scalar propagation and regresses45.055557; reverted. Numeric constants probe94.47037 but emits1084B and retained sdata2 (sin/cos double-folded0.5 becomes lfd), rejected. Remaining axis load order/FP homes and matrix operand/GPR allocation. Singleton remains NonMatching; zero native gain.

## c17_u50_20261107
Source: Codex worker c17_u50_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u50 fn_8023A148: fresh 99.1687 -> 99.43765 with literal 0/1/255/0.1 constants; keep external 0.125 lbl_806DB918 to preserve fade FP homes. Approved SINGLETON_INSTANCE replaces both handwritten getter selects byte-neutrally. Native mask/add color form shrinks text12B (98.42298); flattening SetTextAlpha preserves size but changes fade alpha r5->r4 (99.376526). Retain helper and __rlwimi. All remaining 41 differences are GPR scratch identities in packed colors and fade conversion; text1636/EH8/index12 sizes unchanged, EH/index100. No safe rescue cut; remains NM. Coordinator fallback DOL SHA-1 exact.

## c17_u52_20261107
Source: Codex worker c17_u52_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u52 OptionMenuDraw: owner-approved native pool 803678D8..80367F68 (curve float[255], color uint[42], positions float[5], two layout rows float[10], threshold int[17], strings) fixes aggregate-view add+displacement accesses to target addi/lfsx. All 1678 emitted bytes equal DOL; object rodata comparison 100 incl. final natural 2-byte alignment. Original external base labels remain exported for other TUs. Move title declaration after positions/count/i fixes r28->r27. Fresh 97.46809 -> final99.38298, text1880, owned EH/index/data100. Repeated coordinate expressions lose caching (1884/93.93617); explicit X locals are invariant. Residual FP scratches, shared coordinate homes and pulse coefficient/denominator homes remain. Singleton TU stays NM; full fallback-linked SHA1 exact, no native gain.

## c17_u81_20261107
Source: Codex worker c17_u81_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u81 PathManager_UpdateAll: fresh99.20515 ->99.25592, unchanged5908B/extab8/index12. Explicit display manager cursor declared before count and initialized with count in for initializer fixes entire display lookup register pattern. Block-local independent feedback entry/outer/inner indices restore final slot cursorr27 but leave entryr24 vs31, outerr25 vs28, innerr28 vs24. Function-scope feedback declarations regress99.22884. Inline distance helper regresses99.1239 by rotating FP/Newton homes without fixing x/y pointer load order. Ranking rankr25/limitr28 vs targetr24/r25 and final NORMAL coordinate argument scheduling remain. Single-function TU stays NonMatching; no rescue cut; fallback full DOL SHA-1 exact. No native gain.

## c17_u83_20261107
Source: Codex worker c17_u83_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u83: PointList constructor 8016C94C improves99.15873->99.31746 by declaring diagnostic k immediately before its loop, after copy loop, instead of function-scope int j,n,i,k. This fixes diagnostic r26->r25 with all text504/EH8/index12 sizes unchanged, EH/index100. Scalar Vec ctor emits __construct_array for points[20] (540B/83.79365), return-value vector subtraction emits stack copies (568B/86.150795), in-place DifferenceXZ plus explicit copy byte offset regresses94.20635. Reverted all but scoped k. Residual six reversed x/z expression instructions and copy-offset li vs mr. Sole function prevents B; stays honest NM, full fallback DOL SHA1 exact, zero native gain.

## c17_u115_20261107
Source: Codex worker c17_u115_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u115 fn_801046C4: baseline by-value Bus_TestFlag causes -4B boolean island. Pointer-based ItemEffectBus getter with explicit zero/one if/else returns emits exact branch-over-branch and restores 2064B size and shared sdata2 postprocess offsets. Standard LerpF(a,b,t)=a*(1-t)+t*b helper repairs yaw instruction scheduling and raises text to99.92248; remaining six FP constant/product/negative/result register differences. b*t changes only multiply operand order; named complement/weighted locals are invariant. EH8/index12 exact, singleton stays NM, fallback full DOL SHA1 exact. Prior steering-ring-native c3_n7_801046c4 heading actually describes ring insertion 801E4AF4 and supplied no recorded dead ends for this function.

## c18_u18_20261107
Source: Codex worker c18_u18_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 376 B.

c18_u18 SceneModel_Init 80076494 (376B): inline LoadSceneLights(self,chainLights), including first-null early return and default-light fallback, fixes chain prev/index/base homes. Nested inline LoadSeparateLights(self) fixes count/output/stride callee-saved homes. Pure local-scope changes and explicit byte cursors regress. Combined native helpers match text376/extab8/index12 100%, existing TU promoted Matching, source link and final ELF range verified, full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No shared pool or EH metadata changes needed.

## c18_u25_20261107
Source: Codex worker c18_u25_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u25: fn_80243074 1008B improves fresh 98.583336 ->99.27778% by replacing Root zero/Newton external const references with 0.0f/0.5/3.0 (also zero return/sign test). Fixes second/third Root sum and Newton FP homes. Caller-expanded rotation retains wrong FP homes (99.218254); explicit next local worsens95.230156. Whole-geometry inline helper does not inline (176B primary,14.861111). Retained residual: index/position r28/r29 swap, rotation callee FP homes, projection x/y/z load order vs target y/x/z. Single function stays NonMatching. Final fallback DOL SHA-1 exact; no native gain.

## c18_u29_20261107
Source: Codex worker c18_u29_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u29: LakituStart_UpdateCountdown improves98.510414->99.927086, text1920/EH8/index12 unchanged, EH/index100. Vec3f planar offset fields recover sidef31/forwardf30; scalar height remains f26. HideCountdown(LakituStart*) with local unsigned i reloads self->model per call and fixes all five loop cursorr29/indexr30 without caching model (prior model-parameter helper added saves/moves). Move height calculation before first coordinate evaluation to fix FP scheduling. Vec3f result.x/y/z gives targetf29 for all translation setters. Remaining seven instruction rows: cached dir.x/dir.y f28/f27 versus targetf27/f28, yaw f26 versus targetf29. Decl order dx/dy invariant. Direct setter expressions99.78125, named shared result99.90625; genuine vector results99.927086. Single function remains NM; coordinator all_source/progress/report/ok build SHA1 exact; no native gain.

## c18_u86_20261107
Source: Codex worker c18_u86_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u86 KartPhysics_UpdateSmoothing 801EFFA4 improves 97.181816 -> 99.53247, unchanged text1540/extab8/index12. TU-local matrix multiply with sum declared before distinct left0/right0...left3/right3 scalar pairs reproduces target FP homes and load order; reusable left/right pair only reaches97.49351. Declaring float *result=out.m before n/i restores target output=r6,n=r5,i=r4,column temp=r3 and makes full matrix loop exact. Plain double 0.5/3.0 Newton constants reproduce target sqrt FP homes; retained relocs verified lbl_806DA458/lbl_806DA460 at original offsets. Separate divided speed from final speed and literal lower bound 1.0f. Remaining divided speed/divisor f1/f2 swap and scale identity zero/one/factor f2/f1/f0 vs f1/f0/f2 with initialization scheduling. Flat n++ output indexing changes unrolling (79.0987), rejected. Six hypothesis families; retained NonMatching; fallback full build SHA-1 OK, no native gain.

## c18_u92_20261107
Source: Codex worker c18_u92_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u92 RegisterCarObject8003CF44: original C body emits exact532B operation/control-flow skeleton but e=r24 vs targetr31 and params shifted up one. Whole-function static inline wrapper does not auto-inline (32B wrapper+532B helper); tiny entry accessor is byte-invariant96.80451%; C++ entry reference keeps same homes. Existing-family #pragma exceptions on/reset around original C function restores extab8B and extabindex12B to100% while text stays96.80451%. Kept EH improvement, honest NonMatching, source_input=false, no native gain. No singleton/pool pattern is present. Single-function TU offers no mechanism-B cut. Final full build fallback SHA1 exact.

## c18_u98_20261107
Source: Codex worker c18_u98_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u98 PhysicsState_AccelInterpolate 801EC894 improves 96.59091 to99.09091 via inline AccelRate(entry) returning scale1000*entry[1], outer scale10 multiply, plus pointer-mutating ApproachAccel(current,target,step). Gain helper restores constant-before-field load order and gain f0; interpolation pointer helper preserves per-branch stores. Return-value interpolation merges stores (86.43939%, -8B). Direct reused delta yields98.86364%; in-place step scaling and moving final scale into AccelRate are invariant99.09091. Residual11 operands: stepf4 vsf2, second deltaf2 vsf3. Text264/EH8/index12 sizes exact, EH100%; remains singleton NM, no A/B rescue/native gain. Full fallback DOL SHA1 exact.

## c18_u140_20261107
Source: Codex worker c18_u140_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u140 fn_801046C4: LerpF(a,b,t) returning raw expression had six FPR scratch differences (99.92248%). Writing b = a * (1.0f - t) + t * b; return b; restores constant=f0, negated yaw=f0, interpolated result=f1 and improves99.96124, unchanged2064B/EH8/index12. Residual three rows801049E8/F0/F8: weighted product=f1 versus targetf2 and complement=f2 versus targetf1. Named complement/weighted locals, external1.0 constant and pointer-output helper invariant99.96124; assigning a or t instead restores original six-row residual99.92248. Retained b assignment, singleton remains NonMatching. Sole function prevents B; no pool/singleton pattern addresses this residual. Full coordinator fallback DOL SHA1 exact; zero native gain.

## c18_u176_20261107
Source: Codex worker c18_u176_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 900 B.

c18_u176: DrawEffect_KartWheel_TripleChildUpdate 800C2AAC (900B) reaches 100% from 99.91111 with complete inline ChildLineScale(inverseLength, offset, childScale, factor): offset *= inverseLength; offset = childScale * offset; return factor * offset. Caller passes len, offs.v[i], C(0xB0), k after reciprocal. Unlike prior two-operand offset/inverse helper, this owns all three products and reuses the offset parameter across both intermediates, resolving the two rows 800C2C88/8C. Intermediate childScale accumulation instead gives 99.82222; offset accumulation exact. Text900/extab8/extabindex12 all 100%; TU Matching, source edge excludes fallback, linked ELF ranges byte-equal target, coordinator full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No metadata, pool, or split edits. +1 native fn / +900 B.

## c18_u182_20261107
Source: Codex worker c18_u182_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 1940 B.

c18_u182 retry RalySmokeVariant_Tick 800C80C0: external const aggregate copies leave addi joint-table base and lwzu direction first-word transposed, 99.03381%. Native local initializers for BOTH direction and joint arrays restore exact scheduling. Direction-only literal initializer moves joint loads early; use both. Place four function-local static const char arrays after direction initializer and before joint initializer: compiler rodata becomes dirs48 + strings/alignment112 + joint pointers16, matching 8032A7E0..8032A890. Add that owned rodata split, no symbols/bridge changes; objdiff text828/rodata176/extab8/index12 all100. Matching source edge and full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified by coordinator service. Inline direction getter and two-output table-copy helper invariant; mutable joint table and reversed aggregate assignments regress.

## c18_u198_20261107
Source: Codex worker c18_u198_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 17 fn / 2272 B.

c18_u198 HandleWpType801DE848 improves99.5614->99.82456 by first=1.1f*wave+0.1f; wave=1.0f-wave; wave=1.1f*wave+0.1f; then matrix stores. Fixes rounded wave f3 and amplitude/bias f2/f1; five result/complement/store rows remain. Parameterized affine helper, output-pointer+return helper, post-sin-only external constants neutral. Reusing helper wave/bias adds fmr688B/99.03509; local two-float in-place aggregate99.590645. Keep accumulator draft; text684/data40/EH8/index12 unchanged, data/EH100. Single function stays NM, fallback coordinator DOL SHA1 exact; no native gain.

## c18_u208_20261107
Source: Codex worker c18_u208_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 596 B.

c18_u208: fn_8018A418 (596B) reaches100% from99.79866 with static inline float AdvanceFrameTime(Frame *frame,float step){step=frame->time+step;frame->time=step;return step;} called in both timer branches with1.0f. Pointer-owned load/store plus step-parameter reuse preserves field-loadf2/incrementf1 order and emits sumf1, fixing six result/compare/store operands. Prior c12/c16 by-value increment helper and direct expression initialization reversed loads and regressed; this pointer-mutating helper is structurally distinct. Text596/extab8/index12 all100, existing TU Matching; source edge and original-address linked ELF ranges exact; coordinator full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No shared pool/split/header/EH metadata changes.

## c18_u233_20261107
Source: Codex worker c18_u233_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u233 retry KartPhysics_ApplyCollisionForce 801EDFEC: free inline set_scaled(volatile Vec3&, x,y,z,factor) preserves distinct result webs for second push scaling, and subtract_vector(Vec3&, volatile const Vec3&) snapshots input before position writes. Text93.85714 ->95.62054, same896B; owned EH24/index12 exact. Broad literals raw98.30804 but compiler anonymous IDs collide with inherited add-only @84/@85 EH aliases; reject rather than count. Inner-scope push locals/destination snapshot invariant; reverted. Final valid draft retains original named constants and verified literal sqrt relocs; only source changed. Sole function prevents B. NonMatching fallback source_input=false; coordinator full SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; zero native gain.

## c19_u3_20261107
Source: Codex worker c19_u3_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u3 PathManager_UpdateAll8003B6C4:99.25592->99.81381,5908B/EH8/index12 unchanged,EH100. Correct distance term order to (dx*dx+dy*dy)+dz*dz and declare dy,dx,dz: target squares Y first then FMA X. Integer-before-float private Waypoint prototype (independent EABI GPR/FPR sequences) and matching FIND argument order make every default search call exact. Rank/limit/j/e phase scope with outer function i reused fixes rank24/limit25/index27. Full ranking inline helper does not inline; full feedback helper fixes all GPR homes but rotates FP/Newton homes. dy accumulator makes feedback FP exact but moves X pointer loads, worse overall; do not repeat these probes. Remaining one node load before rather than after candidate addi at8003CA54/58, and feedback entry24/outer25/inner28 versus31/28/24. NonMatching, no B cut, no native gain; coordinator fallback full DOL SHA1 exact.

## c19_u23_20261107
Source: Codex worker c19_u23_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u23 PhysicsStep: fresh96.40763 ->96.42672 by snapshotting response=k->field1d8, reusing previousSpeed=Param(k,0x18)*previousSpeed, then force+=response*previousSpeed. Four source instructions change; three become exact (response f0, coefficient f2, product f1, FMA f26). Primary5212 vs target5240; EH96.23288/index95 unchanged. Vertical scale moved into displacement constructor argument96.4 (six FP scratch changes); typed template vector helpers text-invariant. Explicit drag local corrects multiply operand order but shifts conversion double to @631, colliding with old etb rename; apparent96.430534 rejected. Separate previousForce local restores original96.40763. Retain reuse variant only, no maps/ranges/flags changed; full fallback-linked DOL SHA1ea30f3b1 exact, zero native gain. Future work still needs displacement constructor and plane-projection alias structure; singleton TU has no B cut.

## c19_u36_20261107
Source: Codex worker c19_u36_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 18 fn / 11048 B.

c19_u36: KartShellRibbonDraw 800B3250 (1980B) reaches100% from99.90909. Declare half after halfW and initialize half within width-helper arguments; use inline Ribbon_ScaledHalfWidth(float half,float width){width *= half; return width * lbl_806D5118;} with caller halfW=Ribbon_ScaledHalfWidth(half=lbl_806D50AC,dims[0]); reuse half for sx product in stretched loop. Named half fixes f30/f31; parameter accumulator fixes remaining prelude width/inverse64 f1/f0 homes. Literal half regresses99.69697, early explicit half init99.72727, inline assignment alone99.959595, inverse64 literal invariant, direct halfW accumulator leaves width in f31. Text1980/extab8/index12 all100; Matching source edge excludes fallback; full coordinator SHA1 exact and all three original-address ELF ranges byte-equal. No metadata/data/split/header edits.

## c19_u40_20261107
Source: Codex worker c19_u40_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 232 B.

c19_u40: LakituStart_UpdateCountdown improves99.927086->99.947914 by using canonical Vec3f rotation; rotation.y=offset+(float)atan2(dir.x,dir.z), then SetYaw(...,rotation.y). This fixes yaw f26->targetf29 without reusing translation fields. Remaining five rows are cached dir.x/dir.y f28/f27 vs targetf27/f28. Direction/basis Vec3f snapshots fix dir.x but rotate dy/result to f29/f28 (99.895836); declaration scope and complete perpendicular basis do not improve. Whole ApplyCameraPose helper refuses inline61.925; small affine helper origin accumulation rotates FP homes99.46875. All rejected probes reverted. Final1920B/EH8/index12, EH/index100, NonMatching singleton; no A/B rescue. Full coordinator fallback DOL SHA1exact, zero native gain.

## c19_u41_20261107
Source: Codex worker c19_u41_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u41 OptionMenuDraw 8015A6E4 improves99.38298->99.914894 with same1880B and exact rodata/EH/index. Assign cached Ys in draw-call arguments rather than prior statements (all coordinate scratch f0/f1 fixes); banner zero float literals fix its load/fmr scheduling; first pulse use literal10.0f and0.5f but retain external1.0 for falling fraction (first pulse exact). Genuine OptionDrawPoint{float x,y;} rowOrigin declared before scalar locals replaces rowX/final titleY, fixing all later f30/f31 homes. Plain scope separation regresses98.585106; scalar storage reuse and PulseRamp inline helper invariant; direct fade fields99.5; full pulse literals99.56383; using struct y for early heading or separate heading point99.04256. Remaining seven rows: English heading Yf24 vsf30, second rise durationf1/productf0 vs targetf0/f1. All six structural families exhausted; sole function keeps NM. Literal mappings confirmed GLOBAL UND. Full fallback DOL SHA1exact, native gain0.

## c19_u53_20261107
Source: Codex worker c19_u53_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1412 B.

c19_u53 fn_8023A148: explicit title=(unsigned char)alpha; title|=0xe0202000 fixes the entire phase-3 packed-color web (99.43765->99.66993). Compute fade alpha before loading existing text alpha to recover target integer-conversion scratch homes (->99.792175). Retain both source edits; 1636B text/EH8/index12 sizes exact and EH100. Remaining16rows are phase-2 title r4/white r0 versus target r0/r4. Native byte-union grows12B; unsigned-char helper parameter regresses99.30318; title helper and white-before-title declaration invariant. Six probes exhausted; singleton staysNM, full fallback DOL SHA1OK, no native gain.

## c19_u59_20261107
Source: Codex worker c19_u59_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u59 AI_CalcGPTargetSpeed improves99.34066->99.89011, unchanged1456B/EH8/index12. Explicit function-scope scan rank,driver,candidateRank,targetRank,i,distance,base locals and cached driver rank recover all scan register homes; named targetRank=rank-distance fixes compare operand order. Nested GPScaleFollowDelta(int delta,float factor) with local float value=delta; return factor*value fixes all three conversion bias/converted value/multiplier FP sequences. Integer delta alone and external multiplier constants are byte-invariant. Reduced GPFindAhead helper inlines but regresses96.99176; rejected. GPBaseSpeeds output-pointer helper fixes saved-load/copy shape but swaps cup/round (99.89011, eight differing rows); reversing declarations and making enemy param a helper argument are invariant, so rejected in favor of six-row draft. Retain NonMatching, no native gain or mechanism-B cut; no flags/ranges/maps changed. Existing coordinator baseline DOL SHA1 rechecked; no fresh full-link request.

## c19_u98_20261107
Source: Codex worker c19_u98_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u98 retry FlashFadeOverlay_Draw80070EA8: eliminating separate uplus/vplus locals and reusing u1/v1 through plus, scale, complement improves99.55224->99.60821 at unchanged1072B/extab8/index12, EH100. Residual13 scratch FPR rows in8007119C..711F8; saved homes/FIFO exact. Explicit centers99.55224 (expanded declaration99.4403); scalar Add helper99.38433; products retained in uplus/vplus99.49627; selective one literal99.55224, reciprocal scale literals99.49627; UV lexical scope invariant; struct scale/inset pairs99.49627. Retain attempt3b; singleton NonMatching, native gain0.

## c19_u126_20261107
Source: Codex worker c19_u126_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u126 retry fn_80243464 improves99.40476->99.45238 (840B unchanged) with ScaleFromOffset(float offset) helper reusing offset through /29,1-offset,0.6*offset,+0.4; signed int conversion remains in caller. Unlike c17 int-input scale-return helper, this float parameter owns all intermediate values. Conversion double/load/subtract and divisor now exact;15 FPR operand rows remain, x=f4 vs targetf2, scale=f0 vsf1. Complete scale+store helper99.190475, explicit x/scale accumulators99.04762, hybrid external final-add constants99.14286, geometry aggregate byte-invariant99.40476, combined geometry helper99.09524; all rejected. Six hypotheses exhausted, retain higher draft as NonMatching; EH8/index12 exact, no A/B rescue. Full coordinator fallback DOL SHA1ea30f3b1 exact; zero native gain.

## c19_u142_20261107
Source: Codex worker c19_u142_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u142 HomingMarkerUpdate fn_80172948 fresh89.83424->90.60959/2920B, owned EH8/index12 both100. Literal constants89.87534 fix complete first setter block. Caller-local shared radius/opacity89.80685 rejected. Common scalar Interpolate(from,to,t) for RGB interpolation and Blend alpha raises90.60959; retained with literals. Remaining Pulse/result and RGB/old-channel FP homes plus interpolation scheduling, no valid B cut or unowned pool. All attempts build/w. Coordinator full fallback DOL SHA1 exact, zero native gain.

## c19_u150_20261107
Source: Codex worker c19_u150_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 684 B.

c19_u150: DriveBehavior_HandleWpType801DE848 reaches100% from99.82456 by extracting static inline float DriveWave(float phase){return sin(3.1415927410125732f*phase);} and using wave=DriveWave(self->phase). Keep c18 first/wave accumulator sequence. Unlike earlier affine/matrix-output inline helpers, this owns phase multiplication and double-sin-to-float return conversion. Five post-sin scratch rows become exact: complementf4, firstf0, secondf1. Text684/data40/extab8/index12 all100. Matching flag only; no ranges/maps/flags other than matching status changed. Source edge excludes fallback, four actual ELF ranges byte-equal original DOL, coordinator full DOL SHA1ea30f3b1 exact. +1 native function/+684B; first targeted hypothesis succeeded.

## c19_u175_20261107
Source: Codex worker c19_u175_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u175 PairTracking801E9A84 improves99.47183->99.71831. Semantic PairSpeedContext fieldwise parameter/cup/round grouping restores roundr25 (99.57746). Read lap/rank in PairSpeed caller and pass into calculation-only PairLapBonus; rank-before-cursor declarations in distance helper recover scan while caller snapshots restore target rankr27/lapr26. Text568/EH8/index12 preserved, EH exact. Remaining8 GPR instructions: initial offsetr24 vsr26, cup r26 vsr27, paramr24 vsr26. Explicit offset moves to31; direct declaration reorder regresses; C++ aggregate initializer adds template copy/frame; lap aggregate invariant. Six hypotheses exhausted. Singleton staysNonMatching, no A/B, zero native gain. Full fallback DOL SHA1ea30f3b1 exact.

## c19_u183_20261107
Source: Codex worker c19_u183_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u183 retry fn_8019A9BC: inline SetAxisAngle(MovementQuat*,float x,float y,float z) called directly with orientation row fields restores target pre-sin Z/Y/X load order via argument evaluation, 94.155556->94.162964, primary1080/frame110 and owned24-byte EH unchanged. Axis homes still X/Y/Z29/30/31 vs target30/31/29. sum=a*b+sum recurrence is byte-invariant here (unlike c19_u125 constructor); scalar QuatMatrix(m,x,y,z,w) reverses q-field reload order and scores94.155556, reverted. Remaining quaternion/translation/constant FP and matrix GPR/operand homes. No singleton or pool-base site; one-function B unavailable. Source remainsNonMatching, nativegain0, coordinator full fallback DOL SHA1exact.

## c19_u191_20261107
Source: Codex worker c19_u191_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 504 B.

c19_u191: PointList constructor fn_8016C94C (504 B) promotes from99.84127 to100 by qualifying both constructor SpawnPoint *spawn and walking SpawnPoint *cur with __restrict. Only adjacent Z loads at +0x70/+0x74 change: target loads points[j].z into f1 before cur->z into f0. Named single/all operand snapshots, ComponentDifference helper, and reversed-parameter Displacement helper are invariant. Addition of negated source regresses96.13492/512B. Retain original direct dx/dz source plus alias qualifiers. Text504/extab8/index12 all100. Existing bridge/ranges/flags unchanged except Matching status. Full source-linked DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; gain1 native fn/504B.

## c19_u206_20261107
Source: Codex worker c19_u206_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u206 KartPhysics_ApplyCollisionForce 801EDFEC retry: typed CollisionForceState view with canonical PhysicsPlainVec position/previous/push/impact plus original-DOL literal values and real by-value apply_push snapshot helper gives VALID95.62054->98.33036 (896B), EH24/index12 exact. Const-only probe95.57589 and push-helper-only95.57589 regress. Typed/literal-only raw98.35268 collides with inherited add-only @84/@85 EH aliases; cleanup alone still collides. Composition with useful push helper makes all literal IDs@87..@97, removing those collisions without changing bridges/tools. Damping806DA440 is0x3F199999, so0.599999964f (0.6f is wrong oneULP). Local0.009f@92 remains unexternalized due load-offset difference. Residual angle/offset and push FP homes, gain-load scheduling, final subtraction scheduling; three approaches exhausted, singleton preventsB. HonestNM, source_inputfalse, final service DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact; zero native gain.

## c19_u249_20261107
Source: Codex worker c19_u249_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u249: AI_DecideAndUseItem_PairTracking 801E9840 improves92.889656->97.16552 (560->568B) with family-existing static inline void Decrement(int timer,int &result){result=timer;if(timer>0)result=timer-1;}. Unlike scalar return or pointer-update helpers, reference output preserves two target mr input/result copies and restores initial record-base addi/mulli scheduling. Remaining12B is switch cmpwi8/beq/bge plus GPR homes kart26/target27, hit27/target26, rank29/target26, use28/target29, selected27/target28. Separate case action blocks preserve dispatch but duplicate calls (85.586205%,624B). Singleton stays honest NonMatching; extab100/index91.66667 due length; coordinator full fallback DOL SHA1 exact. c15_u69 had no archived drafts and empty patch.

## c20_u2_20261108
Source: Codex worker c20_u2_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 3308 B.

c20_u2 PathManager_UpdateAll8003B6C4 improves99.81381->99.94922: use candidate->node instead of slot->entries[0].node in the ranking initial validity test. Same participant expression changes scheduling, fixing target8003CA54 addi r3,r6,0x10 thenCA58 lwz r0,0x14(r6). All earlier code and5908B/extab8/index12 exact. Only13 feedback GPR rows remain: entry24 vs31, outer25 vs28, inner28 vs24; slot27 and FP exact. Entry accessor invariant; function e/i reuse99.78673; boolean feedback helper adds16B; per-entry action helper rotates FP/GPR99.70548; typed self->entries feedback indexing adds4B99.134735. Six approaches exhausted. NonMatching retained, no A/B rescue, fallback full DOL SHA1 exact, native gain0.

## c20_u16_20261108
Source: Codex worker c20_u16_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u16 PhysicsStep fresh96.4229 (assignment96.42672) ->96.47633, unchanged5212vs5240B. Reusing consumed brake parameter for later radius rather than traction-response local fixes callee-saved radius/angle/speed and final sign/inverse-speed homes. Distinct new scoped radius local worsens96.40382 by changing earlier force homes. Small QuantizeSteering inline isolates integer conversion constant from inherited @631/@632 EH aliases; final conversion@635 maps to UND lbl806D97B0 with raw4330000080000000. Add-only own @636/@637 EH/index aliases restore96.23288/95; fresh baseline93.64407/61.11111. Reference-scalar displacement ctor instruction-invariant (except literal alias), reverted. Missing zero reload, displacement and projection CSE/FP scratch/EH-PC residuals remain; no B cut or singleton/pool opportunity. TU NonMatching, zero native gain; coordinator full fallback DOL SHA1 ea30f3b1 exact.

## c20_u48_20261108
Source: Codex worker c20_u48_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 3364 B.

c20_u48 AI_CalcGPTargetSpeed99.89011->99.91758: static inline GPDistanceBonus(self,ctrl,kart) owns final rank snapshot and distance call, restoring r26 at801EAC1C/AC34. Four cup/round load/copy-direction rows remain. Typed tuning context and input-only output getter invariant. Caller renderRank reuse fixes final rank but swaps lap rank/lap homes99.86264; caller lap snapshot invariant. Aggregate base-speed return97.10165/1480B materializes result. Native C++ query ctor/Max/Min restores saved-load direction but swaps cup/round homes99.91758; reversed member declarations invariant. Keep only distance helper. Text1456/EH8/index12 sizes retained, EH100. No singleton/pool issue, singleton cannot B-split; honest NM and zero native gain. No configuration edits or new full-link request; baseline fallback DOL SHA1 rechecked exact.

## c20_u73_20261108
Source: Codex worker c20_u73_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u73 FlashFadeOverlay_Draw80070EA8 improves99.60821->99.64552 at1072B/EH8/index12 exact sizes, EH/index100: replace u1=uscale*u1 and v1=vscale*v1 with compound *=. One scratch home becomes exact;12 FP rows remain8007119C..711F8. Inline scaled-sum accumulator99.38433 (offset accumulation invariant); upper endpoint aggregate99.55224; C range-return factory87.02612/1104B with stack returns; selective16/12 literals99.55224; center-to-minus um/vm reuse99.08582. No pragmas/flags/data/split edits retained. Singleton NonMatching, zero native gain; no A/B rescue. Prior c12/c17/c19 archive handoffs and patches read.

## c20_u93_20261108
Source: Codex worker c20_u93_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u93 fn_80243464: explicit normalization-range parameter reused for offset/range quotient fixes denominator-home f6, 99.45238->99.5. Factor and bias parameters then fix scale final add/store, 99.59524 retained at 840B/EH8/index12, EH100. In-place reference helper baseline-invariant; shared affine helper99.28571 (x-only99.166664); DistanceRatio range reuse invariant99.5; isolated x width accumulator99.28571. Twelve FPR rows remain, x f4 vs targetf2 and ratio f0 vsf1 plus constants/complement. No singleton or base-register pool site; singleton NM, no rescue cut. Full coordinator fallback-linked SHA1 exact. Avoid repeating these six hypotheses; snapshots/JSON under build/w.

## c20_u103_20261108
Source: Codex worker c20_u103_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u103 HomingMarkerUpdate direct90.60959->94.09315/report94.10685 at2920B; EH8/index12 both100. SetInterpolated now forwards computed RGB to complete SetScalar (93.46027). Complete BlendScalar regresses92.78082, reverted. Delta-first Approach(from,to,t) for scale/alpha plus constant-first timer expression raises94.09315; restores case4 RGB f31/f13/f12 and first old-channel f30, case3 saved time f31. Pulse/result, remaining setter FPRs/scheduling, case4 constant f10/f11 and second old-channel f11/f10 plus multiply/add ordering remain. Three hypotheses exhausted. Color tables owned by matched Scene80172844 outside claim; no A/B. Full fallback DOL SHA1ea30f3b1 exact; native gain0.

## c20_u153_20261108
Source: Codex worker c20_u153_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 3648 B.

c20_u153 PairTracking801E9840 improves97.16552->99.413795 at exact580B/EH8/index12. Family AI_UpdateItemUseLogic has empty case9, not8: this alone restores missing cmpwi8/beq/bge and raises99.27586. Declaring use,target,hitTimer,rank after ctrl/record and assigning rank later gives99.344826; reusing consumed hit-timer scalar for rank gives99.413795 (retained as decisionValue). Remaining17 GPR rows: kart29 vs27, rank28 vs26, use27 vs29, target26 vs28; initial hit-timer26 exact. Whole-body inline92.61379 changes timer moves/Vec slots; bool flag98.965515 changes cmpwi to clrlwi.; local kart copy byte-invariant99.344826. All six hypotheses archived build/w; no config/range/header/data/EH-map changes. No singleton/base-pool residual or exact subset for A/B; honest NM, fallback coordinator DOL SHA1ea30f3b1 exact; zero native gain.

## c21_u2_20261108
Source: Codex worker c21_u2_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 5908 B.

c21_u2 PathManager_UpdateAll8003B6C4:99.94922->100 at5908B/EH8/index12. Extract full feedback phase into UpdateRankFeedback and its distance arithmetic into ParticipantDistance: all GPR homes exact but19 FPR rows remain99.918755. In the nested distance helper declare dx,dy,dz and reuse dy as squared-distance/Newton/result accumulator (no separate distance local): all FP and pointer scheduling exact100. This composition succeeds where earlier whole-feedback helper plus open-coded dy accumulator changed pointer loads. Inner-loop entry declaration99.92214; function-scope entry alone99.94922 with wrong different GPR homes, both reverted. Matching flag flipped; no range/data/header/bridge/order changes. Full coordinator source-linked build exit0/DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; actual main.elf owned text/EH/index all byte-identical; native gain1fn/5908B.

## c21_u88_20261108
Source: Codex worker c21_u88_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u88 HomingMarkerUpdate fn_80172948 direct94.09315->94.84521/2920B; owned EH8/index12 exact. H1 Pulse named-result single-return invariant94.09315. H2 reference/in-place Approach regresses93.46027, reverted. H3 SetInterpolated transform writes then separate scalar SetColor inline raises94.84521; interpolated setter FPRs/scheduling change in cases2/3. Remaining Pulse/SetRGBA/interpolation FPRs/scheduling, case4 f10/f11 and commuted arithmetic. Three approaches exhausted. Color pool owned by matched Scene80172844 outside claim, singleton cannot B-split. Full fallback DOL SHA1ea30f3b1 exact; zero native gain.

## c21_u153_20261108
Source: Codex worker c21_u153_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u153 fn8019A9BC94.162964->98.0/1080B: reuse fn801ED798-style AccumulateProduct(float& value,float right,float left) for last3 matrix products96.111115; Matrix44 product plus output pointer and j/index/i declarations96.81481 restores target r5 index/r4 row/r6 output and matrix operand schedule. Trivial canonical Vec3 position member captures restore translation f0/f1 and make full matrix/copy block exact98.0. InitVec position adds EH/28B87.8; quaternion squares/products/weighted Vec3 aggregates add16B96.28889; both reverted. Remaining56 rows exclusively FPRs: axis X/Y/Z30/31/29 vs29/30/31; cos25vs29, quaternion product/constants and liftedY12vs11. Owned24B EH and dtor relocation exact; aggregate85.71429/66.66667 unchanged. Single-functionNM, no A/B/nativegain; coordinator full fallback DOL SHA1exact. All attempts build/w/attempt_*.cpp+json.

## c21_u189_20261108
Source: Codex worker c21_u189_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u189 fn_8019ADF4: scalar ForceDot boundary invariant87.533745. ForceScale(volatile Vec3*,float) with own x/y/z locals fixes all9 normalize FPR rows87.90184. ApplyHorizontalForce containing unchanged dot/reflection/impulse addition further improves88.11656,652B, EH/index100. Keep both helpers; initial scheduler/FPR homes, second/third root spill swap and remaining reflection homes persist. No flags/ranges/data changes; singleton remainsNM, full fallback-linked DOL SHA1 exact, gain0.

## c22_u78_20261109
Source: Codex worker c22_u78_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u78 PhysicsStep96.47633->96.48397: SteeringMagnitude(float) inline with double magnitude=__fabs(value); return(float)magnitude fixes exactly fabs@8019D810 and frsp@8019D814; all other primary instructions equal baseline. Global Abs double local regresses96.46488 by changing other Abs sites; caller double local changes callee-saved homes and collides conversion constant with old EH alias. New helper conversion@639 safely maps lbl806D97B0; append own @640/@641->primary etb/eti restores EH96.23288/index95. Delta all-components-before-Set96.46794 fails reloads; previous matrix CopyMatrix inline invariant96.48397. Still5212vs5240B; singleton no B cut or data pool. Honest NonMatching; full coordinator DOL SHA1ea30f3b1 exact, zero native gain.

## c22_u114_20261109
Source: Codex worker c22_u114_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u114 fn_80243464 improves99.59524->99.61905 with narrow AddOffset(value,offset) inline for x final origin addition only; x multiply stays caller-side. Ratio f1, width f2 and origin f0 now exact; 11 FPR operand rows remain: x/sourcef1 targetf2, scale/sourcef2 targetf1, unity/complement sourcef5 targetf4, factor sourcef4 targetf5. Complete840B/EH8/index12 sizes unchanged, EH100. Narrow ComplementRatio invariant; maximum-only complement ownership99.45238; x multiply-only ScaleValue99.09524; external factor and using AddOffset in scale both H4-invariant. Six hypotheses exhausted; keep H4 natural draft. No singleton/pool site, sole function prevents B. Full coordinator fallback DOL SHA1ea30f3b1 exact; zero native gain.

## c22_u116_20261109
Source: Codex worker c22_u116_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u116 fn_8019A9BC 98.0 -> 98.111115% /1080 B: SetAxisAngle takes const float* axis and captures z,y,x locally, preserving argument read semantics while changing parameter webs to locals. Target axes Z/Y/X f29/f31/f30 and pre-sin multiplies now exact, reducing residual 56->50 FPR-only rows. Named cosine local still f29 vs target f25. QuatMatrix const view with named x/y/z/w only reverses x/z reload homes at same98.111115; selective 1.0f/2.0f in QuatMatrix scores98.05556 (sin/cos external retained, avoiding older double-fold issue). Both reverted. Owned24B EH exact; extra weak dtor text unchanged; aggregate85.71429/66.66667. No A/B/native gain, coordinator full fallback DOL SHA1 exact. Attempts build/w/attempt_*.cpp+json.

## c22_u120_20261109
Source: Codex worker c22_u120_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u120 HomingMarkerUpdate fn_80172948 direct94.84521->95.595894/report95.66438 at2920B, EH8/index12 both100. SetRGBA direct pointer-based writes (separate from RGB+alpha SetScalar wrapper) recover exact RGBA setter blocks and remove27 diff rows. Value-parameter from accumulator94.58219; delta-parameter reuse89.363014/text2988/EH75 rejected; SetTransform boundary invariant94.84521. Remaining149 rows: Pulse/result, SetInterpolated FPR/schedule, case0 radius/RGB, case4 constants/old-channel exchange and commuted arithmetic. No singleton/base-pool residual; colors already owned by matched Scene80172844, one-function TU cannot B-split. Retain NM improvement, full fallback DOL SHA1ea30f3b1 exact; native gain0.

## c22_u180_20261109
Source: Codex worker c22_u180_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u180 fn8019ADF4: consumed vz reused as dot and nx*=vz/nz*=vz before reflection improves88.11656->88.17792/652B/EH-index100 (normal-x projection now target f5). Nonvolatile Vec3 locals plus existing volatile helper accessors restores initial x/y/z f4/f5/f6 but score88.11656 and prologue scheduling still wrong. Shared ForceRoot + NormalizeForce nesting recovers slots10/8/c but extra fmr/656B and normal/Newton/scale homes regress86.515335,index91.66667; reverted. No flags/ranges/data changes; full fallback DOL SHA1exact, nativegain0.

## c23_u16_20261109
Source: Codex worker c23_u16_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u16 KartPhysics_ApplyCollisionForce 801EDFEC: shape diagnostic Id_f/Mul_f/t0 scores98.73214 locally. Natural scalar snapshots regress97.65625. By-reference vector_x(const PhysicsPlainVec&) accessor and first-declared dx give98.64286 vs98.44196 baseline, same896B/EH24/index12 exact. Meaningful yaw gain helper invariant; remove it, retain ordinary multiplication. Separate double fabs then float conversion regresses98.30804. Final natural source contains no synthetic identity/multiply wrappers or redundant t0->dx. Residual angle f6->f4, gain scheduling, push X/Z f3/f5 and final subtraction FP homes/load order. Source-only NM; B unavailable; coordinator full fallback DOL SHA1 exact, native gain0.

## c23_u86_20261109
Source: Codex worker c23_u86_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u86 PhysicsStep96.48397->97.84962, primary5212->5236 versus target5240. Three-component pointer-index loops in projection Sub/Scale/Add recover all six missing normal/position reloads and raise97.70458; no extra volatile or codegen pragmas. Globalizing every vector helper lowers97.292366/5248B; integration-only loop copy/scale/add is invariant97.70458. IntegrateVelocity(float velocity) with parameter accumulator changes FP scratch homes, lowers97.35878/5236. Offset initialized from named zero then *=named scale instead of a multiplication initializer raises97.84962, fixing previous-matrix FP web. Append own @688/@689 EH/index aliases; conversion@687 maps UNDlbl806D97B0. EH96.23288/index95 unchanged. Final192->118 aligned diff rows. Remaining missing zero reload+3B0, displacement schedule+C74..D10, quantization/blend/yaw scratch and eight projection scratch rows. No singleton/pool opportunity or single-function B cut; honestNM, native gain0. Full coordinator DOL SHA1ea30f3b1 exact.

## c23_u91_20261109
Source: Codex worker c23_u91_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u91 LakituStart_UpdateCountdown improves99.947914->99.958336 at1920B/EH8/index12 all EH100. Retain float height declared before eye/at/dir, but replace dx/dy top declarations plus later assignments with const float dx=dir.x; const float dy=dir.y at capture point. X cache becomes targetf27; remaining four rows swap dyf26/heightf28 versus targetdyf28/heightf26 at8003D47C/480/508/514. Moving height to const initializer at calculation point restores old five-row X/Y swap99.947914, so declaration placement/initializer web matters. Mtx right-column99.895836 repeats aggregate Y/result conflict; scalar result with matrix99.90625; separate scoped immutable coordinate results99.864586 (Y cache targetf28 but X/height/results differ); complete basis initializer helper99.708336. All six attempted; no flags/ranges/maps/header changes; no A/B or native gain. Build/w sources/diffs retained. Existing baseline SHA1 exact; no fresh full build requested.

## c23_u97_20261109
Source: Codex worker c23_u97_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u97 HomingMarkerUpdate80172948 direct95.595894->95.79452/report95.863014,2920B/EH8/index12 exact. Pulse consumed-parameter reuse fixes all9 case1 result/setter FP rows95.65753 (distinct from earlier named-result join). Const-reference from/to inputs in Interpolate further remove12 aligned rows95.79452. Consumed Interpolate to-delta regresses91.38082/2968B/EH75, reverted. Final128 FPR/scheduling rows remain: case0 radius/RGB, case2 Pulse, interpolated setters, case3 alpha and case4 constants/old-channel/commuted arithmetic. One-function NM, no A/B or unowned pool; final coordinator fallback DOL SHA1 exact; zero native gain.

## c23_u117_20261109
Source: Codex worker c23_u117_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u117 fn_80243464 improves99.61905->99.7619 at unchanged840B/EH8/index12, EH100. Nested Complement(float value){value=1.0f-value;return value;} used only for scale complement fixes unity/complement f4 and factor f5, leaving8 rows solely x=f1/scale=f2 vs targetf2/f1. Named unity accumulator99.47619 (declaration past divide invariant); explicit maximum input retaining range invariant99.61905; factor-only product/bias reuse99.57143 fixes unity but shifts factor/resultf7 and conversion; computing scale before ratio invariant99.61905. On nested Complement draft, width-initialized x accumulator99.21429, in-place reference AddOffset99.11905; rejected. Six hypotheses plus two refinements, bestH5 retained NM. No pool/singleton site or B cut. Coordinator full fallback build exit0/DOL SHA1ea30f3b1 exact; zero nativegain. Snapshots and JSON build/w/attempt_0..6b, final.json.

## c25_u67_20261110
Source: Codex worker c25_u67_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u67 fn_80243074: nested AngleSin/AngleCos float-return helpers plus RotatedAngle(ax,az,bx,bz,angle), computing x=ax-bx and z=az-bz inside it, fixes every rotation FPR arithmetic instruction: 99.27778 -> 99.63492, same 1008B. Nested-inline-level rule changes creation order relative to vector constructor temps; coordinate locals avoid caller split-lifetime x/z ranges. Index helpers GetSegment and AdvanceIndex both sink modulo past first waypoint lookup (95.28968/95.64683). Named copy-constructor scalar locals and nested z getter are byte-invariant. Retain attempt_3; remaining 18 rows are GPR pair and projection copy. No native gain.

## c25_u120_20261110
Source: Codex worker c25_u120_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u120: fn8019ADF4 88.17792->96.04908,652B/EH8/index12 exact sizes and EH100. GC2.7 + nonvolatile caller Vec3 locals makes all entry instructions including five before stwu exact. Remove state k __restrict while retaining input __restrict: otherwise2.7 forwards impulse fields and reduces640B/81.60736. Exact alias form restores652B/96.04908. Compiler mechanism reference docs/mwcc_internals.md: CodeGen.c move_assigned_argument / Alias.c make_distinct_virtual_alias and may_alias_alias; source tree build/mweppc unavailable locally, debugger prohibited by packet. Remaining root slotsC/8 vs8/C and projection FPR/load ordering. Nested reference sqrt/normalize fixes slots but rotates FPRs94.61963; do not repeat without trace of projection and inline temp ordering. Whole fallback-linked service build SHA1ea30f3b1 exact; no native gain.

## c26_u8_20261110
Source: Codex worker c26_u8_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c26_u8 PhysicsStep 97.84962 -> 99.48855. Integration schedule recovered by snapshotting scale before old-position writes and replacing sequential Copy(prev,pos) with existing prev.Set(pos.x,pos.y,pos.z). Set arguments force all z/y/x loads before stores; ApplyDisplacement inline passes scale before the copy, removing store-to-scale-load alias predecessors (Scheduler.c selectinstruction and Alias.c may_alias_alias per mwcc_internals). Reading horizontal x/z into consumed accumulators moves x load before named multiplier. Literal zero throttle comparison restores missing reload. Primary now exact 5240B/1310 opcode sequence; owned EH/index 100 with own @696/@697 aliases. Residual96 FPR/commutative rows, no shape or stack offset difference. Compiler source build/mweppc unavailable here; no debugger attempted.
