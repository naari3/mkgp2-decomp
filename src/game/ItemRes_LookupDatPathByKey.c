typedef struct ItemResKey {
    int key;
    int pad;
} ItemResKey;

typedef struct ItemResPath {
    const char *path;
    int pad;
} ItemResPath;

extern const ItemResKey lbl_80324364[0xF5];
extern const ItemResPath lbl_80323BB4[0xF6];

static inline int ItemRes_FindKey(int key)
{
    int i;

    for (i = 0; i < 0xF5; i++) {
        if (key == lbl_80324364[i].key) {
            return i;
        }
    }
    return 0xF5;
}

const char *ItemRes_LookupDatPathByKey(int key)
{
    return lbl_80323BB4[ItemRes_FindKey(key)].path;
}

void calc_title_params(void *unused, unsigned short *code, unsigned char *sub,
                       unsigned char title, unsigned char lo, int idx)
{
    unsigned char hi;

    if (title == 0x42) {
        hi = 0xF;
    } else {
        hi = (title >> 4) & 0xF;
        lo = (int)title % 16;
    }
    *code = (idx & 0x3F) | ((hi & 0xF) << 6);
    *sub = lo & 0xF;
}

void TitleDecode(void *unused, unsigned char *title, unsigned char *sub, unsigned char *idx,
                 unsigned int code, int lo)
{
    unsigned int hi = (code >> 6) & 0xF;
    unsigned char c = code & 0x3F;
    unsigned char l = lo & 0xF;

    if (hi == 0xF) {
        *title = 0x42;
        *sub = l;
        *idx = c;
        return;
    }
    *title = l + ((unsigned char)hi << 4);
    *sub = 0;
    *idx = c;
}
