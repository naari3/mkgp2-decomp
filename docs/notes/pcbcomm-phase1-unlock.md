# pcbcomm-phase1-unlock

Source: Codex worker c19_u224_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u224 retry: fresh baseline94.948456 ->97.34536, text776/extab8/index12 exact sizes and EH100. Flatten PublishTimers into root, place output cursor after timer read, and reuse function-scope scan phase cursor for publication. Flatten-only96.52062/772B coalesces cursor and loses target addi; cursor reuse restores it. Byte hostRole95.798965/780B regresses; reverted. Remaining phase base/scan r5/r6 swap, duplicate SDA rather than mr, hostRole/output r9/r8 versus r8/r9, idle r6 versusr5. C15 helper extraction and explicit base initialization were not repeated. No singleton/pool rescue, single function precludes B. Honest NonMatching, no native gain; full coordinator DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.
