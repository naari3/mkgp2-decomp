#ifndef GAME_TYPES_CLMAPEFFECT_H
#define GAME_TYPES_CLMAPEFFECT_H

struct clMapEffect {
    virtual ~clMapEffect() {}
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffect() {}
};

#endif /* GAME_TYPES_CLMAPEFFECT_H */
