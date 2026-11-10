#include "game/DNFlash_private.h"

extern const unsigned int DNFlash_tail_rodata_803D0390[0x102] = {
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
extern const float DNFlash_tail_rodata_803D0798[3] = {9.0f, 11.0f, 7.0f};
extern const float lbl_803D07A4[3] = {2000.0f, 3300.0f, 10000.0f};
extern const float lbl_803D07B0[3] = {-3700.0f, -5700.0f, -15000.0f};
extern const TriggerBox DNFlash_tail_rodata_803D07BC[4] = {
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

/* fakematch (layout): zero word that fills the 4-byte dtk gap 0x803D08A4-0x803D08A8 at the end of this TU's .rodata,
 * so DNLensflare's .rodata starts at 0x803D08A8. The original most likely had no such object: this is probably the normal
 * inter-TU padding up to an 8-byte boundary, coming from section/object alignment. Replace it when a natural layout match
 * is found. Pending the repo owner's decision on rodata gap fillers. */
__declspec(section ".rodata") extern const unsigned int gap_06_803D08A4_rodata = 0;

static inline int SpawnArea(const float *xLimits, const float *zLimits, float x, float z) {
    int ix = -1;
    int iz = ix;
    for (int i = 0; i < 3; i++) {
        if (x < lbl_803D07A4[i]) { ix = i; break; }
    }
    for (int i = 0; i < 3; i++) {
        if (z > lbl_803D07B0[i]) { iz = i; break; }
    }
    if (ix < 0 || iz < 0) return -1;
    return ix + iz * 3;
}

static inline void StartPart(FlashPart *p, FlashPoint *pt) {
    pt->used = 1;
    p->owner = pt;
    p->active = 1;
    p->life = 8;
    p->scale = DNFlash_tail_rodata_803D0798[rand() % 3];
    p->dscale = lbl_806DB498;
    p->alpha = lbl_806DB49C;
}

void clDNFlash::Spawn() {
    int list[5];

    if (g_playerRenderObj == 0) {
        return;
    }
    const float *m = KartDriver_GetKartRootMtx(g_playerRenderObj);
    int area = SpawnArea(lbl_803D07A4, lbl_803D07B0, m[3], m[11]);
    if (area < 0) {
        return;
    }
    int n = 0;
    int col = area % 3;
    list[n++] = area - col;
    list[n++] = list[0] + 1;
    list[n++] = list[1] + 1;
    if (area != col) {
        list[n++] = col;
    }
    if (area != col + 3) {
        list[n++] = col + 3;
    }
    if (area != col + 6) {
        list[n++] = col + 6;
    }
    FlashPoint *pt = 0;
    int start = rand() % 5;
    for (int tries = 0; tries < 5; tries++) {
        int k = rand() % counts[list[start]];
        int count = Min(counts[list[start]], lbl_806DB494);
        for (int j = 0; j < count; j++) {
            if (k >= counts[list[start]]) {
                k = 0;
            }
            if (points[list[start]][k].used != 1) {
                pt = &points[list[start]][k];
                break;
            }
            k++;
        }
        if (pt) {
            break;
        }
        if (++start >= 5) {
            start = 0;
        }
    }
    if (pt == 0) {
        return;
    }
    for (int i = 0; i < 2; i++) {
        if (free[i]) {
            StartPart(free[i], pt);
            free[i] = 0;
            return;
        }
    }
}

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
    StartPart(this, pt);
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
