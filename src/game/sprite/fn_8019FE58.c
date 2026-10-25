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

extern const char lbl_80381098[];

const char *fn_8019FE58(SpriteAnim *s) {
    if (s->data == 0) {
        return lbl_80381098;
    }
    return s->name;
}
