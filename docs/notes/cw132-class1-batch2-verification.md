# Class-1 recipe: batch-2 verification (2026-06-11, batch_promote_phase1_class1batch2)

- CarObject_OnItemHit 0x8004AA14 (mask 0x40ULL, hi=0): recipe byte-exact on first build; fn matched 100% / SHA OK. 3rd consecutive u64-family confirmation.
- KartItem_ApplyImpactImpulseAndRumble 0x8004B7D4 (mask 0x10000000ULL, hi=0): NEW CSE-reuse sub-shape - the same mask is first consumed by a direct branch test (`if ((f & M) == 0 || (u8)mode == 0)`) and the class-1 site sits in the else arm re-testing the SAME mask. CW CSEs the and-halves; the recipe site emits only xor; or.; bne L1; b L2; L1: li rZ,1; L2: reusing the first test's partials. Recipe transfers (verified inside an 83.66% park; residual at the site is a bus/zero scratch-reg naming swap belonging to the fn's class-2 cascade).

## OnItemHit win ledger (new, byte-exact)

- switch-on-call-result {0,2,default} lowering: source case order must equal MEMORY order - `case 2: return 0;` listed BEFORE `case 0:` lands the return-0 body at the binary-search fallthrough (pivot cmpwi 1 / cmpwi 3 / cmpwi 0 tree).
- case-disjoint webs want FRESH local names: the second switch arm's secondary/run18 webs only landed on target r25/r24 as new sec2/id2 locals declared between mediaReq and tbl; reusing the case-0 sec name pinned the web to r29.
- `(unsigned char)(x > 0) == 1` reproduces neg/andc/srwi+cmplwi and `(unsigned char)(x >= 0) == 1` reproduces srwi/xori+cmplwi (value-context branchless bool then compare-to-1), both first try.

## ApplyImpactImpulse salvage ledger (inside 83.66% park)

- volatile scratch struct {sqB,sqA,sqD,tA[3],tB[3],d[3],m[16]} @ sp+0x8: all slots + store order + double-overwrite blocks + THREE in-place sqrtf slots reproduce; in-place sqrtf works with a volatile struct MEMBER as the y slot (`s.sqD = (float)(x*guess); x = s.sqD;`).
- anti-fmadds applies to mag-squared sums over plain locals: explicit product temps (or in-place `v0 = c0 * v0;`) required; parenthesized sum fuses.
- fp decl-order mapping scales to ~17 named floats (block C/E registers f2..f13 all matched via decl order).
- NEW unresolved micro-classes: (1) bus/zero scratch pair swap (li r4,0 + bus=r5 vs target li r5,0 + bus=r4; stmt order + decl probes negative x2); (2) rumble/dist copy coalesce - target keeps fsubs f1; fmr f31,f1; fcmpo f1, CW coalesces into f31 (no handle found; 2 sites x 3 lines).
