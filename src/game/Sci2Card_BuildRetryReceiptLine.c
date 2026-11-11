#include "game/types/text_word.h"
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
static const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80317D44[12] = { 0x20, 0x20, 0x11, 0x25, 0x2D, 0x31, 0x31, 0x73, 0x14, 0x00, 0x00, 0x00 };
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
static const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80317F3C[28] = { 0x25, 0x73, 0x25, 0x73, 0x25, 0x73, 0x8C, 0xC2, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00 };
static const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80317F58[28] = { 0x25, 0x73, 0x25, 0x73, 0x25, 0x73, 0x8C, 0xC2, 0x20, 0x8A, 0xEE, 0x96, 0x7B, 0xB1, 0xB2, 0xC3, 0xD1, 0xB9, 0xDE, 0xAF, 0xC4, 0x81, 0x49, 0x20, 0x20, 0x00, 0x00, 0x00 };
static const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80317F74[28] = { 0x25, 0x73, 0x25, 0x73, 0x25, 0x73, 0x8C, 0xC2, 0x20, 0xBA, 0xDE, 0xB0, 0xD9, 0xC4, 0xDE, 0xB1, 0xB2, 0xC3, 0xD1, 0xB9, 0xDE, 0xAF, 0xC4, 0x81, 0x49, 0x00, 0x00, 0x00 };
static const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80317F90[28] = { 0x25, 0x73, 0x25, 0x73, 0x25, 0x73, 0x8C, 0xC2, 0x20, 0xCC, 0xDF, 0xD7, 0xBD, 0xB1, 0xB2, 0xC3, 0xD1, 0xB9, 0xDE, 0xAF, 0xC4, 0x81, 0x49, 0x20, 0x20, 0x00, 0x00, 0x00 };
static const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80317FAC[28] = { 0x25, 0x73, 0x25, 0x73, 0x25, 0x73, 0x8C, 0xC2, 0x20, 0xBD, 0xCD, 0xDF, 0xBC, 0xAC, 0xD9, 0xB1, 0xB2, 0xC3, 0xD1, 0xB9, 0xDE, 0xAF, 0xC4, 0x81, 0x49, 0x00, 0x00, 0x00 };
static const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80317FC8[28] = { 0x25, 0x73, 0x25, 0x73, 0x25, 0x73, 0x8C, 0xC2, 0x20, 0x81, 0x99, 0x8E, 0x63, 0x82, 0xE8, 0x25, 0x73, 0x8C, 0xC2, 0x81, 0x99, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00 };
static const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80317FE4[28] = { 0x82, 0x50, 0x82, 0x50, 0x82, 0x55, 0x8C, 0xC2, 0x20, 0x81, 0x9A, 0xB1, 0xB2, 0xC3, 0xD1, 0xBA, 0xDD, 0xCC, 0xDF, 0xD8, 0xB0, 0xC4, 0x81, 0x49, 0x20, 0x00, 0x00, 0x00 };
static const unsigned char Sci2Card_BuildRetryReceiptLine_rodata_80318000[28] = { 0x25, 0x73, 0x25, 0x73, 0x25, 0x73, 0x8C, 0xC2, 0x20, 0xC4, 0xD8, 0xCC, 0xDF, 0xD9, 0xB1, 0xB2, 0xC3, 0xD1, 0xB9, 0xDE, 0xAF, 0xC4, 0x81, 0x49, 0x20, 0x00, 0x00, 0x00 };
static const char lbl_8031801C[] = "%s%s%s                   ";
static const char lbl_80318038[] = "%s%s%s Basic Item Get!   ";
static const char lbl_80318054[] = "%s%s%s Gold Item Get!    ";
static const char lbl_80318070[] = "%s%s%s Plus Item Get!    ";
static const char lbl_8031808C[] = "%s%s%s SP Item Get!      ";
static const char lbl_803180A8[] = "%s%s%s %s more left      ";
static const unsigned int Sci2Card_BuildRetryReceiptLine_rodata_803180C4[7] = { TEXT_WORD(0x82, 'P', 0x82, 'P'), TEXT_WORD(0x82, 'U', ' ', 'i'), TEXT_WORD('t', 'e', 'm', ' '), TEXT_WORD('c', 'o', 'm', 'p'), TEXT_WORD('l', 'e', 't', 'e'), TEXT_WORD(' ', ' ', ' ', ' '), TEXT_WORD(' ', 0, 0, 0) };
static const unsigned int lbl_803180E0[7] = { TEXT_WORD('%', 's', '%', 's'), TEXT_WORD('%', 's', ' ', 't'), TEXT_WORD('r', 'i', 'p', 'l'), TEXT_WORD('e', ' ', 'i', 't'), TEXT_WORD('e', 'm', ' ', 'g'), TEXT_WORD('e', 't', ' ', ' '), TEXT_WORD(' ', 0, 0, 0) };
static const unsigned int lbl_803180FC[3] = { TEXT_WORD(0x82, 'm', 0x82, '`'), TEXT_WORD(0x82, 'l', 0x82, 'b'), TEXT_WORD(0x82, 'n', 0, 0) };
static const unsigned int Sci2Card_BuildScoreReceiptLine_rodata_80318108[3] = { TEXT_WORD(0x91, 0xCE, 0x90, 0xED), TEXT_WORD(0x83, 0x8C, 0x81, '['), TEXT_WORD(0x83, 'X', 0, 0) };
static const unsigned int lbl_80318114[3] = { TEXT_WORD('T', 'E', 'S', 'T'), TEXT_WORD(' ', 'P', 'R', 'I'), TEXT_WORD('N', 'T', 0, 0) };
static const unsigned int lbl_80318120[6] = { TEXT_WORD(0x82, 's', 0x82, 'd'), TEXT_WORD(0x82, 'r', 0x82, 's'), TEXT_WORD(0x81, '@', 0x82, 'o'), TEXT_WORD(0x82, 'q', 0x82, 'h'), TEXT_WORD(0x82, 'm', 0x82, 's'), 0x00000000 };
static const unsigned char Sci2Card_GetReceiptStringEntry_rodata_80318138[312] = { 0x1B, 0x67, 0x01, 0x1B, 0x67, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x07, 0x1B, 0x67, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x09, 0x1B, 0x67, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x0B, 0x1B, 0x67, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x0D, 0x1B, 0x67, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x0F, 0x1B, 0x67, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x03, 0x1B, 0x67, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x05, 0x1B, 0x67, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x11, 0x1B, 0x67, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x17, 0x1B, 0x67, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x19, 0x1B, 0x67, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x1B, 0x1B, 0x67, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x1D, 0x1B, 0x67, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x1F, 0x1B, 0x67, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x13, 0x1B, 0x67, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x15, 0x1B, 0x67, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x21, 0x1B, 0x67, 0x22, 0x1B, 0x67, 0x23, 0x1B, 0x67, 0x24, 0x00, 0x1B, 0x67, 0x25, 0x1B, 0x67, 0x26, 0x1B, 0x67, 0x27, 0x1B, 0x67, 0x28, 0x00, 0x1B, 0x67, 0x29, 0x1B, 0x67, 0x2A, 0x1B, 0x67, 0x2B, 0x1B, 0x67, 0x2C, 0x00, 0x1B, 0x67, 0x2D, 0x1B, 0x67, 0x2E, 0x1B, 0x67, 0x2F, 0x1B, 0x67, 0x30, 0x00, 0x1B, 0x67, 0x31, 0x1B, 0x67, 0x32, 0x1B, 0x67, 0x33, 0x1B, 0x67, 0x34, 0x00, 0x1B, 0x67, 0x35, 0x1B, 0x67, 0x36, 0x1B, 0x67, 0x37, 0x1B, 0x67, 0x38, 0x00, 0x1B, 0x67, 0x39, 0x1B, 0x67, 0x3A, 0x1B, 0x67, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x67, 0x3C, 0x1B, 0x67, 0x3D, 0x1B, 0x67, 0x3E, 0x00, 0x00, 0x00, 0x00 };

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
extern const char *lbl_803FFDF0_p19[10] = {
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
lbl_806D121C_p12 = card_eject_p12((int *)Sci2Card_Singleton_Get_p12());
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
card_p12 = (int *)Sci2Card_Singleton_Get_p12();
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
lbl_806D121C_p12 = card_eject_p12((int *)Sci2Card_Singleton_Get_p12());
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
__register_global_object(&lbl_806D122C_p21, (void *)dtor_8002F978_p21, lbl_805AC550_p21);
__register_global_object(&lbl_806D1244_p21, (void *)dtor_8002F978_p21, lbl_805AC5E4_p21);
}
__declspec(section ".ctors") static void (*const s_Sci2Card_RegisterReceiptBuffersCleanup_ctor_p21)(void) = Sci2Card_RegisterReceiptBuffersCleanup;
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Sci2Card_ReceiptTables.c (0x80099958) ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
#pragma force_active on

