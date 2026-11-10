/*
 * 0x8014ADB4..0x8014CE74: clCSSceneGetTitle (rank board / prize panel) result-screen
 * controller. Split out of RaceHud_80147470.cpp because this TU owns the pooled
 * .rodata 0x80362D90..0x80363D30 (anchor CSSceneGetTitle_8014ADB4_rodata_80362D90).
 */

/* sdata symbols referenced from asm */
#include "game/types/size_t.h"
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
void fn_801F93EC(void *tm, float x, float y);
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
void fn_80169468(int layer, int id, int flag, float x, float y, float r, float g, float b, float a);
void fn_801697C0(int layer, int id, int flag, float x, float y, float sx, float sy);
void fn_801698B4(int layer, int id, int flag, float x, float y);
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
extern const float lbl_806D7D3C;
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
extern void Saturate_Double();
void *StrPcb_GetInstance(void);
extern void StrPcb_SetStatusBits();
extern void TaRecord_GetEntry_Current();
extern void fn_801420DC();
void fn_801678FC(int layer, float r, float g, float b, float a);
extern void fn_8023CDA8();
extern void fn_8023CFC8();
extern void fn_8023CFD4();
extern void get_title_result();
extern void wcscpy();
extern unsigned int lbl_806D10A0;
extern unsigned int lbl_806D7D58;
extern unsigned int lbl_806D7D5C;
extern const float lbl_806D7D60;
extern unsigned int lbl_806D7D64;
extern const float lbl_806D7D68;
extern unsigned int lbl_806D7D6C;
extern unsigned int lbl_806D7D70;
extern unsigned int lbl_806D7D74;
extern unsigned int lbl_806D7D78;
extern unsigned int lbl_806D7D7C;
extern unsigned int lbl_806D7D80;
extern unsigned int lbl_806D7D84;
extern unsigned int lbl_806D7D88;
extern unsigned int lbl_806D7D8C;
extern unsigned int lbl_806D7D90;
extern unsigned int lbl_806D7D94;
extern unsigned int lbl_806D7D98;
extern unsigned int lbl_806D7D9C;
extern unsigned int lbl_806D7DA0;
extern unsigned int lbl_806D7DA4;
extern unsigned int lbl_806D7DA8;
extern unsigned int lbl_806D7DAC;
extern unsigned int lbl_806D7DB0;
extern unsigned int lbl_806D7DB4;
extern unsigned int lbl_806D7DB8;
extern unsigned int lbl_806D7DBC;
extern unsigned int lbl_806D7DC0;
extern unsigned int lbl_806D7DC4;
extern unsigned int lbl_806D7DC8;
extern unsigned int lbl_806D7DCC;
extern unsigned int lbl_806D7DD0;
extern unsigned int lbl_806D7DD4;
extern unsigned int lbl_806D7DD8;
extern unsigned int lbl_806D7DDC;
extern unsigned int lbl_806D7DE0;
extern unsigned int lbl_806D7DE4;
extern unsigned int lbl_806D7DE8;
extern unsigned int lbl_806D7DEC;
extern unsigned int lbl_806D7DF0;
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
int fn_80169DF0(void);
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
extern void HSD_StateInvalidate(int n);
extern void fn_8011FAB8(void);
extern void fn_8013D940(int i);
extern void fn_8014095C(void *p);
extern void fn_80167F24(int layer, const unsigned short *s, float x, float y, ...);
#ifdef __MWERKS__
void fn_80169334(void *obj, int id, int flag, float x, float y, float sx, float sy, float a);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_80169334(void *, int, float, float, float, float, float, int);
static inline void fn_80169334_Reordered(void *obj, int id, int flag, float x, float y, float sx, float sy, float a) { fn_80169334(obj, id, x, y, sx, sy, a, flag); }
#define fn_80169334 fn_80169334_Reordered
#endif
extern void fn_801A0004(void *spr);
extern unsigned char fn_80231644(int *a, int *b, int *c, int chr, int kart);
extern unsigned char fn_802317E0(int *a, int *b, int *c, int chr, int kart, int special);
extern unsigned char fn_80231B74(int id);
extern const float lbl_806D7E28;
extern const float lbl_806D7E2C;
extern const float lbl_806D7E30;
extern unsigned int lbl_806D7E34;
extern unsigned int lbl_806D7E38;
extern unsigned int lbl_806D7E3C;
extern const unsigned int CSSceneGetTitle_8014ADB4_rodata_80362D90[];
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
const char *fn_8013C26C(int id, int lang);
void fn_801685A4(void *obj, const char *s, float x, float y, float r, float g, float b, float a, ...);
void fn_80168798(void *obj, const char *s, float x, float y, float a, ...);
#ifdef __MWERKS__
void fn_801695E0(void *obj, int id, int flag, float x, float y, float a);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_801695E0(void *, int, float, float, float, int);
static inline void fn_801695E0_Reordered(void *obj, int id, int flag, float x, float y, float a) { fn_801695E0(obj, id, x, y, a, flag); }
#define fn_801695E0 fn_801695E0_Reordered
#endif
void fn_801F93D0(void *tm, float x, float y);
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
extern float lbl_806D7EE4;
void Sprite_Destroy(void *p, int flag);
extern void clRom_PurgeAll();
extern void fn_8012094C();
extern void fn_80121210();
extern void fn_8013DB9C();
extern void fn_80169C44();
extern unsigned int lbl_803FE0C8[];
extern unsigned int CSSceneGetTitle_vtable_8048F118[];
void CalcEarnedCoins(void);
void InitRumbleController(int on);
const char *ItemRes_LookupByKey_Thunk(int key);
void PlayerData_ApplyItemUnlockById(int id);
void ProcessSystemTick(int t);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
struct GtSync *SyncSlot_GetRecv(void);
struct GtItemPose *fn_8013BE98(int id);
void fn_8013D59C(void *m, float x, float y, float z);
void fn_8013DBF8(void);
void fn_801426A0(void *self, int idx, int kart);
void *fn_80160238(void);
void fn_801909A4(int slot);
void fn_8019FF6C(void *sprite, int flag);
int fn_801D59A0(void *pd, int cc, int cup);
void fn_801D5C88(void *pd, int cc);
unsigned char fn_801D6F30(void *pd, int item, int flag);
void fn_801DC870(int mode);
int fn_80209A84(void);
unsigned char fn_8023F714(void);
void *fn_80271340(void *a, int b, void *c, void *d, int e);
unsigned char has_title_changed(void);
extern int g_ccClass;
extern int g_roundIndex;
extern unsigned char lbl_806D17F0;
extern unsigned char lbl_806D17F2;
extern unsigned int lbl_806D7EE8;
extern unsigned int lbl_806D7EEC;
extern unsigned int lbl_806D7EF0;
extern const float lbl_806D7EF4;
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
void fn_80147900(struct HudResSet *o);
void fn_80147AF4(void);
void fn_80147CE8(void);
void fn_80147EE8(StepHolder *self);
void fn_8014816C(StepHolder *self);
struct RecordPanel *fn_80148648(struct RecordPanel *self, short flag);
void fn_80148A44(void);
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
void fn_80149E44(void);
HudPanel *fn_8014A890(HudPanel *self, short flag);
struct StrPanel *fn_8014A8FC(struct StrPanel *self, short flag);
void fn_8014AC48(void *self);
void fn_8014AD7C(VObj *p);
extern "C" void fn_8014ADB4(struct RankBoard *self);
void fn_8014BBE4(struct ResultPanel *self, float alpha);
void fn_8014BF80(struct ResultPanel *self, float alpha);
struct ResultPanel *fn_8014C308(struct ResultPanel *self, short flag);






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
    ObjTrio();
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
};

