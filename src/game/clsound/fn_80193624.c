typedef struct SoundEvent { unsigned int id; int state; int countdown; } SoundEvent;
typedef struct ActiveStream { unsigned int handle; unsigned int id; } ActiveStream;
extern unsigned char ClSound_Initialized;
extern SoundEvent lbl_80677F40[37];
extern ActiveStream ClSound_ActiveStreams[4];
extern void fn_80190D24(void);
extern unsigned char ClStream_IsActive(unsigned int);
extern void ClStream_UpdateAll(void);
void fn_80193624(void) {
    int i, j;
    if (ClSound_Initialized) {
        i = 0;
        while (i < 37) {
            if (lbl_80677F40[i].id == 0xffffffff) break;
            if (lbl_80677F40[i].state == 1) {
                if (lbl_80677F40[i].countdown != 0) lbl_80677F40[i].countdown--;
                else lbl_80677F40[i].state = 2;
            }
            if (lbl_80677F40[i].state == 3) {
                if (lbl_80677F40[i].countdown != 0) lbl_80677F40[i].countdown--;
                else {
                    for (j = i; j < 36; j++) {
                        SoundEvent *next = &lbl_80677F40[j + 1];
                        lbl_80677F40[j].id = next->id;
                        lbl_80677F40[j].state = next->state;
                        lbl_80677F40[j].countdown = next->countdown;
                    }
                    continue;
                }
            }
            i++;
        }
        fn_80190D24();
        { int k;
        for (k = 0; k < 4; k++) {
            if (ClSound_ActiveStreams[k].handle != 0xffffffff && !ClStream_IsActive(ClSound_ActiveStreams[k].handle))
                ClSound_ActiveStreams[k].handle = 0xffffffff;
        }
        }
        ClStream_UpdateAll();
    }
}
