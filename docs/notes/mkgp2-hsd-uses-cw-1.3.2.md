# mkgp2 HSD (sysdolphin) lib は CW for GameCube 1.3.2 で compile されている

Confirmed against `HSD_JObjReqAnimByFlags` (commit `c5da28e`).

## 観察

元 binary の `HSD_JObjReqAnimByFlags @ 0x802CDAF8 size 0x88` の prologue:

```
stwu r1, -0x20(r1)   # stwu first, 32-byte frame
mflr r0
stw r0, 0x24(r1)     # lr at +0x24 (= frame_size + 4)
stfd f31, 0x18(r1)
```

これは新しい CW pattern。`__check_pad3` (init lib) の古い CW 1.0 pattern (mflr first / lr@+0x4 / 8-byte frame) とは別系統。

試した compiler 一覧:

| mw_version | Frame | Prologue order | LR offset | 結果 |
|---|---|---|---|---|
| GC/1.2.5n | 0x28 | mflr first | +0x4 | ✗ 古い pattern を出す |
| GC/1.3.2 | 0x20 | stwu first | +0x24 | ✓ 一致 |

SSBM の sysdolphin lib は `GC/1.2.5n` (`doldecomp/melee/configure.py` の SysdolphinLib helper) を使うが、mkgp2 では同じ HSD HAL library なのに **CW version が違う**。理由は推測しか言えない:

- mkgp2 の dev は SSBM の HSD source を持ち込んで、自分達の build env (CW 1.3.2 系) で再 compile した
- HAL 由来の pre-built lib ではなく、ソースから新規 compile しているため SSBM の object とは別物

## 注意点

- `mw_version_hsd = "GC/1.3.2"` を configure.py で固定する
- GC/1.3, GC/1.3.2, GC/1.3.2r の細かな違いは 1 関数だけでは断定できない。今後関数を増やして `.comment` section 差分が消えるかで詰める

## 副次的な学び: 中間変数を flatten しない

SSBM source の:

```c
if (jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE)) {
    has_dobj = 0;
} else {
    has_dobj = 1;
}
if (has_dobj) {
    HSD_DObjReqAnimAllByFlags(jobj->dobj, frame, flags);
}
```

を `if (!(jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE))) HSD_DObjReqAnimAllByFlags(...);` に flatten すると、mwcceppc が `andi. / bne` の短い branch を出して 2 instruction 短くなり、byte-identical を失う。元 binary は `andi. / cntlzw / srwi. / beq` の boolean 化を出している、 = SSBM の中間変数経由の表現が compile されたことを示唆。

教訓: HSD のような他 decomp project から source を借用するときは **SSBM 源の冗長な書き方をそのまま残す**。中間変数の elision は compiler 出力を変える。
