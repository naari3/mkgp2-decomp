/* clMnSetting and clMnCardInfo: original deferred card-settings unit. */
#include "game/types/size_t.h"
#include "game/singleton.h"
void *operator new(size_t);
void operator delete(void *) throw();
typedef unsigned char u8;
extern "C" {
void DebugPrintf(const char *, ...);
unsigned char ServiceValue_Get(void);
unsigned char ServiceEnable_Get(void);
void fn_801F98CC(void);
void fn_80209FE8(void);
void fn_801F9888(void);
void fn_80209FA4(void);
void wcsncpy(void *, const void *, int);
extern char *g_pInputState;
}
struct clMnCardInfo {
    virtual ~clMnCardInfo();
    int x4;
    int x8;
    u8 xc;
    u8 a1[6]; u8 b1[6]; u8 e1[6]; u8 c1[6][4]; u8 d1[6][4]; u8 f1[6][4];
    u8 a2[6]; u8 b2[6]; u8 c2[6][4]; u8 d2[6][4];
    u8 a3[6]; u8 b3[6]; u8 c3[6][4]; u8 d3[6][4];
    u8 a4[6]; u8 b4[6]; u8 c4[6][4]; u8 d4[6][4]; u8 f4[6][4];
    int x134[6];
    char pad14c[0xC];
    short x158[6];
    int x164;
    clMnCardInfo() { Init(); }
    void Init();
    void CopyName(void *dst);
    void Reset();
    void IncCardCheckCount();
};
struct clMnSetting : clMnCardInfo {
    int field168;
    int field16C;
    int field170;
    int field174;
    int field178;
    int field17C;
    int field180;
    int pad184;
    int field188;
    int field18C;
    int field190;
    unsigned char flag194;
    unsigned char flag195;
    unsigned char flag196;
    unsigned char flag197;
    clMnSetting() : flag194(0), flag195(0), flag196(0), flag197(0) {
        DebugPrintf("clMnSetting _ct\n");
        fn_801F98CC();
        fn_80209FE8();
        field168 = 0;
        field16C = 0;
        field170 = 0;
        field174 = 1;
        field178 = 0;
        field17C = 0;
        field180 = 0;
        field188 = 0x2B;
        field18C = 0x2D;
        field190 = 0x32;
    }
    virtual ~clMnSetting();
};

extern "C" clMnSetting *lbl_806D19D8;
clMnCardInfo::~clMnCardInfo() {}
extern "C" int fn_801FE858(void) {
    char *p;
    p = SINGLETON_INSTANCE(g_pInputState);
    return *(int *)(p + 0x14);
}
void clMnCardInfo::Init() {
    int i, j;
    x4 = 0;
    x8 = 0;
    xc = 0;
    for (i = 0; i < 6; i++) {
        a1[i] = 0; b1[i] = 0;
        a2[i] = 0; b2[i] = 0;
        a3[i] = 0; b3[i] = 0;
        a4[i] = 0; b4[i] = 0;
        for (j = 0; j < 4; j++) {
            c1[i][j] = 0; d1[i][j] = 0;
            c2[i][j] = 0; d2[i][j] = 0;
            c3[i][j] = 0; d3[i][j] = 0;
            c4[i][j] = 0; d4[i][j] = 0;
        }
        for (j = 0; j < 4; j++) {
            f1[i][j] = 0; f4[i][j] = 0;
        }
    }
    for (int k = 0; k < 6; k++) {
        i = k;
        a1[i] = 1; a2[i] = 1; a3[i] = 1; a4[i] = 1;
        if (ServiceEnable_Get() && !ServiceValue_Get()) {
            c1[i][0] = 1; c2[i][0] = 1; c3[i][0] = 1; c4[i][0] = 1;
        } else {
            c1[i][0] = 1; c1[i][1] = 1;
            c2[i][0] = 1; c2[i][1] = 1;
            c3[i][0] = 1; c3[i][1] = 1;
            c4[i][0] = 1; c4[i][1] = 1;
        }
    }
    for (i = 0; i < 6; i++) {
        e1[i] = 1;
        for (j = 0; j < 4; j++) f1[i][j] = 1;
    }
    if (ServiceEnable_Get() && !ServiceValue_Get()) {
        a1[5] = 0; a2[5] = 0; a3[5] = 0; a4[5] = 0;
    }
    for (i = 0; i < 6; i++) x134[i] = 0;
    for (i = 0; i < 6; i++) x158[i] = 0;
    x164 = 0;
}
void clMnCardInfo::IncCardCheckCount() {
    int prev = x4;
    x4 = prev + 1;
    DebugPrintf("clMnCardInfo::incCardCheckCount() %d->%d\n", prev, x4);
}
void clMnCardInfo::Reset() {}
void clMnCardInfo::CopyName(void *dst) { wcsncpy(dst, x158, 5); }
clMnSetting::~clMnSetting() { fn_80209FA4(); fn_801F9888(); DebugPrintf("clMnSetting _dt\n"); }
extern "C" clMnSetting *fn_801FE404(void) {
    if (lbl_806D19D8 == 0) {
        lbl_806D19D8 = new clMnSetting;
    }
    return lbl_806D19D8;
}

extern "C" void fn_801FE3BC(void) {
    if (lbl_806D19D8) {
        delete lbl_806D19D8;
        lbl_806D19D8 = 0;
    }
}
