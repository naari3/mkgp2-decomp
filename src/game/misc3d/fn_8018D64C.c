typedef struct LightView {
    void *object;
    float x, y, z;
    float scale;
    void *dobj;
    unsigned char visible;
} LightView;

extern void HSD_DObjClearFlags(void *, unsigned int);
extern void HSD_DObjSetFlags(void *, unsigned int);
extern void Object_SetJObjPositionXYZ(void *, float, float, float);
extern void Object_SetJObjScaleXYZ(void *, float, float, float);
extern void Object_RenderJObjTree(void *, int);

static inline void SetHidden(void *dobj, int hidden) {
    if (dobj != 0) {
        if (hidden == 0) HSD_DObjClearFlags(dobj, 1);
        else HSD_DObjSetFlags(dobj, 1);
    }
}

#pragma opt_propagation off
void fn_8018D64C(LightView *self) {
    if (self->object != 0 && self->visible != 0) {
        void *dobj = self->dobj;
        int hidden = 0;
        if (dobj == 0) return;
        {
            int z = 0;
            if (z == hidden) HSD_DObjClearFlags(dobj, 1);
            else HSD_DObjSetFlags(dobj, 1);
        }
        Object_SetJObjPositionXYZ(self->object, self->x, self->y, self->z);
        Object_SetJObjScaleXYZ(self->object, self->scale, self->scale, self->scale);
        Object_RenderJObjTree(self->object, 7);
    }
}
