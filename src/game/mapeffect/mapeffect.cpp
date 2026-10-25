/*
 * 0x801752C0..0x8017A52C: the course map effects. CreateMapEffect builds the
 * effect for the current cup; each course class fills a parts list with its
 * animated pieces (sounds, texture scrollers, reverb zones, traps) and spawns
 * static particle effects on marker joints. Every member function is defined
 * inline, so the constructors and the virtual methods are emitted as weak
 * copies after the factory, in the order the compiler first needs them; the
 * vtables, typeinfo and RTTI names fall out in the same order.
 * YIState::Update is a member template so it is instantiated last, as in the
 * target. It is the only function that does not match yet: the quad tests
 * get a different float register assignment (TU kept NonMatching for that).
 * Mangled names are bridged in tools/extab_user_renames.json.
 */

#pragma readonly_strings on

struct ZoneDesc;

struct JObj {
    char pad00[0x8];
    JObj *next;
    JObj *parent;
    JObj *child;
    unsigned int flags;
    char pad18[0x8];
    float rotY;
    char pad24[0x8];
    float scaleX;
    char pad30[0x4];
    float scaleZ;
    char pad38[0xC];
    float mtx[3][4];
};

struct MoveTexDesc {
    const char *name;
    float u;
    float v;
};

struct DrawEffect;

extern "C" {
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_gameMode;
extern int g_cupId;
void DebugPrintf(const char *, ...);
JObj *ResolveJointByName(JObj *, const char *);
void __assert(const char *, int, const char *);
void HSD_JObjSetupMatrixSub(JObj *);
DrawEffect *DrawEffect_SpawnWithMatrix(int id, float (*mtx)[4]);
void DrawEffect_SetFlagsByte(DrawEffect *, unsigned char);
void fn_8016B248(void *desc);
void fn_8016B178(int mode);
void fn_8016B160(float v);
void fn_8016B148(float v);
void fn_8016B0F0(unsigned char r, unsigned char g, unsigned char b);
void fn_8016B190(void);
void fn_8016B0A0(void);
void fn_8016B0C4(void);
unsigned char SoundMgr_PlaySE(int id);
unsigned char fn_8016C360(int id);
unsigned char fn_8016C394(int id);
unsigned char fn_8016C3C8(int id, int mode);
void fn_8016C1B0(int id, int vol);
void fn_8016C168(int id, int pan);
void fn_8016C1F8(int id, float vol);
unsigned char IsRaceStarted(void);
void *GetCourseScene3D(void);
void CObj_LoadProjMatrix(void *cobj, struct Vec3f *pos);
void fn_80193134(unsigned char on);
void fn_80182E18(JObj *joint, float u, float v);
float LUT_Sin12Bit(float);
void fn_802D20AC(JObj *);
extern const float lbl_80495994[];
extern const float lbl_80495A94[];
}

