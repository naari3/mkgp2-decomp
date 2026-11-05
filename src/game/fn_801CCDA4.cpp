#include "game/ItemSelectPendingPrivate.h"
static inline void TickSelectEntries(SelectNode *node, SelectNode *end) {
    SelectEntry *entry;
    for (; node!=end; node=node->next) {
        entry=node->entry;
        if (entry->delay>0) { --entry->delay; }
        else {
            if (entry->delay<=0) entry->active=1;
            for(int i=0;i<5;++i) {
                if(entry->tween[i].enabled==1) {
                    entry->tween[i].value=entry->tween[i].from*(lbl_806D9E24-entry->tween[i].t)+entry->tween[i].to*entry->tween[i].t;
                    entry->tween[i].t+=entry->tween[i].step;
                    if(entry->tween[i].t>lbl_806D9E24) entry->tween[i].t=lbl_806D9E24;
                }
            }
            entry->Apply();
            if(entry->sprite) {
                if(entry->tween[0].enabled==1) entry->sprite->scale=entry->tween[0].value;
                if(entry->tween[1].enabled==1) entry->sprite->z=entry->tween[1].value;
                if(entry->tween[2].enabled==1) entry->sprite->w=entry->tween[2].value;
                if(entry->tween[3].enabled==1) entry->sprite->x=entry->tween[3].value;
                if(entry->tween[4].enabled==1) entry->sprite->y=entry->tween[4].value;
                Sprite_AdvanceAnim(entry->sprite,lbl_806D9E2C);
            }
        }
    }

}

extern "C" void fn_801CCDA4(SelectOwner *self) { SelectNode *end=(SelectNode *)&self->last; TickSelectEntries(self->first,end); fn_801CCAAC(self); }
