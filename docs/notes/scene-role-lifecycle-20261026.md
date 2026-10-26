# Scene role lifecycle — native matching (2026-10-26)

## Update: fn_8024D02C, 220 bytes

First native structural approach matches text220/EH8/index12 completely. Existing FlowSceneList from FlowScene.h supplies signed entries.count at+4 and actual virtual Update at slot0xC. Narrow owner/result views describe only target-observed fields; no live Ghidra type lookup performed. External RTTI descriptor arrays of8 bytes reproduce SDA21 addresses. The established nullable RankLog getter preserves redundant target null branches without permutation search. Actual source link and full DOL SHA-1 must be independently verified on main; no ASM or manual EH used.

## Synchronization boundary

Render fn_8024CFE8 (68B) also matches first native approach. FlowSceneList::Draw supplies slot0x10 r12/r12 dispatch; byte finished+4 guards child+8, then HSD_StateInvalidate(~0U). Automatic EH8/index12 match completely. Canonical shared header unchanged, target-observed owner view only, no live type query, ASM or manual EH.

The preceding pull moved local main296 commits to30d30c5. Rebuilt report, not stale local report, establishes baseline66.202995% aggregate/38.6054% source-linked native. Old ShellRibbon/BurstShard/CharaPop12 alternate HANDOFFs are superseded by the6 latest-main native implementations (independent text/EH/index100 and actual source link), not newly gained functions. Old worktrees remain preserved; their stale active entries were reconciled. Source classification is checked from current tracked sources instead of retaining old ASM labels indefinitely. State remains a cache, not the genuine progress metric.
