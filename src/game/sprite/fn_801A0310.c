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

short *fn_801A0310(SpriteAnim *s, short key) {
    int i;
    SpriteAnimData *d = s->data;
    if (d == 0) {
        return 0;
    }
    for (i = 0; d->params[i] != -1; i++) {
        if (key == d->params[i]) {
            return &d->params[i];
        }
    }
    return 0;
}
