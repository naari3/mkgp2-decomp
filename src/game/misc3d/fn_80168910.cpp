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

struct Buf256 {
    char c[0x100];
};

struct TextManager {
    TextManager();
    ~TextManager() {}
    unsigned char pad0[0x18];
    int x18;
    unsigned char pad1c[0x234 - 0x1c];
};

extern "C" {
extern int vsprintf(char *, const char *, va_list);
extern void TexMgr_SetTexture(TextManager *tex, const char *str, ...);
extern void fn_801F93EC(TextManager *tex, float x, float y);
extern void fn_801F93D0(TextManager *tex, float x, float y);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *ctx, TextManager *tex, void *dst);
extern const char lbl_8036AA90[0x100];
}

extern "C" void fn_80168910(void *dst, const char *fmt, float x, float y, float sx, float sy, ...) {
    TextManager tex;
    va_list args;
    Buf256 buf = *(const Buf256 *)lbl_8036AA90;

    va_start(args, sy);
    vsprintf(buf.c, fmt, args);
    va_end(args);
    TexMgr_SetTexture(&tex, buf.c);
    tex.x18 = 1;
    fn_801F93EC(&tex, x, y);
    fn_801F93D0(&tex, sx, sy);
    fn_801F8A34(fn_801F8E58(), &tex, dst);
}
