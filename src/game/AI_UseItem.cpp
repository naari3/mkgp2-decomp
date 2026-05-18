/*
 * AI_KartController accessor: AI_UseItem @ 0x801E6BA8.
 *
 * If the kart controller has an ItemSlot bound (+0x24) and the bound
 * PathFollower (+0x2c) does not report the item slot as locked, invoke
 * the slot's vtable[4] (use-item) method with the passed item arg.
 *
 * Written as C++ so CW emits the canonical virtual-call sequence
 *   lwz r12, 0x0(r3); lwz r12, 0x10(r12); mtctr r12; bctrl
 * (the AI_UseItemSlot virtual dispatch idiom). The TU sits in `game`
 * lib (CW 1.3.2). #pragma exceptions on/reset wraps the function so
 * CW auto-emits the extab/extabindex entry (matching the AI_HasItem
 * pattern).
 */

struct AI_UseItemSlot {
    virtual void f0();
    virtual void f1();
    virtual void useItem(void *item); // vtable[+0x10]
};

struct AI_UseItemAgent {
    char pad[0x24];
    AI_UseItemSlot *slot;   // +0x24
    char pad2[4];           // +0x28
    void *path;             // +0x2C  PathFollower*
};

extern "C" unsigned char PathFollower_IsItemLocked(void *path);

#pragma exceptions on
extern "C" void AI_UseItem(AI_UseItemAgent *self, void *item) {
    if (self->slot != 0) {
        if (!PathFollower_IsItemLocked(self->path)) {
            self->slot->useItem(item);
        }
    }
}
#pragma exceptions reset
