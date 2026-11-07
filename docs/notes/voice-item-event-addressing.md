# voice-item-event-addressing

Source: Codex worker c19_u10_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u10: static inline short RemapItemVoice(short) containing the unchanged remap switch restores target initial mr input->remapped voice, raises direct objdiff97.90642->98.0843, text5124->5128 versus5172 target, switch data0->100; EH87.5/index91.66667 unchanged. Keep helper. Index-search then selection adds sentinel branches (91.188705); aggregate map-record helper spills copies/frame0x70 (94.862335); both reverted. Remaining map/clip base folding and cursor lifetimes prevent exact match. Whole shared voice .data pool ends8049A060, but two Matching TUs own8049A060..8049A134 before this TU switch table, so a contiguous range expansion is unavailable without out-of-scope ownership changes. No singleton site or B subset. Full fallback DOL SHA1 exact, zero native gain.
