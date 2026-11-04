/* 0x801752C0..0x80179650: exact course map effects.
 * The reversed EH suffix is preserved in mapeffect_nm1.cpp.
 */
#define MAPEFFECT_DEFINE_DATA
#include "game/mapeffect_private.h"

#pragma exceptions on

inline clMapEffectWCC::clMapEffectWCC(JObj *root, int arg) {
    parts = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        parts->Add(4, 2, new P_fn_801967F0());
        parts->Add(0, 0, new clMoveTex(root, lbl_80370E58));
    }
}

inline int PartsList::Add(int kind, int prio, clMapEffectParts *parts) {
    if (!parts) {
        return 0;
    }
    if (head) {
        head->Append(kind, prio, parts);
    } else {
        head = new PartsNode(kind, prio, parts);
    }
    return 1;
}


inline clMapEffectDN::clMapEffectDN(JObj *root, int arg) {
    parts = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        parts->Add(0, 0, new clMoveTex(root, lbl_803710A4));
        parts->Add(2, 2, new P_fn_80228884(ResolveJointByName(root, "DN_stadium_DNA_all_joint")));
        parts->Add(4, 2, new P_fn_8022A890(ResolveJointByName(root, "DN_stadium_DNA_all_joint")));
        if (g_gameMode != 2) {
            parts->Add(0x10, 0x24, new P_fn_80229180());
            parts->Add(0x20, 2, new P_fn_80229768(ResolveJointByName(root, "DN_stadium_DNA_all_joint")));
        }
        if (g_longRoundFlag == 1 && g_cupId != 0x10) {
            parts->Add(1, 2, new P_fn_80227B98(ResolveJointByName(root, "DN_stadium_DNA_all_joint")));
            parts->Add(0x10, 2, new P_MapWaterEffect_Init());
            parts->Add(0, 0, new clReverbCtrl(lbl_803719F8, 1));
        } else {
            parts->Add(0, 0, new clReverbCtrl(lbl_803719BC, 1));
        }
    }
    fn_8016B248(0);
    fn_8016B178(2);
    fn_8016B160(1000.0f);
    fn_8016B148(15000.0f);
    fn_8016B0F0(0xB9, 0xFF, 0xFF);
}

inline clMapEffectYI::clMapEffectYI(JObj *root, int arg) {
    parts = 0;
    state = 0;
    parts = new PartsList();
    if (parts) {
        parts->Add(0, 0, new clMoveTex(root, lbl_8037103C));
    }
    if (g_longRoundFlag == 1) {
        parts->Add(0, 0, new clReverbCtrl(lbl_80371908, 3));
    } else {
        parts->Add(0, 0, new clReverbCtrl(lbl_80371890, 2));
    }
    state = new YIState();
}

inline clMapEffectRB::clMapEffectRB(JObj *root, int arg) {
    parts = 0;
    ctx = 0;
    done = 0;
    parts = new PartsList();
    ctx = (PartsCtx *)arg;
    if (parts) {
        parts->Add(1, 1, new P_fn_8018EDE0(root));
        parts->Add(2, 2, new P_fn_8018E108(root));
        parts->Add(4, 0, new P_fn_8018E510(ResolveJointByName(root, "RB_road_eisei_joint")));
        parts->Add(0, 0, new clMoveTex(root, lbl_80370FD0));
        if (!g_longRoundFlag && g_courseVariantIdx == 2) {
            parts->Add(0, 0, new clReverbCtrl(lbl_803717DC, 3));
        } else {
            parts->Add(0, 0, new clReverbCtrl(lbl_80371764, 2));
        }
    }
}

