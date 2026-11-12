#include "game/objview/morph18f_private.h"
#include "game/types/gx_data.h"
extern float LUT_Sin12Bit(float);
extern void fn_80182578(void *,int);
extern void DCFlushRange(void *,unsigned int);
extern void GXInvalidateVtxCache(void);
static inline float Clamp(float f) {
    return f<0.0f ? 0.0f : (f>1.0f ? 1.0f : f);
}
static inline void BlendVector(MorphVec *dst, const MorphVec *b, const MorphVec *a, float blend) {
    int component;
    float *out=(float *)dst;
    const float *to=(const float *)a;
    const float *from=(const float *)b;
    for (component=0;component<3;component++) {
        GXDATA_SET_F32(&out[component],blend*(GXDATA_F32(&to[component])-GXDATA_F32(&from[component]))+GXDATA_F32(&from[component]));
    }
}
static inline void MorphBlend(MorphNode *n, int side, float blend) {
    int i;
    for (i=0;i<n->count;i++) {
        MorphVec *a=&n->input[0][n->indices[0][i]];
        MorphVec *b=&n->input[1][n->indices[1][i]];
        MorphVec *dst=&n->output[side][i];
        BlendVector(dst,b,a,blend);
    }
}
static inline void MorphSides(MorphNode *n, float angles[2]) {
    int side;
    for (side=0;side<2;side++) {
        float blend,alpha;
        void *material;
        blend=0.5f*(1.0f+LUT_Sin12Bit(angles[side]));
        if (angles[side]<90.0f || angles[side]>=270.0f) {
            alpha=2.0f*blend;
        } else {
            float t=(angles[side]-90.0f)/180.0f;
            blend=1.0f-0.20000000298023224f*(1.0f-blend);
            alpha=1.0f-1.5f*t;
        }
        blend=Clamp(blend);
        alpha=Clamp(alpha);
        material=n->obj[side] ? n->obj[side]->material : 0;
        if (material) fn_80182578(material,(int)(255.0f*alpha));
        MorphBlend(n,side,blend);
    }
}
void fn_8018F1E0(MorphView *self) {
    MorphNode *n;
    if (self->model) {
        self->phase += 0.6666666865348816f;
        if (self->phase>=360.0f) self->phase-=360.0f;
        for (n=self->head;n;n=n->next) {
            float phase=self->phase;
            if (n->obj[0] && n->obj[1]) {
                float angles[2];
                angles[0]=phase;
                angles[1]=180.0f+phase;
                if (angles[1]>=360.0f) angles[1]-=360.0f;
                MorphSides(n,angles);
                DCFlushRange(n->output[0],n->count*12);
                DCFlushRange(n->output[1],n->count*12);
            }
        }
        GXInvalidateVtxCache();
    }
}
