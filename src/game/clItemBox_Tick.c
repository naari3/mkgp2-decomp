/* Run the item box's current step function, then load the step function
 * for the state it returned. Returns 1 while the box is idle/visible. */
#pragma cplusplus on

struct clItemBox;
typedef int (clItemBox::*clItemBoxStepFn)();

struct clItemBox {
    unsigned char pad00[0x18];
    clItemBoxStepFn step; /* 0x18 */
    int state;            /* 0x24 */
};

extern clItemBoxStepFn lbl_803F9CA8[];

extern "C" int clItemBox_Tick(clItemBox *self)
{
    self->state = (self->*self->step)();
    self->step = lbl_803F9CA8[self->state];
    if (self->state == 1 || self->state == 0 || self->state == 3) {
        return 1;
    }
    return 0;
}