inline clMapEffectKP::clMapEffectKP(JObj *root, int arg) {
    parts = 0;
    zone = 0;
    x0c = 0.0f;
    x10 = 0;
    x14 = 0.0f;
    x18 = 0;
    x1c = 0;
    x20 = 0;
    x24 = 0.0f;
    x28 = 0.0f;
    x2c = 0;
    parts = new PartsList();
    if (parts) {
        clMapEffectParts *a;
        clMapEffectParts *b;

        parts->Add(1, 2, new P_fn_801715A0());
        parts->Add(2, 2, new P_fn_8016FD0C(ResolveJointByName(root, "KP_castle_KP_sekizou_null_joint")));
        parts->Add(4, 2, new P_fn_8016D920(ResolveJointByName(root, "KP_castle_kp04_candle_joint")));
        parts->Add(8, 0x22, new P_fn_80170544(ResolveJointByName(root, "KP_castle_kp021_thunder_joint")));
        parts->Add(0x10, 2, new P_fn_8016D2D0(ResolveJointByName(root, "KP_castle_KP_fb_null_joint")));
        parts->Add(0x20, 2, new P_fn_8016E568());
        switch (g_courseVariantIdx) {
        case 0:
            if (g_longRoundFlag) {
                break;
            } else if (g_gameMode) {
                break;
            }
            break;
        case 1:
            parts->Add(0x100, 2, new P_fn_80170B5C());
            break;
        case 2:
            if (!g_longRoundFlag) {
                parts->Add(0x100, 2, new P_fn_80170B5C());
            } else {
                parts->Add(0x100, 2, new P_fn_80170B5C());
            }
            break;
        }
        parts->Add(0, 0, new clMoveTex(root, lbl_80370EEC));
        if (!g_longRoundFlag) {
            parts->Add(0, 0, new clReverbCtrl(lbl_8037150C, 6));
        } else {
            parts->Add(0, 0, new clReverbCtrl(lbl_80371674, 4));
        }
        a = parts->Find(1);
        b = parts->Find(0x10);
        if (a && b) {
            ((P_fn_8016D2D0 *)b)->link = a;
        }
    }
    x10 = ResolveJointByName(root, "KP_castle_kp_frag_joint");
    x1c = ResolveJointByName(root, "KP_castle_kp01_skydome_joint");
    x20 = ResolveJointByName(root, "KP_castle_kp03_skycloud_joint");
    zone = NewKPZone();
    {
        JObj *j;
        JObj *p;

        p = ResolveJointByName(root, "KP_castle_Ef_M2_06_isekifire_joint");
        for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
            DrawEffect_SpawnWithMatrix(8, JObjGetMtxPtr(j));
        }
    }
    fn_8016B248(0);
    fn_8016B178(0);
    fn_8016B160(65535.0f);
    fn_8016B148(65535.0f);
    fn_8016B0F0(0xFF, 0x7F, 0);
    x0c = 0.0f;
}

inline clMapEffectParts *PartsList::Find(unsigned int kind) {
    return head ? head->Find(kind) : 0;
}

inline clMapEffectParts *PartsNode::Find(unsigned int kind) {
    if (this->kind == kind) {
        return parts;
    }
    return next ? next->Find(kind) : 0;
}

inline clMapEffectPC::clMapEffectPC(JObj *root, int arg) {
    parts = 0;
    ctx = 0;
    parts = new PartsList();
    ctx = (PartsCtx *)arg;
    done = 0;
    if (parts) {
        parts->Add(4, 2, new P_fn_8018D3E0());
        if (!g_longRoundFlag) {
            parts->Add(0, 0, new clReverbCtrl(lbl_8037141C, 2));
        } else {
            parts->Add(8, 1, new P_fn_8018CFC4());
            parts->Add(0, 0, new clReverbCtrl(lbl_80371494, 2));
        }
    }
}

inline clMapEffectWC::clMapEffectWC(JObj *root, int arg) {
    parts = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        parts->Add(1, 2, new P_fn_801987C4());
        parts->Add(4, 2, new P_fn_801967F0());
        if (g_longRoundFlag == 1) {
            parts->Add(2, 4, new P_fn_80197D20());
        }
        parts->Add(0, 0, new clMoveTex(root, lbl_80370E04));
        if (!g_longRoundFlag) {
            parts->Add(0, 0, new clReverbCtrl(lbl_8037123C, 4));
        } else {
            parts->Add(0, 0, new clReverbCtrl(lbl_8037132C, 4));
        }
    }
}

