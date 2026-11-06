# race-voice-announcers

Source: Codex worker c6_ob_801a9d58_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 4772 B.

fn_801AC208 addresses lbl_80496C38 voice tables (+0x1C, +0xBC) and goal trigger lines (+0xF8C) through one r31 base held in the prologue. A local `RaceVoiceTables *tables = &lbl_80496C38;` reproduces the base, but CW still reassociates `tables->goalLines + idx` into (base+idx)+0xF8C, while the target has (base+0xF8C)+idx. The likely cause is that the original TU owned that .data (pooled base). In contrast, fn_801A9D58 indexes the separate symbol lbl_80498058 and matches with `lbl_80498058 + idx`. Voice-queue push inlines differ per handler: SpriteVoice_Push (fn_801ACC18), an in-place fill + `g_voiceQueueHead++` statement (fn_801AC208, priority 1), and a direct push without CanPush (fn_801AAF64, priority 4).

## c10_u6_20261106
Source: Codex worker c10_u6_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_801A9D58: independent block-local first/second/third/j in count==3 fixes volatile j/third homes and li-vs-mr initialization, improving 99.483116 to 99.66234 with exact 4620B text size and 8B/12B EH. Entry/progress/kart comparison helper variants leave late global-path-load residual. Remaining 12 differing instructions at offsets 9E0..9F0, C50..C60, D1C..D20. Retained NonMatching.

## c13_u21_20261106
Source: Codex worker c13_u21_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 10 fn / 3684 B.

c13_u21: fn_801AF850 (single fn, text 2976 B) improves 96.80779 -> 99.879036. TU-local driver push with standalone g_voiceQueueHead++ after all field stores removes 16 bytes of loop alias-driven address recalculation and matches the entire participant-count/driver/start-prompt tail. Named int voice locals for cups 6/7/8 remove repeated sum rematerialization (12 bytes) and retain raw sum for sth. Only 15 instruction register differences remain: course ID raw sum vs queue byte offset r8/r9 in cups 6/7 and r7/r8 in cup 8. Named short IDs instead retain extsh result, 99.26075%; a TU-local int-parameter course push helper regresses to 98.80645%, 2988 B. Retained NonMatching; full fallback-linked SHA-1 OK, zero native gain.

## c14_u32_20261106
Source: Codex worker c14_u32_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u32: Race_PerFrameTickAndAudio report 93.44 -> 96.02781 (raw objdiff 92.607185 -> 95.1854). Inverting TickFanfare to unfinished-player first/finished-player else restores target block order. Direct positive stream-length comparison with branch to next dispatch block removes mfcr/extrwi emitted for !(length > elapsed). Per-entry overtake helper changes only volatile homes and does not stop predecessor-rank load hoisting; reverted. Residual includes r30/r31 block/entries homes, merged address calculations, signed-byte extension reuse and goal-table association. Singleton function stays NonMatching; fallback full DOL SHA-1 OK.

## c16_u101_20261106
Source: Codex worker c16_u101_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2976 B.

c16_u101: fn_801AF850 resolves c13 remaining 15 GPR differences with static inline int CourseVoiceId(int base, int round) { return base + round; } used by cups 6/7/8. Caller int voice and shared SpriteVoice_Push retained. Inline arithmetic return changes sum/queue-offset homes to target r8/r9 (cup8 r7/r8). One structural hypothesis: 99.879036 ->100%, text2976. Matching source-linked full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No split/EH/data changes.
