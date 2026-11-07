# shadowbillboard-lerp

Source: Codex worker c18_u43_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u43: fresh raw objdiff96.42857,252B; complete-row static inline helper taking sb,target,t,scale,row restores target scheduling (row offset increment before constant cursor) and improves98.333336, extab8/index12 exact. Scalar element helper invariant96.42857. Explicit row index with scale[i/4] adds4B/text89.888885; separate row counter95.60317. Retained row helper NonMatching; residual pure volatile GPR homes: target rowr5/dstr4/col1r0/col2r7 vs sourcer7/r5/r8/r0. Singleton TU prevents B; no flags/data/splits changed, no new full build. Prior c14_u47 CopyPosition fix retained.
