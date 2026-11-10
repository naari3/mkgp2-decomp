#ifndef GAME_TYPES_CGAMECOIN_H
#define GAME_TYPES_CGAMECOIN_H

struct BossKoopa;
struct CoinHsdObj;
struct CoinScene3D;
struct CoinShellSet;
struct CoinVObj;
struct DefeatDemo;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CGameCoin CGameCoin;
struct CGameCoin {
    /* 0x000 */ void *vt;
    /* 0x004 */ unsigned char pad_004[0x4];
    /* 0x008 */ void *input;
    /* 0x00C */ void *driver;
    /* 0x010 */ void *effects;
    /* 0x014 */ void *audio;
    /* 0x018 */ unsigned char pad18[0x30];
    /* 0x048 */ void *m48;
    /* 0x04C */ struct CoinShellSet *shellSet;
    /* 0x050 */ void *lakitu;
    /* 0x054 */ void *env;
    /* 0x058 */ struct CoinScene3D *scene;
    /* 0x05C */ void *goalCam;
    /* 0x060 */ struct CoinVObj *m60;
    /* 0x064 */ struct CoinHsdObj *lights;
    /* 0x068 */ void *hud;
    /* 0x06C */ struct BossKoopa *koopa;
    /* 0x070 */ void *m70;
    /* 0x074 */ void *m74;
    /* 0x078 */ struct DefeatDemo *defeatDemo;
    /* 0x07C */ unsigned char active;
    /* 0x07D */ unsigned char m7D;
    /* 0x07E */ unsigned char demoMode;
    /* 0x07F */ unsigned char defeated;
    /* 0x080 */ unsigned char pad80[0x40];
    /* 0x0C0 */ struct CoinVObj *particles;
};

#endif /* GAME_TYPES_CGAMECOIN_H */
