typedef struct MaterialNode { char pad[8]; void *material; } MaterialNode;
typedef struct UV { float u,v; } UV;
typedef struct Wave { float speedU,speedV,scaleU,scaleV,ampU,ampV,freqU,freqV; MaterialNode *node; char pad24[0x10]; int count; unsigned short *indices; UV *output,*input; float phaseU,phaseV; } Wave;
typedef struct Obj { void *vt,*model; Wave *wave; } Obj;
extern const float lbl_806D94C8;
extern void *HSD_MObjGetTObj(void *);
extern void fn_80182A5C(void *,float,float);
extern float fn_80186960(float);
extern float LUT_Sin12Bit(float);
extern void DCFlushRange(void *,unsigned int);
void fn_8018FC24(Obj *self) {
    int i;
    UV *dst;
    UV *src;
    Wave *w = self->wave;
    if (w && w->node) {
        float fv, fu;
        w->phaseU += w->speedU;
        if (w->phaseU >= lbl_806D94C8) w->phaseU -= lbl_806D94C8;
        w->phaseV += w->speedV;
        if (w->phaseV >= lbl_806D94C8) w->phaseV -= lbl_806D94C8;
        fn_80182A5C(HSD_MObjGetTObj(w->node ? w->node->material : 0),w->scaleU,w->scaleV);
        fu = lbl_806D94C8 * w->freqU;
        fv = lbl_806D94C8 * w->freqV;
        for (i=0;i<w->count;i++) {
            dst = &w->output[i];
            src = &w->input[w->indices[i]];
            dst->u = w->ampU * fn_80186960(src->u * fu + w->phaseV) + src->u;
            dst->v = w->ampV * LUT_Sin12Bit(src->v * fv + w->phaseV) + src->v;
        }
        DCFlushRange(w->output,w->count * 8);
    }
}
