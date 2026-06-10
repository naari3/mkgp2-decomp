# approach A 完遂ロードマップ (auto_ONKARTHIT_block.c)

2026-06-11 開始。ゴール: TU 先頭から address 順に approach A (exceptions-on auto-extab) 区間を伸ばし、
EH scaffolding 関数 (KartItem_Dtor 0x8004E2B0 ほか) を C で promote する。
各 phase は前 phase の結果に依存する。観察 (事実) と仮説 (推論) を分けて時系列で追記すること。
結論が覆った場合も古い項目を消さず「訂正」を追記する。

背景: docs/per_fn_matching_strategy.md 14.1 (extab approach A/B, mix-failure rule) /
docs/notes/exceptions-on-eh-scaffolding-unpromotable.md (EH class, unlock 条件)

## Phase 一覧

| phase | 内容 | 状態 |
|---|---|---|
| 0 | class 1 の最終 probe (compiler patch rev / 未試行 pragma) | **進行中 (2026-06-11 dispatch)** |
| 1 | class-1 10 fn の回収 (salvage draft 適用) | Phase 0 の解法待ち |
| 2 | 先頭区間 index 0-17 の残り idiom 解決: class 2 (OnKartHit) / flavor 5 (MainUpdate) / flavor 4 (ProcessWarpAndDash) / ScopedTimer (FrameUpdate) | 未着手 |
| 3 | index 0-17 の manual extab 削除 + exceptions-on 再コンパイル (A 化)、1 fn ずつ SHA-1 検証 | 未着手 |
| 4 | KartItem_Dtor (index 18) ほか EH fn の A promote | 未着手 |

## 制約 (再確認)

- auto-extab は .extab_user より常に前に link される (14.1)。よって A 区間は TU 先頭から
  extab 持ち fn が欠けなく連続している必要がある
- index 0-17 はほぼ全て extab 持ち (KartItem_Dtor precan で「17 manual-extab fns precede」確認済み)
- 末尾 dtor 11 個の回収は Trap/Projectile (class 2) を含む TU ほぼ全域の A 化が前提 —
  Phase 4 の現実的な到達点は KartItem_Dtor + (InsertBefore) まで

## Phase 0 詳細

未試行として 14.2 に記録されている 2 手段の消化:

1. 手持ち mwcc の patch revision 違い (同 1.3.2 系の別ビルド含む) での
   branch-over-branch invert 挙動の差
2. 未 probe の pragma (peephole off 系、branch folding 系、CW 1.3.2 の pragma 全列挙から)

判定対象 shape (class 1, KartItem_OnKartHit 0x8004A238 ほか TU 内 9 fn / 19 sites):

```
or.  r0, rA, r0     # u64 flag test の結果
bne  L1
b    L2             # 空 fall-through
L1:
li   rD, 0x1
L2:
```

CW が全既知 form で emit するのは 1 命令短い `beq L2; li rD,1; L2:` (invert 形)。

go/no-go gate: 解けなければ class-1 10 fn + EH 13 fn は恒久 park、Phase 1 以降は中止。

## 時系列ログ

- 2026-06-11: roadmap 作成、Phase 0 dispatch。
