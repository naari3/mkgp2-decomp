typedef struct AwaitInitItem {
    unsigned char pad000[0xC8];
    signed char state;           /* 0x0C8 */
    unsigned char pad0c9[0x18C - 0xC9];
    signed char pendingFree;     /* 0x18C */
} AwaitInitItem;

extern void SpriteSlot_Container_Free(AwaitInitItem *);

void ItemObject_Tick_AwaitInitThenFree(AwaitInitItem *self)
{
    switch (self->state) {
    case 0:
        self->state = 1;
    case 1:
        if (self->pendingFree) {
            self->pendingFree = 0;
            SpriteSlot_Container_Free(self);
        }
        break;
    }
}
