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

int fn_801A024C(SpriteAnim *s) {
    if (s->data == 0) {
        return 0;
    }
    if (s->flag == 0 && s->time >= s->data->length) {
        return 0;
    }
    return 1;
}
