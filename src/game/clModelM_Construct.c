typedef struct ModelDesc {
    void *jobjDesc;
    void **animJoint;
    void **matAnimJoint;
    void **shapeAnimJoint;
} ModelDesc;

extern char lbl_803F57E0[];
extern char lbl_803F5888[];
extern char *lbl_806D1038;
extern char *hsdNew(void *);
extern void *HSD_MObjGetDefaultClass(void);
extern void HSD_MObjSetDefaultClass(void *);
extern void *HSD_JObjLoadJoint(void *);
extern void HSD_JObjAddAnimAll(void *jobj, void *anim, void *matAnim, void *shapeAnim);
extern void HSD_JObjAddChild(void *, void *);

void clModelM_Construct(ModelDesc *desc, void **outModel, void **outJObj) {
    void *jobj;
    void *heap;
    char *model;
    char *saved;

    model = hsdNew(lbl_803F57E0);
    heap = HSD_MObjGetDefaultClass();
    HSD_MObjSetDefaultClass(lbl_803F5888);
    saved = lbl_806D1038;
    lbl_806D1038 = model + 0x88;
    jobj = HSD_JObjLoadJoint(desc->jobjDesc);
    HSD_JObjAddAnimAll(jobj, desc->animJoint != 0 ? *desc->animJoint : 0,
                desc->matAnimJoint != 0 ? *desc->matAnimJoint : 0,
                desc->shapeAnimJoint != 0 ? *desc->shapeAnimJoint : 0);
    HSD_JObjAddChild(model, jobj);
    HSD_MObjSetDefaultClass(heap);
    lbl_806D1038 = saved;
    *outJObj = jobj;
    *outModel = model;
}
