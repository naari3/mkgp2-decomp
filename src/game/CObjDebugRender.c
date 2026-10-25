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
extern void HSD_LObjSetupInit(CObjSDKCameraView *);
extern float *HSD_CObjGetViewingMtxPtr(CObjSDKCameraView *);
extern void fn_80137C8C(const float *viewMatrix, const void *projection);
extern int HSD_CObjSetCurrent(CObjSDKCameraView *);

void CObj_DebugVizPathFlush(CObjDebugRenderView *self) {
    HSD_LObjSetupInit(self->camera);
    fn_80137C8C(HSD_CObjGetViewingMtxPtr(self->camera), self->debugProjection);
}

int CObj_RenderPass_Execute(CObjDebugRenderView *self) {
    if (self->ready == 0) return 0;
    return HSD_CObjSetCurrent(self->camera) != 0;
}
