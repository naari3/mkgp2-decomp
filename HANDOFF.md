# HANDOFF: batch_fable_onkarthit_recheck2 (2026-06-11)

## VERDICT: PINNED-confirmed (Fable recheck, degree-reducing source levers all negative, 0 promote)

KartItem_OnKartHit 0x8004A238 を 96.38% から degree-reducing source 構造で promote
できるかの Fable 再検証 (brief: docs/notes/onkarthit-fable-recheck-brief.md)。
round 3 (Opus x2) の「PINNED」結論で唯一未試行だった interference-degree 削減方向を
4 構造で試し、**全て negative**。param home (self r26 / victim r27, target r30/r31) は
degree をどれだけ下げても動かない。objdiff のみ使用、frida 不使用、shipped compiler 不接触。

worktree は asm body に復元済みで green (`ninja build/GNLJ82/ok` -> `build/GNLJ82/main.dol: OK`)。

## 実験ログ (全て 96.38% baseline = Appendix B body からの差分、builds 計 7)

測定: `tmp/apply_and_measure.py` (body splice -> .o build -> objdiff match% + param home 抽出)。
baseline 再現確認: 96.38%, homes self=r26 victim=r27 bus=r30 (round 3 と一致)。

| 実験 | 構造 | match% | self home | victim home | 判定 |
|---|---|---|---|---|---|
| baseline | Appendix B そのまま | 96.38% | r26 | r27 | (基準) |
| E1 victim-tail-kill | `disp=victim->dispatcher; st=victim->state1f4;` を memset 前に hoist、dispatch 部は local 参照 | 92.54% | **r25** | **r26** | NEGATIVE — 新規 web (disp/st, 遅い key) が param を outrank し home はむしろ降下 |
| E2 late-param-copy | `sc=self; vc=victim;` を memset 直前 (= 遅い位置) に置き tail で copy を使用 | 96.38% | r26 | r27 | NEGATIVE — baseline と **byte-identical**。round 3 lever 2 (先頭 copy) の一般化: copy の位置に関係なく param-merge が coalesce し param web identity (最低 key) が保たれる |
| E3/E3b volatile-slot-kill | copy を `volatile` slot 化して coalesce を遮断。disasm 検証済: 両 param とも 478 行中 row 300/304 (関数の ~63%) の stw で完全に死亡、tail (bool 群/memset/mtx copy/fp cluster/dispatch = 短命 web 最密集域) と一切干渉しない | 87.36% | r26 | r27 | NEGATIVE — degree 大幅削減でも home **微動だにせず** |
| E4 tail-helper | tail (drv2 以降の b25..b28 + memset + dispatch) を static helper `OnKartHit_DispatchTail(self, victim, rm)` に切り出し (inline されない大きさ、実 call として残存) | 52.82% | r27 | r28 | NEGATIVE — callee web 集合が縮小した分 +1 しただけで、param は縮小後の集合の**最下位のまま** (相対順位不変) |

## 解釈 (仮説と観測の区別)

OBSERVED:
- live range / interference degree をどう削っても (E3b: tail 全域で dead、E4: call で終端)、
  param web の callee pool 内の相対順位は最下位から動かない。
- 新しい callee web を足すと param はさらに下がる (E1)。callee web を減らすと相対最下位の
  まま絶対番号だけ上がる (E4)。
- param への copy は出生位置によらず coalesce され、merge 後の web は param 側の identity
  を保持する (E2 = round 3 lever 2 の位置一般化)。

仮説 (高確度): round 3 の OPEN 仮説「pin の正体は degree であり、degree を下げれば
re-rank しうる」は**否定**された。coloring 順位は web-birth key (param = 最低 32/33) で
決まっており、degree は順位に寄与していないと思われる。param を locals より上位に置く
source lever は C の表現空間には存在しない可能性が高い (= source-closed)。
残る未試行方向があるとすれば C 言語の外: 元実装が C++ である場合、this/引数の渡り方や
暗黙の temporaries が web key 構成自体を変えるルートは試していない (本 brief の範囲外)。

