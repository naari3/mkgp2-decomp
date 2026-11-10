#ifndef GAME_TYPES_COINSHOTBASE_H
#define GAME_TYPES_COINSHOTBASE_H

/* Declare before including (each user already does): CoinShot, clNormal3D */

struct CoinShotBase {
    virtual ~CoinShotBase();
    clNormal3D *model;
    clNormal3D *trailModel;
    int xC;
    int x10;
    CoinShot shots[6];
    int trailCount;
    CoinShotBase(const char *modelFile, const char *trailFile);
};

#endif /* GAME_TYPES_COINSHOTBASE_H */
