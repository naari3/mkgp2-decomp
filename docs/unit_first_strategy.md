# Unit-first strategy (2026-07-19 採用)

matching の対象選定を「サイズ順 / 単発 fn つまみ食い」ではなく、
**意味のある unit (struct / class に相当するクラスタ) を 1 つ選んで完食する**
方式に切り替える。他マシン / 他セッションでも同じ判断ができるよう、
選定基準と手順をここに正本として記録する。

関連:
- `tools/plan_units.py` — unit ランキングを出す read-only レポート (本 doc の実装)
- `.claude/skills/mkgp2-orch/SKILL.md` — orchestrator の編成ルール (unit-first 節)
- `docs/per_fn_matching_strategy.md` — unit 内の難関 fn を asm_fn 退避する手順
- `docs/large_extab_group_strategy.md` — extab group >6 の扱い

## 1. なぜ unit-first か

- **元 TU 構成の復元に近づく**: original .cpp は 1 file に同 struct の method が
  まとまっていたはず。単発 fn dispatch を続けると `src/game/` に 1 fn = 1 file が
  線形に発散する (cluster-first 導入時 2026-05-18 と同じ問題意識の徹底)
- **struct layout が 1 回で確定する**: unit 内の全 method を続けて書くと field の
  意味が相互に裏取りされ、header が 1 パスで育つ
- **サイズ順の罠を避ける**: サイズ昇順で拾うと Vec3 / dtor 系のような
  「アドレス空間に散在する非 unit」に手を出して発散する (下記 §3)

## 2. unit 選定基準

`python tools/plan_units.py` でランキングを出し、以下を満たすものから選ぶ:

| 指標 | 条件 | 理由 |
|---|---|---|
| `runs` | **1** (許容 2〜3) | member が 1 連続 address range に並ぶ = 1 TU 1 split で切れる。dtk splits は連続 range が前提 |
| `frgn` (foreign) | **0** (許容 数個) | span 内の他クラスタ関数。あると TU に同居させるか split を割るかの判断が増える |
| `ex>6` | **0** | extab group >6 の member は escalation 対象 (`docs/large_extab_group_strategy.md`) |
| `exX` (extab_cross) | **0** | extab group が unit 外の fn を含む = bundle 制約が unit 境界を跨ぐ blocker |
| `medB` (pending median) | 小さいほど楽 | 立ち上がりは median の小さい unit から |

**理想形 (最初に狙う形)**: `runs=1, frgn=0, ex>6=0, exX=0`。
2026-07-19 時点でこの条件を満たす代表例: VfxSlot (17 fn / 1.7KB / 隙間ゼロ)、
Jyugemu、Tachometer、TaRecord、LapBannerScene、ServiceMenu 等。

ランキングの sort key は `plan_units.py` の `rank_key()` にある通り
(exX blocker → ex>6 → runs → foreign → median)。**どの unit を選ぶかの
最終判断はツールに入れない** — ランキングは材料で、pick は agent / 人の判断
(`docs/orchestrator_ops.md` の plan_batches.py 禁止則と同じ原則)。

## 3. unit として不成立なクラスタ (手を出さない)

prefix が同じでも address 空間に散在するものは unit ではない:

- **Vec3** — 10+ run に散在。inline 展開された別実体が各 TU に転写されている
  可能性が高く、「Vec3.c を 1 個作る」対象ではない
- **dtor 系** — 100+ run。各 struct の dtor はそれぞれの struct unit に属する
- **KartItem** — 24 run + extab >10 が多数。既に部分消化済み (matched/asm_fn)。
  残りは連続 sub-range 単位で個別判断

これらの構成 fn は、所属する本来の unit (または address 近傍の別 unit) の
batch で巻き取る。

## 4. 手順 (1 unit の完食フロー)

1. `python tools/plan_units.py` → ランキング確認
2. `python tools/plan_units.py --unit <Name>` → member 一覧・gap・extab を確認
3. Ghidra (dump / MCP / `tools/mkgp2_types.gdt`) で struct layout を確認、
   `include/game/<Name>.h` を用意
4. `src/game/<Name>.c` を 1 TU として splits.txt に 1 entry 追加
   (span 全体を 1 range で。foreign fn が居る場合はここで同居/分割を判断)
5. unit 内の fn を size 昇順に matching (setter/getter → 中物 → 大物)
6. 難関 fn は asm_fn 退避 (`docs/per_fn_matching_strategy.md`) して
   unit 完了を優先、後日 promote
7. `python configure.py && ninja build/GNLJ82/ok` で SHA-1 verify → commit
8. 次の unit へ。着手順の推奨は毎回 `plan_units.py` を引き直す
   (matched が増えるとランキングが変わる)

orchestrator 運用時は 4〜6 を batch として sub に dispatch する
(unit が大きければ「同 unit 内の連続 sub-range」で複数 batch に分割、
1 TU に複数 sub を並列で当てる場合は `mkgp2-orch/SKILL.md` の
「同 TU 内多 sub 並列 promote」パターン)。

## 4.4 Ctor/Dtor 持ち unit は C++ class 前提で組む (2026-07-19 導入)

unit の member に Ctor / Dtor / Init が居る場合、または dtk asm の extab に
DELETEPOINTER / DESTROYBASE action が見える場合、その unit は元コードが
C++ class だった可能性が高い。C + idiom で寄せず、**最初から .cpp + class
定義で組む**:

