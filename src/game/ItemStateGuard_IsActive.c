typedef struct ItemStateGuard {
    unsigned char pad0[0x18];
    void *active;
} ItemStateGuard;

unsigned char ItemStateGuard_IsActive(ItemStateGuard *guard) {
    return guard->active != 0;
}
