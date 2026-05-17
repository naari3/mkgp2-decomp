# mkgp2-decomp TODO

ライブな次手リスト。完了したら check して push、新しく出てきた課題は下に追記する。

## Status (2026-05-17 commit d8fa749)

- `main.dol` byte-identical rebuild: **OK** (SHA-1 `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65`)
- Named symbols: **~1221 / 7613** functions (~16.0%) + 17 named data/BSS objects
- Matched C source: **0 / 7613**

## Symbol seeding

- [x] **`mkgp2docs/*.md` から symbol を正規表現 scan** — 80 md / 124 件 rename (commit `e02be5e`)
  - `tools/import_symbols_from_mkgp2docs.py` で markdown table と inline `Name (0xADDR)` の両方を拾う
  - 1681 raw mentions → 923 unique (addr→name) → 124 が placeholder を上書き
  - 既存命名と一致した 645 件、placeholder 以外で kept 56 件、cross-source collision 7 件
  - **未消化の 91 アドレス**は下の orphan add task に統合

- [~] **Orphan address を symbols.txt に explicit add (17 / 127 完了、残り 110 件)**
  - **正攻法判明**: dtk の `detect_objects:true` で自動形成された大 blob (`lbl_XXXX size:0x1CC` 等) の中に named subset を入れたいときは、enclosing placeholder blob を「head lbl + named entry + tail lbl」に分割する。`tools/add_orphan_symbols.py` がそれを自動でやる。
  - 完了:
    - commit `12d2870`: kCup0LineBinTable / kBgmDspFilenameTable / kAILapBonusRules_NonRaceCommon / RaceCourse / RaceFallback / g_ammbSocketState (6 件)
    - commit `3631d0a`: kAILapBonusRuleTable_NonRace + g_frameUnlockThresholds_{Partial,Full} + g_tierTextureIdTable + g_DebugPrintfEnable + g_jvsDebounceEnable + g_displayOffsetY/X + g_syncedSceneState + g_playerWinsPrev/LossesPrev (11 件)
  - 残り:
    - **A 残 9 件**: `kRawGameMap_*` (Game0/Raw1/...) は enclosing `kRawGameMap_Raw0` (size 0x28 の array-base name) の subset。base name を細分化するかは struct 定義との兼ね合いで matching 着手時に判断。
    - **B 残 12 件**: `g_jvsSteeringRaw/Accel/Brake` (enclosing `g_jvsOperatorBits`)、`g_playerWins/Losses/CurrentTitleId/LastSelectedTier` (enclosing `g_playerData`)、`g_raceCurrentSpeakerAux/Flag` (enclosing `g_raceCurrentSpeakerId`)、`g_voiceWeightTable` (enclosing `g_voicePlayCountTable`)、`g_OSMachineCheckDMAHandler` (enclosing `__OSErrorTable`)、`g_DefaultThread` (no enclosing)。全部 named enclosing で意味付き → struct 定義として処理する方が筋。
    - **C ~35 件**: mkgp2docs にあるが Ghidra で symbol 化されていない address。size 不明で add 不能。matching 過程で symbol 化が進めば再評価。
    - **D 4 件**: thunk_FUN_* (Ghidra default 名)。skip。
    - **E ~10 件**: LAB_*/DAT_* default 名。mid-function jump や placeholder data。skip。
    - **F 6 件**: 0x84/88/89_xxxx MMIO アドレス (Media Board DMA)、main.dol section 外。書く場所が無い、skip。

- [ ] **mkgp2docs importer の intra-dump dup を精査**
  - 現状 113 件の name dup / 109 件の addr conflict が skip されている
  - variant 名 (`NORMAL`/`GOLD`/`ORIGINAL`/`ENHANCED`) や `vtable`/`block` のような generic 語が table cell から誤抽出 → reserved list に追加でほぼ救える
  - 真っ当な dup (例: `KartMovement_Init` が 2 アドレスにある) は inline copy / 名前再利用なので別途調査

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
