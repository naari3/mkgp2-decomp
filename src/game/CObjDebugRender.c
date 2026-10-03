typedef struct CObjSDKCameraView CObjSDKCameraView;
typedef struct CObjDebugRenderView {
    unsigned char pad00[4];
    CObjSDKCameraView *camera;
    unsigned char pad08[0x20];
    unsigned int ready;
    unsigned char pad2C[0x3008];
    unsigned char debugProjection[0x48];
} CObjDebugRenderView;

/* Camera-only SDK calls; the flush consumes a view matrix and projection data. */
extern void fn_802C4800(CObjSDKCameraView *);
extern float *fn_802C7E30(CObjSDKCameraView *);
extern void fn_80137C8C(const float *viewMatrix, const void *projection);
extern int fn_802C6C98(CObjSDKCameraView *);

void CObj_DebugVizPathFlush(CObjDebugRenderView *self) {
    fn_802C4800(self->camera);
    fn_80137C8C(fn_802C7E30(self->camera), self->debugProjection);
}

int CObj_RenderPass_Execute(CObjDebugRenderView *self) {
    if (self->ready == 0) return 0;
    return fn_802C6C98(self->camera) != 0;
}