## docs_notes

### docs/notes/cw132-allocator-phase2f-research.md round 3 節への追記 prose (そのまま貼れる形)

```
### Fable recheck: degree-reducing levers all NEGATIVE -- OnKartHit source-closed (2026-06-11, batch_fable_onkarthit_recheck2)

Round 3's OPEN direction (attack the param's interference DEGREE instead of
web-birth order) was probed with 4 structures from the 96.38% Appendix-B body,
objdiff-only (no frida, no compiler contact): (1) hoisting victim's tail fields
(dispatcher/state1f4) into pre-memset locals dropped match to 92.54% and moved
the params DOWN (r25/r26) -- the two new late-born webs outrank them; (2) late
param copies placed just before memset coalesce straight back (param-merge) and
are BYTE-IDENTICAL to baseline, generalizing round 3 lever 2: copy position is
irrelevant, the merged web keeps the param identity; (3) volatile-slot copies
(coalescing physically broken; disasm-verified both param webs die at the stw
at ~63% of the fn, zero interference with the entire bool/memset/mtx/dispatch
tail) leave homes EXACTLY at r26/r27 (87.36%); (4) splitting the whole tail
into a non-inlined static helper (params die at the call) shrinks the callee
set and the params stay at its BOTTOM (r27/r28 of an r27-based pool, 52.82%).

CONSEQUENCE: degree is NOT the pin -- no amount of live-range reduction
re-ranks a param web, and adding/removing callee webs only shifts the params'
absolute register while preserving their bottom rank. The coloring position of
param webs is fixed by their identity (lowest web-birth keys 32/33), refuting
round 3's open hypothesis. OnKartHit is source-closed within C: the
params-on-top partition (self=r30/victim=r31) is unreachable from any tried
source shape. Only untried route is outside C source space (e.g. C++-specific
web-key construction), out of scope for this family. Probe harness:
batch_fable_onkarthit_recheck2 worktree tmp/ (apply_and_measure.py, make_e3.py,
make_e4.py, restore_baseline.py).
```

### docs/notes/approachA-roadmap.md への 1 行 entry

```
- 2026-06-11 batch_fable_onkarthit_recheck2: OnKartHit 0x8004A238 Fable recheck — degree-reducing 4 構造全 negative (E1 hoist 92.54%/homes 降下, E2 late-copy byte-identical, E3b volatile-kill 87.36%/homes 不動, E4 helper 52.82%/相対最下位不変)。degree は pin ではなく key が pin。source-closed (C の範囲)、PINNED-confirmed、0 promote。
```

## 再現手段

- probe harness: `tmp/apply_and_measure.py` (splice + build + match% + home 抽出)、
  `tmp/restore_baseline.py` (Appendix B 復元)、`tmp/make_e3.py` / `tmp/make_e4.py` (変種生成)、
  `tmp/check_match.py`、disasm 産物 `tmp/e3_mine.s` / `tmp/e3b_mine.s`
- 出発 body: `docs/drafts/Class2_expansion_nearmatches.handoff.md` Appendix B (HEAD のまま)
- TU は `git checkout -- src/game/auto_ONKARTHIT_block.c` で復元済み、SHA-1 OK 確認済み

## 追補: C++-form probe (同 worktree、merge 後の follow-up)

VERDICT 更新: **C++ 軸も全 negative — register-identity family は C/C++ 両 source 空間で close 確定**。

standalone harness (tmp/cpp_probe_run.py、dtk-disasm ベースで mangled symbol 対応、
P0 検証で in-TU と同一 partition を再現確認) により 6 変種を測定:

