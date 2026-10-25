struct LObjList {
    void* archive;
    unsigned int unknown04;
    void* lights[8];
};
extern "C" {
void HSD_LObjDeleteCurrentAll(void*);
void HSD_LObjAddCurrent(void*);
void HSD_LObjRemoveAll(void*);
void clRom_Release(void*);
void MemoryManager_TimedFree(void*);
extern void* lbl_806D1130[2];

int LObjList_ApplyForCObj(LObjList* self) {
    if (!self->archive) return 0;
    HSD_LObjDeleteCurrentAll(0);
    for (int i = 0; i < 8; ++i) {
        if (self->lights[i]) HSD_LObjAddCurrent(self->lights[i]);
    }
    return 1;
}
LObjList* LObjList_Destroy(LObjList* self, short freeMemory) {
    if (self) {
        if (self->archive) {
            for (int i = 0; i < 8; ++i) {
                if (self->lights[i]) HSD_LObjRemoveAll(self->lights[i]);
            }
            clRom_Release(self->archive);
        }
        if (lbl_806D1130[0]) {
            HSD_LObjRemoveAll(lbl_806D1130[0]);
            lbl_806D1130[0] = 0;
        }
        if (freeMemory > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
}
