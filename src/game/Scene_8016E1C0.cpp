/*
 * 0x8016E1C0..0x8016E568: course prop list (vtable lbl_804911AC, base
 * vtable lbl_80490FE0): draw, per-node update, destructor, and the
 * self-recursive node destructor (node vtable lbl_804911F4).
 */

struct Vec3f {
    float x, y, z;
};

struct PropData {
    Vec3f pos;
    float rotY;
    int type;
};

struct PropKind {
    int pad00;
    float radius;
    float yOffset;
    float scale;
};

struct PropNode {
    PropNode *next;
    char pad04[0x4];
    PropData *data;
    float frame;

    virtual void Update();
    ~PropNode() {
        if (next) {
            delete next;
        }
    }
};

struct PropList {
    void *vtable;
    void *models[3];
    PropNode *nodes;
};

extern "C" {
extern const PropKind lbl_8036D75C[3];
extern char lbl_804911AC[];
extern char lbl_80490FE0[];
extern char lbl_8036D89C[];
unsigned char fn_801379F0(Vec3f *, float);
void Object_SetField8_AndDirty(void *, float);
void clNormal3D_Exec(void *);
void Object_SetJObjPositionVec(void *, Vec3f *);
void Object_SetJObjRotationY(void *, float);
void Object_SetJObjScaleXYZ(void *, float, float, float);
void Object_RenderJObjTree(void *, int);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_TimedFree(void *);
void DebugPrintf(const char *, ...);

void fn_8016E1C0(PropList *self) {
    PropNode *node;

    for (node = self->nodes; node != 0; node = node->next) {
        PropData *d = node->data;
        Vec3f pos;

        pos.x = d->pos.x;
        pos.y = d->pos.y;
        pos.z = d->pos.z;
        pos.y = pos.y + lbl_8036D75C[d->type].yOffset;
        if (fn_801379F0(&pos, lbl_8036D75C[d->type].radius)) {
            Object_SetField8_AndDirty(self->models[d->type], node->frame);
            clNormal3D_Exec(self->models[d->type]);
            Object_SetJObjPositionVec(self->models[d->type], &d->pos);
            Object_SetJObjRotationY(self->models[d->type], d->rotY);
            Object_SetJObjScaleXYZ(self->models[d->type], lbl_8036D75C[d->type].scale,
                                   lbl_8036D75C[d->type].scale, lbl_8036D75C[d->type].scale);
            Object_RenderJObjTree(self->models[d->type], 7);
        }
    }
}

void fn_8016E308(PropList *self) {
    PropNode *node;

    for (node = self->nodes; node != 0; node = node->next) {
        node->Update();
    }
}

void fn_8016E354(void) {
}

PropList *fn_8016E358(PropList *self, short flag) {
    int i;

    if (self) {
        self->vtable = lbl_804911AC;
        for (i = 0; i < 3; i++) {
            if (self->models[i]) {
                Object_DtorWithGXSync(self->models[i], 1);
            }
        }
        if (self->nodes) {
            delete self->nodes;
        }
        DebugPrintf(lbl_8036D89C);
        if (self) {
            self->vtable = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}
