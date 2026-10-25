typedef struct ResCtrl {
    int id;
    int pad4;
    int mode;
    unsigned char padc[0x48 - 0xc];
    int a;
    int b;
    int c;
    unsigned char pad54[0x58 - 0x54];
} ResCtrl;

typedef struct SprMgr {
    int id;
    unsigned char pad4[0x38 - 0x4];
    ResCtrl rc;
} SprMgr;

extern int lbl_806D16E8;
extern SprMgr lbl_8067897C;
extern int lbl_80496BD8[24];
extern void *lbl_80678A0C[];
extern void fn_80121E10(ResCtrl *rc);
extern void *SpriteHandle_CreateDefault(ResCtrl *rc, void *dst);

static inline int IsSpecial(int id) {
    int i;
    for (i = 0; i < 24; i++) {
        if (id == lbl_80496BD8[i]) {
            return 1;
        }
    }
    return 0;
}

void fn_801A1174(int id, void *dst, short a, short b, short c) {
    ResCtrl *rc;
    int i;
    if (lbl_806D16E8 < 199) {
        lbl_8067897C.id = id;
        rc = &lbl_8067897C.rc;
        fn_80121E10(rc);
        rc->id = id;
        if (a > 0 || b > 0 || c > 0) {
            lbl_8067897C.rc.mode = 4;
        }
        for (i = 0; i < 24; i++) {
            if (id == lbl_80496BD8[i]) {
                lbl_8067897C.rc.a = 1;
                lbl_8067897C.rc.b = 4;
                lbl_8067897C.rc.c = 1;
                goto done;
            }
        }
        lbl_8067897C.rc.a = 1;
        lbl_8067897C.rc.b = 4;
        lbl_8067897C.rc.c = 5;
    done:
        lbl_80678A0C[lbl_806D16E8] = SpriteHandle_CreateDefault(rc, dst);
    }
}
