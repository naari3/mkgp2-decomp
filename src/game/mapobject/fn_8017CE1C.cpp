#include "game/FlowScene.h"

extern "C" {
extern VObject *lbl_806D15FC;
extern unsigned char lbl_806CFBA1;
extern int g_characterId;
extern char g_playerData[0x1DC];
extern int lbl_806D1644, lbl_806D1648;
extern int g_cupId, g_longRoundFlag, g_courseVariantIdx;
extern const char lbl_80376220[];
extern float lbl_806D9080;
void ItemUse_ResetAllKartUseSlots();
int RankSlot_AppendOrUpdate(unsigned char,int,int,void *,unsigned char,unsigned char,int,unsigned char,float,float,int);
VObject *fn_8014CEAC();
VObject *fn_8015B6D0();
VObject *fn_8014F6A4();
VObject *fn_80160238();
VObject *fn_80162C3C();
VObject *fn_8015BE44();
VObject *fn_8015CB5C(int);
VObject *fn_80163804(int,int);
VObject *fn_80165C04(int,int);
void fn_80202C34(int);
void fn_80202B48(int);
void *fn_80180670(const char *,int);
void fn_801804CC(void *,const char *);
void fn_801814C8();
void OperationClock_Commit();
void RaceFlow_ResetState_FullColdInit();
void SetReverseRoundFlag(int);
extern const char lbl_806D9000[7];
extern const char lbl_806D9008[7];
extern const char lbl_806D9010[7];
extern const char lbl_806D9018[7];
extern const char lbl_806D9020[7];
extern const char lbl_806D9028[7];
extern const char lbl_806D9030[7];
extern const char lbl_806D9038[7];
extern const char lbl_806D9040[7];
extern const char lbl_806D9048[7];
extern const char lbl_806D9050[7];
extern const char lbl_806D9058[7];
extern const char lbl_806D9060[7];
extern const char lbl_806D9068[7];
extern const char lbl_806D9070[7];
extern const char lbl_806D9078[7];
extern const char lbl_806D9084[6];
extern const char lbl_806D908C[6];
extern const char lbl_806D9094[6];
extern const char lbl_806D909C[6];
extern const char lbl_806D90A4[6];
extern const char lbl_806D90AC[6];
extern const char lbl_806D90B4[3];
extern const char lbl_806D90B8[3];
extern const char lbl_806D90BC[3];
extern const char lbl_806D90C0[3];
extern const char lbl_806D90C4[3];
extern const char lbl_806D90C8[3];
extern const char lbl_806D90CC[5];
extern const char lbl_806D90D4[5];
extern const char lbl_806D90DC[5];
extern const char lbl_806D90E4[8];
extern const char lbl_806D90EC[6];
extern const char lbl_806D90F4[5];
extern const char lbl_806D90FC[8];
extern const char lbl_806D9104[8];
extern const char lbl_806D910C[6];
extern const char lbl_806D9114[8];
extern const char lbl_806D911C[5];
extern const char lbl_806D9124[7];
extern const char lbl_806D912C[7];
extern const char lbl_806D9134[7];
extern const char lbl_806D913C[7];
extern const char lbl_806D9144[7];
extern const char lbl_806D914C[7];
extern const char lbl_806D9154[8];
extern const char lbl_806D915C[8];
extern const char lbl_806D9164[7];
extern const char lbl_806D916C[8];
extern const char lbl_806D9174[7];
extern const char lbl_806D917C[2];
extern const char lbl_806D9180[5];
extern const char lbl_806D9194[5];
extern const char lbl_806D919C[6];
extern const char lbl_806D91A4[4];
extern const char lbl_806D91C0[5];
extern const char lbl_806D91C8[2];
extern const char lbl_806D91CC[8];
extern const char lbl_806D91D4[2];
extern const char lbl_806D91D8[8];
extern const char lbl_806D91E0[6];
extern const char lbl_806D91E8[6];
extern const char lbl_806D91F0[6];
extern const char lbl_806D91F8[6];
}

