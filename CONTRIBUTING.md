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

## 2. 担当を claim する

claim・完了条件・受け入れ基準の正本は [`docs/matching_rules.md`](docs/matching_rules.md)
(naari3 側の Claude スレッドと onmokoworks 側の worker の共通ルール)。要点:

- TU に着手する直前に issue を立てる: タイトル `[unit-claim] retrofit:<configure.py のパス>`、
  ラベル `unit-claim`、担当者は自分。gh / API / MCP どれで立ててもよい
- その TU から離れたら (取り込み済み・成果なし・中止のどれでも) すぐ閉じる。
  開いている claim は今作業している数までに抑える
- 立てる前に開いている `unit-claim` を全件 (ページ指定で) 確認し、
  他人の claim がある TU には merge や rename 経由でも手を出さない

## 3. matching する

- 手順: [`.claude/skills/mkgp2-match/SKILL.md`](.claude/skills/mkgp2-match/SKILL.md)
- レジスタ割当だけが合わないとき: [`docs/regalloc_patterns.md`](docs/regalloc_patterns.md)
- 他の人がすでに試して諦めた関数と WIP の場所: [`docs/gave_up.md`](docs/gave_up.md)
- 自動 sweep ツール (pragmasweep / stmtsweep / typesweep / shapesweep など):
  [`tools/README.md`](tools/README.md)
- 再現性のある観察 (CW の codegen 癖、dtk の挙動等) は `docs/notes/` に追記する

## 4. main に入れる

`docs/matching_rules.md` §2 のとおり: `origin/main` に rebase し、
`rm -f build/GNLJ82/main.dol && ninja` で `build/GNLJ82/main.dol: OK` を確認してから
push (直接 push でも PR でもよい)。fakematch は §3 の形式でマークする。
`config/GNLJ82/build.sha1`、ゲームアセット、`main.dol`、Ghidra decompiler の生出力は commit しない。

## License

このプロジェクトへの貢献は [CC0 1.0](LICENSE) で提供されたものとして
扱われる。同意できる場合のみ contribute すること。
