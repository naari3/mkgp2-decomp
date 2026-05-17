# melee (SSBM) のローカル build レシピ

mkgp2 の HSD lib は melee の HAL sysdolphin lib を流用したもの。matching で「melee 側はどう build されているか」を実物で確認したいときの手順。

## 前提

- melee project: `~/src/github.com/doldecomp/melee` にローカル clone 済み
- 対応 ISO version: **NTSC v1.2 (Rev 2)**
  - main.dol SHA1: `08e0bf20134dfcb260699671004527b2d6bb1a45` (= `config/GALE01/build.sha1`)
  - v1.00 や v1.01 では build sha check が通らない
- ISO 形式: dtk は CISO / RVZ / NKit.iso をネイティブに読める

## main.dol 抽出

mkgp2-decomp の build/tools/dtk.exe を流用 (melee 側にも tools/dtk.exe あり、どちらでも OK):

```sh
build/tools/dtk.exe disc info "<path-to-ssbm-rev2>.ciso"
# → Disc 1, Revision 2 が確認できれば OK

build/tools/dtk.exe disc extract "<path-to-ssbm-rev2>.ciso" /tmp/melee_extract/ --quiet
powershell -Command "Get-FileHash -Algorithm SHA1 /tmp/melee_extract/sys/main.dol"
# → 08E0BF20134DFCB260699671004527B2D6BB1A45 を確認
```

## melee project に main.dol を配置

melee は `orig/GALE01/sys/main.dol` を期待 (`.gitkeep` だけ存在する gap)。

```sh
cp /tmp/melee_extract/sys/main.dol ~/src/github.com/doldecomp/melee/orig/GALE01/sys/main.dol
```

## configure + build

```sh
pushd ~/src/github.com/doldecomp/melee
python configure.py     # build.ninja 生成 (first stage)
ninja                   # full build (~10 分、初回は toolchain download も)
popd
```

成功すると `Progress: All: 92.06% fuzzy, ... linked (770 / 976 files)` のような出力。
`build/GALE01/main.dol: OK` で sha check 通過。

## 何ができるか

build artifact `~/src/github.com/doldecomp/melee/build/GALE01/` に full な per-TU 情報が揃う:

- `src/sysdolphin/baselib/<file>.o` — melee 側 my-source build object (CW 1.2.5n)
- `obj/sysdolphin/baselib/<file>.o` — target object (asm から dtk が生成)
- `report.json` — per-function match progress

## mkgp2 比較で使う典型ケース

1. **同等関数の melee asm を取る** — mkgp2 の対応関数を decomp する際の source 仮説に。

   ```sh
   build/tools/dtk.exe elf disasm \
     ~/src/github.com/doldecomp/melee/build/GALE01/obj/sysdolphin/baselib/jobj.o \
     /tmp/melee_jobj.s
   ```

2. **section layout 比較** — melee splits.txt vs mkgp2 splits.txt で、TU が `.sdata2` を持つか / `.data` を持つか確認。HSD lib の `.sdata2` 構造が両者で違う件は `hsd-sdata2-shared-pool.md` を参照。

3. **inline policy 比較** — melee CW 1.2.5n と mkgp2 CW 1.3.2 で同 source の出力 byte 数を比較できる。例: `HSD_JObjReqAnimAllByFlags` は melee 268 bytes / mkgp2 (my-side CW 1.3.2) 594 bytes / mkgp2 target 712 bytes (= 手動 6-level unroll の結果)。

## 注意

- melee と mkgp2 で **同じ source は使えない** ことが多い。CW version が違う + mkgp2 が独自に手動 unroll しているケースあり (例 `HSD_JObjReqAnimAllByFlags`)。
- melee の source structure は参考にするが、mkgp2 が独自最適化された binary の場合は source 形を再構築する必要がある。
- melee のローカル build は **academic な確認用**。直接 source を流用してマッチさせる用途ではない。
