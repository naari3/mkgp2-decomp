typedef struct ItemStateEntity {
    unsigned char pad[0x10];
    unsigned long long flags;
} ItemStateEntity;

typedef struct KartItemIseView {
    unsigned char pad[0x304];
    ItemStateEntity *ise;
} KartItemIseView;

static inline unsigned char Ise_HasFlag(ItemStateEntity *ise, unsigned long long mask)
{
    if ((ise->flags & mask) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int KartItem_QueryEffectStateFromIse(KartItemIseView *self)
{
    ItemStateEntity *ise = self->ise;
    unsigned char hit = Ise_HasFlag(ise, 0x0080000000000000ULL);

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
