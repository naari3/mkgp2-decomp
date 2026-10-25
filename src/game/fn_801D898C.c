
typedef struct ItemInfoPanel {
    char pad000[4];
    void *sprite;
    char pad008[0x14 - 0x8];
    int field14;
    char pad018[0x64 - 0x18];
    struct {
        const char *asset;
        char pad[0x4C];
    } texts[3];
    short anim154;
    short anim156;
    short anim158;
} ItemInfoPanel;

extern int Item_GetDescriptorField8(int item);
extern int Item_GetDescriptorFieldC(int item);
extern int Item_GetDescriptorField0(int item, int variant);
extern void Sprite_SetAnimParam(void *sprite, short id, short value);
extern int fn_8023DAA8(int item);
extern const char *Item_GetLocalizedAsset(int id, int variant);

void fn_801D898C(ItemInfoPanel *self, int item, unsigned char loadText)
{
    short v;
    int a;
    int i;

    v = Item_GetDescriptorField8(item);
    if (v >= 0) {
        a = v + 0x17A3;
        Sprite_SetAnimParam(self->sprite, self->anim154, a);
        self->anim154 = a;
    }
    v = Item_GetDescriptorFieldC(item);
    if (v >= 0) {
        a = v + 0x1E1D;
        Sprite_SetAnimParam(self->sprite, self->anim156, a);
        self->anim156 = a;
    }
    if (Item_GetDescriptorField0(item, 0) >= 0) {
        a = (short)Item_GetDescriptorField0(item, 0);
        Sprite_SetAnimParam(self->sprite, self->anim158, a);
        self->anim158 = a;
    }
    if (loadText) {
        self->field14 = fn_8023DAA8(item);
        for (i = 0; i < 3; i++) {
            self->texts[i].asset = Item_GetLocalizedAsset(item, i);
        }
    }
}
