typedef struct ColorObject {
    char pad0[0x2c];
    void *model;
    void *altModel;
    char pad34[0x4c - 0x34];
    float r;
    float g;
    float b;
    float a;
} ColorObject;

extern void MJObj_SetColorRGBA_Float(void *model, float r, float g, float b, float a);

#pragma exceptions on

void Object_SetColorRGBA(ColorObject *obj, void *model, float r, float g, float b, float a) {
    if (obj->r != r || obj->g != g || obj->b != b || obj->a != a) {
        obj->r = r;
        obj->g = g;
        obj->b = b;
        obj->a = a;
        if (model == 0) {
            model = obj->altModel ? obj->altModel : obj->model;
        }
        MJObj_SetColorRGBA_Float(model, r, g, b, a);
    }
}

void Object_SetColorAlphaOnly(ColorObject *obj, void *model, float a) {
    if (model == 0) {
        model = obj->altModel ? obj->altModel : obj->model;
    }
    if (1.0f != obj->r || 1.0f != obj->g || 1.0f != obj->b || obj->a != a) {
        obj->r = 1.0f;
        obj->g = 1.0f;
        obj->b = 1.0f;
        obj->a = a;
        MJObj_SetColorRGBA_Float(model, 1.0f, 1.0f, 1.0f, a);
    }
}

#pragma exceptions reset