static inline void ClearScene() {
    if (lbl_806D15FC) {
        delete lbl_806D15FC;
        lbl_806D15FC = 0;
    }
    if (lbl_806CFBA1 != 1) lbl_806CFBA1 = 1;
}
static inline void SetScene(VObject *scene) {
    lbl_806D15FC = scene;
    if (lbl_806CFBA1 != 0) lbl_806CFBA1 = 0;
}

static inline void SelectCharacterMenu(const char *base) {
    void *menu = fn_80180670(base + 0x6C8, 1);
    if (menu) {
        fn_801804CC(menu, lbl_806D9124);
        fn_801804CC(menu, lbl_806D912C);
        fn_801804CC(menu, lbl_806D9134);
        fn_801804CC(menu, lbl_806D913C);
        fn_801804CC(menu, lbl_806D9144);
        fn_801804CC(menu, lbl_806D914C);
        lbl_806D1644 = 1;
    }
}

static inline int SelectSubmenu(int item, int selection, const char *base) {
    int mode;
    switch (item) {
    case 3: SetScene(fn_8015CB5C(selection)); return 0;
    case 4:
        switch (lbl_806D1644) {
        case 0: {
            lbl_806D1648 = selection;
            void *menu = fn_80180670(base + 0x688, 1);
            if (menu) {
                fn_801804CC(menu, lbl_806D90DC);
                fn_801804CC(menu, lbl_806D90E4);
                lbl_806D1644 = 1;
            }
            break;
        }
        case 1: {
            mode = selection == 1 ? 1 : 0;
            OperationClock_Commit();
            RaceFlow_ResetState_FullColdInit();
            SetScene(fn_80163804(lbl_806D1648, mode));
            break;
        }
        }
        return 0;
    case 9:
    case 10:
        switch (lbl_806D1644) {
        case 0: {
            g_cupId = selection + 1;
            void *menu = fn_80180670(base + 0x5D8, 1);
            if (menu) {
                fn_801804CC(menu, lbl_806D90EC);
                fn_801804CC(menu, lbl_806D90F4);
                lbl_806D1644 = 1;
            }
            break;
        }
        case 1: {
            g_longRoundFlag = selection;
            void *menu = fn_80180670(base + 0x694, 1);
            if (menu) {
                fn_801804CC(menu, lbl_806D90FC);
                fn_801804CC(menu, lbl_806D9104);
                fn_801804CC(menu, lbl_806D910C);
                fn_801804CC(menu, base + 0x6A4);
                lbl_806D1644 = 2;
            }
            break;
        }
        case 2: {
            g_courseVariantIdx = selection;
            void *menu = fn_80180670(base + 0x6B0, 1);
            if (menu) {
                fn_801804CC(menu, base + 0x6BC);
                fn_801804CC(menu, lbl_806D9114);
                lbl_806D1644 = 3;
            }
            break;
        }
        case 3: SetReverseRoundFlag(selection); break;
        }
        return 0;
    case 11:
        switch (lbl_806D1644) {
        case 0:
            lbl_806D1648 = selection;
            switch (selection) {
            case 2: {
                void *menu = fn_80180670(base + 0x6C8, 1);
                if (menu) {
                    fn_801804CC(menu, lbl_806D911C);
                    fn_801804CC(menu, base + 0x6D8);
                    fn_801804CC(menu, base + 0x6E8);
                    fn_801804CC(menu, base + 0x6F8);
                    fn_801804CC(menu, base + 0x708);
                    fn_801804CC(menu, base + 0x718);
                    fn_801804CC(menu, base + 0x728);
                    lbl_806D1644 = 1;
                }
                break;
            }
            case 7: {
                SelectCharacterMenu(base);
                break;
            }
            default: SetScene(fn_80165C04(selection, selection)); break;
            }
            break;
        case 1:
            switch (lbl_806D1648) {
            case 2:
            case 7: SetScene(fn_80165C04(lbl_806D1648, selection)); break;
            }
            break;
        }
        return 0;
    }
    return 0;
}

