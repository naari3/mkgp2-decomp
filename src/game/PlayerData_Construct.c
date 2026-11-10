#include "game/PlayerDataConstructPrivate.h"
#include "game/CoinMilestone.h"
/* --- owned .rodata 0x8039D8C0..0x8039D9A4 (tools/own_data.py) --- */
#pragma force_active on
const unsigned int data_8049B530_rodata_8039D8C0[3] = { 0x828D8281, 0x82928289, 0x828F0000 };
const unsigned int data_8049B530_rodata_8039D8CC[3] = { 0x828C8295, 0x82898287, 0x82890000 };
const unsigned int data_8049B530_rodata_8039D8D8[3] = { 0x82978281, 0x82928289, 0x828F0000 };
const unsigned int data_8049B530_rodata_8039D8E4[3] = { 0x82908285, 0x82818283, 0x82880000 };
const unsigned int data_8049B530_rodata_8039D8F0[3] = { 0x828B8289, 0x828E8287, 0x00000000 };
const unsigned int data_8049B530_rodata_8039D8FC[3] = { 0x82AB82CC, 0x82D282A8, 0x00000000 };
const unsigned int data_8049B530_rodata_8039D908[3] = { 0x8294828F, 0x82818284, 0x00000000 };
const unsigned int data_8049B530_rodata_8039D914[3] = { 0x82C782F1, 0x82AB815B, 0x00000000 };
const unsigned int data_8049B530_rodata_8039D920[3] = { 0x82E682C1, 0x82B5815B, 0x00000000 };
const unsigned int data_8049B530_rodata_8039D92C[3] = { 0x8299828F, 0x82938288, 0x82890000 };
const unsigned int data_8049B530_rodata_8039D938[3] = { 0x82CF82C1, 0x82AD82DC, 0x82F10000 };
const unsigned int data_8049B530_rodata_8039D944[3] = { 0x82DD82B8, 0x82DC82C1, 0x82AD0000 };
const unsigned int data_8049B530_rodata_8039D950[3] = { 0x826C8293, 0x81448290, 0x00000000 };
const unsigned int data_8049B530_rodata_8039D95C[3] = { 0x82A082A9, 0x82D782A2, 0x00000000 };
const unsigned int data_8049B530_rodata_8039D968[3] = { 0x82ED82E9, 0x82A2815B, 0x82B60000 };
const unsigned int data_8049B530_rodata_8039D974[3] = { 0x82978281, 0x828C8295, 0x00000000 };
const unsigned int data_8049B530_rodata_8039D980[3] = { 0x82DC82DF, 0x82C182BF, 0x00000000 };
const unsigned int data_8049B530_rodata_8039D98C[6] = { 0x828D8281, 0x828D8285, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
#pragma force_active reset
extern int isJapanese(void);
extern char *strcpy(char *, const char *);
extern int rand(void);
extern const char *PlayerData_Construct_data_8049B608[][2];
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
    strcpy((char *)self->name, PlayerData_Construct_data_8049B608[character][isJapanese()]);
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
