#ifndef GAME_THINKBOX_CREATE_PRIVATE_H
#define GAME_THINKBOX_CREATE_PRIVATE_H
#include "game/types/size_t.h"
#include "game/AIPairPrivate.h"
void *operator new(size_t);
void operator delete(void *) throw();
extern "C" {
extern int g_gameMode;
extern unsigned char g_isCommHost;
extern void *g_pathSystem;
extern const float lbl_806DA3F4;
extern AIPairRecord lbl_806793D8[8];
extern void *ThinkBox_Create_data_804E4B88[];
extern void *ThinkBox_Create_data_804E4BC8[];
extern void *ThinkBox_Create_data_804E4BA8[];
extern void *ThinkBox_Create_data_804E4B74[];
int GetKartSlotCharId(int);
int Path_GetTotalCount(void *);
void fn_801DC778();
void MemoryManager_TimedFree(void *);
}
struct ThinkBoxBase {
    void *vptr;
    int field04, field08, field0C, characterCount;
    ThinkBoxBase() {
        vptr = ThinkBox_Create_data_804E4B88;
        field04 = 0;
        field08 = 0;
        field0C = 0;
        characterCount = 0;
        for (int i = 0; i < 8; ++i)
            if (GetKartSlotCharId(i) == 6) ++characterCount;
    }
};
struct ThinkBoxRace : ThinkBoxBase {
    int pathInterval;
    unsigned char flag18, flag19;
    int field1C;
    float field20;
    int field24;
    float field28;
    int selectedKart;
    ThinkBoxRace() {
        vptr = ThinkBox_Create_data_804E4BC8;
        pathInterval = Path_GetTotalCount(g_pathSystem) / 10;
        flag18 = 0;
        flag19 = 0;
        field1C = 0;
        field20 = lbl_806DA3F4;
        field24 = 0;
        field28 = lbl_806DA3F4;
        selectedKart = -1;
        for (int i = 0; i < 8; ++i) {
            struct DriverView { char opaque[0x1F4]; int type; };
            DriverView *driver = (DriverView *)lbl_806793D8[i].driver;
            if (driver && driver->type >= 0 && driver->type <= 3) {
                selectedKart = i;
                break;
            }
        }
    }
};
struct ThinkBoxHost : ThinkBoxBase {
    ThinkBoxHost() { vptr = ThinkBox_Create_data_804E4BA8; fn_801DC778(); }
};
struct ThinkBoxClient : ThinkBoxBase {
    ThinkBoxClient() { vptr = ThinkBox_Create_data_804E4B74; fn_801DC778(); }
};
#endif
