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

typedef struct TextEntry {
    int x;
    int y;
    unsigned char color;
    char pad09[3];
    float scale;
    char text[0x74];
} TextEntry;

typedef struct DisplayContext {
    char pad00[0x88];
    TextEntry *entries;
    int count;
} DisplayContext;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern int vsprintf(char *, const char *, va_list);
extern char *strncpy(char *, const char *, unsigned long);

void DrawText(DisplayContext *ctx, int x, int y, unsigned char color, float scale, const char *fmt, ...) {
    char buf[0x74];
    va_list args;
    int enabled;

    if (ctx->count < 0x7F) {
        enabled = OSDisableInterrupts();
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        va_end(args);
        OSRestoreInterrupts(enabled);
        ctx->entries[ctx->count].x = x;
        ctx->entries[ctx->count].y = y;
        ctx->entries[ctx->count].color = color;
        ctx->entries[ctx->count].scale = scale;
        strncpy(ctx->entries[ctx->count].text, buf, sizeof(buf));
        ctx->count++;
    }
}
