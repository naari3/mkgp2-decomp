#include "game/JointTracksPrivate.h"

extern "C" {
extern const TrackSet lbl_803E5D44;
extern const TrackGroup lbl_803EA5D4[], lbl_803EEB68[];

void fn_802400A4(TaskBucket *self, const ChildBinding *binding, int group, void *model) {
    TrackTask *owner;
    const char **name;
    const ChildBinding *cursor;
    TaskBucket *bucket;
    if (!binding) return;
    bucket = &self[group];
    cursor = binding;
    for (; cursor->name; ++cursor) {
        HSD_JObj *joint = ResolveJointByName(model, cursor->name);
        if (!joint) {
            DebugPrintf(lbl_803EED14, cursor->name, 0x1B1);
            continue;
        }
        TrackTask *task = new TrackTask(joint, &lbl_803E5D44);
        Append(bucket, task);
        for (name = cursor->children; *name; ++name) {
            HSD_JObj *child = ResolveJointByName(model, *name);
            if (!child) {
                DebugPrintf(lbl_803EED64, *name, 0x1C7);
                continue;
            }
            owner = task;
            MatrixChild *entry = new MatrixChild(owner->joint, child);
            AppendChild(&owner->children, entry);
        }
    }
}

#pragma push
#pragma opt_propagation off
int fn_80240378(TaskBucket *self, const char *name, int group, void *model,
                const TrackGroup *groups) {
    const char *strings = lbl_803E5D38 + 0x10000;
    if (!name) return 0;
    if (!model) return 0;
    if (!groups) return 0;
    const TrackGroup *cursor = groups;
    int index = 0;
    for (; cursor->name; ++cursor, ++index) {
        if (strcmp(cursor->name, name) == 0) {
            DebugPrintf(strings - 0x6F44, 0x164);
            DebugPrintf(strings - 0x6F14, group, name);
            const TrackBinding *binding = groups[index].tracks;
            if (binding) {
                TaskBucket *bucket = &self[group];
                for (; binding->name; ++binding) {
                    HSD_JObj *joint = ResolveJointByName(model, binding->name);
                    if (!joint) {
                        DebugPrintf(strings - 0x6F8C, binding->name, 0x18E);
                        continue;
                    }
                    TrackTask *task = new TrackTask(joint, binding->tracks);
                    Append(bucket, task);
                }
            }
            const char **animated = groups[index].animated;
            if (animated) {
                TaskBucket *bucket = &self[group];
                for (; *animated; ++animated) {
                    HSD_JObj *joint = ResolveJointByName(model, *animated);
                    if (!joint) {
                        DebugPrintf(strings - 0x7070, *animated, 0x1ED);
                        continue;
                    }
                    AnimTask *task = new AnimTask(joint);
                    Append(bucket, task);
                }
            }
            fn_802400A4(self, groups[index].children, group, model);
            return 1;
        }
    }
    return 0;
}
#pragma pop


int fn_80240618(TaskBucket *self, const char *name, int group, void *model) {
    const TrackGroup *groups;
    switch (g_cupId) {
    case 7: case 15: groups = lbl_803EA5D4; break;
    case 8: case 16: groups = lbl_803EEB68; break;
    default: return 0;
    }
    if (!groups) return 0;
    return fn_80240378(self, name, group, model, groups);
}

void *fn_802406A4(TaskBucket *self, short destroy) {
    TaskBucket *bucket;
    int i;
    DispatchTask **it;
    if (self) {
        i = 0;
        bucket = self;
        do {
            for (it = bucket->start; it != bucket->End(); ++it) delete *it;
            bucket->count = 0;
            ++bucket;
            ++i;
        } while (i < 32);
        __destroy_arr(self, (void *)fn_80240764, 12, 32);
        if (destroy > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

void *fn_80240764(TaskBucket *self, short destroy) {
    if (self) {
        if (self) {
            if (self) {
                if (self->start) MemoryManager_TimedFree(self->start);
            }
        }
        if (destroy > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

void *fn_802407C8(TaskBucket *self) {
    __construct_array(self, (void *)fn_80241C08, (void *)fn_80240764, 12, 32);
    return self;
}
}

static inline int TrackLength(const TrackKey *keys) {
    const TrackKey *cursor = keys;
    int count = 0;
    int length;
    for (;;) {
        if (cursor->frame == -1) {
            length = keys[count - 1].frame;
            break;
        }
        ++cursor;
        ++count;
    }
    return length;
}

static inline void SeekTrack(const TrackKey *keys, TrackState *state, int frame) {
    if (keys) {
        int i;
        int key = 0;
        int length = TrackLength(keys);
        int localFrame = frame;
        while (localFrame >= length) localFrame -= length;
        i = 0;
        for (; (length = keys->frame) != -1; ++keys, ++i) {
            if (localFrame < length) {
                key = i;
                break;
            }
        }
        state->frame = localFrame;
        state->key = key;
    }
}

static inline const TrackKey *GetTrack(const TrackSet *tracks, int channel) {
    return tracks->channels[channel];
}

extern "C" void fn_80240810(TrackTask *self, int frame) {
    SeekTrack(GetTrack(self->tracks, 0), &self->state[0], frame);
    SeekTrack(GetTrack(self->tracks, 1), &self->state[1], frame);
    SeekTrack(GetTrack(self->tracks, 2), &self->state[2], frame);
    SeekTrack(GetTrack(self->tracks, 3), &self->state[3], frame);
    SeekTrack(GetTrack(self->tracks, 4), &self->state[4], frame);
    SeekTrack(GetTrack(self->tracks, 5), &self->state[5], frame);
    SeekTrack(GetTrack(self->tracks, 6), &self->state[6], frame);
    SeekTrack(GetTrack(self->tracks, 7), &self->state[7], frame);
    SeekTrack(GetTrack(self->tracks, 8), &self->state[8], frame);
}

extern "C" void fn_80240CFC(TrackTask *self) {
    if (self->children.count != 0) {
        HSD_JObjClearFlagsAll(self->joint, 0x10);
        for (MatrixChild **it = self->children.start; it != self->children.End(); ++it)
            HSD_JObjDispAll((*it)->joint, 0, 7, 0);
        HSD_JObjSetFlagsAll(self->joint, 0x10);
    }
}

static inline float StepTrack(const TrackKey *keys, TrackState *state) {
    int start;
    if (state->frame > keys[state->key].frame) {
        ++state->key;
        if (keys[state->key].frame == -1) {
            state->key = 1;
            state->frame = 1;
        }
    }
    const TrackKey *previous;
    int index = state->key;
    if (index == 0) previous = keys;
    else previous = &keys[index - 1];
    const TrackKey *next = &keys[index];
    int frame = state->frame++;
    start = previous->frame;
    int elapsed = frame - start;
    if (elapsed == 0) return previous->value;
    return (float)elapsed / (float)(next->frame - start) *
        (next->value - previous->value) + previous->value;
}

static inline void SetTranslation(HSD_JObj *j, float v, int component, int line) {
    if (!j) __assert(lbl_806DBDE4, line, lbl_806DBDEC);
    Transform(j)->translation[component] = v;
    if (!(j->flags & 0x02000000)) DirtyMatrix(j);
}
static inline void SetRotation(HSD_JObj *j, float v, int component, int line) {
    if (!j) __assert(lbl_806DBDE4, line, lbl_806DBDEC);
    if (j->flags & 0x20000) __assert(lbl_806DBDE4, line + 1, lbl_803EEE30);
    Transform(j)->rotation[component] = v;
    if (!(j->flags & 0x02000000)) DirtyMatrix(j);
}
static inline void SetScale(HSD_JObj *j, float v, int component, int line) {
    if (!j) __assert(lbl_806DBDE4, line, lbl_806DBDEC);
    Transform(j)->scale[component] = v;
    if (!(j->flags & 0x02000000)) DirtyMatrix(j);
}

extern "C" void fn_80240D8C(TrackTask *self) {
    if (self->tracks->channels[0]) {
        float v = StepTrack(self->tracks->channels[0], &self->state[0]);
        SetTranslation(self->joint, v, 0, 0x3B8);
    }
    if (self->tracks->channels[1]) {
        float v = StepTrack(self->tracks->channels[1], &self->state[1]);
        SetTranslation(self->joint, v, 1, 0x3C6);
    }
    if (self->tracks->channels[2]) {
        float v = StepTrack(self->tracks->channels[2], &self->state[2]);
        SetTranslation(self->joint, v, 2, 0x3D4);
    }
    if (self->tracks->channels[3]) {
        float v = StepTrack(self->tracks->channels[3], &self->state[3]);
        v = lbl_806DBE00 * v;
        SetRotation(self->joint, v, 0, 0x2A4);
    }
    if (self->tracks->channels[4]) {
        float v = StepTrack(self->tracks->channels[4], &self->state[4]);
        v = lbl_806DBE00 * v;
        SetRotation(self->joint, v, 1, 0x2B8);
    }
    if (self->tracks->channels[5]) {
        float v = StepTrack(self->tracks->channels[5], &self->state[5]);
        v = lbl_806DBE00 * v;
        SetRotation(self->joint, v, 2, 0x2CC);
    }
    if (self->tracks->channels[6]) {
        float v = StepTrack(self->tracks->channels[6], &self->state[6]);
        SetScale(self->joint, v, 0, 0x325);
    }
    if (self->tracks->channels[7]) {
        float v = StepTrack(self->tracks->channels[7], &self->state[7]);
        SetScale(self->joint, v, 1, 0x333);
    }
    if (self->tracks->channels[8]) {
        float v = StepTrack(self->tracks->channels[8], &self->state[8]);
        SetScale(self->joint, v, 2, 0x341);
    }
}

extern "C" void *fn_80241A5C(TrackTask *self, short destroy) {
    if (self) {
        self->vtable = lbl_804EE68C;
        for (MatrixChild **it = self->children.start; it != self->children.End(); ++it)
            delete *it;
        if (&self->children) {
            if (&self->children) {
                if (&self->children) {
                    if (self->children.start) MemoryManager_TimedFree(self->children.start);
                }
            }
        }
        if (self) self->vtable = lbl_804EE6C0;
        if (destroy > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

JointTask::~JointTask() { vtable = lbl_804EE6C0; }
