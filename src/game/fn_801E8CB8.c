typedef struct ItemUser {
    char pad[0x18];
    int unk18;
    int unk1C;
    int unk20;
    int unk24;
} ItemUser;

int fn_801E8CB8(void) {
    return 1;
}

int fn_801E8CC0(ItemUser *self) {
    if (self->unk24 > 0) {
        return 0;
    }
    if (self->unk1C <= 0 || self->unk1C >= 0x115) {
        return 0;
    }
    return self->unk20 == 1;
}

void fn_801E8D04(ItemUser *self) {
    self->unk18 = -1;
}
