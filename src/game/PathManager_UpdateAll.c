#include "game/PathManager_UpdateAllPrivate.h"

#define FIND(start, from, to) Waypoint_FindBestAhead(self, start, from, to, *e->px, *e->py, *e->pz, &e->distance)
#define NORMAL() do { if (e->lap >= 0) node = FIND(e->node, -2, 4); else node = FIND(e->node, 0, 4); } while (0)
#define RANGE(lo, hi) (e->node >= (lo) && e->node <= (hi))

static inline float ParticipantDistance(UpdateManager *a, UpdateManager *b)
{
    float dx, dy, dz;
    dy = *a->entries[0].py-*b->entries[0].py;
    dx = *a->entries[0].px-*b->entries[0].px;
    dz = *a->entries[0].pz-*b->entries[0].pz;
    /* Square Y before the fused X term, as in the original. */
    dy = (dx*dx + dy*dy) + dz*dz;
    if (dy > lbl_806D24E8) {
        double guess = __frsqrte(dy);
        guess = lbl_806D24F0*guess*(lbl_806D24F8-dy*(guess*guess));
        guess = lbl_806D24F0*guess*(lbl_806D24F8-dy*(guess*guess));
        guess = lbl_806D24F0*guess*(lbl_806D24F8-dy*(guess*guess));
        {
            volatile float rounded = (float)(dy*guess);
            dy = rounded;
        }
    }
    return dy;
}

static inline void UpdateRankFeedback(UpdateManager *self, UpdateEntry *own)
{
    UpdateEntry *feedbackEntry;
    int feedbackIndex;
    UpdateManager *slot = self;
    int otherIndex;
    for (feedbackIndex = 0; feedbackIndex < 8; feedbackIndex++, slot = (UpdateManager *)((char *)slot + 0x98)) {
        feedbackEntry = &slot->entries[0];
        if (feedbackEntry == own && feedbackEntry->item && feedbackEntry->rankImproved == 1) {
            for (otherIndex = 0; otherIndex < 8; otherIndex++) {
                /* Original compares with this slot's rank before measuring otherIndex. */
                if (slot->entries[0].rank == feedbackEntry->rank-1) {
                    float distance;
                    if (!PathManager_HasPathLoaded(self)) distance = lbl_806D2508;
                    else {
                        distance = ParticipantDistance(slot, (UpdateManager *)((char *)self + otherIndex*0x98));
                    }
                    if (distance > lbl_806D250C) {
                        CoinEvent_PlayAlternatingSE(feedbackEntry->item);
                        feedbackEntry->rankImproved = 0;
                    }
                    break;
                }
            }
        }
    }
}

