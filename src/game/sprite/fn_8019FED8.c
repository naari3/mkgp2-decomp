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

extern const float lbl_806D97D8;

float fn_8019FED8(SpriteAnim *s) {
    if (s->data == 0) {
        return lbl_806D97D8;
    }
    return s->time;
}
