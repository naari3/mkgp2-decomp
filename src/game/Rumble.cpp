/*
 * 0x80169978..0x80169A14: rumble controller mode set / reset. The state
 * buffer lives in lbl_806D15B0 and is allocated by InitRumbleController.
 */

struct RumbleState {
    unsigned char useJvs;
    bool base[2];
    bool out[2];
    char pad05[3];
    unsigned int mode[2];
    int duration[2];
    int timer[2];
};

extern "C" {
extern RumbleState *lbl_806D15B0;

#pragma exceptions on

void SetRumbleMode(unsigned int ch, unsigned int mode, int duration) {
    RumbleState *r = lbl_806D15B0;
    if (r == 0) {
        return;
    }
    if (ch >= 2) {
        return;
    }
    if (mode >= 5) {
        return;
    }
    r->mode[ch] = mode;
    r->duration[ch] = duration;
    r->timer[ch] = 0;
    if (r->mode[ch] == 0) {
        r->duration[ch] = 0;
    } else if (r->mode[ch] == 1) {
        r->duration[ch] = 1;
    }
}

void fn_801699D8(unsigned int ch, bool on) {
    RumbleState *r = lbl_806D15B0;
    if (r == 0) {
        return;
    }
    if (ch >= 2) {
        return;
    }
    r->base[ch] = on;
    r->out[ch] = on;
    r->mode[ch] = 0;
    r->duration[ch] = 0;
    r->timer[ch] = 0;
}

#pragma exceptions reset
}
