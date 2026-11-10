#ifndef GAME_MAPEFFECT_PRIVATE_H
#define GAME_MAPEFFECT_PRIVATE_H

#pragma readonly_strings on

struct ZoneDesc;

#include "game/types/JObj.h"

#include "game/types/MoveTexDesc.h"

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
void HSD_JObjSetMtxDirtySub(JObj *);
extern const float lbl_80495994[];
extern const float lbl_80495A94[];
}

#ifdef MAPEFFECT_DEFINE_DATA
extern const unsigned int mapeffect_rodata_80370870[0x102] = {
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
extern const char mapeffect_rodata_80370DE8[0x1C] = "WC_dcity_wc_neon_rc_joint";
extern const MoveTexDesc lbl_80370E04[7] = {
    {lbl_80370D5C, 0.0f, 0.014999999664723873f},
    {lbl_80370D78, 0.0f, 0.014999999664723873f},
    {lbl_80370D94, 0.0f, 0.014999999664723873f},
    {lbl_80370DB0, 0.0f, 0.014999999664723873f},
    {lbl_80370DCC, 0.0f, 0.014999999664723873f},
    {mapeffect_rodata_80370DE8, 0.0f, 0.014999999664723873f},
    {0, 0.0f, 0.0f},
};
extern const MoveTexDesc mapeffect_rodata_80370E58[7] = {
    {lbl_80370D5C, 0.0f, 0.014999999664723873f},
    {lbl_80370D78, 0.0f, 0.014999999664723873f},
    {lbl_80370D94, 0.0f, 0.014999999664723873f},
    {lbl_80370DB0, 0.0f, 0.014999999664723873f},
    {lbl_80370DCC, 0.0f, 0.014999999664723873f},
    {mapeffect_rodata_80370DE8, 0.0f, 0.014999999664723873f},
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
extern const unsigned int mapeffect_rodata_8037141C[0x1E] = {
    0xC517E5E2, 0x42ADF3A0, 0x43691D98, 0xC517D3FA, 0x42ABE153, 0xC3191FD9,
    0xC44F2268, 0x4293FE2F, 0xC3191F2B, 0xC44F225E, 0x429401CF, 0x43691E49,
    0x00000004, 0x00000000, 0x00000000, 0xC5491A14, 0x43960065, 0xC5D32564,
    0xC52A9A24, 0x43960016, 0xC5BAB927, 0xC550297A, 0x4395FA95, 0xC59F2FC7,
    0xC58C8FAD, 0x439605D0, 0xC5A40718, 0x00000004, 0x00000000, 0x00000000,
};
extern const unsigned int mapeffect_rodata_80371494[0x1E] = {
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

#else
extern const unsigned int mapeffect_rodata_80370870[0x102];
extern const unsigned int lbl_80370C78[0x8];
extern const unsigned int lbl_80370C98[0x8];
extern const unsigned int lbl_80370CB8[0x8];
extern const char lbl_80370CD8[0x1C];
extern const char lbl_80370CF4[0x1C];
extern const char lbl_80370D10[0x1C];
extern const MoveTexDesc lbl_80370D2C[4];
extern const char lbl_80370D5C[0x1C];
extern const char lbl_80370D78[0x1C];
extern const char lbl_80370D94[0x1C];
extern const char lbl_80370DB0[0x1C];
extern const char lbl_80370DCC[0x1C];
extern const char mapeffect_rodata_80370DE8[0x1C];
extern const MoveTexDesc lbl_80370E04[7];
extern const MoveTexDesc mapeffect_rodata_80370E58[7];
extern const char lbl_80370EAC[0x20];
extern const char lbl_80370ECC[0x20];
extern const MoveTexDesc lbl_80370EEC[3];
extern const char lbl_80370F10[0x18];
extern const char lbl_80370F28[0x18];
extern const char lbl_80370F40[0x18];
extern const char lbl_80370F58[0x18];
extern const char lbl_80370F70[0x18];
extern const char lbl_80370F88[0x18];
extern const char lbl_80370FA0[0x18];
extern const char lbl_80370FB8[0x18];
extern const MoveTexDesc lbl_80370FD0[9];
extern const MoveTexDesc lbl_8037103C[1];
extern const char lbl_80371048[0x1C];
extern const char lbl_80371064[0x20];
extern const char lbl_80371084[0x20];
extern const MoveTexDesc lbl_803710A4[4];
extern const unsigned int lbl_803710D4[0x1E];
extern const unsigned int lbl_8037114C[0x3C];
extern const unsigned int lbl_8037123C[0x3C];
extern const unsigned int lbl_8037132C[0x3C];
extern const unsigned int mapeffect_rodata_8037141C[0x1E];
extern const unsigned int mapeffect_rodata_80371494[0x1E];
extern const unsigned int lbl_8037150C[0x5A];
extern const unsigned int lbl_80371674[0x3C];
extern const unsigned int lbl_80371764[0x1E];
extern const unsigned int lbl_803717DC[0x2D];
extern const unsigned int lbl_80371890[0x1E];
extern const unsigned int lbl_80371908[0x2D];
extern const unsigned int lbl_803719BC[0xF];
extern const unsigned int lbl_803719F8[0xF];

#endif

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
        HSD_JObjSetMtxDirtySub(jobj);
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

#include "game/types/Vec3f.h"

#include "game/types/ZoneVolume.h"

#include "game/types/clMapEffectParts.h"

// Named namespace gives vtable references external linkage across the TU split.
namespace MapEffectPrivate {

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
using namespace MapEffectPrivate;

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

#include "game/types/P_fn_80171CD0.h"

#include "game/types/PartsNode.h"

#include "game/types/PartsList.h"

#include "game/types/PartsCtx.h"

#include "game/types/clMapEffect.h"

#include "game/types/clMapEffectDN.h"

#include "game/types/YIState.h"

#include "game/types/clMapEffectYI.h"

#include "game/types/clMapEffectRB.h"

#include "game/types/clMapEffectKP.h"

#include "game/types/clMapEffectPC.h"

#include "game/types/clMapEffectWC.h"

#include "game/types/clMapEffectDK.h"

#include "game/types/clMapEffectMR.h"

#include "game/types/clMapEffectWCC.h"

#include "game/types/clMapEffectKPC.h"

#include "game/types/clMapEffectPCC.h"

#include "game/types/clMapEffectDKC.h"

inline ZoneVolume *NewKPZone() {
    static const unsigned int mapeffect_rodata_80371A34[0x2D] = {
        0xC4B18000, 0x00000000, 0xC52F0000, 0xC4B18000, 0x00000000, 0xC4918000,
        0xC31D0000, 0x00000000, 0xC4918000, 0xC31D0000, 0x00000000, 0xC52F0000,
        0x00000000, 0x00000000, 0x00000000, 0x4417C000, 0x00000000, 0xC544E000,
        0x4417C000, 0x00000000, 0xC4F7A000, 0x4488C000, 0x00000000, 0xC4F7A000,
        0x4488C000, 0x00000000, 0xC544E000, 0x00000000, 0x00000000, 0x00000000,
        0x43490000, 0x00000000, 0x43910000, 0x43490000, 0x00000000, 0x440AC000,
        0x449A6000, 0x00000000, 0x440AC000, 0x449A6000, 0x00000000, 0x43910000,
        0x00000000, 0x00000000, 0x00000000,
    };
    return new ZoneVolume((const ZoneDesc *)mapeffect_rodata_80371A34, 3);
}


#endif
