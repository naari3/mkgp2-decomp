extern void fn_801BA110(void);

#pragma exceptions on
void TrampolineTo_801ba110(void) {
    fn_801BA110();
}
#pragma exceptions reset
