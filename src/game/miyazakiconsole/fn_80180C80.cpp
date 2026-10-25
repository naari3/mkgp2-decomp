#include "game/miyazakiconsole/miyazakiconsole.h"

struct ConsoleInput {
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual bool IsTriggered(int mask);
    virtual bool IsHeld(int mask);
};

extern "C" {
extern unsigned int lbl_806D1664;
extern unsigned int lbl_806D1668;
void *GetInputManager();
ConsoleInput *InputMgr_GetPlayer(void *, int);
}

#define REPEAT() (++lbl_806D1668 > 15 && lbl_806D1668 % 5 == 0)

extern "C" unsigned int fn_80180C80(Menu *m) {
    ConsoleInput *in = InputMgr_GetPlayer(GetInputManager(), 0);

    if (in->IsTriggered(0x10)) {
        lbl_806D1664 = 0;
        lbl_806D1668 = 0;
        return 5;
    } else if (in->IsHeld(0x10)) {
        if (REPEAT()) {
            lbl_806D1664 = 0;
            return 5;
        }
    } else if (in->IsTriggered(0x20)) {
        lbl_806D1664 = 0;
        lbl_806D1668 = 0;
        return 6;
    } else if (in->IsHeld(0x20)) {
        if (REPEAT()) {
            lbl_806D1664 = 0;
            return 6;
        }
    } else if (in->IsTriggered(0x40)) {
        if (m->count != 0) {
            if (m->cursor != 0) {
                m->cursor--;
            } else {
                m->cursor = m->count - 1;
            }
            lbl_806D1664 = 0;
            lbl_806D1668 = 0;
            return 7;
        }
    } else if (in->IsHeld(0x40)) {
        if (m->count != 0 && REPEAT()) {
            if (m->cursor != 0) {
                m->cursor--;
            } else {
                m->cursor = m->count - 1;
            }
            lbl_806D1664 = 0;
            return 7;
        }
    } else if (in->IsTriggered(0x80)) {
        if (m->count != 0) {
            if (m->cursor < m->count - 1) {
                m->cursor++;
            } else {
                m->cursor = 0;
            }
            lbl_806D1664 = 0;
            lbl_806D1668 = 0;
            return 8;
        }
    } else if (in->IsHeld(0x80)) {
        if (m->count != 0 && REPEAT()) {
            if (m->cursor < m->count - 1) {
                m->cursor++;
            } else {
                m->cursor = 0;
            }
            lbl_806D1664 = 0;
            return 8;
        }
    } else if (in->IsTriggered(0x1)) {
        lbl_806D1664 = 0;
        lbl_806D1668 = 0;
        return 1;
    } else if (in->IsTriggered(0x2)) {
        lbl_806D1664 = 0;
        lbl_806D1668 = 0;
        return 2;
    } else if (in->IsTriggered(0x4)) {
        lbl_806D1664 = 0;
        lbl_806D1668 = 0;
        return 3;
    } else if (in->IsTriggered(0x8)) {
        lbl_806D1664 = 0;
        lbl_806D1668 = 0;
        return 4;
    } else if (in->IsTriggered(0x100)) {
        lbl_806D1664 = 0;
        lbl_806D1668 = 0;
        return 9;
    } else if (in->IsTriggered(0x200)) {
        lbl_806D1664 = 0;
        lbl_806D1668 = 0;
        return 10;
    } else if (in->IsTriggered(0x400)) {
        lbl_806D1664 = 0;
        lbl_806D1668 = 0;
        return 11;
    } else {
        lbl_806D1668 = 0;
    }
    return 0;
}
