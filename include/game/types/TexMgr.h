#ifndef GAME_TYPES_TEXMGR_H
#define GAME_TYPES_TEXMGR_H

struct TexMgr {
    unsigned char pad0[0x18];
    int mode;
    unsigned char pad1C[4];
    unsigned int color;
    unsigned char pad24[0x208];
    float fade;
    TexMgr();
    ~TexMgr() {}
    void SetColor(unsigned int c) {
        mode = 1;
        color = c;
    }
};

#endif /* GAME_TYPES_TEXMGR_H */
