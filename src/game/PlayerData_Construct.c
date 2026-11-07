#include "game/PlayerDataConstructPrivate.h"
#include "game/CoinMilestone.h"
extern int isJapanese(void);
extern char *strcpy(char *, const char *);
extern int rand(void);
extern const char *lbl_8049B608[][2];
extern PlayerDataRecord g_playerData;
extern int g_roundIndex;
extern void fn_80209C88(void);
extern void fn_80209AC4(int, int);
extern int fn_80209A84(void);
extern void fn_801D5F74(void *, int, unsigned char);
extern int fn_80216988(int);
extern CoinMilestone *fn_802169F4(int);
extern int fn_80209338(int);
extern int fn_80209330(void);
extern void DebugPrintf(const char *, ...);
extern const ConstructPool lbl_8039C718;

static inline int RollRareItem(void) {
    return rand() % 20 == 0;
}

static inline void GrantMilageItem(int character, const ConstructPool *pool) {
    int item;
    fn_80209338(character);
    item = fn_80209330();
    fn_801D5F74(&g_playerData, item, 1);
    DebugPrintf(pool->grantMessage, item, 0x22B);
}

void PlayerData_Construct(PlayerDataReset *self, int character, int count, int b, int c,
    unsigned char freePlay, unsigned char allRare, unsigned char special,
    int value, int coins, unsigned char allItems) {
    const ConstructPool *pool = &lbl_8039C718;
    strcpy((char *)self->name, lbl_8049B608[character][isJapanese()]);
    *(unsigned short *)((unsigned char *)self + 0xE) = value;
    self->coinMilage = coins;
    self->field1B0 = special;
    if (freePlay == 1) self->speed = 0;
    if (special == 1) self->speed = 0;
    if (self->field1B0 != 1) {
        ThreeModes modes = pool->defaults;
        int cc;
        int mode;
        int cup;
        int round;
        int i;
        modes.modes[0] = count;
        modes.modes[1] = b;
        modes.modes[2] = c;
        for (cc = 0; cc < 3; cc++) {
            count = modes.modes[cc];
            if (count > 0) {
                g_ccClass = cc;
                for (mode = 0; mode < count; mode++) {
                    for (cup = 1; cup < 9; cup++) {
                        g_cupId = cup;
                        for (round = 0; round < 4; round++) {
                            int r = round;
                            if (mode == 1) r = round + 4;
                            g_roundIndex = r;
                            fn_80209C88();
                            fn_80209AC4(cup, round);
                            fn_801D5F74(self, fn_80209A84(), 1);
                        }
                        self->cupRank[cc][cup - 1] = mode == 0 ? 5 : 10;
                    }
                }
            }
        }
        if (allItems == 1) {
            for (i = 14; i <= 59; i++) self->unlockFlags[i] = 1;
            for (i = 3; i <= 48; i++) self->remapFlags[i] = 1;
        }
        if (allRare == 1) {
            self->remapFlags[0] = 1;
            self->remapFlags[1] = 1;
            self->remapFlags[2] = 1;
        } else {
            self->remapFlags[0] = RollRareItem() != 0;
            self->remapFlags[1] = RollRareItem() != 0;
            self->remapFlags[2] = RollRareItem() != 0;
        }
        {
            int maximum;
            int mileage;
            maximum = -1;
            for (mileage = 0; mileage < coins; mileage++) {
                int index = fn_80216988(mileage);
                if (index < 0) {
                    DebugPrintf(pool->mileageError, 0x219);
                    return;
                }
                if (maximum < index) {
                    CoinMilestone *entry;
                    maximum = index;
                    entry = fn_802169F4(index);
                    if (entry != 0 && entry->type == 1) {
                        GrantMilageItem(character, pool);
                    }
                }
            }
        }
    }
}
