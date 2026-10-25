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

extern unsigned char IsDisplayModeEnabled(void);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern int vsprintf(char *, const char *, va_list);
extern void DebugOutput_Stub(const char *msg, ...);

extern unsigned char lbl_80598A60[];
extern char lbl_805960F0[0x2010];
extern const char lbl_806D22D8[3];

void DebugTextOutput(int channel, const char *fmt, ...) {
    va_list args;
    int enabled;

    if (IsDisplayModeEnabled() && lbl_80598A60[0x2A] != 0) {
        enabled = OSDisableInterrupts();
        va_start(args, fmt);
        vsprintf(lbl_805960F0, fmt, args);
        va_end(args);
        OSRestoreInterrupts(enabled);
        DebugOutput_Stub(lbl_806D22D8, lbl_805960F0);
    }
}

void OverlayText(int layer, int x, int y, const char *fmt, ...) {
    va_list args;
    int enabled;

    if (IsDisplayModeEnabled() && lbl_80598A60[0x2A] != 0) {
        enabled = OSDisableInterrupts();
        va_start(args, fmt);
        vsprintf(lbl_805960F0, fmt, args);
        va_end(args);
        OSRestoreInterrupts(enabled);
    }
}
