#ifndef GAME_CREDITHUD_H
#define GAME_CREDITHUD_H

/*
 * Coin / credit counter HUD (0x80218B5C..0x80218F40): an animated sprite
 * (ctor Sprite_InitWithAnim, dtor Sprite_Destroy) whose digit frames are
 * patched through the short pointers returned by fn_801A0310.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct AnimSprite {
    int x0;
    int layer;
    int x8;
    float x;
    float y;
    char pad14[0x20 - 0x14];
    float alpha;
    char pad24[0x30 - 0x24];
    AnimSprite(int res, int a, int b);
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
    ~AnimSprite();
};

template <class T> struct OwnPtr {
    T *p;
    OwnPtr() {}
    OwnPtr(T *q) : p(q) {}
    void operator=(T *q) { p = q; }
    ~OwnPtr() throw() { delete p; }
};

struct CreditHud {
    int x0;
    OwnPtr<AnimSprite> sprite;
    short *coin10;
    short *coin1;
    short *per10;
    short *per1;
    short *slash;
    CreditHud(int mode);
    ~CreditHud();
    void Update();
};

#endif
