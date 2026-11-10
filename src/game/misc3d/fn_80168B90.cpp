#ifdef __MWERKS__
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
#else
#include <stdarg.h>
#endif

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
extern const char lbl_8036A690[0x100];
}

static inline unsigned int PackColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

extern "C" void fn_80168B90(void *dst, const char *fmt, float x, float y, float red, float green, float blue, float alpha, ...) {
    TextManager tex;
    va_list args;
    Buf256 buf = *(const Buf256 *)lbl_8036A690;

    va_start(args, alpha);
    vsprintf(buf.c, fmt, args);
    va_end(args);
    TexMgr_SetTexture(&tex, buf.c);
    tex.x18 = 0;
    fn_801F93EC(&tex, x, y);
    fn_801F93D0(&tex, lbl_806D8A0C, lbl_806D8A0C);
    tex.color = PackColor(lbl_806D8A10 * red, lbl_806D8A10 * green, lbl_806D8A10 * blue, lbl_806D8A10 * alpha);
    fn_801F8A34(fn_801F8E58(), &tex, dst);
}