extern "C" int fn_8017CE1C(int event, int unused, int item, int unused2, int selection) {
    const char *base = lbl_80376220;
    switch (event) {
    case 0:
        switch (selection) {
        case 1: {
            ClearScene();
            int character = g_characterId;
            switch (item) {
            case 0:
                ItemUse_ResetAllKartUseSlots();
                for (int i = 0; i < 6; i++) {
                    if (i == 0) RankSlot_AppendOrUpdate(1,0,character,0,0,0,-1,1,0.0f,0.0f,-1);
                    else RankSlot_AppendOrUpdate(0,6,character,0,0,0,-1,1,0.0f,0.0f,-1);
                }
                SetScene(fn_8014CEAC());
                return 0;
            case 1:
                g_playerData[0x1B8] = character;
                SetScene(fn_8015B6D0()); return 0;
            case 2: SetScene(fn_8014F6A4()); return 0;
            case 3: {
                void *menu = fn_80180670(base + 0x5C8, 1);
                if (menu) {
                    fn_801804CC(menu, lbl_806D9084);
                    fn_801804CC(menu, lbl_806D908C);
                    fn_801804CC(menu, lbl_806D9094);
                    fn_801804CC(menu, lbl_806D909C);
                    fn_801804CC(menu, lbl_806D90A4);
                    fn_801804CC(menu, lbl_806D90AC);
                    lbl_806D1644 = 0;
                }
                return 0;
            }
            case 4: {
                void *menu = fn_80180670(base + 0x5D8, 1);
                if (menu) {
                    fn_801804CC(menu, lbl_806D9084);
                    fn_801804CC(menu, lbl_806D908C);
                    fn_801804CC(menu, lbl_806D9094);
                    fn_801804CC(menu, lbl_806D909C);
                    fn_801804CC(menu, lbl_806D90A4);
                    fn_801804CC(menu, lbl_806D90AC);
                    lbl_806D1644 = 0;
                }
                return 0;
            }
            case 5: SetScene(fn_80160238()); return 0;
            case 6: SetScene(fn_80162C3C()); return 0;
            case 7: SetScene(fn_8015BE44()); return 0;
            case 8:
                fn_80202C34(0); fn_80202B48(0);
                if (lbl_806CFBA1 != 0) lbl_806CFBA1 = 0;
                return 0;
            case 9:
            case 10: {
                void *menu = fn_80180670(base + 0x5E4, 1);
                if (menu) {
                    fn_801804CC(menu, lbl_806D90B4);
                    fn_801804CC(menu, lbl_806D90B8);
                    fn_801804CC(menu, lbl_806D90BC);
                    fn_801804CC(menu, lbl_806D90C0);
                    fn_801804CC(menu, lbl_806D90C4);
                    fn_801804CC(menu, lbl_806D90C8);
                    lbl_806D1644 = 0;
                }
                return 0;
            }
            case 11: {
                void *menu = fn_80180670(base + 0x5F4, 1);
                if (menu) {
                    fn_801804CC(menu, base + 0x604);
                    fn_801804CC(menu, base + 0x610);
                    fn_801804CC(menu, base + 0x61C);
                    fn_801804CC(menu, base + 0x630);
                    fn_801804CC(menu, base + 0x63C);
                    fn_801804CC(menu, base + 0x648);
                    fn_801804CC(menu, lbl_806D90CC);
                    fn_801804CC(menu, base + 0x654);
                    fn_801804CC(menu, base + 0x664);
                    fn_801804CC(menu, base + 0x670);
                    fn_801804CC(menu, base + 0x67C);
                    fn_801804CC(menu, lbl_806D90D4);
                    lbl_806D1644 = 0;
                }
                return 0;
            }
            }
            return 0;
        }
        case 11: fn_801814C8(); break;
        }
        return 0;
    case 1: return SelectSubmenu(item, selection, base);
    case 3: return 0;
    case 4: return 0;
    case 2: ClearScene(); return 0;
    }
    return 0;
}
