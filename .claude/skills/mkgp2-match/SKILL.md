---
name: mkgp2-match
description: "Mario Kart Arcade GP2 (GNLJ82, Triforce / GameCube) の main.dol を byte-identical に再ビルドする naari3/mkgp2-decomp project で、1 関数を C 起こし → CW で compile → SHA-1 一致まで持っていく matching workflow。Ghidra decompile・他 decomp project (mkdd 等) の SDK 参照・splits.txt 編集・scope:global 調整・mw_version 切替・objdiff iterate の手順を一連でカバーする。ユーザーが mkgp2 specific の関数を matching したい / `__check_pad3` のような mkgp2 関数を C 化したい / mkgp2-decomp の matched % を増やしたいと言ったときに trigger する。"
---

# mkgp2 matching workflow

mkgp2-decomp で `__check_pad3` を初めて matched したときに確立した手順 (commit `9c4efa9`)。1 関数を byte-identical に持っていくまでの全工程。

この repo copy が正本。人間の contributor もそのまま手順書として読める。分担ルールと PR 要件は `CONTRIBUTING.md` を参照。

## 前提と関連 repo

- **本体**: [naari3/mkgp2-decomp](https://github.com/naari3/mkgp2-decomp) — この repo。matching の本拠地
- **姉妹 repo**:
  - [naari3/mkgp2-patch](https://github.com/naari3/mkgp2-patch) — Kamek パッチ + Ghidra 解析の蓄積。命名の SoT は decomp 側に寄せる方針
  - `mkgp2docs` — 関数アドレス / 構造体 / HSD format 等の解析メモ 79 md。現状 maintainer (naari3) の手元にのみ存在。共有価値が確定したものから `docs/notes/` に転記される。必要な情報は issue で聞く
  - [naari3/mkgp2-view](https://github.com/naari3/mkgp2-view) — Dolphin プロセスの live memory viewer。動作確認用
- **参考にする他 decomp project**:
  - [doldecomp/mkdd](https://github.com/doldecomp/mkdd) (Mario Kart Double Dash, GameCube) — Dolphin SDK の C 実装が充実。SDK / Runtime.PPCEABI.H 系を matching するときの命綱。`libs/dolphin/os/init/__start.c` などに `__check_pad3`, `__init_registers`, `__copy_rom_section` 等が C で書かれている
  - `dolphin-emu/dolphin` の `Source/Core/Core/HW/EXI_DeviceIPL.cpp` 系 — 低レベル hardware 挙動の参考

参考 repo はローカルにクローンしておくと grep しやすい。ファイル 1 つだけなら `gh search code --repo doldecomp/mkdd "<symbol>"` で速い。

## ワークフロー (手順)

### 1. 対象関数を選ぶ

- `config/GNLJ82/symbols.txt` から候補を選ぶ。小さい (~0x40-0x100 bytes)、placeholder 名 (`fn_XXX`) または既に named だが matching 0% のもの
- 候補メモは `TODO.md` の「Matching に着手」節
- 最初は `.init` セクション、または解析メモが充実している関数から
- **着手前に担当範囲を claim すること** (`CONTRIBUTING.md` の分担ルール参照)。extab group をまたぐ範囲は分割できない (§7.5 制約 D)

### 2. disasm を読む

**重要 — target asm の identification (混同しがちな 4 種類)**:

| ファイル | 何 | 信頼度 |
|---|---|---|
| `build/GNLJ82/asm/<lib>/<file>.s` | dtk が target binary から逆 disasm したもの (= **真の target**) | **唯一の正解** |
| `build/GNLJ82/asm/auto_<group>_text.s` | dtk が target binary から「未 split blob」を逆 disasm したもの。**まだ TU が split されていない関数群の target asm** | target を含むが「現状未 split」を意味する |
| `build/GNLJ82/obj/.../<file>.s` (もし出力されてれば) | target binary 由来の reference asm (1 と本質同じ、dtk-template の dir layout 都合) | target |
| my-side build 産物 (`build/GNLJ82/src/.../<file>.o` から `dtk elf disasm` した結果) | 自分が書いた C を CW が compile した結果 | **自分の出力**、target と diff る対象 |

**よくある罠**: `auto_<group>_text.s` を読んで「これが target」と判断しがちだが、これは前回 build に基づいて再生成される。実際の判定は `config/GNLJ82/build.sha1` (target binary の SHA1) と現状 dol の比較で決まる。dtk-template は build 毎に asm/ を再生成するので、target binary が変わらない限り 1 と 2 の内容も変わらないが、「auto_」 prefix がついた瞬間「未 split blob 由来」と認識すること。

手順:

- まず prologue / epilogue で stack frame size と prologue order を確認 (CW version 判別の手がかり)
- 関数 body の instruction を追い、 immediate address load (`lis r3, 0x8000` + `displacement(r3)`) や SDK 関数呼び出し (`bl OSXxx`) を identify
- 既に他関数で matched なら、`build/GNLJ82/asm/<lib>/<file>.s` の TU 末尾に追加されるはず。新規関数で TU 未 split なら `build/GNLJ82/asm/auto_*_text.s` 内

### 3. Ghidra decompile を取る (mkgp2 specific の関数なら必須)

> **環境 note**: maintainer (naari3) 環境では Ghidra MCP bridge + user scope の `mkgp2-ghidra` / `ghidra-mcp` skill を使う (以下の `mcp__ghidra__*` 呼び出しはそれ前提)。それ以外の環境では、自前の Ghidra project に `main.dol` を import して decompile 出力を取れば同等。committed 済みの `tools/ghidra_symbol_dump.json` と `config/GNLJ82/symbols.txt` に命名済み symbol があるので、import 後に流し込むと読みやすくなる。struct 型定義は `tools/mkgp2_types.gdt` (Data Type Archive) を Data Type Manager で開けば適用できる。dump / gdt の再生成手順は `tools/ghidra_dump_raw.java` / `tools/ghidra_export_gdt.java` (run_script_inline で実行) → `python tools/_build_ghidra_dump.py`。

```
mcp__ghidra__connect_instance(project="mkgp2")
mcp__ghidra__decompile_function(program="main.dol", address="0x...")
```

- maintainer 環境のルール: **`Skill(skill="mkgp2-ghidra")` を先にロード** してから MCP を触る (bmp_output project 固有の起動手順 / domain path / image_base は `mkgp2-ghidra`、汎用の Ghidra MCP 接続作法とツール選択は transitively 参照される `ghidra-mcp` skill 参照)
- decompile 出力で得たいもの:
  - 引数の型と数 (`undefined func(int, int *)` 形式)
  - 関数 body の制御フロー (擬似 C)
  - struct field アクセス (Ghidra で型適用済みなら `kart->field_0x40` のように見える)
  - 呼び出し先 (`FUN_xxxxxxxx` か named かで命名状況がわかる)
- 必要なら対象関数の prototype / plate comment / local var rename を先に整え、decompile 出力を読みやすくする (matching 中の見通しが格段に上がる。maintainer 環境では `ghidra-rename` skill の手順)

#### 3.5. Ghidra struct の有無を必ず確認

**Ghidra に struct 型が定義されているなら、必ず C source 側でもその型と field 名を使う**。素の `(char *)p + 0x240` のような offset 直書きは「Ghidra 側にも何も無い」ことを確認してからの fallback として使う。

確認手順:

1. decompile 出力の引数型を見る
   - `KartMovement *kart` → struct 型あり、field 名で参照しろ
   - `int param_1` / `int *kartMovement` → struct 型なし
2. struct 名で `mcp__ghidra__list_globals(filter="<typename>")` / `search_functions(query="<typename>")` を投げ、関連 fn が型を消費しているか見る
3. 解析メモ (mkgp2docs) の plate comment (`KartMovement+0x17C (vx)` のような offset 記述) は **型ではなく文書**。これだけだと使えないので、先に struct を Ghidra に flush してから matching に入る、が筋

整地のプロセスは matching 着手の前提:

- 同じ struct を消費する 5+ 関数を一気に取りたい round の頭で、**先に struct 化に 30 分使う** 方が結果的に速い。後で書き直しが要らない
- 1 関数だけ取って次に行くなら、Ghidra に struct が無い場合は opaque pointer + offset で済ませてよい (ただしそのことを commit メッセージか TODO に残す)
- 後から struct が定義されたら、`(char *)p + 0x240` 直書きの旧 source は struct 形式に書き直す pass を入れる

### 4. 他 decomp project を grep する (SDK / 標準ライブラリ系のみ)

対象が SDK の `__check_pad3`, `OSInit`, `GX_*`, `memset` のような Dolphin SDK 標準関数なら、mkdd など他 decomp project に C 実装がある可能性が高い:

```
gh search code --repo doldecomp/mkdd "<symbol_name>"
```

見つかったら参考にする。game-specific (Race / Item / Course 系) のときはスキップ。

### 5. C source を起こす

`src/<lib>/<func>.c` に C を書く。ポイント:

- **section 指定**: CW は default で `.text` に配置する。`.init`/`.text`/`.data` 等の section を明示するには `__declspec(section ".init")` を関数前に書く
  ```c
  __declspec(section ".init") void __check_pad3(void) { ... }
  ```
- **extern decl**: SDK 関数は header が無い段階では関数定義の直前に `extern void OSResetSystem(int, unsigned long, int);` のように直書きでよい。後で header に集約する
- **extern array にはサイズを明示**: `extern int buf[]` だと CW は large-data 扱いし `lis/addi` の 2 命令 base 計算を出す。sdata 居住で 1 命令 SDA21 経路 (`addi r5, r13, lbl@sda21`) を引きたいなら `extern int buf[N]` のように **sdata threshold (default 8 bytes) 以下のサイズ** で宣言する。symbols.txt 側で `.sdata:` に居ても、宣言が open のままだと SDA 経路にならない
- **C++ TU で symbol mangling を選択する**: `.cpp` ファイル全体をデフォルト C++ で書くと全 symbol が mangled される。一部だけ unmangled に保ちたい場合は `extern "C" { ... }` で囲む。`__init_cpp_exceptions.cpp` の例: `__init_cpp_exceptions` / `__fini_cpp_exceptions` は `extern "C"` で wrap して unmangled、`GetR2` は外で `asm` 定義のまま → `GetR2__Fv` で mangled に残る
- **`__declspec(section ".ctors"/".dtors") static T const ref = &fn;`** で .ctors / .dtors の 4-byte エントリを発生させる。`static` を付ければシンボル名衝突なしで、別 TU の同名 extern と共存できる
- **integer width**: u8/u16/u32 を `unsigned char/short/int` で書くか、include を用意するかは状況次第。最小実装は raw 型名で

### 6. splits.txt を編集

dtk が auto-split で大 blob として認識している領域から、対象関数を切り出す:

```yaml
init/__check_pad3.c:
    .init       start:0x80003100 end:0x80003140
```

- `<src_path>: <section> start:0xAAA end:0xBBB` 1 行
- end は exclusive ではなく **次の関数の開始 address** (`size` ではない)
- 同じ TU に複数 section があるなら複数行

### 7. symbols.txt を `scope:global` に

対象関数が cross-object 参照される (= 別 TU から `bl <func>` で呼ばれる) なら `scope:global` が必要。`scope:local` のままだと linker が address suffix 付きで mangle して resolve に失敗:

```
__check_pad3 = .init:0x80003100; // type:function size:0x40 scope:global
```

このフラグ無しで `undefined: '<func>_<addr>'` の link error が出たら確実に scope:global 不足。

### 7.5. TU 境界の inline 制約と関数群の分割

複数関数を含む TU を一括 match させようとして、1 関数だけが mismatch するケースは頻繁にある。`HSD_JObjReqAnim*` 系 (commit `c430db8`) で踏んだ典型的な制約と回避策:

**制約 A: CW は別 TU の関数を inline できない**

`HSD_JObjReqAnim` のような「`HSD_JObjReqAnimByFlags(jobj, 0x7FF, frame)` を呼ぶだけの wrapper」が、target asm 上で呼び出しではなく **inline 展開** されていることがある。CW (1.3.2) は同 TU 内の関数しか auto-inline できないため、source を別 TU に分けると wrapper として残ってしまい mismatch する。

回避: wrapper を `HSD_JObjReqAnimByFlags` と同 TU に置く。それが構造上難しい場合は、source 側で **inline 済みの形を直書き** する (`HSD_JObjReqAnim` を `HSD_AObjReqAnim(...)` → `HSD_DObj...` → `HSD_RObj...` の生 source に展開)。

**制約 B: dtk splits の TU 間 cyclic dependency 禁止**

1 .c に複数の disjoint range を書くと、その範囲が他 TU の関数を呼び、相手も呼び返す形になりやすい (例 `jobj.c` が `HSD_JObjReqAnimAllByFlags` を呼び、`jobj_anim_all.c` がそれを再帰 + 同 TU の `HSD_JObjReqAnimByFlags` を呼ぶ)。dtk は link order を一方向に解決できず `Cyclic dependency encountered while resolving link order` で fail する。

回避: 関数群を address 順で一方向 chain になるように 3 TU に分割する。`jobj.c` (HSD_JObjReqAnimByFlags) → `jobj_anim_all.c` (HSD_JObjReqAnimAllByFlags, NonMatching) → `jobj_anim_misc.c` (末尾 3 関数) のパターン。

`__anim_all.c` のようなサフィックス命名は ad-hoc decomp の慣習。`splits.txt` で 3 entry を address 順に並べ、`configure.py` で `Object(Matching, ...)` または `Object(NonMatching, ...)` を 3 つ登録する。

**制約 C: 1 関数だけ NonMatching で隔離して全体の build sha1 を通す**

manual unroll や register allocator chase で 100% に届かない関数を、別 TU `*_anim_all.c` 等に切り出し `Object(NonMatching, "<path>.c")` で登録。dtk-template の挙動として **NonMatching の TU は target asm fallback で link される** ので、build sha1 は通る。`.c` 自体は将来 100% match に昇格するための作業ベースとして残す (89% 等の途中状態でも commit する価値あり)。

**制約 D: dtk reversed extab group は分割不可、関数群を 1 TU として一括 match する**

`.text` 内で `extab` / `extabindex` データを共有する関数群は、dtk が **1 つの indivisible 単位** として扱う。splits.txt で群内に TU boundary を作ろうとすると以下のエラーで fail する:

```
Conflicting splits within reversed extab group
```

判定方法: 一度 `python configure.py && ninja build/GNLJ82/main.dol` を回せば `build/GNLJ82/asm/auto_*_text*.s` が生成される。**1 つの `auto_*_text*.s` ファイル = 1 つの reversed extab group**。ファイル内の `.fn <name>, <scope>` declarations を grep すれば、その group に含まれる全関数がわかる:

```sh
grep -E '^\.fn ' build/GNLJ82/asm/auto_<addr>_text.s
```

`.fn` 行が 1 つだけならその関数は単独 split 可能。2 つ以上なら **全関数を 1 TU に含めて一括 match する必要がある**。

mkgp2 では現状 269 個の multi-fn group (合計 4877 関数、~64% の named function) が存在。最大 937 関数 group も存在し、現実的 single-batch matching は不可能なので、その場合は別戦略 (incremental NonMatching 隔離など) に切り替える。

オーケストレータ運用では `tools/build_extab_map.py` で `.orchestrator/extab_groups.json` を生成し、`fn_to_group` テーブルから seed 関数が属する group を引いて bundle を構築する。

### 8. configure.py に lib + Matching object を登録

```python
mw_version_init = "GC/1.0"  # CW for GameCube 1.0
# ...
config.libs = [
    {
        "lib": "init",
        "mw_version": mw_version_init,
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(Matching, "init/__check_pad3.c"),
        ],
    },
    ...
]
```

- **`mw_version` は per-lib**: `config.linker_version` (= mwldeppc) と混同しない。各 lib が個別 compiler (mwcceppc) を選ぶ
- mkgp2 で確認済みの compiler version (**section ではなく TU 単位で違う** ので注意):
  - `__check_pad3` (lib `init`): `GC/1.0` (mflr-first / lr@caller-slot prologue、8-byte frame で確証)
  - .init の memset / memcpy / __fill_mem / __init_hardware / __flush_cache / fn_800053E0 / fn_80003488 / fn_80003458 (lib `init_sdk`): `GC/2.7` (stwu-first prologue)
  - sysdolphin/baselib/*.c (lib `sysdolphin`): `GC/1.3.2`
  - Runtime.PPCEABI.H/* (lib `Runtime.PPCEABI.H`): `GC/1.3.2`
  - その他 (`.text` ゲーム本体、 SDK lib 大半): **TU ごとに prologue を見て選ぶ**。`config/GNLJ82/config.yml` の `mw_comment_version: 11` は仮置きのまま
- 「同じ section に複数 CW version が混在する」ことが mkgp2 では確認済 (`.init`)。section 名から推測せず、必ず prologue 形を見て切り替える
- **multi-CW link は商用 GC binary の標準的な姿** で、mkgp2 の歪みでも tooling の不備でもない。古い Dolphin SDK の prebuilt object + middleware (HSD 等) + project 時点の新 CW で書かれた game コード、が同じ `mwldeppc` で混ぜて link されているのが本来の構造。mkdd / melee / ogws 等の他 GC decomp project も同じ事情で、lib を CW ごとに分ける運用は **decomp 全体の定石**。痛みは「未確認 TU 1 つずつに CW を当てる discovery 工程」だけで、capability 不足ではない (dtk-template は per-lib `mw_version` を素直に持っている)
- 新 CW version を試行錯誤するときは literal でなく `mw_version_xxx` のような named 変数で定義
- `Object(Matching, ...)` で Matching として登録すれば link 対象。`NonMatching` だと skip
- **既に `NonMatching` で scaffold されている TU を Matching 化する場合**: 新しい lib を足さず、`.c/.cpp` ファイルを作って Object の flag を `Matching` に切り替えるだけで足りる (`Runtime.PPCEABI.H/global_destructor_chain.c` のパターン)

### 9. build + verify

```sh
python configure.py
ninja build/GNLJ82/ok
```

期待する出力:

```
[1/N] MWCC build/GNLJ82/src/<lib>/<func>.o
[2/N] LINK build/GNLJ82/main.elf
[3/N] DOL build/GNLJ82/main.dol
[4/N] CHECK config/GNLJ82/build.sha1
build/GNLJ82/main.dol: OK
```

`OK` が出れば byte-identical 達成。

**重要 - 偽 match の検出**: `OK` だけで満足しないこと。splits.txt のエントリが dtk に strip された / `.c` だけ作って配線していない 等で、自分の `.o` が **実際には link されておらず** dtk auto blob の元 byte がそのまま使われている、というケースが起こる (SHA-1 は元 byte 由来で通る)。

build 末尾の `PROGRESS` セクションで:

```
All: ... linked (N / M files)
    Code: <bytes_matched> / <total_bytes> bytes (<funcs_matched> / <total_funcs> functions)
```

の `<funcs_matched>` の **数値が前回より増えているか** を必ず確認する。増えていなければ link されていない (= 偽 match)。一致対象を増やす作業のたびに数値を読む癖をつける。

### 10. SHA-1 が通らないときの iterate

`main.dol: FAILED` のときの典型的な原因 (上から確認):

| 症状 | 原因 | 対処 |
|---|---|---|
| SHA-1 OK だが PROGRESS の matched function 数が増えない | splits.txt のエントリが dtk に strip された / `Object(Matching, ...)` の path と splits.txt の path がズレている / `.c` 作っただけで configure.py に登録していない | `python configure.py` を走らせた後 `grep <path> config/GNLJ82/splits.txt` で生存確認。dtk は configure.py 実行時に splits.txt を再整列し、整合性のない entry を黙って消す。複数ファイル足すなら 1 つずつ progress 数値を見ながら追加 |
| `_rom_copy_info expected at A, found at A-0x40` (or 別シンボル位置ずれ) | my .o の section が `.text` で生成され、`.init`/`.data` 等の元 section にいない | `__declspec(section "...")` を関数定義に追加 |
| `undefined: '<func>_<addr>'` linker error | local scope の symbol が cross-object 参照されてる | symbols.txt で `scope:global` |
| `Symbol X overlaps with symbol Y` (split error) | 新 entry が既存 dtk blob の中に入る | 既存 blob を head/named/tail に分割。`tools/add_orphan_symbols.py` のパターン |
| code は同じだが prologue / epilogue order が違う、stack frame size が違う | compiler version 不一致 | `mw_version` を切り替えて試す。「section = CW version」ではなく **TU ごとに prologue 形** で判断 (`.init` でも CW 1.0 と 2.7 が混在) |
| `multiply-defined: '<SDK_func>'` linker error | dtk PPCEABI heuristic が SDK 標準名 (例 `__DBExceptionDestination`) を別 address に再上書き | `docs/notes/dtk-ppceabi-overrides-symbols.md` 参照。symbols.txt override が `symbols_known: false` では効かないことがある |
| `<sym>... requires that symbol be in a small data section but is in .bss` linker error | extern 宣言が C 側で sdata と認識される変数だが、実体は .bss にある (or 逆) | `extern unsigned char buf[0x2000]` のようにサイズを明示。sdata threshold (default 8 bytes) を超える宣言だと CW は large-data 経路を選ぶ |
| 関数 size が +4/+8 byte ずれる (`Expected <next_sym> at A, found at A+4`) | extern array を open `[]` で宣言 → CW が large-data 判定で base 計算が 2 命令 (`lis r5, lbl@ha ; addi r5, r5, lbl@l`)。元 binary は `addi r5, r13, lbl@sda21` の 1 命令 | sdata 居住の小さい array は明示サイズ付きで宣言 (`extern void *cam_table[2]`)。size ≤ sdata threshold で CW が SDA21 経路に切り替わる |
| `and rD, rA, rB` の operand 順が違う / 同じ AND 命令だが register 順が逆 | C 側の `a & b` と `b & a` を CW がそのまま採用 | asm に合わせて operand 順を書く。`mask & self->field` vs `self->field & mask` で実 asm の `and rD, rA, rB` の rA / rB が逆になる |
| code 自体が違う (`bl X` の target、即値、register 番号) | C ソースのロジックが違う | `ninja dol_diff` で具体的な instruction-level diff を取り、対応する C を書き直す |

`ninja dol_diff` は `dtk dol diff` で具体的な instruction 差分を表示する。matching iteration の主力ツール。`build/GNLJ82/report.json` で対象関数の `fuzzy_match_percent` も確認可能。

**全体 SHA-1 fail でも個別関数の match 率は `objdiff-cli` で見える**:

```sh
build/tools/objdiff-cli.exe diff \
  -1 build/GNLJ82/obj/sysdolphin/baselib/jobj.o \
  -2 build/GNLJ82/src/sysdolphin/baselib/jobj.o \
  -o - --format json-pretty
```

**引数の left/right 規約**:

| flag | path | 意味 |
|---|---|---|
| `-1` | `build/GNLJ82/obj/<lib>/<file>.o` | **target** (dtk が target binary から抽出した reference object) |
| `-2` | `build/GNLJ82/src/<lib>/<file>.o` | **my-side** (CW が自分の C source を compile した result) |

出力 JSON の `left.symbols[].instructions` が target、`right.symbols[].instructions` が my-side。`symbols[].match_percent` は my-side が target にどれだけ近いかの 0-100 (100 = byte-identical)。**diff 表示で `|` の左右どちらが target か分からなくなったら、必ず `-1`/`-2` の path で確認** (`obj/` が target、`src/` が my-side、これだけ覚えておけば常に解決可能)。

`asm` 内の relocation 表記 (`lbl@sda21` vs `-0x7c10(r13)` のような raw offset) は同じものを別表現してるだけ:
- `lbl_xxx@sda21` = 名前解決済みの sda21 reference
- `-0x7c10(r13)` = sda21 base (r13) からの raw offset

両方 1 行に並べてあると「target が変わった」と勘違いするが、実態は同じ命令。

複数関数を含む TU の一部だけ mismatch しているときに「どの関数が原因か」を即座に特定できる。Python one-liner で抽出:

```sh
... | python -c "import json,sys; d=json.load(sys.stdin); [print(f'  {s[\"name\"]}: {s[\"match_percent\"]:.2f}% ({s[\"size\"]})') for s in d['left']['symbols'] if 'target_symbol' in s and 'match_percent' in s]"
```

**dol_diff が「次の symbol が +N byte ずれてる」しか教えてくれない時は、自分の `.o` を直接逆 disasm する**:

```sh
build/tools/dtk.exe elf disasm build/GNLJ82/src/<lib>/<file>.o /tmp/<file>.s
```

dtk が生成した「期待される asm」(`build/GNLJ82/asm/<lib>/<file>.s`) と比較すれば、CW が余分な命令を出しているか / register 配分が違うか / sdata 経路選択が違うか、を 1 関数単位で見つけられる。

### CW codegen idioms (asm → C への逆引きテンプレ)

CW が安定して出すパターン。disasm でこの形を見たら、C 側はこう書く:

| asm パターン | C ソース | 補足 |
|---|---|---|
| `srawi r0, x, 31 ; andc r0, x, r0` | `(x < 0) ? 0 : x` (branchless max(x,0)) | 負値を 0 に飽和。`x` が signed int 前提 |
| `neg r0, x ; or r0, r0, x ; srwi r3, r0, 31` | `(x != 0) ? 1 : 0` (branchless) | x が int → 0/1 への変換。`return x != 0;` でも出る |
| `cmpw r3, r5 ; ble L ; mr r3, r5 ; blr` + 同パターン繰り返し | 標準の `if (v > hi) return hi; if (v < lo) return lo; return v;` | clamp。順序 (hi 先 / lo 後) を C 側でも合わせる |
| `addi r5, r13, lbl@sda21 ; lwzx r3, r5, r0 ; stwx r4, r5, r0` | `extern T arr[N]; old = arr[i]; arr[i] = v;` | sdata 居住 array への indexed access。`N` を必ず明示 |
| `lwz r0, 0xc(r3) ; and r3, r0, r4` | `return self->mask & arg;` (operand 順 1) | |
| `lwz r0, 0xc(r3) ; and r3, r4, r0` | `return (arg & self->mask) != 0;` (operand 順 2) | AND は可換だが CW は C の operand 順を尊重 |
| `lwz r3, 0xN(r3) ; cmplwi r3, 0 ; bnelr ; li r3, 0 ; blr` | `T *p = self->ptr; if (p) return p; return 0;` | 単純な `return self->ptr;` だと最適化されて 2 命令に縮むので、明示的な if 文が要る |
| `andi. r0, x, M ; cntlzw r0, r0 ; srwi. r0, r0, 5 ; beq L` | `if (cond) { ... } else { has_x = 0; } if (has_x) { ... }` (中間変数経由) | branchless boolean 化。`if (x & M) ...` の直書きだと `andi. / bne` の 2 命令短縮版が出る。中間変数で boolean を経由する source 表現を採用すると mkgp2 binary の形になる |
| 同 body が 4-5 階層 inline 展開 + 5 階層目で `bl func` + 6 階層目で再帰呼び出し (size 0x2C8+) | 単純再帰 source ではなく **source 自体を手動 unroll** で書く。CW 1.3.2 の `-inline auto, deferred` フラグ追加では再現しない | 例 `HSD_JObjReqAnimAllByFlags` (`docs/notes/` の jobj-tu-split 参照)。melee の単純再帰版 (CW 1.2.5n で 268 bytes) を mkgp2 (CW 1.3.2) で build すると 594 bytes、target は 712 bytes (= 6-level 手動 unroll)。100% match に register allocator chase が必要、または NonMatching 別 TU 隔離が現実解 |
| `cmpwi r3, -1 ; ble L` (signed `<= -1` 即 false 経路) | `if (id > -1) { ... }` (NOT `if (id >= 0)`) | `id >= 0` と書くと CW は `cmpwi r3, 0; blt L` 等別経路を選ぶことがある。target が `cmpwi r3, -1; ble` なら `> -1` 形で書くと一致しやすい。range check (`IsValidResourceId` で確認) |
| `cmpwi r3, X ; blt L1 ; cmpwi r3, Y ; bge L1 ; li r3, 1 ; blr ; L1: li r3, 0 ; blr` (short-circuit branch chain で bool 化) | `if (cond1 && cond2) { return 1; } return 0;` (NOT `return cond1 && cond2;`) | `return c1 && c2;` だと CW が `&&` を r0 accumulator 経由の boolean 演算に展開 (`li r0,0 / bge / cmpwi / blt / li r0,1 / mr r3,r0 / blr` 等の 9 instr) して target と diverge する。block 内 `return 1;` + 外 `return 0;` の形にすると short-circuit ジャンプ chain (early-exit branch) に展開される |
| `beq L_exit ; ... ; L_exit: blr` を desired (CW が `beqlr` に潰してしまう) | `asm { opword 0x41820020 }` を使う | CW 1.3.2 の peephole は `beq L / ... / L: blr` を `beqlr` に collapse する。`beq-` (branch hint)、`asm{}` block 分割では防げない。raw 32-bit word の `opword 0x41820020` (= `beq +0x20`) を asm body 内で emit すると collapse を defeat できる。PS Vec3 helper (mkdd `PSVECMag` の `__exit` pattern 系) で 2026-05-19 実証 (`src/game/Vec3.c`) |

### CW132 register allocation rule (load-bearing)

CW 1.3.2 は **local 変数の宣言順** で register 番号を割り当てる (fp / GPR 両方)。最初に宣言された identifier が一番低い番号 (`f0` / `r5` 等) を取る。

**Symptom**: 命令数も addressing も完全一致、register 番号だけが target と diff る (全変数で同方向のオフセット)。

**Fix**: target asm の register 順 (例 `cursor=r6, mode=r7, i=r8`) を読み、その順序で C 側の decl を並べる:

```c
SlotEntry *cursor;  /* -> r6 */
int mode;           /* -> r7 */
int i;              /* -> r8 */
```

混合型 (pointer + int + int) でも 1 つの allocation pool として扱われる。詳細・実例 (KartMovement_SetPosition の fp 版 / ItemSelect_AddSlotItem の GPR 版) は `docs/notes/cw132-fp-decl-order-regalloc.md`。**3 試行内に register 番号 swap pattern が見えたら最優先で疑う**。

### 10.5. 撤退判定と asm function 退避

C で matching に持っていけない関数は、`asm void fn() { nofralloc ... blr }` で C TU 内に inline 化する逃げ道がある。byte-identical 保証されるので bundle 全体の進捗を守れる。詳細は `docs/per_fn_matching_strategy.md`。

#### 撤退判定の閾値

1 関数あたり、以下のいずれかを満たしたら C matching を諦めて `asm_fn` 退避を検討する:

| 条件 | 閾値 | 理由 |
|---|---|---|
| edit → build → objdiff の通算サイクル | **6 回** で `match_percent == 100.0` に届かない | 深堀り傾向の早期検出 |
| diff バイト数の停滞 | **3 サイクル連続** で同じバイト数残 (例: 4 byte diff が 3 連続) | 「あと 1 命令」の罠で同じ箇所を粘る pattern を切る |
| 個別判断 | 「ROI 低い」と判断 | 早期退避 OK。理由を notes に書く |

「分単位」の判定は採用しない。サイクル回数とバイト残量の自己観測可能な指標のみ。

退避は失敗ではない。bundle 内の他関数を優先するため、または天井難度関数を後回しにするための **規約された逃げ道**。

#### asm function の書き方

`build/GNLJ82/asm/auto_<group>_text.s` (もしくは `build/GNLJ82/asm/<lib>/<file>.s`) の `.fn <name>` 〜 `.endfn` 間から命令行のみを取り出し、以下の形で C ファイルに埋め込む:

```c
asm void fn_8002F640(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    ...
    blr
}
```

ポイント:

- `asm` keyword + `nofralloc` で mwcc が prolog/epilog 生成を抑制
- signature は `void fn(void)` で OK (asm body のレジスタ使用で実 ABI が決まる、C 側 signature は呼び出し側の型強制のみ)
- section 指定は基本不要 (`.text` default)。`.init` / `.dtor` 等別 section に置く関数だけ `__declspec(section ".init") asm void fn() { ... }`
- 関数 prototype を C 側で先に extern 宣言してから asm 定義を書くと、他関数からの呼び出し時の型エラーを抑制できる

既存採用例: `src/init/__flush_cache.c`, `src/init/__init_hardware.c`, `src/Runtime.PPCEABI.H/__init_cpp_exceptions.cpp`

切り出しに含める / 含めない行:

| 内容 | 扱い |
|---|---|
| 命令行 (`stwu r1, -0x20(r1)` 等) | そのまま貼る |
| local label (`.L_8002F66C:` 等) | そのまま貼る |
| relocation 表記 (`lis r4, lbl_802E8F48@ha` 等) | そのまま貼る |
| `.fn <name>, <addr>` / `.endfn <name>` ヘッダ | 含めない |
| `.global <name>` / `.local <name>` | 含めない |
| section 切り替え (`.section .text`) | 含めない |
| 末尾の `.size` 等 | 含めない |

#### bundle 内 partial matching の扱い (orchestrator 経由のみ関連)

dtk reversed extab group bundle (`auto_*_text.s` 由来の複数関数を 1 TU に取り込む batch) で、N 関数中 M 関数だけ matching、残り (N-M) を asm_fn に退避するパターンが想定ユースケース。`Object(Matching, "...")` 1 件 + splits.txt 1 entry で TU 全体が成立し、SHA-1 OK を維持できる。

bundle 全関数を asm_fn にすると decomp 価値ゼロなので、その場合は素直に `Object(NonMatching, ...)` に倒した方が configure.py が短い (HANDOFF.md `results[].status` を全件 `nonmatching` にする)。

HANDOFF.md schema は `docs/sub_agent_role.md` の status マトリクス参照。`asm_fn` 行を見ること。

#### extab 持ち関数を asm_fn 退避する場合 (手動 extab emit 必須)

`-Cpp_exceptions on` でも `asm void fn() { nofralloc ... blr }` は extab/extabindex entry を発出しない。bundle 内 N 関数中 M 関数を asm_fn 退避すると TU の extab entries が N-M 個になり、target の N 個と layout がずれて SHA-1 fail する。

extab を持つ関数 (`build/.../auto_*_text*.s` 末尾の `.section extabindex` ブロックに `.4byte <fn_name>` 行がある関数) を asm_fn 退避する場合、C 側から手動で extab/extabindex entry を発出する必要がある。

判定:

```sh
# 該当 group の extabindex に対象 fn が含まれるか確認
grep -A2 ".4byte <fn_name>" build/GNLJ82/asm/auto_<group>_text.s
```

**tool で 1 発生成**: `tools/extract_fn_asm.py` が dtk asm から asm body + 手動 extab/extabindex emit + per-TU renames mapping を 1 ファイルで吐く。mwcc inline asm の制約 (sda21 / crclr/crset / `.L_` ローカル label / extern decl) も全部 tool が吸収する。

```sh
# group 全関数を 1 TU として scaffold
python tools/extract_fn_asm.py <group_id> \
    --tu src/<lib>/<file>.c \
    --out-c src/<lib>/<file>.c \
    --out-renames /tmp/<file>_renames.json
```

例: `auto_fn_8002F640_text` (HeapStats 6-fn bundle) を `src/game/HeapStats.c` として scaffold すると、forward decls + sda21/callee/data refs の extern + extab[N] byte 配列 + extabindex struct + asm void body 6 個を 1 file に出力 (SHA-1 OK 確認済、commit `634b412`)。出力した renames snippet は `tools/extab_user_renames.json` にマージする (per-TU dict、TU path key)。

bundle 全関数 asm_fn で SHA-1 OK を保証したいだけなら、生成された `.c` をそのまま使えば足りる。あとから 1 関数ずつ C 実装に置き換える運用 (mega-bundle promote pattern、Phase 3b) も同じ scaffold が起点になる。

configure.py 側の配線:

```python
Object(Matching, "<lib>/<file>.c", extab_padding=b"\x00\x00"),
```

`extab_padding=b"\x00\x00"` で `mwcc_sjis_extab` build rule にルーティングされ、`tools/postprocess_extab_user.py` が `.extab_user`/`.extabindex_user` → `extab`/`extabindex` rename と `@etb_<addr>`/`@eti_<addr>` symbol redefine を `dtk extab clean` 前に実行する。

例外: extab を持たない関数 (例: `isJapanese`、3 instr の小関数) は asm_fn 退避単独で OK。tool は extabindex に entry の無い fn は自動でスキップして emit する。

reference 実装: `src/game/HeapStats.c` (6-fn 全 asm_fn の Hybrid 構成)、`docs/per_fn_matching_strategy.md` §12 (Phase 1b verify outcome、採用手法 6 点)、`docs/large_extab_group_strategy.md`。

#### bundle 内 fn promote の extab handling (asm_fn → matched 昇格時)

asm_fn の bundle を 1 fn ずつ matched に promote するとき、CW は plain C 関数に対して extab/extabindex を auto-emit するので、bundle の manual emit と二重化して `_eti_init_info` が 0x14 byte シフトし SHA-1 fail する。2 つの解 (どちらでも OK、mix も実証済):

- **Approach A**: 該当 fn の `extab_<fn>` / `extabindex_<fn>` 手動 emit を **削除** (CW 自動 emit に任せる) — 例: `dtor_800A9CC8` (commit cbc8d65)
- **Approach B**: C body を `#pragma exceptions off` / `#pragma exceptions reset` で囲み auto-emit を **抑制** + 手動 emit を keep — 例: `dtor_800A9D2C` (commit 6e98202)

詳細・選択基準・mix の動作性は `docs/per_fn_matching_strategy.md` §14.1。

### 10.6 bundle promote で実証済の idiom 集 (auto_800A8F4C main wave、2026-05-18)

| パターン | C source | target asm の特徴 | 適用条件 |
|---|---|---|---|
| C++ deleting-dtor offset-0 重複 `beq` | `if (this) { if (this) { inner(); ... } } return this;` | `mr. r31, r3; beq L1; ...; beq L1` (2 重 cr0.eq 分岐) | C++ scoped object の deleting-dtor で inner subobject が offset 0 |
| 7-float-arg force | `void X(void *self, float f1, float f2, float f3, float f4, float vx, float vy, float vz);` (先頭 4 unused) | `stfs f5, ...; stfs f6, ...; stfs f7, ...` | leaf 関数で f5-f7 を出したいとき (引数 signature を膨らませて codegen を誘導) |
| 2-entry sda21 pointer array | `extern void *lbl_XXX[2];` + `return lbl_XXX[(u8)id != 0];` | `li r3, lbl_XXX@sda21; neg r0, r4; or r0, r0, r4; rlwinm r0, r0, 3, 29, 29; lwzx r3, r3, r0` | sdata 上の小さい instance array、`(arg != 0) ? 1 : 0` indexing |

詳細・コミット参照・hard-block patterns (CW DSE / frame-spill / register-allocator quirk / `_savegpr_25` vs inline `stmw` 等の **再現不能 idiom 9 件**) は `docs/per_fn_matching_strategy.md` §14.2-§14.3。

### 11. Ghidra 側 rename 同期 (重要)

`__check_pad3` のように既に Ghidra で命名されている関数は OK だが、新規に命名 / 改名した場合は Ghidra 側にも反映しないと、次回 Ghidra dump 再生成時に symbols.txt と divergence する。

- **maintainer 環境**: `rename_function_by_address` で反映し `save_program` で永続化 (詳細は `ghidra-rename` skill)
  ```
  mcp__ghidra__rename_function_by_address(program="main.dol", function_address="0x...", new_name="...")
  mcp__ghidra__save_program(program="main.dol")
  ```
- **外部 contributor**: symbols.txt に命名を入れて PR すれば OK。maintainer 側 Ghidra project への同期は maintainer が行う

### 12. commit

1 関数の matching が確定したら、関連 file を 1 commit に:

- `src/<lib>/<func>.c` (新規)
- `configure.py` (lib / mw_version 追加)
- `config/GNLJ82/splits.txt` (TU entry 追加)
- `config/GNLJ82/symbols.txt` (scope:global など)

commit message に対象関数 / address / size / 動作内容 / SHA-1 verify 通過を明記。

## 定型: extab action 持ち関数は最初から C++ で書く (2026-07-19 確立)

着手前に対象関数の extab を確認する (`python tools/scan_extab_actions.py --all | grep <fn>`
か dtk asm の extab dump)。**entry が 8 byte 超 = EH action 持ち** なら、その関数は
実 C++ 構文 (ctor / new 式 / dtor 持ち local) で compile されている。plain C +
manual extab で寄せると register-identity park に嵌まりやすいので、**最初から
本物の C++ で書く**:

- レシピの正本: `docs/notes/cpp-ctor-retrofit-mangled-bridge.md`
  (mangled 名を extab_user_renames.json の --redefine-sym で既存 C 名に橋渡し、
  vtable は未定義 key function で emission 抑止)
- 兆候の読み方:
  - extab に DELETEPOINTER → その PC は `new T(...)` の ctor call site。
    `li r3, SIZE; bl Alloc; mr. rN, r3; beq; bl ctor` が new 式の定型
  - extab に DESTROYBASE → その関数は derived ctor。base class を宣言する
  - return 直前の branch-over-branch + per-site `mr r3, r30` → implicit
    `return this` = 本物の ctor として書く (free function では出ない)
  - target が stmw/lmw を使う → `-use_lmw_stmw on` を TU に追加
- 注意: 多 fn TU で manual extab と混在させると section 並びが壊れる
  (同 note の「多 fn TU での制約」)。単独 fn TU なら制約なし
- real C++ でも解けない register-identity (EH 無関係のループ web swap 等) は
  ある (ItemObjectManager_Init 実例)。3 試行で動かなければ従来どおり退避

## トラブルシューティング: dtk 関連

- **既存 dtk blob を分割するワークフロー**: orphan symbol を add するときの細分化と同じパターン。`tools/add_orphan_symbols.py` を参考
- **`config/GNLJ82/build.sha1` は変えない**: target SHA-1 は元 binary 固定。一致しなければ source 側を直す
- **mw_comment_version は config.yml で project 全体設定**: 各 lib の `mw_version` (compiler binary 選択) とは別の軸。`.comment` section の差分が出るかは別 lib match で見えてくる予定
- **`dtk elf info` の target `.comment` は misleading**: matched object でも my-side と target で `.comment` の Version / Compiler version が違うことがある (例 HSD lib で my=Version 10/2.4.2.1 vs target=Version 11/2.4.7.1)。dtk-template の `obj/` 側 `.comment` は config.yml の `mw_comment_version` から来るデフォルト値の可能性が高く、**実コード生成 CW を必ずしも反映しない**。CW version 推定は prologue 順序 (`mflr` first vs `stwu` first) / frame layout / LR offset から判断すること。`.comment` の Version 比較を CW version の根拠にしない

## 関連 docs / notes

repo 内 (誰でも見える):

- `CONTRIBUTING.md` — 分担ルール (claim 方式) と PR 要件
- `docs/per_fn_matching_strategy.md` — asm_fn 退避 / bundle promote / hard-block patterns の戦略集
- `docs/large_extab_group_strategy.md` — 大 extab group の扱い
- `docs/notes/mkgp2-init-mixed-cw.md` — `.init` section に CW 1.0 と CW 2.7 が混在している (TU 単位で違う) ことの根拠と内訳
- `docs/notes/mkgp2-hsd-uses-cw-1.3.2.md` — HSD lib が CW 1.3.2 で build されている根拠 (prologue 順序)
- `docs/notes/hsd-sdata2-shared-pool.md` — HSD lib の `.sdata2` が shared pool TU (`_hsd_consts.c`) に集約され、各 TU から UND 参照する構造。`tools/postprocess_sdata2.py` が anonymous local → named UND を post-process する
- `docs/notes/melee-local-build.md` — melee (SSBM v1.2) のローカル build レシピ。CW 1.2.5n vs 1.3.2 の比較や HSD lib の構造確認に
- `docs/notes/dtk-ppceabi-overrides-symbols.md` — dtk PPCEABI heuristic が SDK 名を上書きする現象
- `ONBOARDING.md` — セッション kickoff 用のプロジェクト概要 (maintainer ローカルパス前提の記述を含む)
- `TODO.md` — 次手リスト (live)

maintainer (naari3) 環境のみ (user scope、repo 外):

- `mkgp2-ghidra` / `ghidra-mcp` skill — Ghidra MCP bridge の接続手順と bmp_output project 情報
- `ghidra-rename` skill — Ghidra 側 rename + plate comment + prototype の付け方
- `mkgp2docs` — Ghidra 解析の研究 notes 79 md (dolphin fork ローカル)
