# OnKartHit value-numbering 解析ハンドオフ (次セッション = Fable 5, Ghidra 静的解析)

作成: 2026-06-11 / worktree: `batch_fable_onkarthit_recheck2` (branch `orch/batch_fable_onkarthit_recheck2`)

## このハンドオフの目的とモデル制約

**次セッションは Fable 5 (最上位モデル) で走らせたい。** 本セッションが Opus 4.8 に落ちたのは、
やりとり中で **frida を使おうとすると safety classifier に flag され強制 downgrade される**ため。
よって **次セッションでは frida を一切使わない**。残りの解析は **Ghidra 静的 decompile + objdiff/dtk**
のみで完結する設計にしてある (frida で取るべき情報は本セッションで取り切り、下に observation として
記録済み。再取得不要)。

- ✅ 使ってよい: Ghidra MCP (compiler decompile)、`build/compilers/GC/1.3.2/mwcceppc.exe` での compile、
  dtk disasm、objdiff、`tools/compiler_probe/onkarthit_vn/` の probe harness。
- ⚠️ 既定は frida 不使用 (`tmp/keyscan.py`, `tmp/colorer_ef_run.py`,
  `tools/compiler_probe/frida_colorer_probe.js`, `tmp_probe/mwcceppc_priv.exe` は参照のみ)。

**ただし frida を使いたくなったら遠慮なくユーザーに宣言すること。** 「ここは frida で実行時観測した方が
確実 / 速い」と判断したら、黙って避けずに**はっきり提案する**。その時点でユーザーが方針(モデル downgrade を
許容するか、別の手を取るか)を判断する。frida 回避はあくまで「Fable 5 を維持したい」という運用上の都合で
あって、解析上の禁止事項ではない。確度を犠牲にしてまで frida を避ける必要はない。

---

## 1. 原目標 (大元のミッション)

- **brief**: `docs/notes/onkarthit-fable-recheck-brief.md`
- **roadmap**: `docs/notes/approachA-roadmap.md` (Phase 3 gate)
- **主研究ノート**: `docs/notes/cw132-allocator-phase2f-research.md` ← **本セッションの全 follow-up はここに追記済み。必読。**

`KartItem_OnKartHit` (0x8004A238, `src/game/auto_ONKARTHIT_block.c` の先頭関数 = prefix index 0) を
**96.38% park から byte-identical に昇格**させる。これは Phase 3 (A 区間化) の gate: A 区間は TU 先頭から
連続必須で、index 0 = OnKartHit が park だと prefix が空になり部分 A 化も不可。**この register-identity park
は他の多数の関数で頻出するパターン** (ユーザー曰く「死ぬほど出てくる」) なので、機構解明は family-wide の価値。

現状 OnKartHit は **matched asm (asm_fn) で byte-identical 維持**。SHA-1 OK、worktree green。
C 化 (promote) は未達。

## 2. 現在の確定理解 (本セッションで cross-validate 済み)

CW 1.3.2 の register allocator は graph-coloring。**後半3 pass を frida(実行時)+ Ghidra(静的)で完全解明:**

| pass | Ghidra addr | 機構 (確定) |
|---|---|---|
| SIMPLIFY | `0x507b50` FUN_00507b50 | node を **index(=web key)昇順**走査、trivial(deg<k)を stack に prepend → stack は head=最高 key の降順 |
| SELECT | `0x507a30` FUN_00507a30 | stack を head→tail で walk、**最低 index の空き reg を割当**(bit ordering 上 r31 が先)→ 最高 key→r31、最低 key→最下位 reg。param は forced でも spill でもない通常経路 |
| COALESCE | `0x57a1f0` FUN_0057a1f0 | union-find、**survivor は常に最小 index** (`uf[max]=min`)。arg が局所と coalesce しても arg(小 index)が survivor = 低 index/reg を保持 |

**帰結**: callee-saved reg は web の index(key)で決まる。最低 index → 最下位 reg。
frida 実測 (EF 形, GPR class):

