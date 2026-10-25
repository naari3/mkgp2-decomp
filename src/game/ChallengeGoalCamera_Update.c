/* ChallengeGoalCamera_Update (0x80124AE8): advances the challenge goal
 * camera animation and loads its projection into GX. */
typedef struct { float x, y, z; } Vec;

typedef struct GoalCamAnim {
    unsigned char pad0[4];
    void *cobj;
    unsigned char pad8[0x3084 - 8];
    unsigned char restart;
    unsigned char pad3085[3];
    float rate;
    float frame;
} GoalCamAnim;

typedef struct ChallengeGoalCamera {
    GoalCamAnim *anim;
    float t;
} ChallengeGoalCamera;

extern void PSMTXCopy(const float src[3][4], float dst[3][4]);
extern void PSMTXMultVec(const float m[3][4], const Vec *src, Vec *dst);
extern void Vec3_Normalize(Vec *src, Vec *dst);
extern void HSD_CObjReqAnim(void *cobj, float frame);
extern void HSD_CObjAnim(void *cobj);
extern void CObj_LoadProjMatrix(GoalCamAnim *anim, Vec *out);
extern void CObj_ApplyScissor(GoalCamAnim *anim, Vec *out);
extern void CObj_LoadIntoGX(void *cam, Vec *v);
extern void CObj_ApplyViewport(void *cam, Vec *v);
extern void SceneRender_SetViewportRect(void *rc, float a, float b, float c, float d, float e, float f);
extern void *g_raceCamera;

void ChallengeGoalCamera_Update(ChallengeGoalCamera *self, void *cam, float (*mtx)[4])
{
    Vec scissor;
    Vec proj;
    float m[3][4];
    GoalCamAnim *a;

    if (self->anim == 0 || cam == 0 || mtx == 0) {
        return;
    }
    PSMTXCopy(mtx, m);
    Vec3_Normalize((Vec *)m[0], (Vec *)m[0]);
    Vec3_Normalize((Vec *)m[1], (Vec *)m[1]);
    Vec3_Normalize((Vec *)m[2], (Vec *)m[2]);
    a = self->anim;
    {
        float f = a->frame;
        float t = self->t;
        if (!(f < 0.0f) && !(t < 0.0f)) {
            a->restart = 1;
            a->frame = t;
        }
    }
    a = self->anim;
    if (-1.0f != a->rate) {
        if (a->restart) {
            a->restart = 0;
        } else {
            a->frame += a->rate;
        }
        HSD_CObjReqAnim(a->cobj, a->frame);
        HSD_CObjAnim(a->cobj);
    }
    CObj_LoadProjMatrix(self->anim, &proj);
    CObj_ApplyScissor(self->anim, &scissor);
    PSMTXMultVec(m, &proj, &proj);
    PSMTXMultVec(m, &scissor, &scissor);
    CObj_LoadIntoGX(cam, &proj);
    CObj_ApplyViewport(cam, &scissor);
    if (g_raceCamera != 0) {
        SceneRender_SetViewportRect(g_raceCamera, m[0][3], m[1][3], m[2][3], m[0][1], m[1][1], m[2][1]);
    }
    if ((self->t += 1.0f) > 298.0f) {
        self->t = 298.0f;
    }
}
