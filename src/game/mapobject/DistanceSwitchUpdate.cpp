#include "game/mapobject/mapobject.h"

struct DistanceSwitch {
    DistanceSwitch *next;
    HSD_JObj *farJoint;
    HSD_JObj *nearJoint;
    Vec3f position;
    float radius;
    float distanceSquared;
};
struct DistanceSwitchList { DistanceSwitch *head; };
extern "C" {
void *GetCourseScene3D();
void CObj_LoadProjMatrix(void *, Vec3f *);
unsigned char fn_801375D8(Vec3f *, float);
float PSVECSquareMag(const Vec3f *);
void HSD_JObjClearFlags(HSD_JObj *, unsigned int);
void HSD_JObjSetFlags(HSD_JObj *, unsigned int);
extern const float lbl_806D8E98;

void fn_8017A52C(DistanceSwitchList *self) {
    for (DistanceSwitch *entry = self->head; entry; entry = entry->next) {
        if (lbl_806D8E98 != entry->radius) {
            if (fn_801375D8(&entry->position, entry->radius)) {
                Vec3f pos;
                CObj_LoadProjMatrix(GetCourseScene3D(), &pos);
                Vec3_Subtract(&entry->position, &pos, &pos);
                if (PSVECSquareMag(&pos) > entry->distanceSquared) {
                    HSD_JObjClearFlags(entry->farJoint, 0x10);
                    HSD_JObjSetFlags(entry->nearJoint, 0x10);
                } else {
                    HSD_JObjSetFlags(entry->farJoint, 0x10);
                    HSD_JObjClearFlags(entry->nearJoint, 0x10);
                }
            } else {
                HSD_JObjSetFlags(entry->farJoint, 0x10);
                HSD_JObjSetFlags(entry->nearJoint, 0x10);
            }
        }
    }
}
}
