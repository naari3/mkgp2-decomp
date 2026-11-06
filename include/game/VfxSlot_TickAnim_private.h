#ifndef VFX_SLOT_TICK_ANIM_PRIVATE_H
#define VFX_SLOT_TICK_ANIM_PRIVATE_H
typedef struct VfxSlotAnim {
    unsigned char pad00[4];
    void *effect;
    unsigned char resource;
    unsigned char pad09;
    signed char state;
    unsigned char pad0B;
    float frame;
    float speed;
    signed char enabled;
} VfxSlotAnim;
typedef struct VfxAnimResource {
    unsigned int id;
    signed char mode;
    unsigned char pad05[3];
    int lastFrame;
    signed char loop;
    unsigned char pad0D[7];
} VfxAnimResource;
#endif
