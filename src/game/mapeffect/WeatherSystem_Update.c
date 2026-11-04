/* Weather ambience, music ducking, and BGM transitions. */
typedef struct Vec16B { float x,y,z; } Vec16B;
typedef struct Kart16B { char pad[0x2d0]; unsigned char player; } Kart16B;
typedef struct Weather16B {
    unsigned char kind, volume;
    unsigned char pad2[2];
    const int *bgm;
    int mode, phase;
    unsigned char flag10;
    float fade14;
    unsigned char flag18;
    float fade1c;
    int level;
    float fade24, duck;
    unsigned char muted;
    int player;
    float matrix[8][3][4];
} Weather16B;
extern Weather16B *g_weatherSystem;
extern unsigned char g_weatherSystemInitialized;
extern const float lbl_806D8AD0, kWeatherInitFloatA, kWeatherInitFloatB;
extern const float lbl_806D8ADC, lbl_806D8AE0, lbl_806D8AE4, lbl_806D8AE8;
extern const float lbl_806D8AEC, lbl_806D8AF0;
extern Kart16B *GetKartSlotKartVariant(int);
extern float *KartDriver_GetKartRootMtx(Kart16B *);
extern void PSMTXCopy(const float *, float *);
extern void Vec3_Subtract(const Vec16B *, const Vec16B *, Vec16B *);
extern float PSVECSquareMag(const Vec16B *);
extern float Vec3_Magnitude(const Vec16B *);
extern void Vec3_Normalize(const Vec16B *, Vec16B *);
extern float Vec3_Dot(const Vec16B *, const Vec16B *);
extern float Saturate_Double(float, float, float);
extern int fn_80192010(int);
extern unsigned char SoundMgr_Play(int);
extern void fn_80191A14(int, float);
extern void fn_801915F4(int, int);
extern void fn_80191CF4(int, const Vec16B *);
extern void fn_80192348(int);
extern void fn_8019190C(int, int);
extern unsigned char fn_8019083C(int);
extern void clStream_setVolume(int, unsigned char);
extern void fn_801909A4(int);
extern unsigned char ClSound_PlayBgmStream(int, int);
extern void fn_80190A70(int, int);
extern void fn_80192514(int, int);
#define Playing(id) ((unsigned char)(g_weatherSystem == 0 ? 0 : fn_80192010(id)))
static inline void Play(int id) {
    if (g_weatherSystem && !g_weatherSystem->muted) SoundMgr_Play(id);
}
static inline void Pitch(int id, int p) {
    if (g_weatherSystem && !g_weatherSystem->muted) fn_801915F4(id,p);
}
static inline void Gain(int id, float g) {
    if (g_weatherSystem && !g_weatherSystem->muted) fn_80191A14(id,g);
}
static inline void Position(int id, const Vec16B *p) {
    if (g_weatherSystem && !g_weatherSystem->muted) fn_80191CF4(id,p);
}
static inline void Volume(int id, int v) {
    if (g_weatherSystem && !g_weatherSystem->muted) fn_8019190C(id,v);
}
static inline void Stop(int id) { if (g_weatherSystem) fn_80192348(id); }
static inline void KartPosition(Kart16B *k, Vec16B *p) {
    p->x=KartDriver_GetKartRootMtx(k)[3];
    p->y=KartDriver_GetKartRootMtx(k)[7];
    p->z=KartDriver_GetKartRootMtx(k)[11];
}
#pragma exceptions on
void fn_8016B32C(Weather16B *w) {
    if (g_weatherSystemInitialized) {
        int i;
        g_weatherSystemInitialized=0;
        for (i=0;i<8;++i) {
            Kart16B *k=GetKartSlotKartVariant(i);
            if (k) {
                if (k->player) w->player=i;
                PSMTXCopy(KartDriver_GetKartRootMtx(k), &w->matrix[i][0][0]);
            }
        }
    } else {
        float old=w->duck;
        if (!w->muted) {
            if (w->player >= 0) {
                Vec16B p, q, delta;
                int i;
                int nearest=-1;
                float dist;
                Kart16B *k=GetKartSlotKartVariant(w->player);
                KartPosition(k,&p);
                for (i=0;i<8;++i) {
                    if (i != w->player) {
                        k=GetKartSlotKartVariant(i);
                        if (k) {
                            float d;
                            KartPosition(k,&q);
                            Vec3_Subtract(&q,&p,&delta);
                            d=PSVECSquareMag(&delta);
                            if (nearest < 0) { dist=d; nearest=i; }
                            else if (d<dist) { nearest=i; dist=d; }
                        }
                    }
                }
                if (nearest >= 0) {
                    unsigned short pitch;
                    float speed;
                    k=GetKartSlotKartVariant(nearest);
                    KartPosition(k,&p);
                    q.x=w->matrix[nearest][0][3];
                    q.y=w->matrix[nearest][1][3];
                    q.z=w->matrix[nearest][2][3];
                    Vec3_Subtract(&p,&q,&delta);
                    speed=Saturate_Double(Vec3_Magnitude(&delta)/lbl_806D8AD0,kWeatherInitFloatA,kWeatherInitFloatB);
                    pitch=(int)(lbl_806D8ADC*speed)+0x2000;
                    if (!Playing(0x40000050)) { Play(0x40000050); Gain(0x40000050,lbl_806D8AE0); }
                    Pitch(0x40000050,pitch);
                    Position(0x40000050,&p);
                    if (speed < lbl_806D8AE4) {
                        if (Playing(0x40000051)) Stop(0x40000051);
                    } else {
                        q.x=w->matrix[nearest][0][2];
                        q.y=w->matrix[nearest][1][2];
                        q.z=w->matrix[nearest][2][2];
                        Vec3_Normalize(&q,&q);
                        Vec3_Normalize(&delta,&delta);
                        if (Vec3_Dot(&q,&delta) < lbl_806D8AE8) {
                            if (!Playing(0x40000051)) { Play(0x40000051); Gain(0x40000051,lbl_806D8AE0); }
                            Position(0x40000051,&p);
                        } else if (Playing(0x40000051)) Stop(0x40000051);
                    }
                }
                for (i=0;i<8;++i) {
                    k=GetKartSlotKartVariant(i);
                    if (k) PSMTXCopy(KartDriver_GetKartRootMtx(k), &w->matrix[i][0][0]);
                }
            }
            if (w->flag10) {
                w->fade14 += lbl_806D8AEC;
                if (w->fade14 > 1.0f) w->fade14=1.0f;
                if (!Playing(0xa8)) Play(0xa8);
                Volume(0xa8,(int)(lbl_806D8AF0*w->fade14));
            } else {
                w->fade14 -= lbl_806D8AEC;
                if (w->fade14 < 0.0f) w->fade14=0.0f;
                if (Playing(0xa8)) {
                    Volume(0xa8,(int)(lbl_806D8AF0*w->fade14));
                    if (kWeatherInitFloatA == w->fade14) Stop(0xa8);
                }
            }
            if (w->flag18) {
                w->fade1c += lbl_806D8AEC;
                if (w->fade1c > 1.0f) w->fade1c=1.0f;
                if (!Playing(0xca)) Play(0xca);
            } else {
                w->fade1c -= lbl_806D8AEC;
                if (w->fade1c < 0.0f) w->fade1c=0.0f;
                if (Playing(0xca)) Stop(0xca);
            }
            if (w->level > 0) {
                if (!Playing(0xbf)) Play(0xbf);
                w->fade24 += lbl_806D8AEC;
                if (w->fade24 > 1.0f) w->fade24=1.0f;
            } else {
                w->fade24 -= lbl_806D8AEC;
                if (w->fade24 < 0.0f) {
                    w->fade24=0.0f;
                    if (Playing(0xbf)) Stop(0xbf);
                }
            }
            if (Playing(0xbf)) Volume(0xbf,(int)(lbl_806D8AF0*w->fade24));
            w->duck = kWeatherInitFloatB - Saturate_Double(w->fade24+(w->fade14+w->fade1c),kWeatherInitFloatA,kWeatherInitFloatB);
        }
        if (old != w->duck) {
            if (fn_8019083C(w->bgm[0])) clStream_setVolume(w->bgm[0],(float)w->volume*w->duck);
            if (fn_8019083C(w->bgm[1])) clStream_setVolume(w->bgm[1],(float)w->volume*w->duck);
        }
    }
    if (w->bgm && w->mode) {
        switch (w->mode) {
        case 1:
            if (fn_8019083C(w->bgm[0])) fn_801909A4(w->bgm[0]);
            if (fn_8019083C(w->bgm[1])) fn_801909A4(w->bgm[1]);
            w->mode=0; w->phase=0;
            break;
        case 2:
            if (fn_8019083C(w->bgm[0])) fn_801909A4(w->bgm[0]);
            if (w->kind) {
                if (ClSound_PlayBgmStream(w->bgm[0],0)) {
                    clStream_setVolume(w->bgm[0],(float)w->volume*w->duck);
                    w->mode=0; w->phase=0;
                }
            } else { w->mode=0; w->phase=0; }
            break;
        case 3:
            if (SoundMgr_Play(0x49)) { w->mode=0; w->phase=0; }
            break;
        case 4:
            switch (w->phase) {
            case 0:
                if (w->kind) {
                    if (ClSound_PlayBgmStream(w->bgm[1],0)) {
                        clStream_setVolume(w->bgm[1],(float)w->volume*w->duck);
                        w->phase++;
                    }
                } else w->phase++;
                break;
            case 1:
                if (fn_8019083C(w->bgm[0])) fn_80190A70(w->bgm[0],1);
                w->mode=0; w->phase=0;
                break;
            }
            break;
        case 5: case 6:
            switch (w->phase) {
            case 0:
                if (w->mode==6) { if (SoundMgr_Play(0x1c)) w->phase++; }
                else { if (SoundMgr_Play(0x1e)) w->phase++; }
                w->muted=1;
                fn_80192514(4,2); fn_80192514(5,2); fn_80192514(6,2); fn_80192514(7,2);
                break;
            case 1:
                if (fn_8019083C(w->bgm[0])) fn_80190A70(w->bgm[0],1);
                if (fn_8019083C(w->bgm[1])) fn_80190A70(w->bgm[1],1);
                w->mode=0; w->phase=0;
                break;
            }
            break;
        }
    }
}
#pragma exceptions reset
