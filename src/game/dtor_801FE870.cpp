/* clMnSetting / clMnCardInfo helpers (0x801FE4D0..0x801FE8B8): clMnSetting dtor,
 * card-info counters and the service-menu state block reset. GC/2.6 like the
 * surrounding g6 TUs. */

typedef unsigned char u8;
extern "C" {
void DebugPrintf(const char *, ...);
void MemoryManager_TimedFree(void *);
unsigned char ServiceValue_Get(void);
unsigned char ServiceEnable_Get(void);
void fn_801F9888(void);
void fn_80209FA4(void);
void wcsncpy(void *, const void *, int);
extern char *g_pInputState;
extern char lbl_803BFF98[];
extern char lbl_803BFFAC[];
extern void *lbl_804EC1AC[];
extern void *lbl_804EC1B8[];
}

struct S {
    void *vt;
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
};

extern "C" {
void *fn_801FE4D0(S *self, short flag) {
    if (self != 0) {
        self->vt = lbl_804EC1AC;
        fn_80209FA4();
        fn_801F9888();
        DebugPrintf(lbl_803BFF98);
        if (self != 0) {
            self->vt = lbl_804EC1B8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801FE554(S *self, void *dst) { wcsncpy(dst, self->x158, 5); }
void fn_801FE584(void) {}
void fn_801FE588(S *self) {
    int prev = self->x4;
    self->x4 = prev + 1;
    DebugPrintf(lbl_803BFFAC, prev, self->x4);
}

void fn_801FE5C8(S *self) {
    int i, j;
    self->x4 = 0;
    self->x8 = 0;
    self->xc = 0;
    for (i = 0; i < 6; i++) {
        self->a1[i] = 0; self->b1[i] = 0;
        self->a2[i] = 0; self->b2[i] = 0;
        self->a3[i] = 0; self->b3[i] = 0;
        self->a4[i] = 0; self->b4[i] = 0;
        for (j = 0; j < 4; j++) {
            self->c1[i][j] = 0; self->d1[i][j] = 0;
            self->c2[i][j] = 0; self->d2[i][j] = 0;
            self->c3[i][j] = 0; self->d3[i][j] = 0;
            self->c4[i][j] = 0; self->d4[i][j] = 0;
        }
        for (j = 0; j < 4; j++) {
            self->f1[i][j] = 0; self->f4[i][j] = 0;
        }
    }
    for (int k = 0; k < 6; k++) {
        i = k;
        self->a1[i] = 1; self->a2[i] = 1; self->a3[i] = 1; self->a4[i] = 1;
        if (ServiceEnable_Get() && !ServiceValue_Get()) {
            self->c1[i][0] = 1; self->c2[i][0] = 1; self->c3[i][0] = 1; self->c4[i][0] = 1;
        } else {
            self->c1[i][0] = 1; self->c1[i][1] = 1;
            self->c2[i][0] = 1; self->c2[i][1] = 1;
            self->c3[i][0] = 1; self->c3[i][1] = 1;
            self->c4[i][0] = 1; self->c4[i][1] = 1;
        }
    }
    for (i = 0; i < 6; i++) {
        self->e1[i] = 1;
        for (j = 0; j < 4; j++) self->f1[i][j] = 1;
    }
    if (ServiceEnable_Get() && !ServiceValue_Get()) {
        self->a1[5] = 0; self->a2[5] = 0; self->a3[5] = 0; self->a4[5] = 0;
    }
    for (i = 0; i < 6; i++) self->x134[i] = 0;
    for (i = 0; i < 6; i++) self->x158[i] = 0;
    self->x164 = 0;
}

int fn_801FE858(void) {
    char *p;
    if ((p = g_pInputState) == 0) p = 0;
    return *(int *)(p + 0x14);
}

#pragma exceptions on
void *dtor_801FE870(void *self, short flag) {
    if (self != 0) {
        *(void ***)self = lbl_804EC1B8;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
}
