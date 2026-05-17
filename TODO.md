# mkgp2-decomp TODO

ライブな次手リスト。完了したら check して push、新しく出てきた課題は下に追記する。

## Status (2026-05-17 commit cf84685)

- `main.dol` byte-identical rebuild: **OK** (SHA-1 `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65`)
- Named symbols: **~1080 / 7613** functions (~14%)
- Matched C source: **0 / 7613**

## Symbol seeding

- [ ] **`mkgp2docs/*.md` 79 ファイルから symbol を正規表現 scan**
  - source: `~/src/github.com/dolphin-emu/dolphin/mkgp2docs/`
  - 拾うパターン例: `Name @ 0xADDR` / `FUN_<addr> ⇒ Name` / inline コードブロック内の `0x80XXXXXX  Name`
  - noise が多いので、まず 5-10 ファイルを sample して pattern を確立してから全件回す
  - `tools/import_symbols_from_mkgp2docs.py` として書く (既存 importer と同じ collision guard を持たせる)
  - 期待: 数百〜千件追加

- [ ] **Ghidra dump にあって symbols.txt に無い 40 アドレスを explicit add**
  - 現状 `tools/import_symbols_from_ghidra.py` が `ghidra addresses not present in symbols.txt: 40` と報告している
  - 大半は BSS object (size 不明) や `.rodata` table。dtk auto-detect が拾えない
  - Ghidra から size / data_type を別途取って `add_symbol` 相当の entry を symbols.txt に挿入
  - `g_DebugPrintfEnable @0x80598a8a` / `kBgmDspFilenameTable @0x8037ce1c` (externals.txt の skip 2 件) もこのバッチで救う

- [ ] **4 件の collision 真偽確認 + 解消**
  - `LUT_Sine`: Ghidra 0x80065928 (kept) / 0x80186998 (skipped) — `decompile_function` で両者を見比べて同じ関数を別 address に inline 化したものか、別実装かを確認
  - `KartMovement_SetPosition`: 0x80057960 (kept) / 0x8019a4a0 (skipped) — 同様
  - `__DBExceptionDestination`: dtk 0x80255964 / Ghidra 0x8025591c — どちらが正本か、もう一方は何の stub か
  - `GX_SetCullMode`: dtk 0x80266DA8 / Ghidra 0x802c107c — `GX_SetCullMode` は SDK 標準関数なので 1 つだけのはず、片方は wrapper の可能性
  - 結果次第で suffix (`_inline` 等) を付けて両方残すか、片方 placeholder のままにするか判断

- [ ] **`scope` / `type` の精度向上**
  - 現状 Ghidra 名は `scope` フィールドを書いてない (dtk 既定のまま)
  - `scope:global` / `scope:local` の正しさは link 時に効くので、SDK lib 系を `scope:global` で固定する pass を後で書く

## Matching に着手

- [ ] **1 関数だけ matching を試す (proof of concept)**
  - 候補: `__check_pad3 = .init:0x80003100; size:0x40` (boot 直後の小さな関数、CW で書きやすい)
  - 手順:
    1. `build/GNLJ82/asm/.init/...s` で disasm を読む
    2. decomp.me に scratch を作る (compiler は `gc/1.3.2` または同等)
    3. C ソース起こし → byte-identical を目指す
    4. matched したら `src/init/__check_pad3.c` 等に保存
    5. `configure.py` の `config.libs` に該当 lib + object を Matching として登録
    6. `ninja` で link が通り SHA-1 verify が OK なら 1 関数進捗

- [ ] **`mw_comment_version` の再評価**
  - 現状 `config/GNLJ82/config.yml: mw_comment_version: 11` (CW for GameCube 2.7) は仮置き
  - SMG (2007) と同じく `14` (CW 3.0a3+) が本命候補
  - SDK ライブラリ関数 (`memset` / `OSReport` / `GX*` 等) を 1 つ matching に持ち込み、`.comment` セクション差分が消える `mw_version` を採用
  - 同時に `configure.py` の `compilers_tag` も妥当な mwcceppc を選ぶ

- [ ] **SDK lib (Dolphin SDK / Runtime.PPCEABI.H) の TU 構成を確立**
  - dtk-template の `Runtime.PPCEABI.H` placeholder を実物 lib に差し替え
  - `DolphinLib("OS", [...])` 等を `configure.py` に追加していく
  - 既存 decomp project (mkdd / ogws / tww) の `configure.py` を雛形として借用するのが速い

## 運用

- [ ] **mkgp2-patch との symbol sync 運用**
  - 命名の SoT は decomp 側に置く。mkgp2-patch/externals.txt は decomp の symbols.txt から再生成できる形にする
  - 逆方向 (mkgp2-patch で新たに rename → decomp に反映) も script で扱える形に
  - rename wave のたびに sync script を回す

- [ ] **GitHub Actions による CI**
  - `docs/github_actions.md` のテンプレを参考に
  - 必要なのは: Python + ninja install、main.dol を secret から復元、`configure.py && ninja` で SHA-1 verify 通過
  - main.dol は `secrets.MAIN_DOL_BASE64` のような形で安全に取り回す
  - public 化前に repo を変えるなら CI は private 用ジョブのまま

- [ ] **README に進捗バッジ / decomp.dev 連携**
  - private な間はスキップ。public 化を検討するタイミングで一緒に整備

## 中長期マイルストーン

- [ ] **5% matched** — small leaf functions と SDK 短いものを束で潰すと到達できる
- [ ] **HSD ライブラリ (`HSD_*`) を 1 TU まるごと match** — mkgp2-patch の研究成果が直接活きる領域、進捗を作りやすい
- [ ] **コース系 (`CourseScene_*`, `CourseData_*`, `clNormal3D_*`) を集中攻略** — mkgp2docs と externals.txt がほぼ揃ってる
- [ ] **AI / item / race state** — mkgp2-patch で深掘りした領域、`mkgp2docs/mkgp2_race_position_lap_system.md` 等が大量に存在
