/*
 * UI sound-effect helpers @ 0x801FE1D0..0x801FE3BC.
 * Small SoundMgr_Play wrappers used by menu / result scenes.
 */

extern void SoundMgr_Play(int id);
extern int isJapanese(void);

void fn_801FE1D0(void) {
}

void fn_801FE1D4(void) {
}

void fn_801FE1D8(void) {
    SoundMgr_Play(0x16);
}

void fn_801FE1FC(int time) {
    if (time == 300) {
        if (isJapanese() == 0) {
            SoundMgr_Play(0x12);
        } else {
            SoundMgr_Play(0x11);
        }
    } else if (time == 180) {
        SoundMgr_Play(0x13);
    } else if (time == 120) {
        SoundMgr_Play(0x14);
    } else if (time == 60) {
        SoundMgr_Play(0x15);
    }
}

void fn_801FE27C(int time) {
    if (time == 180 || time == 120 || time == 60) {
        SoundMgr_Play(3);
    }
}

void fn_801FE2B8(void) {
    SoundMgr_Play(0xC);
}

void fn_801FE2DC(void) {
    SoundMgr_Play(0xB);
}

void fn_801FE300(void) {
    SoundMgr_Play(8);
}

void fn_801FE324(void) {
    SoundMgr_Play(9);
}

void fn_801FE348(void) {
    SoundMgr_Play(8);
}

void fn_801FE36C(void) {
    SoundMgr_Play(6);
}

void fn_801FE390(void) {
    SoundMgr_Play(5);
}

void fn_801FE3B4(char *self, int value) {
    *(int *)(self + 0x174) = value;
}
