/* clMenu: deferred generation, definitions in reverse target order. */
typedef struct MenuEntry {
    unsigned int field0;   /* 0x0 */
    char *label;           /* 0x4 */
    unsigned char pad8;    /* 0x8 */
    unsigned char hidden;  /* 0x9 */
} MenuEntry;

#include "game/types/clJobRunner.h"

struct clMenu : clJobRunner {
    virtual int Update();
    virtual void Draw();
    virtual ~clMenu();
    clMenu(MenuEntry *);
    MenuEntry *entries;
    int count;
    int cursor;
    int blink;
};

void operator delete(void *) throw();

/* Input player object: virtual button-state query at vtable +0x20. */
struct InputObject {
    virtual unsigned char vf08();
    virtual unsigned char vf0c();
    virtual unsigned char vf10();
    virtual unsigned char vf14();
    virtual unsigned char vf18();
    virtual unsigned char vf1c();
    virtual unsigned char checkButton(unsigned int mask); /* +0x20 */
};

extern "C" {

extern void DeadCounter_Set_806d0fb8(int);
extern void OverlayText(int, int, int, const char *, ...);
extern InputObject **GetInputManager(void);
extern InputObject *InputMgr_GetPlayer(InputObject **mgr, unsigned int playerIdx);
extern void GameMode_BaseInit(void *self);
extern void *dtor_8002CDF4(void *self, short flag);
extern void MemoryManager_TimedFree(void *);


extern const char lbl_806D22C8[8];   /* header string  @ .sdata2:0x806D22C8 */
extern const char lbl_806D22D0[3];   /* cursor string  @ .sdata2:0x806D22D0 */

} // extern "C"

clMenu::clMenu(MenuEntry *menuEntries) {
    this->entries = menuEntries;
    this->blink = 0;
    this->count = 0;
    while (this->entries[this->count].field0 != 0) {
        this->count++;
    }
    this->cursor = 0;
    for (;;) {
        if (this->entries[this->cursor].hidden == 0) break;
        this->cursor++;
        this->cursor %= this->count;
        this->blink = 0;
    }
}


clMenu::~clMenu() {}

int clMenu::Update() {
    int dir;
    unsigned char decide;
    InputObject *p;

    dir = 0;
    decide = 0;
    this->blink = this->blink + 1;
    this->blink = this->blink & 0x1F;
    p = InputMgr_GetPlayer(GetInputManager(), 0);
    if (p->checkButton(0x40) == 1) {
        dir = -1;
    } else if (p->checkButton(0x80) == 1 || p->checkButton(0x800) == 1) {
        dir = 1;
    } else if (p->checkButton(0x401) == 1) {
        decide = 1;
    }

    if (decide == 1) {
        this->blink = 0;
        return this->cursor;
    }
    if (dir != 0) {
        do {
            this->cursor = this->cursor + dir;
            if (this->cursor < 0) {
                this->cursor = this->count - 1;
            } else if (this->cursor >= this->count) {
                this->cursor = 0;
            }
            this->blink = 0;
        } while (this->entries[this->cursor].hidden != 0);
    }
    return -2;
}

void clMenu::Draw() {
    short row;
    int i;

    DeadCounter_Set_806d0fb8(0x10);
    OverlayText(2, 1, 0, lbl_806D22C8);
    row = 6;
    for (i = 0; i < this->count; i++) {
        if (this->entries[i].hidden == 0) {
            OverlayText(2, 3, row, this->entries[i].label);
            if (this->blink < 0x18 && this->cursor == i) {
                OverlayText(2, 1, row, lbl_806D22D0);
            }
            row++;
        }
    }
    DeadCounter_Set_806d0fb8(0x10);
}
