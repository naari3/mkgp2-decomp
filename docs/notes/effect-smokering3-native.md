# SmokeRing3 native draft

## 2026-10-23

Complete `800C46AC..800C48D8` source reconstructs the signed state switch, three spawn/bind11/scale children, signed cleanup, bounded yaw, per-child external Vec3 copies and by-value slot positioning. Native556B/frame60/r26-r31/f31 matches target size, with compiler-generated extab8/index12 both100%. Text96.97122%; the residual short-lived child usesr10 instead of targetr5, with addi/fmr/load scheduling across two aggregate copies. Three bounded structural approaches (indexed field, early position pointer, named conditional child) produced identical code. Do not repeat declaration/register permutations.

Worker source-link trial SHA-1 `7e88a397e482971b74bb83295544cdb084be82df` failed; honest NonMatching fallback restored `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65`. Genuine matched gain0. No ASM/manual EH/data ownership trick. These source-trial observations are recorded from the raw worker HANDOFF; main acceptance independently checks the final native object and full fallback build.
