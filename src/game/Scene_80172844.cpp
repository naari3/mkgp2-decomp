/*
 * 0x80172844..0x80172948: homing target handle update: projects the world
 * anchor to the screen and eases the marker toward it. The TU owns the homing
 * marker .rodata 0x8036E8B0..0x8036E978 (texture names, slot table, colors,
 * wobble offsets and the zero initializer of the screen position).
 */

#include "game/types/Vec3f.h"

#include "game/types/Vec2f.h"

#include "game/types/SlotDesc.h"

extern const char lbl_8036E8B0[0x14] = "homing_target.tpl";
extern const char lbl_8036E8C4[0x10] = "target_line.tpl";
extern const SlotDesc Scene_80172844_rodata_8036E8D4[4] = {
    {{1.0f, 1.0f, 78.0f, 78.0f}, 0},
    {{80.0f, 1.0f, 113.0f, 113.0f}, 0},
    {{194.0f, 1.0f, 52.0f, 52.0f}, 0},
    {{0.0f, 0.0f, 128.0f, 128.0f}, 1},
};
extern const float HomingMarkerUpdate_rodata_8036E924[4] = {0.0f, 1.0f, 1.0f, 1.0f};
extern const float HomingMarkerUpdate_rodata_8036E934[4] = {1.0f, 1.0f, 1.0f, 1.0f};
extern const float HomingMarkerUpdate_rodata_8036E944[4] = {1.0f, 0.0f, 0.0f, 1.0f};
extern const Vec2f Scene_801734B0_rodata_8036E954[3] = {
    {5.0f, 3.0f},
    {3.0f, 5.0f},
    {4.0f, 4.0f},
};

struct SharedRef {
    int id;
    float t;
    unsigned char active;
    Vec3f pos;

    void SetPos(float x, float y, float z) {
        pos.x = x;
        pos.y = y;
        pos.z = z;
    }
};

#include "game/types/EffectHandle.h"

extern "C" {
void *GetCourseScene3D(void);
void CObj_ProjectPoint(void *, float *, float *, float *, float *, float, float, float);
void fn_80172948(SharedRef *);

void fn_80172844(EffectHandle *self) {
    void *scene;
    Vec3f screen = {0.0f, 0.0f, 0.0f};
    float depth;

    scene = GetCourseScene3D();
    if (scene) {
        CObj_ProjectPoint(scene, &screen.x, &screen.y, &screen.z, &depth, self->anchor.x, self->anchor.y,
                          self->anchor.z);
    }
    self->blend += 0.033333335f;
    if (self->blend > 1.0f) {
        self->blend = 1.0f;
    }
    self->cur.x += self->blend * (screen.x - self->cur.x);
    self->cur.y += self->blend * (screen.y - self->cur.y);
    self->cur.z += self->blend * (screen.z - self->cur.z);
    self->ref->SetPos(self->cur.x, self->cur.y, self->cur.z);
    fn_80172948(self->ref);
}

}
