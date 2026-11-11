#include "game/KartChoiceOwnerPrivate.h"

/* clFaceRank has no base class; the first virtual declaration fixes its vptr. */
class clFaceRank {
public:
    virtual ~clFaceRank();
    unsigned char hidden;
    ChoiceRender *render;
    int layer;
    int sprites[4];
    float x, y;
    int variant, resource, value, texture, alias;
    float scale;
    clFaceRank(ChoiceRender *, int);
};

clFaceRank::~clFaceRank() {
    for (int i = 0; i < 4; ++i) SpriteHandle_Destroy(sprites[i]);
}

clFaceRank::clFaceRank(ChoiceRender *render_, int layer_)
    : hidden(0), render(render_), layer(layer_), x(lbl_806DB980), y(lbl_806DB980),
      variant(render_->variant), texture(0xc24), alias(-1), scale(lbl_806DB984) {
    unsigned char special = 0;
    if (g_gameMode == 2) special = 1;
    if (fn_802317E0(&alias, &resource, &texture, render_->variant, render_->character, special) == 1) {
        if (!special) texture = 0xc24;
        value = fn_80231B74(resource);
    } else {
        resource = fn_80231BD4(6, render_->character, 0);
        texture = fn_80231B94(render_->variant);
        if (!special) texture = 0xc24;
    }
    PreloadResource(resource);
    PreloadResource(0xc28);
    PreloadResource(texture);
    ResCtrl res;
    fn_80121E10(&res);
    res.resId = alias;
    sprites[0] = SpriteHandle_CreateDefault(&res, layer);
    if (alias < 0) {
        fn_80121E10(&res);
        res.resId = resource;
        sprites[1] = SpriteHandle_CreateDefault(&res, layer);
        fn_80121E10(&res);
        res.resId = texture;
        sprites[2] = SpriteHandle_CreateDefault(&res, layer);
    } else {
        fn_80121E10(&res);
        res.resId = texture;
        sprites[2] = SpriteHandle_CreateDefault(&res, layer);
        fn_80121E10(&res);
        res.resId = resource;
        sprites[1] = SpriteHandle_CreateDefault(&res, layer);
    }
    fn_80121E10(&res);
    res.resId = 0xc28;
    sprites[3] = SpriteHandle_CreateDefault(&res, layer);
    for (int i = 0; i < 4; ++i) {
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}