inline clMapEffectDK::clMapEffectDK(JObj *root, int arg) {
    parts = 0;
    x08 = 0;
    x0c = 0;
    x10 = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        if (!g_longRoundFlag) {
            parts->Add(1, 2, new P_fn_8018A70C());
            parts->Add(2, 2, new P_fn_8016AB58());
            parts->Add(4, 2, new P_fn_8016A1AC());
        } else {
            parts->Add(0x100, 0, new P_fn_8016A3D4(ResolveJointByName(root, "DK_jungle_Ef_M2_02_kiri_joint")));
            parts->Add(0, 0, new clReverbCtrl(lbl_8037114C, 4));
        }
        parts->Add(0x10, 2, new P_MapWaterEffect_Init());
        if (g_courseVariantIdx == 1) {
            parts->Add(0x20, 4, new P_fn_8016AF3C());
        }
    }
    switch (g_courseVariantIdx) {
    case 0:
        fn_8016B248(0);
        fn_8016B178(2);
        fn_8016B160(0.0f);
        fn_8016B148(10000.0f);
        fn_8016B0F0(0xC0, 0xC0, 0xC0);
        break;
    case 1:
        fn_8016B248(0);
        fn_8016B178(2);
        fn_8016B160(0.0f);
        fn_8016B148(3000.0f);
        fn_8016B0F0(0xC0, 0xC0, 0xC0);
        break;
    case 2:
        fn_8016B248(0);
        fn_8016B178(2);
        fn_8016B160(0.0f);
        fn_8016B148(10000.0f);
        fn_8016B0F0(0xC0, 0xC0, 0xC0);
        break;
    }
    JObj *j;
    JObj *p;

    p = ResolveJointByName(root, "DK_jungle_Ef_M2_02_fire_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SetFlagsByte(DrawEffect_SpawnWithMatrix(8, JObjGetMtxPtr(j)), 0);
    }
    p = ResolveJointByName(root, "DK_jungle_Ef_M2_02_fire_a_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SetFlagsByte(DrawEffect_SpawnWithMatrix(8, JObjGetMtxPtr(j)), 1);
    }
    p = ResolveJointByName(root, "DK_jungle_Ef_M2_02_fire_b_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SetFlagsByte(DrawEffect_SpawnWithMatrix(8, JObjGetMtxPtr(j)), 2);
    }
    p = ResolveJointByName(root, "DK_jungle_Ef_M2_02_kiri_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SpawnWithMatrix(7, JObjGetMtxPtr(j));
    }
    p = ResolveJointByName(root, "DK_jungle_Ef_M2_08_noroshi_joint");
    for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
        DrawEffect_SpawnWithMatrix(10, JObjGetMtxPtr(j));
    }
}

inline clMapEffectMR::clMapEffectMR(JObj *root, int arg) {
    JObj *j;

    parts = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        switch (g_courseVariantIdx) {
        case 0:
            parts->Add(4, 4, new P_fn_80171CD0("halation.dat", ResolveJointByName(root, "MR_highway_sun_joint"), 1.0f, 1.0f));
            break;
        case 1:
            parts->Add(4, 4, new P_fn_80171CD0("halation_tw.dat", ResolveJointByName(root, "MR_highway_sun_joint"), 1.0f, 1.0f));
            break;
        case 2:
            parts->Add(0x40, 2, new P_fn_80187878());
            break;
        }
        parts->Add(1, 2, new P_fn_8018FEAC());
        parts->Add(2, 2, new P_fn_8018F614());
        parts->Add(0x20, 2, new P_fn_80187410());
        if (g_longRoundFlag == 1) {
            parts->Add(8, 2, new P_fn_8018A70C());
            parts->Add(0x10, 2, new P_fn_80187BF4());
        }
        parts->Add(0, 0, new clMoveTex(root, lbl_80370D2C));
        parts->Add(0, 0, new clReverbCtrl(lbl_803710D4, 2));
    }
    j = ResolveJointByName(root, "MR_highway_volcano_joint");
    if (j) {
        DrawEffect_SpawnWithMatrix(0xB, JObjGetMtxPtr(j));
    }
}

inline clMapEffectMR::~clMapEffectMR() {
    if (parts) {
        delete parts;
    }
    if (done) {
        fn_8016C394(0x24);
    }
}

inline PartsList::~PartsList() {
    if (head) {
        delete head;
    }
}

inline PartsNode::~PartsNode() {
    if (next) {
        delete next;
    }
    delete parts;
}

inline void clMapEffectMR::Update() {
    if (parts) {
        parts->Update();
    }
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x24);
        }
    } else if (done == 1) {
        fn_8016C3C8(0x24, 1);
        done = 0;
    }
}

inline void PartsList::Update() {
    if (head) {
        head->Update();
    }
}

inline void PartsNode::Update() {
    done = 0;
    if (!(prio & 0x40)) {
        parts->Update();
        done = 1;
    }
    if (next) {
        next->Update();
    }
}

inline void clMapEffectMR::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline void PartsList::Draw(int mask) {
    if (head) {
        head->Draw(mask & 7);
    }
}

