#ifndef GAME_TYPES_CLMAPEFFECTPARTS_H
#define GAME_TYPES_CLMAPEFFECTPARTS_H

struct clMapEffectParts {
    virtual ~clMapEffectParts() {}
    virtual void Update();
    virtual void Draw();
    virtual void Enable(int on);
    clMapEffectParts() {}
};

#endif /* GAME_TYPES_CLMAPEFFECTPARTS_H */
