#ifndef GAME_TYPES_HUDINPUT_H
#define GAME_TYPES_HUDINPUT_H

class HudInput {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual float v18();
    virtual void v1C();
    virtual unsigned char Pressed(int mask);
};

#endif /* GAME_TYPES_HUDINPUT_H */
