#include "game/types/DrawNode.h"
struct DrawRoot { DrawNode* nodes; };
struct DrawArchive { void* a; void* b; DrawRoot** roots; };
struct DrawSlot { int id; int a; int b; int mode; void* entry; };
extern "C" {
extern DrawSlot g_transparentDrawSlots[32];
extern unsigned char lbl_806D10F0;
extern int g_sceneDrawListNextId, lbl_806D10F8;
extern char lbl_8030E588[];
void* Archive_GetCurrent(void*);
DrawArchive* HSD_ArchiveGetPublicAddress(void*, const char*);
void TransparentDraw_InitEntry(void*, DrawNode*);
void TransparentDraw_DestroyEntry(void*, int);
}
static inline DrawSlot* FindSlot() {
    for (int i=0;i<32;i++) {
        if (g_transparentDrawSlots[i].id == -1 && g_transparentDrawSlots[i].entry)
            return &g_transparentDrawSlots[i];
    }
    return 0;
}
extern "C" int SceneDrawList_RegisterArchive(void* archive, int mode) {
    if (!archive) return -1;
    DrawArchive* desc=HSD_ArchiveGetPublicAddress(Archive_GetCurrent(archive),lbl_8030E588);
    if (!desc) return -1;
    if (!desc->roots) return -1;
    int count=0;
    for (int i=0;desc->roots[i];i++) {
        for (DrawNode* node=desc->roots[i]->nodes;node;node=node->next) {
            int selected;
            if (mode==4) {
                if (!(node->flags&3)) selected=0;
                else selected=mode;
            } else {
                if (!(node->flags&3)) selected=5;
                else selected=mode;
            }
            if (selected!=5) {
                DrawSlot* slot=FindSlot();
                if (!slot) {
                    if (count) return g_sceneDrawListNextId++;
                    return -1;
                }
                TransparentDraw_InitEntry(slot->entry,node);
                slot->id=g_sceneDrawListNextId;
                slot->mode=selected;
                count++;
            }
        }
    }
    return g_sceneDrawListNextId++;
}
extern "C" void SceneDrawList_Reset() {
    if (lbl_806D10F0) {
        for (int i=0;i<32;i++) {
            DrawSlot* slot=&g_transparentDrawSlots[i];
            if (slot->id!=-1) { slot->id=-1; slot->mode=5; }
            if (slot->entry) TransparentDraw_DestroyEntry(slot->entry,1);
            slot->entry=0;
        }
        g_sceneDrawListNextId=0;
        lbl_806D10F8=0;
        lbl_806D10F0=0;
    }
}
