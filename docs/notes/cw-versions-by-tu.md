# TU → CW version 対応表

`configure.py` の各 lib / object に紐付いている mwcceppc (CW) version の
記録。**section ではなく TU 単位で違う** ので、新しい TU を取るときの参照に
する。

## 確認済み (2026-05-17 commit `bc622be` 時点)

| TU (src path) | lib | mw_version | 含まれる関数 (確認できているもの) | section |
|---|---|---|---|---|
| `init/__check_pad3.c` | `init` | **GC/1.0** | `__check_pad3` | `.init` |
| `init/__init_hardware.c` | `init_sdk` | **GC/2.7** | `__init_hardware` (asm) | `.init` |
| `init/__flush_cache.c` | `init_sdk` | **GC/2.7** | `__flush_cache` (asm) | `.init` |
| `init/fn_80003458.c` | `init_sdk` | **GC/2.7** | `fn_80003458` | `.init` |
| `init/fn_80003488.c` | `init_sdk` | **GC/2.7** | `fn_80003488` | `.init` |
| `init/fn_800053E0.c` | `init_sdk` | **GC/2.7** | `fn_800053E0` | `.init` |
| `init/memset.c` | `init_sdk` | **GC/2.7** | `memset` | `.init` |
| `init/__fill_mem.c` | `init_sdk` | **GC/2.7** | `__fill_mem` | `.init` |
| `init/memcpy.c` | `init_sdk` | **GC/2.7** | `memcpy` | `.init` |
| `sysdolphin/baselib/_hsd_consts.c` | `sysdolphin` | **GC/1.3.2** | (sdata2 共有 pool のみ) | `.sdata2` |
| `sysdolphin/baselib/aobj.c` | `sysdolphin` | **GC/1.3.2** | `HSD_AObjReqAnim` | `.text` |
| `sysdolphin/baselib/dobj.c` | `sysdolphin` | **GC/1.3.2** | `HSD_DObjReqAnimAllByFlags` | `.text` |
| `sysdolphin/baselib/fobj.c` | `sysdolphin` | **GC/1.3.2** | (main session 作業中) | `.text` |
| `sysdolphin/baselib/jobj.c` | `sysdolphin` | **GC/1.3.2** | `HSD_JObjReqAnimByFlags` | `.text` |
| `sysdolphin/baselib/robj.c` | `sysdolphin` | **GC/1.3.2** | `HSD_RObjReqAnimAllByFlags` | `.text` |
| `Runtime.PPCEABI.H/global_destructor_chain.c` | `Runtime.PPCEABI.H` | **GC/1.3.2** | `__destroy_global_chain`, `__register_global_object`, .dtors ref | `.text` + `.dtors` |
| `Runtime.PPCEABI.H/__init_cpp_exceptions.cpp` | `Runtime.PPCEABI.H` | **GC/1.3.2** | `GetR2__Fv`, `__fini_cpp_exceptions`, `__init_cpp_exceptions`, .ctors/.dtors refs, fragmentID | `.text` + `.ctors` + `.dtors` + `.sdata` |
| `game/GameMode_Base.c` | `game` | **GC/1.3.2** | `GameMode_BaseInit` | `.text` |
| `game/Clamp.c` | `game` | **GC/1.3.2** | `fn_80038778`, `fn_80038798`, `Clamp_Int` | `.text` |
| `game/Profiler.c` | `game` | **GC/1.3.2** | `fn_8002FF08`, `Profiler_ResetWriteIndex`, `fn_8002FF20`, `fn_8002FF30` | `.text` |
| `game/Collision.c` | `game` | **GC/1.3.2** | `Collision_SetGlobalData` | `.text` |
| `game/KartMovement.c` | `game` | **GC/1.3.2** | `KartMovement_SetRemainingLaps` | `.text` |
| `game/InputObj.c` | `game` | **GC/1.3.2** | `InputObj_GetHeldMasked/GetPressedMasked/IsHeld/IsPressed/GetBrake/GetAccelerator/GetSteering` | `.text` |
| `game/Camera.c` | `game` | **GC/1.3.2** | `SetActiveCamera` | `.text` |
| `game/Archive.c` | `game` | **GC/1.3.2** | `Archive_GetRootJObj` | `.text` |

**カバレッジ**: 38 / 7614 functions matched、25 TU 確定 (.init = 9、sysdolphin = 6、
Runtime.PPCEABI.H = 2、game = 8)。

## なぜ複数 CW が混ざるのか (要件の整理)

これは mkgp2 固有の歪みでも、`dtk-template` / `decomp-toolkit` の不備でもなく、
**商用 GameCube binary を再現する以上は本質的に発生する**。2007 年の GC タイトル
の link には:

