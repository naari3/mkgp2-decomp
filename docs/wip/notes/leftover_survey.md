# C/C++にできなかった関数・asmのまま残った関数の調査（2026-10-25）

対象: origin/main `ac371ea`（#347 マージ後）をクリーンビルドした `build/GNLJ82/report.json`。
集計スクリプト: 元DOLの extabindex（0x8001F3A0..）から「例外テーブルを持つ関数」を拾い、`src/` の `asm` 関数定義と configure.py の Matching/NonMatching を突き合わせた。

## 0. 全体像

全 7612 関数のうち matched は 6238。ただし「matched」には inline asm のまま TU に入っている関数も含まれる。

| 状態 | ゲーム側 (G1〜G7) | ライブラリ (SDK/MSL/HSD/MusyX/Triforce/THP 等) |
|---|---|---|
| C/C++ で 100% 一致 | 3735 | 1928 |
| inline asm（matched 扱い） | 482 | 93 |
| NonMatching（C/C++ はあるが 100% 未満） | 460 | 98 |
| 未分割の asm（auto_* ユニット） | 815 | 1 |

グループ別（ゲーム側）:

| | C/C++一致 | inline asm | NonMatching | 未分割asm |
|---|---|---|---|---|
| G1 0x80003100.. | 920 | 201 | 87 | 187 |
| G2 0x8009B98C.. | 647 | 96 | 127 | 17 |
| G3 0x801077C8.. | 409 | 172 | 30 | 0 |
| G4 0x8015A6E4.. | 560 | 1 | 20 | 151 |
| G5 0x801A9D58.. | 548 | 5 | 44 | 230 |
| G6 0x801FC1E0.. | 550 | 5 | 144 | 230 |
| G7 0x8024D764.. | 101 | 2 | 8 | 0 |

つまり「本当に C/C++ になっていない」ゲーム関数は 482 + 460 + 815 ≒ 1760 個。

## 1. 未分割のまま（815 関数、約 620KB）

できなかったのではなく、作業を区切った時点で手が届いていない範囲。G5 230 (204KB)、G6 230 (87KB)、G4 151 (173KB)、G1 187 (133KB)、G2 17 (22KB)。
このうち 745 個（91%）は元バイナリで extab を持つ、つまり C++ 例外有効でコンパイルされた関数。
G2 の 17 個は名前つきで、TaMode_Init/FrameUpdate、WarpDashMgr_Init と std::vector<WarpZone> の insert/reserve、CourseData_LoadPathTable、KartShellRibbonDraw（下書き 87.6%）など。

## 2. inline asm のまま残ったもの（ゲーム 482、ライブラリ 93）

### ゲーム側 482 個（G1 201 / G3 172 / G2 96 / 他 13、約 425KB）
- 521/549 個が「extab を手で出力する asm TU」（`__declspec(section ".extab_user")`）に入っている。中身は例外テーブル付きの C++ 関数で、C で書くと extab が合わないので、asm と手書き extab で枠だけ合わせ、そこから 1 関数ずつ C に昇格させる方式だった。昇格が途中で止まったのがこの 482 個。
- 226 ファイル（313 関数）はファイル全体が asm。ほとんどが巨大関数 1 個の入れ物で、手が付いていない。最大級: CGameCoin_Update 8.5KB、ShadowBillboard_Tick 7.7KB、Scene fn_801558CC 5.9KB、SuikaBall_Update 5.7KB、VSMode_FrameUpdate 5.0KB、CreditMgr_DrawCoinCreditBanner、clFlowChara_Update、clFlowRound_Update、PowItem_TickActive、VSMode_Init。
- 54 ファイル（236 関数）は C と asm が混ざっている。昇格途中の TU で、auto_ONKARTHIT_block.c 39、Scene_8014E0C4.cpp 26、RaceHud_80147470.cpp 25、SpriteHandle.cpp 18、CGameCoin_8012BF5C.cpp 16、auto_800A8F4C_block.c 12 など。
- 意図的に残した理由がわかっているもの:
  - **extab の順序が逆（reversed extab）で TU を分けられない**: dtk が分割を拒否するので 1 TU にまとめるしかない。auto_ONKARTHIT_block（KartItem_OnKartHit 系）、HeapStats、ItemEffectBus、RivalRun など。
  - **std::list 風ヘルパの命令順 3 個違い**: SpriteHandle の fn_8012215C 他、SceneList_80157940..。
  - **レジスタ割り当て**: TexMgr_Apply（i/self 入れ替え）、clFlowItem_Draw、clFlowItemSelect_CommitSlotAnim（別々の誘導ポインタ）、fn_8011EC18（r0/r4）。
  - **プール基底**: PoseChar ctor（.rodata を TU が所有しないと `lis/addi` 基底が再現しない）。
  - **G3 の旧保留**: fn_80114990, fn_801193F4, fn_80117494, fn_80117E08, fn_8010C110。

