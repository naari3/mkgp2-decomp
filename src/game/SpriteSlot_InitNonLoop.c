#include "game/types/c_region.h"
C_REGION_BEGIN
/* Observed singleton layout and external constructor ABI only. */
#include "game/types/size_t.h"
C_REGION_END
#pragma cplusplus on
void* operator new(size_t);
void operator delete(void*);
struct NonLoopNormal3D {
    unsigned char opaque[0x5C];
    NonLoopNormal3D(void* model, int enabled);
};
struct NonLoopVector { float x, y, z; };
struct NonLoopAnimRow { unsigned int opaque; float start, end; };
struct NonLoopModelEntry {
    void* model;
    NonLoopAnimRow* rows;
    unsigned char opaque[12];
};
struct NonLoopSpriteSlot {
    unsigned char active, state, opaque2[2];
    NonLoopNormal3D* object;
    unsigned char modelIndex;
    signed char rowIndex;
    unsigned char completed, opaqueB;
    float frameOffset, speed;
    unsigned char looping, opaque15[3];
    float scale;
    NonLoopVector position;
};
extern "C" {
extern const float lbl_806D5960;
extern const float lbl_806D5964;
extern NonLoopModelEntry g_itemDescriptorTable[];
unsigned char Object_SetField14_IfValid(NonLoopNormal3D*, float);
void GetSpawnPosition(NonLoopVector*, float, float, float);
unsigned char clNormal3D_SetScale(NonLoopNormal3D*, void*, float, float, float, float);
void SpriteSlot_InitNonLoop(NonLoopSpriteSlot* self, unsigned char modelIndex)
{
    self->active = 0;
    self->state = 1;
    self->modelIndex = modelIndex;
    self->object = new NonLoopNormal3D(g_itemDescriptorTable[modelIndex].model, 1);
    Object_SetField14_IfValid(self->object, lbl_806D5960);
    self->speed = lbl_806D5964;
    self->looping = 1;
    self->scale = lbl_806D5964;
    GetSpawnPosition(&self->position, lbl_806D5964, lbl_806D5964, lbl_806D5964);
    if (self->object != 0) {
        self->rowIndex = 0;
        float frame = lbl_806D5960 + g_itemDescriptorTable[self->modelIndex].rows[self->rowIndex].start;
        if (g_itemDescriptorTable[self->modelIndex].rows[self->rowIndex].end < frame)
            frame = g_itemDescriptorTable[self->modelIndex].rows[self->rowIndex].end;
        self->completed = 0;
        self->frameOffset = frame - g_itemDescriptorTable[self->modelIndex].rows[self->rowIndex].start;
        float scaleFrame = *(float*)((unsigned char*)g_itemDescriptorTable[self->modelIndex].rows + self->rowIndex * 12 + 4);
        scaleFrame += self->frameOffset;
        clNormal3D_SetScale(self->object, 0, scaleFrame,
            lbl_806D5964, lbl_806D5960, lbl_806D5960);
        Object_SetField14_IfValid(self->object, lbl_806D5960);
    }
}
}
#pragma cplusplus off


