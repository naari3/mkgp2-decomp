#include "game/types/c_region.h"
C_REGION_BEGIN
/* 23 TUs merged by tools/merge_tus.py, .text 0x80094d80..0x80099994.
 * Each section is the preprocessed original TU with its names suffixed _pN
 * (tools/extab_user_renames.json maps the symbols back). */
/* ==== pool (tools/data2c.py) ==== */
extern char lbl_806D3578[];
extern char lbl_806D3580[];
/* element type read off the values (all floats), not from code */
static const float Sci2Card_BuildRetryReceiptLine_rodata_80317948[255] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f,
    0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f,
    83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f,
    83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f
};
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_80317D44[3] = { 0x20201125, 0x2D313173, 0x14000000 };
static const char lbl_80317D50[] = "             %s %s";
static const char lbl_80317D64[] = "                    %s";
static const char lbl_80317D7C[] = "              %5d";
static const char lbl_80317D90[] = "  %s %6s%s";
static const char lbl_80317D9C[] = " %4s%2s%2s%2s%2s";
/* The score receipt layout: one format string and its printer line per row. */
typedef struct ScoreReceiptFormat_p1 {
const char *format_p1;
unsigned char line_p1;
unsigned char reserved_p1[3];
} ScoreReceiptFormat_p1;
static const ScoreReceiptFormat_p1 Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[10] = {
    { (const char *)&Sci2Card_BuildRetryReceiptLine_rodata_80317D44, 0 },
    { (const char *)&lbl_80317D50, 0 },
    { (const char *)&lbl_80317D64, 0 },
    { (const char *)&lbl_80317D7C, 0 },
    { (const char *)&lbl_80317D90, 0 },
    { (const char *)&lbl_806D3578, 3 },
    { (const char *)&lbl_806D3578, 3 },
    { (const char *)&lbl_80317D9C, 6 },
    { (const char *)&lbl_80317D9C, 7 },
    { (const char *)&lbl_806D3580, 9 }
};
/* element type read off the values (all small integers), not from code */
static const int Sci2Card_BuildItemGetReceiptLine_rodata_80317E00[67] = {
    60, 60, 61, 62, 70, 75, 80, 85,
    90, 95, 100, 101, 106, 63, 64, 71,
    76, 81, 86, 91, 96, 102, 102, 107,
    65, 66, 72, 77, 82, 87, 92, 97,
    103, 103, 108, 67, 68, 73, 78, 83,
    88, 93, 98, 104, 104, 109, 69, 69,
    74, 79, 84, 89, 94, 99, 105, 105,
    110, 111, 112, 113, 114, 115, 116, 117,
    118, 119, 120
};
static const unsigned int Sci2Card_BuildItemGetReceiptLine_rodata_80317F0C[12] = { 0x0000002E, 0x00000030, 0x00000033, 0x0000002F, 0x00000031, 0x00000032, 0x00000034, 0x00000035, 0x00000036, 0x00000039, 0x00000037, 0x00000038 };
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_80317F3C[7] = { 0x25732573, 0x25738CC2, 0x20202020, 0x20202020, 0x20202020, 0x20202020, 0x20000000 };
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_80317F58[7] = { 0x25732573, 0x25738CC2, 0x208AEE96, 0x7BB1B2C3, 0xD1B9DEAF, 0xC4814920, 0x20000000 };
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_80317F74[7] = { 0x25732573, 0x25738CC2, 0x20BADEB0, 0xD9C4DEB1, 0xB2C3D1B9, 0xDEAFC481, 0x49000000 };
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_80317F90[7] = { 0x25732573, 0x25738CC2, 0x20CCDFD7, 0xBDB1B2C3, 0xD1B9DEAF, 0xC4814920, 0x20000000 };
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_80317FAC[7] = { 0x25732573, 0x25738CC2, 0x20BDCDDF, 0xBCACD9B1, 0xB2C3D1B9, 0xDEAFC481, 0x49000000 };
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_80317FC8[7] = { 0x25732573, 0x25738CC2, 0x2081998E, 0x6382E825, 0x738CC281, 0x99202020, 0x20000000 };
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_80317FE4[7] = { 0x82508250, 0x82558CC2, 0x20819AB1, 0xB2C3D1BA, 0xDDCCDFD8, 0xB0C48149, 0x20000000 };
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_80318000[7] = { 0x25732573, 0x25738CC2, 0x20C4D8CC, 0xDFD9B1B2, 0xC3D1B9DE, 0xAFC48149, 0x20000000 };
static const char lbl_8031801C[] = "%s%s%s                   ";
static const char lbl_80318038[] = "%s%s%s Basic Item Get!   ";
static const char lbl_80318054[] = "%s%s%s Gold Item Get!    ";
static const char lbl_80318070[] = "%s%s%s Plus Item Get!    ";
static const char lbl_8031808C[] = "%s%s%s SP Item Get!      ";
static const char lbl_803180A8[] = "%s%s%s %s more left      ";
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_803180C4[7] = { 0x82508250, 0x82552069, 0x74656D20, 0x636F6D70, 0x6C657465, 0x20202020, 0x20000000 };
static const unsigned int lbl_803180E0[7] = { 0x25732573, 0x25732074, 0x7269706C, 0x65206974, 0x656D2067, 0x65742020, 0x20000000 };
static const unsigned int lbl_803180FC[3] = { 0x826D8260, 0x826C8262, 0x826E0000 };
static const unsigned int Sci2Card_BuildScoreReceiptLine_rodata_80318108[3] = { 0x91CE90ED, 0x838C815B, 0x83580000 };
static const unsigned int lbl_80318114[3] = { 0x54455354, 0x20505249, 0x4E540000 };
static const unsigned int lbl_80318120[6] = { 0x82738264, 0x82728273, 0x8140826F, 0x82718268, 0x826D8273, 0x00000000 };
static const unsigned int Sci2Card_GetReceiptStringEntry_rodata_80318138[78] = { 0x1B67011B, 0x67020000, 0x00000000, 0x001B6707, 0x1B670800, 0x00000000, 0x00001B67, 0x091B670A, 0x00000000, 0x0000001B, 0x670B1B67, 0x0C000000, 0x00000000, 0x1B670D1B, 0x670E0000, 0x00000000, 0x001B670F, 0x1B671000, 0x00000000, 0x00001B67, 0x031B6704, 0x00000000, 0x0000001B, 0x67051B67, 0x06000000, 0x00000000, 0x1B67111B, 0x67120000, 0x00000000, 0x001B6717, 0x1B671800, 0x00000000, 0x00001B67, 0x191B671A, 0x00000000, 0x0000001B, 0x671B1B67, 0x1C000000, 0x00000000, 0x1B671D1B, 0x671E0000, 0x00000000, 0x001B671F, 0x1B672000, 0x00000000, 0x00001B67, 0x131B6714, 0x00000000, 0x0000001B, 0x67151B67, 0x16000000, 0x00000000, 0x1B67211B, 0x67221B67, 0x231B6724, 0x001B6725, 0x1B67261B, 0x67271B67, 0x28001B67, 0x291B672A, 0x1B672B1B, 0x672C001B, 0x672D1B67, 0x2E1B672F, 0x1B673000, 0x1B67311B, 0x67321B67, 0x331B6734, 0x001B6735, 0x1B67361B, 0x67371B67, 0x38001B67, 0x391B673A, 0x1B673B00, 0x0000001B, 0x673C1B67, 0x3D1B673E, 0x00000000 };

/* ItemGet receipt tables (.data 0x803FFDF0): defined before the first function so they precede the switch tables. */
extern const char lbl_806D35D4_p19[3];
extern const char lbl_806D35E4_p19[4];
extern const char lbl_806D3594_p19[];
extern const char lbl_806D3598_p19[];
extern const char lbl_806D359C_p19[];
extern const char lbl_806D35A0_p19[];
extern const char lbl_806D35A4_p19[];
extern const char lbl_806D35A8_p19[];
extern const char lbl_806D35AC_p19[];
extern const char lbl_806D35B0_p19[];
extern const char lbl_806D35B4_p19[];
extern const char lbl_806D35B8_p19[];
const char *lbl_803FFDF0_p19[10] = {
lbl_806D3594_p19, lbl_806D3598_p19, lbl_806D359C_p19, lbl_806D35A0_p19, lbl_806D35A4_p19, lbl_806D35A8_p19, lbl_806D35AC_p19, lbl_806D35B0_p19, lbl_806D35B4_p19, lbl_806D35B8_p19
};
static const char *receiptEnglish_p19[8] = {
(*(const char (*)[])&Sci2Card_BuildRetryReceiptLine_rodata_80317F3C), (*(const char (*)[])&Sci2Card_BuildRetryReceiptLine_rodata_80317F58), (*(const char (*)[])&Sci2Card_BuildRetryReceiptLine_rodata_80317F74), (*(const char (*)[])&Sci2Card_BuildRetryReceiptLine_rodata_80317F90), (*(const char (*)[])&Sci2Card_BuildRetryReceiptLine_rodata_80317FAC), (*(const char (*)[])&Sci2Card_BuildRetryReceiptLine_rodata_80317FC8), (*(const char (*)[])&Sci2Card_BuildRetryReceiptLine_rodata_80317FE4), (*(const char (*)[])&Sci2Card_BuildRetryReceiptLine_rodata_80318000)
};
static const char *receiptJapanese_p19[8] = {
(*(const char (*)[])&lbl_8031801C), (*(const char (*)[])&lbl_80318038), (*(const char (*)[])&lbl_80318054), (*(const char (*)[])&lbl_80318070), (*(const char (*)[])&lbl_8031808C), (*(const char (*)[])&lbl_803180A8), (*(const char (*)[])&Sci2Card_BuildRetryReceiptLine_rodata_803180C4), (*(const char (*)[])&lbl_803180E0)
};