- 任天堂が配布した古い Dolphin SDK の prebuilt object (GC/1.0〜GC/1.2.5n 頃に
  ビルドされて、その後の project では再ビルドされず流用)
- middleware (HSD / MetroTRK / 各社ライブラリ。ベンダーが独自に build した
  object をそのまま受け取る)
- project 時点で最新の CW で書かれた game コード / SDK 拡張 (mkgp2 では GC/2.7
  + GC/1.3.2 が混在)

の object が同じ `mwldeppc` で混ぜて link される。CW の `.o` format は version
間でほぼ互換なので、混在 link は普通に通る。

`dtk-template` は **per-lib `mw_version`** を素直に持っているので、ここで困る
ことはない。我々のやっている「lib を CW ごとに分ける」運用は他 GC decomp
project (mkdd / melee / ogws) でも完全に同じ定石。

唯一の痛みは「未確認の TU 1 つずつに CW を当てる discovery 工程」で、ここは
**capability 不足ではなく automation 不在の話**。`tools/find_cw_version.py` の
ような trial loop を書けば 1 TU 30 秒〜1 分に圧縮できる。

## CW 分布の現状

| mw_version | TU 数 | 由来推定 |
|---|---|---|
| `GC/1.0` | 1 | 古い Dolphin SDK の `__start.c` 由来 (`__check_pad3`) |
| `GC/2.7` | 8 | プロジェクト時点の Dolphin SDK (memset / memcpy / __fill_mem / __init_hardware / __flush_cache / fn_80003488 / fn_800053E0 / fn_80003458) |
| `GC/1.3.2` | 16 | HSD / Runtime.PPCEABI.H / game 本体 |

## 未確認領域 (~7576 functions)

7614 関数中 38 関数のみ確定。残り 7576 関数は CW 未確認。section と推定原産で
分類:

- `.init` (0x80003100..0x80005600): 9 関数 全部確定済 (残り 0)
- `.text` ゲーム本体 (0x80020000 付近〜0x80250000 付近): ほぼ全部未確認
- `.text` SDK 領域 (0x80255000 付近〜0x802B0000 付近): ほぼ全部未確認
- `.text` HSD 領域 (0x802BD000..0x802DA000): jobj/aobj/dobj/fobj/robj のごく一部のみ
- `.text` MetroTRK 領域 (0x8026D000 付近): 全部未確認
- `.text` Runtime.PPCEABI.H (0x80270B00 付近〜0x80273400 付近): 2 関数のみ確定

## CW version 判別の手順

1. **prologue 形を見る** (`build/GNLJ82/asm/auto_*_<addr>_text.s`)
   - 最初の 2 命令が `mflr; stw r0, 0x4(r1)` → CW 1.0
   - 最初の命令が `stwu r1, -F(r1)` → CW 1.2.5n 以降 (要 trial)
   - leaf 関数 (stwu/mflr なし) → 周辺 TU の prologue を見て推測
2. **隣接 TU の CW を参照** — 連続する auto blob 内の named 関数は同じ TU と
   推定される。1 つ確定したら隣も同じ CW でまず試す
3. **trial 順序の優先度** — `GC/1.3.2` (HSD/Runtime/game 多数) > `GC/2.7` (SDK)
   > `GC/1.2.5n` (Dolphin SDK 既定) > `GC/1.0` (古い SDK 残骸) >
   `GC/3.0a3` 系 (新しい SDK 拡張、必要なら)
4. **`build/tools/dtk.exe elf disasm <obj.o> <out.s>`** で自分の .o を直接見て、
   register 配分や 1 命令の選択が違う場合は CW 違いを疑う

## 自動化候補 (未着手)

`tools/find_cw_version.py` のような script を 1 つ書けば trial loop を機械化
できる:

- 入力: TU の C source path、splits.txt entry、対象 address range
- 処理: 候補 CW を順に `configure.py` に差し込んで `ninja dol_diff` を回す。
  `.text` 範囲が完全一致した CW を返す
- 出力: 一致した CW version、または「該当なし」

未着手。次に踏むときに作るかどうか判断する。

## 関連

- [`mkgp2-init-mixed-cw.md`](mkgp2-init-mixed-cw.md) — `.init` 内の CW 混在の
  詳細。prologue 形での見分け方
- skill `mkgp2-match` の Step 8 (configure.py) に「mkgp2 で確認済みの compiler
  version」一覧があるので、この表を更新したら skill 側も合わせる
- [`TODO.md`](../../TODO.md) の「`mw_comment_version` の再評価」タスク
