/* ItemEffectMgr_TickPickLowestTimer @ 0x8007B534: polls every kart slot for
 * a pending item effect and picks the one with the lowest timer, keeping
 * the previous pick when it is still pending. */

extern "C" {
extern const float lbl_806D2F58;
int GetKartSlotKartVariant(int slot);
}

struct ItemPickEntry {
    void *source;
    float timer;
    int target;
    int repeat;
};

struct ItemEffectMgr {
    int field0;
    int picked;
    void *owner;
    void (ItemEffectMgr::*poll)(int variant, ItemPickEntry *entry);
    ItemPickEntry cur;

    void ResetEntry(ItemPickEntry *e)
    {
        if (e == 0) {
            e = &cur;
        }
        e->source = 0;
        e->timer = lbl_806D2F58;
        e->target = -1;
        e->repeat = 0;
    }
};

extern "C" int ItemEffectMgr_TickPickLowestTimer(ItemEffectMgr *self)
{
    ItemPickEntry entries[8];
    int i;
    int best;

    if (self->owner == 0) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        self->ResetEntry(&entries[i]);
        if (self->poll) {
            (self->*self->poll)(GetKartSlotKartVariant(i), &entries[i]);
        }
    }
    best = -1;
    for (i = 0; i < 8; i++) {
        if (entries[i].target >= 0) {
            if (i == self->picked) {
                best = i;
                break;
            }
            if (best == -1) {
                best = i;
            } else if (entries[i].timer < entries[best].timer) {
                best = i;
            }
        }
    }
    if (best != -1) {
        if (self->cur.source == entries[best].source) {
            self->cur.repeat++;
        } else {
            self->cur.repeat = 1;
        }
        self->cur.source = entries[best].source;
        self->cur.timer = entries[best].timer;
        self->cur.target = entries[best].target;
    } else {
        self->ResetEntry(0);
    }
    self->picked = best;
    return 1;
}
