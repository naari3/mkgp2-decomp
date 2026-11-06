# strpcb-lifetime-unlock

Source: Codex worker c16_u45_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 8 B.

c16_u45: fresh ctor82.21925/Shutdown98.05882 unchanged after 3/2 bounded probes. Named global-buffer local invariant; whole ctor-body helper fails to inline; init-only helper invariant. Delete wrapper and StopCommunication helper invariant. Target ctor keeps lbl80598100 base r31 before Alloc and materializes elapsed >= threshold via mfcr/extrwi, unlike source cror/bne. EH order: ctor80005D18; buffer dtor80005D4C; Shutdown80005D54; Ensure80005D5C. Thus Shutdown..dtor is one reversed group and cannot be split. Getter80038574/8B is independent and rescued via mechanism B; full source-linked getter DOL SHA1 exact. No other function/byte gain.