inline void PartsNode::Draw(int mask) {
    if (done && (prio & mask)) {
        if (prio & 0x20) {
            fn_8016B0A0();
            parts->Draw();
            fn_8016B0C4();
        } else {
            parts->Draw();
        }
        done = 0;
    }
    if (next) {
        next->Draw(mask);
    }
}

inline clMapEffectDK::~clMapEffectDK() {
    if (parts) {
        delete parts;
    }
    fn_8016B190();
    if (fn_8016C360(0x2C)) {
        fn_8016C394(0x2C);
    }
}

inline void clMapEffectDK::Update() {
    if (parts) {
        parts->Update();
    }
    if (x08 > 0) {
        x08--;
    } else if (!fn_8016C360(0x27)) {
        unsigned char vol;
        int pan;

        x08 = (int)(1000.0f * lbl_80495994[x0c]) + 60;
        vol = (int)(64.0f * lbl_80495994[x0c]) + 64;
        pan = (int)(127.0f * lbl_80495A94[x10]);
        SoundMgr_PlaySE(0x27);
        fn_8016C1B0(0x27, vol);
        fn_8016C168(0x27, pan);
        if (++x0c >= 0x40) {
            x0c = 0;
        }
        if (++x10 >= 0x30) {
            x10 = 0;
        }
    }
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x2C);
            done = 1;
        }
    } else if (done == 1) {
        done = fn_8016C3C8(0x2C, 1);
        done = 0;
    }
}

inline void clMapEffectDK::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectWC::~clMapEffectWC() {
    if (parts) {
        delete parts;
    }
    if (fn_8016C360(0x2E)) {
        fn_8016C394(0x2E);
    }
    if (fn_8016C360(0x2F)) {
        fn_8016C394(0x2F);
    }
}

inline void clMapEffectWC::Update() {
    if (parts) {
        parts->Update();
    }
    if (g_gameMode == 1) {
        if (!done) {
            done = SoundMgr_PlaySE(0x2F);
        }
    } else if (!done) {
        if (!IsRaceStarted()) {
            done = SoundMgr_PlaySE(0x2E);
        }
    } else if (IsRaceStarted() && fn_8016C360(0x2E)) {
        fn_8016C3C8(0x2E, 2);
        done = 0;
    }
}

inline void clMapEffectWC::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectPC::~clMapEffectPC() {
    if (parts) {
        delete parts;
    }
    if (fn_8016C360(0x31)) {
        fn_8016C394(0x31);
    }
    if (fn_8016C360(0x32)) {
        fn_8016C394(0x32);
    }
}

inline void clMapEffectPC::Update() {
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x31);
            done = 1;
        }
    } else if (done == 1) {
        fn_8016C3C8(0x31, 1);
        done = 0;
    }
    if (ctx) {
        if (ctx->mode == 0) {
            if (!fn_8016C360(0x32)) {
                SoundMgr_PlaySE(0x32);
            }
        } else if (fn_8016C360(0x32) == 1) {
            fn_8016C394(0x32);
        }
    }
    if (parts) {
        if (ctx) {
            if (ctx->mode == 1) {
                parts->SetHidden(7, 0);
                parts->SetHidden(8, 1);
            } else if (ctx->mode == 0) {
                parts->SetHidden(7, 1);
                parts->SetHidden(8, 0);
            } else {
                parts->SetHidden(0xF, 0);
            }
        }
        parts->Update();
    }
}

inline void PartsList::SetHidden(int mask, unsigned char hide) {
    if (head) {
        head->SetHidden(mask, hide);
    }
}

inline void PartsNode::SetHidden(int mask, unsigned char hide) {
    if (mask & kind) {
        if (hide) {
            if (!(prio & 0x40)) {
                parts->Enable(0);
                prio = prio | 0x40;
            }
        } else if (prio & 0x40) {
            parts->Enable(1);
            prio = prio & ~0x40;
        }
    }
    if (next) {
        next->SetHidden(mask, hide);
    }
}

inline void clMapEffectPC::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectKP::~clMapEffectKP() {
    if (parts) {
        delete parts;
    }
    if (zone) {
        delete zone;
    }
    fn_8016B190();
    if (x18) {
        fn_8016C394(0x33);
    }
    if (x2c) {
        fn_8016C394(0x36);
    }
}

