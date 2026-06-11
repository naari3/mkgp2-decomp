# CW 1.3.2 (mwcceppc) 内部を frida + Ghidra で実行時 trace する playbook

目的: 「この残差は source 制御できるか」を**推測でなく compiler 内部の実測で**判定するための再現手順。
register allocation / value-numbering / scheduling が source-closed かを示す/疑うときに使う。
[cw132-hardblock-index.md](cw132-hardblock-index.md) の A 群・C 群の根拠はここで作られる。

**位置づけ: main 主導の研究活動**。subagent の per-fn ループには入れない (frida 起動は重く、priv copy +
Ghidra 常駐が要る)。1 関数の即 park 判定は索引で済ませ、索引に無い構造的疑問のときだけここに降りる。

---

## 0. 絶対制約

- **出荷コンパイラ `build/compilers/GC/1.3.2/mwcceppc.exe` (SHA-1 `d8f9c36d62f66c2a044d5a20a132b79eeb2f36e5`)
  は絶対に改変しない**。trace は必ずコピーに対して行う。各セッション冒頭と終わりで SHA-1 を確認。
- frida は priv copy を spawn する。元 exe には attach しない。

---

## 1. 道具立て (capability の部品)

| 部品 | 所在 | 役割 |
|---|---|---|
| priv copy | `tmp_probe/mwcceppc_priv.exe` (gitignore=scratch) | frida spawn 対象。出荷 exe を cp して作る |
| Ghidra project | `bmp_output` の program `/mwcceppc_132.exe` | 静的解析 (decompile/disasm)。[[mkgp2-ghidra]] skill 参照。ASLR off, image_base `0x400000` ⇒ **VA = file offset**、frida の `va(a)=base+(a-0x400000)` がそのまま効く |
| frida runner | `tmp_probe/run_probe.py` (汎用), `run_color.py` | priv を spawn → JS load → probe .c を compile → `rpc.dump()` → detach |
| probe JS | `tmp_probe/probe_color.js` (colorer), `probe_foldcond.js` (VN fold 判定 + 代表形成), `probe_vn2.js` (VN table walk) | 各機構の hook |
| verify harness | `tools/compiler_probe/onkarthit_vn/verify_any.py` (+ `cpp_probe_run.py`) | probe .c を compile→dtk disasm→target と reg+fp マスク diff |
| frida 実行 | `uv run` (PEP723 inline metadata)。[[frida-windows]] skill 参照 | Frida 17.x。Module API はインスタンスメソッド |

tmp_probe は gitignore (scratch) なので probe 群はコミットされない。**雛形は本 doc §3-§5 から再生できる**。
研究結論は `docs/notes/cw132-*.md` に残す (これが SoT)。

---

## 2. セットアップ

```powershell
# priv copy (出荷 exe は触らない)
Copy-Item build/compilers/GC/1.3.2/mwcceppc.exe tmp_probe/mwcceppc_priv.exe
# Ghidra: bmp_output 起動済みなら connect_instance(project="bmp_output") → open /mwcceppc_132.exe
# trace 実行
cd tmp_probe; uv run run_probe.py probe_foldcond.js   # 既定 src = probe_ef.c
```

Ghidra 未起動なら [[mkgp2-ghidra]] の自動起動手順。

---

## 3. frida runner 雛形 (run_probe.py の核)

