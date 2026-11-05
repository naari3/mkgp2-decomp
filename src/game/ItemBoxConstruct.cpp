#include "game/ItemBoxConstruct_private.h"
static inline BoxJoint *FirstChild(BoxJoint *j) { if (!j) return 0; return j->child; }
BoxConstruct::BoxConstruct(BoxJoint *root) {
    const char *resources = lbl_8036D588;
    DebugPrintf(resources + 0x40);
    sound = 0; modelA = 0; modelB = 0; archive = 0;
    nodes = 0; selected = 0; slots = 0; count = 0;
    modelA = new BoxModel(resources + 0x60, 0);
    modelB = new BoxModel(resources + 0x70, 0);
    archive = new BoxModel(resources + 0x80, 0);
    if (!modelA || !modelB || !archive) return;
    Object_SetJObjScaleXYZ(modelA,lbl_806D8B30,lbl_806D8B30,lbl_806D8B30);
    Object_SetJObjScaleXYZ(modelB,lbl_806D8B30,lbl_806D8B30,lbl_806D8B30);
    HSD_JObjSetFlags(Archive_GetRootJObj(archive),0x200);
    nodes = HSD_JObjGetDObj(Archive_GetRootJObj(modelB));
    for (BoxDObj *d = nodes; d; d = d->next) HSD_DObjSetFlags(d,1);
    for (BoxJoint *j = FirstChild(root); j; j = j->next) ++count;
    if (count == 0) return;
    slots = (BoxSlot *)FUN_8003b120(count * sizeof(BoxSlot));
    if (!slots) { count = 0; return; }
    int i = 0;
    BoxJoint *j = FirstChild(root);
    for (; j; j = j->next, ++i) {
        if (i > count) break;
        BoxJoint *p = j->child;
        int k = 0;
        for (; p; p = p->next, ++k) {
            if (k > 3) break;
            if (!p) __assert(lbl_806D8B34,0x3f1,lbl_806D8B3C);
            slots[i].points[k].x = p->pos.x;
            if (!p) __assert(lbl_806D8B34,0x3fd,lbl_806D8B3C);
            slots[i].points[k].y = p->pos.y;
            if (!p) __assert(lbl_806D8B34,0x409,lbl_806D8B3C);
            slots[i].points[k].z = p->pos.z;
        }
        slots[i].pos.x = lbl_806D8B0C;
        slots[i].pos.y = lbl_806D8B0C;
        slots[i].pos.z = lbl_806D8B0C;
        slots[i].rx = lbl_806D8B0C;
        slots[i].ry = lbl_806D8B0C;
        slots[i].unknown = lbl_806D8B0C;
        slots[i].t = lbl_806D8B0C;
        slots[i].delay = (i % 3) * 60;
        slots[i].cooldown = 0;
        slots[i].randIdx = 0;
        for (k = 0; k < 10; ++k) {
            slots[i].shadows[k].pos.x = lbl_806D8B0C;
            slots[i].shadows[k].pos.y = lbl_806D8B0C;
            slots[i].shadows[k].pos.z = lbl_806D8B0C;
            slots[i].shadows[k].scale = lbl_806D8B0C;
        }
    }
}
