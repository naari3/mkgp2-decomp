/* Whole-TU C++ lifetime retrofit; only observed manager layout is modeled.
 * Slot+0x14 is the external SpriteSlot subobject. The loop invokes each
 * element destructor without deallocating the static 256-element pool.
 * The canonical strong ScopedTimer destructor owns exception cleanup;
 * the generated weak copy is discarded at link time. */
#pragma cplusplus on
class ManagedObject {
public:
    ~ManagedObject();
};
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
void SpriteSlot_Destroy(void *slot);
void AnimStatePool_FreeAll(void);
extern const float lbl_806D5A94;
}
class ScopedTimer {
public:
    inline ScopedTimer(int slot) { m_slot = slot; m_startTick = OSGetTick(); }
    inline ~ScopedTimer()
    {
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D5A94);
    }
private:
    unsigned int m_startTick;
    volatile int m_slot;
};
class ItemSlot {
public:
    unsigned char active;
    unsigned char reserved[0x1EB];
    inline ~ItemSlot()
    {
        SpriteSlot_Destroy((unsigned char *)this + 0x14);
        active = 0;
    }
};
struct ManagerView {
    ItemSlot slots[256];
    ManagedObject *object;
};
static inline void DestroySlots(ItemSlot *first)
{
    ItemSlot *slot = first;
    int i = 0;
    for (; i < 256; ++i, ++slot) {
        slot->~ItemSlot();
    }
}
extern "C" {
extern ManagerView lbl_80638300;
void ItemObjectManager_RenderImpl(ManagerView *manager);
void ItemObjectManager_TickActiveItems(ManagerView *manager);
void ItemObjectManager_Render(void)
{
    ScopedTimer timer(0x1D);
    ItemObjectManager_RenderImpl(&lbl_80638300);
}
void ItemObjectManager_Reset(void)
{
    DestroySlots(lbl_80638300.slots);
    if (lbl_80638300.object != 0) {
        delete lbl_80638300.object;
    }
    lbl_80638300.object = 0;
    AnimStatePool_FreeAll();
}
void ItemObjectManager_Update(void)
{
    ScopedTimer timer(0x1C);
    ItemObjectManager_TickActiveItems(&lbl_80638300);
}
}
#pragma cplusplus off


