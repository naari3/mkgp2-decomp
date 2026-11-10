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

## c2_b7_pobj_20261105
Source: Codex worker c2_b7_pobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 27 fn / 18076 B.

pobj rescue: all raw .data bytes can agree while objdiff text reports R_PPC_NONE argument mismatches if target data symbol spans class info plus strings. Splitting symbols at genuine class-info/string boundaries makes all owned sections and functions 100% without code or postprocess changes.

## c2_i12_jobj_20261105
Source: Codex worker c2_i12_jobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 33 fn / 13040 B.

jobj rescue: 33 functions / 13040 bytes isolated with owned sections 100% (full-link pending). Splitting canonical static inline dirty helper directly creates local copies whose calls cannot resolve to the original address. A private adapter aliases the canonical header helpers and supplies genuine global inline (weak) equivalents with named shared assertion strings. Primary native functions remain verbatim. Weak CheckDepend and SetMtxDirty copies must be discarded in favor of the strong fallback originals, and weak MtxIsDirty copies in favor of the new strong native helper. MWCC .sdata defaults to align 8 even for char[4]/char[5]; a new TU at target .sdata address 0x806D0DC4 would grow layout by 4 bytes. Keep those strings in an existing contiguous fallback pool and reference them extern. The 40-byte IK rodata target has a final 16-byte unit vector; use a native float[4] (1,1,1,0) viewed as Vec3 to preserve its genuine trailing zero.

## c3_u16_jobj_20261105
Source: Codex worker c3_u16_jobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 13 fn / 5544 B.

c3 jobj_load unlock: canonical small assertion file/text references remove a spurious pooled-base live range and restore fn_802CFB68 recursive register allocation exactly. ResolveRefs/AddChild require one local shared string-pool base. ResolveRefsAll matches by explicit four-level traversal with progressively outlined ref/ID helpers; cache child during ref increment and initialize child joint before child jobj. MObjUpdateFunc text/data exact still needs named constant exports: material fallback references lbl_806DCBCC. A separate native .sdata2 constants TU plus existing postprocess_sdata2 mechanism preserves exports without duplicated anonymous constants. DATA_ALIGN4_TUS required at .data804FC214.

## c5_s23_fn80197f24_20261105
Source: Codex worker c5_s23_fn80197f24_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 816 B.

c5_s23: HSD_JObjCheckDepend dirty test as switch(dirty) { case 0: ...; break; } preserves target beq body + unconditional exit rather than optimizer folded bne exit. Text300 exact. Existing jobj_unlock_private.h avoids private assertion strings after shared pools move to NonMatching jobj_data_nm.c. HSD_MaterialAlloc already exact96 only needed flag promotion. Full source-linked SHA-1 OK.

## c14_u15_20261106
Source: Codex worker c14_u15_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u15: HSD_JObjDispAll (802CF3B0, 1348 B) improves 94.16321 -> 98.76855% by three explicit inline traversal levels, specializing the instance-child view as nonnull and using actual outlined SetupMatrix/camera/matrix helper declarations at deeper levels. Baseline recursive inline leaves an addic. stack-address NULL test, impossible camera branch and extra saved flags copies (1396 B). Directly embedding matrix body instead expands 1852 B (59.47181%) because inline depth changes. Flat explicit expansion gives exact1348 B at98.36498% but wrong stack ordering; inline tiers restore all stack offsets at98.76855%. Final remaining outer parameter homes r29/r26/r27/r28 versus target r26/r27/r28/r29 and leaf walker/base coalescing r25 versus target distinct r24; stop at3 hypotheses. Sole-function TU remains NonMatching; full fallback DOL SHA-1 OK, native gain0.

## c16_u121_20261106
Source: Codex worker c16_u121_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2372 B.

c16_u121: JObjUpdateFunc802CE454 matches2372B by extracting callback traversal into static inline helper with helper-local node and compile-time byte/float selector, then path-point lookup/clamp into another inline helper with local jp. This fixes type r27, jp/walkers r28 without permutations (fresh99.763916 ->99.94098 ->99.97471). Final three relocation rows disappear by assigning compiler switch-table data804FCA50..804FCB38 to jobj_tail; split surrounding shared assertion fallback pool at CA50 and CB38. Text2372/data232 all100, native main.elf addr802CE454/size2372, full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No EH, padding or DATA_ALIGN4 needed.

## c17_u12_20261107
Source: Codex worker c17_u12_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 47 fn / 6152 B.

c17_u12: baselib/cobj unlock yields 47 native functions / 6152 B. setupBottomHalfCamera 716 B reaches exact via double tan with float-rounded argument/result. HSD_CObjSetCurrent 1284 B needs double scales against signed reference width/height globals 640/480, not render-mode viWidth/viHeight. The newer eye helper is success-returning without fallback writes; fabs/FLT_MIN changes improve upvec/roll helpers to ~99%, but folded output-pointer null-test branch remains. SetUpVector reports/asserts invalid input and only stores a changed normalized vector. Seven contiguous native TUs (one constants-only) use canonical shared diagnostic symbols; original coarse data pools stay fallback-backed. CObjInfoInit original 140 B body remains NM because original pooled-data context is unavailable after B. The jump table starts 804FC52C and requires existing DATA_ALIGN4_TUS handling. Export all 80 B constants at 806DCC08..58 as typed data. Explicit NULL initializers are essential for exported cobj_default_class/current: plain tentative definitions reverse their order despite .sbss objdiff 100% (all zeros). First full link differed in exactly seven r13 displacements; final source-linked SHA-1 OK.

