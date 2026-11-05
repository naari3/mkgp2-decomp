/* VSMode_SeedRandomItemSequence (0x8009BDC0): fill `count` consecutive kart
 * slots starting at `slot` with CPU drivers (driverId 6) whose characters are
 * drawn at random without repetition from the 13 selectable characters;
 * `exclude` (the player's character) is never drawn. Returns the next slot. */

extern int rand(void);

typedef struct KartSlot {
    int driverId;           /* 0x00 */
    int charId;             /* 0x04 */
    int field8;             /* 0x08 */
    int fieldC;             /* 0x0C */
    int kartVariant;        /* 0x10 */
    unsigned char items[3]; /* 0x14 */
    unsigned char pad17;
} KartSlot;

extern KartSlot lbl_805AC600[8];

static inline void KartSlot_Set(int i, int driver, int chr)
{
    if (i < 0 || i >= 8 || chr < 0 || chr >= 15) {
        return;
    }
    lbl_805AC600[i].driverId = driver;
    lbl_805AC600[i].charId = chr;
    lbl_805AC600[i].field8 = 1;
    lbl_805AC600[i].fieldC = 0;
    lbl_805AC600[i].kartVariant = 0;
}

#pragma use_lmw_stmw on
int VSMode_SeedRandomItemSequence(int slot, int exclude, int count)
{
    unsigned char used[13];
    int i;
    int chr;

    for (i = 0; i < 13; i++) {
        used[i] = 0;
    }
    used[exclude] = 1;
    for (i = 0; i < count; i++) {
        do {
            chr = rand() % 13;
        } while (used[chr]);
        used[chr] = 1;
        KartSlot_Set(slot, 6, chr);
        slot++;
    }
    return slot;
}
#pragma use_lmw_stmw reset
