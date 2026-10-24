typedef struct HSD_JObj {
    unsigned char pad[0x1C];
    float rotation[4];
    float scale[3];
    float position[3];
} HSD_JObj;

void Object_CopyFieldsRotPosScale(void *object, HSD_JObj *src, HSD_JObj *dst) {
    dst->position[0] = src->position[0];
    dst->position[1] = src->position[1];
    dst->position[2] = src->position[2];
    dst->rotation[0] = src->rotation[0];
    dst->rotation[1] = src->rotation[1];
    dst->rotation[2] = src->rotation[2];
    dst->rotation[3] = src->rotation[3];
    dst->scale[0] = src->scale[0];
    dst->scale[1] = src->scale[1];
    dst->scale[2] = src->scale[2];
}
