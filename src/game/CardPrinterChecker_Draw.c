/*
 * Formatted text helpers and CardPrinterChecker status drawing,
 * 0x8008F5D4..0x8008FA2C.
 *
 * The two Format variants destroy their TexMgr local on unwind (dtor_800869D0)
 * but never call it on the normal path, so their extab entries are emitted by
 * hand; tools/extab_order.json restores the address order.
 */

typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];
typedef __va_list va_list;

#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))
#define va_end(ap) ((void)0)

typedef struct TexMgr {
    unsigned char pad00[0x18];
    int mode; /* 0x18 */
    unsigned char pad1C[0x20 - 0x1C];
    int texId; /* 0x20 */
    unsigned char pad24[0x234 - 0x24];
} TexMgr;

extern const char *lbl_803135E8[][2][2]; /* status error labels [code - 1][isJapanese][line] */
extern const char lbl_806D3404[3]; /* "%s" */
extern const char lbl_806D3420[5]; /* "RPS:" */
extern const char lbl_806D342C[5]; /* "%02x" */

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern int vsprintf(char *, const char *, va_list);
extern unsigned long strlen(const char *s);
int isJapanese(void);
void TexMgr_Init(void *self);
void TexMgr_SetTexture(void *self, const char *text, ...);
void fn_801F93EC(void *self, float x, float y);
void *fn_801F8E58(void);
void fn_801F8A34(void *mgr, void *self, int flag);
void dtor_800869D0(void *self);
void *Sci2Card_Singleton_Get(void);
unsigned char Sci2Card_IsStatusOkNonTerm(void *card);
unsigned char Sci2Card_IsRetryExhausted(void *card);
unsigned char Sci2Card_IsStatus2Two(void *card);
unsigned char Sci2Card_IsStatus2Three(void *card);
unsigned char Sci2Card_IsStatus2Five(void *card);

void TexMgr_DrawText_Format_Variant3(int mode, const char *fmt, float x, float y, ...)
{
    va_list args;
    char buf[0x200];
    TexMgr tm;
    int enabled;

    TexMgr_Init(&tm);
    tm.mode = mode;
    tm.texId = -1;
    fn_801F93EC(&tm, x, y);
    enabled = OSDisableInterrupts();
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    OSRestoreInterrupts(enabled);
    TexMgr_SetTexture(&tm, buf);
    fn_801F8A34(fn_801F8E58(), &tm, 0);
}

void TexMgr_DrawText_Format_Variant4(int mode, const char *fmt, float x, float y, ...);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_TexMgr_DrawText_Format_Variant3 = { 0x10880000, 0x00000094, 0x00160010, 0x00000000, 0x82000274, (void *)&dtor_800869D0 };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TexMgr_DrawText_Format_Variant3 = {
    (void *)&TexMgr_DrawText_Format_Variant3, 0x0000010C, (void *)&extab_TexMgr_DrawText_Format_Variant3
};

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_TexMgr_DrawText_Format_Variant4 = { 0x10880000, 0x00000094, 0x00160010, 0x00000000, 0x82000274, (void *)&dtor_800869D0 };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TexMgr_DrawText_Format_Variant4 = {
    (void *)&TexMgr_DrawText_Format_Variant4, 0x0000010C, (void *)&extab_TexMgr_DrawText_Format_Variant4
};

#pragma exceptions on

void CardPrinterChecker_DrawStatusErrorLabel(int code)
{
    int x;
    const char *label;

    if (code != 0) {
        code--;
        x = (24 - strlen(lbl_803135E8[code][isJapanese()][0])) * 4 + 232;
        label = lbl_803135E8[code][isJapanese()][0];
        TexMgr_DrawText_Format_Variant4(0, lbl_806D3404, x, 200.0f, label);
        TexMgr_DrawText_Format_Variant4(0, lbl_806D3404, 308.0f, 296.0f, lbl_803135E8[code][isJapanese()][1]);
    }
}

int Sci2Card_ClassifyStatusToCode(void)
{
    void *card = Sci2Card_Singleton_Get();

    if (Sci2Card_IsStatusOkNonTerm(card) == 1) {
        return 0;
    }
    if (Sci2Card_IsRetryExhausted(card) == 1) {
        return 1;
    }
    if (Sci2Card_IsStatus2Two(card) == 1) {
        return 2;
    }
    if (Sci2Card_IsStatus2Three(card) == 1) {
        return 3;
    }
    return Sci2Card_IsStatus2Five(card) == 1 ? 4 : 5;
}

void CardPrinterChecker_DrawResponseStatusBytes(unsigned char s1, unsigned char s2, unsigned char s3)
{
    TexMgr_DrawText_Format_Variant4(0, lbl_806D3420, 156.0f, 76.0f);
    TexMgr_DrawText_Format_Variant4(0, lbl_806D342C, 284.0f, 76.0f, s1);
    TexMgr_DrawText_Format_Variant4(0, lbl_806D342C, 368.0f, 76.0f, s2);
    TexMgr_DrawText_Format_Variant4(0, lbl_806D342C, 452.0f, 76.0f, s3);
}

#pragma exceptions reset

void TexMgr_DrawText_Format_Variant4(int mode, const char *fmt, float x, float y, ...)
{
    va_list args;
    char buf[0x200];
    TexMgr tm;
    int enabled;

    TexMgr_Init(&tm);
    tm.mode = mode;
    tm.texId = -1;
    fn_801F93EC(&tm, x, y);
    enabled = OSDisableInterrupts();
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    OSRestoreInterrupts(enabled);
    TexMgr_SetTexture(&tm, buf);
    fn_801F8A34(fn_801F8E58(), &tm, 0);
}
