struct CourseObjectSlot {
    unsigned char active;
    unsigned char pad[0x1CB];
};

class cLNormal3DWrap_Mgr {
public:
    cLNormal3DWrap_Mgr();
    unsigned char data[0x24];
};

extern CourseObjectSlot g_drawEffectSlots[0x200];
extern "C" cLNormal3DWrap_Mgr *g_normal3DWrapMgr;
extern "C" void fn_8022B278(void);

extern "C" void CourseObjectManager_Init(void) {
    int i;

    for (i = 0; i < 0x200; i++) {
        g_drawEffectSlots[i].active = 0;
    }
    g_normal3DWrapMgr = new cLNormal3DWrap_Mgr;
    fn_8022B278();
}
