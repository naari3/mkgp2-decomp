typedef struct ClStreamSlot {
    unsigned int handle;
    unsigned int id;
} ClStreamSlot;

extern unsigned char ClSound_Initialized;
extern ClStreamSlot ClSound_ActiveStreams[4];
extern void DebugPrintf(const char *fmt, ...);

extern const char lbl_8037CF50[];
extern unsigned char ClStream_Stop(unsigned int handle);

int fn_801909A4(unsigned int id) {
    int i;
    if (!ClSound_Initialized) {
        return 1;
    }
    for (i = 0; i < 4; i++) {
        if (ClSound_ActiveStreams[i].handle != -1 && id == ClSound_ActiveStreams[i].id) {
            if (!ClStream_Stop(ClSound_ActiveStreams[i].handle)) {
                DebugPrintf(lbl_8037CF50, ClSound_ActiveStreams[i].handle);
                return 0;
            }
            ClSound_ActiveStreams[i].handle = -1;
        }
    }
    return 1;
}
