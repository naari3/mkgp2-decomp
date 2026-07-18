typedef struct StrPcbEffectState {
    unsigned char pad_00[0x60];
    int effect_active;
    unsigned char pad_64[8];
    unsigned char effect_id;
} StrPcbEffectState;

extern int lbl_802E9838[];

void StrPcb_BeginEffect(StrPcbEffectState *pcb, int effect)
{
    pcb->effect_id = lbl_802E9838[effect];
    pcb->effect_active = 1;
}
