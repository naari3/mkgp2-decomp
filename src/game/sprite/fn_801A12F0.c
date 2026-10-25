typedef struct SpriteAnimData {
    unsigned char pad[0x14];
    float length;
    void *frames;
    short *params;
} SpriteAnimData;

typedef struct SpriteAnim {
    unsigned char flag;
    unsigned char pad1[7];
    float time;
    float c[6];
    const char *name;
    SpriteAnimData *data;
} SpriteAnim;

extern int g_spriteSystemInited;
extern int lbl_806D16EC;
extern int lbl_806D16E8;
extern int lbl_80678A0C[200];
extern void fn_80120A08(short id);
extern void MemoryManager_Free(void *p);
extern void SpriteHandle_Destroy(int h);

static inline void ReleaseParams(SpriteAnimData *d) {
    int i;
    if (d != 0 && g_spriteSystemInited == -1) {
        for (i = 0; d->params[i] != -1; i++) {
            fn_80120A08(d->params[i]);
        }
    }
}

int fn_801A12F0(SpriteAnimData *d) {
    if (d == 0) {
        return 0;
    }
    ReleaseParams(d);
    MemoryManager_Free(d);
    if (--lbl_806D16EC == 0) {
        int i;
        for (i = 0; i < 200; i++) {
            if (lbl_80678A0C[i] != -1) {
                SpriteHandle_Destroy(lbl_80678A0C[i]);
            }
            lbl_80678A0C[i] = -1;
        }
        lbl_806D16E8 = 0;
    }
    return 1;
}
