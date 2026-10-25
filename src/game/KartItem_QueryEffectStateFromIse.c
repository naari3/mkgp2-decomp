typedef struct ItemStateEntity {
    unsigned char pad[0x10];
    unsigned long long flags;
} ItemStateEntity;

typedef struct KartItemIseView {
    unsigned char pad[0x304];
    ItemStateEntity *ise;
} KartItemIseView;

int KartItem_QueryEffectStateFromIse(KartItemIseView *self)
{
    ItemStateEntity *ise = self->ise;
    unsigned long long zero = 0;
    unsigned char hit = zero;

    if (((ise->flags & 0x0080000000000000ULL) ^ zero) == 0) {
    } else {
        hit = 1;
    }
    if (hit) {
        return 2;
    }
    if (ise->flags & 0x0100000000000000ULL) {
        return 2;
    }
    if (ise->flags & 0x40ULL) {
        return 2;
    }
    if (ise->flags & 0x400ULL) {
        return 3;
    }
    if (ise->flags & 0x80ULL) {
        return 5;
    }
    return 1;
}
