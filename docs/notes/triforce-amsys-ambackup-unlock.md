# triforce-amsys-ambackup-unlock

Source: Codex worker c3_u17_amsys_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 23 fn / 6068 B.

amsys fn_80293DD4 becomes exact with explicit idle cases 0/4 (jump table), AmFirm/AmInfo shared base pointers, caller-local serial insertion loop, and explicit 0xFF mask on version high-byte shifts. fn_80294810 serial insertion uses the caller loop variable to resolve r3/r4 swap. ambackup first two I/O functions become exact after materializing ordered buffer/length/address local cursors. No EH groups constrain these TUs; seven exact backup functions can be isolated in three Matching text runs.

## c3_u17_amsys_20261105
Source: Codex worker c3_u17_amsys_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 23 fn / 6068 B.

Coordinator caught amsys SHA-1 failure despite object section/text 100%: CW reordered BSS/SBSS definitions, and objdiff ignored BSS symbol offsets. Extern declarations before functions plus real definitions deferred until after functions, in reverse target order, reproduce all eight target storage offsets with exact code. A read-only diagnostic correcting the 73 affected relocations in the failed DOL in memory produced target SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; actual coordinator relink still required.

## c5_m1_amnet_20261105
Source: Codex worker c5_m1_amnet_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 92 B.

c5: fn_802889AC target forwards chan to fn_8028812C, rather than zero: correction raises 94.0171 -> 95.04273. BackupReadRecord explicit result variables avoid branchless boolean return lowering; k before j fixes selection-loop registers. Call-local ternary mirrored read length and i before size yield 88.92216. Remaining align-load/address scheduling and checksum register identity did not resolve with inline stride or manual checksum locals; rejected regressions.

## c14_u31_20261106
Source: Codex worker c14_u31_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u31: BackupWriteRecord 80288364 rises 93.44697 -> 94.621216 with mirror length ternary and computing reset length before clearing e->reset, eliminating an address reload. Remaining recSize/hdr r31/r29 vs r29/r31, checksum pointer/sum r4/r3 vs r3/r4, align-load scheduling and reset shift/store scheduling. Caller checksum+declaration probe 93.56061; inline alignment plus n/sum/p probe 94.393936 rejected. BSS emitted D83C vs target D840: final BackupState 3C vs40, trailing gap 80690E1C..80690E20; no filler added. Retained NonMatching.

## c16_u73_20261106
Source: Codex worker c16_u73_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u73 fn_80288BCC fresh baseline73.01588 (assignment74.05), 236B vs252B. Inline cfg/entry/info helper unchanged; memcpy emits call73.92063. Volatile BackupEntry pointer preserves post-copy size/flags and post-store mirror reloads; const volatile BackupInfo plus one cached alignment load yields92.93651,248B. Retained NonMatching. Residual extra target branch at80288C44 plus info-base materialization/scratch register differences. Volatile provenance remains a hypothesis from target repeated loads. Single function prevents mechanismB; zero native gain; no config/split/EH/data changes.

## c19_u251_20261107
Source: Codex worker c19_u251_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 468 B.

c19_u251: fn_802889AC unlocks95.04273->100 using the newer matched BackupWriteRecord running-sum ChecksumFrom(p,sum,n) idiom, GC/1.3 (default CSE), and mirror->addr <<=1. Helper alone96.49573 fixes pointer/sum homes; GC/1.3 fixes post-size-store alignment load98.589745; explicit shift removes li2/mullw and finishes. opt_common_subs off harms this function96.15385. Split Matching ambackup_load_header.c .text802889AC..80288B80; full source-linked SHA1 exact and actual ELF468B range equals target. BackupReadRecord improves88.92216->89.88024 with matched-family opt_common_subs off only, retains GC/1.3.2/NonMatching. GetInfo inline accessor and running-sum/compare reversal are invariant for read; no data/EH/symbol changes.

## c23_u138_20261109
Source: Codex worker c23_u138_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 3372 B.

c23_u138:BackupReadRecord97.39521->97.45509,668B. Resolve mwccdbg first root (narrowed sum r0 vs targetr3, stored checksum r3 vs targetr0) by splitting flags check, block-scoped u16 sum assignment, and matched sibling ChecksumFrom(p,u16 initial,u32 n) with initial0. Plain Checksum with named result96.437126 swaps pointer/sum; running-sum parameter restores loop homes and makes entire checksum tail exact. First-call buffer/rounding register cycle remains. Compare-only inline94.61078 (stored load hoists); reversed args97.33533. Buffer-only accessor invariant97.39521. No-pragmas A/B90.2994. Retain positive native-C draft with pre-existing pragmas unchanged; NonMatching, no A/B native rescue or config/data changes.
