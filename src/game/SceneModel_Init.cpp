/*
 * SceneModel_Init, 0x80076494..0x8007660C: loads a scene archive and its
 * lights into an LObjList (see LObjList.cpp).
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
#include "game/types/LObjList.h"
extern "C" {
extern void* g_sceneLights[2];
extern const char lbl_803114C0[]; /* "scene_data" */
extern unsigned char SceneModel_Init_data_803FDFF8[]; /* default LObj desc */
void* FileLoader_Open(const char*);
void* Archive_GetCurrent(void*);
void* HSD_ArchiveGetPublicAddress(void*, const char*);
void* HSD_LObjLoadDesc(void*);

static inline void LoadSeparateLights(LObjList* self) {
    int i;
    for (i = 0; i < 8; ++i) {
        LObjEntry* entry = self->scene->lights[i];
        if (!entry) break;
        if (entry->desc) self->lights[i] = HSD_LObjLoadDesc(entry->desc);
    }
}
static inline void LoadSceneLights(LObjList* self, unsigned char chainLights) {
    int i;
    if (self->scene->lights) {
        if (chainLights == 1) {
            LObjDesc* prev = (LObjDesc*)self->scene->lights[0]->desc;
            if (!prev) return;
            for (i = 1; self->scene->lights[i]; ++i) {
                prev->next = self->scene->lights[i]->desc;
                prev = (LObjDesc*)self->scene->lights[i]->desc;
            }
            self->lights[0] = HSD_LObjLoadDesc(self->scene->lights[0]->desc);
        } else {
            LoadSeparateLights(self);
        }
        if (!g_sceneLights[0]) g_sceneLights[0] = HSD_LObjLoadDesc(SceneModel_Init_data_803FDFF8);
    }
}

LObjList* SceneModel_Init(LObjList* self, const char* path, unsigned char chainLights) {
    int i;
    self->archive = 0;
    for (i = 0; i < 8; ++i) self->lights[i] = 0;
    self->archive = FileLoader_Open(path);
    if (self->archive) {
        self->scene = (LObjScene*)HSD_ArchiveGetPublicAddress(Archive_GetCurrent(self->archive), lbl_803114C0);
        LoadSceneLights(self, chainLights);
    }
    return self;
}
}
