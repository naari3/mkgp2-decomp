/* Observed list-owner layout only; no virtual base or exception specification. */
#pragma cplusplus on
#pragma exceptions on

struct clRom {
    unsigned char unknown00[8];
    clRom *previous;
    clRom *next;
    void *payload;
    unsigned char directFree;
    ~clRom();
};

extern "C" {
extern clRom *lbl_806D0FE0;
extern clRom *lbl_806D0FE4;
extern unsigned int lbl_806D0FE8;
void fn_802DC964(void *);
void fn_802DB2D4(void *);
}
void operator delete(void *);

clRom::~clRom() {
    --lbl_806D0FE8;
    if (payload != 0) {
        if (directFree == 0) fn_802DC964(payload);
        else fn_802DB2D4(payload);
    }
    if (previous == 0) lbl_806D0FE0 = next;
    else previous->next = next;
    if (next == 0) lbl_806D0FE4 = previous;
    else next->previous = previous;
}

#pragma cplusplus off
