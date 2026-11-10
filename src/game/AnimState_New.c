#include "game/types/AnimVec3.h"

#include "game/types/AnimState.h"

extern void AnimState_Init(AnimState *, void *entries);

AnimState *AnimState_New(AnimState *self, void *entries)
{
    int i;

    self->current = -1;
    for (i = 0; i < 4; i++) {
        self->pos[i].x = 0.0f;
        self->pos[i].y = 0.0f;
        self->pos[i].z = 0.0f;
        self->rot[i].x = 0.0f;
        self->rot[i].y = 0.0f;
        self->rot[i].z = 0.0f;
        self->scale[i].x = 1.0f;
        self->scale[i].y = 1.0f;
        self->scale[i].z = 1.0f;
        self->d[i] = 1.0f;
    }
    self->weight = 1.0f;
    AnimState_Init(self, entries); /* the second argument goes straight through */
    return self;
}
