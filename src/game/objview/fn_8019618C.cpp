#include "game/ObjViewParticles_private.h"

extern "C" {
void *GetCourseScene3D();
void CObj_LoadProjMatrix(void *, Vec3f *);
float PSVECSquareMag(const Vec3f *);
float Vec3_Dot(const Vec3f *, const Vec3f *);
void PSMTXMultVec(const Mtx, const Vec3f *, Vec3f *);
float LUT_Sin12Bit(float);
float fn_80186960(float);
float Saturate_Double(float, float, float);
}

static inline ObjParticle *FindFreeParticle(ObjParticleView *self) {
    for (ObjParticle *p = self->particles; p < self->particles + 70; p++) {
        if (lbl_806D9560 == p->age) return p;
    }
    return 0;
}
static inline float PositionRandom(ObjParticleView *self, float scale, float base) {
    if (self->positionRandom >= 64) self->positionRandom = 0;
    return scale * lbl_80495994[self->positionRandom++] + base;
}

extern "C" void fn_8019618C(ObjParticleView *self) {
    void *scene = GetCourseScene3D();
    if (scene == 0) return;
    Vec3f camera;
    Vec3f delta;
    Mtx rotation;
    CObj_LoadProjMatrix(scene, &camera);
    for (int i = 0; i < 7; i++) {
        if (self->directions[i].cooldown > 0) {
            self->directions[i].cooldown--;
            continue;
        }
        Vec3_Subtract(&camera, &lbl_8037D888[i].start, &delta);
        float distance = PSVECSquareMag(&delta);
        float facing = Vec3_Dot(&delta, &self->directions[i].direction);
        if (distance < lbl_806D956C && facing >= 0.0f) {
            ObjParticle *p = FindFreeParticle(self);
            if (p != 0) {
                p->age = lbl_806D9570;
                p->position.x = PositionRandom(self, lbl_806D9578, lbl_806D9574) + lbl_8037D888[i].start.x;
                p->position.y = PositionRandom(self, lbl_806D9580, lbl_806D957C) + lbl_8037D888[i].start.y;
                p->position.z = PositionRandom(self, lbl_806D9578, lbl_806D9574) + lbl_8037D888[i].start.z;
                p->rotation.x = lbl_806D9570;
                p->rotation.y = lbl_806D9570;
                p->rotation.z = lbl_806D9570;
                p->alpha = lbl_806D9584;
                if (self->velocityRandom >= 48) self->velocityRandom = 0;
                p->ageStep = lbl_806D9588 * lbl_80495A94[self->velocityRandom++] + lbl_806D9588;
                p->velocity.x = p->ageStep * self->directions[i].direction.x;
                p->velocity.y = p->ageStep * self->directions[i].direction.y;
                p->velocity.z = p->ageStep * self->directions[i].direction.z;
                if (self->velocityRandom >= 48) self->velocityRandom = 0;
                PSMTXRotRad(rotation, 'Y', lbl_806D9584 * lbl_80495A94[self->velocityRandom++] + lbl_806D958C);
                PSMTXMultVec(rotation, &p->velocity, &p->velocity);
                if (self->spinRandom >= 48) self->spinRandom = 0;
                p->spin.x = lbl_806D9594 * lbl_80495A94[self->spinRandom++] + lbl_806D9590;
                if (self->spinRandom >= 48) self->spinRandom = 0;
                p->spin.y = lbl_806D9594 * lbl_80495A94[self->spinRandom++] + lbl_806D9590;
                if (self->spinRandom >= 48) self->spinRandom = 0;
                p->spin.z = lbl_806D9594 * lbl_80495A94[self->spinRandom++] + lbl_806D9590;
                if (self->phaseRandom >= 48) self->phaseRandom = 0;
                p->sway = lbl_806D9584 * lbl_80495A94[self->phaseRandom++] + lbl_806D9570;
                if (self->phaseRandom >= 48) self->phaseRandom = 0;
                p->phase = lbl_806D9598 * lbl_80495A94[self->phaseRandom++] + lbl_806D9570;
                if (self->phaseRandom >= 48) self->phaseRandom = 0;
                p->phaseStep = lbl_806D95A0 * lbl_80495A94[self->phaseRandom++] + lbl_806D959C;
            }
            if (self->cooldownRandom >= 64) self->cooldownRandom = 0;
            self->directions[i].cooldown = (int)(lbl_806D959C * lbl_80495994[self->cooldownRandom++] + lbl_806D95A4);
        }
    }
    for (ObjParticle *p = self->particles; p < self->particles + 70; p++) {
        if (lbl_806D9560 != p->age) {
            PSVECAdd(&p->position, &p->velocity, &p->position);
            PSVECAdd(&p->rotation, &p->spin, &p->rotation);
            p->position.x = p->sway * LUT_Sin12Bit(p->phase) + p->position.x;
            p->position.z = p->sway * fn_80186960(p->phase) + p->position.z;
            p->phase = p->phase + p->phaseStep;
            p->age = p->age + p->ageStep;
            if (p->age < lbl_806D95A8) {
                p->alpha = Saturate_Double(lbl_806D95AC * p->age, lbl_806D9570, lbl_806D9584);
            } else {
                p->alpha = Saturate_Double(lbl_806D9584 - lbl_806D95B0 * (p->age - lbl_806D95B4), lbl_806D9570, lbl_806D9584);
            }
            if (p->alpha <= lbl_806D9570) p->age = lbl_806D9560;
        }
    }
}
