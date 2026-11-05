typedef struct HudSelectionStep {
    int field00;
    int selection;
    int field08;
    int state;
} HudSelectionStep;
void fn_80245834(HudSelectionStep *self, int selection) {
    if (self->state < 4) self->selection = selection + 1;
}
void fn_8024584C(void) {}
