# Permuter shard 2: leftover notes (2026-11-07)

Landed: f36235a (RaceScene_FrameUpdate linked). postprocess_sdata2.py exports owned .sdata2 literals by name, with one definition per name.

## acsocket nm2..nm5: the `addi rX, bufOff, 0` residue (acModifyMyIPaddr, acInetAddr, acConnect, acBind, acAccept)
Target: `lwz r0,bufAddr(k); lwz r5,bufOff(State); ...; addi r24,r5,0; mr r3,buf; add r24,r0,r24`.
acAccept shows the pattern most clearly: `addi r28,r4,0` and `addi r29,r4,4` first, then `add r28,b,r28` and `add r29,b,r29`.
So the original keeps (bufOff + c) as one op and only then adds bufAddr.

- `addrOff = (u32)&((u8*)b + 4)[State.bufOff];` (b = k->bufAddr) gives the target +4 form exactly. acAccept goes 89.5 -> 96.2%.
- In acConnect, an s32 local n = 0 with `*off = State.bufOff + n; buf = Buf + n; *off = k->bufAddr + *off;` fixes the lis/lwz register order (96.72%). The +0 copy is still folded.
- These did NOT keep the +0: opt_propagation/lifetimes/dead_assignments/common_subs off, optimization_level, -O1..-O3 (R2: -O2 matches registers in nm2 but not the copy), -inline deferred/all, GC 1.3..2.7 (1.2.5n is much worse), offsetof/struct member 0, (buf - Buf), an address-taken cursor, an inline returning bufOff + n, non-inline static helpers.
- `(u8)`/`(u16)` casts put a clrlwi in that slot (permuter best, score 4). It is wrong; don't use it.

## Others
- AI_CalcTargetSpeed_PairTracking 99.47%: pure regalloc. The permuter got 34 -> 14 (best in /tmp, lost). Decl order and all GC versions change nothing.
- fn_80204218 (anon_80203EA0_nm2) 98.4%: the target has an extra stack slot (Erase result at 0x10, it at 0x14); ours merges them. Tried Remove()/RemoveTask/temp variants, and the permuter ran 20 min (score 11). Unsolved.
- fn_801F894C: `addi r3, r31, 0` for the offset-0 member of lbl_803BEDC0. The .rodata is owned by fn_801F7604.cpp, so it needs a TU merge across claimed fn_801F7604/8404/8728/8A34.
