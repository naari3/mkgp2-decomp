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

int Sprite_SetAnimTime(SpriteAnim *s, float t) {
    if (s->data == 0) {
        return 0;
    }
    if (t >= s->data->length) {
        return 0;
    }
    s->time = t;
    return 1;
}
