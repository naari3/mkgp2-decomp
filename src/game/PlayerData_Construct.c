#include "game/PlayerDataResetPrivate.h"
extern int isJapanese(void);
extern char *strcpy(char *, const char *);
extern int rand(void);
extern const char *lbl_8049B608[][2];
extern const unsigned char lbl_8039C718[];
extern PlayerDataRecord g_playerData;
extern int g_roundIndex;
extern void fn_80209C88(void);
extern void fn_80209AC4(int, int);
extern int fn_80209A84(void);
extern void fn_801D5F74(void *, int, unsigned char);
extern int fn_80216988(int);
typedef struct MilageEntry { int threshold, kind; } MilageEntry;
extern MilageEntry *fn_802169F4(int);
extern int fn_80209338(int);
extern int fn_80209330(void);
extern void DebugPrintf(const char *, ...);
typedef struct ThreeModes { int modes[3]; } ThreeModes;

void PlayerData_Construct(PlayerDataReset *self, int character, int a, int b, int c,
    unsigned char freePlay, unsigned char allRare, unsigned char special,
    int value, int coins, unsigned char allItems) {
    const unsigned char *pool = lbl_8039C718;
    strcpy((char *)self->name, lbl_8049B608[character][isJapanese()]);
    *(unsigned short *)((unsigned char *)self + 0xE) = value;
    self->coinMilage = coins;
    self->field1B0 = special;
    if (freePlay == 1) self->speed = 0;
    if (special == 1) self->speed = 0;
    if (self->field1B0 != 1) {
        ThreeModes modes = *(const ThreeModes *)(pool + 0x1280);
        int cc;
        int mode;
        int cup;
        int round;
        int maximum;
        int i;
        modes.modes[0] = a;
        modes.modes[1] = b;
        modes.modes[2] = c;
        for (cc = 0; cc < 3; cc++) {
            int count = modes.modes[cc];
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
            self->remapFlags[0] = (rand() % 20 == 0) != 0;
            self->remapFlags[1] = (rand() % 20 == 0) != 0;
            self->remapFlags[2] = (rand() % 20 == 0) != 0;
        }
        maximum = -1;
        for (i = 0; i < coins; i++) {
            int index = fn_80216988(i);
            if (index < 0) {
                DebugPrintf((const char *)pool + 0x1DA4, 0x219);
                return;
            }
            if (maximum < index) {
                MilageEntry *entry;
                maximum = index;
                entry = fn_802169F4(index);
                if (entry != 0 && entry->kind == 1) {
                    int item;
                    fn_80209338(character);
                    item = fn_80209330();
                    fn_801D5F74(&g_playerData, item, 1);
                    DebugPrintf((const char *)pool + 0x1DC8, item, 0x22B);
                }
            }
        }
    }
}