### ライブラリ側 93 個: ほとんどは元から asm
PPCArch 23、OSCache 10、OSContext 10、TRK targimpl 7、HSD mtx 6、OS 5、mtx/vec（paired single）、MusyX reverb/chorus など。元の SDK ソースでも asm 関数なので、これで正しい。

## 3. NonMatching（C/C++ にはしたが 100% にならない: ゲーム 460、ライブラリ 98）

一致率の分布:
- ゲーム: 0%（TU に枠はあるが未記述）60 / 90% 未満 58 / 90〜99% 222 / 99% 以上 120
- ライブラリ: 0% 1 / 90% 未満 32 / 90〜99% 46 / 99% 以上 19

0% の内訳: FlowCardCheck 24（カードの CharaItem/Item/Date ページ未記述）、fn_801DEF94（AI ステアリング）13、resultscene.cpp 12、anon_801FC1E0 4、carobject.cpp 3。
未一致が多い TU: FlowCardCheck 27、anon_8021F088 22（平均 96%）、fn_801DEF94 20、fn_801BAA88 19（NameEntry キーボード）、DbgMenu 14、resultscene 14、Triforce acsocket 12、clItemBoxManager 10、amnet 10、RankLog 9、HSD texpdag 9。

詰まった理由のカテゴリ（各スレッドのメモ・TIPS.md からの集約。件数は「90% 以上で止まっている約 400 個」の大まかな内訳）:

### A. レジスタ割り当て（最多。体感で 6 割以上）
命令列は同じで GPR/FPR の番号だけが違うもの。コンパイラ版とフラグの総当たり（GC 1.2.5n〜2.7 × -inline/-use_lmw_stmw/-O）では直らず、ソースの形（宣言順、inline ヘルパ化、リテラルか extern const か）でしか動かない。lit.py（float リテラル総当たり）で 17+4 個、decomp-permuter で 1 個（`kind++; kind--;` という fakematch）は拾えたが、残りは手詰まり。
- 例: SoundMgr_Play（find ループの r6/r7）、clFlowRound_Update（self=r31 と TU 所有プール基底の優先順）、MWRTTI `__dynamic_cast`（2 か所の入れ替え）、THP fn_80299D58、Terrain_GetGroundHeight 系（98%）、ClSound キュー fn_80193624、Triforce acsocket/amnet/amsrv 全般、HSD texp TExp2TevDesc、G2 の ItemObject_SpawnWithAlias など 98〜99.9% 群。
- 未解決パターン: ゼロを書き込んだレジスタを後のループカウンタに流用（`li r31,0; stw r31..; ループ i=r31`）、オフセット付き誘導変数（`addi r0,r27,0x2c; stwx`）vs ポインタ誘導変数（clFlowRound_Init / clFlowCup_Init）。

### B. 命令スケジューリング / ロード・ストア順
- `lwz r3,off(r3)` が `stw r0,0x14(r1)` より前に来る形: GC/2.6 + const ポインタでしか出ず、fn_801DBA34、fn_801EC698、KartItem_*（ONKARTHIT）などに残っている。
- sqrt 系で target は stwu が遅い。CardData_InitDefaults / PlayStats_CopyStatsBlock はエピローグとコピーの順序だけ違う。
- ItemEffect_TornadoLift / BossGrab: 行列コピーが「エイリアスしない」前提でスケジュールされている。`__restrict` でも再現しない。
- Item_BendVelocityByGroundProbe: `fneg` の前に生の結果を `stfs`。約 10 通り試して駄目。
- JumpDistanceMode_InitTimerDisplay: 十の位の計算が呼び出しの前か後か。

