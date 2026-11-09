# Retrospective, 2026-11-09: how we have been matching, and what to change for the last ~210 functions

State at 13:00Z on 2026-11-09 (CI progress history, `origin/progress-data`):
7403 / 7612 functions matched, 89.44 % of code bytes, 158 functions still inline
asm (counted as matched by the report), 2807 / 3255 units complete.

This document looks at the period 2026-11-04 .. 11-09, when the project went
from 6438 to 7403 matched functions (+965), and asks three questions per
approach: what did it land, what did it cost, and what should we do next.
Numbers come from the CI history, `git log`, `docs/sweeps/*.jsonl`,
`tools/patterns/hits.jsonl`, the project thread list and the project memory.
Where a number is an estimate it says so.

## 1. The curve

| day (UTC) | matched fns at day end | delta | asm fns | commits on main | notes |
| --- | --- | --- | --- | --- | --- |
| 11-04 | 6438 | +31 | 530 | 9 | onmokoworks only |
| 11-05 | 6798 | +360 | 490 | 209 | onmokoworks Codex batches only |
| 11-06 | 6916 | +118 | 309 | 285 | onmokoworks only |
| 11-07 | 7217 | +301 | 191 | 815 | round 2 starts 03:53Z (6 range threads, later 10+), onmokoworks in parallel |
| 11-08 | 7366 | +149 | 158 | 651 | autopipe x4, data ownership, asm->C, gave-up retry |
| 11-09 | 7403 | +37 | 158 | 272 (to 13:00Z) | autopipe99, shapesweep, regfix, 3 hand threads |

The daily delta has fallen by roughly half each day since 11-07 while commit
volume stayed high: 815 commits for +301, 651 for +149, 272 for +37. The work
per landed function has gone up about 8x in three days. That is the expected
shape of a long tail, but it also means every approach must now be judged by
landings per thread-hour, not by how much it runs.

Attribution between the two sides is not clean (onmokoworks merges `origin/main`
into their batch line, so CI deltas on their merge commits include our work).
Indicators: onmokoworks' own merge messages report +587 / +267 / +23 "native
functions" on 11-07 / 08 / 09 (their metric, not objdiff matched), and our
threads made 111 / 67 / 30 landing-type commits on those days. Both sides are
slowing at the same rate; the pool of easy functions is gone for everyone.

## 2. What each approach landed, and what it cost

Thread-hours are from the project's thread list (created -> last activity),
rounded. "Landings" are functions that reached 100 % and are on main.

| approach | when | thread-hours | landings | landings / thread-hour | evidence |
| --- | --- | --- | --- | --- | --- |
| Round 2 range threads R1..R6 + asm->C A/B + mid-range + HSD (hand work, early rules) | 11-07 03:53 .. 11-08 11:50 | ~230 | our share of +450 over two days; est. 150-250 | ~0.7-1.1 | CI curve, 178 landing commits |
| decomp-permuter shards 1-3 (+ autosweep compiler/flag switch) | 11-07 11:40 .. 16:07 | ~13 | 0 by the permuter; 1 hand landing (RaceScene_FrameUpdate) on the side | 0.08 | `permuter-shard*` memory, `docs/gave_up.md` |
| autopipe shards 1-4 (pragma -> decl order -> cperm) | 11-08 06:00 .. 11:45 | ~20 | 0 of 59 functions | 0 | `docs/sweeps/autopipe/results_*.jsonl`: 56 nomatch, 3 held |
| autopipe99 (pragma + decl + stmt + typesweep, >=99 % only) | 11-09 03:53 .. 07:14 | ~3.5 | 0 of 80 functions (335 attempts incl. re-runs) | 0 | `docs/sweeps/autopipe99/*.jsonl`: 142 nomatch, 193 held |
| stmtsweep trial | 11-08 12:06 .. 12:21 | 0.3 | 0 (re-finds the TextRenderer_DrawEntry fix) | 0 | `docs/gave_up.md` "stmtsweep trial" |
| shapesweep (source-shape beam search), 3 passes | 11-09 04:50 .. 07:33 | ~2.7 build + ~3 runs | 2 (fn_80231D50, CardRegister_Session_Tick), both "hoist into a local" | ~0.35 | `docs/sweeps/shapesweep/hits/` |
| regfix (MWCC regalloc simulator, diag + decl solver + auto inline move) | 11-09 09:57 .. now | ~3 | 2 direct (Sci2Card_BuildItemGetReceiptLine, THPDec fn_8029B54C); diag used in 3 more hand landings; batch over 51 fns running, 0 so far | ~0.7 direct, more as an assist | `tools/patterns/hits.jsonl`, `docs/sweeps/regfix/` |
| asm->source catalog (asmgrep, rules.jsonl, hits.jsonl, sibling list) | 11-09 11:17 .. 12:40 | ~1.4 | 0 directly; the sibling list gave 3 hand landings within 2 hours | n/a (enabler) | `docs/sibling_candidates.md`, hits `inline-matched-sibling` x3 |
| 3 hand threads by address range, regfix-diag first | 11-09 11:49 .. 13:00 | ~3.5 | 11 (7 rule ids: inline-matched-sibling x3, decl-order, stmt-order, shared-local-into-inline, inline-local-to-outer-ref, nested-inline-level, rolled-loop-blocks-cse, const-pointee-hoist, loop-unroll-budget) | ~3 | `tools/patterns/hits.jsonl` (11 landed rows dated 11-09) |
| data ownership / pool merges (own_data.py, data2c.py, pool audit, §13) | 11-08 .. 11-09 | ~10 | +4 fns, +~1 MB matched data (0.92 -> 1.85 MB on 11-08, +18 KB more 11-09) | small in fns, large in bytes | `data-own-sweep` memory, commit log |

