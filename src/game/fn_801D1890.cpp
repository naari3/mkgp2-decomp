#include "game/types/pcb_link.h"
#include "game/RankingFlow_private.h"
union RankingPcbSlot { unsigned int flags; unsigned char bytes[4]; };
extern "C" {
RankingPcbSlot *PcbSlot_GetByIndex(int);
extern int g_localPcbRole, g_characterId;
extern unsigned char g_lakituStartAnimDone, lbl_806D1290, g_rendererGateFlag;
extern char g_playerData[0x2000];
void Sprite_AdvanceAnim(RankingSprite *, float);
void SetSyncTarget(int);
unsigned char IsSyncReached();
void fn_801B7CD0(int);
void SetTimerModeEnabled(int);
void SyncSlot_ApplyCourseChoice();
}
static inline RankingFlowIter RankingInsertAt(RankingFlowList *list, const RankingFlowIter &last, RankingAnim *const &fade) {
    return DoublyLinkedList_PushBefore(list, &last, &fade);
}
static inline void RankingInsertFade(RankingFlowList *list, RankingFlowNode *end, RankingAnim *const &fade) {
    RankingInsertAt(list, RankingFlowIter(end), fade);
}
static inline bool operator!=(const RankingFlowIter &a, const RankingFlowIter &b) {
    return a.node != b.node;
}
static inline RankingFlowIter &operator++(RankingFlowIter &it) {
    it.node = it.node->next;
    return it;
}
static inline RankingFlowIter RankingAdvanceFlow(RankingFlowList *list) {
    RankingFlowIter end(list->End());
    for (RankingFlowIter node(list->first); node != end; ++node) {
        RankingAnim *entry = node.node->entry;
        if (entry->delay > 0) {
            --entry->delay;
        } else {
            if (entry->delay <= 0) entry->active = 1;
            for (int j = 0; j < 5; ++j) {
                RankingFlowTrack *track = &entry->tracks[j];
                if (track->active == 1) {
                    track->value = track->from * (lbl_806D9FAC - track->time) + track->to * track->time;
                    track->time += track->speed;
                    if (track->time > lbl_806D9FAC) track->time = lbl_806D9FAC;
                }
            }
            entry->Update();
            if (entry->sprite) {
                if (entry->tracks[0].active == 1) entry->sprite->alpha = entry->tracks[0].value;
                if (entry->tracks[1].active == 1) entry->sprite->sx = entry->tracks[1].value;
                if (entry->tracks[2].active == 1) entry->sprite->sy = entry->tracks[2].value;
                if (entry->tracks[3].active == 1) entry->sprite->x = entry->tracks[3].value;
                if (entry->tracks[4].active == 1) entry->sprite->y = entry->tracks[4].value;
                Sprite_AdvanceAnim(entry->sprite, lbl_806D9FC0);
            }
        }
    }
    return end;
}
int RankingFlowView::Update() {
    RankingFlowView *self = this;
    int i;
    for (i = 0; i < 4; ++i) {
        RankingPcbSlot *slot = PcbSlot_GetByIndex(i);
        if ((int)((slot->bytes[0] >> 4) & 7) == g_localPcbRole &&
            (PCB_HDR_SCENE(slot->flags) == 0x27 || PCB_HDR_SCENE(slot->flags) == 0x28)) {
            if (self->players[i]) self->players[i]->hideMark = 1;
        }
    }
    RankingFlowIter end = RankingAdvanceFlow(&self->list);
    if (self->phase == 0) {
        if (self->delay-- > 0) return -1;
        SetSyncTarget(0x28);
        ++self->timer;
        if (IsSyncReached() && self->phase == 0) {
            self->phase = 1;
            self->timer = 0;
            RankingAnim *fade = new RankingFade;
            RankingStartFade(fade);
            RankingInsertFade(&self->list, end.node, fade);
        }
        if (self->phase == 1) {
            if ((float)self->timer > lbl_806D9FB4) {
                fn_801B7CD0(-1);
                SetTimerModeEnabled(1);
                SyncSlot_ApplyCourseChoice();
                g_lakituStartAnimDone = 0;
                lbl_806D1290 = 0;
                g_rendererGateFlag = 1;
                g_playerData[0x1B8] = g_characterId;
                self->state = 0x2A;
            }
        }
        return self->state;
    } else {
        SetSyncTarget(0x28);
        ++self->timer;
        if (IsSyncReached() && self->phase == 0) {
            self->phase = 1;
            self->timer = 0;
            RankingAnim *fade = new RankingFade;
            RankingStartFade(fade);
            RankingInsertFade(&self->list, end.node, fade);
        }
        if (self->phase == 1) {
            if ((float)self->timer > lbl_806D9FB4) {
                fn_801B7CD0(-1);
                SetTimerModeEnabled(1);
                SyncSlot_ApplyCourseChoice();
                g_lakituStartAnimDone = 0;
                lbl_806D1290 = 0;
                g_rendererGateFlag = 1;
                g_playerData[0x1B8] = g_characterId;
                self->state = 0x2A;
            }
        }
        return self->state;
    }
}
