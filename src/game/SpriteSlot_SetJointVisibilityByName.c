/* Show or hide a named joint of the slot's object. */
typedef struct SpriteSlot {
    unsigned char pad00[0x4];
    void *object; /* 0x04 */
} SpriteSlot;

extern void *ResolveJointByName(void *object, const char *name);
extern void JObj_Show(void *object, void *jobj, int flag);
extern void JObj_Hide(void *object, void *jobj, int flag);

void SpriteSlot_SetJointVisibilityByName(SpriteSlot *self, const char *name, int flag, signed char hide)
{
    void *jobj;

    if (self != 0) {
        jobj = ResolveJointByName(self->object, name);
        if (jobj != 0) {
            if (hide) {
                JObj_Hide(self->object, jobj, flag);
            } else {
                JObj_Show(self->object, jobj, flag);
            }
        }
    }
}
