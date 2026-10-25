
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

struct StepObj {
    int state;
};

struct StepHolder {
    char pad0[0x18];
    int state;
    float t;
    char pad20[0x78];
    StepObj *step;
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
extern unsigned int lbl_806D7BA4;
extern void dtor_8013EB50();
extern unsigned int lbl_806D7C0C;
extern unsigned int lbl_806D7C10;
extern const float lbl_80362620[4];
extern float lbl_8048EFB8[4];
extern void GetTextureByIdAndLang();
void PreloadResource(int id);
extern void TexMgr_Apply();
void TexMgr_Init(void *t);
extern void TexMgr_SetTexture();
extern unsigned int g_cupId;
extern unsigned int dtor_800869D0[];
extern unsigned int lbl_80362790[];
extern const float lbl_806D7C2C;
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern unsigned int lbl_806D7C20;
extern unsigned int lbl_806D7C34;
extern unsigned int lbl_806D7C38;
extern unsigned int lbl_806D7C3C;
extern unsigned int lbl_806D7C40;
extern unsigned int lbl_806D7C44;
extern void SoundMgr_Play();
extern unsigned int lbl_806D7C48;
extern unsigned int lbl_806D7C4C;
extern unsigned int lbl_806D7C50;
extern void IsCardValid();
extern void ResCtrl_Init();
extern void fn_8011F994();
extern void fn_8011FAFC();
extern void fn_8013D4B0();
extern void fn_8013D570();
extern void fn_8013D608();
extern void fn_8013D660();
extern void fn_8014017C();
extern void fn_801F8A34();
extern void fn_801F8E58();
extern unsigned int lbl_806D7C74;
extern unsigned int lbl_806D7C78;
extern unsigned int lbl_806D7C7C;
extern unsigned int lbl_806D7C80;
extern unsigned int lbl_806D7C84;
extern unsigned int lbl_806D7C88;
extern unsigned int lbl_806D7C8C;
extern unsigned int dtor_80082960[];
extern void Cosf_LUT_Wrap();
extern void Sinf_LUT_Wrap();
extern void fn_80140344();
extern void rand();
extern unsigned int lbl_806D7C18;
extern unsigned int lbl_806D7C28;
extern unsigned int lbl_806D7C30;
extern unsigned int lbl_806D7C54;
extern unsigned int lbl_806D7C58;
extern unsigned int lbl_806D7C5C;
extern unsigned int lbl_806D7C60;
extern unsigned int lbl_806D7C64;
extern unsigned int lbl_806D7C68;
extern unsigned int lbl_806D7C6C;
extern unsigned int lbl_806D7C70;
extern unsigned int lbl_806D7C90;
extern unsigned int lbl_806D7C94;
void __destroy_arr(void *p, void *dtor, unsigned long size, unsigned long n);
extern void __unexpected();
void fn_80120A08(int id);
extern void fn_80140810();
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
extern void isJapanese();
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
extern void LUT_Sin12Bit();
extern void RankSlot_GetByIndex();
extern void fn_8013C534();
extern void fn_8013C5FC();
extern void fn_8013C674();
extern void fn_8013C6EC();
extern void fn_8013C7B0();
extern void fn_8013C91C();
extern void fn_8013CA04();
extern void fn_8013CA70();
extern void fn_8013CC24();
extern void fn_801680A0();
extern void fn_80169468();
extern void fn_801697C0();
extern void fn_801698B4();
extern void fn_80186960();
int fn_80231BD4(int a, int b, int c);
extern unsigned int lbl_806D6DE4;
extern unsigned int lbl_806D6DE8;
extern unsigned int lbl_806D7CD8;
extern unsigned int lbl_806D7CDC;
extern unsigned int lbl_806D7CE0;
extern unsigned int lbl_806D7CE4;
extern unsigned int lbl_806D7CE8;
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
extern unsigned int lbl_806D7D3C;
extern unsigned int lbl_806D7D40;
extern unsigned int lbl_806D7D44;
extern unsigned int lbl_806D7D48;
extern unsigned int lbl_806D7D4C;
extern unsigned int lbl_806D7D50;
extern unsigned int lbl_80362858[];
extern unsigned int lbl_8048F058[];
extern void fn_80141924();
extern void fn_8014393C();
struct KartVariant *GetKartSlotKartVariant(int slot);
void fn_8014196C(void);
void fn_80143DB0(void);
extern int g_gameMode;
void fn_8023CD54(void *p);
extern void RumbleUpdate();
extern void Saturate_Double();
extern void StrPcb_GetInstance();
extern void StrPcb_SetStatusBits();
extern void TaRecord_GetEntry_Current();
extern void fn_801420DC();
extern void fn_801678FC();
extern void fn_8023CDA8();
extern void fn_8023CFC8();
extern void fn_8023CFD4();
extern void get_title_result();
extern void wcscpy();
extern unsigned int lbl_806D10A0;
extern unsigned int lbl_806D7D58;
extern unsigned int lbl_806D7D5C;
extern unsigned int lbl_806D7D60;
extern unsigned int lbl_806D7D64;
extern unsigned int lbl_806D7D68;
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
extern void StrPcb_ClearStatusBits();
extern void fn_8023CFE0();
extern unsigned int lbl_8048F090[];
extern void TaRecord_GetLastInsertedRank();
extern void fn_8014403C();
extern void fn_80144308();
extern void fn_80167744();
extern void fn_80169DF0();
extern void fn_8023CCF8();
extern void fn_8023CD3C();
extern void fn_8023CEB4();
extern void fn_8023D080();
extern void fn_8024F588();
extern unsigned int g_totalRaceTime;
extern unsigned int lbl_806D7E00;
extern unsigned int lbl_806D7E04;
extern unsigned int lbl_806D7E08;
extern unsigned int lbl_806D7E0C;
extern void fn_80141E70();
extern void fn_80142010();
extern unsigned int lbl_806D7E10;
extern unsigned int lbl_806D7E14;
extern unsigned int lbl_806D7E18;
extern unsigned int lbl_806D7E1C;
extern unsigned int lbl_803628A8[];
extern void HSD_StateInvalidate();
extern void fn_8011FAB8();
extern void fn_8013D940();
extern void fn_8014095C();
extern void fn_80167F24();
extern void fn_80169334();
extern void fn_801A0004();
extern void fn_80231644();
extern void fn_802317E0();
extern void fn_80231B74();
extern unsigned int lbl_806D7E28;
extern unsigned int lbl_806D7E2C;
extern unsigned int lbl_806D7E30;
extern unsigned int lbl_806D7E34;
extern unsigned int lbl_806D7E38;
extern unsigned int lbl_806D7E3C;
extern unsigned int lbl_80362D90[];
extern void ClSound_PlayBgmStream();
extern void SetRumbleMode();
extern void Sprite_AdvanceAnim();
extern void clStream_setVolume();
extern void fn_80140ECC();
extern void fn_8014219C();
extern void fn_801699D8();
extern void fn_8019083C();
extern void fn_80192010();
extern void fn_80192688();
extern void fn_801932F8();
extern unsigned int lbl_806D7E40;
extern unsigned int lbl_806D7E44;
extern unsigned int lbl_806D7E48;
extern unsigned int lbl_806D7E4C;
extern unsigned int lbl_806D7E50;
extern unsigned int lbl_806D7E54;
extern unsigned int jumptable_8048F130[];
extern void Item_GetDescriptorField0();
extern void Item_GetDescriptorField8();
extern void fn_8013BEC8();
extern void fn_8013C26C();
extern void fn_801685A4();
extern void fn_80168798();
extern void fn_801695E0();
extern void fn_801F93D0();
extern void fn_8023DAA8();
extern unsigned int lbl_806D7E58;
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
extern void Item_GetDescriptorFieldC();
extern void fn_8013D50C();
extern void fn_8013DAC8();
extern void fn_80168B90();
extern void fn_80168D84();
extern void fn_8023D938();
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
extern void Sprite_Destroy();
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
asm void fn_80147638(void);
void fn_80147778(void);
asm void fn_801477BC(void);
void fn_801478B0(StepHolder *self);
asm void fn_80147900(struct StepObj *o);
asm void fn_80147AF4(void);
asm void fn_80147CE8(void);
asm void fn_80147EE8(void);
asm void fn_8014816C(void);
asm void fn_80148648(void);
asm void fn_80148810(void);
asm void fn_80148A44(void);
void *dtor_8014917C(void *self, short flag);
void fn_801491DC(VObj *p);
void *fn_80149214(void *t);
asm void dtor_80149244(void);
asm void dtor_80149320(void);
void fn_801493B0(CountList *self);
void fn_80149420(CdHolder *self);
asm void fn_801494A4(void);
asm void fn_80149A88(void);
asm void fn_80149B8C(void);
void fn_80149CD8(void);
void fn_80149D58(VObj *p);
void fn_80149D90(CdHolder2 *self);
asm void fn_80149E44(void);
HudPanel *fn_8014A890(HudPanel *self, short flag);
asm void fn_8014A8FC(void);
asm void fn_8014AA38(void);
asm void fn_8014AC48(void);
void fn_8014AD7C(VObj *p);
asm void fn_8014ADB4(void);
asm void fn_8014B118(void);
asm void fn_8014BBE4(void);
asm void fn_8014BF80(void);
asm void fn_8014C308(void);
asm void fn_8014C53C(void);

#pragma section R ".extab_user"



__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; unsigned int f13; void *f14; unsigned int f15; void *f16; unsigned int f17; unsigned int f18; void *f19; } extab_fn_80147638 = { 0x100A0000, 0x00000070, 0x00000030, 0x00000080, 0x00000028, 0x0000008C, 0x00000030, 0x00000098, 0x0000003C, 0x00000000, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8013EB50, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8013EB50 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_801477BC = { 0x08080000, 0x0000004C, 0x00250010, 0x00000000, 0x82000008, (void *)&dtor_800869D0 };


__declspec(section ".extab_user") static const unsigned char extab_fn_80147900[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80147AF4[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80147CE8[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_80147EE8 = { 0x284A0000, 0x0000007C, 0x00770010, 0x00000000, 0x82000008, (void *)&dtor_80082960 };

__declspec(section ".extab_user") static const unsigned char extab_fn_8014816C[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80148648[92] = {
    0x20, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0,
    0x00, 0x0E, 0x00, 0x38, 0x00, 0x00, 0x00, 0xF4,
    0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x01, 0x20,
    0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x01, 0x2C,
    0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x01, 0x58,
    0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x01, 0x64,
    0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x00,
    0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC,
    0x00, 0x00, 0x00, 0x38, 0x8D, 0x00, 0x00, 0x38,
    0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x24,
    0x00, 0x00, 0x00, 0x20, 0x8D, 0x00, 0x00, 0x20,
    0x8D, 0x00, 0x00, 0x08
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; void *f29; unsigned int f30; unsigned int f31; void *f32; unsigned int f33; void *f34; unsigned int f35; unsigned int f36; void *f37; unsigned int f38; unsigned int f39; void *f40; unsigned int f41; void *f42; unsigned int f43; unsigned int f44; void *f45; unsigned int f46; unsigned int f47; void *f48; unsigned int f49; unsigned int f50; void *f51; unsigned int f52; unsigned int f53; void *f54; unsigned int f55; unsigned int f56; void *f57; unsigned int f58; } extab_fn_80148810 = { 0x280A0000, 0x00000080, 0x00000078, 0x00000094, 0x00000070, 0x000000A0, 0x0000008C, 0x000000B4, 0x00000084, 0x000000C0, 0x000000AC, 0x000000CC, 0x000000A4, 0x000000E0, 0x000000AC, 0x000000EC, 0x000800BC, 0x00000130, 0x000000D0, 0x00000144, 0x000000C8, 0x00000158, 0x000000D0, 0x0000016C, 0x000000E0, 0x00000180, 0x001A00D0, 0x00000000, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801419C8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x00000024, (void *)&dtor_80149320, 0x8680001F, 0x00000000, (void *)&dtor_801419C8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x00000028, (void *)&dtor_80149320, 0x0100008C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x010000AC, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x00000098, (void *)&dtor_80149244, 0x010000AC, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x010000D0 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; void *f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; void *f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; void *f20; } extab_fn_80148A44 = { 0x388A0000, 0x00000090, 0x00000040, 0x000000B0, 0x0000002C, 0x000000C4, 0x018F0020, 0x00000000, 0x0780001F, 0x00000A68, (void *)&dtor_8014917C, 0x0980001F, 0x000003D8, 0x00000003, 0x00000230, (void *)&dtor_800869D0, 0x8980001F, 0x00000010, 0x0000000B, 0x00000058, (void *)&dtor_80082960 };




__declspec(section ".extab_user") static const unsigned char extab_dtor_80149244[40] = {
    0x20, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58,
    0x00, 0x12, 0x00, 0x18, 0x00, 0x00, 0x00, 0xB0,
    0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
    0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA8,
    0x00, 0x00, 0x00, 0x08, 0x8D, 0x00, 0x00, 0x08
};

__declspec(section ".extab_user") static const unsigned char extab_dtor_80149320[40] = {
    0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48,
    0x00, 0x04, 0x00, 0x18, 0x00, 0x00, 0x00, 0x68,
    0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
    0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
    0x00, 0x00, 0x00, 0x08, 0x8D, 0x00, 0x00, 0x08
};



__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_801494A4 = { 0x294A0000, 0x000000C8, 0x00000010, 0x00000000, 0x8A80001F, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const unsigned char extab_fn_80149A88[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; void *f13; unsigned int f14; unsigned int f15; void *f16; unsigned int f17; void *f18; unsigned int f19; unsigned int f20; void *f21; } extab_fn_80149B8C = { 0x180A0000, 0x00000070, 0x00000038, 0x00000084, 0x00000030, 0x00000090, 0x00000038, 0x0000009C, 0x00000044, 0x000000CC, 0x00000038, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_801419C8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_801419C8 };




__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_80149E44 = { 0x214A0000, 0x000005E4, 0x00000010, 0x00000000, 0x8A80001C, (void *)&MemoryManager_TimedFree };


__declspec(section ".extab_user") static const unsigned char extab_fn_8014A8FC[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; void *f21; unsigned int f22; unsigned int f23; void *f24; unsigned int f25; void *f26; unsigned int f27; unsigned int f28; void *f29; unsigned int f30; void *f31; unsigned int f32; unsigned int f33; void *f34; unsigned int f35; void *f36; unsigned int f37; unsigned int f38; void *f39; } extab_fn_8014AA38 = { 0x300A0000, 0x00000080, 0x00150058, 0x000000E4, 0x00000050, 0x0000011C, 0x00060058, 0x00000148, 0x00000064, 0x00000154, 0x00000058, 0x00000160, 0x00000078, 0x0000018C, 0x00000058, 0x000001AC, 0x0000008C, 0x000001B8, 0x00100058, 0x00000000, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801419C8, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801419C8, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801419C8, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801419C8 };

__declspec(section ".extab_user") static const unsigned char extab_fn_8014AC48[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const unsigned char extab_fn_8014ADB4[8] = {
    0x40, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_8014B118[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_8014BBE4 = { 0x204A0000, 0x0000004C, 0x00C80010, 0x00000000, 0x82000008, (void *)&dtor_800869D0 };

__declspec(section ".extab_user") static const unsigned char extab_fn_8014BF80[8] = {
    0x28, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_8014C308[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; void *f61; unsigned int f62; unsigned int f63; void *f64; unsigned int f65; void *f66; unsigned int f67; unsigned int f68; void *f69; unsigned int f70; void *f71; unsigned int f72; unsigned int f73; void *f74; unsigned int f75; void *f76; unsigned int f77; unsigned int f78; void *f79; unsigned int f80; void *f81; unsigned int f82; unsigned int f83; void *f84; unsigned int f85; void *f86; unsigned int f87; void *f88; unsigned int f89; unsigned int f90; void *f91; unsigned int f92; void *f93; unsigned int f94; void *f95; unsigned int f96; unsigned int f97; void *f98; unsigned int f99; void *f100; unsigned int f101; unsigned int f102; void *f103; unsigned int f104; unsigned int f105; void *f106; unsigned int f107; void *f108; unsigned int f109; unsigned int f110; void *f111; unsigned int f112; void *f113; unsigned int f114; unsigned int f115; void *f116; unsigned int f117; void *f118; unsigned int f119; unsigned int f120; void *f121; } extab_fn_8014C53C = { 0x414A0000, 0x00000068, 0x000400F8, 0x00000088, 0x000000F0, 0x00000098, 0x001800F8, 0x00000104, 0x00000104, 0x00000110, 0x000000F8, 0x0000011C, 0x00000118, 0x00000128, 0x000000F8, 0x00000134, 0x0000012C, 0x00000180, 0x00A500F8, 0x00000420, 0x00000140, 0x00000428, 0x000F00F8, 0x00000498, 0x0000015C, 0x000004A8, 0x00040154, 0x000004CC, 0x0020015C, 0x0000058C, 0x000900F8, 0x000005C8, 0x00000178, 0x000005DC, 0x00000170, 0x000005E8, 0x00000178, 0x000005FC, 0x0000018C, 0x00000634, 0x00160178, 0x000006B8, 0x000700F8, 0x000006E4, 0x00040198, 0x00000708, 0x003000F8, 0x000007E0, 0x000001AC, 0x00000804, 0x000000F8, 0x0000081C, 0x000001C0, 0x0000084C, 0x000B00F8, 0x00000884, 0x000001D4, 0x0000089C, 0x001700F8, 0x00000000, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x01000178, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8007D0D4 };

#pragma section R ".extabindex_user"



__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147638 = {
    (void *)&fn_80147638, 0x00000140, (void *)&extab_fn_80147638
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801477BC = {
    (void *)&fn_801477BC, 0x000000F4, (void *)&extab_fn_801477BC
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147900 = {
    (void *)&fn_80147900, 0x000001F4, (void *)extab_fn_80147900
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147AF4 = {
    (void *)&fn_80147AF4, 0x000001F4, (void *)extab_fn_80147AF4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147CE8 = {
    (void *)&fn_80147CE8, 0x00000200, (void *)extab_fn_80147CE8
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147EE8 = {
    (void *)&fn_80147EE8, 0x00000284, (void *)&extab_fn_80147EE8
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014816C = {
    (void *)&fn_8014816C, 0x000004DC, (void *)extab_fn_8014816C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80148648 = {
    (void *)&fn_80148648, 0x000001C8, (void *)extab_fn_80148648
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80148810 = {
    (void *)&fn_80148810, 0x00000234, (void *)&extab_fn_80148810
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80148A44 = {
    (void *)&fn_80148A44, 0x00000738, (void *)&extab_fn_80148A44
};




__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_dtor_80149244 = {
    (void *)&dtor_80149244, 0x000000DC, (void *)extab_dtor_80149244
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_dtor_80149320 = {
    (void *)&dtor_80149320, 0x00000090, (void *)extab_dtor_80149320
};



__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801494A4 = {
    (void *)&fn_801494A4, 0x000005E4, (void *)&extab_fn_801494A4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80149A88 = {
    (void *)&fn_80149A88, 0x00000104, (void *)extab_fn_80149A88
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80149B8C = {
    (void *)&fn_80149B8C, 0x0000014C, (void *)&extab_fn_80149B8C
};




__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80149E44 = {
    (void *)&fn_80149E44, 0x00000A4C, (void *)&extab_fn_80149E44
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014A8FC = {
    (void *)&fn_8014A8FC, 0x0000013C, (void *)extab_fn_8014A8FC
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014AA38 = {
    (void *)&fn_8014AA38, 0x00000210, (void *)&extab_fn_8014AA38
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014AC48 = {
    (void *)&fn_8014AC48, 0x00000134, (void *)extab_fn_8014AC48
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014ADB4 = {
    (void *)&fn_8014ADB4, 0x00000364, (void *)extab_fn_8014ADB4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014B118 = {
    (void *)&fn_8014B118, 0x00000ACC, (void *)extab_fn_8014B118
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014BBE4 = {
    (void *)&fn_8014BBE4, 0x0000039C, (void *)&extab_fn_8014BBE4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014BF80 = {
    (void *)&fn_8014BF80, 0x00000388, (void *)extab_fn_8014BF80
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014C308 = {
    (void *)&fn_8014C308, 0x00000234, (void *)extab_fn_8014C308
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014C53C = {
    (void *)&fn_8014C53C, 0x00000938, (void *)&extab_fn_8014C53C
};

}


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

extern "C" asm void fn_80147638(void) { /* 0x80147638 size:0x140 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, lbl_8048EB44@ha
    li r6, 0x0
    stw r0, 0x14(r1)
    addi r0, r5, lbl_8048EB44@l
    lfs f1, lbl_806D7B58(r2)
    stw r31, 0xc(r1)
    mr r31, r3
    lis r3, lbl_8048EFD4@ha
    lfs f0, lbl_806D7BA4(r2)
    stw r30, 0x8(r1)
    addi r5, r3, lbl_8048EFD4@l
    li r3, 0xc
    stw r0, 0x14(r31)
    li r0, 0x4b0
    stw r6, 0x0(r31)
    stb r6, 0x4(r31)
    stfs f1, 0x8(r31)
    stfs f1, 0xc(r31)
    stfs f0, 0x10(r31)
    stw r5, 0x14(r31)
    stw r6, 0x18(r31)
    stfs f1, 0x1c(r31)
    stw r4, 0x20(r31)
    stw r0, 0x74(r31)
    stw r6, 0x78(r31)
    bl Alloc
    mr. r30, r3
    beq fn_80147638_L_801476B8
    li r4, 0x0
    bl fn_80167730
    fn_80147638_L_801476B8:
    stw r30, 0x7c(r31)
    li r3, 0x1c
    bl Alloc
    mr. r30, r3
    beq fn_80147638_L_801476D0
    bl fn_80146260
    fn_80147638_L_801476D0:
    stw r30, 0x80(r31)
    lwz r0, 0x0(r31)
    lwz r3, 0x80(r31)
    cmpwi r0, 0x0
    blt fn_80147638_L_801476F0
    cmpwi r0, 0x8
    bge fn_80147638_L_801476F0
    stw r0, 0x0(r3)
    fn_80147638_L_801476F0:
    lfs f2, lbl_806D7B58(r2)
    li r3, 0x0
    lfs f1, lbl_806D7B60(r2)
    stfs f2, 0x24(r31)
    lfs f0, lbl_806D7B5C(r2)
    stfs f2, 0x28(r31)
    stfs f2, 0x2c(r31)
    stfs f2, 0x30(r31)
    lwz r0, 0x20(r31)
    cmpw r3, r0
    bne fn_80147638_L_80147724
    stfs f1, 0x44(r31)
    b fn_80147638_L_80147728
    fn_80147638_L_80147724:
    stfs f2, 0x44(r31)
    fn_80147638_L_80147728:
    stfs f0, 0x48(r31)
    li r3, 0x1
    stfs f2, 0x4c(r31)
    stfs f2, 0x50(r31)
    stfs f2, 0x54(r31)
    stfs f2, 0x58(r31)
    lwz r0, 0x20(r31)
    cmpw r3, r0
    bne fn_80147638_L_80147754
    stfs f1, 0x6c(r31)
    b fn_80147638_L_80147758
    fn_80147638_L_80147754:
    stfs f2, 0x6c(r31)
    fn_80147638_L_80147758:
    stfs f0, 0x70(r31)
    mr r3, r31
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" void fn_80147778(void) {
    lbl_8048EFB8[0] = 320.0f - lbl_80362620[0];
    lbl_8048EFB8[1] = 262.0f - lbl_80362620[1];
    lbl_8048EFB8[2] = 320.0f - lbl_80362620[2];
    lbl_8048EFB8[3] = 262.0f - lbl_80362620[3];
}

extern "C" asm void fn_801477BC(void) { /* 0x801477BC size:0xF4 */
    nofralloc
    stwu r1, -0x240(r1)
    mflr r0
    li r3, 0x16d8
    stw r0, 0x244(r1)
    stw r31, 0x23c(r1)
    bl PreloadResource
    li r3, 0x14ba
    bl PreloadResource
    li r3, 0x16d1
    bl PreloadResource
    li r3, 0x16d2
    bl PreloadResource
    addi r3, r1, 0x8
    bl TexMgr_Init
    li r0, 0x1
    li r3, 0x8a
    stw r0, 0x20(r1)
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x8
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r3, r1, 0x8
    bl TexMgr_Apply
    lwz r3, g_cupId(r13)
    subi r0, r3, 0x8
    cmpwi r0, 0x9
    beq fn_801477BC_L_8014789C
    cmpwi r0, 0x6
    beq fn_801477BC_L_8014789C
    lis r3, lbl_80362790@ha
    slwi r31, r0, 3
    addi r0, r3, lbl_80362790@l
    li r4, -0x1
    add r3, r0, r31
    lwz r3, -0x8(r3)
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x8
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r3, r1, 0x8
    bl TexMgr_Apply
    lis r3, lbl_80362790@ha
    li r4, -0x1
    addi r0, r3, lbl_80362790@l
    add r3, r0, r31
    lwz r3, -0x4(r3)
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x8
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r3, r1, 0x8
    bl TexMgr_Apply
    fn_801477BC_L_8014789C:
    lwz r0, 0x244(r1)
    lwz r31, 0x23c(r1)
    mtlr r0
    addi r1, r1, 0x240
    blr
}

extern "C" void fn_801478B0(StepHolder *self) {
    fn_80147900(self->step);
    if (self->step->state == 5) {
        self->t = lbl_806D7C2C;
        self->state = 4;
    }
}

extern "C" asm void fn_80147900(struct StepObj *o) { /* 0x80147900 size:0x1F4 */
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

extern "C" asm void fn_80147EE8(void) { /* 0x80147EE8 size:0x284 */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stmw r27, 0x6c(r1)
    mr r31, r3
    addi r3, r1, 0x8
    bl ResCtrl_Init
    lbz r5, 0x9c(r31)
    li r4, 0x2
    lfs f4, lbl_806D7C74(r2)
    li r0, 0x1
    lfs f3, lbl_806D7C78(r2)
    addi r3, r1, 0x8
    lfs f2, lbl_806D7C7C(r2)
    lfs f1, lbl_806D7C80(r2)
    lfs f0, lbl_806D7C38(r2)
    stw r5, 0x3c(r1)
    stw r5, 0x40(r1)
    stw r5, 0x44(r1)
    stw r5, 0x48(r1)
    stw r4, 0x10(r1)
    stfs f4, 0x28(r1)
    stfs f3, 0x2c(r1)
    stb r0, 0x18(r1)
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    lwz r4, 0x14(r31)
    bl fn_8011FAFC
    lwz r3, 0x14(r31)
    bl fn_8011F994
    lwz r0, 0x18(r31)
    cmpwi r0, 0x0
    bne fn_80147EE8_L_80147FDC
    lwz r4, 0x94(r31)
    lwz r3, 0x8(r4)
    cmpwi r3, 0x0
    ble fn_80147EE8_L_80147F98
    subi r0, r3, 0x1
    li r3, 0x0
    stw r0, 0x8(r4)
    b fn_80147EE8_L_80147FBC
    fn_80147EE8_L_80147F98:
    lwz r0, 0xc(r4)
    cmpwi r0, 0x1
    bne fn_80147EE8_L_80147FAC
    li r0, 0x2
    stw r0, 0xc(r4)
    fn_80147EE8_L_80147FAC:
    lwz r0, 0xc(r4)
    li r3, 0x1
    cntlzw r0, r0
    rlwnm r3, r3, r0, 31, 31
    fn_80147EE8_L_80147FBC:
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_80147EE8_L_80147FDC
    lwz r3, 0x94(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    fn_80147EE8_L_80147FDC:
    bl IsCardValid
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_80147EE8_L_80148000
    lbz r0, 0x10(r31)
    cmplwi r0, 0x1
    bne fn_80147EE8_L_80148000
    lwz r3, 0x90(r31)
    bl fn_8014017C
    fn_80147EE8_L_80148000:
    lwz r28, 0x98(r31)
    bl fn_801F8E58
    lwz r29, 0x4(r28)
    mr r30, r3
    addi r3, r28, 0xa68
    mr r4, r29
    bl fn_8011FAFC
    mr r4, r29
    addi r3, r28, 0xac0
    bl fn_8011FAFC
    mr r4, r29
    addi r3, r28, 0xb18
    bl fn_8011FAFC
    li r29, 0x0
    mr r27, r28
    fn_80147EE8_L_8014803C:
    lwz r5, 0x4(r28)
    mr r3, r30
    addi r4, r27, 0x3d8
    bl fn_801F8A34
    addi r29, r29, 0x1
    addi r27, r27, 0x230
    cmpwi r29, 0x3
    blt fn_80147EE8_L_8014803C
    li r29, 0x0
    mr r27, r28
    fn_80147EE8_L_80148064:
    lwz r4, 0x4(r28)
    addi r3, r27, 0x10
    bl fn_8011FAFC
    addi r29, r29, 0x1
    addi r27, r27, 0x58
    cmpwi r29, 0xb
    blt fn_80147EE8_L_80148064
    lwz r3, 0x24(r31)
    lfs f1, 0x2c(r31)
    lfs f2, 0x30(r31)
    bl fn_8013D660
    lfs f1, lbl_806D7C84(r2)
    lfs f0, 0x38(r31)
    lwz r3, 0x24(r31)
    fmuls f1, f1, f0
    bl fn_8013D570
    lwz r3, 0x24(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r28, 0x0
    mr r27, r31
    fn_80147EE8_L_801480C0:
    lwz r0, 0x4c(r27)
    cmpwi r0, 0x0
    blt fn_80147EE8_L_80148140
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0x64(r1)
    lfd f2, lbl_806D7C20(r2)
    stw r0, 0x60(r1)
    lfs f0, lbl_806D7C88(r2)
    lfd f1, 0x60(r1)
    lfs f4, lbl_806D7C38(r2)
    fsubs f3, f1, f2
    lwz r3, 0x28(r31)
    lfs f1, 0x40(r27)
    lfs f2, 0x44(r27)
    fdivs f0, f3, f0
    fsubs f31, f4, f0
    bl fn_8013D660
    fmr f1, f31
    lwz r3, 0x28(r31)
    bl fn_8013D4B0
    lfs f0, lbl_806D7C8C(r2)
    lwz r3, 0x28(r31)
    fmuls f1, f0, f31
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    lwz r3, 0x28(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_80147EE8_L_80148140:
    addi r28, r28, 0x1
    addi r27, r27, 0x10
    cmpwi r28, 0x5
    blt fn_80147EE8_L_801480C0
    psq_l f31, 0x88(r1), 0, 0
    lfd f31, 0x80(r1)
    lmw r27, 0x6c(r1)
    lwz r0, 0x94(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

extern "C" asm void fn_8014816C(void) { /* 0x8014816C size:0x4DC */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r31, r3
    lwz r0, 0x18(r3)
    cmpwi r0, 0x3
    beq fn_8014816C_L_80148260
    bge fn_8014816C_L_801481B4
    cmpwi r0, 0x1
    beq fn_8014816C_L_80148288
    bge fn_8014816C_L_801484A4
    cmpwi r0, 0x0
    bge fn_8014816C_L_801481C4
    b fn_8014816C_L_801484E0
    fn_8014816C_L_801481B4:
    cmpwi r0, 0x5
    beq fn_8014816C_L_801484D4
    bge fn_8014816C_L_801484E0
    b fn_8014816C_L_801484AC
    fn_8014816C_L_801481C4:
    lwz r3, 0x94(r31)
    lwz r0, 0x8(r3)
    cmpwi r0, 0x0
    ble fn_8014816C_L_801481DC
    li r0, 0x0
    b fn_8014816C_L_801481EC
    fn_8014816C_L_801481DC:
    lwz r0, 0xc(r3)
    li r4, 0x1
    cntlzw r0, r0
    rlwnm r0, r4, r0, 31, 31
    fn_8014816C_L_801481EC:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne fn_8014816C_L_80148208
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_8014816C_L_80148208:
    lwz r3, 0x94(r31)
    lwz r0, 0xc(r3)
    cmpwi r0, 0x2
    blt fn_8014816C_L_801484E0
    lfs f0, lbl_806D7C2C(r2)
    li r0, 0x1
    stfs f0, 0x1c(r31)
    stw r0, 0x18(r31)
    lwz r0, g_cupId(r13)
    cmpwi r0, 0xd
    bne fn_8014816C_L_80148248
    lbz r0, 0x10(r31)
    cmplwi r0, 0x1
    bne fn_8014816C_L_80148248
    li r0, 0x3
    stw r0, 0x18(r31)
    fn_8014816C_L_80148248:
    bl IsCardValid
    clrlwi. r0, r3, 24
    bne fn_8014816C_L_801484E0
    li r0, 0x4
    stw r0, 0x18(r31)
    b fn_8014816C_L_801484E0
    fn_8014816C_L_80148260:
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D7C30(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014816C_L_801484E0
    li r0, 0x1
    lfs f0, lbl_806D7C2C(r2)
    stw r0, 0x18(r31)
    stfs f0, 0x1c(r31)
    b fn_8014816C_L_801484E0
    fn_8014816C_L_80148288:
    lfs f2, 0x1c(r31)
    lfs f0, lbl_806D7C54(r2)
    fctiwz f1, f2
    fcmpo cr0, f2, f0
    stfd f1, 0x8(r1)
    lwz r30, 0xc(r1)
    bge fn_8014816C_L_8014838C
    fdivs f0, f2, f0
    lfs f1, lbl_806D7C18(r2)
    fmuls f1, f1, f0
    bl Sinf_LUT_Wrap
    lfs f3, lbl_806D7C5C(r2)
    clrlwi. r0, r30, 30
    lfs f2, lbl_806D7C58(r2)
    lfs f0, lbl_806D7C60(r2)
    fmadds f1, f3, f1, f2
    stfs f1, 0x30(r31)
    stfs f0, 0x3c(r31)
    bne fn_8014816C_L_801484E0
    li r0, 0x5
    mr r3, r31
    li r30, 0x0
    mtctr r0
    fn_8014816C_L_801482E4:
    lwz r0, 0x4c(r3)
    cmpwi r0, 0x0
    bge fn_8014816C_L_8014837C
    bl rand
    lis r4, 0xb60b
    lis r0, 0x4330
    addi r4, r4, 0x60b7
    stw r0, 0x8(r1)
    mulhw r0, r4, r3
    lfd f1, lbl_806D7C20(r2)
    add r0, r0, r3
    srawi r0, r0, 8
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0x168
    subf r0, r0, r3
    xoris r0, r0, 0x8000
    stw r0, 0xc(r1)
    lfd f0, 0x8(r1)
    fsubs f31, f0, f1
    fmr f1, f31
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7C18(r2)
    slwi r30, r30, 4
    lfs f0, 0x2c(r31)
    add r3, r31, r30
    fmadds f0, f2, f1, f0
    fmr f1, f31
    stfs f0, 0x40(r3)
    bl Sinf_LUT_Wrap
    lfs f2, lbl_806D7C18(r2)
    add r3, r31, r30
    lfs f0, 0x30(r31)
    li r0, 0x0
    fmadds f0, f2, f1, f0
    stfs f0, 0x44(r3)
    stw r0, 0x4c(r3)
    b fn_8014816C_L_801484E0
    fn_8014816C_L_8014837C:
    addi r3, r3, 0x10
    addi r30, r30, 0x1
    bdnz fn_8014816C_L_801482E4
    b fn_8014816C_L_801484E0
    fn_8014816C_L_8014838C:
    lfs f0, lbl_806D7C64(r2)
    fcmpo cr0, f2, f0
    bge fn_8014816C_L_80148454
    clrlwi. r0, r30, 30
    bne fn_8014816C_L_801484E0
    li r0, 0x5
    li r30, 0x0
    mtctr r0
    fn_8014816C_L_801483AC:
    lwz r0, 0x4c(r3)
    cmpwi r0, 0x0
    bge fn_8014816C_L_80148444
    bl rand
    lis r4, 0xb60b
    lis r0, 0x4330
    addi r4, r4, 0x60b7
    stw r0, 0x8(r1)
    mulhw r0, r4, r3
    lfd f1, lbl_806D7C20(r2)
    add r0, r0, r3
    srawi r0, r0, 8
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0x168
    subf r0, r0, r3
    xoris r0, r0, 0x8000
    stw r0, 0xc(r1)
    lfd f0, 0x8(r1)
    fsubs f31, f0, f1
    fmr f1, f31
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7C18(r2)
    slwi r30, r30, 4
    lfs f0, 0x2c(r31)
    add r3, r31, r30
    fmadds f0, f2, f1, f0
    fmr f1, f31
    stfs f0, 0x40(r3)
    bl Sinf_LUT_Wrap
    lfs f2, lbl_806D7C18(r2)
    add r3, r31, r30
    lfs f0, 0x30(r31)
    li r0, 0x0
    fmadds f0, f2, f1, f0
    stfs f0, 0x44(r3)
    stw r0, 0x4c(r3)
    b fn_8014816C_L_801484E0
    fn_8014816C_L_80148444:
    addi r3, r3, 0x10
    addi r30, r30, 0x1
    bdnz fn_8014816C_L_801483AC
    b fn_8014816C_L_801484E0
    fn_8014816C_L_80148454:
    lfs f0, lbl_806D7C68(r2)
    fcmpo cr0, f2, f0
    bge fn_8014816C_L_80148474
    lfs f1, 0x3c(r31)
    lfs f0, lbl_806D7C6C(r2)
    fsubs f0, f1, f0
    stfs f0, 0x3c(r31)
    b fn_8014816C_L_801484E0
    fn_8014816C_L_80148474:
    lfs f0, lbl_806D7C70(r2)
    fcmpo cr0, f2, f0
    bge fn_8014816C_L_80148490
    lbz r3, 0x9c(r31)
    addi r0, r3, 0x3
    stb r0, 0x9c(r31)
    b fn_8014816C_L_801484E0
    fn_8014816C_L_80148490:
    lfs f0, lbl_806D7C2C(r2)
    li r0, 0x2
    stfs f0, 0x1c(r31)
    stw r0, 0x18(r31)
    b fn_8014816C_L_801484E0
    fn_8014816C_L_801484A4:
    bl fn_801478B0
    b fn_8014816C_L_801484E0
    fn_8014816C_L_801484AC:
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D7C28(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014816C_L_801484E0
    lfs f0, lbl_806D7C2C(r2)
    li r0, 0x5
    stfs f0, 0x1c(r31)
    stw r0, 0x18(r31)
    b fn_8014816C_L_801484E0
    fn_8014816C_L_801484D4:
    li r0, 0x1
    stw r0, 0xc(r31)
    b fn_8014816C_L_80148628
    fn_8014816C_L_801484E0:
    lfs f2, 0x38(r31)
    lfs f1, 0x3c(r31)
    lfs f0, lbl_806D7C90(r2)
    fadds f1, f2, f1
    stfs f1, 0x38(r31)
    lfs f1, 0x38(r31)
    fcmpo cr0, f1, f0
    ble fn_8014816C_L_80148508
    fsubs f0, f1, f0
    stfs f0, 0x38(r31)
    fn_8014816C_L_80148508:
    lwz r3, 0x4c(r31)
    li r0, -0x1
    lfs f1, lbl_806D7C94(r2)
    cmpwi r3, 0x0
    blt fn_8014816C_L_80148540
    lfs f0, 0x44(r31)
    fadds f0, f0, f1
    stfs f0, 0x44(r31)
    lwz r3, 0x4c(r31)
    addi r3, r3, 0x1
    cmpwi r3, 0xa
    stw r3, 0x4c(r31)
    ble fn_8014816C_L_80148540
    stw r0, 0x4c(r31)
    fn_8014816C_L_80148540:
    lwz r3, 0x5c(r31)
    cmpwi r3, 0x0
    blt fn_8014816C_L_80148570
    lfs f0, 0x54(r31)
    fadds f0, f0, f1
    stfs f0, 0x54(r31)
    lwz r3, 0x5c(r31)
    addi r3, r3, 0x1
    cmpwi r3, 0xa
    stw r3, 0x5c(r31)
    ble fn_8014816C_L_80148570
    stw r0, 0x5c(r31)
    fn_8014816C_L_80148570:
    addi r4, r31, 0x20
    lwz r3, 0x6c(r31)
    cmpwi r3, 0x0
    blt fn_8014816C_L_801485A4
    lfs f0, 0x44(r4)
    fadds f0, f0, f1
    stfs f0, 0x44(r4)
    lwz r3, 0x4c(r4)
    addi r3, r3, 0x1
    cmpwi r3, 0xa
    stw r3, 0x4c(r4)
    ble fn_8014816C_L_801485A4
    stw r0, 0x4c(r4)
    fn_8014816C_L_801485A4:
    lwz r3, 0x5c(r4)
    cmpwi r3, 0x0
    blt fn_8014816C_L_801485D4
    lfs f0, 0x54(r4)
    fadds f0, f0, f1
    stfs f0, 0x54(r4)
    lwz r3, 0x5c(r4)
    addi r3, r3, 0x1
    cmpwi r3, 0xa
    stw r3, 0x5c(r4)
    ble fn_8014816C_L_801485D4
    stw r0, 0x5c(r4)
    fn_8014816C_L_801485D4:
    lwz r3, 0x6c(r4)
    cmpwi r3, 0x0
    blt fn_8014816C_L_80148604
    lfs f0, 0x64(r4)
    fadds f0, f0, f1
    stfs f0, 0x64(r4)
    lwz r3, 0x6c(r4)
    addi r3, r3, 0x1
    cmpwi r3, 0xa
    stw r3, 0x6c(r4)
    ble fn_8014816C_L_80148604
    stw r0, 0x6c(r4)
    fn_8014816C_L_80148604:
    lbz r0, 0x10(r31)
    cmplwi r0, 0x1
    bne fn_8014816C_L_80148618
    lwz r3, 0x90(r31)
    bl fn_80140344
    fn_8014816C_L_80148618:
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D7C38(r2)
    fadds f0, f1, f0
    stfs f0, 0x1c(r31)
    fn_8014816C_L_80148628:
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void fn_80148648(void) { /* 0x80148648 size:0x1C8 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stw r31, 0x5c(r1)
    mr r31, r1
    stw r30, 0x58(r1)
    mr r30, r4
    stw r29, 0x54(r1)
    mr. r29, r3
    stw r28, 0x50(r1)
    beq fn_80148648_L_801487E4
    lis r3, lbl_8048F020@ha
    li r4, 0x1
    addi r0, r3, lbl_8048F020@l
    stw r0, 0x0(r29)
    lwz r3, 0x90(r29)
    bl fn_80140810
    lwz r3, 0x94(r29)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    bl fn_801F8E54
    li r3, 0x16d8
    bl fn_80120A08
    li r3, 0x14ba
    bl fn_80120A08
    li r3, 0x16d1
    bl fn_80120A08
    li r3, 0x16d2
    bl fn_80120A08
    addic. r0, r29, 0x98
    beq fn_80148648_L_80148740
    lwz r28, 0x98(r29)
    cmplwi r28, 0x0
    beq fn_80148648_L_80148740
    addic. r0, r28, 0xa68
    beq fn_80148648_L_801486F8
    lis r4, dtor_80082960@ha
    addi r3, r28, 0xa68
    addi r4, r4, dtor_80082960@l
    li r5, 0x58
    li r6, 0x3
    bl __destroy_arr
    fn_80148648_L_801486F8:
    lis r4, dtor_800869D0@ha
    addi r3, r28, 0x3d8
    addi r4, r4, dtor_800869D0@l
    li r5, 0x230
    li r6, 0x3
    bl __destroy_arr
    lis r4, dtor_80082960@ha
    addi r3, r28, 0x10
    addi r4, r4, dtor_80082960@l
    li r5, 0x58
    li r6, 0xb
    bl __destroy_arr
    mr r3, r28
    bl MemoryManager_TimedFree
    b fn_80148648_L_80148740
    addi r3, r31, 0x38
    bl __unexpected
    fn_80148648_L_8014873C:
    b fn_80148648_L_8014873C
    fn_80148648_L_80148740:
    addic. r0, r29, 0x28
    beq fn_80148648_L_80148778
    lwz r3, 0x28(r29)
    cmplwi r3, 0x0
    beq fn_80148648_L_80148778
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    b fn_80148648_L_80148778
    addi r3, r31, 0x20
    bl __unexpected
    fn_80148648_L_80148774:
    b fn_80148648_L_80148774
    fn_80148648_L_80148778:
    addic. r0, r29, 0x24
    beq fn_80148648_L_801487B0
    lwz r3, 0x24(r29)
    cmplwi r3, 0x0
    beq fn_80148648_L_801487B0
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    b fn_80148648_L_801487B0
    addi r3, r31, 0x8
    bl __unexpected
    fn_80148648_L_801487AC:
    b fn_80148648_L_801487AC
    fn_80148648_L_801487B0:
    cmplwi r29, 0x0
    beq fn_80148648_L_801487D4
    lis r3, lbl_8048ED10@ha
    addi r0, r3, lbl_8048ED10@l
    stw r0, 0x0(r29)
    beq fn_80148648_L_801487D4
    lis r3, lbl_8048ECF8@ha
    addi r0, r3, lbl_8048ECF8@l
    stw r0, 0x0(r29)
    fn_80148648_L_801487D4:
    extsh. r0, r30
    ble fn_80148648_L_801487E4
    mr r3, r29
    bl MemoryManager_TimedFree
    fn_80148648_L_801487E4:
    mr r10, r31
    lwz r31, 0x5c(r31)
    mr r3, r29
    lwz r30, 0x58(r10)
    lwz r29, 0x54(r10)
    lwz r28, 0x50(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
}

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

extern "C" asm void dtor_80149244(void) { /* 0x80149244 size:0xDC */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r1
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    mr r29, r4
    stw r28, 0x20(r1)
    mr. r28, r3
    beq dtor_80149244_L_801492E4
    lwz r30, 0x0(r28)
    cmplwi r30, 0x0
    beq dtor_80149244_L_801492D4
    addic. r0, r30, 0xa68
    beq dtor_80149244_L_8014929C
    lis r4, dtor_80082960@ha
    addi r3, r30, 0xa68
    addi r4, r4, dtor_80082960@l
    li r5, 0x58
    li r6, 0x3
    bl __destroy_arr
    dtor_80149244_L_8014929C:
    lis r4, dtor_800869D0@ha
    addi r3, r30, 0x3d8
    addi r4, r4, dtor_800869D0@l
    li r5, 0x230
    li r6, 0x3
    bl __destroy_arr
    lis r4, dtor_80082960@ha
    addi r3, r30, 0x10
    addi r4, r4, dtor_80082960@l
    li r5, 0x58
    li r6, 0xb
    bl __destroy_arr
    mr r3, r30
    bl MemoryManager_TimedFree
    dtor_80149244_L_801492D4:
    extsh. r0, r29
    ble dtor_80149244_L_801492E4
    mr r3, r28
    bl MemoryManager_TimedFree
    dtor_80149244_L_801492E4:
    mr r3, r28
    b dtor_80149244_L_801492F8
    addi r3, r31, 0x8
    bl __unexpected
    dtor_80149244_L_801492F4:
    b dtor_80149244_L_801492F4
    dtor_80149244_L_801492F8:
    mr r10, r31
    lwz r31, 0x2c(r31)
    lwz r30, 0x28(r10)
    lwz r29, 0x24(r10)
    lwz r28, 0x20(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
}

extern "C" asm void dtor_80149320(void) { /* 0x80149320 size:0x90 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r1
    stw r30, 0x28(r1)
    mr r30, r4
    stw r29, 0x24(r1)
    mr. r29, r3
    beq dtor_80149320_L_80149378
    lwz r3, 0x0(r29)
    cmplwi r3, 0x0
    beq dtor_80149320_L_80149368
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    dtor_80149320_L_80149368:
    extsh. r0, r30
    ble dtor_80149320_L_80149378
    mr r3, r29
    bl MemoryManager_TimedFree
    dtor_80149320_L_80149378:
    mr r3, r29
    b dtor_80149320_L_8014938C
    addi r3, r31, 0x8
    bl __unexpected
    dtor_80149320_L_80149388:
    b dtor_80149320_L_80149388
    dtor_80149320_L_8014938C:
    mr r10, r31
    lwz r31, 0x2c(r31)
    lwz r30, 0x28(r10)
    lwz r29, 0x24(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
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

extern "C" asm void fn_801494A4(void) { /* 0x801494A4 size:0x5E4 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 0x68(r1), 0, 0
    stfd f30, 0x50(r1)
    psq_st f30, 0x58(r1), 0, 0
    stfd f29, 0x40(r1)
    psq_st f29, 0x48(r1), 0, 0
    stfd f28, 0x30(r1)
    psq_st f28, 0x38(r1), 0, 0
    stfd f27, 0x20(r1)
    psq_st f27, 0x28(r1), 0, 0
    stmw r27, 0xc(r1)
    mr r28, r3
    lwz r3, 0x1c(r3)
    cmplwi r3, 0x0
    beq fn_801494A4_L_80149510
    lwz r0, 0xc(r3)
    cmpwi r0, 0x2
    blt fn_801494A4_L_80149510
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r0, 0x0
    stw r0, 0x1c(r28)
    fn_801494A4_L_80149510:
    lbz r0, 0x18(r28)
    cmplwi r0, 0x0
    beq fn_801494A4_L_801499CC
    li r30, 0x0
    mr r29, r28
    fn_801494A4_L_80149524:
    mr r3, r30
    bl RankSlot_GetByIndex
    mr r27, r3
    lwz r0, 0x14(r3)
    cmpwi r0, 0x0
    blt fn_801494A4_L_801495DC
    lwz r0, 0x2c(r29)
    cmpwi r0, 0x0
    bne fn_801494A4_L_801495DC
    li r0, 0x1
    li r3, 0x90
    stw r0, 0x2c(r29)
    bl Alloc
    mr. r31, r3
    beq fn_801494A4_L_8014956C
    lwz r4, 0x14(r27)
    li r5, 0x1
    bl fn_8013CC24
    fn_801494A4_L_8014956C:
    stw r31, 0x34(r29)
    lbz r0, 0x0(r27)
    cmplwi r0, 0x0
    beq fn_801494A4_L_801495B0
    lfs f1, lbl_806D7CD8(r2)
    lwz r3, 0x34(r29)
    fmr f2, f1
    fmr f3, f1
    bl fn_8013C6EC
    lfs f1, lbl_806D7CDC(r2)
    lwz r3, 0x34(r29)
    fmr f2, f1
    fmr f3, f1
    fmr f4, f1
    bl fn_8013C534
    stw r30, 0x74(r28)
    b fn_801494A4_L_801495DC
    fn_801494A4_L_801495B0:
    lfs f1, lbl_806D7CE0(r2)
    lwz r3, 0x34(r29)
    fmr f2, f1
    fmr f3, f1
    bl fn_8013C6EC
    lfs f1, lbl_806D7CDC(r2)
    lwz r3, 0x34(r29)
    fmr f2, f1
    fmr f3, f1
    fmr f4, f1
    bl fn_8013C534
    fn_801494A4_L_801495DC:
    addi r30, r30, 0x1
    addi r29, r29, 0xc
    cmpwi r30, 0x6
    blt fn_801494A4_L_80149524
    lfs f1, 0x14(r28)
    lfs f0, lbl_806D7CE4(r2)
    fcmpo cr0, f1, f0
    ble fn_801494A4_L_801499CC
    lis r3, lbl_80362858@ha
    mr r31, r28
    addi r30, r3, lbl_80362858@l
    li r29, 0x0
    fn_801494A4_L_8014960C:
    lwz r0, 0x2c(r31)
    cmpwi r0, 0x0
    beq fn_801494A4_L_801499B8
    mr r3, r29
    bl RankSlot_GetByIndex
    lwz r0, 0x74(r28)
    mr r27, r3
    lfs f27, lbl_806D7CE8(r2)
    cmpw r29, r0
    bge fn_801494A4_L_80149638
    lfs f27, lbl_806D7CEC(r2)
    fn_801494A4_L_80149638:
    cmpw r29, r0
    ble fn_801494A4_L_80149644
    lfs f27, lbl_806D7CF0(r2)
    fn_801494A4_L_80149644:
    lwz r3, 0x2c(r31)
    cmpwi r3, 0x3
    beq fn_801494A4_L_8014974C
    bge fn_801494A4_L_80149664
    cmpwi r3, 0x1
    beq fn_801494A4_L_80149670
    bge fn_801494A4_L_801496E8
    b fn_801494A4_L_80149988
    fn_801494A4_L_80149664:
    cmpwi r3, 0x5
    bge fn_801494A4_L_80149988
    b fn_801494A4_L_80149840
    fn_801494A4_L_80149670:
    cmpwi r29, 0x0
    bne fn_801494A4_L_8014968C
    addi r0, r3, 0x1
    lfs f0, lbl_806D7CE8(r2)
    stw r0, 0x2c(r31)
    stfs f0, 0x30(r31)
    b fn_801494A4_L_801496DC
    fn_801494A4_L_8014968C:
    lwz r0, 0x20(r31)
    cmpwi r0, 0x2
    bne fn_801494A4_L_801496C8
    lfs f3, lbl_806D7CF8(r2)
    lfs f2, 0x24(r31)
    lfs f1, lbl_806D7CF4(r2)
    lfs f0, lbl_806D7CFC(r2)
    fmadds f1, f3, f2, f1
    fcmpo cr0, f1, f0
    bge fn_801494A4_L_801496DC
    addi r0, r3, 0x1
    lfs f0, lbl_806D7CE8(r2)
    stw r0, 0x2c(r31)
    stfs f0, 0x30(r31)
    b fn_801494A4_L_801496DC
    fn_801494A4_L_801496C8:
    ble fn_801494A4_L_801496DC
    addi r0, r3, 0x1
    lfs f0, lbl_806D7CE8(r2)
    stw r0, 0x2c(r31)
    stfs f0, 0x30(r31)
    fn_801494A4_L_801496DC:
    lfs f31, lbl_806D7CF4(r2)
    lfs f30, lbl_806D7D00(r2)
    b fn_801494A4_L_80149988
    fn_801494A4_L_801496E8:
    lfs f1, 0x30(r31)
    lfs f0, lbl_806D7CDC(r2)
    lfs f2, lbl_806D7CF8(r2)
    fadds f3, f1, f0
    lfs f1, lbl_806D7CF4(r2)
    lfs f0, lbl_806D7D04(r2)
    stfs f3, 0x30(r31)
    lfs f3, 0x30(r31)
    fmadds f31, f2, f3, f1
    fmuls f1, f0, f3
    bl LUT_Sin12Bit
    lfs f0, 0x0(r30)
    lfs f2, lbl_806D7D00(r2)
    fadds f0, f27, f0
    lfs f29, lbl_806D7CE8(r2)
    fadds f30, f2, f1
    lfs f28, lbl_806D7D08(r2)
    fcmpo cr0, f31, f0
    bge fn_801494A4_L_80149988
    lwz r3, 0x2c(r31)
    fmr f31, f0
    addi r0, r3, 0x1
    stw r0, 0x2c(r31)
    stfs f29, 0x30(r31)
    b fn_801494A4_L_80149988
    fn_801494A4_L_8014974C:
    lfs f2, 0x30(r31)
    lfs f1, lbl_806D7CDC(r2)
    lfs f0, 0x0(r30)
    fadds f2, f2, f1
    lfs f1, lbl_806D7D18(r2)
    lfs f4, lbl_806D7D10(r2)
    fadds f31, f27, f0
    lfs f0, lbl_806D7D28(r2)
    stfs f2, 0x30(r31)
    lfs f5, lbl_806D7D0C(r2)
    lfs f6, 0x30(r31)
    lfs f3, lbl_806D7D14(r2)
    fdivs f2, f6, f1
    lfs f1, lbl_806D7D08(r2)
    lfs f30, lbl_806D7D00(r2)
    fmuls f4, f4, f6
    fcmpo cr0, f6, f0
    fmadds f28, f3, f2, f1
    fmuls f29, f5, f4
    cror eq, lt, eq
    bne fn_801494A4_L_801497B8
    lfs f0, lbl_806D7D20(r2)
    fmuls f1, f0, f6
    bl LUT_Sin12Bit
    lfs f0, lbl_806D7D1C(r2)
    fmuls f3, f0, f1
    b fn_801494A4_L_801497D4
    fn_801494A4_L_801497B8:
    fsubs f0, f6, f0
    lfs f1, lbl_806D7D04(r2)
    fmuls f1, f1, f0
    bl fn_80186960
    lfs f2, lbl_806D7D24(r2)
    lfs f0, lbl_806D7CDC(r2)
    fmadds f3, f2, f1, f0
    fn_801494A4_L_801497D4:
    lfs f0, lbl_806D7D2C(r2)
    fmr f4, f3
    lwz r3, 0x10(r28)
    addi r4, r29, 0x96b
    fadds f1, f0, f31
    lfs f2, lbl_806D7D30(r2)
    addi r3, r3, 0x1
    li r5, 0x0
    bl fn_801697C0
    lfs f1, 0x30(r31)
    lfs f0, lbl_806D7D18(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_801494A4_L_80149988
    lwz r3, 0x2c(r31)
    cmpwi r29, 0x0
    lfs f0, lbl_806D7CE8(r2)
    addi r0, r3, 0x1
    stw r0, 0x2c(r31)
    stfs f0, 0x30(r31)
    bne fn_801494A4_L_80149834
    lwz r3, 0x34(r31)
    bl fn_8013CA70
    b fn_801494A4_L_80149988
    fn_801494A4_L_80149834:
    lwz r3, 0x34(r31)
    bl fn_8013CA04
    b fn_801494A4_L_80149988
    fn_801494A4_L_80149840:
    lfs f2, 0x30(r31)
    lfs f1, lbl_806D7CDC(r2)
    lfs f0, 0x0(r30)
    fadds f1, f2, f1
    lfs f30, lbl_806D7D00(r2)
    fadds f31, f27, f0
    lfs f29, lbl_806D7D10(r2)
    lfs f28, lbl_806D7D34(r2)
    stfs f1, 0x30(r31)
    lwz r3, 0x1c(r27)
    cmpwi r3, 0x0
    blt fn_801494A4_L_801498DC
    lfs f0, lbl_806D7D18(r2)
    addi r4, r3, 0x2b00
    lwz r3, 0x10(r28)
    li r5, 0x0
    fadds f27, f0, f31
    lfs f4, lbl_806D7D3C(r2)
    lfs f2, lbl_806D6DE4(r2)
    addi r3, r3, 0x1
    lfs f0, lbl_806D6DE8(r2)
    fmr f1, f27
    fmuls f3, f4, f2
    lfs f2, lbl_806D7D38(r2)
    fmuls f4, f4, f0
    bl fn_801697C0
    lwz r3, 0x10(r27)
    li r5, 0x0
    lwz r4, 0x14(r27)
    bl fn_80231BD4
    lfs f3, lbl_806D7D3C(r2)
    fmr f1, f27
    lwz r5, 0x10(r28)
    mr r4, r3
    fmr f4, f3
    lfs f2, lbl_806D7D38(r2)
    addi r3, r5, 0x1
    li r5, 0x0
    bl fn_801697C0
    fn_801494A4_L_801498DC:
    lfs f0, lbl_806D7D40(r2)
    addi r4, r27, 0x2
    lwz r3, 0x10(r28)
    fadds f1, f0, f31
    lfs f2, lbl_806D7D44(r2)
    addi r3, r3, 0x1
    creqv 6, 6, 6
    bl fn_801680A0
    lfs f0, lbl_806D7D2C(r2)
    addi r4, r29, 0x96b
    lwz r3, 0x10(r28)
    li r5, 0x0
    fadds f27, f0, f31
    lfs f2, lbl_806D7D30(r2)
    addi r3, r3, 0x1
    fmr f1, f27
    bl fn_801698B4
    lbz r0, 0x0(r27)
    cmplwi r0, 0x0
    beq fn_801494A4_L_8014996C
    lfs f1, lbl_806D7D4C(r2)
    lfs f0, 0x30(r31)
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    lfs f3, lbl_806D7CDC(r2)
    addi r4, r29, 0x96b
    lfs f0, lbl_806D7D48(r2)
    li r5, 0x2
    lwz r3, 0x10(r28)
    fmr f4, f3
    fmuls f6, f0, f1
    lfs f2, lbl_806D7D30(r2)
    fmr f1, f27
    addi r3, r3, 0x1
    fmr f5, f3
    bl fn_80169468
    fn_801494A4_L_8014996C:
    lfs f1, 0x30(r31)
    lfs f0, lbl_806D7D50(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_801494A4_L_80149988
    lfs f0, lbl_806D7CE8(r2)
    stfs f0, 0x30(r31)
    fn_801494A4_L_80149988:
    fmr f1, f31
    lwz r3, 0x34(r31)
    fmr f2, f30
    bl fn_8013C7B0
    fmr f1, f28
    lwz r3, 0x34(r31)
    bl fn_8013C5FC
    fmr f1, f29
    lwz r3, 0x34(r31)
    bl fn_8013C674
    lwz r3, 0x34(r31)
    bl fn_8013C91C
    fn_801494A4_L_801499B8:
    addi r29, r29, 0x1
    addi r30, r30, 0x4
    cmpwi r29, 0x6
    addi r31, r31, 0xc
    blt fn_801494A4_L_8014960C
    fn_801494A4_L_801499CC:
    lwz r3, 0x24(r28)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x24(r28)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x1c(r28)
    cmplwi r3, 0x0
    beq fn_801494A4_L_80149A3C
    lwz r0, 0x8(r3)
    cmpwi r0, 0x0
    ble fn_801494A4_L_80149A14
    li r0, 0x0
    b fn_801494A4_L_80149A24
    fn_801494A4_L_80149A14:
    lwz r0, 0xc(r3)
    li r4, 0x1
    cntlzw r0, r0
    rlwnm r0, r4, r0, 31, 31
    fn_801494A4_L_80149A24:
    clrlwi. r0, r0, 24
    beq fn_801494A4_L_80149A3C
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_801494A4_L_80149A3C:
    lfs f1, 0x14(r28)
    lfs f0, lbl_806D7CDC(r2)
    fadds f0, f1, f0
    stfs f0, 0x14(r28)
    psq_l f31, 0x68(r1), 0, 0
    lfd f31, 0x60(r1)
    psq_l f30, 0x58(r1), 0, 0
    lfd f30, 0x50(r1)
    psq_l f29, 0x48(r1), 0, 0
    lfd f29, 0x40(r1)
    psq_l f28, 0x38(r1), 0, 0
    lfd f28, 0x30(r1)
    psq_l f27, 0x28(r1), 0, 0
    lfd f27, 0x20(r1)
    lmw r27, 0xc(r1)
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

extern "C" asm void fn_80149A88(void) { /* 0x80149A88 size:0x104 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr. r28, r3
    beq fn_80149A88_L_80149B68
    lis r3, lbl_8048F058@ha
    addi r0, r3, lbl_8048F058@l
    stw r0, 0x0(r28)
    lwz r3, 0x1c(r28)
    cmplwi r3, 0x0
    beq fn_80149A88_L_80149AD8
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_80149A88_L_80149AD8:
    lwz r3, 0x24(r28)
    cmplwi r3, 0x0
    beq fn_80149A88_L_80149AF8
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80149A88_L_80149AF8:
    li r30, 0x0
    mr r31, r28
    fn_80149A88_L_80149B00:
    lwz r3, 0x34(r31)
    cmplwi r3, 0x0
    beq fn_80149A88_L_80149B24
    beq fn_80149A88_L_80149B24
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80149A88_L_80149B24:
    addi r30, r30, 0x1
    addi r31, r31, 0xc
    cmpwi r30, 0x6
    blt fn_80149A88_L_80149B00
    cmplwi r28, 0x0
    beq fn_80149A88_L_80149B58
    lis r3, lbl_8048ED10@ha
    addi r0, r3, lbl_8048ED10@l
    stw r0, 0x0(r28)
    beq fn_80149A88_L_80149B58
    lis r3, lbl_8048ECF8@ha
    addi r0, r3, lbl_8048ECF8@l
    stw r0, 0x0(r28)
    fn_80149A88_L_80149B58:
    extsh. r0, r29
    ble fn_80149A88_L_80149B68
    mr r3, r28
    bl MemoryManager_TimedFree
    fn_80149A88_L_80149B68:
    lwz r0, 0x24(r1)
    mr r3, r28
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void fn_80149B8C(void) { /* 0x80149B8C size:0x14C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r6, lbl_8048ED10@ha
    lfs f0, lbl_806D7CE8(r2)
    stw r0, 0x24(r1)
    addi r6, r6, lbl_8048ED10@l
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    mr r30, r3
    lis r3, lbl_8048ECF8@ha
    stw r29, 0x14(r1)
    addi r0, r3, lbl_8048ECF8@l
    mr r7, r30
    lis r3, lbl_8048F058@ha
    stw r0, 0x0(r30)
    mr r8, r7
    addi r0, r3, lbl_8048F058@l
    li r7, 0x0
    stw r5, 0x4(r8)
    li r3, 0x1c
    stw r7, 0x8(r8)
    stw r7, 0xc(r8)
    stw r6, 0x0(r8)
    stw r0, 0x0(r30)
    stw r31, 0x10(r30)
    stfs f0, 0x14(r30)
    bl Alloc
    mr. r29, r3
    beq fn_80149B8C_L_80149C10
    mr r4, r31
    li r5, 0x0
    bl fn_80141924
    fn_80149B8C_L_80149C10:
    stw r29, 0x1c(r30)
    li r3, 0x28
    bl Alloc
    mr. r29, r3
    beq fn_80149B8C_L_80149C28
    bl fn_8014393C
    fn_80149B8C_L_80149C28:
    stw r29, 0x24(r30)
    cmpwi r31, 0x0
    lwz r3, 0x24(r30)
    blt fn_80149B8C_L_80149C44
    cmpwi r31, 0x8
    bge fn_80149B8C_L_80149C44
    stw r31, 0x0(r3)
    fn_80149B8C_L_80149C44:
    lwz r3, 0x24(r30)
    lwz r12, 0x14(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r4, 0x0
    lfs f0, lbl_806D7CE8(r2)
    stw r4, 0x28(r30)
    li r0, 0x6
    mr r3, r30
    stw r4, 0x2c(r30)
    stfs f0, 0x30(r30)
    stw r4, 0x34(r30)
    stw r4, 0x38(r30)
    stfs f0, 0x3c(r30)
    stw r4, 0x40(r30)
    stw r4, 0x44(r30)
    stfs f0, 0x48(r30)
    stw r4, 0x4c(r30)
    stw r4, 0x50(r30)
    stfs f0, 0x54(r30)
    stw r4, 0x58(r30)
    stw r4, 0x5c(r30)
    stfs f0, 0x60(r30)
    stw r4, 0x64(r30)
    stw r4, 0x68(r30)
    stfs f0, 0x6c(r30)
    stw r4, 0x70(r30)
    stw r0, 0x74(r30)
    stb r4, 0x18(r30)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
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

extern "C" asm void fn_8014A8FC(void) { /* 0x8014A8FC size:0x13C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr. r28, r3
    beq fn_8014A8FC_L_8014AA14
    lis r3, lbl_8048F090@ha
    addi r0, r3, lbl_8048F090@l
    stw r0, 0x0(r28)
    bl StrPcb_GetInstance
    li r4, 0x4
    bl StrPcb_ClearStatusBits
    lwz r3, 0x34(r28)
    cmplwi r3, 0x0
    beq fn_8014A8FC_L_8014A958
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_8014A8FC_L_8014A958:
    lwz r3, 0x38(r28)
    cmplwi r3, 0x0
    beq fn_8014A8FC_L_8014A978
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014A8FC_L_8014A978:
    lwz r3, 0x68(r28)
    li r4, 0x1
    bl fn_8023CFE0
    lwz r3, 0x60(r28)
    cmplwi r3, 0x0
    beq fn_8014A8FC_L_8014A9A8
    beq fn_8014A8FC_L_8014A9A8
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014A8FC_L_8014A9A8:
    li r30, 0x0
    mr r31, r28
    fn_8014A8FC_L_8014A9B0:
    lwz r3, 0x3c(r31)
    cmplwi r3, 0x0
    beq fn_8014A8FC_L_8014A9D0
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014A8FC_L_8014A9D0:
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0x9
    blt fn_8014A8FC_L_8014A9B0
    cmplwi r28, 0x0
    beq fn_8014A8FC_L_8014AA04
    lis r3, lbl_8048ED10@ha
    addi r0, r3, lbl_8048ED10@l
    stw r0, 0x0(r28)
    beq fn_8014A8FC_L_8014AA04
    lis r3, lbl_8048ECF8@ha
    addi r0, r3, lbl_8048ECF8@l
    stw r0, 0x0(r28)
    fn_8014A8FC_L_8014AA04:
    extsh. r0, r29
    ble fn_8014A8FC_L_8014AA14
    mr r3, r28
    bl MemoryManager_TimedFree
    fn_8014A8FC_L_8014AA14:
    lwz r0, 0x24(r1)
    mr r3, r28
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void fn_8014AA38(void) { /* 0x8014AA38 size:0x210 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r6, lbl_8048ED10@ha
    lfs f1, lbl_806D7D68(r2)
    stw r0, 0x24(r1)
    addi r6, r6, lbl_8048ED10@l
    lfs f0, lbl_806D7E00(r2)
    stmw r26, 0x8(r1)
    mr r31, r3
    lis r3, lbl_8048ECF8@ha
    mr r27, r4
    addi r0, r3, lbl_8048ECF8@l
    mr r7, r31
    mr r8, r7
    lis r3, lbl_8048F090@ha
    li r7, 0x0
    stw r0, 0x0(r31)
    addi r0, r3, lbl_8048F090@l
    stw r5, 0x4(r8)
    stw r7, 0x8(r8)
    stw r7, 0xc(r8)
    stw r6, 0x0(r8)
    stw r0, 0x0(r31)
    stw r27, 0x10(r31)
    stfs f1, 0x14(r31)
    stfs f1, 0x18(r31)
    stfs f1, 0x1c(r31)
    stw r7, 0x20(r31)
    lfs f1, g_totalRaceTime(r13)
    stfs f1, 0x2c(r31)
    stfs f0, 0x30(r31)
    bl TaRecord_GetLastInsertedRank
    stw r3, 0x24(r31)
    bl fn_80169DF0
    stb r3, 0x28(r31)
    bl fn_8024F588
    lbz r0, 0x1(r3)
    li r30, 0x0
    li r29, 0x0
    stb r0, 0x29(r31)
    stw r30, 0x60(r31)
    sth r30, 0x70(r31)
    sth r30, 0x72(r31)
    sth r30, 0x74(r31)
    sth r30, 0x76(r31)
    sth r30, 0x78(r31)
    sth r30, 0x7a(r31)
    fn_8014AA38_L_8014AAF4:
    lfs f1, 0x2c(r31)
    subfic r3, r29, 0x8
    bl fn_80167744
    addi r28, r3, 0x998
    li r3, 0x1c
    bl Alloc
    mr. r26, r3
    beq fn_8014AA38_L_8014AB1C
    mr r4, r28
    bl fn_80144308
    fn_8014AA38_L_8014AB1C:
    addi r0, r30, 0x3c
    cmpwi r27, 0x0
    stwx r26, r31, r0
    lwzx r3, r31, r0
    blt fn_8014AA38_L_8014AB3C
    cmpwi r27, 0x8
    bge fn_8014AA38_L_8014AB3C
    stw r27, 0x0(r3)
    fn_8014AA38_L_8014AB3C:
    addi r0, r30, 0x3c
    lwzx r3, r31, r0
    lwz r12, 0x14(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    addi r29, r29, 0x1
    addi r30, r30, 0x4
    cmpwi r29, 0x9
    blt fn_8014AA38_L_8014AAF4
    li r3, 0x1c
    bl Alloc
    mr. r26, r3
    beq fn_8014AA38_L_8014AB80
    mr r4, r27
    li r5, 0x0
    bl fn_80141924
    fn_8014AA38_L_8014AB80:
    stw r26, 0x34(r31)
    li r3, 0x28
    bl Alloc
    mr. r26, r3
    beq fn_8014AA38_L_8014AB98
    bl fn_8014403C
    fn_8014AA38_L_8014AB98:
    stw r26, 0x38(r31)
    li r0, 0x0
    cmpwi r27, 0x0
    stw r0, 0x64(r31)
    lwz r3, 0x38(r31)
    blt fn_8014AA38_L_8014ABBC
    cmpwi r27, 0x8
    bge fn_8014AA38_L_8014ABBC
    stw r27, 0x0(r3)
    fn_8014AA38_L_8014ABBC:
    li r3, 0x20
    bl Alloc
    mr. r26, r3
    beq fn_8014AA38_L_8014ABE4
    li r4, 0x74
    li r5, -0x1
    li r6, 0x1872
    li r7, -0x1
    li r8, 0x4
    bl fn_8023D080
    fn_8014AA38_L_8014ABE4:
    stw r26, 0x68(r31)
    lwz r3, 0x68(r31)
    bl fn_8023CEB4
    lwz r3, 0x68(r31)
    lfs f1, lbl_806D7E04(r2)
    lfs f2, lbl_806D7E08(r2)
    bl fn_8023CD3C
    lwz r3, 0x68(r31)
    lfs f1, lbl_806D7E0C(r2)
    lfs f2, lbl_806D7D94(r2)
    bl fn_8023CCF8
    li r0, 0x0
    stw r0, 0x6c(r31)
    bl StrPcb_GetInstance
    li r4, 0x4
    bl StrPcb_ClearStatusBits
    bl StrPcb_GetInstance
    li r4, 0x8
    bl StrPcb_ClearStatusBits
    mr r3, r31
    lmw r26, 0x8(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void fn_8014AC48(void) { /* 0x8014AC48 size:0x134 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f3, lbl_806D7D60(r2)
    lis r4, lbl_803628A8@ha
    stw r0, 0x14(r1)
    li r5, 0x0
    fmr f4, f3
    lfs f1, lbl_806D7E10(r2)
    stw r31, 0xc(r1)
    addi r31, r4, lbl_803628A8@l
    fmr f5, f3
    lfs f2, lbl_806D7D68(r2)
    stw r30, 0x8(r1)
    fmr f6, f3
    fmr f7, f3
    mr r30, r3
    fmr f8, f3
    li r4, 0x580
    bl fn_80142010
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_8014AC48_L_8014AD04
    lfs f3, lbl_806D7D60(r2)
    mr r3, r30
    lfs f1, lbl_806D7E14(r2)
    addi r4, r31, 0x494
    fmr f4, f3
    lfs f2, lbl_806D7E18(r2)
    fmr f5, f3
    fmr f6, f3
    fmr f7, f3
    fmr f8, f3
    creqv 6, 6, 6
    bl fn_80141E70
    lfs f3, lbl_806D7D60(r2)
    mr r3, r30
    lfs f1, lbl_806D7E14(r2)
    addi r4, r31, 0x4a4
    fmr f4, f3
    lfs f2, lbl_806D7E1C(r2)
    fmr f5, f3
    fmr f6, f3
    fmr f7, f3
    fmr f8, f3
    creqv 6, 6, 6
    bl fn_80141E70
    b fn_8014AC48_L_8014AD64
    fn_8014AC48_L_8014AD04:
    lfs f3, lbl_806D7D60(r2)
    mr r3, r30
    lfs f1, lbl_806D7E14(r2)
    addi r4, r31, 0x4b8
    fmr f4, f3
    lfs f2, lbl_806D7E18(r2)
    fmr f5, f3
    fmr f6, f3
    fmr f7, f3
    fmr f8, f3
    creqv 6, 6, 6
    bl fn_80141E70
    lfs f3, lbl_806D7D60(r2)
    mr r3, r30
    lfs f1, lbl_806D7E14(r2)
    addi r4, r31, 0x4d0
    fmr f4, f3
    lfs f2, lbl_806D7E1C(r2)
    fmr f5, f3
    fmr f6, f3
    fmr f7, f3
    fmr f8, f3
    creqv 6, 6, 6
    bl fn_80141E70
    fn_8014AC48_L_8014AD64:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
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

extern "C" asm void fn_8014B118(void) { /* 0x8014B118 size:0xACC */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 0x8(r1)
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    bne fn_8014B118_L_8014BBCC
    lwz r0, 0x24(r31)
    li r30, 0x0
    cmpwi r0, 0x12
    bne fn_8014B118_L_8014B158
    li r0, 0x1
    stb r0, 0x4(r31)
    b fn_8014B118_L_8014BBCC
    fn_8014B118_L_8014B158:
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x100
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    bne fn_8014B118_L_8014B1A8
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x2000
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_8014B118_L_8014B1BC
    fn_8014B118_L_8014B1A8:
    li r3, 0x0
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    li r30, 0x1
    fn_8014B118_L_8014B1BC:
    lwz r0, 0x24(r31)
    cmplwi r0, 0x11
    bgt fn_8014B118_L_8014BB00
    lis r3, jumptable_8048F130@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_8048F130@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lbz r0, 0x21(r31)
    cmplwi r0, 0x0
    bne fn_8014B118_L_8014B1FC
    li r3, 0x1f
    bl SoundMgr_Play
    li r0, 0x1
    stb r0, 0x21(r31)
    fn_8014B118_L_8014B1FC:
    lfs f2, 0x28(r31)
    li r3, 0x6
    lfs f0, lbl_806D7E40(r2)
    lfs f1, lbl_806D7E30(r2)
    fdivs f0, f2, f0
    lfs f4, lbl_806D7E2C(r2)
    fmr f2, f1
    fmr f3, f1
    fsubs f4, f4, f0
    bl fn_801678FC
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    li r0, 0x1
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r3, 0x0
    li r4, 0x1
    bl fn_801699D8
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x8(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D7E30(r2)
    li r0, 0x2
    stfs f0, 0x28(r31)
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x8(r31)
    bl fn_8014219C
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8014B118_L_8014BB00
    li r0, 0x3
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    li r0, 0x4
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E44(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    lwz r0, 0x38(r31)
    cmpwi r0, 0x0
    beq fn_8014B118_L_8014B39C
    li r0, 0x5
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014B3EC
    fn_8014B118_L_8014B39C:
    lbz r0, 0x4c(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014B3B4
    li r0, 0xb
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014B3EC
    fn_8014B118_L_8014B3B4:
    lbz r0, 0x40(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014B3CC
    li r0, 0xe
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014B3EC
    fn_8014B118_L_8014B3CC:
    lbz r0, 0x70(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014B3E4
    li r0, 0x8
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014B3EC
    fn_8014B118_L_8014B3E4:
    li r0, 0x11
    stw r0, 0x24(r31)
    fn_8014B118_L_8014B3EC:
    lfs f0, lbl_806D7E30(r2)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lbz r0, 0x34(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014B444
    lfs f1, 0x28(r31)
    mr r3, r31
    lfs f0, lbl_806D7E40(r2)
    fdivs f1, f1, f0
    bl fn_8014BF80
    b fn_8014B118_L_8014B458
    fn_8014B118_L_8014B444:
    lfs f1, 0x28(r31)
    mr r3, r31
    lfs f0, lbl_806D7E40(r2)
    fdivs f1, f1, f0
    bl fn_8014BBE4
    fn_8014B118_L_8014B458:
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    lfs f0, lbl_806D7E30(r2)
    li r0, 0x6
    stfs f0, 0x28(r31)
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lbz r0, 0x34(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014B4C4
    lfs f1, lbl_806D7E2C(r2)
    mr r3, r31
    bl fn_8014BF80
    b fn_8014B118_L_8014B4D0
    fn_8014B118_L_8014B4C4:
    lfs f1, lbl_806D7E2C(r2)
    mr r3, r31
    bl fn_8014BBE4
    fn_8014B118_L_8014B4D0:
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E48(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    beq fn_8014B118_L_8014B4EC
    clrlwi. r0, r30, 24
    beq fn_8014B118_L_8014BB00
    fn_8014B118_L_8014B4EC:
    li r0, 0x7
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lbz r0, 0x34(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014B554
    lfs f1, 0x28(r31)
    mr r3, r31
    lfs f0, lbl_806D7E40(r2)
    lfs f2, lbl_806D7E2C(r2)
    fdivs f0, f1, f0
    fsubs f1, f2, f0
    bl fn_8014BF80
    b fn_8014B118_L_8014B570
    fn_8014B118_L_8014B554:
    lfs f1, 0x28(r31)
    mr r3, r31
    lfs f0, lbl_806D7E40(r2)
    lfs f2, lbl_806D7E2C(r2)
    fdivs f0, f1, f0
    fsubs f1, f2, f0
    bl fn_8014BBE4
    fn_8014B118_L_8014B570:
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    lfs f0, lbl_806D7E30(r2)
    stfs f0, 0x28(r31)
    lbz r0, 0x4c(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014B5A4
    li r0, 0xb
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014BB00
    fn_8014B118_L_8014B5A4:
    lbz r0, 0x40(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014B5BC
    li r0, 0xe
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014BB00
    fn_8014B118_L_8014B5BC:
    lbz r0, 0x70(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014B5D4
    li r0, 0x8
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014BB00
    fn_8014B118_L_8014B5D4:
    li r0, 0x11
    stw r0, 0x24(r31)
    b fn_8014B118_L_8014BB00
    li r0, 0x1
    stb r0, 0x58(r31)
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lfs f2, lbl_806D7E4C(r2)
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fmuls f1, f2, f1
    fdivs f0, f1, f0
    stfs f0, 0x5c(r31)
    lwz r3, 0x54(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x54(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    li r0, 0x9
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x54(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x54(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x54(r31)
    lbz r0, 0x4(r3)
    cmplwi r0, 0x1
    bne fn_8014B118_L_8014BB00
    lfs f1, lbl_806D7E30(r2)
    li r3, 0x7
    lfs f4, lbl_806D7E2C(r2)
    fmr f2, f1
    fmr f3, f1
    bl fn_801678FC
    li r3, 0x12
    li r0, 0x1
    stw r3, 0x24(r31)
    lfs f0, lbl_806D7E30(r2)
    stb r0, 0x4(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x54(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x54(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E50(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    li r3, 0x12
    li r0, 0x1
    stw r3, 0x24(r31)
    lfs f0, lbl_806D7E30(r2)
    stb r0, 0x4(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lfs f0, 0x5c(r31)
    lfs f2, lbl_806D7E4C(r2)
    fcmpo cr0, f0, f2
    bge fn_8014B118_L_8014B7D8
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fmuls f1, f2, f1
    fdivs f0, f1, f0
    stfs f0, 0x5c(r31)
    fn_8014B118_L_8014B7D8:
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    li r0, 0xc
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x50(r31)
    cmplwi r3, 0x0
    beq fn_8014B118_L_8014B858
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x50(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fn_8014B118_L_8014B858:
    lwz r3, 0x50(r31)
    cmplwi r3, 0x0
    beq fn_8014B118_L_8014BB00
    bl fn_80140ECC
    clrlwi. r0, r3, 24
    beq fn_8014B118_L_8014BB00
    li r0, 0xd
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    li r0, 0xe
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lfs f0, 0x5c(r31)
    lfs f2, lbl_806D7E4C(r2)
    fcmpo cr0, f0, f2
    bge fn_8014B118_L_8014B90C
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fmuls f1, f2, f1
    fdivs f0, f1, f0
    stfs f0, 0x5c(r31)
    fn_8014B118_L_8014B90C:
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    li r0, 0xf
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x44(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x44(r31)
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014BB00
    li r0, 0x10
    lfs f0, lbl_806D7E30(r2)
    stw r0, 0x24(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x44(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lfs f2, 0x28(r31)
    li r3, 0x7
    lfs f0, lbl_806D7E40(r2)
    lfs f1, lbl_806D7E30(r2)
    fdivs f4, f2, f0
    fmr f2, f1
    fmr f3, f1
    bl fn_801678FC
    lfs f0, 0x28(r31)
    lfs f1, lbl_806D7E40(r2)
    fdivs f0, f0, f1
    stfs f0, 0x5c(r31)
    lfs f0, 0x28(r31)
    fcmpo cr0, f0, f1
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    li r3, 0x12
    li r0, 0x1
    stw r3, 0x24(r31)
    lfs f0, lbl_806D7E30(r2)
    stb r0, 0x4(r31)
    stfs f0, 0x28(r31)
    b fn_8014B118_L_8014BB00
    lbz r0, 0x21(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014BA4C
    li r3, 0x1f
    li r4, 0x5
    bl fn_80192688
    li r0, 0x0
    stb r0, 0x21(r31)
    fn_8014B118_L_8014BA4C:
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lbz r0, 0x58(r31)
    cmplwi r0, 0x0
    beq fn_8014B118_L_8014BAA8
    lwz r3, 0x54(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x54(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    fn_8014B118_L_8014BAA8:
    lfs f2, 0x28(r31)
    li r3, 0x7
    lfs f0, lbl_806D7E40(r2)
    lfs f1, lbl_806D7E30(r2)
    fdivs f4, f2, f0
    fmr f2, f1
    fmr f3, f1
    bl fn_801678FC
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E40(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8014B118_L_8014BB00
    li r3, 0x12
    li r0, 0x1
    stw r3, 0x24(r31)
    li r3, 0x0
    lfs f0, lbl_806D7E30(r2)
    li r4, 0x0
    stb r0, 0x4(r31)
    stfs f0, 0x28(r31)
    bl fn_801699D8
    fn_8014B118_L_8014BB00:
    lwz r3, 0x8(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x14(r31)
    bl fn_80140344
    lwz r3, 0x64(r31)
    cmplwi r3, 0x0
    beq fn_8014B118_L_8014BB30
    lfs f1, lbl_806D7E54(r2)
    bl Sprite_AdvanceAnim
    fn_8014B118_L_8014BB30:
    lwz r0, 0x24(r31)
    cmpwi r0, 0xa
    bgt fn_8014B118_L_8014BBA4
    cmpwi r0, 0x5
    blt fn_8014B118_L_8014BBA4
    lbz r0, 0x70(r31)
    cmplwi r0, 0x1
    bne fn_8014B118_L_8014BBA4
    lbz r0, 0x4c(r31)
    cmplwi r0, 0x0
    bne fn_8014B118_L_8014BBA4
    lbz r0, 0x40(r31)
    cmplwi r0, 0x0
    bne fn_8014B118_L_8014BBA4
    li r3, 0x1f
    bl fn_80192010
    clrlwi. r0, r3, 24
    bne fn_8014B118_L_8014BBA4
    li r3, 0x1
    bl fn_8019083C
    clrlwi. r0, r3, 24
    bne fn_8014B118_L_8014BBA4
    li r3, 0x1
    li r4, 0x0
    bl ClSound_PlayBgmStream
    bl fn_801932F8
    mr r4, r3
    li r3, 0x1
    bl clStream_setVolume
    fn_8014B118_L_8014BBA4:
    bl RumbleUpdate
    lfs f1, 0x28(r31)
    lfs f0, lbl_806D7E2C(r2)
    fadds f0, f1, f0
    stfs f0, 0x28(r31)
    lbz r0, 0x20(r31)
    cmplwi r0, 0x0
    bne fn_8014B118_L_8014BBCC
    li r0, 0x1
    stb r0, 0x20(r31)
    fn_8014B118_L_8014BBCC:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void fn_8014BBE4(void) { /* 0x8014BBE4 size:0x39C */
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

extern "C" asm void fn_8014BF80(void) { /* 0x8014BF80 size:0x388 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stmw r27, 0xc(r1)
    mr r31, r3
    fmr f31, f1
    lwz r28, 0x38(r3)
    mr r3, r28
    bl Item_GetDescriptorField8
    mr r0, r3
    mr r3, r28
    mr r30, r0
    bl Item_GetDescriptorFieldC
    cmpwi r30, 0x0
    li r0, -0x1
    blt fn_8014BF80_L_8014BFCC
    addi r0, r30, 0x503
    fn_8014BF80_L_8014BFCC:
    cmpwi r3, 0x0
    mr r27, r0
    li r29, -0x1
    blt fn_8014BF80_L_8014BFE0
    addi r29, r3, 0x1e1d
    fn_8014BF80_L_8014BFE0:
    mr r3, r30
    bl fn_8013BEC8
    fmr f5, f31
    mr r30, r3
    lfs f1, lbl_806D7E58(r2)
    li r3, 0x0
    lfs f2, lbl_806D7E5C(r2)
    li r4, 0x14e5
    lfs f3, lbl_806D7E60(r2)
    li r5, 0x0
    lfs f4, lbl_806D7E2C(r2)
    bl fn_80169334
    fmr f3, f31
    lfs f1, lbl_806D7E9C(r2)
    lfs f2, lbl_806D7EA0(r2)
    li r3, 0x0
    li r4, 0x14e7
    li r5, 0x0
    bl fn_801695E0
    fmr f5, f31
    lfs f1, lbl_806D7EA4(r2)
    lfs f2, lbl_806D7EA0(r2)
    li r3, 0x0
    lfs f3, lbl_806D7EA8(r2)
    li r4, 0x14e8
    lfs f4, lbl_806D7E2C(r2)
    li r5, 0x0
    bl fn_80169334
    fmr f3, f31
    lfs f1, lbl_806D7EAC(r2)
    lfs f2, lbl_806D7EB0(r2)
    li r3, 0x0
    li r4, 0x14e2
    li r5, 0x0
    bl fn_801695E0
    lfs f3, lbl_806D7E2C(r2)
    fmr f5, f31
    lfs f1, lbl_806D7EB4(r2)
    li r3, 0x0
    fmr f4, f3
    lfs f2, lbl_806D7EB8(r2)
    li r4, 0x14ea
    li r5, 0x0
    bl fn_80169334
    fmr f3, f31
    lfs f1, lbl_806D7EB4(r2)
    lfs f2, lbl_806D7EBC(r2)
    mr r4, r27
    li r3, 0x0
    li r5, 0x0
    bl fn_801695E0
    fmr f3, f31
    lfs f1, lbl_806D7EB4(r2)
    lfs f2, lbl_806D7EBC(r2)
    mr r4, r29
    li r3, 0x0
    li r5, 0x0
    bl fn_801695E0
    mr r3, r28
    li r4, 0x0
    bl Item_GetDescriptorField0
    fmr f3, f31
    mr r4, r3
    lfs f1, lbl_806D7EC0(r2)
    li r3, 0x0
    lfs f2, lbl_806D7EC4(r2)
    li r5, 0x0
    bl fn_801695E0
    fmr f3, f31
    lfs f1, lbl_806D7EC8(r2)
    lfs f2, lbl_806D7ECC(r2)
    li r3, 0x0
    li r4, 0x14e6
    li r5, 0x0
    bl fn_801695E0
    li r3, 0x4d
    li r4, -0x1
    bl GetTextureByIdAndLang
    fmr f3, f31
    mr r4, r3
    lfs f1, lbl_806D7ED0(r2)
    li r3, 0x0
    lfs f2, lbl_806D7ECC(r2)
    creqv 6, 6, 6
    bl fn_80168798
    cmplwi r30, 0x0
    beq fn_8014BF80_L_8014C174
    mr r3, r28
    bl fn_8023DAA8
    lfs f0, 0xc(r30)
    mr r4, r3
    lfs f1, lbl_806D7ED4(r2)
    li r3, 0x0
    fmuls f6, f0, f31
    lfs f2, lbl_806D7ED8(r2)
    lfs f3, 0x0(r30)
    lfs f4, 0x4(r30)
    lfs f5, 0x8(r30)
    creqv 6, 6, 6
    bl fn_80168B90
    b fn_8014BF80_L_8014C198
    fn_8014BF80_L_8014C174:
    mr r3, r28
    bl fn_8023DAA8
    fmr f3, f31
    mr r4, r3
    lfs f1, lbl_806D7ED4(r2)
    li r3, 0x0
    lfs f2, lbl_806D7ED8(r2)
    creqv 6, 6, 6
    bl fn_80168D84
    fn_8014BF80_L_8014C198:
    mr r3, r28
    li r4, 0x0
    bl fn_8023D938
    fmr f3, f31
    mr r4, r3
    lfs f1, lbl_806D7EDC(r2)
    li r3, 0x0
    lfs f2, lbl_806D7EE0(r2)
    creqv 6, 6, 6
    bl fn_80168D84
    mr r3, r28
    li r4, 0x1
    bl fn_8023D938
    fmr f3, f31
    mr r4, r3
    lfs f1, lbl_806D7EDC(r2)
    li r3, 0x0
    lfs f2, lbl_806D7EBC(r2)
    creqv 6, 6, 6
    bl fn_80168D84
    mr r3, r28
    li r4, 0x2
    bl fn_8023D938
    fmr f3, f31
    mr r4, r3
    lfs f1, lbl_806D7EDC(r2)
    li r3, 0x0
    lfs f2, lbl_806D7EC8(r2)
    creqv 6, 6, 6
    bl fn_80168D84
    lwz r28, 0x68(r31)
    cmplwi r28, 0x0
    beq fn_8014BF80_L_8014C274
    li r29, 0x0
    fn_8014BF80_L_8014C220:
    lfs f1, lbl_806D7EE4(r2)
    fmr f4, f31
    lwz r3, 0x4(r28)
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D50C
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x3
    blt fn_8014BF80_L_8014C220
    lwz r30, 0x68(r31)
    li r29, 0x0
    mr r28, r30
    fn_8014BF80_L_8014C254:
    lwz r3, 0x4(r28)
    lwz r4, 0x0(r30)
    bl fn_8013DAC8
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x3
    blt fn_8014BF80_L_8014C254
    b fn_8014BF80_L_8014C2E4
    fn_8014BF80_L_8014C274:
    lwz r28, 0x6c(r31)
    cmplwi r28, 0x0
    beq fn_8014BF80_L_8014C2CC
    li r29, 0x0
    fn_8014BF80_L_8014C284:
    fmr f1, f31
    lwz r3, 0x4(r28)
    bl fn_8013D4B0
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x2
    blt fn_8014BF80_L_8014C284
    lwz r30, 0x6c(r31)
    li r29, 0x0
    mr r28, r30
    fn_8014BF80_L_8014C2AC:
    lwz r3, 0x4(r28)
    lwz r4, 0x0(r30)
    bl fn_8013DAC8
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x2
    blt fn_8014BF80_L_8014C2AC
    b fn_8014BF80_L_8014C2E4
    fn_8014BF80_L_8014C2CC:
    fmr f1, f31
    lwz r3, 0x3c(r31)
    bl fn_8013D4B0
    lwz r3, 0x3c(r31)
    li r4, 0x1
    bl fn_8013DAC8
    fn_8014BF80_L_8014C2E4:
    lwz r3, 0x64(r31)
    stfs f31, 0x20(r3)
    psq_l f31, 0x28(r1), 0, 0
    lfd f31, 0x20(r1)
    lmw r27, 0xc(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void fn_8014C308(void) { /* 0x8014C308 size:0x234 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr. r30, r3
    mr r31, r4
    beq fn_8014C308_L_8014C524
    lis r3, lbl_8048F118@ha
    addi r0, r3, lbl_8048F118@l
    stw r0, 0x0(r30)
    bl fn_8013DB9C
    lwz r3, 0x64(r30)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C350
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    stw r0, 0x64(r30)
    fn_8014C308_L_8014C350:
    lwz r3, 0x8(r30)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C370
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014C308_L_8014C370:
    lwz r3, 0xc(r30)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C390
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014C308_L_8014C390:
    lwz r3, 0x10(r30)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C3B0
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014C308_L_8014C3B0:
    lwz r3, 0x14(r30)
    li r4, 0x1
    bl fn_80140810
    lwz r3, 0x18(r30)
    li r4, 0x1
    bl fn_8023CFE0
    lwz r27, 0x68(r30)
    cmplwi r27, 0x0
    beq fn_8014C308_L_8014C418
    beq fn_8014C308_L_8014C418
    li r29, 0x0
    mr r28, r27
    fn_8014C308_L_8014C3E0:
    lwz r3, 0x4(r28)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C400
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014C308_L_8014C400:
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x3
    blt fn_8014C308_L_8014C3E0
    mr r3, r27
    bl MemoryManager_TimedFree
    fn_8014C308_L_8014C418:
    lwz r27, 0x6c(r30)
    cmplwi r27, 0x0
    beq fn_8014C308_L_8014C468
    beq fn_8014C308_L_8014C468
    li r29, 0x0
    mr r28, r27
    fn_8014C308_L_8014C430:
    lwz r3, 0x4(r28)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C450
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014C308_L_8014C450:
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x2
    blt fn_8014C308_L_8014C430
    mr r3, r27
    bl MemoryManager_TimedFree
    fn_8014C308_L_8014C468:
    lwz r3, 0x3c(r30)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C48C
    beq fn_8014C308_L_8014C48C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014C308_L_8014C48C:
    lwz r3, 0x44(r30)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C4B0
    beq fn_8014C308_L_8014C4B0
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014C308_L_8014C4B0:
    lwz r3, 0x50(r30)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C4D4
    beq fn_8014C308_L_8014C4D4
    lwz r12, 0x14(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014C308_L_8014C4D4:
    lwz r3, 0x54(r30)
    cmplwi r3, 0x0
    beq fn_8014C308_L_8014C4F0
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_8014C308_L_8014C4F0:
    bl fn_80169C44
    bl fn_80121210
    bl fn_8012094C
    bl clRom_PurgeAll
    cmplwi r30, 0x0
    beq fn_8014C308_L_8014C514
    lis r3, lbl_803FE0C8@ha
    addi r0, r3, lbl_803FE0C8@l
    stw r0, 0x0(r30)
    fn_8014C308_L_8014C514:
    extsh. r0, r31
    ble fn_8014C308_L_8014C524
    mr r3, r30
    bl MemoryManager_TimedFree
    fn_8014C308_L_8014C524:
    mr r3, r30
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

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