inline void clMapEffectKP::Update() {
    if (parts) {
        parts->Update();
    }
    if (x10) {
        float s;
        float sx;
        JObj *j;

        x14 += 30.0f;
        if (x14 >= 360.0f) {
            x14 = 0.0f;
        }
        s = LUT_Sin12Bit(x14);
        sx = 1.0f - 0.2f * (s < 0.0f ? -s : s);
        JObj *p = x10;
        for (j = p == 0 ? 0 : p->child; j; j = j == 0 ? 0 : j->next) {
            JObjSetScaleZ(j, s);
            JObjSetScaleX(j, sx);
        }
    }
    if (x1c) {
        x24 += 0.0008726644446142018f;
        if (x24 >= 6.283184051513672f) {
            x24 -= 6.283184051513672f;
        }
        JObjSetRotationY(x1c, x24);
    }
    if (x20) {
        x28 += 0.0005817763158120215f;
        if (x28 >= 6.283184051513672f) {
            x28 -= 6.283184051513672f;
        }
        JObjSetRotationY(x20, x28);
    }
    if (GetCourseScene3D()) {
        Vec3f pos;

        CObj_LoadProjMatrix(GetCourseScene3D(), &pos);
        if (zone->Contains(&pos)) {
            x0c += 0.01666666753590107f;
        } else {
            x0c -= 0.01666666753590107f;
        }
        x0c = x0c < 0.0f ? 0.0f : (x0c > 1.0f ? 1.0f : x0c);
        if (x0c > 0.0f) {
            fn_8016B178(2);
        } else {
            fn_8016B178(0);
        }
        fn_8016B160(3000.0f - 2900.0f * x0c);
        fn_8016B148(10000.0f - 3000.0f * x0c);
        if (x0c > 0.0f) {
            int vol = (int)(127.0f * x0c);

            if (!x18) {
                x18 = SoundMgr_PlaySE(0x33);
            }
            fn_8016C1B0(0x33, vol);
        } else if (x18) {
            fn_8016C394(0x33);
            x18 = 0;
        }
    }
    if (!IsRaceStarted()) {
        if (!x2c) {
            x2c = SoundMgr_PlaySE(0x36);
            x2c = 1;
        }
    } else if (x2c == 1) {
        x2c = fn_8016C3C8(0x36, 1);
        x2c = 0;
    }
}

inline void clMapEffectKP::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectRB::~clMapEffectRB() {
    if (parts) {
        delete parts;
    }
}

inline void clMapEffectRB::Update() {
    if (parts) {
        if (ctx) {
            if (ctx->mode == 0) {
                parts->SetHidden(5, 0);
                parts->SetHidden(2, 1);
            } else {
                parts->SetHidden(5, 1);
                parts->SetHidden(2, 0);
            }
        }
        parts->Update();
    }
    if (!done) {
        if (!IsRaceStarted()) {
            done = SoundMgr_PlaySE(0x39);
        }
    } else if (IsRaceStarted() && fn_8016C360(0x39)) {
        fn_8016C3C8(0x39, 2);
        done = 0;
    }
}

inline void clMapEffectRB::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

inline clMapEffectYI::~clMapEffectYI() {
    if (parts) {
        delete parts;
    }
    if (state) {
        delete state;
    }
}

inline void clMapEffectYI::Update() {
    if (parts) {
        parts->Update();
    }
    if (state) {
        state->Update();
    }
}

extern "C" clMapEffect *fn_801752C0(JObj *root, int arg) {
    if (!root) {
        return 0;
    }
    switch (g_cupId) {
    case 1:
        return new clMapEffectMR(root, arg);
    case 2:
        return new clMapEffectDK(root, arg);
    case 3:
        return new clMapEffectWC(root, arg);
    case 4:
        return new clMapEffectPC(root, arg);
    case 5:
        return new clMapEffectKP(root, arg);
    case 6:
        return new clMapEffectRB(root, arg);
    case 7:
        return new clMapEffectYI(root, arg);
    case 8:
        return new clMapEffectDN(root, arg);
    case 10:
        return new clMapEffectDKC();
    case 11:
        return new clMapEffectWCC(root, arg);
    case 12:
        return new clMapEffectPCC();
    case 13:
        return new clMapEffectKPC();
    case 14:
        return new clMapEffectRB(root, arg);
    case 15:
        return new clMapEffectYI(root, arg);
    case 16:
        return new clMapEffectDN(root, arg);
    }
    return 0;
}


#pragma exceptions reset