extern const unsigned int lbl_80370870[0x102] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_80370C78[0x8] = {
    0xC5478B33, 0xC5986F33, 0x44BB6333, 0xC5E3F666, 0xC487CCCD, 0xC65FCACD,
    0xC5B2199A, 0xC6313B9A,
};
extern const unsigned int lbl_80370C98[0x8] = {
    0xC4158000, 0xC5CDE59A, 0x4465F333, 0xC5BA3D9A, 0x440CA000, 0xC657E133,
    0xC4BD2333, 0xC64B6ACD,
};
extern const unsigned int lbl_80370CB8[0x8] = {
    0xC48F6666, 0xC5BF0333, 0xC5201800, 0xC5DC6333, 0xC5BB899A, 0xC50BC000,
    0xC58E7333, 0xC49F099A,
};
extern const char lbl_80370CD8[0x1C] = "MR_highway_mr_neon_a_joint";
extern const char lbl_80370CF4[0x1C] = "MR_highway_Amr_neon_n_joint";
extern const char lbl_80370D10[0x1C] = "MR_highway_Amr_neon_r_joint";
extern const MoveTexDesc lbl_80370D2C[4] = {
    {lbl_80370CD8, 0.0f, 0.009999999776482582f},
    {lbl_80370CF4, 0.0f, 0.009999999776482582f},
    {lbl_80370D10, 0.0f, 0.009999999776482582f},
    {0, 0.0f, 0.0f},
};
extern const char lbl_80370D5C[0x1C] = "WC_dcity_wc_neon_na_joint";
extern const char lbl_80370D78[0x1C] = "WC_dcity_wc_neon_nb_joint";
extern const char lbl_80370D94[0x1C] = "WC_dcity_wc_neon_nc_joint";
extern const char lbl_80370DB0[0x1C] = "WC_dcity_wc_neon_ra_joint";
extern const char lbl_80370DCC[0x1C] = "WC_dcity_wc_neon_rb_joint";
extern const char lbl_80370DE8[0x1C] = "WC_dcity_wc_neon_rc_joint";
extern const MoveTexDesc lbl_80370E04[7] = {
    {lbl_80370D5C, 0.0f, 0.014999999664723873f},
    {lbl_80370D78, 0.0f, 0.014999999664723873f},
    {lbl_80370D94, 0.0f, 0.014999999664723873f},
    {lbl_80370DB0, 0.0f, 0.014999999664723873f},
    {lbl_80370DCC, 0.0f, 0.014999999664723873f},
    {lbl_80370DE8, 0.0f, 0.014999999664723873f},
    {0, 0.0f, 0.0f},
};
extern const MoveTexDesc lbl_80370E58[7] = {
    {lbl_80370D5C, 0.0f, 0.014999999664723873f},
    {lbl_80370D78, 0.0f, 0.014999999664723873f},
    {lbl_80370D94, 0.0f, 0.014999999664723873f},
    {lbl_80370DB0, 0.0f, 0.014999999664723873f},
    {lbl_80370DCC, 0.0f, 0.014999999664723873f},
    {lbl_80370DE8, 0.0f, 0.014999999664723873f},
    {0, 0.0f, 0.0f},
};
extern const char lbl_80370EAC[0x20] = "KP_castle_KP_yougan_taki_joint";
extern const char lbl_80370ECC[0x20] = "KP_castle_KP_yougan_yuka_joint";
extern const MoveTexDesc lbl_80370EEC[3] = {
    {lbl_80370EAC, 0.0f, -0.0020000000949949026f},
    {lbl_80370ECC, 0.0f, -0.0010000000474974513f},
    {0, 0.0f, 0.0f},
};
extern const char lbl_80370F10[0x18] = "RB_road_rb_neon_a_joint";
extern const char lbl_80370F28[0x18] = "RB_road_rb_neon_b_joint";
extern const char lbl_80370F40[0x18] = "RB_road_rb_neon_c_joint";
extern const char lbl_80370F58[0x18] = "RB_road_rb_neon_d_joint";
extern const char lbl_80370F70[0x18] = "RB_road_rb_neon_e_joint";
extern const char lbl_80370F88[0x18] = "RB_road_rb_hikari_joint";
extern const char lbl_80370FA0[0x18] = "RB_road_rb_taki_joint";
extern const char lbl_80370FB8[0x18] = "RB_road_rb_mizu_joint";
extern const MoveTexDesc lbl_80370FD0[9] = {
    {lbl_80370F10, 0.0f, 0.009999999776482582f},
    {lbl_80370F28, 0.0f, 0.004999999888241291f},
    {lbl_80370F40, 0.0f, 0.009999999776482582f},
    {lbl_80370F58, 0.0f, 0.009999999776482582f},
    {lbl_80370F70, 0.0005000000237487257f, 0.0003000000142492354f},
    {lbl_80370F88, 0.0006000000284984708f, -0.008999999612569809f},
    {lbl_80370FA0, 0.0f, 0.009999999776482582f},
    {lbl_80370FB8, 0.0f, 0.009999999776482582f},
    {0, 0.0f, 0.0f},
};
extern const MoveTexDesc lbl_8037103C[1] = {
    {0, 0.0f, 0.0f},
};
extern const char lbl_80371048[0x1C] = "DN_stadium_neon_na_joint";
extern const char lbl_80371064[0x20] = "DN_stadium_neon_normal_joint";
extern const char lbl_80371084[0x20] = "DN_stadium_neon_reverse_joint";
extern const MoveTexDesc lbl_803710A4[4] = {
    {lbl_80371048, 0.0f, 0.009999999776482582f},
    {lbl_80371064, 0.0f, 0.004999999888241291f},
    {lbl_80371084, 0.0f, 0.004999999888241291f},
    {0, 0.0f, 0.0f},
};
extern const unsigned int lbl_803710D4[0x1E] = {
    0xC3DC5551, 0x00000000, 0x4500DDD0, 0x4341DDDA, 0x00000000, 0x44E73318,
    0x44172AB3, 0x00000000, 0x44E7EA94, 0x4423F77B, 0x00000000, 0x45358662,
    0x00000004, 0x00000000, 0x00000000, 0x441499AC, 0x00000000, 0x44E7EA9A,
    0x44643BB4, 0x00000000, 0x44E09DE4, 0x44BB6669, 0x00000000, 0x44EFFBA0,
    0x44212233, 0x00000000, 0x45353114, 0x00000004, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_8037114C[0x3C] = {
    0xC59A8AC3, 0x4392091C, 0xC5277021, 0xC59124BF, 0x4392091C, 0xC555F653,
    0xC511B01C, 0x4392091C, 0xC51B8A54, 0xC5247C24, 0x4392091C, 0xC4DA0846,
    0x00000004, 0x00000000, 0x00000000, 0xC5A4C698, 0x4392091C, 0xC4E98ED9,
    0xC59A34E5, 0x4392091C, 0xC529191C, 0xC52E1C73, 0x4392091C, 0xC4E5AC4C,
    0xC5433FDC, 0x4392091C, 0xC47A11D8, 0x00000004, 0x00000000, 0x00000000,
    0xC446C000, 0x00000000, 0xC4210000, 0x43E2CCCD, 0x00000000, 0xC30B3333,
    0x4373999A, 0x00000000, 0x43BDE666, 0xC47B4000, 0x00000000, 0xC2FA0000,
    0x00000001, 0xC0A00000, 0x00000000, 0x43E2CCCD, 0x00000000, 0xC30B3333,
    0x443FC000, 0x00000000, 0xC1500000, 0x440B4000, 0x00000000, 0x43FD0000,
    0x4373999A, 0x00000000, 0x43BDE666, 0x00000000, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_8037123C[0x3C] = {
    0xC4C5D99B, 0x00000000, 0xC5B53EE6, 0x4281999E, 0x00000000, 0xC5A7377F,
    0xC3BA443B, 0x00000000, 0xC5914879, 0xC4C69DDA, 0x00000000, 0xC591C325,
    0x00000004, 0x00000000, 0x00000000, 0xC4C69558, 0x00000000, 0xC5922332,
    0xC3AEDDE3, 0x00000000, 0xC5917AAA, 0xC3AC88FF, 0x00000000, 0xC5834FE5,
    0xC433C449, 0x00000000, 0xC55FAA7D, 0x00000004, 0x00000000, 0x00000000,
    0x4404C3D4, 0x00000000, 0xC567E1BC, 0x4502AEC5, 0x00000000, 0xC5335967,
    0x4501EA8D, 0x00000000, 0xC508CA79, 0x4381435B, 0x00000000, 0xC548DD7B,
    0x00000004, 0x00000000, 0x00000000, 0x44BF10E1, 0x00000000, 0xC51EF742,
    0x44FAC40C, 0x00000000, 0xC5110A69, 0x44EE2A72, 0x00000000, 0xC4F42E6F,
    0x44B2151D, 0x00000000, 0xC505B50F, 0x00000004, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_8037132C[0x3C] = {
    0x42F50E5D, 0x00000000, 0xC5A49632, 0xC3AA4501, 0x00000000, 0xC590551F,
    0xC4ABF79A, 0x00000000, 0xC5918647, 0xC4AA8022, 0x00000000, 0xC5AFFBB0,
    0x00000004, 0x00000000, 0x00000000, 0xC3A49A44, 0x00000000, 0xC590FB83,
    0xC3C3338D, 0x00000000, 0xC581FA70, 0xC47166CF, 0x00000000, 0xC5478615,
    0xC4F78471, 0x00000000, 0xC592BFD1, 0x00000004, 0x00000000, 0x00000000,
    0x43F2CC4C, 0x00000000, 0xC5659968, 0x44E14426, 0x00000000, 0xC55B2EC1,
    0x4508B103, 0x00000000, 0xC51110E1, 0x435CCBD4, 0x00000000, 0xC549F525,
    0x00000004, 0x00000000, 0x00000000, 0x45262875, 0x00000000, 0xC5284CA2,
    0x454090F1, 0x00000000, 0xC50A9FD9, 0x452B0427, 0x00000000, 0xC4EDDD98,
    0x450A086C, 0x00000000, 0xC50D7978, 0x00000004, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_8037141C[0x1E] = {
    0xC517E5E2, 0x42ADF3A0, 0x43691D98, 0xC517D3FA, 0x42ABE153, 0xC3191FD9,
    0xC44F2268, 0x4293FE2F, 0xC3191F2B, 0xC44F225E, 0x429401CF, 0x43691E49,
    0x00000004, 0x00000000, 0x00000000, 0xC5491A14, 0x43960065, 0xC5D32564,
    0xC52A9A24, 0x43960016, 0xC5BAB927, 0xC550297A, 0x4395FA95, 0xC59F2FC7,
    0xC58C8FAD, 0x439605D0, 0xC5A40718, 0x00000004, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_80371494[0x1E] = {
    0xC517D3FA, 0x00000000, 0xC3191FD9, 0xC4272268, 0x00000000, 0xC3191F2B,
    0xC427225E, 0x00000000, 0x43691E49, 0xC517E5E2, 0x00000000, 0x43691D98,
    0x00000004, 0x00000000, 0x00000000, 0xC56EF3C3, 0x00000000, 0xC5D8B861,
    0xC554FA35, 0x00000000, 0xC5D70E70, 0xC562E97A, 0x00000000, 0xC5A06FC7,
    0xC57CFF5A, 0x00000000, 0xC5A22718, 0x00000004, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_8037150C[0x5A] = {
    0x4481C000, 0x00000000, 0xC4E8C000, 0x44F11333, 0x00000000, 0xC4E8C000,
    0x44F11333, 0x00000000, 0xC47A0000, 0x4481C000, 0x00000000, 0xC47A0000,
    0x00000000, 0x00000000, 0x00000000, 0x44A2C000, 0x00000000, 0xC47D0000,
    0x44F10000, 0x00000000, 0xC47D0000, 0x44F10000, 0x00000000, 0xC30A0000,
    0x44A2C000, 0x00000000, 0xC30A0000, 0x00000000, 0x00000000, 0x00000000,
    0x43330000, 0x00000000, 0xC40F4000, 0x44A4C000, 0x00000000, 0xC40F4000,
    0x44A4C000, 0x00000000, 0xC30A0000, 0x43330000, 0x00000000, 0xC30A0000,
    0x00000000, 0x00000000, 0x00000000, 0x449D4000, 0x00000000, 0x43838000,
    0x450C4000, 0x00000000, 0x43838000, 0x450C4000, 0x00000000, 0x450EA000,
    0x449D4000, 0x00000000, 0x450EA000, 0x00000000, 0x00000000, 0x00000000,
    0xC4A38000, 0x00000000, 0xC4930000, 0xC473C000, 0x00000000, 0xC4930000,
    0xC473C000, 0x00000000, 0x42940000, 0xC4A38000, 0x00000000, 0x42940000,
    0x00000000, 0x00000000, 0x00000000, 0xC3390000, 0x00000000, 0xC4FA2000,
    0x44832000, 0x00000000, 0xC4FA2000, 0x44832000, 0x00000000, 0xC4B80000,
    0xC3390000, 0x00000000, 0xC4B80000, 0x00000000, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_80371674[0x3C] = {
    0x44CE8000, 0x00000000, 0xC5827800, 0x4539A000, 0x00000000, 0xC58FF800,
    0x4539A000, 0x00000000, 0xC53D4000, 0x45049000, 0x00000000, 0xC5579000,
    0x00000004, 0x00000000, 0x00000000, 0x4501A000, 0x00000000, 0xC4952000,
    0x4533A000, 0x00000000, 0xC4E18000, 0x4541A000, 0x00000000, 0xC4888000,
    0x4530F000, 0x00000000, 0xC40B8000, 0x00000004, 0x00000000, 0x00000000,
    0xC4A38000, 0x00000000, 0xC4930000, 0xC473C000, 0x00000000, 0xC4930000,
    0xC473C000, 0x00000000, 0x42940000, 0xC4A38000, 0x00000000, 0x42940000,
    0x00000000, 0x00000000, 0x00000000, 0xC3390000, 0x00000000, 0xC4FA2000,
    0x44832000, 0x00000000, 0xC4FA2000, 0x44832000, 0x00000000, 0xC4B80000,
    0xC3390000, 0x00000000, 0xC4B80000, 0x00000000, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_80371764[0x1E] = {
    0x45973000, 0x00000000, 0xC50ED000, 0x45A0A800, 0x00000000, 0xC50ED000,
    0x45A0A800, 0x00000000, 0xC4982000, 0x45973000, 0x00000000, 0xC4982000,
    0x00000000, 0x00000000, 0x00000000, 0x4596F000, 0x00000000, 0x423C0000,
    0x45A40000, 0x00000000, 0x423C0000, 0x45A40000, 0x00000000, 0x44D86000,
    0x4596F000, 0x00000000, 0x44D86000, 0x00000000, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_803717DC[0x2D] = {
    0x45973000, 0x00000000, 0xC50ED000, 0x45A0A800, 0x00000000, 0xC50ED000,
    0x45A0A800, 0x00000000, 0xC4982000, 0x45973000, 0x00000000, 0xC4982000,
    0x00000000, 0x00000000, 0x00000000, 0x4596F000, 0x00000000, 0x423C0000,
    0x45A40000, 0x00000000, 0x423C0000, 0x45A40000, 0x00000000, 0x44D86000,
    0x4596F000, 0x00000000, 0x44D86000, 0x00000000, 0x00000000, 0x00000000,
    0xC5847000, 0x00000000, 0x45751000, 0xC526D000, 0x00000000, 0x45751000,
    0xC526D000, 0x00000000, 0x45CC5800, 0xC5847000, 0x00000000, 0x45CC5800,
    0x00000000, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_80371890[0x1E] = {
    0xC5410000, 0x00000000, 0xC63D84CD, 0xC4828666, 0x00000000, 0xC63D84CD,
    0xC4828666, 0x00000000, 0xC5D5E8CD, 0xC5410000, 0x00000000, 0xC5D5E8CD,
    0x00000000, 0x00000000, 0x00000000, 0xC5674000, 0x00000000, 0xC6ABE000,
    0xC4480000, 0x00000000, 0xC6ABE000, 0xC4480000, 0x00000000, 0xC67DAE66,
    0xC5674000, 0x00000000, 0xC67DAE66, 0x00000000, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_80371908[0x2D] = {
    0xC432D99A, 0x00000000, 0xC642DB33, 0x43B90000, 0x00000000, 0xC642DB33,
    0x43B90000, 0x00000000, 0xC5DDE000, 0xC432D99A, 0x00000000, 0xC5DDE000,
    0x00000000, 0x00000000, 0x00000000, 0xC5DAC000, 0x00000000, 0xC653AC00,
    0xC4FF2CCD, 0x00000000, 0xC653AC00, 0xC4FF2CCD, 0x00000000, 0xC604BACD,
    0xC5DAC000, 0x00000000, 0xC604BACD, 0x00000000, 0x00000000, 0x00000000,
    0xC50D1000, 0x00000000, 0xC5B52C00, 0xC51C64CD, 0x00000000, 0xC5BB9F33,
    0xC591B8CD, 0x00000000, 0xC51CE000, 0xC598B000, 0x00000000, 0xC526B333,
    0x00000000, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_803719BC[0xF] = {
    0x455AC000, 0x00000000, 0xC5F3C000, 0x4592E800, 0x00000000, 0xC5F3C000,
    0x4592E800, 0x00000000, 0xC5B86000, 0x455AC000, 0x00000000, 0xC5B86000,
    0x00000000, 0x00000000, 0x00000000,
};
extern const unsigned int lbl_803719F8[0xF] = {
    0x4541C000, 0x00000000, 0xC5610000, 0x45866000, 0x00000000, 0xC5610000,
    0x45866000, 0x00000000, 0xC4FA0000, 0x4541C000, 0x00000000, 0xC4FA0000,
    0x00000000, 0x00000000, 0x00000000,
};

static inline unsigned char JObjMtxIsDirty(JObj *jobj) {
    unsigned char result;

    if (!jobj) {
        __assert("jobj.h", 0x25D, "jobj");
    }
    result = 0;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void JObjSetupMatrix(JObj *jobj) {
    if (!jobj) {
        return;
    }
    if (JObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

static inline void JObjSetMtxDirty(JObj *jobj) {
    if (jobj && !JObjMtxIsDirty(jobj)) {
        fn_802D20AC(jobj);
    }
}

static inline void JObjSetRotationY(JObj *jobj, float y) {
    if (!jobj) {
        __assert("jobj.h", 0x2B8, "jobj");
    }
    if (jobj->flags & 0x20000) {
        __assert("jobj.h", 0x2B9, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotY = y;
    if (!(jobj->flags & 0x2000000)) {
        JObjSetMtxDirty(jobj);
    }
}

static inline void JObjSetScaleX(JObj *jobj, float x) {
    if (!jobj) {
        __assert("jobj.h", 0x325, "jobj");
    }
    jobj->scaleX = x;
    if (!(jobj->flags & 0x2000000)) {
        JObjSetMtxDirty(jobj);
    }
}

static inline void JObjSetScaleZ(JObj *jobj, float z) {
    if (!jobj) {
        __assert("jobj.h", 0x341, "jobj");
    }
    jobj->scaleZ = z;
    if (!(jobj->flags & 0x2000000)) {
        JObjSetMtxDirty(jobj);
    }
}

static inline float (*JObjGetMtxPtr(JObj *jobj))[4] {
    if (!jobj) {
        __assert("jobj.h", 0x47C, "jobj");
    }
    JObjSetupMatrix(jobj);
    return jobj->mtx;
}

struct Vec3f {
    float x, y, z;
};

struct ZoneVolume {
    ZoneVolume(const ZoneDesc *desc, int closed);
    ~ZoneVolume();
    unsigned char Contains(Vec3f *pos);
    void Draw();
    char pad00[0x4];
};

struct clMapEffectParts {
    virtual ~clMapEffectParts() {}
    virtual void Update();
    virtual void Draw();
    virtual void Enable(int on);
    clMapEffectParts() {}
};

namespace {

struct clReverbCtrl : clMapEffectParts {
    ZoneVolume *vol;

    virtual ~clReverbCtrl();
    virtual void Update();
    virtual void Draw();

    clReverbCtrl(const unsigned int *desc, int n) {
        vol = 0;
        if (desc) {
            vol = new ZoneVolume((const ZoneDesc *)desc, n);
        }
    }
};

struct clMoveTex : clMapEffectParts {
    const MoveTexDesc *table;
    JObj **joints;
    int count;

    virtual ~clMoveTex();
    virtual void Update();

    clMoveTex(JObj *root, const MoveTexDesc *t) {
        DebugPrintf(" CreateMapEffect : clMoveTex\n");
        table = t;
        joints = 0;
        count = 0;
        if (table && root) {
            for (;;) {
                if (!table[count].name) {
                    break;
                }
                count++;
            }
            if (count) {
                int i;

                joints = new JObj *[count];
                for (i = 0; i < count; i++) {
                    joints[i] = ResolveJointByName(root, table[i].name);
                }
            }
        }
    }
};

}

#define PART0(sym, size)                                                     \
    struct P_##sym : clMapEffectParts {                                      \
        char pad[size - 4];                                                  \
        P_##sym();                                                           \
    };
#define PART1(sym, size)                                                     \
    struct P_##sym : clMapEffectParts {                                      \
        char pad[size - 4];                                                  \
        P_##sym(JObj *);                                                     \
    };

PART1(fn_8018EDE0, 0x24)
PART1(fn_8018E108, 0x1C)
PART1(fn_8018E510, 0xC)
PART0(fn_801715A0, 0x2974)
PART1(fn_8016FD0C, 0x8)
PART1(fn_8016D920, 0xC)
PART1(fn_80170544, 0x68)
PART0(fn_8016E568, 0x14)
PART0(fn_80170B5C, 0x10)
PART0(fn_8018D3E0, 0x10)
PART0(fn_8018CFC4, 0xC)
PART0(fn_801987C4, 0x20)
PART0(fn_801967F0, 0x24)
PART0(fn_80197D20, 0x34)
PART0(fn_8018A70C, 0x20)
PART0(fn_8016AB58, 0x10)
PART0(fn_8016A1AC, 0xC)
PART1(fn_8016A3D4, 0x10)
PART0(MapWaterEffect_Init, 0x10)
PART0(fn_8016AF3C, 0x18)
PART0(fn_80187878, 0xC)
PART0(fn_8018FEAC, 0xC)
PART0(fn_8018F614, 0x10)
PART0(fn_80187410, 0x18)
PART0(fn_80187BF4, 0xC)
PART1(fn_80228884, 0x1300)
PART1(fn_8022A890, 0x528)
PART0(fn_80229180, 0x14)
PART1(fn_80229768, 0x158)
PART1(fn_80227B98, 0x748)

struct P_fn_8016D2D0 : clMapEffectParts {
    clMapEffectParts *link;
    char pad08[0x1C];

    P_fn_8016D2D0(JObj *);
};

struct P_fn_80171CD0 : clMapEffectParts {
    char pad[0x78];

    P_fn_80171CD0(const char *file, JObj *joint, float a, float b);
};

struct PartsNode {
    int kind;
    int prio;
    clMapEffectParts *parts;
    unsigned char done;
    PartsNode *next;

    PartsNode(int kind, int prio, clMapEffectParts *parts) {
        this->kind = kind;
        this->prio = prio;
        this->parts = parts;
        done = 0;
        next = 0;
    }

    int Append(int kind, int prio, clMapEffectParts *parts) {
        if (parts) {
            if (next) {
                next->Append(kind, prio, parts);
            } else {
                next = new PartsNode(kind, prio, parts);
            }
            return 1;
        }
        return 0;
    }

    ~PartsNode();
    clMapEffectParts *Find(unsigned int kind);
    void Update();
    void Draw(int mask);
    void SetHidden(int mask, unsigned char hide);
};

struct PartsList {
    PartsNode *head;

    PartsList() {
        head = 0;
    }

    ~PartsList();
    int Add(int kind, int prio, clMapEffectParts *parts);
    clMapEffectParts *Find(unsigned int kind);
    void Update();
    void Draw(int mask);
    void SetHidden(int mask, unsigned char hide);
};

struct PartsCtx {
    char pad00[0xC];
    int mode;
};

struct clMapEffect {
    virtual ~clMapEffect() {}
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffect() {}
};

struct clMapEffectDN : clMapEffect {
    PartsList *parts;
    unsigned char done;

    virtual ~clMapEffectDN();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectDN(JObj *root, int arg);
};

struct YIState {
    unsigned char a;
    float x04;
    unsigned char b;
    int x0c;
    unsigned char c;
    float x14;
    unsigned char d;
    float x1c;
    int x20;
    int x24;
    int x28;
    int x2c;

    YIState() {
        x20 = 0;
        x24 = 0;
        x2c = 0;
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        x14 = 0.0f;
        x1c = 0.0f;
    }

    ~YIState() {
        if (a == 1) {
            fn_8016C394(0x3E);
        }
        if (d == 1) {
            fn_8016C394(0x3F);
        }
        if (c == 1) {
            fn_8016C394(0x40);
        }
        if (b == 1) {
            fn_8016C394(0x3B);
        }
    }

    template <int N>
    void UpdateT();

    void Update() {
        UpdateT<0>();
    }
};

struct clMapEffectYI : clMapEffect {
    PartsList *parts;
    YIState *state;

    virtual ~clMapEffectYI();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectYI(JObj *root, int arg);
};

struct clMapEffectRB : clMapEffect {
    PartsList *parts;
    PartsCtx *ctx;
    unsigned char done;

    virtual ~clMapEffectRB();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectRB(JObj *root, int arg);
};

struct clMapEffectKP : clMapEffect {
    PartsList *parts;
    ZoneVolume *zone;
    float x0c;
    JObj *x10;
    float x14;
    unsigned char x18;
    JObj *x1c;
    JObj *x20;
    float x24;
    float x28;
    unsigned char x2c;

    virtual ~clMapEffectKP();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectKP(JObj *root, int arg);
};

struct clMapEffectPC : clMapEffect {
    PartsList *parts;
    PartsCtx *ctx;
    unsigned char done;

    virtual ~clMapEffectPC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectPC(JObj *root, int arg);
};

struct clMapEffectWC : clMapEffect {
    PartsList *parts;
    unsigned char done;

    virtual ~clMapEffectWC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectWC(JObj *root, int arg);
};

struct clMapEffectDK : clMapEffect {
    PartsList *parts;
    int x08;
    int x0c;
    int x10;
    unsigned char done;

    virtual ~clMapEffectDK();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectDK(JObj *root, int arg);
};

struct clMapEffectMR : clMapEffect {
    PartsList *parts;
    unsigned char done;

    virtual ~clMapEffectMR();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectMR(JObj *root, int arg);
};

struct clMapEffectWCC : clMapEffect {
    PartsList *parts;
    unsigned char done;

    virtual ~clMapEffectWCC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectWCC(JObj *root, int arg);
};

struct clMapEffectKPC : clMapEffect {
    unsigned char done;

    virtual ~clMapEffectKPC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectKPC() {
        done = 0;
    }
};

struct clMapEffectPCC : clMapEffect {
    unsigned char done;

    virtual ~clMapEffectPCC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectPCC() {
        done = 0;
    }
};

struct clMapEffectDKC : clMapEffect {
    int wait;
    int volIdx;
    int panIdx;
    unsigned char done;

    virtual ~clMapEffectDKC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectDKC() {
        wait = 0;
        volIdx = 0;
        panIdx = 0;
        done = 0;
        fn_8016B248(0);
        fn_8016B178(2);
        fn_8016B160(0.0f);
        fn_8016B148(10000.0f);
        fn_8016B0F0(0xC0, 0xC0, 0xC0);
    }
};

inline ZoneVolume *NewKPZone() {
    static const unsigned int lbl_80371A34[0x2D] = {
        0xC4B18000, 0x00000000, 0xC52F0000, 0xC4B18000, 0x00000000, 0xC4918000,
        0xC31D0000, 0x00000000, 0xC4918000, 0xC31D0000, 0x00000000, 0xC52F0000,
        0x00000000, 0x00000000, 0x00000000, 0x4417C000, 0x00000000, 0xC544E000,
        0x4417C000, 0x00000000, 0xC4F7A000, 0x4488C000, 0x00000000, 0xC4F7A000,
        0x4488C000, 0x00000000, 0xC544E000, 0x00000000, 0x00000000, 0x00000000,
        0x43490000, 0x00000000, 0x43910000, 0x43490000, 0x00000000, 0x440AC000,
        0x449A6000, 0x00000000, 0x440AC000, 0x449A6000, 0x00000000, 0x43910000,
        0x00000000, 0x00000000, 0x00000000,
    };
    return new ZoneVolume((const ZoneDesc *)lbl_80371A34, 3);
}

#pragma exceptions on

inline clMapEffectWCC::clMapEffectWCC(JObj *root, int arg) {
    parts = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        parts->Add(4, 2, new P_fn_801967F0());
        parts->Add(0, 0, new clMoveTex(root, lbl_80370E58));
    }
}

inline int PartsList::Add(int kind, int prio, clMapEffectParts *parts) {
    if (!parts) {
        return 0;
    }
    if (head) {
        head->Append(kind, prio, parts);
    } else {
        head = new PartsNode(kind, prio, parts);
    }
    return 1;
}


inline clMapEffectDN::clMapEffectDN(JObj *root, int arg) {
    parts = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        parts->Add(0, 0, new clMoveTex(root, lbl_803710A4));
        parts->Add(2, 2, new P_fn_80228884(ResolveJointByName(root, "DN_stadium_DNA_all_joint")));
        parts->Add(4, 2, new P_fn_8022A890(ResolveJointByName(root, "DN_stadium_DNA_all_joint")));
        if (g_gameMode != 2) {
            parts->Add(0x10, 0x24, new P_fn_80229180());
            parts->Add(0x20, 2, new P_fn_80229768(ResolveJointByName(root, "DN_stadium_DNA_all_joint")));
        }
        if (g_longRoundFlag == 1 && g_cupId != 0x10) {
            parts->Add(1, 2, new P_fn_80227B98(ResolveJointByName(root, "DN_stadium_DNA_all_joint")));
            parts->Add(0x10, 2, new P_MapWaterEffect_Init());
            parts->Add(0, 0, new clReverbCtrl(lbl_803719F8, 1));
        } else {
            parts->Add(0, 0, new clReverbCtrl(lbl_803719BC, 1));
        }
    }
    fn_8016B248(0);
    fn_8016B178(2);
    fn_8016B160(1000.0f);
    fn_8016B148(15000.0f);
    fn_8016B0F0(0xB9, 0xFF, 0xFF);
}

inline clMapEffectYI::clMapEffectYI(JObj *root, int arg) {
    parts = 0;
    state = 0;
    parts = new PartsList();
    if (parts) {
        parts->Add(0, 0, new clMoveTex(root, lbl_8037103C));
    }
    if (g_longRoundFlag == 1) {
        parts->Add(0, 0, new clReverbCtrl(lbl_80371908, 3));
    } else {
        parts->Add(0, 0, new clReverbCtrl(lbl_80371890, 2));
    }
    state = new YIState();
}

inline clMapEffectRB::clMapEffectRB(JObj *root, int arg) {
    parts = 0;
    ctx = 0;
    done = 0;
    parts = new PartsList();
    ctx = (PartsCtx *)arg;
    if (parts) {
        parts->Add(1, 1, new P_fn_8018EDE0(root));
        parts->Add(2, 2, new P_fn_8018E108(root));
        parts->Add(4, 0, new P_fn_8018E510(ResolveJointByName(root, "RB_road_eisei_joint")));
        parts->Add(0, 0, new clMoveTex(root, lbl_80370FD0));
        if (!g_longRoundFlag && g_courseVariantIdx == 2) {
            parts->Add(0, 0, new clReverbCtrl(lbl_803717DC, 3));
        } else {
            parts->Add(0, 0, new clReverbCtrl(lbl_80371764, 2));
        }
    }
}

inline clMapEffectKP::clMapEffectKP(JObj *root, int arg) {
    parts = 0;
    zone = 0;
    x0c = 0.0f;
    x10 = 0;
    x14 = 0.0f;
    x18 = 0;
    x1c = 0;
    x20 = 0;
    x24 = 0.0f;
    x28 = 0.0f;
    x2c = 0;
    parts = new PartsList();
    if (parts) {
        clMapEffectParts *a;
        clMapEffectParts *b;

        parts->Add(1, 2, new P_fn_801715A0());
        parts->Add(2, 2, new P_fn_8016FD0C(ResolveJointByName(root, "KP_castle_KP_sekizou_null_joint")));
        parts->Add(4, 2, new P_fn_8016D920(ResolveJointByName(root, "KP_castle_kp04_candle_joint")));
        parts->Add(8, 0x22, new P_fn_80170544(ResolveJointByName(root, "KP_castle_kp021_thunder_joint")));
        parts->Add(0x10, 2, new P_fn_8016D2D0(ResolveJointByName(root, "KP_castle_KP_fb_null_joint")));
        parts->Add(0x20, 2, new P_fn_8016E568());
        switch (g_courseVariantIdx) {
        case 0:
            if (g_longRoundFlag) {
                break;
            } else if (g_gameMode) {
                break;
            }
            break;
        case 1:
            parts->Add(0x100, 2, new P_fn_80170B5C());
            break;
        case 2:
            if (!g_longRoundFlag) {
                parts->Add(0x100, 2, new P_fn_80170B5C());
            } else {
                parts->Add(0x100, 2, new P_fn_80170B5C());
            }
            break;
        }
        parts->Add(0, 0, new clMoveTex(root, lbl_80370EEC));
        if (!g_longRoundFlag) {
            parts->Add(0, 0, new clReverbCtrl(lbl_8037150C, 6));
        } else {
            parts->Add(0, 0, new clReverbCtrl(lbl_80371674, 4));
        }
        a = parts->Find(1);
        b = parts->Find(0x10);
        if (a && b) {
            ((P_fn_8016D2D0 *)b)->link = a;
        }
    }
    x10 = ResolveJointByName(root, "KP_castle_kp_frag_joint");
    x1c = ResolveJointByName(root, "KP_castle_kp01_skydome_joint");
    x20 = ResolveJointByName(root, "KP_castle_kp03_skycloud_joint");
    zone = NewKPZone();
    {
        JObj *j;
        JObj *p;

        p = ResolveJointByName(root, "KP_castle_Ef_M2_06_isekifire_joint");
        for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
            DrawEffect_SpawnWithMatrix(8, JObjGetMtxPtr(j));
        }
    }
    fn_8016B248(0);
    fn_8016B178(0);
    fn_8016B160(65535.0f);
    fn_8016B148(65535.0f);
    fn_8016B0F0(0xFF, 0x7F, 0);
    x0c = 0.0f;
}

inline clMapEffectParts *PartsList::Find(unsigned int kind) {
    return head ? head->Find(kind) : 0;
}

inline clMapEffectParts *PartsNode::Find(unsigned int kind) {
    if (this->kind == kind) {
        return parts;
    }
    return next ? next->Find(kind) : 0;
}

inline clMapEffectPC::clMapEffectPC(JObj *root, int arg) {
    parts = 0;
    ctx = 0;
    parts = new PartsList();
    ctx = (PartsCtx *)arg;
    done = 0;
    if (parts) {
        parts->Add(4, 2, new P_fn_8018D3E0());
        if (!g_longRoundFlag) {
            parts->Add(0, 0, new clReverbCtrl(lbl_8037141C, 2));
        } else {
            parts->Add(8, 1, new P_fn_8018CFC4());
            parts->Add(0, 0, new clReverbCtrl(lbl_80371494, 2));
        }
    }
}

inline clMapEffectWC::clMapEffectWC(JObj *root, int arg) {
    parts = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        parts->Add(1, 2, new P_fn_801987C4());
        parts->Add(4, 2, new P_fn_801967F0());
        if (g_longRoundFlag == 1) {
            parts->Add(2, 4, new P_fn_80197D20());
        }
        parts->Add(0, 0, new clMoveTex(root, lbl_80370E04));
        if (!g_longRoundFlag) {
            parts->Add(0, 0, new clReverbCtrl(lbl_8037123C, 4));
        } else {
            parts->Add(0, 0, new clReverbCtrl(lbl_8037132C, 4));
        }
    }
}

inline clMapEffectDK::clMapEffectDK(JObj *root, int arg) {
    parts = 0;
    x08 = 0;
    x0c = 0;
    x10 = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        if (!g_longRoundFlag) {
            parts->Add(1, 2, new P_fn_8018A70C());
            parts->Add(2, 2, new P_fn_8016AB58());
            parts->Add(4, 2, new P_fn_8016A1AC());
        } else {
            parts->Add(0x100, 0, new P_fn_8016A3D4(ResolveJointByName(root, "DK_jungle_Ef_M2_02_kiri_joint")));
            parts->Add(0, 0, new clReverbCtrl(lbl_8037114C, 4));
        }
        parts->Add(0x10, 2, new P_MapWaterEffect_Init());
        if (g_courseVariantIdx == 1) {
            parts->Add(0x20, 4, new P_fn_8016AF3C());
        }
    }
    switch (g_courseVariantIdx) {
    case 0:
        fn_8016B248(0);
        fn_8016B178(2);
        fn_8016B160(0.0f);
        fn_8016B148(10000.0f);
        fn_8016B0F0(0xC0, 0xC0, 0xC0);
        break;
    case 1:
        fn_8016B248(0);
        fn_8016B178(2);
        fn_8016B160(0.0f);
        fn_8016B148(3000.0f);
        fn_8016B0F0(0xC0, 0xC0, 0xC0);
        break;
    case 2:
        fn_8016B248(0);
        fn_8016B178(2);
        fn_8016B160(0.0f);
        fn_8016B148(10000.0f);
        fn_8016B0F0(0xC0, 0xC0, 0xC0);
        break;
    }
    JObj *j;
    JObj *p;

    p = ResolveJointByName(root, "DK_jungle_Ef_M2_02_fire_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SetFlagsByte(DrawEffect_SpawnWithMatrix(8, JObjGetMtxPtr(j)), 0);
    }
    p = ResolveJointByName(root, "DK_jungle_Ef_M2_02_fire_a_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SetFlagsByte(DrawEffect_SpawnWithMatrix(8, JObjGetMtxPtr(j)), 1);
    }
    p = ResolveJointByName(root, "DK_jungle_Ef_M2_02_fire_b_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SetFlagsByte(DrawEffect_SpawnWithMatrix(8, JObjGetMtxPtr(j)), 2);
    }
    p = ResolveJointByName(root, "DK_jungle_Ef_M2_02_kiri_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SpawnWithMatrix(7, JObjGetMtxPtr(j));
    }
    p = ResolveJointByName(root, "DK_jungle_Ef_M2_08_noroshi_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SpawnWithMatrix(10, JObjGetMtxPtr(j));
    }
}

inline clMapEffectMR::clMapEffectMR(JObj *root, int arg) {
    JObj *j;

    parts = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        switch (g_courseVariantIdx) {
        case 0:
            parts->Add(4, 4, new P_fn_80171CD0("halation.dat", ResolveJointByName(root, "MR_highway_sun_joint"), 1.0f, 1.0f));
            break;
        case 1:
            parts->Add(4, 4, new P_fn_80171CD0("halation_tw.dat", ResolveJointByName(root, "MR_highway_sun_joint"), 1.0f, 1.0f));
            break;
        case 2:
            parts->Add(0x40, 2, new P_fn_80187878());
            break;
        }
        parts->Add(1, 2, new P_fn_8018FEAC());
        parts->Add(2, 2, new P_fn_8018F614());
        parts->Add(0x20, 2, new P_fn_80187410());
        if (g_longRoundFlag == 1) {
            parts->Add(8, 2, new P_fn_8018A70C());
            parts->Add(0x10, 2, new P_fn_80187BF4());
        }
        parts->Add(0, 0, new clMoveTex(root, lbl_80370D2C));
        parts->Add(0, 0, new clReverbCtrl(lbl_803710D4, 2));
    }
    j = ResolveJointByName(root, "MR_highway_volcano_joint");
    if (j) {
        DrawEffect_SpawnWithMatrix(0xB, JObjGetMtxPtr(j));
    }
}

inline clMapEffectMR::~clMapEffectMR() {
    if (parts) {
        delete parts;
    }
    if (done) {
        fn_8016C394(0x24);
    }
}

inline PartsList::~PartsList() {
    if (head) {
        delete head;
    }
}

inline PartsNode::~PartsNode() {
    if (next) {
        delete next;
    }
    delete parts;
}

inline void clMapEffectMR::Update() {
    if (parts) {
        parts->Update();
    }
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x24);
        }
    } else if (done == 1) {
        fn_8016C3C8(0x24, 1);
        done = 0;
    }
}

inline void PartsList::Update() {
    if (head) {
        head->Update();
    }
}

inline void PartsNode::Update() {
    done = 0;
    if (!(prio & 0x40)) {
        parts->Update();
        done = 1;
    }
    if (next) {
        next->Update();
    }
}

inline void clMapEffectMR::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline void PartsList::Draw(int mask) {
    if (head) {
        head->Draw(mask & 7);
    }
}

inline void PartsNode::Draw(int mask) {
    if (done && (prio & mask)) {
        if (prio & 0x20) {
            fn_8016B0A0();
            parts->Draw();
            fn_8016B0C4();
        } else {
            parts->Draw();
        }
        done = 0;
    }
    if (next) {
        next->Draw(mask);
    }
}

inline clMapEffectDK::~clMapEffectDK() {
    if (parts) {
        delete parts;
    }
    fn_8016B190();
    if (fn_8016C360(0x2C)) {
        fn_8016C394(0x2C);
    }
}

inline void clMapEffectDK::Update() {
    if (parts) {
        parts->Update();
    }
    if (x08 > 0) {
        x08--;
    } else if (!fn_8016C360(0x27)) {
        unsigned char vol;
        int pan;

        x08 = (int)(1000.0f * lbl_80495994[x0c]) + 60;
        vol = (int)(64.0f * lbl_80495994[x0c]) + 64;
        pan = (int)(127.0f * lbl_80495A94[x10]);
        SoundMgr_PlaySE(0x27);
        fn_8016C1B0(0x27, vol);
        fn_8016C168(0x27, pan);
        if (++x0c >= 0x40) {
            x0c = 0;
        }
        if (++x10 >= 0x30) {
            x10 = 0;
        }
    }
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x2C);
            done = 1;
        }
    } else if (done == 1) {
        done = fn_8016C3C8(0x2C, 1);
        done = 0;
    }
}

inline void clMapEffectDK::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectWC::~clMapEffectWC() {
    if (parts) {
        delete parts;
    }
    if (fn_8016C360(0x2E)) {
        fn_8016C394(0x2E);
    }
    if (fn_8016C360(0x2F)) {
        fn_8016C394(0x2F);
    }
}

inline void clMapEffectWC::Update() {
    if (parts) {
        parts->Update();
    }
    if (g_gameMode == 1) {
        if (!done) {
            done = SoundMgr_PlaySE(0x2F);
        }
    } else if (!done) {
        if (!IsRaceStarted()) {
            done = SoundMgr_PlaySE(0x2E);
        }
    } else if (IsRaceStarted() && fn_8016C360(0x2E)) {
        fn_8016C3C8(0x2E, 2);
        done = 0;
    }
}

inline void clMapEffectWC::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectPC::~clMapEffectPC() {
    if (parts) {
        delete parts;
    }
    if (fn_8016C360(0x31)) {
        fn_8016C394(0x31);
    }
    if (fn_8016C360(0x32)) {
        fn_8016C394(0x32);
    }
}

inline void clMapEffectPC::Update() {
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x31);
            done = 1;
        }
    } else if (done == 1) {
        fn_8016C3C8(0x31, 1);
        done = 0;
    }
    if (ctx) {
        if (ctx->mode == 0) {
            if (!fn_8016C360(0x32)) {
                SoundMgr_PlaySE(0x32);
            }
        } else if (fn_8016C360(0x32) == 1) {
            fn_8016C394(0x32);
        }
    }
    if (parts) {
        if (ctx) {
            if (ctx->mode == 1) {
                parts->SetHidden(7, 0);
                parts->SetHidden(8, 1);
            } else if (ctx->mode == 0) {
                parts->SetHidden(7, 1);
                parts->SetHidden(8, 0);
            } else {
                parts->SetHidden(0xF, 0);
            }
        }
        parts->Update();
    }
}

