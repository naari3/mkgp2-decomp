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

struct GXColor {
    unsigned int r : 8;
    unsigned int g : 8;
    unsigned int b : 8;
    unsigned int a : 8;
};

struct Buf256 {
    unsigned short c[0x100];
};

struct TextManager {
    TextManager();
    ~TextManager() {}
    unsigned char pad0[0x18];
    int x18;
    unsigned char pad1c[0x20 - 0x1c];
    unsigned int color;
    unsigned char pad24[0x234 - 0x24];
};

extern "C" {
extern int vswprintf(unsigned short *, unsigned int, const unsigned short *, va_list);
extern void fn_801F9014(TextManager *tex, const unsigned short *str, ...);
extern void TexMgr_SetTexture(TextManager *tex, const char *str, ...);
extern void fn_801F93EC(TextManager *tex, float x, float y);
extern void fn_801F93D0(TextManager *tex, float x, float y);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *ctx, TextManager *tex, void *dst);
extern const float lbl_806D8A0C;
extern const float lbl_806D8A10;
extern const unsigned short lbl_8036AF90[0x100];
}

extern "C" void fn_801680A0(void *dst, const unsigned short *fmt, float x, float y, ...) {
    TextManager tex;
    va_list args;
    Buf256 buf = *(const Buf256 *)lbl_8036AF90;

    va_start(args, y);
    vswprintf(buf.c, 0x100, fmt, args);
    va_end(args);
    fn_801F9014(&tex, buf.c);
    tex.x18 = 0;
    fn_801F93EC(&tex, x, y);
    fn_801F93D0(&tex, lbl_806D8A0C, lbl_806D8A0C);
    fn_801F8A34(fn_801F8E58(), &tex, dst);
}
