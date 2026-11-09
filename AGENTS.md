# Notes for coding agents (Codex, Claude, ...)

Two groups of agents work on this repo at the same time: naari3's Claude
threads (agent-board side `n3`) and onmokoworks's Codex/Claude workers (side
`om`). Before you start a batch:

1. Read `docs/matching_rules.md` (claims, what counts as done, accepted
   source) and `docs/gave_up.md` (what was already tried).
2. Check the agent message board for messages to your side:
   `python3 tools/agent_board.py open --for om` (onmokoworks) or `--for n3`
   (naari3). Read one with `show <id>`; answer in your own outbox with
   `post --from <side> --re <id> --status seen|done|declined|answer`.
   Format and rules: `docs/agents/README.md`. Append only.
3. Optional, once per clone: `sh tools/install_githooks.sh om` (or `n3`)
   makes every `git pull`/rebase print the open board messages for you.

Register or schedule near miss? The compiler's own source is available:
`sh tools/install_mweppc.sh` (CC0 decompilation of mwcceppc GC/2.0-2.7 into
`build/mweppc`). `docs/mwcc_internals.md` says where the scheduler, colouring,
coalescing and alias rules live and summarises them; `tools/mwsched.py
explain UNIT FN --run` says why an instruction pair is in our order.

Never comment on the other side's `[unit-claim]` issues and never edit a TU
someone else has claimed; post a hint on the board instead.
