/* Homing-target marker animation. Constants and colors are owned by adjacent TUs. */
static inline float Interpolate(const float &from, const float &to, float t) {
    return t * (to - from) + from;
}

static inline float Approach(float from, float to, float t) {
    return (to - from) * t + from;
}

struct MarkerPart {
    unsigned char visible;
    float sx, sy, angle;
    float color[4];
    void SetScalar(float scale, float rotation, float red, float green, float blue, float alpha) {
        visible = 1; sy = scale; sx = scale; angle = rotation;
        color[0] = red; color[1] = green; color[2] = blue; color[3] = alpha;
    }
    void Set(float scale, float rotation, const float *rgb, float alpha) {
        SetScalar(scale, rotation, rgb[0], rgb[1], rgb[2], alpha);
    }
    void SetRGBA(float scale, float rotation, const float *rgba) {
        visible = 1; sy = scale; sx = scale; angle = rotation;
        color[0] = rgba[0]; color[1] = rgba[1]; color[2] = rgba[2]; color[3] = rgba[3];
    }
    void Fade(float scale, float rotation, const float *rgb, float t) {
        sx = Approach(sx, scale, t); sy = Approach(sy, scale, t); angle = rotation;
        color[0] = Interpolate(color[0], rgb[0], t);
        color[1] = Interpolate(color[1], rgb[1], t);
        color[2] = Interpolate(color[2], rgb[2], t);
        color[3] += -color[3] * t;
    }
    void SetColor(float red, float green, float blue, float alpha) {
        color[0] = red; color[1] = green; color[2] = blue; color[3] = alpha;
    }
    void SetInterpolated(float scale, float rotation, const float *a, const float *b, float t, float alpha) {
        visible = 1; sy = scale; sx = scale; angle = rotation;
        SetColor(Interpolate(a[0], b[0], t), Interpolate(a[1], b[1], t),
                 Interpolate(a[2], b[2], t), alpha);
    }
    void Blend(float scale, float rotation, const float *rgb, float alpha, float t) {
        sx = Approach(sx, scale, t); sy = Approach(sy, scale, t); angle = rotation;
        color[0] = Interpolate(color[0], rgb[0], t);
        color[1] = Interpolate(color[1], rgb[1], t);
        color[2] = Interpolate(color[2], rgb[2], t);
        color[3] = Approach(color[3], alpha, t);
    }
};
struct Marker {
    int state;
    float time;
    unsigned char active;
    float position[3];
    MarkerPart part[5];
};
extern "C" {
float fn_80173F5C(float, float, float);
float fn_80173F7C(float, float, float);
}
extern const float HomingMarkerUpdate_rodata_8036E924[4], HomingMarkerUpdate_rodata_8036E934[4], HomingMarkerUpdate_rodata_8036E944[4];
extern const float lbl_806D8D90;
#define C8D90 0.0f
extern const float lbl_806D8D94;
#define C8D94 1.0f
extern const float lbl_806D8D98;
#define C8D98 255.0f
extern const float lbl_806D8D9C;
#define C8D9C -1.0f
extern const float lbl_806D8DA0;
#define C8DA0 0.0333333351f
extern const float lbl_806D8DA4;
#define C8DA4 10.0f
extern const float lbl_806D8DA8;
#define C8DA8 32.0f
extern const float lbl_806D8DAC;
#define C8DAC 116.0f
extern const float lbl_806D8DB0;
#define C8DB0 -74.0f
extern const float lbl_806D8DB4;
#define C8DB4 5.0f
extern const float lbl_806D8DB8;
#define C8DB8 42.0f
extern const float lbl_806D8DBC;
#define C8DBC 22.0f
extern const float lbl_806D8DC0;
#define C8DC0 15.0f
extern const float lbl_806D8DC4;
#define C8DC4 30.0f
extern const float lbl_806D8DC8;
#define C8DC8 54.0f
extern const float lbl_806D8DCC;
#define C8DCC 2.0f
extern const float lbl_806D8DD0;
#define C8DD0 0.5f
extern const float lbl_806D8DD4;
#define C8DD4 78.0f
extern const float lbl_806D8DD8;
#define C8DD8 13.0f
extern const float lbl_806D8DDC;
#define C8DDC 17.0f
extern const float lbl_806D8DE0;
#define C8DE0 300.0f
extern const float lbl_806D8DE4;
#define C8DE4 -244.0f
extern const float lbl_806D8DE8;
#define C8DE8 0.785398185f
extern const float lbl_806D8DEC;
#define C8DEC 7.0f
extern const float lbl_806D8DF0;
#define C8DF0 20.0f
extern const float lbl_806D8DF4;
#define C8DF4 800.0f
extern const float lbl_806D8DF8;
#define C8DF8 86.0f
extern const float lbl_806D8DFC;
#define C8DFC 120.0f
extern const float lbl_806D8E00;
#define C8E00 150.0f
extern const float lbl_806D8E04;
#define C8E04 -30.0f
extern const float lbl_806D8E08;
#define C8E08 56.0f
extern const float lbl_806D8E0C;
#define C8E0C 60.0f
extern const float lbl_806D8E10;
#define C8E10 0.87266463f

