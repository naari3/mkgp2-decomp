extern unsigned char lbl_806CED34[4];
extern unsigned char Boot_bss_806D0FA0;
extern unsigned char ServiceButton_bss_806D0F8D;
extern unsigned char g_serviceEnable;
extern unsigned char vblank_flag;
extern unsigned char lbl_806D0F96;
extern unsigned char lbl_806D0F97;
extern unsigned char g_serviceValue;
extern unsigned char g_vblankValue;
extern unsigned char g_bootState[0x60];

void fn_8002CFB8(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    lbl_806CED34[0] = a;
    lbl_806CED34[1] = b;
    lbl_806CED34[2] = c;
    lbl_806CED34[3] = d;
}

unsigned char BootConfigFlag_Get(void) {
    return Boot_bss_806D0FA0;
}

int ServiceLatch_CheckTriggered(void) {
    if (g_serviceEnable == 0) {
        return 0;
    }
    return g_serviceValue != 1;
}

void VBlankValue_Set(unsigned char value) {
    if (vblank_flag != 0) {
        g_vblankValue = value;
    }
}

void ServiceLatchAux97_Set(unsigned char value) {
    lbl_806D0F97 = value;
}

void VBlankEnable_Set(unsigned char enable) {
    vblank_flag = enable;
    if (enable == 0) {
        g_vblankValue = 1;
    }
}

unsigned char VBlankValue_Get(void) {
    return g_vblankValue;
}

unsigned char GetVBlankFlag(void) {
    return vblank_flag;
}

void ServiceValue_Set(unsigned char value) {
    unsigned char v = 1;
    if (g_serviceEnable != 0) {
        v = value;
    }
    g_serviceValue = v;
}

void ServiceLatchAux96_Set(unsigned char value) {
    lbl_806D0F96 = value;
}

void ServiceEnable_Set(unsigned char enable) {
    g_serviceEnable = enable;
    if (enable == 0) {
        g_serviceValue = 1;
    }
}

unsigned char ServiceValue_Get(void) {
    return g_serviceValue;
}

unsigned char ServiceEnable_Get(void) {
    return g_serviceEnable;
}

void *BootStateStruct_Get(void) {
    return g_bootState;
}

unsigned char ServiceButtonExtra_Get(void) {
    return ServiceButton_bss_806D0F8D;
}

void ServiceButtonExtra_Set(unsigned char value) {
    ServiceButton_bss_806D0F8D = value;
}
