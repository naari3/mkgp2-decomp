# service-mode-schedule-gate

Source: Codex worker c19_u241_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 320 B.

c19_u241: ServiceMode_UpdateScheduleGate 80075330/320B unlocks99.4375->100 by replacing repeated time->wday reads plus a distinct prev local with int day=time->wday; current-day lookups use day; then day-=1; if(day==-1)day=6; previous-day lookups reuse day. This resolves weekday/hour-base/minute-base volatile register cycle (baseline9/10/11 vs target11/9/10). Signed-char[2] slot layout and ServiceSettings* helper parameter were byte-invariant99.4375. Read c17_u62 and c5_s7 prior handoffs first; do not repeat their scalar-argument or explicit-column-pointer regressions. No missing functions, no data/split/bridge/pragma changes. Text320/extab8/index12 all100. Matching source edge and final ELF address80075330 size320 verified. Full DOL SHA-1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.
