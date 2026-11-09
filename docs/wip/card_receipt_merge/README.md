# Card receipt TU merge (0x80094D80..0x80099994, 23 units): WIP, not landed

Evidence that these units are one original TU is in `docs/gave_up.md`
("Data layout / TU split problems", Sci2Card_BuildRetryReceiptLine row).

Not landed (2026-11-09): the merged TU is NonMatching and the function count
does not rise (Score drops to 99.96), so 20 Matching units would only be
demoted. main.dol is OK with the merge applied.

## Reproduce (about 5 minutes)

1. In `src/game/Sci2Card_BuildItemGetReceiptLine.c` replace the three table
   definitions (`lbl_803FFDF0[10]`, `receiptEnglish`, `receiptJapanese`) with
   `extern const char *lbl_803FFDF0[26];` plus
   `#define receiptEnglish (lbl_803FFDF0 + 10)` and
   `#define receiptJapanese (lbl_803FFDF0 + 18)`; drop the `[10]` extern from
   `include/game/Sci2CardItemReceiptPrivate.h`. Commit (merge_tus `git rm`s
   the sources and refuses modified files).
2. `ninja build.ninja` (merge_tus reads `ninja -t commands`), then

       python3 tools/merge_tus.py apply --first 0x80094D80 --last 0x80099958 \
         --pool docs/wip/card_receipt_merge/pool.c \
         --pool-sec .rodata:0x80317948:0x80318270 --pool-sec .data:0x803FFDF0:0x803FFE58

3. Hand fixes in the merged `src/game/Sci2Card_BuildRetryReceiptLine.c`:
   - ReceiptTables section: delete `extern char lbl_80318138[][0xD];` and use
     `((char (*)[0xD])lbl_80318138)[index]` (the extern follows a `#pragma`
     line, which hides it from the pool rewrite).
   - configure.py: add `extab_padding=b""` to the Object so the build goes
     through the extab rule (that rule applies extab_user_renames.json).
   - Pool `.data`: split `lbl_803FFDF0[26]` into `lbl_803FFDF0[10]`,
     `static receiptEnglish[8]`, `static receiptJapanese[8]`; in the ItemGet
     section use `((const char **)receiptEnglish)` / `receiptJapanese`;
     symbols.txt: `lbl_803FFDF0` size 0x28 + local `receiptEnglish`
     0x803FFE18 / `receiptJapanese` 0x803FFE38 (size 0x20). ItemGet = 100.
   - Pool `.rodata`: Retry's anchor offsets give object boundaries (§40):
     split `lbl_803180E0[10]` into `[7]` + `lbl_803180FC[3]`, and
     `lbl_80318108[12]` into `[3]` + `lbl_80318114[3]` + `lbl_80318120[6]`
     (same split in symbols.txt). In Retry replace `pool + 0x468` with
     `lbl_80317DB0`, `pool + 0x7B4/0x7C0/0x7CC/0x7D8` with the objects.

## State after that

31 of 34 functions 100%, extab 100%, .rodata 100%.

- `Sci2Card_BuildRetryReceiptLine` 87.84 -> about 89 (`Retry_body_best.c`).
  The table accesses now have the target's shape (`addi r3, r30, 0x468;
  lwzx`). Left: (1) saved registers: target line r31, anchor r30, update r29,
  finish r28, card r27, c r26, b r25, a r24, d r23; the best draft has
  finish/update right (declare `card, update, finish, c, b, a, d` and assign
  `finish = 0; update = 0; card = ...` as statements); (2) an extra
  `mr r0, r3 ... mr rN, r0` after each `Sci2Card_GetReceiptStringEntry` call
  in cases 7/8 (target: one `mr rN, r3`); direct call arguments, initialisers
  at the declaration and a `char *` return type do not remove it; (3) the
  last `table[line - 1].rows` lookup (target `addi; slwi; add; lbz -4`).
- `Sci2Card_BuildScoreReceiptLine` 100 -> 99.96: r0/r4 swap at the same
  `[line - 1]` lookup once `lbl_80317DB0` is a static pool object.
- `card_force_backup_now` 84.14 (unchanged).
