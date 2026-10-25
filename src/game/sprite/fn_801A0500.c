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

extern void fn_801A12F0(SpriteAnimData *d);

int fn_801A0500(SpriteAnim *s) {
    if (s->data == 0) {
        return 0;
    }
    fn_801A12F0(s->data);
    s->data = 0;
    s->name = 0;
    return 1;
}
