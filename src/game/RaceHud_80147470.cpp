
/* sdata symbols referenced from asm */
extern unsigned char lbl_806CF810[8];
extern unsigned char CSSceneGetTitle_8014ADB4_data_806CF818[8];
extern unsigned char lbl_806D7CC0[4];
extern unsigned char lbl_806D7E8C[7];
/*
 * 0x80147470..0x8014CE74: race HUD controllers (lap/record panels,
 * countdowns and their text holders).
 */
#pragma cplusplus on

#include "game/types/VObj.h"

#include "game/types/VObjC.h"

#include "game/types/Pad14.h"

#include "game/types/VObj14.h"

#include "game/types/Countdown.h"

#include "game/types/LapSlot.h"

#include "game/types/LapCtrl.h"

#include "game/types/RecordCounter.h"

#include "game/types/Spark.h"

#include "game/types/StepHolder.h"

#include "game/types/KartVariant.h"

#include "game/types/CountEntry.h"

#include "game/types/CountList.h"

#include "game/types/HudPanel.h"

#include "game/types/CdHolder.h"

#include "game/types/CdHolder2.h"

inline bool Countdown_Tick(Countdown *c) {
    if (c->delay > 0) {
        c->delay--;
        return 0;
    }
    if (c->state == 1) {
        c->state = 2;
    }
    return c->state <= 0;
}

/* TOP-END */

extern "C" {
void fn_801FE390(struct LapCtrl *c);
extern const float lbl_806D7B58;
extern const float lbl_806D7B5C;
void fn_801FE27C(int n);
void MemoryManager_TimedFree(void *p);
void fn_801676AC(void *p, int flag);
extern unsigned int lbl_8048EB44[];
extern unsigned int LapHud_vtable_8048EFD4[];
extern void Alloc();
extern void fn_80146260();
extern void fn_80167730();
extern unsigned int lbl_806D7B60;
extern const float lbl_806D7BA4;
extern void dtor_8013EB50();
extern unsigned int lbl_806D7C0C;
extern unsigned int lbl_806D7C10;
extern const float lbl_80362620[4];
extern float lbl_8048EFB8[4];
const char *GetTextureByIdAndLang(int id, int lang);
void PreloadResource(int id);
void TexMgr_Apply(struct TextManager *t);
void TexMgr_Init(void *t);
void TexMgr_SetTexture(struct TextManager *t, const char *s, ...);
extern int g_cupId;
extern unsigned int dtor_800869D0[];
extern const float lbl_806D7C2C;
void *GetInputManager(void);
class HudInput *InputMgr_GetPlayer(void *mgr, int idx);
extern unsigned int lbl_806D7C20;
extern unsigned int lbl_806D7C34;
extern const float lbl_806D7C38;
extern unsigned int lbl_806D7C3C;
extern unsigned int lbl_806D7C40;
extern unsigned int lbl_806D7C44;
void SoundMgr_Play(int id);
extern unsigned int lbl_806D7C48;
extern unsigned int lbl_806D7C4C;
extern unsigned int lbl_806D7C50;
unsigned char IsCardValid(void);
extern void ResCtrl_Init();
void fn_8011F994(int layer);
void fn_8011FAFC(void *ctrl, int layer);
void fn_8013D4B0(void *model, float a);
void fn_8013D570(void *m, float a);
void fn_8013D608(void *m, float x, float y, float z);
void fn_8013D660(void *m, float x, float y);
void fn_8014017C(void *p);
void fn_801F8A34(void *ctx, void *tm, int layer);
void *fn_801F8E58(void);
extern const float lbl_806D7C74;
extern const float lbl_806D7C78;
extern const float lbl_806D7C7C;
extern const float lbl_806D7C80;
extern const float lbl_806D7C84;
extern const float lbl_806D7C88;
extern const float lbl_806D7C8C;
extern unsigned int dtor_80082960[];
float Cosf_LUT_Wrap(float a);
float Sinf_LUT_Wrap(float a);
void fn_80140344(void *p);
int rand(void);
extern unsigned int lbl_806D7C18;
extern unsigned int lbl_806D7C28;
extern unsigned int lbl_806D7C30;
extern unsigned int lbl_806D7C54;
extern unsigned int lbl_806D7C58;
extern unsigned int lbl_806D7C5C;
extern unsigned int lbl_806D7C60;
extern unsigned int lbl_806D7C64;
extern unsigned int lbl_806D7C68;
extern const float lbl_806D7C6C;
extern unsigned int lbl_806D7C70;
extern unsigned int lbl_806D7C90;
extern unsigned int lbl_806D7C94;
void __destroy_arr(void *p, void *dtor, unsigned long size, unsigned long n);
extern void __unexpected();
void fn_80120A08(int id);
void fn_80140810(void *p, int flag);
extern void fn_801F8E54();
extern unsigned int lbl_8048ECF8[];
extern unsigned int lbl_8048ED10[];
extern unsigned int RecordHud_vtable_8048F020[];
int Clamp_Int(int v, int lo, int hi);
int GetCoinCount(void);
void fn_8013D634(void *m, float x, float y, float z);
void fn_8013D738(void *m, float a, float b);
extern void fn_8013D800();
extern void fn_80140874();
extern const float lbl_806D7C98;
extern void dtor_801419C8();
extern void DebugPrintf();
extern void __construct_array();
extern void fn_801F8E90();
extern void fn_801F93EC();
int isJapanese(void);
extern void strlen();
extern unsigned int lbl_806D7C9C;
extern unsigned int lbl_806D7CA0;
extern unsigned int lbl_806D7CA4;
extern unsigned int lbl_806D7CA8;
extern unsigned int lbl_806D7CAC;
extern unsigned int lbl_806D7CB0;
extern unsigned int lbl_806D7CB4;
extern unsigned int lbl_806D7CB8;
extern unsigned int lbl_806D7CBC;
extern unsigned int lbl_806D7CC4;
extern unsigned int lbl_806D7CC8;
extern unsigned int lbl_806D7CCC;
extern unsigned int lbl_806D7CD0;
extern unsigned int lbl_806D7CD4;
float LUT_Sin12Bit(float a);
struct HudRankSlot *RankSlot_GetByIndex(int i);
void fn_8013C534(void *m, float r, float g, float b, float a);
void fn_8013C5FC(void *m, float a);
void fn_8013C674(void *m, float a);
void fn_8013C6EC(void *m, float x, float y, float z);
void fn_8013C7B0(void *m, float x, float y);
void fn_8013C91C(void *m);
void fn_8013CA04(void *m);
void fn_8013CA70(void *m);
void fn_8013CC24(void *m, int kart, int flag);
void fn_801680A0(int layer, const unsigned short *s, float x, float y, ...);
#ifdef __MWERKS__
void fn_80169468(int layer, int id, int flag, float x, float y, float r, float g, float b, float a);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_80169468(int, int, float, float, float, float, float, float, int);
static inline void fn_80169468_Reordered(int layer, int id, int flag, float x, float y, float r, float g, float b, float a) { fn_80169468(layer, id, x, y, r, g, b, a, flag); }
#define fn_80169468 fn_80169468_Reordered
#endif
#ifdef __MWERKS__
void fn_801697C0(int layer, int id, int flag, float x, float y, float sx, float sy);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_801697C0(int, int, float, float, float, float, int);
static inline void fn_801697C0_Reordered(int layer, int id, int flag, float x, float y, float sx, float sy) { fn_801697C0(layer, id, x, y, sx, sy, flag); }
#define fn_801697C0 fn_801697C0_Reordered
#endif
#ifdef __MWERKS__
void fn_801698B4(int layer, int id, int flag, float x, float y);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_801698B4(int, int, float, float, int);
static inline void fn_801698B4_Reordered(int layer, int id, int flag, float x, float y) { fn_801698B4(layer, id, x, y, flag); }
#define fn_801698B4 fn_801698B4_Reordered
#endif
float fn_80186960(float a);
int fn_80231BD4(int a, int b, int c);
extern const float lbl_806D6DE4;
extern const float lbl_806D6DE8;
extern unsigned int lbl_806D7CD8;
extern const float lbl_806D7CDC;
extern unsigned int lbl_806D7CE0;
extern unsigned int lbl_806D7CE4;
extern const float lbl_806D7CE8;
extern unsigned int lbl_806D7CEC;
extern unsigned int lbl_806D7CF0;
extern unsigned int lbl_806D7CF4;
extern unsigned int lbl_806D7CF8;
extern unsigned int lbl_806D7CFC;
extern unsigned int lbl_806D7D00;
extern unsigned int lbl_806D7D04;
extern unsigned int lbl_806D7D08;
extern unsigned int lbl_806D7D0C;
extern unsigned int lbl_806D7D10;
extern unsigned int lbl_806D7D14;
extern unsigned int lbl_806D7D18;
extern unsigned int lbl_806D7D1C;
extern unsigned int lbl_806D7D20;
extern unsigned int lbl_806D7D24;
extern unsigned int lbl_806D7D28;
extern unsigned int lbl_806D7D2C;
extern unsigned int lbl_806D7D30;
extern unsigned int lbl_806D7D34;
extern unsigned int lbl_806D7D38;
extern unsigned int lbl_806D7D40;
extern unsigned int lbl_806D7D44;
extern unsigned int lbl_806D7D48;
extern const float lbl_806D7D4C;
extern const float lbl_806D7D50;
extern const float RaceHud_80147470_rodata_80362858[6];
extern unsigned int CountHud_vtable_8048F058[];
extern void fn_80141924();
extern void fn_8014393C();
struct KartVariant *GetKartSlotKartVariant(int slot);
void fn_8014196C(void);
void fn_80143DB0(void);
extern int g_gameMode;
void fn_8023CD54(void *p);
void RumbleUpdate(void);
float Saturate_Double(float v, float lo, float hi);
void *StrPcb_GetInstance(void);
void StrPcb_SetStatusBits(void *p, int bits, int flag);
struct TaEntry *TaRecord_GetEntry_Current(int rank);
void fn_801420DC(void *self);
void fn_801678FC(int layer, float r, float g, float b, float a);
void fn_8023CDA8(void *box);
void fn_8023CFC8(void *box);
void fn_8023CFD4(void *box);
unsigned char get_title_result(void *p, int *a, int *b, int flag);
void wcscpy(void *dst, const short *src);
extern void *lbl_806D10A0;
extern const float lbl_806D7D60;
extern const float lbl_806D7D68;
extern unsigned int lbl_806D7DF8;
extern unsigned int RaceHud_80147470_data_8048F0C8[];
void fn_8014205C(void *self, int flag);
void StrPcb_ClearStatusBits(void *p, int bits);
void fn_8023CFE0(void *p, int flag);
extern unsigned int StrHud_vtable_8048F090[];
int TaRecord_GetLastInsertedRank(void);
extern void fn_8014403C();
extern void fn_80144308();
char *fn_80167744(int n, float t);
unsigned char fn_80169DF0(void);
void fn_8023CCF8(struct StrBox *p, float x, float y);
void fn_8023CD3C(struct StrBox *p, float x, float y);
void fn_8023CEB4(struct StrBox *p);
extern void fn_8023D080();
unsigned char *fn_8024F588(void);
extern float g_totalRaceTime;
extern const float lbl_806D7E00;
extern unsigned int lbl_806D7E04;
extern unsigned int lbl_806D7E08;
extern unsigned int lbl_806D7E0C;
void fn_80141E70(void *self, float x, float y, float w, float h, float r, float g, float b, float a, const char *fmt, ...);
void fn_80142010(void *self, int id, int flag, float x, float y, float w, float h, float r, float g, float b, float a);
extern unsigned int lbl_806D7E10;
extern unsigned int lbl_806D7E14;
extern unsigned int lbl_806D7E18;
extern unsigned int lbl_806D7E1C;
extern char RaceHud_80147470_rodata_803628A8[];
extern void HSD_StateInvalidate();
extern void fn_8011FAB8();
extern void fn_8013D940();
extern void fn_8014095C();
extern void fn_80167F24();
void fn_80169334(void *obj, int id, int flag, float x, float y, float sx, float sy, float a);
extern void fn_801A0004();
extern void fn_80231644();
extern void fn_802317E0();
extern void fn_80231B74();
extern const float lbl_806D7E28;
extern const float lbl_806D7E2C;
extern const float lbl_806D7E30;
extern unsigned int lbl_806D7E34;
extern unsigned int lbl_806D7E38;
extern unsigned int lbl_806D7E3C;
extern unsigned int CSSceneGetTitle_8014ADB4_rodata_80362D90[];
void ClSound_PlayBgmStream(int slot, int id);
void SetRumbleMode(int a, int b, int c);
unsigned char Sprite_AdvanceAnim(void *s, float step);
void clStream_setVolume(int slot, int vol);
unsigned char fn_80140ECC(void *p);
unsigned char fn_8014219C(void *p);
void fn_801699D8(int a, int b);
unsigned char fn_8019083C(int slot);
unsigned char fn_80192010(int id);
void fn_80192688(int id, int a);
int fn_801932F8(void);
extern const float lbl_806D7E40;
extern const float lbl_806D7E44;
extern const float lbl_806D7E48;
extern const float lbl_806D7E4C;
extern const float lbl_806D7E50;
extern unsigned int lbl_806D7E54;
extern unsigned int jumptable_8048F130[];
int Item_GetDescriptorField0(int item, int a);
int Item_GetDescriptorField8(int item);
float *fn_8013BEC8(int a);
extern void fn_8013C26C();
extern void fn_801685A4();
void fn_80168798(void *obj, const char *s, float x, float y, float a, ...);
void fn_801695E0(void *obj, int id, int flag, float x, float y, float a);
extern void fn_801F93D0();
const char *fn_8023DAA8(int item);
extern const float lbl_806D7E58;
extern unsigned int lbl_806D7E5C;
extern unsigned int lbl_806D7E60;
extern unsigned int lbl_806D7E64;
extern unsigned int lbl_806D7E68;
extern unsigned int lbl_806D7E6C;
extern unsigned int lbl_806D7E70;
extern unsigned int lbl_806D7E74;
extern unsigned int lbl_806D7E78;
extern unsigned int lbl_806D7E7C;
extern unsigned int lbl_806D7E80;
extern unsigned int lbl_806D7E84;
extern unsigned int lbl_806D7E88;
extern unsigned int lbl_806D7E94;
extern unsigned int lbl_806D7E98;
extern unsigned int CSSceneGetTitle_8014ADB4_data_8048F0FC[];
int Item_GetDescriptorFieldC(int item);
void fn_8013D50C(void *model, float r, float g, float b, float a);
void fn_8013DAC8(void *model, int a);
void fn_80168B90(void *obj, const char *s, float x, float y, float r, float g, float b, float a, ...);
void fn_80168D84(void *obj, const char *s, float x, float y, float a, ...);
const char *fn_8023D938(int item, int line);
extern unsigned int lbl_806D7E9C;
extern unsigned int lbl_806D7EA0;
extern unsigned int lbl_806D7EA4;
extern unsigned int lbl_806D7EA8;
extern unsigned int lbl_806D7EAC;
extern unsigned int lbl_806D7EB0;
extern unsigned int lbl_806D7EB4;
extern unsigned int lbl_806D7EB8;
extern unsigned int lbl_806D7EBC;
extern unsigned int lbl_806D7EC0;
extern unsigned int lbl_806D7EC4;
extern unsigned int lbl_806D7EC8;
extern unsigned int lbl_806D7ECC;
extern unsigned int lbl_806D7ED0;
extern unsigned int lbl_806D7ED4;
extern unsigned int lbl_806D7ED8;
extern unsigned int lbl_806D7EDC;
extern unsigned int lbl_806D7EE0;
extern unsigned int lbl_806D7EE4;
void Sprite_Destroy(void *p, int flag);
extern void clRom_PurgeAll();
extern void fn_8012094C();
extern void fn_80121210();
extern void fn_8013DB9C();
extern void fn_80169C44();
extern unsigned int lbl_803FE0C8[];
extern unsigned int CSSceneGetTitle_vtable_8048F118[];
extern void CalcEarnedCoins();
extern void InitRumbleController();
extern void ItemRes_LookupByKey_Thunk();
extern void PlayerData_ApplyItemUnlockById();
extern void ProcessSystemTick();
extern void ServiceEnable_Get();
extern void ServiceValue_Get();
extern void Sprite_InitWithAnim();
extern void SyncSlot_GetRecv();
extern void fn_8013BE98();
extern void fn_8013D59C();
extern void fn_8013DBF8();
extern void fn_8013FF6C();
extern void fn_80140FEC();
extern void fn_801426A0();
extern void fn_80142964();
extern void fn_80160238();
extern void fn_801909A4();
extern void fn_8019FF6C();
extern void fn_801D59A0();
extern void fn_801D5C88();
extern void fn_801D6F30();
extern void fn_801DC870();
extern void fn_80209A84();
extern void fn_8023F714();
extern void fn_80271340();
extern void has_title_changed();
extern unsigned int g_ccClass;
extern unsigned int g_roundIndex;
extern unsigned int lbl_806D17F0;
extern unsigned int lbl_806D17F2;
extern unsigned int lbl_806D7EE8;
extern unsigned int lbl_806D7EEC;
extern unsigned int lbl_806D7EF0;
extern unsigned int lbl_806D7EF4;
extern unsigned int lbl_806D7EF8;
extern unsigned int g_playerData[];
extern void dtor_8007D0D4();
int fn_80147470(LapCtrl *self, int idx);
void fn_801474FC(LapCtrl *self, int idx);
int fn_80147530(char *self);
void fn_80147574(char *self, int v);
HudPanel *dtor_80147584(HudPanel *self, short flag);
void fn_80147778(void);
void fn_801477BC(void);
void fn_801478B0(StepHolder *self);
#ifdef NON_MATCHING
extern "C" void fn_80147900(HudResSet *set);
#else
void fn_80147900(struct HudResSet *o);
#endif
void fn_80147AF4(struct HudResSet *o);
void fn_80147CE8(struct HudResSet *o);
void fn_80147EE8(StepHolder *self);
void fn_8014816C(StepHolder *self);
struct RecordPanel *fn_80148648(struct RecordPanel *self, short flag);
#ifdef NON_MATCHING
extern "C" HudResSet *fn_80148A44(HudResSet *set, int coins, int param, int ly);
#else
void fn_80148A44(void);
#endif
void *dtor_8014917C(void *self, short flag);
void fn_801491DC(VObj *p);
void *fn_80149214(void *t);
struct HudResHolder *dtor_80149244(struct HudResHolder *self, short flag) throw();
struct PtrHolder *dtor_80149320(struct PtrHolder *self, short flag) throw();
void fn_801493B0(CountList *self);
void fn_80149420(CdHolder *self);
void fn_801494A4(struct CountListFull *self);
struct CountListFull *fn_80149A88(struct CountListFull *self, short flag);
void fn_80149CD8(void);
void fn_80149D58(VObj *p);
void fn_80149D90(CdHolder2 *self);
HudPanel *fn_8014A890(HudPanel *self, short flag);
struct StrPanel *fn_8014A8FC(struct StrPanel *self, short flag);
void fn_8014AC48(void *self);
void fn_8014AD7C(VObj *p);
void fn_8014ADB4(void);
void fn_8014BBE4(struct ResultPanel *self, float alpha);
void fn_8014BF80(struct ResultPanel *self, float alpha);
struct ResultPanel *fn_8014C308(struct ResultPanel *self, short flag);
void fn_8014C53C(void);

#pragma section R ".extab_user"






__declspec(section ".extab_user") static const unsigned char extab_fn_80147900[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};








__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; void *f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; void *f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; void *f20; } extab_fn_80148A44 = { 0x388A0000, 0x00000090, 0x00000040, 0x000000B0, 0x0000002C, 0x000000C4, 0x018F0020, 0x00000000, 0x0780001F, 0x00000A68, (void *)&dtor_8014917C, 0x0980001F, 0x000003D8, 0x00000003, 0x00000230, (void *)&dtor_800869D0, 0x8980001F, 0x00000010, 0x0000000B, 0x00000058, (void *)&dtor_80082960 };





















