/* Minimal views of fields observed in the camera wrapper instructions. */
typedef struct CObjSDKCameraView {
    unsigned char pad00[8];
    unsigned int flags;
    unsigned char pad0C[0x48];
    float worldMatrix[3][4];
} CObjSDKCameraView;

typedef struct CObjViewportView {
    unsigned char pad00[4];
    CObjSDKCameraView *camera;
    unsigned char pad08[0x20];
    unsigned int ready;
} CObjViewportView;

extern void fn_802C72AC(CObjSDKCameraView *, const void *);
extern void fn_802C7384(CObjSDKCameraView *, const void *);
extern void fn_8025D1B8(const void *source, void *destination);
extern void __assert(const char *, int, const char *);
extern const char lbl_806D22E4[7];
extern const char lbl_806D22EC[5];

int CObj_ApplyViewport(CObjViewportView *self, const void *value) {
    if (self->ready == 0) return 0;
    fn_802C72AC(self->camera, value);
    return 1;
}

int CObj_LoadIntoGX(CObjViewportView *self, const void *value) {
    if (self->ready == 0) return 0;
    fn_802C7384(self->camera, value);
    return 1;
}

int CObj_SetWorldMatrix(CObjViewportView *self, const void *matrix) {
    CObjSDKCameraView *camera;
    if (self->ready == 0) return 0;
    camera = self->camera;
    if (camera == 0) __assert(lbl_806D22E4, 0x1A2, lbl_806D22EC);
    camera->flags |= 0x80000002;
    fn_8025D1B8(matrix, camera->worldMatrix);
    return 1;
}
