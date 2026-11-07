/* 0x80179650..0x8017A52C: reversed EH group; YIState update remains nonmatching. */
#include "game/mapeffect_private.h"

extern "C" const float lbl_806D8E90;

#pragma exceptions on
void clMapEffectYI::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

clReverbCtrl::~clReverbCtrl() {
    if (vol) {
        fn_80193134(0);
        delete vol;
        vol = 0;
    }
}

void clReverbCtrl::Update() {
    if (GetCourseScene3D() && vol) {
        Vec3f pos;

        CObj_LoadProjMatrix(GetCourseScene3D(), &pos);
        fn_80193134(vol->Contains(&pos));
    }
}

void clReverbCtrl::Draw() {
    if (vol) {
        vol->Draw();
    }
}

clMapEffectDN::~clMapEffectDN() {
    fn_8016B190();
    if (parts) {
        delete parts;
    }
    if (done == 1) {
        done = fn_8016C394(0x42);
    }
    if (fn_8016C360(0x3C) == 1) {
        fn_8016C394(0x3C);
    }
}

void clMapEffectDN::Update() {
    if (parts) {
        parts->Update();
    }
    if (!IsRaceStarted()) {
        if (!done) {
            SoundMgr_PlaySE(0x42);
            fn_8016C1F8(0x42, 0.7300000190734863f);
            done = 1;
        }
    } else if (done == 1) {
        fn_8016C3C8(0x42, 1);
        done = 0;
    }
}

void clMapEffectDN::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

clMoveTex::~clMoveTex() {
    if (joints) {
        delete[] joints;
    }
    DebugPrintf(" DeleteMapEffect : clMoveTex\n");
}

void clMoveTex::Update() {
    int i;

    for (i = 0; i < count; i++) {
        if (joints[i]) {
            fn_80182E18(joints[i], table[i].u, table[i].v);
        }
    }
}

clMapEffectWCC::~clMapEffectWCC() {
    if (parts) {
        delete parts;
    }
    if (fn_8016C360(0x2F)) {
        fn_8016C394(0x2F);
    }
}

void clMapEffectWCC::Update() {
    if (parts) {
        parts->Update();
    }
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x2F);
        }
    } else if (done == 1) {
        done = 0;
        fn_8016C3C8(0x2F, 1);
    }
}

void clMapEffectWCC::Draw(int mask) {
    if (parts) {
        parts->Draw(mask);
    }
}

clMapEffectKPC::~clMapEffectKPC() {
    if (done) {
        fn_8016C394(0x36);
    }
}

void clMapEffectKPC::Update() {
    if (!IsRaceStarted()) {
        if (!done) {
            SoundMgr_PlaySE(0x36);
            done = 1;
        }
    } else if (done == 1) {
        fn_8016C3C8(0x36, 1);
        done = 0;
    }
}

void clMapEffectKPC::Draw(int mask) {
}

clMapEffectPCC::~clMapEffectPCC() {
    if (fn_8016C360(0x32)) {
        fn_8016C394(0x32);
    }
}

void clMapEffectPCC::Update() {
    if (!IsRaceStarted()) {
        if (!done) {
            done = SoundMgr_PlaySE(0x32);
        }
    } else if (done == 1) {
        done = 0;
        fn_8016C3C8(0x32, 1);
    }
}

void clMapEffectPCC::Draw(int mask) {
}

clMapEffectDKC::~clMapEffectDKC() {
    fn_8016B190();
    if (done) {
        fn_8016C394(0x2C);
    }
}

void clMapEffectDKC::Update() {
    if (!IsRaceStarted()) {
        if (wait > 0) {
            wait--;
        } else if (!fn_8016C360(0x27)) {
            unsigned char vol;
            int pan;

            wait = (int)(1000.0f * lbl_80495994[volIdx]) + 60;
            vol = (int)(64.0f * lbl_80495994[volIdx]) + 64;
            pan = (int)(127.0f * lbl_80495A94[panIdx]);
            SoundMgr_PlaySE(0x27);
            fn_8016C1B0(0x27, vol);
            fn_8016C168(0x27, pan);
            if (++volIdx >= 0x40) {
                volIdx = 0;
            }
            if (++panIdx >= 0x30) {
                panIdx = 0;
            }
        }
        if (!done) {
            done = SoundMgr_PlaySE(0x2C);
        }
    } else if (done == 1) {
        done = 0;
        fn_8016C3C8(0x2C, 1);
    }
}


static unsigned char InQuad(const float *q, const Vec3f *p) {
    if (((q[2] - q[0]) * (p->z - q[1]) - (q[3] - q[1]) * (p->x - q[0]) <= 0.0f) == 0) {
        return 0;
    }
    if (((q[4] - q[2]) * (p->z - q[3]) - (q[5] - q[3]) * (p->x - q[2]) <= 0.0f) == 0) {
        return 0;
    }
    if (((q[6] - q[4]) * (p->z - q[5]) - (q[7] - q[5]) * (p->x - q[4]) <= 0.0f) == 0) {
        return 0;
    }
    if (((q[0] - q[6]) * (p->z - q[7]) - (q[1] - q[7]) * (p->x - q[6]) <= 0.0f) == 0) {
        return 0;
    }
    return 1;
}


void clMapEffectDKC::Draw(int mask) {
}

template <>
void YIState::UpdateT<0>() {
    const char *pool = (const char *)lbl_80370870;
    Vec3f pos;

    if (!IsRaceStarted()) {
        if (!a) {
            SoundMgr_PlaySE(0x3E);
            a = 1;
            x04 = 1.0f;
        }
    } else if (a == 1) {
        x04 -= 0.003000000026077032f;
        fn_8016C1F8(0x3E, x04);
        if (x04 <= 0.0f) {
            a = 0;
            fn_8016C394(0x3E);
        }
    }
    CObj_LoadProjMatrix(GetCourseScene3D(), &pos);
    if (!g_longRoundFlag) {
        if (InQuad((const float *)(pool + 0x408), &pos) == 1) {
            if (++x20 >= 0x78) {
                x20 = 0;
            }
            if (x20 == 0x1A) {
                SoundMgr_PlaySE(0x3B);
            }
        }
    } else {
        if (InQuad((const float *)(pool + 0x448), &pos) == 1) {
            if (!c) {
                SoundMgr_PlaySE(0x40);
                c = 1;
            } else if (x14 < 1.0f) {
                x14 += lbl_806D8E90;
                if (x14 >= 1.0f) {
                    x14 = 1.0f;
                }
                fn_8016C1F8(0x40, x14);
            }
        } else if (c == 1) {
            x14 -= 0.003000000026077032f;
            fn_8016C1F8(0x40, x14);
            if (x14 <= 0.0f) {
                c = 0;
                fn_8016C394(0x40);
            }
        }
        if (InQuad((const float *)(pool + 0x428), &pos) == 1) {
            x24++;
            if (x24 >= 0x168) {
                fn_8016C394(0x3F);
                d = 0;
                x24 = 0;
            }
            if (x24 > 0x96) {
                if (!d) {
                    SoundMgr_PlaySE(0x3F);
                    d = 1;
                    x1c = 1.0f;
                } else if (x1c < 1.0f) {
                    x1c += lbl_806D8E90;
                    if (x1c >= 1.0f) {
                        x1c = 1.0f;
                    }
                    fn_8016C1F8(0x3F, x1c);
                }
            }
        } else if (d == 1) {
            x1c -= 0.003000000026077032f;
            fn_8016C1F8(0x3F, x1c);
            if (x1c <= 0.0f) {
                d = 0;
                fn_8016C394(0x3F);
            }
        }
    }
}

#pragma exceptions reset
