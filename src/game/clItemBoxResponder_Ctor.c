/* Construct an item box responder and register it with the item box
 * manager when one exists. */

typedef struct clItemBoxResponder {
    void *vtable;
    void *owner;
    int registered;
} clItemBoxResponder;

extern void *lbl_806D10D0;
extern void *lbl_803F9D00[];
extern void clItemBoxManager_RegisterResponder(void *manager, clItemBoxResponder *responder);

static inline void *clItemBoxManager_Get(void)
{
    return lbl_806D10D0 == 0 ? 0 : lbl_806D10D0;
}

clItemBoxResponder *clItemBoxResponder_Ctor(clItemBoxResponder *self, void *owner)
{
    self->vtable = lbl_803F9D00;
    self->owner = owner;
    self->registered = 0;
    if (clItemBoxManager_Get() == 0) {
        return self;
    }
    clItemBoxManager_RegisterResponder(clItemBoxManager_Get(), self);
    return self;
}
