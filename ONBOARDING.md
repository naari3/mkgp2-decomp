# mkgp2-decomp セッション kickoff

このリポジトリの作業を新しい Claude Code セッションで始めるときに、
最初のメッセージとして全文コピペできるコンテキスト集。
人間が読み直すときの index にもなる。

---

## このリポジトリは何か

Mario Kart Arcade GP2 (GNLJ82, GameCube/Triforce, 2007) の `main.dol`
を **byte-identical** に再ビルドする matching decompilation project。
C/C++ ソースから CodeWarrior でリンクして元バイナリを再現するのが
最終目標。reverse engineering 用 doc 倉庫ではない。

- 立ち上げ: 2026-05-17 (`mkgp2-patch` session から spin-off)
- target `main.dol` SHA-1: `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65`
- main.dol は **gitignore**、`orig/GNLJ82/sys/main.dol` にローカル配置

## 現状 (commit `fc85f66`)

- analyzer-only baseline OK: `python configure.py && ninja` で
  `build/GNLJ82/main.dol: OK` (SHA-1 一致) する状態
- 関数数: **7,613** / object 分割数: **3,752**
- named symbols: **~1,080 / 7,613 (~14%)**
  - `mkgp2-patch/externals.txt` 由来: 97
  - Ghidra MCP dump 由来: 974
  - dtk PPCEABI auto-detect: ~8
- matched C source: **0** (matching そのものはこれから)
- 次手は `TODO.md` を参照 (live なチェックリスト)

## 道具立て

- Python + ninja のみ依存 (venv / uv は使わない、システム Python そのまま)
- toolchain: dtk-template `95a941f` / dtk `v1.8.3` / objdiff `v3.6.1` /
  compilers tag `20251118` / linker `GC/1.3.2`
- `mw_comment_version: 11` は **仮置き**、SDK lib match で確証取り予定
  (本命候補は 14 = CW 3.0a3+)

## 関連プロジェクト

- `~/src/github.com/naari3/mkgp2-patch/` — 姉妹プロジェクト。Kamek
  パッチ + Ghidra 解析の蓄積。command/struct の研究はここに溜まる。
  symbol 命名の SoT は **decomp 側に寄せていく** 方針
- `~/src/github.com/dolphin-emu/dolphin/mkgp2docs/` — 関数アドレス /
  構造体 / HSD format 等の調査メモ 79 md。設計前に必ず参照
- `~/src/github.com/naari3/mkgp2-view/` — Dolphin プロセスの
  live memory viewer。動作確認用

## 守るルール (mkgp2-patch session から持ち越し)

1. **Ghidra MCP を触る前に `Skill(skill="mkgp2-ghidra")` を必ずロード**。
   bmp_output project (mkgp2_main.dol / segaboot_main.dol) 固有の起動手順 / domain path はこちら、汎用の Ghidra MCP 接続作法とツール選択は transitively 参照される `ghidra-mcp` skill で扱う。
   memory の Ghidra 関連ノートは skill ロード後の補助情報として参照。
2. **`list_instances` 空でも `connect_instance` を即試す**。
   socket 検出のみに依存しており TCP bridge は見落とされる既知の罠。
3. **シンボル rename は link-order neutral** = リビルド SHA-1 は
   変わらない。rename 後に SHA-1 verify が崩れたら、それは別問題
   (collision / splits.txt 破壊 等) を疑う。
4. **作業区切りでは自動 commit** (push は明示時のみ)。
5. **断定的表現を避ける** ("真の原因" "完全に" 等)、観察と仮説を
   分けて書く。実機 / SHA-1 verify で確証取れるまでは「仮説」止まり。

## 知見の保存場所

- **共有価値あり** (再現性ある観察、運用知見、回避策、確証取れた仕様)
  → repo 内 `docs/notes/` (or 相当の docs path) に commit
- **session 内 cache** (transient な作業メモ、対応中の仮説、調査途中)
  → Claude の memory (project ごとに分離保存される)

memory は project 別保存のため両 session で共有できない。共有価値ある
知見は docs 化して repo に commit すると、`mkgp2-patch` / `mkgp2-decomp`
のどちらの session からでも path 指定で参照できる。

棲み分け:

| 内容 | 場所 |
| --- | --- |
| decomp toolchain / dtk / CW 挙動の運用知見 | `mkgp2-decomp/docs/notes/` |
| Ghidra 解析の研究 notes (関数 / 構造体 / format) | `~/src/github.com/dolphin-emu/dolphin/mkgp2docs/` |
| cross-repo workflow (matching の手順、命名規約) | `~/.claude/skills/` (global skill) |

## 主要ファイル

| パス | 役割 |
| --- | --- |
| `config/GNLJ82/config.yml` | dtk 設定 (sections, mw_comment_version, hash) |
| `config/GNLJ82/symbols.txt` | 47k 行の symbol DB (committed) |
| `config/GNLJ82/splits.txt` | section-level 分割 (committed) |
| `config/GNLJ82/build.sha1` | SHA-1 verify target |
| `orig/GNLJ82/sys/main.dol` | ローカル only、gitignore |
| `tools/import_symbols_from_externals.py` | mkgp2-patch/externals.txt 流し込み |
| `tools/import_symbols_from_ghidra.py` | Ghidra dump 流し込み (collision guard 付) |
| `tools/ghidra_symbol_dump.json` | Ghidra MCP bulk export 結果 |
| `tools/_build_ghidra_dump.py` | Ghidra DB 更新時の再 dump 用中間 script |
| `TODO.md` | 次手リスト (live) |

## 進め方の標準パターン

1. 何か変えたら `python configure.py && ninja` で SHA-1 verify を必ず通す
2. 通らなくなったら直前の差分を疑う
3. 区切りごとに commit、不要な中間ファイルは `_` prefix で命名
4. mkgp2-patch との symbol 同期は import script の collision guard 経由

## skip された 4 collision (要手動診断)

| 名前 | 場所 1 (kept) | 場所 2 (skipped) |
| --- | --- | --- |
| `LUT_Sine` | Ghidra 0x80065928 | Ghidra 0x80186998 |
| `KartMovement_SetPosition` | Ghidra 0x80057960 | Ghidra 0x8019a4a0 |
| `__DBExceptionDestination` | dtk 0x80255964 | Ghidra 0x8025591c |
| `GX_SetCullMode` | dtk 0x80266DA8 | Ghidra 0x802c107c |

decompile して同一関数の inline copy なのか別実装なのかを確認する必要あり。
