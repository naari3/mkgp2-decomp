# triforce-amsys-ambackup-unlock

Source: Codex worker c3_u17_amsys_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 23 fn / 6068 B.

amsys fn_80293DD4 becomes exact with explicit idle cases 0/4 (jump table), AmFirm/AmInfo shared base pointers, caller-local serial insertion loop, and explicit 0xFF mask on version high-byte shifts. fn_80294810 serial insertion uses the caller loop variable to resolve r3/r4 swap. ambackup first two I/O functions become exact after materializing ordered buffer/length/address local cursors. No EH groups constrain these TUs; seven exact backup functions can be isolated in three Matching text runs.

## c3_u17_amsys_20261105
Source: Codex worker c3_u17_amsys_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 23 fn / 6068 B.

Coordinator caught amsys SHA-1 failure despite object section/text 100%: CW reordered BSS/SBSS definitions, and objdiff ignored BSS symbol offsets. Extern declarations before functions plus real definitions deferred until after functions, in reverse target order, reproduce all eight target storage offsets with exact code. A read-only diagnostic correcting the 73 affected relocations in the failed DOL in memory produced target SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; actual coordinator relink still required.

## c5_m1_amnet_20261105
Source: Codex worker c5_m1_amnet_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 92 B.

c5: fn_802889AC target forwards chan to fn_8028812C, rather than zero: correction raises 94.0171 -> 95.04273. BackupReadRecord explicit result variables avoid branchless boolean return lowering; k before j fixes selection-loop registers. Call-local ternary mirrored read length and i before size yield 88.92216. Remaining align-load/address scheduling and checksum register identity did not resolve with inline stride or manual checksum locals; rejected regressions.
