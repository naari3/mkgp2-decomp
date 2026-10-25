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

extern int fn_801A13BC(SpriteAnimData *d);

int fn_801A0550(SpriteAnim *s) {
    SpriteAnimData *d = s->data;
    if (d != 0) {
        return 0;
    }
    return fn_801A13BC(d);
}