inline void PartsList::SetHidden(int mask, unsigned char hide) {
    if (head) {
        head->SetHidden(mask, hide);
    }
}

inline void PartsNode::SetHidden(int mask, unsigned char hide) {
    if (mask & kind) {
        if (hide) {
            if (!(prio & 0x40)) {
                parts->Enable(0);
                prio = prio | 0x40;
            }
        } else if (prio & 0x40) {
            parts->Enable(1);
            prio = prio & ~0x40;
        }
    }
    if (next) {
        next->SetHidden(mask, hide);
    }
}

inline void clMapEffectPC::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectKP::~clMapEffectKP() {
    if (parts) {
        delete parts;
    }
    if (zone) {
        delete zone;
    }
    fn_8016B190();
    if (x18) {
        fn_8016C394(0x33);
    }
    if (x2c) {
        fn_8016C394(0x36);
    }
}

inline void clMapEffectKP::Update() {
    if (parts) {
        parts->Update();
    }
    if (x10) {
        float s;
        float sx;
        JObj *j;

        x14 += 30.0f;
        if (x14 >= 360.0f) {
            x14 = 0.0f;
        }
        s = LUT_Sin12Bit(x14);
        sx = 1.0f - 0.2f * (s < 0.0f ? -s : s);
        JObj *p = x10;
        for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
            JObjSetScaleZ(j, s);
            JObjSetScaleX(j, sx);
        }
    }
    if (x1c) {
        x24 += 0.0008726644446142018f;
        if (x24 >= 6.283184051513672f) {
            x24 -= 6.283184051513672f;
        }
        JObjSetRotationY(x1c, x24);
    }
    if (x20) {
        x28 += 0.0005817763158120215f;
        if (x28 >= 6.283184051513672f) {
            x28 -= 6.283184051513672f;
        }
        JObjSetRotationY(x20, x28);
    }
    if (GetCourseScene3D()) {
        Vec3f pos;

        CObj_LoadProjMatrix(GetCourseScene3D(), &pos);
        if (zone->Contains(&pos)) {
            x0c += 0.01666666753590107f;
        } else {
            x0c -= 0.01666666753590107f;
        }
        x0c = x0c < 0.0f ? 0.0f : (x0c > 1.0f ? 1.0f : x0c);
        if (x0c > 0.0f) {
            fn_8016B178(2);
        } else {
            fn_8016B178(0);
        }
        fn_8016B160(3000.0f - 2900.0f * x0c);
        fn_8016B148(10000.0f - 3000.0f * x0c);
        if (x0c > 0.0f) {
            int vol = (int)(127.0f * x0c);

            if (!x18) {
                x18 = SoundMgr_PlaySE(0x33);
            }
            fn_8016C1B0(0x33, vol);
        } else if (x18) {
            fn_8016C394(0x33);
            x18 = 0;
        }
    }
    if (!IsRaceStarted()) {
        if (!x2c) {
            x2c = SoundMgr_PlaySE(0x36);
            x2c = 1;
        }
    } else if (x2c == 1) {
        x2c = fn_8016C3C8(0x36, 1);
        x2c = 0;
    }
}

