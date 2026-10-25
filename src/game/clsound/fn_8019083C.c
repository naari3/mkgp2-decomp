typedef struct ClStreamSlot {
    unsigned int handle;
    unsigned int id;
} ClStreamSlot;

extern unsigned char ClSound_Initialized;
extern ClStreamSlot ClSound_ActiveStreams[4];
extern void DebugPrintf(const char *fmt, ...);

int fn_8019083C(unsigned int id) {
    int i;
    if (!ClSound_Initialized) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (ClSound_ActiveStreams[i].handle != -1 && id == ClSound_ActiveStreams[i].id) {
            return 1;
        }
    }
    return 0;
}
