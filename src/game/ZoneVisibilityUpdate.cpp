#include "game/mapobject/mapobject.h"

struct ZoneVolume;
struct Zone {
    Zone *next;
    ZoneVolume *vol;
    unsigned int mask;
    int id;

    unsigned int GetMask() const { return mask; }
};
#include "game/types/ZoneVisibility.h"
extern "C" {
void *GetCourseScene3D();
void CObj_LoadProjMatrix(void *, Vec3f *);
unsigned char fn_80123480(ZoneVolume *, Vec3f *);
void HSD_JObjClearFlagsAll(HSD_JObj *, unsigned int);
void HSD_JObjSetFlagsAll(HSD_JObj *, unsigned int);

void fn_80173FA4(ZoneVisibility *self) {
    Vec3f pos;
    unsigned int mask;
    Zone *zone;
    if (!self->zones) return;
    void *scene = GetCourseScene3D();
    if (!scene) return;
    CObj_LoadProjMatrix(scene, &pos);
    self->cur = -1;
    for (zone = self->zones; zone; zone = zone->next) {
        unsigned char contains;
        if (zone->vol) contains = fn_80123480(zone->vol, &pos);
        else contains = 0;
        if (contains) {
            mask = zone->GetMask();
            for (int i = 0; i < self->count; i++) {
                HSD_JObj *joint = self->joints[i];
                if (joint) {
                    if (mask & (1 << i)) HSD_JObjClearFlagsAll(joint, 0x10);
                    else HSD_JObjSetFlagsAll(joint, 0x10);
                }
            }
            self->cur = zone->id;
            break;
        }
    }
}
}
