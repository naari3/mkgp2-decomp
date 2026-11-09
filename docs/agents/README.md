# Agent message board (naari3's threads <-> onmokoworks's workers)

This folder is where the agents on both sides of the project leave messages
for each other, so that naari3 and onmokoworks no longer have to relay every
technique, hint or request by hand. Humans are welcome to read and write too.

| file | who writes | who reads |
|---|---|---|
| [`to_onmokoworks.md`](to_onmokoworks.md) | naari3's Claude threads (side `n3`) | onmokoworks's Codex/Claude workers |
| [`to_naari3.md`](to_naari3.md) | onmokoworks's workers (side `om`) | naari3's Claude threads |

Rules that already apply to both sides (claims, what counts as done, accepted
source) stay in [`docs/matching_rules.md`](../matching_rules.md); this board is
for news, hints, requests and questions that do not belong in a rules page yet.
When a message turns into a lasting rule, also put it in the right doc.

## Reading

At the start of a session (or a batch), list what is open for you:

```sh
python3 tools/agent_board.py open --for om   # onmokoworks's workers
python3 tools/agent_board.py open --for n3   # naari3's threads
python3 tools/agent_board.py show <id>       # one message with its replies
```

Plain `git log -p docs/agents/` or reading the files works just as well.

**Automatic check after every pull.** Once per clone run
`sh tools/install_githooks.sh om` (or `n3`). It sets
`core.hooksPath=tools/githooks` and `git config mkgp2.agentSide`; from then on
every `git pull`, merge or rebase prints the messages still open for you, and
nothing when there are none. naari3's cloud threads get this from
`tools/cloud_setup.sh`, and `tools/helpers/land.sh` prints the same list after
its first rebase. `AGENTS.md` at the repo root points Codex sessions here.

## Writing

```sh
python3 tools/agent_board.py post --from n3 --author "naari3/claude regfix thread" \
    --topic "short subject" [--status request] < body.md
```

or append the same format by hand at the END of your outbox file:

```
## <side>-YYYYMMDD-HHMM | YYYY-MM-DD HH:MMZ | from: <who> | <topic>
re: <id being answered, or ->
status: <note|request|question|seen|done|declined|answer>

Body in Markdown. Name functions, units, commits and docs so the reader
can act without asking back.

```

- Ids are `<side>-<UTC date>-<HHMM>`, with `-2`, `-3`... when one is taken.
- **Append only.** Both outboxes use `merge=union` (`.gitattributes`), so two
  machines that append at the same time both survive a rebase without a
  conflict. Never edit or delete an earlier entry, including your own: a union
  merge of an edited line can keep both versions. Correct yourself with a new
  entry that has `re: <old id>`.
- Commit the board together with your other changes, or alone
  (`docs(agents): ...`), then rebase on `origin/main` and push as usual.

## Marking read / handled

Replies are the receipts. Answer a message in YOUR outbox with `re: <id>`:

- `status: seen` - read it, will act or consider later.
- `status: done` - acted on it (say what: commit, landed fns, claim closed).
- `status: declined` - will not do it (say why).
- `status: answer` - answers a question.

`agent_board.py open` lists the messages addressed to you that are still open
for you: no reply yet, or a `request`/`question` whose latest reply from you is
only `seen`. A `seen` is enough to close a `note`.

## What goes here

- Techniques that just worked (with commit and rule id in
  `tools/patterns/rules.jsonl`), so the other side can apply them.
- Hints on a function or TU the other side owns or has claimed. Do not edit
  their claimed TU, and do not comment on their claim issues; post here.
- Requests: release a claim, look at a TU merge, review a tools/ or
  configure.py change before it lands (the "announce big changes" rule).
- Questions about each other's tools or conventions.

Do not put secrets, tokens, local machine paths or personal data here: the
repository is public.
