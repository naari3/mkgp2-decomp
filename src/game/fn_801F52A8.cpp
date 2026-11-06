#include "game/RaceConfig801FPrivate.h"
extern "C" {
int WrapInRange(int, int, int);
int fn_801F9868(void *, int, int);
int fn_801F9844(void *, int, int);
int fn_801F9820(void *, int, int);
signed char ItemClass_GetFlagByte0(int);
void fn_8023E1E4(MenuWidget *, int, int);
void fn_8023E324(MenuWidget *, int);
extern const float lbl_806DA688;
}
static inline void *CourseTable801F() {
    return fn_801F98CC();
}
extern "C" void fn_801F52A8(MenuScene *self) {
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    unsigned char pressed = input->Pressed(1);
    switch (self->state) {
    case 0:
        if (pressed == 1) {
            self->cup++;
            self->cup = WrapInRange(self->cup, 0, 16);
        }
        break;
    case 1:
        if (pressed == 1) {
            self->course++;
            self->course = WrapInRange(self->course, 0, 1);
        }
        break;
    case 2:
        if (pressed == 1) {
            self->round++;
            self->round = WrapInRange(self->round, 0, 1);
        }
        break;
    case 3:
        if (pressed == 1) {
            self->variant++;
            self->variant = WrapInRange(self->variant, 0, 3);
        }
        break;
    case 4:
        if (pressed == 1) {
            self->character++;
            self->character = WrapInRange(self->character, 0, 12);
        }
        break;
    case 5:
        if (pressed == 1) {
            self->kart++;
            self->kart = WrapInRange(self->kart, 0, 3);
        }
        break;
    case 6:
        if (pressed == 1) {
            self->mode++;
            self->mode = WrapInRange(self->mode, 0, 2);
        }
        break;
    case 7:
        if (pressed == 1) {
            self->itemCount++;
            self->itemCount = WrapInRange(self->itemCount, 0, 7);
        }
        break;
    case 8:
        if (pressed == 1) {
            if (self->gate == 0) self->gate = 1;
            else self->gate = 0;
        }
        break;
    case 9:
        if (pressed == 1) {
            if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(1) == 1) {
                self->roundIndex++;
                self->roundIndex = WrapInRange(self->roundIndex, 0, 7);
            }
            if (self->mode == 0) {
                self->course = fn_801F9868(CourseTable801F(), self->cup, self->roundIndex);
                self->variant = fn_801F9844(CourseTable801F(), self->cup, self->roundIndex);
                self->round = fn_801F9820(CourseTable801F(), self->cup, self->roundIndex);
            }
        }
        break;
    case 10:
        if (pressed == 1) {
            self->cc++;
            self->cc = WrapInRange(self->cc, 0, 2);
        }
        break;
    case 11:
        if (pressed == 1) {
            self->input = (void *)((int)self->input + 1);
            self->input = (void *)WrapInRange((int)self->input, 0, 2);
        }
        break;
    case 13: {
        bool backward;
        unsigned char held;
        unsigned char down;
        InputPlayer *player;
        player = InputMgr_GetPlayer(GetInputManager(), 0);
        down = player->Pressed(1);
        held = player->Held(1);
        backward = player->StickLeft() >= lbl_806DA688;
        if (down == 1) self->state2 = 0;
        if (held == 1) {
            if (self->state2 > 0) self->state2--;
            else {
                self->state2 = 10;
                do {
                    if (backward) {
                        self->items[0]--;
                        if (self->items[0] <= 1) self->items[0] = 276;
                    } else {
                        self->items[0]++;
                        if (self->items[0] >= 277) self->items[0] = 1;
                    }
                } while (ItemClass_GetFlagByte0(self->items[0]) == 0);
            }
        }
        break;
    }
    case 14: {
        bool backward;
        unsigned char held;
        unsigned char down;
        InputPlayer *player;
        player = InputMgr_GetPlayer(GetInputManager(), 0);
        down = player->Pressed(1);
        held = player->Held(1);
        backward = player->StickLeft() >= lbl_806DA688;
        if (down == 1) self->state2 = 0;
        if (held == 1) {
            if (self->state2 > 0) self->state2--;
            else {
                self->state2 = 10;
                do {
                    if (backward) {
                        self->items[1]--;
                        if (self->items[1] <= 1) self->items[1] = 276;
                    } else {
                        self->items[1]++;
                        if (self->items[1] >= 277) self->items[1] = 1;
                    }
                } while (ItemClass_GetFlagByte0(self->items[1]) == 0);
            }
        }
        break;
    }
    case 15: {
        bool backward;
        unsigned char held;
        unsigned char down;
        InputPlayer *player;
        player = InputMgr_GetPlayer(GetInputManager(), 0);
        down = player->Pressed(1);
        held = player->Held(1);
        backward = player->StickLeft() >= lbl_806DA688;
        if (down == 1) self->state2 = 0;
        if (held == 1) {
            if (self->state2 > 0) self->state2--;
            else {
                self->state2 = 10;
                do {
                    if (backward) {
                        self->items[2]--;
                        if (self->items[2] <= 1) self->items[2] = 276;
                    } else {
                        self->items[2]++;
                        if (self->items[2] >= 277) self->items[2] = 1;
                    }
                } while (ItemClass_GetFlagByte0(self->items[2]) == 0);
            }
        }
        break;
    }
    case 12:
        if (pressed == 1) {
            self->selection++;
            if (self->selection > 2) self->selection = 0;
        }
        break;
    }
    fn_8023E1E4(self->widgets[0], self->items[0], 0);
    fn_8023E1E4(self->widgets[1], self->items[1], 0);
    fn_8023E1E4(self->widgets[2], self->items[2], 0);
    fn_8023E324(self->widgets[0], 1);
    fn_8023E324(self->widgets[1], 1);
    fn_8023E324(self->widgets[2], 1);
    if (!input->Held(1)) {
        if (input->Pressed(0x40) == 1) self->state--;
        else if (input->Pressed(0x80) == 1) self->state++;
        else if (input->Pressed(0x800)) self->state++;
    }
    self->state = WrapInRange(self->state, 0, 15);
    if (input->Pressed(0x400) == 1) self->done = 1;
}
