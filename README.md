# progress-data

Per-commit decomp progress history for the GitHub Pages dashboard.
`history/<VERSION>.jsonl` has one JSON line per `main` commit with the
objdiff `report.json` measures.

Appended automatically by CI (`Update progress history` in
`.github/workflows/build.yml`); do not edit by hand. Seeded 2026-07-18 from
past CI report artifacts via `tools/progress_history.py backfill`.
See `docs/github_actions.md` on `main`.