## c17_u29_20261107
Source: Codex worker c17_u29_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 400 B.

c17_u29: HSD_JObjSetCurrent 802D0F50 (400B) requires inline canonical reference/destruction logic and shared current global jobj_bss_806D21C4. Inline helpers with explicit caller-local pool argument lbl_804FC9A8 preserve target r31 assertion base across both Ref/Unref; direct global-offset expressions rematerialize base at both assertions (87.70%). Explicit pool helper argument reaches 100% text. Restore existing owned sdata strings jobj.c[7], jp[3], prev[5] before eff[4]/robj[5], remove unowned duplicate class/private BSS scaffold, then Matching. No new split, filler or EH. Source-linked final ELF 802D0F50/400 and all five data labels exact; full DOL SHA-1 OK.

## c17_u47_20261107
Source: Codex worker c17_u47_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 112 B.

c17_u47: jobj_dirty baseline reported 0% because its global inline SetMtxDirty had no emitted symbol, while unrelated reset/walk scaffolding emitted outside its split. Strong native C definition using jobj_rescue_private.h restores canonical shared assertions. if(dirty)return folds target branch pair (96.07143%,108B); switch(dirty){case 0: SetMtxDirtySub(jobj); break;} preserves target112B exactly, the same established CheckDepend zero-case idiom. Only assigned source and Matching flag changed. Final ELF strong global802CD7B8/112, actual source link edge, full DOL SHA-1 OK.

## c18_u4_20261107
Source: Codex worker c18_u4_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1240 B.

c18_u4: cobj_nm2 upvec2roll802C74F4/496B and roll2upvec802C76E4/744B become exact by retaining camera/eye-object validation as the outer if/else and moving !eye failure into a nested early return in its valid branch. The original combined four-way OR folds the known stack output pointer but leaves beq plus an extra b; the nested form produces target bne into the valid body. Both +4B size errors disappear and standard sdata2 postprocessing resolves all constant relocations without any data/split/tool changes. Fresh objdiff98.870964/99.19355 ->100/100, whole text1240 exact. Promote existing TU; source edge and final ELF addresses/sizes verified; full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Native gain2fn/1240B.

## c18_u8_20261107
Source: Codex worker c18_u8_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u8: SetUpVector802C7A34 fresh text94.58763 improves97.08247 at exact776B by caller-local class-descriptor pool (hsdCObj+0xD8 origin,+0xE4 up,+0xF0 diagnostic) passed to inline upvec helper and checking eye output separately before cobj/eyepos/interest validity. The latter removes a compiler-retained branch from folded stack output NULL test. Only r31/r30/r29 allocation/prologue residual remains. Whole-setter pool helper worsens93.68557/772B; helper-local pool worsens95.07732/788B. Original data range cannot move wholesale because matched cobj.c switch table occupies804FC52C..560 between hsdCObj and vectors/messages. No ranges transferred; singleton function stays honest NM.

## c18_u7_20261107
Source: Codex worker c18_u7_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u7: HSD_CObjSetRoll 802C7EC8 (1088 B) improves fresh96.04412 to99.88971. Mirror canonical dirty setter as extern inline and use __fabs in local float abs helper; specialize private eye-vector helper for known local output to remove folded output-pointer branch; direct (float)__fabs(eye.y) under double comparison restores abs result f1. Final five operand-only rows at7FFC/8000/8004/8010/8020 swap eye.y f2 vs targetf3 and double1.0 f3 vs targetf2. Three hypotheses exhausted; singleton remains NonMatching. No owned data/EH or split changes; full fallback DOL SHA-1 OK; native gain0.

## c18_u155_20261107
Source: Codex worker c18_u155_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 44 B.

c18_u155: HSD_JObjDispAll802CF3B0/1348 improves98.76855->99.85163 by consuming outer jobj parameter in sibling for loop instead of separate child local. This fixes root/view/flags/rendermode homes to targetr26/r27/r28/r29 and all propagated flag masks. Residual8operand rows: first two leaf child loops source r25 vs targetr24 at802CF5B0/5B8/5CC/5D0 and802CF7D4/7DC/7F0/7F4. Leaf inline traversal helper, canonical child/next accessors and even minimal8B getter outline at exhausted inline depth; avoid repeating. Leaf local inner scope and next-tier parameter-walker reuse are byte invariant. Existing six-hypothesis allowance exhausted; retain improved honest NM, no B cut for sole-function TU. Full fallback DOL SHA1 exact; no native gain.

## c19_u166_20261107
Source: Codex worker c19_u166_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 612 B.

c19_u166: setupTopHalfCamera802C669C/612B becomes100% from fresh99.08497%/616B by replacing bottom=viewport.ymax; bottom=bottom<efbHeight?bottom:efbHeight with bottom=viewport.ymax<efbHeight?viewport.ymax:efbHeight. Direct field reads remove extra fmr f0,f2 and restore target clamp destination f2; existing sdata2 postprocess then resolves all shifted constants. Positive branch-local height computation99.052284%, separate scoped scissor-bottom99.08497%, positive in-place if/else98.90849%/608B do not match. No data ranges, EH, padding or new flags needed. Existing TU promoted Matching, report complete612B/1fn, actual main.elf strong symbol802C669C/612 and source link edge verified, full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.
