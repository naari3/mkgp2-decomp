typedef struct SoundEvent { unsigned int id; int state; int countdown; } SoundEvent;
extern unsigned char ClSound_Initialized;
extern SoundEvent ClSound_InitSoundSystem_bss_80677F40[37];
extern const char lbl_8037D058[];
extern int sprintf(char *, const char *, ...);
extern void DeadCounter_Set_ced48(int);
extern void OverlayText(int, int, int, const char *, ...);
void fn_801934F4(void) {
    int i;
    int row;
    SoundEvent *event;
    char text[64];
    row = 0;
    if (ClSound_Initialized) {
        event = ClSound_InitSoundSystem_bss_80677F40;
        for (i = row; i < 37; i++, event++) {
            if (event->id == 0xffffffff) break;
            {
                unsigned int id = event->id & 0x87ffffff;
                sprintf(text, lbl_8037D058, id, (event->id >> 27) & 15);
            }
            switch (event->state) {
            case 1:
                DeadCounter_Set_ced48(4);
                OverlayText(1, 1, row + 2, text);
                break;
            case 2:
                DeadCounter_Set_ced48(7);
                OverlayText(1, 1, row + 2, text);
                break;
            default:
                DeadCounter_Set_ced48(0);
                OverlayText(1, 1, row + 2, text);
                break;
            }
            row++;
            if (row >= 29) break;
        }
        DeadCounter_Set_ced48(7);
    }
}