| probe | 形 | homes (target self=r30/victim=r31) | 備考 |
|---|---|---|---|
| P0 | C baseline (検証) | r26/r27 | in-TU と同一 stream |
| P1 | C + full prototypes | r26/r27 | prototype 化は中立 |
| P2 | 同一 body を -lang=c++ (extern "C" free fn) | r26/r27 | C++ FE 単体は中立 |
| P3 | this-call method 形 | r26/r27 | this web も named param と同扱い |
| P4 | real virtual + method (base 無し) | r26/r27 | vptr が末尾 0x108 に置かれ offset 不一致 |
| P4b | **polymorphic base 派生** (vptr=0x0、offset 完全一致) | r26/r27 | 最忠実 C++ 形でも不動 |
| P5 | reference param | r26/r27 | |

副産物 (OnKartHit 以外にも効く新事実):
1. **real C++ virtual dispatch は target の r12-chain vcall 形を出す**
   (`lwz r12, 0x0(rX); lwz r12, 0x8/0x34(r12); mtctr; bctrl`)。C の明示 vt-struct 形が出す
   r6 中間 reg (OnKartHit 残差の 1 つ、6 sites) は **C-source artifact**。vcall 形だけが
   残差の park fn があれば C++ TU 化で解ける可能性がある。
2. **CW 1.3.2 は base 無し polymorphic class の vptr を class 末尾に置く**。mkgp2 binary は
   vptr=0x0 なので、元実装の class 群は polymorphic な基底からの派生 (P4b 形) と思われる。
   将来の C++ 再構成時の layout 指針。

probe files: tmp/probe_p0.c .. probe_p5.cpp, probe_p4b.cpp, probe_common*.h, cpp_probe_run.py

## 追補 2: inline-composition probe で VERDICT を再訂正 (詳細は main の docs が SoT)

「C/C++ 両空間で close」は過大だった。inline-splice composition (I1/I3) で partition が動き、
残差は param-class flip 1 点に縮約。OFOD/CAE flip pair も発見。詳細・次の一手は
docs/notes/cw132-allocator-phase2f-research.md 末尾「訂正 + inline-composition probe」節と
approachA-roadmap.md (Phase 3/4 は断念→保留に訂正、commit f4cc0b7)。
probe assets は本 worktree tmp/ (probe_i1.c / probe_i3.cpp / probe_i5.c / scan_param_class.py /
homes_detail.py / tu_probe.py / t_*.py)。

## 追補 3 (最終): IR-dump batch 完了、frida 可 session への引き継ぎ点

transplant matrix (M 系) / whole-binary scan / IR-dump 検証 / register hint の 4 軸を消化
(main commits 7cb0d1b, 32b3c59, c0da06b)。rank rule の同定は frida hook channel のみ残存。
引き継ぎ素材: tmp/probe_i3.cpp (残差 = 7-web permutation 1 点)、tmp/param_rank_scan.tsv、
tmp/irdump_run.py (+probe_*.log)、tools/compiler_probe/frida_colorer_probe.js (手法実証済み)。
次 batch 仕様は approachA-roadmap.md 末尾 entry と research note follow-up 5 節。


## 追補2: EF bool-form 深掘り — 「命令一致」撤回 + coalescing-pin の確証 (同 worktree、Fable 継続)

VERDICT 更新: round-3/追補1 の「key が pin」をさらに精密化 → **pin の正体は coalescing**。
EF (単一アーム bool) が「命令一致」とした in-session draft は**誤計測**で撤回。

### 撤回 (誤計測の訂正)

EF = dispatch bool を `b=0; if((flags&mask)!=0) b=1;` の単一アーム化した形。これが target と
reg-masked 100% / 0 diff と報告したが、diff カウンタが branch label を address のまま比較して
構造差を equal 扱いしていた bug。**label 正規化 (分岐先を行 index に写像) + reg masking** で
再検証 (tmp/verify_ef.py): EF vs target は 416 行・**真の差分 16**。命令一致ではない。

### 16 差分は全て partition の下流症状

- FP スケジュール ×4 (row ~81-90): 命令同一、`fsubs` と隣接 `lfs` の順が 1 行ずれ。base reg も
  target `0xc(r29)` vs EF `0xc(r31)` = partition。
