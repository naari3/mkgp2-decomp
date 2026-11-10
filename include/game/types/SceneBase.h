#ifndef GAME_TYPES_SCENEBASE_H
#define GAME_TYPES_SCENEBASE_H

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    bool done;
    SceneBase() : done(false) {}
};

#endif /* GAME_TYPES_SCENEBASE_H */