```python
# /// script
# requires-python = ">=3.10"
# dependencies = ["frida"]
# ///
import os, sys, time, frida
HERE = os.path.dirname(os.path.abspath(__file__)); WT = os.path.abspath(os.path.join(HERE, ".."))
PRIV = os.path.join(HERE, "mwcceppc_priv.exe")
# BASE_FLAGS = 実際の TU の cflags に合わせる (下は OnKartHit TU 用の例)
BASE_FLAGS = ["-nodefaults","-proc","gekko","-align","powerpc","-enum","int","-fp","hardware",
  "-Cpp_exceptions","off","-O4,p","-inline","auto","-pragma","cats off","-pragma","warn_notinlined off",
  "-maxerrors","1","-nosyspath","-RTTI","off","-fp_contract","on","-str","reuse","-multibyte",
  "-i",os.path.join(WT,"include"),"-i",os.path.join(WT,"build/GNLJ82/include"),"-i",os.path.join(WT,"tmp"),
  "-i",os.path.join(WT,"tools/compiler_probe/onkarthit_vn"),
  "-DBUILD_VERSION=0","-DVERSION_GNLJ82","-DNDEBUG=1","-Cpp_exceptions","on","-use_lmw_stmw","on","-lang=c"]
def main():
    js, src = sys.argv[1], (sys.argv[2] if len(sys.argv)>2 else DEFAULT_SRC)
    obj = os.path.join(HERE,"probe_out.o")
    if os.path.exists(obj): os.remove(obj)
    dev = frida.get_local_device()
    pid = dev.spawn([PRIV]+BASE_FLAGS+["-c",src,"-o",obj], cwd=HERE)
    sess = dev.attach(pid); sc = sess.create_script(open(js,encoding="utf-8").read(), runtime="v8")
    sc.on("message", lambda m,d: print(m.get("payload") if m["type"]=="send" else m, flush=True))
    sc.set_log_handler(lambda lvl,txt: print(txt, flush=True))
    sc.load(); dev.resume(pid)
    for _ in range(120):
        time.sleep(0.1)
        if os.path.exists(obj): time.sleep(0.4); break
    try: print("[dump]", sc.exports_sync.dump())
    except Exception as e: print("[dump failed]", e)
    sess.detach()
```

frida JS の共通 boilerplate:
```javascript
'use strict';
const IMAGE_BASE=0x400000; let BASE=null;
function modBase(){ if(BASE)return BASE;
  for(const n of ['mwcceppc_priv.exe','mwcceppc.exe']){try{const b=Module.getBaseAddress(n);if(b)return BASE=b;}catch(e){}}
  return BASE=Process.enumerateModules()[0].base; }
function va(a){ return modBase().add(a-IMAGE_BASE); }   // VA→runtime addr (ASLR off なので base 一定)
```

---

## 4. 落とし穴 (実測済み)

- **mid-instruction の inline hook は crash しうる**: hook 点の直後が branch target だと、Frida の
  trampoline relocation が分岐を壊す (例: `0x5081c8` の置換 store は次命令 `0x5081cc` が複数 JNZ の
  target で crash)。→ **branch target でない命令**で hook し、native 条件を JS で複製して観測する
  (例: fold は `0x508182` で hook して `0x5081c8` の置換条件を再現)。
- **function-entry/leave hook は安全**。中身を読むなら entry/leave + 自前 walk。
- **onLeave で読むのは処理後の状態**: VN の代表 (transient) は def 処理でクリアされるため、onLeave walk
  では「クリア後」しか見えない。形成過程は代表設定関数 (`FUN_005092b0` 等) を直接 hook して捉える。
- **`rpc.dump()` はプロセス終了と競合**: obj 生成後すぐ exit して script destroyed になる。
  → periodic に full dump (例: VN pass leave の N 回ごとに全集計を出す) し、exit 前の最後の出力を採る。
- **ExitProcess hook は発火しないことがある**。periodic dump が確実。

---

## 5. mwcc 内部 module map (white-box 済み)

VA = file offset (image_base 0x400000, ASLR off)。`FUN_xxxx` は Ghidra `/mwcceppc_132.exe` の名前。

### Value Numbering (ValueNumbering.c, assert 文字列 @`0x5bbb28`)
- **`FUN_00508140`** — 1 basic block の VN 処理。命令を辿り、各命令で:
  1. **operand 置換 (= fold)**: use-operand (`*pcVar7==0 && (flags&0xb)==1`) について VN-table を引き、
     その**代表 web** (entry[1]) が同 value-id なら operand の web 参照を代表に置換 (store @`0x5081c8`)。
     置換条件本体は branch-target でない `0x508182` で観測可。
  2. **def 処理**: 命令 flag (`puVar4[5]`) で分岐 — copy(`&0x10`)→`FUN_005092b0`、
     immediate/leaf(`&8 & 0x1000100`)→`FUN_005086a0`、move(`&2`)→`FUN_005088d0`/`FUN_00508aa0`、
     arithmetic(`&4`)→`FUN_00510b60` + def-web の**代表クリア+新 value-id**。
