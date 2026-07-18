# CI / progress publishing

This repo ships two pieces of infrastructure for tracking decomp progress:

1. `.github/workflows/build.yml` — builds `main.dol` on every push and PR,
   uploads `report.json` as an artifact, and (on `main`) renders a static
   dashboard published to GitHub Pages.
2. `tools/gen_progress_page.py` — turns `build/<version>/report.json` into a
   self-contained HTML dashboard (treemap + per-category bars + unit table).

Public dashboards:

| | URL | Source |
| --- | --- | --- |
| Self-hosted (active) | <https://naari3.github.io/mkgp2-decomp/> | rendered by `tools/gen_progress_page.py` in CI |
| decomp.dev (not yet registered) | <https://decomp.dev/naari3/mkgp2-decomp> | webhook pulls `GNLJ82_report` artifact once enrolled |

decomp.dev は現状未登録。`build.yml` 側で `GNLJ82_report` artifact は
既に出ているので、必要になったタイミングで下の "decomp.dev integration"
セクション通りに登録するだけで連動が始まる。

## Build container

`main.dol` is **not** committed to this repo. CI pulls it from a private
companion repository (`naari3/mkgp2-decomp-build`) that packages
`main.dol` + binutils + CodeWarrior into a Docker image at
`ghcr.io/naari3/mkgp2-decomp-build:main`. This is the
[dtk-template-build](https://github.com/encounter/dtk-template-build) pattern.

> [!CAUTION]
> The build repo must stay **private** — the published Docker image embeds
> `main.dol`. Granting the public repo read access to the GHCR package is the
> only place where access is shared.

Setup steps (one-time):

1. Create `naari3/mkgp2-decomp-build` as a **private** repo from the
   `encounter/dtk-template-build` template.
2. Place `main.dol` at `orig/GNLJ82/sys/main.dol` (matching SHA-1
   `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65`).
3. Push to `main`. The build repo's workflow builds and pushes
   `ghcr.io/naari3/mkgp2-decomp-build:main`.
4. In the GHCR package settings for that image (Packages → mkgp2-decomp-build
   → Package settings → Manage Actions access), add `naari3/mkgp2-decomp`
   with the **Read** role so this repo's CI can pull it.

After that, every push to `naari3/mkgp2-decomp` will:

- Pull the image, run `python configure.py` + `ninja`.
- Upload `GNLJ82_maps` (link map files) and `GNLJ82_report` (`report.json`).
- On `main`, render `site/index.html` via `tools/gen_progress_page.py` and
  deploy it to GitHub Pages.

## decomp.dev integration

decomp.dev ingests `report.json` via a GitHub App that listens to
`workflow_run` webhook events:

1. Install the [decomp.dev GitHub App](https://github.com/apps/decomp-dev) on
   `naari3/mkgp2-decomp` (read-only access to Actions artifacts).
2. Visit <https://decomp.dev/manage/new>, pick the repo, fill in the form.
3. After the next workflow run on `main` finishes, the app pulls the
   `GNLJ82_report` artifact, parses `report.json`, and updates
   <https://decomp.dev/naari3/mkgp2-decomp>.

The artifact **must** be named `<version>_report` and contain `report.json` at
its root — the dtk-template `build.yml` already does this.

Useful URLs once registered:

- Dashboard: `https://decomp.dev/naari3/mkgp2-decomp`
- Treemap SVG: `https://decomp.dev/naari3/mkgp2-decomp.svg`
- Full JSON: `https://decomp.dev/naari3/mkgp2-decomp.json`
- Shield JSON (for shields.io): `https://decomp.dev/naari3/mkgp2-decomp.json?mode=shield&measure=matched_code`

Available `measure=` values: `matched_code`, `fuzzy_match`, `matched_data`,
`complete_code`, `matched_functions`. See
[`crates/web/src/handlers/report.rs`](https://github.com/encounter/decomp.dev/blob/main/crates/web/src/handlers/report.rs)
in the decomp.dev source for the full list.

## Self-hosted dashboard (GitHub Pages)

If you only want the self-hosted dashboard (no decomp.dev), enable Pages on
this repo with the **GitHub Actions** source. The `deploy-pages` job in
`.github/workflows/build.yml` will then publish `site/` after each `main`
build.

Locally:

```bash
python configure.py
ninja progress build/GNLJ82/report.json
python tools/gen_progress_page.py build/GNLJ82/report.json --out-dir site
# open site/index.html
```

## Per-commit progress history (progress-data branch)

The dashboard's "Progress over time" charts (matched % toward the 100 % goal
per commit, daily gained percentage points, per-commit delta table) read a
JSONL history that lives on the orphan **`progress-data`** branch as
`history/GNLJ82.jsonl` — one JSON line per `main` commit with the
`report.json` measures. Pages artifacts are stateless, so git is the storage.

- CI (`Update progress history` step, `main` only) checks the branch out into
  a `.progress-data/` worktree, appends the current commit via
  `tools/progress_history.py append` (idempotent by sha), and pushes. On a
  rejected push (concurrent run won the race) it resets to the new remote tip
  and redoes the append — both runs append at EOF, so a textual rebase would
  always conflict; regenerating is the conflict-free path.
- The page generator consumes it via
  `gen_progress_page.py --history .progress-data/history/GNLJ82.jsonl` and
  also republishes it as `history.jsonl` on the Pages site.
- If history ever needs rebuilding (branch lost, schema change), reseed it
  from past CI report artifacts (retained ~90 days):

  ```bash
  git worktree add .progress-data progress-data
  python tools/progress_history.py backfill \
      --history .progress-data/history/GNLJ82.jsonl
  # commit + push .progress-data
  ```

## Troubleshooting

- **`ghcr.io/...:main` not found in CI** — confirm the build repo's image was
  pushed and that `naari3/mkgp2-decomp` has Read access to the GHCR package
  (Manage Actions access).
- **`report.json` artifact missing** — the dtk-template ninja `progress`
  target depends on `objdiff-cli report generate`, which is auto-downloaded
  by `configure.py`. A failed download leaves the rule unbuildable; check the
  `Build` step log.
- **decomp.dev not updating** — confirm the artifact name ends with
  `_report` and the GitHub App still has permissions.
