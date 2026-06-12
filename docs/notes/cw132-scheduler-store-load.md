# CW 1.3.2 命令スケジューラ: store-vs-load 順序と「pinned load」レバー

対象: `KartItem_GetBoostArmedAndTimer` (OnKartHit TU, 0x8004F14C, 4 命令 leaf)。
「同一 unit 内で asm のまま諦めていた leaf を mechanism-driven で promote する」手順の確定記録。
2026-06-12 に byte-identical promote 達成 (`build/GNLJ82/main.dol: OK`)。

観察 (事実) と仮説 (推論) を分ける。断定は避ける。

---

## 1. ターゲットと素朴な C の不一致 (観察)

```
target:  lfs f0, 0xb4(r3)   ; boostTimer (float)
         lbz r3, 0xb1(r3)   ; boostArmed (byte) -> r3 (= 返り値レジスタに直接)
         stfs f0, 0x0(r4)   ; *out = timer
         blr
```

素朴な C はどれもこの順序を出さない (observed, `tmp/getcur/boostsweep.py`):

| source 形 | mwcc 1.3.2 出力 | 差分 |
|---|---|---|
| `*out=self->boostTimer; return self->boostArmed;` (store-first) | `lfs; stfs; lbz r3` | stfs と lbz が逆 (store-first) |
| `unsigned char a=self->boostArmed; *out=self->boostTimer; return a;` (load-first) | `lbz r0; lfs; mr r3,r0; stfs` | byte が r0 経由 + mr 1 命令増 |
| `float t=...; unsigned char a=...; *out=t; return a;` (4 文, float 先) | `lbz r0; lfs; mr r3,r0; stfs` | 同上 |

3 命令の並びは「lfs; **lbz**; stfs」(byte が中央) のときだけ byte が r3 直行になる。
これがターゲット。素朴形では出ない。

---

## 2. スケジューラの白箱化 (観察)

mwcceppc_132.exe (Ghidra: bmp_output `/mwcceppc_132.exe`) のリスト・スケジューラ:

- `FUN_00506e10` — driver。processor model table `DAT_005df8f8` を `DAT_005e90ea` で選択、
  per-block scheduler を呼ぶ。**2 回**呼ばれる (arg 0 = pre-coloring, arg 1 = post-coloring)。
- `FUN_00506f20` — per-block list scheduler。node list を構築 (alloc 0x1a/node)、
  依存エッジを `FUN_00507230` で張り、priority 計算後に schedule loop。
  emit は scheduled order で `FUN_004dc270`。
- `FUN_005070f0` — ready-set の PICK。tie-break チェーン:
  - A: urgency (deadline `node+0x14` ≤ cycle を優先)
  - B: successor-freeing 数 (pred-count==1 の後続を数え、多い方)
  - C: latency (`node+0x16`、大きい方)
  - D: opcode table `DAT_005bee81[op*0x12]` (小さい方)。**ただし gate `DAT_005e86a0` が 0 = 無効**
  - 最終 fallback: **ready-list 順 (= 命令の emission 順)**

node layout (`FUN_00506f20` の alloc 0x1a):
`+0x00 next  +0x04 prev  +0x08 succ-edge-list  +0x0c insn  +0x12 readytime(u16)  +0x14 deadline(u16)  +0x16 latency(u16)  +0x18 predcount/in-deg(s16, 0 で eligible)`。
`insn+0x20 = opcode index`, `insn+0x14 = flags`。
probe: `tmp_probe/probe_sched.js` (`FUN_005070f0` を hook し ready list 全 node を dump)。

観測 opcode: 142=lfs (lat 6 pre/4 post), 150=stfs (4/2), 21=lbz (lat 4 post), 139=mr (1), 17=blr (0)。

---

## 3. store-vs-load は tie-break ではなく「保守的 aliasing 依存エッジ」(観察 → 仮説)

`FUN_00507230` は store `*out=...` と byte-load `self->boostArmed` の間に
**順序エッジ**を張る (両者が alias しうる: out が self 内を指す可能性を否定できない)。

- エッジの**向き = source のプログラム順**。
  - store-first source (`*out=...; return self->b1;`) → store→load エッジ → store が先。
  - load-first source (`a=self->b1; *out=...;`) → load→store エッジ → store が後 (最後)。
- これは probe_sched.js で確認 (boost.c vs boost2.c でエッジ向きが反転)。

→ store を最後に回す (`lbz` を `stfs` より前に) には load-first source が必要。**条件1**。

---

## 4. lfs-vs-lbz は emission 順 tie-break。素朴形で詰む理由 (観察 → 仮説)

lfs (float-load) と lbz (byte-load) の間にはエッジが無い (互いに alias しない)。
両者は cycle 0 で pred=0、同時 ready。tie-break チェーン A–D は差を付けず、
**ready-list 順 (emission 順)** で決まる。

