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
