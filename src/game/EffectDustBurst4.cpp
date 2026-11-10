/* Dust burst's four independent resource slots share an external curve table.
 * These local views name only fields observed in the target function. */
struct DustVec { float x, y, z; };
struct DustEffect;
struct DustGroup { unsigned char pad00[0x10]; DustEffect *children[4];
    unsigned char pad20[0x64]; float phase; };
struct DustEffect {
    unsigned char pad00[0x14]; unsigned char slot[0x18]; float alpha;
    unsigned char pad30[0x5C]; DustVec position;
    unsigned char pad98[0x18]; float scale; signed char state;
    unsigned char padB5[0xCC - 0xB5]; DustGroup group;
};
/* Time, scale and alpha triples share one array so the shifted interval
 * view can index all three without crossing a subarray boundary. */
#include "game/types/DustCurve.h"
extern "C" {
extern DustCurve Effect_DustBurst4_Update_data_8041A398[4];
extern unsigned char lbl_805DF3D0[0x98];
extern const float lbl_806D5400, lbl_806D540C, lbl_806D5424, lbl_806D549C, lbl_806D54A0;
void fn_800AF4F8(void *);
DustEffect *DrawEffect_SpawnDirect(void (*)(void *));
void DrawEffect_Free(DustEffect *);
void VfxSlot_BindResourceEx(void *, int, int);
void Vec3_Copy(DustVec *, const DustVec *);
void Vec3_Subtract_DestFirst(DustVec *, const DustVec *, const DustVec *);
float Vec3_Magnitude_Wrapper(const DustVec *);
void Vec3_Scale(DustVec *, const DustVec *, float);
void Vec3_Add_DestFirst(DustVec *, const DustVec *, const DustVec *);
void VfxSlot_SetPositionFromVec(void *, const DustVec *);
/* The slot API takes a pointer; this value adapter owns the caller copy. */
static inline void SetPosition(void *slot, DustVec position) {
    VfxSlot_SetPositionFromVec(slot, &position);
}
void VfxSlot_SetScaleUniform(void *, float);

static inline void UpdateChildren(DustEffect *self, DustGroup *group, DustVec &delta, DustGroup *&cursor, DustCurve *curve, const DustVec *globalPosition) {
    int i;
    cursor=group;
    for (i=0; i<4; ++i, ++curve, cursor=(DustGroup *)((unsigned char *)cursor+4)) {
        if (cursor->children[0]) {
            if (curve->values[0] <= group->phase && group->phase < curve->values[2]) {
                if (curve->values[0] <= group->phase && group->phase < curve->values[1]) {
                    float ratio=group->phase-curve->values[0];
                    ratio *= lbl_806D5424/(curve->values[1]-curve->values[0]);
                    cursor->children[0]->scale=ratio*(curve->values[4]-curve->values[3])+curve->values[3];
                    cursor->children[0]->alpha=ratio*(curve->values[7]-curve->values[6])+curve->values[6];
                    cursor->children[0]->scale *= lbl_806D54A0;
                }
                float *next=&curve->values[1];
                if (next[0] <= group->phase && group->phase < next[1]) {
                    float ratio=group->phase-next[0];
                    ratio *= lbl_806D5424/(next[1]-next[0]);
                    cursor->children[0]->scale=ratio*(next[4]-next[3])+next[3];
                    cursor->children[0]->alpha=ratio*(next[7]-next[6])+next[6];
                    cursor->children[0]->scale *= lbl_806D54A0;
                }
            } else {
                cursor->children[0]->scale=lbl_806D5400;
                cursor->children[0]->alpha=lbl_806D5400;
            }
            if (i==3) {
                Vec3_Subtract_DestFirst(&delta,globalPosition,&self->position);
                float magnitude=Vec3_Magnitude_Wrapper(&delta);
                if (magnitude != lbl_806D5400) {
                    Vec3_Scale(&delta,&delta,lbl_806D5424/magnitude);
                    Vec3_Add_DestFirst(&cursor->children[0]->position,&self->position,&delta);
                }
            }
            SetPosition(cursor->children[0]->slot,cursor->children[0]->position);
            VfxSlot_SetScaleUniform(cursor->children[0]->slot,cursor->children[0]->scale);
        }
    }
}

void Effect_DustBurst4_Update(DustEffect *self) {
    DustVec delta;
    int i;
    DustGroup *cursor;
    DustGroup *group = &self->group;
    switch (self->state) {
    case 0: {
        for (i=0; i<4; ++i) {
            group->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (group->children[i]) {
                switch (i) {
                case 0: VfxSlot_BindResourceEx(group->children[i]->slot,0x69,0); break;
                case 1: VfxSlot_BindResourceEx(group->children[i]->slot,0x6B,0); break;
                case 2: VfxSlot_BindResourceEx(group->children[i]->slot,0x6A,0); break;
                case 3: VfxSlot_BindResourceEx(group->children[i]->slot,0x6C,0); break;
                }
                Vec3_Copy(&group->children[i]->position, &self->position);
            }
        }
        group->phase=lbl_806D5400;
        ++self->state;
        break;
    }
    case 1: break;
    }
    group->phase += lbl_806D540C;
    if (lbl_806D549C <= group->phase) {
        i=0;
        for (; i<4; ++i) {
            DrawEffect_Free(group->children[i]);
            group->children[i]=0;
        }
        DrawEffect_Free(self);
        return;
    }
    UpdateChildren(self, group, delta, cursor, Effect_DustBurst4_Update_data_8041A398,
        (const DustVec *)(lbl_805DF3D0+0x80));
}
}