- bool ゼロ自己流用 ×12 (row ~220-267): target は 0 初期化した callee-saved bool reg を 64bit
  `(flags&maskULL)` の上位語 `&0` 兼 `!=0` の compare-rhs に再利用 (`li r28,0; and r0,r0,r28;
  xor r3,r3,r28; bne set1; b done`)。ours は別 scratch (`li r4,0; beq done`)。同イディオム・
  ゼロ register 共有のみ差 = value/move-coalescing 差。

### 決定的観察: degree は target と同一

target victim=r31 は **row 5..390 live**、EF victim=r26 も **row 5..390 で完全に同一 range**。
self も両者ほぼ全域 live。**degree が等しいのに color が r31 vs r26 に分岐** → partition は
coalescing/value-numbering が決める (追補1 の「degree は pin でない」を直接証拠で裏付け、
さらに「key だけでなく coalescing」と精密化)。

### bool 綴り 6 形 sweep (label+reg 正規化 genuine-diff vs target)

single-arm 16 / empty-then 16 (CW が single-arm に潰す) / clean-two-arm-no-preinit 37 (+4 li-0) /
direct `b=(f&m)!=0` 96 / ternary 68 / chained-zero 16。clean イディオム形は 16 が床で params 低位、
params を上げる形 (direct/ternary→r27/r28) は bool→int 変換イディオムが崩壊 (+50-80 diff)。
**clean イディオム ⇔ params 高位 が排他**。target の bool-zero-reuse coalescing を再現する形は未発見。

### round-3 OPEN 「degree-reducing」の論理的 CLOSE

target 自身が self を row 406・victim を row 390 まで使う = params は target でも最大 degree。
live range を縮める形は target と必ず乖離する。よって degree-reducing 方向は閉。

### 確定

OnKartHit は **coalescing-pin** で source-closed (C/C++ 両空間)。残差 16 は coalescing 由来の
partition 症状。matched asm 維持 (SHA-1 OK)。probe: tmp/verify_ef.py, verify_any.py, make_{f,g,h}.py,
make_direct.py, dump_region.py, dump_fp.py, lastuse{,_ef}.py。


## 追補3: frida colorer 直接観測 — arg-key pinning を機構レベルで確定 (同 worktree)

「coalescing pin (仮説)」を frida 実測で精密化 → **argument-key pinning + key 順 callee-saved 割当**。
private copy (tmp_probe/mwcceppc_priv.exe、SHA-1 一致) + tools/compiler_probe/frida_colorer_probe.js を
build CFLAGS で EF に適用 (tmp/colorer_ef_run.py, keyscan.py)。GPR class node の key/deg/reg/flags 実測:

- params self/victim = key 32/33 (最低) flags=0x02 (非coalesce) adjN=135/137 (最大干渉) → r25/r26 (最下位)。
- rm=key94→r31, bus=key52→r30, bools=key46-51 flags=0x42 (coalesced) → r27-r30。
- **callee-saved reg は key 厳密順** (最高 key→r31 降順)。degree/adjN は reg を決めない。
- **arg key は 32/33 に hard-pin**: param 使用前に長寿命 web を1つ born させる probe (tmp/probe_earlyweb.c)
  でも param は 32/33 不動、新 web は key43。引数 web は entry で最優先に予約される。
- **competitor 除去でも上がらない**: bus cache 除去 (tmp/probe_nobus.c) でも param は r25/r26 不動
  (rm+bools がまだ上位)。params を上げるには全競合 web を消す = 関数を壊す必要。
- target は bus も最大寿命 (r25 span 7..398) なのに self/victim を r30/r31・bus を r25 に置く =
  arg key > bus key が必要 = hard-pin と矛盾 = source 不可。

結論精密化: param は **coalesce されていない** (flags 0x02)。park の正体は coalescing でなく
**arg-key pin (32/33) + key 順割当 + 6 個の高 key 長寿命競合 web (rm/bus/5 bools)**。
family floor を algorithm level で characterize: 引数以外に最大寿命 callee-saved web が >=3 ある fn は
引数が最下位に park し、どの source lever も arg web の key を動かせない。