```
rm    key=94 → r31   (非coalesce)
bus   key=52 → r30   (非coalesce)
bools key=46-51 → r27-r30  (coalesced, flags 0x42)
victim key=33 → r26  (PARAM, 非coalesce, adjN=137 最大干渉)
self   key=32 → r25  (PARAM, 非coalesce, adjN=135)
```

params は最大干渉度なのに最低 key(32/33)ゆえ最下位 reg。**degree は reg を決めない、key が決める。**

## 3. 唯一の未解明 = THE OPEN QUESTION (次セッションの本題)

**args がなぜ web index 32/33 (最低) を取るのか**、そして**どういう IR 構造なら arg の実効 key が上がるのか**。

これは **value-numbering / web-formation pass**(coloring driver `0x5077b0` FUN_005077b0 より**上流**の
独立 pass。driver 実行時には webCount は既に確定済み)で決まる。**この pass はまだ decompile していない。**

### 解くべき hard contradiction (これが羅針盤)

- 後半3 pass は「key 32/33 の arg を**必ず**最下位にする」と**証明済み**(上表)。
- しかし **target は self=r30 / victim=r31 (最上位)、bus=r25 (最下位)** に置く(EF と完全に逆順)。
- target は同一コンパイラ(GC/1.3.2, SHA-1 `d8f9c36d62f66c2a044d5a20a132b79eeb2f36e5`)・同一 flag で
  生成された(standalone probe が in-TU partition を P0 再現済み = flag 差ではない)。
- ∴ **target では arg の実効 key が 32/33 ではない**。それを決めるのが未 decompile の value-numbering。

**重要な訂正(本セッション後半)**: 「source-closed / 再現不能」は**言い過ぎ**で撤回済み。target が存在する
以上、再現する C++ source は**必ず存在する**。元開発者は register 配置を設計したのではなく、**自然な C++ を
書いてコンパイルしただけ**。俺の再構築 C は命令 96.38% 一致だが value-numbering が分岐して args-low になる。
残差 16 命令(下記)はその value-numbering 差の**症状**。

### frida 観測(参照のみ、再取得不要)

- arg key は試した範囲で 32/33 不動。**早期 web test**: param 使用前に長寿命 local を1つ born させても
  param は 32/33、新 web は key=43 (`tmp/probe_earlyweb.c`)。→ args は entry で最優先に番号付けされると観測。
  **ただしこれは数パターンの観測で、target が反例**(args が実効高 key)。「args は常に 32/33」は一般化しすぎ。
- competitor 除去 test: bus cache 除去でも param は r25/r26 不動 (rm+bools がまだ上位) (`tmp/probe_nobus.c`)。

## 4. 次の具体的ステップ (Ghidra)

目標: web の index([+0x1c] on web record / node array の添字)を**割り当てる関数**を特定し、
「どの IR 構造だと arg が後番号(高 key)になるか」を読む。当たれば **source lever が直接判明**する。

1. **web 番号付け関数の特定**。手がかり:
   - node 配列 `DAT_005e87d0` は web index で添字。web record `[+0x1c]` が index。web list head `DAT_005e87b0`。
   - `lowReg[class] = DAT_005e8778[class] = 32` (GPR) = 物理 reg 0-31 の次から virtual web 開始。
   - `webCount[class] = DAT_005e8a7c[class]`。
   - これらを **書き込む / 初期化する**関数を Ghidra で探す(`DAT_005e87b0` / `DAT_005e87d0` / `DAT_005e8a7c`
     への write の xref、または web record `[+0x1c]` への store)。value-numbering は coloring の前段なので、
     coloring driver `0x5077b0` を呼ぶ**手前**のパイプライン(`FUN_00433310` CodeGen 系、prior note 参照)を辿る。
