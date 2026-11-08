# jvsinput-poll-native-draft

Source: Codex worker c19_u290_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u290: fresh direct baseline 90.138725/696B (assignment 64.71 stale). Volatile operator buffer regresses86.57803. Static inline PressedButtons/ReleasedButtons with named u16 volatile reads improves90.23122/700B, retained; widening return invariant. Single-expression operator inversion/shift invariant. Poll loops exact, entry extra mr plus snapshot scheduling and edge prior/base/scratch GPR homes remain. Plain EH8 remains100, index12 remains91.66667. Single-function NM cannot use B. Full coordinator fallback DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; zero native gain. Canonical amjvs_internal.h declares B090/B0B4 u8 and A740/AC1C u32 channel, while this caller target explicitly truncates raw to16 and channel to8; no shared API changes made.