### C. データの所有・プール（文字列・.rodata・.bss）
関数が `lis/addi` で TU の先頭ラベルを基底にしてオフセットで参照する形は、その TU が該当 .rodata/.data/.bss を「定義」していないと再現しない。分割済み TU の境界と元のファイル境界がずれていると直せない。
- 例: Sci2Card_Tick / AllocAndOpenSci2（3 TU を 1 つに統合しないと無理）、FinalLapBanner_Init、Card_VerifyChecksum、PcbIdToIpAndModify、ClSound_PlayBgmStream、fn_8018CFC4 / fn_8016AF3C / fn_8016AB58（文字列プール基底が vtable ストアより前に巻き上げられる）、acLibMedia / acLibInit（.bss 共有基底。3 TU の統合が必要）、Gecko `__unexpected`。
- DrawEffect_KartDustRing_Update: オフセット 0 のアンカーで target は `addi rX,rY,0`、CW 1.3.2 は `mr` を出す（98%）。

### D. C++ 固有の構造（extab・RTTI・弱シンボル・sinit・STL）
- **extab の順序が逆**: 0x8015C41C..0x8016219C（resultscene.cpp）、0x8019E1A8..0x8019F5BC（carobject.cpp）、SpecialFace*、STLContainer、clDrawMan、CardTaskWelcome。複数関数を持つ C++ TU では MWCC 1.3.2 が関数を逆順に出すので、元の 1 ファイル単位でまとめて書かないと並ばない。
- **RTTI 型名の置き場所**: target は .rodata、このリポジトリの CW は .data に出す。cLNormal3DWrap.cpp（28 関数すべて 100% なのに TU は NonMatching）、anon_801FEBD8、DebugStageSelect_UpdateInput。テンプレート基底の弱い dtor が target では TU の最後に出る点も同じ TU で合わない。
- **sinit（グローバルオブジェクトの静的初期化）**: fn_801A1714、fn_801C1C14、clEzMenu の PTMF テーブル（fn_801F27B4）。
- **STL**: WarpZoneVector（std::vector の insert/reserve）、std::list ヘルパ（3 命令の順序）。
- **`new T` と ctor の extab cleanup**、メンバ dtor の null チェック入れ子なども同類だが、こちらはほぼ解決済み（TIPS.md 参照）。

### E. コンパイラ版・peephole の癖
- GC/2.6 でしか出ない色詰め（`li rX,-256; rlwimi`）: Scene_8014E0C4 は 2.6 で解決。fn_8015E608 と 801690xx 群の `__rlwimi` パターンは未解決。
- `0 == 0` が畳まれずに残る（fn_8018D64C）。u64 のテストで xor が 2 回出る（KartItem_QueryEffectStateFromIse）。if-conversion（NokoNokoChallenge_GetCoinDivisor）。
- `__ppc_eabi_init`（GC/1.0 + peephole off で解決済み）のように、正しい版を見つければ一発で直るものもあった。

### F. 分岐・switch の形
EffectStarBurst（switch 範囲チェック後の `b` が 1 個足りない）、CardRegister_Session_Tick（`bne body; b end`）、amsys fn_80293DD4（fallthrough する状態機械）、EffectVfx_KartChildAttached_RenderHook（`flags&2` の分岐が反転）。

### G. 元のコード自体が違う（参考ソースと別バージョン）
HSD TObjUpdateFunc（mkgp2 0x5CC vs melee 0x2FC）、texpdag SimplifyByMerge 33%（mkgp2 0x17C8 vs melee 0xA04）、THP デコーダ（dolsdk より古い版。IDCT は C ループ + asm ブロック）。

