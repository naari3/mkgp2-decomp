typedef struct ModelDesc {
    void *jobjDesc;
    void **animJoint;
    void **matAnimJoint;
    void **shapeAnimJoint;
} ModelDesc;

extern char lbl_803F57E0[];
extern char lbl_803F5888[];
extern char *lbl_806D1038;
extern char *fn_802DE2F4(void *);
extern void *fn_802C2988(void);
extern void fn_802C2930(void *);
extern void *HSD_JObjLoadDesc(void *);
extern void fn_802CE078(void *jobj, void *anim, void *matAnim, void *shapeAnim);
extern void fn_802D060C(void *, void *);

void clModelM_Construct(ModelDesc *desc, void **outModel, void **outJObj) {
    void *jobj;
    void *heap;
    char *model;
    char *saved;

    model = fn_802DE2F4(lbl_803F57E0);
    heap = fn_802C2988();
    fn_802C2930(lbl_803F5888);
    saved = lbl_806D1038;
    lbl_806D1038 = model + 0x88;
    jobj = HSD_JObjLoadDesc(desc->jobjDesc);
    fn_802CE078(jobj, desc->animJoint != 0 ? *desc->animJoint : 0,
                desc->matAnimJoint != 0 ? *desc->matAnimJoint : 0,
                desc->shapeAnimJoint != 0 ? *desc->shapeAnimJoint : 0);
    fn_802D060C(model, jobj);
    fn_802C2930(heap);
    lbl_806D1038 = saved;
    *outJObj = jobj;
    *outModel = model;
}
