typedef struct CObjSDKCameraView CObjSDKCameraView;
typedef struct CObjCachedView {
    unsigned char pad00[4];
    CObjSDKCameraView *camera;
    unsigned char pad08[0x20];
    unsigned int ready;
} CObjCachedView;

/* Both status callees copy three words into the second argument. */
extern void HSD_CObjGetInterest(CObjSDKCameraView *, void *output);
extern void HSD_CObjGetEyePosition(CObjSDKCameraView *, void *output);
extern float *HSD_CObjGetInvViewingMtxPtr(CObjSDKCameraView *);
extern float *HSD_CObjGetViewingMtxPtr(CObjSDKCameraView *);

int CObj_ApplyScissor(CObjCachedView *self, void *output) {
    if (self->ready == 0) return 0;
    HSD_CObjGetInterest(self->camera, output);
    return 1;
}

int CObj_LoadProjMatrix(CObjCachedView *self, void *output) {
    if (self->ready == 0) return 0;
    HSD_CObjGetEyePosition(self->camera, output);
    return 1;
}

float *CObj_GetProjMatrix_Cached(CObjCachedView *self) {
    if (self->ready == 0) return 0;
    return HSD_CObjGetInvViewingMtxPtr(self->camera);
}

float *CObj_GetViewMatrix_Cached(CObjCachedView *self) {
    if (self->ready == 0) return 0;
    return HSD_CObjGetViewingMtxPtr(self->camera);
}
