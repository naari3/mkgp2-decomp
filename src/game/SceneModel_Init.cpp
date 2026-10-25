/*
 * SceneModel_Init, 0x80076494..0x8007660C: loads a scene archive and its
 * lights into an LObjList (see LObjList.cpp).
 *
 * NonMatching: register allocation in both light loops comes out in the
 * reverse order of the target.
 */
struct LObjEntry {
    void* desc;
};
struct LObjScene {
    unsigned char pad00[8];
    LObjEntry** lights;
};
struct LObjDesc {
    void* unk00;
    void* next;
};
struct LObjList {
    void* archive;
    LObjScene* scene;
    void* lights[8];
};
extern "C" {
extern void* lbl_806D1130[2];
extern const char lbl_803114C0[]; /* "scene_data" */
extern unsigned char lbl_803FDFF8[]; /* default LObj desc */
void* FileLoader_Open(const char*);
void* Archive_GetCurrent(void*);
void* HSD_ArchiveGetPublicAddress(void*, const char*);
void* HSD_LObjLoadDesc(void*);

LObjList* SceneModel_Init(LObjList* self, const char* path, unsigned char chainLights) {
    int i;
    self->archive = 0;
    for (i = 0; i < 8; ++i) self->lights[i] = 0;
    self->archive = FileLoader_Open(path);
    if (self->archive) {
        self->scene = (LObjScene*)HSD_ArchiveGetPublicAddress(Archive_GetCurrent(self->archive), lbl_803114C0);
        if (self->scene->lights) {
            if (chainLights == 1) {
                LObjDesc* prev = (LObjDesc*)self->scene->lights[0]->desc;
                if (!prev) goto done;
                for (i = 1; self->scene->lights[i]; ++i) {
                    prev->next = self->scene->lights[i]->desc;
                    prev = (LObjDesc*)self->scene->lights[i]->desc;
                }
                self->lights[0] = HSD_LObjLoadDesc(self->scene->lights[0]->desc);
            } else {
                for (i = 0; i < 8; ++i) {
                    LObjEntry* entry = self->scene->lights[i];
                    if (!entry) break;
                    if (entry->desc) self->lights[i] = HSD_LObjLoadDesc(entry->desc);
                }
            }
            if (!lbl_806D1130[0]) lbl_806D1130[0] = HSD_LObjLoadDesc(lbl_803FDFF8);
        }
    }
done:
    return self;
}
}
