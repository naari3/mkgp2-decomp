/* 0x8017FF10: printf into the debug console's character grid at (x, y).
 * Characters outside the grid are clipped. */

typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];
typedef __va_list va_list;

#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))

extern char *lbl_806D1650;
extern unsigned int lbl_806CFB98;
extern unsigned int lbl_806CFB9C;
extern char lbl_80677D18[0x100];
extern const char lbl_80376E10[];
extern const char lbl_80376E24[];
extern int vsprintf(char *buf, const char *fmt, va_list ap);
extern void OSPanic(const char *file, int line, const char *msg, ...);

static inline void Console_PutRow(char *row, int x, const char *s, int n) {
    int i;
    const char *p = s;
    for (i = 0; i < n; i++) {
        int c = i + x;
        if (c >= 0 && (unsigned int)c < lbl_806CFB98) row[c] = *p;
        p++;
    }
}

void fn_8017FF10(int x, int y, const char *fmt, ...) {
    va_list ap;
    int n;
    if (lbl_806D1650 == 0) return;
    if (y < 0 || (unsigned int)y >= lbl_806CFB9C) return;
    va_start(ap, fmt);
    n = vsprintf(lbl_80677D18, fmt, ap);
    if (n >= 0x100) OSPanic(lbl_80376E10, 0x4c, lbl_80376E24);
    Console_PutRow(lbl_806D1650 + y * lbl_806CFB98, x, lbl_80677D18, n);
}