/* ==== game/Sci2Card_BuildRetryReceiptLine.c (0x80094d80) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
extern void *Sci2Card_Singleton_Get_p0(void);
extern unsigned char Sci2Card_IsIdleOrExhausted_p0(void *card_p0);
extern unsigned char Sci2Card_IsStatusOkNonTerm_p0(void *card_p0);
extern unsigned char Sci2Card_IsStatus3Five_p0(void *card_p0);
extern unsigned char Sci2Card_IsRetryExhausted_p0(void *card_p0);
extern unsigned char Sci2Card_IsStatus2Two_p0(void *card_p0);
extern unsigned char Sci2Card_IsStatus2One_p0(void *card_p0);
extern unsigned char Sci2Card_IsStatus2Three_p0(void *card_p0);
extern unsigned char Sci2Card_IsStatus2Five_p0(void *card_p0);
extern unsigned char Sci2Card_IsStatus2A_p0(void *card_p0);
extern void Sci2Card_GetResponseStatus_p0(void *card_p0, unsigned char *a_p0, unsigned char *b_p0, unsigned char *c_p0);
extern unsigned char ServiceLatch_CheckTriggered_p0(void);
extern unsigned char Sci2Card_IsStatus3Zero_p0(void *card_p0);
extern int Sci2Card_BuildScoreReceiptLine_p0(int line_p0);
extern int Sci2Card_BuildRetryReceiptLine(int line_p0);
unsigned char Sci2Card_PrintReceipt_PollState_p0(void);
unsigned char Sci2Card_PrintReceipt_StartFlow_p0(int mode_p0, unsigned char header_p0, unsigned char retry_p0);
extern int lbl_806D1210_p0;
extern int lbl_806CF0DC_p0;
extern int lbl_806CF0E0_p0;
extern int lbl_806CF0E4_p0;
extern int lbl_806CF0E8_p0;
extern int lbl_806CF0EC_p0;
extern int lbl_806D1214_p0;
extern int lbl_806D1218_p0;
extern unsigned char lbl_806D121C_p0;
extern unsigned char lbl_806D1228_p0;
extern unsigned char lbl_806D1229_p0;
extern unsigned char lbl_806D122A_p0;
extern unsigned char lbl_806D122B_p0;
extern int lbl_806D123C_p0;
extern signed char g_playerData_p0[];
static inline void Sci2Card_SetFailCode_p0(void)
{
void *card_p0 = Sci2Card_Singleton_Get_p0();
unsigned char status1_p0;
unsigned char status2_p0;
unsigned char status3_p0;
lbl_806D1210_p0 = 0;
if (Sci2Card_IsStatus3Five_p0(card_p0) == 1) {
lbl_806D1210_p0 = 2;
}
if (Sci2Card_IsRetryExhausted_p0(card_p0) == 1) {
lbl_806D1210_p0 = 101;
}
if (Sci2Card_IsStatus2Two_p0(card_p0) == 1) {
lbl_806D1210_p0 = 102;
}
if (Sci2Card_IsStatus2One_p0(card_p0) == 1) {
lbl_806D1210_p0 = 103;
}
if (Sci2Card_IsStatus2Three_p0(card_p0) == 1) {
lbl_806D1210_p0 = 104;
}
if (Sci2Card_IsStatus2Five_p0(card_p0) == 1) {
lbl_806D1210_p0 = 105;
}
if (Sci2Card_IsStatus2A_p0(card_p0) == 1) {
lbl_806D1210_p0 = 106;
}
if (lbl_806D1210_p0 == 0) {
Sci2Card_GetResponseStatus_p0(card_p0, &status1_p0, &status2_p0, &status3_p0);
if (status3_p0 == 50) {
lbl_806D1210_p0 = 100;
} else {
lbl_806D1210_p0 = 1;
}
}
}
static inline unsigned char Receipt_IsDone_p0(int line_p0)
{
unsigned char done_p0 = 0;
if (line_p0 >= 9 && lbl_806CF0EC_p0 == 1) {
done_p0 = 1;
} else if (line_p0 >= 10) {
done_p0 = 1;
} else if (line_p0 >= 2 && lbl_806CF0EC_p0 == 0) {
done_p0 = 1;
}
return done_p0;
}
static inline void Receipt_BuildLine_p0(int line_p0)
{
int next_p0;
if (lbl_806D122B_p0 == 0) {
next_p0 = Sci2Card_BuildScoreReceiptLine_p0(line_p0);
} else {
next_p0 = Sci2Card_BuildRetryReceiptLine(line_p0);
}
lbl_806D1218_p0 = next_p0;
}
static inline unsigned char Receipt_Advance_p0(void)
{
int line_p0 = lbl_806D1218_p0;
if (Receipt_IsDone_p0(line_p0) == 1) {
lbl_806D122A_p0 = 0;
lbl_806D1210_p0 = 1;
lbl_806D122B_p0 = 0;
return 1;
}
Receipt_BuildLine_p0(line_p0);
return 0;
}
static inline unsigned char Receipt_StartFlow_p0(int mode_p0, unsigned char header_p0, unsigned char retry_p0)
{
lbl_806D122B_p0 = retry_p0;
if (!ServiceLatch_CheckTriggered_p0()) {
lbl_806D122A_p0 = 1;
lbl_806D121C_p0 = 0;
lbl_806CF0E4_p0 = 5;
lbl_806D1210_p0 = 1;
return 1;
}
lbl_806CF0EC_p0 = mode_p0;
lbl_806D1210_p0 = 0;
lbl_806D122A_p0 = 1;
lbl_806D121C_p0 = 0;
lbl_806CF0E4_p0 = 5;
lbl_806D1218_p0 = 0;
lbl_806D123C_p0 = 0;
Sci2Card_Singleton_Get_p0();
if (lbl_806CF0EC_p0 == 0 || lbl_806CF0EC_p0 == 3) {
if (header_p0 == 1) {
Receipt_BuildLine_p0(-3);
} else {
Receipt_BuildLine_p0(0);
}
} else {
lbl_806D1218_p0 = lbl_806CF0EC_p0 == 2 ? 9 : 2;
if (Receipt_Advance_p0() == 1) {
return 1;
}
}
return 1;
}
static inline unsigned char Receipt_PollState_p0(void)
{
void *card_p0;
unsigned char status1_p0;
unsigned char status2_p0;
unsigned char status3_p0;
if (!ServiceLatch_CheckTriggered_p0()) {
lbl_806D1210_p0 = 1;
return 1;
}
if (lbl_806D1210_p0 != 0) {
return 1;
}
card_p0 = Sci2Card_Singleton_Get_p0();
Sci2Card_GetResponseStatus_p0(Sci2Card_Singleton_Get_p0(), &status1_p0, &status2_p0, &status3_p0);
if (Sci2Card_IsIdleOrExhausted_p0(card_p0) == 1) {
if (!Sci2Card_IsStatusOkNonTerm_p0(card_p0)) {
Sci2Card_SetFailCode_p0();
return 1;
}
if (Sci2Card_IsStatus3Zero_p0(card_p0) == 1) {
if (Receipt_Advance_p0() == 1) {
lbl_806D122A_p0 = 0;
lbl_806D1210_p0 = 1;
lbl_806D122B_p0 = 0;
return 1;
}
}
}
return 0;
}
extern void *memset_p0(void *, int, unsigned long);
extern int sprintf_p0(char *, const char *, ...);
extern char *strcat_p0(char *, const char *);
extern int isJapanese_p0(void);
extern const char *Sci2Card_GetReceiptStringEntry_p0(int);
extern void Sci2Card_SendCmdLedSet_p0(void *, int, int);
extern void Sci2Card_SendCmdRegister_p0(void *, char *, unsigned char, unsigned char, unsigned char);

extern const char *lbl_803FFDF0_p0[];
extern const char *lbl_806CF0F0_p0[2];
extern unsigned char lbl_806D1225_p0;
extern char lbl_806D1230_p0[7];
extern const char lbl_806D35BC_p0[2], lbl_806D35C0_p0[4], lbl_806D35C4_p0[3];
extern const char lbl_806D35C8_p0[7], lbl_806D35D0_p0[4], lbl_806D35D4_p0[3];
extern const char lbl_806D35D8_p0[4], lbl_806D35DC_p0[5];
typedef struct RetryReceiptFormat_p0 {
const char *format_p0;
unsigned char rows_p0;
unsigned char reserved_p0[3];
} RetryReceiptFormat_p0;
static inline const char *Retry_WinLabel_p0(void) { if (isJapanese_p0() == 0) return (const char *)Sci2Card_BuildScoreReceiptLine_rodata_80318108; return lbl_806D35C8_p0; }
static inline char *Retry_WinDigits_p0(void)
{
char number_p0[4];
char *cursor_p0;
int i_p0;
memset_p0(lbl_806D1230_p0, 0, 7);
sprintf_p0(number_p0, lbl_806D35D0_p0, 999);

for (i_p0 = 0; i_p0 < 3; ++i_p0) {
if (number_p0[i_p0] != ' ') strcat_p0(lbl_806D1230_p0, lbl_803FFDF0_p0[number_p0[i_p0] - '0']);
else strcat_p0(lbl_806D1230_p0, lbl_806D35D4_p0);
}
return lbl_806D1230_p0;
}
static inline const char *Retry_Text_p0(int i) { return Sci2Card_GetReceiptStringEntry_p0(i); }
int Sci2Card_BuildRetryReceiptLine(int line_p0)
{
char output_p0[0x1400];
char scratch_p0[0x200];
unsigned char finish_p0 = 0;
unsigned char update_p0 = 0;
void *card_p0 = Sci2Card_Singleton_Get_p0();
if (line_p0 < 0) {
if (lbl_806D1225_p0 == 0) Sci2Card_SendCmdLedSet_p0(card_p0, 12, 1);
return line_p0 + 1;
}
memset_p0(output_p0, 0, 0x1400);
switch (line_p0) {
case 0:
memset_p0(scratch_p0, 0, 0x200) ;
sprintf_p0(output_p0, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0].format_p1 , (const char *)lbl_803180FC);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
break;
case 1: {
const char *text_p0;
memset_p0(scratch_p0, 0, 0x200) ;
if (isJapanese_p0() == 0) text_p0 = Sci2Card_GetReceiptStringEntry_p0(22);
else text_p0 = Sci2Card_GetReceiptStringEntry_p0(23);
sprintf_p0(scratch_p0, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0].format_p1 , text_p0, lbl_806D35C0_p0);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35C4_p0);
++line_p0;
break;
}
case 2:
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
{ const char *text_p0 = lbl_806CF0F0_p0[isJapanese_p0()];
sprintf_p0(scratch_p0, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0].format_p1 , text_p0); }
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
case 3:
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
sprintf_p0(scratch_p0, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0].format_p1 , 99999);
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
case 4: {
const char *label_p0;
char *digits_p0;
const char *suffix_p0;
memset_p0(scratch_p0, 0, 0x200) ;
label_p0 = Retry_WinLabel_p0();
digits_p0 = Retry_WinDigits_p0();
suffix_p0 = isJapanese_p0() == 0 ? lbl_806D35D8_p0 : lbl_806D35DC_p0;
sprintf_p0(scratch_p0, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0].format_p1 , label_p0, digits_p0, suffix_p0);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
break;
}
case 5:
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
sprintf_p0(scratch_p0, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0].format_p1 , (const char *)lbl_80318114);
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
case 6:
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
sprintf_p0(scratch_p0, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0].format_p1 , (const char *)lbl_80318120);
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35C4_p0);
++line_p0;
break;
case 7: {
const char *a_p0, *b_p0, *c_p0, *d_p0;
memset_p0(scratch_p0, 0, 0x200) ;
a_p0 = Retry_Text_p0(6);
b_p0 = Retry_Text_p0(0);
c_p0 = Retry_Text_p0(7);
d_p0 = Retry_Text_p0(1);
sprintf_p0(scratch_p0, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0].format_p1 , Sci2Card_GetReceiptStringEntry_p0(18), a_p0, b_p0, c_p0, d_p0);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
break;
}
case 8: {
const char *a_p0, *b_p0, *c_p0, *d_p0;
memset_p0(scratch_p0, 0, 0x200) ;
a_p0 = Retry_Text_p0(2);
b_p0 = Retry_Text_p0(3);
c_p0 = Retry_Text_p0(4);
d_p0 = Retry_Text_p0(5);
sprintf_p0(scratch_p0, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0].format_p1 , Sci2Card_GetReceiptStringEntry_p0(19), a_p0, b_p0, c_p0, d_p0);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
break;
}
case 9: {
finish_p0 = 1;
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
{ int i_p0; for (i_p0 = 0; i_p0 < 25; i_p0++) scratch_p0[i_p0] = 'A'; scratch_p0[i_p0] = 0; }
strcat_p0(output_p0, scratch_p0) ;
++line_p0;
break;
}
default: return line_p0;
}
Sci2Card_SendCmdRegister_p0(card_p0, output_p0,
(unsigned char)(Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p0 - 1].line_p1 + 1),
finish_p0, update_p0);
return line_p0;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_BuildScoreReceiptLine.c (0x80095388) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
typedef struct ScoreReceiptPlayer_p1 {
char name_p1[13];
unsigned char item_p1;
unsigned short wins_p1;
unsigned char pad10_p1[4];
unsigned int raceTime_p1;
unsigned char cup_p1, longRound_p1, reverse_p1;
unsigned char pad1B_p1;
int ccClass_p1, character_p1, kart_p1;
unsigned char pad28_p1[0x199 - 0x28];
unsigned char hasTitle_p1;
unsigned char pad19A_p1;
unsigned char b19B_p1, b19C_p1;
unsigned char pad19D_p1[0x1B1 - 0x19D];
unsigned char b1B1_p1;
} ScoreReceiptPlayer_p1;
extern ScoreReceiptPlayer_p1 g_playerData_p1;

extern const char *lbl_803FFDF0_p1[26];
extern const char *lbl_806CF0F0_p1[2];
extern unsigned char lbl_806D1225_p1;
extern char lbl_806D1230_p1[7];
extern int lbl_806D123C_p1;
extern void *lbl_806D10A0_p1;
extern const char lbl_806D3580_p1[3], lbl_806D35BC_p1[2], lbl_806D35C0_p1[4];
extern const char lbl_806D35C4_p1[3], lbl_806D35C8_p1[7], lbl_806D35D0_p1[4];
extern const char lbl_806D35D4_p1[3], lbl_806D35D8_p1[4], lbl_806D35DC_p1[5];
extern const char lbl_806D35E4_p1[4], lbl_806D35E8_p1[5];

extern const float lbl_806D35F0_p1;
extern void *Sci2Card_Singleton_Get_p1(void);
extern unsigned char Sci2Card_SendCmdLedSet_p1(void *, unsigned char, unsigned char);
extern unsigned char Sci2Card_SendCmdRegister_p1(void *, char *, unsigned char, unsigned char, unsigned char);
extern void *memset_p1(void *, int, unsigned long);
extern int sprintf_p1(char *, const char *, ...);
extern char *strcat_p1(char *, const char *);
extern int isJapanese_p1(void);
extern char *Sci2Card_GetReceiptStringEntry_p1(int);
extern int GetCoinMilage_p1(ScoreReceiptPlayer_p1 *);
extern char *get_title_name_global_p1(void *);
extern char *Sci2Card_BuildItemGetReceiptLine_p1(void);
extern void Sci2Card_PopulateRankRowByMode_p1(int *, unsigned char *, unsigned char *);
extern void fn_8018CC64_p1(void);
extern char *fn_8018B2E4_p1(void);
extern char *fn_8018B300_p1(void);
extern void fn_8018B31C_p1(ScoreReceiptPlayer_p1 *, int, int, int, int, int, int, int, int, int, int, int, float);
static inline void *Receipt_TitleTracker_p1(void)
{
void *tracker_p1 = lbl_806D10A0_p1;
if (tracker_p1 == 0) return 0;
return tracker_p1;
}
static inline const char *Receipt_RankText_p1(unsigned char flag_p1, unsigned char mode_p1, int rank_p1)
{
int offset_p1 = 8;
if (mode_p1 == 0) offset_p1 = 0;
if (flag_p1 == 0) return lbl_806D35E8_p1;
return Sci2Card_GetReceiptStringEntry_p1(offset_p1 + rank_p1);
}
static inline const char *Receipt_WinDigits_p1(void)
{
char number_p1[4];
char *numberCursor_p1;
int i_p1;
int wins_p1 = g_playerData_p1.wins_p1;
memset_p1(lbl_806D1230_p1, 0, 7);
sprintf_p1(number_p1, lbl_806D35D0_p1, wins_p1 > 999 ? 999 : wins_p1);
numberCursor_p1 = number_p1;
for (i_p1 = 0; i_p1 < 3; i_p1++, numberCursor_p1++) {
if (*numberCursor_p1 != ' ') strcat_p1(lbl_806D1230_p1, lbl_803FFDF0_p1[*numberCursor_p1 - '0']);
else strcat_p1(lbl_806D1230_p1, lbl_806D35D4_p1);
}
return lbl_806D1230_p1;
}
int Sci2Card_BuildScoreReceiptLine(int line_p1)
{
char output_p1[0x1400];
char row_p1[0x200];
char scratch_p1[0x200];
int key7_p1;
int key8_p1;
unsigned char final_p1 = 0;
unsigned char highlight_p1 = 0;
void *card_p1 = Sci2Card_Singleton_Get_p1();
if (line_p1 < 0) {
if (lbl_806D1225_p1 == 0) Sci2Card_SendCmdLedSet_p1(card_p1, 12, 1);
return line_p1 + 1;
}
memset_p1(output_p1, 0, sizeof(output_p1));
switch (line_p1) {
case 0:
memset_p1(row_p1, 0, sizeof(row_p1));
sprintf_p1(output_p1, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1].format_p1, &g_playerData_p1);
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
strcat_p1(output_p1, lbl_806D35BC_p1);
line_p1++;
break;
case 1:
memset_p1(row_p1, 0, sizeof(row_p1));
sprintf_p1(scratch_p1, lbl_806D35C0_p1);
{
const char *text_p1;
if (isJapanese_p1() == 0) text_p1 = Sci2Card_GetReceiptStringEntry_p1(22);
else text_p1 = Sci2Card_GetReceiptStringEntry_p1(23);
sprintf_p1(row_p1, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1].format_p1, text_p1, scratch_p1);
}
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
strcat_p1(output_p1, row_p1);
strcat_p1(output_p1, lbl_806D35C4_p1);
line_p1++;
break;
case 2:
memset_p1(row_p1, 0, sizeof(row_p1));
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
{
const char *title_p1;
if (g_playerData_p1.hasTitle_p1 == 0) title_p1 = lbl_806D35E4_p1;
else title_p1 = lbl_806CF0F0_p1[isJapanese_p1()];
sprintf_p1(row_p1, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1].format_p1, title_p1);
}
strcat_p1(output_p1, row_p1);
strcat_p1(output_p1, lbl_806D35BC_p1);
line_p1++;
case 3:
memset_p1(row_p1, 0, sizeof(row_p1));
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
sprintf_p1(row_p1, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1].format_p1, GetCoinMilage_p1(&g_playerData_p1));
strcat_p1(output_p1, row_p1);
strcat_p1(output_p1, lbl_806D35BC_p1);
line_p1++;
case 4:
if (g_playerData_p1.wins_p1 != 0) {
const char *label_p1;
const char *digits_p1;
const char *suffix_p1;
memset_p1(row_p1, 0, sizeof(row_p1));
label_p1 = isJapanese_p1() == 0 ? (*(const char (*)[])&Sci2Card_BuildScoreReceiptLine_rodata_80318108) : lbl_806D35C8_p1;
digits_p1 = Receipt_WinDigits_p1();
suffix_p1 = isJapanese_p1() == 0 ? lbl_806D35D8_p1 : lbl_806D35DC_p1;
sprintf_p1(row_p1, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1].format_p1, label_p1, digits_p1, suffix_p1);
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
strcat_p1(output_p1, row_p1);
strcat_p1(output_p1, lbl_806D35BC_p1);
} else strcat_p1(output_p1, lbl_806D35BC_p1);
line_p1++;
break;
case 5:
memset_p1(row_p1, 0, sizeof(row_p1));
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
{
void *title_p1 = Receipt_TitleTracker_p1();
const char *text_p1;
if (title_p1 == 0) text_p1 = lbl_806D35E4_p1;
else text_p1 = get_title_name_global_p1(title_p1);
sprintf_p1(row_p1, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1].format_p1, text_p1);
}
strcat_p1(output_p1, row_p1);
strcat_p1(output_p1, lbl_806D35BC_p1);
line_p1++;
case 6:
memset_p1(row_p1, 0, sizeof(row_p1));
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
sprintf_p1(row_p1, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1].format_p1, Sci2Card_BuildItemGetReceiptLine_p1());
strcat_p1(output_p1, row_p1);
strcat_p1(output_p1, lbl_806D35C4_p1);
line_p1++;
break;
case 7:
memset_p1(row_p1, 0, sizeof(row_p1));
{
unsigned char mode_p1;
unsigned char ranks_p1[8];
const char *a_p1;
const char *b_p1;
const char *c_p1;
const char *d_p1;
int i_p1;
key7_p1 = 0;
mode_p1 = 0;
for (i_p1 = 0; i_p1 < 8; i_p1++) ranks_p1[i_p1] = 0;
Sci2Card_PopulateRankRowByMode_p1(&key7_p1, ranks_p1, &mode_p1);
a_p1 = Receipt_RankText_p1(ranks_p1[6], mode_p1, 6);
b_p1 = Receipt_RankText_p1(ranks_p1[0], mode_p1, 0);
c_p1 = Receipt_RankText_p1(ranks_p1[7], mode_p1, 7);
d_p1 = Receipt_RankText_p1(ranks_p1[1], mode_p1, 1);
sprintf_p1(row_p1, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1].format_p1, Sci2Card_GetReceiptStringEntry_p1(key7_p1 * 2 + 16), a_p1, b_p1, c_p1, d_p1);
}
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
strcat_p1(output_p1, row_p1);
strcat_p1(output_p1, lbl_806D35BC_p1);
line_p1++;
break;
case 8:
memset_p1(row_p1, 0, sizeof(row_p1));
{
unsigned char mode_p1;
unsigned char ranks_p1[8];
const char *a_p1;
const char *b_p1;
const char *c_p1;
const char *d_p1;
int i_p1;
key8_p1 = 0;
mode_p1 = 0;
for (i_p1 = 0; i_p1 < 8; i_p1++) ranks_p1[i_p1] = 0;
Sci2Card_PopulateRankRowByMode_p1(&key8_p1, ranks_p1, &mode_p1);
a_p1 = Receipt_RankText_p1(ranks_p1[2], mode_p1, 2);
b_p1 = Receipt_RankText_p1(ranks_p1[3], mode_p1, 3);
c_p1 = Receipt_RankText_p1(ranks_p1[4], mode_p1, 4);
d_p1 = Receipt_RankText_p1(ranks_p1[5], mode_p1, 5);
sprintf_p1(row_p1, Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1].format_p1, Sci2Card_GetReceiptStringEntry_p1(key8_p1 * 2 + 17), a_p1, b_p1, c_p1, d_p1);
}
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
strcat_p1(output_p1, row_p1);
strcat_p1(output_p1, lbl_806D35BC_p1);
line_p1++;
break;
case 9:
final_p1 = 1;
if (lbl_806D1225_p1 == 0) {
ScoreReceiptPlayer_p1 *player_p1;
char *record_p1;
memset_p1(row_p1, 0, sizeof(row_p1));
if (lbl_806D123C_p1 == line_p1) highlight_p1 = 1;
player_p1 = &g_playerData_p1;
fn_8018CC64_p1();
record_p1 = fn_8018B2E4_p1();
if (record_p1 == 0) {
fn_8018B31C_p1(player_p1, player_p1->character_p1, player_p1->kart_p1, player_p1->ccClass_p1,
player_p1->cup_p1, player_p1->longRound_p1, player_p1->reverse_p1, GetCoinMilage_p1(player_p1),
player_p1->b19B_p1, player_p1->b19C_p1, player_p1->b1B1_p1, 0, player_p1->raceTime_p1 / lbl_806D35F0_p1);
record_p1 = fn_8018B300_p1();
}
if (record_p1 != 0) {
sprintf_p1(row_p1, lbl_806D3580_p1, record_p1);
strcat_p1(output_p1, row_p1);
}
line_p1++;
} else line_p1++;
break;
default:
return line_p1;
}
Sci2Card_SendCmdRegister_p1(card_p1, output_p1, (unsigned char)(Sci2Card_BuildScoreReceiptLine_rodata_80317DB0[line_p1 - 1].line_p1 + 1), final_p1, highlight_p1);
return line_p1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_WriteTrackData.c (0x80095c5c) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
extern void *Sci2Card_Singleton_Get_p2(void);
extern unsigned char Sci2Card_IsIdleOrExhausted_p2(void *card_p2);
extern unsigned char Sci2Card_IsStatusOkNonTerm_p2(void *card_p2);
extern unsigned char Sci2Card_IsStatus3Five_p2(void *card_p2);
extern unsigned char Sci2Card_IsRetryExhausted_p2(void *card_p2);
extern unsigned char Sci2Card_IsStatus2Two_p2(void *card_p2);
extern unsigned char Sci2Card_IsStatus2One_p2(void *card_p2);
extern unsigned char Sci2Card_IsStatus2Three_p2(void *card_p2);
extern unsigned char Sci2Card_IsStatus2Five_p2(void *card_p2);
extern unsigned char Sci2Card_IsStatus2A_p2(void *card_p2);
extern void Sci2Card_GetResponseStatus_p2(void *card_p2, unsigned char *a_p2, unsigned char *b_p2, unsigned char *c_p2);
extern unsigned char ServiceLatch_CheckTriggered_p2(void);
extern unsigned char Sci2Card_IsStatus3Zero_p2(void *card_p2);
extern int Sci2Card_BuildScoreReceiptLine_p2(int line_p2);
extern int Sci2Card_BuildRetryReceiptLine_p2(int line_p2);
unsigned char Sci2Card_PrintReceipt_PollState_p2(void);
unsigned char Sci2Card_PrintReceipt_StartFlow_p2(int mode_p2, unsigned char header_p2, unsigned char retry_p2);
extern int lbl_806D1210_p2;
extern int lbl_806CF0DC_p2;
extern int lbl_806CF0E0_p2;
extern int lbl_806CF0E4_p2;
extern int lbl_806CF0E8_p2;
extern int lbl_806CF0EC_p2;
extern int lbl_806D1214_p2;
extern int lbl_806D1218_p2;
extern unsigned char lbl_806D121C_p2;
extern unsigned char lbl_806D1228_p2;
extern unsigned char lbl_806D1229_p2;
extern unsigned char lbl_806D122A_p2;
extern unsigned char lbl_806D122B_p2;
extern int lbl_806D123C_p2;
extern signed char g_playerData_p2[];
static inline void Sci2Card_SetFailCode_p2(void)
{
void *card_p2 = Sci2Card_Singleton_Get_p2();
unsigned char status1_p2;
unsigned char status2_p2;
unsigned char status3_p2;
lbl_806D1210_p2 = 0;
if (Sci2Card_IsStatus3Five_p2(card_p2) == 1) {
lbl_806D1210_p2 = 2;
}
if (Sci2Card_IsRetryExhausted_p2(card_p2) == 1) {
lbl_806D1210_p2 = 101;
}
if (Sci2Card_IsStatus2Two_p2(card_p2) == 1) {
lbl_806D1210_p2 = 102;
}
if (Sci2Card_IsStatus2One_p2(card_p2) == 1) {
lbl_806D1210_p2 = 103;
}
if (Sci2Card_IsStatus2Three_p2(card_p2) == 1) {
lbl_806D1210_p2 = 104;
}
if (Sci2Card_IsStatus2Five_p2(card_p2) == 1) {
lbl_806D1210_p2 = 105;
}
if (Sci2Card_IsStatus2A_p2(card_p2) == 1) {
lbl_806D1210_p2 = 106;
}
if (lbl_806D1210_p2 == 0) {
Sci2Card_GetResponseStatus_p2(card_p2, &status1_p2, &status2_p2, &status3_p2);
if (status3_p2 == 50) {
lbl_806D1210_p2 = 100;
} else {
lbl_806D1210_p2 = 1;
}
}
}
static inline unsigned char Receipt_IsDone_p2(int line_p2)
{
unsigned char done_p2 = 0;
if (line_p2 >= 9 && lbl_806CF0EC_p2 == 1) {
done_p2 = 1;
} else if (line_p2 >= 10) {
done_p2 = 1;
} else if (line_p2 >= 2 && lbl_806CF0EC_p2 == 0) {
done_p2 = 1;
}
return done_p2;
}
static inline void Receipt_BuildLine_p2(int line_p2)
{
int next_p2;
if (lbl_806D122B_p2 == 0) {
next_p2 = Sci2Card_BuildScoreReceiptLine_p2(line_p2);
} else {
next_p2 = Sci2Card_BuildRetryReceiptLine_p2(line_p2);
}
lbl_806D1218_p2 = next_p2;
}
static inline unsigned char Receipt_Advance_p2(void)
{
int line_p2 = lbl_806D1218_p2;
if (Receipt_IsDone_p2(line_p2) == 1) {
lbl_806D122A_p2 = 0;
lbl_806D1210_p2 = 1;
lbl_806D122B_p2 = 0;
return 1;
}
Receipt_BuildLine_p2(line_p2);
return 0;
}
static inline unsigned char Receipt_StartFlow_p2(int mode_p2, unsigned char header_p2, unsigned char retry_p2)
{
lbl_806D122B_p2 = retry_p2;
if (!ServiceLatch_CheckTriggered_p2()) {
lbl_806D122A_p2 = 1;
lbl_806D121C_p2 = 0;
lbl_806CF0E4_p2 = 5;
lbl_806D1210_p2 = 1;
return 1;
}
lbl_806CF0EC_p2 = mode_p2;
lbl_806D1210_p2 = 0;
lbl_806D122A_p2 = 1;
lbl_806D121C_p2 = 0;
lbl_806CF0E4_p2 = 5;
lbl_806D1218_p2 = 0;
lbl_806D123C_p2 = 0;
Sci2Card_Singleton_Get_p2();
if (lbl_806CF0EC_p2 == 0 || lbl_806CF0EC_p2 == 3) {
if (header_p2 == 1) {
Receipt_BuildLine_p2(-3);
} else {
Receipt_BuildLine_p2(0);
}
} else {
lbl_806D1218_p2 = lbl_806CF0EC_p2 == 2 ? 9 : 2;
if (Receipt_Advance_p2() == 1) {
return 1;
}
}
return 1;
}
static inline unsigned char Receipt_PollState_p2(void)
{
void *card_p2;
unsigned char status1_p2;
unsigned char status2_p2;
unsigned char status3_p2;
if (!ServiceLatch_CheckTriggered_p2()) {
lbl_806D1210_p2 = 1;
return 1;
}
if (lbl_806D1210_p2 != 0) {
return 1;
}
card_p2 = Sci2Card_Singleton_Get_p2();
Sci2Card_GetResponseStatus_p2(Sci2Card_Singleton_Get_p2(), &status1_p2, &status2_p2, &status3_p2);
if (Sci2Card_IsIdleOrExhausted_p2(card_p2) == 1) {
if (!Sci2Card_IsStatusOkNonTerm_p2(card_p2)) {
Sci2Card_SetFailCode_p2();
return 1;
}
if (Sci2Card_IsStatus3Zero_p2(card_p2) == 1) {
if (Receipt_Advance_p2() == 1) {
lbl_806D122A_p2 = 0;
lbl_806D1210_p2 = 1;
lbl_806D122B_p2 = 0;
return 1;
}
}
}
return 0;
}
extern void *card_pack_p2(void *source_p2, void *destination_p2, int mode_p2);
extern unsigned char card_send_track_data_p2(void *card_p2, void *data_p2, int size_p2, int flags_p2);
extern unsigned char card_eject_p2(void *card_p2);
extern unsigned char card_eject_state_machine_p2(void);
extern int lbl_806CF0D0_p2;
extern int lbl_806CF0D8_p2;
extern int lbl_806D1220_p2;
extern unsigned char lbl_806D1227_p2;
extern unsigned char lbl_806CF0D4_p2;
extern unsigned char lbl_805AC55C_p2[];
unsigned char Sci2Card_WriteTrackData_PollState(void)
{
void *card_p2;
if (!ServiceLatch_CheckTriggered_p2()) {
lbl_806D1210_p2 = 1;
return 1;
}
if (lbl_806D1210_p2 != 0) {
return 1;
}
card_p2 = Sci2Card_Singleton_Get_p2();
if (lbl_806D121C_p2 == 0) {
lbl_806D121C_p2 = card_send_track_data_p2(card_p2, lbl_805AC55C_p2, 0x45, 0);
return 0;
}
if (Sci2Card_IsIdleOrExhausted_p2(card_p2) == 1) {
if (!Sci2Card_IsStatusOkNonTerm_p2(card_p2)) {
Sci2Card_SetFailCode_p2();
return 1;
}
lbl_806D122A_p2 = 0;
lbl_806D1210_p2 = 1;
lbl_806D122B_p2 = 0;
return 1;
}
return 0;
}
unsigned char Sci2Card_WriteTrackData_StartFlow(void)
{
lbl_806D1210_p2 = 0;
lbl_806D122A_p2 = 1;
lbl_806D121C_p2 = 0;
lbl_806CF0E4_p2 = 5;
if (!ServiceLatch_CheckTriggered_p2()) {
lbl_806D1210_p2 = 1;
return 1;
}
card_pack_p2(g_playerData_p2, lbl_805AC55C_p2, 1);
lbl_806D121C_p2 = card_send_track_data_p2(Sci2Card_Singleton_Get_p2(), lbl_805AC55C_p2, 0x45, 0);
return 1;
}
static inline unsigned char Eject_IsPending_p2(void)
{
return lbl_806D1227_p2 != 0;
}
unsigned char Sci2Card_EjectAndFinalize_Step(void)
{
if (!ServiceLatch_CheckTriggered_p2()) {
lbl_806D1210_p2 = 1;
return 1;
}
if (lbl_806D1210_p2 != 0) {
return 1;
}
switch (lbl_806D1220_p2) {
case 0:
case 1:
case 2:
case 3:
return 0;
case 4:
lbl_806CF0D0_p2 = 2;
lbl_806D1210_p2 = 0;
lbl_806D122A_p2 = 1;
lbl_806D121C_p2 = 0;
lbl_806CF0E4_p2 = 5;
if (!ServiceLatch_CheckTriggered_p2()) {
lbl_806D1210_p2 = 1;
} else {
lbl_806D1227_p2 = 0;
lbl_806D121C_p2 = card_eject_p2(Sci2Card_Singleton_Get_p2());
lbl_806CF0D4_p2 = 0;
}
lbl_806CF0D8_p2 = 1;
lbl_806D1220_p2++;
case 5:
if (Eject_IsPending_p2() == 1) {
lbl_806CF0D0_p2 = 3;
}
if (card_eject_state_machine_p2() == 1) {
if (lbl_806D1210_p2 != 0 && lbl_806D1210_p2 != 1) {
lbl_806D1220_p2--;
return 0;
}
lbl_806CF0E8_p2 = 3;
lbl_806CF0D0_p2 = 5;
lbl_806CF0D8_p2 = 2;
return 1;
}
break;
default:
return 1;
}
return 0;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/card_rw_state_machine_short.c (0x80096034) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern void Backup_PublishShadowCopy_Inline_p3();
extern void Sci2Card_BuildRetryReceiptLine_p3();
extern void Sci2Card_BuildScoreReceiptLine_p3();
extern void Sci2Card_GetResponseStatus_p3();
extern void Sci2Card_IsIdleOrExhausted_p3();
extern void Sci2Card_IsRetryExhausted_p3();
extern void Sci2Card_IsStatus2A_p3();
extern void Sci2Card_IsStatus2Five_p3();
extern void Sci2Card_IsStatus2One_p3();
extern void Sci2Card_IsStatus2Three_p3();
extern void Sci2Card_IsStatus2Two_p3();
extern void Sci2Card_IsStatus3Five_p3();
extern void Sci2Card_IsStatus3Zero_p3();
extern void Sci2Card_IsStatusOkNonTerm_p3();
extern void Sci2Card_Singleton_Get_p3();
extern void ServiceLatch_CheckTriggered_p3();
extern void __copy();
extern void card_backup_p3();
extern void card_pack_p3();
extern void card_send_track_data_p3();
extern unsigned int lbl_806CF0D0_p3;
extern unsigned int lbl_806CF0D4_p3;
extern unsigned int lbl_806CF0E4_p3;
extern unsigned int lbl_806CF0E8_p3;
extern unsigned int lbl_806CF0EC_p3;
extern unsigned int lbl_806D1210_p3;
extern unsigned int lbl_806D1218_p3;
extern unsigned int lbl_806D121C_p3;
extern unsigned int lbl_806D1220_p3;
extern unsigned int lbl_806D1225_p3;
extern unsigned int lbl_806D122A_p3;
extern unsigned int lbl_806D122B_p3;
extern unsigned int lbl_806D123C_p3;
extern unsigned int g_playerData_p3[];
extern unsigned int lbl_80598A60_p3[];
extern unsigned int lbl_805AC55C_p3[];
#ifndef NON_MATCHING /* C version: end of this file */
void card_rw_state_machine_short(void);

#pragma section R".extab_user"

