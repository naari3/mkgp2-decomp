typedef struct ClStreamSlot {
    unsigned int handle;
    unsigned int id;
} ClStreamSlot;

extern unsigned char ClSound_Initialized;
extern ClStreamSlot ClSound_ActiveStreams[4];
extern void DebugPrintf(const char *fmt, ...);

extern const char lbl_8037CF24[];
extern unsigned char fn_80194AE0(unsigned int handle, unsigned char vol);

int clStream_setVolume(unsigned int id, unsigned char vol) {
    int i;
    if (!ClSound_Initialized) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (ClSound_ActiveStreams[i].handle != -1 && id == ClSound_ActiveStreams[i].id) {
            if (!fn_80194AE0(ClSound_ActiveStreams[i].handle, vol)) {
                DebugPrintf(lbl_8037CF24, ClSound_ActiveStreams[i].handle, vol);
                return 0;
            }
            return 1;
        }
    }
    return 1;
}
