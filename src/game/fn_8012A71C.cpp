/*
 * 0x8012A71C..0x8012B394: challenge scene update.
 * Steers the preview driver toward the target lean, blends the driver /
 * lean / reaction animations, toggles the parts per mode, bobs two joints
 * and drives the attachment bound to a driver joint.
 */
#pragma cplusplus on

#include "game/types/HSD_JObj.h"

#include "game/types/CharacterData.h"

typedef struct ChallengeDriver {
    void *kart;         /* 0x000 */
    void *pad04;
    void *driver;       /* 0x008 */
    void *base;         /* 0x00C */
    void *over;         /* 0x010 */
    void *anim[50];     /* 0x014 */
    float vel[3];       /* 0x0DC */
    int charId;         /* 0x0E8 */
    int overAnim;       /* 0x0EC */
    int action;         /* 0x0F0 */
    int dir;            /* 0x0F4 */
    float steer;        /* 0x0F8 */
    float lean;         /* 0x0FC */
    float leanBlend;    /* 0x100 */
    int leanSet;        /* 0x104 */
    float frame;        /* 0x108 */
    float speed;        /* 0x10C */
    float frameEnd;     /* 0x110 */
    float inBlend;      /* 0x114 */
    float inBlendStep;  /* 0x118 */
    float outBlend;     /* 0x11C */
    float outBlendStep; /* 0x120 */
    void *attach;       /* 0x124 */
    HSD_JObj *attachJoint; /* 0x128 */
    HSD_JObj *bob0;     /* 0x12C */
    HSD_JObj *bob1;     /* 0x130 */
    float bobAmp;       /* 0x134 */
    float bobPhase;     /* 0x138 */
    float bobBase0;     /* 0x13C */
    float bobBase1;     /* 0x140 */
    unsigned char pad144[0x10];
    int partMode;       /* 0x154 */
    void *part0;        /* 0x158 */
    void *part1;        /* 0x15C */
    void *part2;        /* 0x160 */
} ChallengeDriver;

extern "C" {
void *Archive_GetRootJObj(void *obj);
CharacterData *GetCharacterDataEntry(int id);
void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
void JObj_Hide(void *obj, void *part, int flag);
void JObj_Show(void *obj, void *part, int flag);
float LUT_Sin12Bit(float deg);
void ObjectTree_BlendOrCopy_Timed(void *obj, void *a, void *b, void *c, float t);
void Object_DriveAnimAndSkin(void *obj, float frame, float rate, void *anim);
void Object_DriveAnimMatrix(void *obj);
float Object_GetField8(void *obj);
void Object_SetAnimBinding(void *obj, float (*mtx)[4], int flag);
void Object_SetField8_10_14(void *obj, float a, float b, float c);
float Vec3_Magnitude(float *v);
void __assert(char *file, int line, char *expr);
void clNormal3D_Exec(void *obj);
extern float lbl_806CF018;
extern char lbl_806D70C8[7];
extern char lbl_806D70D0[5];
}