struct ObjPair {
    int f0;
    VObj *objs[2];
    ObjPair();
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
};

struct ResultFader {
    char pad0[0xC];
    float x;
    float y;
    char pad14[0xC];
    float alpha;
    char pad24[0xC];
    ResultFader(int id, int a, int b);
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

#include "game/types/Pad14F.h"

#include "game/types/VObj14F.h"

#include "game/types/VObjCF.h"

#include "game/types/HudInput.h"

#include "game/types/ResultPanel.h"

#include "game/types/HudRankSlot.h"

#include "game/types/HudModel.h"

#include "game/types/CountListFull.h"

struct GtVec {
    float x, y, z;
};

/* .rodata 0x80362D90..0x80363D30 (raw for now) */
struct RankVec2 {
    float x, y;
};

extern "C" const unsigned int CSSceneGetTitle_8014ADB4_rodata_80362D90[300] = {
    0x00000060, 0x000000FF, 0x00000000, 0x000000C8, 0x00000040, 0x00000000, 0x00000000, 0x00000060,
    0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000,
    0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF,
    0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060,
    0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000, 0x00000060, 0x000000FF, 0x00000000,
    0x00000060, 0x000000FF, 0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x00000000,
};
/* rank board layout per kart count (13) and slot (6) */
/* only the asm functions read these for now */
#pragma force_active on
extern "C" const RankVec2 sRankPortraitPos[13][6] = {
    {{320.0f, 92.0f}, {208.0f, 116.0f}, {423.0f, 132.0f}, {64.0f, 181.0f}, {508.0f, 180.0f}, {590.0f, 196.0f}},
    {{320.0f, 84.0f}, {208.0f, 116.0f}, {423.0f, 132.0f}, {64.0f, 173.0f}, {508.0f, 172.0f}, {590.0f, 196.0f}},
    {{320.0f, 84.0f}, {208.0f, 116.0f}, {423.0f, 132.0f}, {64.0f, 181.0f}, {508.0f, 180.0f}, {590.0f, 196.0f}},
    {{320.0f, 68.0f}, {208.0f, 100.0f}, {423.0f, 116.0f}, {64.0f, 165.0f}, {508.0f, 172.0f}, {590.0f, 188.0f}},
    {{320.0f, 68.0f}, {208.0f, 100.0f}, {423.0f, 116.0f}, {64.0f, 165.0f}, {508.0f, 164.0f}, {590.0f, 196.0f}},
    {{320.0f, 92.0f}, {208.0f, 124.0f}, {423.0f, 140.0f}, {64.0f, 197.0f}, {508.0f, 196.0f}, {590.0f, 212.0f}},
    {{320.0f, 68.0f}, {208.0f, 100.0f}, {423.0f, 116.0f}, {64.0f, 165.0f}, {508.0f, 172.0f}, {590.0f, 196.0f}},
    {{320.0f, 84.0f}, {208.0f, 116.0f}, {423.0f, 132.0f}, {64.0f, 181.0f}, {508.0f, 180.0f}, {590.0f, 204.0f}},
    {{320.0f, 92.0f}, {208.0f, 116.0f}, {423.0f, 132.0f}, {64.0f, 181.0f}, {508.0f, 180.0f}, {590.0f, 204.0f}},
    {{320.0f, 92.0f}, {208.0f, 116.0f}, {423.0f, 132.0f}, {64.0f, 181.0f}, {508.0f, 180.0f}, {590.0f, 204.0f}},
    {{320.0f, 92.0f}, {208.0f, 116.0f}, {423.0f, 132.0f}, {64.0f, 181.0f}, {508.0f, 180.0f}, {590.0f, 204.0f}},
    {{320.0f, 62.0f}, {208.0f, 94.0f}, {423.0f, 110.0f}, {64.0f, 159.0f}, {508.0f, 158.0f}, {590.0f, 190.0f}},
    {{320.0f, 92.0f}, {208.0f, 116.0f}, {423.0f, 132.0f}, {64.0f, 181.0f}, {508.0f, 180.0f}, {590.0f, 204.0f}},
};
extern "C" const RankVec2 sRankNamePos[13][6] = {
    {{296.0f, 48.0f}, {184.0f, 56.0f}, {399.0f, 72.0f}, {40.0f, 117.0f}, {484.0f, 116.0f}, {566.0f, 132.0f}},
    {{296.0f, 40.0f}, {184.0f, 56.0f}, {399.0f, 72.0f}, {40.0f, 109.0f}, {484.0f, 108.0f}, {566.0f, 132.0f}},
    {{296.0f, 40.0f}, {184.0f, 56.0f}, {399.0f, 72.0f}, {40.0f, 117.0f}, {484.0f, 116.0f}, {566.0f, 132.0f}},
    {{296.0f, 24.0f}, {184.0f, 40.0f}, {399.0f, 56.0f}, {40.0f, 101.0f}, {484.0f, 108.0f}, {566.0f, 124.0f}},
    {{296.0f, 24.0f}, {184.0f, 40.0f}, {399.0f, 56.0f}, {40.0f, 101.0f}, {484.0f, 100.0f}, {566.0f, 132.0f}},
    {{296.0f, 48.0f}, {184.0f, 64.0f}, {399.0f, 80.0f}, {40.0f, 133.0f}, {484.0f, 132.0f}, {566.0f, 148.0f}},
    {{296.0f, 24.0f}, {184.0f, 40.0f}, {399.0f, 56.0f}, {40.0f, 101.0f}, {484.0f, 108.0f}, {566.0f, 132.0f}},
    {{296.0f, 40.0f}, {184.0f, 56.0f}, {399.0f, 72.0f}, {40.0f, 117.0f}, {484.0f, 116.0f}, {566.0f, 140.0f}},
    {{296.0f, 48.0f}, {184.0f, 56.0f}, {399.0f, 72.0f}, {40.0f, 117.0f}, {484.0f, 116.0f}, {566.0f, 140.0f}},
    {{296.0f, 48.0f}, {184.0f, 56.0f}, {399.0f, 72.0f}, {40.0f, 117.0f}, {484.0f, 116.0f}, {566.0f, 140.0f}},
    {{296.0f, 48.0f}, {184.0f, 56.0f}, {399.0f, 72.0f}, {40.0f, 117.0f}, {484.0f, 116.0f}, {566.0f, 140.0f}},
    {{296.0f, 18.0f}, {184.0f, 34.0f}, {399.0f, 50.0f}, {40.0f, 95.0f}, {484.0f, 94.0f}, {566.0f, 126.0f}},
    {{296.0f, 48.0f}, {184.0f, 56.0f}, {399.0f, 72.0f}, {40.0f, 117.0f}, {484.0f, 116.0f}, {566.0f, 140.0f}},
};
extern "C" const RankVec2 sRankPos990[13][6] = {
    {{325.0f, 119.0f}, {213.0f, 143.0f}, {428.0f, 159.0f}, {69.0f, 208.0f}, {513.0f, 207.0f}, {595.0f, 223.0f}},
    {{325.0f, 111.0f}, {213.0f, 143.0f}, {428.0f, 159.0f}, {69.0f, 200.0f}, {513.0f, 199.0f}, {595.0f, 223.0f}},
    {{325.0f, 111.0f}, {213.0f, 143.0f}, {428.0f, 159.0f}, {69.0f, 208.0f}, {513.0f, 207.0f}, {595.0f, 223.0f}},
    {{325.0f, 95.0f}, {213.0f, 127.0f}, {428.0f, 143.0f}, {69.0f, 192.0f}, {513.0f, 199.0f}, {595.0f, 215.0f}},
    {{325.0f, 95.0f}, {213.0f, 127.0f}, {428.0f, 143.0f}, {69.0f, 192.0f}, {513.0f, 191.0f}, {595.0f, 223.0f}},
    {{325.0f, 119.0f}, {213.0f, 151.0f}, {428.0f, 167.0f}, {69.0f, 224.0f}, {513.0f, 223.0f}, {595.0f, 239.0f}},
    {{325.0f, 95.0f}, {213.0f, 127.0f}, {428.0f, 143.0f}, {69.0f, 192.0f}, {513.0f, 199.0f}, {595.0f, 223.0f}},
    {{325.0f, 111.0f}, {213.0f, 143.0f}, {428.0f, 159.0f}, {69.0f, 208.0f}, {513.0f, 207.0f}, {595.0f, 231.0f}},
    {{325.0f, 119.0f}, {213.0f, 143.0f}, {428.0f, 159.0f}, {69.0f, 208.0f}, {513.0f, 207.0f}, {595.0f, 231.0f}},
    {{325.0f, 119.0f}, {213.0f, 143.0f}, {428.0f, 159.0f}, {69.0f, 208.0f}, {513.0f, 207.0f}, {595.0f, 231.0f}},
    {{325.0f, 119.0f}, {213.0f, 143.0f}, {428.0f, 159.0f}, {69.0f, 208.0f}, {513.0f, 207.0f}, {595.0f, 231.0f}},
    {{325.0f, 89.0f}, {213.0f, 121.0f}, {428.0f, 137.0f}, {69.0f, 186.0f}, {513.0f, 193.0f}, {595.0f, 217.0f}},
    {{325.0f, 119.0f}, {213.0f, 143.0f}, {428.0f, 159.0f}, {69.0f, 208.0f}, {513.0f, 207.0f}, {595.0f, 231.0f}},
};
extern "C" const RankVec2 sRankNameOnlyPos[13][6] = {
    {{296.0f, 124.0f}, {184.0f, 148.0f}, {399.0f, 164.0f}, {40.0f, 213.0f}, {484.0f, 212.0f}, {566.0f, 228.0f}},
    {{296.0f, 116.0f}, {184.0f, 148.0f}, {399.0f, 164.0f}, {40.0f, 205.0f}, {484.0f, 204.0f}, {566.0f, 228.0f}},
    {{296.0f, 116.0f}, {184.0f, 148.0f}, {399.0f, 164.0f}, {40.0f, 213.0f}, {484.0f, 212.0f}, {566.0f, 228.0f}},
    {{296.0f, 100.0f}, {184.0f, 132.0f}, {399.0f, 148.0f}, {40.0f, 197.0f}, {484.0f, 204.0f}, {566.0f, 220.0f}},
    {{296.0f, 100.0f}, {184.0f, 132.0f}, {399.0f, 148.0f}, {40.0f, 197.0f}, {484.0f, 196.0f}, {566.0f, 228.0f}},
    {{296.0f, 124.0f}, {184.0f, 156.0f}, {399.0f, 172.0f}, {40.0f, 229.0f}, {484.0f, 228.0f}, {566.0f, 244.0f}},
    {{296.0f, 100.0f}, {184.0f, 132.0f}, {399.0f, 148.0f}, {40.0f, 197.0f}, {484.0f, 204.0f}, {566.0f, 228.0f}},
    {{296.0f, 116.0f}, {184.0f, 148.0f}, {399.0f, 164.0f}, {40.0f, 213.0f}, {484.0f, 212.0f}, {566.0f, 236.0f}},
    {{296.0f, 124.0f}, {184.0f, 148.0f}, {399.0f, 164.0f}, {40.0f, 213.0f}, {484.0f, 212.0f}, {566.0f, 236.0f}},
    {{296.0f, 124.0f}, {184.0f, 148.0f}, {399.0f, 164.0f}, {40.0f, 213.0f}, {484.0f, 212.0f}, {566.0f, 236.0f}},
    {{296.0f, 124.0f}, {184.0f, 148.0f}, {399.0f, 164.0f}, {40.0f, 213.0f}, {484.0f, 212.0f}, {566.0f, 236.0f}},
    {{296.0f, 94.0f}, {184.0f, 126.0f}, {399.0f, 142.0f}, {40.0f, 191.0f}, {484.0f, 198.0f}, {566.0f, 222.0f}},
    {{296.0f, 124.0f}, {184.0f, 148.0f}, {399.0f, 164.0f}, {40.0f, 213.0f}, {484.0f, 212.0f}, {566.0f, 236.0f}},
};
/* item trophy model placement (clCSSceneGetTitle ctor) */
static const GtVec sPumpTrioPos[3] = {
    {2.28f, -2.6f, -8.0f},
    {0.71f, -3.3f, 0.0f},
    {-1.39f, -3.8f, 6.0f},
};
static const GtVec sPumpTrioRot[3] = {
    {9.5f, 340.5f, 358.0f},
    {9.5f, 340.5f, 358.0f},
    {9.5f, 340.5f, 358.0f},
};
static const float sPumpTrioScale[3] = {0.65f, 0.83f, 1.13f};
extern "C" const float lbl_80363C54[3] = {0.0f, 1.0f, 1.0f};
static const GtVec sPumpPairPos[2] = {
    {0.0f, -3.0f, 0.0f},
    {0.0f, -3.0f, 0.0f},
};
extern "C" const float lbl_80363C78[3] = {0.0f, 0.0f, 0.0f};
static const GtVec sPumpPairRot = {0.0f, 39.5f, 1.0f};
#pragma force_active reset
extern "C" const unsigned int lbl_80363C90[5] = {
    0x636C4353, 0x5363656E, 0x65476574, 0x5469746C, 0x65000000,
};
extern "C" const unsigned int lbl_80363CA4[5] = {
    0x636C5363, 0x656E6549, 0x6E746572, 0x66616365, 0x00000000,
};
extern "C" const unsigned int lbl_80363CB8[4] = {
    0x20676F74, 0x20612070, 0x72697A65, 0x20210000,
};
extern "C" const unsigned int data_8048EEE8_rodata_80363CC8[3] = {
    0x97448F9F, 0x82B582BD, 0x00000000,
};
extern "C" const unsigned int data_8048EEE8_rodata_80363CD4[7] = {
    0x82C982CD, 0x8FDC9569, 0x82AA91A1, 0x82E782EA, 0x82DC82B5, 0x82BD8149, 0x00000000,
};
extern "C" const char sdata_806CF750_rodata_80363CF0[0x14] = "clCSSceneAccolade";
static const char sPumpFile[0x14] = "it_w_09_pump.dat";
static const char sPumpStandFile[0x18] = "it_w_09_pump_dodai.dat";

/* Rank board shown after the race: per-slot character portrait, voice
 * label and place number, laid out from this area's pooled tables. */
struct RankBoard {
    char pad0[4];
    unsigned char hidden;   /* 0x04 */
    char pad5[3];
    VObj14 *f08;            /* 0x08 */
    char padC[8];
    void *f14;              /* 0x14 */
    char pad18[8];
    unsigned char f20;      /* 0x20 */
    char pad21[3];
    int state;              /* 0x24 */
    char pad28[0x1C];
    VObj14 *f44;            /* 0x44 */
    char pad48[8];
    void *f50;              /* 0x50 */
    char pad54[8];
    float alpha;            /* 0x5C */
    float t;                /* 0x60 */
    void *f64;              /* 0x64 */
};

#pragma use_lmw_stmw on
/* fakematch (callee prototype, regalloc_patterns 74): natural code calls
 * fn_80169334(obj, id, flag, x, y, sx, sy, a). Declaring the float
 * parameters first keeps the same argument registers but makes the compiler
 * evaluate the floats before `id`, as the target does (id is loaded last). */
#ifdef __MWERKS__ /* same registers as the declaration above, another argument order in the source */
namespace RankDraw { extern "C" void fn_80169334(float x, float y, float sx, float sy, float a, void *obj, int id, int flag); }
#else
namespace RankDraw { static inline void fn_80169334(float x, float y, float sx, float sy, float a, void *obj, int id, int flag) { ::fn_80169334(obj, id, flag, x, y, sx, sy, a); } }
#endif
#define SPR(obj, id, flag, x, y, sx, sy, a) RankDraw::fn_80169334(x, y, sx, sy, a, obj, id, flag)
extern "C" void fn_8014ADB4(RankBoard *self)
{
    int i;

    if (self->hidden) {
        return;
    }
    if (self->state > 3) {
        self->t += 0.05f;
        if (self->t > 1.0f) {
            self->t = 1.0f;
        }
        for (i = 0; i < 6; i++) {
            HudRankSlot *slot;
            int kart;
            int portrait;
            int voice;
            int extra;
            unsigned char ok;

            slot = RankSlot_GetByIndex(i);
            if (slot == 0) {
                continue;
            }
            kart = slot->kart;
            if (kart < 0 || kart >= 13) {
                continue;
            }
            if (slot->chr < 0 || slot->chr > 3) {
                continue;
            }
            portrait = 0x2B00;
            voice = 0x1ECD;
            if (g_gameMode == 0) {
                ok = fn_802317E0(&portrait, &voice, &extra, slot->chr, slot->kart, 0);
            } else {
                ok = fn_80231644(&portrait, &voice, &extra, slot->chr, slot->kart);
            }
            if (ok == 1) {
                const RankVec2 *q;
                float dy;
                float yy;

                SPR(0, portrait, 0, sRankPortraitPos[kart][i].x, sRankPortraitPos[kart][i].y, lbl_806D6DE4, lbl_806D6DE8, self->t);
                dy = lbl_806D7E30;
                if (!fn_80231B74(voice)) {
                    dy = *(float *)&lbl_806D7E34;
                }
                yy = sRankPortraitPos[kart][i].y;
                yy = dy + yy;
                SPR(0, voice, 0, sRankPortraitPos[kart][i].x, yy, *(float *)&lbl_806D7E38, *(float *)&lbl_806D7E38, self->t);
                if (i < 3) {
                    SPR(0, i + 0x14DB, 0, sRankPortraitPos[kart][i].x, sRankPortraitPos[kart][i].y, lbl_806D7E2C, lbl_806D7E2C, self->t);
                } else {
                    SPR(0, 0x14DE, 0, sRankPortraitPos[kart][i].x, sRankPortraitPos[kart][i].y, lbl_806D7E2C, lbl_806D7E2C, self->t);
                    SPR(0, i + 0x14DC, 0, sRankPortraitPos[kart][i].x, sRankPortraitPos[kart][i].y - *(float *)&lbl_806D7E3C, lbl_806D7E2C, lbl_806D7E2C, self->t);
                }
                q = &sRankNamePos[kart][i];
                fn_80167F24(0, slot->name, q->x, q->y, self->t);
            } else {
                const RankVec2 *q = &sRankNameOnlyPos[kart][i];
                fn_80167F24(0, slot->name, q->x, q->y, self->t);
            }
        }
    }
    fn_801678FC(0, lbl_806D7E30, lbl_806D7E30, lbl_806D7E30, self->alpha);
    if (self->f20 == 1) {
        self->f08->v1C();
        fn_8014017C(self->f14);
        if (self->state >= 11 && self->state <= 13 && self->f50 != 0) {
            fn_8014095C(self->f50);
        }
        if (self->state >= 5 && self->state <= 7) {
            fn_8011FAB8();
        }
        if (self->state >= 14 && self->state <= 16) {
            self->f44->v18();
            self->f44->v1C();
        }
        if (self->f64 != 0) {
            fn_801A0004(self->f64);
        }
        for (i = 0; i < 8; i++) {
            fn_8013D940(i);
        }
        HSD_StateInvalidate(-1);
    }
}
#pragma use_lmw_stmw reset


extern "C" void fn_8014B118(ResultPanel *self) {
    unsigned char hit;
    if (self->done != 0) {
        return;
    }
    hit = 0;
    if (self->state == 18) {
        self->done = 1;
        return;
    }
    if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x100) ||
        InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x2000)) {
        SetRumbleMode(0, 1, 1);
        hit = 1;
    }
    switch (self->state) {
    case 0:
        if (self->f21 == 0) {
            SoundMgr_Play(0x1F);
            self->f21 = 1;
        }
        fn_801678FC(6, lbl_806D7E30, lbl_806D7E30, lbl_806D7E30, lbl_806D7E2C - self->t / lbl_806D7E40);
        if (self->t >= lbl_806D7E40) {
            self->state = 1;
            self->t = lbl_806D7E30;
            self->fC->vC();
            fn_801699D8(0, 1);
        }
        break;
    case 1:
        self->fC->v14();
        self->fC->v18();
        self->f8->vC();
        self->t = lbl_806D7E30;
        self->state = 2;
        break;
    case 2:
        self->fC->v14();
        self->fC->v18();
        if (fn_8014219C(self->f8) == 1) {
            self->state = 3;
            self->t = lbl_806D7E30;
        }
        break;
    case 3:
        self->fC->v14();
        self->fC->v18();
        self->state = 4;
        self->t = lbl_806D7E30;
        break;
    case 4:
        self->fC->v14();
        self->fC->v18();
        if (self->t >= lbl_806D7E44) {
            if (self->item != 0) {
                self->state = 5;
            } else if (self->f4C != 0) {
                self->state = 11;
            } else if (self->f40 != 0) {
                self->state = 14;
            } else if (self->f70 != 0) {
                self->state = 8;
            } else {
                self->state = 17;
            }
            self->t = lbl_806D7E30;
        }
        break;
    case 5:
        self->fC->v14();
        self->fC->v18();
        if (self->f34 != 0) {
            fn_8014BF80(self, self->t / lbl_806D7E40);
        } else {
            fn_8014BBE4(self, self->t / lbl_806D7E40);
        }
        if (self->t >= lbl_806D7E40) {
            self->t = lbl_806D7E30;
            self->state = 6;
        }
        break;
    case 6:
        self->fC->v14();
        self->fC->v18();
        if (self->f34 != 0) {
            fn_8014BF80(self, lbl_806D7E2C);
        } else {
            fn_8014BBE4(self, lbl_806D7E2C);
        }
        if (self->t >= lbl_806D7E48 || hit) {
            self->state = 7;
            self->t = lbl_806D7E30;
        }
        break;
    case 7:
        self->fC->v14();
        self->fC->v18();
        if (self->f34 != 0) {
            fn_8014BF80(self, lbl_806D7E2C - self->t / lbl_806D7E40);
        } else {
            fn_8014BBE4(self, lbl_806D7E2C - self->t / lbl_806D7E40);
        }
        if (self->t >= lbl_806D7E40) {
            self->t = lbl_806D7E30;
            if (self->f4C != 0) {
                self->state = 11;
            } else if (self->f40 != 0) {
                self->state = 14;
            } else if (self->f70 != 0) {
                self->state = 8;
            } else {
                self->state = 17;
            }
        }
        break;
    case 8:
        self->f58 = 1;
        self->fC->v14();
        self->fC->v18();
        self->f5C = lbl_806D7E4C * self->t / lbl_806D7E40;
        self->f54->v10();
        self->f54->v14();
        if (self->t >= lbl_806D7E40) {
            self->state = 9;
            self->t = lbl_806D7E30;
        }
        break;
    case 9:
        self->fC->v14();
        self->fC->v18();
        self->f54->v10();
        self->f54->v14();
        if (self->f54->f4 == 1) {
            fn_801678FC(7, lbl_806D7E30, lbl_806D7E30, lbl_806D7E30, lbl_806D7E2C);
            self->state = 18;
            self->done = 1;
            self->t = lbl_806D7E30;
        }
        break;
    case 10:
        self->fC->v14();
        self->fC->v18();
        self->f54->v10();
        self->f54->v14();
        if (self->t >= lbl_806D7E50) {
            self->state = 18;
            self->done = 1;
            self->t = lbl_806D7E30;
        }
        break;
    case 11:
        self->fC->v14();
        self->fC->v18();
        if (self->f5C < lbl_806D7E4C) {
            self->f5C = lbl_806D7E4C * self->t / lbl_806D7E40;
        }
        if (self->t >= lbl_806D7E40) {
            self->state = 12;
            self->t = lbl_806D7E30;
        }
        break;
    case 12:
        self->fC->v14();
        self->fC->v18();
        if (self->f50 != 0) {
            self->f50->v14();
            self->f50->v18();
        }
        if (self->f50 != 0 && fn_80140ECC(self->f50)) {
            self->state = 13;
            self->t = lbl_806D7E30;
        }
        break;
    case 13:
        self->fC->v14();
        self->fC->v18();
        self->state = 14;
        self->t = lbl_806D7E30;
        break;
    case 14:
        self->fC->v14();
        self->fC->v18();
        if (self->f5C < lbl_806D7E4C) {
            self->f5C = lbl_806D7E4C * self->t / lbl_806D7E40;
        }
        if (self->t >= lbl_806D7E40) {
            self->state = 15;
            self->t = lbl_806D7E30;
        }
        break;
    case 15:
        self->fC->v14();
        self->fC->v18();
        self->f44->v14();
        if (self->f44->f4 != 0) {
            self->state = 16;
            self->t = lbl_806D7E30;
        }
        break;
    case 16:
        self->fC->v14();
        self->fC->v18();
        self->f44->v14();
        fn_801678FC(7, lbl_806D7E30, lbl_806D7E30, lbl_806D7E30, self->t / lbl_806D7E40);
        self->f5C = self->t / lbl_806D7E40;
        if (self->t >= lbl_806D7E40) {
            self->state = 18;
            self->done = 1;
            self->t = lbl_806D7E30;
        }
        break;
    case 17:
        if (self->f21 != 0) {
            fn_80192688(0x1F, 5);
            self->f21 = 0;
        }
        self->fC->v14();
        self->fC->v18();
        if (self->f58 != 0) {
            self->f54->v10();
            self->f54->v14();
        }
        fn_801678FC(7, lbl_806D7E30, lbl_806D7E30, lbl_806D7E30, self->t / lbl_806D7E40);
        if (self->t >= lbl_806D7E40) {
            self->state = 18;
            self->done = 1;
            self->t = lbl_806D7E30;
            fn_801699D8(0, 0);
        }
        break;
    }
    self->f8->v14();
    fn_80140344(self->f14);
    if (self->f64 != 0) {
        Sprite_AdvanceAnim(self->f64, 0.0165f);
    }
    if (self->state <= 10 && self->state >= 5 && self->f70 == 1 && self->f4C == 0 && self->f40 == 0 &&
        !fn_80192010(0x1F) && !fn_8019083C(1)) {
        ClSound_PlayBgmStream(1, 0);
        clStream_setVolume(1, fn_801932F8());
    }
    RumbleUpdate();
    self->t += lbl_806D7E2C;
    if (self->f20 == 0) {
        self->f20 = 1;
    }
}