inline void clMapEffectKP::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectRB::~clMapEffectRB() {
    if (parts) {
        delete parts;
    }
}

inline void clMapEffectRB::Update() {
    if (parts) {
        if (ctx) {
            if (ctx->mode == 0) {
                parts->SetHidden(5, 0);
                parts->SetHidden(2, 1);
            } else {
                parts->SetHidden(5, 1);
                parts->SetHidden(2, 0);
            }
        }
        parts->Update();
    }
    if (!done) {
        if (!IsRaceStarted()) {
            done = SoundMgr_PlaySE(0x39);
        }
    } else if (IsRaceStarted() && fn_8016C360(0x39)) {
        fn_8016C3C8(0x39, 2);
        done = 0;
    }
}

inline void clMapEffectRB::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectYI::~clMapEffectYI() {
    if (parts) {
        delete parts;
    }
    if (state) {
        delete state;
    }
}

inline void clMapEffectYI::Update() {
    if (parts) {
        parts->Update();
    }
    if (state) {
        state->Update();
    }
}

inline void clMapEffectYI::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clReverbCtrl::~clReverbCtrl() {
    if (vol) {
        fn_80193134(0);
        delete vol;
        vol = 0;
    }
}

inline void clReverbCtrl::Update() {
    if (GetCourseScene3D() && vol) {
        Vec3f pos;

        CObj_LoadProjMatrix(GetCourseScene3D(), &pos);
        fn_80193134(vol->Contains(&pos));
    }
}