static inline float Clamp(float v) { return fn_80173F5C(v, C8D90, C8D94); }
static inline float Pulse(float v) {
    v = fn_80173F7C(v, C8D90, C8DA4);
    if (v >= C8DB4) v = C8D94 - (v - C8DB4) / C8DB4;
    else v /= C8DB4;
    return v;
}
extern "C" void fn_80172948(Marker *self) {
    if (self->state == -1) return;
    switch (self->state) {
    case 0: {
        if (self->time < C8DA4) {
            float t = Clamp(self->time / C8DA4);
            self->part[0].Set(C8DA8 * t, C8D90, HomingMarkerUpdate_rodata_8036E924, t);
            self->part[1].Set(C8DB0 * t + C8DAC, C8D90, HomingMarkerUpdate_rodata_8036E924, C8D94);
            self->part[2].Set(C8DB0 * t + C8DAC, C8D90, HomingMarkerUpdate_rodata_8036E934, C8D94);
        } else {
            float t = Clamp((self->time - C8DA4) / C8DB4);
            self->part[0].Set(C8DA8, C8D90, HomingMarkerUpdate_rodata_8036E924, C8D94 - t);
            self->part[1].Set(C8DB8, C8D90, HomingMarkerUpdate_rodata_8036E924, C8D94);
            self->part[2].Set(C8DBC * t + C8DB8, C8D90, HomingMarkerUpdate_rodata_8036E934, C8D94 - t);
        }
        self->part[3].visible = 0; self->part[4].visible = 0;
        if (++self->time >= C8DC0) { self->time = C8D90; self->state = 1; }
        break;
    }
    case 1: {
        float t = Pulse(self->time);
        self->part[0].Set(C8DA8, C8D90, HomingMarkerUpdate_rodata_8036E924, t);
        self->part[1].Set(C8DB8, C8D90, HomingMarkerUpdate_rodata_8036E924, C8D94);
        self->part[2].visible = 0; self->part[3].visible = 0; self->part[4].visible = 0;
        if (++self->time >= C8DC4) { if (self->active) self->state = 2; self->time = C8D90; }
        break;
    }
    case 2: {
        if (self->time < C8DC0) {
            float t = Pulse(self->time);
            self->part[0].Set(C8DA8, C8D90, HomingMarkerUpdate_rodata_8036E924, t);
            self->part[1].Set(C8DB8, C8D90, HomingMarkerUpdate_rodata_8036E924, t);
            self->part[2].visible = 0;
        } else {
            float t = Clamp((self->time - C8DC0) / C8DA4);
            self->part[0].SetInterpolated(C8DC8 * t + C8DA8, C8D90, HomingMarkerUpdate_rodata_8036E924, HomingMarkerUpdate_rodata_8036E934, t, C8D94);
            {
                float alpha = Clamp(C8DCC * (t - C8DD0));
                self->part[1].SetInterpolated(C8DD4 * t + C8DB8, C8D90, HomingMarkerUpdate_rodata_8036E924, HomingMarkerUpdate_rodata_8036E944, t, alpha);
            }
            self->part[2].visible = 0;
        }
        if (self->time >= C8DD8) {
            float t = Clamp((self->time - C8DD8) / C8DDC);
            self->part[3].SetRGBA(C8DE4 * t + C8DE0, C8DE8 * (C8D94 - t), HomingMarkerUpdate_rodata_8036E944);
            self->part[3].color[3] = Clamp((self->time - C8DD8) / C8DEC);
        }
        if (self->time >= C8DCC) {
            float t = C8D94 - Clamp((self->time - C8DCC) / C8DF0);
            if (t > C8D90) self->part[4].Set(C8DF4 * t, C8DE8 * t, HomingMarkerUpdate_rodata_8036E944, t);
            else self->part[4].visible = 0;
        }
        if (++self->time >= C8DC4) { self->state = 3; self->time = C8D90; }
        break;
    }
    case 3: {
        float t = fn_80173F7C(self->time, C8D90, C8DA4);
        if (t < C8DB4) {
            t = Clamp(t / C8DB4);
            self->part[0].SetInterpolated(C8DF8, C8D90, HomingMarkerUpdate_rodata_8036E934, HomingMarkerUpdate_rodata_8036E944, t, C8D94);
        } else {
            t = Clamp((t - C8DB4) / C8DB4);
            self->part[0].SetInterpolated(C8DF8, C8D90, HomingMarkerUpdate_rodata_8036E944, HomingMarkerUpdate_rodata_8036E934, t, C8D94);
        }
        self->part[1].Set(C8DFC, C8D90, HomingMarkerUpdate_rodata_8036E944, C8D94);
        t = fn_80173F7C(self->time, C8D90, C8DC0);
        self->part[2].SetRGBA(C8E04 * Clamp(t / C8DA4) + C8E00, C8D90, HomingMarkerUpdate_rodata_8036E934);
        if (t < C8DEC) self->part[2].color[3] = C8D94;
        else self->part[2].color[3] = C8D94 - Clamp((t - C8DEC) * C8DD0);
        self->part[3].visible = 1;
        self->part[3].sy = C8E08; self->part[3].sx = C8E08;
        t = fn_80173F7C(self->time, C8D90, C8DC4) / C8DC4;
        self->part[3].angle = C8DE8 * t;
        self->part[3].color[0] = HomingMarkerUpdate_rodata_8036E944[0]; self->part[3].color[1] = HomingMarkerUpdate_rodata_8036E944[1];
        self->part[3].color[2] = HomingMarkerUpdate_rodata_8036E944[2]; self->part[3].color[3] = HomingMarkerUpdate_rodata_8036E944[3];
        t = fn_80173F7C(self->time, C8D90, C8DC4);
        if (t < C8DC0) self->part[3].color[3] = C8D94 - Clamp(t / C8DC0);
        else self->part[3].color[3] = Clamp((t - C8DC0) / C8DC0);
        self->part[4].visible = 0;
        if (++self->time >= C8E0C) self->time = C8D90;
        break;
    }
    case 4: {
        float t = Clamp(self->time / C8DA4);
        self->part[0].Blend(C8DA8, C8D90, HomingMarkerUpdate_rodata_8036E924, C8D94, t);
        self->part[1].Blend(C8DB8, C8D90, HomingMarkerUpdate_rodata_8036E924, C8D94, t);
        self->part[3].sx += (C8DE0 - self->part[3].sx) * t;
        self->part[3].sy += (C8DE0 - self->part[3].sy) * t;
        self->part[3].angle += (C8E10 - self->part[3].angle) * t;
        self->part[3].color[0] = HomingMarkerUpdate_rodata_8036E944[0]; self->part[3].color[1] = HomingMarkerUpdate_rodata_8036E944[1];
        self->part[3].color[2] = HomingMarkerUpdate_rodata_8036E944[2]; self->part[3].color[3] = HomingMarkerUpdate_rodata_8036E944[3];
        self->part[3].color[3] += -self->part[3].color[3] * t;
        t = Clamp(self->time / C8DB4);
        self->part[2].Fade(C8DFC, C8D90, HomingMarkerUpdate_rodata_8036E934, t);
        self->part[4].visible = 0;
        if (++self->time >= C8DA4) { self->state = 1; self->time = C8D90; }
        break;
    }
    }
}
