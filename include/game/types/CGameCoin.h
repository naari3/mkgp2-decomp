#ifndef GAME_TYPES_CGAMECOIN_H
#define GAME_TYPES_CGAMECOIN_H

struct BossKoopa;
struct CoinHsdObj;
struct CoinScene3D;
struct CoinShellSet;
struct CoinVObj;
struct DefeatDemo;

struct CoinCourseParams;
struct CoinJObj;

/* Update state; offsets are relative to CGameCoin. Names inferred from use. */
struct CGameCoinTail {
    int demoFrame;             /* 0x80 */
    struct CoinCourseParams *course; /* 0x84 */
    int lane;                  /* 0x88 */
    int laneTarget;            /* 0x8C */
    float laneT;               /* 0x90 */
    float jumpT;               /* 0x94 */
    float hitT;                /* 0x98 */
    int shellWait;             /* 0x9C */
    float yaw;                 /* 0xA0 */
    void *spinA;               /* 0xA4 */
    void *spinB;               /* 0xA8 */
    void *spinC;               /* 0xAC */
    struct CoinJObj *wheelA;    /* 0xB0 */
    struct CoinJObj *wheelB;    /* 0xB4 */
    float wheelAngleA;         /* 0xB8 */
    float wheelAngleB;         /* 0xBC */
};

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
    /* 0x018 */ union {
        unsigned char pad18[0x30];
        float kartMtx[3][4];
    };
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
    /* 0x080 */ union {
        unsigned char pad80[0x40];
        struct CGameCoinTail update;
    };
    /* 0x0C0 */ struct CoinVObj *particles;
};

#endif /* GAME_TYPES_CGAMECOIN_H */