#define FK(x) (*(const float *)&(x))

/* 0x230-byte text drawer (ctor TexMgr_Init, inline dtor dtor_800869D0). */
struct TextManager {
    TextManager();
    ~TextManager() {}
    char pad0[0x18];
    int visible;            /* 0x18 */
    char pad1C[4];
    unsigned int color;     /* 0x20 */
    char pad24[0x22C - 0x24];
    float scale;            /* 0x22C */
};

extern "C" void fn_8014BBE4(ResultPanel *self, float alpha) {
    int item = self->item;
    float *col = fn_8013BEC8(Item_GetDescriptorField8(item));
    TextManager tm;
    void *ctx;
    HudRankSlot *slot;
    unsigned short *name;

    ctx = fn_801F8E58();
    fn_80169334(0, 0x14E5, 0, lbl_806D7E58, FK(lbl_806D7E5C), FK(lbl_806D7E60), lbl_806D7E2C, alpha);
    fn_801695E0(0, 0x14E3, 0, FK(lbl_806D7E64), FK(lbl_806D7E68), alpha);
    fn_801695E0(0, 0x14E4, 0, FK(lbl_806D7E6C), FK(lbl_806D7E68), alpha);
    fn_801695E0(0, Item_GetDescriptorField0(item, 0), 0, FK(lbl_806D7E70), FK(lbl_806D7E74), alpha);
    if (!isJapanese()) {
        if (col != 0) {
            fn_801685A4(0, fn_8023DAA8(item), FK(lbl_806D7E64), FK(lbl_806D7E78), col[0], col[1], col[2], col[3] * alpha);
        } else {
            fn_80168798(0, fn_8023DAA8(item), FK(lbl_806D7E64), FK(lbl_806D7E78), alpha);
        }
    } else {
        TexMgr_SetTexture(&tm, fn_8023DAA8(item));
        if (col != 0) {
            float k = FK(lbl_806D7E7C);
            unsigned char r = (int)(k * col[0]);
            unsigned char g = (int)(k * col[1]);
            unsigned char b = (int)(k * col[2]);
            float ka = k * col[3];
            unsigned char a = (int)(ka * alpha);
            tm.color = ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
        } else {
            float ka = FK(lbl_806D7E7C) * col[3];
            tm.color = __rlwimi(-0x100, (unsigned char)(int)(ka * alpha), 0, 24, 31);
        }
        tm.visible = 1;
        fn_801F93EC(&tm, FK(lbl_806D7E64), FK(lbl_806D7E78));
        fn_801F93D0(&tm, FK(lbl_806D7E80), FK(lbl_806D7E80));
        tm.scale = FK(lbl_806D7E84);
        fn_801F8A34(ctx, &tm, 0);
    }
    fn_80169334(0, 0x14E9, 0, lbl_806D7E58, FK(lbl_806D7E88), FK(lbl_806D7E60), lbl_806D7E2C, alpha);
    slot = RankSlot_GetByIndex(0);
    name = slot->name;
    if (name[0] != 0) {
        TexMgr_Init(&tm);
        if (!isJapanese()) {
            TexMgr_SetTexture(&tm, (const char *)lbl_806D7E8C, ((const char **)CSSceneGetTitle_8014ADB4_data_8048F0FC)[2], name, ((const char **)CSSceneGetTitle_8014ADB4_data_8048F0FC)[3]);
        } else {
            TexMgr_SetTexture(&tm, (const char *)lbl_806D7E8C, ((const char **)CSSceneGetTitle_8014ADB4_data_8048F0FC)[0], name, ((const char **)CSSceneGetTitle_8014ADB4_data_8048F0FC)[1]);
        }
        tm.visible = 1;
        fn_801F93EC(&tm, FK(lbl_806D7E94), FK(lbl_806D7E98));
        tm.color = __rlwimi(-0x100, (unsigned char)(int)(FK(lbl_806D7E7C) * alpha), 0, 24, 31);
        fn_801F8A34(ctx, &tm, 0);
    } else {
        fn_80168798(0, GetTextureByIdAndLang(0x4E, -1), FK(lbl_806D7E94), FK(lbl_806D7E98), alpha, fn_8013C26C(slot->kart, -1));
    }
    self->f64->alpha = alpha;
}