inline void clReverbCtrl::Draw() {
    if (vol) {
        vol->Draw();
    }
}

inline clMapEffectDN::~clMapEffectDN() {
    fn_8016B190();
    if (parts) {
        delete parts;
    }
    if (done == 1) {
        done = fn_8016C394(0x42);
    }
    if (fn_8016C360(0x3C) == 1) {
        fn_8016C394(0x3C);
    }
}

inline void clMapEffectDN::Update() {
    if (parts) {
        parts->Update();
    }
    if (!IsRaceStarted()) {
        if (!done) {
            SoundMgr_PlaySE(0x42);
            fn_8016C1F8(0x42, 0.7300000190734863f);
            done = 1;
        }
    } else if (done == 1) {
        fn_8016C3C8(0x42, 1);
        done = 0;
    }
}

inline void clMapEffectDN::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMoveTex::~clMoveTex() {
    if (joints) {
        delete[] joints;
    }
    DebugPrintf(" DeleteMapEffect : clMoveTex\n");
}

inline void clMoveTex::Update() {
    int i;

    for (i = 0; i < count; i++) {
        if (joints[i]) {
            fn_80182E18(joints[i], table[i].u, table[i].v);
        }
    }
}

inline clMapEffectWCC::~clMapEffectWCC() {
    if (parts) {
        delete parts;
    }
    if (fn_8016C360(0x2F)) {
        fn_8016C394(0x2F);
    }
}

