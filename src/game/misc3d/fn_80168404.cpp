typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];
typedef __va_list va_list;

#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))
#define va_end(ap)        ((void)0)

typedef struct Buf256 {
    char c[0x100];
} Buf256;

#include "game/types/TextManager.h"

extern "C" {
extern int vsprintf(char *, const char *, va_list);
extern void TexMgr_SetTexture(TextManager *tex, const char *str, ...);
extern void fn_801F93EC(TextManager *tex, float x, float y);
extern void fn_801F93D0(TextManager *tex, float x, float y);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *ctx, TextManager *tex, void *dst);
extern const float lbl_806D8A0C;
extern const float lbl_806D8A10;
extern const char lbl_8036AD90[0x100];
}

extern "C" void fn_80168404(void *dst, const char *fmt, float x, float y, float sx, float sy, float alpha, ...) {
    TextManager tex;
    va_list args;
    Buf256 buf = *(const Buf256 *)lbl_8036AD90;

    va_start(args, alpha);
    vsprintf(buf.c, fmt, args);
    va_end(args);
    TexMgr_SetTexture(&tex, buf.c);
    tex.x18 = 1;
    fn_801F93EC(&tex, x, y);
    fn_801F93D0(&tex, sx, sy);
    tex.color = __rlwimi(-0x100, (unsigned char)(int)(lbl_806D8A10 * alpha), 0, 24, 31);
    fn_801F8A34(fn_801F8E58(), &tex, dst);
}
