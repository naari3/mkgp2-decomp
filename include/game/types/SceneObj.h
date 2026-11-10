#ifndef GAME_TYPES_SCENEOBJ_H
#define GAME_TYPES_SCENEOBJ_H

struct SceneObj {
    char pad00[0x20];
    SceneObj(int a, int b, int c, int d, int e);
    ~SceneObj();
    void Update();
    void Draw();
};

#endif /* GAME_TYPES_SCENEOBJ_H */
