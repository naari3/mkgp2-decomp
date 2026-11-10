/* clCSSceneGetRace (0x80224ECC..0x802253EC): fade-in/out banner scene.
 * One TU with RTTI, so it owns the vtable clCSSceneGetRace_vtable_804EDF14, the base list
 * clCSSceneGetRace_data_804EDF08, the type_info objects and the class-name strings. */
#include "game/anon_80224ECC_private.h"

static SpriteResourceId sBannerSprite = { 0x68 };

void clCSSceneGetRace::Draw() {
    if (spr) {
        fn_801A0004(spr);
    }
    obj->Draw();
}

void clCSSceneGetRace::Update() {
    if (done == 1) {
        return;
    }
    bool pressed = false;
    if (GetInput()->held == 1) {
        pressed = true;
    }
    switch (state) {
    case 0:
        SpriteHandle_SetCornerAlpha(fade, (int)(lbl_806DB320 * (timer / lbl_806DB324)));
        if (timer >= 30) {
            state = 1;
            timer = 0;
        }
        break;
    case 1:
        spr->alpha = timer / lbl_806DB328;
        if (timer >= 20) {
            state = 2;
            timer = 0;
        }
        break;
    case 2:
        if (timer >= 120 || pressed) {
            state = 3;
            timer = 0;
        }
        break;
    case 3:
        spr->alpha = lbl_806DB32C - timer / lbl_806DB328;
        if (timer >= 20) {
            state = 4;
            timer = 0;
        }
        break;
    case 4:
        SpriteHandle_SetCornerAlpha(fade, (int)lbl_806DB330);
        if (timer >= 30) {
            done = 1;
        }
        break;
    }
    timer++;
    if (spr) {
        Sprite_AdvanceAnim(spr, lbl_806DB334);
    }
    obj->Update();
    SpriteHandle_RecomputeCull(fade);
}

clCSSceneGetRace::~clCSSceneGetRace() {
    fn_80169C44();
    SpriteHandle_Destroy(fade);
    if (obj) {
        delete obj;
        obj = 0;
    }
    /* fakematch (permuter): a one-trip loop hoists the 0 store into r31 ahead
     * of the null test, as in the target. Natural code: DeleteSprite(spr); */
    for (int i = 0; i < 1; i++) {
        DeleteSprite(spr);
    }
}

clCSSceneGetRace::clCSSceneGetRace() {
    obj = 0;
    xc = 0;
    timer = 0;
    state = 0;
    spr = 0;
    obj = new SceneObj(-1, -1, -1, -1, 5);
    bool show = false;
    if (g_gameMode == 0 && fn_8024F588()->flag == 1 && g_roundIndex != 3 && g_roundIndex != 7) {
        show = true;
    }
    if (fn_8024F588()->x10 >= 0) {
        done = 1;
        state = 4;
    }
    CreditMgr_SetActiveSlot(1);
    InitRumbleController(1);
    if (!show) {
        state = 4;
        done = 1;
    }
    fn_8023F5B4(&spr, &sBannerSprite, 1, lbl_806DB340, lbl_806DB344);
    spr->alpha = lbl_806DB330;
    ResCtrl rc;
    rc.mode = 2;
    rc.SetSize(lbl_806DB348, lbl_806DB34C);
    rc.Show(lbl_806DB340, lbl_806DB350, lbl_806DB32C);
    rc.SetColor(0);
    fade = SpriteHandle_CreateDefault(&rc, 3);
}

void clCSSceneGetRace::Destroy() {
    delete this;
}


extern "C" clCSSceneGetRace *fn_802253B0(void) {
    return new clCSSceneGetRace;
}

#pragma readonly_strings on