2. **arg web 生成箇所**を特定。incoming param (r3/r4) を virtual web 化する所。なぜ 32/33 (最初) になるか、
   first-use / entry / definition のどれが trigger か。`FUN_005797a0` 内の `DAT_005e8848` / `DAT_005e8ad8`
   (特殊 ABI web = 戻り値 / 第1引数候補。flag 8/0x10 を立てる) も arg 扱いの手がかり。
3. **arg key を上げる条件**を読む。target は bus(本体ポインタ)を arg より先に番号付けしている(bus key < arg key)。
   どんな IR 構造でそれが起きるか。読めたら source 形に翻訳し objdiff で検証(下記 harness)。

### 既 decompile 済み(再 decompile 不要、参照用サマリ)

| addr | 役割 |
|---|---|
| `0x5077b0` | RegisterColoring driver。class 0..4 loop。各 class で 579cf0→507d40→507b50→507a30、spill 時 57abd0 で retry |
| `0x579cf0` | build+coalesce orchestrator。呼ぶ: 5797a0, 579e50, 57a640, **57a1f0(coalesce)**, 579fe0, 579d50 |
| `0x5797a0` | 干渉グラフ bit-matrix builder。web `[+0x1c]` で添字。`DAT_005e8848`/`DAT_005e8ad8` に ABI flag |
| `0x507b50` | simplify(上表) |
| `0x507a30` | select(上表) |
| `0x57a1f0` | coalesce union-find、survivor=min index(上表) |

### node / web 構造体 offset(frida で確定済み)

node (array `DAT_005e87d0` の要素): `[+0x04]` web/temp record ptr, `[+0x0c]` spill-cost numer,
`[+0x10]` key/index (u16), `[+0x12]` 動的 degree (u16), `[+0x14]` **home reg (u16, 0xffff=未着色)**,
`[+0x16]` flags (0x2=removed, 0x40=coalesced-into, 0x8=coalesce-related), `[+0x18]` adjN, `[+0x1a]` 隣接配列。
web record: `[+0x1c]` index, `[+0x18]` node-chain head。
globals: `DAT_005e931f`=現 class(4=GPR,3=FPR), `DAT_005e21c8`=union-find array,
`DAT_005df940`=webCount(cost比 閾値), `DAT_005e8cfe`=class4 で coalesce 除外する特殊 reg。

## 5. Ghidra 環境 (接続手順)

- **onboarding**: まず `Skill(skill="mkgp2-ghidra")` をロード(MCP を触る前)。汎用作法は `ghidra-mcp` skill。
- **接続**: `mcp__ghidra__connect_instance(project="bmp_output")`。
  - 注意: `list_instances` は Unix domain socket を探すので**空に見えるが**、bmp_output は **TCP 8089** で稼働。
    必ず `connect_instance` を直接叩いて確認すること(本セッションはこれを誤って「未起動」と判断した)。
  - 未起動(WinError 10061)なら skill の手順で起動:
    `cmd.exe /c 'C:\Ghidra\ghidra_12.0.3_PUBLIC\ghidraRun.bat C:\Users\naari\ghidra\bmp_output.gpr'` → port 8089 polling → connect。
- **対象 program**: **`/mwcceppc_132.exe`** (= CW 1.3.2 compiler, image_base `0x00400000`, x86:LE:32, 3711 fn)。
  既に bmp_output に import 済み・open 済み。`decompile_function(address=..., program="/mwcceppc_132.exe")`。
  - ASLR off (image_base 直)なので VA = file の addr。Ghidra addr と frida VA(image_base 0x400000)は一致。

## 6. objdiff probe harness (hypothesis 検証用、frida 不要)

source 仮説を試すとき:
- `tools/compiler_probe/onkarthit_vn/probe_ef.c` = **96.38% baseline を単一アーム bool 化した形**(残差 16 の最良 base)。
  `#include "probe_common.h"` (同ディレクトリに同梱)。
