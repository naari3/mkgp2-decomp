/* === extracted from auto_TornadoEffect_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

extern void DrawEffect_SetByte104(void *fx, int on);
extern void DrawEffect_SetFloat108Avg(void *fx, float l, float r);
extern void DrawEffect_SetFloat110(void *fx, float v);
extern void KartDriver_SetUniformScale_4Wheels(void *kart, float s);
extern void KartItem_BroadcastParamToCarAndISE(void *kart, int param);
extern float Object_GetJObjRotationY(void *obj);
extern void Object_SetColorAlphaOnly(void *obj, int idx, float a);
extern void Object_SetJObjRotationY(void *obj, float ry);

extern const float lbl_806D28C8;
extern const float lbl_806D28CC;
extern const float lbl_806D28D0;
extern const float lbl_806D28D4;
extern const float lbl_806D28D8;
extern const float lbl_806D28DC;
extern const float lbl_806D28E8;
extern const float lbl_806D28EC;
extern const float lbl_806D28F0;
extern const float lbl_806D28F4;
extern const float lbl_806D28F8;
extern const float lbl_806D28FC;
extern const float lbl_806D2900;
extern const float lbl_806D2904;
extern const float lbl_806D2908;
extern const float lbl_806D290C;
extern const float lbl_806D2910;
extern const float lbl_806D2914;
extern const double lbl_806D2918;
extern const float lbl_806D2920;
extern const float lbl_806D2924;
extern const float lbl_806D2928;

typedef struct { float *p[3]; } TEPtr3;
extern const TEPtr3 TornadoEffect_Tick_rodata_802EDC3C; /* zero templates for the two pointer triples */
extern const TEPtr3 TornadoEffect_Tick_rodata_802EDC48;

#define TE_U64(p, o) (*(unsigned long long *)((char *)(p) + (o)))

static inline unsigned char TE_StateHasFlag(void *st, unsigned long long mask)
{
    unsigned long long f = TE_U64(st, 0x10);
    f |= TE_U64(st, 0x18);
    if ((f & mask) == 0) {
        return 0;
    }
    return 1;
}

static inline unsigned char TE_StateHasFlagLo(void *st, unsigned long long mask)
{
    if ((TE_U64(st, 0x10) & mask) == 0) {
        return 0;
    }
    return 1;
}