The brute-force family (permuter, autosweep, autopipe, autopipe99, stmtsweep,
shapesweep passes 2-3) consumed roughly 40 thread-hours since 11-07 and landed
2 functions. `rewrite_rules.py backfill` over the sweep logs counts about 1950
blind rule applications for 2 matches and 39 score improvements. The same
levers, picked by hand after reading the diff (or regfix's diagnosis), landed
11 functions in 3.5 thread-hours today.

This is not because the sweeps are badly built. autopipe found that a cc x
pragma x decl-order grid never reaches 100 on these functions; autopipe99 added
statement order and type sweeps and still got 0 of 80. The remaining diffs are
not in the space those sweeps search. The 11 hand landings today each needed a
source-structure change that no sweep enumerates (inline a matched sibling's
body, lift a local one inline level up, write unrolled stores as a loop, make a
global `extern const`, change an unroll budget).

## 3. What worked

1. **Reading the diagnosis before choosing the lever.** regfix `diag` (and
   mwccdbg under it) says which vreg is coloured wrong and why ("'credits' is a
   named local ... turn it into a temp"). Every one of today's 11 landings
   started from that or from an equivalent hand reading. The decl-order solver
   in regfix replaces a 5040-build sweep with a simulation.
2. **Copying a matched sibling.** `asmgrep similar` lists unmatched functions
   that contain a matched function's body. 3 of 3 attempts where the body was a
   true duplicate landed within minutes (fn_8024D3D4, DoublyLinkedList_RemoveByKey,
   AssocTree_FreeAll); the one that did not (fn_8022ACE4) was not a true
   duplicate. `docs/sibling_candidates.md` still has ~17 untried rows.
3. **Writing rules down as soon as they land**, in one place with an id.
   `docs/regalloc_patterns.md` grew from 17 to 24 sections in two days, each
   with a commit id; `tools/patterns/rules.jsonl` has 37 rules; 153 of 193 past
   fixes reuse a known family. onmokoworks' workers read matching_rules.md and
   gave_up.md first, so a rule written here is applied on both sides.
4. **Data ownership as a separate lane.** It does not move the function count
   much, but it doubled matched data bytes and removed a class of "anchor"
   blockers (§9, §13) that the function threads kept tripping over.
5. **Coordination infrastructure that removed the human relay**: unit-claim
   issues (3808 created, 18 open now; onmokoworks 3044, us 764), the in-repo
   agent board (`docs/agents/`), the shared folder -> repo migration (TIPS,
   drafts, sweep logs, helpers), `land.sh` with `rewrite_rules check --strict`.
   Since the board went up on 11-09 12:20 there has been no relay request.
6. **Round 2's range split** worked while easy functions existed (+300 on
   11-07). It stopped working when the ranges emptied (11-08), and the threads
   then needed a new source of work, which is where the idling came from.

## 4. What was wasted, or cost more than it returned

1. **Blind sweeps after the first zero pass.** autopipe ran 4 shards for ~6 h
   after the first hour already showed no stage-1/2 hits. autopipe99 ran a
   second pass with typesweep that "changed nothing anywhere". The stop rule
   now written down (two zero passes -> stop) was applied by shapesweep, which
   is why it only cost ~3 run-hours.
2. **Permuter time.** 0 matches in three shards on 11-07, 0 in the 11-09 retry,
   8 + 4 hits back on 10-25/26 when the functions were easier. For regalloc
   diffs the permuter's random edits do not reach the needed structures.
3. **Claim hygiene incidents.** Twice our threads touched onmokoworks TUs
   because `gh --paginate` stopped at 100 issues (reverts 3ede22f, 53a82c2);
   autopipe swept onmoko TUs with a 13-entry claims.txt vs 233 open claims;
   25 stale claims of ours were closed in one inventory on 11-08. Each incident
   cost a revert or an apology, and user attention.
4. **Idle threads.** Threads stopped to ask "continue?" on 11-07 (05:00-09:38)
   and again 11-08 (02:00-04:32); a Stop hook and a standing rule fixed it, but
   roughly 10-15 thread-hours were lost, and the user had to notice both times.
5. **Numbering collisions and record gaps.** Two threads took regalloc §22 at
   once (fixed as §24 in af3c6372); hits were first logged with pre-rebase
   commit ids (3 rows repaired). `rewrite_rules check --strict` in `land.sh`
   now catches both, but only for threads that use `land.sh`.
6. **Knowledge in the shared folder.** Until 11-09 the TIPS file, drafts and
   sweep logs lived in `/mnt/project-files`, invisible to onmokoworks and to
   anyone reading the repo. Everything that was learned 10-25..11-08 was shared
   only through the two docs; the move on 11-09 fixed this.
7. **Tool-building ahead of evidence.** Each sweep tool (autosweep, autopipe,
   autopipe99 stages, stmtsweep, shapesweep moves, typesweep) was built from a
   plausible idea, then validated on zero or one past fix, then run broadly.
   The ones that paid back (regfix, asmgrep/sibling list) were built from
   several real landings. The user's rule from 13:00Z today says the same
   thing: automate a rule only after it has >= 2 landed hits.

## 5. Where the remaining work is

From `tools/patterns/nearmiss_history.jsonl` (11-09 11:33Z) and the census:

| band | fns |
| --- | --- |
| 99-100 % | 99 |
| 97-99 % | 51 |
| 90-97 % | 59 |
| < 90 % | 12 |
| still inline asm (counted matched) | 158 |

Of the 209 near misses >= 90 %: 71 register-only, 25 register + scheduling,
100 register + other, 13 no register diff. Only 46 have a precise rule
trigger today. Most of the 158 asm functions are SDK/libc/MusyX/THP leftovers
and the hard game functions that two threads (asm-A/B) already tried; the
report counts them as matched, so they are easy to forget but they are part of
"100 %".

Another 99 % band fact: 18 claims are open right now (4 ours), so about 190 of
the 221 near misses are unclaimed and available to either side.

## 6. Recommendations

Ranked by expected landings per thread-hour, based on the table in §2.

1. **Make diagnosis-first hand matching the default lane, 2-3 threads, not 6.**
   Today's rate was ~3 landings per thread-hour versus ~1 for range threads and
   0-0.35 for sweeps. Keep the three address-range threads; each takes the next
   function from the queue, runs `regfix diag`, checks `asmgrep similar` and
   `docs/sibling_candidates.md`, tries one lever, and either lands or writes a
   gave_up note within ~20 minutes. Do not add more range threads: the hand
   rate is bounded by distinct functions, not by hands.
2. **Stop all blind sweeps; keep the sweep code only as the verification step
   behind a chosen lever.** No autopipe/autopipe99/shapesweep batch runs unless
   a new stage has >= 2 landed hits that it replays from the pre-fix source.
   Apply the same bar to regfix `fix`: the current 51-function batch is the
   right experiment (inline + boolnorm, 2 hits replayed), and if it lands 0 the
   answer is more diagnoses, not more moves.
3. **Finish the sibling list.** ~17 rows untried in `docs/sibling_candidates.md`
   at 3/3 on true duplicates. Extend `asmgrep similar` to partial bodies (a
   matched inline helper used in the near miss) and to onmokoworks' matched
   code; this is the cheapest source of landings on the board.
4. **Put the 158 asm functions back on the plan.** They are hidden by the
   report. Split them: SDK/libc/MusyX (reference source exists; mostly
   compiler-flag work), THP/card/net (hand), and the game leftovers that asm-A/B
   parked (need the same regalloc levers). Give them one thread with
   `tools/scan_asm_fns.py` output as its queue, and show them on the progress
   page as not matched.
5. **Rule capture discipline, once per landing, by the lander.** Every landing
   gets: `rewrite_rules record` after `land.sh` says LANDED, a rule id, and
   (if new) a regalloc_patterns section with the number from `check`. Every
   give-up gets a gave_up.md note with what was tried. The retrospective of the
   next week should be computable from `hits.jsonl` + `gave_up.md` alone.
6. **Coordinator operations.** (a) On every wake, list threads and nudge any
   non-working one; a thread never ends a turn waiting for the user.
   (b) Open claims inventory once a day (explicit page numbers); a thread holds
   at most one claim and closes it when it leaves the TU. (c) One line to the
   project chat per landing batch, not per commit. (d) No new sweep thread
   without the >= 2-hit bar. (e) Use `docs/agents/` for everything to
   onmokoworks; ask the user to relay nothing.
7. **Work with onmokoworks on the unsolved families instead of racing them.**
   Their Codex lane is slowing at the same rate (+23 today). The open shapes
   (r3-avoidance after a call result, "target keeps a loaded value in a temp
   then `mr`", acsocket `addi rX,rY,0`, C++ temp slots) are the same on both
   sides. Post each unsolved family on the board with the smallest failing
   function, and ask whether their workers have a matched instance.
8. **Accept that some functions will need a compiler-internals answer.** For
   the "Still open" shapes in regalloc_patterns.md, the next lever is
   extending the regfix simulator (frontend temp numbering, coalescing of
   call results) rather than another source rewrite. That is one focused
   thread, measured by how many open shapes it explains.

## 7. Numbers to watch next week

- landings per thread-hour, per lane (hand / regfix batch / asm / data)
- rows added to `hits.jsonl` vs functions landed (should be 1:1)
- `rewrite_rules.py report`: fraction of near misses with a precise trigger (46/209 now)
- open claims held by our threads (target: <= number of working threads)
- asm_fn_count (158) shown next to matched_functions on the progress page
