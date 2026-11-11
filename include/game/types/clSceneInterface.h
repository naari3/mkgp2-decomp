#ifndef GAME_TYPES_CLSCENEINTERFACE_H
#define GAME_TYPES_CLSCENEINTERFACE_H

struct clSceneInterface {
    virtual ~clSceneInterface() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
    unsigned char align[3];
    clSceneInterface() : done(false) {}
};

#endif /* GAME_TYPES_CLSCENEINTERFACE_H */