#pragma use_lmw_stmw on
extern "C" void fn_8014BF80(ResultPanel *self, float alpha) {
    int item = self->item;
    int a = Item_GetDescriptorField8(item);
    int b = Item_GetDescriptorFieldC(item);
    int idA;
    int idB;
    if (a >= 0) {
        idA = a + 0x503;
    } else {
        idA = -1;
    }
    idB = b >= 0 ? b + 0x1E1D : -1;
    float *col = fn_8013BEC8(a);
    fn_80169334(0, 0x14E5, 0, lbl_806D7E58, 373.0f, 1.25f, lbl_806D7E2C, alpha);
    fn_801695E0(0, 0x14E7, 0, 204.0f, 394.0f, alpha);
    fn_80169334(0, 0x14E8, 0, 420.0f, 394.0f, 10.6f, lbl_806D7E2C, alpha);
    fn_801695E0(0, 0x14E2, 0, 113.0f, 374.0f, alpha);
    fn_80169334(0, 0x14EA, 0, 305.0f, 399.0f, lbl_806D7E2C, lbl_806D7E2C, alpha);
    fn_801695E0(0, idA, 0, 305.0f, 398.0f, alpha);
    fn_801695E0(0, idB, 0, 305.0f, 398.0f, alpha);
    fn_801695E0(0, Item_GetDescriptorField0(item, 0), 0, 365.0f, 402.0f, alpha);
    fn_801695E0(0, 0x14E6, 0, 418.0f, 316.0f, alpha);
    fn_80168798(0, GetTextureByIdAndLang(0x4D, -1), 228.0f, 316.0f, alpha);
    if (col != 0) {
        fn_80168B90(0, fn_8023DAA8(item), 224.0f, 362.0f, col[0], col[1], col[2], col[3] * alpha);
    } else {
        fn_80168D84(0, fn_8023DAA8(item), 224.0f, 362.0f, alpha);
    }
    fn_80168D84(0, fn_8023D938(item, 0), 424.0f, 378.0f, alpha);
    fn_80168D84(0, fn_8023D938(item, 1), 424.0f, 398.0f, alpha);
    fn_80168D84(0, fn_8023D938(item, 2), 424.0f, 418.0f, alpha);
    if (self->f68 != 0) {
        self->f68->SetColor(alpha);
        self->f68->Apply();
    } else if (self->f6C != 0) {
        self->f6C->SetAlpha(alpha);
        self->f6C->Apply();
    } else {
        fn_8013D4B0(self->f3C, alpha);
        fn_8013DAC8(self->f3C, 1);
    }
    self->f64->alpha = alpha;
}
#pragma use_lmw_stmw reset

