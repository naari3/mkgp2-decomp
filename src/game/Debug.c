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

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern int vsprintf(char *, const char *, va_list);

extern unsigned char lbl_80598A60[];

void DebugOutput_Stub(const char *msg, ...);

void OSPanic_Stub(const char *file, int line, const char *msg, ...) {
}

void DebugOutput_Stub(const char *msg, ...) {
}

void DebugPrintf(const char *fmt, ...) {
    char buf[1028];
    va_list args;
    int enabled;

    if (lbl_80598A60[0x2A] != 0) {
        enabled = OSDisableInterrupts();
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        va_end(args);
        OSRestoreInterrupts(enabled);
        DebugOutput_Stub(buf);
    }
}
