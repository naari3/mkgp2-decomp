#ifndef GAME_TYPES_RACEHUD_SUPPORT_H
#define GAME_TYPES_RACEHUD_SUPPORT_H

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
extern unsigned long strlen(const char *);
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


#endif
