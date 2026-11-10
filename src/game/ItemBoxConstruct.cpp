#include "game/ItemBoxConstruct_private.h"
// Original file-static string pool; direct references preserve the pooled base.
#include "game/types/shared_data.h"
SHARED_STATIC const char lbl_8036D588[] = "clKPBubble";
SHARED_STATIC const char lbl_8036D594[] = "clMapEffectParts";
SHARED_STATIC const char lbl_8036D5A8[] = " DeleteMapEffect : clKPBubble\n";
static const char lbl_8036D5C8[] = " CreateMapEffect : clKPBubble\n";
static const char lbl_8036D5E8[] = "red_sphere.dat";
static const char lbl_8036D5F8[] = "bubble_fire.dat";
static const char lbl_8036D608[] = "bubble_fire_drop.dat";

BoxConstruct::BoxConstruct(BoxJoint *root) {
    BoxJoint *j;
    int i;
    BoxJoint *p;
    int k;
    BoxDObj *d;
    DebugPrintf(lbl_8036D5C8);
    sound = 0; modelA = 0; modelB = 0; archive = 0;
    nodes = 0; selected = 0; slots = 0; count = 0;
    modelA = new BoxModel(lbl_8036D5E8, 0);
    modelB = new BoxModel(lbl_8036D5F8, 0);
    archive = new BoxModel(lbl_8036D608, 0);
    if (!modelA || !modelB || !archive) return;
    Object_SetJObjScaleXYZ(modelA,lbl_806D8B30,lbl_806D8B30,lbl_806D8B30);
    Object_SetJObjScaleXYZ(modelB,lbl_806D8B30,lbl_806D8B30,lbl_806D8B30);
    HSD_JObjSetFlags(Archive_GetRootJObj(archive),0x200);
    nodes = HSD_JObjGetDObj(Archive_GetRootJObj(modelB));
    for (d = nodes; d; d = d->next) HSD_DObjSetFlags(d,1);
    for (BoxJoint *j = (root == 0 ? 0 : root->child); j; j = j->next) ++count;
    if (count == 0) return;
    slots = (BoxSlot *)FUN_8003b120(count * sizeof(BoxSlot));
    if (!slots) { count = 0; return; }
    i = 0;
    j = (root == 0 ? 0 : root->child);
    for (; j; j = j->next, ++i) {
        if (i > count) break;
        p = j->child;
        k = 0;
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