#pragma section R ".extabindex_user"







__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147900 = {
    (void *)&fn_80147900, 0x000001F4, (void *)extab_fn_80147900
};








__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80148A44 = {
    (void *)&fn_80148A44, 0x00000738, (void *)&extab_fn_80148A44
};





















}


#include "game/types/ResTrio.h"

inline ResTrio *ResTrio_Destroy(ResTrio *self, short flag) {
    if (self != 0) {
        __destroy_arr(self, (void *)dtor_80082960, 0x58, 3);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#include "game/types/HudResSet.h"

#include "game/types/HudResHolder.h"

#include "game/types/PtrHolder.h"

inline HudResHolder *HudResHolder_Destroy(HudResHolder *self, short flag) throw() {
    if (self != 0) {
        delete self->p;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

inline PtrHolder *PtrHolder_Destroy(PtrHolder *self, short flag) throw() {
    if (self != 0) {
        delete self->p;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

struct ObjTrio {
    int f0;
    VObj *objs[3];
    void SetColor(float a) {
        int i;
        for (i = 0; i < 3; i++) {
            fn_8013D50C(objs[i], 2.0f, 2.0f, 2.0f, a);
        }
    }
    void Apply() {
        int i;
        for (i = 0; i < 3; i++) {
            fn_8013DAC8(objs[i], f0);
        }
    }
    ~ObjTrio() {
        int i;
        for (i = 0; i < 3; i++) {
            delete objs[i];
        }
    }
    static void operator delete(void *p) {
        MemoryManager_TimedFree(p);
    }
};

struct ObjPair {
    int f0;
    VObj *objs[2];
    void SetAlpha(float a) {
        int i;
        for (i = 0; i < 2; i++) {
            fn_8013D4B0(objs[i], a);
        }
    }
    void Apply() {
        int i;
        for (i = 0; i < 2; i++) {
            fn_8013DAC8(objs[i], f0);
        }
    }
    ~ObjPair() {
        int i;
        for (i = 0; i < 2; i++) {
            delete objs[i];
        }
    }
    static void operator delete(void *p) {
        MemoryManager_TimedFree(p);
    }
};

#include "game/types/ResultFader.h"

#include "game/types/Pad14F.h"

#include "game/types/VObj14F.h"

#include "game/types/VObjCF.h"

#include "game/types/HudInput.h"

#include "game/types/ResultPanel.h"

#include "game/types/HudRankSlot.h"

#include "game/types/HudModel.h"

#include "game/types/CountListFull.h"

extern "C" int fn_80147470(LapCtrl *self, int idx) {
    if (idx < 0 || idx >= 2) {
        return 0;
    }
    if (self->mode == 1) {
        if (self->cur != idx) {
            if (self->slots[self->cur].t >= 0.0f) {
                self->slots[self->cur].t = -1.0f;
            }
            self->cur = idx;
            self->f1C = 0.0f;
            fn_801FE390(self);
        }
        return 1;
    }
    return 0;
}

extern "C" void fn_801474FC(LapCtrl *self, int idx) {
    if (idx < 0 || idx >= 2) {
        return;
    }
    if (self->slots[idx].t < 0.0f) {
        self->slots[idx].t = 0.0f;
    }
}

extern "C" int fn_80147530(char *self) {
    if (*(int *)(self + 0x74) > 0) {
        *(int *)(self + 0x74) = *(int *)(self + 0x74) - 1;
        fn_801FE27C(*(int *)(self + 0x74));
        return 1;
    }
    return 0;
}

extern "C" void fn_80147574(char *self, int v) {
    if (v < 0) {
        return;
    }
    *(int *)(self + 0x74) = v;
}

extern "C" HudPanel *dtor_80147584(HudPanel *self, short flag) {
    if (self != 0) {
        self->vt14 = LapHud_vtable_8048EFD4;
        if (self->f78 != 0) {
            self->f78->vC();
        }
        fn_801676AC(self->f7C, 1);
        delete self->f80;
        if (self != 0) {
            self->vt14 = lbl_8048EB44;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

struct LapHudData {
    int f0;
    unsigned char f4;
    float f8;
    float fC;
    float f10;
};

class LapHudBase : public LapHudData {
public:
    LapHudBase() {
        f0 = 0;
        f4 = 0;
        f8 = 0.0f;
        fC = 0.0f;
        f10 = lbl_806D7BA4;
    }
    virtual ~LapHudBase();
};

struct LapHudText {
    int f0;
    int f4;
    int f8;
    LapHudText(int v);
};

struct HudGaugeData {
    int kind;
    char pad4[0x10];
};

class HudGauge : public HudGaugeData {
public:
    virtual ~HudGauge();
    virtual void Start();
    void SetKind(int v) {
        if (v >= 0 && v < 8) {
            kind = v;
        }
    }
};

class LapHudGauge : public HudGauge {
public:
    int f18;
    LapHudGauge();
};

struct LapHudSlot {
    float x;
    float y;
    float w;
    float h;
    char pad10[0x10];
    float hl;
    float t;
};

class LapHud : public LapHudBase {
public:
    int f18;
    float f1C;
    int cur;
    LapHudSlot slots[2];
    int f74;
    int f78;
    LapHudText *text;
    LapHudGauge *gauge;
    LapHud(int cur);
    virtual ~LapHud();
};

LapHud::LapHud(int n) {
    int i;
    f18 = 0;
    f1C = 0.0f;
    cur = n;
    f74 = 1200;
    f78 = 0;
    text = new LapHudText(0);
    gauge = new LapHudGauge;
    gauge->SetKind(f0);
    for (i = 0; i < 2; i++) {
        slots[i].x = 0.0f;
        slots[i].y = 0.0f;
        slots[i].w = 0.0f;
        slots[i].h = 0.0f;
        if (i == cur) {
            slots[i].hl = 15.0f;
        } else {
            slots[i].hl = 0.0f;
        }
        slots[i].t = -1.0f;
    }
}

extern "C" void fn_80147778(void) {
    lbl_8048EFB8[0] = 320.0f - lbl_80362620[0];
    lbl_8048EFB8[1] = 262.0f - lbl_80362620[1];
    lbl_8048EFB8[2] = 320.0f - lbl_80362620[2];
    lbl_8048EFB8[3] = 262.0f - lbl_80362620[3];
}

struct TextManager {
    TextManager();
    ~TextManager() {}
    char pad0[0x18];
    int x18;
    char pad1C[0x230 - 0x1C];
};

struct TexIdPair {
    int a;
    int b;
};

/* .rodata 0x80362778..0x80362858 (record HUD). */
extern const float RaceHud_80147470_rodata_80362778[3] = {0.0f, 0.0f, 0.0f};
static const float sRecordModelPos[3] = {0.0f, 0.0f, -5.0f};
extern const TexIdPair RaceHud_80147470_rodata_80362790[8] = {
    {0, 0}, {0x8D, 0x92}, {0x8E, 0x93}, {0x8E, 0x93},
    {0x8F, 0x94}, {0, 0}, {0x8B, 0x90}, {0x8C, 0x91},
};
static const unsigned short sRecordDigitTex[10] = {
    0x23E7, 0x23E9, 0x23EB, 0x23ED, 0x23EF, 0x23F1, 0x23F3, 0x23F5, 0x23F7, 0x23F9,
};
extern const char lbl_803627E4[] = "clCSResultChallenge";
extern const char lbl_803627F8[] = "clYTaskInterface";
extern const char lbl_8036280C[] = "clCTaskInterface";
static const char sRecordCoinModel[] = "mario_coin.dat";
static const char sRecordKiraModel[] = "k_kira13.dat";
static const char sRecordParamFmt[] = "Param : %d, Coin : %d\n";

extern "C" void fn_801477BC(void) {
    PreloadResource(0x16D8);
    PreloadResource(0x14BA);
    PreloadResource(0x16D1);
    PreloadResource(0x16D2);
    TextManager tm;
    tm.x18 = 1;
    TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x8A, -1));
    TexMgr_Apply(&tm);
    int idx = g_cupId - 8;
    if (idx != 9 && idx != 6) {
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(RaceHud_80147470_rodata_80362790[idx - 1].a, -1));
        TexMgr_Apply(&tm);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(RaceHud_80147470_rodata_80362790[idx - 1].b, -1));
        TexMgr_Apply(&tm);
    }
}

#pragma auto_inline off
extern "C" void fn_801478B0(StepHolder *self) {
    fn_80147900(self->step);
    if (self->step->state == 5) {
        self->t = lbl_806D7C2C;
        self->state = 4;
    }
}
#pragma auto_inline reset

#ifndef NON_MATCHING /* C version: end of this file */
extern "C" asm void fn_80147900(struct HudResSet *o) { /* 0x80147900 size:0x1F4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    lwz r0, 0x0(r3)
    cmpwi r0, 0x3
    beq fn_80147900_L_80147A68
    bge fn_80147900_L_80147940
    cmpwi r0, 0x1
    beq fn_80147900_L_801479BC
    bge fn_80147900_L_80147A60
    cmpwi r0, 0x0
    bge fn_80147900_L_80147950
    b fn_80147900_L_80147AD0
    fn_80147900_L_80147940:
    cmpwi r0, 0x5
    beq fn_80147900_L_80147ADC
    bge fn_80147900_L_80147AD0
    b fn_80147900_L_80147A70
    fn_80147900_L_80147950:
    lwz r0, 0x8(r31)
    cmpwi r0, 0xf
    bgt fn_80147900_L_801479A0
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfs f0, lbl_806D7C38(r2)
    stw r0, 0x8(r1)
    lfd f3, lbl_806D7C20(r2)
    lfd f2, 0x8(r1)
    lfs f1, lbl_806D7C34(r2)
    fsubs f2, f2, f3
    stfs f0, 0xa94(r31)
    fdivs f1, f2, f1
    stfs f1, 0xa98(r31)
    stfs f0, 0xaec(r31)
    stfs f1, 0xaf0(r31)
    stfs f0, 0xb44(r31)
    stfs f1, 0xb48(r31)
    b fn_80147900_L_80147AD0
    fn_80147900_L_801479A0:
    cmpwi r0, 0x2d
    blt fn_80147900_L_80147AD0
    li r3, 0x1
    li r0, 0x0
    stw r3, 0x0(r31)
    stw r0, 0x8(r31)
    b fn_80147900_L_80147AD0
    fn_80147900_L_801479BC:
    lwz r0, 0x8(r31)
    cmpwi r0, 0x14
    bgt fn_80147900_L_80147A30
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    li r4, -0x100
    lfd f2, lbl_806D7C20(r2)
    mr r3, r4
    stw r0, 0x8(r1)
    lfs f0, lbl_806D7C40(r2)
    lfd f1, 0x8(r1)
    lfs f3, lbl_806D7C3C(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fmuls f0, f3, f0
    fctiwz f0, f0
    stfd f0, 0x10(r1)
    lwz r0, 0x14(r1)
    rlwimi r4, r0, 0, 24, 31
    rlwimi r3, r0, 0, 24, 31
    stw r4, 0x3f8(r31)
    stw r4, 0x628(r31)
    stw r4, 0x858(r31)
    stw r3, 0x44(r31)
    stw r3, 0x48(r31)
    stw r3, 0x4c(r31)
    stw r3, 0x50(r31)
    b fn_80147900_L_80147AD0
    fn_80147900_L_80147A30:
    cmpwi r0, 0x50
    blt fn_80147900_L_80147AD0
    li r3, 0x2
    li r0, 0x0
    stw r3, 0x0(r31)
    stw r0, 0x8(r31)
    lbz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne fn_80147900_L_80147AD0
    li r0, 0x3
    stw r0, 0x0(r31)
    b fn_80147900_L_80147AD0
    fn_80147900_L_80147A60:
    bl fn_80147CE8
    b fn_80147900_L_80147AD0
    fn_80147900_L_80147A68:
    bl fn_80147AF4
    b fn_80147900_L_80147AD0
    fn_80147900_L_80147A70:
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r30, r3
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D7C44(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    beq fn_80147900_L_80147AB8
    mr r3, r30
    li r4, 0x2000
    lwz r12, 0x0(r30)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    fn_80147900_L_80147AB8:
    li r3, 0x5
    li r0, 0x0
    stw r3, 0x0(r31)
    stw r0, 0x8(r31)
    b fn_80147900_L_80147AD0
    b fn_80147900_L_80147ADC
    fn_80147900_L_80147AD0:
    lwz r3, 0x8(r31)
    addi r0, r3, 0x1
    stw r0, 0x8(r31)
    fn_80147900_L_80147ADC:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
#endif

/* Views of the HudResSet sub-objects touched by the intro steps. */
static inline unsigned int HudColor_SetAlpha(unsigned int c, int a) {
    return (c & ~0xFF) | (a & 0xFF);
}
struct HudResCtrlView {
    char pad0[0x2C];
    float scaleX;
    float scaleY;
    unsigned int colors[4];
    char pad44[0x58 - 0x44];
};

struct HudTextView {
    char pad0[0x20];
    unsigned int color;
    char pad24[0x230 - 0x24];
};

struct HudResSetView {
    int state;
    int layer;
    int timer;
    unsigned char skipCheck;
    char padD[3];
    HudResCtrlView res[11];
    HudTextView texts[3];
    HudResCtrlView tail[3];
};
static inline void HudTexts_SetColor(HudResSetView *o, int c, int a) {
    c = (c & ~0xFF) | (a & 0xFF);
    for (int i = 0; i < 3; i++) {
        o->texts[i].color = c;
    }
}
static inline void HudRes_SetColor(HudResCtrlView *r, unsigned int c) {
    r->colors[0] = c;
    r->colors[1] = c;
    r->colors[2] = c;
    r->colors[3] = c;
}

static inline void HudTail_SetScale(HudResSetView *o, float sx, float sy) {
    for (int i = 0; i < 3; i++) {
        o->tail[i].scaleX = sx;
        o->tail[i].scaleY = sy;
    }
}

extern "C" void fn_80147AF4(HudResSet *set) {
    HudResSetView *o = (HudResSetView *)set;

    if (1 == o->timer) {
        SoundMgr_Play(0x71);
    }
    if (o->timer < 20) {
        float t = o->timer / 20.0f;
        int a = (int)(3.0f * (255.0f * t));
        if (a > 255) {
            a = 255;
        }
        float s = 0.2f * t + 1.1f;
        for (int i = 1; i < 5; i++) {
            o->res[i].scaleX = s;
            o->res[i].scaleY = s;
        }
        unsigned int color;
        color = HudColor_SetAlpha(0xFFFFFF00, a);
        for (int i = 1; i < 5; i++) {
            HudRes_SetColor(&o->res[i], color);
        }
    } else if (o->timer >= 30) {
        if (o->timer < 45) {
            float t = (o->timer - 30) / 15.0f;
            int a = (int)(255.0f * (t = 1.0f - t));
            float s = 0.2f * t + 1.1f;
            for (int i = 1; i < 5; i++) {
                o->res[i].scaleX = s;
                o->res[i].scaleY = s;
            }
            for (int i = 1; i < 3; i++) {
                HudRes_SetColor(&o->res[i], 0xFFFFFFFF);
            }
            unsigned int color = HudColor_SetAlpha(0xFFFFFF00, a);
            for (int i = 3; i < 5; i++) {
                HudRes_SetColor(&o->res[i], color);
            }
        } else if (o->timer >= 90) {
            { o->state = 4;
            o->timer = 0; }
        }
    }
}

extern "C" void fn_80147CE8(HudResSet *set) {
    HudResSetView *o = (HudResSetView *)set;

    if (o->timer < 20) {
        float t = o->timer / 20.0f;
        int a = (int)(3.0f * (255.0f * t));
        if (a > 255) {
            a = 255;
        }
        float s = 0.2f * t + 1.0f;
        for (int i = 5; i < 9; i++) {
            o->res[i].scaleX = s;
            o->res[i].scaleY = s;
        }
        unsigned int color = HudColor_SetAlpha(0xFFFFFF00, a);
        for (int i = 5; i < 11; i++) {
            HudRes_SetColor(&o->res[i], color);
        }
    } else if (o->timer >= 30) {
        if (o->timer < 45) {
            int a = (int)(255.0f * (1.0f - (o->timer - 30) / 15.0f));
            float s = 0.2f * (1.0f - (o->timer - 30) / 15.0f) + 1.0f;
            for (int i = 5; i < 9; i++) {
                o->res[i].scaleX = s;
                o->res[i].scaleY = s;
            }
            for (int i = 5; i < 8; i++) {
                HudRes_SetColor(&o->res[i], 0xFFFFFFFF);
            }
            unsigned int color = HudColor_SetAlpha(0xFFFFFF00, a);
            for (int i = 8; i < 11; i++) {
                HudRes_SetColor(&o->res[i], color);
            }
        } else if (o->timer >= 90) {
            o->state = 3;
            o->timer = 0;
        }
    }
}

struct ResCtrl {
    int resId;
    int field4;
    int mode;
    int fieldc;
    unsigned char flag;
    char pad11[3];
    float x;
    float y;
    float z;
    float width;
    float height;
    float field28;
    float scaleX;
    float scaleY;
    unsigned int colors[4];
    char pad44[0x58 - 0x44];
    ResCtrl();
    ~ResCtrl() {}
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetSize(float w, float h) {
        width = w;
        height = h;
    }
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
};

inline void ResTrio_Draw(ResTrio *t, int layer) {
    fn_8011FAFC(t->res[0], layer);
    fn_8011FAFC(t->res[1], layer);
    fn_8011FAFC(t->res[2], layer);
}

inline void HudResSet_Draw(HudResSet *res) {
    int i;
    void *ctx = fn_801F8E58();
    ResTrio_Draw(&res->tail, res->layer);
    for (i = 0; i < 3; i++) {
        fn_801F8A34(ctx, res->texts[i], res->layer);
    }
    for (i = 0; i < 11; i++) {
        fn_8011FAFC(res->res[i], res->layer);
    }
}

inline void Record_DrawSparks(StepHolder *self) {
    int i;
    for (i = 0; i < 5; i++) {
        if (self->sparks[i].life >= 0) {
            float a = lbl_806D7C38 - self->sparks[i].life / lbl_806D7C88;
            fn_8013D660(self->m28, self->sparks[i].x, self->sparks[i].y);
            fn_8013D4B0(self->m28, a);
            float sc = lbl_806D7C8C * a;
            fn_8013D608(self->m28, sc, sc, sc);
            self->m28->vC();
        }
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_80147EE8(StepHolder *self) {
    ResCtrl rc;
    rc.SetColor(self->glow);
    rc.mode = 2;
    rc.SetSize(lbl_806D7C74, lbl_806D7C78);
    rc.Show(lbl_806D7C7C, lbl_806D7C80, lbl_806D7C38);
    fn_8011FAFC(&rc, self->layer);
    fn_8011F994(self->layer);
    if (self->state == 0 && self->counter->Tick() == 1) {
        self->counter->v14();
    }
    if (IsCardValid() == 1 && self->active == 1) {
        fn_8014017C(self->f90);
    }
    HudResSet_Draw(self->step);
    fn_8013D660(self->m24, self->cx, self->cy);
    fn_8013D570(self->m24, lbl_806D7C84 * self->rot);
    self->m24->vC();
    Record_DrawSparks(self);
}
#pragma use_lmw_stmw reset

inline void Record_SpawnSpark(StepHolder *self) {
    int i;
    for (i = 0; i < 5; i++) {
        if (self->sparks[i].life < 0) {
            float ang = rand() % 360;
            self->sparks[i].x = 90.0f * Cosf_LUT_Wrap(ang) + self->cx;
            self->sparks[i].y = 90.0f * Sinf_LUT_Wrap(ang) + self->cy;
            self->sparks[i].life = 0;
            return;
        }
    }
}

extern "C" void fn_8014816C(StepHolder *self) {
    int i;
    switch (self->state) {
    case 0:
        if (self->counter->Idle() == 1) {
            self->counter->Start();
        }
        if (self->counter->count >= 2) {
            self->t = lbl_806D7C2C;
            self->state = 1;
            if (g_cupId == 13 && self->active == 1) {
                self->state = 3;
            }
            if (!IsCardValid()) {
                self->state = 4;
            }
        }
        break;
    case 3:
        if (self->t >= 160.0f) {
            self->state = 1;
            self->t = lbl_806D7C2C;
        }
        break;
    case 1: {
        float t = self->t;
        int frame = (int)t;
        if (t < 60.0f) {
            self->cy = 550.0f * Sinf_LUT_Wrap(90.0f * (t / 60.0f)) + 200.0f;
            self->rotSpeed = 30.0f;
            if ((frame & 3) == 0) {
                Record_SpawnSpark(self);
            }
        } else if (t < 70.0f) {
            if ((frame & 3) == 0) {
                Record_SpawnSpark(self);
            }
        } else if (t < 108.0f) {
            self->rotSpeed -= lbl_806D7C6C;
        } else if (t < 138.0f) {
            self->glow += 3;
        } else {
            self->t = lbl_806D7C2C;
            self->state = 2;
        }
        break;
    }
    case 2:
        fn_801478B0(self);
        break;
    case 4:
        if (self->t >= 180.0f) {
            self->t = lbl_806D7C2C;
            self->state = 5;
        }
        break;
    case 5:
        self->done = 1;
        return;
    }
    self->rot += self->rotSpeed;
    if (self->rot > 360.0f) {
        self->rot -= 360.0f;
    }
    for (i = 0; i < 5; i++) {
        if (self->sparks[i].life >= 0) {
            self->sparks[i].y += 4.0f;
            if (++self->sparks[i].life > 10) {
                self->sparks[i].life = -1;
            }
        }
    }
    if (self->active == 1) {
        fn_80140344(self->f90);
    }
    self->t += lbl_806D7C38;
}

struct RecordPanel {
    void *vt;
    char pad4[0x20];
    PtrHolder f24;
    PtrHolder f28;
    char pad2C[0x90 - 0x2C];
    void *f90;
    VObjC *f94;
    HudResHolder f98;
};

extern "C" RecordPanel *fn_80148648(RecordPanel *self, short flag) {
    if (self != 0) {
        self->vt = RecordHud_vtable_8048F020;
        fn_80140810(self->f90, 1);
        self->f94->vC();
        fn_801F8E54();
        fn_80120A08(0x16D8);
        fn_80120A08(0x14BA);
        fn_80120A08(0x16D1);
        fn_80120A08(0x16D2);
        HudResHolder_Destroy(&self->f98, 0);
        PtrHolder_Destroy(&self->f28, 0);
        PtrHolder_Destroy(&self->f24, 0);
        if (self != 0) {
            self->vt = lbl_8048ED10;
            if (self != 0) {
                self->vt = lbl_8048ECF8;
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

class HudRoot {
public:
    virtual ~HudRoot();
    int id;
    int f8;
    int fC;
    HudRoot(int i) : id(i), f8(0), fC(0) {}
};

class HudTask : public HudRoot {
public:
    HudTask(int i) : HudRoot(i) {}
    virtual ~HudTask();
};

class RecSprite : public VObj {
public:
    char pad4[0x1C];
    RecSprite(const char *file, int flag);
};

struct RecFx {
    char pad0[0x24];
    RecFx();
};

class RecCounterCard : public RecordCounter {
public:
    char pad10[0x10];
    RecCounterCard(int layer, int flag);
    static RecordCounter *Create(int layer) {
        return new RecCounterCard(layer, 0);
    }
};

class RecCounterFree : public RecordCounter {
public:
    char pad10[0x4];
    RecCounterFree(int layer, int flag);
    static RecordCounter *Create(int layer) {
        return new RecCounterFree(layer, 0);
    }
};

class RecordHud : public HudTask {
public:
    unsigned char active;
    int layer;
    int state;
    float t;
    int mode;
    PtrHolder m24;
    PtrHolder m28;
    float cx;
    float cy;
    char pad34[4];
    float rot;
    float rotSpeed;
    Spark sparks[5];
    RecFx *f90;
    RecordCounter *counter;
    HudResHolder step;
    unsigned char glow;
    RecordHud(int layer, unsigned char active, int mode, int id);
    virtual ~RecordHud();
};

#pragma use_lmw_stmw on
RecordHud::RecordHud(int ly, unsigned char act, int md, int id)
    : HudTask(id), active(act), layer(ly), state(0), t(lbl_806D7C2C), mode(md),
      m24(new RecSprite(sRecordCoinModel, 0)), m28(new RecSprite(sRecordKiraModel, 1)),
      f90(new RecFx), counter(0), step(new HudResSet(Clamp_Int(GetCoinCount(), 0, 15), md, ly)) {
    int i;
    glow = 0;
    if (active == 1) {
        counter = RecCounterCard::Create(layer);
    } else {
        counter = RecCounterFree::Create(layer);
    }
    fn_8013D738(m24.p, lbl_806D7C2C, lbl_806D7C38);
    fn_8013D608(m24.p, lbl_806D7C8C, lbl_806D7C8C, lbl_806D7C8C);
    fn_8013D634(m24.p, sRecordModelPos[0], sRecordModelPos[1], sRecordModelPos[2]);
    fn_8013D738(m28.p, lbl_806D7C2C, lbl_806D7C38);
    fn_8013D608(m28.p, lbl_806D7C8C, lbl_806D7C8C, lbl_806D7C8C);
    fn_8013D634(m28.p, sRecordModelPos[0], sRecordModelPos[1], sRecordModelPos[2]);
    cx = lbl_806D7C7C;
    cy = lbl_806D7C98;
    rot = lbl_806D7C2C;
    rotSpeed = lbl_806D7C2C;
    for (i = 0; i < 5; i++) {
        sparks[i].life = -1;
    }
}
#pragma use_lmw_stmw reset

#ifndef NON_MATCHING /* C version: end of this file */
extern "C" asm void fn_80148A44(void) { /* 0x80148A44 size:0x738 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stfd f30, 0x40(r1)
    psq_st f30, 0x48(r1), 0, 0
    stmw r25, 0x24(r1)
    mr r31, r3
    li r8, 0x0
    stw r8, 0x0(r3)
    lis r7, ResCtrl_Init@ha
    lis r3, dtor_80082960@ha
    lis r9, RaceHud_80147470_rodata_80362778@ha
    stw r6, 0x4(r31)
    addi r6, r7, ResCtrl_Init@l
    mr r28, r4
    addi r0, r3, dtor_80082960@l
    stw r8, 0x8(r31)
    mr r26, r5
    mr r4, r6
    mr r5, r0
    stb r8, 0xc(r31)
    addi r30, r9, RaceHud_80147470_rodata_80362778@l
    addi r3, r31, 0x10
    li r6, 0x58
    li r7, 0xb
    bl __construct_array
    lis r3, fn_80149214@ha
    lis r5, dtor_800869D0@ha
    addi r4, r3, fn_80149214@l
    li r6, 0x230
    addi r3, r31, 0x3d8
    addi r5, r5, dtor_800869D0@l
    li r7, 0x3
    bl __construct_array
    lis r3, ResCtrl_Init@ha
    lis r5, dtor_80082960@ha
    addi r4, r3, ResCtrl_Init@l
    li r6, 0x58
    addi r3, r31, 0xa68
    addi r5, r5, dtor_80082960@l
    li r7, 0x3
    bl __construct_array
    mr r4, r26
    mr r5, r28
    addi r3, r30, 0xc8
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r6, g_cupId(r13)
    li r0, 0x1d56
    li r4, 0x1d57
    lis r3, 0x6666
    stw r0, 0xa68(r31)
    addi r0, r3, 0x6667
    mulhw r0, r0, r28
    li r3, 0x1d58
    stw r4, 0xac0(r31)
    li r5, 0x1
    lfs f0, lbl_806D7C9C(r2)
    li r4, 0x16d8
    stw r3, 0xb18(r31)
    srawi r0, r0, 2
    lfs f5, lbl_806D7C90(r2)
    srwi r3, r0, 31
    stb r5, 0xa78(r31)
    add. r3, r0, r3
    lfs f4, lbl_806D7C38(r2)
    subi r27, r6, 0x8
    stfs f0, 0xa7c(r31)
    addi r0, r3, 0x14ba
    lfs f0, lbl_806D7CA0(r2)
    stfs f5, 0xa80(r31)
    extsh r0, r0
    lfs f3, lbl_806D7CA4(r2)
    stfs f4, 0xa84(r31)
    lfs f2, lbl_806D7C2C(r2)
    stb r5, 0xad0(r31)
    lfs f1, lbl_806D7CA8(r2)
    stfs f0, 0xad4(r31)
    lfs f0, lbl_806D7CAC(r2)
    stfs f5, 0xad8(r31)
    stfs f4, 0xadc(r31)
    stb r5, 0xb28(r31)
    stfs f3, 0xb2c(r31)
    stfs f5, 0xb30(r31)
    stfs f4, 0xb34(r31)
    stfs f4, 0xa94(r31)
    stfs f2, 0xa98(r31)
    stfs f4, 0xaec(r31)
    stfs f2, 0xaf0(r31)
    stfs f4, 0xb44(r31)
    stfs f2, 0xb48(r31)
    stw r4, 0x10(r31)
    stb r5, 0x20(r31)
    stfs f1, 0x24(r31)
    stfs f0, 0x28(r31)
    stfs f4, 0x2c(r31)
    bne fn_80148A44_L_80148BD4
    li r0, 0x1ecd
    fn_80148A44_L_80148BD4:
    extsh r5, r0
    lis r3, 0x6666
    stw r5, 0x68(r31)
    addi r0, r3, 0x6667
    li r7, 0x1
    lfs f3, lbl_806D7CB0(r2)
    stb r7, 0x78(r31)
    mulhw r4, r0, r28
    lis r3, 0x51ec
    lfs f2, lbl_806D7CB4(r2)
    stfs f3, 0x7c(r31)
    li r6, 0x3
    subi r0, r3, 0x7ae1
    stfs f2, 0x80(r31)
    srawi r3, r4, 2
    lfs f1, lbl_806D7C38(r2)
    srwi r4, r3, 31
    add r3, r3, r4
    lfs f0, lbl_806D7CB8(r2)
    stfs f1, 0x84(r31)
    mulli r4, r3, 0xa
    addi r3, r30, 0x58
    stw r5, 0x118(r31)
    subf r4, r4, r28
    stb r7, 0x128(r31)
    addi r4, r4, 0x14ba
    mulhw r0, r0, r26
    stfs f3, 0x12c(r31)
    extsh r5, r4
    stfs f2, 0x130(r31)
    stfs f1, 0x134(r31)
    srawi r0, r0, 5
    srwi r4, r0, 31
    stw r6, 0x120(r31)
    add. r29, r0, r4
    stw r5, 0xc0(r31)
    slwi r0, r29, 1
    stb r7, 0xd0(r31)
    lhax r0, r3, r0
    stfs f0, 0xd4(r31)
    stfs f2, 0xd8(r31)
    stfs f1, 0xdc(r31)
    stw r5, 0x170(r31)
    stb r7, 0x180(r31)
    stfs f0, 0x184(r31)
    stfs f2, 0x188(r31)
    stfs f1, 0x18c(r31)
    stw r6, 0x178(r31)
    bne fn_80148A44_L_80148C9C
    li r0, 0x1ecd
    fn_80148A44_L_80148C9C:
    lis r3, 0x6666
    extsh r4, r0
    addi r5, r3, 0x6667
    stw r4, 0x1c8(r31)
    mulhw r0, r5, r26
    addi r3, r30, 0x58
    stw r4, 0x2d0(r31)
    li r4, 0x3
    stw r4, 0x2d8(r31)
    srawi r0, r0, 2
    srwi r4, r0, 31
    add. r28, r0, r4
    mulhw r0, r5, r28
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    subf r0, r0, r28
    slwi r0, r0, 1
    lhax r0, r3, r0
    bne fn_80148A44_L_80148CF4
    li r0, 0x1ecd
    fn_80148A44_L_80148CF4:
    lis r3, 0x6666
    extsh r5, r0
    addi r0, r3, 0x6667
    stw r5, 0x220(r31)
    mulhw r4, r0, r26
    addi r3, r30, 0x58
    stw r5, 0x328(r31)
    li r6, 0x3
    li r0, 0xb
    stw r6, 0x330(r31)
    srawi r4, r4, 2
    li r7, 0x0
    srwi r5, r4, 31
    add r4, r4, r5
    mulli r4, r4, 0xa
    li r5, -0x100
    subf r4, r4, r26
    slwi r4, r4, 1
    lhax r3, r3, r4
    stw r3, 0x278(r31)
    stw r3, 0x380(r31)
    stw r6, 0x388(r31)
    mtctr r0
    fn_80148A44_L_80148D50:
    addi r0, r7, 0x44
    addi r4, r7, 0x48
    stwx r5, r31, r0
    addi r3, r7, 0x4c
    addi r0, r7, 0x50
    addi r7, r7, 0x58
    stwx r5, r31, r4
    stwx r5, r31, r3
    stwx r5, r31, r0
    bdnz fn_80148A44_L_80148D50
    li r3, 0x8a
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r31, 0x3d8
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    lfs f1, lbl_806D7CBC(r2)
    addi r3, r31, 0x3d8
    lfs f2, lbl_806D7CAC(r2)
    bl fn_801F93EC
    cmpwi r27, 0x1
    beq fn_80148A44_L_80148DB4
    cmpwi r27, 0x6
    bne fn_80148A44_L_80148E78
    fn_80148A44_L_80148DB4:
    li r0, 0x0
    addi r3, r31, 0x608
    stb r0, 0xc(r31)
    la r4, lbl_806D7CC0(r2)  /* lbl_806D7CC0 */
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r3, r31, 0x838
    la r4, lbl_806D7CC0(r2)  /* lbl_806D7CC0 */
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    li r0, 0x1ecd
    lfs f1, lbl_806D7CBC(r2)
    stw r0, 0x1c8(r31)
    addi r3, r31, 0x3d8
    lfs f2, lbl_806D7C90(r2)
    stw r0, 0x220(r31)
    stw r0, 0x278(r31)
    stw r0, 0x2d0(r31)
    stw r0, 0x328(r31)
    stw r0, 0x380(r31)
    bl fn_801F93EC
    li r0, 0x1
    lfs f5, lbl_806D7CB0(r2)
    stb r0, 0x78(r31)
    lfs f4, lbl_806D7CC4(r2)
    stfs f5, 0x7c(r31)
    lfs f3, lbl_806D7C38(r2)
    stfs f4, 0x80(r31)
    lfs f2, lbl_806D7CB8(r2)
    stfs f3, 0x84(r31)
    lfs f1, lbl_806D7CA8(r2)
    stb r0, 0x128(r31)
    lfs f0, lbl_806D7C90(r2)
    stfs f5, 0x12c(r31)
    stfs f4, 0x130(r31)
    stfs f3, 0x134(r31)
    stb r0, 0xd0(r31)
    stfs f2, 0xd4(r31)
    stfs f4, 0xd8(r31)
    stfs f3, 0xdc(r31)
    stb r0, 0x180(r31)
    stfs f2, 0x184(r31)
    stfs f4, 0x188(r31)
    stfs f3, 0x18c(r31)
    stb r0, 0x20(r31)
    stfs f1, 0x24(r31)
    stfs f0, 0x28(r31)
    stfs f3, 0x2c(r31)
    b fn_80148A44_L_80149104
    fn_80148A44_L_80148E78:
    bl isJapanese
    cmpwi r3, 0x0
    bne fn_80148A44_L_80148E8C
    lfs f31, lbl_806D7CC8(r2)
    b fn_80148A44_L_80148E90
    fn_80148A44_L_80148E8C:
    lfs f31, lbl_806D7C40(r2)
    fn_80148A44_L_80148E90:
    addi r0, r30, 0x18
    slwi r26, r27, 3
    add r27, r0, r26
    lwzu r3, -0x8(r27)
    li r0, 0x1
    li r4, -0x1
    stb r0, 0xc(r31)
    bl GetTextureByIdAndLang
    bl strlen
    addi r0, r30, 0x18
    mr r25, r3
    add r30, r0, r26
    lwzu r3, -0x4(r30)
    li r4, -0x1
    bl GetTextureByIdAndLang
    bl strlen
    cmpwi r28, 0x0
    mr r26, r3
    li r28, 0x1
    ble fn_80148A44_L_80148EE4
    li r28, 0x2
    fn_80148A44_L_80148EE4:
    cmpwi r29, 0x0
    ble fn_80148A44_L_80148EF0
    li r28, 0x3
    fn_80148A44_L_80148EF0:
    mr r29, r28
    bl isJapanese
    cmpwi r3, 0x0
    bne fn_80148A44_L_80148F04
    slwi r29, r28, 1
    fn_80148A44_L_80148F04:
    add r3, r29, r26
    lis r0, 0x4330
    addi r3, r3, 0x1
    stw r0, 0x8(r1)
    add r0, r25, r3
    lfd f3, lbl_806D7C20(r2)
    xoris r0, r0, 0x8000
    lfs f4, lbl_806D7CCC(r2)
    stw r0, 0xc(r1)
    addi r3, r31, 0x608
    lfs f0, lbl_806D7C7C(r2)
    lfd f1, 0x8(r1)
    lfs f2, lbl_806D7CD0(r2)
    fsubs f1, f1, f3
    fmuls f1, f31, f1
    fnmsubs f30, f4, f1, f0
    fmr f1, f30
    bl fn_801F93EC
    addi r0, r25, 0x1
    lis r4, 0x4330
    xoris r0, r0, 0x8000
    stw r4, 0x10(r1)
    lfd f5, lbl_806D7C20(r2)
    cmpwi r28, 0x2
    stw r0, 0x14(r1)
    lfd f0, 0x10(r1)
    fsubs f0, f0, f5
    fmadds f1, f0, f31, f30
    beq fn_80148A44_L_80148FF0
    bge fn_80148A44_L_80148F88
    cmpwi r28, 0x1
    bge fn_80148A44_L_80149058
    b fn_80148A44_L_801490C0
    fn_80148A44_L_80148F88:
    cmpwi r28, 0x4
    bge fn_80148A44_L_801490C0
    xoris r3, r29, 0x8000
    xoris r0, r28, 0x8000
    stw r3, 0x14(r1)
    li r3, 0x1
    lfs f4, lbl_806D7CD0(r2)
    stw r4, 0x10(r1)
    lfs f3, lbl_806D7C38(r2)
    lfd f0, 0x10(r1)
    stw r0, 0xc(r1)
    fsubs f2, f0, f5
    stw r4, 0x8(r1)
    lfd f0, 0x8(r1)
    fmuls f2, f2, f31
    stb r3, 0x1d8(r31)
    fsubs f0, f0, f5
    stfs f1, 0x1dc(r31)
    fdivs f0, f2, f0
    stfs f4, 0x1e0(r31)
    stfs f3, 0x1e4(r31)
    stb r3, 0x2e0(r31)
    stfs f1, 0x2e4(r31)
    stfs f4, 0x2e8(r31)
    fadds f1, f1, f0
    stfs f3, 0x2ec(r31)
    fn_80148A44_L_80148FF0:
    lis r3, 0x4330
    xoris r0, r29, 0x8000
    stw r0, 0x14(r1)
    xoris r0, r28, 0x8000
    li r4, 0x1
    lfd f3, lbl_806D7C20(r2)
    stw r3, 0x10(r1)
    lfs f5, lbl_806D7CD0(r2)
    lfd f0, 0x10(r1)
    stw r0, 0xc(r1)
    fsubs f2, f0, f3
    lfs f4, lbl_806D7C38(r2)
    stw r3, 0x8(r1)
    lfd f0, 0x8(r1)
    fmuls f2, f2, f31
    stb r4, 0x230(r31)
    fsubs f0, f0, f3
    stfs f1, 0x234(r31)
    fdivs f0, f2, f0
    stfs f5, 0x238(r31)
    stfs f4, 0x23c(r31)
    stb r4, 0x338(r31)
    stfs f1, 0x33c(r31)
    stfs f5, 0x340(r31)
    fadds f1, f1, f0
    stfs f4, 0x344(r31)
    fn_80148A44_L_80149058:
    lis r3, 0x4330
    xoris r0, r29, 0x8000
    stw r0, 0x14(r1)
    xoris r0, r28, 0x8000
    li r4, 0x1
    lfd f3, lbl_806D7C20(r2)
    stw r3, 0x10(r1)
    lfs f5, lbl_806D7CD0(r2)
    lfd f0, 0x10(r1)
    stw r0, 0xc(r1)
    fsubs f2, f0, f3
    lfs f4, lbl_806D7C38(r2)
    stw r3, 0x8(r1)
    lfd f0, 0x8(r1)
    fmuls f2, f2, f31
    stb r4, 0x288(r31)
    fsubs f0, f0, f3
    stfs f1, 0x28c(r31)
    fdivs f0, f2, f0
    stfs f5, 0x290(r31)
    stfs f4, 0x294(r31)
    stb r4, 0x390(r31)
    stfs f1, 0x394(r31)
    stfs f5, 0x398(r31)
    fadds f1, f1, f0
    stfs f4, 0x39c(r31)
    fn_80148A44_L_801490C0:
    lfs f2, lbl_806D7CD0(r2)
    addi r3, r31, 0x838
    bl fn_801F93EC
    lwz r3, 0x0(r27)
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r31, 0x608
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    lwz r3, 0x0(r30)
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r31, 0x838
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    fn_80148A44_L_80149104:
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80148A44_L_80149118
    lfs f0, lbl_806D7CD4(r2)
    stfs f0, 0x604(r31)
    fn_80148A44_L_80149118:
    li r28, 0x0
    li r27, -0x100
    mr r25, r28
    li r26, 0x1
    fn_80148A44_L_80149128:
    addi r0, r25, 0x3f8
    addi r3, r25, 0x3d8
    stwx r27, r31, r0
    addi r0, r25, 0x3f0
    add r3, r31, r3
    stwx r26, r31, r0
    bl fn_801F8E90
    addi r28, r28, 0x1
    addi r25, r25, 0x230
    cmpwi r28, 0x3
    blt fn_80148A44_L_80149128
    mr r3, r31
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    psq_l f30, 0x48(r1), 0, 0
    lfd f30, 0x40(r1)
    lmw r25, 0x24(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}
#endif

extern "C" void *dtor_8014917C(void *self, short flag) {
    if (self != 0) {
        __destroy_arr(self, (void *)dtor_80082960, 0x58, 3);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_801491DC(VObj *p) {
    delete p;
}

extern "C" void *fn_80149214(void *t) {
    TexMgr_Init(t);
    return t;
}

extern "C" HudResHolder *dtor_80149244(HudResHolder *self, short flag) throw() {
    if (self != 0) {
        delete self->p;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" PtrHolder *dtor_80149320(PtrHolder *self, short flag) throw() {
    if (self != 0) {
        delete self->p;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_801493B0(CountList *self) {
    if (self->on) {
        int i;
        for (i = 0; i < 6; i++) {
            if (self->e[i].count > 1) {
                self->e[i].obj->vC();
            }
        }
    }
}

extern "C" void fn_80149420(CdHolder *self) {
    if (self->cd != 0) {
        if (Countdown_Tick(self->cd)) {
            ((VObjC *)self->cd)->v14();
        }
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_801494A4(CountListFull *self) {
    int i;
    if (self->f1C != 0 && self->f1C->count >= 2) {
        self->f1C->vC();
        self->f1C = 0;
    }
    if (self->on) {
        for (i = 0; i < 6; i++) {
            HudRankSlot *slot = RankSlot_GetByIndex(i);
            if (slot->kart >= 0 && self->e[i].count == 0) {
                self->e[i].count = 1;
                self->e[i].obj = (VObj *)new HudModel(slot->kart, 1);
                if (slot->active) {
                    fn_8013C6EC(self->e[i].obj, 0.014f, 0.014f, 0.014f);
                    fn_8013C534(self->e[i].obj, 1.0f, 1.0f, 1.0f, 1.0f);
                    self->highlight = i;
                } else {
                    fn_8013C6EC(self->e[i].obj, 0.007f, 0.007f, 0.007f);
                    fn_8013C534(self->e[i].obj, 1.0f, 1.0f, 1.0f, 1.0f);
                }
            }
        }
        if (self->t > 300.0f) {
            for (i = 0; i < 6; i++) {
                HudRankSlot *slot;
                float x;
                float y;
                float sy;
                float sx;
                float off;
                if (self->e[i].count == 0) {
                    continue;
                }
                slot = RankSlot_GetByIndex(i);
                off = lbl_806D7CE8;
                if (i < self->highlight) {
                    off = -25.0f;
                }
                if (i > self->highlight) {
                    off = 25.0f;
                }
                switch (self->e[i].count) {
                case 1:
                    if (i == 0) {
                        self->e[i].count++;
                        self->e[i].t = lbl_806D7CE8;
                    } else if (self->e[i - 1].count == 2) {
                        if (-18.0f * self->e[i - 1].t + 718.0f < 510.0f) {
                            self->e[i].count++;
                            self->e[i].t = lbl_806D7CE8;
                        }
                    } else if (self->e[i - 1].count > 2) {
                        self->e[i].count++;
                        self->e[i].t = lbl_806D7CE8;
                    }
                    x = 718.0f;
                    y = 350.0f;
                    break;
                case 2:
                    self->e[i].t += 1.0f;
                    x = -18.0f * self->e[i].t + 718.0f;
                    y = 350.0f + LUT_Sin12Bit(45.0f * self->e[i].t);
                    sy = lbl_806D7CE8;
                    sx = -1.570796f;
                    if (x < off + RaceHud_80147470_rodata_80362858[i]) {
                        x = off + RaceHud_80147470_rodata_80362858[i];
                        self->e[i].count++;
                        self->e[i].t = lbl_806D7CE8;
                    }
                    break;
                case 3: {
                    float s;
                    self->e[i].t += 1.0f;
                    x = off + RaceHud_80147470_rodata_80362858[i];
                    y = 350.0f;
                    sy = 0.1f * (0.17453292f * self->e[i].t);
                    sx = 1.4311696f * (self->e[i].t / 10.0f) + -1.570796f;
                    if (self->e[i].t <= 8.0f) {
                        s = 1.5f * LUT_Sin12Bit(11.25f * self->e[i].t);
                    } else {
                        s = 0.5f * fn_80186960(45.0f * (self->e[i].t - 8.0f)) + 1.0f;
                    }
                    fn_801697C0(self->layer + 1, i + 0x96B, 0, -20.0f + x, 380.0f, s, s);
                    if (self->e[i].t >= 10.0f) {
                        self->e[i].count++;
                        self->e[i].t = lbl_806D7CE8;
                        if (i == 0) {
                            fn_8013CA70(self->e[i].obj);
                        } else {
                            fn_8013CA04(self->e[i].obj);
                        }
                    }
                    break;
                }
                case 4: {
                    float nx;
                    self->e[i].t += 1.0f;
                    y = 350.0f;
                    x = off + RaceHud_80147470_rodata_80362858[i];
                    sy = 0.17453292f;
                    sx = -0.13962634f;
                    if (slot->icon >= 0) {
                        float ix = 10.0f + x;
                        fn_801697C0(self->layer + 1, slot->icon + 0x2B00, 0, ix, 370.0f, 0.75f * lbl_806D6DE4, 0.75f * lbl_806D6DE8);
                        fn_801697C0(self->layer + 1, fn_80231BD4(slot->chr, slot->kart, 0), 0, ix, 370.0f, 0.75f, 0.75f);
                    }
                    fn_801680A0(self->layer + 1, slot->name, -30.0f + x, 408.0f);
                    nx = -20.0f + x;
                    fn_801698B4(self->layer + 1, i + 0x96B, 0, nx, 380.0f);
                    if (slot->active) {
                        fn_80169468(self->layer + 1, i + 0x96B, 2, nx, 380.0f, 1.0f, 1.0f, 1.0f, 0.8f * LUT_Sin12Bit(lbl_806D7D4C * self->e[i].t));
                    }
                    if (self->e[i].t >= lbl_806D7D50) {
                        self->e[i].t = lbl_806D7CE8;
                    }
                    break;
                }
                }
                fn_8013C7B0(self->e[i].obj, x, y);
                fn_8013C5FC(self->e[i].obj, sx);
                fn_8013C674(self->e[i].obj, sy);
                fn_8013C91C(self->e[i].obj);
            }
        }
    }
    self->f24->v14();
    self->f24->v18();
    if (self->f1C != 0 && self->f1C->Idle()) {
        self->f1C->Start();
    }
    self->t += 1.0f;
}
#pragma use_lmw_stmw reset

extern "C" CountListFull *fn_80149A88(CountListFull *self, short flag) {
    if (self != 0) {
        int i;
        self->vt = CountHud_vtable_8048F058;
        if (self->f1C != 0) {
            self->f1C->vC();
        }
        delete self->f24;
        for (i = 0; i < 6; i++) {
            if (self->e[i].obj != 0) {
                delete self->e[i].obj;
            }
        }
        if (self != 0) {
            self->vt = lbl_8048ED10;
            if (self != 0) {
                self->vt = lbl_8048ECF8;
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

struct CountText {
    char pad0[0x1C];
    CountText(int layer, int flag);
};

class CountGauge : public HudGauge {
public:
    char pad18[0x10];
    CountGauge();
};

struct CountHudEntry {
    int count;
    float t;
    void *obj;
};

class CountHud : public HudTask {
public:
    int layer;
    float t;
    unsigned char on;
    CountText *text;
    int f20;
    CountGauge *gauge;
    int f28;
    CountHudEntry e[6];
    int highlight;
    CountHud(int layer, int id);
    virtual ~CountHud();
};

CountHud::CountHud(int ly, int id) : HudTask(id) {
    int i;
    layer = ly;
    t = lbl_806D7CE8;
    text = new CountText(ly, 0);
    gauge = new CountGauge;
    gauge->SetKind(ly);
    gauge->Start();
    f28 = 0;
    for (i = 0; i < 6; i++) {
        e[i].count = 0;
        e[i].t = lbl_806D7CE8;
        e[i].obj = 0;
    }
    highlight = 6;
    on = 0;
}

extern "C" void fn_80149CD8(void) {
    if (g_gameMode == 2) {
        int i;
        for (i = 0; i < 8; i++) {
            KartVariant *k = GetKartSlotKartVariant(i);
            if (k != 0) {
                int kind = k->kind;
                int sub = k->sub;
                if (kind >= 0 && kind <= 3) {
                    PreloadResource(fn_80231BD4(kind, sub, 0));
                }
            }
        }
    }
    fn_8014196C();
    fn_80143DB0();
}

extern "C" void fn_80149D58(VObj *p) {
    delete p;
}

extern "C" void fn_80149D90(CdHolder2 *self) {
    fn_8023CD54(self->f68);
    if (self->cd != 0) {
        if (Countdown_Tick(self->cd)) {
            ((VObjC *)self->cd)->v14();
        }
    }
    if (self->f60 != 0) {
        self->f60->v1C();
    }
}

struct StrMsg;
class StrDigit : public HudGauge {
public:
    int f18;
    StrDigit(char *res);
};

class StrGauge : public HudGauge {
public:
    char pad18[0x10];
    StrGauge();
};

struct StrBox {
    char pad0[0x20];
    StrBox(int a, int b, int c, int d, int e);
};

class StrHud : public HudTask {
public:
    int layer;
    float f14;
    float f18;
    float f1C;
    int f20;
    int rank;
    unsigned char f28;
    unsigned char f29;
    float time;
    float f30;
    CountText *text;
    StrGauge *gauge;
    StrDigit *digits[9];
    struct StrMsg *f60;
    int f64;
    StrBox *box;
    int f6C;
    short f70[6];
    StrHud(int layer, int id);
    virtual ~StrHud();
};

struct StrMsg {
    int kind;
    unsigned char done;
    char pad5[0xF];
    void *vt14;
    char pad18[0x30];
    StrMsg() {
        fn_801420DC(this);
        vt14 = RaceHud_80147470_data_8048F0C8;
    }
    void SetKind(int v) {
        if (v >= 0 && v < 8) {
            kind = v;
        }
    }
};

struct GaugePos {
    int kind;
    unsigned char done;
    char pad5[3];
    float x;
    float y;
    float alpha;
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

inline bool Countdown_IsDone(Countdown *c) {
    if (c->delay > 0) {
        return 0;
    }
    return c->state <= 0;
}

#include "game/types/TaEntry.h"

inline void *StrTitle_GetInstance() {
    if (lbl_806D10A0 == 0) {
        return 0;
    }
    return lbl_806D10A0;
}

inline unsigned char StrHud_Pressed(int mask) {
    return InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(mask);
}

inline void StrHud_DrawRank(StrHud *self, float a) {
    int i;
    float t;
    LUT_Sin12Bit(3.0f * self->f1C);
    if (self->f18 > 10.0f) {
        t = Saturate_Double((self->f18 - 10.0f) / 25.0f, 0.0f, 1.0f);
        fn_80169468(self->layer, 0x9A4, 0, 173.0f - 320.0f * (1.0f - t), 112.0f, 1.0f, 1.0f, 1.0f, a);
    }
    for (i = 0; i < 9; i++) {
        if (!(self->f18 < 10.0f + 2.0f * (float)i)) {
            t = Saturate_Double((self->f18 - (8.0f + 2.0f * (float)i)) / 25.0f, 0.0f, 1.0f);
            if (0.0f == t) {
                self->digits[i]->Start();
            }
            ((GaugePos *)self->digits[i])->SetPos((40.0f * (float)i + 139.0f) - 320.0f * (1.0f - t), 155.0f);
            ((GaugePos *)self->digits[i])->alpha = a;
            ((VObj14 *)self->digits[i])->v14();
            ((VObj14 *)self->digits[i])->v18();
        }
    }
    self->f18 += 1.0f;
    self->f1C += 1.0f;
    if (self->f1C >= 60.0f) {
        self->f1C = 0.0f;
    }
    ((GaugePos *)self->gauge)->alpha = a;
    ((VObj14 *)self->gauge)->v14();
    ((VObj14 *)self->gauge)->v18();
}

extern "C" void fn_80149E44(StrHud *self) {
    int i;
    float a;
    float t;
    float x;
    switch (self->f20) {
    case 0:
        StrHud_DrawRank(self, 1.0f);
        if (145.0f == self->f14) {
            StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 0);
            fn_8023CFD4(self->box);
        }
        if ((self->f14 += 1.0f) >= 450.0f || (self->f14 > 145.0f && (StrHud_Pressed(0x100) || StrHud_Pressed(0x2000)))) {
            fn_8023CFC8(self->box);
            self->f14 = 0.0f;
            self->fC = 1;
            self->f20 = 5;
        }
        break;
    case 1:
        a = 1.0f - self->f14 / 30.0f;
        StrHud_DrawRank(self, a);
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f * (1.0f - a));
        if ((self->f14 += 1.0f) >= 30.0f) {
            self->f14 = 0.0f;
            if (self->f29 == 1) {
                self->f20 = 2;
            } else if (self->f28 == 0) {
                self->f20 = 3;
            } else {
                self->f20 = 5;
            }
        }
        break;
    case 2:
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f);
        if (self->f60 == 0) {
            StrMsg *m = new StrMsg;
            self->f60 = m;
            if (m != 0) {
                self->f60->SetKind(self->layer);
            }
        } else {
            ((VObj14 *)self->f60)->v14();
            if (self->f60->done) {
                delete (VObj14 *)self->f60;
                self->f60 = 0;
                self->f14 = 0.0f;
                if (self->rank >= 0 && self->rank < 10) {
                    if (self->f28 == 0) {
                        self->f20 = 3;
                    } else {
                        self->f20 = 5;
                    }
                } else {
                    self->fC = 1;
                    self->f20 = 6;
                }
            }
        }
        break;
    case 3: {
        TaEntry *e;
        void *p;
        self->f14 += 1.0f;
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f);
        t = self->f14;
        x = 284.0f;
        if (t < 10.0f) {
            x += 640.0f;
        } else if (t < 25.0f) {
            x += 640.0f + -660.0f * (t - 10.0f) / 15.0f;
        } else if (t < 30.0f) {
            x += -20.0f + 21.0f * (t - 25.0f) / 5.0f;
        }
        fn_801698B4(self->layer, 0x8AE, 0, x, 60.0f);
        self->f6C = 0;
        e = TaRecord_GetEntry_Current(self->rank);
        wcscpy(e, self->f70);
        p = StrTitle_GetInstance();
        if (p != 0) {
            int ra;
            int rb;
            if (get_title_result(p, &ra, &rb, 0)) {
                e->titleA = ra;
                e->titleB = rb;
            }
        }
        self->f20 = 4;
        self->f14 = 0.0f;
        break;
    }
    case 4:
        self->f14 += 1.0f;
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f);
        t = self->f14;
        if (t < 7.0f) {
            x = 50.0f * (t / 7.0f) + 284.0f;
        } else if (t < 13.0f) {
            x = 334.0f - 167.0f * ((t - 7.0f) / 6.0f);
        } else if (t < 17.0f) {
            x = 167.0f - 192.0f * ((t - 13.0f) / 4.0f);
        } else if (t < 20.0f) {
            x = -25.0f - 331.0f * ((t - 17.0f) / 3.0f);
        } else {
            x = -356.0f;
        }
        fn_801698B4(self->layer, 0x8AE, 0, x, 60.0f);
        if (self->f14 > 20.0f) {
            self->f20 = 5;
            self->f14 = 0.0f;
        }
        break;
    case 5:
        if (0.0f == self->f14) {
            fn_80120A08(0x8AE);
        }
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f);
        if ((self->f14 += 1.0f) >= 600.0f || StrHud_Pressed(0x100) || StrHud_Pressed(0x2000)) {
            self->fC = 1;
            self->f14 = 0.0f;
            self->f20 = 6;
        }
        break;
    }
    fn_8023CDA8(self->box);
    if (self->text != 0) {
        if (Countdown_IsDone((Countdown *)self->text)) {
            ((VObjC *)self->text)->v10();
        }
    }
    if (self->f60 != 0) {
        ((VObj14 *)self->f60)->v18();
    }
    RumbleUpdate();
}


extern "C" HudPanel *fn_8014A890(HudPanel *self, short flag) {
    if (self != 0) {
        self->vt14 = RaceHud_80147470_data_8048F0C8;
        fn_80120A08(0x580);
        fn_8014205C(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

struct StrPanel {
    void *vt;
    char pad4[0x30];
    VObjC *f34;
    VObj14 *f38;
    VObj14 *f3C[9];
    VObj14 *f60;
    char pad64[4];
    void *f68;
};

extern "C" StrPanel *fn_8014A8FC(StrPanel *self, short flag) {
    if (self != 0) {
        int i;
        self->vt = StrHud_vtable_8048F090;
        StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
        if (self->f34 != 0) {
            self->f34->vC();
        }
        delete self->f38;
        fn_8023CFE0(self->f68, 1);
        if (self->f60 != 0) {
            delete self->f60;
        }
        for (i = 0; i < 9; i++) {
            delete self->f3C[i];
        }
        if (self != 0) {
            self->vt = lbl_8048ED10;
            if (self != 0) {
                self->vt = lbl_8048ECF8;
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma use_lmw_stmw on
StrHud::StrHud(int ly, int id) : HudTask(id) {
    int i;
    layer = ly;
    f14 = lbl_806D7D68;
    f18 = lbl_806D7D68;
    f1C = lbl_806D7D68;
    f20 = 0;
    time = g_totalRaceTime;
    f30 = lbl_806D7E00;
    rank = TaRecord_GetLastInsertedRank();
    f28 = fn_80169DF0();
    f29 = fn_8024F588()[1];
    f60 = 0;
    for (i = 0; i < 6; i++) {
        f70[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        char *res = fn_80167744(8 - i, time) + 0x998;
        digits[i] = new StrDigit(res);
        digits[i]->SetKind(ly);
        digits[i]->Start();
    }
    text = new CountText(ly, 0);
    gauge = new StrGauge;
    f64 = 0;
    gauge->SetKind(ly);
    box = new StrBox(0x74, -1, 0x1872, -1, 4);
    fn_8023CEB4(box);
    fn_8023CD3C(box, 286.0f, 454.0f);
    fn_8023CCF8(box, 345.0f, 450.0f);
    f6C = 0;
    StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
    StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
}
#pragma use_lmw_stmw reset

extern "C" void fn_8014AC48(void *self) {
    char *str = RaceHud_80147470_rodata_803628A8;
    fn_80142010(self, 0x580, 0, 134.0f, lbl_806D7D68, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60);
    if (isJapanese() == 1) {
        fn_80141E70(self, -212.0f, -52.0f, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, str + 0x494);
        fn_80141E70(self, -212.0f, -22.0f, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, str + 0x4A4);
    } else {
        fn_80141E70(self, -212.0f, -52.0f, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, str + 0x4B8);
        fn_80141E70(self, -212.0f, -22.0f, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, str + 0x4D0);
    }
}

extern "C" void fn_8014AD7C(VObj *p) {
    delete p;
}


__declspec(section ".ctors") static void *const fn_80147778_ctor_ref = (void *)fn_80147778;

#ifdef NON_MATCHING
/* NON_MATCHING: equivalent C++, 99.52 % (target shares one 0xFFFFFF00 constant via mr; docs/gave_up.md). */
extern "C" void fn_80147900(HudResSet *set) {
    HudResSetView *o = (HudResSetView *)set;

    switch (o->state) {
    case 0:
        if (o->timer <= 15) {
            HudTail_SetScale(o, 1.0f, o->timer / 15.0f);
        } else if (o->timer >= 45) {
            o->state = 1;
            o->timer = 0;
        }
        break;
    case 1:
        if (o->timer <= 20) {
            int a = (int)(255.0f * (o->timer / 20.0f));
            int textColor = 0xFFFFFF00;
            textColor = (textColor & ~0xFF) | (a & 0xFF);
            for (int i = 0; i < 3; i++) {
                o->texts[i].color = textColor;
            }
            unsigned int color = HudColor_SetAlpha(0xFFFFFF00, a);
            o->res[0].colors[0] = color;
            o->res[0].colors[1] = color;
            o->res[0].colors[2] = color;
            o->res[0].colors[3] = color;
        } else if (o->timer >= 80) {
            o->state = 2;
            o->timer = 0;
            if (o->skipCheck == 0) {
                o->state = 3;
            }
        }
        break;
    case 2:
        fn_80147CE8(set);
        break;
    case 3:
        fn_80147AF4(set);
        break;
    case 4: {
        HudInput *in = InputMgr_GetPlayer(GetInputManager(), 0);
        if (!(in->v18() >= 0.7f)) {
            in->Pressed(0x2000);
        }
        o->state = 5;
        o->timer = 0;
        break;
    }
    case 5:
        return;
    }
    o->timer++;
}
#endif

#ifdef NON_MATCHING
/* NON_MATCHING: equivalent C++ for the HudResSet ctor (coins, record value, layer).
 * Written as a plain function over a view; the 99.4 % class version is
 * docs/wip/HudResSet_ctor_fn_80148A44_99.4.patch. */
struct NMHudRes {
    int resId;          /* 0x00 */
    int field4;
    int mode;           /* 0x08 */
    int fieldc;
    unsigned char flag; /* 0x10 */
    char pad11[3];
    float x, y, z;      /* 0x14 */
    float width, height;
    float field28;
    float scaleX, scaleY; /* 0x2C */
    unsigned int colors[4]; /* 0x34 */
    char pad44[0x58 - 0x44];
    void Show(float px, float py, float pz) { flag = 1; x = px; y = py; z = pz; }
    void SetColors(unsigned int c) { for (int j = 0; j < 4; j++) colors[j] = c; }
};
struct NMHudText {
    char pad0[0x18];
    int x18;
    int x1c;
    unsigned int color; /* 0x20 */
    char pad24[0x22C - 0x24];
    float y;            /* 0x22C */
};
struct NMHudSet {
    int state;
    int layer;
    int field8;
    unsigned char flagC;
    char padD[3];
    NMHudRes res[11];   /* 0x10 */
    NMHudText texts[3]; /* 0x3D8 */
    NMHudRes tail[3];   /* 0xA68 */
};
#define NM_Printf ((void (*)(const char *, ...))DebugPrintf)
#define NM_ConstructArray ((void (*)(void *, void *, void *, unsigned long, unsigned long))__construct_array)
#define NM_TextSetPos ((void (*)(void *, float, float))fn_801F93EC)
#define NM_TextApply ((void (*)(void *))fn_801F8E90)
#define NM_strlen ((unsigned long (*)(const char *))strlen)
#define NMCC0 lbl_806D7CC0
extern "C" HudResSet *fn_80148A44(HudResSet *set, int coins, int param, int ly) {
    int i;
    short v;
    int idx;
    NMHudSet *o = (NMHudSet *)set;

    o->state = 0;
    o->layer = ly;
    o->field8 = 0;
    o->flagC = 0;
    NM_ConstructArray(o->res, (void *)ResCtrl_Init, (void *)dtor_80082960, 0x58, 11);
    NM_ConstructArray(o->texts, (void *)fn_80149214, (void *)dtor_800869D0, 0x230, 3);
    NM_ConstructArray(o->tail, (void *)ResCtrl_Init, (void *)dtor_80082960, 0x58, 3);
    NM_Printf(sRecordParamFmt, param, coins);
    idx = g_cupId - 8;
    o->tail[0].resId = 0x1D56;
    o->tail[1].resId = 0x1D57;
    o->tail[2].resId = 0x1D58;
    o->tail[0].Show(156.5f, 360.0f, 1.0f);
    o->tail[1].Show(412.5f, 360.0f, 1.0f);
    o->tail[2].Show(576.0f, 360.0f, 1.0f);
    o->tail[0].scaleX = 1.0f;
    o->tail[0].scaleY = 0.0f;
    o->tail[1].scaleX = 1.0f;
    o->tail[1].scaleY = 0.0f;
    o->tail[2].scaleX = 1.0f;
    o->tail[2].scaleY = 0.0f;
    o->res[0].resId = 0x16D8;
    o->res[0].Show(535.0f, 380.0f, 1.0f);
    v = coins / 10 + 0x14BA;
    if (coins / 10 == 0) v = 0x1ECD;
    o->res[1].resId = v;
    o->res[1].Show(400.0f, 375.0f, 1.0f);
    o->res[3].resId = v;
    o->res[3].Show(400.0f, 375.0f, 1.0f);
    o->res[3].mode = 3;
    v = coins % 10 + 0x14BA;
    o->res[2].resId = v;
    o->res[2].Show(450.0f, 375.0f, 1.0f);
    o->res[4].resId = v;
    o->res[4].Show(450.0f, 375.0f, 1.0f);
    o->res[4].mode = 3;
    v = sRecordDigitTex[param / 100];
    if (param / 100 == 0) v = 0x1ECD;
    o->res[5].resId = v;
    o->res[8].resId = v;
    o->res[8].mode = 3;
    v = sRecordDigitTex[(param / 10) % 10];
    if (param / 10 == 0) v = 0x1ECD;
    o->res[6].resId = v;
    o->res[9].resId = v;
    o->res[9].mode = 3;
    v = sRecordDigitTex[param % 10];
    o->res[7].resId = v;
    o->res[10].resId = v;
    o->res[10].mode = 3;
    for (i = 0; i < 11; i++) {
        o->res[i].SetColors(0xFFFFFF00);
    }
    TexMgr_SetTexture((TextManager *)&o->texts[0], GetTextureByIdAndLang(0x8A, -1));
    NM_TextSetPos(&o->texts[0], 80.0f, 380.0f);
    if (idx == 1 || idx == 6) {
        o->flagC = 0;
        TexMgr_SetTexture((TextManager *)&o->texts[1], (const char *)NMCC0);
        TexMgr_SetTexture((TextManager *)&o->texts[2], (const char *)NMCC0);
        o->res[5].resId = 0x1ECD;
        o->res[6].resId = 0x1ECD;
        o->res[7].resId = 0x1ECD;
        o->res[8].resId = 0x1ECD;
        o->res[9].resId = 0x1ECD;
        o->res[10].resId = 0x1ECD;
        NM_TextSetPos(&o->texts[0], 80.0f, 360.0f);
        o->res[1].Show(400.0f, 355.0f, 1.0f);
        o->res[3].Show(400.0f, 355.0f, 1.0f);
        o->res[2].Show(450.0f, 355.0f, 1.0f);
        o->res[4].Show(450.0f, 355.0f, 1.0f);
        o->res[0].Show(535.0f, 360.0f, 1.0f);
    } else {
        float w = isJapanese() == 0 ? 12.0f : 20.0f;
        int len1, len2, n, m, total;
        float x0, x;
        o->flagC = 1;
        len1 = NM_strlen(GetTextureByIdAndLang(RaceHud_80147470_rodata_80362790[idx - 1].a, -1));
        len2 = NM_strlen(GetTextureByIdAndLang(RaceHud_80147470_rodata_80362790[idx - 1].b, -1));
        n = 1;
        if (param / 10 > 0) n = 2;
        if (param / 100 > 0) n = 3;
        m = n;
        if (!isJapanese()) m = n * 2;
        x0 = 320.0f - 0.5f * (w * (float)(len1 + m + len2 + 1));
        NM_TextSetPos(&o->texts[1], x0, 330.0f);
        x = (float)(len1 + 1) * w + x0;
        switch (n) {
        case 3:
            o->res[5].Show(x, 330.0f, 1.0f);
            o->res[8].Show(x, 330.0f, 1.0f);
            x += (float)m * w / (float)n;
        case 2:
            o->res[6].Show(x, 330.0f, 1.0f);
            o->res[9].Show(x, 330.0f, 1.0f);
            x += (float)m * w / (float)n;
        case 1:
            o->res[7].Show(x, 330.0f, 1.0f);
            o->res[10].Show(x, 330.0f, 1.0f);
            x += (float)m * w / (float)n;
        }
        NM_TextSetPos(&o->texts[2], x, 330.0f);
        TexMgr_SetTexture((TextManager *)&o->texts[1], GetTextureByIdAndLang(RaceHud_80147470_rodata_80362790[idx - 1].a, -1));
        TexMgr_SetTexture((TextManager *)&o->texts[2], GetTextureByIdAndLang(RaceHud_80147470_rodata_80362790[idx - 1].b, -1));
    }
    if (isJapanese() == 1) {
        o->texts[0].y = -4.0f;
    }
    for (i = 0; i < 3; i++) {
        o->texts[i].color = 0xFFFFFF00;
        o->texts[i].x18 = 1;
        NM_TextApply(&o->texts[i]);
    }
    return set;
}
#undef NM_Printf
#undef NM_ConstructArray
#undef NM_TextSetPos
#undef NM_TextApply
#undef NM_strlen
#undef NMCC0
#endif