#pragma use_lmw_stmw on
extern "C" ResultPanel *fn_8014C308(ResultPanel *self, short flag) {
    if (self != 0) {
        self->vt = CSSceneGetTitle_vtable_8048F118;
        fn_8013DB9C();
        if (self->f64 != 0) {
            Sprite_Destroy(self->f64, 1);
            self->f64 = 0;
        }
        delete self->f8;
        delete self->fC;
        delete self->f10;
        fn_80140810(self->f14, 1);
        fn_8023CFE0(self->f18, 1);
        if (self->f68 != 0) {
            delete self->f68;
        }
        if (self->f6C != 0) {
            delete self->f6C;
        }
        if (self->f3C != 0) {
            delete self->f3C;
        }
        if (self->f44 != 0) {
            delete self->f44;
        }
        if (self->f50 != 0) {
            delete self->f50;
        }
        if (self->f54 != 0) {
            self->f54->vC();
        }
        fn_80169C44();
        fn_80121210();
        fn_8012094C();
        clRom_PurgeAll();
        if (self != 0) {
            self->vt = lbl_803FE0C8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma use_lmw_stmw reset

/* clCSSceneGetTitle: base clSceneInterface (vtable lbl_803FE0C8). */
struct GtSceneBase {
    virtual ~GtSceneBase();
    unsigned char done;
    GtSceneBase() : done(0) {}
};

struct GtRankList {
    char data[0x48];
    GtRankList(int flag);
};
struct GtPanelC {
    char data[0x28];
    GtPanelC();
};
struct GtPanel10 {
    char data[0x1C];
    GtPanel10();
};
struct GtPanel14 {
    char data[0x24];
    GtPanel14();
};
struct GtCoinPanel {
    char data[0x44];
    GtCoinPanel();
};
struct GtTitlePanel {
    int f0;
    char pad4[0x280];
    GtTitlePanel();
};
struct GtFlowInfo {
    unsigned char f0;
    char pad1;
    unsigned char f2;
    char pad3;
    int cup;
    int round;
    unsigned char fC;
    void SetNext(int c, int r) {
        f2 = 1;
        cup = c;
        round = r;
    }
};
struct GtItemPose {
    float pos[3];
    float rot[3];
    float scale;
};
struct GtSync {
    int f0;
    int item;
};

class GtModel : public VObj {
public:
    char pad4[0x1C];
    GtModel(const char *name, int flag);
};

/* pump trophy (item 0x9B): three stacked models */
inline unsigned char IsCleared(int count, int round) {
    unsigned char r = 0;
    if (count >= (round >= 4 ? 9 : 4)) {
        r = 1;
    }
    return r;
}

inline void GtSetPos(VObj *o, const GtVec &p, float k) {
    fn_8013D634(o, p.x * k, p.y * k, p.z * k);
}

inline void GtSetScale(VObj *o, float s, float k) {
    float v = s * k;
    fn_8013D608(o, v, v, v);
}

inline ObjTrio::ObjTrio() {
    const GtVec *rot;
    const GtVec *pos;
    const float *scale;
    int i;
    f0 = 1;
    scale = sPumpTrioScale;
    pos = sPumpTrioPos;
    rot = sPumpTrioRot;
    for (i = 0; i < 3; i++) {
        objs[i] = new GtModel(ItemRes_LookupByKey_Thunk(0x32), 1);
        fn_8013D738(objs[i], 0.0f, 1.0f);
        fn_8013D660(objs[i], 114.0f, 358.0f);
        GtSetPos(objs[i], *pos, 0.02f);
        GtSetScale(objs[i], *scale, 0.02f);
        fn_8013D59C(objs[i], 0.017453292f * (*rot).x, 0.017453292f * (*rot).y, 0.017453292f * (*rot).z);
        fn_8013D50C(objs[i], 2.0f, 2.0f, 2.0f, 0.0f);
        scale++;
        pos++;
        rot++;
    }
}

/* pump + stand (item 0x9D) */
inline ObjPair::ObjPair() {
    int i;
    f0 = 1;
    objs[0] = new GtModel(sPumpFile, 1);
    objs[1] = new GtModel(sPumpStandFile, 1);
    for (i = 0; i < 2; i++) {
        const GtVec &p = sPumpPairPos[i];
        fn_8013D738(objs[i], 0.0f, 1.0f);
        fn_8013D660(objs[i], 114.0f, 358.0f);
        GtSetPos(objs[i], p, 0.02f);
        fn_8013D608(objs[i], 0.02f, 0.02f, 0.02f);
        fn_8013D59C(objs[i], 0.017453292f * sPumpPairRot.x, 0.017453292f * sPumpPairRot.y, 0.017453292f * sPumpPairRot.z);
    }
}

class CSSceneGetTitle : public GtSceneBase {
public:
    CSSceneGetTitle();
    virtual ~CSSceneGetTitle();

    GtRankList *f8;
    GtPanelC *fC;
    GtPanel10 *f10;
    GtPanel14 *f14;
    void *f18;
    char pad1C[4];
    unsigned char f20;
    unsigned char f21;
    char pad22[2];
    int state;
    float t;
    char pad2C;
    unsigned char f2D;
    char pad2E[2];
    int kart;
    unsigned char f34;
    char pad35[3];
    int item;
    VObj *f3C;
    unsigned char f40;
    char pad41[3];
    GtCoinPanel *f44;
    int f48;
    unsigned char f4C;
    char pad4D[3];
    GtTitlePanel *f50;
    void *f54;
    unsigned char f58;
    char pad59[3];
    float f5C;
    float f60;
    ResultFader *f64;
    ObjTrio *f68;
    ObjPair *f6C;
    unsigned char f70;
};

#pragma use_lmw_stmw on
/* opt_dead_assignments off: found by tools/pragmasweep.py */
#pragma opt_dead_assignments off
CSSceneGetTitle::CSSceneGetTitle() { /* 0x8014C53C size:0x938 */
    /* local declaration order is load-bearing (register coloring) */
    int cup;
    unsigned char done;
    GtItemPose *pose;
    HudRankSlot *slot;
    int cc;
    int n;
    int round;
    unsigned char sync;
    int i;

    fn_8013DBF8();
    InitRumbleController(1);
    f8 = new GtRankList(1);
    f2D = 1;
    if (!ServiceEnable_Get() || ServiceValue_Get() == 1) {
        f2D = 0;
    }
    for (i = 0; i < 6; i++) {
        HudRankSlot *s = RankSlot_GetByIndex(i);
        if (s != 0) {
            fn_801426A0(f8, i, s->kart);
        }
    }
    ProcessSystemTick(0);
    fC = new GtPanelC;
    f10 = new GtPanel10;
    f14 = new GtPanel14;
    f18 = 0;
    f20 = 0;
    f21 = 0;
    state = 0;
    t = 0.0f;
    item = 0;
    f3C = 0;
    f68 = 0;
    f6C = 0;
    f40 = 0;
    f44 = 0;
    f48 = -1;
    f4C = 0;
    f50 = 0;
    f54 = fn_80271340(fn_80160238(), 0, CSSceneGetTitle_8014ADB4_data_806CF818, lbl_806CF810, 0);
    f58 = 0;
    f5C = 0.0f;
    f60 = 0.0f;
    f64 = 0;
    f70 = has_title_changed();
    ProcessSystemTick(0);
    slot = RankSlot_GetByIndex(0);
    kart = slot->chr;
    f34 = slot->active;
    /* fakematch (permuter): natural code is `cc = g_ccClass;`; the no-op cast
     * makes CW load straight into the callee-saved register. */
    cc = (int)g_ccClass;
    cup = g_cupId;
    round = g_roundIndex;
    fn_801D5C88(g_playerData, cc);
    sync = 0;
    if (slot->f28) {
        switch (g_gameMode) {
        case 0:
            if (f34) {
                if (cup >= 1 && cup <= 8 && round >= 0 && round <= 7) {
                    item = fn_80209A84();
                    if (item <= 0 || item >= 0x115) {
                        item = 0;
                    } else if (fn_801D6F30(g_playerData, item, 1)) {
                        item = 0;
                    }
                    if (item != 0) {
                        PlayerData_ApplyItemUnlockById(item);
                    }
                    lbl_806D17F2 = 1;
                }
                done = 0;
                n = fn_801D59A0(g_playerData, cc, cup);
                if (n >= (round >= 4 ? 9 : 4)) {
                    done = 1;
                }
                if (done) {
                    f40 = 1;
                    f48 = cup + 8;
                }
                if (done == 1 && *fn_8024F588() == 1) {
                    f4C = 1;
                }
            } else {
                fn_801DC870(1);
            }
            break;
        case 2:
            if (kart >= 0 && kart <= 3) {
                item = SyncSlot_GetRecv()->item;
                if (item <= 0 || item >= 0x115) {
                    item = 0;
                }
                if (item != 0 && f34 == 1) {
                    PlayerData_ApplyItemUnlockById(item);
                }
                if (f34 == 1 && fn_8023F714() == 1) {
                    sync = 1;
                }
            }
            break;
        }
    }
    if (f40 == 1) {
        CalcEarnedCoins();
    }
    if (sync == 1) {
        ((GtFlowInfo *)fn_8024F588())->SetNext(g_cupId, g_roundIndex + 1);
        lbl_806D17F0 = 1;
        lbl_806D17F2 = 1;
        fn_801DC870(2);
    }
    if (f40) {
        f44 = new GtCoinPanel;
        GtFlowInfo *info = (GtFlowInfo *)fn_8024F588();
        info->fC = 1;
    }
    if (item != 0 && f34 == 1) {
        pose = fn_8013BE98(item);
        if (item == 0x9B) {
            f68 = new ObjTrio;
            f68->SetColor(0.0f);
        } else if (item == 0x9D) {
            f6C = new ObjPair;
            f6C->SetAlpha(0.0f);
        } else {
            f3C = new GtModel(ItemRes_LookupByKey_Thunk(item), 1);
            fn_8013D738(f3C, 0.0f, 1.0f);
            fn_8013D660(f3C, 114.0f, 358.0f);
            fn_8013D634(f3C, 0.02f * pose->pos[0], 0.02f * pose->pos[1], 0.02f * pose->pos[2]);
            fn_8013D59C(f3C, 0.017453292f * pose->rot[0], 0.017453292f * pose->rot[1], 0.017453292f * pose->rot[2]);
            {
                float s = 0.02f * pose->scale;
                fn_8013D608(f3C, s, s, s);
            }
            if (item == 0x81) {
                fn_8013D50C(f3C, 1.3f, 1.3f, 1.3f, 0.0f);
            }
        }
    }
    f64 = 0;
    if (item != 0) {
        if (f34 == 1) {
            f64 = new ResultFader(0x40, 1, 0);
            f64->SetPos(113.0f, 374.0f);
        } else {
            f64 = new ResultFader(0x41, 1, 0);
            f64->SetPos(320.0f, 373.0f);
        }
        f64->alpha = 0.0f;
        fn_8019FF6C(f64, 1);
    }
    if (fn_8019083C(1)) {
        fn_801909A4(1);
    }
    if (f4C == 1) {
        f50 = new GtTitlePanel;
        f50->f0 = 0;
    }
    PreloadResource(0x14E5);
    if (item != 0) {
        if (f34) {
            PreloadResource(0x14E7);
            PreloadResource(0x14E8);
            PreloadResource(0x14E2);
            PreloadResource(0x14EA);
            PreloadResource(0x14E6);
        } else {
            PreloadResource(0x14E3);
            PreloadResource(0x14E4);
            PreloadResource(0x14E9);
        }
    }
}
#pragma use_lmw_stmw reset
#pragma opt_dead_assignments reset

/* ---- 0x8014CE74..0x8014D540: result-screen 3D part holders (was
 * game/CSPartsHolders.c, merged so fn_8014D038 reaches sPumpPair* /
 * sPumpFile through the section anchor, docs/regalloc_patterns.md §13). */
#pragma use_lmw_stmw on

void *operator new(size_t);
void operator delete(void *);

struct CSPVObj {
    virtual ~CSPVObj();
};

struct Part3D;

extern "C" {
extern void Frame_PostDrawOverlay(void);
extern void Frame_UpdatePerFrameState(void);
}


struct PairHolder {
    int arg;
    Part3D *parts[2];
    ~PairHolder();
};

struct TripleHolder {
    int arg;
    Part3D *parts[3];
    ~TripleHolder();
};

struct Runner {
    virtual void m08();
    virtual void m0C();
    virtual void m10();
    virtual void m14();
    virtual void m18();
};

struct RunnerOwner {
    int m0;
    int m4;
    Runner *runner;
};

struct ResultScene {
    char pad[0x50];
    ResultScene();
};

extern "C" {
TripleHolder *fn_8014D344(TripleHolder *h, int arg, float x, float y, float s);



}


extern "C" void fn_8014CE74(CSPVObj *p) {
    delete p;
}

extern "C" CSSceneGetTitle *fn_8014CEAC(void) {
    return new CSSceneGetTitle();
}

extern "C" void fn_8014CEE8(PairHolder *h, float t) {
    int i;

    for (i = 0; i < 2; i++) {
        fn_8013D4B0(h->parts[i], t);
    }
}

extern "C" void fn_8014CF44(PairHolder *h) {
    int i;

    for (i = 0; i < 2; i++) {
        fn_8013DAC8(h->parts[i], h->arg);
    }
}

extern "C" void fn_8014CFA0(void) {
}

PairHolder::~PairHolder() {
    int i;

    for (i = 0; i < 2; i++) {
        delete (CSPVObj *)parts[i];
    }
}

extern "C" ObjPair *fn_8014D038(ObjPair *h, int arg, float x, float y, float s) {
    int i;
    h->f0 = arg;
    h->objs[0] = new GtModel(sPumpFile, 1);
    h->objs[1] = new GtModel(sPumpStandFile, 1);
    for (i = 0; i < 2; i++) {
        const GtVec &p = sPumpPairPos[i];
        fn_8013D738(h->objs[i], 0.0f, 1.0f);
        fn_8013D660(h->objs[i], x, y);
        GtSetPos(h->objs[i], p, s);
        fn_8013D608(h->objs[i], s, s, s);
        fn_8013D59C(h->objs[i], 0.017453292f * sPumpPairRot.x, 0.017453292f * sPumpPairRot.y, 0.017453292f * sPumpPairRot.z);
    }
    return h;
}

extern "C" void fn_8014D1E0(TripleHolder *h, float a) {
    int i;

    for (i = 0; i < 3; i++) {
        fn_8013D50C(h->parts[i], 2.0f, 2.0f, 2.0f, a);
    }
}

extern "C" void fn_8014D250(TripleHolder *h) {
    int i;

    for (i = 0; i < 3; i++) {
        fn_8013DAC8(h->parts[i], h->arg);
    }
}

extern "C" void fn_8014D2AC(void) {
}

TripleHolder::~TripleHolder() {
    int i;

    for (i = 0; i < 3; i++) {
        delete (CSPVObj *)parts[i];
    }
}

struct PreviewPart {
    char pad[0x20];
    PreviewPart(void *resource, unsigned char flag);
};
struct PartVec { float x, y, z; };

/* Three-model holder ctor body: one preview model per slot, placed from
 * this area's pooled layout tables (positions, rotations in degrees, scales).
 * fakematch (permuter): the slot cursor `c` walks the holder 4 bytes at a
 * time so that the parts pointer gets the target's register; the natural code
 * is `h->parts[i]` with i as the loop index. */
extern "C" TripleHolder *fn_8014D344(TripleHolder *h, int arg, float x, float y, float s) {
    float *scale = (float *)((char *)CSSceneGetTitle_8014ADB4_rodata_80362D90 + 0xEB8);
    PartVec *pos = (PartVec *)((char *)CSSceneGetTitle_8014ADB4_rodata_80362D90 + 0xE70);
    PartVec *rot = (PartVec *)((char *)CSSceneGetTitle_8014ADB4_rodata_80362D90 + 0xE94);
    TripleHolder *c = h;
    float k;
    int i;

    h->arg = arg;
    k = lbl_806D7EF4;
    for (i = 0; i < 3; i++) {
        c->parts[0] = (Part3D *)new PreviewPart((void *)ItemRes_LookupByKey_Thunk(0x32), 1);
        fn_8013D738(c->parts[0], lbl_806D7E30, lbl_806D7E2C);
        fn_8013D660(c->parts[0], x, y);
        fn_8013D634(c->parts[0], pos->x * s, pos->y * s, pos->z * s);
        fn_8013D608(c->parts[0], *scale * s, *scale * s, *scale * s);
        fn_8013D59C(c->parts[0], k * rot->x, k * rot->y, k * rot->z);
        fn_8013D50C(c->parts[0], lbl_806D7EE4, lbl_806D7EE4, lbl_806D7EE4, lbl_806D7E30);
        scale++;
        pos++;
        rot++;
        c = (TripleHolder *)&c->parts[0];
    }
    return h;
}

extern "C" void fn_8014D4B8(RunnerOwner *o) {
    o->runner->m14();
    HSD_StateInvalidate(-1);
}

extern "C" void fn_8014D4F0(RunnerOwner *o) {
    o->runner->m10();
    o->runner->m18();
}
#pragma use_lmw_stmw reset
