#ifndef GAME_TYPES_HUDPART_H
#define GAME_TYPES_HUDPART_H

struct HudPart {
    virtual ~HudPart() {}
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void SetDelay(int n) = 0;
    virtual void _keyH();
    int delay;
    HudPart() : delay(-1) {}
};

#endif /* GAME_TYPES_HUDPART_H */
