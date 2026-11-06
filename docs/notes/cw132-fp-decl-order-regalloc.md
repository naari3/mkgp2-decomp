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

c15_a44: clFlowItemSelect_Update 801CBD58 (940 B) native exact under unchanged GC/1.3.2 flags. if (++self->intro >= 9) avoids an extra reload versus increment then separate compare. Declare alpha before y to obtain y=f1/alpha=f0. Separate animation-loop cursor gets r28 while shared cursor used r31. Existing TU anonymous-symbol rename behavior collided with literal IDs (@77 float210 mapped to lbl_806CFE18 and @80 decrement mapped to lbl_806D9DB0); named external float labels avoid collisions without editing rename keys. Compiler-emitted conversion double is postprocessed to lbl_806D9DC8. Owned text/EH/index 100 and source-linked full SHA1 OK. History had only extracted asm and relocation repair, with no explicit reason for prior C parking.

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
