/*
 * LampTest_Page @ 0x80070238..0x8007044C: the lamp test page. Owns a lamp
 * tester object (fn_801DAB7C ctor, virtual dtor) that lights the selected
 * lamp group while sub != -1.
 */
#include "game/TestMenuPage.h"

class LampTester {
public:
    LampTester(int mode);
    virtual ~LampTester();
    void Select(int group);
    void Update();
    void Draw();

    unsigned char data[8];
};


extern "C" {
extern MenuItem lbl_803FC7B0[];
void fn_80121210(void);
void SpriteHandlePool_GC(void);
}

#define LAMP(self) (*(LampTester **)((char *)(self) + 0x278))

#pragma exceptions on

extern "C" int LampTest_Page(TestPage *self, int phase)
{
    InputPlayer *pl;

    if (phase == 0) {
        self->cursor = 4;
        self->sub = -1;
        LAMP(self) = new LampTester(0);
        fn_80121210();
    }
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (self->sub == -1 && pl->Pressed(0x800)) {
            self->blink = 0x1F;
            if (++self->cursor > 4) {
                self->cursor = 0;
            }
        }
        if (pl->Pressed(0x1000)) {
            if (self->cursor == 4) {
                delete LAMP(self);
                LAMP(self) = 0;
                self->next = 0;
            }
            if (self->sub == -1) {
                self->sub = self->cursor;
                if (LAMP(self) != 0) {
                    LAMP(self)->Select(self->sub);
                }
            } else {
                self->sub = -1;
            }
        }
        if (LAMP(self) != 0) {
            LAMP(self)->Update();
        }
    }
    if (phase == 2) {
        if (self->sub == -1) {
            TestPage_DrawItems(self, lbl_803FC7B0, self->cursor + 1);
        } else if (LAMP(self) != 0) {
            LAMP(self)->Draw();
        }
        SpriteHandlePool_GC();
    }
    return 1;
}

#pragma exceptions reset
