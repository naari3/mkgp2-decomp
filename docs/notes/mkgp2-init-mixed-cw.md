# `.init` section は CodeWarrior の複数 version で混在 compile されている

`main.dol` の `.init` section (0x80003100..0x80005600、boot 9.5 KB) の関数は
**1 つの CW version で揃っていない**。当初 `__check_pad3` 1 件で「.init = CW 1.0」
と結論付けたが、後続の matching で他の .init 関数は **CW for GameCube 2.7**
の prologue 形に一致することが判明した。section 単位ではなく **TU 単位** で
CW version が違う。

## 確認済みの内訳 (2026-05-17 commit `c6c9df4` 時点)

| 関数 | address | size | CW version | lib |
|---|---|---|---|---|
| `__check_pad3` | 0x80003100 | 0x40 | **GC/1.0** | `init` |
| `__init_hardware` | 0x80003400 | 0x24 | **GC/2.7** (asm) | `init_sdk` |
| `__flush_cache` | 0x80003424 | 0x34 | **GC/2.7** (asm) | `init_sdk` |
| `fn_80003458` | 0x80003458 | 0x30 | **GC/2.7** | `init_sdk` |
| `fn_80003488` | 0x80003488 | 0x24 | **GC/2.7** | `init_sdk` |
| `fn_800053E0` | 0x800053E0 | 0x2C | **GC/2.7** | `init_sdk` |
| `memset` | 0x8000540C | 0x30 | **GC/2.7** | `init_sdk` |
| `__fill_mem` | 0x8000543C | 0xB8 | **GC/2.7** | `init_sdk` |
| `memcpy` | 0x800054F4 | 0x50 | **GC/2.7** | `init_sdk` |

`__check_pad3` だけが CW 1.0、残る .init 関数 (8 件) は CW 2.7 で byte-identical。
`configure.py` では `init` lib (GC/1.0) と `init_sdk` lib (GC/2.7) を分けて管理する
構成にしてある。

## prologue 形での見分け方

CW 1.0 (`__check_pad3` 形):

```
mflr  r0
lis   r3, 0x8000
stw   r0, 0x4(r1)        ; lr を caller frame の lr-save slot に置く
stwu  r1, -0x8(r1)       ; その後 stack を確保
```

CW 2.7 / 1.2.5n / 1.3.2 等 (memset 等の形):

```
stwu  r1, -F(r1)         ; 先に stack frame 確保 (F は 0x10+)
mflr  r0
stw   r0, F+4(r1)        ; lr を caller frame の lr-save slot に store
```

prologue の最初の 2 命令が `mflr; stw r0, 0x4(r1)` なら CW 1.0、
`stwu r1, -F(r1); mflr r0` なら CW 1.2.5n 以降。

`fn_80003488` / `fn_800053E0` のように **stack frame を持たない leaf** だと
prologue だけでは見分けがつかない。その場合は周辺関数 (同じ TU と推定される
もの) の prologue 形を見て CW version を決める。

CW 1.2.5n と GC/2.7 の見分け: 同じ stwu-first 形だが、register 配分 / inline 展開
の細部が違う。一致しなければもう片方を試す。mkgp2 の .init 残り 8 件は GC/2.7
で揃った。

## なぜ複数 CW が混在しているか (仮説)

mkgp2 (2007) の開発が、Dolphin SDK の既存 object (古い CW でビルド済み) と、
プロジェクト時点の CW (新しい) でビルドした game / SDK 拡張 object を **混在
link** している、と推測している。具体的に:

- `__check_pad3`: 古い Dolphin SDK 由来 (CW 1.0 でビルドされた `__start.c` 等)
  の object をそのまま再利用していた可能性
- それ以外の .init 関数: mkgp2 プロジェクト側で再ビルド or 拡張した SDK 部分
  (CW 2.7 で出した) を `.init` セクションに配置

確証はない。`.text` 本体や他の SDK lib も同じ要領で複数 CW が混在している
可能性が高い。

## 対処指針

- 新しい関数を matching するときは、prologue 形を見て CW version を選ぶ。
  「section 名 → CW」の単純対応にはしない
- 既に同じ TU と分かっている関数の CW がはっきりしているなら、同 TU の他関数
  も同じ CW で試す (TU 単位で揃うのは通例)
- `configure.py` では section ではなく **想定 TU 単位で lib を分ける**。
  既に `init` / `init_sdk` / `sysdolphin` / `Runtime.PPCEABI.H` で実例あり
- `config.linker_version = "GC/1.3.2"` はそのまま (linker は最新で OK)
- `mw_comment_version: 11` (= CW 2.7) は `.comment` section の差分が出る lib で
  再評価する。現状は仮置き

## 関連

- [`TODO.md`](../../TODO.md) の「`mw_comment_version` の再評価」タスク
- [`dtk-ppceabi-overrides-symbols.md`](dtk-ppceabi-overrides-symbols.md)
  — SDK runtime 関数の heuristic 検出も CW version によって prologue 形式が
  変わる可能性
- skill `mkgp2-match` の「mkgp2 で確認済みの compiler version」一覧
