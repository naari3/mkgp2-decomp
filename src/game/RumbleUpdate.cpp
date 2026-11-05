#include "game/RumbleUpdate_private.h"
#pragma exceptions on
extern "C" void RumbleUpdate() {
    int ch;
    RumbleUpdateState *cursor;
    RumbleUpdateState *r = lbl_806D15B0;
    if (!r) return;
    for (ch = 0, cursor = r; ch < 2; cursor = (RumbleUpdateState *)((char *)cursor + 4), ++ch) {
        switch (cursor->mode[0]) {
        case 1: r->out[ch] = !r->out[ch]; cursor->mode[0] = 0; break;
        case 2: if (cursor->timer[0] % 10 == 0) r->out[ch] = !r->out[ch]; break;
        case 3: if (cursor->timer[0] % 4 == 0) r->out[ch] = !r->out[ch]; break;
        case 4: r->out[ch] = !r->out[ch]; break;
        default: r->out[ch] = r->base[ch]; break;
        }
        if (cursor->mode[0]) {
            ++cursor->timer[0];
            if (cursor->duration[0] >= 0 && cursor->timer[0] >= cursor->duration[0]) cursor->mode[0] = 0;
        }
    }
    RumbleApply(r);
}
