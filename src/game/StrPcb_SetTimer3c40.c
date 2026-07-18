typedef struct StrPcbTimerState {
    unsigned char pad_00[0x3c];
    unsigned char timer;
    unsigned char pad_3d[3];
    int mode;
} StrPcbTimerState;

extern const float lbl_806D241C;

void StrPcb_SetTimer3c40(StrPcbTimerState *pcb, float time, int mode)
{
    float scale = lbl_806D241C;
    pcb->timer = scale * time;
    pcb->mode = mode;
}