unsigned char lbl_803FFEA8_p22[72] = { 0x00, 0xF0, 0x00, 0x01, 0xF0, 0x00, 0x03, 0xF0, 0x00, 0x03, 0xF1, 0xFF, 0x03, 0xF1, 0xFF, 0x03, 0xF9, 0xF3, 0x01, 0xFF, 0xE3, 0x03, 0xFD, 0xE3, 0x03, 0xFD, 0xC9, 0x03, 0xFD, 0xC9, 0x03, 0xFD, 0x9C, 0x01, 0xFD, 0x9C, 0x00, 0x7D, 0x3E, 0x00, 0x7F, 0x3E, 0x00, 0x7F, 0xFF, 0x00, 0x3F, 0xFF, 0x00, 0x1E, 0xFF, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x73, 0x00, 0x00, 0xCF, 0x00, 0x00, 0xFF };
unsigned char lbl_803FFEF0_p22[72] = { 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x0F, 0xC0, 0xFF, 0x8F, 0xC0, 0xFF, 0x8F, 0xC0, 0xCF, 0x9F, 0xC0, 0xC7, 0xFF, 0x80, 0xC7, 0xBF, 0xC0, 0x93, 0xBF, 0xC0, 0x93, 0xBF, 0xC0, 0x39, 0xBF, 0xC0, 0x39, 0xBF, 0x80, 0x7C, 0xBE, 0x00, 0x7C, 0xFE, 0x00, 0xFF, 0xFE, 0x00, 0xFF, 0x7C, 0x00, 0xFE, 0x78, 0x00, 0xFC, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x77, 0x00, 0x00, 0x7B, 0x80, 0x00, 0xFF, 0x80, 0x00 };
unsigned char lbl_803FFF38_p22[72] = { 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0xC1, 0xC1, 0x00, 0xE3, 0x77, 0x38, 0xF6, 0x1C, 0x7E, 0xFE, 0x08, 0x3F, 0xFE, 0x07, 0x31, 0xFE, 0x0F, 0x30, 0xFE, 0x1F, 0x30, 0xFC, 0x3F, 0x10, 0xF8, 0x3F, 0x18, 0x40, 0x3F, 0x08, 0x60, 0x3F, 0x04, 0x20, 0x3F, 0x02, 0x30, 0x1F, 0x01, 0x6C, 0x0F, 0x00, 0xE6, 0x07, 0x00, 0x63, 0xC0, 0x06, 0xE0, 0x7F, 0x07, 0xC0, 0x02, 0x03, 0x80, 0x3F, 0x00, 0x00, 0xEF, 0x00, 0x01, 0x9F, 0x00, 0x07, 0xFF };
unsigned char lbl_803FFF80_p22[72] = { 0x00, 0x00, 0x00, 0x80, 0x81, 0x00, 0xC1, 0xC3, 0x00, 0x77, 0x63, 0x00, 0x1C, 0x37, 0x1C, 0x08, 0x7F, 0x7E, 0xE0, 0x7F, 0xFC, 0xF0, 0x7F, 0x8C, 0xF8, 0x7F, 0x0C, 0xFC, 0x3F, 0x0C, 0xFC, 0x1F, 0x08, 0xFC, 0x02, 0x18, 0xFC, 0x06, 0x10, 0xFC, 0x04, 0x20, 0xF8, 0x0C, 0x40, 0xF0, 0x36, 0x80, 0xE0, 0x67, 0x00, 0x03, 0xC6, 0x00, 0xFE, 0x07, 0x60, 0xE0, 0x03, 0xE0, 0xFE, 0x01, 0xC0, 0x77, 0x80, 0x00, 0x7B, 0xC0, 0x00, 0xFF, 0xF0, 0x00 };
unsigned char lbl_803FFFC8_p22[72] = { 0x00, 0x00, 0x00, 0x01, 0xF0, 0xFF, 0x01, 0xFC, 0xAA, 0x00, 0xDE, 0xFF, 0x00, 0xC7, 0xFF, 0x00, 0xC3, 0xF8, 0x00, 0x61, 0xF8, 0x00, 0x60, 0xF9, 0x00, 0x30, 0xF9, 0x00, 0x18, 0x79, 0x00, 0x8C, 0x79, 0x00, 0x86, 0x39, 0x00, 0x83, 0x39, 0x00, 0x83, 0xF9, 0x00, 0xC1, 0xF9, 0x00, 0x60, 0x3F, 0x00, 0x30, 0x1F, 0x00, 0x3F, 0xDF, 0x00, 0x1F, 0xCF, 0x00, 0x0F, 0xEF, 0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 0x00, 0x00, 0x36, 0x00, 0x00, 0xEE };
unsigned char lbl_80400010_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0x87, 0xC0, 0xAA, 0x9F, 0xC0, 0xFF, 0xBD, 0x80, 0xFF, 0xF1, 0x80, 0x0F, 0xE1, 0x80, 0x0F, 0xC3, 0x00, 0xFF, 0x83, 0x00, 0xFF, 0x86, 0x00, 0xFF, 0x0C, 0x00, 0xFF, 0x18, 0x00, 0xFE, 0x30, 0x80, 0xFE, 0x60, 0x80, 0xFF, 0xE0, 0x80, 0xFF, 0xC1, 0x80, 0xFC, 0x03, 0x00, 0xF8, 0x06, 0x00, 0xFB, 0xFE, 0x00, 0xF3, 0xFC, 0x00, 0xF7, 0xF8, 0x00, 0xE0, 0x00, 0x00, 0x40, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xFF, 0x00, 0x00 };
unsigned char lbl_80400058_p22[72] = { 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x00, 0xF9, 0x80, 0x00, 0x65, 0x00, 0x00, 0x23, 0xFF, 0x00, 0x29, 0xC3, 0x00, 0x15, 0xC1, 0x00, 0x15, 0xEC, 0x00, 0x15, 0xEC, 0x00, 0x14, 0x2C, 0x00, 0x14, 0x2C, 0x00, 0x25, 0xEC, 0x00, 0x45, 0xC1, 0x01, 0x99, 0xC3, 0x02, 0x23, 0xFF, 0x04, 0xC6, 0x80, 0x05, 0x0C, 0xC0, 0x04, 0x30, 0x7F, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xE0, 0x00, 0x01, 0xE0, 0x00, 0x01, 0xFF };
unsigned char lbl_804000A0_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0x83, 0x80, 0x00, 0xCF, 0x80, 0x00, 0x53, 0x00, 0xFF, 0xE2, 0x00, 0x9C, 0xCA, 0x00, 0x99, 0xD4, 0x00, 0xD3, 0xD4, 0x00, 0xC7, 0xD4, 0x00, 0xC6, 0x14, 0x00, 0xC6, 0x14, 0x00, 0xD3, 0xD2, 0x00, 0x99, 0xD1, 0x00, 0x9C, 0xCC, 0xC0, 0xFF, 0xE2, 0x20, 0x00, 0xB1, 0x90, 0x01, 0x98, 0x50, 0xFF, 0x06, 0x10, 0x60, 0x01, 0xE0, 0x60, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x01, 0xC0, 0x00, 0x01, 0xE0, 0x00, 0xFF, 0xE0, 0x00 };
unsigned char lbl_804000E8_p22[72] = { 0x00, 0x00, 0x00, 0x01, 0xE3, 0xFF, 0x01, 0xF3, 0xFF, 0x01, 0xDB, 0xFF, 0x00, 0xCF, 0xFF, 0x00, 0xC7, 0x3E, 0x00, 0xC3, 0x3E, 0x00, 0x63, 0x9C, 0x00, 0x63, 0x9C, 0x00, 0x33, 0xC9, 0x00, 0x1B, 0xC9, 0x00, 0x07, 0xE3, 0x00, 0x03, 0xE3, 0x00, 0x01, 0xF3, 0x08, 0x44, 0xFF, 0x0E, 0xEE, 0x7F, 0x07, 0xFF, 0x1F, 0x03, 0xBB, 0x82, 0x01, 0x11, 0x02, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x7B, 0x00, 0x00, 0xE6, 0x00, 0x03, 0xCE, 0x00, 0x03, 0xFF };
unsigned char lbl_80400130_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0xC7, 0x80, 0xFF, 0xCF, 0x80, 0xFF, 0xDB, 0x80, 0xFF, 0xF3, 0x80, 0x7C, 0xE3, 0x00, 0x7C, 0xC3, 0x00, 0x39, 0xC6, 0x00, 0x39, 0xC6, 0x00, 0x93, 0xCC, 0x00, 0x93, 0xD8, 0x00, 0xC7, 0xE0, 0x00, 0xC7, 0xC0, 0x00, 0xCF, 0x80, 0x00, 0xFF, 0x22, 0x10, 0xFE, 0x77, 0x70, 0xFC, 0xFF, 0xE0, 0xC1, 0xDD, 0xC0, 0xC0, 0x88, 0x80, 0xF8, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x77, 0x00, 0x00, 0x7B, 0xC0, 0x00, 0xFF, 0xC0, 0x00 };
unsigned char lbl_80400178_p22[72] = { 0x00, 0x00, 0x00, 0x07, 0x9F, 0xFF, 0x0F, 0xDF, 0xF8, 0x1F, 0xFF, 0xF0, 0x3F, 0xFF, 0xC0, 0x3F, 0xDF, 0x80, 0x3F, 0x1F, 0x80, 0x3E, 0x1F, 0xF0, 0x3F, 0x1F, 0xFC, 0x3F, 0xD2, 0x7F, 0x1F, 0xF2, 0x7F, 0x0F, 0xDF, 0xFC, 0x07, 0x9F, 0xF0, 0x00, 0x1F, 0x80, 0x00, 0x1F, 0xC0, 0x00, 0x1F, 0xE0, 0x00, 0x07, 0xF8, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x02, 0x00, 0x00, 0x07, 0x00, 0x03, 0xFF, 0x00, 0x03, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0xFF };
unsigned char lbl_804001C0_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0xFC, 0xF0, 0x3F, 0xFD, 0xF8, 0x0F, 0xFF, 0xFC, 0x07, 0xFF, 0xFE, 0x03, 0xFD, 0xFE, 0x03, 0xFC, 0x7E, 0x01, 0xFC, 0x3E, 0x01, 0xFC, 0x7E, 0x81, 0x25, 0xFE, 0x81, 0x27, 0xFC, 0x01, 0xFD, 0xF8, 0x01, 0xFC, 0xF0, 0x03, 0xFC, 0x00, 0x07, 0xFC, 0x00, 0x0F, 0xFC, 0x00, 0x3F, 0xE0, 0x00, 0xFF, 0x00, 0x00, 0xC0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x01, 0xC0, 0x00, 0x01, 0xE0, 0x00, 0xFF, 0xE0, 0x00 };
unsigned char lbl_80400208_p22[72] = { 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x01, 0x80, 0x00, 0x03, 0x38, 0x00, 0x02, 0x7F, 0xC3, 0x03, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x01, 0xFE, 0x7F, 0x00, 0xFC, 0xBF, 0x00, 0xF8, 0xDF, 0x00, 0x7C, 0x3F, 0x00, 0x5E, 0x7E, 0x00, 0xCF, 0xFC, 0x00, 0x9F, 0xF8, 0x01, 0xBF, 0xFC, 0x01, 0x7D, 0xFE, 0x03, 0xF8, 0x7F, 0x03, 0xE0, 0x0F, 0x07, 0x80, 0x06, 0x06, 0x00, 0x1F, 0x00, 0x00, 0xF3, 0x00, 0x01, 0xCF, 0x00, 0x03, 0x9F, 0x00, 0x03, 0xFF };
unsigned char lbl_80400250_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x40, 0xF0, 0x1E, 0x40, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x80, 0xFE, 0x7F, 0x80, 0xFC, 0xBF, 0x00, 0xF8, 0xDF, 0x00, 0xFC, 0x3E, 0x00, 0x7E, 0x7B, 0x00, 0xBF, 0xF3, 0x00, 0xDF, 0xF9, 0x80, 0x3F, 0xFD, 0x80, 0x7F, 0xBE, 0x80, 0xFE, 0x1F, 0xC0, 0xF0, 0x07, 0xC0, 0x60, 0x01, 0xE0, 0xF8, 0x00, 0x60, 0x7F, 0x00, 0x00, 0x7B, 0x80, 0x00, 0x7D, 0xC0, 0x00, 0xFF, 0xC0, 0x00 };
unsigned char lbl_80400298_p22[72] = { 0x00, 0x00, 0x61, 0x00, 0x00, 0x73, 0x01, 0xFC, 0x6E, 0x00, 0x82, 0x75, 0x08, 0x4D, 0x40, 0x08, 0x52, 0xD8, 0x36, 0x51, 0x50, 0x08, 0x50, 0xC1, 0x08, 0x50, 0x42, 0x08, 0x50, 0x52, 0x00, 0x68, 0x43, 0x00, 0x14, 0x53, 0x00, 0x0A, 0x43, 0x00, 0x05, 0x41, 0x00, 0x02, 0xD0, 0x00, 0x1A, 0x58, 0x00, 0x16, 0xA0, 0x00, 0x11, 0x11, 0x01, 0x0E, 0x0C, 0x01, 0x00, 0x02, 0x06, 0xC0, 0x02, 0x01, 0x00, 0x7F, 0x01, 0x00, 0x60, 0x01, 0x00, 0xFF };
unsigned char lbl_804002E0_p22[72] = { 0xC3, 0x00, 0x00, 0xE7, 0x00, 0x00, 0xBB, 0x1F, 0xC0, 0x57, 0x20, 0x80, 0x81, 0x59, 0x00, 0x0D, 0xA5, 0x00, 0x85, 0x45, 0x00, 0xC1, 0x85, 0x00, 0x61, 0x05, 0x00, 0xE5, 0x05, 0x10, 0xE1, 0x0B, 0x10, 0xE5, 0x14, 0x6C, 0xE1, 0x28, 0x10, 0xC1, 0x50, 0x10, 0x85, 0xA0, 0x10, 0x0D, 0x2C, 0x00, 0x83, 0xB4, 0x00, 0xC4, 0x44, 0x00, 0x98, 0x38, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x03, 0x00, 0x00, 0xFF, 0x80, 0x00 };
unsigned char lbl_80400328_p22[72] = { 0x0F, 0x0F, 0xFF, 0x1E, 0x0F, 0xFF, 0x1C, 0x0F, 0xFF, 0x3C, 0x0E, 0x00, 0x3C, 0x0E, 0x00, 0x3C, 0x06, 0x0C, 0x3E, 0x00, 0x1C, 0x3C, 0x02, 0x1C, 0x3C, 0x02, 0x36, 0x3C, 0x02, 0x36, 0x3C, 0x02, 0x63, 0x3E, 0x02, 0x63, 0x3F, 0x82, 0xC1, 0x3F, 0x80, 0xC1, 0x3F, 0x80, 0x00, 0x3F, 0xC0, 0x00, 0x3F, 0xE1, 0x00, 0x3F, 0xFF, 0xC0, 0x3F, 0xFF, 0xFD, 0x3F, 0xFF, 0xFD, 0x1F, 0xFF, 0xE0, 0x1F, 0xFF, 0x8C, 0x07, 0xFF, 0x30, 0x03, 0xFF, 0x00 };
unsigned char lbl_80400370_p22[72] = { 0xFF, 0xF0, 0xE0, 0xFF, 0xF0, 0x78, 0xFF, 0xF0, 0x3C, 0x00, 0x70, 0x3E, 0x00, 0x70, 0x3E, 0x30, 0x60, 0x3E, 0x38, 0x00, 0x7E, 0x38, 0x40, 0x3E, 0x6C, 0x40, 0x3E, 0x6C, 0x40, 0x3E, 0xC6, 0x40, 0x3E, 0xC6, 0x40, 0x7E, 0x83, 0x41, 0xFE, 0x83, 0x01, 0xFE, 0x00, 0x01, 0xFE, 0x00, 0x83, 0xFE, 0x01, 0x87, 0xFE, 0x03, 0xFF, 0xFE, 0x1F, 0xFF, 0xFE, 0x1F, 0xFF, 0xFE, 0x03, 0xFF, 0xFE, 0x88, 0xFF, 0xFC, 0x84, 0x7F, 0xFC, 0x00, 0x7F, 0xF0 };
unsigned char lbl_804003B8_p22[72] = { 0x0F, 0xFF, 0xFF, 0x1F, 0x7F, 0x7F, 0x1F, 0x3E, 0x3E, 0x3F, 0x1C, 0x88, 0x07, 0x09, 0xE3, 0x01, 0x01, 0xF7, 0x00, 0x01, 0xF8, 0x0E, 0x01, 0xF0, 0x0F, 0x01, 0xE0, 0x0F, 0x03, 0xC0, 0x2F, 0x07, 0xC0, 0x27, 0xBF, 0xC0, 0x37, 0x9F, 0xC0, 0x3B, 0xDF, 0xC0, 0x3D, 0xCF, 0xE0, 0x3E, 0x93, 0xF0, 0x3F, 0x19, 0xF8, 0x3F, 0x9C, 0x3F, 0x39, 0x1F, 0x80, 0x38, 0x3F, 0xFD, 0x3C, 0x7F, 0xC0, 0x1F, 0xFF, 0x10, 0x07, 0xFE, 0x60, 0x03, 0xF8, 0x00 };
unsigned char lbl_80400400_p22[72] = { 0xFF, 0xFF, 0xE0, 0x7F, 0x7E, 0xF8, 0x3E, 0x3C, 0xFC, 0x88, 0x9C, 0xFE, 0xE3, 0xC8, 0xE2, 0xF7, 0x80, 0x80, 0x1F, 0x80, 0x02, 0x0F, 0x80, 0x72, 0x07, 0x80, 0xF2, 0x03, 0xC0, 0xF2, 0x03, 0xE0, 0xF6, 0x03, 0xFD, 0xE6, 0x03, 0xF9, 0xEE, 0x03, 0xFB, 0xDE, 0x07, 0xF3, 0xBE, 0x0F, 0xC9, 0x7E, 0x1F, 0x98, 0xFE, 0xFC, 0x39, 0xFE, 0x01, 0xF8, 0x9E, 0x1F, 0xFC, 0x1E, 0x01, 0xFE, 0x3E, 0x88, 0x7F, 0xFC, 0x84, 0x3F, 0xFC, 0x00, 0x0F, 0xF0 };
unsigned char lbl_80400448_p22[72] = { 0xFF, 0xFF, 0xFF, 0xFE, 0x0F, 0x00, 0xFE, 0x03, 0x55, 0xFF, 0x21, 0x00, 0xFF, 0x38, 0x00, 0xFF, 0x3C, 0x07, 0xFF, 0x9E, 0x07, 0xFF, 0x9F, 0x06, 0xFF, 0xCF, 0x06, 0xFF, 0xE7, 0x86, 0xFF, 0x73, 0x86, 0xFF, 0x79, 0xC6, 0xFF, 0x7C, 0xC6, 0xFF, 0x7C, 0x06, 0xFF, 0x3E, 0x06, 0xFF, 0x9F, 0xC0, 0xFF, 0xCF, 0xE0, 0xFF, 0xC0, 0x20, 0xFF, 0xE0, 0x30, 0xFF, 0xF0, 0x10, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0x11 };
unsigned char lbl_80400490_p22[72] = { 0xFF, 0xFF, 0xFF, 0x00, 0x78, 0x3F, 0x55, 0x60, 0x3F, 0x00, 0x42, 0x7F, 0x00, 0x0E, 0x7F, 0xF0, 0x1E, 0x7F, 0xF0, 0x3C, 0xFF, 0x00, 0x7C, 0xFF, 0x00, 0x79, 0xFF, 0x00, 0xF3, 0xFF, 0x00, 0xE7, 0xFF, 0x01, 0xCF, 0x7F, 0x01, 0x9F, 0x7F, 0x00, 0x1F, 0x7F, 0x00, 0x3E, 0x7F, 0x03, 0xFC, 0xFF, 0x07, 0xF9, 0xFF, 0x04, 0x01, 0xFF, 0x0C, 0x03, 0xFF, 0x08, 0x07, 0xFF, 0x1F, 0xFF, 0xFF, 0xBF, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x00, 0xFF, 0xFF };
unsigned char lbl_804004D8_p22[72] = { 0x07, 0xFF, 0xFF, 0x1F, 0x1F, 0x00, 0x1F, 0x06, 0x7F, 0x3F, 0x9A, 0xFF, 0x3F, 0xDC, 0x00, 0x3F, 0xD6, 0x3C, 0x3F, 0xEA, 0x3E, 0x3F, 0xEA, 0x13, 0x3F, 0xEA, 0x13, 0x3F, 0xEB, 0xD3, 0x3F, 0xEB, 0xD3, 0x3F, 0xDA, 0x13, 0x3F, 0xBA, 0x3E, 0x3E, 0x66, 0x3C, 0x3D, 0xDC, 0x00, 0x3B, 0x39, 0x7F, 0x3A, 0xF3, 0x3F, 0x3B, 0xCF, 0x80, 0x3C, 0x3F, 0xFE, 0x3F, 0xFF, 0xFE, 0x1F, 0xFF, 0x00, 0x1F, 0xFF, 0x1F, 0x07, 0xFE, 0x1F, 0x03, 0xFE, 0x00 };
unsigned char lbl_80400520_p22[72] = { 0xFF, 0xFF, 0xE0, 0x00, 0x7C, 0x78, 0xFF, 0x30, 0x7C, 0xFF, 0xAC, 0xFE, 0x00, 0x1D, 0xFE, 0x63, 0x35, 0xFE, 0x66, 0x2B, 0xFE, 0x2C, 0x2B, 0xFE, 0x38, 0x2B, 0xFE, 0x39, 0xEB, 0xFE, 0x39, 0xEB, 0xFE, 0x2C, 0x2D, 0xFE, 0x66, 0x2E, 0xFE, 0x63, 0x33, 0x3E, 0x00, 0x1D, 0xDE, 0xFF, 0x4E, 0x6E, 0xFE, 0x67, 0xAE, 0x00, 0xF9, 0xEE, 0x1F, 0xFE, 0x1E, 0x1F, 0xFF, 0xFE, 0x00, 0x3F, 0xFE, 0xFE, 0x3F, 0xFC, 0xFE, 0x1F, 0xFC, 0x00, 0x1F, 0xF0 };
unsigned char lbl_80400568_p22[72] = { 0x07, 0xFF, 0xFF, 0x1E, 0x1C, 0x00, 0x1E, 0x0C, 0x00, 0x3E, 0x24, 0x00, 0x3F, 0x30, 0x00, 0x3F, 0x38, 0xC1, 0x3F, 0x3C, 0xC1, 0x3F, 0x9C, 0x63, 0x3F, 0x9C, 0x63, 0x3F, 0xCC, 0x36, 0x3F, 0xE4, 0x36, 0x3F, 0xF8, 0x1C, 0x3F, 0xFC, 0x1C, 0x3F, 0xFE, 0x0C, 0x37, 0xBB, 0x00, 0x31, 0x11, 0x80, 0x38, 0x00, 0xE0, 0x3C, 0x44, 0x7D, 0x3E, 0xEE, 0xFD, 0x3F, 0xFF, 0xE0, 0x1F, 0xFF, 0x84, 0x1F, 0xFF, 0x19, 0x07, 0xFC, 0x31, 0x03, 0xFC, 0x00 };
unsigned char lbl_804005B0_p22[72] = { 0xFF, 0xFF, 0xE0, 0x00, 0x38, 0x78, 0x00, 0x30, 0x7C, 0x00, 0x24, 0x7E, 0x00, 0x0C, 0x7E, 0x83, 0x1C, 0xFE, 0x83, 0x3C, 0xFE, 0xC6, 0x39, 0xFE, 0xC6, 0x39, 0xFE, 0x6C, 0x33, 0xFE, 0x6C, 0x27, 0xFE, 0x38, 0x1F, 0xFE, 0x38, 0x3F, 0xFE, 0x30, 0x7F, 0xFE, 0x00, 0xDD, 0xEE, 0x01, 0x88, 0x8E, 0x03, 0x00, 0x1E, 0x3E, 0x22, 0x3E, 0x3F, 0x77, 0x7E, 0x07, 0xFF, 0xFE, 0x81, 0xFF, 0xFE, 0x88, 0xFF, 0xFC, 0x84, 0x3F, 0xFC, 0x00, 0x3F, 0xF0 };
unsigned char lbl_804005F8_p22[72] = { 0x1F, 0xFF, 0xFF, 0x38, 0x60, 0x00, 0x30, 0x20, 0x07, 0x60, 0x00, 0x0F, 0x40, 0x00, 0x3F, 0x40, 0x20, 0x7F, 0x00, 0xE0, 0x7F, 0x01, 0xE0, 0x0F, 0x00, 0xE0, 0x03, 0x00, 0x2D, 0x80, 0x20, 0x0D, 0x80, 0x30, 0x20, 0x03, 0x38, 0x60, 0x0F, 0x3F, 0xE0, 0x7F, 0x3F, 0xE0, 0x3F, 0x3F, 0xE0, 0x1F, 0x3F, 0xF8, 0x07, 0x3F, 0xFF, 0x00, 0x3F, 0xFF, 0xFD, 0x3F, 0xFF, 0xF8, 0x1F, 0xFC, 0x00, 0x1F, 0xFC, 0x7F, 0x07, 0xF8, 0x7F, 0x07, 0xF8, 0x00 };
unsigned char lbl_80400640_p22[72] = { 0xFF, 0xFF, 0xE0, 0x00, 0x03, 0x08, 0xC0, 0x02, 0x04, 0xF0, 0x00, 0x02, 0xF8, 0x00, 0x00, 0xFC, 0x02, 0x00, 0xFC, 0x03, 0x80, 0xFE, 0x03, 0xC0, 0xFE, 0x03, 0x80, 0x7E, 0xDA, 0x00, 0x7E, 0xD8, 0x02, 0xFE, 0x02, 0x06, 0xFE, 0x03, 0x0E, 0xFC, 0x03, 0xFE, 0xF8, 0x03, 0xFE, 0xF0, 0x03, 0xFE, 0xC0, 0x1F, 0xFE, 0x00, 0xFF, 0xFE, 0x3F, 0xFF, 0xFE, 0x1F, 0xFF, 0xFE, 0x00, 0x3F, 0xFE, 0xFE, 0x3F, 0xFC, 0xFE, 0x1F, 0xFC, 0x00, 0x1F, 0xF0 };
unsigned char lbl_80400688_p22[72] = { 0x07, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x1E, 0x7F, 0xFF, 0x3C, 0xC7, 0xFF, 0x3D, 0x80, 0x3C, 0x3C, 0xFF, 0xFF, 0x3E, 0x00, 0x00, 0x3E, 0x01, 0x80, 0x3F, 0x03, 0x40, 0x3F, 0x07, 0x20, 0x3F, 0x83, 0xC0, 0x3F, 0xA1, 0x81, 0x3F, 0x30, 0x03, 0x3F, 0x60, 0x07, 0x3E, 0x40, 0x03, 0x3E, 0x82, 0x01, 0x3C, 0x07, 0x80, 0x3C, 0x1F, 0xF0, 0x38, 0x7F, 0xF9, 0x39, 0xFF, 0xE0, 0x1F, 0xFF, 0x0C, 0x1F, 0xFE, 0x30, 0x07, 0xFC, 0x60, 0x03, 0xFC, 0x00 };
unsigned char lbl_804006D0_p22[72] = { 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0xF8, 0xFF, 0xFE, 0x7C, 0xFF, 0xFF, 0xBE, 0x0F, 0xE1, 0xBE, 0xFF, 0xFF, 0x3E, 0x00, 0x00, 0x7E, 0x01, 0x80, 0x7E, 0x03, 0x40, 0xFE, 0x07, 0x20, 0xFE, 0x03, 0xC1, 0xFE, 0x81, 0x84, 0xFE, 0x40, 0x0C, 0xFE, 0x20, 0x06, 0x7E, 0xC0, 0x02, 0x7E, 0x80, 0x41, 0x7E, 0x01, 0xE0, 0x3E, 0x0F, 0xF8, 0x3E, 0x9F, 0xFE, 0x1E, 0x07, 0xFF, 0x9E, 0x80, 0xFF, 0xFE, 0x84, 0x7F, 0xFC, 0x82, 0x3F, 0xFC, 0x00, 0x3F, 0xF0 };
unsigned char lbl_80400718_p22[72] = { 0x07, 0xFF, 0x9E, 0x1F, 0xFF, 0x8C, 0x1E, 0x03, 0x91, 0x3F, 0x7D, 0x8A, 0x37, 0xB2, 0xBF, 0x37, 0xAD, 0x27, 0x09, 0xAE, 0xAF, 0x37, 0xAF, 0x3E, 0x37, 0xAF, 0xBD, 0x37, 0xAF, 0xAD, 0x3F, 0x97, 0xBC, 0x3F, 0xEB, 0xAC, 0x3F, 0xF5, 0xBC, 0x3F, 0xFA, 0xBE, 0x3F, 0xFD, 0x2F, 0x3F, 0xE5, 0xA7, 0x3F, 0xE9, 0x5F, 0x3F, 0xEE, 0xEE, 0x3E, 0xF1, 0xF3, 0x3E, 0xFF, 0xFD, 0x19, 0x3F, 0xFD, 0x1E, 0xFF, 0x80, 0x06, 0xFF, 0x9F, 0x02, 0xFF, 0x00 };
unsigned char lbl_80400760_p22[72] = { 0x3C, 0xFF, 0xE0, 0x18, 0xFF, 0xF8, 0x44, 0xE0, 0x3C, 0xA8, 0xDF, 0x7E, 0x7E, 0xA6, 0xFE, 0xF2, 0x5A, 0xFE, 0x7A, 0xBA, 0xFE, 0x3E, 0x7A, 0xFE, 0x9E, 0xFA, 0xFE, 0x1A, 0xFA, 0xEE, 0x1E, 0xF4, 0xEE, 0x1A, 0xEB, 0x92, 0x1E, 0xD7, 0xEE, 0x3E, 0xAF, 0xEE, 0x7A, 0x5F, 0xEE, 0xF2, 0xD3, 0xFE, 0x7C, 0x4B, 0xFE, 0x3B, 0xBB, 0xFE, 0x67, 0xC7, 0xFE, 0xDF, 0xFF, 0xFE, 0xDF, 0xFF, 0xFE, 0x00, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0x00, 0x7F, 0xF0 };
unsigned char lbl_804007A8_p22[72] = { 0xFF, 0xE0, 0x00, 0x80, 0x20, 0x7F, 0xBF, 0xA0, 0x40, 0xA0, 0x20, 0x5F, 0xAF, 0xE0, 0x5F, 0xA8, 0x00, 0x5F, 0xA8, 0x00, 0x5E, 0xA8, 0x00, 0x5E, 0xA8, 0x00, 0x5E, 0x88, 0x00, 0x5E, 0xF8, 0x00, 0x5E, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x40, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x40, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x40, 0x00, 0x00, 0x7F };
unsigned char lbl_804007F0_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0xC7, 0xFF, 0x00, 0x4C, 0x00, 0xFF, 0x59, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x57, 0xFF, 0x00, 0x57, 0x01, 0xFF, 0xD7, 0x7D, 0x80, 0x17, 0x45, 0xFF, 0x17, 0x45, 0x01, 0x97, 0x45, 0xFC, 0xD7, 0x45, 0xFE, 0x57, 0x45, 0xFF, 0x57, 0x45, 0x0F, 0x57, 0x45, 0xEF, 0x57, 0x45, 0x2F, 0x57, 0x45, 0xEF, 0x57, 0x7D, 0x0F, 0x57, 0x01, 0xFF, 0x57, 0xFF, 0xFE, 0x53, 0xFF, 0xFC, 0xD9, 0xFF, 0x01, 0x8C, 0x00, 0xFF, 0x07, 0xFF };
unsigned char lbl_80400838_p22[72] = { 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x30, 0x00, 0x00, 0x90, 0x00, 0x00, 0xD1, 0xFF, 0x07, 0xD3, 0x01, 0x8C, 0xD6, 0x7C, 0xD9, 0xD4, 0xFE, 0x53, 0xD5, 0xFF, 0x57, 0xD5, 0xC7, 0x57, 0xD5, 0xD7, 0x57, 0xD5, 0xD0, 0x57, 0xD5, 0xDF, 0xD7, 0xD5, 0xD0, 0x17, 0xD5, 0xDF, 0xD7, 0xD5, 0xD0, 0x57, 0xD5, 0xD7, 0x57, 0xD5, 0xC7, 0x57, 0xD5, 0xFF, 0x57, 0x94, 0xFE, 0x53, 0x36, 0x7C, 0xD9, 0x63, 0x01, 0x8C, 0xC1, 0xFF, 0x07 };
unsigned char lbl_80400880_p22[72] = { 0x00, 0x07, 0xFF, 0x00, 0x04, 0x01, 0x00, 0x05, 0xFD, 0x00, 0x04, 0x05, 0x00, 0x07, 0xF5, 0xFC, 0x00, 0x15, 0x06, 0x00, 0x15, 0xF3, 0x00, 0x15, 0xF9, 0x00, 0x15, 0xFD, 0x00, 0x11, 0x1D, 0x00, 0x1F, 0x5D, 0x00, 0x00, 0x41, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x40, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x41, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x1D, 0x00, 0x00, 0xFD, 0x00, 0x00, 0xF9, 0x00, 0x00, 0xF3, 0x00, 0x00, 0x06, 0x00, 0x00, 0xFC, 0x00, 0x00 };
unsigned char lbl_804008C8_p22[72] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0xC0, 0x00, 0x01, 0x9F, 0x00, 0x01, 0x3F, 0x00, 0x01, 0x7F, 0x00, 0x01, 0x71, 0x00, 0x01, 0x75, 0x00, 0x01, 0x74, 0x00, 0x01, 0x77, 0x00, 0x01, 0x74, 0xF8, 0x01, 0x77, 0x88, 0x01, 0x74, 0xA8, 0x01, 0x75, 0xA8, 0x01, 0x71, 0xA8, 0x01, 0x7F, 0xA8, 0x01, 0x3F, 0xAF, 0xE1, 0x9F, 0xA0, 0x20, 0xC0, 0xBF, 0xA0, 0x7F, 0x80, 0x20, 0x00, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400910_p22[72] = { 0x00, 0x00, 0x00, 0xC7, 0xF0, 0x1F, 0x64, 0x10, 0x30, 0x35, 0xD0, 0x67, 0x95, 0xD0, 0x4F, 0xD5, 0xD0, 0x5F, 0xD5, 0xD0, 0x5C, 0xD5, 0xD0, 0x5D, 0x15, 0xD0, 0x5D, 0xF5, 0xD0, 0x5D, 0x05, 0xD0, 0x5C, 0xF5, 0xD0, 0x5F, 0x15, 0xD0, 0x5F, 0xD5, 0xDF, 0x5F, 0xD5, 0xC1, 0x5C, 0xD5, 0xFD, 0x5D, 0x95, 0xFD, 0x5D, 0x35, 0xFD, 0x5D, 0x64, 0x01, 0x41, 0xC7, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400958_p22[72] = { 0x00, 0x00, 0x00, 0xF0, 0x7F, 0xF1, 0x18, 0xC0, 0x13, 0xCD, 0x9F, 0xD6, 0xE5, 0x3F, 0xD4, 0xF5, 0x7F, 0xD5, 0x75, 0x70, 0x15, 0x75, 0x77, 0xF5, 0x75, 0x70, 0x65, 0x75, 0x7F, 0x35, 0x75, 0x3F, 0x94, 0xF5, 0x9F, 0xD6, 0xF4, 0xC1, 0xD3, 0xF5, 0xFD, 0xD7, 0x75, 0x01, 0xD4, 0x75, 0x7F, 0xD5, 0x75, 0x7F, 0x95, 0x75, 0x7F, 0x35, 0x05, 0x00, 0x64, 0xFD, 0xFF, 0xC7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_804009A0_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x40, 0x00, 0x7F, 0x40, 0x00, 0xFF, 0x40, 0x00, 0xFF, 0x40, 0x00, 0xC0, 0x40, 0x00, 0xDF, 0xC0, 0x00, 0xC1, 0x80, 0x00, 0xFC, 0xC0, 0x00, 0xFE, 0x40, 0x00, 0x7F, 0x40, 0x1F, 0x07, 0x40, 0x11, 0xF7, 0x40, 0x15, 0x07, 0x40, 0x15, 0xFF, 0x40, 0x15, 0xFE, 0x40, 0x15, 0xFC, 0xC7, 0xF5, 0x01, 0x84, 0x05, 0xFF, 0x05, 0xFD, 0x00, 0x04, 0x01, 0x00, 0x07, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_804009E8_p22[72] = { 0xFF, 0xE0, 0x00, 0x80, 0x21, 0xFC, 0xBF, 0xA3, 0x04, 0xA0, 0x26, 0x75, 0xAF, 0xE4, 0xF5, 0xA8, 0x05, 0xF5, 0xA8, 0x05, 0xF5, 0xA8, 0x05, 0xF5, 0xA8, 0x04, 0x75, 0x88, 0x07, 0x75, 0xF8, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x04, 0x00, 0x01, 0xFC };
unsigned char lbl_80400A30_p22[72] = { 0x00, 0x00, 0x00, 0x7F, 0xF8, 0x3F, 0xC0, 0x0C, 0x60, 0x9F, 0xE6, 0xCF, 0x3F, 0xF2, 0x9F, 0x7F, 0xFA, 0xBF, 0x70, 0x3A, 0xB8, 0x77, 0xBA, 0xBB, 0x74, 0xBA, 0xBA, 0x74, 0xBA, 0xBA, 0x74, 0xBA, 0xBA, 0x74, 0xBA, 0xBA, 0x74, 0xBA, 0xBA, 0x74, 0xBA, 0xBA, 0x74, 0xBA, 0xBA, 0x74, 0xBA, 0xBA, 0x74, 0xBA, 0xBA, 0x77, 0xBA, 0xBB, 0x70, 0x3A, 0xB8, 0x7F, 0xFA, 0xBF, 0x3F, 0xF2, 0x9F, 0x9F, 0xE6, 0xCF, 0xC0, 0x0C, 0x60, 0x7F, 0xF8, 0x3F };
unsigned char lbl_80400A78_p22[72] = { 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x06, 0x00, 0x00, 0xF3, 0x00, 0x00, 0xF9, 0x00, 0x00, 0xFD, 0x1F, 0xF0, 0x1D, 0x30, 0x18, 0xDD, 0x67, 0xCD, 0x5D, 0x4F, 0xE5, 0x5D, 0x5F, 0xF5, 0x5D, 0x5C, 0x75, 0x5D, 0x5D, 0x75, 0x5D, 0x5D, 0x05, 0x5D, 0x5D, 0xFD, 0x5D, 0x5D, 0x01, 0x5D, 0x5D, 0xFD, 0x5D, 0x5D, 0x05, 0xDD, 0x5D, 0x75, 0x1D, 0x5C, 0x75, 0xFD, 0x5F, 0xF5, 0xF9, 0x4F, 0xE5, 0xF3, 0x67, 0xCD, 0x06, 0x30, 0x18, 0xFC, 0x1F, 0xF0 };
unsigned char lbl_80400AC0_p22[72] = { 0x00, 0x07, 0xFF, 0x00, 0x04, 0x01, 0x00, 0x05, 0xFD, 0x00, 0x04, 0x05, 0x00, 0x07, 0xF5, 0x7F, 0xC0, 0x15, 0xC0, 0x60, 0x15, 0x9F, 0x30, 0x15, 0x3F, 0x90, 0x15, 0x7F, 0xD0, 0x11, 0x71, 0xD0, 0x1F, 0x75, 0xD0, 0x00, 0x74, 0x10, 0x00, 0x77, 0xF0, 0x00, 0x74, 0x00, 0x00, 0x77, 0xF0, 0x00, 0x74, 0x10, 0x00, 0x75, 0xD0, 0x00, 0x71, 0xD0, 0x00, 0x7F, 0xD0, 0x00, 0x3F, 0x90, 0x00, 0x9F, 0x30, 0x00, 0xC0, 0x60, 0x00, 0x7F, 0xC0, 0x00 };
unsigned char lbl_80400B08_p22[72] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0xC0, 0x00, 0x01, 0x9F, 0x00, 0x01, 0x3F, 0x00, 0x01, 0x7F, 0x00, 0x01, 0x71, 0x00, 0x01, 0x75, 0x00, 0x01, 0x74, 0x00, 0x01, 0x77, 0x00, 0x01, 0x74, 0xF8, 0x01, 0x77, 0x88, 0x01, 0x74, 0xA8, 0x01, 0x75, 0xA8, 0x01, 0x71, 0xA8, 0x01, 0x7F, 0xA8, 0x01, 0x3F, 0xAF, 0xE1, 0x9F, 0xA0, 0x20, 0xC0, 0xBF, 0xA0, 0x7F, 0x80, 0x20, 0x00, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400B50_p22[72] = { 0x00, 0x00, 0x00, 0xC7, 0xF0, 0x1F, 0x64, 0x10, 0x30, 0x35, 0xD0, 0x67, 0x95, 0xD0, 0x4F, 0xD5, 0xD0, 0x5F, 0xD5, 0xD0, 0x5C, 0xD5, 0xD0, 0x5D, 0x15, 0xD0, 0x5D, 0xF5, 0xD0, 0x5D, 0x05, 0xD0, 0x5C, 0xF5, 0xD0, 0x5F, 0x15, 0xD0, 0x5F, 0xD5, 0xDF, 0x5F, 0xD5, 0xC1, 0x5C, 0xD5, 0xFD, 0x5D, 0x95, 0xFD, 0x5D, 0x35, 0xFD, 0x5D, 0x64, 0x01, 0x41, 0xC7, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400B98_p22[72] = { 0x00, 0x00, 0x00, 0xF0, 0x7F, 0xF1, 0x18, 0xC0, 0x13, 0xCD, 0x9F, 0xD6, 0xE5, 0x3F, 0xD4, 0xF5, 0x7F, 0xD5, 0x75, 0x70, 0x15, 0x75, 0x77, 0xF5, 0x75, 0x70, 0x65, 0x75, 0x7F, 0x35, 0x75, 0x3F, 0x94, 0xF5, 0x9F, 0xD6, 0xF4, 0xC1, 0xD3, 0xF5, 0xFD, 0xD7, 0x75, 0x01, 0xD4, 0x75, 0x7F, 0xD5, 0x75, 0x7F, 0x95, 0x75, 0x7F, 0x35, 0x05, 0x00, 0x64, 0xFD, 0xFF, 0xC7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400BE0_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x40, 0x00, 0x7F, 0x40, 0x00, 0xFF, 0x40, 0x00, 0xFF, 0x40, 0x00, 0xC0, 0x40, 0x00, 0xDF, 0xC0, 0x00, 0xC1, 0x80, 0x00, 0xFC, 0xC0, 0x00, 0xFE, 0x40, 0x00, 0x7F, 0x40, 0x1F, 0x07, 0x40, 0x11, 0xF7, 0x40, 0x15, 0x07, 0x40, 0x15, 0xFF, 0x40, 0x15, 0xFE, 0x40, 0x15, 0xFC, 0xC7, 0xF5, 0x01, 0x84, 0x05, 0xFF, 0x05, 0xFD, 0x00, 0x04, 0x01, 0x00, 0x07, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400C28_p22[72] = { 0xFF, 0xE0, 0x00, 0x80, 0x21, 0xFD, 0xBF, 0xA3, 0x05, 0xA0, 0x26, 0x75, 0xAF, 0xE4, 0xF5, 0xA8, 0x05, 0xF5, 0xA8, 0x05, 0xF5, 0xA8, 0x05, 0xF5, 0xA8, 0x04, 0x75, 0x88, 0x07, 0x75, 0xF8, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x74, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x75, 0x00, 0x01, 0x05, 0x00, 0x01, 0xFD };
unsigned char lbl_80400C70_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x3F, 0x00, 0x02, 0x60, 0x7F, 0xFA, 0xCF, 0x7F, 0xFA, 0x9F, 0x7F, 0xFA, 0xBF, 0x78, 0x02, 0xB8, 0x7B, 0xFE, 0xBB, 0x7A, 0x00, 0xBA, 0x7B, 0xF8, 0xBA, 0x78, 0x0C, 0xBA, 0x7F, 0xE6, 0xBA, 0x7F, 0xF2, 0xBA, 0x7F, 0xFA, 0xBA, 0x00, 0x7A, 0xBA, 0xFF, 0x7A, 0xBA, 0x01, 0x7A, 0xBA, 0xFF, 0x7A, 0xBB, 0x00, 0x7A, 0xB8, 0x7F, 0xFA, 0xBF, 0x7F, 0xF2, 0x9F, 0x7F, 0xE6, 0xCF, 0x00, 0x0C, 0x60, 0xFF, 0xF8, 0x3F };
unsigned char lbl_80400CB8_p22[72] = { 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x06, 0x00, 0x00, 0xF3, 0x00, 0x00, 0xF9, 0x00, 0x00, 0xFD, 0x1F, 0xF0, 0x1D, 0x30, 0x18, 0xDD, 0x67, 0xCD, 0x5D, 0x4F, 0xE5, 0x5D, 0x5F, 0xF5, 0x5D, 0x5C, 0x75, 0x5D, 0x5D, 0x75, 0x5D, 0x5D, 0x05, 0x5D, 0x5D, 0xFD, 0x5D, 0x5D, 0x01, 0x5D, 0x5D, 0xFD, 0x5D, 0x5D, 0x05, 0xDD, 0x5D, 0x75, 0x1D, 0x5C, 0x75, 0xFD, 0x5F, 0xF5, 0xF9, 0x4F, 0xE5, 0xF3, 0x67, 0xCD, 0x06, 0x30, 0x18, 0xFC, 0x1F, 0xF0 };
unsigned char lbl_80400D00_p22[72] = { 0x00, 0x07, 0xFF, 0x00, 0x04, 0x01, 0x00, 0x05, 0xFD, 0x00, 0x04, 0x05, 0x00, 0x07, 0xF5, 0x7F, 0xC0, 0x15, 0xC0, 0x60, 0x15, 0x9F, 0x30, 0x15, 0x3F, 0x90, 0x15, 0x7F, 0xD0, 0x11, 0x71, 0xD0, 0x1F, 0x75, 0xD0, 0x00, 0x74, 0x10, 0x00, 0x77, 0xF0, 0x00, 0x74, 0x00, 0x00, 0x77, 0xF0, 0x00, 0x74, 0x10, 0x00, 0x75, 0xD0, 0x00, 0x71, 0xD0, 0x00, 0x7F, 0xD0, 0x00, 0x3F, 0x90, 0x00, 0x9F, 0x30, 0x00, 0xC0, 0x60, 0x00, 0x7F, 0xC0, 0x00 };
unsigned char lbl_80400D48_p22[72] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0xC0, 0x00, 0x01, 0x9F, 0x00, 0x01, 0x3F, 0x00, 0x01, 0x7F, 0x00, 0x01, 0x71, 0x00, 0x01, 0x75, 0x00, 0x01, 0x74, 0x00, 0x01, 0x77, 0x00, 0x01, 0x74, 0xF8, 0x01, 0x77, 0x88, 0x01, 0x74, 0xA8, 0x01, 0x75, 0xA8, 0x01, 0x71, 0xA8, 0x01, 0x7F, 0xA8, 0x01, 0x3F, 0xAF, 0xE1, 0x9F, 0xA0, 0x20, 0xC0, 0xBF, 0xA0, 0x7F, 0x80, 0x20, 0x00, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400D90_p22[72] = { 0x00, 0x00, 0x00, 0xC7, 0xF0, 0x1F, 0x64, 0x10, 0x30, 0x35, 0xD0, 0x67, 0x95, 0xD0, 0x4F, 0xD5, 0xD0, 0x5F, 0xD5, 0xD0, 0x5C, 0xD5, 0xD0, 0x5D, 0x15, 0xD0, 0x5D, 0xF5, 0xD0, 0x5D, 0x05, 0xD0, 0x5C, 0xF5, 0xD0, 0x5F, 0x15, 0xD0, 0x5F, 0xD5, 0xDF, 0x5F, 0xD5, 0xC1, 0x5C, 0xD5, 0xFD, 0x5D, 0x95, 0xFD, 0x5D, 0x35, 0xFD, 0x5D, 0x64, 0x01, 0x41, 0xC7, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400DD8_p22[72] = { 0x00, 0x00, 0x00, 0xF0, 0x7F, 0xF1, 0x18, 0xC0, 0x13, 0xCD, 0x9F, 0xD6, 0xE5, 0x3F, 0xD4, 0xF5, 0x7F, 0xD5, 0x75, 0x70, 0x15, 0x75, 0x77, 0xF5, 0x75, 0x70, 0x65, 0x75, 0x7F, 0x35, 0x75, 0x3F, 0x94, 0xF5, 0x9F, 0xD6, 0xF4, 0xC1, 0xD3, 0xF5, 0xFD, 0xD7, 0x75, 0x01, 0xD4, 0x75, 0x7F, 0xD5, 0x75, 0x7F, 0x95, 0x75, 0x7F, 0x35, 0x05, 0x00, 0x64, 0xFD, 0xFF, 0xC7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400E20_p22[72] = { 0x00, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x40, 0x00, 0x7F, 0x40, 0x00, 0xFF, 0x40, 0x00, 0xFF, 0x40, 0x00, 0xC0, 0x40, 0x00, 0xDF, 0xC0, 0x00, 0xC1, 0x80, 0x00, 0xFC, 0xC0, 0x00, 0xFE, 0x40, 0x00, 0x7F, 0x40, 0x1F, 0x07, 0x40, 0x11, 0xF7, 0x40, 0x15, 0x07, 0x40, 0x15, 0xFF, 0x40, 0x15, 0xFE, 0x40, 0x15, 0xFC, 0xC7, 0xF5, 0x01, 0x84, 0x05, 0xFF, 0x05, 0xFD, 0x00, 0x04, 0x01, 0x00, 0x07, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char lbl_80400E68_p22[72] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x80, 0x1F, 0xF3, 0x80, 0x1F, 0xE3, 0xFF, 0x9F, 0xE7, 0xFF, 0x9F, 0xC7, 0xFF, 0x9F, 0x8C, 0xFF, 0x9F, 0x1C, 0xFF, 0x9E, 0x1F, 0xFF, 0x9C, 0x1F, 0xFF, 0x98, 0x9F, 0xFF, 0x91, 0x9F, 0xFF, 0x93, 0x9F, 0xFF, 0x97, 0x9F, 0xFF, 0x9F, 0x9F, 0xFF, 0x9F, 0x9F, 0xFF, 0x9F, 0x9F, 0xFF, 0x9F, 0x9F, 0xFF, 0x9F, 0x9F, 0x80, 0x1F, 0x9E, 0x80, 0x1F, 0x9E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
unsigned char lbl_80400EB0_p22[72] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xE7, 0xFF, 0xFC, 0xE7, 0xFF, 0xFC, 0xE7, 0xFF, 0xC0, 0x20, 0xFE, 0x40, 0x20, 0xFE, 0x78, 0x67, 0x1E, 0x78, 0x67, 0x06, 0x70, 0x27, 0x86, 0x70, 0x27, 0xFE, 0x70, 0x9F, 0xFE, 0x70, 0x99, 0xFE, 0x64, 0x99, 0xFE, 0x64, 0xC9, 0xFE, 0x64, 0xC9, 0xFE, 0x64, 0xF8, 0xFE, 0x64, 0xF8, 0xFC, 0x44, 0xFC, 0xF8, 0xCC, 0xFC, 0xF1, 0xCC, 0xF8, 0x03, 0xCC, 0xE1, 0x07, 0xCC, 0xE3, 0xFF, 0xFC, 0xE7, 0xFF, 0xFF, 0xFF };
unsigned char lbl_80400EF8_p22[72] = { 0xFF, 0xFF, 0xFF, 0xF9, 0x24, 0xFF, 0xF9, 0x24, 0xFF, 0xF9, 0x24, 0xFF, 0x0F, 0x3C, 0x01, 0x00, 0x00, 0x01, 0x30, 0x00, 0xE7, 0x3F, 0x3C, 0xE7, 0x39, 0x24, 0xE7, 0x39, 0x24, 0xE7, 0x39, 0x27, 0xE7, 0x3F, 0xFF, 0x27, 0x3C, 0xFF, 0x27, 0x30, 0x01, 0x27, 0x30, 0x01, 0x27, 0x3C, 0xE7, 0x07, 0x3C, 0xE7, 0x07, 0x7C, 0xE7, 0x8F, 0x3C, 0x47, 0x87, 0x1E, 0x0F, 0x03, 0x8F, 0x0C, 0x31, 0xCC, 0x00, 0x79, 0xEC, 0x60, 0xFD, 0xFF, 0xFF, 0xFF };
unsigned char lbl_80400F40_p22[72] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0xFC, 0xF1, 0x8F, 0xF1, 0xE7, 0xE7, 0xE7, 0xCF, 0xF3, 0xCF, 0xCF, 0xF1, 0xCF, 0x8F, 0xF1, 0x8F, 0x8F, 0xFF, 0x8F, 0x8F, 0xFF, 0x8F, 0x8F, 0xFF, 0x8F, 0x8F, 0xFF, 0x8F, 0x8F, 0xFF, 0x8F, 0x8F, 0xFF, 0x8F, 0x8F, 0xFF, 0x8F, 0x8F, 0xF1, 0x8F, 0x8F, 0xF1, 0x8F, 0xCF, 0xF3, 0xCF, 0xCF, 0xF3, 0xCF, 0xE7, 0xE7, 0xE7, 0xF1, 0x8F, 0xF1, 0xFC, 0x3F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
unsigned char lbl_80400F88_p22[72] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xC7, 0x1F, 0x8F, 0xC7, 0x0F, 0xE7, 0xC7, 0x07, 0xF3, 0xC7, 0x07, 0xF3, 0xC7, 0x13, 0xF1, 0xC7, 0x13, 0xF1, 0xC7, 0x19, 0xF1, 0xC7, 0x19, 0xF1, 0xC7, 0x1C, 0xF1, 0xC7, 0x1C, 0xF1, 0xC7, 0x1E, 0xF1, 0xC7, 0x1E, 0xF1, 0xC7, 0x1F, 0xF1, 0xC7, 0x1F, 0xF1, 0xC7, 0x1F, 0xF3, 0xC7, 0x1F, 0xF3, 0xC7, 0x1F, 0xE7, 0xC7, 0x1F, 0x8F, 0xC7, 0x1F, 0x3F, 0xC7, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
unsigned char lbl_80400FD0_p22[72] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF1, 0xF8, 0x1F, 0xF1, 0xE3, 0xC7, 0xF1, 0xCF, 0xF3, 0xF1, 0x8F, 0xF1, 0xF1, 0x8F, 0xF1, 0xF1, 0x8F, 0xF1, 0xF1, 0x8F, 0xFF, 0xF1, 0xC7, 0xFF, 0xF1, 0xE0, 0xFF, 0xF1, 0xFC, 0x3F, 0x71, 0xFF, 0x8F, 0x71, 0xFF, 0xE3, 0x31, 0xFF, 0xF1, 0x31, 0x8F, 0xF1, 0x91, 0x8F, 0xF1, 0x81, 0x8F, 0xF1, 0xC1, 0xCF, 0xF1, 0xC1, 0xCF, 0xF3, 0xE1, 0xE3, 0xC7, 0xF1, 0xF8, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
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
