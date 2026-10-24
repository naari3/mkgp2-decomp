class GuardedItem {
public:
    virtual void Destroy();
    virtual unsigned char IsAlive();
};

struct ItemStateGuard {
    unsigned char pad[0x18];
    GuardedItem *item;
};

extern "C" int ItemStateGuard_PruneIfDeadAndReport(ItemStateGuard *guard) {
    if (guard->item == 0) {
        return 0;
    }
    if (!guard->item->IsAlive()) {
        guard->item->Destroy();
        guard->item = 0;
        return 0;
    }
    return 1;
}