__declspec(section ".extab_user") static const unsigned char extab_card_rw_state_machine_short_p3[8] = {
0x90, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn_p3; unsigned int fn_size_p3; void *extab_p3; } extabindex_card_rw_state_machine_short_p3 = {
(void *)&card_rw_state_machine_short, 0x00000A28, (void *)extab_card_rw_state_machine_short_p3
};
asm void card_rw_state_machine_short(void) {
nofralloc
stwu r1, -0x80(r1)
mflr r0
stw r0, 0x84(r1)
stmw r14, 0x38(r1)
bl ServiceLatch_CheckTriggered_p3
clrlwi. r0, r3, 24
bne card_rw_state_machine_short_L_80096060
li r0, 0x1
li r3, 0x1
stw r0, lbl_806D1210_p3(r13)
b card_rw_state_machine_short_L_80096A48
card_rw_state_machine_short_L_80096060:
lwz r0, lbl_806D1210_p3(r13)
cmpwi r0, 0x0
beq card_rw_state_machine_short_L_80096074
li r3, 0x1
b card_rw_state_machine_short_L_80096A48
card_rw_state_machine_short_L_80096074:
lwz r0, lbl_806D1220_p3(r13)
cmpwi r0, 0x2
beq card_rw_state_machine_short_L_80096304
bge card_rw_state_machine_short_L_80096094
cmpwi r0, 0x0
beq card_rw_state_machine_short_L_800960A0
bge card_rw_state_machine_short_L_8009611C
b card_rw_state_machine_short_L_80096A3C
card_rw_state_machine_short_L_80096094:
cmpwi r0, 0x4
bge card_rw_state_machine_short_L_80096A3C
b card_rw_state_machine_short_L_80096488
card_rw_state_machine_short_L_800960A0:
li r4, 0x0
li r3, 0x1
li r0, 0x5
stw r4, lbl_806D1210_p3(r13)
stb r3, lbl_806D122A_p3(r13)
stb r4, lbl_806D121C_p3(r13)
stw r0, lbl_806CF0E4_p3(r13)
bl ServiceLatch_CheckTriggered_p3
clrlwi. r0, r3, 24
bne card_rw_state_machine_short_L_800960D4
li r0, 0x1
stw r0, lbl_806D1210_p3(r13)
b card_rw_state_machine_short_L_80096108
card_rw_state_machine_short_L_800960D4:
lis r3, g_playerData_p3@ha
lis r4, lbl_805AC55C_p3@ha
addi r3, r3, g_playerData_p3@l
li r5, 0x1
addi r4, r4, lbl_805AC55C_p3@l
bl card_pack_p3
bl Sci2Card_Singleton_Get_p3
lis r4, lbl_805AC55C_p3@ha
li r5, 0x45
addi r4, r4, lbl_805AC55C_p3@l
li r6, 0x0
bl card_send_track_data_p3
stb r3, lbl_806D121C_p3(r13)
card_rw_state_machine_short_L_80096108:
lwz r3, lbl_806D1220_p3(r13)
li r0, 0x0
stw r0, lbl_806CF0D0_p3(r13)
addi r0, r3, 0x1
stw r0, lbl_806D1220_p3(r13)
card_rw_state_machine_short_L_8009611C:
bl ServiceLatch_CheckTriggered_p3
clrlwi. r0, r3, 24
bne card_rw_state_machine_short_L_80096134
li r3, 0x1
stw r3, lbl_806D1210_p3(r13)
b card_rw_state_machine_short_L_800962D0
card_rw_state_machine_short_L_80096134:
lwz r0, lbl_806D1210_p3(r13)
cmpwi r0, 0x0
beq card_rw_state_machine_short_L_80096148
li r3, 0x1
b card_rw_state_machine_short_L_800962D0
card_rw_state_machine_short_L_80096148:
bl Sci2Card_Singleton_Get_p3
lbz r0, lbl_806D121C_p3(r13)
mr r14, r3
cmplwi r0, 0x0
bne card_rw_state_machine_short_L_8009617C
lis r4, lbl_805AC55C_p3@ha
li r5, 0x45
addi r4, r4, lbl_805AC55C_p3@l
li r6, 0x0
bl card_send_track_data_p3
stb r3, lbl_806D121C_p3(r13)
li r3, 0x0
b card_rw_state_machine_short_L_800962D0
card_rw_state_machine_short_L_8009617C:
bl Sci2Card_IsIdleOrExhausted_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_800962CC
mr r3, r14
bl Sci2Card_IsStatusOkNonTerm_p3
clrlwi. r0, r3, 24
bne card_rw_state_machine_short_L_800962B4
bl Sci2Card_Singleton_Get_p3
li r0, 0x0
mr r14, r3
stw r0, lbl_806D1210_p3(r13)
bl Sci2Card_IsStatus3Five_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_800961C4
li r0, 0x2
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_800961C4:
mr r3, r14
bl Sci2Card_IsRetryExhausted_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_800961E0
li r0, 0x65
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_800961E0:
mr r3, r14
bl Sci2Card_IsStatus2Two_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_800961FC
li r0, 0x66
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_800961FC:
mr r3, r14
bl Sci2Card_IsStatus2One_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096218
li r0, 0x67
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_80096218:
mr r3, r14
bl Sci2Card_IsStatus2Three_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096234
li r0, 0x68
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_80096234:
mr r3, r14
bl Sci2Card_IsStatus2Five_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096250
li r0, 0x69
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_80096250:
mr r3, r14
bl Sci2Card_IsStatus2A_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_8009626C
li r0, 0x6a
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_8009626C:
lwz r0, lbl_806D1210_p3(r13)
cmpwi r0, 0x0
bne card_rw_state_machine_short_L_800962AC
mr r3, r14
addi r4, r1, 0xe
addi r5, r1, 0xf
addi r6, r1, 0x10
bl Sci2Card_GetResponseStatus_p3
lbz r0, 0x10(r1)
cmplwi r0, 0x32
bne card_rw_state_machine_short_L_800962A4
li r0, 0x64
stw r0, lbl_806D1210_p3(r13)
b card_rw_state_machine_short_L_800962AC
card_rw_state_machine_short_L_800962A4:
li r0, 0x1
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_800962AC:
li r3, 0x1
b card_rw_state_machine_short_L_800962D0
card_rw_state_machine_short_L_800962B4:
li r0, 0x0
li r3, 0x1
stb r0, lbl_806D122A_p3(r13)
stw r3, lbl_806D1210_p3(r13)
stb r0, lbl_806D122B_p3(r13)
b card_rw_state_machine_short_L_800962D0
card_rw_state_machine_short_L_800962CC:
li r3, 0x0
card_rw_state_machine_short_L_800962D0:
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096A44
lwz r0, lbl_806D1210_p3(r13)
cmpwi r0, 0x1
beq card_rw_state_machine_short_L_800962F0
li r3, 0x1
b card_rw_state_machine_short_L_80096A48
card_rw_state_machine_short_L_800962F0:
lwz r3, lbl_806D1220_p3(r13)
li r0, 0x1
stw r0, lbl_806CF0D0_p3(r13)
addi r0, r3, 0x1
stw r0, lbl_806D1220_p3(r13)
card_rw_state_machine_short_L_80096304:
lbz r4, lbl_806CF0D4_p3(r13)
li r0, 0x0
stb r0, lbl_806D122B_p3(r13)
subfic r3, r4, 0x1
subi r0, r4, 0x1
or r0, r3, r0
lwz r14, lbl_806CF0E8_p3(r13)
srwi r15, r0, 31
bl ServiceLatch_CheckTriggered_p3
clrlwi. r0, r3, 24
bne card_rw_state_machine_short_L_80096350
li r4, 0x1
li r3, 0x0
li r0, 0x5
stb r4, lbl_806D122A_p3(r13)
stb r3, lbl_806D121C_p3(r13)
stw r0, lbl_806CF0E4_p3(r13)
stw r4, lbl_806D1210_p3(r13)
b card_rw_state_machine_short_L_8009647C
card_rw_state_machine_short_L_80096350:
li r4, 0x0
li r3, 0x1
li r0, 0x5
stw r14, lbl_806CF0EC_p3(r13)
stw r4, lbl_806D1210_p3(r13)
stb r3, lbl_806D122A_p3(r13)
stb r4, lbl_806D121C_p3(r13)
stw r0, lbl_806CF0E4_p3(r13)
stw r4, lbl_806D1218_p3(r13)
stw r4, lbl_806D123C_p3(r13)
bl Sci2Card_Singleton_Get_p3
lwz r4, lbl_806CF0EC_p3(r13)
cmpwi r4, 0x0
beq card_rw_state_machine_short_L_80096390
cmpwi r4, 0x3
bne card_rw_state_machine_short_L_800963E8
card_rw_state_machine_short_L_80096390:
cmplwi r15, 0x1
bne card_rw_state_machine_short_L_800963C0
lbz r0, lbl_806D122B_p3(r13)
cmplwi r0, 0x0
bne card_rw_state_machine_short_L_800963B0
li r3, -0x3
bl Sci2Card_BuildScoreReceiptLine_p3
b card_rw_state_machine_short_L_800963B8
card_rw_state_machine_short_L_800963B0:
li r3, -0x3
bl Sci2Card_BuildRetryReceiptLine_p3
card_rw_state_machine_short_L_800963B8:
stw r3, lbl_806D1218_p3(r13)
b card_rw_state_machine_short_L_8009647C
card_rw_state_machine_short_L_800963C0:
lbz r0, lbl_806D122B_p3(r13)
cmplwi r0, 0x0
bne card_rw_state_machine_short_L_800963D8
li r3, 0x0
bl Sci2Card_BuildScoreReceiptLine_p3
b card_rw_state_machine_short_L_800963E0
card_rw_state_machine_short_L_800963D8:
li r3, 0x0
bl Sci2Card_BuildRetryReceiptLine_p3
card_rw_state_machine_short_L_800963E0:
stw r3, lbl_806D1218_p3(r13)
b card_rw_state_machine_short_L_8009647C
card_rw_state_machine_short_L_800963E8:
cmpwi r4, 0x2
li r3, 0x2
bne card_rw_state_machine_short_L_800963F8
li r3, 0x9
card_rw_state_machine_short_L_800963F8:
cmpwi r3, 0x9
stw r3, lbl_806D1218_p3(r13)
li r0, 0x0
blt card_rw_state_machine_short_L_80096418
cmpwi r4, 0x1
bne card_rw_state_machine_short_L_80096418
li r0, 0x1
b card_rw_state_machine_short_L_8009643C
card_rw_state_machine_short_L_80096418:
cmpwi r3, 0xa
blt card_rw_state_machine_short_L_80096428
li r0, 0x1
b card_rw_state_machine_short_L_8009643C
card_rw_state_machine_short_L_80096428:
cmpwi r3, 0x2
blt card_rw_state_machine_short_L_8009643C
cmpwi r4, 0x0
bne card_rw_state_machine_short_L_8009643C
li r0, 0x1
card_rw_state_machine_short_L_8009643C:
clrlwi r0, r0, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096460
li r3, 0x0
li r0, 0x1
stb r3, lbl_806D122A_p3(r13)
stw r0, lbl_806D1210_p3(r13)
stb r3, lbl_806D122B_p3(r13)
b card_rw_state_machine_short_L_8009647C
card_rw_state_machine_short_L_80096460:
lbz r0, lbl_806D122B_p3(r13)
cmplwi r0, 0x0
bne card_rw_state_machine_short_L_80096474
bl Sci2Card_BuildScoreReceiptLine_p3
b card_rw_state_machine_short_L_80096478
card_rw_state_machine_short_L_80096474:
bl Sci2Card_BuildRetryReceiptLine_p3
card_rw_state_machine_short_L_80096478:
stw r3, lbl_806D1218_p3(r13)
card_rw_state_machine_short_L_8009647C:
lwz r3, lbl_806D1220_p3(r13)
addi r0, r3, 0x1
stw r0, lbl_806D1220_p3(r13)
card_rw_state_machine_short_L_80096488:
bl ServiceLatch_CheckTriggered_p3
clrlwi. r0, r3, 24
bne card_rw_state_machine_short_L_800964A0
li r3, 0x1
stw r3, lbl_806D1210_p3(r13)
b card_rw_state_machine_short_L_800966D8
card_rw_state_machine_short_L_800964A0:
lwz r0, lbl_806D1210_p3(r13)
cmpwi r0, 0x0
beq card_rw_state_machine_short_L_800964B4
li r3, 0x1
b card_rw_state_machine_short_L_800966D8
card_rw_state_machine_short_L_800964B4:
bl Sci2Card_Singleton_Get_p3
mr r14, r3
bl Sci2Card_Singleton_Get_p3
addi r4, r1, 0xb
addi r5, r1, 0xc
addi r6, r1, 0xd
bl Sci2Card_GetResponseStatus_p3
mr r3, r14
bl Sci2Card_IsIdleOrExhausted_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_800966D4
mr r3, r14
bl Sci2Card_IsStatusOkNonTerm_p3
clrlwi. r0, r3, 24
bne card_rw_state_machine_short_L_8009660C
bl Sci2Card_Singleton_Get_p3
li r0, 0x0
mr r14, r3
stw r0, lbl_806D1210_p3(r13)
bl Sci2Card_IsStatus3Five_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_8009651C
li r0, 0x2
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_8009651C:
mr r3, r14
bl Sci2Card_IsRetryExhausted_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096538
li r0, 0x65
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_80096538:
mr r3, r14
bl Sci2Card_IsStatus2Two_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096554
li r0, 0x66
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_80096554:
mr r3, r14
bl Sci2Card_IsStatus2One_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096570
li r0, 0x67
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_80096570:
mr r3, r14
bl Sci2Card_IsStatus2Three_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_8009658C
li r0, 0x68
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_8009658C:
mr r3, r14
bl Sci2Card_IsStatus2Five_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_800965A8
li r0, 0x69
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_800965A8:
mr r3, r14
bl Sci2Card_IsStatus2A_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_800965C4
li r0, 0x6a
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_800965C4:
lwz r0, lbl_806D1210_p3(r13)
cmpwi r0, 0x0
bne card_rw_state_machine_short_L_80096604
mr r3, r14
addi r4, r1, 0x8
addi r5, r1, 0x9
addi r6, r1, 0xa
bl Sci2Card_GetResponseStatus_p3
lbz r0, 0xa(r1)
cmplwi r0, 0x32
bne card_rw_state_machine_short_L_800965FC
li r0, 0x64
stw r0, lbl_806D1210_p3(r13)
b card_rw_state_machine_short_L_80096604
card_rw_state_machine_short_L_800965FC:
li r0, 0x1
stw r0, lbl_806D1210_p3(r13)
card_rw_state_machine_short_L_80096604:
li r3, 0x1
b card_rw_state_machine_short_L_800966D8
card_rw_state_machine_short_L_8009660C:
mr r3, r14
bl Sci2Card_IsStatus3Zero_p3
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_800966D4
lwz r3, lbl_806D1218_p3(r13)
li r4, 0x0
cmpwi r3, 0x9
blt card_rw_state_machine_short_L_80096644
lwz r0, lbl_806CF0EC_p3(r13)
cmpwi r0, 0x1
bne card_rw_state_machine_short_L_80096644
li r4, 0x1
b card_rw_state_machine_short_L_8009666C
card_rw_state_machine_short_L_80096644:
cmpwi r3, 0xa
blt card_rw_state_machine_short_L_80096654
li r4, 0x1
b card_rw_state_machine_short_L_8009666C
card_rw_state_machine_short_L_80096654:
cmpwi r3, 0x2
blt card_rw_state_machine_short_L_8009666C
lwz r0, lbl_806CF0EC_p3(r13)
cmpwi r0, 0x0
bne card_rw_state_machine_short_L_8009666C
li r4, 0x1
card_rw_state_machine_short_L_8009666C:
clrlwi r0, r4, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096690
li r0, 0x0
li r3, 0x1
stb r0, lbl_806D122A_p3(r13)
stw r3, lbl_806D1210_p3(r13)
stb r0, lbl_806D122B_p3(r13)
b card_rw_state_machine_short_L_800966B0
card_rw_state_machine_short_L_80096690:
lbz r0, lbl_806D122B_p3(r13)
cmplwi r0, 0x0
bne card_rw_state_machine_short_L_800966A4
bl Sci2Card_BuildScoreReceiptLine_p3
b card_rw_state_machine_short_L_800966A8
card_rw_state_machine_short_L_800966A4:
bl Sci2Card_BuildRetryReceiptLine_p3
card_rw_state_machine_short_L_800966A8:
stw r3, lbl_806D1218_p3(r13)
li r3, 0x0
card_rw_state_machine_short_L_800966B0:
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_800966D4
li r0, 0x0
li r3, 0x1
stb r0, lbl_806D122A_p3(r13)
stw r3, lbl_806D1210_p3(r13)
stb r0, lbl_806D122B_p3(r13)
b card_rw_state_machine_short_L_800966D8
card_rw_state_machine_short_L_800966D4:
li r3, 0x0
card_rw_state_machine_short_L_800966D8:
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096A44
lwz r0, lbl_806D1210_p3(r13)
cmpwi r0, 0x1
beq card_rw_state_machine_short_L_800966F8
li r3, 0x1
b card_rw_state_machine_short_L_80096A48
card_rw_state_machine_short_L_800966F8:
lis r3, lbl_80598A60_p3@ha
addi r31, r3, lbl_80598A60_p3@l
lwz r3, 0x26c(r31)
addi r0, r3, 0x1
cmpwi r0, 0xc8
stw r0, 0x26c(r31)
ble card_rw_state_machine_short_L_8009671C
li r0, 0xc8
stw r0, 0x26c(r31)
card_rw_state_machine_short_L_8009671C:
bl Backup_PublishShadowCopy_Inline_p3
lbz r0, lbl_806D1225_p3(r13)
cmplwi r0, 0x1
bne card_rw_state_machine_short_L_80096A18
lis r3, g_playerData_p3@ha
addi r14, r3, g_playerData_p3@l
lwz r29, 0x58(r14)
lwz r0, 0x50(r14)
stw r29, 0x28(r1)
lwz r29, 0x5c(r14)
stw r0, 0xe0(r31)
lwz r0, 0x28(r1)
stw r29, 0x14(r1)
lwz r29, 0x60(r14)
stw r0, 0xe8(r31)
lwz r0, 0x14(r1)
stw r29, 0x18(r1)
lwz r29, 0x64(r14)
stw r0, 0xec(r31)
lwz r0, 0x18(r1)
stw r29, 0x1c(r1)
li r29, 0x0
lwz r28, 0x0(r14)
stb r29, 0x1a0(r14)
li r29, 0x0
lwz r27, 0x4(r14)
lwz r26, 0x8(r14)
lbz r25, 0xc(r14)
lbz r24, 0xd(r14)
lhz r23, 0xe(r14)
lhz r22, 0x10(r14)
lwz r21, 0x14(r14)
lbz r20, 0x18(r14)
lbz r19, 0x19(r14)
lbz r18, 0x1a(r14)
lwz r17, 0x1c(r14)
lwz r16, 0x20(r14)
lwz r15, 0x24(r14)
lwz r12, 0x28(r14)
lwz r11, 0x2c(r14)
lwz r10, 0x30(r14)
lwz r9, 0x34(r14)
lwz r8, 0x38(r14)
lwz r7, 0x3c(r14)
lwz r6, 0x40(r14)
lwz r5, 0x44(r14)
lwz r4, 0x48(r14)
lwz r3, 0x4c(r14)
lwz r30, 0x54(r14)
stb r29, 0x199(r14)
li r29, 0x32
stw r0, 0xf0(r31)
lwz r0, 0x1c(r1)
stb r29, 0x198(r14)
li r29, 0x1
stb r29, 0x64(r31)
stw r28, 0x90(r31)
stw r27, 0x94(r31)
stw r26, 0x98(r31)
stb r25, 0x9c(r31)
stb r24, 0x9d(r31)
sth r23, 0x9e(r31)
sth r22, 0xa0(r31)
stw r21, 0xa4(r31)
stb r20, 0xa8(r31)
stb r19, 0xa9(r31)
stb r18, 0xaa(r31)
stw r17, 0xac(r31)
stw r16, 0xb0(r31)
stw r15, 0xb4(r31)
stw r12, 0xb8(r31)
stw r11, 0xbc(r31)
stw r10, 0xc0(r31)
stw r9, 0xc4(r31)
stw r8, 0xc8(r31)
stw r7, 0xcc(r31)
stw r6, 0xd0(r31)
stw r5, 0xd4(r31)
stw r4, 0xd8(r31)
stw r3, 0xdc(r31)
stw r30, 0xe4(r31)
stw r0, 0xf4(r31)
lwz r22, 0x68(r14)
addi r3, r31, 0x138
lwz r21, 0x6c(r14)
addi r4, r14, 0xa8
lwz r20, 0x70(r14)
li r5, 0x79
lwz r19, 0x74(r14)
lwz r18, 0x78(r14)
lwz r17, 0x7c(r14)
lwz r16, 0x80(r14)
lwz r15, 0x84(r14)
lwz r12, 0x88(r14)
lwz r11, 0x8c(r14)
lwz r10, 0x90(r14)
lwz r9, 0x94(r14)
lwz r8, 0x98(r14)
lwz r7, 0x9c(r14)
lwz r6, 0xa0(r14)
lwz r0, 0xa4(r14)
stw r22, 0xf8(r31)
stw r21, 0xfc(r31)
stw r20, 0x100(r31)
stw r19, 0x104(r31)
stw r18, 0x108(r31)
stw r17, 0x10c(r31)
stw r16, 0x110(r31)
stw r15, 0x114(r31)
stw r12, 0x118(r31)
stw r11, 0x11c(r31)
stw r10, 0x120(r31)
stw r9, 0x124(r31)
stw r8, 0x128(r31)
stw r7, 0x12c(r31)
stw r6, 0x130(r31)
stw r0, 0x134(r31)
bl __copy
lis r4, g_playerData_p3@ha
addi r3, r31, 0x1b1
addi r4, r4, g_playerData_p3@l
li r5, 0x69
addi r4, r4, 0x121
bl __copy
lis r3, g_playerData_p3@ha
lbz r18, 0x198(r14)
addi r3, r3, g_playerData_p3@l
lbz r19, 0x199(r14)
lbz r0, 0x19e(r3)
lbz r24, 0x1a0(r14)
lwz r15, 0x18c(r3)
stw r0, 0x20(r1)
lbz r0, 0x19f(r3)
stw r15, 0x21c(r31)
lwz r15, 0x20(r1)
stw r0, 0x24(r1)
lwz r16, 0x190(r3)
lwz r17, 0x194(r3)
lbz r20, 0x19a(r3)
lbz r21, 0x19b(r3)
lbz r22, 0x19c(r3)
lbz r23, 0x19d(r3)
lwz r25, 0x1a4(r3)
lbz r26, 0x1a8(r3)
lwz r27, 0x1ac(r3)
lbz r28, 0x1b0(r3)
lbz r29, 0x1b1(r3)
lwz r30, 0x1b4(r3)
lbz r12, 0x1b8(r3)
lbz r11, 0x1b9(r3)
lwz r10, 0x1ba(r3)
lwz r9, 0x1be(r3)
lwz r8, 0x1c2(r3)
lwz r7, 0x1c6(r3)
lwz r6, 0x1ca(r3)
lwz r5, 0x1ce(r3)
lwz r4, 0x1d4(r3)
lbz r0, 0x1d8(r3)
lbz r14, 0x1d9(r3)
lbz r3, 0x1da(r3)
stb r15, 0x22e(r31)
lwz r15, 0x24(r1)
stw r16, 0x220(r31)
stw r17, 0x224(r31)
stb r18, 0x228(r31)
stb r19, 0x229(r31)
stb r20, 0x22a(r31)
stb r21, 0x22b(r31)
stb r22, 0x22c(r31)
stb r23, 0x22d(r31)
stb r15, 0x22f(r31)
stb r24, 0x230(r31)
stw r25, 0x234(r31)
stb r26, 0x238(r31)
stw r27, 0x23c(r31)
stb r28, 0x240(r31)
stb r29, 0x241(r31)
stw r30, 0x244(r31)
stb r12, 0x248(r31)
stb r11, 0x249(r31)
stw r10, 0x24a(r31)
stw r9, 0x24e(r31)
stw r8, 0x252(r31)
stw r7, 0x256(r31)
stw r6, 0x25a(r31)
stw r5, 0x25e(r31)
stw r4, 0x264(r31)
stb r0, 0x268(r31)
stb r14, 0x269(r31)
stb r3, 0x26a(r31)
bl card_backup_p3
card_rw_state_machine_short_L_80096A18:
lwz r3, lbl_806D1220_p3(r13)
li r0, 0x3
li r4, 0x5
stw r0, lbl_806CF0E8_p3(r13)
addi r0, r3, 0x1
li r3, 0x1
stw r4, lbl_806CF0D0_p3(r13)
stw r0, lbl_806D1220_p3(r13)
b card_rw_state_machine_short_L_80096A48
card_rw_state_machine_short_L_80096A3C:
li r3, 0x1
b card_rw_state_machine_short_L_80096A48
card_rw_state_machine_short_L_80096A44:
li r3, 0x0
card_rw_state_machine_short_L_80096A48:
lmw r14, 0x38(r1)
lwz r0, 0x84(r1)
mtlr r0
addi r1, r1, 0x80
blr
}
#endif
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/card_rw_state_machine.c (0x80096a5c) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern void Backup_PublishShadowCopy_Inline_p4();
extern void Sci2Card_BuildRetryReceiptLine_p4();
extern void Sci2Card_BuildScoreReceiptLine_p4();
extern void Sci2Card_GetResponseStatus_p4();
extern void Sci2Card_IsIdleOrExhausted_p4();
extern void Sci2Card_IsRetryExhausted_p4();
extern void Sci2Card_IsStatus2A_p4();
extern void Sci2Card_IsStatus2Five_p4();
extern void Sci2Card_IsStatus2One_p4();
extern void Sci2Card_IsStatus2Three_p4();
extern void Sci2Card_IsStatus2Two_p4();
extern void Sci2Card_IsStatus3Five_p4();
extern void Sci2Card_IsStatus3Zero_p4();
extern void Sci2Card_IsStatusOkNonTerm_p4();
extern void Sci2Card_Singleton_Get_p4();
extern void ServiceLatch_CheckTriggered_p4();
extern void __copy();
extern void card_backup_p4();
extern void card_eject_p4();
extern void card_eject_state_machine_p4();
extern void card_pack_p4();
extern void card_send_track_data_p4();
extern unsigned int lbl_806CF0D0_p4;
extern unsigned int lbl_806CF0D4_p4;
extern unsigned int lbl_806CF0D8_p4;
extern unsigned int lbl_806CF0E4_p4;
extern unsigned int lbl_806CF0E8_p4;
extern unsigned int lbl_806CF0EC_p4;
extern unsigned int lbl_806D1210_p4;
extern unsigned int lbl_806D1218_p4;
extern unsigned int lbl_806D121C_p4;
extern unsigned int lbl_806D1220_p4;
extern unsigned int lbl_806D1225_p4;
extern unsigned int lbl_806D1227_p4;
extern unsigned int lbl_806D122A_p4;
extern unsigned int lbl_806D122B_p4;
extern unsigned int lbl_806D123C_p4;
extern unsigned int g_playerData_p4[];
extern unsigned int lbl_80598A60_p4[];
extern unsigned int lbl_805AC55C_p4[];
#ifndef NON_MATCHING /* C version: end of this file */
void card_rw_state_machine(void);

#pragma section R".extab_user"