emission 順を決めるのは scheduler の前段 (instruction selection)。観測した規則 (仮説):

- **単一用途の float-load は store に bundle され、store 文の地点で emit される。**
  load-first source では byte-load 文 (1 文目) が store 文 (2 文目) より先に emit される
  ため、emission 順は `lbz, lfs, stfs`。
- cycle 0 で lfs より lbz が先に picked → **lfs が lbz より後**になる。
  lbz 実行時点で self (r3) はまだ lfs に必要 → byte は r3 に置けず r0 経由 + `mr r3,r0`。

→ ターゲット (lfs; lbz; stfs) には「lfs を lbz より**前**に emit」が要る。**条件2**。

条件1 (load-first, store 最後) と 条件2 (lfs 先 emit) は素朴形では両立しない:
load-first にすると byte 文が先 → lbz が先 emit (条件2 を破る)。

---

## 5. レバー: float-load を source 地点に pin する (観察、確定的に byte-identical)

float-load を store に bundle させず、宣言地点で先に materialize させれば条件2 を満たす。

確認した pin 方法 (`tmp/getcur/boostsweep2.py`, `boost_realstruct.py`、実 struct で再現):

1. **volatile-qualified read** (採用):
   ```c
   float t = *(volatile float *)&self->boostTimer;  /* lfs を source 地点に pin */
   unsigned char a = self->boostArmed;
   *out = t;
   return a;
   ```
   → `lfs f0,0xb4(r3); lbz r3,0xb1(r3); stfs f0,0x0(r4); blr` = **EXACT**。
   volatile read は sink/defer 不可なので、宣言地点 (byte-load 文より前) で lfs を emit。
2. `volatile CarObjGetterView *s = self;` で view 全体を volatile 化しても同一の EXACT 一致。
3. **二重ストア** (`*out=f; out[1]=f;`) でも float が複数用途になり lfs が先 emit され、
   先頭 3 命令が EXACT 一致 (semantics が違うので採用不可、機構の裏付け probe)。

採用形は `vol-read-f` (float read のみ volatile)。`src/game/auto_ONKARTHIT_block.c`
の `KartItem_GetBoostArmedAndTimer` に適用、`build/GNLJ82/main.dol: OK` (byte-identical)。

### 5.1 volatile に関する留保 (仮説 + 注意)

- 元ソースが volatile だった保証は無い。**non-volatile のどの形もこの順序を再現しなかった**
  (boostsweep.py / boostsweep2.py で広く掃いた) ため、現状 volatile が唯一の byte-identical 構文。
- boostTimer は physics が毎フレーム更新する live state なので、getter が volatile read する
  解釈は不自然ではない (仮説)。ただし「元がそうだった」と断定はしない。
- これは matching device。より faithful な non-volatile 構文が将来見つかれば差し替え可。

---

## 6. 一般化: 「leaf store/return-read tie-break」family への手順

同 family (leaf で `*out = self->floatField; return self->byteField;` 系) の手順:

1. 素朴形 (store-first / load-first / 4 文) を掃く。`lfs; lbz; stfs` が出れば即採用。
2. 出ない場合、ターゲットが `lfs; lbz; stfs` (byte 中央, r3 直行) なら:
   - load-first source で store を最後に回す (条件1)
   - float read を `*(volatile float*)&...` で pin して lfs を先 emit (条件2)
3. objdiff / dtk disasm で EXACT 一致を確認 → full build `ninja build/GNLJ82/ok`。

probe 資産: `tmp/getcur/boostsweep.py`, `boostsweep2.py`, `boost_realstruct.py`,
`tmp_probe/probe_sched.js` (scheduler ready-list dump)。

---

## 7. 横展開検証: KartItem_GetCarVelocityVec3 (2026-06-12, 11/13 まで前進)

「volatile-pin lever は GetBoostArmedAndTimer 1 個だけか」の検証として、同 TU の別 leaf
`KartItem_GetCarVelocityVec3` (0x..., 13 命令) に適用。これは source-sweep (`velsweep.py`) で
「どの形もターゲット順を出さない」と諦めていた leaf。Vec3 を out へコピー + dead stack temp 付き。

ターゲット (n=13):
```
lwz r3,0x28(r3); lfs f2,0x184; lfs f1,0x180; lfs f0,0x17c;   ; 3 load を先に (vz=f2,vy=f1,vx=f0)
stfs f1,0xc(r1); stfs f0,0x0(r4); stfs f1,0x4(r4);           ; dead/out 交互
stfs f0,0x8(r1); stfs f2,0x10(r1); stfs f2,0x8(r4); ...
```