- 根拠 (2026-07-19 観測):
  - ServiceMenu_Init / SeqMenuScene_Init は C で 99%+ 到達も register/extab
    残差で asm_fn 退避。target extab の DELETEPOINTER/DESTROYBASE は
    `-Cpp_exceptions on` の C++ ctor でしか自然に出ない
  - virtual call の r12/r12 dispatch は `-lang=c++` の実 virtual でのみ再現
    (SeqMenuScene_HandleInput、Vtable_CallSlot2.cpp 先例)
  - 各 unit の Dtor は「vtable demote → dtor_8002CDF4(self, 0) →
    flag > 0 で MemoryManager_TimedFree」の CW deleting-dtor 定型 =
    共通基底 + 仮想 dtor の継承階層が存在した
- 前提作業: 共通基底 (dtor_8002CDF4 / vtable layout) を `include/game/` に
  1 回だけ class としてモデル化し全 unit で共有する。各 sub が独自定義すると
  header conflict になるので main が管理
- 注意: C++ 化で symbol が mangled 名になる場合は symbols.txt rename が要る
  (ScopedTimer 昇格 commit b8f8bf4 と同手順)
- 既存 asm_fn の .cpp retrofit 候補: ServiceMenu_Init / SeqMenuScene_Init
  (C body 保存済み、残差が register/extab のみ)
- **2026-07-19 実証済み**: ServiceMenu_Init を本物の C++ ctor として 100% match
  (asm_fn → matched 昇格)。mangled 名は llvm-objcopy --redefine-sym で既存 C 名
  に橋渡しする。手法の正本: `docs/notes/cpp-ctor-retrofit-mangled-bridge.md`

## 4.5 unit claim (GitHub issue、2026-07-19 導入)

複数人 / 複数マシンでの重複着手を防ぐため、**着手前に GitHub issue で unit を
claim する**。SoT は GitHub issues (label `unit-claim`) で、repo を clone した
誰でも `gh` CLI 経由で同じ状態が見える。

規約:
- 1 unit = 1 issue、title `[unit-claim] <Unit>`、label `unit-claim`
- **open issue = claim 中** (assignee = claim した人)。closed = 未 claim
- close の使い分け: 完食 → `--reason completed` / 途中で手放す → `--reason not planned`
  (どちらも closed = 再 claim 可能。履歴は issue に残る)

操作 (すべて `tools/claim_unit.py` 経由、gh CLI 認証済みが前提):

```
python tools/plan_units.py --claims        # ランキング + claim 状況
python tools/claim_unit.py list            # open claim 一覧
python tools/claim_unit.py claim VfxSlot   # claim (member snapshot 付き issue 作成)
python tools/claim_unit.py done VfxSlot    # 完食 close
python tools/claim_unit.py release VfxSlot # 未完了 close (手放す)
```

フロー: `plan_units.py --claims` で未 claim の理想形 unit を選ぶ → `claim` →
§4 の完食フロー → merge / push 後に `done`。長期停滞したら `release` して手放す。

ツールがやるのは実在検証 (symbols.txt に prefix がある / pending が残ってる) と
二重 claim 防止のみ。**どれを claim するかの判断は人 / agent**。
issue を手で立てても title / label の規約さえ守れば同じに扱われる。

注意 (2026-07-19 の e2e テスト #2 で観察): `gh issue list` の反映は
create / close から数秒遅れることがある。claim 直後に `list` に出なくても
issue URL が返っていれば claim は成立している。二重 claim 検出も同様に
数秒窓のラグがあるが、unit 単位の作業粒度 (時間オーダー) では実害なし。

## 5. 他マシンでの再現に必要なもの

repo tracked (clone すれば揃う):
- 本 doc + `tools/plan_units.py` + `tools/claim_unit.py` + `.claude/skills/*` (プロジェクト skill として自動ロード)
- `config/GNLJ82/symbols.txt` / `splits.txt` / `configure.py` (SoT)
- `tools/ghidra_symbol_dump.json` / `tools/mkgp2_types.gdt`

ローカルで別途必要:
- `orig/GNLJ82/sys/main.dol` (gitignore、手渡し。SHA-1 `ea30f3b1...`)
- claim 操作には gh CLI (`gh auth login` 済み、repo への write 権限)
- extab 列を出すには 1 度 build して
  `python tools/build_extab_map.py` (→ `.orchestrator/extab_groups.json`)
- struct の live な詳細が要る場合のみ Ghidra + MCP (`bmp_output` project)

## 6. 経緯 (時系列ログ)

- 2026-05-18: cluster-first 既定を導入 (単発 fn dispatch のファイル発散対策)
- 2026-07-19: サイズ順のつまみ食いを続けた結果、散在系 (Vec3/dtor/KartItem) に
  手が伸びかける問題をユーザーが指摘。「意味のある unit を 1 つ選んで完食」に
  方針を明確化。連続性 (runs) / 異物 (foreign) / extab 閉包 (exX) を選定基準に
  採用し、`tools/plan_units.py` として固定。初回検証で VfxSlot が理想形
  (17 fn 完全連続・異物ゼロ・extab 内部完結) であることを確認
- 2026-07-19: 複数人 / 複数マシン運用を見据え、GitHub issue (label `unit-claim`)
  による unit claim 機構を導入 (§4.5、`tools/claim_unit.py`)
- 2026-07-19: 初の unit 完食 = ItemTracker (claim #4、4/4 全関数 1 試行 100%)。
  隣接 singleton extab group 群は `-Cpp_exceptions on` の auto-emit で
  extab/extabindex 込み 1 TU 再現できることを確認 (ISESlot_Update と同パターン)。
  理想形 unit (runs=1/frgn=0/extab 閉包) は手戻りなく完食できる、という
  選定基準の妥当性を裏付ける初観測
