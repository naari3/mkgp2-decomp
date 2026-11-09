# Permuter shard 1 (2026-11-07) leftovers

Permuter (autosweep, shard 1/4): round 1 (22 fns, score<=40, 5 min) and round 2
(4 fns, score 41..150, 10 min): no matches. Hand work afterwards:

- fn_80291134 (triforce/amsrv_nm1): 82 -> 8 with `#pragma opt_common_subs off`
  around the fn (like its sibling fn_8029121C) + spelled-out reply block
  (`u32 fl; ... fl = BSWAP16(req->flags) | 0x8000; rsp->flags = BSWAP16(fl);`).
  Left: r4/r6 swap for req->result vs req->arg[0] loads. File: amsrv_nm1_fn_80291134_score8.c
- fn_801934F4 (game/clsound): 38 -> 34 by moving `row = 0;` above the `if`.
  Target has `mr r30, r29` (i = row copy, not li) and computes `id` before
  `mr r4, r31`. File: fn_801934F4_score34.c
- fn_8020A6CC (anon_80209FA4_nm2, Tween::Value): 16 -> 15 (`value = from; value += ...`).
  Writing it as `float Tween::Value()` member (rename exists) fixes the int part
  (lha r4 / extsh. r0,r4) but loses the hoisted `lha a` load (34). Target ends
  `fmadds f0 ...; fmr f1, f0`.
- acAccept (acsocket_nm5): permuter 96 -> 23 only via uninitialised-variable UB, rejected.
  Target computes `addi r28,r4,0 ; addi r29,r4,4 ; add r28,b,r28 ; add r29,b,r29`
  (bufOff+0 and bufOff+4 first, then add bufAddr). Compiler switch does not help.

sc.py SRC OBJ FN [-d]: one-shot cperm score/diff (CC_=2.6 env overrides compiler).
var2.py SRC OBJ FN VARIANTS: block 0 = original snippet, other blocks replace it.

## Update 15:55 (thread stopped by coordinator)
- acAccept: 96 -> 45 by hand (acsocket_nm5_acAccept_score45.c): `GetSocketBuffer(0,&lenOff)` /
  `(u32)&d->len` style fixes the whole prologue regalloc. Still missing the unfolded
  `addi r28, bufOff, 0` + `add off, bufAddr, off` (same open problem as acsocket nm2/nm3/nm4,
  see r6-status memory). Guess worth trying: offsets produced by a fully unrolled 2-iteration loop.
- psweep.py LIST...: wraps each candidate fn in `#pragma push / <X> / pop` for 15 pragmas and
  scores. Partial run (15/106 fns, psweep_partial.out): no improvement. Slow on big TUs.
- No claims were opened by this thread; nothing pushed.
