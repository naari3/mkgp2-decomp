#pragma cplusplus on
/* Two-channel status output, with steady and blinking modes. */
typedef struct StatusOutput {
    unsigned char enabled;
    int frame;
    int mode[2];
    bool out[2];
    unsigned char status;
} StatusOutput;
extern "C" const unsigned char lbl_806DA260, lbl_806DA261;
extern "C" void *StrPcb_GetInstance(void);
extern "C" void StrPcb_SetStatusBits(void *, int, int);
extern "C" void StrPcb_ClearStatusBits(void *, int);
extern "C" void fn_801DABFC(StatusOutput *self) {
    unsigned int on, off;
    int frame;
    if (self->enabled) {
        frame = self->frame;
        switch (self->mode[0]) {
        case 1: self->out[0] = 1; break;
        case 2: if (frame % 10 == 0) self->out[0] = !self->out[0]; break;
        case 3: if (frame % 4 == 0) self->out[0] = !self->out[0]; break;
        case 4: self->out[0] = !self->out[0]; break;
        case 0:
        default: self->out[0] = 0; break;
        }
        switch (self->mode[1]) {
        case 1: self->out[1] = 1; break;
        case 2: if (frame % 10 == 0) self->out[1] = !self->out[1]; break;
        case 3: if (frame % 4 == 0) self->out[1] = !self->out[1]; break;
        case 4: self->out[1] = !self->out[1]; break;
        case 0:
        default: self->out[1] = 0; break;
        }
        on = 0; off = 0;
        /* Select exactly one mask for each output before applying both masks. */
        if (!self->out[0]) goto output0_off;
        on |= lbl_806DA260;
        goto output0_done;
    output0_off:
        off |= lbl_806DA260;
    output0_done:;
        if (!self->out[1]) goto output1_off;
        on |= lbl_806DA261;
        goto output1_done;
    output1_off:
        off |= lbl_806DA261;
    output1_done:;
        if (StrPcb_GetInstance()) {
            if ((unsigned char)on) StrPcb_SetStatusBits(StrPcb_GetInstance(), on, self->status);
            if ((unsigned char)off) StrPcb_ClearStatusBits(StrPcb_GetInstance(), off);
        }
        self->frame++;
        if (self->frame >= 60) self->frame = 0;
    }
}
