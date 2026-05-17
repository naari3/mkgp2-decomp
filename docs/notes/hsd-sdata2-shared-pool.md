# mkgp2 HSD lib は sdata2 を shared pool に集約している

`fobj.c` を match させた経緯 (commit `725e3bc`、`tools/postprocess_sdata2.py`) で確認した sdata2 layout。

## 観察

melee と mkgp2 の HSD lib で、`.sdata2` の TU 配置が決定的に違う。

| | melee (CW 1.2.5n) | mkgp2 (CW 1.3.2) |
|---|---|---|
| 各 HSD TU の `.sdata2` | 各 TU に存在 (例 fobj.c は 0x28 bytes) | **存在しない** |
| `0.0f` / `(f32)s16` magic | TU 内 anonymous local (`@114`, `@116` 等) | shared pool TU の named global (`lbl_806DCC58`, `lbl_806DCC60`) を **UND** 参照 |
| sda21 reloc target | local symbol への参照 | extern UND への参照 |

実証 (melee/mkgp2 双方を build して target fobj.o の disasm 比較):

```asm
; melee target fobj.o (HSD_FObjReqAnimAll)
lfd f3, "@116"@sda21(r0)   ; 同 TU 内の anonymous local
lfs f0, "@114"@sda21(r0)

; mkgp2 target fobj.o (HSD_FObjReqAnimAll)
lfd f3, lbl_806DCC60@sda21(r0)   ; 別 TU の named global
lfs f0, lbl_806DCC58@sda21(r0)
```

## 原因の仮説 (2 通り、どちらか)

A) mkgp2 開発者が手動で pool TU (`_hsd_consts.c` 相当) を作り、`const float lbl_806DCC58 = 0.0f` 等を定義 + 各 TU から extern 参照に書き換えた。

B) HSD lib を静的 link 済みの `.a` として持ち込み、リンク時に全 .o の `.sdata2` が concat されて 1 セクションになった。decomp 時 dtk は origin TU を判別できず、単一 `.sdata2` として split した。

(B) が自然 (商用 GC binary の標準的な姿)。HAL の pre-built HSD lib + mkgp2 ゲームコード、を `mwldeppc` で link。

## 反映

- `src/sysdolphin/baselib/_hsd_consts.c` に `lbl_806DCC58/60` を pool TU として定義
- 各 HSD TU は anonymous local sdata2 を出すが、`tools/postprocess_sdata2.py` がそれを target .o の reloc 名 (= shared pool の named UND) に書き換える
- splits.txt で `_hsd_consts.c: .sdata2 start:0x806DCC58 end:0x806DCC68` を割り当て

## なぜ post-process が必要か

CW (1.3.2) は `0.0f` / `(f32)s16` magic を unconditionally **anonymous local sdata2 symbol** として emit する。source 側で `extern const float lbl_806DCC58` を参照しても、CW は別の anonymous local を生成する。

つまり source レベルでは「lbl_806DCC58 を extern 参照する」と書けない。CW の codegen 動作のため、`@N` anonymous local が emit され、これを `tools/postprocess_sdata2.py` で named UND に rewrite している。

## 確認済み TU

| TU | sda21 reloc 有無 | post-process 適用 |
|---|---|---|
| `aobj.c` | なし | no-op |
| `dobj.c` | なし | no-op |
| `fobj.c` | あり (`@26`→`lbl_806DCC58`, `@28`→`lbl_806DCC60`) | 動作中 |
| `jobj.c` 系 (3 TU) | なし | no-op |
| `robj.c` | なし | no-op |

`HSD_FObjReqAnimAll` のように literal 演算 (`0.0f` への代入、s16 → float 変換) を含む関数を持つ TU で必要。

## 他 TU も pool に依存しているか

HSD lib の他 TU (`HSD_*Init*` 系等) でも sda21 reloc が出る可能性。new TU を match するときに `objdump -r` で `R_PPC_EMB_SDA21 lbl_806DCC*` が見えたら、post-process が自動で kick する (target .o の reloc を SoT に名前解決)。
