/*
 * PathManager_RefreshFinishPositions @ 0x8003B668 (size 0x5C).
 *
 * 1-fn loop over the 8 player slots of a PathManager (per-slot stride 0x98).
 * For each slot whose field 0x14 (active flag, signed) is >= 0, fetches an
 * id from the KartItem at field 0xA0 via KartItem_GetOrAssignId (still named
 * fn_8003F418 in symbols.txt) and stores it into field 0x68.
 *
 * Singleton dtk reversed-extab group `auto_PathManager_RefreshF_text` — the
 * function has an extab/extabindex entry (Large Frame: Yes / Saved GPR
 * r30-r31, body 0x10080000 / 0x00000000). #pragma exceptions on/reset wraps
 * the function so CW auto-emits the matching extab/extabindex layout
 * (same pattern as AI_GetYaw.c, GetCourseSectionType.c).
 */

extern int fn_8003F418(void *kartItem);

#pragma exceptions on
void PathManager_RefreshFinishPositions(int self) {
    int cursor;
    int playerIdx;

    cursor = self;
    playerIdx = 0;
    do {
        if (*(int *)(cursor + 0x14) >= 0) {
            *(int *)(cursor + 0x68) =
                fn_8003F418(*(void **)(cursor + 0xA0));
        }
        playerIdx++;
        cursor += 0x98;
    } while (playerIdx < 8);
}
#pragma exceptions reset
