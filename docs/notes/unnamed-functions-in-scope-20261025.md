# placeholder 名関数を pending に含める (2026-10-25)

時系列ログ。観測 (事実) と仮説 (推論) を分けて書く。

## 2026-10-25 変更前の観測

- `tools/init_orchestrator.py` の `derive_status()` が `has_named_symbol=false`
  (`fn_*` 等の placeholder 名) を `excluded` にしていた。導入は orchestrator
  scaffolding commit `4796b89` (2026-05-17)。excluded にする理由の記述は
  docs/commit message に見当たらなかった
- `.orchestrator/state.json` (2026-10-24 sync) の内訳:
  excluded 4570 / pending 1789 / matched 1062 / nonmatching 104 / asm_fn 79
- excluded のコード量は 1,636,368 B。`report.json` の total_code 2,879,600 B の約 57%
- サイズ分布は pending と excluded でほぼ同じ (中央値 156 B / 160 B)
- extab group に属する pending 1069 fn のうち 772 fn は、excluded を含む group に居た。
  excluded を含む group で matched になった関数は 1、含まない group では 158
- `plan_units.py` は placeholder を unit member にしないため、placeholder は
  named unit の `foreign` / `exX` (extab_cross) に計上されていた

## 仮説 (変更前)

- excluded のままだと、named pending を全部消化しても到達上限は関数数で約 40%、
  コードで約 43% になる (matched + pending + NM/asm ÷ total から算出)
- excluded を含む extab group の pending が進まないのは、bundle 制約が unit 外の
  placeholder に漏れて `exX>0` になり、選定から外れていたためと思われる。
  ただし 41 fn 以上の大 group (pending 546) は大 extab 方針側の難しさもあり、
  exclusion だけが原因とは言えない
- 時間あたりの match 数そのものは、対象を増やしても直接は上がらない
  (named pending の在庫はまだ残っていた)

## 2026-10-25 変更内容

- `derive_status()`: placeholder でも `pending`。`excluded` は derive されなくなった
- `plan_units.py`: `assign_units()` を追加。placeholder を extab group → 前後同 unit →
  `anon_<addr>` の順で unit に所属させる (`docs/unit_first_strategy.md` §3.5)
- `claim_unit.py`: unit member の取得を `assign_units()` 経由に変更 (anon_* を claim 可能に)

## 2026-10-25 変更後の観測

- `orch_sync.py --dry-run`: status_changes=4581 (excluded → pending が大半。
  前回 sync 以降の pending → matched も含む)
- placeholder 4583 fn のうち 1284 が named unit に所属、3299 が `anon_*` unit (306 個、
  サイズ中央値 3 fn、最大 377 fn、1 fn だけのもの 96)
- `plan_units.py --json --min-fns 1` の比較 (理想形 = runs=1, ex>6=0, exX=0):
  - named unit 712 個のうち理想形: 193 → 209、exX=0: 238 → 260
  - exX=0 の named unit に居る pending: 319 → 598
  - 理想形 unit に居る pending の総数: 203 → 1534 (anon_* を含む)
- ランキング上位は anon_* が多数を占めるようになった

## 未確認

- anon_* unit が元 TU 境界と一致しているか (run が複数 TU を跨ぐ可能性)
- 名前なしの関数で worker の match 率が named と同等か (Ghidra 側の情報量が少ない)