inline void clMapEffectWCC::Update() {
    if (parts) {
        parts->Update();
    }
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x2F);
        }
    } else if (done == 1) {
        done = 0;
        fn_8016C3C8(0x2F, 1);
    }
}

inline void clMapEffectWCC::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectKPC::~clMapEffectKPC() {
    if (done) {
        fn_8016C394(0x36);
    }
}

inline void clMapEffectKPC::Update() {
    if (!IsRaceStarted()) {
        if (!done) {
            SoundMgr_PlaySE(0x36);
            done = 1;
        }
    } else if (done == 1) {
        fn_8016C3C8(0x36, 1);
        done = 0;
    }
}

inline void clMapEffectKPC::Draw(int mask) {
}

inline clMapEffectPCC::~clMapEffectPCC() {
    if (fn_8016C360(0x32)) {
        fn_8016C394(0x32);
    }
}

inline void clMapEffectPCC::Update() {
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x32);
        }
    } else if (done == 1) {
        done = 0;
        fn_8016C3C8(0x32, 1);
    }
}

inline void clMapEffectPCC::Draw(int mask) {
}

inline clMapEffectDKC::~clMapEffectDKC() {
    fn_8016B190();
    if (done) {
        fn_8016C394(0x2C);
    }
}

inline void clMapEffectDKC::Update() {
    if (!IsRaceStarted()) {
        if (wait > 0) {
            wait--;
        } else if (!fn_8016C360(0x27)) {
            unsigned char vol;
            int pan;

            wait = (int)(1000.0f * lbl_80495994[volIdx]) + 60;
            vol = (int)(64.0f * lbl_80495994[volIdx]) + 64;
            pan = (int)(127.0f * lbl_80495A94[panIdx]);
            SoundMgr_PlaySE(0x27);
            fn_8016C1B0(0x27, vol);
            fn_8016C168(0x27, pan);
            if (++volIdx >= 0x40) {
                volIdx = 0;
            }
            if (++panIdx >= 0x30) {
                panIdx = 0;
            }
        }
        if (!done) {
            done = SoundMgr_PlaySE(0x2C);
        }
    } else if (done == 1) {
        done = 0;
        fn_8016C3C8(0x2C, 1);
    }
}


