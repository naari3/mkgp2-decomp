typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char group;
    unsigned char pad9[0x18 - 0x9];
    unsigned char x18;
    unsigned char pad19[0x1c - 0x19];
} SndSlot;

typedef struct ClStreamSlot {
    unsigned int handle;
    unsigned int id;
} ClStreamSlot;

extern unsigned char ClSound_Initialized;
extern SndSlot lbl_80678378[32];
extern ClStreamSlot ClSound_ActiveStreams[4];
extern int lbl_806CF010;
extern void *lbl_806D16B4;
extern void *lbl_806D16B8;
extern void *lbl_806D16BC;
extern void fn_8019522C(void);
extern void sndQuit(void);
extern void ARReset(void);
extern void AIReset(void);
extern void OSFreeToHeap(int heap, void *ptr);

void fn_80193838(void) {
    int i;
    if (ClSound_Initialized) {
        fn_8019522C();
        sndQuit();
        ARReset();
        AIReset();
        if (lbl_806D16B4) {
            OSFreeToHeap(lbl_806CF010, lbl_806D16B4);
        }
        if (lbl_806D16B8) {
            OSFreeToHeap(lbl_806CF010, lbl_806D16B8);
        }
        if (lbl_806D16BC) {
            OSFreeToHeap(lbl_806CF010, lbl_806D16BC);
        }
        lbl_806D16B4 = 0;
        lbl_806D16B8 = 0;
        lbl_806D16BC = 0;
        for (i = 0; i < 32; i++) {
            lbl_80678378[i].id = -1;
            lbl_80678378[i].group = 0xff;
            lbl_80678378[i].x18 = 0xff;
            lbl_80678378[i].flags = 0;
        }
        ClSound_Initialized = 0;
        for (i = 0; i < 4; i++) {
            ClSound_ActiveStreams[i].id = -1;
        }
    }
}
