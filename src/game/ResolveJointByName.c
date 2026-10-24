typedef struct ModelDesc {
    void ***root;
} ModelDesc;

typedef struct JointOwner {
    unsigned char pad[0x24];
    void *archive;
    ModelDesc *model;
    void *jobj;
} JointOwner;

extern void *Archive_GetCurrent(void *);
extern void *HSD_ArchiveGetPublicAddress(void *archive, char *name);
extern void *fn_802CFB68(void *symbol, void *root, void *jobj);

void *ResolveJointByName(JointOwner *owner, char *name) {
    void *jobj;
    ModelDesc *model;
    void *archive;
    void *result;

    if (owner->jobj == 0) {
        return 0;
    }
    archive = Archive_GetCurrent(owner->archive);
    jobj = owner->jobj;
    model = jobj == 0 ? 0 : owner->model;
    if (jobj == 0) {
        jobj = 0;
    }
    result = fn_802CFB68(HSD_ArchiveGetPublicAddress(archive, name), **model->root, jobj);
    if (result == owner->jobj) {
        return 0;
    }
    return result;
}
