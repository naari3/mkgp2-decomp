#include "game/DNFlash_private.h"

extern const unsigned int lbl_803D0390[0x102] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x00000000,
};
extern const float lbl_803D0798[3] = {9.0f, 11.0f, 7.0f};
extern const float lbl_803D07A4[3] = {2000.0f, 3300.0f, 10000.0f};
extern const float lbl_803D07B0[3] = {-3700.0f, -5700.0f, -15000.0f};
extern const TriggerBox lbl_803D07BC[4] = {
    {{4709.0f, 0.0f, -5895.0f}, {4493.0f, 0.0f, -5820.0f}},
    {{3515.0f, 0.0f, -7468.0f}, {3428.0f, 0.0f, -7700.0f}},
    {{4300.0f, 0.0f, -2580.0f}, {4265.0f, 0.0f, -2455.0f}},
    {{3150.0f, 0.0f, -3577.0f}, {3220.0f, 0.0f, -3683.0f}},
};
extern const char lbl_803D081C[0xA] = "clDNFlash";
extern const char lbl_803D0828[0x11] = "clMapEffectParts";
extern const char lbl_803D083C[0x1E] = " DeleteMapEffect : clDNFlash\n";
extern const char lbl_803D085C[0x1E] = " CreateMapEffect : clDNFlash\n";
extern const char lbl_803D087C[0x10] = "ef_camflash.dat";
extern const char lbl_803D088C[0x16] = "DNA_cameraF_trans.dat";

__declspec(section ".rodata") extern const unsigned int gap_06_803D08A4_rodata = 0;

void clDNFlash::Update() {
    if (Check() == 1) {
        burst = 180;
    }
    if (--timer <= 0) {
        Spawn();
        timer = rand() % 10;
    }
    if (burst > 0) {
        Spawn();
        burst--;
    }
    for (int i = 0; i < 20; i++) {
        if (!parts[i].active) {
            if (free[0]) {
                free[1] = &parts[i];
            } else {
                free[0] = &parts[i];
            }
        } else if (--parts[i].life <= 0) {
            parts[i].owner->used = 0;
            parts[i].owner = 0;
            parts[i].active = 0;
        } else {
            parts[i].scale += parts[i].dscale;
            if (parts[i].life <= 5) {
                parts[i].alpha -= lbl_806DB4A0;
            }
        }
    }
}

clDNFlash::~clDNFlash() {
    if (fx) {
        delete fx;
        fx = 0;
    }
    DebugPrintf(lbl_803D083C);
}

clDNFlash::clDNFlash() {
    fx = 0;
    timer = 0;
    inside = 0;
    burst = 0;
    DebugPrintf(lbl_803D085C);
    fx = new clNormal3D(lbl_803D087C, 1);
    fn_80182954(Archive_GetRootJObj(fx), 1);
    HSD_JObjSetFlags(Archive_GetRootJObj(fx), 0x200);
    for (int i = 0; i < 20; i++) {
        parts[i].active = 0;
        parts[i].owner = 0;
    }
    for (int i = 0; i < 20; i++) {
        counts[i] = 0;
    }
    free[0] = free[1] = 0;
    clNormal3D *path = new clNormal3D(lbl_803D088C, 0);
    float(*lm)[4] = Object_GetJObjLocalMatrix(path);
    HSD_JObj *jobj = Archive_GetRootJObj(path);
    HSD_JObj *next = 0;
    for (; jobj; jobj = next) {
        Vec3f p;
        GetTranslation(jobj, &p);
        PSMTXMultVec(lm, &p, &p);
        int area = AreaIndexV(p);
        if (area < 0) {
            continue;
        }
        if (counts[area] < 30) {
            points[area][counts[area]].pos.x = p.x;
            points[area][counts[area]].pos.y = p.y;
            points[area][counts[area]].pos.z = p.z;
            points[area][counts[area]].used = 0;
            counts[area]++;
        }
        next = JObjNext(jobj);
        if (next == 0) {
            next = JObjChild(jobj);
        }
    }
    Object_DtorWithGXSync(path, 1);
}

void FlashPart::Tick() {
    if (!active) {
        return;
    }
    if (--life <= 0) {
        owner->used = 0;
        owner = 0;
        active = 0;
        return;
    }
    scale += dscale;
    if (life <= 5) {
        alpha -= lbl_806DB4A0;
    }
}

void FlashPart::Start(FlashPoint *pt) {
    pt->used = 1;
    owner = pt;
    active = 1;
    life = 8;
    scale = lbl_803D0798[rand() % 3];
    dscale = lbl_806DB498;
    alpha = lbl_806DB49C;
}

FlashPartObj::FlashPartObj() {
    active = 0;
    scale = lbl_806DB49C;
    alpha = lbl_806DB490;
    dscale = lbl_806DB490;
    life = 0;
    owner = 0;
}



template int Min<int>(const int &, const int &);
