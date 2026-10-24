typedef struct VSModeIntro {
    void *vtable;
    int field4;
    int course;
    int param2;
    int param3;
    int slotArg;
} VSModeIntro;

extern void MemoryManager_TimedFree(void *);
extern void dtor_8002CDF4(void *, int);
extern void SetCourseParams(int, int, int, int);
extern void RaceSlot_InitSlot(int, int, int, int, int);
extern char lbl_8040F154[];  /* VSModeIntro vtable */

#pragma exceptions on
VSModeIntro *VSModeIntro_Dtor(VSModeIntro *self, short flag)
{
    if (self != 0) {
        self->vtable = lbl_8040F154;
        SetCourseParams(self->course, self->param2, self->param3, 0);
        RaceSlot_InitSlot(7, 0, self->slotArg, 1, 0);
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
