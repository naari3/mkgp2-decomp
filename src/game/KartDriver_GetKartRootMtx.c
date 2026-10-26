/* Local matrix of the kart's root joint, or NULL before it is loaded. */
typedef struct KartDriver {
    void *model;           /* 0x00 */
    unsigned char pad04[0x8];
    void *loaded;          /* 0x0C */
} KartDriver;

extern void *Object_GetJObjLocalMatrix(void *model);

void *KartDriver_GetKartRootMtx(KartDriver *self)
{
    if (self->model == 0 || self->loaded == 0) {
        return 0;
    }
    return Object_GetJObjLocalMatrix(self->model);
}
