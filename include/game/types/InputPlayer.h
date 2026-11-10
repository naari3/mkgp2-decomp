#ifndef GAME_TYPES_INPUTPLAYER_H
#define GAME_TYPES_INPUTPLAYER_H

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
};

#endif /* GAME_TYPES_INPUTPLAYER_H */