void TornadoEffect_Tick(void *e)
{
    float old;
    void *st;
    float l;
    float r;

    st = TE_PTR(TE_PTR(e, 0xC), 0x304);
    if (TE_S32(e, 0x140) > 0) {
        TE_S32(e, 0x140)--;
    }
    if (TE_StateHasFlag(st, 0x0800000000000000ULL) == 1) {
        KartItem_BroadcastParamToCarAndISE(TE_PTR(e, 0xC), TE_S32(st, 0x4C));
    } else {
        KartItem_BroadcastParamToCarAndISE(TE_PTR(e, 0xC), -1);
    }
    if (TE_S32(e, 0x138) > 0) {
        TE_S32(e, 0x138)--;
    }
    if (TE_S32(e, 0x124) != 0) {
        TE_S32(e, 0x130)++;
    }
    if (TE_S32(e, 0x128) != 0) {
        TE_S32(e, 0x134)++;
    }
    if (TE_S32(e, 0x100) > 0) {
        TE_S32(e, 0x100)--;
        Object_SetJObjRotationY(TE_PTR(e, 0xA8), Object_GetJObjRotationY(TE_PTR(e, 0xA8)) - lbl_806D28DC);
        Object_SetColorAlphaOnly(TE_PTR(e, 0xA8), 0,
                                 Saturate_Double(lbl_806D28E8 * ((float)TE_S32(e, 0x100) / lbl_806D28EC), lbl_806D28C8,
                                                 TE_U8(e, 0x8) == 1 ? lbl_806D28D4 : lbl_806D28D8));
    }

    old = TE_F(e, 0x10C);
    switch (TE_S32(e, 0x104)) {
    case 0:
        if (old > lbl_806D28CC) {
            TE_F(e, 0x10C) = old - lbl_806D28D0;
            if (TE_F(e, 0x10C) < lbl_806D28CC) {
                TE_F(e, 0x10C) = lbl_806D28CC;
            }
        } else {
            TE_F(e, 0x10C) = old + lbl_806D28D0;
            if (TE_F(e, 0x10C) > lbl_806D28CC) {
                TE_F(e, 0x10C) = lbl_806D28CC;
            }
        }
        break;
    case 1:
        if (old > TE_F(e, 0x108)) {
            TE_F(e, 0x10C) = old - lbl_806D28D0;
            if (TE_F(e, 0x10C) < TE_F(e, 0x108)) {
                TE_F(e, 0x10C) = TE_F(e, 0x108);
            }
        } else {
            TE_F(e, 0x10C) = old + lbl_806D28D0;
            if (TE_F(e, 0x10C) > TE_F(e, 0x108)) {
                TE_F(e, 0x10C) = TE_F(e, 0x108);
            }
        }
        break;
    case 2: {
        float d = TE_F(e, 0x110);
        float v = old + d;
        if (v > lbl_806D28F0 || v < lbl_806D28F4) {
            TE_F(e, 0x110) = -d;
        }
        TE_F(e, 0x10C) = Saturate_Double(v, lbl_806D28F4, lbl_806D28F0);
        break;
    }
    }
    if (TE_F(e, 0x10C) > old) {
        if (TE_S32(e, 0x144) <= 0) {
            TE_S32(e, 0x144) = 1;
            TE_S32(e, 0x148) = 1;
        }
    } else if (TE_F(e, 0x10C) < old) {
        if (TE_S32(e, 0x144) >= 0) {
            TE_S32(e, 0x144) = -1;
            TE_S32(e, 0x148) = -1;
        }
    } else {
        TE_S32(e, 0x144) = 0;
        TE_S32(e, 0x148) = 0;
    }
    KartDriver_SetUniformScale_4Wheels(TE_PTR(e, 0xC), TE_F(e, 0x10C));

    {
        float inc;
        float max;
        if (TE_F(e, 0xBC) < lbl_806D28D8) {
            inc = lbl_806D28D0;
        } else {
            inc = lbl_806D28F8;
        }
        max = lbl_806D28FC;
        if (TE_U8(e, 0xB4) == 1) {
            max = lbl_806D28CC;
        }
        TE_F(e, 0xB8) = Saturate_Double(TE_F(e, 0xB8) + inc, lbl_806D28C8, max);
    }
    {
        float steer = TE_F(e, 0xAC);
        float a;
        l = TE_F(e, 0xB8);
        r = l;
        { double d = __fabs(steer); a = d; }
        if (a > lbl_806D2900) {
            float k = lbl_806D2904 * (lbl_806D28CC - a) + lbl_806D2904;
            if (steer < lbl_806D28C8) {
                l = l * k;
            } else {
                r = l * k;
            }
        }
    }
    if (TE_U8(e, 0x8) == 0 || TE_U8(e, 0xC0) == 1 || TE_U8(e, 0xD2) == 1) {
        l = lbl_806D28C8;
        r = l;
    }
    DrawEffect_SetFloat108Avg(TE_PTR(e, 0x10), l, r);

    if (TE_U8(e, 0xD2) == 1) {
        DrawEffect_SetByte10C(TE_PTR(e, 0x10), 1);
        if (TE_S32(e, 0x13C) > 0) {
            TE_S32(e, 0x13C)--;
            if (TE_S32(e, 0x13C) == 0) {
                DrawEffect_SetByte10C(TE_PTR(e, 0x10), 0);
                TE_U8(e, 0xD2) = 0;
            }
        }
    } else {
        DrawEffect_SetByte10C(TE_PTR(e, 0x10), 0);
        TE_S32(e, 0x13C) = 0;
    }

    if (TE_U8(e, 0xC0) == 1) {
        DrawEffect_SetBytePairD4D5(TE_PTR(e, 0x10), 0, 0);
    } else {
        if (TE_U8(e, 0x8) == 1) {
            DrawEffect_SetBytePairD4D5(TE_PTR(e, 0x10), TE_S32(e, 0xC8), TE_S32(e, 0xCC));
        } else {
            DrawEffect_SetBytePairD4D5(TE_PTR(e, 0x10), 0, 0);
        }
        if (TE_F(e, 0xC4) > lbl_806D28C8 && TE_U8(e, 0x8) == 1) {
            DrawEffect_SetFloat110(TE_PTR(e, 0x10), TE_F(e, 0xC4));
        }
        TE_F(e, 0xC4) = lbl_806D28C8;
    }

    {
        float add = lbl_806D28C8;
        st = TE_PTR(TE_PTR(e, 0xC), 0x304);
        if (TE_StateHasFlagLo(st, 0x20) == 1) {
            if (TE_S32(st, 0x2C) == 1) {
                add = lbl_806D2908;
            } else {
                add = lbl_806D290C;
            }
        }
        TE_F(e, 0x120) = TE_F(e, 0x120) + Saturate_Double(TE_F(e, 0x11C) + add - TE_F(e, 0x120), lbl_806D2910, lbl_806D2914);
        TE_F(st, 0x48) = lbl_806D2918 * TE_F(e, 0x120);
    }
    if (TE_U8(e, 0x12C) == 1) {
        DrawEffect_SetByte104(TE_PTR(e, 0x10), 1);
    } else {
        DrawEffect_SetByte104(TE_PTR(e, 0x10), 0);
    }

    if (TE_S32(e, 0xD4) == 0) {
        return;
    }
    switch (TE_S32(e, 0xD4)) {
    case 1:
        TE_F(e, 0xF0) += 0.016666668f;
        if (TE_F(e, 0xF0) > 1.0f) {
            TE_F(e, 0xF0) = 1.0f;
            TE_S32(e, 0xD4) = 0;
        }
        break;
    case 2: {
        float t = TE_F(e, 0xE4);
        float c = TE_F(e, 0xF0);
        if (c < t) {
            c += lbl_806D2924;
            if (c > t) {
                TE_S32(e, 0xD4) = 0;
                c = t;
            }
        } else if (c > t) {
            c -= lbl_806D2928;
            if (c < t) {
                TE_S32(e, 0xD4) = 0;
                c = t;
            }
        }
        TE_F(e, 0xEC) = c;
        TE_F(e, 0xF0) = c;
        TE_F(e, 0xF4) = c;
        break;
    }
    case 3: {
        TEPtr3 tgt;
        TEPtr3 cur;
        int done;
        int i;
        float **tp;
        float **cp;
        tgt = TornadoEffect_Tick_rodata_802EDC3C;
        tgt.p[0] = &TE_F(e, 0xE0);
        tgt.p[1] = &TE_F(e, 0xE4);
        tgt.p[2] = &TE_F(e, 0xE8);
        cur = TornadoEffect_Tick_rodata_802EDC48;
        cur.p[0] = &TE_F(e, 0xEC);
        cur.p[1] = &TE_F(e, 0xF0);
        cur.p[2] = &TE_F(e, 0xF4);
        done = 0;
        tp = tgt.p;
        cp = cur.p;
        for (i = 0; i < 3; i++) {
            float t = **tp;
            float c = **cp;
            if (c < t) {
                c += lbl_806D28D0;
                if (c > t) {
                    c = t;
                    done++;
                }
            } else if (c > t) {
                c -= lbl_806D28D0;
                if (c < t) {
                    c = t;
                    done++;
                }
            }
            **cp = c;
            tp++;
            cp++;
        }
        if (done >= 3) {
            TE_S32(e, 0xD4) = 0;
        }
        break;
    }
    }
}

