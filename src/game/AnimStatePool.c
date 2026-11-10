/* AnimState pool management, 0x800AF240..0x800AF4F8. */
#include "game/types/size_t.h"
extern void AnimState_Init(void*, void*);
extern void MemoryManager_TimedFree(void*);
extern unsigned int AnimStatePool_bss_805DF350[];
extern const float lbl_806D4FC8;
extern const float lbl_806D4FCC;

#pragma cplusplus on
#pragma exceptions on
void* operator new(size_t);
void operator delete(void*) throw();

struct PoolAnimState {
    unsigned char opaque00[0x28];
    float field28;
    unsigned char opaque2C[0x18];
    int key44;
    float position[4][3];
    float rotation[4][3];
    float scale[4][3];
    float weight[4];

    PoolAnimState(void* data) {
        key44 = -1;
        for (int i = 0; i < 4; ++i) {
            position[i][0] = lbl_806D4FC8;
            position[i][1] = lbl_806D4FC8;
            position[i][2] = lbl_806D4FC8;
            rotation[i][0] = lbl_806D4FC8;
            rotation[i][1] = lbl_806D4FC8;
            rotation[i][2] = lbl_806D4FC8;
            scale[i][0] = lbl_806D4FCC;
            scale[i][1] = lbl_806D4FCC;
            scale[i][2] = lbl_806D4FCC;
            weight[i] = lbl_806D4FCC;
        }
        field28 = lbl_806D4FCC;
        AnimState_Init(this, data);
    }
};

#pragma cplusplus off
void AnimStatePool_Free(void* state) {
    int i;
    for (i = 0; i < 32; ++i) {
        if ((void*)AnimStatePool_bss_805DF350[i] == state) {
            MemoryManager_TimedFree((void*)AnimStatePool_bss_805DF350[i]);
            AnimStatePool_bss_805DF350[i] = 0;
            break;
        }
    }
}

#pragma cplusplus on
extern "C" void* AnimStatePool_Alloc(void* data) {
    for (int i = 0; i < 32; ++i) {
        if (AnimStatePool_bss_805DF350[i] == 0) {
            AnimStatePool_bss_805DF350[i] = (unsigned int)new PoolAnimState(data);
            return (void*)AnimStatePool_bss_805DF350[i];
        }
    }
    return 0;
}

extern "C" void AnimStatePool_FreeAll(void) {
    for (int i = 0; i < 32; ++i) {
        if (AnimStatePool_bss_805DF350[i] != 0) {
            MemoryManager_TimedFree((void*)AnimStatePool_bss_805DF350[i]);
            AnimStatePool_bss_805DF350[i] = 0;
        }
    }
}
#pragma cplusplus off
#pragma exceptions off

void AnimStatePool_ZeroInit(void) {
    AnimStatePool_bss_805DF350[0] = 0;
    AnimStatePool_bss_805DF350[1] = 0;
    AnimStatePool_bss_805DF350[2] = 0;
    AnimStatePool_bss_805DF350[3] = 0;
    AnimStatePool_bss_805DF350[4] = 0;
    AnimStatePool_bss_805DF350[5] = 0;
    AnimStatePool_bss_805DF350[6] = 0;
    AnimStatePool_bss_805DF350[7] = 0;
    AnimStatePool_bss_805DF350[8] = 0;
    AnimStatePool_bss_805DF350[9] = 0;
    AnimStatePool_bss_805DF350[10] = 0;
    AnimStatePool_bss_805DF350[11] = 0;
    AnimStatePool_bss_805DF350[12] = 0;
    AnimStatePool_bss_805DF350[13] = 0;
    AnimStatePool_bss_805DF350[14] = 0;
    AnimStatePool_bss_805DF350[15] = 0;
    AnimStatePool_bss_805DF350[16] = 0;
    AnimStatePool_bss_805DF350[17] = 0;
    AnimStatePool_bss_805DF350[18] = 0;
    AnimStatePool_bss_805DF350[19] = 0;
    AnimStatePool_bss_805DF350[20] = 0;
    AnimStatePool_bss_805DF350[21] = 0;
    AnimStatePool_bss_805DF350[22] = 0;
    AnimStatePool_bss_805DF350[23] = 0;
    AnimStatePool_bss_805DF350[24] = 0;
    AnimStatePool_bss_805DF350[25] = 0;
    AnimStatePool_bss_805DF350[26] = 0;
    AnimStatePool_bss_805DF350[27] = 0;
    AnimStatePool_bss_805DF350[28] = 0;
    AnimStatePool_bss_805DF350[29] = 0;
    AnimStatePool_bss_805DF350[30] = 0;
    AnimStatePool_bss_805DF350[31] = 0;
}
