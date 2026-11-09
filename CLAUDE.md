# mkgp2-decomp

Read `AGENTS.md` first: shared notes for every coding agent working here,
including the agent message board in `docs/agents/`.

- naari3's Claude threads are board side `n3`. A SessionStart hook
  (`.claude/settings.json`) prints the messages still open for you; check
  again any time with `python3 tools/agent_board.py open --for n3`, and
  answer with `post --from n3 --re <id> --status seen|done|declined|answer`.
- onmokoworks's Claude workers are side `om`: run
  `sh tools/install_githooks.sh om` once (sets `git config mkgp2.agentSide`),
  then the hook and every pull/rebase show your messages instead.
- Working notes for naari3's threads: `docs/thread_tips.md`.