進捗 (観察):
- 素朴な `Vec3 v` field-copy → temp が完全 DCE され n=8 (frame 無し)。dead store が消える。
- `volatile Vec3 v` で dead store は残るが reload 発生 → n=16 (`velsweep.py` の dead-end)。
- **volatile-pin した float read (`float x=*(volatile float*)&mv->vx;…`) + `volatile Vec3 v` で reload 解消 → n=13** (ターゲットと同命令数、3 load 先行)。lever が効いた。
- read 順 xyz + dead-store 順 yxz (`v.y=y;v.x=x;v.z=z`) + out 順 xyz で **11/13 一致** (`velsweep2.py`)。
  **全 6 store + 全 register が一致**。残差は load 2 本 (lfs vz/vx) の emission 順だけ。

残る 2/13 (観察 + 仮説):
- ターゲットの load emission 順は**降順アドレス** (0x184→0x180→0x17c)、register は**使用順** (out.x が先 → vx=f0、out.z が後 → vz=f2)。つまり「最初に emit した load (vz) が最高 reg f2、最後の load (vx) が最低 reg f0」という**逆対応**。
- volatile-pin は emission 順 = read 順 = register 割当を**結合**してしまう (pin zyx → vz=f0)。ターゲットは emission(降順) と register(使用順) を**分離**しており、source の read/store 順では到達不能だった (read×temp 全 permutation を `_v6` sweep で掃いても max 11/13)。
- **仮説**: 降順 load 順は scheduler の latency 隠蔽 (最後に使う vz を最初に load して最大の遅延猶予) によるもので、register は store/使用順で別途割当。この「降順 emission × 使用順 register」状態は source read 順操作では出せず、allocator/scheduler の trace が要る (GetBoostArmedAndTimer で load 順を pin で制御できたのとは別レイヤ)。

結論 (現時点): lever/法は GetBoostArmedAndTimer 以外にも効く (この leaf を放棄状態 n=16 → 11/13 まで前進)。

### 7.1 allocator/scheduler trace の結果 (2026-06-12, succFree tie-break 同定)

`tmp_probe/probe_sched.js` で plain-read 形 (`vec_plain.c`) を trace。pre-coloring scheduler の
ready-list を解析:
- `op=34` (succFree=3) = `lwz movement` (3 float-load を養う)。
- `op=142` ×3 = vx/vy/vz の lfs。**3 つのうち「最初の volatile dead-store を養う load」だけ succFree=1**、他は 0。
- scheduler は succFree の高い node を先に PICK (tie-break B)。→ **どの load が最初に emit されるかは「最初の volatile dead-store の値」で決まる** (creation/宣言順より優先)。

これで register/emission の分離法が判明し 11/13 まで前進した:
- **register 割当 (どの値=f0)** = ローカル**宣言順** (`float x,y,z` → vx=f0)。
- **load emission 順** = 最初の volatile dead-store の値 (succFree) → その後は creation/代入順。
- **dead-store emission 順** = volatile の**ソース順** (volatile store は相互に reorder 不可)。

`Mv*mv; float x,y,z; volatile Vec3 v;` を宣言し、代入を z,y,x 順 (load emission 用)、
宣言を x,y,z 順 (register 用) に**分離**することで register と load 順を独立制御できた。

### 7.2 残る 2/13 の機構的ブロック (観察 → 仮説、現時点で source 到達不能)

ターゲットは **load を vz 先**で emit しつつ **dead-store を v.y 先**で emit する。
volatile Vec3 では「最初の dead-store」が次の二役を**同時に**負う:
1. その load に succFree=1 を与え **最初の load pick を支配** (→ 最初の dead-store は v.z でないと vz が先に出ない)
2. それ自身が**最初に emit される** (volatile = strict source 順 → 最初の dead-store emit が v.y でないとストア順が合わない)

→ 「最初の dead-store = v.z」(load 用) と「= v.y」(store 用) が**両立しない**。volatile 単一チェーンでは詰む。
2 方向の 11/13 (dead=yxz でストア全一致/load 反転、dead=zyx で load 一致/ストア 2 個違い) はこの二択の表裏。
out-store を先に置く / 全 dead×out permutation も掃いたが (100+ 形) max 11/13。

**仮説**: ターゲットの dead-store は volatile temp ではなく、**非 volatile で DCE を免れた dead-store**
(inline 展開された callee の stack temp、または out/mv の alias 不確定による scratch 材料化) から来ており、
dead-store 群が strict chain でないため scheduler が load-pick と独立に並べ替えられる。simple C の
volatile 構文ではこの「生存する非 volatile dead-store」を再現できず、13/13 は未到達。

結論: 法は 2 個目 (GetCarVelocityVec3) を放棄状態から 11/13 まで動かし、最後の 2/13 を阻む機構
(volatile-chain の succFree/emission 二役) を trace で同定。完全一致には別系統の dead-store 生存構文が要る。
probe: `velsweep2.py`, `tmp_probe/vec_plain.c` + `probe_sched.js`。
