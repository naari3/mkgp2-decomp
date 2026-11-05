#include "game/RaceFloatListPrivate.h"

extern "C" void fn_80247CFC(RaceFloatList *self, unsigned int count, const float *value) {
    while (count) {
        {
            RaceFloatNode *end=self->End();
            RaceFloatNodeGuard guard(&self->last,(RaceFloatNode *)Alloc(sizeof(RaceFloatNode)));
            new (&guard.node->value) float(*value);
            RaceFloatNode *node=guard.Release();
            end->prev->next=node;
            node->prev=end->prev;
            end->prev=node;
            node->next=end;
            self->count++;
        }
        count--;
    }
}
