# dtk PPCEABI heuristic が SDK 標準名を symbols.txt 上書きする

dtk-decomp-toolkit の `dol split` ステップは PPCEABI heuristic を走らせて、SDK
runtime 関数 (`memset` / `OSPanic` / `__DBExceptionDestination` / `GX_*` 等)
を prologue signature で認識し、canonical SDK name を自動で適用する。

`symbols_known: false` (`config/GNLJ82/config.yml` の現状) のとき、この自動
適用は `symbols.txt` の override と **共存** または **優先** する挙動が
観察されている。

## 観察 (commit `ef9b456`, 2026-05-17)

`__DBExceptionDestination` を dtk が heuristic で割り当てた 0x80255964 から
Ghidra が同定した body の 0x8025591C に動かそうとした結果:

```
### build\compilers\GC\1.3.2\mwldeppc.exe Linker Error:
#   multiply-defined: '__DBExceptionDestination' in auto_03_80255964_text.o
#   Previously defined in auto_03_802557B4_text.o
```

dtk は symbols.txt の override (0x8025591C) を honor した上に、heuristic で
0x80255964 にも `__DBExceptionDestination` を再適用し、両 split object で
global export して衝突した。

## 影響範囲

PPCEABI heuristic が拾う **SDK runtime / standard 名前** に限定される。
2026-05-17 の 4-pair collision audit (`LUT_Sine` / `KartMovement_SetPosition`
/ `GX_SetCullMode` / `__DBExceptionDestination`) のうち、前 3 つは dtk
auto-detect 由来 **ではない** ので普通に Ghidra 側 rename + import 経路で
解消できた。dtk PPCEABI 認識される SDK 名だけがこの罠に該当する。

## 対処指針

- **dtk が auto-detect した SDK 標準名は別 address に動かさない**。Ghidra
  側で同名を持っている body の方を non-SDK 名にリネームする方が早い。
- `symbols_known: true` に切り替えれば dtk heuristic は無効化されるが、
  逆に他の symbol 自動検出も止まる。matching が一定進むまでは触らない。
- 実質的には、SDK lib TU を matching に持ち込んだ時点で linker が
  resolve するので、それまで collision は放置で良い。

## 関連

- [`TODO.md`](../../TODO.md) の collision 真偽確認タスク
- [`mkgp2-init-uses-cw-1.0.md`](mkgp2-init-uses-cw-1.0.md) — CW 別 version
  への対応もこの heuristic と関連する可能性 (未確認)
