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

## c18_u130_20261107
Source: Codex worker c18_u130_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 5264 B.

c18_u130 fn_801A9D58: resolves c10/c16 12-row path-load scheduling residual by correcting semantic types, 99.66234 ->100%/4620B. Race_CompareKartProgress definition takes integer participant indices; existing RaceVoiceKart::progress void* and pointer parameters were incorrect. TU-private MidRaceKart has int participantIndex at +0x2AC, accessor uses existing entry pad44 kart pointer, call prototype uses int a/b. This restores target kart scratch homes and late global-path load. Typed entry pointer overlay alone regressed99.588745 and was reverted. Text4620/EH8/index12 all100. Matching source-linked main.elf range801A9D58..801AAF64 byte-equal target; full DOL SHA1ea30f3b1 OK. New private include/game/MidRaceVoicePrivate.h; no split/shared header/EH bridge changes.

## c20_u29_20261108
Source: Codex worker c20_u29_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 548 B.

c20_u29 fn801AC208: new native in/out pointer AdvanceGoalLine(float **line){*line += cup/round/reverse offset;} called from GetGoalLine with local line=tables->goalLines resolves external aggregate +F8C reassociation WITHOUT pool ownership. Raw98.07453->99.666145,2576B,EH8/index12 all100. Whole participant loop exact; only first goal setup six positions +48,+50,+58,+5C,+60,+64 differ (cup/reverse load r5/r6 exchange, early cup-minus-one, dependent scheduling). Explicit call argument order and staged scalar locals invariant; parenthesized sums98.23758 and sequential roundOffset98.50777 regress. Retain attempt2 natural source NM. c18 ownership cycle with fn801A1798 remains out of scope, but pool not necessary to solve association. Full coordinator fallback DOL SHA1ea30f3b1exact; native gain0.

## c21_p46_20261108
Source: Codex worker c21_p46_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p46: RacePerFrame pool remains OTHER-owned by game/sprite/fn_801A7D0C.c at BSS 80678D90..80679260 (queue, speaker, entries). No ownership edits made. A two-source merge would violate contiguous text policy because owner text ends 801A8688 and RacePerFrame starts 801B5E18; coordinate intervening TUs across 801A7D0C..801B6B94. Correcting TickKart +2AC to int participantIndex and comparator arguments to int is instruction-invariant. A 128-float-row goal-table declaration raises raw object metric 95.1854->95.20278 but lowers report 96.02781->95.9073, so it was reverted. Indexed first-loop form is invariant. Retained original matching quality and semantic type correction; final fallback-linked DOL SHA-1 OK, no native gain.

## c22_u25_20261109
Source: Codex worker c22_u25_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u25 Race_PerFrameTickAndAudio: static inline signed char TickPlayerRank(const TickEntry*) returning entry->player, used instead of repeated signed-char casts, raises raw95.1854->95.52491/report96.02781->96.27694; text3412->3420 versus target3452. Getter restores inner-loop rank reload, both sign extensions and predecessor subtraction (target +204..218), plus outer extsb. predicate. Simple signed player field declaration is invariant. Goal in/out class+course cursor versions94.8146/94.82619 regress. Same getter pattern on BGM state invariant and removed. BSS80678D90..80679260 remains OTHER-owned by fn801A7D0C; coordinated contiguous merge801A7D0C..801B6B94 needed, no out-of-scope owner edits. Singleton stays NonMatching; full coordinator build exit0/DOL SHA1ea30f3b1 exact, native gain0.