- **`FUN_005092b0(srcRec,dstRec)`** — copy 伝播。`dst=src` のとき dst.value-id=src.value-id、
  **dst の代表 web (entry[1]) = src.rep (無ければ src 自身)** を設定。**代表を非ゼロにするのは事実上これだけ**
  (+`FUN_00509010` 経由)。⇒ **fold 対象になるのは copy-backed web のみ**。immediate `li 0` は代表を持たない。
- **`FUN_005093f0(node,src)`** — 値番号割当 (undo-journal 付き)。src==0→新 value-id (`DAT_005e8abc++`)、
  src≠0→src の web の value-id 継承。VN-table の代表 web は触らない。
- **`FUN_005086a0`** — immediate/leaf def の VN。def-web の代表クリア+新 value-id 後、`FUN_00510b60` で hash。
- **`FUN_00510b60`** — value-number hash 本体 (alias class 0/1/2 で分岐、`FUN_005093f0` を呼ぶ)。

VN-table 構造 (class = register class, GPR=4):
- table base = `*(0x5df954 + class*4)`、web w の entry = base + `w*0xc`。entry[0]=value-id, [1]=代表 web, [2]=chain。
- boundary (有効 web 下限) = `*(0x5e8778 + class*4)`、web count = `*(0x5e8a7c + class*4)`。
- value-id 採番カウンタ = `DAT_005e8abc`。current class byte = `DAT_005e931f`。

### Register Coloring (Coloring.c, assert @`0x5bbb18`/`0x177`)
- **`FUN_005077b0`** RegisterColoring driver: class 0..4 ループ、各 class で `FUN_00579cf0` を while で回す。
- **`FUN_00579cf0`** per-class color step: build → coalesce (`FUN_0057a1f0`, union-find, `parent[max]=min` ⇒
  survivor=**MIN key**) → adjacency → simplify/select。
- **`FUN_00507b50`** simplify (Chaitin-Briggs): 低 degree node を push して **select stack** (singly linked) を作る。
  spill-pick section `0x507c02-0x507caa`。spill ratio = degree/cost (cost=loop-weighted use count)。
- **`FUN_00507a30`** select: stack の head (=最後に push) から **callee register を降順に**割り当て。
- node 配列 base = `*(0x5e87d0)` (class register で index)、node = base+id*4 の指す先。
  node fields: +0x12 initial degree(s16), +0x14 color(=物理 reg 番号, s16), +0x16 flags(u16), +0x18 neighbor count(s16)。
- **color 値 = 物理レジスタ番号そのもの** (bit/値で rN)。param web の key は最小 (hard-pin) かつ最大 degree → 最下位 reg に固定。

### その他
- numbering chain: `FUN_00435c60` → `FUN_004cf530` (RegisterInfo.c) → `FUN_004fd680`。
- per-pass IR dump gate: `DAT_005e9409` / `DAT_005e90ec` (IrOptimizer FUN_0042ddd0)。
  emit stub の多くは空 (`FUN_004ffdb0` は単一 RET) — dump 経路は基本死んでいる。深追い非推奨。

---

## 6. probe の型 (再生用)

- **colorer 観測** (`probe_color.js`): `FUN_00507b50` onEnter で class4 各 web の initial degree/nbcount を
  snapshot、`FUN_00507a30` onLeave で color(=reg) を読む。→ どの web がどの reg に着色されたか。
- **VN fold 判定** (`probe_foldcond.js`): `0x508182` で use-operand の (class,web,value,rep,rep.value) を読み
  native 条件 (`rep≠0 && rep≥boundary && value==rep.value`) を複製して fold する/しないを全数記録。
  `FUN_005092b0` entry で copy 伝播 (代表形成) を記録。periodic full dump。
- **VN table walk** (`probe_vn2.js`): `FUN_00508140` onLeave で class4 の全 web の value-id/代表を walk
  (post-state のみ見える点に注意)。

---

## 7. 既知の適用例

- OnKartHit の VN fold が source 非制御である根拠 ⇒ [cw132-allocator-phase2f-research.md](cw132-allocator-phase2f-research.md)
  (colorer 全機構 white-box + fold = copy-backed 代表置換 + 実行時 trace で fold 18件は全て 64bit-load CSE、
  定数0/bool 統合 0 件)。

関連 skill: [[mkgp2-ghidra]] (mwcceppc Ghidra project), [[frida-windows]] (frida 手順)。
