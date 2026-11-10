#include "game/types/c_region.h"
C_REGION_BEGIN
/* 18 TUs merged by tools/merge_tus.py, .text 0x801b7ef8..0x801ba034.
 * Each section is the preprocessed original TU with its names suffixed _pN
 * (tools/extab_user_renames.json maps the symbols back). */
/* ==== .bss pool: countdown sprites, used through the section anchor by fn_801B7EF8 and fn_801B9928 ==== */
/* defined in C++ mode: a C++ TU lays .bss out in definition order, a C TU in first-use order */
#include "game/types/size_t.h"
C_REGION_END
#pragma cplusplus on
extern "C" {
void *lbl_80679280[3];
void *lbl_8067928C[4];
unsigned short *lbl_8067929C[5];
}
#pragma cplusplus reset
C_REGION_BEGIN

/* ==== game/fn_801B7EF8.c (0x801b7ef8) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
typedef struct CountdownSprites_p0 {
void *digits_p0[3];
void *transitions_p0[4];
unsigned short *glyphs_p0[5];
} CountdownSprites_p0;
extern const float lbl_806D9898_p0;
extern const double lbl_806D98A0_p0;
extern signed char lbl_806D181C_p0, lbl_806D181D_p0, lbl_806D181E_p0;
extern float lbl_806D1838_p0, lbl_806D183C_p0;
extern double modf_p0(double, double *);
extern void Sprite_SetAnimTime_p0(void *, float);

#pragma exceptions on

int fn_801B7EF8(void) {
double integral_p0;
double phase_p0;
int digit_p0;
if (lbl_806D183C_p0 < 0.0f) return 0;
if (lbl_806D1838_p0 != lbl_806D183C_p0) {
digit_p0 = (int)lbl_806D183C_p0;
if ((float)digit_p0 >= 10.0f) {
lbl_806D181C_p0 = 0;
*lbl_8067929C[1] = 0x1842 + digit_p0 / 10;
*lbl_8067929C[0] = 0x1842 + digit_p0 % 10;
} else if ((float)digit_p0 >= lbl_806D9898_p0) {
lbl_806D181C_p0 = 1;
*lbl_8067929C[2] = 0x1842 + digit_p0 % 10;
} else {
lbl_806D181C_p0 = 2;
*lbl_8067929C[4] = 0x184C + digit_p0 % 10;
}
phase_p0 = modf_p0(lbl_806D183C_p0, &integral_p0);
if ((signed char)integral_p0 != lbl_806D181E_p0) {
if ((signed char)integral_p0 >= 6) {
if (lbl_806D181E_p0 < -1) lbl_806D181D_p0 = 0;
else lbl_806D181D_p0 = 1;
} else {
if (lbl_806D181E_p0 >= 6) lbl_806D181D_p0 = 2;
else lbl_806D181D_p0 = 3;
}
lbl_806D181E_p0 = (signed char)integral_p0;
}
phase_p0 = lbl_806D98A0_p0 - phase_p0;
Sprite_SetAnimTime_p0(lbl_80679280[lbl_806D181C_p0], (float)phase_p0);
Sprite_SetAnimTime_p0(lbl_8067928C[lbl_806D181D_p0], (float)phase_p0);
lbl_806D1838_p0 = lbl_806D183C_p0;
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/SetScreenBrightness.c (0x801b8154) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
extern float lbl_806D9890_p1, lbl_806D98B0_p1, lbl_806D98B4_p1, lbl_806D98B8_p1, lbl_806D9898_p1, lbl_806D98BC_p1, lbl_806D98C0_p1, lbl_806D98C4_p1, lbl_806D98C8_p1, lbl_806D98CC_p1, lbl_806D98D0_p1, lbl_806D98D4_p1, lbl_806D98D8_p1, lbl_806D98DC_p1, lbl_806D98E0_p1, lbl_806D98E4_p1;
extern signed char lbl_806D184E_p1, lbl_806D181C_p1, lbl_806D181D_p1, lbl_806D181E_p1;
extern float lbl_806D1838_p1, lbl_806D183C_p1;
extern void SoundMgr_Play_p1(int);

#pragma exceptions on

int SetScreenBrightness(float value_p1) {
unsigned char crossed_p1;
if (lbl_806D98B0_p1 <= value_p1) return 0;
if (value_p1 < 0.0f || lbl_806D98B4_p1 < value_p1) lbl_806D184E_p1 = 6;
if (value_p1 < 0.0f) {
lbl_806D181C_p1 = -1;
lbl_806D181D_p1 = -1;
lbl_806D181E_p1 = -1;
lbl_806D1838_p1 = lbl_806D98B8_p1;
lbl_806D183C_p1 = lbl_806D98B8_p1;
return 1;
}
crossed_p1 = 0;
switch (lbl_806D184E_p1) {
case 6:
if (lbl_806D9898_p1 >= value_p1 && value_p1 >= lbl_806D98BC_p1) crossed_p1 = 1;
break;
case 5:
if (lbl_806D98C0_p1 >= value_p1 && value_p1 >= lbl_806D98C4_p1) crossed_p1 = 1;
break;
case 4:
if (lbl_806D98C8_p1 >= value_p1 && value_p1 >= lbl_806D98CC_p1) crossed_p1 = 1;
break;
case 3:
if (lbl_806D98D0_p1 >= value_p1 && value_p1 >= lbl_806D98D4_p1) crossed_p1 = 1;
break;
case 2:
if (lbl_806D98D8_p1 >= value_p1 && value_p1 >= lbl_806D98DC_p1) crossed_p1 = 1;
break;
case 1:
if (lbl_806D98E0_p1 >= value_p1 && value_p1 >= lbl_806D98E4_p1) crossed_p1 = 1;
break;
}
if (crossed_p1) {
SoundMgr_Play_p1(3);
--lbl_806D184E_p1;
}
lbl_806D183C_p1 = value_p1;
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/InitBGM.c (0x801b833c) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
extern unsigned char lbl_806D17F4_p2;
extern void fn_801908F0_p2(void);
extern void ClSound_PlayBgmStream_p2(int stream_p2, int flag_p2);
extern unsigned char fn_801932F8_p2(void);
extern void clStream_setVolume_p2(int stream_p2, unsigned char vol_p2);

#pragma exceptions on

int InitBGM(void) {
if (lbl_806D17F4_p2 != 0) {
return 0;
}
fn_801908F0_p2();
ClSound_PlayBgmStream_p2(1, 0);
clStream_setVolume_p2(1, fn_801932F8_p2());
lbl_806D17F4_p2 = 1;
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B8398.c (0x801b8398) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
extern void *lbl_806D180C_p3;
extern signed char lbl_806D1818_p3;
extern unsigned char lbl_806D1819_p3;
extern void Sprite_SetupAnim_p3(void *sprite_p3, int anim_p3, int loop_p3, int arg_p3);
extern void Sprite_SetAnimParam_p3(void *sprite_p3, int id_p3, int value_p3);
extern void fn_801A0550_p3(void *sprite_p3);
extern void fn_8019FF6C_p3(void *sprite_p3, int arg_p3);
int fn_801B8398(int value_p3) {
void *sprite_p3 = lbl_806D180C_p3;
if (sprite_p3 == 0) {
return 0;
}
if (lbl_806D1818_p3 <= 1) {
Sprite_SetupAnim_p3(sprite_p3, 0x1B, 0, 0);
Sprite_SetAnimParam_p3(lbl_806D180C_p3, 0x1D3E, value_p3);
fn_801A0550_p3(lbl_806D180C_p3);
} else {
Sprite_SetupAnim_p3(sprite_p3, 0x13, 1, 0);
}
lbl_806D1818_p3 = 4;
return 1;
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B8434.c (0x801b8434) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
extern void *lbl_806D180C_p4;
extern signed char lbl_806D1818_p4;
extern unsigned char lbl_806D1819_p4;
extern void Sprite_SetupAnim_p4(void *sprite_p4, int anim_p4, int loop_p4, int arg_p4);
extern void Sprite_SetAnimParam_p4(void *sprite_p4, int id_p4, int value_p4);
extern void fn_801A0550_p4(void *sprite_p4);
extern void fn_8019FF6C_p4(void *sprite_p4, int arg_p4);
int fn_801B8434(void) {
void *sprite_p4 = lbl_806D180C_p4;
if (sprite_p4 == 0) {
return 0;
}
if (lbl_806D1818_p4 != 3) {
return 0;
}
if (lbl_806D1819_p4) {
Sprite_SetupAnim_p4(sprite_p4, 0x39, 1, 0);
} else {
Sprite_SetupAnim_p4(sprite_p4, 0x37, 1, 0);
}
lbl_806D1818_p4 = 4;
return 1;
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B84B4.c (0x801b84b4) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
extern void *lbl_806D180C_p5;
extern signed char lbl_806D1818_p5;
extern unsigned char lbl_806D1819_p5;
extern void Sprite_SetupAnim_p5(void *sprite_p5, int anim_p5, int loop_p5, int arg_p5);
extern void Sprite_SetAnimParam_p5(void *sprite_p5, int id_p5, int value_p5);
extern void fn_801A0550_p5(void *sprite_p5);
extern void fn_8019FF6C_p5(void *sprite_p5, int arg_p5);
int fn_801B84B4(int value_p5) {
void *sprite_p5 = lbl_806D180C_p5;
if (sprite_p5 == 0) {
return 0;
}
if (lbl_806D1818_p5 != 1) {
return 0;
}
Sprite_SetupAnim_p5(sprite_p5, 0x167, 0, 0);
Sprite_SetAnimParam_p5(lbl_806D180C_p5, 0x1D3E, value_p5);
fn_801A0550_p5(lbl_806D180C_p5);
fn_8019FF6C_p5(lbl_806D180C_p5, 1);
return 1;
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B8540.c (0x801b8540) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
extern void *lbl_806D180C_p6;
extern int lbl_806D1810_p6;
extern int lbl_806D1814_p6;
extern signed char lbl_806D1818_p6;
extern void Sprite_SetupAnim_p6(void *sprite_p6, int anim_p6, int loop_p6, int arg_p6);
extern void Sprite_SetAnimParam_p6(void *sprite_p6, int id_p6, int value_p6);
extern void fn_801A0550_p6(void *sprite_p6);
int fn_801B8540(int value_p6) {
void *sprite_p6 = lbl_806D180C_p6;
if (sprite_p6 == 0) {
return 0;
}
if (lbl_806D1818_p6 != 1) {
return 0;
}
lbl_806D1810_p6 = 0;
lbl_806D1818_p6 = 2;
if (lbl_806D1814_p6 == 0xD) {
Sprite_SetupAnim_p6(sprite_p6, 0x1A, 0, 0);
Sprite_SetAnimParam_p6(lbl_806D180C_p6, 0x1D3E, value_p6);
fn_801A0550_p6(lbl_806D180C_p6);
}
return 1;
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B85DC.cpp (0x801b85dc) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
C_REGION_END
#pragma cplusplus on
class Sprite_p7 {
public:
Sprite_p7(int id_p7, int a_p7, int b_p7);
char pad0_p7[0xC];
float x_p7;
float y_p7;
char pad14_p7[4];
float rot_p7;
char pad1C_p7[0x30 - 0x1C];
void SetPos_p7(float px_p7, float py_p7) { x_p7 = px_p7; y_p7 = py_p7; }
void SetRot_p7(float r_p7) { rot_p7 = r_p7; }
};
extern "C"{
extern Sprite_p7 *lbl_806D180C_p7;
extern int lbl_806D1810_p7;
extern int lbl_806D1814_p7;
extern unsigned char lbl_806D1818_p7;
extern unsigned char lbl_806D1819_p7;
extern short lbl_806D181A_p7;
void Sprite_SetAnimParam_p7(Sprite_p7 *sprite_p7, short id_p7, short value_p7);
void fn_8019FF6C_p7(Sprite_p7 *sprite_p7, int on_p7);
int fn_801B85DC(int kind_p7, unsigned char alt_p7, short param_p7);
}
int fn_801B85DC(int kind_p7, unsigned char alt_p7, short param_p7)
{
if (lbl_806D180C_p7 != 0) {
return 0;
}
lbl_806D1810_p7 = 0;
lbl_806D1814_p7 = kind_p7;
lbl_806D1819_p7 = alt_p7;
lbl_806D181A_p7 = param_p7;
if (kind_p7 == 0x1B) {
if (alt_p7) {
lbl_806D180C_p7 = new Sprite_p7(0x18E, 1, 0);
} else {
lbl_806D180C_p7 = new Sprite_p7(0x184, 1, 0);
}
lbl_806D180C_p7->SetPos_p7(320.0f, 210.0f);
lbl_806D180C_p7->SetRot_p7(0.0f);
fn_8019FF6C_p7(lbl_806D180C_p7, 1);
lbl_806D1818_p7 = 2;
return 1;
}
if (kind_p7 == 0xD) {
Sprite_p7 *s_p7 = new Sprite_p7(0x1C, 1, 0);
lbl_806D180C_p7 = s_p7;
Sprite_SetAnimParam_p7(s_p7, 0x1D3E, param_p7);
lbl_806D180C_p7->SetPos_p7(320.0f, 348.0f);
}
if (kind_p7 == 0x15) {
if (alt_p7) {
lbl_806D180C_p7 = new Sprite_p7(0x18E, 1, 0);
} else {
lbl_806D180C_p7 = new Sprite_p7(0x184, 1, 0);
}
lbl_806D180C_p7->SetPos_p7(320.0f, 191.0f);
}
lbl_806D1818_p7 = 0;
return 1;
}
#pragma cplusplus reset
C_REGION_BEGIN
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B87B0.c (0x801b87b0) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
extern void *lbl_806D1800_p8;
extern int lbl_806D1808_p8;
int fn_801B87B0(void) {
if (lbl_806D1800_p8 != 0) {
return 1;
}
return lbl_806D1808_p8 != 0;
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B87D8.c (0x801b87d8) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
typedef struct SpriteObj_p9 {
char pad0_p9[0xC];
float x_p9;
float y_p9;
} SpriteObj_p9;
extern SpriteObj_p9 *lbl_806D1800_p9;
extern int lbl_806D1804_p9;
extern int lbl_806D1808_p9;
extern unsigned char lbl_806D17F3_p9;
extern void Sprite_SetupAnim_p9(void *sprite_p9, int anim_p9, int loop_p9, int arg_p9);
extern void Sprite_SetAnimParam_p9(void *sprite_p9, int id_p9, int value_p9);
extern void fn_801A0550_p9(void *sprite_p9);
extern void fn_8019FF6C_p9(void *sprite_p9, int arg_p9);
extern void Sprite_Destroy_p9(void *sprite_p9, int arg_p9);
extern void *Alloc_p9(int size_p9);
extern const float lbl_806D98F8_p9;
extern const float lbl_806D98FC_p9;
static inline void SpriteObj_SetPos_p9(SpriteObj_p9 *sprite_p9, float x_p9, float y_p9) {
sprite_p9->x_p9 = x_p9;
sprite_p9->y_p9 = y_p9;
}
extern void Sprite_InitWithAnim_p9(void *sprite_p9, int anim_p9, int loop_p9, int arg_p9);
int fn_801B87D8(void) {
SpriteObj_p9 *sprite_p9 = lbl_806D1800_p9;
if (sprite_p9 == 0) {
return 0;
}
if (lbl_806D1808_p9 != 1) {
return 0;
}
Sprite_SetupAnim_p9(sprite_p9, 0xC7, 0, 0);
Sprite_SetAnimParam_p9(lbl_806D1800_p9, 0x1AD4, (short)lbl_806D1804_p9);
fn_801A0550_p9(lbl_806D1800_p9);
SpriteObj_SetPos_p9(lbl_806D1800_p9, lbl_806D98F8_p9, lbl_806D98FC_p9);
fn_8019FF6C_p9(lbl_806D1800_p9, 0);
lbl_806D1808_p9 = 2;
return 1;
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B8874.c (0x801b8874) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
typedef struct SpriteObj_p10 {
char pad0_p10[0xC];
float x_p10;
float y_p10;
} SpriteObj_p10;
extern SpriteObj_p10 *lbl_806D1800_p10;
extern int lbl_806D1804_p10;
extern int lbl_806D1808_p10;
extern unsigned char lbl_806D17F3_p10;
extern void Sprite_SetupAnim_p10(void *sprite_p10, int anim_p10, int loop_p10, int arg_p10);
extern void Sprite_SetAnimParam_p10(void *sprite_p10, int id_p10, int value_p10);
extern void fn_801A0550_p10(void *sprite_p10);
extern void fn_8019FF6C_p10(void *sprite_p10, int arg_p10);
extern void Sprite_Destroy_p10(void *sprite_p10, int arg_p10);
extern void *Alloc_p10(int size_p10);
extern const float lbl_806D98F8_p10;
extern const float lbl_806D98FC_p10;
static inline void SpriteObj_SetPos_p10(SpriteObj_p10 *sprite_p10, float x_p10, float y_p10) {
sprite_p10->x_p10 = x_p10;
sprite_p10->y_p10 = y_p10;
}
extern void Sprite_InitWithAnim_p10(void *sprite_p10, int anim_p10, int loop_p10, int arg_p10);
int fn_801B8874(int value_p10) {
SpriteObj_p10 *sprite_p10 = lbl_806D1800_p10;
if (sprite_p10 == 0) {
return 0;
}
if (lbl_806D1808_p10 != 1) {
return 0;
}
lbl_806D1804_p10 = value_p10;
Sprite_SetupAnim_p10(sprite_p10, 0x1DD, 0, 0);
Sprite_SetAnimParam_p10(lbl_806D1800_p10, 0x1AD4, (short)value_p10);
fn_801A0550_p10(lbl_806D1800_p10);
SpriteObj_SetPos_p10(lbl_806D1800_p10, lbl_806D98F8_p10, lbl_806D98FC_p10);
fn_8019FF6C_p10(lbl_806D1800_p10, 1);
return 1;
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B8918.cpp (0x801b8918) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
C_REGION_END
#pragma cplusplus on
struct SpriteObj_p11 {
char pad0_p11[0xC];
float x_p11;
float y_p11;
char pad14_p11[0x30 - 0x14];
SpriteObj_p11(int anim_p11, int loop_p11, int arg_p11);
};
extern "C"{
extern SpriteObj_p11 *lbl_806D1800_p11;
extern int lbl_806D1804_p11;
extern int lbl_806D1808_p11;
extern unsigned char lbl_806D17F3_p11;
extern const float lbl_806D98F8_p11;
extern const float lbl_806D98FC_p11;
void Sprite_SetAnimParam_p11(void *sprite_p11, int id_p11, short value_p11);
void fn_801A0550_p11(void *sprite_p11);
void Sprite_Destroy_p11(void *sprite_p11, int arg_p11);
}
static inline void SpriteObj_SetPos_p11(SpriteObj_p11 *sprite_p11, float x_p11, float y_p11) {
sprite_p11->x_p11 = x_p11;
sprite_p11->y_p11 = y_p11;
}
extern "C"int fn_801B8918(int value_p11) {
if (!lbl_806D17F3_p11) {
return 0;
}
Sprite_Destroy_p11(lbl_806D1800_p11, 1);
lbl_806D1804_p11 = value_p11;
lbl_806D1800_p11 = new SpriteObj_p11(0xC8, 0, 0);
Sprite_SetAnimParam_p11(lbl_806D1800_p11, 0x1AD4, value_p11);
fn_801A0550_p11(lbl_806D1800_p11);
SpriteObj_SetPos_p11(lbl_806D1800_p11, lbl_806D98F8_p11, lbl_806D98FC_p11);
lbl_806D1808_p11 = 0;
return 1;
}
#pragma cplusplus reset
C_REGION_BEGIN
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B89C8.c (0x801b89c8) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
extern void *lbl_806D17F8_p12;
extern void *lbl_806D17FC_p12;
extern int g_gameMode_p12;
extern void Sprite_SetupAnim_p12(void *sprite_p12, int anim_p12, int loop_p12, int arg_p12);
int fn_801B89C8(unsigned char flag_p12) {
void *sprite_p12 = lbl_806D17FC_p12;
if (sprite_p12 == 0) {
return 0;
}
if (flag_p12) {
Sprite_SetupAnim_p12(sprite_p12, 0x1E2, 1, 0);
} else {
switch (g_gameMode_p12) {
case 1:
Sprite_SetupAnim_p12(lbl_806D17F8_p12, 0x199, 1, 0);
break;
case 2:
Sprite_SetupAnim_p12(lbl_806D17F8_p12, 0x198, 1, 0);
break;
case 0:
default:
Sprite_SetupAnim_p12(lbl_806D17F8_p12, 0x197, 1, 0);
break;
}
}
return 1;
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/SetupBgSprites.cpp (0x801b8a80) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
C_REGION_END
#pragma cplusplus on
struct SpriteObj_p13 {
char pad0_p13[0x30];
SpriteObj_p13(int anim_p13, int loop_p13, int arg_p13);
};
extern "C"{
extern int g_gameMode_p13;
extern int lbl_806CFD60_p13;
extern SpriteObj_p13 *lbl_806D17F8_p13;
extern SpriteObj_p13 *lbl_806D17FC_p13;
void Sprite_Destroy_p13(void *sprite_p13, int arg_p13);
}
extern "C"int SetupBgSprites(unsigned char enable_p13) {
if (lbl_806CFD60_p13 >= 0 && enable_p13 == 1) {
return 0;
}
if (lbl_806CFD60_p13 == -1 && enable_p13 == 0) {
return 0;
}
if (enable_p13) {
lbl_806CFD60_p13 = 0;
switch (g_gameMode_p13) {
case 1:
lbl_806D17F8_p13 = new SpriteObj_p13(0x199, 1, 0);
break;
case 2:
lbl_806D17F8_p13 = new SpriteObj_p13(0x198, 1, 0);
break;
case 0:
default:
lbl_806D17F8_p13 = new SpriteObj_p13(0x197, 1, 0);
break;
}
lbl_806D17FC_p13 = new SpriteObj_p13(0x4B, 1, 0);
} else {
Sprite_Destroy_p13(lbl_806D17F8_p13, 1);
Sprite_Destroy_p13(lbl_806D17FC_p13, 1);
lbl_806CFD60_p13 = -1;
lbl_806D17F8_p13 = 0;
lbl_806D17FC_p13 = 0;
}
return 1;
}
#pragma cplusplus reset
C_REGION_BEGIN
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B8BD8.cpp (0x801b8bd8) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
C_REGION_END
#pragma cplusplus on
void *operator new(size_t size_p14);
void operator delete(void *p_p14) throw();
void *operator new[](size_t size_p14);
void operator delete[](void *p_p14) throw();
struct VObject_p14 {
virtual ~VObject_p14();
};
struct InputState_p14 {
char pad00_p14[4];
unsigned char enabled_p14;
char pad05_p14[0xF];
int dir_p14;
int held_p14;
int edge_p14;
};
extern "C"InputState_p14 *g_pInputState_p14;
static inline InputState_p14 *GetInput_p14() {
return g_pInputState_p14 == 0 ? (InputState_p14 *)0 : g_pInputState_p14;
}
template <class T_p14> struct VHolder_p14 {
T_p14 *p_p14;
VHolder_p14() : p_p14(0) {}
VHolder_p14(T_p14 *q_p14) : p_p14(q_p14) {}
~VHolder_p14() throw() { delete p_p14; }
void Reset_p14(T_p14 *q_p14) throw() {
if (p_p14 != q_p14) {
delete p_p14;
p_p14 = q_p14;
}
}
};
struct FlowRoot_p14 {
virtual void _key_p14();
int id_p14;
int field08_p14;
int field0C_p14;
FlowRoot_p14(int id__p14) : id_p14(id__p14), field08_p14(0), field0C_p14(0) {}
~FlowRoot_p14() {}
};
struct FlowTask_p14 : FlowRoot_p14 {
FlowTask_p14(int id_p14);
~FlowTask_p14();
virtual void Finish_p14();
virtual void Update_p14();
virtual void Draw_p14();
bool CanUpdate_p14() {
if (field08_p14 > 0) {
return 0;
}
return field0C_p14 <= 0;
}
};
struct TextManager_p14 {
char pad000_p14[0x18];
int visible_p14;
char pad01C_p14[4];
unsigned int color_p14;
char pad024_p14[0x22C - 0x24];
float scale_p14;
TextManager_p14();
~TextManager_p14();
};
extern "C"{
int isJapanese_p14(void);
void TexMgr_SetTexture_p14(TextManager_p14 *tm_p14, const char *fmt_p14, ...);
void fn_801F93EC_p14(TextManager_p14 *tm_p14, float x_p14, float y_p14);
void fn_801F8FCC_p14(TextManager_p14 *tm_p14, int mode_p14);
void fn_801F8E90_p14(TextManager_p14 *tm_p14);
void CreditMgr_SetActiveSlot_p14(int slot_p14);
int CreditMgr_GetCoinCount_p14(int slot_p14, int mode_p14);
}
struct ListNode_p14 {
ListNode_p14 *prev_p14;
ListNode_p14 *next_p14;
FlowTask_p14 *task_p14;
};
struct ListIter_p14 {
ListNode_p14 *node_p14;
ListIter_p14() {}
ListIter_p14(ListNode_p14 *n_p14) : node_p14(n_p14) {}
ListIter_p14 &operator=(const ListIter_p14 &o_p14) {
node_p14 = o_p14.node_p14;
return *this;
}
};
struct DoublyLinkedList_p14 {
int count_p14;
ListNode_p14 *last_p14;
ListNode_p14 *first_p14;
DoublyLinkedList_p14();
ListIter_p14 Erase_p14(ListIter_p14 it_p14);
ListNode_p14 *End_p14() { return (ListNode_p14 *)&last_p14; }
};
struct FlowSceneList_p14 {
virtual ~FlowSceneList_p14();
virtual void Update_p14();
virtual void Draw_p14();
DoublyLinkedList_p14 entries_p14;
FlowSceneList_p14() {}
};
struct SceneListImpl_p14 : FlowSceneList_p14 {
SceneListImpl_p14() {}
virtual void Update_p14();
virtual void Draw_p14();
virtual void _key2_p14();
void Sort_p14();
void Kill_p14(unsigned int id_p14);
ListIter_p14 Remove_p14(ListIter_p14 it_p14) { return entries_p14.Erase_p14(it_p14); }
};
extern "C"{
FlowTask_p14 *fn_801F4DC0_p14(FlowSceneList_p14 *list_p14, int id_p14);
void fn_801F4DF0_p14(FlowSceneList_p14 *list_p14, FlowTask_p14 *task_p14, int mode_p14);
void fn_801F4D3C_p14(FlowSceneList_p14 *list_p14);
}
struct FlowFader_p14 {
virtual ~FlowFader_p14();
short a_p14;
short b_p14;
FlowFader_p14() : a_p14(0), b_p14(0) {}
void Step_p14() {
b_p14++;
short lim_p14 = a_p14;
if (b_p14 >= lim_p14) {
b_p14 = lim_p14;
}
}
bool Done_p14() { return b_p14 >= a_p14; }
};
extern "C"const float lbl_806DA880_p14;
struct FlowFaderF_p14 : FlowFader_p14 {
float x_p14;
float y_p14;
float z_p14;
FlowFaderF_p14(float v_p14) : x_p14(v_p14), y_p14(v_p14), z_p14(v_p14) {}
FlowFaderF_p14() : x_p14(lbl_806DA880_p14), y_p14(lbl_806DA880_p14), z_p14(lbl_806DA880_p14) {}
virtual void _key2_p14();
float Value_p14();
void Set_p14(float from_p14, float to_p14, short dur_p14);
};
struct FlowFaderI_p14 : FlowFader_p14 {
int x_p14;
int y_p14;
int z_p14;
FlowFaderI_p14() : x_p14(0), y_p14(0), z_p14(0) {}
virtual void _key2_p14();
int Value_p14();
void Set_p14(int from_p14, int to_p14, short dur_p14);
};
struct FlowScene_p14 : FlowTask_p14 {
VHolder_p14<FlowSceneList_p14> list_p14;
VHolder_p14<FlowFaderI_p14> fader_p14;
int state_p14;
int subState_p14;
int timer_p14;
int cursor_p14;
FlowScene_p14(int id_p14);
~FlowScene_p14();
virtual void _key3_p14();
};
struct ResCtrl_p14 {
int resId_p14;
int field4_p14, mode_p14, fieldc_p14;
unsigned char flag_p14, pad11_p14[3];
float x_p14, y_p14, z_p14, width_p14, height_p14, field28_p14, scaleX_p14, scaleY_p14;
unsigned int colors_p14[4];
bool flipX_p14;
bool flipY_p14;
char pad46_p14[2];
int tail_p14[4];
ResCtrl_p14();
~ResCtrl_p14() {}
void Show_p14(float px_p14, float py_p14, float pz_p14) {
flag_p14 = 1;
x_p14 = px_p14;
y_p14 = py_p14;
z_p14 = pz_p14;
}
void SetScale_p14(float s_p14) {
scaleX_p14 = s_p14;
scaleY_p14 = s_p14;
}
void SetScaleXY_p14(float sx_p14, float sy_p14) {
scaleX_p14 = sx_p14;
scaleY_p14 = sy_p14;
}
void SetSize_p14(float w_p14, float h_p14) {
width_p14 = w_p14;
height_p14 = h_p14;
}
void SetColor_p14(unsigned int c_p14) {
colors_p14[0] = c_p14;
colors_p14[1] = c_p14;
colors_p14[2] = c_p14;
colors_p14[3] = c_p14;
}
void SetPos_p14(float px_p14, float py_p14, float pz_p14) {
x_p14 = px_p14;
y_p14 = py_p14;
z_p14 = pz_p14;
}
};
struct Sprite_p14 {
int field0_p14, layer_p14, field8_p14;
float x_p14, y_p14;
char pad14_p14[0x20 - 0x14];
float alpha_p14;
char pad24_p14[0x30 - 0x24];
Sprite_p14(int resource_p14, int mode_p14, int flags_p14);
~Sprite_p14();
};
struct SpritePairOwner_p14 {
Sprite_p14 *sprites_p14[2];
int handles_p14[2];
int resources_p14[2];
float alpha_p14, speed_p14;
SpritePairOwner_p14(int back_p14, int front_p14, int backHandle_p14, int frontHandle_p14, int layer_p14);
~SpritePairOwner_p14();
void Tick_p14();
void Reset_p14();
};
extern "C"{
void SpriteHandle_SetActiveFlag_p14(int, int);
void fn_8011F804_p14(int, float, float);
void fn_801A0004_p14(Sprite_p14 *);
unsigned char Sprite_AdvanceAnim_p14(Sprite_p14 *, float);
void SpriteHandle_SetCornerAlpha_p14(int, int);
void SpriteHandle_RecomputeCull_p14(int);
void SpriteHandle_Destroy_p14(int);
void fn_8019FF6C_p14(Sprite_p14 *, int);
void fn_80121E10_p14(ResCtrl_p14 *);
int SpriteHandle_CreateDefault_p14(ResCtrl_p14 *, int);
extern const float lbl_806DB9D8_p14, lbl_806DB9DC_p14, lbl_806DB9E0_p14, lbl_806DB9E4_p14;
}
struct MenuChildView_p14 {
virtual ~MenuChildView_p14();
virtual int Update_p14();
virtual void Draw_p14();
};
struct MenuOwnerView_p14 {
void *vtable_p14;
unsigned char finished_p14;
unsigned char padding_p14[3];
MenuChildView_p14 *child_p14;
};
extern "C"{
extern Sprite_p14 *lbl_806D17F8_p14, *lbl_806D17FC_p14, *lbl_806D1800_p14, *lbl_806D180C_p14;
extern Sprite_p14 *lbl_806D1820_p14, *lbl_806D1840_p14, *lbl_806D1844_p14;
extern Sprite_p14 *lbl_80679280_p14[3], *lbl_8067928C_p14[4];
extern unsigned char lbl_806D184F_p14, lbl_806D1850_p14;
extern signed char lbl_806D1858_p14, lbl_806D181C_p14, lbl_806D181D_p14, lbl_806D184D_p14;
extern float lbl_806D1854_p14, lbl_806D1848_p14;
void fn_801A1174_p14(int, int, int, int, int);
void fn_801A10DC_p14(float, float);
void fn_801A1128_p14(float, float);
void fn_801A0FD4_p14(float, float, float, float);
void fn_801A0DF0_p14();
void fn_8011FA98_p14();
}
extern "C"const float lbl_806D9890_p14;
extern "C"void fn_801B8BD8(MenuOwnerView_p14 *self_p14) {
if (lbl_806D17F8_p14) fn_801A0004_p14(lbl_806D17F8_p14);
if (lbl_806D17FC_p14) fn_801A0004_p14(lbl_806D17FC_p14);
if (lbl_806D1800_p14) fn_801A0004_p14(lbl_806D1800_p14);
if (lbl_806D180C_p14) fn_801A0004_p14(lbl_806D180C_p14);
if (self_p14->child_p14) self_p14->child_p14->Draw_p14();
if (lbl_806D184F_p14 || lbl_806D1850_p14) {
fn_801A1174_p14(2, 6, 0, 0, 0);
fn_801A10DC_p14(640.0f, 480.0f);
fn_801A1128_p14(320.0f, 240.0f);
fn_801A0FD4_p14(255.0f, 255.0f, 255.0f, (float)(255 - lbl_806D1858_p14 * 25));
fn_801A0DF0_p14();
fn_801A1174_p14(0x1B12, 6, 0, 0, 0);
fn_801A1128_p14(0.0f, 374.0f + lbl_806D1854_p14);
fn_801A0DF0_p14();
fn_801A1174_p14(0x1B13, 6, 0, 0, 0);
fn_801A1128_p14(0.0f, 366.0f + lbl_806D1854_p14);
fn_801A0DF0_p14();
}
if (lbl_806D181D_p14 != -1 && lbl_8067928C_p14[lbl_806D181D_p14]) fn_801A0004_p14(lbl_8067928C_p14[lbl_806D181D_p14]);
if (lbl_806D181C_p14 != -1 && lbl_80679280_p14[lbl_806D181C_p14]) fn_801A0004_p14(lbl_80679280_p14[lbl_806D181C_p14]);
if (lbl_806D1820_p14) fn_801A0004_p14(lbl_806D1820_p14);
if (lbl_806D1848_p14 > lbl_806D9890_p14) {
if (lbl_806D1840_p14) { lbl_806D1840_p14->alpha_p14 = lbl_806D1848_p14; fn_801A0004_p14(lbl_806D1840_p14); }
if (lbl_806D1844_p14) { lbl_806D1844_p14->alpha_p14 = lbl_806D1848_p14; fn_801A0004_p14(lbl_806D1844_p14); }
if (lbl_806D184D_p14 == 0) fn_801A1174_p14(0x1875, 5, 0, 0, 0);
else fn_801A1174_p14(0x1875, 5, 0, 0, 0);
fn_801A1128_p14(244.0f, 450.0f);
fn_801A0FD4_p14(1.0f, 1.0f, 1.0f, lbl_806D1848_p14);
fn_801A0DF0_p14();
if (lbl_806D184D_p14 == 0) fn_801A1174_p14(0x1874, 5, 0, 0, 0);
else fn_801A1174_p14(0x1874, 5, 0, 0, 0);
fn_801A1128_p14(400.0f, 450.0f);
fn_801A0FD4_p14(1.0f, 1.0f, 1.0f, lbl_806D1848_p14);
fn_801A0DF0_p14();
}
fn_8011FA98_p14();
}
#pragma cplusplus reset
C_REGION_BEGIN
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/MenuScene_Dispatch.cpp (0x801b8ec0) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
C_REGION_END
#pragma cplusplus on
void *operator new(size_t size_p15);
void operator delete(void *p_p15) throw();
void *operator new[](size_t size_p15);
void operator delete[](void *p_p15) throw();
struct VObject_p15 {
virtual ~VObject_p15();
};
struct InputState_p15 {
char pad00_p15[4];
unsigned char enabled_p15;
char pad05_p15[0xF];
int dir_p15;
int held_p15;
int edge_p15;
};
extern "C"InputState_p15 *g_pInputState_p15;
static inline InputState_p15 *GetInput_p15() {
return g_pInputState_p15 == 0 ? (InputState_p15 *)0 : g_pInputState_p15;
}
template <class T_p15> struct VHolder_p15 {
T_p15 *p_p15;
VHolder_p15() : p_p15(0) {}
VHolder_p15(T_p15 *q_p15) : p_p15(q_p15) {}
~VHolder_p15() throw() { delete p_p15; }
void Reset_p15(T_p15 *q_p15) throw() {
if (p_p15 != q_p15) {
delete p_p15;
p_p15 = q_p15;
}
}
};
struct FlowRoot_p15 {
virtual void _key_p15();
int id_p15;
int field08_p15;
int field0C_p15;
FlowRoot_p15(int id__p15) : id_p15(id__p15), field08_p15(0), field0C_p15(0) {}
~FlowRoot_p15() {}
};
struct FlowTask_p15 : FlowRoot_p15 {
FlowTask_p15(int id_p15);
~FlowTask_p15();
virtual void Finish_p15();
virtual void Update_p15();
virtual void Draw_p15();
bool CanUpdate_p15() {
if (field08_p15 > 0) {
return 0;
}
return field0C_p15 <= 0;
}
};
struct TextManager_p15 {
char pad000_p15[0x18];
int visible_p15;
char pad01C_p15[4];
unsigned int color_p15;
char pad024_p15[0x22C - 0x24];
float scale_p15;
TextManager_p15();
~TextManager_p15();
};
extern "C"{
int isJapanese_p15(void);
void TexMgr_SetTexture_p15(TextManager_p15 *tm_p15, const char *fmt_p15, ...);
void fn_801F93EC_p15(TextManager_p15 *tm_p15, float x_p15, float y_p15);
void fn_801F8FCC_p15(TextManager_p15 *tm_p15, int mode_p15);
void fn_801F8E90_p15(TextManager_p15 *tm_p15);
void CreditMgr_SetActiveSlot_p15(int slot_p15);
int CreditMgr_GetCoinCount_p15(int slot_p15, int mode_p15);
}
struct ListNode_p15 {
ListNode_p15 *prev_p15;
ListNode_p15 *next_p15;
FlowTask_p15 *task_p15;
};
struct ListIter_p15 {
ListNode_p15 *node_p15;
ListIter_p15() {}
ListIter_p15(ListNode_p15 *n_p15) : node_p15(n_p15) {}
ListIter_p15 &operator=(const ListIter_p15 &o_p15) {
node_p15 = o_p15.node_p15;
return *this;
}
};
struct DoublyLinkedList_p15 {
int count_p15;
ListNode_p15 *last_p15;
ListNode_p15 *first_p15;
DoublyLinkedList_p15();
ListIter_p15 Erase_p15(ListIter_p15 it_p15);
ListNode_p15 *End_p15() { return (ListNode_p15 *)&last_p15; }
};
struct FlowSceneList_p15 {
virtual ~FlowSceneList_p15();
virtual void Update_p15();
virtual void Draw_p15();
DoublyLinkedList_p15 entries_p15;
FlowSceneList_p15() {}
};
struct SceneListImpl_p15 : FlowSceneList_p15 {
SceneListImpl_p15() {}
virtual void Update_p15();
virtual void Draw_p15();
virtual void _key2_p15();
void Sort_p15();
void Kill_p15(unsigned int id_p15);
ListIter_p15 Remove_p15(ListIter_p15 it_p15) { return entries_p15.Erase_p15(it_p15); }
};
extern "C"{
FlowTask_p15 *fn_801F4DC0_p15(FlowSceneList_p15 *list_p15, int id_p15);
void fn_801F4DF0_p15(FlowSceneList_p15 *list_p15, FlowTask_p15 *task_p15, int mode_p15);
void fn_801F4D3C_p15(FlowSceneList_p15 *list_p15);
}
struct FlowFader_p15 {
virtual ~FlowFader_p15();
short a_p15;
short b_p15;
FlowFader_p15() : a_p15(0), b_p15(0) {}
void Step_p15() {
b_p15++;
short lim_p15 = a_p15;
if (b_p15 >= lim_p15) {
b_p15 = lim_p15;
}
}
bool Done_p15() { return b_p15 >= a_p15; }
};
extern "C"const float lbl_806DA880_p15;
struct FlowFaderF_p15 : FlowFader_p15 {
float x_p15;
float y_p15;
float z_p15;
FlowFaderF_p15(float v_p15) : x_p15(v_p15), y_p15(v_p15), z_p15(v_p15) {}
FlowFaderF_p15() : x_p15(lbl_806DA880_p15), y_p15(lbl_806DA880_p15), z_p15(lbl_806DA880_p15) {}
virtual void _key2_p15();
float Value_p15();
void Set_p15(float from_p15, float to_p15, short dur_p15);
};
struct FlowFaderI_p15 : FlowFader_p15 {
int x_p15;
int y_p15;
int z_p15;
FlowFaderI_p15() : x_p15(0), y_p15(0), z_p15(0) {}
virtual void _key2_p15();
int Value_p15();
void Set_p15(int from_p15, int to_p15, short dur_p15);
};
struct FlowScene_p15 : FlowTask_p15 {
VHolder_p15<FlowSceneList_p15> list_p15;
VHolder_p15<FlowFaderI_p15> fader_p15;
int state_p15;
int subState_p15;
int timer_p15;
int cursor_p15;
FlowScene_p15(int id_p15);
~FlowScene_p15();
virtual void _key3_p15();
};
struct ResCtrl_p15 {
int resId_p15;
int field4_p15, mode_p15, fieldc_p15;
unsigned char flag_p15, pad11_p15[3];
float x_p15, y_p15, z_p15, width_p15, height_p15, field28_p15, scaleX_p15, scaleY_p15;
unsigned int colors_p15[4];
bool flipX_p15;
bool flipY_p15;
char pad46_p15[2];
int tail_p15[4];
ResCtrl_p15();
~ResCtrl_p15() {}
void Show_p15(float px_p15, float py_p15, float pz_p15) {
flag_p15 = 1;
x_p15 = px_p15;
y_p15 = py_p15;
z_p15 = pz_p15;
}
void SetScale_p15(float s_p15) {
scaleX_p15 = s_p15;
scaleY_p15 = s_p15;
}
void SetScaleXY_p15(float sx_p15, float sy_p15) {
scaleX_p15 = sx_p15;
scaleY_p15 = sy_p15;
}
void SetSize_p15(float w_p15, float h_p15) {
width_p15 = w_p15;
height_p15 = h_p15;
}
void SetColor_p15(unsigned int c_p15) {
colors_p15[0] = c_p15;
colors_p15[1] = c_p15;
colors_p15[2] = c_p15;
colors_p15[3] = c_p15;
}
void SetPos_p15(float px_p15, float py_p15, float pz_p15) {
x_p15 = px_p15;
y_p15 = py_p15;
z_p15 = pz_p15;
}
};
struct Sprite_p15 {
int field0_p15, layer_p15, field8_p15;
float x_p15, y_p15;
char pad14_p15[0x20 - 0x14];
float alpha_p15;
char pad24_p15[0x30 - 0x24];
Sprite_p15(int resource_p15, int mode_p15, int flags_p15);
~Sprite_p15();
};
struct SpritePairOwner_p15 {
Sprite_p15 *sprites_p15[2];
int handles_p15[2];
int resources_p15[2];
float alpha_p15, speed_p15;
SpritePairOwner_p15(int back_p15, int front_p15, int backHandle_p15, int frontHandle_p15, int layer_p15);
~SpritePairOwner_p15();
void Tick_p15();
void Reset_p15();
};
extern "C"{
void SpriteHandle_SetActiveFlag_p15(int, int);
void fn_8011F804_p15(int, float, float);
void fn_801A0004_p15(Sprite_p15 *);
unsigned char Sprite_AdvanceAnim_p15(Sprite_p15 *, float);
void SpriteHandle_SetCornerAlpha_p15(int, int);
void SpriteHandle_RecomputeCull_p15(int);
void SpriteHandle_Destroy_p15(int);
void fn_8019FF6C_p15(Sprite_p15 *, int);
void fn_80121E10_p15(ResCtrl_p15 *);
int SpriteHandle_CreateDefault_p15(ResCtrl_p15 *, int);
extern const float lbl_806DB9D8_p15, lbl_806DB9DC_p15, lbl_806DB9E0_p15, lbl_806DB9E4_p15;
}
struct MenuChildView_p15 {
virtual ~MenuChildView_p15();
virtual int Update_p15();
virtual void Draw_p15();
};
struct MenuOwnerView_p15 {
void *vtable_p15;
unsigned char finished_p15;
unsigned char padding_p15[3];
MenuChildView_p15 *child_p15;
};
extern "C"{
extern Sprite_p15 *lbl_806D17F8_p15, *lbl_806D17FC_p15, *lbl_806D1800_p15, *lbl_806D180C_p15;
extern Sprite_p15 *lbl_806D1820_p15, *lbl_806D1840_p15, *lbl_806D1844_p15;
extern Sprite_p15 *lbl_80679280_p15[3], *lbl_8067928C_p15[4];
extern unsigned char lbl_806D184F_p15, lbl_806D1850_p15;
extern signed char lbl_806D1858_p15, lbl_806D181C_p15, lbl_806D181D_p15, lbl_806D184D_p15;
extern float lbl_806D1854_p15, lbl_806D1848_p15;
void fn_801A1174_p15(int, int, int, int, int);
void fn_801A10DC_p15(float, float);
void fn_801A1128_p15(float, float);
void fn_801A0FD4_p15(float, float, float, float);
void fn_801A0DF0_p15();
void fn_8011FA98_p15();
}
struct MenuEntryScene_p15 : MenuChildView_p15 { char state_p15[0x14 - 4]; MenuEntryScene_p15(); };
struct MenuTitleScene_p15 : MenuChildView_p15 { char state_p15[0x20 - 4]; MenuTitleScene_p15(); };
struct MenuAttractScene_p15 : MenuChildView_p15 { char state_p15[0x38 - 4]; MenuAttractScene_p15(); };
struct MenuUnknown8020E0E0Scene_p15 : MenuChildView_p15 { char state_p15[0x28 - 4]; MenuUnknown8020E0E0Scene_p15(); };
struct MenuUnknown8020D850Scene_p15 : MenuChildView_p15 { char state_p15[0x38 - 4]; MenuUnknown8020D850Scene_p15(); };
struct MenuCardScene_p15 : MenuChildView_p15 { char state_p15[0x2c - 4]; MenuCardScene_p15(); };
struct MenuClassScene_p15 : MenuChildView_p15 { char state_p15[0x58 - 4]; MenuClassScene_p15(); };
struct MenuFrameSelectionScene_p15 : MenuChildView_p15 { char state_p15[0x1d8 - 4]; MenuFrameSelectionScene_p15(); };
struct MenuKartScene_p15 : MenuChildView_p15 { char state_p15[0xdc - 4]; MenuKartScene_p15(); };
struct MenuFigureScene_p15 : MenuChildView_p15 { char state_p15[0xb0 - 4]; MenuFigureScene_p15(); };
struct MenuCupScene_p15 : MenuChildView_p15 { char state_p15[0x158 - 4]; MenuCupScene_p15(); };
struct MenuRoundScene_p15 : MenuChildView_p15 { char state_p15[0x16c - 4]; MenuRoundScene_p15(); };
struct MenuCourseScene_p15 : MenuChildView_p15 { char state_p15[0x160 - 4]; MenuCourseScene_p15(); };
struct MenuItemSelectScene_p15 : MenuChildView_p15 { char state_p15[0xec - 4]; MenuItemSelectScene_p15(); };
struct MenuItemScene_p15 : MenuChildView_p15 { char state_p15[0x34 - 4]; MenuItemScene_p15(); };
struct MenuGpPleaseScene_p15 : MenuChildView_p15 { char state_p15[0x1c - 4]; MenuGpPleaseScene_p15(); };
struct MenuTaPleaseScene_p15 : MenuChildView_p15 { char state_p15[0x3c - 4]; MenuTaPleaseScene_p15(); };
struct Menuranking_displayScene_p15 : MenuChildView_p15 { char state_p15[0x3c - 4]; Menuranking_displayScene_p15(); };
extern "C"{
void CGameCoin_ProcessInput_p15(InputState_p15 *);
void fn_801A1280_p15(); void fn_8020F290_p15(); void *fn_801DAEC0_p15(); void fn_801DABFC_p15(void *);
void GXDrawDone_p15(); void fn_80121210_p15(); void clRom_PurgeAll_p15();
void Sprite_SetupAnim_p15(Sprite_p15 *, int, int, int);
void Sprite_SetAnimParam_p15(Sprite_p15 *, int, short);
void fn_801A0550_p15(Sprite_p15 *); void Sprite_Destroy_p15(Sprite_p15 *, int);
int fn_801B7EF8_p15();
int CreditMgr_GetCoinsPerCredit_p15(int);
extern int lbl_806CFD60_p15, lbl_806D1804_p15, lbl_806D1808_p15, lbl_806D1810_p15, lbl_806D1814_p15, lbl_806D1824_p15;
extern signed char lbl_806D1818_p15, lbl_806D184C_p15;
extern unsigned char lbl_806D1819_p15;
extern short lbl_806D181A_p15;
extern short *lbl_806D1828_p15, *lbl_806D182C_p15, *lbl_806D1830_p15, *lbl_806D1834_p15;
extern const float lbl_806D9890_p15, lbl_806D98E0_p15, lbl_806D98E8_p15, lbl_806D98EC_p15, lbl_806D98F8_p15, lbl_806D98FC_p15;
extern const float lbl_806D9924_p15, lbl_806D9928_p15, lbl_806D992C_p15, lbl_806D9930_p15, lbl_806D9934_p15;
extern const double lbl_806D9938_p15, lbl_806D9940_p15;
}

#pragma fp_contract off

extern "C"int MenuScene_Dispatch(MenuOwnerView_p15 *self_p15) {
if (self_p15->finished_p15) return 4;
if (GetInput_p15()) CGameCoin_ProcessInput_p15(GetInput_p15());
fn_801A1280_p15();
fn_8020F290_p15();
fn_801DABFC_p15(fn_801DAEC0_p15());
int next_p15 = -1;
if (self_p15->child_p15) next_p15 = self_p15->child_p15->Update_p15();
if (next_p15 != -1) {
GXDrawDone_p15();
delete self_p15->child_p15;
self_p15->child_p15 = 0;
fn_80121210_p15();
clRom_PurgeAll_p15();
switch (next_p15) {
case 2:
self_p15->child_p15 = new MenuEntryScene_p15;
break;
case 7:
self_p15->child_p15 = new MenuTitleScene_p15;
break;
case 6:
self_p15->child_p15 = new MenuAttractScene_p15;
break;
case 49:
self_p15->child_p15 = new MenuUnknown8020E0E0Scene_p15;
break;
case 48:
self_p15->child_p15 = new MenuUnknown8020D850Scene_p15;
break;
case 9:
self_p15->child_p15 = new MenuCardScene_p15;
break;
case 11:
self_p15->child_p15 = new MenuClassScene_p15;
break;
case 13:
self_p15->child_p15 = new MenuFrameSelectionScene_p15;
break;
case 15:
self_p15->child_p15 = new MenuKartScene_p15;
break;
case 19:
self_p15->child_p15 = new MenuFigureScene_p15;
break;
case 21:
self_p15->child_p15 = new MenuCupScene_p15;
break;
case 27:
self_p15->child_p15 = new MenuRoundScene_p15;
break;
case 23:
self_p15->child_p15 = new MenuCourseScene_p15;
break;
case 25:
self_p15->child_p15 = new MenuCourseScene_p15;
break;
case 34:
self_p15->child_p15 = new MenuItemSelectScene_p15;
break;
case 33:
self_p15->child_p15 = new MenuItemScene_p15;
break;
case 37:
self_p15->child_p15 = new MenuGpPleaseScene_p15;
break;
case 38:
self_p15->child_p15 = new MenuTaPleaseScene_p15;
break;
case 39:
self_p15->child_p15 = new Menuranking_displayScene_p15;
break;
case 42: self_p15->finished_p15 = 1; break;
case 0: case 1: default: break;
}
}
if (lbl_806CFD60_p15 != -1) {
if (lbl_806D17F8_p15) Sprite_AdvanceAnim_p15(lbl_806D17F8_p15, lbl_806D9924_p15);
if (lbl_806D17FC_p15) {
if (lbl_806CFD60_p15 == 0) {
if (!Sprite_AdvanceAnim_p15(lbl_806D17FC_p15, lbl_806D9924_p15)) {
Sprite_SetupAnim_p15(lbl_806D17FC_p15, 0x4C, 1, 0);
fn_8019FF6C_p15(lbl_806D17FC_p15, 1);
++lbl_806CFD60_p15;
}
} else if (lbl_806CFD60_p15 == 1) Sprite_AdvanceAnim_p15(lbl_806D17FC_p15, lbl_806D9924_p15);
}
}
if (lbl_806D1800_p15) {
unsigned char active_p15 = Sprite_AdvanceAnim_p15(lbl_806D1800_p15, lbl_806D9924_p15);
if (lbl_806D1808_p15 == 0 && !active_p15) {
Sprite_SetupAnim_p15(lbl_806D1800_p15, 0x1DD, 0, 0);
Sprite_SetAnimParam_p15(lbl_806D1800_p15, 0x1AD4, (short)lbl_806D1804_p15);
fn_801A0550_p15(lbl_806D1800_p15);
Sprite_p15 *sprite_p15 = lbl_806D1800_p15;
sprite_p15->x_p15 = lbl_806D98F8_p15;
sprite_p15->y_p15 = lbl_806D98FC_p15;
fn_8019FF6C_p15(lbl_806D1800_p15, 1);
++lbl_806D1808_p15;
}
if (lbl_806D1808_p15 == 2 && !active_p15) {
Sprite_Destroy_p15(lbl_806D1800_p15, 1);
lbl_806D1800_p15 = 0;
lbl_806D1808_p15 = 0;
}
}
if (lbl_806D180C_p15) {
unsigned char active_p15 = Sprite_AdvanceAnim_p15(lbl_806D180C_p15, lbl_806D9924_p15);
if (lbl_806D1818_p15 == 0 && !active_p15) {
if (lbl_806D1814_p15 == 13) {
Sprite_SetupAnim_p15(lbl_806D180C_p15, 0x167, 1, 0);
Sprite_SetAnimParam_p15(lbl_806D180C_p15, 0x1D3E, lbl_806D181A_p15);
}
if (lbl_806D1814_p15 == 21) {
if (lbl_806D1819_p15) Sprite_SetupAnim_p15(lbl_806D180C_p15, 0x18E, 1, 0);
else Sprite_SetupAnim_p15(lbl_806D180C_p15, 0x184, 1, 0);
}
fn_8019FF6C_p15(lbl_806D180C_p15, 1);
++lbl_806D1818_p15;
}
if (lbl_806D1818_p15 == 2) {
++lbl_806D1810_p15;
if (lbl_806D1814_p15 == 13 && !active_p15) {
Sprite_SetupAnim_p15(lbl_806D180C_p15, 0x150, 1, 0);
Sprite_p15 *sprite_p15 = lbl_806D180C_p15;
sprite_p15->x_p15 = lbl_806D98E8_p15;
sprite_p15->y_p15 = lbl_806D9928_p15;
fn_8019FF6C_p15(lbl_806D180C_p15, 1);
}
if (lbl_806D1814_p15 == 21) {
int frame_p15 = lbl_806D1810_p15;
float scale_p15;
float y_p15;
y_p15 = lbl_806D98EC_p15 + lbl_806D9930_p15 * (float)frame_p15;
scale_p15 = lbl_806D992C_p15 * (float)frame_p15;
lbl_806D180C_p15->y_p15 = y_p15;
*(float *)((char *)lbl_806D180C_p15 + 0x18) = lbl_806D98E0_p15 + scale_p15;
if (lbl_806D1810_p15 >= 10) ++lbl_806D1818_p15;
}
if (lbl_806D1814_p15 == 27) {
*(float *)((char *)lbl_806D180C_p15 + 0x18) = lbl_806D9934_p15 * (float)lbl_806D1810_p15;
if (lbl_806D1810_p15 >= 10) ++lbl_806D1818_p15;
}
}
if (lbl_806D1818_p15 == 4 && !active_p15) {
Sprite_Destroy_p15(lbl_806D180C_p15, 1);
lbl_806D180C_p15 = 0;
lbl_806D1810_p15 = 0;
lbl_806D1818_p15 = 0;
}
}
fn_801B7EF8_p15();
if (lbl_806D1820_p15) {
int coins_p15 = CreditMgr_GetCoinCount_p15(0, lbl_806D1824_p15);
int cost_p15 = CreditMgr_GetCoinsPerCredit_p15(lbl_806D1824_p15);
int coinTens_p15 = coins_p15 / 10;
int coinUnits_p15 = coins_p15 % 10;
int costTens_p15 = cost_p15 / 10;
int costUnits_p15 = cost_p15 % 10;
if (cost_p15 != -1) {
if (coinTens_p15 != 0) {
*lbl_806D1828_p15 = 0x1D63 + coinTens_p15;
*lbl_806D182C_p15 = 0x1D63 + coinUnits_p15;
} else {
*lbl_806D1828_p15 = -1;
*lbl_806D182C_p15 = 0x1D63 + coinUnits_p15;
}
if (costTens_p15 != 0) {
*lbl_806D1830_p15 = 0x1D63 + costTens_p15;
*lbl_806D1834_p15 = 0x1D63 + costUnits_p15;
} else {
*lbl_806D1830_p15 = 0x1D63 + costUnits_p15;
*lbl_806D1834_p15 = -1;
}
}
}
if (lbl_806D184C_p15 > 0) {
lbl_806D1848_p15 += 0.125;
if (lbl_806D1848_p15 >= 1.0f) {
lbl_806D1848_p15 = 1.0f;
lbl_806D184C_p15 = 0;
}
}
if (lbl_806D184C_p15 < 0) {
lbl_806D1848_p15 -= 0.08333333333333333;
if (lbl_806D1848_p15 <= 0.0f) {
lbl_806D1848_p15 = 0.0f;
lbl_806D184C_p15 = 0;
}
}
if (lbl_806D1848_p15 > lbl_806D9890_p15) {
if (lbl_806D1840_p15) Sprite_AdvanceAnim_p15(lbl_806D1840_p15, lbl_806D9924_p15);
if (lbl_806D1844_p15) Sprite_AdvanceAnim_p15(lbl_806D1844_p15, lbl_806D9924_p15);
}
if (lbl_806D184F_p15) {
if (lbl_806D1858_p15 < 5) ++lbl_806D1858_p15;
}
if (lbl_806D1850_p15) {
if (lbl_806D1858_p15 > 0) --lbl_806D1858_p15;
if (lbl_806D1858_p15 == 0) lbl_806D1850_p15 = 0;
}
return -2;
}
#pragma cplusplus reset
C_REGION_BEGIN
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B9740.cpp (0x801b9740) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
C_REGION_END
#pragma cplusplus on
struct SpriteObj_p16 {
~SpriteObj_p16();
};
class InputState_p16 {
public:
virtual ~InputState_p16();
};
struct GameModeBase_p16 {
void *vt_p16;
GameModeBase_p16();
~GameModeBase_p16();
};
extern "C"{
extern void *lbl_8049A734_p16[];
extern unsigned char lbl_806D17F4_p16;
extern unsigned char lbl_806D17F3_p16;
extern int lbl_806CFD60_p16;
extern SpriteObj_p16 *lbl_806D1820_p16;
extern SpriteObj_p16 *lbl_806D17F8_p16;
extern SpriteObj_p16 *lbl_806D17FC_p16;
extern SpriteObj_p16 *lbl_806D1800_p16;
extern SpriteObj_p16 *lbl_806D180C_p16;
extern SpriteObj_p16 *lbl_806D1840_p16;
extern SpriteObj_p16 *lbl_806D1844_p16;
extern SpriteObj_p16 *lbl_80679280_p16[3];
extern SpriteObj_p16 *lbl_8067928C_p16[4];
extern InputState_p16 *g_pInputState_p16;
void fn_80120A08_p16(int id_p16);
unsigned char fn_8019083C_p16(int arg_p16);
void fn_801909A4_p16(int arg_p16);
void fn_801908F0_p16(void);
void fn_801B7CD0_p16(int arg_p16);
void fn_801DAE54_p16(void);
void fn_80121210_p16(void);
void clRom_PurgeAll_p16(void);
}
struct Mode801B9740 : GameModeBase_p16 {
~Mode801B9740();
};
Mode801B9740::~Mode801B9740() {
vt_p16 = lbl_8049A734_p16;
fn_80120A08_p16(0x186E);
fn_80120A08_p16(0x186F);
fn_80120A08_p16(0x1870);
fn_80120A08_p16(0x1871);
fn_80120A08_p16(0x1872);
fn_80120A08_p16(0x1873);
fn_80120A08_p16(0x1874);
fn_80120A08_p16(0x1875);
if (lbl_806D17F4_p16) {
if (fn_8019083C_p16(1)) {
fn_801909A4_p16(1);
}
fn_801908F0_p16();
lbl_806D17F4_p16 = 0;
}
fn_801B7CD0_p16(-1);
delete lbl_806D1820_p16;
delete lbl_806D17F8_p16;
delete lbl_806D17FC_p16;
delete lbl_806D1800_p16;
delete lbl_806D180C_p16;
lbl_806D1820_p16 = 0;
lbl_806CFD60_p16 = -1;
lbl_806D17F8_p16 = 0;
lbl_806D17FC_p16 = 0;
lbl_806D1800_p16 = 0;
lbl_806D180C_p16 = 0;
lbl_806D17F3_p16 = 0;
delete lbl_806D1840_p16;
delete lbl_806D1844_p16;
lbl_806D1840_p16 = 0;
lbl_806D1844_p16 = 0;
for (int i_p16 = 0; i_p16 < 3; i_p16++) {
delete lbl_80679280_p16[i_p16];
lbl_80679280_p16[i_p16] = 0;
}
for (int j_p16 = 0; j_p16 < 4; j_p16++) {
delete lbl_8067928C_p16[j_p16];
lbl_8067928C_p16[j_p16] = 0;
}
delete g_pInputState_p16;
g_pInputState_p16 = 0;
fn_801DAE54_p16();
fn_80121210_p16();
clRom_PurgeAll_p16();
}
#pragma cplusplus reset
C_REGION_BEGIN
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/fn_801B9928.cpp (0x801b9928) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
C_REGION_END
#pragma cplusplus on
#pragma optimize_for_size on
void *operator new(size_t);
void operator delete(void *) throw();
struct SceneBase_p17 {
virtual ~SceneBase_p17() {}
virtual void Destroy_p17();
virtual void Update_p17();
virtual void Draw_p17();
bool done_p17;
SceneBase_p17() : done_p17(false) {}
};
struct MenuModeBase_p17 : SceneBase_p17 {
virtual void _key_p17();
int cup_p17, course_p17, variant_p17, round_p17, startAnim_p17, timer_p17, itemCount_p17, randomItem_p17;
int role_p17, modeFlag_p17, items_p17[3], character_p17, kart_p17, mode_p17, roundIndex_p17, cc_p17, gate_p17;
void *input_p17;
int selection_p17;
MenuModeBase_p17();
~MenuModeBase_p17();
};
struct MenuWidget_p17 {
char pad_p17[0x3c]; float x_p17, y_p17;
MenuWidget_p17(int);
void SetPosition_p17(float a_p17, float b_p17) { x_p17=a_p17; y_p17=b_p17; }
};
struct MenuScene_p17 : MenuModeBase_p17 {
virtual void _key_p17();
~MenuScene_p17();
int state_p17, state2_p17;
MenuWidget_p17 *widgets_p17[3];
MenuScene_p17();
};
struct GameModeBase_p17 {
void *vt_p17;
GameModeBase_p17();
~GameModeBase_p17();
};
struct MenuDisplay_p17 {
char opaque_p17[0x1c];
MenuDisplay_p17(int);
};
struct MenuMode_p17 : GameModeBase_p17 {
MenuMode_p17();
MenuModeBase_p17 *scene_p17;
int cup_p17, course_p17, variant_p17, round_p17, startAnim_p17, timer_p17, itemCount_p17, randomItem_p17;
int role_p17, modeFlag_p17, character_p17, kart_p17, menuId_p17, mode_p17, roundIndex_p17, gate_p17, selection_p17;
MenuDisplay_p17 *display_p17;
};
extern "C"{
extern int g_cupId_p17, g_localPcbRole_p17, g_characterId_p17, g_gameMode_p17, g_roundIndex_p17;
extern int g_ccClass_p17, g_kartVariant_p17, g_humanPlayerCount_p17;
extern unsigned char g_rendererGateFlag_p17, g_lakituStartAnimDone_p17, g_namCamFlag_p17;
extern unsigned char lbl_806D0050_p17, lbl_806D0051_p17, lbl_806D1290_p17;
extern unsigned char lbl_806D1264_p17[3];
extern int lbl_806CF110_p17;
extern volatile int lbl_806D12C0_p17;
extern int lbl_804E53B0_p17[3];
extern char lbl_806D005C_p17[8], lbl_806D0054_p17[8];
extern char g_playerData_p17[0x2000];
extern void *lbl_804E5444_p17[], *lbl_804E549C_p17[], *lbl_803FE0C8_p17[], *lbl_804E54D8_p17[];
extern const float lbl_806DA690_p17, lbl_806DA694_p17, lbl_806DA698_p17, lbl_806DA69C_p17;
void fn_8023E808_p17(MenuWidget_p17 *, int);
void fn_80209FA4_p17(); void fn_801F9888_p17();
void InputCmd_SetGlobalConfig_p17(void *); void *InputCmd_GetGlobalConfig_p17();
void fn_801F6494_p17(); int fn_801DC868_p17();
SceneBase_p17 *fn_8020CEAC_p17();
MenuModeBase_p17 *fn_80271340_p17(SceneBase_p17 *, int, char *, char *, int);
void fn_801F98CC_p17(); void fn_80209FE8_p17();
void fn_80218B5C_p17(MenuDisplay_p17 *); void fn_80218B80_p17(MenuDisplay_p17 *);
void fn_80218D98_p17(MenuDisplay_p17 *, int);
void SetTimerModeEnabled_p17(int); void SetCourseParams_p17(int,int,int,int);
int VSMode_SeedRandomItemSequence_p17(int,int,int);
int GetDisplayBufferIndex_p17();
int RaceSlot_InitSlot_p17(int, int, int, int, int);
int RaceSlot_SetItemSlotByte_p17(int, int, unsigned char);
void SetKartVariant_p17(int); void fn_801DC870_p17(int);
void fn_80121210_p17(); void clRom_PurgeAll_p17();
void MemoryManager_TimedFree_p17(void *);
void dtor_8002CDF4_p17(void *, int);
}
void *operator new(size_t size_p17);
void operator delete(void *p_p17) throw();
void *operator new[](size_t size_p17);
void operator delete[](void *p_p17) throw();
struct VObject_p17 {
virtual ~VObject_p17();
};
struct InputState_p17 {
char pad00_p17[4];
unsigned char enabled_p17;
char pad05_p17[0xF];
int dir_p17;
int held_p17;
int edge_p17;
};
extern "C"InputState_p17 *g_pInputState_p17;
static inline InputState_p17 *GetInput_p17() {
return g_pInputState_p17 == 0 ? (InputState_p17 *)0 : g_pInputState_p17;
}
template <class T_p17> struct VHolder_p17 {
T_p17 *p_p17;
VHolder_p17() : p_p17(0) {}
VHolder_p17(T_p17 *q_p17) : p_p17(q_p17) {}
~VHolder_p17() throw() { delete p_p17; }
void Reset_p17(T_p17 *q_p17) throw() {
if (p_p17 != q_p17) {
delete p_p17;
p_p17 = q_p17;
}
}
};
struct FlowRoot_p17 {
virtual void _key_p17();
int id_p17;
int field08_p17;
int field0C_p17;
FlowRoot_p17(int id__p17) : id_p17(id__p17), field08_p17(0), field0C_p17(0) {}
~FlowRoot_p17() {}
};
struct FlowTask_p17 : FlowRoot_p17 {
FlowTask_p17(int id_p17);
~FlowTask_p17();
virtual void Finish_p17();
virtual void Update_p17();
virtual void Draw_p17();
bool CanUpdate_p17() {
if (field08_p17 > 0) {
return 0;
}
return field0C_p17 <= 0;
}
};
struct TextManager_p17 {
char pad000_p17[0x18];
int visible_p17;
char pad01C_p17[4];
unsigned int color_p17;
char pad024_p17[0x22C - 0x24];
float scale_p17;
TextManager_p17();
~TextManager_p17();
};
extern "C"{
int isJapanese_p17(void);
void TexMgr_SetTexture_p17(TextManager_p17 *tm_p17, const char *fmt_p17, ...);
void fn_801F93EC_p17(TextManager_p17 *tm_p17, float x_p17, float y_p17);
void fn_801F8FCC_p17(TextManager_p17 *tm_p17, int mode_p17);
void fn_801F8E90_p17(TextManager_p17 *tm_p17);
void CreditMgr_SetActiveSlot_p17(int slot_p17);
int CreditMgr_GetCoinCount_p17(int slot_p17, int mode_p17);
}
struct ListNode_p17 {
ListNode_p17 *prev_p17;
ListNode_p17 *next_p17;
FlowTask_p17 *task_p17;
};
struct ListIter_p17 {
ListNode_p17 *node_p17;
ListIter_p17() {}
ListIter_p17(ListNode_p17 *n_p17) : node_p17(n_p17) {}
ListIter_p17 &operator=(const ListIter_p17 &o_p17) {
node_p17 = o_p17.node_p17;
return *this;
}
};
struct DoublyLinkedList_p17 {
int count_p17;
ListNode_p17 *last_p17;
ListNode_p17 *first_p17;
DoublyLinkedList_p17();
ListIter_p17 Erase_p17(ListIter_p17 it_p17);
ListNode_p17 *End_p17() { return (ListNode_p17 *)&last_p17; }
};
struct FlowSceneList_p17 {
virtual ~FlowSceneList_p17();
virtual void Update_p17();
virtual void Draw_p17();
DoublyLinkedList_p17 entries_p17;
FlowSceneList_p17() {}
};
struct SceneListImpl_p17 : FlowSceneList_p17 {
SceneListImpl_p17() {}
virtual void Update_p17();
virtual void Draw_p17();
virtual void _key2_p17();
void Sort_p17();
void Kill_p17(unsigned int id_p17);
ListIter_p17 Remove_p17(ListIter_p17 it_p17) { return entries_p17.Erase_p17(it_p17); }
};
extern "C"{
FlowTask_p17 *fn_801F4DC0_p17(FlowSceneList_p17 *list_p17, int id_p17);
void fn_801F4DF0_p17(FlowSceneList_p17 *list_p17, FlowTask_p17 *task_p17, int mode_p17);
void fn_801F4D3C_p17(FlowSceneList_p17 *list_p17);
}
struct FlowFader_p17 {
virtual ~FlowFader_p17();
short a_p17;
short b_p17;
FlowFader_p17() : a_p17(0), b_p17(0) {}
void Step_p17() {
b_p17++;
short lim_p17 = a_p17;
if (b_p17 >= lim_p17) {
b_p17 = lim_p17;
}
}
bool Done_p17() { return b_p17 >= a_p17; }
};
extern "C"const float lbl_806DA880_p17;
struct FlowFaderF_p17 : FlowFader_p17 {
float x_p17;
float y_p17;
float z_p17;
FlowFaderF_p17(float v_p17) : x_p17(v_p17), y_p17(v_p17), z_p17(v_p17) {}
FlowFaderF_p17() : x_p17(lbl_806DA880_p17), y_p17(lbl_806DA880_p17), z_p17(lbl_806DA880_p17) {}
virtual void _key2_p17();
float Value_p17();
void Set_p17(float from_p17, float to_p17, short dur_p17);
};
struct FlowFaderI_p17 : FlowFader_p17 {
int x_p17;
int y_p17;
int z_p17;
FlowFaderI_p17() : x_p17(0), y_p17(0), z_p17(0) {}
virtual void _key2_p17();
int Value_p17();
void Set_p17(int from_p17, int to_p17, short dur_p17);
};
struct FlowScene_p17 : FlowTask_p17 {
VHolder_p17<FlowSceneList_p17> list_p17;
VHolder_p17<FlowFaderI_p17> fader_p17;
int state_p17;
int subState_p17;
int timer_p17;
int cursor_p17;
FlowScene_p17(int id_p17);
~FlowScene_p17();
virtual void _key3_p17();
};
struct ResCtrl_p17 {
int resId_p17;
int field4_p17, mode_p17, fieldc_p17;
unsigned char flag_p17, pad11_p17[3];
float x_p17, y_p17, z_p17, width_p17, height_p17, field28_p17, scaleX_p17, scaleY_p17;
unsigned int colors_p17[4];
bool flipX_p17;
bool flipY_p17;
char pad46_p17[2];
int tail_p17[4];
ResCtrl_p17();
~ResCtrl_p17() {}
void Show_p17(float px_p17, float py_p17, float pz_p17) {
flag_p17 = 1;
x_p17 = px_p17;
y_p17 = py_p17;
z_p17 = pz_p17;
}
void SetScale_p17(float s_p17) {
scaleX_p17 = s_p17;
scaleY_p17 = s_p17;
}
void SetScaleXY_p17(float sx_p17, float sy_p17) {
scaleX_p17 = sx_p17;
scaleY_p17 = sy_p17;
}
void SetSize_p17(float w_p17, float h_p17) {
width_p17 = w_p17;
height_p17 = h_p17;
}
void SetColor_p17(unsigned int c_p17) {
colors_p17[0] = c_p17;
colors_p17[1] = c_p17;
colors_p17[2] = c_p17;
colors_p17[3] = c_p17;
}
void SetPos_p17(float px_p17, float py_p17, float pz_p17) {
x_p17 = px_p17;
y_p17 = py_p17;
z_p17 = pz_p17;
}
};
struct CourseSprite {
char pad0_p17[12]; float x_p17,y_p17; char tail_p17[0x30-0x14];
CourseSprite(int, int, int);
CourseSprite(int, int, float, float);
void SetPosition_p17(float px_p17, float py_p17) { x_p17=px_p17; y_p17=py_p17; }
};
struct CourseClassTask_p17 { char data_p17[0x58]; CourseClassTask_p17(); };
struct CourseCupTask_p17 { char data_p17[0x158]; CourseCupTask_p17(); };
struct CourseRoundTask_p17 { char data_p17[0x16C]; CourseRoundTask_p17(); };
struct CourseFrameTask_p17 { char data_p17[0x1D8]; CourseFrameTask_p17(); };
struct CourseEntryTask_p17 { char data_p17[0x14]; CourseEntryTask_p17(); };
struct CourseModeInit : GameModeBase_p17 {
unsigned char done_p17; char pad5_p17[3]; void *task_p17;
CourseModeInit();
};
extern "C"{
extern "C" { extern void *lbl_80679280[3]; extern void *lbl_8067928C[4]; extern unsigned short *lbl_8067929C[5]; }
#define lbl_80679280_p17 ((CourseSprite **)lbl_80679280)
#define lbl_8067928C_p17 ((CourseSprite **)lbl_8067928C)
#define lbl_8067929C_p17 ((short **)lbl_8067929C)
extern void *lbl_8049A734_p17[];
extern unsigned char lbl_806D17F0_p17, lbl_806D17F1_p17, lbl_806D17F2_p17, lbl_806D17F3_p17, lbl_806D17F4_p17;
extern int lbl_806CFD60_p17, lbl_806D17F8_p17, lbl_806D17FC_p17, lbl_806D1800_p17, lbl_806D1804_p17, lbl_806D1808_p17, lbl_806D180C_p17, lbl_806D1810_p17;
extern unsigned char lbl_806D1818_p17, lbl_806D1819_p17, lbl_806D184F_p17, lbl_806D1850_p17, lbl_806D1858_p17;
extern int lbl_806D1820_p17;
extern float lbl_806D1854_p17, lbl_806D1848_p17;
extern unsigned char lbl_806D184C_p17, lbl_806D184D_p17;
extern CourseSprite *lbl_806D1840_p17, *lbl_806D1844_p17;
extern const float lbl_806D9890_p17, lbl_806D98B8_p17, lbl_806D98E0_p17, lbl_806D9948_p17, lbl_806D994C_p17, lbl_806D9950_p17;
extern const float lbl_806D9954_p17, lbl_806D9958_p17, lbl_806D995C_p17, lbl_806D991C_p17;
void fn_8002CFB8_p17(int,int,int,int);
void fn_801DAE54_p17(); void fn_80121210_p17(); void clRom_PurgeAll_p17();
void ProcessSystemTick_p17(int); void PcbSlot_ResetScratchAreas_p17(); void CommBroadcast_ClearTable_p17(); void SyncSlot_Reset_p17();
void PreloadResource_p17(int); void SetScreenBrightness_p17(float);
short *fn_801A0310_p17(CourseSprite *, short);
void *StrPcb_GetInstance_p17(); void StrPcb_ForceRun_Neutral_p17(void *); void StrPcb_ResetCommands_Neutral_p17(void *, int);
int CountPeersWithRole_p17(int); void SetLocalPcbRole_p17(int); void SetTimerModeEnabled_p17(int);
unsigned char fn_801D5A68_p17(void *);
void fn_801B7CD0_p17(int);
char *fn_801DAEC0_p17();
}
extern "C"void Sprite_CreateWithParams_p17(CourseSprite *, int, int, float, float, float, float, float, float);
inline CourseSprite::CourseSprite(int a_p17, int b_p17, float x_p17, float y_p17) {
float scale_p17 = lbl_806D98E0_p17;
float zero_p17 = lbl_806D9890_p17;
Sprite_CreateWithParams_p17(this, a_p17, b_p17, x_p17, y_p17, scale_p17, scale_p17, zero_p17, zero_p17);
}
inline void CourseSetFlag(char *flag_p17) { *flag_p17 = 1; }
struct CourseInputImpl_p17 {
void *vt_p17; unsigned char enabled_p17, flag5_p17, flag6_p17; int fields_p17[8];
};
extern "C"{ extern void *lbl_803FDF28_p17[], *lbl_803FDF40_p17[]; void *Alloc_p17(unsigned long); }
inline void CourseEnsureInput() {
if (((g_pInputState_p17) == 0 ? 0 : (g_pInputState_p17)) == 0) {
CourseInputImpl_p17 *p_p17 = (CourseInputImpl_p17 *)Alloc_p17(0x28);
if (p_p17) {
p_p17->vt_p17 = lbl_803FDF28_p17;
g_pInputState_p17 = (InputState_p17 *)p_p17;
p_p17->vt_p17 = lbl_803FDF40_p17;
p_p17->enabled_p17=0; p_p17->flag5_p17=1; p_p17->flag6_p17=1;
p_p17->fields_p17[0]=0; p_p17->fields_p17[1]=0; p_p17->fields_p17[2]=0; p_p17->fields_p17[3]=0;
p_p17->fields_p17[4]=0; p_p17->fields_p17[5]=0; p_p17->fields_p17[6]=0; p_p17->fields_p17[7]=0;
}
}
StrPcb_ForceRun_Neutral_p17(StrPcb_GetInstance_p17());
StrPcb_ResetCommands_Neutral_p17(StrPcb_GetInstance_p17(), 1);
}
CourseModeInit::CourseModeInit() {
vt_p17=lbl_8049A734_p17;
fn_8002CFB8_p17(0,0,0,0);
delete (VObject_p17 *)g_pInputState_p17;
g_pInputState_p17=0;
fn_801DAE54_p17(); fn_80121210_p17(); clRom_PurgeAll_p17(); ProcessSystemTick_p17(0);
PcbSlot_ResetScratchAreas_p17(); CommBroadcast_ClearTable_p17(); SyncSlot_Reset_p17();
PreloadResource_p17(0x186E); PreloadResource_p17(0x186F); PreloadResource_p17(0x1870); PreloadResource_p17(0x1871);
PreloadResource_p17(0x1872); PreloadResource_p17(0x1873); PreloadResource_p17(0x1874); PreloadResource_p17(0x1875);
ProcessSystemTick_p17(0);
done_p17=0; lbl_806D17F3_p17=1; lbl_806D17F4_p17=0; lbl_806CFD60_p17=-1;
lbl_806D17F8_p17=0; lbl_806D17FC_p17=0; lbl_806D1800_p17=0; lbl_806D1804_p17=0;
lbl_806D1808_p17=0; lbl_806D180C_p17=0; lbl_806D1810_p17=0;
lbl_806D1818_p17=0; lbl_806D1819_p17=0; lbl_806D1820_p17=0;
lbl_806D184F_p17=0; lbl_806D1850_p17=0; lbl_806D1854_p17=lbl_806D9890_p17; lbl_806D1858_p17=0;
SetScreenBrightness_p17(lbl_806D98B8_p17);
lbl_80679280_p17[0]=new CourseSprite(0xA2,1,0);
lbl_80679280_p17[1]=new CourseSprite(0xA1,1,0);
lbl_80679280_p17[2]=new CourseSprite(0xA0,1,0);
lbl_8067929C_p17[0]=fn_801A0310_p17(lbl_80679280_p17[0],0x1842);
lbl_8067929C_p17[1]=fn_801A0310_p17(lbl_80679280_p17[0],0x1843);
lbl_8067929C_p17[2]=fn_801A0310_p17(lbl_80679280_p17[1],0x1842);
lbl_8067929C_p17[4]=fn_801A0310_p17(lbl_80679280_p17[2],0x184C);
lbl_8067928C_p17[0]=new CourseSprite(0xA6,1,0);
lbl_8067928C_p17[1]=new CourseSprite(0xA5,1,0);
lbl_8067928C_p17[2]=new CourseSprite(0xA4,1,0);
lbl_8067928C_p17[3]=new CourseSprite(0xA3,1,0);
{CourseSprite *s;
s=lbl_80679280_p17[0]; s->SetPosition_p17(lbl_806D9948_p17,lbl_806D994C_p17);
s=lbl_80679280_p17[1]; s->SetPosition_p17(lbl_806D9948_p17,lbl_806D994C_p17);
s=lbl_80679280_p17[2]; s->SetPosition_p17(lbl_806D9948_p17,lbl_806D994C_p17);
s=lbl_8067928C_p17[0]; s->SetPosition_p17(lbl_806D9948_p17,lbl_806D9950_p17);
s=lbl_8067928C_p17[1]; s->SetPosition_p17(lbl_806D9948_p17,lbl_806D9950_p17);
s=lbl_8067928C_p17[2]; s->SetPosition_p17(lbl_806D9948_p17,lbl_806D9950_p17);
s=lbl_8067928C_p17[3]; s->SetPosition_p17(lbl_806D9948_p17,lbl_806D9950_p17);
}
lbl_806D1840_p17=new CourseSprite(0x74,1,lbl_806D9954_p17,lbl_806D9958_p17);
lbl_806D1844_p17=new CourseSprite(0x4A,1,lbl_806D995C_p17,lbl_806D991C_p17);
lbl_806D1848_p17=lbl_806D9890_p17; lbl_806D184C_p17=0; lbl_806D184D_p17=9;
ProcessSystemTick_p17(0);
if (lbl_806D17F0_p17) {
if (lbl_806D17F1_p17) {
CourseEnsureInput();
if (CountPeersWithRole_p17(-1)==1) { SetLocalPcbRole_p17(0); g_gameMode_p17=0; SetTimerModeEnabled_p17(0); }
task_p17=new CourseClassTask_p17;
} else if (g_gameMode_p17==2) {
CourseEnsureInput(); g_gameMode_p17=0;
task_p17=new CourseClassTask_p17;
} else if (lbl_806D17F2_p17) {
CourseEnsureInput();
if (fn_801D5A68_p17(g_playerData_p17)) task_p17=new CourseCupTask_p17;
else task_p17=new CourseRoundTask_p17;
} else {
CourseEnsureInput(); task_p17=new CourseFrameTask_p17;
}
} else task_p17=new CourseEntryTask_p17;
lbl_806D17F0_p17=0; lbl_806D17F1_p17=0; lbl_806D17F2_p17=0;
fn_801B7CD0_p17(0);
CourseSetFlag(fn_801DAEC0_p17());
CourseSetFlag(fn_801DAEC0_p17()+0x12);
}
#pragma optimize_for_size reset
#pragma cplusplus reset
C_REGION_BEGIN
#pragma use_lmw_stmw reset
#pragma exceptions reset
C_REGION_END

