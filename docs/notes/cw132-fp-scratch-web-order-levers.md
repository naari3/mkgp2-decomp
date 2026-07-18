# CW 1.3.2 fp scratch web-order levers (Vec2 unit, 2026-07-19)

batch_text_800d6188_vec2 (Vec2_RotateZ/Y/X, 0x800D6188..0x800D6338) で、命令列・schedule 完全一致 + fp scratch register 割付のみ相違の状態から、source 形状 3 点の組合せで byte-identical に到達した。fp-numbering park family と即断する前に試す価値のある lever 集。

観察 (6 variant の割付表から帰納した仮説、CW 1.3.2 -O4,p):
- volatile fp pool の割付順序モデル: [最初に READ される named local] → [expression temp を評価順] → [残りの named local を宣言順]。named local の初期化 load は宣言位置ではなく first-use 位置で web key を得る (decl 順の入替えは単独では無効、volatile cast も無効)。
- fmsubs/fmadds の dest は「その命令で死ぬ operand のうち最も番号の低い register」を再利用する (target の fmadds f1 = c の register 再利用は、他 web の割付が合えば自動で出る)。

lever 3 点 (組合せで有効、src/game/Vec2.c header にも記載):
1. `__restrict` を両 pointer param に付ける。CW 1.3.2 は `__restrict` を受理し、store 越えの load CSE + load group への hoist が有効化される (先例: src/game/Vec3_ScaleXZ.c)。restrict 無しでは最初の out-> store 以降の in-> 読みが reload になる。
2. passthrough 成分は named local に置かず、最終文で `out->z = in->z;` と直読みする。restrict 下ではこの load が pre-store load group に入り、最も早い web key を得て f0 を取る。named local 経由だと web が末尾グループに落ちて f4 になる。
3. 回転結果は named local (rx/ry) 経由で store する。naming により result web が b*c の fmuls temp と merge され、temp が b/a より先に f2 を取る。直接 expression store だと t=f3/b=f2 に swap する。

試行の dead end (再試行不要): plain named locals の宣言順 permutation は割付不変 (use-order 支配、3 permutation で同一出力)。struct copy `Vec3 v = *in;` は stack frame 経由 (frame 0x40) になり形状崩壊。static inline helper 化 (Phase 2f re-key 期待、passthrough を引数に含む形も含む) はこのケースでは無効。