static inline int HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    unsigned char result;
    if (!jobj) {
        __assert(lbl_806D70C8, 0x25d, lbl_806D70D0);
    }
    result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, float y)
{
    if (!jobj) {
        __assert(lbl_806D70C8, 0x3c6, lbl_806D70D0);
    }
    jobj->translate.y = y;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void HSD_JObjSetupMatrix(HSD_JObj *jobj)
{
    if (jobj == 0) {
        __assert(lbl_806D70C8, 0x47C, lbl_806D70D0);
    }
    if (jobj != 0 && HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

extern "C" int fn_8012A71C(ChallengeDriver *s, float target)
{
    float leanFrame;
    float end;
    float bob;
    int action;
    int t;

    if (s->kart == 0 || s->driver == 0) {
        return 0;
    }
    Object_DriveAnimMatrix(s->kart);

    if (s->steer > target) {
        if ((s->steer -= lbl_806CF018) < target) {
            s->steer = target;
        }
    } else {
        if ((s->steer += lbl_806CF018) > target) {
            s->steer = target;
        }
    }

    if (-0.26f < s->steer && s->steer < 0.26f) {
        if (s->lean < 0.0f) {
            if ((s->lean += 0.045f) > 0.0f) {
                s->lean = 0.0f;
            }
        } else if (s->lean > 0.0f) {
            if ((s->lean -= 0.045f) < 0.0f) {
                s->lean = 0.0f;
            }
        }
    } else if (s->steer < 0.0f) {
        if ((s->lean -= 0.045f) < -1.0f) {
            s->lean = -1.0f;
        }
    } else {
        if ((s->lean += 0.045f) > 1.0f) {
            s->lean = 1.0f;
        }
    }

    leanFrame = 30.0f * (2.0f - (1.0f + s->lean));
    action = s->action;
    if (action == 0x2a || action == 0x2b) {
        Object_DriveAnimAndSkin(s->base, s->frame, 0.0f, s->anim[action]);
        ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), 0, 0.0f);
        if (s->action == 0x2a) {
            end = GetCharacterDataEntry(s->charId)->anim1C;
        } else {
            end = GetCharacterDataEntry(s->charId)->anim24;
        }
        if ((s->frame += s->speed) >= end) {
            s->frame = 0.0f;
        }
    } else if (action == 1) {
        Object_DriveAnimAndSkin(s->base, leanFrame, 0.0f, s->anim[s->dir]);
        Object_DriveAnimAndSkin(s->over, -1.0f, 0.0f, s->anim[0]);
        ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->over), Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), s->outBlend);
        if ((s->outBlend += s->outBlendStep) >= 1.0f) {
            s->action = 0;
        }
    } else if (action != 0) {
        if (action != -1 && s->frame < s->frameEnd) {
            Object_DriveAnimAndSkin(s->base, s->frame, 0.0f, s->anim[action]);
            s->frame += s->speed;
            if (s->inBlend < 1.0f) {
                Object_DriveAnimAndSkin(s->over, -1.0f, 0.0f, s->anim[s->overAnim]);
                ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->over), Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), s->inBlend);
                s->inBlend += s->inBlendStep;
            } else {
                clNormal3D_Exec(s->anim[s->action]);
                Object_DriveAnimAndSkin(s->over, s->frame, 0.0f, s->anim[s->action]);
                ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->over), Archive_GetRootJObj(s->driver), 0, 0.0f);
            }
        } else {
            Object_DriveAnimAndSkin(s->base, leanFrame, 0.0f, s->anim[s->leanSet + s->dir]);
            Object_DriveAnimAndSkin(s->over, -1.0f, 0.0f, s->anim[s->action]);
            ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->over), Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), s->outBlend);
            s->outBlend += s->outBlendStep;
            if (s->outBlend >= 1.0f) {
                s->action = 0;
            }
        }
    } else if (-0.26f < s->lean && s->lean < 0.26f) {
        s->leanSet = 5;
        if ((s->frame += 1.0f) > 60.0f) {
            s->frame = 0.0f;
        }
        Object_DriveAnimAndSkin(s->base, s->frame, 0.0f, s->anim[s->dir + 5]);
        if (s->leanBlend < 1.0f) {
            Object_DriveAnimAndSkin(s->over, -1.0f, 0.0f, s->anim[s->dir]);
            ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->over), Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), s->leanBlend);
            if ((s->leanBlend += 0.1f) >= 1.0f) {
                s->leanBlend = 1.0f;
            }
        } else {
            ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), 0, 0.0f);
        }
    } else if (0.9f < s->lean) {
        s->leanSet = 10;
        if ((s->frame += 1.0f) > 60.0f) {
            s->frame = 0.0f;
        }
        Object_DriveAnimAndSkin(s->base, s->frame, 0.0f, s->anim[s->dir + 10]);
        if (s->leanBlend < 1.0f) {
            Object_DriveAnimAndSkin(s->over, -1.0f, 0.0f, s->anim[s->dir]);
            ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->over), Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), s->leanBlend);
            if ((s->leanBlend += 0.1f) >= 1.0f) {
                s->leanBlend = 1.0f;
            }
        } else {
            ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), 0, 0.0f);
        }
    } else if (s->lean < -0.9f) {
        s->leanSet = 15;
        if ((s->frame += 1.0f) > 60.0f) {
            s->frame = 0.0f;
        }
        Object_DriveAnimAndSkin(s->base, s->frame, 0.0f, s->anim[s->dir + 15]);
        if (s->leanBlend < 1.0f) {
            Object_DriveAnimAndSkin(s->over, -1.0f, 0.0f, s->anim[s->dir]);
            ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->over), Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), s->leanBlend);
            if ((s->leanBlend += 0.1f) >= 1.0f) {
                s->leanBlend = 1.0f;
            }
        } else {
            ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), 0, 0.0f);
        }
    } else {
        Object_DriveAnimAndSkin(s->base, leanFrame, 0.0f, s->anim[s->dir]);
        if (s->leanBlend > 0.0f) {
            Object_DriveAnimAndSkin(s->over, -1.0f, 0.0f, s->anim[s->leanSet + s->dir]);
            ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->over), Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), 1.0f - s->leanBlend);
            if ((s->leanBlend -= 0.1f) <= 0.0f) {
                s->leanBlend = 0.0f;
                s->leanSet = 0;
            }
        } else {
            ObjectTree_BlendOrCopy_Timed(s->driver, Archive_GetRootJObj(s->base), Archive_GetRootJObj(s->driver), 0, 0.0f);
        }
    }

    Object_DriveAnimMatrix(s->driver);
    if (s->partMode == 2) {
        if (s->part0 != 0) {
            JObj_Hide(s->driver, s->part0, 0x10);
        }
        if (s->part1 != 0) {
            JObj_Hide(s->driver, s->part1, 0x10);
        }
        if (s->part2 != 0) {
            JObj_Show(s->driver, s->part2, 0x10);
        }
    } else if (s->partMode == 1) {
        if (s->part0 != 0) {
            JObj_Hide(s->driver, s->part0, 0x10);
        }
        if (s->part1 != 0) {
            JObj_Show(s->driver, s->part1, 0x10);
        }
        if (s->part2 != 0) {
            JObj_Hide(s->driver, s->part2, 0x10);
        }
    } else {
        if (s->part0 != 0) {
            JObj_Show(s->driver, s->part0, 0x10);
        }
        if (s->part1 != 0) {
            JObj_Hide(s->driver, s->part1, 0x10);
        }
        if (s->part2 != 0) {
            JObj_Hide(s->driver, s->part2, 0x10);
        }
    }

    s->bobPhase += 98.67f;
    bob = 0.2f * (s->bobAmp * LUT_Sin12Bit(s->bobPhase));
    HSD_JObjSetTranslateY(s->bob0, bob + s->bobBase0);
    bob = 0.08f * (s->bobAmp * LUT_Sin12Bit(s->bobPhase));
    HSD_JObjSetTranslateY(s->bob1, bob + s->bobBase1);

    if (s->attach != 0 && s->attachJoint != 0) {
        HSD_JObj *joint;

        clNormal3D_Exec(s->attach);
        if ((int)Object_GetField8(s->attach) % 30 == 0) {
            float mag;

            t = 0;
            mag = Vec3_Magnitude(s->vel);
            if (mag > 0.6f) {
                t = 90;
            } else if (mag > 0.4f) {
                t = 60;
            } else if (mag > 0.2f) {
                t = 30;
            }
            Object_SetField8_10_14(s->attach, t, 1.0f, t + 30);
        }
        joint = s->attachJoint;
        HSD_JObjSetupMatrix(joint);
        Object_SetAnimBinding(s->attach, joint->mtx, 0);
        clNormal3D_Exec(s->attach);
        Object_DriveAnimMatrix(s->attach);
    }
    return 1;
}
