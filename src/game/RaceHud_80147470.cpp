
/* sdata symbols referenced from asm */
extern unsigned char lbl_806CF810[8];
extern unsigned char lbl_806CF818[8];
extern unsigned char lbl_806D7CC0[4];
extern unsigned char lbl_806D7E8C[7];
/*
 * 0x80147470..0x8014CE74: race HUD controllers (lap/record panels,
 * countdowns and their text holders).
 */
#pragma cplusplus on

class VObj {
public:
    virtual ~VObj();
};

class VObjC {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
};

struct Pad14 {
    char pad[0x14];
};

class VObj14 : public Pad14 {
public:
    virtual ~VObj14();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
};

struct Countdown {
    void *vt;
    int f4;
    int delay;
    int state;
};

struct LapSlot {
    float t;
    char pad4[0x24];
};

struct LapCtrl {
    char pad0[0x18];
    int mode;
    float f1C;
    int cur;
    char pad24[0x24];
    LapSlot slots[2];
    char pad98[0x74 - 0x98 + 0x50];
};

class RecordCounter {
public:
    virtual void v8();
    virtual void vC();
    virtual void Start();
    virtual void v14();
    int f4;
    int busy;
    int count;
    bool Tick() {
        if (busy > 0) {
            busy--;
            return 0;
        }
        if (count == 1) {
            count = 2;
        }
        return count <= 0;
    }
    bool Idle() {
        if (busy > 0) {
            return 0;
        }
        return count <= 0;
    }
};

struct Spark {
    float x;
    float y;
    float z;
    int life;
};

struct StepHolder {
    char pad0[0xC];
    int done;
    unsigned char active;
    char pad11[3];
    int layer;
    int state;
    float t;
    char pad20[4];
    VObjC *m24;
    VObjC *m28;
    float cx;
    float cy;
    char pad34[4];
    float rot;
    float rotSpeed;
    Spark sparks[5];
    void *f90;
    RecordCounter *counter;
    struct HudResSet *step;
    unsigned char glow;
};

struct KartVariant {
    char pad0[0x1F4];
    int kind;
    int sub;
};

struct CountEntry {
    int count;
    int f4;
    VObjC *obj;
};

struct CountList {
    char pad0[0x18];
    unsigned char on;
    char pad19[0x2C - 0x19];
    CountEntry e[6];
};

struct HudPanel {
    char pad0[0x14];
    void *vt14;
    char pad18[0x60];
    VObjC *f78;
    void *f7C;
    VObj14 *f80;
};

struct CdHolder {
    char pad0[0x1C];
    Countdown *cd;
};

struct CdHolder2 {
    char pad0[0x34];
    Countdown *cd;
    char pad38[0x28];
    VObj14 *f60;
    char pad64[4];
    void *f68;
};

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
extern unsigned int lbl_8048EFD4[];
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
extern struct TexIdPair lbl_80362790[];
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
extern unsigned int lbl_8048F020[];
extern void Clamp_Int();
extern void GetCoinCount();
extern void fn_8013D634();
extern void fn_8013D738();
extern void fn_8013D800();
extern void fn_80140874();
extern void fn_80217F78();
extern void fn_802182BC();
extern unsigned int lbl_806D7C98;
extern unsigned int lbl_80362778[];
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
extern const float lbl_80362858[6];
extern unsigned int lbl_8048F058[];
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
extern unsigned int lbl_8048F0C8[];
void fn_8014205C(void *self, int flag);
void StrPcb_ClearStatusBits(void *p, int bits);
void fn_8023CFE0(void *p, int flag);
extern unsigned int lbl_8048F090[];
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
extern char lbl_803628A8[];
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
extern unsigned int lbl_80362D90[];
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
extern unsigned int lbl_8048F0FC[];
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
extern unsigned int lbl_8048F118[];
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
asm void fn_80147900(struct HudResSet *o);
asm void fn_80147AF4(void);
asm void fn_80147CE8(void);
void fn_80147EE8(StepHolder *self);
void fn_8014816C(StepHolder *self);
struct RecordPanel *fn_80148648(struct RecordPanel *self, short flag);
asm void fn_80148810(void);
asm void fn_80148A44(void);
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
asm void fn_80149E44(void);
HudPanel *fn_8014A890(HudPanel *self, short flag);
struct StrPanel *fn_8014A8FC(struct StrPanel *self, short flag);
void fn_8014AC48(void *self);
void fn_8014AD7C(VObj *p);
asm void fn_8014ADB4(void);
asm void fn_8014BBE4(struct ResultPanel *self, float alpha);
void fn_8014BF80(struct ResultPanel *self, float alpha);
struct ResultPanel *fn_8014C308(struct ResultPanel *self, short flag);
asm void fn_8014C53C(void);

#pragma section R ".extab_user"






