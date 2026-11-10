#ifndef GAME_TYPES_DISPATCHPAYLOAD_H
#define GAME_TYPES_DISPATCHPAYLOAD_H

struct DispatchEffect;
struct DispatchKart;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DispatchPayload DispatchPayload;
struct DispatchPayload {
    /* 0x000 */ struct DispatchKart *kart;
    /* 0x004 */ unsigned char pad_004[0x20];
    /* 0x024 */ float wheelSpeed;
    /* 0x028 */ unsigned char pad_028[0x10];
    /* 0x038 */ signed char auxAccel;
    /* 0x039 */ unsigned char pad_039[0x7];
    /* 0x040 */ signed char active;
    /* 0x041 */ unsigned char pad_041[0xB];
    /* 0x04C */ struct DispatchEffect *horn;
    /* 0x050 */ struct DispatchEffect *drift;
    /* 0x054 */ unsigned char flashDelay;
    /* 0x055 */ unsigned char flashIndex;
    /* 0x056 */ unsigned char landDelay;
    /* 0x057 */ unsigned char boostPrevious[2];
    /* 0x059 */ unsigned char pad_059[0x3];
    /* 0x05C */ struct DispatchEffect *streak;
    /* 0x060 */ struct DispatchEffect *spark;
    /* 0x064 */ unsigned char auxDelay;
    /* 0x065 */ unsigned char pad_065[0x3];
    /* 0x068 */ struct DispatchEffect *wheel;
    /* 0x06C */ unsigned char wheelPrevious;
    /* 0x06D */ unsigned char wheelDelay;
    /* 0x06E */ unsigned char pad_06E[0x2];
    /* 0x070 */ struct DispatchEffect *fire;
    /* 0x074 */ struct DispatchEffect *status;
    /* 0x078 */ struct DispatchEffect *matrix;
    /* 0x07C */ struct DispatchEffect *trail;
    /* 0x080 */ unsigned char timer;
    /* 0x081 */ unsigned char previousActive;
    /* 0x082 */ unsigned char pad_082[0x2];
};

#endif /* GAME_TYPES_DISPATCHPAYLOAD_H */