__declspec(section ".extab_user") static const unsigned char extab_card_rw_state_machine_p4[8] = {
0x90, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn_p4; unsigned int fn_size_p4; void *extab_p4; } extabindex_card_rw_state_machine_p4 = {
(void *)&card_rw_state_machine, 0x00000B00, (void *)extab_card_rw_state_machine_p4
};
asm void card_rw_state_machine(void) {
nofralloc
stwu r1, -0x80(r1)
mflr r0
stw r0, 0x84(r1)
stmw r14, 0x38(r1)
bl ServiceLatch_CheckTriggered_p4
clrlwi. r0, r3, 24
bne card_rw_state_machine_L_80096A88
li r0, 0x1
li r3, 0x1
stw r0, lbl_806D1210_p4(r13)
b card_rw_state_machine_L_80097548
card_rw_state_machine_L_80096A88:
lwz r0, lbl_806D1210_p4(r13)
cmpwi r0, 0x0
beq card_rw_state_machine_L_80096A9C
li r3, 0x1
b card_rw_state_machine_L_80097548
card_rw_state_machine_L_80096A9C:
lwz r0, lbl_806D1220_p4(r13)
cmpwi r0, 0x3
beq card_rw_state_machine_L_80096EBC
bge card_rw_state_machine_L_80096AC4
cmpwi r0, 0x1
beq card_rw_state_machine_L_80096B50
bge card_rw_state_machine_L_80096D38
cmpwi r0, 0x0
bge card_rw_state_machine_L_80096AD4
b card_rw_state_machine_L_8009753C
card_rw_state_machine_L_80096AC4:
cmpwi r0, 0x5
beq card_rw_state_machine_L_800974C4
bge card_rw_state_machine_L_8009753C
b card_rw_state_machine_L_80097460
card_rw_state_machine_L_80096AD4:
li r4, 0x0
li r3, 0x1
li r0, 0x5
stw r4, lbl_806D1210_p4(r13)
stb r3, lbl_806D122A_p4(r13)
stb r4, lbl_806D121C_p4(r13)
stw r0, lbl_806CF0E4_p4(r13)
bl ServiceLatch_CheckTriggered_p4
clrlwi. r0, r3, 24
bne card_rw_state_machine_L_80096B08
li r0, 0x1
stw r0, lbl_806D1210_p4(r13)
b card_rw_state_machine_L_80096B3C
card_rw_state_machine_L_80096B08:
lis r3, g_playerData_p4@ha
lis r4, lbl_805AC55C_p4@ha
addi r3, r3, g_playerData_p4@l
li r5, 0x1
addi r4, r4, lbl_805AC55C_p4@l
bl card_pack_p4
bl Sci2Card_Singleton_Get_p4
lis r4, lbl_805AC55C_p4@ha
li r5, 0x45
addi r4, r4, lbl_805AC55C_p4@l
li r6, 0x0
bl card_send_track_data_p4
stb r3, lbl_806D121C_p4(r13)
card_rw_state_machine_L_80096B3C:
lwz r3, lbl_806D1220_p4(r13)
li r0, 0x0
stw r0, lbl_806CF0D0_p4(r13)
addi r0, r3, 0x1
stw r0, lbl_806D1220_p4(r13)
card_rw_state_machine_L_80096B50:
bl ServiceLatch_CheckTriggered_p4
clrlwi. r0, r3, 24
bne card_rw_state_machine_L_80096B68
li r3, 0x1
stw r3, lbl_806D1210_p4(r13)
b card_rw_state_machine_L_80096D04
card_rw_state_machine_L_80096B68:
lwz r0, lbl_806D1210_p4(r13)
cmpwi r0, 0x0
beq card_rw_state_machine_L_80096B7C
li r3, 0x1
b card_rw_state_machine_L_80096D04
card_rw_state_machine_L_80096B7C:
bl Sci2Card_Singleton_Get_p4
lbz r0, lbl_806D121C_p4(r13)
mr r14, r3
cmplwi r0, 0x0
bne card_rw_state_machine_L_80096BB0
lis r4, lbl_805AC55C_p4@ha
li r5, 0x45
addi r4, r4, lbl_805AC55C_p4@l
li r6, 0x0
bl card_send_track_data_p4
stb r3, lbl_806D121C_p4(r13)
li r3, 0x0
b card_rw_state_machine_L_80096D04
card_rw_state_machine_L_80096BB0:
bl Sci2Card_IsIdleOrExhausted_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096D00
mr r3, r14
bl Sci2Card_IsStatusOkNonTerm_p4
clrlwi. r0, r3, 24
bne card_rw_state_machine_L_80096CE8
bl Sci2Card_Singleton_Get_p4
li r0, 0x0
mr r14, r3
stw r0, lbl_806D1210_p4(r13)
bl Sci2Card_IsStatus3Five_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096BF8
li r0, 0x2
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096BF8:
mr r3, r14
bl Sci2Card_IsRetryExhausted_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096C14
li r0, 0x65
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096C14:
mr r3, r14
bl Sci2Card_IsStatus2Two_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096C30
li r0, 0x66
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096C30:
mr r3, r14
bl Sci2Card_IsStatus2One_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096C4C
li r0, 0x67
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096C4C:
mr r3, r14
bl Sci2Card_IsStatus2Three_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096C68
li r0, 0x68
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096C68:
mr r3, r14
bl Sci2Card_IsStatus2Five_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096C84
li r0, 0x69
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096C84:
mr r3, r14
bl Sci2Card_IsStatus2A_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096CA0
li r0, 0x6a
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096CA0:
lwz r0, lbl_806D1210_p4(r13)
cmpwi r0, 0x0
bne card_rw_state_machine_L_80096CE0
mr r3, r14
addi r4, r1, 0xe
addi r5, r1, 0xf
addi r6, r1, 0x10
bl Sci2Card_GetResponseStatus_p4
lbz r0, 0x10(r1)
cmplwi r0, 0x32
bne card_rw_state_machine_L_80096CD8
li r0, 0x64
stw r0, lbl_806D1210_p4(r13)
b card_rw_state_machine_L_80096CE0
card_rw_state_machine_L_80096CD8:
li r0, 0x1
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096CE0:
li r3, 0x1
b card_rw_state_machine_L_80096D04
card_rw_state_machine_L_80096CE8:
li r0, 0x0
li r3, 0x1
stb r0, lbl_806D122A_p4(r13)
stw r3, lbl_806D1210_p4(r13)
stb r0, lbl_806D122B_p4(r13)
b card_rw_state_machine_L_80096D04
card_rw_state_machine_L_80096D00:
li r3, 0x0
card_rw_state_machine_L_80096D04:
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80097544
lwz r0, lbl_806D1210_p4(r13)
cmpwi r0, 0x1
beq card_rw_state_machine_L_80096D24
li r3, 0x1
b card_rw_state_machine_L_80097548
card_rw_state_machine_L_80096D24:
lwz r3, lbl_806D1220_p4(r13)
li r0, 0x1
stw r0, lbl_806CF0D0_p4(r13)
addi r0, r3, 0x1
stw r0, lbl_806D1220_p4(r13)
card_rw_state_machine_L_80096D38:
lbz r4, lbl_806CF0D4_p4(r13)
li r0, 0x0
stb r0, lbl_806D122B_p4(r13)
subfic r3, r4, 0x1
subi r0, r4, 0x1
or r0, r3, r0
lwz r14, lbl_806CF0E8_p4(r13)
srwi r15, r0, 31
bl ServiceLatch_CheckTriggered_p4
clrlwi. r0, r3, 24
bne card_rw_state_machine_L_80096D84
li r4, 0x1
li r3, 0x0
li r0, 0x5
stb r4, lbl_806D122A_p4(r13)
stb r3, lbl_806D121C_p4(r13)
stw r0, lbl_806CF0E4_p4(r13)
stw r4, lbl_806D1210_p4(r13)
b card_rw_state_machine_L_80096EB0
card_rw_state_machine_L_80096D84:
li r4, 0x0
li r3, 0x1
li r0, 0x5
stw r14, lbl_806CF0EC_p4(r13)
stw r4, lbl_806D1210_p4(r13)
stb r3, lbl_806D122A_p4(r13)
stb r4, lbl_806D121C_p4(r13)
stw r0, lbl_806CF0E4_p4(r13)
stw r4, lbl_806D1218_p4(r13)
stw r4, lbl_806D123C_p4(r13)
bl Sci2Card_Singleton_Get_p4
lwz r4, lbl_806CF0EC_p4(r13)
cmpwi r4, 0x0
beq card_rw_state_machine_L_80096DC4
cmpwi r4, 0x3
bne card_rw_state_machine_L_80096E1C
card_rw_state_machine_L_80096DC4:
cmplwi r15, 0x1
bne card_rw_state_machine_L_80096DF4
lbz r0, lbl_806D122B_p4(r13)
cmplwi r0, 0x0
bne card_rw_state_machine_L_80096DE4
li r3, -0x3
bl Sci2Card_BuildScoreReceiptLine_p4
b card_rw_state_machine_L_80096DEC
card_rw_state_machine_L_80096DE4:
li r3, -0x3
bl Sci2Card_BuildRetryReceiptLine_p4
card_rw_state_machine_L_80096DEC:
stw r3, lbl_806D1218_p4(r13)
b card_rw_state_machine_L_80096EB0
card_rw_state_machine_L_80096DF4:
lbz r0, lbl_806D122B_p4(r13)
cmplwi r0, 0x0
bne card_rw_state_machine_L_80096E0C
li r3, 0x0
bl Sci2Card_BuildScoreReceiptLine_p4
b card_rw_state_machine_L_80096E14
card_rw_state_machine_L_80096E0C:
li r3, 0x0
bl Sci2Card_BuildRetryReceiptLine_p4
card_rw_state_machine_L_80096E14:
stw r3, lbl_806D1218_p4(r13)
b card_rw_state_machine_L_80096EB0
card_rw_state_machine_L_80096E1C:
cmpwi r4, 0x2
li r3, 0x2
bne card_rw_state_machine_L_80096E2C
li r3, 0x9
card_rw_state_machine_L_80096E2C:
cmpwi r3, 0x9
stw r3, lbl_806D1218_p4(r13)
li r0, 0x0
blt card_rw_state_machine_L_80096E4C
cmpwi r4, 0x1
bne card_rw_state_machine_L_80096E4C
li r0, 0x1
b card_rw_state_machine_L_80096E70
card_rw_state_machine_L_80096E4C:
cmpwi r3, 0xa
blt card_rw_state_machine_L_80096E5C
li r0, 0x1
b card_rw_state_machine_L_80096E70
card_rw_state_machine_L_80096E5C:
cmpwi r3, 0x2
blt card_rw_state_machine_L_80096E70
cmpwi r4, 0x0
bne card_rw_state_machine_L_80096E70
li r0, 0x1
card_rw_state_machine_L_80096E70:
clrlwi r0, r0, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096E94
li r3, 0x0
li r0, 0x1
stb r3, lbl_806D122A_p4(r13)
stw r0, lbl_806D1210_p4(r13)
stb r3, lbl_806D122B_p4(r13)
b card_rw_state_machine_L_80096EB0
card_rw_state_machine_L_80096E94:
lbz r0, lbl_806D122B_p4(r13)
cmplwi r0, 0x0
bne card_rw_state_machine_L_80096EA8
bl Sci2Card_BuildScoreReceiptLine_p4
b card_rw_state_machine_L_80096EAC
card_rw_state_machine_L_80096EA8:
bl Sci2Card_BuildRetryReceiptLine_p4
card_rw_state_machine_L_80096EAC:
stw r3, lbl_806D1218_p4(r13)
card_rw_state_machine_L_80096EB0:
lwz r3, lbl_806D1220_p4(r13)
addi r0, r3, 0x1
stw r0, lbl_806D1220_p4(r13)
card_rw_state_machine_L_80096EBC:
bl ServiceLatch_CheckTriggered_p4
clrlwi. r0, r3, 24
bne card_rw_state_machine_L_80096ED4
li r3, 0x1
stw r3, lbl_806D1210_p4(r13)
b card_rw_state_machine_L_8009710C
card_rw_state_machine_L_80096ED4:
lwz r0, lbl_806D1210_p4(r13)
cmpwi r0, 0x0
beq card_rw_state_machine_L_80096EE8
li r3, 0x1
b card_rw_state_machine_L_8009710C
card_rw_state_machine_L_80096EE8:
bl Sci2Card_Singleton_Get_p4
mr r14, r3
bl Sci2Card_Singleton_Get_p4
addi r4, r1, 0xb
addi r5, r1, 0xc
addi r6, r1, 0xd
bl Sci2Card_GetResponseStatus_p4
mr r3, r14
bl Sci2Card_IsIdleOrExhausted_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80097108
mr r3, r14
bl Sci2Card_IsStatusOkNonTerm_p4
clrlwi. r0, r3, 24
bne card_rw_state_machine_L_80097040
bl Sci2Card_Singleton_Get_p4
li r0, 0x0
mr r14, r3
stw r0, lbl_806D1210_p4(r13)
bl Sci2Card_IsStatus3Five_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096F50
li r0, 0x2
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096F50:
mr r3, r14
bl Sci2Card_IsRetryExhausted_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096F6C
li r0, 0x65
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096F6C:
mr r3, r14
bl Sci2Card_IsStatus2Two_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096F88
li r0, 0x66
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096F88:
mr r3, r14
bl Sci2Card_IsStatus2One_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096FA4
li r0, 0x67
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096FA4:
mr r3, r14
bl Sci2Card_IsStatus2Three_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096FC0
li r0, 0x68
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096FC0:
mr r3, r14
bl Sci2Card_IsStatus2Five_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096FDC
li r0, 0x69
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096FDC:
mr r3, r14
bl Sci2Card_IsStatus2A_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80096FF8
li r0, 0x6a
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80096FF8:
lwz r0, lbl_806D1210_p4(r13)
cmpwi r0, 0x0
bne card_rw_state_machine_L_80097038
mr r3, r14
addi r4, r1, 0x8
addi r5, r1, 0x9
addi r6, r1, 0xa
bl Sci2Card_GetResponseStatus_p4
lbz r0, 0xa(r1)
cmplwi r0, 0x32
bne card_rw_state_machine_L_80097030
li r0, 0x64
stw r0, lbl_806D1210_p4(r13)
b card_rw_state_machine_L_80097038
card_rw_state_machine_L_80097030:
li r0, 0x1
stw r0, lbl_806D1210_p4(r13)
card_rw_state_machine_L_80097038:
li r3, 0x1
b card_rw_state_machine_L_8009710C
card_rw_state_machine_L_80097040:
mr r3, r14
bl Sci2Card_IsStatus3Zero_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80097108
lwz r3, lbl_806D1218_p4(r13)
li r4, 0x0
cmpwi r3, 0x9
blt card_rw_state_machine_L_80097078
lwz r0, lbl_806CF0EC_p4(r13)
cmpwi r0, 0x1
bne card_rw_state_machine_L_80097078
li r4, 0x1
b card_rw_state_machine_L_800970A0
card_rw_state_machine_L_80097078:
cmpwi r3, 0xa
blt card_rw_state_machine_L_80097088
li r4, 0x1
b card_rw_state_machine_L_800970A0
card_rw_state_machine_L_80097088:
cmpwi r3, 0x2
blt card_rw_state_machine_L_800970A0
lwz r0, lbl_806CF0EC_p4(r13)
cmpwi r0, 0x0
bne card_rw_state_machine_L_800970A0
li r4, 0x1
card_rw_state_machine_L_800970A0:
clrlwi r0, r4, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_800970C4
li r0, 0x0
li r3, 0x1
stb r0, lbl_806D122A_p4(r13)
stw r3, lbl_806D1210_p4(r13)
stb r0, lbl_806D122B_p4(r13)
b card_rw_state_machine_L_800970E4
card_rw_state_machine_L_800970C4:
lbz r0, lbl_806D122B_p4(r13)
cmplwi r0, 0x0
bne card_rw_state_machine_L_800970D8
bl Sci2Card_BuildScoreReceiptLine_p4
b card_rw_state_machine_L_800970DC
card_rw_state_machine_L_800970D8:
bl Sci2Card_BuildRetryReceiptLine_p4
card_rw_state_machine_L_800970DC:
stw r3, lbl_806D1218_p4(r13)
li r3, 0x0
card_rw_state_machine_L_800970E4:
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80097108
li r0, 0x0
li r3, 0x1
stb r0, lbl_806D122A_p4(r13)
stw r3, lbl_806D1210_p4(r13)
stb r0, lbl_806D122B_p4(r13)
b card_rw_state_machine_L_8009710C
card_rw_state_machine_L_80097108:
li r3, 0x0
card_rw_state_machine_L_8009710C:
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80097544
lwz r0, lbl_806D1210_p4(r13)
cmpwi r0, 0x1
beq card_rw_state_machine_L_8009712C
li r3, 0x1
b card_rw_state_machine_L_80097548
card_rw_state_machine_L_8009712C:
lis r3, lbl_80598A60_p4@ha
addi r31, r3, lbl_80598A60_p4@l
lwz r3, 0x26c(r31)
addi r0, r3, 0x1
cmpwi r0, 0xc8
stw r0, 0x26c(r31)
ble card_rw_state_machine_L_80097150
li r0, 0xc8
stw r0, 0x26c(r31)
card_rw_state_machine_L_80097150:
bl Backup_PublishShadowCopy_Inline_p4
lbz r0, lbl_806D1225_p4(r13)
cmplwi r0, 0x1
bne card_rw_state_machine_L_8009744C
lis r3, g_playerData_p4@ha
addi r14, r3, g_playerData_p4@l
lwz r29, 0x58(r14)
lwz r0, 0x50(r14)
stw r29, 0x28(r1)
lwz r29, 0x5c(r14)
stw r0, 0xe0(r31)
lwz r0, 0x28(r1)
stw r29, 0x14(r1)
lwz r29, 0x60(r14)
stw r0, 0xe8(r31)
lwz r0, 0x14(r1)
stw r29, 0x18(r1)
lwz r29, 0x64(r14)
stw r0, 0xec(r31)
lwz r0, 0x18(r1)
stw r29, 0x1c(r1)
li r29, 0x0
lwz r28, 0x0(r14)
stb r29, 0x1a0(r14)
li r29, 0x0
lwz r27, 0x4(r14)
lwz r26, 0x8(r14)
lbz r25, 0xc(r14)
lbz r24, 0xd(r14)
lhz r23, 0xe(r14)
lhz r22, 0x10(r14)
lwz r21, 0x14(r14)
lbz r20, 0x18(r14)
lbz r19, 0x19(r14)
lbz r18, 0x1a(r14)
lwz r17, 0x1c(r14)
lwz r16, 0x20(r14)
lwz r15, 0x24(r14)
lwz r12, 0x28(r14)
lwz r11, 0x2c(r14)
lwz r10, 0x30(r14)
lwz r9, 0x34(r14)
lwz r8, 0x38(r14)
lwz r7, 0x3c(r14)
lwz r6, 0x40(r14)
lwz r5, 0x44(r14)
lwz r4, 0x48(r14)
lwz r3, 0x4c(r14)
lwz r30, 0x54(r14)
stb r29, 0x199(r14)
li r29, 0x32
stw r0, 0xf0(r31)
lwz r0, 0x1c(r1)
stb r29, 0x198(r14)
li r29, 0x1
stb r29, 0x64(r31)
stw r28, 0x90(r31)
stw r27, 0x94(r31)
stw r26, 0x98(r31)
stb r25, 0x9c(r31)
stb r24, 0x9d(r31)
sth r23, 0x9e(r31)
sth r22, 0xa0(r31)
stw r21, 0xa4(r31)
stb r20, 0xa8(r31)
stb r19, 0xa9(r31)
stb r18, 0xaa(r31)
stw r17, 0xac(r31)
stw r16, 0xb0(r31)
stw r15, 0xb4(r31)
stw r12, 0xb8(r31)
stw r11, 0xbc(r31)
stw r10, 0xc0(r31)
stw r9, 0xc4(r31)
stw r8, 0xc8(r31)
stw r7, 0xcc(r31)
stw r6, 0xd0(r31)
stw r5, 0xd4(r31)
stw r4, 0xd8(r31)
stw r3, 0xdc(r31)
stw r30, 0xe4(r31)
stw r0, 0xf4(r31)
lwz r22, 0x68(r14)
addi r3, r31, 0x138
lwz r21, 0x6c(r14)
addi r4, r14, 0xa8
lwz r20, 0x70(r14)
li r5, 0x79
lwz r19, 0x74(r14)
lwz r18, 0x78(r14)
lwz r17, 0x7c(r14)
lwz r16, 0x80(r14)
lwz r15, 0x84(r14)
lwz r12, 0x88(r14)
lwz r11, 0x8c(r14)
lwz r10, 0x90(r14)
lwz r9, 0x94(r14)
lwz r8, 0x98(r14)
lwz r7, 0x9c(r14)
lwz r6, 0xa0(r14)
lwz r0, 0xa4(r14)
stw r22, 0xf8(r31)
stw r21, 0xfc(r31)
stw r20, 0x100(r31)
stw r19, 0x104(r31)
stw r18, 0x108(r31)
stw r17, 0x10c(r31)
stw r16, 0x110(r31)
stw r15, 0x114(r31)
stw r12, 0x118(r31)
stw r11, 0x11c(r31)
stw r10, 0x120(r31)
stw r9, 0x124(r31)
stw r8, 0x128(r31)
stw r7, 0x12c(r31)
stw r6, 0x130(r31)
stw r0, 0x134(r31)
bl __copy
lis r4, g_playerData_p4@ha
addi r3, r31, 0x1b1
addi r4, r4, g_playerData_p4@l
li r5, 0x69
addi r4, r4, 0x121
bl __copy
lis r3, g_playerData_p4@ha
lbz r18, 0x198(r14)
addi r3, r3, g_playerData_p4@l
lbz r19, 0x199(r14)
lbz r0, 0x19e(r3)
lbz r24, 0x1a0(r14)
lwz r15, 0x18c(r3)
stw r0, 0x20(r1)
lbz r0, 0x19f(r3)
stw r15, 0x21c(r31)
lwz r15, 0x20(r1)
stw r0, 0x24(r1)
lwz r16, 0x190(r3)
lwz r17, 0x194(r3)
lbz r20, 0x19a(r3)
lbz r21, 0x19b(r3)
lbz r22, 0x19c(r3)
lbz r23, 0x19d(r3)
lwz r25, 0x1a4(r3)
lbz r26, 0x1a8(r3)
lwz r27, 0x1ac(r3)
lbz r28, 0x1b0(r3)
lbz r29, 0x1b1(r3)
lwz r30, 0x1b4(r3)
lbz r12, 0x1b8(r3)
lbz r11, 0x1b9(r3)
lwz r10, 0x1ba(r3)
lwz r9, 0x1be(r3)
lwz r8, 0x1c2(r3)
lwz r7, 0x1c6(r3)
lwz r6, 0x1ca(r3)
lwz r5, 0x1ce(r3)
lwz r4, 0x1d4(r3)
lbz r0, 0x1d8(r3)
lbz r14, 0x1d9(r3)
lbz r3, 0x1da(r3)
stb r15, 0x22e(r31)
lwz r15, 0x24(r1)
stw r16, 0x220(r31)
stw r17, 0x224(r31)
stb r18, 0x228(r31)
stb r19, 0x229(r31)
stb r20, 0x22a(r31)
stb r21, 0x22b(r31)
stb r22, 0x22c(r31)
stb r23, 0x22d(r31)
stb r15, 0x22f(r31)
stb r24, 0x230(r31)
stw r25, 0x234(r31)
stb r26, 0x238(r31)
stw r27, 0x23c(r31)
stb r28, 0x240(r31)
stb r29, 0x241(r31)
stw r30, 0x244(r31)
stb r12, 0x248(r31)
stb r11, 0x249(r31)
stw r10, 0x24a(r31)
stw r9, 0x24e(r31)
stw r8, 0x252(r31)
stw r7, 0x256(r31)
stw r6, 0x25a(r31)
stw r5, 0x25e(r31)
stw r4, 0x264(r31)
stb r0, 0x268(r31)
stb r14, 0x269(r31)
stb r3, 0x26a(r31)
bl card_backup_p4
card_rw_state_machine_L_8009744C:
lwz r3, lbl_806D1220_p4(r13)
li r0, 0x2
stw r0, lbl_806CF0D0_p4(r13)
addi r0, r3, 0x1
stw r0, lbl_806D1220_p4(r13)
card_rw_state_machine_L_80097460:
li r4, 0x0
li r3, 0x1
li r0, 0x5
stw r4, lbl_806D1210_p4(r13)
stb r3, lbl_806D122A_p4(r13)
stb r4, lbl_806D121C_p4(r13)
stw r0, lbl_806CF0E4_p4(r13)
bl ServiceLatch_CheckTriggered_p4
clrlwi. r0, r3, 24
bne card_rw_state_machine_L_80097494
li r0, 0x1
stw r0, lbl_806D1210_p4(r13)
b card_rw_state_machine_L_800974B0
card_rw_state_machine_L_80097494:
li r0, 0x0
stb r0, lbl_806D1227_p4(r13)
bl Sci2Card_Singleton_Get_p4
bl card_eject_p4
li r0, 0x0
stb r3, lbl_806D121C_p4(r13)
stb r0, lbl_806CF0D4_p4(r13)
card_rw_state_machine_L_800974B0:
lwz r3, lbl_806D1220_p4(r13)
li r0, 0x1
stw r0, lbl_806CF0D8_p4(r13)
addi r0, r3, 0x1
stw r0, lbl_806D1220_p4(r13)
card_rw_state_machine_L_800974C4:
lbz r3, lbl_806D1227_p4(r13)
neg r0, r3
or r0, r0, r3
srwi r0, r0, 31
cmplwi r0, 0x1
bne card_rw_state_machine_L_800974E4
li r0, 0x3
stw r0, lbl_806CF0D0_p4(r13)
card_rw_state_machine_L_800974E4:
bl card_eject_state_machine_p4
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_rw_state_machine_L_80097544
lwz r0, lbl_806D1210_p4(r13)
cmpwi r0, 0x0
beq card_rw_state_machine_L_8009751C
cmpwi r0, 0x1
beq card_rw_state_machine_L_8009751C
lwz r4, lbl_806D1220_p4(r13)
li r3, 0x0
subi r0, r4, 0x1
stw r0, lbl_806D1220_p4(r13)
b card_rw_state_machine_L_80097548
card_rw_state_machine_L_8009751C:
li r3, 0x3
li r4, 0x5
li r0, 0x2
stw r3, lbl_806CF0E8_p4(r13)
li r3, 0x1
stw r4, lbl_806CF0D0_p4(r13)
stw r0, lbl_806CF0D8_p4(r13)
b card_rw_state_machine_L_80097548
card_rw_state_machine_L_8009753C:
li r3, 0x1
b card_rw_state_machine_L_80097548
card_rw_state_machine_L_80097544:
li r3, 0x0
card_rw_state_machine_L_80097548:
lmw r14, 0x38(r1)
lwz r0, 0x84(r1)
mtlr r0
addi r1, r1, 0x80
blr
}
#endif
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardReadCommand.c (0x8009755c) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
extern unsigned int OSGetTick_p5(void);
extern unsigned char ServiceLatch_CheckTriggered_p5(void);
extern unsigned char card_rw_state_machine_p5(void);
extern unsigned char card_read_state_machine_p5(void);
extern void *Sci2Card_Singleton_Get_p5(void);
extern unsigned char Sci2Card_SendCmdOptions_p5(void *card_p5, unsigned char read_p5,
unsigned char option_p5);
extern int lbl_806CF0D8_p5;
extern int lbl_806CF0DC_p5;
extern int lbl_806CF0E4_p5;
extern int lbl_806D1210_p5;
extern int lbl_806D1214_p5;
extern unsigned char lbl_806D121C_p5;
extern int lbl_806D1220_p5;
extern unsigned char lbl_806D1227_p5;
extern unsigned char lbl_806D1228_p5;
extern unsigned char lbl_806D122A_p5;
extern unsigned int lbl_806D122C_p5;
unsigned char card_rw_kick_state_machine(void)
{
if (lbl_806D1228_p5 == 1) {
return 0;
}
lbl_806D122C_p5 = OSGetTick_p5();
lbl_806D1210_p5 = 0;
lbl_806D122A_p5 = 1;
lbl_806D121C_p5 = 0;
lbl_806CF0E4_p5 = 5;
if (!ServiceLatch_CheckTriggered_p5()) {
lbl_806D1210_p5 = 1;
return 1;
}
lbl_806D1227_p5 = 0;
lbl_806D1220_p5 = 0;
lbl_806CF0D8_p5 = 0;
card_rw_state_machine_p5();
return 1;
}
unsigned char card_read_tick(void)
{
if (!ServiceLatch_CheckTriggered_p5()) {
return 1;
}
if (card_read_state_machine_p5() == 1) {
if (lbl_806D1210_p5 == 1 && lbl_806D1214_p5 != 5) {
lbl_806CF0DC_p5 = 0;
}
return 1;
}
return 0;
}
unsigned char card_send_read_cmd_init(void)
{
lbl_806D1210_p5 = 0;
lbl_806D122A_p5 = 1;
lbl_806D121C_p5 = 0;
lbl_806CF0E4_p5 = 5;
if (!ServiceLatch_CheckTriggered_p5()) {
lbl_806D1210_p5 = 1;
} else {
void *card_p5 = Sci2Card_Singleton_Get_p5();
lbl_806D121C_p5 = Sci2Card_SendCmdOptions_p5(card_p5, 1, 0);
}
lbl_806CF0DC_p5 = -1;
return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/card_read_state_machine.c (0x800976c0) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern void PlayerData_ResetForFlow_p6();
extern void Sci2Card_GetResponsePayload_p6();
extern void Sci2Card_GetResponseStatus_p6();
extern void Sci2Card_IsIdleOrExhausted_p6();
extern void Sci2Card_IsRetryExhausted_p6();
extern void Sci2Card_IsStatus2A_p6();
extern void Sci2Card_IsStatus2Five_p6();
extern void Sci2Card_IsStatus2One_p6();
extern void Sci2Card_IsStatus2Three_p6();
extern void Sci2Card_IsStatus2Two_p6();
extern void Sci2Card_IsStatus3Five_p6();
extern void Sci2Card_IsStatusOkNonTerm_p6();
extern void Sci2Card_SendCmdOptions_p6();
extern void Sci2Card_Singleton_Get_p6();
extern void ServiceLatch_CheckTriggered_p6();
extern void __copy();
extern void card_backup_p6();
extern void fn_801D4FF4_p6();
extern void memset_p6();
extern unsigned int lbl_806D1210_p6;
extern unsigned int lbl_806D1214_p6;
extern unsigned int lbl_806D121C_p6;
extern unsigned int lbl_806D1224_p6;
extern unsigned int lbl_806D122A_p6;
extern unsigned int lbl_806D122B_p6;
extern unsigned int g_playerData_p6[];
extern unsigned int lbl_80598A60_p6[];
extern unsigned int lbl_805AC55C_p6[];
extern unsigned int lbl_805D275C_p6[];
#ifndef NON_MATCHING /* C version: end of this file */
void card_read_state_machine(void);

#pragma section R".extab_user"

__declspec(section ".extab_user") static const unsigned char extab_card_read_state_machine_p6[8] = {
0x90, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn_p6; unsigned int fn_size_p6; void *extab_p6; } extabindex_card_read_state_machine_p6 = {
(void *)&card_read_state_machine, 0x00000C60, (void *)extab_card_read_state_machine_p6
};
asm void card_read_state_machine(void) {
nofralloc
stwu r1, -0x140(r1)
mflr r0
stw r0, 0x144(r1)
stmw r14, 0xf8(r1)
bl ServiceLatch_CheckTriggered_p6
clrlwi. r0, r3, 24
bne card_read_state_machine_L_800976EC
li r0, 0x1
li r3, 0x1
stw r0, lbl_806D1210_p6(r13)
b card_read_state_machine_L_8009830C
card_read_state_machine_L_800976EC:
lwz r0, lbl_806D1210_p6(r13)
cmpwi r0, 0x0
beq card_read_state_machine_L_80097700
li r3, 0x1
b card_read_state_machine_L_8009830C
card_read_state_machine_L_80097700:
bl Sci2Card_Singleton_Get_p6
lbz r0, lbl_806D121C_p6(r13)
mr r14, r3
cmplwi r0, 0x0
bne card_read_state_machine_L_8009772C
li r4, 0x1
li r5, 0x0
bl Sci2Card_SendCmdOptions_p6
stb r3, lbl_806D121C_p6(r13)
li r3, 0x0
b card_read_state_machine_L_8009830C
card_read_state_machine_L_8009772C:
bl Sci2Card_IsIdleOrExhausted_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_80098308
mr r3, r14
bl Sci2Card_IsStatusOkNonTerm_p6
clrlwi. r0, r3, 24
bne card_read_state_machine_L_80097864
bl Sci2Card_Singleton_Get_p6
li r0, 0x0
mr r14, r3
stw r0, lbl_806D1210_p6(r13)
bl Sci2Card_IsStatus3Five_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_80097774
li r0, 0x2
stw r0, lbl_806D1210_p6(r13)
card_read_state_machine_L_80097774:
mr r3, r14
bl Sci2Card_IsRetryExhausted_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_80097790
li r0, 0x65
stw r0, lbl_806D1210_p6(r13)
card_read_state_machine_L_80097790:
mr r3, r14
bl Sci2Card_IsStatus2Two_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_800977AC
li r0, 0x66
stw r0, lbl_806D1210_p6(r13)
card_read_state_machine_L_800977AC:
mr r3, r14
bl Sci2Card_IsStatus2One_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_800977C8
li r0, 0x67
stw r0, lbl_806D1210_p6(r13)
card_read_state_machine_L_800977C8:
mr r3, r14
bl Sci2Card_IsStatus2Three_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_800977E4
li r0, 0x68
stw r0, lbl_806D1210_p6(r13)
card_read_state_machine_L_800977E4:
mr r3, r14
bl Sci2Card_IsStatus2Five_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_80097800
li r0, 0x69
stw r0, lbl_806D1210_p6(r13)
card_read_state_machine_L_80097800:
mr r3, r14
bl Sci2Card_IsStatus2A_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_8009781C
li r0, 0x6a
stw r0, lbl_806D1210_p6(r13)
card_read_state_machine_L_8009781C:
lwz r0, lbl_806D1210_p6(r13)
cmpwi r0, 0x0
bne card_read_state_machine_L_8009785C
mr r3, r14
addi r4, r1, 0x8
addi r5, r1, 0x9
addi r6, r1, 0xa
bl Sci2Card_GetResponseStatus_p6
lbz r0, 0xa(r1)
cmplwi r0, 0x32
bne card_read_state_machine_L_80097854
li r0, 0x64
stw r0, lbl_806D1210_p6(r13)
b card_read_state_machine_L_8009785C
card_read_state_machine_L_80097854:
li r0, 0x1
stw r0, lbl_806D1210_p6(r13)
card_read_state_machine_L_8009785C:
li r3, 0x1
b card_read_state_machine_L_8009830C
card_read_state_machine_L_80097864:
mr r3, r14
bl Sci2Card_IsStatusOkNonTerm_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_800982F8
li r0, 0x1
lis r3, lbl_805AC55C_p6@ha
stb r0, lbl_806D1224_p6(r13)
addi r3, r3, lbl_805AC55C_p6@l
li r4, 0x0
li r5, 0x45
bl memset_p6
lis r4, lbl_805AC55C_p6@ha
mr r3, r14
addi r4, r4, lbl_805AC55C_p6@l
bl Sci2Card_GetResponsePayload_p6
lis r3, g_playerData_p6@ha
lis r4, lbl_805AC55C_p6@ha
addi r3, r3, g_playerData_p6@l
li r5, 0x1
addi r4, r4, lbl_805AC55C_p6@l
bl fn_801D4FF4_p6
clrlwi r0, r3, 24
cmplwi r0, 0x1
bne card_read_state_machine_L_800982D8
lis r3, g_playerData_p6@ha
lis r4, lbl_805D275C_p6@ha
addi r15, r3, g_playerData_p6@l
lwz r30, 0x58(r15)
addi r6, r4, lbl_805D275C_p6@l
lwz r0, 0x50(r15)
stw r30, 0xd8(r1)
lwz r30, 0x5c(r15)
stw r0, 0x50(r6)
lwz r0, 0xd8(r1)
stw r30, 0x14(r1)
lwz r30, 0x60(r15)
stw r0, 0x58(r6)
lwz r0, 0x14(r1)
stw r30, 0x18(r1)
lwz r30, 0x64(r15)
stw r0, 0x5c(r6)
lwz r0, 0x18(r1)
lwz r29, 0x0(r15)
lwz r28, 0x4(r15)
lwz r27, 0x8(r15)
lbz r26, 0xc(r15)
lbz r25, 0xd(r15)
lhz r24, 0xe(r15)
lhz r23, 0x10(r15)
lwz r22, 0x14(r15)
lbz r21, 0x18(r15)
lbz r20, 0x19(r15)
lbz r19, 0x1a(r15)
lwz r18, 0x1c(r15)
lwz r17, 0x20(r15)
lwz r16, 0x24(r15)
lwz r14, 0x28(r15)
lwz r12, 0x2c(r15)
lwz r11, 0x30(r15)
lwz r10, 0x34(r15)
lwz r9, 0x38(r15)
lwz r8, 0x3c(r15)
lwz r7, 0x40(r15)
lwz r5, 0x44(r15)
lwz r4, 0x48(r15)
lwz r3, 0x4c(r15)
lwz r31, 0x54(r15)
stw r0, 0x60(r6)
mr r0, r30
stw r30, 0x1c(r1)
stw r29, 0x0(r6)
stw r28, 0x4(r6)
stw r27, 0x8(r6)
stb r26, 0xc(r6)
stb r25, 0xd(r6)
sth r24, 0xe(r6)
sth r23, 0x10(r6)
stw r22, 0x14(r6)
stb r21, 0x18(r6)
stb r20, 0x19(r6)
stb r19, 0x1a(r6)
stw r18, 0x1c(r6)
stw r17, 0x20(r6)
stw r16, 0x24(r6)
stw r14, 0x28(r6)
stw r12, 0x2c(r6)
stw r11, 0x30(r6)
stw r10, 0x34(r6)
stw r9, 0x38(r6)
stw r8, 0x3c(r6)
stw r7, 0x40(r6)
stw r5, 0x44(r6)
stw r4, 0x48(r6)
stw r3, 0x4c(r6)
stw r31, 0x54(r6)
stw r0, 0x64(r6)
addi r0, r15, 0xa8
lwz r23, 0x68(r15)
lwz r22, 0x6c(r15)
mr r4, r0
stw r0, 0x10(r1)
addi r3, r6, 0xa8
lwz r21, 0x70(r15)
li r5, 0x79
lwz r20, 0x74(r15)
lwz r19, 0x78(r15)
lwz r18, 0x7c(r15)
lwz r17, 0x80(r15)
lwz r16, 0x84(r15)
lwz r14, 0x88(r15)
lwz r12, 0x8c(r15)
lwz r11, 0x90(r15)
lwz r10, 0x94(r15)
lwz r9, 0x98(r15)
lwz r8, 0x9c(r15)
lwz r7, 0xa0(r15)
lwz r0, 0xa4(r15)
stw r23, 0x68(r6)
stw r22, 0x6c(r6)
stw r21, 0x70(r6)
stw r20, 0x74(r6)
stw r19, 0x78(r6)
stw r18, 0x7c(r6)
stw r17, 0x80(r6)
stw r16, 0x84(r6)
stw r14, 0x88(r6)
stw r12, 0x8c(r6)
stw r11, 0x90(r6)
stw r10, 0x94(r6)
stw r9, 0x98(r6)
stw r8, 0x9c(r6)
stw r7, 0xa0(r6)
stw r0, 0xa4(r6)
bl __copy
lis r3, g_playerData_p6@ha
lis r4, lbl_805D275C_p6@ha
addi r3, r3, g_playerData_p6@l
li r5, 0x69
addi r0, r3, 0x121
addi r6, r4, lbl_805D275C_p6@l
stw r0, 0xc(r1)
mr r4, r0
addi r3, r6, 0x121
bl __copy
lis r4, g_playerData_p6@ha
lis r3, lbl_805D275C_p6@ha
addi r30, r4, g_playerData_p6@l
lbz r27, 0x198(r30)
addi r26, r3, lbl_805D275C_p6@l
lwz r29, 0x1ce(r30)
extsb. r0, r27
lwz r0, 0x1c6(r30)
stw r29, 0xdc(r1)
lwz r29, 0x1d4(r30)
stw r0, 0x1c6(r26)
lwz r0, 0xdc(r1)
stw r29, 0x20(r1)
lbz r29, 0x1d8(r30)
stw r0, 0x1ce(r26)
lwz r0, 0x20(r1)
stw r29, 0x24(r1)
lbz r29, 0x1d9(r30)
stw r0, 0x1d4(r26)
lwz r0, 0x24(r1)
stw r29, 0x28(r1)
lbz r29, 0x1da(r30)
stb r0, 0x1d8(r26)
lwz r0, 0x28(r1)
lwz r25, 0x18c(r30)
lwz r24, 0x190(r30)
lwz r23, 0x194(r30)
lbz r28, 0x199(r30)
lbz r22, 0x19a(r30)
lbz r21, 0x19b(r30)
lbz r20, 0x19c(r30)
lbz r19, 0x19d(r30)
lbz r18, 0x19e(r30)
lbz r17, 0x19f(r30)
lbz r16, 0x1a0(r30)
lwz r14, 0x1a4(r30)
lbz r12, 0x1a8(r30)
lwz r11, 0x1ac(r30)
lbz r10, 0x1b0(r30)
lbz r9, 0x1b1(r30)
lwz r8, 0x1b4(r30)
lbz r7, 0x1b8(r30)
lbz r6, 0x1b9(r30)
lwz r5, 0x1ba(r30)
lwz r4, 0x1be(r30)
lwz r3, 0x1c2(r30)
lwz r31, 0x1ca(r30)
stb r0, 0x1d9(r26)
mr r0, r29
stw r29, 0x2c(r1)
stw r25, 0x18c(r26)
stw r24, 0x190(r26)
stw r23, 0x194(r26)
stb r27, 0x198(r26)
stb r28, 0x199(r26)
stb r22, 0x19a(r26)
stb r21, 0x19b(r26)
stb r20, 0x19c(r26)
stb r19, 0x19d(r26)
stb r18, 0x19e(r26)
stb r17, 0x19f(r26)
stb r16, 0x1a0(r26)
stw r14, 0x1a4(r26)
stb r12, 0x1a8(r26)
stw r11, 0x1ac(r26)
stb r10, 0x1b0(r26)
stb r9, 0x1b1(r26)
stw r8, 0x1b4(r26)
stb r7, 0x1b8(r26)
stb r6, 0x1b9(r26)
stw r5, 0x1ba(r26)
stw r4, 0x1be(r26)
stw r3, 0x1c2(r26)
stw r31, 0x1ca(r26)
stb r0, 0x1da(r26)
ble card_read_state_machine_L_80097F50
cmplwi r28, 0x0
bne card_read_state_machine_L_80097F50
lwz r0, 0x54(r15)
lis r3, lbl_80598A60_p6@ha
addi r31, r3, lbl_80598A60_p6@l
lwz r3, 0x4c(r15)
stw r0, 0xe0(r1)
lwz r0, 0x58(r15)
stw r3, 0xdc(r31)
lwz r3, 0xe0(r1)
stw r0, 0x30(r1)
lwz r0, 0x5c(r15)
stw r3, 0xe4(r31)
lwz r3, 0x30(r1)
stw r0, 0x34(r1)
lwz r0, 0x60(r15)
stw r3, 0xe8(r31)
lwz r3, 0x34(r1)
stw r0, 0x38(r1)
lwz r0, 0x64(r15)
stw r3, 0xec(r31)
lwz r3, 0x38(r1)
stw r0, 0x3c(r1)
lwz r0, 0x68(r15)
stw r3, 0xf0(r31)
lwz r3, 0x3c(r1)
stw r0, 0x40(r1)
lwz r0, 0x6c(r15)
stw r3, 0xf4(r31)
lwz r3, 0x40(r1)
stw r0, 0x44(r1)
lwz r0, 0x70(r15)
stw r3, 0xf8(r31)
lwz r3, 0x44(r1)
stw r0, 0x48(r1)
lwz r0, 0x74(r15)
stw r3, 0xfc(r31)
lwz r3, 0x48(r1)
stw r0, 0x4c(r1)
lwz r0, 0x78(r15)
stw r3, 0x100(r31)
lwz r3, 0x4c(r1)
stw r0, 0x50(r1)
lwz r0, 0x7c(r15)
stw r3, 0x104(r31)
lwz r3, 0x50(r1)
stw r0, 0x54(r1)
lwz r0, 0x80(r15)
stw r3, 0x108(r31)
lwz r3, 0x54(r1)
stw r0, 0x58(r1)
lwz r0, 0x84(r15)
stw r3, 0x10c(r31)
lwz r3, 0x58(r1)
stw r0, 0x5c(r1)
lwz r0, 0x88(r15)
stw r3, 0x110(r31)
lwz r3, 0x5c(r1)
stw r0, 0x60(r1)
lwz r0, 0x8c(r15)
stw r3, 0x114(r31)
lwz r3, 0x60(r1)
stw r0, 0x64(r1)
lwz r0, 0x90(r15)
stw r3, 0x118(r31)
lwz r3, 0x64(r1)
stw r0, 0x68(r1)
lwz r0, 0x94(r15)
stw r3, 0x11c(r31)
lwz r3, 0x68(r1)
stw r0, 0x6c(r1)
lwz r0, 0x98(r15)
stw r3, 0x120(r31)
lwz r3, 0x6c(r1)
stw r0, 0x70(r1)
lwz r0, 0x9c(r15)
stw r3, 0x124(r31)
lwz r3, 0x70(r1)
stw r0, 0x74(r1)
lwz r0, 0xa0(r15)
lbz r25, 0xc(r15)
lbz r24, 0xd(r15)
lhz r23, 0xe(r15)
lhz r22, 0x10(r15)
lwz r21, 0x14(r15)
lbz r20, 0x18(r15)
lbz r19, 0x19(r15)
lbz r18, 0x1a(r15)
lwz r17, 0x1c(r15)
lwz r16, 0x20(r15)
lwz r14, 0x24(r15)
lwz r12, 0x28(r15)
lwz r11, 0x2c(r15)
lwz r10, 0x30(r15)
lwz r9, 0x34(r15)
lwz r8, 0x38(r15)
lwz r7, 0x3c(r15)
lwz r6, 0x40(r15)
lwz r5, 0x44(r15)
lwz r4, 0x48(r15)
lwz r29, 0x50(r15)
stw r0, 0x78(r1)
lwz r0, 0xa4(r15)
li r15, 0x2
stw r15, lbl_806D1214_p6(r13)
li r15, 0x0
lwz r28, 0x0(r30)
stw r3, 0x128(r31)
lwz r3, 0x74(r1)
stb r15, lbl_806D122A_p6(r13)
li r15, 0x1
lwz r27, 0x4(r30)
lwz r26, 0x8(r30)
stw r15, lbl_806D1210_p6(r13)
li r15, 0x0
stw r3, 0x12c(r31)
lwz r3, 0x78(r1)
stb r15, lbl_806D122B_p6(r13)
li r15, 0x1
stb r15, 0x64(r31)
stw r28, 0x90(r31)
stw r27, 0x94(r31)
stw r26, 0x98(r31)
stb r25, 0x9c(r31)
stb r24, 0x9d(r31)
sth r23, 0x9e(r31)
sth r22, 0xa0(r31)
stw r21, 0xa4(r31)
stb r20, 0xa8(r31)
stb r19, 0xa9(r31)
stb r18, 0xaa(r31)
stw r17, 0xac(r31)
stw r16, 0xb0(r31)
stw r14, 0xb4(r31)
stw r12, 0xb8(r31)
stw r11, 0xbc(r31)
stw r10, 0xc0(r31)
stw r9, 0xc4(r31)
stw r8, 0xc8(r31)
stw r7, 0xcc(r31)
stw r6, 0xd0(r31)
stw r5, 0xd4(r31)
stw r4, 0xd8(r31)
stw r29, 0xe0(r31)
stw r3, 0x130(r31)
stw r0, 0x134(r31)
lwz r4, 0x10(r1)
addi r3, r31, 0x138
li r5, 0x79
bl __copy
lwz r4, 0xc(r1)
addi r3, r31, 0x1b1
li r5, 0x69
bl __copy
lwz r15, 0x1d4(r30)
lwz r0, 0x1ca(r30)
stw r15, 0xe4(r1)
lbz r15, 0x1d8(r30)
stw r0, 0x25a(r31)
lwz r0, 0xe4(r1)
stw r15, 0x7c(r1)
lbz r15, 0x1d9(r30)
stw r0, 0x264(r31)
lwz r0, 0x7c(r1)
stw r15, 0x80(r1)
lwz r16, 0x18c(r30)
lwz r17, 0x190(r30)
lwz r18, 0x194(r30)
lbz r19, 0x198(r30)
lbz r20, 0x199(r30)
lbz r21, 0x19a(r30)
lbz r22, 0x19b(r30)
lbz r23, 0x19c(r30)
lbz r24, 0x19d(r30)
lbz r25, 0x19e(r30)
lbz r26, 0x19f(r30)
lbz r27, 0x1a0(r30)
lwz r28, 0x1a4(r30)
lbz r29, 0x1a8(r30)
lwz r12, 0x1ac(r30)
lbz r11, 0x1b0(r30)
lbz r10, 0x1b1(r30)
lwz r9, 0x1b4(r30)
lbz r8, 0x1b8(r30)
lbz r7, 0x1b9(r30)
lwz r6, 0x1ba(r30)
lwz r5, 0x1be(r30)
lwz r4, 0x1c2(r30)
lwz r3, 0x1c6(r30)
lwz r14, 0x1ce(r30)
lbz r15, 0x1da(r30)
stb r0, 0x268(r31)
lwz r0, 0x80(r1)
stw r16, 0x21c(r31)
stw r17, 0x220(r31)
stw r18, 0x224(r31)
stb r19, 0x228(r31)
stb r20, 0x229(r31)
stb r21, 0x22a(r31)
stb r22, 0x22b(r31)
stb r23, 0x22c(r31)
stb r24, 0x22d(r31)
stb r25, 0x22e(r31)
stb r26, 0x22f(r31)
stb r27, 0x230(r31)
stw r28, 0x234(r31)
stb r29, 0x238(r31)
stw r12, 0x23c(r31)
stb r11, 0x240(r31)
stb r10, 0x241(r31)
stw r9, 0x244(r31)
stb r8, 0x248(r31)
stb r7, 0x249(r31)
stw r6, 0x24a(r31)
stw r5, 0x24e(r31)
stw r4, 0x252(r31)
stw r3, 0x256(r31)
stw r14, 0x25e(r31)
stb r0, 0x269(r31)
stb r15, 0x26a(r31)
bl card_backup_p6
b card_read_state_machine_L_800982F0
card_read_state_machine_L_80097F50:
li r3, 0x0
li r0, 0x3
cmplwi r28, 0x1
stb r3, lbl_806D122A_p6(r13)
stw r0, lbl_806D1210_p6(r13)
stb r3, lbl_806D122B_p6(r13)
bne card_read_state_machine_L_80097F7C
li r0, 0x6
stb r3, 0x198(r30)
stw r0, lbl_806D1214_p6(r13)
b card_read_state_machine_L_800982F0
card_read_state_machine_L_80097F7C:
lis r3, g_playerData_p6@ha
lwzu r29, g_playerData_p6@l(r3)
lwz r0, 0x54(r15)
lis r4, lbl_80598A60_p6@ha
lwz r28, 0x4(r3)
addi r14, r4, lbl_80598A60_p6@l
lwz r27, 0x8(r3)
lwz r3, 0x4c(r15)
stw r0, 0xe8(r1)
lwz r0, 0x58(r15)
stw r3, 0xdc(r14)
lwz r3, 0xe8(r1)
stw r0, 0x84(r1)
lwz r0, 0x5c(r15)
stw r3, 0xe4(r14)
lwz r3, 0x84(r1)
stw r0, 0x88(r1)
lwz r0, 0x60(r15)
stw r3, 0xe8(r14)
lwz r3, 0x88(r1)
stw r0, 0x8c(r1)
lwz r0, 0x64(r15)
stw r3, 0xec(r14)
lwz r3, 0x8c(r1)
stw r0, 0x90(r1)
lwz r0, 0x68(r15)
stw r3, 0xf0(r14)
lwz r3, 0x90(r1)
stw r0, 0x94(r1)
lwz r0, 0x6c(r15)
stw r3, 0xf4(r14)
lwz r3, 0x94(r1)
stw r0, 0x98(r1)
lwz r0, 0x70(r15)
stw r3, 0xf8(r14)
lwz r3, 0x98(r1)
stw r0, 0x9c(r1)
lwz r0, 0x74(r15)
stw r3, 0xfc(r14)
lwz r3, 0x9c(r1)
stw r0, 0xa0(r1)
lwz r0, 0x78(r15)
stw r3, 0x100(r14)
lwz r3, 0xa0(r1)
stw r0, 0xa4(r1)
lwz r0, 0x7c(r15)
stw r3, 0x104(r14)
lwz r3, 0xa4(r1)
stw r0, 0xa8(r1)
lwz r0, 0x80(r15)
stw r3, 0x108(r14)
lwz r3, 0xa8(r1)
stw r0, 0xac(r1)
lwz r0, 0x84(r15)
stw r3, 0x10c(r14)
lwz r3, 0xac(r1)
stw r0, 0xb0(r1)
lwz r0, 0x88(r15)
stw r3, 0x110(r14)
lwz r3, 0xb0(r1)
stw r0, 0xb4(r1)
lwz r0, 0x8c(r15)
stw r3, 0x114(r14)
lwz r3, 0xb4(r1)
stw r0, 0xb8(r1)
lwz r0, 0x90(r15)
stw r3, 0x118(r14)
lwz r3, 0xb8(r1)
stw r0, 0xbc(r1)
lwz r0, 0x94(r15)
stw r3, 0x11c(r14)
lwz r3, 0xbc(r1)
stw r0, 0xc0(r1)
lwz r0, 0x98(r15)
stw r3, 0x120(r14)
lwz r3, 0xc0(r1)
stw r0, 0xc4(r1)
lwz r0, 0x9c(r15)
stw r3, 0x124(r14)
lwz r3, 0xc4(r1)
stw r0, 0xc8(r1)
lwz r0, 0xa0(r15)
stw r3, 0x128(r14)
lwz r3, 0xc8(r1)
stw r0, 0xcc(r1)
lbz r26, 0xc(r15)
lbz r25, 0xd(r15)
lhz r24, 0xe(r15)
lhz r23, 0x10(r15)
lwz r22, 0x14(r15)
lbz r21, 0x18(r15)
lbz r20, 0x19(r15)
lbz r19, 0x1a(r15)
lwz r18, 0x1c(r15)
lwz r17, 0x20(r15)
lwz r16, 0x24(r15)
lwz r12, 0x28(r15)
lwz r11, 0x2c(r15)
lwz r10, 0x30(r15)
lwz r9, 0x34(r15)
lwz r8, 0x38(r15)
lwz r7, 0x3c(r15)
lwz r6, 0x40(r15)
lwz r5, 0x44(r15)
lwz r4, 0x48(r15)
lwz r31, 0x50(r15)
lwz r0, 0xa4(r15)
li r15, 0x5
stw r3, 0x12c(r14)
lwz r3, 0xcc(r1)
stw r15, lbl_806D1214_p6(r13)
li r15, 0x1
stb r15, 0x64(r14)
stw r29, 0x90(r14)
stw r28, 0x94(r14)
stw r27, 0x98(r14)
stb r26, 0x9c(r14)
stb r25, 0x9d(r14)
sth r24, 0x9e(r14)
sth r23, 0xa0(r14)
stw r22, 0xa4(r14)
stb r21, 0xa8(r14)
stb r20, 0xa9(r14)
stb r19, 0xaa(r14)
stw r18, 0xac(r14)
stw r17, 0xb0(r14)
stw r16, 0xb4(r14)
stw r12, 0xb8(r14)
stw r11, 0xbc(r14)
stw r10, 0xc0(r14)
stw r9, 0xc4(r14)
stw r8, 0xc8(r14)
stw r7, 0xcc(r14)
stw r6, 0xd0(r14)
stw r5, 0xd4(r14)
stw r4, 0xd8(r14)
stw r31, 0xe0(r14)
stw r3, 0x130(r14)
stw r0, 0x134(r14)
lwz r4, 0x10(r1)
addi r3, r14, 0x138
li r5, 0x79
bl __copy
lwz r4, 0xc(r1)
addi r3, r14, 0x1b1
li r5, 0x69
bl __copy
lwz r29, 0x1d4(r30)
lwz r0, 0x1ca(r30)
stw r29, 0xec(r1)
lbz r29, 0x1d8(r30)
stw r0, 0x25a(r14)
lwz r0, 0xec(r1)
stw r29, 0xd0(r1)
lbz r29, 0x1d9(r30)
stw r0, 0x264(r14)
lwz r0, 0xd0(r1)
stw r29, 0xd4(r1)
lwz r28, 0x18c(r30)
lwz r27, 0x190(r30)
lwz r26, 0x194(r30)
lbz r25, 0x198(r30)
lbz r24, 0x199(r30)
lbz r23, 0x19a(r30)
lbz r22, 0x19b(r30)
lbz r21, 0x19c(r30)
lbz r20, 0x19d(r30)
lbz r19, 0x19e(r30)
lbz r18, 0x19f(r30)
lbz r17, 0x1a0(r30)
lwz r16, 0x1a4(r30)
lbz r15, 0x1a8(r30)
lwz r12, 0x1ac(r30)
lbz r11, 0x1b0(r30)
lbz r10, 0x1b1(r30)
lwz r9, 0x1b4(r30)
lbz r8, 0x1b8(r30)
lbz r7, 0x1b9(r30)
lwz r6, 0x1ba(r30)
lwz r5, 0x1be(r30)
lwz r4, 0x1c2(r30)
lwz r3, 0x1c6(r30)
lwz r31, 0x1ce(r30)
lbz r29, 0x1da(r30)
stb r0, 0x268(r14)
lwz r0, 0xd4(r1)
stw r28, 0x21c(r14)
stw r27, 0x220(r14)
stw r26, 0x224(r14)
stb r25, 0x228(r14)
stb r24, 0x229(r14)
stb r23, 0x22a(r14)
stb r22, 0x22b(r14)
stb r21, 0x22c(r14)
stb r20, 0x22d(r14)
stb r19, 0x22e(r14)
stb r18, 0x22f(r14)
stb r17, 0x230(r14)
stw r16, 0x234(r14)
stb r15, 0x238(r14)
stw r12, 0x23c(r14)
stb r11, 0x240(r14)
stb r10, 0x241(r14)
stw r9, 0x244(r14)
stb r8, 0x248(r14)
stb r7, 0x249(r14)
stw r6, 0x24a(r14)
stw r5, 0x24e(r14)
stw r4, 0x252(r14)
stw r3, 0x256(r14)
stw r31, 0x25e(r14)
stb r0, 0x269(r14)
stb r29, 0x26a(r14)
bl card_backup_p6
b card_read_state_machine_L_800982F0
card_read_state_machine_L_800982D8:
bl PlayerData_ResetForFlow_p6
li r3, 0x0
li r0, 0x4
stb r3, lbl_806D122A_p6(r13)
stw r0, lbl_806D1210_p6(r13)
stb r3, lbl_806D122B_p6(r13)
card_read_state_machine_L_800982F0:
li r3, 0x1
b card_read_state_machine_L_8009830C
card_read_state_machine_L_800982F8:
mr r3, r14
li r4, 0x1
li r5, 0x0
bl Sci2Card_SendCmdOptions_p6
card_read_state_machine_L_80098308:
li r3, 0x0
card_read_state_machine_L_8009830C:
lmw r14, 0xf8(r1)
lwz r0, 0x144(r1)
mtlr r0
addi r1, r1, 0x140
blr
}
#endif
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardReadCommandUnused.c (0x80098320) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
extern unsigned char ServiceLatch_CheckTriggered_p7(void);
extern void *Sci2Card_Singleton_Get_p7(void);
extern unsigned char Sci2Card_SendCmdOptions_p7(void *card_p7, unsigned char read_p7,
unsigned char option_p7);
extern int lbl_806CF0E4_p7;
extern int lbl_806D1210_p7;
extern unsigned char lbl_806D121C_p7;
extern unsigned char lbl_806D122A_p7;
unsigned char card_send_read_cmd_init_dup_unused(void)
{
lbl_806D1210_p7 = 0;
lbl_806D122A_p7 = 1;
lbl_806D121C_p7 = 0;
lbl_806CF0E4_p7 = 5;
if (!ServiceLatch_CheckTriggered_p7()) {
lbl_806D1210_p7 = 1;
return 1;
}
lbl_806D121C_p7 = Sci2Card_SendCmdOptions_p7(Sci2Card_Singleton_Get_p7(), 1, 0);
return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/card_is_ejected.c (0x8009838c) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern unsigned char lbl_806D1227_p8;
unsigned int card_is_ejected(void) {
return lbl_806D1227_p8 != 0;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardPingCommand.c (0x800983a0) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
extern unsigned char ServiceLatch_CheckTriggered_p9(void);
extern void *Sci2Card_Singleton_Get_p9(void);
extern unsigned char Sci2Card_SendCmdPing_p9(void *card_p9);
extern unsigned char Sci2Card_IsIdleOrExhausted_p9(void *card_p9);
extern unsigned char Sci2Card_IsStatusOkNonTerm_p9(void *card_p9);
extern unsigned char Sci2Card_IsStatus3Five_p9(void *card_p9);
extern unsigned char Sci2Card_IsRetryExhausted_p9(void *card_p9);
extern unsigned char Sci2Card_IsStatus2Two_p9(void *card_p9);
extern unsigned char Sci2Card_IsStatus2One_p9(void *card_p9);
extern unsigned char Sci2Card_IsStatus2Three_p9(void *card_p9);
extern unsigned char Sci2Card_IsStatus2Five_p9(void *card_p9);
extern unsigned char Sci2Card_IsStatus2A_p9(void *card_p9);
extern unsigned char Sci2Card_GetResponseStatus_p9(void *card_p9,
unsigned char *status1_p9,
unsigned char *status2_p9,
unsigned char *status3_p9);
extern int lbl_806CF0E4_p9;
extern int lbl_806D1210_p9;
extern unsigned char lbl_806D121C_p9;
extern int lbl_806D1220_p9;
extern unsigned char lbl_806D1224_p9;
extern unsigned char lbl_806D122A_p9;
extern unsigned char lbl_806D122B_p9;
extern unsigned char lbl_806D1237_p9;
static inline unsigned char CardPing_Begin_p9(void)
{
lbl_806D1210_p9 = 0;
lbl_806D122A_p9 = 1;
lbl_806D121C_p9 = 0;
lbl_806CF0E4_p9 = 5;
if (!ServiceLatch_CheckTriggered_p9()) {
lbl_806D1210_p9 = 1;
return 1;
}
if (lbl_806D1224_p9 == 1) {
return 1;
}
lbl_806D1220_p9 = 0;
lbl_806D121C_p9 = Sci2Card_SendCmdPing_p9(Sci2Card_Singleton_Get_p9());
return 1;
}
unsigned char card_ping_state_machine(void)
{
void *card_p9;
unsigned char completedStatus3_p9;
unsigned char completedStatus2_p9;
unsigned char completedStatus1_p9;
unsigned char activeStatus3_p9;
unsigned char activeStatus2_p9;
unsigned char activeStatus1_p9;
if (!ServiceLatch_CheckTriggered_p9() || lbl_806D1224_p9 == 1) {
lbl_806D1210_p9 = 1;
lbl_806D1224_p9 = 0;
return 1;
}
if (lbl_806D1210_p9 != 0) {
return 1;
}
card_p9 = Sci2Card_Singleton_Get_p9();
if (lbl_806D121C_p9 == 0) {
lbl_806D121C_p9 = CardPing_Begin_p9();
}
if (Sci2Card_IsIdleOrExhausted_p9(card_p9) == 1) {
if (!Sci2Card_IsStatusOkNonTerm_p9(card_p9)) {
card_p9 = Sci2Card_Singleton_Get_p9();
lbl_806D1210_p9 = 0;
if (Sci2Card_IsStatus3Five_p9(card_p9) == 1) {
lbl_806D1210_p9 = 2;
}
if (Sci2Card_IsRetryExhausted_p9(card_p9) == 1) {
lbl_806D1210_p9 = 101;
}
if (Sci2Card_IsStatus2Two_p9(card_p9) == 1) {
lbl_806D1210_p9 = 102;
}
if (Sci2Card_IsStatus2One_p9(card_p9) == 1) {
lbl_806D1210_p9 = 103;
}
if (Sci2Card_IsStatus2Three_p9(card_p9) == 1) {
lbl_806D1210_p9 = 104;
}
if (Sci2Card_IsStatus2Five_p9(card_p9) == 1) {
lbl_806D1210_p9 = 105;
}
if (Sci2Card_IsStatus2A_p9(card_p9) == 1) {
lbl_806D1210_p9 = 106;
}
if (lbl_806D1210_p9 == 0) {
Sci2Card_GetResponseStatus_p9(card_p9, &completedStatus1_p9,
&completedStatus2_p9, &completedStatus3_p9);
if (completedStatus3_p9 == 0x32) {
lbl_806D1210_p9 = 100;
} else {
lbl_806D1210_p9 = 1;
}
}
if (lbl_806D1210_p9 == 100) {
lbl_806D1237_p9 = 0;
}
return 1;
}
lbl_806D1237_p9 = 0;
lbl_806D122A_p9 = 0;
lbl_806D1210_p9 = 1;
lbl_806D122B_p9 = 0;
return 1;
}
if (!Sci2Card_IsStatusOkNonTerm_p9(card_p9)) {
card_p9 = Sci2Card_Singleton_Get_p9();
lbl_806D1210_p9 = 0;
if (Sci2Card_IsStatus3Five_p9(card_p9) == 1) {
lbl_806D1210_p9 = 2;
}
if (Sci2Card_IsRetryExhausted_p9(card_p9) == 1) {
lbl_806D1210_p9 = 101;
}
if (Sci2Card_IsStatus2Two_p9(card_p9) == 1) {
lbl_806D1210_p9 = 102;
}
if (Sci2Card_IsStatus2One_p9(card_p9) == 1) {
lbl_806D1210_p9 = 103;
}
if (Sci2Card_IsStatus2Three_p9(card_p9) == 1) {
lbl_806D1210_p9 = 104;
}
if (Sci2Card_IsStatus2Five_p9(card_p9) == 1) {
lbl_806D1210_p9 = 105;
}
if (Sci2Card_IsStatus2A_p9(card_p9) == 1) {
lbl_806D1210_p9 = 106;
}
if (lbl_806D1210_p9 == 0) {
Sci2Card_GetResponseStatus_p9(card_p9, &activeStatus1_p9,
&activeStatus2_p9, &activeStatus3_p9);
if (activeStatus3_p9 == 0x32) {
lbl_806D1210_p9 = 100;
} else {
lbl_806D1210_p9 = 1;
}
}
}
return 0;
}
unsigned char card_send_ping_cmd_init(void)
{
lbl_806D1210_p9 = 0;
lbl_806D122A_p9 = 1;
lbl_806D121C_p9 = 0;
lbl_806CF0E4_p9 = 5;
if (!ServiceLatch_CheckTriggered_p9()) {
lbl_806D1210_p9 = 1;
return 1;
}
if (lbl_806D1224_p9 == 1) {
return 1;
}
lbl_806D1220_p9 = 0;
lbl_806D121C_p9 = Sci2Card_SendCmdPing_p9(Sci2Card_Singleton_Get_p9());
return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/card_ping_clear_pending_flag.c (0x80098790) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern unsigned char lbl_806D1224_p10;
extern unsigned char lbl_806D1237_p10;
void card_ping_clear_pending_flag(void) {
if (lbl_806D1224_p10 == 0) {
lbl_806D1237_p10 = 0;
}
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardCleaningCommand.c (0x800987a8) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
extern unsigned char ServiceLatch_CheckTriggered_p11(void);
extern void *Sci2Card_Singleton_Get_p11(void);
extern unsigned char Sci2Card_SendCmdOptions_p11(void *card_p11, unsigned char read_p11,
unsigned char option_p11);
extern unsigned char Sci2Card_ForceFailState_p11(void *card_p11);
extern int lbl_806CF0E4_p11;
extern int lbl_806D1210_p11;
extern int lbl_806D1214_p11;
extern unsigned char lbl_806D121C_p11;
extern unsigned char lbl_806D1224_p11;
extern unsigned char lbl_806D122A_p11;
extern unsigned char lbl_806D1237_p11;
extern unsigned char lbl_806D1238_p11;
extern unsigned char Sci2Card_IsIdleOrExhausted_p11(void *card_p11);
extern unsigned char Sci2Card_IsStatusOk02_p11(void *card_p11);
extern unsigned char Sci2Card_IsStatusOkNonTerm_p11(void *card_p11);
extern unsigned char Sci2Card_IsStatus1OneTwoThree_p11(void *card_p11);
extern unsigned char lbl_806CF0D4_p11;
extern unsigned char lbl_806D122B_p11;
static inline unsigned char CardCleaning_Begin_p11(void)
{
void *card_p11;
lbl_806D1238_p11 = 1;
if (!ServiceLatch_CheckTriggered_p11()) {
lbl_806D122A_p11 = 1;
lbl_806D121C_p11 = 0;
lbl_806CF0E4_p11 = 5;
lbl_806D1224_p11 = 0;
lbl_806D1214_p11 = 0;
lbl_806D1210_p11 = 1;
return 1;
}
card_p11 = Sci2Card_Singleton_Get_p11();
if (lbl_806D1237_p11 == 0) {
lbl_806D1210_p11 = 0;
lbl_806D122A_p11 = 1;
lbl_806D121C_p11 = 0;
lbl_806D121C_p11 = Sci2Card_SendCmdOptions_p11(card_p11, 0, 1);
} else {
lbl_806D1210_p11 = 0;
lbl_806D122A_p11 = 1;
lbl_806D121C_p11 = 0;
lbl_806CF0E4_p11 = 5;
Sci2Card_ForceFailState_p11(card_p11);
}
return 1;
}
unsigned char card_cleaning_state_machine(void)
{
void *card_p11;
if (!ServiceLatch_CheckTriggered_p11()) {
lbl_806D1224_p11 = 0;
lbl_806D1214_p11 = 0;
lbl_806D1210_p11 = 1;
lbl_806D1238_p11 = 0;
return 1;
}
if (lbl_806D1210_p11 != 0) {
return 1;
}
card_p11 = Sci2Card_Singleton_Get_p11();
if (lbl_806D121C_p11 == 0) {
lbl_806D121C_p11 = CardCleaning_Begin_p11();
return 0;
}
if (Sci2Card_IsIdleOrExhausted_p11(card_p11) == 1) {
if (Sci2Card_IsStatusOk02_p11(card_p11) == 1) {
lbl_806D122A_p11 = 0;
lbl_806D1210_p11 = 6;
lbl_806D122B_p11 = 0;
if (--lbl_806CF0E4_p11 <= 0) {
lbl_806D1210_p11 = 104;
}
lbl_806D1237_p11 = 0;
} else if (!Sci2Card_IsStatusOkNonTerm_p11(card_p11)) {
lbl_806D122A_p11 = 0;
lbl_806D1210_p11 = 6;
lbl_806D122B_p11 = 0;
lbl_806D1237_p11 = 0;
if (--lbl_806CF0E4_p11 <= 0) {
lbl_806D1210_p11 = 104;
}
} else if (Sci2Card_IsStatus1OneTwoThree_p11(card_p11) == 1) {
lbl_806D1224_p11 = 1;
lbl_806D1237_p11 = 0;
lbl_806CF0D4_p11 = 0;
lbl_806D122A_p11 = 0;
lbl_806D1210_p11 = 1;
lbl_806D122B_p11 = 0;
} else {
lbl_806D1237_p11 = 1;
lbl_806D122A_p11 = 0;
lbl_806D1210_p11 = 6;
lbl_806D122B_p11 = 0;
}
lbl_806D1238_p11 = 0;
return 1;
}
return 0;
}
unsigned char card_send_cleaning_cmd_init(void)
{
void *card_p11;
if (lbl_806D1238_p11 == 1) {
return 1;
}
lbl_806D1238_p11 = 1;
if (!ServiceLatch_CheckTriggered_p11()) {
lbl_806D122A_p11 = 1;
lbl_806D121C_p11 = 0;
lbl_806CF0E4_p11 = 5;
lbl_806D1224_p11 = 0;
lbl_806D1214_p11 = 0;
lbl_806D1210_p11 = 1;
return 1;
}
card_p11 = Sci2Card_Singleton_Get_p11();
if (lbl_806D1237_p11 == 0) {
lbl_806D1210_p11 = 0;
lbl_806D122A_p11 = 1;
lbl_806D121C_p11 = 0;
lbl_806D121C_p11 = Sci2Card_SendCmdOptions_p11(card_p11, 0, 1);
} else {
lbl_806D1210_p11 = 0;
lbl_806D122A_p11 = 1;
lbl_806D121C_p11 = 0;
lbl_806CF0E4_p11 = 5;
Sci2Card_ForceFailState_p11(card_p11);
}
return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardEjectCommand.c (0x80098a90) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
extern unsigned char ServiceLatch_CheckTriggered_p12(void);
extern void *Sci2Card_Singleton_Get_p12(void);
extern unsigned int card_eject_p12(int *self_p12);
extern unsigned int Sci2Card_SendCmdSpace_p12(int *self_p12);
extern unsigned char Sci2Card_IsIdleOrExhausted_p12(int *self_p12);
extern unsigned char Sci2Card_IsStatusOkNonTerm_p12(int *self_p12);
extern unsigned char Sci2Card_IsStatus1OneTwoThree_p12(int *self_p12);
extern unsigned char Sci2Card_IsStatus1Zero_p12(int *self_p12);
extern unsigned char lbl_806CF0D4_p12;
extern int lbl_806CF0E4_p12;
extern int lbl_806CF0F8_p12[2];
extern int lbl_806D1210_p12;
extern int lbl_806D1214_p12;
extern unsigned char lbl_806D121C_p12;
extern unsigned char lbl_806D1224_p12;
extern unsigned char lbl_806D1227_p12;
extern unsigned char lbl_806D122A_p12;
extern unsigned char lbl_806D122B_p12;
static inline unsigned char CardEject_Begin_p12(void)
{
lbl_806D1210_p12 = 0;
lbl_806D122A_p12 = 1;
lbl_806D121C_p12 = 0;
lbl_806CF0E4_p12 = 5;
if (!ServiceLatch_CheckTriggered_p12()) {
lbl_806D1210_p12 = 1;
return 1;
}
lbl_806D1227_p12 = 0;
lbl_806D121C_p12 = card_eject_p12(Sci2Card_Singleton_Get_p12());
lbl_806CF0D4_p12 = 0;
return 1;
}
unsigned char card_eject_state_machine(void)
{
int *card_p12;
if (!ServiceLatch_CheckTriggered_p12()) {
lbl_806D1210_p12 = 1;
return 1;
}
if (lbl_806D1210_p12 != 0) {
return 1;
}
card_p12 = Sci2Card_Singleton_Get_p12();
if (lbl_806D1227_p12 == 0) {
if (lbl_806D121C_p12 == 0) {
lbl_806D121C_p12 = CardEject_Begin_p12();
} else if (Sci2Card_IsIdleOrExhausted_p12(card_p12) == 1) {
if (!Sci2Card_IsStatusOkNonTerm_p12(card_p12)) {
if (--lbl_806CF0F8_p12[0] > 0) {
lbl_806D122B_p12 = 0;
CardEject_Begin_p12();
return 0;
}
lbl_806D1210_p12 = 100;
return 1;
}
if (Sci2Card_IsStatus1OneTwoThree_p12(card_p12) == 1) {
lbl_806D121C_p12 = CardEject_Begin_p12();
} else {
lbl_806D1227_p12 = 1;
Sci2Card_SendCmdSpace_p12(card_p12);
}
}
} else if (Sci2Card_IsIdleOrExhausted_p12(card_p12) == 1) {
if (!Sci2Card_IsStatusOkNonTerm_p12(card_p12)) {
if (--lbl_806CF0F8_p12[0] > 0) {
lbl_806D122B_p12 = 0;
CardEject_Begin_p12();
return 0;
}
lbl_806D1210_p12 = 100;
return 1;
}
if (Sci2Card_IsStatus1OneTwoThree_p12(card_p12) == 1) {
lbl_806D1227_p12 = 0;
lbl_806D122B_p12 = 0;
CardEject_Begin_p12();
return 0;
}
if (Sci2Card_IsStatus1Zero_p12(card_p12) == 1) {
lbl_806D1224_p12 = 0;
lbl_806D1214_p12 = 0;
lbl_806CF0F8_p12[0] = 5;
lbl_806D122A_p12 = 0;
lbl_806D1210_p12 = 1;
lbl_806D122B_p12 = 0;
return 1;
}
Sci2Card_SendCmdSpace_p12(card_p12);
}
return 0;
}
unsigned char card_eject_init(void)
{
lbl_806D1210_p12 = 0;
lbl_806D122A_p12 = 1;
lbl_806D121C_p12 = 0;
lbl_806CF0E4_p12 = 5;
if (!ServiceLatch_CheckTriggered_p12()) {
lbl_806D1210_p12 = 1;
return 1;
}
lbl_806D1227_p12 = 0;
lbl_806D121C_p12 = card_eject_p12(Sci2Card_Singleton_Get_p12());
lbl_806CF0D4_p12 = 0;
return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/card_rw_get_substate.c (0x80098e48) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern int lbl_806CF0D0_p13;
int card_rw_get_substate(void)
{
return lbl_806CF0D0_p13;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardForceBackup.c (0x80098e50) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
#pragma inline_max_size(1000)


C_REGION_END
#pragma cplusplus on

extern "C"{
struct CardPackedWords_p14 {
unsigned int word1BA_p14, word1BE_p14, word1C2_p14, word1C6_p14, word1CA_p14, word1CE_p14;
};
struct CardPlayerSnapshot_p14 {
unsigned int word000_p14, word004_p14, word008_p14;
unsigned char byte00C_p14, byte00D_p14;
unsigned short half00E_p14, half010_p14;
unsigned int word014_p14;
unsigned char byte018_p14, byte019_p14, byte01A_p14;
unsigned int word01C_p14, word020_p14, word024_p14, word028_p14, word02C_p14;
unsigned int word030_p14, word034_p14, word038_p14, word03C_p14, word040_p14;
unsigned int word044_p14, word048_p14, word04C_p14, word050_p14, word054_p14;
unsigned int word058_p14, word05C_p14, word060_p14, word064_p14, word068_p14;
unsigned int word06C_p14, word070_p14, word074_p14, word078_p14, word07C_p14;
unsigned int word080_p14, word084_p14, word088_p14, word08C_p14, word090_p14;
unsigned int word094_p14, word098_p14, word09C_p14, word0A0_p14, word0A4_p14;
unsigned char bytes0A8_p14[0x79];
unsigned char bytes121_p14[0x69];
unsigned int unlockIdx_p14;
unsigned int word190_p14, word194_p14;
unsigned char byte198_p14, byte199_p14, byte19A_p14, byte19B_p14, byte19C_p14;
unsigned char byte19D_p14, byte19E_p14, byte19F_p14, byte1A0_p14;
unsigned int word1A4_p14;
unsigned char byte1A8_p14;
unsigned int word1AC_p14;
unsigned char byte1B0_p14, byte1B1_p14;
unsigned int word1B4_p14;
unsigned char byte1B8_p14, byte1B9_p14;
struct CardPackedWords_p14 words1BA_p14;
unsigned int word1D4_p14;
unsigned char byte1D8_p14, byte1D9_p14, byte1DA_p14;
};
struct CardBackupSnapshot_p14 {
unsigned char prefix000_p14[0x64];
unsigned char captured_p14;
unsigned char prefix065_p14[0x90 - 0x65];
struct CardPlayerSnapshot_p14 player_p14;
};
typedef char CheckSnapshotSize_p14[sizeof(struct CardPlayerSnapshot_p14) == 0x1DC ? 1 : -1];
typedef char CheckPackedSize_p14[sizeof(struct CardPackedWords_p14) == 0x18 ? 1 : -1];
extern struct CardPlayerSnapshot_p14 g_playerData_p14;
extern struct CardBackupSnapshot_p14 lbl_80598A60_p14;
extern void card_backup_p14(void);
void card_force_backup_now_p14(void)
{
struct CardPlayerSnapshot_p14 *d_p14 = &lbl_80598A60_p14.player_p14;
*d_p14 = g_playerData_p14;
lbl_80598A60_p14.captured_p14 = 1;
card_backup_p14();
}
}

#pragma cplusplus reset
C_REGION_BEGIN
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_FlagReceiptTestEnable.c (0x800991d8) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern int lbl_806D1214_p15;
extern unsigned char lbl_806D1224_p15;
extern unsigned char lbl_806D1226_p15;
void Sci2Card_FlagReceiptTestEnable(void) {
lbl_806D1226_p15 = 1;
}
unsigned char Sci2Card_GetReceiptTestFlag(void) {
return lbl_806D1226_p15;
}
int Sci2Card_GetUnpackStatusCode(void) {
return lbl_806D1214_p15;
}
unsigned char Sci2Card_GetByteFlag1224(void) {
return lbl_806D1224_p15;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_PollResponseStatusTri.c (0x800991fc) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern unsigned char ServiceLatch_CheckTriggered_p16(void);
extern void *Sci2Card_Singleton_Get_p16(void);
extern unsigned char Sci2Card_IsIdleOrExhausted_p16(void *card_p16);
extern unsigned char Sci2Card_GetResponseStatus_p16(void *card_p16, unsigned char *status1_p16,
unsigned char *status2_p16, unsigned char *status3_p16);

#pragma exceptions on

int Sci2Card_PollResponseStatusTri(void)
{
void *card_p16;
unsigned char status1_p16;
unsigned char status2_p16;
unsigned char status3_p16;
if (!ServiceLatch_CheckTriggered_p16()) {
return 0;
}
card_p16 = Sci2Card_Singleton_Get_p16();
if (Sci2Card_IsIdleOrExhausted_p16(card_p16) == 1) {
return 0;
}
return -(unsigned char)(Sci2Card_GetResponseStatus_p16(card_p16, &status1_p16, &status2_p16, &status3_p16) == 0) + 2;
}

#pragma exceptions reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_GetPrintErrorCode.c (0x8009927c) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern int lbl_806D1210_p17;
int Sci2Card_GetPrintErrorCode(void)
{
return lbl_806D1210_p17;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_ResetRetryAndStatus.c (0x80099284) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
extern unsigned char ServiceLatch_CheckTriggered_p18(void);
extern void *Sci2Card_Singleton_Get_p18(void);
extern void Sci2Card_ResetRetryCount_p18(void *card_p18);
extern int lbl_806D1210_p18;
extern int lbl_806D1214_p18;

#pragma exceptions on

void Sci2Card_ResetRetryAndStatus(void)
{
if (ServiceLatch_CheckTriggered_p18()) {
Sci2Card_ResetRetryCount_p18(Sci2Card_Singleton_Get_p18());
lbl_806D1210_p18 = 0;
lbl_806D1214_p18 = 0;
}
}

#pragma exceptions reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_BuildItemGetReceiptLine.c (0x800992c0) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
typedef struct ReceiptPlayer_p19 {
unsigned char pad0_p19[0xD];
unsigned char item_p19;
unsigned char padE_p19[0x198 - 0xE];
signed char cardVersion_p19;
} ReceiptPlayer_p19;
extern ReceiptPlayer_p19 g_playerData_p19;
extern const char *lbl_803FFDF0_p19[10];


extern char lbl_805AC5A4_p19[64];
extern const char lbl_806D35D4_p19[3];
extern const char lbl_806D35E4_p19[4];
extern int fn_801D5E80_p19(ReceiptPlayer_p19 *);
extern int fn_801D5DE8_p19(ReceiptPlayer_p19 *);
extern unsigned char fn_801D5F40_p19(ReceiptPlayer_p19 *);
extern int ItemAlias_DestToSource_p19(int, unsigned char *);
extern int isJapanese_p19(void);
extern void *memset_p19(void *, int, unsigned long);
extern int sprintf_p19(char *, const char *, ...);
extern const char lbl_806D3594_p19[];
extern const char lbl_806D3598_p19[];
extern const char lbl_806D359C_p19[];
extern const char lbl_806D35A0_p19[];
extern const char lbl_806D35A4_p19[];
extern const char lbl_806D35A8_p19[];
extern const char lbl_806D35AC_p19[];
extern const char lbl_806D35B0_p19[];
extern const char lbl_806D35B4_p19[];
extern const char lbl_806D35B8_p19[];
















static inline int Receipt_ItemClass_p19(int item_p19)
{
signed char alias_p19;
int source_p19 = ItemAlias_DestToSource_p19(item_p19, (unsigned char *)&alias_p19);
int i_p19;
for (i_p19 = 0; i_p19 < 67; i_p19++) {
if (source_p19 == (*(const int (*)[67])&Sci2Card_BuildItemGetReceiptLine_rodata_80317E00)[i_p19]) return (signed char)alias_p19;
}
if (alias_p19 == 1) return 2;
return -1;
}
static inline unsigned char Receipt_IsSpecialItem_p19(int item_p19)
{
int i_p19;
for (i_p19 = 0; i_p19 < 12; i_p19++) {
if (item_p19 == (*(const int (*)[12])&Sci2Card_BuildItemGetReceiptLine_rodata_80317F0C)[i_p19]) return 1;
}
return 0;
}
char *Sci2Card_BuildItemGetReceiptLine(void)
{
int count_p19;
unsigned char extra_p19;
unsigned char ordinary_p19;
unsigned char special_p19;
int remaining_p19;
ReceiptPlayer_p19 *player_p19;
const char *hundreds_p19;
const char *tens_p19;
const char *ones_p19;
player_p19 = &g_playerData_p19;
count_p19 = fn_801D5E80_p19(player_p19);
if (count_p19 >= fn_801D5DE8_p19(&g_playerData_p19)) {
if (isJapanese_p19() == 0) return (char *)receiptEnglish_p19[6];
else return (char *)receiptJapanese_p19[6];
}
extra_p19 = fn_801D5F40_p19(player_p19);
ordinary_p19 = 0;
special_p19 = 0;
remaining_p19 = fn_801D5DE8_p19(player_p19) - count_p19;
if (player_p19->item_p19 != 0x7F) {
int itemClass_p19 = Receipt_ItemClass_p19(g_playerData_p19.item_p19);
if (itemClass_p19 >= 0 && itemClass_p19 <= 1) ordinary_p19 = 1;
if (Receipt_IsSpecialItem_p19(player_p19->item_p19) == 1) special_p19 = 1;
}
memset_p19(lbl_805AC5A4_p19, 0, 64);
if (count_p19 / 100 == 0) hundreds_p19 = lbl_806D35E4_p19;
else hundreds_p19 = lbl_803FFDF0_p19[count_p19 / 100];
if (count_p19 < 10) tens_p19 = lbl_806D35D4_p19;
else tens_p19 = lbl_803FFDF0_p19[(count_p19 / 10) % 10];
if (count_p19 <= 0) ones_p19 = lbl_806D35D4_p19;
else ones_p19 = lbl_803FFDF0_p19[count_p19 % 10];
if (g_playerData_p19.cardVersion_p19 >= 49 && extra_p19 == 1) {
if (isJapanese_p19() == 0) {
sprintf_p19(lbl_805AC5A4_p19, receiptEnglish_p19[2], hundreds_p19, tens_p19, ones_p19);
} else {
sprintf_p19(lbl_805AC5A4_p19, receiptJapanese_p19[2], hundreds_p19, tens_p19, ones_p19);
}
}
else if (g_playerData_p19.cardVersion_p19 >= 49 && count_p19 == 14) {
if (isJapanese_p19() == 0) {
sprintf_p19(lbl_805AC5A4_p19, receiptEnglish_p19[1], hundreds_p19, tens_p19, ones_p19);
} else {
sprintf_p19(lbl_805AC5A4_p19, receiptJapanese_p19[1], hundreds_p19, tens_p19, ones_p19);
}
}
else if (ordinary_p19 == 1) {
if (isJapanese_p19() == 0) {
sprintf_p19(lbl_805AC5A4_p19, receiptEnglish_p19[4], hundreds_p19, tens_p19, ones_p19);
} else {
sprintf_p19(lbl_805AC5A4_p19, receiptJapanese_p19[4], hundreds_p19, tens_p19, ones_p19);
}
}
else if (special_p19 == 1) {
if (isJapanese_p19() == 0) {
sprintf_p19(lbl_805AC5A4_p19, receiptEnglish_p19[7], hundreds_p19, tens_p19, ones_p19);
} else {
sprintf_p19(lbl_805AC5A4_p19, receiptJapanese_p19[7], hundreds_p19, tens_p19, ones_p19);
}
}
else if (remaining_p19 <= 5) {
if (isJapanese_p19() == 0) {
sprintf_p19(lbl_805AC5A4_p19, receiptEnglish_p19[5], hundreds_p19, tens_p19, ones_p19, lbl_803FFDF0_p19[remaining_p19]);
} else {
sprintf_p19(lbl_805AC5A4_p19, receiptJapanese_p19[5], hundreds_p19, tens_p19, ones_p19, lbl_803FFDF0_p19[remaining_p19]);
}
}
else {
if (isJapanese_p19() == 0) {
sprintf_p19(lbl_805AC5A4_p19, receiptEnglish_p19[0], hundreds_p19, tens_p19, ones_p19);
} else {
sprintf_p19(lbl_805AC5A4_p19, receiptJapanese_p19[0], hundreds_p19, tens_p19, ones_p19);
}
}
return lbl_805AC5A4_p19;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_PopulateRankRowByMode.c (0x800997e4) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
extern unsigned char fn_801D5B8C_p20(void *data_p20, int key_p20, int rank_p20, int kind_p20);
extern int g_gameMode_p20;
extern unsigned char g_playerData_p20[];
extern unsigned char lbl_805D275C_p20[];
void Sci2Card_PopulateRankRowByMode(int *key_p20, unsigned char *ranks_p20, unsigned char *mode_p20)
{
unsigned char *alt_p20 = lbl_805D275C_p20;
unsigned char *data_p20 = g_playerData_p20;
int i_p20;
for (i_p20 = 0; i_p20 < 8; i_p20++) {
ranks_p20[i_p20] = 0;
}
if (g_gameMode_p20 != 0) {
int k_p20 = *(int *)(alt_p20 + 0x1D4);
unsigned char m_p20 = alt_p20[0x1D8];
int r_p20;
*key_p20 = k_p20;
for (r_p20 = 1; r_p20 <= 8; r_p20++) {
if (fn_801D5B8C_p20(alt_p20, k_p20, r_p20, m_p20 == 0 ? 3 : 7) == 1) {
ranks_p20[r_p20 - 1] = 1;
}
}
*mode_p20 = m_p20;
} else {
int k_p20 = *(int *)(data_p20 + 0x1D4);
unsigned char m_p20 = data_p20[0x1D8];
int r_p20;
*key_p20 = k_p20;
for (r_p20 = 1; r_p20 <= 8; r_p20++) {
if (fn_801D5B8C_p20(data_p20, k_p20, r_p20, m_p20 == 0 ? 3 : 7) == 1) {
ranks_p20[r_p20 - 1] = 1;
}
}
*mode_p20 = m_p20;
}
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_RegisterReceiptBuffersCleanup.c (0x8009990c) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
extern void __register_global_object(void *object_p21, void *dtor_p21, void *block_p21);
extern void dtor_8002F978_p21(void *self_p21, int flag_p21);
extern int lbl_806D122C_p21;
extern int lbl_806D1244_p21;
extern unsigned char lbl_805AC550_p21[];
extern unsigned char lbl_805AC5E4_p21[];
void Sci2Card_RegisterReceiptBuffersCleanup(void)
{
__register_global_object(&lbl_806D122C_p21, dtor_8002F978_p21, lbl_805AC550_p21);
__register_global_object(&lbl_806D1244_p21, dtor_8002F978_p21, lbl_805AC5E4_p21);
}
__declspec(section ".ctors") static void (*const s_Sci2Card_RegisterReceiptBuffersCleanup_ctor_p21)(void) = Sci2Card_RegisterReceiptBuffersCleanup;
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_ReceiptTables.c (0x80099958) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
#pragma force_active on

unsigned int lbl_803FFEA8_p22[18] = { 0x00F00001, 0xF00003F0, 0x0003F1FF, 0x03F1FF03, 0xF9F301FF, 0xE303FDE3, 0x03FDC903, 0xFDC903FD, 0x9C01FD9C, 0x007D3E00, 0x7F3E007F, 0xFF003FFF, 0x001EFF00, 0x003F0000, 0x02000002, 0x00001F00, 0x00730000, 0xCF0000FF };
unsigned int lbl_803FFEF0_p22[18] = { 0x000F0000, 0x0F80000F, 0xC0FF8FC0, 0xFF8FC0CF, 0x9FC0C7FF, 0x80C7BFC0, 0x93BFC093, 0xBFC039BF, 0xC039BF80, 0x7CBE007C, 0xFE00FFFE, 0x00FF7C00, 0xFE7800FC, 0x0000E000, 0x00E00000, 0xFC000077, 0x00007B80, 0x00FF8000 };
unsigned int lbl_803FFF38_p22[18] = { 0x00000000, 0x808000C1, 0xC100E377, 0x38F61C7E, 0xFE083FFE, 0x0731FE0F, 0x30FE1F30, 0xFC3F10F8, 0x3F18403F, 0x08603F04, 0x203F0230, 0x1F016C0F, 0x00E60700, 0x63C006E0, 0x7F07C002, 0x03803F00, 0x00EF0001, 0x9F0007FF };
unsigned int lbl_803FFF80_p22[18] = { 0x00000080, 0x8100C1C3, 0x00776300, 0x1C371C08, 0x7F7EE07F, 0xFCF07F8C, 0xF87F0CFC, 0x3F0CFC1F, 0x08FC0218, 0xFC0610FC, 0x0420F80C, 0x40F03680, 0xE0670003, 0xC600FE07, 0x60E003E0, 0xFE01C077, 0x80007BC0, 0x00FFF000 };
unsigned int lbl_803FFFC8_p22[18] = { 0x00000001, 0xF0FF01FC, 0xAA00DEFF, 0x00C7FF00, 0xC3F80061, 0xF80060F9, 0x0030F900, 0x1879008C, 0x79008639, 0x00833900, 0x83F900C1, 0xF900603F, 0x00301F00, 0x3FDF001F, 0xCF000FEF, 0x00000700, 0x00030000, 0x360000EE };
unsigned int lbl_80400010_p22[18] = { 0x000000FF, 0x87C0AA9F, 0xC0FFBD80, 0xFFF1800F, 0xE1800FC3, 0x00FF8300, 0xFF8600FF, 0x0C00FF18, 0x00FE3080, 0xFE6080FF, 0xE080FFC1, 0x80FC0300, 0xF80600FB, 0xFE00F3FC, 0x00F7F800, 0xE0000040, 0x0000FC00, 0x00FF0000 };
unsigned int lbl_80400058_p22[18] = { 0x00000000, 0xE0FF00F9, 0x80006500, 0x0023FF00, 0x29C30015, 0xC10015EC, 0x0015EC00, 0x142C0014, 0x2C0025EC, 0x0045C101, 0x99C30223, 0xFF04C680, 0x050CC004, 0x307F03C0, 0x01000001, 0x0000FF00, 0x00E00001, 0xE00001FF };
unsigned int lbl_804000A0_p22[18] = { 0x000000FF, 0x838000CF, 0x80005300, 0xFFE2009C, 0xCA0099D4, 0x00D3D400, 0xC7D400C6, 0x1400C614, 0x00D3D200, 0x99D1009C, 0xCCC0FFE2, 0x2000B190, 0x019850FF, 0x06106001, 0xE0600000, 0xFFC00001, 0xC00001E0, 0x00FFE000 };
unsigned int lbl_804000E8_p22[18] = { 0x00000001, 0xE3FF01F3, 0xFF01DBFF, 0x00CFFF00, 0xC73E00C3, 0x3E00639C, 0x00639C00, 0x33C9001B, 0xC90007E3, 0x0003E300, 0x01F30844, 0xFF0EEE7F, 0x07FF1F03, 0xBB820111, 0x0200001F, 0x00007B00, 0x00E60003, 0xCE0003FF };
unsigned int lbl_80400130_p22[18] = { 0x000000FF, 0xC780FFCF, 0x80FFDB80, 0xFFF3807C, 0xE3007CC3, 0x0039C600, 0x39C60093, 0xCC0093D8, 0x00C7E000, 0xC7C000CF, 0x8000FF22, 0x10FE7770, 0xFCFFE0C1, 0xDDC0C088, 0x80F80000, 0x7E000077, 0x00007BC0, 0x00FFC000 };
unsigned int lbl_80400178_p22[18] = { 0x00000007, 0x9FFF0FDF, 0xF81FFFF0, 0x3FFFC03F, 0xDF803F1F, 0x803E1FF0, 0x3F1FFC3F, 0xD27F1FF2, 0x7F0FDFFC, 0x079FF000, 0x1F80001F, 0xC0001FE0, 0x0007F800, 0x00FF0000, 0x02000007, 0x0003FF00, 0x03800007, 0x800007FF };
unsigned int lbl_804001C0_p22[18] = { 0x000000FF, 0xFCF03FFD, 0xF80FFFFC, 0x07FFFE03, 0xFDFE03FC, 0x7E01FC3E, 0x01FC7E81, 0x25FE8127, 0xFC01FDF8, 0x01FCF003, 0xFC0007FC, 0x000FFC00, 0x3FE000FF, 0x0000C000, 0x00E00000, 0xFFC00001, 0xC00001E0, 0x00FFE000 };
unsigned int lbl_80400208_p22[18] = { 0x00000000, 0xFFFF0180, 0x00033800, 0x027FC303, 0x000001FF, 0xFF01FE7F, 0x00FCBF00, 0xF8DF007C, 0x3F005E7E, 0x00CFFC00, 0x9FF801BF, 0xFC017DFE, 0x03F87F03, 0xE00F0780, 0x0606001F, 0x0000F300, 0x01CF0003, 0x9F0003FF };
unsigned int lbl_80400250_p22[18] = { 0x000000FF, 0xFF000001, 0x80000040, 0xF01E4000, 0x00C0FFFF, 0x80FE7F80, 0xFCBF00F8, 0xDF00FC3E, 0x007E7B00, 0xBFF300DF, 0xF9803FFD, 0x807FBE80, 0xFE1FC0F0, 0x07C06001, 0xE0F80060, 0x7F00007B, 0x80007DC0, 0x00FFC000 };
unsigned int lbl_80400298_p22[18] = { 0x00006100, 0x007301FC, 0x6E008275, 0x084D4008, 0x52D83651, 0x500850C1, 0x08504208, 0x50520068, 0x43001453, 0x000A4300, 0x05410002, 0xD0001A58, 0x0016A000, 0x1111010E, 0x0C010002, 0x06C00201, 0x007F0100, 0x600100FF };
unsigned int lbl_804002E0_p22[18] = { 0xC30000E7, 0x0000BB1F, 0xC0572080, 0x8159000D, 0xA5008545, 0x00C18500, 0x610500E5, 0x0510E10B, 0x10E5146C, 0xE12810C1, 0x501085A0, 0x100D2C00, 0x83B400C4, 0x44009838, 0x00200000, 0x200000FF, 0x00000300, 0x00FF8000 };
unsigned int lbl_80400328_p22[18] = { 0x0F0FFF1E, 0x0FFF1C0F, 0xFF3C0E00, 0x3C0E003C, 0x060C3E00, 0x1C3C021C, 0x3C02363C, 0x02363C02, 0x633E0263, 0x3F82C13F, 0x80C13F80, 0x003FC000, 0x3FE1003F, 0xFFC03FFF, 0xFD3FFFFD, 0x1FFFE01F, 0xFF8C07FF, 0x3003FF00 };
unsigned int lbl_80400370_p22[18] = { 0xFFF0E0FF, 0xF078FFF0, 0x3C00703E, 0x00703E30, 0x603E3800, 0x7E38403E, 0x6C403E6C, 0x403EC640, 0x3EC6407E, 0x8341FE83, 0x01FE0001, 0xFE0083FE, 0x0187FE03, 0xFFFE1FFF, 0xFE1FFFFE, 0x03FFFE88, 0xFFFC847F, 0xFC007FF0 };
unsigned int lbl_804003B8_p22[18] = { 0x0FFFFF1F, 0x7F7F1F3E, 0x3E3F1C88, 0x0709E301, 0x01F70001, 0xF80E01F0, 0x0F01E00F, 0x03C02F07, 0xC027BFC0, 0x379FC03B, 0xDFC03DCF, 0xE03E93F0, 0x3F19F83F, 0x9C3F391F, 0x80383FFD, 0x3C7FC01F, 0xFF1007FE, 0x6003F800 };
unsigned int lbl_80400400_p22[18] = { 0xFFFFE07F, 0x7EF83E3C, 0xFC889CFE, 0xE3C8E2F7, 0x80801F80, 0x020F8072, 0x0780F203, 0xC0F203E0, 0xF603FDE6, 0x03F9EE03, 0xFBDE07F3, 0xBE0FC97E, 0x1F98FEFC, 0x39FE01F8, 0x9E1FFC1E, 0x01FE3E88, 0x7FFC843F, 0xFC000FF0 };
unsigned int lbl_80400448_p22[18] = { 0xFFFFFFFE, 0x0F00FE03, 0x55FF2100, 0xFF3800FF, 0x3C07FF9E, 0x07FF9F06, 0xFFCF06FF, 0xE786FF73, 0x86FF79C6, 0xFF7CC6FF, 0x7C06FF3E, 0x06FF9FC0, 0xFFCFE0FF, 0xC020FFE0, 0x30FFF010, 0xFFFFF8FF, 0xFFFCFFFF, 0xC9FFFF11 };
unsigned int lbl_80400490_p22[18] = { 0xFFFFFF00, 0x783F5560, 0x3F00427F, 0x000E7FF0, 0x1E7FF03C, 0xFF007CFF, 0x0079FF00, 0xF3FF00E7, 0xFF01CF7F, 0x019F7F00, 0x1F7F003E, 0x7F03FCFF, 0x07F9FF04, 0x01FF0C03, 0xFF0807FF, 0x1FFFFFBF, 0xFFFF03FF, 0xFF00FFFF };
unsigned int lbl_804004D8_p22[18] = { 0x07FFFF1F, 0x1F001F06, 0x7F3F9AFF, 0x3FDC003F, 0xD63C3FEA, 0x3E3FEA13, 0x3FEA133F, 0xEBD33FEB, 0xD33FDA13, 0x3FBA3E3E, 0x663C3DDC, 0x003B397F, 0x3AF33F3B, 0xCF803C3F, 0xFE3FFFFE, 0x1FFF001F, 0xFF1F07FE, 0x1F03FE00 };
unsigned int lbl_80400520_p22[18] = { 0xFFFFE000, 0x7C78FF30, 0x7CFFACFE, 0x001DFE63, 0x35FE662B, 0xFE2C2BFE, 0x382BFE39, 0xEBFE39EB, 0xFE2C2DFE, 0x662EFE63, 0x333E001D, 0xDEFF4E6E, 0xFE67AE00, 0xF9EE1FFE, 0x1E1FFFFE, 0x003FFEFE, 0x3FFCFE1F, 0xFC001FF0 };
unsigned int lbl_80400568_p22[18] = { 0x07FFFF1E, 0x1C001E0C, 0x003E2400, 0x3F30003F, 0x38C13F3C, 0xC13F9C63, 0x3F9C633F, 0xCC363FE4, 0x363FF81C, 0x3FFC1C3F, 0xFE0C37BB, 0x00311180, 0x3800E03C, 0x447D3EEE, 0xFD3FFFE0, 0x1FFF841F, 0xFF1907FC, 0x3103FC00 };
unsigned int lbl_804005B0_p22[18] = { 0xFFFFE000, 0x38780030, 0x7C00247E, 0x000C7E83, 0x1CFE833C, 0xFEC639FE, 0xC639FE6C, 0x33FE6C27, 0xFE381FFE, 0x383FFE30, 0x7FFE00DD, 0xEE01888E, 0x03001E3E, 0x223E3F77, 0x7E07FFFE, 0x81FFFE88, 0xFFFC843F, 0xFC003FF0 };
unsigned int lbl_804005F8_p22[18] = { 0x1FFFFF38, 0x60003020, 0x0760000F, 0x40003F40, 0x207F00E0, 0x7F01E00F, 0x00E00300, 0x2D80200D, 0x80302003, 0x38600F3F, 0xE07F3FE0, 0x3F3FE01F, 0x3FF8073F, 0xFF003FFF, 0xFD3FFFF8, 0x1FFC001F, 0xFC7F07F8, 0x7F07F800 };
unsigned int lbl_80400640_p22[18] = { 0xFFFFE000, 0x0308C002, 0x04F00002, 0xF80000FC, 0x0200FC03, 0x80FE03C0, 0xFE03807E, 0xDA007ED8, 0x02FE0206, 0xFE030EFC, 0x03FEF803, 0xFEF003FE, 0xC01FFE00, 0xFFFE3FFF, 0xFE1FFFFE, 0x003FFEFE, 0x3FFCFE1F, 0xFC001FF0 };
unsigned int lbl_80400688_p22[18] = { 0x07FFFF1F, 0x00001E7F, 0xFF3CC7FF, 0x3D803C3C, 0xFFFF3E00, 0x003E0180, 0x3F03403F, 0x07203F83, 0xC03FA181, 0x3F30033F, 0x60073E40, 0x033E8201, 0x3C07803C, 0x1FF0387F, 0xF939FFE0, 0x1FFF0C1F, 0xFE3007FC, 0x6003FC00 };
unsigned int lbl_804006D0_p22[18] = { 0xFFFFE000, 0x00F8FFFE, 0x7CFFFFBE, 0x0FE1BEFF, 0xFF3E0000, 0x7E01807E, 0x0340FE07, 0x20FE03C1, 0xFE8184FE, 0x400CFE20, 0x067EC002, 0x7E80417E, 0x01E03E0F, 0xF83E9FFE, 0x1E07FF9E, 0x80FFFE84, 0x7FFC823F, 0xFC003FF0 };
unsigned int lbl_80400718_p22[18] = { 0x07FF9E1F, 0xFF8C1E03, 0x913F7D8A, 0x37B2BF37, 0xAD2709AE, 0xAF37AF3E, 0x37AFBD37, 0xAFAD3F97, 0xBC3FEBAC, 0x3FF5BC3F, 0xFABE3FFD, 0x2F3FE5A7, 0x3FE95F3F, 0xEEEE3EF1, 0xF33EFFFD, 0x193FFD1E, 0xFF8006FF, 0x9F02FF00 };
unsigned int lbl_80400760_p22[18] = { 0x3CFFE018, 0xFFF844E0, 0x3CA8DF7E, 0x7EA6FEF2, 0x5AFE7ABA, 0xFE3E7AFE, 0x9EFAFE1A, 0xFAEE1EF4, 0xEE1AEB92, 0x1ED7EE3E, 0xAFEE7A5F, 0xEEF2D3FE, 0x7C4BFE3B, 0xBBFE67C7, 0xFEDFFFFE, 0xDFFFFE00, 0xFFFCFCFF, 0xFC007FF0 };
unsigned int lbl_804007A8_p22[18] = { 0xFFE00080, 0x207FBFA0, 0x40A0205F, 0xAFE05FA8, 0x005FA800, 0x5EA8005E, 0xA8005E88, 0x005EF800, 0x5E00005F, 0x00005F00, 0x005F0000, 0x4000007F, 0x00000000, 0x007F0000, 0x4000005F, 0x00005F00, 0x005F0000, 0x4000007F };
unsigned int lbl_804007F0_p22[18] = { 0x000000FF, 0xC7FF004C, 0x00FF59FF, 0xFF53FFFF, 0x57FF0057, 0x01FFD77D, 0x801745FF, 0x17450197, 0x45FCD745, 0xFE5745FF, 0x57450F57, 0x45EF5745, 0x2F5745EF, 0x577D0F57, 0x01FF57FF, 0xFE53FFFC, 0xD9FF018C, 0x00FF07FF };
unsigned int lbl_80400838_p22[18] = { 0x000000C0, 0x00006000, 0x00300000, 0x900000D1, 0xFF07D301, 0x8CD67CD9, 0xD4FE53D5, 0xFF57D5C7, 0x57D5D757, 0xD5D057D5, 0xDFD7D5D0, 0x17D5DFD7, 0xD5D057D5, 0xD757D5C7, 0x57D5FF57, 0x94FE5336, 0x7CD96301, 0x8CC1FF07 };
unsigned int lbl_80400880_p22[18] = { 0x0007FF00, 0x04010005, 0xFD000405, 0x0007F5FC, 0x00150600, 0x15F30015, 0xF90015FD, 0x00111D00, 0x1F5D0000, 0x4100007F, 0x00004000, 0x007F0000, 0x4100005D, 0x00001D00, 0x00FD0000, 0xF90000F3, 0x00000600, 0x00FC0000 };
unsigned int lbl_804008C8_p22[18] = { 0x00000000, 0x007F0000, 0xC000019F, 0x00013F00, 0x017F0001, 0x71000175, 0x00017400, 0x01770001, 0x74F80177, 0x880174A8, 0x0175A801, 0x71A8017F, 0xA8013FAF, 0xE19FA020, 0xC0BFA07F, 0x802000FF, 0xE0000000, 0x00000000 };
unsigned int lbl_80400910_p22[18] = { 0x000000C7, 0xF01F6410, 0x3035D067, 0x95D04FD5, 0xD05FD5D0, 0x5CD5D05D, 0x15D05DF5, 0xD05D05D0, 0x5CF5D05F, 0x15D05FD5, 0xDF5FD5C1, 0x5CD5FD5D, 0x95FD5D35, 0xFD5D6401, 0x41C7FF7F, 0x00000000, 0x00000000, 0x00000000 };
unsigned int lbl_80400958_p22[18] = { 0x000000F0, 0x7FF118C0, 0x13CD9FD6, 0xE53FD4F5, 0x7FD57570, 0x157577F5, 0x75706575, 0x7F35753F, 0x94F59FD6, 0xF4C1D3F5, 0xFDD77501, 0xD4757FD5, 0x757F9575, 0x7F350500, 0x64FDFFC7, 0x00000000, 0x00000000, 0x00000000 };
unsigned int lbl_804009A0_p22[18] = { 0x000000FF, 0xC0000040, 0x007F4000, 0xFF4000FF, 0x4000C040, 0x00DFC000, 0xC18000FC, 0xC000FE40, 0x007F401F, 0x074011F7, 0x40150740, 0x15FF4015, 0xFE4015FC, 0xC7F50184, 0x05FF05FD, 0x00040100, 0x07FF0000, 0x00000000 };
unsigned int lbl_804009E8_p22[18] = { 0xFFE00080, 0x21FCBFA3, 0x04A02675, 0xAFE4F5A8, 0x05F5A805, 0xF5A805F5, 0xA8047588, 0x0775F801, 0x75000175, 0x00017500, 0x01750001, 0x75000175, 0x00017500, 0x01750001, 0x75000175, 0x00017500, 0x01750001, 0x040001FC };
unsigned int lbl_80400A30_p22[18] = { 0x0000007F, 0xF83FC00C, 0x609FE6CF, 0x3FF29F7F, 0xFABF703A, 0xB877BABB, 0x74BABA74, 0xBABA74BA, 0xBA74BABA, 0x74BABA74, 0xBABA74BA, 0xBA74BABA, 0x74BABA77, 0xBABB703A, 0xB87FFABF, 0x3FF29F9F, 0xE6CFC00C, 0x607FF83F };
unsigned int lbl_80400A78_p22[18] = { 0x000000FC, 0x00000600, 0x00F30000, 0xF90000FD, 0x1FF01D30, 0x18DD67CD, 0x5D4FE55D, 0x5FF55D5C, 0x755D5D75, 0x5D5D055D, 0x5DFD5D5D, 0x015D5DFD, 0x5D5D05DD, 0x5D751D5C, 0x75FD5FF5, 0xF94FE5F3, 0x67CD0630, 0x18FC1FF0 };
unsigned int lbl_80400AC0_p22[18] = { 0x0007FF00, 0x04010005, 0xFD000405, 0x0007F57F, 0xC015C060, 0x159F3015, 0x3F90157F, 0xD01171D0, 0x1F75D000, 0x74100077, 0xF0007400, 0x0077F000, 0x74100075, 0xD00071D0, 0x007FD000, 0x3F90009F, 0x3000C060, 0x007FC000 };
unsigned int lbl_80400B08_p22[18] = { 0x00000000, 0x007F0000, 0xC000019F, 0x00013F00, 0x017F0001, 0x71000175, 0x00017400, 0x01770001, 0x74F80177, 0x880174A8, 0x0175A801, 0x71A8017F, 0xA8013FAF, 0xE19FA020, 0xC0BFA07F, 0x802000FF, 0xE0000000, 0x00000000 };
unsigned int lbl_80400B50_p22[18] = { 0x000000C7, 0xF01F6410, 0x3035D067, 0x95D04FD5, 0xD05FD5D0, 0x5CD5D05D, 0x15D05DF5, 0xD05D05D0, 0x5CF5D05F, 0x15D05FD5, 0xDF5FD5C1, 0x5CD5FD5D, 0x95FD5D35, 0xFD5D6401, 0x41C7FF7F, 0x00000000, 0x00000000, 0x00000000 };
unsigned int lbl_80400B98_p22[18] = { 0x000000F0, 0x7FF118C0, 0x13CD9FD6, 0xE53FD4F5, 0x7FD57570, 0x157577F5, 0x75706575, 0x7F35753F, 0x94F59FD6, 0xF4C1D3F5, 0xFDD77501, 0xD4757FD5, 0x757F9575, 0x7F350500, 0x64FDFFC7, 0x00000000, 0x00000000, 0x00000000 };
unsigned int lbl_80400BE0_p22[18] = { 0x000000FF, 0xC0000040, 0x007F4000, 0xFF4000FF, 0x4000C040, 0x00DFC000, 0xC18000FC, 0xC000FE40, 0x007F401F, 0x074011F7, 0x40150740, 0x15FF4015, 0xFE4015FC, 0xC7F50184, 0x05FF05FD, 0x00040100, 0x07FF0000, 0x00000000 };
unsigned int lbl_80400C28_p22[18] = { 0xFFE00080, 0x21FDBFA3, 0x05A02675, 0xAFE4F5A8, 0x05F5A805, 0xF5A805F5, 0xA8047588, 0x0775F801, 0x75000175, 0x00017500, 0x01750001, 0x75000175, 0x00017400, 0x01750001, 0x75000175, 0x00017500, 0x01750001, 0x050001FD };
unsigned int lbl_80400C70_p22[18] = { 0x000000FF, 0xFE3F0002, 0x607FFACF, 0x7FFA9F7F, 0xFABF7802, 0xB87BFEBB, 0x7A00BA7B, 0xF8BA780C, 0xBA7FE6BA, 0x7FF2BA7F, 0xFABA007A, 0xBAFF7ABA, 0x017ABAFF, 0x7ABB007A, 0xB87FFABF, 0x7FF29F7F, 0xE6CF000C, 0x60FFF83F };
unsigned int lbl_80400CB8_p22[18] = { 0x000000FC, 0x00000600, 0x00F30000, 0xF90000FD, 0x1FF01D30, 0x18DD67CD, 0x5D4FE55D, 0x5FF55D5C, 0x755D5D75, 0x5D5D055D, 0x5DFD5D5D, 0x015D5DFD, 0x5D5D05DD, 0x5D751D5C, 0x75FD5FF5, 0xF94FE5F3, 0x67CD0630, 0x18FC1FF0 };
unsigned int lbl_80400D00_p22[18] = { 0x0007FF00, 0x04010005, 0xFD000405, 0x0007F57F, 0xC015C060, 0x159F3015, 0x3F90157F, 0xD01171D0, 0x1F75D000, 0x74100077, 0xF0007400, 0x0077F000, 0x74100075, 0xD00071D0, 0x007FD000, 0x3F90009F, 0x3000C060, 0x007FC000 };
unsigned int lbl_80400D48_p22[18] = { 0x00000000, 0x007F0000, 0xC000019F, 0x00013F00, 0x017F0001, 0x71000175, 0x00017400, 0x01770001, 0x74F80177, 0x880174A8, 0x0175A801, 0x71A8017F, 0xA8013FAF, 0xE19FA020, 0xC0BFA07F, 0x802000FF, 0xE0000000, 0x00000000 };
unsigned int lbl_80400D90_p22[18] = { 0x000000C7, 0xF01F6410, 0x3035D067, 0x95D04FD5, 0xD05FD5D0, 0x5CD5D05D, 0x15D05DF5, 0xD05D05D0, 0x5CF5D05F, 0x15D05FD5, 0xDF5FD5C1, 0x5CD5FD5D, 0x95FD5D35, 0xFD5D6401, 0x41C7FF7F, 0x00000000, 0x00000000, 0x00000000 };
unsigned int lbl_80400DD8_p22[18] = { 0x000000F0, 0x7FF118C0, 0x13CD9FD6, 0xE53FD4F5, 0x7FD57570, 0x157577F5, 0x75706575, 0x7F35753F, 0x94F59FD6, 0xF4C1D3F5, 0xFDD77501, 0xD4757FD5, 0x757F9575, 0x7F350500, 0x64FDFFC7, 0x00000000, 0x00000000, 0x00000000 };
unsigned int lbl_80400E20_p22[18] = { 0x000000FF, 0xC0000040, 0x007F4000, 0xFF4000FF, 0x4000C040, 0x00DFC000, 0xC18000FC, 0xC000FE40, 0x007F401F, 0x074011F7, 0x40150740, 0x15FF4015, 0xFE4015FC, 0xC7F50184, 0x05FF05FD, 0x00040100, 0x07FF0000, 0x00000000 };
unsigned int lbl_80400E68_p22[18] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xF3801FF3, 0x801FE3FF, 0x9FE7FF9F, 0xC7FF9F8C, 0xFF9F1CFF, 0x9E1FFF9C, 0x1FFF989F, 0xFF919FFF, 0x939FFF97, 0x9FFF9F9F, 0xFF9F9FFF, 0x9F9FFF9F, 0x9FFF9F9F, 0x801F9E80, 0x1F9EFFFF, 0xFFFFFFFF };
unsigned int lbl_80400EB0_p22[18] = { 0xFFFFFFFF, 0xFCE7FFFC, 0xE7FFFCE7, 0xFFC020FE, 0x4020FE78, 0x671E7867, 0x06702786, 0x7027FE70, 0x9FFE7099, 0xFE6499FE, 0x64C9FE64, 0xC9FE64F8, 0xFE64F8FC, 0x44FCF8CC, 0xFCF1CCF8, 0x03CCE107, 0xCCE3FFFC, 0xE7FFFFFF };
unsigned int lbl_80400EF8_p22[18] = { 0xFFFFFFF9, 0x24FFF924, 0xFFF924FF, 0x0F3C0100, 0x00013000, 0xE73F3CE7, 0x3924E739, 0x24E73927, 0xE73FFF27, 0x3CFF2730, 0x01273001, 0x273CE707, 0x3CE7077C, 0xE78F3C47, 0x871E0F03, 0x8F0C31CC, 0x0079EC60, 0xFDFFFFFF };
unsigned int lbl_80400F40_p22[18] = { 0xFFFFFFFF, 0xFFFFFC3F, 0xFCF18FF1, 0xE7E7E7CF, 0xF3CFCFF1, 0xCF8FF18F, 0x8FFF8F8F, 0xFF8F8FFF, 0x8F8FFF8F, 0x8FFF8F8F, 0xFF8F8FFF, 0x8F8FF18F, 0x8FF18FCF, 0xF3CFCFF3, 0xCFE7E7E7, 0xF18FF1FC, 0x3FFCFFFF, 0xFFFFFFFF };
unsigned int lbl_80400F88_p22[18] = { 0xFFFFFFFF, 0xFFFF3FC7, 0x1F8FC70F, 0xE7C707F3, 0xC707F3C7, 0x13F1C713, 0xF1C719F1, 0xC719F1C7, 0x1CF1C71C, 0xF1C71EF1, 0xC71EF1C7, 0x1FF1C71F, 0xF1C71FF3, 0xC71FF3C7, 0x1FE7C71F, 0x8FC71F3F, 0xC71FFFFF, 0xFFFFFFFF };
unsigned int lbl_80400FD0_p22[18] = { 0xFFFFFFFF, 0xFFFFF1F8, 0x1FF1E3C7, 0xF1CFF3F1, 0x8FF1F18F, 0xF1F18FF1, 0xF18FFFF1, 0xC7FFF1E0, 0xFFF1FC3F, 0x71FF8F71, 0xFFE331FF, 0xF1318FF1, 0x918FF181, 0x8FF1C1CF, 0xF1C1CFF3, 0xE1E3C7F1, 0xF81FFFFF, 0xFFFFFFFF };
void * lbl_80401018_p22[64] = { 0, (void *)&lbl_803FFEA8_p22, (void *)&lbl_803FFEF0_p22, (void *)&lbl_803FFF38_p22, (void *)&lbl_803FFF80_p22, (void *)&lbl_803FFFC8_p22, (void *)&lbl_80400010_p22, (void *)&lbl_80400058_p22, (void *)&lbl_804000A0_p22, (void *)&lbl_804000E8_p22, (void *)&lbl_80400130_p22, (void *)&lbl_80400178_p22, (void *)&lbl_804001C0_p22, (void *)&lbl_80400208_p22, (void *)&lbl_80400250_p22, (void *)&lbl_80400298_p22, (void *)&lbl_804002E0_p22, (void *)&lbl_80400328_p22, (void *)&lbl_80400370_p22, (void *)&lbl_804003B8_p22, (void *)&lbl_80400400_p22, (void *)&lbl_80400448_p22, (void *)&lbl_80400490_p22, (void *)&lbl_804004D8_p22, (void *)&lbl_80400520_p22, (void *)&lbl_80400568_p22, (void *)&lbl_804005B0_p22, (void *)&lbl_804005F8_p22, (void *)&lbl_80400640_p22, (void *)&lbl_80400688_p22, (void *)&lbl_804006D0_p22, (void *)&lbl_80400718_p22, (void *)&lbl_80400760_p22, (void *)&lbl_804007A8_p22, (void *)&lbl_804007F0_p22, (void *)&lbl_80400838_p22, (void *)&lbl_80400880_p22, (void *)&lbl_804008C8_p22, (void *)&lbl_80400910_p22, (void *)&lbl_80400958_p22, (void *)&lbl_804009A0_p22, (void *)&lbl_804009E8_p22, (void *)&lbl_80400A30_p22, (void *)&lbl_80400A78_p22, (void *)&lbl_80400AC0_p22, (void *)&lbl_80400B08_p22, (void *)&lbl_80400B50_p22, (void *)&lbl_80400B98_p22, (void *)&lbl_80400BE0_p22, (void *)&lbl_80400C28_p22, (void *)&lbl_80400C70_p22, (void *)&lbl_80400CB8_p22, (void *)&lbl_80400D00_p22, (void *)&lbl_80400D48_p22, (void *)&lbl_80400D90_p22, (void *)&lbl_80400DD8_p22, (void *)&lbl_80400E20_p22, (void *)&lbl_80400E68_p22, (void *)&lbl_80400EB0_p22, (void *)&lbl_80400EF8_p22, (void *)&lbl_80400F40_p22, (void *)&lbl_80400F88_p22, (void *)&lbl_80400FD0_p22, 0 };

#pragma force_active reset

char *Sci2Card_GetReceiptStringEntry(int index_p22)
{
return (*(char (*)[24][0xD])&Sci2Card_GetReceiptStringEntry_rodata_80318138)[index_p22];
}
void *CardPrintJob_GetFontPagePayload(int page_p22)
{
page_p22++;
if (page_p22 >= 0x3F) {
return 0;
}
return lbl_80401018_p22[page_p22];
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

C_REGION_END
#ifdef NON_MATCHING
C_REGION_BEGIN
/*
 * Equivalent C for the PC port (docs/nonmatching_c.md) of the three card
 * state machines that are inline asm above. They are built from the same
 * steps that exist as separate functions in this unit
 * (Sci2Card_WriteTrackData_*, Sci2Card_PrintReceipt_*, Sci2Card_EjectAndFinalize_Step);
 * the target inlines them and then takes the backup snapshot of g_playerData.
 */
#pragma inline_max_size(10000)
C_REGION_END
#pragma cplusplus on
extern "C" {
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D1225;
extern struct CardPlayerSnapshot_p14 SetCourseParams_bss_805D275C;
extern int Backup_PublishShadowCopy_Inline(void);
extern void Sci2Card_GetResponsePayload(void *card, void *payload);
extern unsigned char fn_801D4FF4(void *player, const void *raw, unsigned char publish);
extern void PlayerData_ResetForFlow(void);
unsigned char card_rw_state_machine_short(void);
unsigned char card_rw_state_machine(void);
unsigned char card_read_state_machine(void);

extern int g_cardReceiptMode;
extern int g_cardReceiptLine;
extern int lbl_806D123C;
extern unsigned char Sci2Card_IsStatus3Zero(void *card);
extern int Sci2Card_BuildScoreReceiptLine(int line);

/* same as the Receipt_* inlines of the receipt units above */
static inline unsigned char CardSM_ReceiptIsDone(int line)
{
    unsigned char done = 0;
    if (line >= 9 && g_cardReceiptMode == 1) {
        done = 1;
    } else if (line >= 10) {
        done = 1;
    } else if (line >= 2 && g_cardReceiptMode == 0) {
        done = 1;
    }
    return done;
}

static inline void CardSM_ReceiptBuildLine(int line)
{
    int next;
    if (lbl_806D122B_p2 == 0) {
        next = Sci2Card_BuildScoreReceiptLine(line);
    } else {
        next = Sci2Card_BuildRetryReceiptLine(line);
    }
    g_cardReceiptLine = next;
}

static inline unsigned char CardSM_ReceiptAdvance(void)
{
    int line = g_cardReceiptLine;
    if (CardSM_ReceiptIsDone(line) == 1) {
        lbl_806D122A_p2 = 0;
        lbl_806D1210_p2 = 1;
        lbl_806D122B_p2 = 0;
        return 1;
    }
    CardSM_ReceiptBuildLine(line);
    return 0;
}

static inline unsigned char CardSM_ReceiptStart(int mode, unsigned char header, unsigned char retry)
{
    lbl_806D122B_p2 = retry;
    if (!ServiceLatch_CheckTriggered_p2()) {
        lbl_806D122A_p2 = 1;
        lbl_806D121C_p2 = 0;
        lbl_806CF0E4_p2 = 5;
        lbl_806D1210_p2 = 1;
        return 1;
    }
    g_cardReceiptMode = mode;
    lbl_806D1210_p2 = 0;
    lbl_806D122A_p2 = 1;
    lbl_806D121C_p2 = 0;
    lbl_806CF0E4_p2 = 5;
    g_cardReceiptLine = 0;
    lbl_806D123C = 0;
    Sci2Card_Singleton_Get_p2();
    if (g_cardReceiptMode == 0 || g_cardReceiptMode == 3) {
        if (header == 1) {
            CardSM_ReceiptBuildLine(-3);
        } else {
            CardSM_ReceiptBuildLine(0);
        }
    } else {
        g_cardReceiptLine = g_cardReceiptMode == 2 ? 9 : 2;
        if (CardSM_ReceiptAdvance() == 1) {
            return 1;
        }
    }
    return 1;
}

static inline unsigned char CardSM_ReceiptPoll(void)
{
    void *card;
    unsigned char status1;
    unsigned char status2;
    unsigned char status3;

    if (!ServiceLatch_CheckTriggered_p2()) {
        lbl_806D1210_p2 = 1;
        return 1;
    }
    if (lbl_806D1210_p2 != 0) {
        return 1;
    }
    card = Sci2Card_Singleton_Get_p2();
    Sci2Card_GetResponseStatus_p2(Sci2Card_Singleton_Get_p2(), &status1, &status2, &status3);
    if (Sci2Card_IsIdleOrExhausted_p2(card) == 1) {
        if (!Sci2Card_IsStatusOkNonTerm_p2(card)) {
            Sci2Card_SetFailCode_p2();
            return 1;
        }
        if (Sci2Card_IsStatus3Zero(card) == 1) {
            if (CardSM_ReceiptAdvance() == 1) {
                lbl_806D122A_p2 = 0;
                lbl_806D1210_p2 = 1;
                lbl_806D122B_p2 = 0;
                return 1;
            }
        }
    }
    return 0;
}

static inline void CardSM_Snapshot(void)
{
    lbl_80598A60_p14.captured_p14 = 1;
    lbl_80598A60_p14.player_p14 = g_playerData_p14;
    card_backup_p14();
}

static inline void CardSM_WriteStart(void)
{
    lbl_806D1210_p2 = 0;
    lbl_806D122A_p2 = 1;
    lbl_806D121C_p2 = 0;
    lbl_806CF0E4_p2 = 5;
    if (!ServiceLatch_CheckTriggered_p2()) {
        lbl_806D1210_p2 = 1;
        return;
    }
    card_pack_p2(g_playerData_p2, lbl_805AC55C_p2, 1);
    lbl_806D121C_p2 = card_send_track_data_p2(Sci2Card_Singleton_Get_p2(), lbl_805AC55C_p2, 0x45, 0);
}

static inline unsigned char CardSM_WritePoll(void)
{
    void *card;

    if (!ServiceLatch_CheckTriggered_p2()) {
        lbl_806D1210_p2 = 1;
        return 1;
    }
    if (lbl_806D1210_p2 != 0) {
        return 1;
    }
    card = Sci2Card_Singleton_Get_p2();
    if (lbl_806D121C_p2 == 0) {
        lbl_806D121C_p2 = card_send_track_data_p2(card, lbl_805AC55C_p2, 0x45, 0);
        return 0;
    }
    if (Sci2Card_IsIdleOrExhausted_p2(card) == 1) {
        if (!Sci2Card_IsStatusOkNonTerm_p2(card)) {
            Sci2Card_SetFailCode_p2();
            return 1;
        }
        lbl_806D122A_p2 = 0;
        lbl_806D1210_p2 = 1;
        lbl_806D122B_p2 = 0;
        return 1;
    }
    return 0;
}

/* states 0..3 of both write machines; returns -1 to fall into the next state */
static inline int CardSM_WriteAndPrint(int doneState)
{
    switch (lbl_806D1220_p2) {
    case 0:
        CardSM_WriteStart();
        lbl_806CF0D0_p2 = 0;
        lbl_806D1220_p2++;
        /* fall through */
    case 1:
        if (CardSM_WritePoll() != 1) {
            return 0;
        }
        if (lbl_806D1210_p2 != 1) {
            return 1;
        }
        lbl_806CF0D0_p2 = 1;
        lbl_806D1220_p2++;
        /* fall through */
    case 2:
        CardSM_ReceiptStart(lbl_806CF0E8_p2, lbl_806CF0D4_p2 != 1, 0);
        lbl_806D1220_p2++;
        /* fall through */
    case 3:
        if (CardSM_ReceiptPoll() != 1) {
            return 0;
        }
        if (lbl_806D1210_p2 != 1) {
            return 1;
        }
        {
            int *count = (int *)((char *)&lbl_80598A60_p14 + 0x26c);
            *count = *count + 1;
            if (*count > 200) {
                *count = 200;
            }
        }
        Backup_PublishShadowCopy_Inline();
        if (lbl_806D1225 == 1) {
            g_playerData_p14.byte1A0_p14 = 0;
            g_playerData_p14.byte199_p14 = 0;
            g_playerData_p14.byte198_p14 = 50;
            CardSM_Snapshot();
        }
        return doneState;
    }
    return -2;
}

unsigned char card_rw_state_machine_short(void)
{
    int r;

    if (!ServiceLatch_CheckTriggered_p2()) {
        lbl_806D1210_p2 = 1;
        return 1;
    }
    if (lbl_806D1210_p2 != 0) {
        return 1;
    }
    r = CardSM_WriteAndPrint(-1);
    if (r == -2) {
        return 1; /* state out of range */
    }
    if (r != -1) {
        return r;
    }
    lbl_806CF0E8_p2 = 3;
    lbl_806CF0D0_p2 = 5;
    lbl_806D1220_p2++;
    return 1;
}

unsigned char card_rw_state_machine(void)
{
    int r;

    if (!ServiceLatch_CheckTriggered_p2()) {
        lbl_806D1210_p2 = 1;
        return 1;
    }
    if (lbl_806D1210_p2 != 0) {
        return 1;
    }
    switch (lbl_806D1220_p2) {
    case 0:
    case 1:
    case 2:
    case 3:
        r = CardSM_WriteAndPrint(-1);
        if (r != -1) {
            return r;
        }
        lbl_806CF0D0_p2 = 2;
        lbl_806D1220_p2++;
        /* fall through */
    case 4:
        lbl_806D1210_p2 = 0;
        lbl_806D122A_p2 = 1;
        lbl_806D121C_p2 = 0;
        lbl_806CF0E4_p2 = 5;
        if (!ServiceLatch_CheckTriggered_p2()) {
            lbl_806D1210_p2 = 1;
        } else {
            lbl_806D1227_p2 = 0;
            lbl_806D121C_p2 = card_eject_p2(Sci2Card_Singleton_Get_p2());
            lbl_806CF0D4_p2 = 0;
        }
        lbl_806CF0D8_p2 = 1;
        lbl_806D1220_p2++;
        /* fall through */
    case 5:
        if (Eject_IsPending_p2() == 1) {
            lbl_806CF0D0_p2 = 3;
        }
        if (card_eject_state_machine_p2() == 1) {
            if (lbl_806D1210_p2 != 0 && lbl_806D1210_p2 != 1) {
                lbl_806D1220_p2--;
                return 0;
            }
            lbl_806CF0E8_p2 = 3;
            lbl_806CF0D0_p2 = 5;
            lbl_806CF0D8_p2 = 2;
            return 1;
        }
        break;
    default:
        return 1;
    }
    return 0;
}

unsigned char card_read_state_machine(void)
{
    void *card;

    if (!ServiceLatch_CheckTriggered_p2()) {
        lbl_806D1210_p2 = 1;
        return 1;
    }
    if (lbl_806D1210_p2 != 0) {
        return 1;
    }
    card = Sci2Card_Singleton_Get_p2();
    if (lbl_806D121C_p2 == 0) {
        lbl_806D121C_p2 = Sci2Card_SendCmdOptions_p5(card, 1, 0);
        return 0;
    }
    if (Sci2Card_IsIdleOrExhausted_p2(card) == 1) {
        if (!Sci2Card_IsStatusOkNonTerm_p2(card)) {
            Sci2Card_SetFailCode_p2();
            return 1;
        }
        if (Sci2Card_IsStatusOkNonTerm_p2(card) == 1) {
            lbl_806D1224 = 1;
            memset_p0(lbl_805AC55C_p2, 0, 0x45);
            Sci2Card_GetResponsePayload(card, lbl_805AC55C_p2);
            if (fn_801D4FF4(&g_playerData_p14, lbl_805AC55C_p2, 1) == 1) {
                SetCourseParams_bss_805D275C = g_playerData_p14;
                if ((signed char)g_playerData_p14.byte198_p14 > 0 && g_playerData_p14.byte199_p14 == 0) {
                    lbl_806D1214_p15 = 2;
                    lbl_806D122A_p2 = 0;
                    lbl_806D1210_p2 = 1;
                    lbl_806D122B_p2 = 0;
                    CardSM_Snapshot();
                } else {
                    lbl_806D122A_p2 = 0;
                    lbl_806D1210_p2 = 3;
                    lbl_806D122B_p2 = 0;
                    if (g_playerData_p14.byte199_p14 == 1) {
                        g_playerData_p14.byte198_p14 = 0;
                        lbl_806D1214_p15 = 6;
                    } else {
                        lbl_806D1214_p15 = 5;
                        CardSM_Snapshot();
                    }
                }
            } else {
                PlayerData_ResetForFlow();
                lbl_806D122A_p2 = 0;
                lbl_806D1210_p2 = 4;
                lbl_806D122B_p2 = 0;
            }
            return 1;
        }
        Sci2Card_SendCmdOptions_p5(card, 1, 0);
    }
    return 0;
}
}
#pragma cplusplus reset
#endif
