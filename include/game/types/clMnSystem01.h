#ifndef GAME_TYPES_CLMNSYSTEM01_H
#define GAME_TYPES_CLMNSYSTEM01_H

/* Private class family view: explicit tail padding preserves the MWCC base
 * layout when a host compiler reuses non-POD base tail padding. */
struct clSceneInterface {
    virtual ~clSceneInterface() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    bool done;
    unsigned char align[3];
    clSceneInterface() : done(false) {}
};
struct clEzTopInterface : clSceneInterface {
    virtual void Destroy();
    int f08, f0C, f10, f14;
    char pad18[0x28 - 0x18];
    int f28;
    int pad2C;
    int f30[3];
    int chara, pad40, mode, f48;
    char pad4C[0x5C - 0x4C];
    clEzTopInterface();
    ~clEzTopInterface() {}
};
struct clMnSystem01 : clEzTopInterface {
    virtual ~clMnSystem01();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    clSceneInterface *task;
    clMnSystem01();
};
#endif

