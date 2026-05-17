# `.init` section は CodeWarrior for GameCube 1.0 で compile されている

`main.dol` の `.init` section (0x80003100..0x80005600、boot 9.5 KB) の関数は
**CW for GameCube 1.0** が出す prologue 形式に一致する。`configure.py` の
`init` lib に `mw_version = "GC/1.0"` を設定すると byte-identical で matching
する。

## 観察 (commit `9c4efa9`, 2026-05-17)

`__check_pad3` (`.init:0x80003100`, size 0x40) を matching したときの確認:

元 binary の prologue:

```
mflr  r0
lis   r3, 0x8000
stw   r0, 0x4(r1)        ; lr を caller frame に置く
stwu  r1, -0x8(r1)       ; その後 stack を 8 bytes 切る
```

これは CW for GameCube 1.0 の出力形式。

新しい CW (1.3.2 / 2.x / 3.0a3) は逆順:

```
stwu  r1, -F(r1)         ; 先に stack frame を確保 (F は通常 0x10+)
mflr  r0
stw   r0, F+4(r1)
```

`GC/1.0` で compile した結果が元 binary と byte-identical。新しい CW は
frame size も大きく取る (典型的に 0x10+)、`.init` の `__check_pad3` は
0x08 frame で済んでいるので CW 1.0 確度が高い。

## 影響と未確定範囲

mkgp2 (2007) の開発は `.init` の boot code を古い CW で書き、その既存
object を引き続き使っていた、と推測している (確証なし、可能性)。

- `.init` section (boot コード): CW 1.0 (`__check_pad3` の 1 件で確認)
- `.text` ゲーム本体・SDK lib: 未確定
- project config の `mw_comment_version: 11` (= CW 2.7) は **仮置きのまま**

`.text` 本体は別 version で試す必要があり、最終決定は SDK lib match まで
保留。

## 対処指針

- `.init` の関数を matching するときは `configure.py` の lib entry で
  `mw_version: "GC/1.0"` を使う
- `config.linker_version = "GC/1.3.2"` はそのまま (linker は別、最新で OK)
- `.text` 関数の matching に着手するときは、prologue 形式を上記の比較で
  確認してから `mw_version` を選ぶ

## 関連

- [`TODO.md`](../../TODO.md) の「`mw_comment_version` の再評価」タスク
- [`dtk-ppceabi-overrides-symbols.md`](dtk-ppceabi-overrides-symbols.md)
  — SDK runtime 関数の heuristic 検出も CW version によって prologue 形式が
  変わる可能性
