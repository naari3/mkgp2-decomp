typedef struct CObjSDKCameraView CObjSDKCameraView;
typedef struct CObjCachedView {
    unsigned char pad00[4];
    CObjSDKCameraView *camera;
    unsigned char pad08[0x20];
    unsigned int ready;
} CObjCachedView;

/* Both status callees copy three words into the second argument. */
extern void fn_802C7240(CObjSDKCameraView *, void *output);
extern void fn_802C7318(CObjSDKCameraView *, void *output);
extern float *fn_802C7E60(CObjSDKCameraView *);
extern float *fn_802C7E30(CObjSDKCameraView *);

int CObj_ApplyScissor(CObjCachedView *self, void *output) {
    if (self->ready == 0) return 0;
    fn_802C7240(self->camera, output);
    return 1;
}

int CObj_LoadProjMatrix(CObjCachedView *self, void *output) {
    if (self->ready == 0) return 0;
    fn_802C7318(self->camera, output);
    return 1;
}

float *CObj_GetProjMatrix_Cached(CObjCachedView *self) {
    if (self->ready == 0) return 0;
    return fn_802C7E60(self->camera);
}

float *CObj_GetViewMatrix_Cached(CObjCachedView *self) {
    if (self->ready == 0) return 0;
    return fn_802C7E30(self->camera);
}
