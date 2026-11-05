# race-voice-announcers

Source: Codex worker c6_ob_801a9d58_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 4772 B.

fn_801AC208 addresses lbl_80496C38 voice tables (+0x1C, +0xBC) and goal trigger lines (+0xF8C) through one r31 base held in the prologue. A local `RaceVoiceTables *tables = &lbl_80496C38;` reproduces the base, but CW still reassociates `tables->goalLines + idx` into (base+idx)+0xF8C, while the target has (base+0xF8C)+idx. The likely cause is that the original TU owned that .data (pooled base). In contrast, fn_801A9D58 indexes the separate symbol lbl_80498058 and matches with `lbl_80498058 + idx`. Voice-queue push inlines differ per handler: SpriteVoice_Push (fn_801ACC18), an in-place fill + `g_voiceQueueHead++` statement (fn_801AC208, priority 1), and a direct push without CanPush (fn_801AAF64, priority 4).

## c10_u6_20261106
Source: Codex worker c10_u6_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_801A9D58: independent block-local first/second/third/j in count==3 fixes volatile j/third homes and li-vs-mr initialization, improving 99.483116 to 99.66234 with exact 4620B text size and 8B/12B EH. Entry/progress/kart comparison helper variants leave late global-path-load residual. Remaining 12 differing instructions at offsets 9E0..9F0, C50..C60, D1C..D20. Retained NonMatching.
