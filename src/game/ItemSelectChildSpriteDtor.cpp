#include "game/ItemSelectChildSprite.h"
extern "C" {
extern unsigned char lbl_806D1264[3];
int Item_GetDescriptorField0(int, void *);
void fn_80120A08(int);
}
inline ItemSelectChildOverlay::~ItemSelectChildOverlay() {
    for (int i=0; i<2; ++i) SpriteHandle_Destroy(handles[i]);
    fn_80120A08(0x13b7);
}
ItemSelectChildSprite::~ItemSelectChildSprite() {
    SpriteHandle_Destroy(handle);
    for (int i=0; i<3; ++i)
        fn_80120A08(Item_GetDescriptorField0(lbl_806D1264[i], 0));
    delete overlay;
    delete effect;
    delete item;
    delete fade;
}
