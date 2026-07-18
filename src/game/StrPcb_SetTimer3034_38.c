typedef struct StrPcbTimer3034State {
    unsigned char pad_00[0x30];
    unsigned char timer;
    unsigned char pad_31[3];
    int field_34;
    int field_38;
} StrPcbTimer3034State;

extern const float lbl_806D241C;

void StrPcb_SetTimer3034_38(StrPcbTimer3034State *pcb, int value34,
                            int value38, float time)
{
    float scale = lbl_806D241C;
    pcb->timer = scale * time;
    pcb->field_34 = value34;
    pcb->field_38 = value38;
}
