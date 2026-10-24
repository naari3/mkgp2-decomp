typedef struct Scene3D {
    unsigned char pad_0000[4];
    void *camera;
    unsigned char pad_0008[0x20];
    void *active;
    unsigned char pad_002C[0x3008];
    unsigned char projection[0x48];
    float nearZ;
    float farZ;
} Scene3D;

extern char lbl_802E96D0[];
extern char lbl_802E96FC[];
extern void fn_802C8440(void *);
extern int fn_802C8418(void *);
extern float fn_802C834C(void *);
extern float fn_802C8308(void *);
extern void fn_8013879C(void *, float, float, float, float);
extern void DebugPrintf(const char *, ...);

int Scene3D_SetupProjection(Scene3D *scene) {
    float aspect;

    if (scene->active == 0) {
        return 0;
    }
    fn_802C8440(scene->camera);
    if (fn_802C8418(scene->camera) == 1) {
        aspect = fn_802C834C(scene->camera);
        fn_8013879C(scene->projection, 0.017453292f * fn_802C8308(scene->camera), aspect,
                    scene->nearZ, scene->farZ);
    } else {
        DebugPrintf(lbl_802E96D0);
        DebugPrintf(lbl_802E96FC);
        DebugPrintf(lbl_802E96D0);
    }
    return 1;
}