static inline unsigned char InQuad(const float *q, const Vec3f *p) {
    if (((q[2] - q[0]) * (p->z - q[1]) - (q[3] - q[1]) * (p->x - q[0]) <= 0.0f) == 0) {
        return 0;
    }
    if (((q[4] - q[2]) * (p->z - q[3]) - (q[5] - q[3]) * (p->x - q[2]) <= 0.0f) == 0) {
        return 0;
    }
    if (((q[6] - q[4]) * (p->z - q[5]) - (q[7] - q[5]) * (p->x - q[4]) <= 0.0f) == 0) {
        return 0;
    }
    if (((q[0] - q[6]) * (p->z - q[7]) - (q[1] - q[7]) * (p->x - q[6]) <= 0.0f) == 0) {
        return 0;
    }
    return 1;
}


extern "C" clMapEffect *fn_801752C0(JObj *root, int arg) {
    if (!root) {
        return 0;
    }
    switch (g_cupId) {
    case 1:
        return new clMapEffectMR(root, arg);
    case 2:
        return new clMapEffectDK(root, arg);
    case 3:
        return new clMapEffectWC(root, arg);
    case 4:
        return new clMapEffectPC(root, arg);
    case 5:
        return new clMapEffectKP(root, arg);
    case 6:
        return new clMapEffectRB(root, arg);
    case 7:
        return new clMapEffectYI(root, arg);
    case 8:
        return new clMapEffectDN(root, arg);
    case 10:
        return new clMapEffectDKC();
    case 11:
        return new clMapEffectWCC(root, arg);
    case 12:
        return new clMapEffectPCC();
    case 13:
        return new clMapEffectKPC();
    case 14:
        return new clMapEffectRB(root, arg);
    case 15:
        return new clMapEffectYI(root, arg);
    case 16:
        return new clMapEffectDN(root, arg);
    }
    return 0;
}

