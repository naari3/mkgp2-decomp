#ifndef GAME_TYPES_CLGAMECOINBASE_H
#define GAME_TYPES_CLGAMECOINBASE_H

/* The owning unit declares CoinShot and clNormal3D before this header. */
struct clJobRunner;
extern "C" void Object_DtorWithGXSync(void *, int);

struct clCGameCoinBase {
    virtual ~clCGameCoinBase();
    static clCGameCoinBase *CheckType(clJobRunner *);
    virtual void Update()=0;
    virtual void Draw()=0;
    clNormal3D *model;
    clNormal3D *trailModel;
    int xC;
    int x10;
    CoinShot shots[6];
    int trailCount;
    clCGameCoinBase(const char *modelFile, const char *trailFile);
};

#endif /* GAME_TYPES_CLGAMECOINBASE_H */
