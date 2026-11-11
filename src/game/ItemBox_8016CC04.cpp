/* clKPBubble: placed bubbles and their shadow particles.
 * Deferred compilation emits the definitions in reverse source order.
 */
#include "game/types/clKPBubble.h"
typedef float Mtx[3][4];
#include "game/types/GXChannel.h"
extern "C" {
extern const float lbl_80495A94[];
void fn_801712E4(void *, float, float, float, float);
void Vec3_Subtract(Vec3f *, Vec3f *, Vec3f *);
void PSVECScale(Vec3f *, Vec3f *, float);
void PSVECAdd(Vec3f *, Vec3f *, Vec3f *);
float LookupSin(float);
double atan2(double, double);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_Free(void *);
void MemoryManager_TimedFree(void *);
void DebugPrintf(const char *, ...);

void HSD_DObjClearFlags(BoxDObj *, int);

unsigned char fn_801379F0(Vec3f *, float);
void Object_SetJObjPositionVec(void *, Vec3f *);
void Object_SetJObjRotationX(void *, float);
void Object_SetJObjRotationY(void *, float);
void Object_SetJObjRotationZ(void *, float);
void Object_RenderJObjTree(void *, int);


void PSMTXScale(Mtx, float, float, float);

}

clKPBubble::clKPBubble(BoxJoint *root) {
    BoxJoint *j;
    int i;
    BoxJoint *p;
    int k;
    BoxDObj *d;
    DebugPrintf(" CreateMapEffect : clKPBubble\n");
    sound = 0; modelA = 0; modelB = 0; archive = 0;
    nodes = 0; selected = 0; slots = 0; count = 0;
    modelA = new BoxModel("red_sphere.dat", 0);
    modelB = new BoxModel("bubble_fire.dat", 0);
    archive = new BoxModel("bubble_fire_drop.dat", 0);
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

clKPBubble::~clKPBubble() {
    if (modelA) Object_DtorWithGXSync(modelA, 1);
    if (modelB) Object_DtorWithGXSync(modelB, 1);
    if (archive) Object_DtorWithGXSync(archive, 1);
    if (slots) MemoryManager_Free(slots);
    DebugPrintf(" DeleteMapEffect : clKPBubble\n");
}

void clKPBubble::Update() {
    BoxSlot *it;
    int i;
    int spawned;
    Vec3f d;

    if (count == 0) {
        return;
    }

    for (it = slots; it <= &slots[count - 1]; it++) {
        if (it->delay > 0) {
            it->delay--;
            if (it->delay == 0) {
                it->t = 0.0f;
            }
        } else {
            if (0.0f == it->t && sound) {
                fn_801712E4(sound, it->points[1].x, it->points[1].y, it->points[1].z, 5.0f);
            }
            if (it->t >= 1.0f) {
                if (sound) {
                    fn_801712E4(sound, it->points[2].x, it->points[2].y, it->points[2].z, 5.0f);
                }
                it->delay = 60;
            }
            Vec3_Subtract(&it->points[2], &it->points[1], &d);
            PSVECScale(&d, &it->pos, it->t);
            PSVECAdd(&it->points[1], &it->pos, &it->pos);
            it->pos.y += (it->points[0].y - it->pos.y) * LookupSin(3.1415927f * it->t);
            it->ry = 1.5707964f - (float)atan2(d.z, d.x);
            it->rx = 3.1415927f * LookupSin(1.5707964f * it->t) + 1.5707964f;
            it->t += 0.008333334f;
        }

        if (it->cooldown > 0) {
            it->cooldown--;
        }

        spawned = 0;
        for (i = 0; i < 10; i++) {
            if (it->shadows[i].scale > 0.0f) {
                it->shadows[i].scale = it->shadows[i].scale - 0.1f;
                if (it->shadows[i].scale < 0.0f) {
                    it->shadows[i].scale = 0.0f;
                }
            } else if (it->delay == 0 && spawned < 1 && it->cooldown == 0) {
                it->shadows[i].scale = 0.5f * lbl_80495A94[it->randIdx] + 1.0f;
                if (++it->randIdx >= 48) {
                    it->randIdx = 0;
                }
                it->shadows[i].pos.x = 20.0f * lbl_80495A94[it->randIdx] + it->pos.x - 10.0f;
                if (++it->randIdx >= 48) {
                    it->randIdx = 0;
                }
                it->shadows[i].pos.y = 20.0f * lbl_80495A94[it->randIdx] + it->pos.y - 10.0f;
                if (++it->randIdx >= 48) {
                    it->randIdx = 0;
                }
                it->shadows[i].pos.z = 20.0f * lbl_80495A94[it->randIdx] + it->pos.z - 10.0f;
                if (++it->randIdx >= 48) {
                    it->randIdx = 0;
                }
                spawned++;
                it->cooldown = 3;
            }
        }
    }

    selected++;
    if (selected >= 15) {
        selected = 0;
    }
}


void clKPBubble::Draw() {
    int n;
    BoxSlot *it;
    BoxDObj *node;
    int i;

    if (count == 0) {
        return;
    }

    for (node = nodes, n = 0; node != 0; node = node->next, n++) {
        if (n == selected) {
            HSD_DObjClearFlags(node, 1);
        } else {
            HSD_DObjSetFlags(node, 1);
        }
    }

    for (it = slots; it <= &slots[count - 1]; it++) {
        it->visible = 0;
        if (it->delay == 0) {
            it->visible = fn_801379F0(&it->pos, 3.0f);
        }
    }

    for (it = slots; it <= &slots[count - 1]; it++) {
        if (it->visible) {
            Object_SetJObjPositionVec(modelA, &it->pos);
            Object_SetJObjRotationX(modelA, it->rx);
            Object_SetJObjRotationY(modelA, it->ry);
            Object_SetJObjRotationZ(modelA, it->unknown);
            Object_RenderJObjTree(modelA, 7);
        }
    }

    for (it = slots; it <= &slots[count - 1]; it++) {
        if (it->visible) {
            Object_SetJObjPositionVec(modelB, &it->pos);
            Object_SetJObjRotationX(modelB, it->rx);
            Object_SetJObjRotationY(modelB, it->ry);
            Object_SetJObjRotationZ(modelB, it->unknown);
            Object_RenderJObjTree(modelB, 7);
        }
    }

    GXChannel ch(Archive_GetRootJObj(archive), HSD_JObjGetDObj(Archive_GetRootJObj(archive)), 0x40000000, 1);

    for (it = slots; it <= &slots[count - 1]; it++) {
        for (i = 0; i < 10; i++) {
            if (it->shadows[i].scale > 0.0f && fn_801379F0(&it->shadows[i].pos, 1.0f)) {
                Mtx m;
                PSMTXScale(m, it->shadows[i].scale, it->shadows[i].scale, it->shadows[i].scale);
                m[0][3] = it->shadows[i].pos.x;
                m[1][3] = it->shadows[i].pos.y;
                m[2][3] = it->shadows[i].pos.z;
                ch.PushTransform(m);
            }
        }
    }
}
