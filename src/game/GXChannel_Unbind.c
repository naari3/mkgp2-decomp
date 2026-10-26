/* Unbind a GX channel: let the bound object restore its state, then clear
 * the current HSD MObj/DObj, vertex descriptors and render state. */
typedef struct GXObjClass {
    unsigned char pad00[0x50];
    void (*unbind)(void *obj, void *arg);
} GXObjClass;

typedef struct GXObj {
    GXObjClass *klass;
} GXObj;

typedef struct GXOwner {
    unsigned char pad00[0x8];
    GXObj *obj; /* 0x08 */
} GXOwner;

typedef struct GXChannel {
    unsigned char pad00[0x4];
    GXOwner *owner;      /* 0x04 */
    void *arg;           /* 0x08 */
    unsigned char bound; /* 0x0C */
} GXChannel;

extern void HSD_MObjSetCurrent(void *mobj);
extern void HSD_DObjSetCurrent(void *dobj);
extern void HSD_ClearVtxDesc(void);
extern void HSD_StateInvalidate(int state);

int GXChannel_Unbind(GXChannel *self)
{
    if (self->bound == 1) {
        GXObj *obj = self->owner->obj;
        obj->klass->unbind(obj, self->arg);
        HSD_MObjSetCurrent(0);
        HSD_DObjSetCurrent(0);
        HSD_ClearVtxDesc();
        HSD_StateInvalidate(-1);
        self->bound = 0;
    }
    return 1;
}
