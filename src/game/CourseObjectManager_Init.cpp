struct CourseObjectSlot {
    unsigned char active;
    unsigned char pad[0x1CB];
};

class cLNormal3DWrap_Mgr {
public:
    cLNormal3DWrap_Mgr();
    unsigned char data[0x24];
};

extern CourseObjectSlot lbl_805DF468[0x200];
extern "C" cLNormal3DWrap_Mgr *lbl_806D14A8;
extern "C" void fn_8022B278(void);

extern "C" void CourseObjectManager_Init(void) {
    int i;

    for (i = 0; i < 0x200; i++) {
        lbl_805DF468[i].active = 0;
    }
    lbl_806D14A8 = new cLNormal3DWrap_Mgr;
    fn_8022B278();
}
