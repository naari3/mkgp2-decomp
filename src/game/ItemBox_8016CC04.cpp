/*
 * 0x8016CC04..0x8016CEA0: draw pass for a set of placed item boxes
 * (two JObj models per box plus scaled shadow transforms).
 */

typedef float Mtx[3][4];

struct Vec3f {
    float x, y, z;
};

struct BoxShadow {
    Vec3f pos;
    float scale;
};

struct ItemBoxSlot {
    char pad00[0x24];
    Vec3f pos;
    float rotX;
    float rotY;
    float rotZ;
    char pad3C[0x4];
    int hidden;
    unsigned char visible;
    char pad45[0x3];
    BoxShadow shadows[10];
    char padE8[0x8];
};

struct ListNode {
    char pad00[0x4];
    ListNode *next;
};

struct ItemBoxSet {
    char pad00[0x8];
    void *modelA;
    void *modelB;
    void *archive;
    ListNode *nodes;
    int selected;
    ItemBoxSlot *slots;
    int count;
};

class GXChannel {
public:
    GXChannel(void *root, void *desc, int flags, int mode);
    ~GXChannel();
    void PushTransform(Mtx m);

private:
    char pad[0x14];
};

extern "C" {
void HSD_DObjClearFlags(ListNode *, int);
void HSD_DObjSetFlags(ListNode *, int);
unsigned char fn_801379F0(Vec3f *, float);
void Object_SetJObjPositionVec(void *, Vec3f *);
void Object_SetJObjRotationX(void *, float);
void Object_SetJObjRotationY(void *, float);
void Object_SetJObjRotationZ(void *, float);
void Object_RenderJObjTree(void *, int);
void *Archive_GetRootJObj(void *);
void *fn_802D0758(void *);
void PSMTXScale(Mtx, float, float, float);

void fn_8016CC04(ItemBoxSet *set) {
    int n;
    ItemBoxSlot *it;
    ListNode *node;
    int i;

    if (set->count == 0) {
        return;
    }

    for (node = set->nodes, n = 0; node != 0; node = node->next, n++) {
        if (n == set->selected) {
            HSD_DObjClearFlags(node, 1);
        } else {
            HSD_DObjSetFlags(node, 1);
        }
    }

    for (it = set->slots; it <= &set->slots[set->count - 1]; it++) {
        it->visible = 0;
        if (it->hidden == 0) {
            it->visible = fn_801379F0(&it->pos, 3.0f);
        }
    }

    for (it = set->slots; it <= &set->slots[set->count - 1]; it++) {
        if (it->visible) {
            Object_SetJObjPositionVec(set->modelA, &it->pos);
            Object_SetJObjRotationX(set->modelA, it->rotX);
            Object_SetJObjRotationY(set->modelA, it->rotY);
            Object_SetJObjRotationZ(set->modelA, it->rotZ);
            Object_RenderJObjTree(set->modelA, 7);
        }
    }

    for (it = set->slots; it <= &set->slots[set->count - 1]; it++) {
        if (it->visible) {
            Object_SetJObjPositionVec(set->modelB, &it->pos);
            Object_SetJObjRotationX(set->modelB, it->rotX);
            Object_SetJObjRotationY(set->modelB, it->rotY);
            Object_SetJObjRotationZ(set->modelB, it->rotZ);
            Object_RenderJObjTree(set->modelB, 7);
        }
    }

    GXChannel ch(Archive_GetRootJObj(set->archive), fn_802D0758(Archive_GetRootJObj(set->archive)), 0x40000000, 1);

    for (it = set->slots; it <= &set->slots[set->count - 1]; it++) {
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

}
