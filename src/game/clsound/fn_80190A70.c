typedef struct ClStreamSlot {
    unsigned int handle;
    unsigned int id;
} ClStreamSlot;

extern unsigned char ClSound_Initialized;
extern ClStreamSlot ClSound_ActiveStreams[4];
extern void DebugPrintf(const char *fmt, ...);

extern const char lbl_8037CF74[];
extern unsigned char fn_80194CEC(unsigned int handle, unsigned int arg);

int fn_80190A70(unsigned int id, unsigned int arg) {
    int i;
    if (!ClSound_Initialized) {
        return 1;
    }
    for (i = 0; i < 4; i++) {
        if (ClSound_ActiveStreams[i].handle != -1 && id == ClSound_ActiveStreams[i].id) {
            if (!fn_80194CEC(ClSound_ActiveStreams[i].handle, arg)) {
                DebugPrintf(lbl_8037CF74, ClSound_ActiveStreams[i].handle);
                return 0;
            }
        }
    }
    return 1;
}
