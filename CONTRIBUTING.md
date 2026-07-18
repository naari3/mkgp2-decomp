# Contributing

> Most contributor docs in this repo are written in Japanese. Issues and PRs in
> English are welcome too.

mkgp2-decomp への貢献手順。matching workflow の技術的な本体は
[`.claude/skills/mkgp2-match/SKILL.md`](.claude/skills/mkgp2-match/SKILL.md)
にある (Claude Code なら project skill として自動ロードされる。人間もそのまま
手順書として読める)。この文書は「環境を作る」「担当を決める」「PR を出す」の
運用ルールに絞る。

## 1. 環境を作る

1. [README の Setup](README.md#setup) に従う。依存は
   [`docs/dependencies.md`](docs/dependencies.md) 参照
2. `main.dol` は **各自が合法的に入手した実物** を `orig/GNLJ82/sys/main.dol`
   に置く。SHA-1 `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65` に一致すること。
   このファイルおよびゲームアセットは絶対に commit しない
3. `python configure.py && ninja` を回して `build/GNLJ82/main.dol: OK`
   (SHA-1 一致) が出るのを確認してから作業に入る。ここが通らない状態で
   source を触らない

Ghidra について: maintainer の Ghidra project は共有していない。decompile
出力が欲しい場合は自前の Ghidra project に `main.dol` を import する。
命名済み symbol は `config/GNLJ82/symbols.txt` と
`tools/ghidra_symbol_dump.json` に committed 済みなので、これを流し込むと
読みやすくなる。struct 型定義 (KartMovement / CarObject / ItemEffect 系など
109 struct を含む 356 型) は Data Type Archive `tools/mkgp2_types.gdt` に
export 済み。Ghidra の Data Type Manager → 「Open File Archive」で開いて
program に適用すれば maintainer 側と同じ型が使える。Ghidra decompiler の生出力を repo に commit しないこと
(commit するのは自分で書いた matched C source のみ)。

## 2. 担当範囲を claim する

`config/GNLJ82/symbols.txt` / `splits.txt` / `configure.py` は全員が触る
集中管理ファイルで、同じ領域を 2 人が触るとほぼ確実に conflict する。
着手前に GitHub issue で担当範囲を宣言すること。

claim の単位:

- **address-contiguous な範囲** を 1 単位とする。dtk の splits は
  1 TU = 1 連続 range が前提
- **reversed extab group はまたげない / 割れない**。1 つの
  `build/GNLJ82/asm/auto_*_text*.s` ファイル = 1 group で、
  `grep -E '^\.fn ' build/GNLJ82/asm/auto_<addr>_text.s` で群内の全関数が
  わかる。`.fn` が 2 つ以上ある group は全関数を 1 TU で一括 match する
  必要がある (詳細は SKILL.md §7.5 制約 D)。group 全体を map したいときは
  `python tools/build_extab_map.py`
- issue には対象 address 範囲 (例 `0x8002F640..0x8002FA00`) と関数名を書く。
  先に claim された範囲には手を出さない

小さく始めたい場合は、`.fn` が 1 つだけの単独 split 可能な関数、または
`TODO.md` に載っている候補が向いている。

## 3. matching する

[`.claude/skills/mkgp2-match/SKILL.md`](.claude/skills/mkgp2-match/SKILL.md)
の手順に従う。要点だけ:

- 1 関数が C で 100% に届かないときは asm_fn 退避 / NonMatching 隔離という
  規約された逃げ道がある (SKILL.md §10.5)。途中状態 (89% 等) にも commit
  する価値はある
- 新規命名は `symbols.txt` に入れる。maintainer 側 Ghidra project への同期は
  maintainer が行うので気にしなくてよい
- 再現性のある観察 (CW の codegen 癖、dtk の挙動等) は `docs/notes/` に
  追記する。時系列で追記し、観察 (事実) と仮説 (推論) を分けて書く。
  後で覆った結論も消さず「訂正」を追記する

## 4. PR を出す

要件:

- `python configure.py && ninja` で `build/GNLJ82/main.dol: OK` (SHA-1 一致)
- build 末尾 `PROGRESS` の matched functions 数が **増えている** こと。
  SHA-1 OK でも自分の `.o` が link されていない「偽 match」があり得る
  (SKILL.md §9)。PR 本文に着手前後の数値を書く
- 変更は claim した範囲に閉じる。典型的な構成:
  `src/<lib>/<file>.c` + `configure.py` + `config/GNLJ82/splits.txt` +
  `config/GNLJ82/symbols.txt`
- `config/GNLJ82/build.sha1` は変更しない (target は元 binary 固定)
- ゲームアセット / `main.dol` / Ghidra decompiler 生出力を含めない
- commit message に対象関数 / address / size / SHA-1 verify 通過を明記

CI (GitHub Actions) でも build + SHA-1 verify が走る。green にしてから
review を求めること。

## License

このプロジェクトへの貢献は [CC0 1.0](LICENSE) で提供されたものとして
扱われる。同意できる場合のみ contribute すること。
