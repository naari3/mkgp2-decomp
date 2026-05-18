# CW 1.3.2 bool intermediate + `== 1` compare idiom

`Profiler_RecordFrame` (0x80039CF4) で発見。`if (cond) return;` 直書きでは `bltlr` で短絡するが、`bool oob; if (cond) oob=1; else oob=0; if (oob == 1) return;` の 3-step form で `clrlwi + cmplwi 0x1 + beqlr` の正規化形を出す。

## C → CW pattern

```c
unsigned char oob;
if (slot < 0 || slot >= 0x30) oob = 1;
else oob = 0;
if (oob == 1) return;
```

CW 1.3.2 出力:

```
cmpwi r3, 0; blt L_oob       ; bool short-circuit OR
cmpwi r3, 0x30; blt L_valid
L_oob:  li r0, 1; b L_check
L_valid: li r0, 0
L_check: clrlwi r0, r0, 24; cmplwi r0, 0x1; beqlr
```

## 重要点

- `if (oob)` は `clrlwi. r0,r0,24; bnelr` の 2 命令短縮形になる (不可)
- `if (oob != 0)` 同上
- `if (oob == 1)` だけが 3 命令展開 (`clrlwi + cmplwi + beqlr`) を出す
- §16.9 の bool→int の裏返し: 引数 bool は int に倒して clrlwi を避けるが、ローカル u8 では `== 1` 等値で 3 命令展開を引き出す

## fadds operand 順 (副次的知見)

`a = a + b` vs `a += b` は CW 1.3.2 で **operand 順が flip する** (float の場合):

- `g_table[i] = g_table[i] + v;` → `fadds f0, f1, f0` (RHS-LHS 順)
- `g_table[i] += v;` → `fadds f0, f0, f1` (LHS-RHS 順)

integer 版 §16.5 と結論が逆 (integer は intermediate local が必要、float は `+=` で十分)。
