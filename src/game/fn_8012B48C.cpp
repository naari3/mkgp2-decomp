/*
 * 0x8012B48C..0x8012B924: challenge scene init.
 */
#pragma cplusplus on

struct JObj {
    unsigned char pad0[0x14];
    unsigned int flags;
    unsigned char pad18[0x48];
    float ty;
};

struct clNormal3D {
    unsigned char _opaque[0x5C];
    clNormal3D(void *data, int flags);
};

struct KartTireFX {
    unsigned char _opaque[0xC4];
    KartTireFX(int id, int flags, JObj *fl, JObj *fr, JObj *rl, JObj *rr);
};

struct KartModelEntry {
    void *model;
};

#include "game/types/CharacterDataEntry.h"

struct ChallengeScene {
    clNormal3D *kart;
    KartTireFX *tireFx;
    clNormal3D *body;
    clNormal3D *hand;
    clNormal3D *effect;
    clNormal3D *parts[0x31];
    unsigned char padD8[0x10];
    int id;
    unsigned char padEC[0x38];
    clNormal3D *extra;
    JObj *extraJoint;
    JObj *engine;
    JObj *cartBody;
    float scale;
    float scale2;
    float engineY;
    float bodyY;
    JObj *tireFL;
    JObj *tireFR;
    JObj *tireRL;
    JObj *tireRR;
    unsigned char pad154[4];
    JObj *handGoo;
    JObj *handPa;
    JObj *handFin;
    JObj *rHandNull;
};

extern "C" {
extern char lbl_806D70C8[7];
extern char lbl_806D70D0[5];
extern const float lbl_806D70E0;
extern const float lbl_806D70EC;
extern const float lbl_806D70F0;
extern char *chara_mario_hand_fin_joint[];
extern char *chara_mario_hand_goo_joint[];
extern char *chara_mario_hand_pa_joint[];
extern char *chara_mario_r_hand_null_joint[];
extern char lbl_80356708[];
extern char lbl_80356724[];
extern char *mario_cart_body_joint[];
extern char *mario_cart_engine_joint[];
extern char *mario_cart_tire_fl_joint[];
extern char *mario_cart_tire_fr_joint[];
extern char *mario_cart_tire_rl_joint[];
extern char *mario_cart_tire_rr_joint[];
void __assert(const char *file, int line, const char *cond);
void fn_8012BDF4(struct ChallengeScene *s);
KartModelEntry *GetKartModelNameEntry(int id, int variant);
CharacterDataEntry *GetCharacterDataEntry(int id);
void Object_SetAnimBinding(clNormal3D *obj, void *anim, int flags);
void Object_DriveAnimAndSkin(clNormal3D *obj, float a, float b, clNormal3D *src);
JObj *Archive_GetRootJObj(clNormal3D *obj);
void ObjectTree_BlendOrCopy_Timed(clNormal3D *obj, JObj *src, JObj *dst, int flags, float t);
JObj *ResolveJointByName(clNormal3D *obj, const char *name);
void KartTireFX_SetVisibleAll4Wheels(KartTireFX *fx, int visible);
void clNormal3D_SetScale(clNormal3D *obj, int anim, float t, float a, float b, float c);
void HSD_JObjSetupMatrixSub(JObj *jobj);
}

static inline bool JObjMtxIsDirty(JObj *jobj) {
    bool result;
    if (jobj == 0) {
        __assert(lbl_806D70C8, 0x25D, lbl_806D70D0);
    }
    result = false;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = true;
    }
    return result;
}

static inline void JObjSetupMatrix(JObj *jobj) {
    if (jobj == 0) {
        return;
    }
    if (JObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

static inline float JObjGetWorldY(JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806D70C8, 0x47C, lbl_806D70D0);
    }
    JObjSetupMatrix(jobj);
    return jobj->ty;
}

extern "C" ChallengeScene *fn_8012B48C(ChallengeScene *s, int id, void *anim) {
    KartModelEntry *kart;
    CharacterDataEntry *chara;
    int i;

    fn_8012BDF4(s);
    s->id = id;
    if (s->id < 0 || s->id >= 13) {
        return s;
    }
    kart = GetKartModelNameEntry(s->id, -1);
    chara = GetCharacterDataEntry(s->id);
    s->kart = new clNormal3D(kart->model, 0);
    s->body = new clNormal3D(chara->body, 0);
    s->hand = new clNormal3D(chara->hand, 0);
    s->effect = new clNormal3D(chara->effect, 0);
    Object_SetAnimBinding(s->kart, anim, 0);
    Object_SetAnimBinding(s->body, anim, 0);
    Object_DriveAnimAndSkin(s->body, lbl_806D70E0, lbl_806D70EC, 0);
    for (i = 0; i < 0x31; i++) {
        if (chara->parts[i] != 0) {
            s->parts[i] = new clNormal3D(chara->parts[i], 0);
        } else {
            s->parts[i] = 0;
        }
    }
    Object_DriveAnimAndSkin(s->hand, lbl_806D70F0, lbl_806D70E0, s->parts[0]);
    ObjectTree_BlendOrCopy_Timed(s->body, Archive_GetRootJObj(s->hand), Archive_GetRootJObj(s->body), 0, lbl_806D70E0);
    s->tireFL = ResolveJointByName(s->kart, mario_cart_tire_fl_joint[s->id]);
    s->tireFR = ResolveJointByName(s->kart, mario_cart_tire_fr_joint[s->id]);
    s->tireRL = ResolveJointByName(s->kart, mario_cart_tire_rl_joint[s->id]);
    s->tireRR = ResolveJointByName(s->kart, mario_cart_tire_rr_joint[s->id]);
    s->engine = ResolveJointByName(s->kart, mario_cart_engine_joint[s->id]);
    s->cartBody = ResolveJointByName(s->kart, mario_cart_body_joint[s->id]);
    if (s->id != 12) {
        s->handGoo = ResolveJointByName(s->body, chara_mario_hand_goo_joint[s->id]);
        s->handPa = ResolveJointByName(s->body, chara_mario_hand_pa_joint[s->id]);
        s->handFin = ResolveJointByName(s->body, chara_mario_hand_fin_joint[s->id]);
    }
    s->rHandNull = ResolveJointByName(s->body, chara_mario_r_hand_null_joint[s->id]);
    s->tireFx = new KartTireFX(id, 0, s->tireFL, s->tireFR, s->tireRL, s->tireRR);
    if (s->tireFx != 0) {
        KartTireFX_SetVisibleAll4Wheels(s->tireFx, 0);
    }
    if (s->id == 3) {
        s->extraJoint = ResolveJointByName(s->body, lbl_80356708);
        s->extra = new clNormal3D(lbl_80356724, 0);
        clNormal3D_SetScale(s->extra, 0, lbl_806D70E0, lbl_806D70EC, lbl_806D70E0, lbl_806D70F0);
    }
    s->engineY = JObjGetWorldY(s->engine);
    s->bodyY = JObjGetWorldY(s->cartBody);
    s->scale = lbl_806D70EC;
    s->scale2 = lbl_806D70E0;
    return s;
}
