# EggItem asm_fn → native C (2026-10-25)

unit claim #71 `retrofit:game/EggItem.c`。3 関数 (OnGroundDriftTick / Tick_HeldAndHoming /
Dispatch、計 3.3KB) を plain C + TU 全体 `-Cpp_exceptions on` で 100% match (commit 7703531)。
3 関数とも extab は 8 byte で EH action なし。C++ 化や extab_order.json 宣言は不要だった。

## 観測 (worker 報告)

- **jumptable の case 順**: body を共有する case が複数あるとき、jumptable の各 entry が
  どの body を指すかで source の case 順が決まる。Dispatch は case 0,3,4,7,9,5 の順で
  ないと .text は同一でも .data (jumptable) がずれて SHA-1 が合わなかった
- **ternary 引数と `mr r3` の位置**: `call(self, cond ? a : b, ...)` で `mr r3` が分岐前に
  上がる形は、IR の ECOND が call 引数に残ったときだけ出た。cond と arm で同じ定数を
  CSE した一時変数がまたがると ECOND が一時変数代入に落ちてこの形にならない。
  定数を local 変数に入れる (`thr = lbl_806D5E74;`) と再現した
- 引数の評価順も効く: prototype は
  `Item_AdvanceFallingDrop(void *self, float gravity, int *landed, float *groundY)` の順が必要
- **stack 上の Vec3 local**: 後に宣言した変数ほど低い SP offset に置かれた (本 TU 3 関数で一貫)
- `ninja dol_diff` が `jumptable_804215C0` の名前不一致 ERROR を出すが、DOL バイトは一致し
  SHA-1 OK。ShellItem の jumptable と同じ状況

## 仮説

- jumptable 順の依存は CW の switch lowering が case を source 順に走査して重複 body を
  先勝ちで割り当てるためと思われる (未検証)
