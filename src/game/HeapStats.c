/* Boot-state refresh, heap stat dump and a couple of small destructors.
 * The format strings live in a shared .rodata pool that starts at
 * lbl_802E8F48; the compiler keeps the pool base in a register. */
#pragma cplusplus on

struct Word2 {
    unsigned int w[2];
};

struct BootState {
    unsigned short f00;
    unsigned short f02;
    unsigned short f04;
    unsigned short f06;
    Word2 f08;
    unsigned char f10;
    unsigned char f11;
    unsigned short f12;
    unsigned short f14;
    unsigned short f16;
    Word2 f18;
    Word2 f20;
    unsigned int f28;
    Word2 f2C;
    Word2 f34;
    unsigned int f3C;
    Word2 f40;
    Word2 f48;
    Word2 f50;
    unsigned int f58;
    unsigned int f5C;

    BootState &operator=(const BootState &o)
    {
        f00 = o.f00;
        f02 = o.f02;
        f04 = o.f04;
        f06 = o.f06;
        f08 = o.f08;
        f10 = o.f10;
        f11 = o.f11;
        f12 = o.f12;
        f14 = o.f14;
        f16 = o.f16;
        f18 = o.f18;
        f20 = o.f20;
        f28 = o.f28;
        f2C = o.f2C;
        f34 = o.f34;
        f3C = o.f3C;
        f40 = o.f40;
        f48 = o.f48;
        f50 = o.f50;
        f58 = o.f58;
        f5C = o.f5C;
        return *this;
    }
};

struct BootTimer {
    unsigned int lastTick;
};

extern "C" {
void DebugPrintf(const char *fmt, ...);
void MemoryHeap_GetStats(void *heap, int *total, int *used, int *count);
unsigned int OSGetTick(void);
void MemoryManager_TimedFree(void *p);
void fn_801DB68C(void *p, int flag);
void fn_802554DC(void);
BootState *fn_80293BBC(void);

extern const float SAFE;
extern void *lbl_806CF010;
extern BootTimer *lbl_806D0F9C;
extern int lbl_806D0FA4;
extern signed char lbl_806D0FA8;
extern void *lbl_806D1880;
extern const float lbl_806D2294;
extern const float lbl_806D22B4;
extern const char lbl_802E8F48[];
extern char lbl_802E9650[];
extern BootState lbl_80594080;
}

static inline unsigned char BootState_IsDue(void)
{
    BootTimer *timer = lbl_806D0F9C;
    if ((float)((OSGetTick() - timer->lastTick) * 8 /
                (*(unsigned int *)0x800000F8 / 4 / 125000)) /
            lbl_806D2294 >= SAFE) {
        return 1;
    }
    return 0;
}

extern "C" void BootStateStruct_RefreshIfDue(void)
{
    if (!lbl_806D0FA8) {
        lbl_806D0FA4 = 0;
        lbl_806D0FA8 = 1;
    }
    if (BootState_IsDue() == 1) {
        BootTimer *timer;
        fn_802554DC();
        lbl_80594080 = *fn_80293BBC();
        timer = lbl_806D0F9C;
        timer->lastTick = OSGetTick();
    }
}

extern "C" int HeapStats_DumpForTag(const char *tag)
{
    char *str = (char *)lbl_802E8F48;
    int total;
    int used;
    int count;

    DebugPrintf(&str[0x6ac]);
    MemoryHeap_GetStats(lbl_806CF010, &total, &used, &count);
    total /= 1024;
    used /= 1024;
    DebugPrintf(str + 0x6d4, total, tag, (float)total * lbl_806D22B4);
    DebugPrintf(str + 0x6ec, used);
    DebugPrintf(str + 0x6fc, count);
    return 0;
}

extern "C" int isJapanese(void)
{
    return 0;
}

extern "C" void DebugLog_LvIdMsg(int lv, int id, const char *msg)
{
    DebugPrintf(lbl_802E9650, lv, id, msg);
}

extern "C" void *dtor_8002F910(void *self, short flag)
{
    if (self) {
        if (lbl_806D1880 == 0) {
            fn_801DB68C(lbl_806D1880, 1);
            lbl_806D1880 = 0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void *dtor_8002F978(void *self, short flag)
{
    if (self && flag > 0) {
        MemoryManager_TimedFree(self);
    }
    return self;
}
