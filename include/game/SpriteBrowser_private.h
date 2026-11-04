#ifndef SPRITE_BROWSER_PRIVATE_H
#define SPRITE_BROWSER_PRIVATE_H
struct BrowserInput {
    virtual void v0();
    virtual void v1();
    virtual float axis();
    virtual void v3();
    virtual float right();
    virtual float left();
    virtual unsigned char pressed(int);
};
struct BrowserSprite {
    char pad0[0xC];
    float x, y;
    void SetPos(float px, float py) { x = px; y = py; }
};
struct SpriteBrowser {
    void *vtable;
    int animation;
    int repeat;
    int fieldC;
    BrowserSprite *sprite;
};
extern "C" {
void *GetInputManager();
BrowserInput *InputMgr_GetPlayer(void *, int);
void OverlayText(int, int, int, const char *, ...);
unsigned char fn_8019FF50(BrowserSprite *);
void fn_801A0004(BrowserSprite *);
void fn_8011FA98();
}
#endif
