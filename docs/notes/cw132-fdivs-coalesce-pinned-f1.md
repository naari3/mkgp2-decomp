# CW 1.3.2 FP colorer: 死ぬ divisor を return-pinned f1 へ「in-place 除算」で寄せる

対象: `CarObject_CalcSpeedRatio` (OnKartHit TU, 0x8004EFFC, 17 命令 leaf)。
2026-06-12 に byte-identical promote 達成 (`build/GNLJ82/main.dol: OK`)。
allocator 白箱化 (FP colorer trace) で source lever を導出した記録。

観察 (事実) と仮説 (推論) を分ける。

---

## 1. 症状: 構造 100% 一致、FP register 番号だけ違う (観察)

ターゲット:
```
lfs f2, 0xc(r3)        ; speed
...
lfs f1, 0x8(r3)        ; divisor (refSpeed)
fdivs f1, f2, f1       ; ratio = speed / divisor   <- divisor(f1) と result(f1) が同一 reg
fcmpo cr0, f1, f0      ; ratio vs K1(f0)
blelr; fmr f1, f0; blr
```

素朴な C (`ratio = speed / mv->table[idx].refSpeed; clamp; return`) は**命令列が完全一致**するが
FP register 割当だけ違う (`tmp/getcur/ratio.py`):
- clamp-assign 形 (`r=K1;return r`): result=f1 だが divisor が**別 reg** → `fdivs f1,f3,f0` (4 reg, speed=f3)
- ternary 形 (`r>K1?K1:r`): divisor を result に寄せるが**非 pinned f0** → `fdivs f0,f2,f0`、K1 が f1

ターゲットは divisor を **return-pinned f1** に寄せる。これがどの素朴形でも出ない。

## 2. FP colorer の白箱化 (観察)

mwcceppc_132.exe (Ghidra: bmp_output `/mwcceppc_132.exe`)。register colorer:
- class 番号: `DAT_005e931f`。**GPR=4, FP=3** (`tmp_probe/probe_color_all.js` で同定)。
- web id 範囲 `[DAT_005e8778[c], DAT_005e8a7c[c])`、node = `*(DAT_005e87d0 + id*4)`。
  node layout: `+0x12 initDeg(s16) +0x14 color(s16) +0x16 flags(u16) +0x18 nbCnt(s16)`。flags 0x4 = pinned。
- **select/color = FUN_00507a30**。decompile したロジック:
  - 各 web について `avail = 全 reg mask`、interfere する**着色済み neighbor の色を avail から除く**
  - `avail != 0` なら **最小の空き color を割当** (lowest-available)
  - simplify (FUN_00507b50) の push 逆順で着色 (低 degree が先 push → 後着色)

## 3. ブロックの機構 (観察 → 仮説)

clamp 形を trace (`ratio_clamp.c` + `probe_color_all.js`、FP class 3):
- divisor web (initDeg=0、最低 degree → **最後に着色**) が **f0** を取る。
- 理由: divisor は **result web (pinned f1) と interfere** するため avail から f1 が除かれ、最小の空き = f0。
- ターゲットでは divisor が f1。つまり divisor と result が **interfere しない (= 同一 web)** 必要がある。

fdivs は 3-operand で copy ではないので、divisor と result が別 web のままだと colorer は両者を
別レジスタにする (interfere)。**両者を同一 web にするには、divisor を result 変数に load して
in-place で除算する**しかない。

## 4. レバー: in-place 除算 (観察、byte-identical)

```c
float ratio = mv->table[mv->tableIdx].refSpeed;  /* divisor を return 変数 ratio に load */
ratio = speed / ratio;                           /* in-place: ratio = speed / ratio */
if (ratio > K1) ratio = K1;
return ratio;
```

`ratio` の web = {divisor-load, fdivs-result, clamp, return} の単一 web で、return-pinned f1。
→ `fdivs f1, f2, f1` (divisor=result=f1)。**EXACT 一致** (`tmp/getcur/ratio.py` in-place 各形)。

素朴形 (`r = speed / divisor_expr` や `float d=...; r=s/d`) は divisor が別 web になり f0 へ。
**「除算の右辺を、結果を入れる変数自身にする」**のが鍵。

採用形を `src/game/auto_ONKARTHIT_block.c` の `CarObject_CalcSpeedRatio` に適用、
`build/GNLJ82/main.dol: OK` (byte-identical)。

## 5. 一般化

「死ぬ被演算子 (divisor/減数/etc) を pinned register web に寄せたい」family:
- 該当被演算子を**結果変数に先 load し、in-place 演算** (`r = b; r = a OP r;`) すると、
  被演算子 web と result web が単一化し、colorer が両者を同色 (= result の pinned reg) にする。
- 別 temp / 部分式のままだと別 web になり、colorer は最小空き reg を割当てて pinned reg を避ける。

probe 資産: `tmp/getcur/ratio.py` (sweep)、`tmp_probe/ratio_clamp.c` + `probe_color_all.js` (colorer trace)。
colorer: FUN_00507a30 (select/lowest-available)、FUN_00507b50 (simplify)、class FP=3 GPR=4。