__declspec(section ".extab_user") static const unsigned char extab_fn_80147900[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80147AF4[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80147CE8[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};





__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; void *f29; unsigned int f30; unsigned int f31; void *f32; unsigned int f33; void *f34; unsigned int f35; unsigned int f36; void *f37; unsigned int f38; unsigned int f39; void *f40; unsigned int f41; void *f42; unsigned int f43; unsigned int f44; void *f45; unsigned int f46; unsigned int f47; void *f48; unsigned int f49; unsigned int f50; void *f51; unsigned int f52; unsigned int f53; void *f54; unsigned int f55; unsigned int f56; void *f57; unsigned int f58; } extab_fn_80148810 = { 0x280A0000, 0x00000080, 0x00000078, 0x00000094, 0x00000070, 0x000000A0, 0x0000008C, 0x000000B4, 0x00000084, 0x000000C0, 0x000000AC, 0x000000CC, 0x000000A4, 0x000000E0, 0x000000AC, 0x000000EC, 0x000800BC, 0x00000130, 0x000000D0, 0x00000144, 0x000000C8, 0x00000158, 0x000000D0, 0x0000016C, 0x000000E0, 0x00000180, 0x001A00D0, 0x00000000, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801419C8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x00000024, (void *)&dtor_80149320, 0x8680001F, 0x00000000, (void *)&dtor_801419C8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x00000028, (void *)&dtor_80149320, 0x0100008C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x010000AC, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x00000098, (void *)&dtor_80149244, 0x010000AC, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x010000D0 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; void *f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; void *f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; void *f20; } extab_fn_80148A44 = { 0x388A0000, 0x00000090, 0x00000040, 0x000000B0, 0x0000002C, 0x000000C4, 0x018F0020, 0x00000000, 0x0780001F, 0x00000A68, (void *)&dtor_8014917C, 0x0980001F, 0x000003D8, 0x00000003, 0x00000230, (void *)&dtor_800869D0, 0x8980001F, 0x00000010, 0x0000000B, 0x00000058, (void *)&dtor_80082960 };














__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_80149E44 = { 0x214A0000, 0x000005E4, 0x00000010, 0x00000000, 0x8A80001C, (void *)&MemoryManager_TimedFree };






__declspec(section ".extab_user") static const unsigned char extab_fn_8014ADB4[8] = {
    0x40, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_8014BBE4 = { 0x204A0000, 0x0000004C, 0x00C80010, 0x00000000, 0x82000008, (void *)&dtor_800869D0 };



__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; void *f61; unsigned int f62; unsigned int f63; void *f64; unsigned int f65; void *f66; unsigned int f67; unsigned int f68; void *f69; unsigned int f70; void *f71; unsigned int f72; unsigned int f73; void *f74; unsigned int f75; void *f76; unsigned int f77; unsigned int f78; void *f79; unsigned int f80; void *f81; unsigned int f82; unsigned int f83; void *f84; unsigned int f85; void *f86; unsigned int f87; void *f88; unsigned int f89; unsigned int f90; void *f91; unsigned int f92; void *f93; unsigned int f94; void *f95; unsigned int f96; unsigned int f97; void *f98; unsigned int f99; void *f100; unsigned int f101; unsigned int f102; void *f103; unsigned int f104; unsigned int f105; void *f106; unsigned int f107; void *f108; unsigned int f109; unsigned int f110; void *f111; unsigned int f112; void *f113; unsigned int f114; unsigned int f115; void *f116; unsigned int f117; void *f118; unsigned int f119; unsigned int f120; void *f121; } extab_fn_8014C53C = { 0x414A0000, 0x00000068, 0x000400F8, 0x00000088, 0x000000F0, 0x00000098, 0x001800F8, 0x00000104, 0x00000104, 0x00000110, 0x000000F8, 0x0000011C, 0x00000118, 0x00000128, 0x000000F8, 0x00000134, 0x0000012C, 0x00000180, 0x00A500F8, 0x00000420, 0x00000140, 0x00000428, 0x000F00F8, 0x00000498, 0x0000015C, 0x000004A8, 0x00040154, 0x000004CC, 0x0020015C, 0x0000058C, 0x000900F8, 0x000005C8, 0x00000178, 0x000005DC, 0x00000170, 0x000005E8, 0x00000178, 0x000005FC, 0x0000018C, 0x00000634, 0x00160178, 0x000006B8, 0x000700F8, 0x000006E4, 0x00040198, 0x00000708, 0x003000F8, 0x000007E0, 0x000001AC, 0x00000804, 0x000000F8, 0x0000081C, 0x000001C0, 0x0000084C, 0x000B00F8, 0x00000884, 0x000001D4, 0x0000089C, 0x001700F8, 0x00000000, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x01000178, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4 };

#pragma section R ".extabindex_user"







__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147900 = {
    (void *)&fn_80147900, 0x000001F4, (void *)extab_fn_80147900
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147AF4 = {
    (void *)&fn_80147AF4, 0x000001F4, (void *)extab_fn_80147AF4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147CE8 = {
    (void *)&fn_80147CE8, 0x00000200, (void *)extab_fn_80147CE8
};





__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80148810 = {
    (void *)&fn_80148810, 0x00000234, (void *)&extab_fn_80148810
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80148A44 = {
    (void *)&fn_80148A44, 0x00000738, (void *)&extab_fn_80148A44
};














__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80149E44 = {
    (void *)&fn_80149E44, 0x00000A4C, (void *)&extab_fn_80149E44
};






__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014ADB4 = {
    (void *)&fn_8014ADB4, 0x00000364, (void *)extab_fn_8014ADB4
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014BBE4 = {
    (void *)&fn_8014BBE4, 0x0000039C, (void *)&extab_fn_8014BBE4
};



__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014C53C = {
    (void *)&fn_8014C53C, 0x00000938, (void *)&extab_fn_8014C53C
};

}


struct ResTrio {
    char res[3][0x58];
};

inline ResTrio *ResTrio_Destroy(ResTrio *self, short flag) {
    if (self != 0) {
        __destroy_arr(self, (void *)dtor_80082960, 0x58, 3);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

struct HudResSet {
    int state;
    int layer;
    char pad8[8];
    char res[11][0x58];
    char texts[3][0x230];
    ResTrio tail;
    ~HudResSet() {
        ResTrio_Destroy(&tail, 0);
        __destroy_arr(texts, (void *)dtor_800869D0, 0x230, 3);
        __destroy_arr(res, (void *)dtor_80082960, 0x58, 11);
    }
    static void operator delete(void *p) {
        MemoryManager_TimedFree(p);
    }
};

struct HudResHolder {
    HudResSet *p;
};

struct PtrHolder {
    VObj *p;
};

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

struct ResultFader {
    char pad0[0x20];
    float alpha;
};

struct Pad14F {
    char pad0[4];
    unsigned char f4;
    char pad5[0xF];
};

class VObj14F : public Pad14F {
public:
    virtual ~VObj14F();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
};

class VObjCF : public VObjC {
public:
    unsigned char f4;
};

class HudInput {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual float v18();
    virtual void v1C();
    virtual unsigned char Pressed(int mask);
};

struct ResultPanel {
    void *vt;
    unsigned char done;
    char pad5[3];
    VObj14 *f8;
    VObj14 *fC;
    VObj14 *f10;
    void *f14;
    void *f18;
    char pad1C[4];
    unsigned char f20;
    unsigned char f21;
    char pad22[2];
    int state;
    float t;
    char pad2C[8];
    unsigned char f34;
    char pad35[3];
    int item;
    VObj *f3C;
    unsigned char f40;
    char pad41[3];
    VObj14F *f44;
    char pad48[4];
    unsigned char f4C;
    char pad4D[3];
    VObj14 *f50;
    VObjCF *f54;
    unsigned char f58;
    char pad59[3];
    float f5C;
    char pad60[4];
    ResultFader *f64;
    ObjTrio *f68;
    ObjPair *f6C;
    unsigned char f70;
};

struct HudRankSlot {
    unsigned char active;
    char pad1;
    unsigned short name[7];
    int chr;
    int kart;
    char pad18[4];
    int icon;
};

struct HudModel {
    char data[0x90];
    HudModel(int kart, int flag) {
        fn_8013CC24(this, kart, flag);
    }
};

struct CountListFull {
    void *vt;
    char pad4[0xC];
    int layer;
    float t;
    unsigned char on;
    char pad19[3];
    RecordCounter *f1C;
    char pad20[4];
    VObj14 *f24;
    char pad28[4];
    struct {
        int count;
        float t;
        VObj *obj;
    } e[6];
    int highlight;
};

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
        self->vt14 = lbl_8048EFD4;
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
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(lbl_80362790[idx - 1].a, -1));
        TexMgr_Apply(&tm);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(lbl_80362790[idx - 1].b, -1));
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

extern "C" asm void fn_80147AF4(void) { /* 0x80147AF4 size:0x1F4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    lwz r0, 0x8(r3)
    cmpwi r0, 0x1
    bne fn_80147AF4_L_80147B1C
    li r3, 0x71
    bl SoundMgr_Play
    fn_80147AF4_L_80147B1C:
    lwz r3, 0x8(r31)
    cmpwi r3, 0x14
    bge fn_80147AF4_L_80147BEC
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfd f3, lbl_806D7C20(r2)
    stw r0, 0x8(r1)
    lfs f2, lbl_806D7C40(r2)
    lfd f1, 0x8(r1)
    lfs f0, lbl_806D7C3C(r2)
    fsubs f3, f1, f3
    lfs f1, lbl_806D7C48(r2)
    fdivs f2, f3, f2
    fmuls f0, f0, f2
    fmuls f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x10(r1)
    lwz r3, 0x14(r1)
    cmpwi r3, 0xff
    ble fn_80147AF4_L_80147B74
    li r3, 0xff
    fn_80147AF4_L_80147B74:
    lfs f1, lbl_806D7C50(r2)
    li r0, -0x100
    lfs f0, lbl_806D7C4C(r2)
    rlwimi r0, r3, 0, 24, 31
    fmadds f0, f1, f2, f0
    stfs f0, 0x94(r31)
    stfs f0, 0x98(r31)
    stfs f0, 0xec(r31)
    stfs f0, 0xf0(r31)
    stfs f0, 0x144(r31)
    stfs f0, 0x148(r31)
    stfs f0, 0x19c(r31)
    stfs f0, 0x1a0(r31)
    stw r0, 0x9c(r31)
    stw r0, 0xa0(r31)
    stw r0, 0xa4(r31)
    stw r0, 0xa8(r31)
    stw r0, 0xf4(r31)
    stw r0, 0xf8(r31)
    stw r0, 0xfc(r31)
    stw r0, 0x100(r31)
    stw r0, 0x14c(r31)
    stw r0, 0x150(r31)
    stw r0, 0x154(r31)
    stw r0, 0x158(r31)
    stw r0, 0x1a4(r31)
    stw r0, 0x1a8(r31)
    stw r0, 0x1ac(r31)
    stw r0, 0x1b0(r31)
    b fn_80147AF4_L_80147CD4
    fn_80147AF4_L_80147BEC:
    cmpwi r3, 0x1e
    blt fn_80147AF4_L_80147CD4
    cmpwi r3, 0x2d
    bge fn_80147AF4_L_80147CBC
    subi r3, r3, 0x1e
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    stw r0, 0x10(r1)
    lfd f1, lbl_806D7C20(r2)
    li r0, -0x1
    stw r3, 0x14(r1)
    li r3, -0x100
    lfs f4, lbl_806D7C34(r2)
    lfd f0, 0x10(r1)
    lfs f2, lbl_806D7C38(r2)
    fsubs f5, f0, f1
    lfs f1, lbl_806D7C50(r2)
    lfs f0, lbl_806D7C4C(r2)
    lfs f3, lbl_806D7C3C(r2)
    fdivs f4, f5, f4
    fsubs f2, f2, f4
    fmadds f1, f1, f2, f0
    fmuls f0, f3, f2
    stfs f1, 0x94(r31)
    fctiwz f0, f0
    stfs f1, 0x98(r31)
    stfs f1, 0xec(r31)
    stfs f1, 0xf0(r31)
    stfs f1, 0x144(r31)
    stfs f1, 0x148(r31)
    stfs f1, 0x19c(r31)
    stfs f1, 0x1a0(r31)
    stw r0, 0x9c(r31)
    stw r0, 0xa0(r31)
    stw r0, 0xa4(r31)
    stw r0, 0xa8(r31)
    stw r0, 0xf4(r31)
    stw r0, 0xf8(r31)
    stfd f0, 0x8(r1)
    stw r0, 0xfc(r31)
    lwz r4, 0xc(r1)
    stw r0, 0x100(r31)
    rlwimi r3, r4, 0, 24, 31
    stw r3, 0x14c(r31)
    stw r3, 0x150(r31)
    stw r3, 0x154(r31)
    stw r3, 0x158(r31)
    stw r3, 0x1a4(r31)
    stw r3, 0x1a8(r31)
    stw r3, 0x1ac(r31)
    stw r3, 0x1b0(r31)
    b fn_80147AF4_L_80147CD4
    fn_80147AF4_L_80147CBC:
    cmpwi r3, 0x5a
    blt fn_80147AF4_L_80147CD4
    li r3, 0x4
    li r0, 0x0
    stw r3, 0x0(r31)
    stw r0, 0x8(r31)
    fn_80147AF4_L_80147CD4:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void fn_80147CE8(void) { /* 0x80147CE8 size:0x200 */
    nofralloc
    stwu r1, -0x20(r1)
    lwz r4, 0x8(r3)
    cmpwi r4, 0x14
    bge fn_80147CE8_L_80147DDC
    xoris r4, r4, 0x8000
    lis r0, 0x4330
    stw r4, 0xc(r1)
    lfd f3, lbl_806D7C20(r2)
    stw r0, 0x8(r1)
    lfs f2, lbl_806D7C40(r2)
    lfd f1, 0x8(r1)
    lfs f0, lbl_806D7C3C(r2)
    fsubs f3, f1, f3
    lfs f1, lbl_806D7C48(r2)
    fdivs f2, f3, f2
    fmuls f0, f0, f2
    fmuls f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x10(r1)
    lwz r4, 0x14(r1)
    cmpwi r4, 0xff
    ble fn_80147CE8_L_80147D44
    li r4, 0xff
    fn_80147CE8_L_80147D44:
    lfs f1, lbl_806D7C50(r2)
    li r0, -0x100
    lfs f0, lbl_806D7C38(r2)
    rlwimi r0, r4, 0, 24, 31
    fmadds f0, f1, f2, f0
    stfs f0, 0x1f4(r3)
    stfs f0, 0x1f8(r3)
    stfs f0, 0x24c(r3)
    stfs f0, 0x250(r3)
    stfs f0, 0x2a4(r3)
    stfs f0, 0x2a8(r3)
    stfs f0, 0x2fc(r3)
    stfs f0, 0x300(r3)
    stw r0, 0x1fc(r3)
    stw r0, 0x200(r3)
    stw r0, 0x204(r3)
    stw r0, 0x208(r3)
    stw r0, 0x254(r3)
    stw r0, 0x258(r3)
    stw r0, 0x25c(r3)
    stw r0, 0x260(r3)
    stw r0, 0x2ac(r3)
    stw r0, 0x2b0(r3)
    stw r0, 0x2b4(r3)
    stw r0, 0x2b8(r3)
    stw r0, 0x304(r3)
    stw r0, 0x308(r3)
    stw r0, 0x30c(r3)
    stw r0, 0x310(r3)
    stw r0, 0x35c(r3)
    stw r0, 0x360(r3)
    stw r0, 0x364(r3)
    stw r0, 0x368(r3)
    stw r0, 0x3b4(r3)
    stw r0, 0x3b8(r3)
    stw r0, 0x3bc(r3)
    stw r0, 0x3c0(r3)
    b fn_80147CE8_L_80147EE0
    fn_80147CE8_L_80147DDC:
    cmpwi r4, 0x1e
    blt fn_80147CE8_L_80147EE0
    cmpwi r4, 0x2d
    bge fn_80147CE8_L_80147EC8
    subi r4, r4, 0x1e
    lis r0, 0x4330
    xoris r4, r4, 0x8000
    stw r0, 0x10(r1)
    lfd f2, lbl_806D7C20(r2)
    li r0, -0x1
    stw r4, 0x14(r1)
    li r4, -0x100
    lfs f1, lbl_806D7C34(r2)
    lfd f0, 0x10(r1)
    lfs f3, lbl_806D7C38(r2)
    fsubs f2, f0, f2
    lfs f0, lbl_806D7C50(r2)
    lfs f4, lbl_806D7C3C(r2)
    fdivs f1, f2, f1
    fsubs f1, f3, f1
    fmadds f2, f0, f1, f3
    fmuls f0, f4, f1
    stfs f2, 0x1f4(r3)
    fctiwz f0, f0
    stfs f2, 0x1f8(r3)
    stfs f2, 0x24c(r3)
    stfs f2, 0x250(r3)
    stfs f2, 0x2a4(r3)
    stfs f2, 0x2a8(r3)
    stfs f2, 0x2fc(r3)
    stfs f2, 0x300(r3)
    stw r0, 0x1fc(r3)
    stw r0, 0x200(r3)
    stw r0, 0x204(r3)
    stw r0, 0x208(r3)
    stw r0, 0x254(r3)
    stw r0, 0x258(r3)
    stw r0, 0x25c(r3)
    stw r0, 0x260(r3)
    stw r0, 0x2ac(r3)
    stw r0, 0x2b0(r3)
    stfd f0, 0x8(r1)
    stw r0, 0x2b4(r3)
    lwz r5, 0xc(r1)
    stw r0, 0x2b8(r3)
    rlwimi r4, r5, 0, 24, 31
    stw r4, 0x304(r3)
    stw r4, 0x308(r3)
    stw r4, 0x30c(r3)
    stw r4, 0x310(r3)
    stw r4, 0x35c(r3)
    stw r4, 0x360(r3)
    stw r4, 0x364(r3)
    stw r4, 0x368(r3)
    stw r4, 0x3b4(r3)
    stw r4, 0x3b8(r3)
    stw r4, 0x3bc(r3)
    stw r4, 0x3c0(r3)
    b fn_80147CE8_L_80147EE0
    fn_80147CE8_L_80147EC8:
    cmpwi r4, 0x5a
    blt fn_80147CE8_L_80147EE0
    li r4, 0x3
    li r0, 0x0
    stw r4, 0x0(r3)
    stw r0, 0x8(r3)
    fn_80147CE8_L_80147EE0:
    addi r1, r1, 0x20
    blr
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
        self->vt = lbl_8048F020;
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

extern "C" asm void fn_80148810(void) { /* 0x80148810 size:0x234 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r8, lbl_8048ED10@ha
    lfs f0, lbl_806D7C2C(r2)
    stw r0, 0x24(r1)
    lis r10, lbl_80362778@ha
    stmw r27, 0xc(r1)
    mr r31, r3
    lis r3, lbl_8048ECF8@ha
    mr r29, r4
    addi r0, r3, lbl_8048ECF8@l
    mr r9, r31
    mr r11, r9
    lis r3, lbl_8048F020@ha
    li r9, 0x0
    mr r28, r6
    addi r30, r10, lbl_80362778@l
    stw r0, 0x0(r31)
    addi r0, r3, lbl_8048F020@l
    li r3, 0x20
    stw r7, 0x4(r11)
    addi r7, r8, lbl_8048ED10@l
    stw r9, 0x8(r11)
    stw r9, 0xc(r11)
    stw r7, 0x0(r11)
    stw r0, 0x0(r31)
    stb r5, 0x10(r31)
    stw r29, 0x14(r31)
    stw r9, 0x18(r31)
    stfs f0, 0x1c(r31)
    stw r28, 0x20(r31)
    bl Alloc
    mr. r27, r3
    beq fn_80148810_L_801488A4
    addi r4, r30, 0xa8
    li r5, 0x0
    bl fn_8013D800
    fn_80148810_L_801488A4:
    stw r27, 0x24(r31)
    li r3, 0x20
    bl Alloc
    mr. r27, r3
    beq fn_80148810_L_801488C4
    addi r4, r30, 0xb8
    li r5, 0x1
    bl fn_8013D800
    fn_80148810_L_801488C4:
    stw r27, 0x28(r31)
    li r3, 0x24
    bl Alloc
    mr. r27, r3
    beq fn_80148810_L_801488DC
    bl fn_80140874
    fn_80148810_L_801488DC:
    stw r27, 0x90(r31)
    li r0, 0x0
    li r3, 0xb70
    stw r0, 0x94(r31)
    bl Alloc
    mr. r27, r3
    beq fn_80148810_L_8014891C
    bl GetCoinCount
    li r4, 0x0
    li r5, 0xf
    bl Clamp_Int
    mr r4, r3
    mr r3, r27
    mr r5, r28
    mr r6, r29
    bl fn_80148A44
    fn_80148810_L_8014891C:
    stw r27, 0x98(r31)
    li r0, 0x0
    stb r0, 0x9c(r31)
    lbz r0, 0x10(r31)
    cmplwi r0, 0x1
    bne fn_80148810_L_8014895C
    lwz r29, 0x14(r31)
    li r3, 0x20
    bl Alloc
    mr. r27, r3
    beq fn_80148810_L_80148954
    mr r4, r29
    li r5, 0x0
    bl fn_80217F78
    fn_80148810_L_80148954:
    stw r27, 0x94(r31)
    b fn_80148810_L_80148980
    fn_80148810_L_8014895C:
    lwz r29, 0x14(r31)
    li r3, 0x14
    bl Alloc
    mr. r27, r3
    beq fn_80148810_L_8014897C
    mr r4, r29
    li r5, 0x0
    bl fn_802182BC
    fn_80148810_L_8014897C:
    stw r27, 0x94(r31)
    fn_80148810_L_80148980:
    lwz r3, 0x24(r31)
    lfs f1, lbl_806D7C2C(r2)
    lfs f2, lbl_806D7C38(r2)
    bl fn_8013D738
    lfs f1, lbl_806D7C8C(r2)
    lwz r3, 0x24(r31)
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    addi r28, r30, 0xc
    lwz r3, 0x24(r31)
    lfs f1, 0xc(r30)
    addi r29, r28, 0x8
    lfs f2, 0x4(r28)
    lfs f3, 0x8(r28)
    bl fn_8013D634
    lwz r3, 0x28(r31)
    lfs f1, lbl_806D7C2C(r2)
    lfs f2, lbl_806D7C38(r2)
    bl fn_8013D738
    lfs f1, lbl_806D7C8C(r2)
    lwz r3, 0x28(r31)
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    lwz r3, 0x28(r31)
    lfs f1, 0xc(r30)
    lfs f2, 0x4(r28)
    lfs f3, 0x0(r29)
    bl fn_8013D634
    lfs f0, lbl_806D7C7C(r2)
    li r0, -0x1
    lfs f1, lbl_806D7C98(r2)
    mr r3, r31
    stfs f0, 0x2c(r31)
    lfs f0, lbl_806D7C2C(r2)
    stfs f1, 0x30(r31)
    stfs f0, 0x38(r31)
    stfs f0, 0x3c(r31)
    stw r0, 0x4c(r31)
    stw r0, 0x5c(r31)
    stw r0, 0x6c(r31)
    stw r0, 0x7c(r31)
    stw r0, 0x8c(r31)
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

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
    lis r9, lbl_80362778@ha
    stw r6, 0x4(r31)
    addi r6, r7, ResCtrl_Init@l
    mr r28, r4
    addi r0, r3, dtor_80082960@l
    stw r8, 0x8(r31)
    mr r26, r5
    mr r4, r6
    mr r5, r0
    stb r8, 0xc(r31)
    addi r30, r9, lbl_80362778@l
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
                    if (x < off + lbl_80362858[i]) {
                        x = off + lbl_80362858[i];
                        self->e[i].count++;
                        self->e[i].t = lbl_806D7CE8;
                    }
                    break;
                case 3: {
                    float s;
                    self->e[i].t += 1.0f;
                    x = off + lbl_80362858[i];
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
                    x = off + lbl_80362858[i];
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
        self->vt = lbl_8048F058;
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

extern "C" asm void fn_80149E44(void) { /* 0x80149E44 size:0xA4C */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stfd f30, 0x60(r1)
    psq_st f30, 0x68(r1), 0, 0
    stfd f29, 0x50(r1)
    psq_st f29, 0x58(r1), 0, 0
    stfd f28, 0x40(r1)
    psq_st f28, 0x48(r1), 0, 0
    stfd f27, 0x30(r1)
    psq_st f27, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    stw r28, 0x20(r1)
    mr r31, r3
    lwz r0, 0x20(r3)
    cmpwi r0, 0x3
    beq fn_80149E44_L_8014A4F8
    bge fn_80149E44_L_80149EB4
    cmpwi r0, 0x1
    beq fn_80149E44_L_8014A174
    bge fn_80149E44_L_8014A3F0
    cmpwi r0, 0x0
    bge fn_80149E44_L_80149EC4
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_80149EB4:
    cmpwi r0, 0x5
    beq fn_80149E44_L_8014A720
    bge fn_80149E44_L_8014A7D8
    b fn_80149E44_L_8014A620
    fn_80149E44_L_80149EC4:
    lfs f1, lbl_806D7D58(r2)
    lfs f0, 0x1c(r31)
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    lfs f1, 0x18(r31)
    lfs f0, lbl_806D7D5C(r2)
    fcmpo cr0, f1, f0
    ble fn_80149E44_L_80149F30
    fsubs f1, f1, f0
    lfs f0, lbl_806D7D64(r2)
    lfs f2, lbl_806D7D68(r2)
    lfs f3, lbl_806D7D60(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lfs f3, lbl_806D7D60(r2)
    li r4, 0x9a4
    lfs f7, lbl_806D7D70(r2)
    li r5, 0x0
    fsubs f1, f3, f1
    lfs f0, lbl_806D7D6C(r2)
    fmr f4, f3
    lwz r3, 0x10(r31)
    fmr f5, f3
    lfs f2, lbl_806D7D74(r2)
    fmr f6, f3
    fnmsubs f1, f7, f1, f0
    bl fn_80169468
    fn_80149E44_L_80149F30:
    lfs f31, lbl_806D7D5C(r2)
    mr r28, r31
    lfs f30, lbl_806D7D78(r2)
    li r29, 0x0
    lfd f29, lbl_806D7DF8(r2)
    lis r30, 0x4330
    fn_80149E44_L_80149F48:
    xoris r0, r29, 0x8000
    stw r30, 0x10(r1)
    lfs f4, 0x18(r31)
    stw r0, 0x14(r1)
    lfd f0, 0x10(r1)
    fsubs f0, f0, f29
    fmuls f2, f30, f0
    fadds f0, f31, f2
    fcmpo cr0, f4, f0
    blt fn_80149E44_L_8014A02C
    lfs f1, lbl_806D7D7C(r2)
    lfs f0, lbl_806D7D64(r2)
    fadds f1, f1, f2
    lfs f2, lbl_806D7D68(r2)
    lfs f3, lbl_806D7D60(r2)
    fsubs f1, f4, f1
    fdivs f1, f1, f0
    bl Saturate_Double
    fmr f27, f1
    lfs f0, lbl_806D7D68(r2)
    fcmpu cr0, f0, f27
    bne fn_80149E44_L_80149FB4
    lwz r3, 0x3c(r28)
    lwz r12, 0x14(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_80149E44_L_80149FB4:
    xoris r3, r29, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfs f4, lbl_806D7D60(r2)
    stw r0, 0x10(r1)
    lfd f1, lbl_806D7DF8(r2)
    fsubs f3, f4, f27
    lfd f0, 0x10(r1)
    lfs f2, lbl_806D7D84(r2)
    fsubs f1, f0, f1
    lfs f0, lbl_806D7D80(r2)
    lfs f5, lbl_806D7D70(r2)
    lwz r3, 0x3c(r28)
    fmadds f1, f2, f1, f0
    lfs f0, lbl_806D7D88(r2)
    fnmsubs f1, f5, f3, f1
    stfs f1, 0x8(r3)
    stfs f0, 0xc(r3)
    lwz r3, 0x3c(r28)
    stfs f4, 0x10(r3)
    lwz r3, 0x3c(r28)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x3c(r28)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fn_80149E44_L_8014A02C:
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x9
    blt fn_80149E44_L_80149F48
    lfs f1, 0x18(r31)
    lfs f2, lbl_806D7D60(r2)
    lfs f0, lbl_806D7D8C(r2)
    fadds f1, f1, f2
    stfs f1, 0x18(r31)
    lfs f1, 0x1c(r31)
    fadds f1, f1, f2
    stfs f1, 0x1c(r31)
    lfs f1, 0x1c(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80149E44_L_8014A074
    lfs f0, lbl_806D7D68(r2)
    stfs f0, 0x1c(r31)
    fn_80149E44_L_8014A074:
    lfs f0, lbl_806D7D60(r2)
    lwz r3, 0x38(r31)
    stfs f0, 0x10(r3)
    lwz r3, 0x38(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x38(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lfs f1, lbl_806D7D90(r2)
    lfs f0, 0x14(r31)
    fcmpu cr0, f1, f0
    bne fn_80149E44_L_8014A0D0
    bl StrPcb_GetInstance
    li r4, 0x4
    li r5, 0x0
    bl StrPcb_SetStatusBits
    lwz r3, 0x68(r31)
    bl fn_8023CFD4
    fn_80149E44_L_8014A0D0:
    lfs f2, 0x14(r31)
    lfs f1, lbl_806D7D60(r2)
    lfs f0, lbl_806D7D94(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x14(r31)
    cror eq, gt, eq
    beq fn_80149E44_L_8014A150
    lfs f1, 0x14(r31)
    lfs f0, lbl_806D7D90(r2)
    fcmpo cr0, f1, f0
    ble fn_80149E44_L_8014A7D8
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x100
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    bne fn_80149E44_L_8014A150
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x2000
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A150:
    lwz r3, 0x68(r31)
    bl fn_8023CFC8
    lfs f0, lbl_806D7D68(r2)
    li r3, 0x1
    li r0, 0x5
    stfs f0, 0x14(r31)
    stw r3, 0xc(r31)
    stw r0, 0x20(r31)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A174:
    lfs f1, 0x14(r31)
    lfs f0, lbl_806D7D98(r2)
    lfs f3, lbl_806D7D60(r2)
    fdivs f2, f1, f0
    lfs f1, lbl_806D7D58(r2)
    lfs f0, 0x1c(r31)
    fsubs f28, f3, f2
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    lfs f1, 0x18(r31)
    lfs f0, lbl_806D7D5C(r2)
    fcmpo cr0, f1, f0
    ble fn_80149E44_L_8014A1F4
    fsubs f1, f1, f0
    lfs f0, lbl_806D7D64(r2)
    lfs f2, lbl_806D7D68(r2)
    lfs f3, lbl_806D7D60(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lfs f3, lbl_806D7D60(r2)
    fmr f6, f28
    lfs f2, lbl_806D7D70(r2)
    li r4, 0x9a4
    fsubs f1, f3, f1
    lfs f0, lbl_806D7D6C(r2)
    fmr f4, f3
    fmr f5, f3
    lwz r3, 0x10(r31)
    fnmsubs f1, f2, f1, f0
    lfs f2, lbl_806D7D74(r2)
    li r5, 0x0
    bl fn_80169468
    fn_80149E44_L_8014A1F4:
    lfs f29, lbl_806D7D5C(r2)
    mr r28, r31
    lfs f30, lbl_806D7D78(r2)
    li r29, 0x0
    lfd f31, lbl_806D7DF8(r2)
    lis r30, 0x4330
    fn_80149E44_L_8014A20C:
    xoris r0, r29, 0x8000
    stw r30, 0x10(r1)
    lfs f4, 0x18(r31)
    stw r0, 0x14(r1)
    lfd f0, 0x10(r1)
    fsubs f0, f0, f31
    fmuls f2, f30, f0
    fadds f0, f29, f2
    fcmpo cr0, f4, f0
    blt fn_80149E44_L_8014A2F0
    lfs f1, lbl_806D7D7C(r2)
    lfs f0, lbl_806D7D64(r2)
    fadds f1, f1, f2
    lfs f2, lbl_806D7D68(r2)
    lfs f3, lbl_806D7D60(r2)
    fsubs f1, f4, f1
    fdivs f1, f1, f0
    bl Saturate_Double
    fmr f27, f1
    lfs f0, lbl_806D7D68(r2)
    fcmpu cr0, f0, f27
    bne fn_80149E44_L_8014A278
    lwz r3, 0x3c(r28)
    lwz r12, 0x14(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_80149E44_L_8014A278:
    xoris r3, r29, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfs f0, lbl_806D7D60(r2)
    stw r0, 0x10(r1)
    lfd f1, lbl_806D7DF8(r2)
    fsubs f3, f0, f27
    lfd f0, 0x10(r1)
    lfs f2, lbl_806D7D84(r2)
    fsubs f1, f0, f1
    lfs f0, lbl_806D7D80(r2)
    lfs f4, lbl_806D7D70(r2)
    lwz r3, 0x3c(r28)
    fmadds f1, f2, f1, f0
    lfs f0, lbl_806D7D88(r2)
    fnmsubs f1, f4, f3, f1
    stfs f1, 0x8(r3)
    stfs f0, 0xc(r3)
    lwz r3, 0x3c(r28)
    stfs f28, 0x10(r3)
    lwz r3, 0x3c(r28)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x3c(r28)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fn_80149E44_L_8014A2F0:
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x9
    blt fn_80149E44_L_8014A20C
    lfs f1, 0x18(r31)
    lfs f2, lbl_806D7D60(r2)
    lfs f0, lbl_806D7D8C(r2)
    fadds f1, f1, f2
    stfs f1, 0x18(r31)
    lfs f1, 0x1c(r31)
    fadds f1, f1, f2
    stfs f1, 0x1c(r31)
    lfs f1, 0x1c(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80149E44_L_8014A338
    lfs f0, lbl_806D7D68(r2)
    stfs f0, 0x1c(r31)
    fn_80149E44_L_8014A338:
    lwz r3, 0x38(r31)
    stfs f28, 0x10(r3)
    lwz r3, 0x38(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x38(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D7D60(r2)
    lfs f1, lbl_806D7D68(r2)
    fsubs f0, f0, f28
    lfs f4, lbl_806D7D9C(r2)
    fmr f2, f1
    lwz r3, 0x10(r31)
    fmr f3, f1
    fmuls f4, f4, f0
    bl fn_801678FC
    lfs f2, 0x14(r31)
    lfs f1, lbl_806D7D60(r2)
    lfs f0, lbl_806D7D98(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x14(r31)
    cror eq, gt, eq
    bne fn_80149E44_L_8014A7D8
    lfs f0, lbl_806D7D68(r2)
    stfs f0, 0x14(r31)
    lbz r0, 0x29(r31)
    cmplwi r0, 0x1
    bne fn_80149E44_L_8014A3CC
    li r0, 0x2
    stw r0, 0x20(r31)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A3CC:
    lbz r0, 0x28(r31)
    cmplwi r0, 0x0
    bne fn_80149E44_L_8014A3E4
    li r0, 0x3
    stw r0, 0x20(r31)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A3E4:
    li r0, 0x5
    stw r0, 0x20(r31)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A3F0:
    lfs f1, lbl_806D7D68(r2)
    lwz r3, 0x10(r31)
    fmr f2, f1
    lfs f4, lbl_806D7D9C(r2)
    fmr f3, f1
    bl fn_801678FC
    lwz r3, 0x60(r31)
    cmplwi r3, 0x0
    bne fn_80149E44_L_8014A460
    li r3, 0x48
    bl Alloc
    mr. r28, r3
    beq fn_80149E44_L_8014A434
    bl fn_801420DC
    lis r3, lbl_8048F0C8@ha
    addi r0, r3, lbl_8048F0C8@l
    stw r0, 0x14(r28)
    fn_80149E44_L_8014A434:
    cmplwi r28, 0x0
    stw r28, 0x60(r31)
    beq fn_80149E44_L_8014A7D8
    lwz r0, 0x10(r31)
    lwz r3, 0x60(r31)
    cmpwi r0, 0x0
    blt fn_80149E44_L_8014A7D8
    cmpwi r0, 0x8
    bge fn_80149E44_L_8014A7D8
    stw r0, 0x0(r3)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A460:
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x60(r31)
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq fn_80149E44_L_8014A7D8
    cmplwi r3, 0x0
    beq fn_80149E44_L_8014A49C
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80149E44_L_8014A49C:
    li r0, 0x0
    lfs f0, lbl_806D7D68(r2)
    stw r0, 0x60(r31)
    stfs f0, 0x14(r31)
    lwz r0, 0x24(r31)
    cmpwi r0, 0x0
    blt fn_80149E44_L_8014A4E4
    cmpwi r0, 0xa
    bge fn_80149E44_L_8014A4E4
    lbz r0, 0x28(r31)
    cmplwi r0, 0x0
    bne fn_80149E44_L_8014A4D8
    li r0, 0x3
    stw r0, 0x20(r31)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A4D8:
    li r0, 0x5
    stw r0, 0x20(r31)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A4E4:
    li r3, 0x1
    li r0, 0x6
    stw r3, 0xc(r31)
    stw r0, 0x20(r31)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A4F8:
    lfs f2, 0x14(r31)
    lfs f0, lbl_806D7D60(r2)
    lfs f1, lbl_806D7D68(r2)
    fadds f0, f2, f0
    lfs f4, lbl_806D7D9C(r2)
    fmr f2, f1
    fmr f3, f1
    stfs f0, 0x14(r31)
    lwz r3, 0x10(r31)
    bl fn_801678FC
    lfs f3, 0x14(r31)
    lfs f0, lbl_806D7D5C(r2)
    lfs f1, lbl_806D7DA0(r2)
    fcmpo cr0, f3, f0
    bge fn_80149E44_L_8014A540
    lfs f0, lbl_806D7DA4(r2)
    fadds f1, f1, f0
    b fn_80149E44_L_8014A59C
    fn_80149E44_L_8014A540:
    lfs f2, lbl_806D7D64(r2)
    fcmpo cr0, f3, f2
    bge fn_80149E44_L_8014A570
    fsubs f2, f3, f0
    lfs f3, lbl_806D7DA8(r2)
    lfs f0, lbl_806D7DAC(r2)
    lfs f4, lbl_806D7DA4(r2)
    fmuls f2, f3, f2
    fdivs f0, f2, f0
    fadds f0, f4, f0
    fadds f1, f1, f0
    b fn_80149E44_L_8014A59C
    fn_80149E44_L_8014A570:
    lfs f0, lbl_806D7D98(r2)
    fcmpo cr0, f3, f0
    bge fn_80149E44_L_8014A59C
    fsubs f2, f3, f2
    lfs f3, lbl_806D7DB4(r2)
    lfs f0, lbl_806D7DB8(r2)
    lfs f4, lbl_806D7DB0(r2)
    fmuls f2, f3, f2
    fdivs f0, f2, f0
    fadds f0, f4, f0
    fadds f1, f1, f0
    fn_80149E44_L_8014A59C:
    lwz r3, 0x10(r31)
    li r4, 0x8ae
    lfs f2, lbl_806D7D8C(r2)
    li r5, 0x0
    bl fn_801698B4
    li r0, 0x0
    stw r0, 0x6c(r31)
    lwz r3, 0x24(r31)
    bl TaRecord_GetEntry_Current
    mr r30, r3
    addi r4, r31, 0x70
    bl wcscpy
    lwz r3, lbl_806D10A0(r13)
    cmplwi r3, 0x0
    bne fn_80149E44_L_8014A5DC
    li r3, 0x0
    fn_80149E44_L_8014A5DC:
    cmplwi r3, 0x0
    beq fn_80149E44_L_8014A60C
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    li r6, 0x0
    bl get_title_result
    clrlwi. r0, r3, 24
    beq fn_80149E44_L_8014A60C
    lwz r0, 0xc(r1)
    stb r0, 0xd(r30)
    lwz r0, 0x8(r1)
    stb r0, 0xe(r30)
    fn_80149E44_L_8014A60C:
    li r0, 0x4
    lfs f0, lbl_806D7D68(r2)
    stw r0, 0x20(r31)
    stfs f0, 0x14(r31)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A620:
    lfs f2, 0x14(r31)
    lfs f0, lbl_806D7D60(r2)
    lfs f1, lbl_806D7D68(r2)
    fadds f0, f2, f0
    lfs f4, lbl_806D7D9C(r2)
    fmr f2, f1
    fmr f3, f1
    stfs f0, 0x14(r31)
    lwz r3, 0x10(r31)
    bl fn_801678FC
    lfs f2, 0x14(r31)
    lfs f1, lbl_806D7DBC(r2)
    fcmpo cr0, f2, f1
    bge fn_80149E44_L_8014A66C
    fdivs f1, f2, f1
    lfs f2, lbl_806D7DC0(r2)
    lfs f0, lbl_806D7DA0(r2)
    fmadds f1, f2, f1, f0
    b fn_80149E44_L_8014A6E8
    fn_80149E44_L_8014A66C:
    lfs f0, lbl_806D7DC4(r2)
    fcmpo cr0, f2, f0
    bge fn_80149E44_L_8014A694
    fsubs f2, f2, f1
    lfs f1, lbl_806D7DD0(r2)
    lfs f3, lbl_806D7DCC(r2)
    lfs f0, lbl_806D7DC8(r2)
    fdivs f1, f2, f1
    fnmsubs f1, f3, f1, f0
    b fn_80149E44_L_8014A6E8
    fn_80149E44_L_8014A694:
    lfs f1, lbl_806D7DD4(r2)
    fcmpo cr0, f2, f1
    bge fn_80149E44_L_8014A6BC
    fsubs f2, f2, f0
    lfs f1, lbl_806D7DDC(r2)
    lfs f3, lbl_806D7DD8(r2)
    lfs f0, lbl_806D7DCC(r2)
    fmuls f1, f2, f1
    fnmsubs f1, f3, f1, f0
    b fn_80149E44_L_8014A6E8
    fn_80149E44_L_8014A6BC:
    lfs f0, lbl_806D7DE0(r2)
    fcmpo cr0, f2, f0
    bge fn_80149E44_L_8014A6E4
    fsubs f2, f2, f1
    lfs f1, lbl_806D7D58(r2)
    lfs f3, lbl_806D7DE8(r2)
    lfs f0, lbl_806D7DE4(r2)
    fdivs f1, f2, f1
    fnmsubs f1, f3, f1, f0
    b fn_80149E44_L_8014A6E8
    fn_80149E44_L_8014A6E4:
    lfs f1, lbl_806D7DEC(r2)
    fn_80149E44_L_8014A6E8:
    lwz r3, 0x10(r31)
    li r4, 0x8ae
    lfs f2, lbl_806D7D8C(r2)
    li r5, 0x0
    bl fn_801698B4
    lfs f1, 0x14(r31)
    lfs f0, lbl_806D7DE0(r2)
    fcmpo cr0, f1, f0
    ble fn_80149E44_L_8014A7D8
    li r0, 0x5
    lfs f0, lbl_806D7D68(r2)
    stw r0, 0x20(r31)
    stfs f0, 0x14(r31)
    b fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A720:
    lfs f1, lbl_806D7D68(r2)
    lfs f0, 0x14(r31)
    fcmpu cr0, f1, f0
    bne fn_80149E44_L_8014A738
    li r3, 0x8ae
    bl fn_80120A08
    fn_80149E44_L_8014A738:
    lfs f1, lbl_806D7D68(r2)
    lwz r3, 0x10(r31)
    fmr f2, f1
    lfs f4, lbl_806D7D9C(r2)
    fmr f3, f1
    bl fn_801678FC
    lfs f2, 0x14(r31)
    lfs f1, lbl_806D7D60(r2)
    lfs f0, lbl_806D7DF0(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x14(r31)
    cror eq, gt, eq
    beq fn_80149E44_L_8014A7C0
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x100
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    bne fn_80149E44_L_8014A7C0
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x2000
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_80149E44_L_8014A7D8
    fn_80149E44_L_8014A7C0:
    li r0, 0x1
    lfs f0, lbl_806D7D68(r2)
    stw r0, 0xc(r31)
    li r0, 0x6
    stfs f0, 0x14(r31)
    stw r0, 0x20(r31)
    fn_80149E44_L_8014A7D8:
    lwz r3, 0x68(r31)
    bl fn_8023CDA8
    lwz r3, 0x34(r31)
    cmplwi r3, 0x0
    beq fn_80149E44_L_8014A828
    lwz r0, 0x8(r3)
    cmpwi r0, 0x0
    ble fn_80149E44_L_8014A800
    li r0, 0x0
    b fn_80149E44_L_8014A810
    fn_80149E44_L_8014A800:
    lwz r0, 0xc(r3)
    li r4, 0x1
    cntlzw r0, r0
    rlwnm r0, r4, r0, 31, 31
    fn_80149E44_L_8014A810:
    clrlwi. r0, r0, 24
    beq fn_80149E44_L_8014A828
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_80149E44_L_8014A828:
    lwz r3, 0x60(r31)
    cmplwi r3, 0x0
    beq fn_80149E44_L_8014A844
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fn_80149E44_L_8014A844:
    bl RumbleUpdate
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    psq_l f30, 0x68(r1), 0, 0
    lfd f30, 0x60(r1)
    psq_l f29, 0x58(r1), 0, 0
    lfd f29, 0x50(r1)
    psq_l f28, 0x48(r1), 0, 0
    lfd f28, 0x40(r1)
    psq_l f27, 0x38(r1), 0, 0
    lfd f27, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r0, 0x84(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

extern "C" HudPanel *fn_8014A890(HudPanel *self, short flag) {
    if (self != 0) {
        self->vt14 = lbl_8048F0C8;
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
        self->vt = lbl_8048F090;
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
    int f60;
    int f64;
    StrBox *box;
    int f6C;
    short f70[6];
    StrHud(int layer, int id);
    virtual ~StrHud();
};

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
    char *str = lbl_803628A8;
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

extern "C" asm void fn_8014ADB4(void) { /* 0x8014ADB4 size:0x364 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stmw r24, 0x20(r1)
    mr r29, r3
    lis r3, lbl_80362D90@ha
    lbz r0, 0x4(r29)
    addi r31, r3, lbl_80362D90@l
    cmplwi r0, 0x0
    bne fn_8014ADB4_L_8014B0FC
    lwz r0, 0x24(r29)
    cmpwi r0, 0x3
    ble fn_8014ADB4_L_8014B014
    lfs f2, 0x60(r29)
    lfs f1, lbl_806D7E28(r2)
    lfs f0, lbl_806D7E2C(r2)
    fadds f1, f2, f1
    stfs f1, 0x60(r29)
    lfs f1, 0x60(r29)
    fcmpo cr0, f1, f0
    ble fn_8014ADB4_L_8014AE14
    stfs f0, 0x60(r29)
    fn_8014ADB4_L_8014AE14:
    li r30, 0x0
    li r27, 0x0
    fn_8014ADB4_L_8014AE1C:
    mr r3, r30
    bl RankSlot_GetByIndex
    mr. r28, r3
    beq fn_8014ADB4_L_8014B004
    lwz r24, 0x14(r28)
    cmpwi r24, 0x0
    blt fn_8014ADB4_L_8014B004
    cmpwi r24, 0xd
    bge fn_8014ADB4_L_8014B004
    lwz r0, 0x10(r28)
    cmpwi r0, 0x0
    blt fn_8014ADB4_L_8014B004
    cmpwi r0, 0x3
    bgt fn_8014ADB4_L_8014B004
    lwz r0, g_gameMode(r13)
    li r4, 0x2b00
    li r3, 0x1ecd
    stw r4, 0x10(r1)
    cmpwi r0, 0x0
    stw r3, 0xc(r1)
    bne fn_8014ADB4_L_8014AE90
    lwz r6, 0x10(r28)
    addi r3, r1, 0x10
    lwz r7, 0x14(r28)
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    li r8, 0x0
    bl fn_802317E0
    b fn_8014ADB4_L_8014AEA8
    fn_8014ADB4_L_8014AE90:
    lwz r6, 0x10(r28)
    addi r3, r1, 0x10
    lwz r7, 0x14(r28)
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl fn_80231644
    fn_8014ADB4_L_8014AEA8:
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8014ADB4_L_8014AFD8
    mulli r24, r24, 0x30
    addi r0, r31, 0x4b0
    lfs f3, lbl_806D6DE4(r2)
    li r3, 0x0
    lfs f4, lbl_806D6DE8(r2)
    li r5, 0x0
    add r26, r24, r27
    lfs f5, 0x60(r29)
    add r26, r0, r26
    lwz r4, 0x10(r1)
    addi r25, r26, 0x4
    lfs f1, 0x0(r26)
    lfs f2, 0x4(r26)
    bl fn_80169334
    lfs f31, lbl_806D7E30(r2)
    lwz r3, 0xc(r1)
    bl fn_80231B74
    clrlwi. r0, r3, 24
    bne fn_8014ADB4_L_8014AF04
    lfs f31, lbl_806D7E34(r2)
    fn_8014ADB4_L_8014AF04:
    lfs f0, 0x0(r25)
    li r3, 0x0
    lfs f3, lbl_806D7E38(r2)
    li r5, 0x0
    fadds f2, f31, f0
    lfs f1, 0x0(r26)
    fmr f4, f3
    lfs f5, 0x60(r29)
    lwz r4, 0xc(r1)
    bl fn_80169334
    cmpwi r30, 0x3
    bge fn_8014ADB4_L_8014AF5C
    lfs f3, lbl_806D7E2C(r2)
    addi r4, r30, 0x14db
    lfs f1, 0x0(r26)
    li r3, 0x0
    fmr f4, f3
    lfs f2, 0x0(r25)
    lfs f5, 0x60(r29)
    li r5, 0x0
    bl fn_80169334
    b fn_8014ADB4_L_8014AFAC
    fn_8014ADB4_L_8014AF5C:
    lfs f3, lbl_806D7E2C(r2)
    li r3, 0x0
    lfs f1, 0x0(r26)
    li r4, 0x14de
    fmr f4, f3
    lfs f2, 0x0(r25)
    lfs f5, 0x60(r29)
    li r5, 0x0
    bl fn_80169334
    lfs f3, lbl_806D7E2C(r2)
    addi r4, r30, 0x14dc
    lfs f2, 0x0(r25)
    li r3, 0x0
    lfs f0, lbl_806D7E3C(r2)
    fmr f4, f3
    lfs f1, 0x0(r26)
    li r5, 0x0
    fsubs f2, f2, f0
    lfs f5, 0x60(r29)
    bl fn_80169334
    fn_8014ADB4_L_8014AFAC:
    addi r0, r31, 0x720
    add r3, r24, r27
    add r3, r0, r3
    lfs f3, 0x60(r29)
    lfs f1, 0x0(r3)
    addi r4, r28, 0x2
    lfs f2, 0x4(r3)
    li r3, 0x0
    creqv 6, 6, 6
    bl fn_80167F24
    b fn_8014ADB4_L_8014B004
    fn_8014ADB4_L_8014AFD8:
    mulli r5, r24, 0x30
    addi r0, r31, 0xc00
    lfs f3, 0x60(r29)
    addi r4, r28, 0x2
    li r3, 0x0
    add r5, r5, r27
    add r5, r0, r5
    lfs f1, 0x0(r5)
    lfs f2, 0x4(r5)
    creqv 6, 6, 6
    bl fn_80167F24
    fn_8014ADB4_L_8014B004:
    addi r30, r30, 0x1
    addi r27, r27, 0x8
    cmpwi r30, 0x6
    blt fn_8014ADB4_L_8014AE1C
    fn_8014ADB4_L_8014B014:
    lfs f1, lbl_806D7E30(r2)
    li r3, 0x0
    lfs f4, 0x5c(r29)
    fmr f2, f1
    fmr f3, f1
    bl fn_801678FC
    lbz r0, 0x20(r29)
    cmplwi r0, 0x1
    bne fn_8014ADB4_L_8014B0FC
    lwz r3, 0x8(r29)
    lwz r12, 0x14(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x14(r29)
    bl fn_8014017C
    lwz r0, 0x24(r29)
    cmpwi r0, 0xb
    blt fn_8014ADB4_L_8014B078
    cmpwi r0, 0xd
    bgt fn_8014ADB4_L_8014B078
    lwz r3, 0x50(r29)
    cmplwi r3, 0x0
    beq fn_8014ADB4_L_8014B078
    bl fn_8014095C
    fn_8014ADB4_L_8014B078:
    lwz r0, 0x24(r29)
    cmpwi r0, 0x5
    blt fn_8014ADB4_L_8014B090
    cmpwi r0, 0x7
    bgt fn_8014ADB4_L_8014B090
    bl fn_8011FAB8
    fn_8014ADB4_L_8014B090:
    lwz r0, 0x24(r29)
    cmpwi r0, 0xe
    blt fn_8014ADB4_L_8014B0CC
    cmpwi r0, 0x10
    bgt fn_8014ADB4_L_8014B0CC
    lwz r3, 0x44(r29)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x44(r29)
    lwz r12, 0x14(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    fn_8014ADB4_L_8014B0CC:
    lwz r3, 0x64(r29)
    cmplwi r3, 0x0
    beq fn_8014ADB4_L_8014B0DC
    bl fn_801A0004
    fn_8014ADB4_L_8014B0DC:
    li r24, 0x0
    fn_8014ADB4_L_8014B0E0:
    mr r3, r24
    bl fn_8013D940
    addi r24, r24, 0x1
    cmpwi r24, 0x8
    blt fn_8014ADB4_L_8014B0E0
    li r3, -0x1
    bl HSD_StateInvalidate
    fn_8014ADB4_L_8014B0FC:
    psq_l f31, 0x48(r1), 0, 0
    lfd f31, 0x40(r1)
    lmw r24, 0x20(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

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


extern "C" asm void fn_8014BBE4(struct ResultPanel *self, float alpha) { /* 0x8014BBE4 size:0x39C */
    nofralloc
    stwu r1, -0x280(r1)
    mflr r0
    stw r0, 0x284(r1)
    stfd f31, 0x270(r1)
    psq_st f31, 0x278(r1), 0, 0
    stw r31, 0x26c(r1)
    stw r30, 0x268(r1)
    stw r29, 0x264(r1)
    stw r28, 0x260(r1)
    mr r30, r3
    fmr f31, f1
    lwz r28, 0x38(r3)
    mr r3, r28
    bl Item_GetDescriptorField8
    bl fn_8013BEC8
    mr r29, r3
    addi r3, r1, 0x8
    bl TexMgr_Init
    bl fn_801F8E58
    fmr f5, f31
    mr r31, r3
    lfs f1, lbl_806D7E58(r2)
    li r3, 0x0
    lfs f2, lbl_806D7E5C(r2)
    li r4, 0x14e5
    lfs f3, lbl_806D7E60(r2)
    li r5, 0x0
    lfs f4, lbl_806D7E2C(r2)
    bl fn_80169334
    fmr f3, f31
    lfs f1, lbl_806D7E64(r2)
    lfs f2, lbl_806D7E68(r2)
    li r3, 0x0
    li r4, 0x14e3
    li r5, 0x0
    bl fn_801695E0
    fmr f3, f31
    lfs f1, lbl_806D7E6C(r2)
    lfs f2, lbl_806D7E68(r2)
    li r3, 0x0
    li r4, 0x14e4
    li r5, 0x0
    bl fn_801695E0
    mr r3, r28
    li r4, 0x0
    bl Item_GetDescriptorField0
    fmr f3, f31
    mr r4, r3
    lfs f1, lbl_806D7E70(r2)
    li r3, 0x0
    lfs f2, lbl_806D7E74(r2)
    li r5, 0x0
    bl fn_801695E0
    bl isJapanese
    cmpwi r3, 0x0
    bne fn_8014BBE4_L_8014BD2C
    cmplwi r29, 0x0
    beq fn_8014BBE4_L_8014BD04
    mr r3, r28
    bl fn_8023DAA8
    lfs f0, 0xc(r29)
    mr r4, r3
    lfs f1, lbl_806D7E64(r2)
    li r3, 0x0
    fmuls f6, f0, f31
    lfs f2, lbl_806D7E78(r2)
    lfs f3, 0x0(r29)
    lfs f4, 0x4(r29)
    lfs f5, 0x8(r29)
    creqv 6, 6, 6
    bl fn_801685A4
    b fn_8014BBE4_L_8014BE2C
    fn_8014BBE4_L_8014BD04:
    mr r3, r28
    bl fn_8023DAA8
    fmr f3, f31
    mr r4, r3
    lfs f1, lbl_806D7E64(r2)
    li r3, 0x0
    lfs f2, lbl_806D7E78(r2)
    creqv 6, 6, 6
    bl fn_80168798
    b fn_8014BBE4_L_8014BE2C
    fn_8014BBE4_L_8014BD2C:
    mr r3, r28
    bl fn_8023DAA8
    mr r4, r3
    addi r3, r1, 0x8
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    cmplwi r29, 0x0
    beq fn_8014BBE4_L_8014BDC4
    lfs f4, lbl_806D7E7C(r2)
    lfs f2, 0xc(r29)
    lfs f1, 0x0(r29)
    fmuls f3, f4, f2
    lfs f0, 0x4(r29)
    lfs f2, 0x8(r29)
    fmuls f1, f4, f1
    fmuls f0, f4, f0
    fmuls f2, f4, f2
    fctiwz f1, f1
    fctiwz f0, f0
    fctiwz f2, f2
    stfd f1, 0x248(r1)
    fmuls f3, f3, f31
    lwz r0, 0x24c(r1)
    fctiwz f1, f3
    stfd f2, 0x240(r1)
    clrlwi r3, r0, 24
    stfd f0, 0x250(r1)
    lwz r4, 0x244(r1)
    lwz r0, 0x254(r1)
    stfd f1, 0x238(r1)
    clrlslwi r0, r0, 24, 16
    rlwimi r0, r3, 24, 0, 7
    clrlwi r3, r4, 24
    lwz r4, 0x23c(r1)
    rlwimi r0, r3, 8, 16, 23
    rlwimi r0, r4, 0, 24, 31
    stw r0, 0x28(r1)
    b fn_8014BBE4_L_8014BDEC
    fn_8014BBE4_L_8014BDC4:
    lfs f1, lbl_806D7E7C(r2)
    li r0, -0x100
    lfs f0, 0xc(r29)
    fmuls f0, f1, f0
    fmuls f0, f0, f31
    fctiwz f0, f0
    stfd f0, 0x250(r1)
    lwz r3, 0x254(r1)
    rlwimi r0, r3, 0, 24, 31
    stw r0, 0x28(r1)
    fn_8014BBE4_L_8014BDEC:
    li r0, 0x1
    lfs f1, lbl_806D7E64(r2)
    stw r0, 0x20(r1)
    addi r3, r1, 0x8
    lfs f2, lbl_806D7E78(r2)
    bl fn_801F93EC
    lfs f1, lbl_806D7E80(r2)
    addi r3, r1, 0x8
    fmr f2, f1
    bl fn_801F93D0
    lfs f0, lbl_806D7E84(r2)
    mr r3, r31
    addi r4, r1, 0x8
    li r5, 0x0
    stfs f0, 0x234(r1)
    bl fn_801F8A34
    fn_8014BBE4_L_8014BE2C:
    fmr f5, f31
    lfs f1, lbl_806D7E58(r2)
    lfs f2, lbl_806D7E88(r2)
    li r3, 0x0
    lfs f3, lbl_806D7E60(r2)
    li r4, 0x14e9
    lfs f4, lbl_806D7E2C(r2)
    li r5, 0x0
    bl fn_80169334
    li r3, 0x0
    bl RankSlot_GetByIndex
    lhz r0, 0x2(r3)
    addi r28, r3, 0x2
    cmplwi r0, 0x0
    beq fn_8014BBE4_L_8014BF14
    addi r3, r1, 0x8
    bl TexMgr_Init
    bl isJapanese
    cmpwi r3, 0x0
    bne fn_8014BBE4_L_8014BEA4
    lis r3, lbl_8048F0FC@ha
    mr r6, r28
    addi r7, r3, lbl_8048F0FC@l
    addi r3, r1, 0x8
    lwz r5, 0x8(r7)
    la r4, lbl_806D7E8C(r2)  /* lbl_806D7E8C */
    lwz r7, 0xc(r7)
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    b fn_8014BBE4_L_8014BEC8
    fn_8014BBE4_L_8014BEA4:
    lis r3, lbl_8048F0FC@ha
    mr r6, r28
    addi r7, r3, lbl_8048F0FC@l
    addi r3, r1, 0x8
    lwz r5, 0x0(r7)
    la r4, lbl_806D7E8C(r2)  /* lbl_806D7E8C */
    lwz r7, 0x4(r7)
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    fn_8014BBE4_L_8014BEC8:
    li r0, 0x1
    lfs f1, lbl_806D7E94(r2)
    stw r0, 0x20(r1)
    addi r3, r1, 0x8
    lfs f2, lbl_806D7E98(r2)
    bl fn_801F93EC
    lfs f0, lbl_806D7E7C(r2)
    li r0, -0x100
    mr r3, r31
    addi r4, r1, 0x8
    fmuls f0, f0, f31
    li r5, 0x0
    fctiwz f0, f0
    stfd f0, 0x250(r1)
    lwz r6, 0x254(r1)
    rlwimi r0, r6, 0, 24, 31
    stw r0, 0x28(r1)
    bl fn_801F8A34
    b fn_8014BBE4_L_8014BF50
    fn_8014BBE4_L_8014BF14:
    lwz r3, 0x14(r3)
    li r4, -0x1
    bl fn_8013C26C
    mr r31, r3
    li r3, 0x4e
    li r4, -0x1
    bl GetTextureByIdAndLang
    fmr f3, f31
    mr r4, r3
    lfs f1, lbl_806D7E94(r2)
    mr r5, r31
    lfs f2, lbl_806D7E98(r2)
    li r3, 0x0
    creqv 6, 6, 6
    bl fn_80168798
    fn_8014BBE4_L_8014BF50:
    lwz r3, 0x64(r30)
    stfs f31, 0x20(r3)
    psq_l f31, 0x278(r1), 0, 0
    lwz r0, 0x284(r1)
    lfd f31, 0x270(r1)
    lwz r31, 0x26c(r1)
    lwz r30, 0x268(r1)
    lwz r29, 0x264(r1)
    lwz r28, 0x260(r1)
    mtlr r0
    addi r1, r1, 0x280
    blr
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
        self->vt = lbl_8048F118;
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

extern "C" asm void fn_8014C53C(void) { /* 0x8014C53C size:0x938 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stfd f30, 0x60(r1)
    psq_st f30, 0x68(r1), 0, 0
    stfd f29, 0x50(r1)
    psq_st f29, 0x58(r1), 0, 0
    stfd f28, 0x40(r1)
    psq_st f28, 0x48(r1), 0, 0
    stfd f27, 0x30(r1)
    psq_st f27, 0x38(r1), 0, 0
    stmw r24, 0x10(r1)
    lis r5, lbl_803FE0C8@ha
    lis r4, lbl_8048F118@ha
    mr r31, r3
    lis r6, lbl_80362D90@ha
    addi r0, r5, lbl_803FE0C8@l
    li r3, 0x0
    stw r0, 0x0(r31)
    addi r0, r4, lbl_8048F118@l
    addi r30, r6, lbl_80362D90@l
    stb r3, 0x4(r31)
    stw r0, 0x0(r31)
    bl fn_8013DBF8
    li r3, 0x1
    bl InitRumbleController
    li r3, 0x48
    bl Alloc
    mr. r25, r3
    beq fn_8014C53C_L_8014C5C4
    li r4, 0x1
    bl fn_80142964
    fn_8014C53C_L_8014C5C4:
    stw r25, 0x8(r31)
    li r0, 0x1
    stb r0, 0x2d(r31)
    bl ServiceEnable_Get
    clrlwi. r0, r3, 24
    beq fn_8014C53C_L_8014C5EC
    bl ServiceValue_Get
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014C5F4
    fn_8014C53C_L_8014C5EC:
    li r0, 0x0
    stb r0, 0x2d(r31)
    fn_8014C53C_L_8014C5F4:
    li r25, 0x0
    fn_8014C53C_L_8014C5F8:
    mr r3, r25
    bl RankSlot_GetByIndex
    mr. r5, r3
    beq fn_8014C53C_L_8014C618
    lwz r3, 0x8(r31)
    mr r4, r25
    lwz r5, 0x14(r5)
    bl fn_801426A0
    fn_8014C53C_L_8014C618:
    addi r25, r25, 0x1
    cmpwi r25, 0x6
    blt fn_8014C53C_L_8014C5F8
    li r3, 0x0
    bl ProcessSystemTick
    li r3, 0x28
    bl Alloc
    mr. r25, r3
    beq fn_8014C53C_L_8014C640
    bl fn_8014403C
    fn_8014C53C_L_8014C640:
    stw r25, 0xc(r31)
    li r3, 0x1c
    bl Alloc
    mr. r25, r3
    beq fn_8014C53C_L_8014C658
    bl fn_80146260
    fn_8014C53C_L_8014C658:
    stw r25, 0x10(r31)
    li r3, 0x24
    bl Alloc
    mr. r25, r3
    beq fn_8014C53C_L_8014C670
    bl fn_80140874
    fn_8014C53C_L_8014C670:
    stw r25, 0x14(r31)
    li r3, 0x0
    lfs f0, lbl_806D7E30(r2)
    li r0, -0x1
    stw r3, 0x18(r31)
    stb r3, 0x20(r31)
    stb r3, 0x21(r31)
    stw r3, 0x24(r31)
    stfs f0, 0x28(r31)
    stw r3, 0x38(r31)
    stw r3, 0x3c(r31)
    stw r3, 0x68(r31)
    stw r3, 0x6c(r31)
    stb r3, 0x40(r31)
    stw r3, 0x44(r31)
    stw r0, 0x48(r31)
    stb r3, 0x4c(r31)
    stw r3, 0x50(r31)
    bl fn_80160238
    li r4, 0x0
    la r5, lbl_806CF818(r13)  /* lbl_806CF818 */
    la r6, lbl_806CF810(r13)  /* lbl_806CF810 */
    li r7, 0x0
    bl fn_80271340
    stw r3, 0x54(r31)
    li r0, 0x0
    lfs f0, lbl_806D7E30(r2)
    stb r0, 0x58(r31)
    stfs f0, 0x5c(r31)
    stfs f0, 0x60(r31)
    stw r0, 0x64(r31)
    bl has_title_changed
    stb r3, 0x70(r31)
    li r3, 0x0
    bl ProcessSystemTick
    li r3, 0x0
    bl RankSlot_GetByIndex
    mr r26, r3
    lis r3, g_playerData@ha
    lwz r0, 0x10(r26)
    addi r3, r3, g_playerData@l
    stw r0, 0x30(r31)
    lbz r0, 0x0(r26)
    stb r0, 0x34(r31)
    lwz r28, g_ccClass(r13)
    lwz r29, g_cupId(r13)
    lwz r27, g_roundIndex(r13)
    mr r4, r28
    bl fn_801D5C88
    lbz r0, 0x28(r26)
    li r26, 0x0
    cmplwi r0, 0x0
    beq fn_8014C53C_L_8014C8F0
    lwz r0, g_gameMode(r13)
    cmpwi r0, 0x1
    beq fn_8014C53C_L_8014C8F0
    bge fn_8014C53C_L_8014C760
    cmpwi r0, 0x0
    bge fn_8014C53C_L_8014C76C
    b fn_8014C53C_L_8014C8F0
    fn_8014C53C_L_8014C760:
    cmpwi r0, 0x3
    bge fn_8014C53C_L_8014C8F0
    b fn_8014C53C_L_8014C878
    fn_8014C53C_L_8014C76C:
    lbz r0, 0x34(r31)
    cmplwi r0, 0x0
    beq fn_8014C53C_L_8014C86C
    cmpwi r29, 0x1
    blt fn_8014C53C_L_8014C7F8
    cmpwi r29, 0x8
    bgt fn_8014C53C_L_8014C7F8
    cmpwi r27, 0x0
    blt fn_8014C53C_L_8014C7F8
    cmpwi r27, 0x7
    bgt fn_8014C53C_L_8014C7F8
    bl fn_80209A84
    stw r3, 0x38(r31)
    lwz r4, 0x38(r31)
    cmpwi r4, 0x0
    ble fn_8014C53C_L_8014C7B4
    cmpwi r4, 0x115
    blt fn_8014C53C_L_8014C7C0
    fn_8014C53C_L_8014C7B4:
    li r0, 0x0
    stw r0, 0x38(r31)
    b fn_8014C53C_L_8014C7E0
    fn_8014C53C_L_8014C7C0:
    lis r3, g_playerData@ha
    li r5, 0x1
    addi r3, r3, g_playerData@l
    bl fn_801D6F30
    clrlwi. r0, r3, 24
    beq fn_8014C53C_L_8014C7E0
    li r0, 0x0
    stw r0, 0x38(r31)
    fn_8014C53C_L_8014C7E0:
    lwz r3, 0x38(r31)
    cmpwi r3, 0x0
    beq fn_8014C53C_L_8014C7F0
    bl PlayerData_ApplyItemUnlockById
    fn_8014C53C_L_8014C7F0:
    li r0, 0x1
    stb r0, lbl_806D17F2(r13)
    fn_8014C53C_L_8014C7F8:
    lis r3, g_playerData@ha
    mr r4, r28
    addi r3, r3, g_playerData@l
    mr r5, r29
    li r25, 0x0
    bl fn_801D59A0
    cmpwi r27, 0x4
    li r0, 0x4
    blt fn_8014C53C_L_8014C820
    li r0, 0x9
    fn_8014C53C_L_8014C820:
    cmpw r3, r0
    blt fn_8014C53C_L_8014C82C
    li r25, 0x1
    fn_8014C53C_L_8014C82C:
    clrlwi. r0, r25, 24
    beq fn_8014C53C_L_8014C844
    li r3, 0x1
    addi r0, r29, 0x8
    stb r3, 0x40(r31)
    stw r0, 0x48(r31)
    fn_8014C53C_L_8014C844:
    clrlwi r0, r25, 24
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014C8F0
    bl fn_8024F588
    lbz r0, 0x0(r3)
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014C8F0
    li r0, 0x1
    stb r0, 0x4c(r31)
    b fn_8014C53C_L_8014C8F0
    fn_8014C53C_L_8014C86C:
    li r3, 0x1
    bl fn_801DC870
    b fn_8014C53C_L_8014C8F0
    fn_8014C53C_L_8014C878:
    lwz r0, 0x30(r31)
    cmpwi r0, 0x0
    blt fn_8014C53C_L_8014C8F0
    cmpwi r0, 0x3
    bgt fn_8014C53C_L_8014C8F0
    bl SyncSlot_GetRecv
    lwz r0, 0x4(r3)
    stw r0, 0x38(r31)
    lwz r0, 0x38(r31)
    cmpwi r0, 0x0
    ble fn_8014C53C_L_8014C8AC
    cmpwi r0, 0x115
    blt fn_8014C53C_L_8014C8B4
    fn_8014C53C_L_8014C8AC:
    li r0, 0x0
    stw r0, 0x38(r31)
    fn_8014C53C_L_8014C8B4:
    lwz r3, 0x38(r31)
    cmpwi r3, 0x0
    beq fn_8014C53C_L_8014C8D0
    lbz r0, 0x34(r31)
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014C8D0
    bl PlayerData_ApplyItemUnlockById
    fn_8014C53C_L_8014C8D0:
    lbz r0, 0x34(r31)
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014C8F0
    bl fn_8023F714
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014C8F0
    li r26, 0x1
    fn_8014C53C_L_8014C8F0:
    lbz r0, 0x40(r31)
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014C900
    bl CalcEarnedCoins
    fn_8014C53C_L_8014C900:
    clrlwi r0, r26, 24
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014C93C
    lwz r3, g_roundIndex(r13)
    lwz r26, g_cupId(r13)
    addi r27, r3, 0x1
    bl fn_8024F588
    li r0, 0x1
    stb r0, 0x2(r3)
    stw r26, 0x4(r3)
    stw r27, 0x8(r3)
    li r3, 0x2
    stb r0, lbl_806D17F0(r13)
    stb r0, lbl_806D17F2(r13)
    bl fn_801DC870
    fn_8014C53C_L_8014C93C:
    lbz r0, 0x40(r31)
    cmplwi r0, 0x0
    beq fn_8014C53C_L_8014C96C
    li r3, 0x44
    bl Alloc
    mr. r25, r3
    beq fn_8014C53C_L_8014C95C
    bl fn_8013FF6C
    fn_8014C53C_L_8014C95C:
    stw r25, 0x44(r31)
    bl fn_8024F588
    li r0, 0x1
    stb r0, 0xc(r3)
    fn_8014C53C_L_8014C96C:
    lwz r3, 0x38(r31)
    cmpwi r3, 0x0
    beq fn_8014C53C_L_8014CCDC
    lbz r0, 0x34(r31)
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014CCDC
    bl fn_8013BE98
    lwz r0, 0x38(r31)
    mr r26, r3
    cmpwi r0, 0x9b
    bne fn_8014C53C_L_8014CADC
    li r3, 0x10
    bl Alloc
    mr. r24, r3
    beq fn_8014C53C_L_8014CAA4
    li r0, 0x1
    lfs f28, lbl_806D7EF0(r2)
    stw r0, 0x0(r24)
    mr r25, r24
    lfs f27, lbl_806D7EF4(r2)
    addi r27, r30, 0xeb8
    addi r28, r30, 0xe70
    addi r29, r30, 0xe94
    li r26, 0x0
    fn_8014C53C_L_8014C9CC:
    li r3, 0x20
    bl Alloc
    mr. r30, r3
    beq fn_8014C53C_L_8014C9F4
    li r3, 0x32
    bl ItemRes_LookupByKey_Thunk
    mr r4, r3
    mr r3, r30
    li r5, 0x1
    bl fn_8013D800
    fn_8014C53C_L_8014C9F4:
    stw r30, 0x4(r25)
    lfs f1, lbl_806D7E30(r2)
    lwz r3, 0x4(r25)
    lfs f2, lbl_806D7E2C(r2)
    bl fn_8013D738
    lwz r3, 0x4(r25)
    lfs f1, lbl_806D7EE8(r2)
    lfs f2, lbl_806D7EEC(r2)
    bl fn_8013D660
    lfs f1, 0x0(r28)
    lfs f2, 0x4(r28)
    lfs f0, 0x8(r28)
    fmuls f1, f1, f28
    fmuls f2, f2, f28
    lwz r3, 0x4(r25)
    fmuls f3, f0, f28
    bl fn_8013D634
    lfs f0, 0x0(r27)
    lwz r3, 0x4(r25)
    fmuls f1, f0, f28
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    lfs f1, 0x0(r29)
    lfs f2, 0x4(r29)
    lfs f0, 0x8(r29)
    fmuls f1, f27, f1
    fmuls f2, f27, f2
    lwz r3, 0x4(r25)
    fmuls f3, f27, f0
    bl fn_8013D59C
    lfs f1, lbl_806D7EE4(r2)
    lwz r3, 0x4(r25)
    fmr f2, f1
    lfs f4, lbl_806D7E30(r2)
    fmr f3, f1
    bl fn_8013D50C
    addi r26, r26, 0x1
    addi r28, r28, 0xc
    cmpwi r26, 0x3
    addi r29, r29, 0xc
    addi r25, r25, 0x4
    addi r27, r27, 0x4
    blt fn_8014C53C_L_8014C9CC
    fn_8014C53C_L_8014CAA4:
    stw r24, 0x68(r31)
    li r26, 0x0
    lwz r25, 0x68(r31)
    fn_8014C53C_L_8014CAB0:
    lfs f1, lbl_806D7EE4(r2)
    lwz r3, 0x4(r25)
    fmr f2, f1
    lfs f4, lbl_806D7E30(r2)
    fmr f3, f1
    bl fn_8013D50C
    addi r26, r26, 0x1
    addi r25, r25, 0x4
    cmpwi r26, 0x3
    blt fn_8014C53C_L_8014CAB0
    b fn_8014C53C_L_8014CCDC
    fn_8014C53C_L_8014CADC:
    cmpwi r0, 0x9d
    bne fn_8014C53C_L_8014CC08
    li r3, 0xc
    bl Alloc
    mr. r24, r3
    beq fn_8014C53C_L_8014CBDC
    li r0, 0x1
    li r3, 0x20
    stw r0, 0x0(r24)
    bl Alloc
    mr. r25, r3
    beq fn_8014C53C_L_8014CB18
    addi r4, r30, 0xf74
    li r5, 0x1
    bl fn_8013D800
    fn_8014C53C_L_8014CB18:
    stw r25, 0x4(r24)
    li r3, 0x20
    bl Alloc
    mr. r25, r3
    beq fn_8014C53C_L_8014CB38
    addi r4, r30, 0xf88
    li r5, 0x1
    bl fn_8013D800
    fn_8014C53C_L_8014CB38:
    addi r3, r30, 0xef4
    stw r25, 0x8(r24)
    lfs f27, lbl_806D7EF0(r2)
    mr r27, r24
    lfs f28, lbl_806D7EF4(r2)
    addi r25, r30, 0xed0
    lfs f29, 0xef4(r30)
    li r26, 0x0
    lfs f30, 0x4(r3)
    lfs f31, 0x8(r3)
    fn_8014C53C_L_8014CB60:
    lwz r3, 0x4(r27)
    lfs f1, lbl_806D7E30(r2)
    lfs f2, lbl_806D7E2C(r2)
    bl fn_8013D738
    lwz r3, 0x4(r27)
    lfs f1, lbl_806D7EE8(r2)
    lfs f2, lbl_806D7EEC(r2)
    bl fn_8013D660
    lfs f1, 0x0(r25)
    lfs f2, 0x4(r25)
    lfs f0, 0x8(r25)
    fmuls f1, f1, f27
    fmuls f2, f2, f27
    lwz r3, 0x4(r27)
    fmuls f3, f0, f27
    bl fn_8013D634
    lfs f1, lbl_806D7EF0(r2)
    lwz r3, 0x4(r27)
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    fmuls f1, f28, f29
    lwz r3, 0x4(r27)
    fmuls f2, f28, f30
    fmuls f3, f28, f31
    bl fn_8013D59C
    addi r26, r26, 0x1
    addi r27, r27, 0x4
    cmpwi r26, 0x2
    addi r25, r25, 0xc
    blt fn_8014C53C_L_8014CB60
    fn_8014C53C_L_8014CBDC:
    stw r24, 0x6c(r31)
    li r26, 0x0
    lwz r25, 0x6c(r31)
    fn_8014C53C_L_8014CBE8:
    lwz r3, 0x4(r25)
    lfs f1, lbl_806D7E30(r2)
    bl fn_8013D4B0
    addi r26, r26, 0x1
    addi r25, r25, 0x4
    cmpwi r26, 0x2
    blt fn_8014C53C_L_8014CBE8
    b fn_8014C53C_L_8014CCDC
    fn_8014C53C_L_8014CC08:
    li r3, 0x20
    bl Alloc
    mr. r24, r3
    beq fn_8014C53C_L_8014CC30
    lwz r3, 0x38(r31)
    bl ItemRes_LookupByKey_Thunk
    mr r4, r3
    mr r3, r24
    li r5, 0x1
    bl fn_8013D800
    fn_8014C53C_L_8014CC30:
    stw r24, 0x3c(r31)
    lfs f1, lbl_806D7E30(r2)
    lwz r3, 0x3c(r31)
    lfs f2, lbl_806D7E2C(r2)
    bl fn_8013D738
    lwz r3, 0x3c(r31)
    lfs f1, lbl_806D7EE8(r2)
    lfs f2, lbl_806D7EEC(r2)
    bl fn_8013D660
    lfs f3, lbl_806D7EF0(r2)
    lfs f1, 0x0(r26)
    lfs f2, 0x4(r26)
    lfs f0, 0x8(r26)
    fmuls f1, f3, f1
    fmuls f2, f3, f2
    lwz r3, 0x3c(r31)
    fmuls f3, f3, f0
    bl fn_8013D634
    lfs f3, lbl_806D7EF4(r2)
    lfs f1, 0xc(r26)
    lfs f2, 0x10(r26)
    lfs f0, 0x14(r26)
    fmuls f1, f3, f1
    fmuls f2, f3, f2
    lwz r3, 0x3c(r31)
    fmuls f3, f3, f0
    bl fn_8013D59C
    lfs f1, lbl_806D7EF0(r2)
    lfs f0, 0x18(r26)
    lwz r3, 0x3c(r31)
    fmuls f1, f1, f0
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    lwz r0, 0x38(r31)
    cmpwi r0, 0x81
    bne fn_8014C53C_L_8014CCDC
    lfs f1, lbl_806D7EF8(r2)
    lwz r3, 0x3c(r31)
    fmr f2, f1
    lfs f4, lbl_806D7E30(r2)
    fmr f3, f1
    bl fn_8013D50C
    fn_8014C53C_L_8014CCDC:
    li r0, 0x0
    stw r0, 0x64(r31)
    lwz r0, 0x38(r31)
    cmpwi r0, 0x0
    beq fn_8014C53C_L_8014CD88
    lbz r0, 0x34(r31)
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014CD38
    li r3, 0x30
    bl Alloc
    mr. r24, r3
    beq fn_8014C53C_L_8014CD1C
    li r4, 0x40
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8014C53C_L_8014CD1C:
    stw r24, 0x64(r31)
    lfs f1, lbl_806D7EAC(r2)
    lwz r3, 0x64(r31)
    lfs f0, lbl_806D7EB0(r2)
    stfs f1, 0xc(r3)
    stfs f0, 0x10(r3)
    b fn_8014C53C_L_8014CD70
    fn_8014C53C_L_8014CD38:
    li r3, 0x30
    bl Alloc
    mr. r24, r3
    beq fn_8014C53C_L_8014CD58
    li r4, 0x41
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_8014C53C_L_8014CD58:
    stw r24, 0x64(r31)
    lfs f1, lbl_806D7E58(r2)
    lwz r3, 0x64(r31)
    lfs f0, lbl_806D7E5C(r2)
    stfs f1, 0xc(r3)
    stfs f0, 0x10(r3)
    fn_8014C53C_L_8014CD70:
    lfs f0, lbl_806D7E30(r2)
    li r4, 0x1
    lwz r3, 0x64(r31)
    stfs f0, 0x20(r3)
    lwz r3, 0x64(r31)
    bl fn_8019FF6C
    fn_8014C53C_L_8014CD88:
    li r3, 0x1
    bl fn_8019083C
    clrlwi. r0, r3, 24
    beq fn_8014C53C_L_8014CDA0
    li r3, 0x1
    bl fn_801909A4
    fn_8014C53C_L_8014CDA0:
    lbz r0, 0x4c(r31)
    cmplwi r0, 0x1
    bne fn_8014C53C_L_8014CDD0
    li r3, 0x284
    bl Alloc
    mr. r24, r3
    beq fn_8014C53C_L_8014CDC0
    bl fn_80140FEC
    fn_8014C53C_L_8014CDC0:
    stw r24, 0x50(r31)
    li r0, 0x0
    lwz r3, 0x50(r31)
    stw r0, 0x0(r3)
    fn_8014C53C_L_8014CDD0:
    li r3, 0x14e5
    bl PreloadResource
    lwz r0, 0x38(r31)
    cmpwi r0, 0x0
    beq fn_8014C53C_L_8014CE34
    lbz r0, 0x34(r31)
    cmplwi r0, 0x0
    beq fn_8014C53C_L_8014CE1C
    li r3, 0x14e7
    bl PreloadResource
    li r3, 0x14e8
    bl PreloadResource
    li r3, 0x14e2
    bl PreloadResource
    li r3, 0x14ea
    bl PreloadResource
    li r3, 0x14e6
    bl PreloadResource
    b fn_8014C53C_L_8014CE34
    fn_8014C53C_L_8014CE1C:
    li r3, 0x14e3
    bl PreloadResource
    li r3, 0x14e4
    bl PreloadResource
    li r3, 0x14e9
    bl PreloadResource
    fn_8014C53C_L_8014CE34:
    mr r3, r31
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    psq_l f30, 0x68(r1), 0, 0
    lfd f30, 0x60(r1)
    psq_l f29, 0x58(r1), 0, 0
    lfd f29, 0x50(r1)
    psq_l f28, 0x48(r1), 0, 0
    lfd f28, 0x40(r1)
    psq_l f27, 0x38(r1), 0, 0
    lfd f27, 0x30(r1)
    lmw r24, 0x10(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

__declspec(section ".ctors") static void *const fn_80147778_ctor_ref = (void *)fn_80147778;