inline void clMapEffectDKC::Draw(int mask) {
}

template <int N>
inline void YIState::UpdateT() {
    Vec3f pos;

    if (!IsRaceStarted()) {
        if (!a) {
            SoundMgr_PlaySE(0x3E);
            a = 1;
            x04 = 1.0f;
        }
    } else if (a == 1) {
        x04 -= 0.003000000026077032f;
        fn_8016C1F8(0x3E, x04);
        if (x04 <= 0.0f) {
            a = 0;
            fn_8016C394(0x3E);
        }
    }
    CObj_LoadProjMatrix(GetCourseScene3D(), &pos);
    if (!g_longRoundFlag) {
        if (InQuad((const float *)lbl_80370C78, &pos) == 1) {
            if (++x20 >= 0x78) {
                x20 = 0;
            }
            if (x20 == 0x1A) {
                SoundMgr_PlaySE(0x3B);
            }
        }
    } else {
        if (InQuad((const float *)lbl_80370CB8, &pos) == 1) {
            if (!c) {
                SoundMgr_PlaySE(0x40);
                c = 1;
            } else if (x14 < 1.0f) {
                x14 += 0.004999999888241291f;
                if (x14 >= 1.0f) {
                    x14 = 1.0f;
                }
                fn_8016C1F8(0x40, x14);
            }
        } else if (c == 1) {
            x14 -= 0.003000000026077032f;
            fn_8016C1F8(0x40, x14);
            if (x14 <= 0.0f) {
                c = 0;
                fn_8016C394(0x40);
            }
        }
        if (InQuad((const float *)lbl_80370C98, &pos) == 1) {
            x24++;
            if (x24 >= 0x168) {
                fn_8016C394(0x3F);
                d = 0;
                x24 = 0;
            }
            if (x24 > 0x96) {
                if (!d) {
                    SoundMgr_PlaySE(0x3F);
                    d = 1;
                    x1c = 1.0f;
                } else if (x1c < 1.0f) {
                    x1c += 0.004999999888241291f;
                    if (x1c >= 1.0f) {
                        x1c = 1.0f;
                    }
                    fn_8016C1F8(0x3F, x1c);
                }
            }
        } else if (d == 1) {
            x1c -= 0.003000000026077032f;
            fn_8016C1F8(0x3F, x1c);
            if (x1c <= 0.0f) {
                d = 0;
                fn_8016C394(0x3F);
            }
        }
    }
}

#pragma exceptions reset
