/* Brightness threshold sound and display state. */
extern float lbl_806D9890, lbl_806D98B0, lbl_806D98B4, lbl_806D98B8, lbl_806D9898, lbl_806D98BC, lbl_806D98C0, lbl_806D98C4, lbl_806D98C8, lbl_806D98CC, lbl_806D98D0, lbl_806D98D4, lbl_806D98D8, lbl_806D98DC, lbl_806D98E0, lbl_806D98E4;
extern signed char lbl_806D184E, lbl_806D181C, lbl_806D181D, lbl_806D181E;
extern float lbl_806D1838, lbl_806D183C;
extern void SoundMgr_Play(int);

#pragma exceptions on
int SetScreenBrightness(float value) {
    unsigned char crossed;
    if (lbl_806D98B0 <= value) return 0;
    if (value < 0.0f || lbl_806D98B4 < value) lbl_806D184E = 6;
    if (value < 0.0f) {
        lbl_806D181C = -1;
        lbl_806D181D = -1;
        lbl_806D181E = -1;
        lbl_806D1838 = lbl_806D98B8;
        lbl_806D183C = lbl_806D98B8;
        return 1;
    }
    crossed = 0;
    switch (lbl_806D184E) {
    case 6:
        if (lbl_806D9898 >= value && value >= lbl_806D98BC) crossed = 1;
        break;
    case 5:
        if (lbl_806D98C0 >= value && value >= lbl_806D98C4) crossed = 1;
        break;
    case 4:
        if (lbl_806D98C8 >= value && value >= lbl_806D98CC) crossed = 1;
        break;
    case 3:
        if (lbl_806D98D0 >= value && value >= lbl_806D98D4) crossed = 1;
        break;
    case 2:
        if (lbl_806D98D8 >= value && value >= lbl_806D98DC) crossed = 1;
        break;
    case 1:
        if (lbl_806D98E0 >= value && value >= lbl_806D98E4) crossed = 1;
        break;
    }
    if (crossed) {
        SoundMgr_Play(3);
        --lbl_806D184E;
    }
    lbl_806D183C = value;
    return 1;
}
#pragma exceptions reset
