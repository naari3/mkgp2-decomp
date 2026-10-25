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

typedef struct Remap {
    int from;
    int to;
} Remap;

typedef struct GameCfg {
    unsigned char pad[0x20];
    signed char region;
} GameCfg;

extern GameCfg lbl_80598A60;
extern Remap lbl_806CFD00[1];
extern const char *lbl_80496428[];
extern const float lbl_806D97D8;
extern SpriteAnimData *fn_801A1494(const char *name, void *a, void *b);

static inline int Remap_(int id) {
    int i;
    if (!lbl_80598A60.region) {
        return id;
    }
    for (i = 0; lbl_806CFD00[i].from != -1; i++) {
        if (id == lbl_806CFD00[i].from) {
            return lbl_806CFD00[i].to;
        }
    }
    return id;
}

int fn_801A0584(SpriteAnim *s, int id, void *a, void *b) {
    if (s->data != 0) {
        return 0;
    }
    if (id >= 0x1ec) {
        return 0;
    }
    id = Remap_(id);
    s->name = lbl_80496428[id];
    if (s->name == 0) {
        return 0;
    }
    s->data = fn_801A1494(s->name, a, b);
    if (s->data == 0) {
        return 0;
    }
    s->time = lbl_806D97D8;
    s->flag = 0;
    return 1;
}
