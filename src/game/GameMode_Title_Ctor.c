#pragma cplusplus on
void *operator new(unsigned long);
void operator delete(void *);

extern "C" {
extern void GameMode_BaseInit(void *);
extern char lbl_80419E3C[];  /* GameMode_Title vtable */
}

struct GameModeTitle {
    void *vtable;
    int field4;

    GameModeTitle() {
        GameMode_BaseInit(this);
        vtable = lbl_80419E3C;
        field4 = 0;
    }
};

#pragma exceptions on
extern "C" GameModeTitle *GameMode_Title_Ctor(void)
{
    return new GameModeTitle;
}
#pragma exceptions reset
#pragma cplusplus off
