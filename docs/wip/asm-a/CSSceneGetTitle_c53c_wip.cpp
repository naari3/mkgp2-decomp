/*
 * 0x8014ADB4..0x8014CE74: clCSSceneGetTitle (rank board / prize panel) result-screen
 * controller. Split out of RaceHud_80147470.cpp because this TU owns the pooled
 * .rodata 0x80362D90..0x80363D30 (anchor CSSceneGetTitle_8014ADB4_rodata_80362D90).
 */

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

#define FK(x) (*(const float *)&(x))

class VObj {
public:
    VObj(const void *res, unsigned char flag);
    virtual ~VObj();
    char pad4[0x1C];
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
void fn_80169334(void *obj, int id, int flag, float x, float y, float sx, float sy, float a);
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
void fn_801695E0(void *obj, int id, int flag, float x, float y, float a);
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
extern unsigned int lbl_806D7EE4;
void Sprite_Destroy(void *p, int flag);
extern void clRom_PurgeAll();
extern void fn_8012094C();
extern void fn_80121210();
extern void fn_8013DB9C();
extern void fn_80169C44();
extern unsigned int lbl_803FE0C8[];
extern unsigned int CSSceneGetTitle_vtable_8048F118[];
void CalcEarnedCoins(void);
void InitRumbleController(int a);
void *ItemRes_LookupByKey_Thunk(int key);
void PlayerData_ApplyItemUnlockById(int item);
void ProcessSystemTick(int a);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
extern void Sprite_InitWithAnim();
struct SyncRecv *SyncSlot_GetRecv(void);
const float *fn_8013BE98(int item);
void fn_8013D59C(void *m, float x, float y, float z);
void fn_8013DBF8(void);
extern void fn_8013FF6C();
extern void fn_80140FEC();
void fn_801426A0(void *p, int i, int kart);
extern void fn_80142964();
void *fn_80160238(void);
void fn_801909A4(int slot);
void fn_8019FF6C(void *spr, int a);
int fn_801D59A0(void *pd, int cc, int cup);
void fn_801D5C88(void *pd, int cc);
unsigned char fn_801D6F30(void *pd, int item, int a);
void fn_801DC870(int a);
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
void fn_8014BBE4(struct ResultPanel *self, float alpha);
void fn_8014BF80(struct ResultPanel *self, float alpha);
struct ResultPanel *fn_8014C308(struct ResultPanel *self, short flag);

#pragma section R ".extab_user"


__declspec(section ".extab_user") static const unsigned char extab_fn_8014ADB4[8] = {
    0x40, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




#pragma section R ".extabindex_user"


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014ADB4 = {
    (void *)&fn_8014ADB4, 0x00000364, (void *)extab_fn_8014ADB4
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
    HudResSet(int coins, int layer, int mode);
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
};

struct HudResHolder {
    HudResSet *p;
    HudResHolder(HudResSet *q) : p(q) {}
    ~HudResHolder() throw();
};

struct PtrHolder {
    VObj *p;
    PtrHolder(VObj *q) : p(q) {}
    ~PtrHolder() throw();
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

struct PartVec {
    float x, y, z;
};
extern "C" const PartVec sTriPos[3];
extern "C" const PartVec sTriRot[3];
extern "C" const float sTriScale[3];
extern "C" const PartVec sPairPos[2];
extern "C" const PartVec sPairRot;
extern "C" const char sPumpModel[];
extern "C" const char sPumpBaseModel[];

struct ObjTrio {
    int f0;
    VObj *objs[3];
    ObjTrio(int a, float s) {
        const PartVec *rot;
        const PartVec *pos;
        const float *scale;
        float k;
        int i;

        f0 = a;
        k = FK(lbl_806D7EF4);
        scale = sTriScale;
        pos = sTriPos;
        rot = sTriRot;
        for (i = 0; i < 3; i++) {
            objs[i] = new VObj(ItemRes_LookupByKey_Thunk(0x32), 1);
            fn_8013D738(objs[i], lbl_806D7E30, lbl_806D7E2C);
            fn_8013D660(objs[i], FK(lbl_806D7EE8), FK(lbl_806D7EEC));
            fn_8013D634(objs[i], pos->x * s, pos->y * s, pos->z * s);
            fn_8013D608(objs[i], *scale * s, *scale * s, *scale * s);
            fn_8013D59C(objs[i], k * rot->x, k * rot->y, k * rot->z);
            fn_8013D50C(objs[i], FK(lbl_806D7EE4), FK(lbl_806D7EE4), FK(lbl_806D7EE4), lbl_806D7E30);
            scale++;
            pos++;
            rot++;
        }
    }
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
    ObjPair(int a) {
        const PartVec *pos;
        float s;
        float k;
        int i;

        f0 = a;
        objs[0] = new VObj(sPumpModel, 1);
        objs[1] = new VObj(sPumpBaseModel, 1);
        s = FK(lbl_806D7EF0);
        k = FK(lbl_806D7EF4);
        pos = sPairPos;
        for (i = 0; i < 2; i++) {
            fn_8013D738(objs[i], lbl_806D7E30, lbl_806D7E2C);
            fn_8013D660(objs[i], FK(lbl_806D7EE8), FK(lbl_806D7EEC));
            fn_8013D634(objs[i], pos->x * s, pos->y * s, pos->z * s);
            fn_8013D608(objs[i], FK(lbl_806D7EF0), FK(lbl_806D7EF0), FK(lbl_806D7EF0));
            fn_8013D59C(objs[i], k * sPairRot.x, k * sPairRot.y, k * sPairRot.z);
            pos++;
        }
    }
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
    char pad20[8];
    unsigned char f28;
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
/* item-get preview layouts: three-piece (0x9B) and pump pair (0x9D) */
extern "C" const PartVec sTriPos[3] = {{2.28f, -2.6f, -8.0f}, {0.71f, -3.3f, 0.0f}, {-1.39f, -3.8f, 6.0f}};
extern "C" const PartVec sTriRot[3] = {{9.5f, 340.5f, 358.0f}, {9.5f, 340.5f, 358.0f}, {9.5f, 340.5f, 358.0f}};
extern "C" const float sTriScale[3] = {0.65f, 0.83f, 1.13f};
extern "C" const float sPool_EC4[3] = {0.0f, 1.0f, 1.0f};
extern "C" const PartVec sPairPos[2] = {{0.0f, -3.0f, 0.0f}, {0.0f, -3.0f, 0.0f}};
extern "C" const PartVec sPool_EE8 = {0.0f, 0.0f, 0.0f};
extern "C" const PartVec sPairRot = {0.0f, 39.5f, 1.0f};
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
extern "C" const unsigned int sdata_806CF750_rodata_80363CF0[5] = {
    0x636C4353, 0x5363656E, 0x65416363, 0x6F6C6164, 0x65000000,
};
extern "C" const char sPumpModel[20] = "it_w_09_pump.dat";
extern "C" const char sPumpBaseModel[24] = "it_w_09_pump_dodai.dat";

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

extern "C" asm void fn_8014ADB4(void) { /* 0x8014ADB4 size:0x364 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stmw r24, 0x20(r1)
    mr r29, r3
    lis r3, CSSceneGetTitle_8014ADB4_rodata_80362D90@ha
    lbz r0, 0x4(r29)
    addi r31, r3, CSSceneGetTitle_8014ADB4_rodata_80362D90@l
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

class SceneBase {
public:
    virtual ~SceneBase();
    unsigned char f4;
    SceneBase() : f4(0) {}
};

struct Obj48 { char pad[0x48]; Obj48(int n); };
struct Obj28 { char pad[0x28]; Obj28(); };
struct Obj1C { char pad[0x1C]; Obj1C(); };
struct Obj24 { char pad[0x24]; Obj24(); };
struct Obj44 { char pad[0x44]; Obj44(); };
struct Obj284 { int f0; char pad[0x280]; Obj284(); };
struct GetSprite {
    char pad[0xC];
    float x;        /* 0x0C */
    float y;        /* 0x10 */
    char pad14[0xC];
    float alpha;    /* 0x20 */
    char pad24[0xC];
    GetSprite(int id, int a, int b);
    void SetPos(float px, float py) {
        float t = px;
        y = py;
        x = t;
    }
};
struct SyncRecv { int f0; int item; };
struct GameFlags { unsigned char f0, f1, f2, f3; int cup; int round; unsigned char fC; };

class clCSSceneGetTitle : public SceneBase {
public:
    clCSSceneGetTitle();
    virtual ~clCSSceneGetTitle();
    Obj48 *f8;
    Obj28 *fC;
    Obj1C *f10;
    Obj24 *f14;
    int f18;
    char pad1C[4];
    unsigned char f20;
    unsigned char f21;
    char pad22[2];
    int state;
    float t;
    char pad2C;
    unsigned char f2D;
    char pad2E[2];
    int chr;
    unsigned char active;
    char pad35[3];
    int item;
    VObj *model;
    unsigned char f40;
    char pad41[3];
    Obj44 *f44;
    int f48;
    unsigned char f4C;
    char pad4D[3];
    Obj284 *f50;
    void *f54;
    unsigned char f58;
    char pad59[3];
    float f5C;
    float f60;
    GetSprite *sprite;
    ObjTrio *tri;
    ObjPair *pair;
    unsigned char f70;
};

#pragma use_lmw_stmw on
clCSSceneGetTitle::clCSSceneGetTitle() {
    HudRankSlot *slot;
    int cup;
    int cc;
    int round;
    unsigned char unlocked;
    int i;

    fn_8013DBF8();
    InitRumbleController(1);
    f8 = new Obj48(1);
    f2D = 1;
    if (!ServiceEnable_Get() || ServiceValue_Get() == 1) {
        f2D = 0;
    }
    for (i = 0; i < 6; i++) {
        slot = RankSlot_GetByIndex(i);
        if (slot != 0) {
            fn_801426A0(f8, i, slot->kart);
        }
    }
    ProcessSystemTick(0);
    fC = new Obj28();
    f10 = new Obj1C();
    f14 = new Obj24();
    f18 = 0;
    f20 = 0;
    f21 = 0;
    state = 0;
    t = lbl_806D7E30;
    item = 0;
    model = 0;
    tri = 0;
    pair = 0;
    f40 = 0;
    f44 = 0;
    f48 = -1;
    f4C = 0;
    f50 = 0;
    f54 = fn_80271340(fn_80160238(), 0, CSSceneGetTitle_8014ADB4_data_806CF818, lbl_806CF810, 0);
    f58 = 0;
    f5C = lbl_806D7E30;
    f60 = lbl_806D7E30;
    sprite = 0;
    f70 = has_title_changed();
    ProcessSystemTick(0);
    slot = RankSlot_GetByIndex(0);
    chr = slot->chr;
    active = slot->active;
    cc = g_ccClass;
    cup = g_cupId;
    round = g_roundIndex;
    fn_801D5C88(g_playerData, cc);
    unlocked = 0;
    if (slot->f28) {
        switch (g_gameMode) {
        case 0:
            if (active) {
                unsigned char cleared;
                int wins;
                int need;
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
                cleared = 0;
                wins = fn_801D59A0(g_playerData, cc, cup);
                need = 4;
                if (round >= 4) {
                    need = 9;
                }
                if (wins >= need) {
                    cleared = 1;
                }
                if (cleared) {
                    f40 = 1;
                    f48 = cup + 8;
                }
                if (cleared == 1 && fn_8024F588()[0] == 1) {
                    f4C = 1;
                }
            } else {
                fn_801DC870(1);
            }
            break;
        case 2:
            if (chr >= 0 && chr <= 3) {
                item = SyncSlot_GetRecv()->item;
                if (item <= 0 || item >= 0x115) {
                    item = 0;
                }
                if (item != 0 && active == 1) {
                    PlayerData_ApplyItemUnlockById(item);
                }
                if (active == 1 && fn_8023F714() == 1) {
                    unlocked = 1;
                }
            }
            break;
        }
    }
    if (f40 == 1) {
        CalcEarnedCoins();
    }
    if (unlocked == 1) {
        GameFlags *flags;
        int next = g_roundIndex + 1;
        int c = g_cupId;
        flags = (GameFlags *)fn_8024F588();
        flags->f2 = 1;
        flags->cup = c;
        flags->round = next;
        lbl_806D17F0 = 1;
        lbl_806D17F2 = 1;
        fn_801DC870(2);
    }
    if (f40) {
        f44 = new Obj44();
        GameFlags *g = (GameFlags *)fn_8024F588();
        g->fC = 1;
    }
    if (item != 0 && active == 1) {
        const float *col = fn_8013BE98(item);
        if (item == 0x9B) {
            tri = new ObjTrio(1, FK(lbl_806D7EF0));
            tri->SetColor(lbl_806D7E30);
        } else if (item == 0x9D) {
            pair = new ObjPair(1);
            pair->SetAlpha(lbl_806D7E30);
        } else {
            model = new VObj(ItemRes_LookupByKey_Thunk(item), 1);
            fn_8013D738(model, lbl_806D7E30, lbl_806D7E2C);
            fn_8013D660(model, FK(lbl_806D7EE8), FK(lbl_806D7EEC));
            fn_8013D634(model, FK(lbl_806D7EF0) * col[0], FK(lbl_806D7EF0) * col[1], FK(lbl_806D7EF0) * col[2]);
            fn_8013D59C(model, FK(lbl_806D7EF4) * col[3], FK(lbl_806D7EF4) * col[4], FK(lbl_806D7EF4) * col[5]);
            fn_8013D608(model, FK(lbl_806D7EF0) * col[6], FK(lbl_806D7EF0) * col[6], FK(lbl_806D7EF0) * col[6]);
            if (item == 0x81) {
                fn_8013D50C(model, FK(lbl_806D7EF8), FK(lbl_806D7EF8), FK(lbl_806D7EF8), lbl_806D7E30);
            }
        }
    }
    sprite = 0;
    if (item != 0) {
        if (active == 1) {
            sprite = new GetSprite(0x40, 1, 0);
            sprite->SetPos(FK(lbl_806D7EAC), FK(lbl_806D7EB0));
        } else {
            sprite = new GetSprite(0x41, 1, 0);
            sprite->SetPos(lbl_806D7E58, FK(lbl_806D7E5C));
        }
        sprite->alpha = lbl_806D7E30;
        fn_8019FF6C(sprite, 1);
    }
    if (fn_8019083C(1)) {
        fn_801909A4(1);
    }
    if (f4C == 1) {
        f50 = new Obj284();
        f50->f0 = 0;
    }
    PreloadResource(0x14E5);
    if (item != 0) {
        if (active) {
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
