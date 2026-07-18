# mkgp2-decomp

[![Build](https://github.com/naari3/mkgp2-decomp/actions/workflows/build.yml/badge.svg)](https://github.com/naari3/mkgp2-decomp/actions/workflows/build.yml)
[![matched code](https://img.shields.io/endpoint?url=https%3A%2F%2Fnaari3.github.io%2Fmkgp2-decomp%2Fshield.json)](https://naari3.github.io/mkgp2-decomp/)

Matching decompilation of **Mario Kart Arcade GP2** (Triforce, JP) — `main.dol` only.

Game ID: `GNLJ82` — Namco Bandai / Nintendo, 2007.

## Progress

- Dashboard (GitHub Pages, generated each CI run on `main`):
  <https://naari3.github.io/mkgp2-decomp/>
- Per-commit `report.json` is uploaded as the `GNLJ82_report` workflow artifact.

decomp.dev への登録はまだ行っていない。登録手順は `docs/github_actions.md`
の "decomp.dev integration" に記載済みで、必要になったら有効化する。

## Scope

- **PPC code only.** No game assets (textures, dat, arc, bin, audio, etc.) are
  committed to this repository. The `orig/` and `build/` directories are
  gitignored; users must supply their own legally-obtained copy of `main.dol`.
- The goal is byte-identical reconstruction of `main.dol` from C/C++ source via
  CodeWarrior, using the [`decomp-toolkit`](https://github.com/encounter/decomp-toolkit)
  build pipeline.

## Status

Bring-up. Early matching in progress — see the dashboards above for live numbers.

| | Value |
| --- | --- |
| `main.dol` SHA-1 | `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65` |
| `main.dol` size | 5,275,488 bytes |
| Entry point | `0x80003154` |
| `.text` ranges | `0x80003100..0x80005600` (boot, 9.5 KB), `0x8002BCA0..0x802E88E0` (main, 2.8 MB) |
| BSS | `0x804FE060..0x806DCF90` (1.96 MB) |
| Toolchain (guess) | CodeWarrior for GameCube 2.7 (`mw_comment_version: 11`) — to be re-verified |

## Setup

1. Install dependencies: see [`docs/dependencies.md`](docs/dependencies.md).
2. Place your `main.dol` (matching the SHA-1 above) at:

   ```
   orig/GNLJ82/sys/main.dol
   ```

3. CodeWarrior `mwcceppc.exe` and friends are downloaded automatically by
   `configure.py` from the [`decompals/wii-tools`](https://github.com/decompals/wii-tools)
   archive (see `config.compilers_tag` in `configure.py`).
4. Configure and build:

   ```
   python configure.py
   ninja
   ```

   On a fresh bring-up this will run analyzer-only and emit disassembly into
   `build/GNLJ82/asm/`. Once any C/C++ object matches, it begins replacing the
   corresponding asm in the link.

## Layout

```
config/GNLJ82/        # config.yml, symbols.txt, splits.txt (committed)
orig/GNLJ82/sys/      # main.dol lives here locally (gitignored)
build/                # all build output (gitignored)
src/  include/        # C/C++ source as it is decompiled
tools/                # shared dtk-template Python helpers
docs/                 # decomp-toolkit documentation
```

## Related projects

- [`mkgp2-patch`](https://github.com/naari3/mkgp2-patch) — Kamek patch and
  Ghidra-driven analysis (`mkgp2docs/`). Symbol names and struct layouts are
  seeded from there. The decomp side is intended to become the single source
  of truth once enough functions match.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) (mostly in Japanese) — how to set up,
claim a function range via an issue, and what a PR must include. The matching
workflow itself is documented in
[`.claude/skills/mkgp2-match/SKILL.md`](.claude/skills/mkgp2-match/SKILL.md).

## License

[`CC0 1.0`](LICENSE) for project scaffolding and decompiled source contributed
to this repo. No game data is included.