#pragma exceptions on
int PathManager_UpdateAll(UpdateManager *self)
{
    int node;
    UpdateEntry *e;
    UpdateManager *displaySlot;
    int count;
    int i;
    float *finish;
    UpdateEntry *own;
    float u[3], t;

    finish = GetFinishLineSegment();
    if (!PathManager_HasPathLoaded(self)) return -1;
    if (g_gameMode == 2) {
        for (count = 0, displaySlot = self; count < 8; count++, displaySlot = (UpdateManager *)((char *)displaySlot + 0x98)) {
            own = &displaySlot->entries[0];
            if (own->kart) {
                node = own->kart->playerId;
                if (node == GetDisplayBufferIndex()) break;
            }
        }
    } else own = &self->entries[0];
    count = 0;
    for (i = 0; i < 8; i++) {
        e = &self->entries[i];
        if (e->node < 0) continue;
        if (e->pathVariant != e->kart->pathVariant) {
            int variant = e->kart->pathVariant;
            if (g_cupId == 4 && g_longRoundFlag == 1) {
                if (g_reverseRoundFlag == 0) {
                    if (variant == 1) e->node = 0x2E; else e->node = 0x65;
                } else {
                    if (variant == 1) e->node = 0xE; else e->node = 0x47;
                }
            }
            if (g_cupId == 14 || (g_cupId == 6 && g_longRoundFlag == 0)) {
                if (g_reverseRoundFlag == 0) {
                    if (variant == 1) e->node = 0x38; else e->node = 0xB7;
                } else {
                    if (variant == 1) e->node = 0x47; else e->node = 0x141;
                }
            }
            if (g_cupId == 6 && g_longRoundFlag == 1) {
                if (g_reverseRoundFlag == 0) {
                    if (variant == 1) e->node = 0x3B; else e->node = 0xA3;
                } else {
                    if (variant == 1) e->node = 0x24; else e->node = 0x82;
                }
            }
            e->pathVariant = variant;
        }
        if (g_cupId == 14 || (g_cupId == 6 && g_longRoundFlag == 0)) {
            if (g_reverseRoundFlag == 0) {
                if (RANGE(0x38,0x3E)) node = FIND(e->node,0,4);
                else if (RANGE(0xB7,0xC1)) node = FIND(e->node,0,4);
                else NORMAL();
            } else {
                if (RANGE(0x47,0x4D)) node = FIND(e->node,0,4);
                else if (RANGE(0x141,0x147)) node = FIND(e->node,0,4);
                else NORMAL();
            }
        } else if (g_cupId == 6 && g_longRoundFlag == 1) {
            if (g_reverseRoundFlag == 0) {
                if (RANGE(0x3A,0x40)) node = FIND(e->node,0,4);
                else if (RANGE(0xA2,0xA8)) node = FIND(e->node,0,4);
                else if (RANGE(0x69,0xA2)) node = FIND(e->node,0,5);
                else NORMAL();
            } else {
                if (RANGE(0x23,0x29)) node = FIND(e->node,0,4);
                else if (RANGE(0x81,0x87)) node = FIND(e->node,0,4);
                else if (RANGE(0x32,0x78)) node = FIND(e->node,0,5);
                else NORMAL();
                if (node >= e->node) { if (node == 0x64) node++; }
                else { if (node == 0x64) node--; }
            }
        } else if (g_cupId == 5) {
            if (g_longRoundFlag == 0) {
                if (RANGE(0x1E,0x37)) node = FIND(e->node,0,5); else NORMAL();
            } else {
                if (RANGE(0x1E,0x37)) node = FIND(e->node,0,5); else NORMAL();
            }
        } else if (g_cupId == 4 && g_longRoundFlag == 1) {
            if (g_reverseRoundFlag == 0) {
                if (RANGE(0x2E,0x34)) node = FIND(e->node,0,4);
                else if (RANGE(0x65,0x6B)) node = FIND(e->node,0,4);
                else NORMAL();
            } else {
                if (RANGE(0xE,0x14)) node = FIND(e->node,0,4);
                else if (RANGE(0x47,0x4D)) node = FIND(e->node,0,4);
                else NORMAL();
            }
        } else if (g_cupId == 7) {
            if (g_longRoundFlag == 0) {
                if (g_reverseRoundFlag == 0) {
                    if (RANGE(0x5C,0x60)) node = FIND(0x60,-1,2); else NORMAL();
                } else {
                    if (RANGE(0x12,0x17)) node = FIND(0x17,-1,2); else NORMAL();
                }
            } else {
                if (g_reverseRoundFlag == 0) {
                    if (RANGE(0x98,0x9D)) node = FIND(0x9D,-1,2); else NORMAL();
                } else {
                    if (RANGE(0x14,0x18)) node = FIND(0x18,-1,2); else NORMAL();
                }
            }
        } else NORMAL();
        if (node >= 0) {
            if (node <= 5 && Path_GetTotalCount(self)-1 <= e->progress)
                e->progress = node + Path_GetTotalCount(self);
            else if (node < 50 || e->progress > 10 || e->crossedEnd != 0)
                e->progress = node;
            if (e->maxProgress < e->progress && e->progress < e->maxProgress+10)
                e->maxProgress = e->progress;
            e->node = node;
        }
        e->changed = 0;
        count++;
    }
    for (i = 0; i < 8; i++) {
        unsigned char crossed;
        e = &self->entries[i];
        if (e->node >= 0 && e->node != e->maxNode) {
            if (e->maxNode < e->node && e->node-e->maxNode < 5) e->maxNode = e->node;
            else if (Path_GetTotalCount(self)-5 < e->maxNode && e->node < 5) e->maxNode = e->node;
            if (e->lap < 10 && Path_GetTotalCount(self)-10 < e->maxNode && e->maxNode < Path_GetTotalCount(self)-5)
                e->crossedEnd = 1;
        }
        if (lbl_806D24E8 == g_raceTimeRemaining || e->node < 0 || e->lap >= 10) continue;
        crossed = 0;
        if (g_gameMode == 2 && !g_isCommHost) {
            if (e->lap != CommBroadcast_GetKartLap(e->kart->commId)) crossed = 1;
        } else if (e->maxProgress > Path_GetTotalCount(self)-10 && e->crossedEnd == 1) {
            if (Math_Segment2DIntersect(e->previous[0],e->previous[2],*e->px,*e->pz,
                    finish[0],finish[2],finish[3],finish[5],&t,u) == 1) crossed = 1;
        }
        if (crossed) {
            e->progress = 0;
            e->maxProgress = 0;
            if (e->lap == -1) e->lap++;
            else if (e->kart->finished != 1) {
                e->lapTimes[e->lap] += DANGER*t;
                e->totalTime += e->lapTimes[e->lap];
                if (e == own) g_currentLapTime = e->lapTimes[e->lap];
                if (e->lap+1 < 10) e->lapTimes[e->lap+1] = DANGER*(lbl_806D2504-t);
                if (lbl_806D24E8 == e->bestLap || e->lapTimes[e->lap] < e->bestLap) {
                    e->bestLap = e->lapTimes[e->lap];
                    if (e->item) CoinEvent_PlaySE_0x13(e->item);
                }
                e->lap++;
                if (g_gameMode == 2 && g_isCommHost) CommBroadcast_SetKartLap(e->kart->commId,(signed char)e->lap);
                if (e->lap >= g_totalLaps) {
                    if (!lbl_806D1048) e->rank = KartMovement_CalcFinishPosition(e->kart,1);
                    if (e->kart->rank == 0) KartMovement_ResetOnGoal(e->kart);
                    else KartMovement_ResetOnTimeout(e->kart);
                    if (e->item && !e->kart->suppressResult) {
                        KartItem_OnFallOffOrDeath(e->item);
                        CoinJumpFlasher_SetArmed(e->item,0);
                        CoinEvent_PlayResultSE(e->item,e->rank);
                    }
                    KartItem_SetByte2b8(e->kart,1);
                } else if (e->kart->playerId >= 0 && e->kart->playerId <= 3 && e->lap-1 == self->bonusLap) {
                    if (IsTimerModeEnabled() == 1) g_raceTimeRemaining += g_lapBonusTimeDelta;
                    self->bonusLap++;
                }
            }
            e->crossedEnd = 0;
        }
        if (IsRaceStarted() == 1) {
            if (e->lap < 0) e->lapTimes[0] += DANGER;
            else e->lapTimes[e->lap] += DANGER;
        }
        if (!e->kart->finished) e->rank = -1;
        KartMovement_SetRemainingLaps(e->kart,g_totalLaps-e->lap);
        e->previous[0] = *e->px;
        e->previous[1] = *e->py;
        e->previous[2] = *e->pz;
    }
    {
        int rank;
        int j;
        int limit;
        UpdateEntry *e;
        rank = -1;
        limit = 8;
        if (g_gameMode == 1) limit = 2;
        for (i = 0; i < limit; i++) {
            e = &self->entries[i];
            if (e->node >= 0 && rank < e->rank) rank = e->rank;
        }
        rank++;
        if (g_gameMode != 2 || g_isCommHost) {
            for (i = 0; i < limit; i++) {
                UpdateManager *scan;
                UpdateManager *slot = self;
                UpdateEntry *candidate;
                slot = (UpdateManager *)((char *)slot + i*0x98);
                candidate = &slot->entries[0];
                if (candidate->node < 0 || candidate->rank != -1) continue;
                for (j = 0; j < limit; j++) {
                    scan = (UpdateManager *)((char *)self + j*0x98);
                    if (scan->entries[0].node < 0 || scan->entries[0].rank != -1) continue;
                    if (candidate->lap < scan->entries[0].lap) candidate = &scan->entries[0];
                    else if (candidate->lap == scan->entries[0].lap) {
                        if (candidate->progress < scan->entries[0].progress) candidate = &scan->entries[0];
                        else if (candidate->progress == scan->entries[0].progress && scan->entries[0].distance < candidate->distance) candidate = &scan->entries[0];
                    }
                }
                if (!lbl_806D1048) {
                    if (!candidate->kart->finished) {
                        candidate->rank = rank;
                        candidate->kart->rank = rank;
                    }
                } else {
                    candidate->rank = rank;
                    candidate->kart->rank = rank;
                }
                if (slot->entries[0].rank == -1) i--;
                else if (rank < candidate->rank) candidate->rankImproved = 1;
                else candidate->rankImproved = 0;
                rank++;
                if (rank >= limit) break;
                if (g_gameMode == 2) CommBroadcast_SetKartRankNibble(candidate->kart->commId,candidate->rank);
            }
        } else {
            for (i = 0; i < 4; i++) {
                e = &self->entries[i];
                rank = CommBroadcast_GetKartRankNibble(e->kart->commId);
                if (!e->kart->finished) {
                    if (rank < e->rank) e->rankImproved = 1; else e->rankImproved = 0;
                    e->rank = rank;
                    e->kart->rank = rank;
                } else if (lbl_806D1048) e->rank = KartMovement_CalcFinishPosition(e->kart,1);
            }
        }
    }
    node = own->lap;
    node = node == -1 ? 0 : node;
    if (g_currentLap != node+1) g_lapChangePending = 1;
    g_currentLap = node+1;
    g_currentLapTime = own->lapTimes[node];
    g_finalRacePosition = own->rank;
    g_bestLapTime = own->bestLap;
    g_totalRaceTime = own->totalTime;
    lbl_806CF128 = node+1;
    UpdateRankFeedback(self, own);
    return count;
}
#pragma exceptions reset
