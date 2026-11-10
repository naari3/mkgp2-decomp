#ifndef CUP_TILE_STATE_PRIVATE_H
#define CUP_TILE_STATE_PRIVATE_H

struct TileSprite {
    char opaque[0xC];
    float x, y, sx, sy;
    char tail[0x14];
    TileSprite(int, int, int);
    void Position(float px, float py) { x = px; y = py; }
    void Scale(float s) { sx = s; sy = s; }
};

extern "C" {
void Sprite_SetupAnim(TileSprite *, int, int, int);
void Sprite_SetAnimParam(TileSprite *, int, int);
void fn_801A0550(TileSprite *);
void fn_8019FF6C(TileSprite *, int);
extern const float lbl_806D9C70, lbl_806D9C80, lbl_806D9C84, lbl_806D9C88;
extern const float lbl_806D9D28, lbl_806D9D38, lbl_806D9D3C, lbl_806D9D40;
extern int g_cupId;
}

struct CupTileSlot {
    int state, timer, frame;
    TileSprite *sprite;
};
struct CupTileOwner {
    char opaque[0x20];
    CupTileSlot slots[9];
    char opaqueB0[0x68];
    unsigned char mode;
    char opaque119[0x3B];
    unsigned char unlock154, unlock155;
};
struct CupTileInfo { short id, sub; float x, y; };
extern "C" CupTileInfo clFlowCup_data_8049AD58[];

struct RoundTileSlot {
    int state, variant, timer, frame;
    TileSprite *sprite;
};
struct RoundTileOwner { char opaque[0x2C]; RoundTileSlot slots[5]; };
struct RoundTileParams { short id, alternate; };
struct RoundTileTable {
    CupTileInfo positions[4];
    RoundTileParams params[9][4];
    int animations[7][3];
    char gap114[8];
    short cups[2];
};
extern "C" RoundTileTable clFlowRound_data_8049AE70;
#endif
