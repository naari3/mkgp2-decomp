typedef struct MaterialNode { char pad[8]; void *material; } MaterialNode;
#include "game/types/UV.h"
#include "game/types/gx_data.h"
typedef struct Wave { float speedU,speedV,scaleU,scaleV,ampU,ampV,freqU,freqV; MaterialNode *node; char pad24[0x10]; int count; unsigned short *indices; UV *output,*input; float phaseU,phaseV; } Wave;
typedef struct Obj { void *vt,*model; Wave *wave; } Obj;

extern void *HSD_MObjGetTObj(void *);
extern void fn_80182A5C(void *,float,float);
extern float fn_80186960(float);
extern float LUT_Sin12Bit(float);
extern void DCFlushRange(void *,unsigned int);

static inline void UpdateUV(Wave *w) {
    UV *src;
    UV *dst;
    int i;
    float fu, fv;
    fu = 360.0f * w->freqU;
    fv = 360.0f * w->freqV;
    for (i=0;i<w->count;i++) {
        dst = &w->output[i];
        src = &w->input[w->indices[i]];
        GXDATA_SET_F32(&dst->u, w->ampU * fn_80186960(GXDATA_F32(&src->u) * fu + w->phaseV) + GXDATA_F32(&src->u));
        GXDATA_SET_F32(&dst->v, w->ampV * LUT_Sin12Bit(GXDATA_F32(&src->v) * fv + w->phaseV) + GXDATA_F32(&src->v));
    }
}

void fn_8018FC24(Obj *self) {
    Wave *w = self->wave;
    if (w && w->node) {
        w->phaseU += w->speedU;
        if (w->phaseU >= 360.0f) w->phaseU -= 360.0f;
        w->phaseV += w->speedV;
        if (w->phaseV >= 360.0f) w->phaseV -= 360.0f;
        fn_80182A5C(HSD_MObjGetTObj(w->node ? w->node->material : 0),w->scaleU,w->scaleV);
        UpdateUV(w);
        DCFlushRange(w->output,w->count * 8);
    }
}
