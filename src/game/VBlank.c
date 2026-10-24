extern unsigned char lbl_806CED34[4];
extern unsigned char lbl_806D0FA0;
extern unsigned char lbl_806D0F8D;
extern unsigned char lbl_806D0F94;
extern unsigned char vblank_flag;
extern unsigned char lbl_806D0F96;
extern unsigned char lbl_806D0F97;
extern unsigned char lbl_806D0F98;
extern unsigned char lbl_806D0F99;
extern unsigned char lbl_80594080[0x60];

void fn_8002CFB8(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    lbl_806CED34[0] = a;
    lbl_806CED34[1] = b;
    lbl_806CED34[2] = c;
    lbl_806CED34[3] = d;
}

unsigned char BootConfigFlag_Get(void) {
    return lbl_806D0FA0;
}

int ServiceLatch_CheckTriggered(void) {
    if (lbl_806D0F94 == 0) {
        return 0;
    }
    return lbl_806D0F98 != 1;
}

void VBlankValue_Set(unsigned char value) {
    if (vblank_flag != 0) {
        lbl_806D0F99 = value;
    }
}

void ServiceLatchAux97_Set(unsigned char value) {
    lbl_806D0F97 = value;
}

void VBlankEnable_Set(unsigned char enable) {
    vblank_flag = enable;
    if (enable == 0) {
        lbl_806D0F99 = 1;
    }
}

unsigned char VBlankValue_Get(void) {
    return lbl_806D0F99;
}

unsigned char GetVBlankFlag(void) {
    return vblank_flag;
}

void ServiceValue_Set(unsigned char value) {
    unsigned char v = 1;
    if (lbl_806D0F94 != 0) {
        v = value;
    }
    lbl_806D0F98 = v;
}

void ServiceLatchAux96_Set(unsigned char value) {
    lbl_806D0F96 = value;
}

void ServiceEnable_Set(unsigned char enable) {
    lbl_806D0F94 = enable;
    if (enable == 0) {
        lbl_806D0F98 = 1;
    }
}

unsigned char ServiceValue_Get(void) {
    return lbl_806D0F98;
}

unsigned char ServiceEnable_Get(void) {
    return lbl_806D0F94;
}

void *BootStateStruct_Get(void) {
    return lbl_80594080;
}

unsigned char ServiceButtonExtra_Get(void) {
    return lbl_806D0F8D;
}

void ServiceButtonExtra_Set(unsigned char value) {
    lbl_806D0F8D = value;
}
