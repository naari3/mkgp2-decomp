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
extern short lbl_80678D2C[];
extern void PreloadResource(short id);

int fn_801A13BC(SpriteAnimData *d) {
    int i;
    if (d == 0) {
        return 0;
    }
    for (i = 0; d->params[i] != -1; i++) {
        int n = g_spriteSystemInited;
        unsigned char isNew = 1;
        if (n != -1) {
            int j;
            for (j = 0; j < n; j++) {
                if (lbl_80678D2C[j] == d->params[i]) {
                    isNew = 0;
                    break;
                }
            }
        }
        if (isNew) {
            if (n != -1) {
                lbl_80678D2C[n] = d->params[i];
                g_spriteSystemInited++;
            }
            PreloadResource(d->params[i]);
        }
    }
    return 1;
}