### ライブラリ側 NonMatching 98 の内訳
Triforce 52（acsocket 12、amnet 10、amjvs 8、ambackup 6 など。ほぼレジスタ割り当て）、HSD 38（texpdag 9、cobj 8、tobj 6、state/mobj/lobj。レジスタ・スケジュールに加えて G の版差）、THP 6、Runtime 2（MWRTTI）。

## 4. 「ほとんど C++ のクラスでは？」という前提について

**前提はほぼ正しい。**
- 元バイナリの extabindex は 4284 エントリあり、ゲーム側 5492 関数のうち 4252（77%）が extab を持つ（ライブラリは 32 だけ）。extab は「例外有効でコンパイルされた」印で、zlib のような C でも付くので単独では証拠にならない。ただし vtable、RTTI、`__ct__`/`__dt__`、`new`/`delete` の cleanup action、sinit がゲーム全域に出ていることも合わせると、ゲーム本体は C++ と見てよい。
- **ところがリポジトリ側は C で書いたものが多い**:
  - ゲームの Object は .c が 1543、.cpp が 480。
  - 一致済みゲーム関数は .c 2241 / .cpp 1494。
  - .c のうち 769 は `-Cpp_exceptions on`、64 は `#pragma cplusplus on`、19 は `-lang=c++` で、C++ として通している。
  - 書き方の主流は「self ポインタを取る extern "C" の自由関数 + extab_user_renames.json で名前合わせ」。ctor/dtor のリネームだけで 1427 行ある。
  - クラスのメンバとして書いた関数は、クラス外定義だけで約 400（84 ファイル）。`virtual` を使うファイルは 228。
  - 1 関数 1 ファイルの .c が多いのは、dtk の auto 分割に沿って関数単位で切り出したため。元のソースファイル境界はかなり崩れている。

**クラスのメソッドに書き直せば合いやすくなるか:**
- レジスタ割り当て・スケジューリング（A/B、最多）: **ほぼ効かない**。`this` 付きメンバ関数と self 付き自由関数は r3 に同じものが入り、生成コードは同じ。
- 効くのは C/D の「構造」系:
  - 元の .cpp 単位で TU をまとめ直すと、プール基底（C）、extab の逆順（D）、弱い inline の出力順、vtable/RTTI の置き場所、sinit がまとめて自然に再現できる見込みが高い。今の 1 関数 1 ファイル構成は、これらと相性が悪い。
  - 手書き extab の asm TU に入った 482 個と、未分割 745 個の EH 関数は、最初から「クラス + ローカルオブジェクトの dtor + new/delete」で書くのが一番素直。C で extab を真似る回り道（手書き extab → 1 関数ずつ昇格）が、昇格の止まった asm を大量に残した原因でもある。
- 注意点: RTTI 名が .rodata に出ない件と GC/2.6 でしか出ない形がある件から、ゲーム本体の一部は 1.3.2 ではない別バージョン（2.x 系）でビルドされた可能性がある。クラス化と並行して、TU ごとのコンパイラ版の見直しも必要。

## 5. 次ラウンドへの提案
1. 未分割 815 と全 asm ファイル 226 は、最初から C++ クラス + 元のファイル単位（extab が連続する範囲）で TU を切る。
2. NonMatching の 99% 以上（ゲーム 120 + ライブラリ 19）は、lit.py、宣言順の総当たり（hill.py/permsel.py）、permuter をまとめて回す。
3. プール基底が原因のもの（Sci2Card、acLib、FinalLapBanner など）は、TU の統合で解決できる。
4. RTTI 文字列の .rodata 問題は 1 回調べれば複数 TU がまとめて Matching になる（cLNormal3DWrap は関数がすべて 100%）。

## 追記（2026-10-25 20:xx、項目3・4の簡単なものに対処）
- PR #348: acLib の 3 TU と fn_802557B4 を 1 TU に統合し、.bss/.sbss を TU に持たせた。fn_80255640 と fn_802557B4 が一致し、+2。
- RTTI 型名は `#pragma readonly_strings on` で .rodata に出せることがわかった。anon_801FEBD8 と cLNormal3DWrap は、共有 RTTI 領域の所有と TU 統合まで必要なので保留。詳細は TIPS.md 末尾。