- `tools/compiler_probe/onkarthit_vn/cpp_probe_run.py` = compile(`build/compilers/GC/1.3.2/mwcceppc.exe`)
  + dtk disasm + target 比較 + homes(self/victim/bus)抽出。CFLAGS は in-TU 一致を確認済み。
- `tools/compiler_probe/onkarthit_vn/verify_any.py` = **label 正規化(分岐先→行 index)+ reg masking** で
  target との**真の命令差分**を出す(register 番号差は無視、構造差のみ)。**single source of truth な比較器。**
  注: パス前提が `tmp/` 基準なので新 worktree では `target_tu_full.s` 生成と相対パスを調整すること。
- target asm 再生成: `build/tools/dtk.exe elf disasm build/GNLJ82/obj/game/auto_ONKARTHIT_block.o <out>.s`
  → `KartItem_OnKartHit` を抽出。本セッションでは `tmp/target_tu_full.s` (566KB, TU 全体)。
- baseline body の出所: `docs/drafts/Class2_expansion_nearmatches.handoff.md` Appendix B (96.38% C body)。

### EF vs target の残差 16(参照: これを 0 にできれば match)

label+reg 正規化で 16 diff。全て partition の下流症状:
- **FP scheduling ×4** (row ~81-90): 命令同一、`fsubs` と隣接 `lfs` の順が 1 行ずれ。base reg target r29 vs EF r31。
- **bool zero-self-reuse ×12** (row ~220-267): target は 0 初期化した callee-saved bool reg を 64bit
  `(flags&maskULL)` の上位語ゼロ兼 compare-rhs に**自己流用**(`li r28,0; and r0,r0,r28; bne set1; b done`)。
  EF は別 scratch(`li r4,0; beq done`)。**これが value-numbering 差の唯一の可視 fingerprint。** 6 bool 形
  (single-arm/empty-then/clean-two-arm/direct/ternary/chained-zero)全て再現せず。これを再現する形が
  見つかれば partition ごと反転する可能性が高い ← **Ghidra で value-numbering を読む際の最重要 cross-check。**

## 7. target の確定事実(参照)

- callee-saved span: self r30 rows 4..406 / victim r31 rows 5..390 / **bus r25 rows 7..398**(3つとも最大寿命)。
  target は args を最上位・bus を最下位、EF は逆。entry は両者 `mr rX,r3; mr rX,r4`(args は文字通り incoming web)。
- 16 diff の生データ生成: `verify_any.py` を probe_ef に対して実行。

## 8. 制約・状態

- **shipped compiler 不接触**: `build/compilers/GC/1.3.2/mwcceppc.exe` SHA-1 `d8f9c36d62f66c2a044d5a20a132b79eeb2f36e5` を維持。
- **worktree green 維持**: OnKartHit は `src/game/auto_ONKARTHIT_block.c` 内で asm_fn。実験で body を差し替えたら
  `git checkout -- src/game/auto_ONKARTHIT_block.c` で復元。`ninja build/GNLJ82/ok` → `main.dol: OK` 確認。
- `tmp/` は scratch(untracked、worktree clean で消える)。重要 probe は `tools/compiler_probe/onkarthit_vn/` に保全済み。
- 本セッションの commit: `997f548`(訂正), `4824cd0`(Ghidra), `e08451a`(frida), `fa4d966`(EF撤回) 他。
  研究ノート末尾の追記節が詳細の SoT。

## 9. 一言サマリ(次セッションへ)

後半3 pass(simplify/select/coalesce)は完全解明済み。残るは**唯一**「value-numbering が arg に index 32/33 を
刻む工程」を Ghidra で decompile し、**arg を後番号(高 key)にする IR 構造**を見つけること。それが分かれば
target の bool-zero-reuse を再現する source 形に翻訳でき、OnKartHit が promote できる(= Phase 3 gate が開く)。
既定は Ghidra + objdiff で完結(Fable 5 維持のため frida 回避)。**だが frida が要ると思ったら遠慮なく宣言**して
ユーザーの判断を仰ぐこと(§0 参照)。
