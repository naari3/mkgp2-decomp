#ifndef GAME_TYPES_BURSTEFFECT_H
#define GAME_TYPES_BURSTEFFECT_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct BurstEffect BurstEffect;
struct BurstEffect {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ int state;
    /* 0x014 */ unsigned char slot[0x78];
    /* 0x08C */ float position[3];
    /* 0x098 */ float rotationX;
    /* 0x09C */ float yaw;
    /* 0x0A0 */ float rotationZ;
    /* 0x0A4 */ unsigned char velocity[12];
    /* 0x0B0 */ float scale;
    /* 0x0B4 */ signed char state_0B4;
    /* 0x0B5 */ unsigned char pad_0B5[0x17];
    /* 0x0CC */ void *trackedDriver;
    /* 0x0D0 */ unsigned char pad_0D0[0x4C];
    /* 0x11C */ void *owner;
    /* 0x120 */ unsigned char pad_120[0x60];
    /* 0x180 */ unsigned int timer0;
    /* 0x184 */ unsigned int timer1;
    /* 0x188 */ unsigned int timer2;
    /* 0x18C */ unsigned int timer3;
};

#endif /* GAME_TYPES_BURSTEFFECT_H */
