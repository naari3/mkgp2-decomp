#ifndef GAME_TYPES_SCENEBASE_H
#define GAME_TYPES_SCENEBASE_H

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    bool done;
    unsigned char pad5[3]; /* tail padding, named so a derived class cannot use it */
    SceneBase() : done(false) {}
};

#endif /* GAME_TYPES_SCENEBASE_H */
