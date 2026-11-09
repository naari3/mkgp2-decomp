# mkgp2-decomp 並列作業プラン (2026-10-24)

## セットアップ (各スレッド共通)
repo root で `bash tools/cloud_setup.sh` を実行するだけ。
ISO から main.dol 抽出 (SHA-1 検証付き)、ユーザーがアップロードした compilers zip の展開、
GitHub から binutils/wibo/dtk/objdiff/sjiswrap 取得、configure、full build + `build/GNLJ82/main.dol: OK` 確認まで行う (初回 ~3 分)。
ISO / main.dol / compilers は絶対に commit しない (orig/ と build/ は gitignore 済み)。

再ビルド: `python3 configure.py --binutils build/binutils --compilers build/compilers --wrapper build/tools/wibo && ninja all_source progress build/GNLJ82/report.json build/GNLJ82/ok`

## 手順書
- `.claude/skills/mkgp2-match/SKILL.md` (matching 手順の正本)、`docs/unit_first_strategy.md`、`CONTRIBUTING.md`
- native C/C++ + automatic EH が既定。asm_fn 退避は genuine progress に数えない。NonMatching 隔離は可
- PR 要件: SHA-1 OK、PROGRESS の matched functions が増えていること (前後の数値を PR 本文に)
- `tools/claim_unit.py` は gh が使えないので不要。下の担当範囲が claim の代わり
- 共有ファイル (configure.py / splits.txt / symbols.txt) は自分の範囲の行だけ触る。PR 前に main を取り込んで再 build
- `tools/plan_units.py`、`tools/build_extab_map.py` (extab group) を活用。1 つの auto_*_text.s = 分割不可の extab group

## 担当範囲 (.text アドレス、未 match コード量がほぼ均等 ~316KB)
| # | 範囲 | 主な対象 |
|---|---|---|
| 1 | 0x80003100..0x8009B98C | Sci2Card, card, RenderObj, ShadowBillboard, NameCheck, TransitionEffect, PCBComm (このスレッドが担当) |
| 2 | 0x8009B98C..0x801077C8 | ItemObject, DrawEffect, KartFx, GabyouItem, Effect, RaceScene |
| 3 | 0x801077C8..0x8015A6E4 | CGameCoin, SuikaBall, NokoNokoChallenge, SpriteHandle, BossKoopa |
| 4 | 0x8015A6E4..0x801A9D58 | KartMovement, RaceAnnouncer, ClStream, ClSound, Sprite |
| 5 | 0x801A9D58..0x801FC1E0 | AI, clFlowCourse, KartPhysics, VoiceEvent, KartController |
| 6 | 0x801FC1E0..0x8024D764 | MiniGame, ItemSelectState, CoinResultScene, clFlowItem, CollisionTest |
| 7 | 0x8024D764..0x802731B4 と 0x802BD0FC..末尾 | Dolphin SDK (GX, OS, EXI, SI, ...) / MSL / Runtime。doldecomp/mkdd 等を参照 |
| 8 | 0x802731B4..0x802BD0FC | HSD sysdolphin。937 関数の巨大 extab group 1 つ。`docs/large_extab_group_strategy.md` / `docs/large_tu_cpp_conversion.md` を先に読む |

ベースライン (commit 41d7ee3): matched 12.04%, 1117 / 7614 functions。
