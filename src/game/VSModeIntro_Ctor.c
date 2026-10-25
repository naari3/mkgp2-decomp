#pragma cplusplus on
void *operator new(unsigned long);
void operator delete(void *);

extern "C" {
extern void GameMode_BaseInit(void *);
extern char lbl_8040F154[];  /* VSModeIntro vtable */
}

struct VSModeIntro {
    void *vtable;
    int field4;
    int course;
    int param2;
    int param3;
    int slotArg;

    VSModeIntro() {
        GameMode_BaseInit(this);
        vtable = lbl_8040F154;
        field4 = 0;
        course = 0;
        param2 = 0;
        param3 = 0;
        slotArg = 0;
    }
};

#pragma exceptions on
extern "C" VSModeIntro *VSModeIntro_Ctor(void)
{
    return new VSModeIntro;
}
#pragma exceptions reset
#pragma cplusplus off
