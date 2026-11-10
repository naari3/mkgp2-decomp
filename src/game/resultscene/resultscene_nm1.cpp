#define RESULTSCENE_INLINE_SPRITE_HOLDER
#include "game/resultscene_shared.h"

ResultBuf1::~ResultBuf1() {}

ResultBuf2::~ResultBuf2() {}

ResultScreenObj::~ResultScreenObj() {
    int i;
    if (prompt) delete prompt;
    if (detail) delete detail;
    for (i = 0; i < 3; i++) {
        if (anims[i]) {
            SpriteAnimHandle_Destroy(anims[i], 1);
            anims[i] = 0;
        }
    }
    for (i = 0; i < 2; i++) {
        if (texts[i]) {
            delete texts[i];
            texts[i] = 0;
        }
    }
    SpriteHandle_Destroy(sprite);
    fn_801699D8(0, 0);
    fn_80169C44();
    fn_80120A08(0x971);
    fn_80120A08(0x972);
    fn_80120A08(0x1ad9);
    fn_80120A08(0x1ada);
    fn_80120A08(0x152c);
    fn_80232284(ItemMsg_Get(), -1.0f);
}

CoinPopupDetail::~CoinPopupDetail() {
    void **it;
    for (it = sprites.data; it != sprites.data + sprites.b; ++it) Sprite_Destroy(*it, 1);
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) {
        if (*it) delete (char *)*it;
    }
}

extern "C" {
void fn_80160364(VObj *p) {
    delete p;
}
}

extern "C" {
SceneBase *fn_80160238(void) {
    return new ResultSceneA;
}
}

extern "C" {
void fn_8015F0FC(ResultScreen *s) {
    int i;
    if (s->state == 99) return;
    for (i = 0; i < 3; i++) {
        if (s->items[i]) fn_801A0004(s->items[i]->obj);
    }
    if (s->p54) fn_8023CD54(s->p54);
    if (s->items[0]) {
        float pos[14];
        void *mgr;
        int j;
        fn_8019FF8C(s->items[0]->obj, 0x23e5, pos);
        fn_801F93EC(s->texts[0], pos[0], 12.0f + pos[1]);
        mgr = fn_801F8E58();
        for (j = 0; j < 2; j++) fn_801F8A34(mgr, s->texts[j], 6);
    }
    if (s->p58) fn_8016039C((CoinPopupDetail *)s->p58);
    fn_801678FC(7, 0.0f, 0.0f, 0.0f, s->alpha);
}
}

extern "C" {
void fn_8016039C(CoinPopupDetail *o) {
    void **it;
    void *mgr;
    if (o->on) {
        ResCtrlR r;
        r.mode = 2;
        r.u = lbl_806D87CC;
        r.v = lbl_806D87D0;
        r.enable = 1;
        r.x = lbl_806D87D4;
        r.y = lbl_806D87D8;
        r.z = lbl_806D87DC;
        r.c0 = 0x80;
        r.c1 = 0x80;
        r.c2 = 0x80;
        r.c3 = 0x80;
        fn_8011FAFC_r(&r, 4);
        fn_801A0004(o->h5c.s);
        if (o->extra) {
            fn_80121E10(&r);
            r.id = 0x1aea;
            r.enable = 1;
            r.x = lbl_806D87D4;
            r.y = lbl_806D87E0;
            r.z = lbl_806D87DC;
            fn_8011FAFC_r(&r, 4);
            fn_801A0004(o->h64.s);
            fn_80121E10(&r);
            r.id = 0x1875;
            r.enable = 1;
            r.x = lbl_806D87E4;
            r.y = lbl_806D87E8;
            r.z = lbl_806D87DC;
            fn_8011FAFC_r(&r, 4);
            fn_801A0004(o->h68.s);
            fn_80121E10(&r);
            r.id = 0x1874;
            r.enable = 1;
            r.x = lbl_806D87EC;
            r.y = lbl_806D87E8;
            r.z = lbl_806D87DC;
            fn_8011FAFC_r(&r, 4);
        }
    }
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) fn_801A0004(*it);
    mgr = fn_801F8E58();
    {
        void **jt;
        for (jt = o->bufs.data; jt != o->bufs.data + o->bufs.b; ++jt) fn_801F8A34(mgr, *jt, 5);
    }
    fn_801A0004(o->h60.s);
}
}

extern "C" {
void fn_80161444(CoinPopupDetail *o) {
    int cnt = 0;
    void **it;
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
        if (!fn_801A024C(*it)) cnt++;
    }
    if (cnt == 2) {
        if (o->mode == 0) {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].anim8, 1, 0);
        } else {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].anim8, 1, 0);
        }
        fn_80161128(o);
        o->x40 = 0x80;
        o->x44 = 0;
        o->state = 5;
        o->extra = 0;
        Sprite_SetupAnim(o->h5c.s, 0x11, 1, 0);
    }
}
}

extern "C" {
void fn_80161720(CoinPopupDetail *o) {
    int anim;
    if (o->mode == 0) {
        anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].animC;
    } else {
        anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].anim14;
    }
    Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), anim, 1, 0);
    if (o->mode == 1) {
        anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].animC;
    } else {
        anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].anim14;
    }
    Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), anim, 1, 0);
    fn_80161128(o);
    o->state = 3;
}
}

extern "C" {
void fn_801615A4(CoinPopupDetail *o) {
    if (o->active) {
        fn_801FE348();
        if (o->mode == 0) {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].anim18, 1, 0);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 2), lbl_806D884C);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 3), lbl_806D884C);
        } else {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].anim18, 1, 0);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 0), lbl_806D884C);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 1), lbl_806D884C);
        }
        fn_801A0500(o->h60.s);
        fn_80161128(o);
        o->state = 4;
    }
}
}

extern "C" {
void fn_80161128(CoinPopupDetail *o) {
    PopupSprite_SetPos(POPUP_SPR(o, 0), o->ax, o->ay);
    PopupSprite_SetPos(POPUP_SPR(o, 1), o->bx, o->by);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 0), 0x23e7, 0x1ecd);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x23e7, 0x1ecd);
    {
        PopupInfo *inf = PopupInfo_Get(o->idxA);
        Sprite_SetAnimParam(*fn_80146000(&o->sprites, 0), 0x1cfb, inf->a4);
    }
    {
        PopupInfo *inf = PopupInfo_Get(o->idxB);
        Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1cfb, inf->b14);
    }
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1565, 0x1566);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1cf5, 0x1cf6);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1563, 0x1564);
    if ((signed char)lbl_80598A60[0x20] == 2) {
        Sprite_SetAnimParam(*fn_80146000(&o->sprites, 0), 0x1cfb, 0x1d01);
    }
    if (o->mode == 0) {
        PopupSprite_SetScale(POPUP_SPR(o, 0), 1.0f);
        PopupSprite_SetScale(POPUP_SPR(o, 1), 0.8f);
        PopupText_SetCol(POPUP_TXT(o, 0), 0xFFFFFFFF);
        PopupText_SetCol(POPUP_TXT(o, 1), 0xFFFFFFFF);
        PopupText_SetCol(POPUP_TXT(o, 2), 0xC3D7F5FF);
        PopupText_SetCol(POPUP_TXT(o, 3), 0xC3D7F5FF);
    } else {
        PopupSprite_SetScale(POPUP_SPR(o, 0), 0.8f);
        PopupSprite_SetScale(POPUP_SPR(o, 1), 1.0f);
        PopupText_SetCol(POPUP_TXT(o, 0), 0xC3D7F5FF);
        PopupText_SetCol(POPUP_TXT(o, 1), 0xC3D7F5FF);
        PopupText_SetCol(POPUP_TXT(o, 2), 0xFFFFFFFF);
        PopupText_SetCol(POPUP_TXT(o, 3), 0xFFFFFFFF);
    }
    fn_80160A90(o);
}
}

extern "C" {
int has_title_changed(void) {
    int a;
    int c;
    int b;
    void *t = TitleTracker_Get();
    if (!t || !get_title_result(t, &a, &b, &c)) return 0;
    if (a == 0) return 0;
    if (a == g_playerData[0x19b] && b == g_playerData[0x19c] && c == g_playerData[0x1b1]) return 0;
    return 1;
}
}

extern "C" {
void fn_80160A90(CoinPopupDetail *o) {
    float offset = lbl_806D87C8;
    float scale = lbl_806D87DC;
    float pos[12];
    if (isJapanese()) {
        offset = lbl_806D87C4;
        scale = lbl_806D8848;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 0), 0x23e5, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 0), (12.0f + pos[0]) + offset, 12.0f + pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 0), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 0), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 0)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 0)->col = c;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 0), 0x1ecd, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 1), pos[0] + offset, pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 1), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 1), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 1)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 1)->col = c;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 1), 0x23e5, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 2), (12.0f + pos[0]) + offset, 12.0f + pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 2), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 2), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 2)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 2)->col = c;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 1), 0x1ecd, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 3), pos[0] + offset, pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 3), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 3), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 3)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 3)->col = c;
    }
}
}

extern "C" {
void fn_80160E04(CoinPopupDetail *o) {
    if (o->state < 2 && o->creditOn == 1) {
        bool unavailable;
        int credits = CreditMgr_GetCreditCount(o->creditMgr);
        unavailable = credits <= 0 || CreditMgr_GetCoinsPerCredit(o->creditMgr) == -1;
        if (!unavailable && o->credits != credits) {
            o->credits = credits;
            if (!isJapanese()) {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                void **text = fn_80146000(&o->bufs, 0);
                TexMgr_SetTexture(*text, info->textA, CreditMgr_GetCreditCount(o->creditMgr));
                fn_801F8E90(*fn_80146000(&o->bufs, 0));
            } else {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                void **text = fn_80146000(&o->bufs, 1);
                TexMgr_SetTexture(*text, info->textB, CreditMgr_GetCreditCount(o->creditMgr));
                fn_801F8E90(*fn_80146000(&o->bufs, 1));
            }
        } else if (unavailable == 1) {
            o->creditOn = 0;
            o->idxA = o->nextIdx;
            o->nextIdx = 0;
            o->mode = 0;
            {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                TexMgr_SetTexture(*fn_80146000(&o->bufs, 0), info->textA);
            }
            {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                TexMgr_SetTexture(*fn_80146000(&o->bufs, 1), info->textB);
            }
            fn_801F8E90(*fn_80146000(&o->bufs, 0));
            fn_801F8E90(*fn_80146000(&o->bufs, 1));
            if (o->state == 0) {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), resultscene_nm1_rodata_80368D80[info->a].pad0, 1, 0);
            } else {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), resultscene_nm1_rodata_80368D80[info->a].pad4, 1, 0);
                fn_8019FF6C(*fn_80146000(&o->sprites, 0), 1);
            }
            if (PopupInput_Peek()) {
                PopupInputState *input = PopupInput_Get();
                input->active = 1;
                input->x18 = 0;
                input->x1c = 0;
            }
            o->changed = 1;
            fn_80161128(o);
        }
    }
}
}

extern "C" {
void fn_80160588(void *self, int step, bool confirm) {
    CoinPopupDetail *o = (CoinPopupDetail *)self;
    if (o->state == 0) {
        if (o->x44 <= 10) {
            o->x40 = (int)(lbl_806D8834 * ((float)o->x44 / lbl_806D880C));
            o->x44++;
        }
        int cnt = Popup_CountIdle(o);
        if (cnt == 2 && fn_801A024C(o->h60.s) != 1) {
            Sprite_SetupAnim(o->h60.s, 0x9c, 1, 0);
            fn_8019FF6C(o->h60.s, 1);
            o->state = 1;
            if (PopupInput_Peek()) {
                PopupInputState *input = PopupInput_Get();
                input->active = 1;
                input->x18 = 0;
                input->x1c = 0;
            }
            o->extra = 1;
            o->pad14 = -1;
        }
    } else if (o->state == 1) {
        if (!confirm) o->changed = 0;
        if (confirm == 1 && !o->changed) {
            o->state = 2;
            if (PopupInput_Peek()) {
                PopupInputState *input = PopupInput_Get();
                input->active = 0;
                input->x18 = 0;
                input->x1c = 0;
            }
        } else {
            int old = o->mode;
            o->mode = Clamp_Int(old + step, 0, 1);
            if (old != o->mode) fn_801FE390();
        }
    } else if (o->state == 2) {
        fn_80161720(o);
    } else if (o->state == 3) {
        fn_801615A4(o);
    } else if (o->state == 4) {
        fn_80161444(o);
    } else if (o->state == 5) {
        if (o->x44 <= 15) {
            o->x40 = (int)(lbl_806D8834 * (lbl_806D87DC - (float)o->x44 / lbl_806D87F0));
            o->x44++;
        }
        int cnt = Popup_CountIdle(o);
        if (cnt == 2) o->state = 6;
    }
    if (o->pad14 != o->mode && o->state < 3 && o->state > 0) {
        int anim;
        if (o->mode == 0) anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].pad4;
        else anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxA)->a].anim14;
        Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), anim, 1, 0);
        if (o->mode == 1) anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].pad4;
        else anim = resultscene_nm1_rodata_80368D80[PopupInfo_Get(o->idxB)->b].anim14;
        Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), anim, 1, 0);
        fn_8019FF6C(*fn_80146000(&o->sprites, 0), 1);
        fn_8019FF6C(*fn_80146000(&o->sprites, 1), 1);
        ((PopupCursorSprite *)o->h60.s)->y = o->mode == 0 ? lbl_806D87C8 : lbl_806D8838;
        fn_80161128(o);
        o->pad14 = o->mode;
    }
    void **it;
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
        Sprite_AdvanceAnim(*it, lbl_806D8830);
    }
    Sprite_AdvanceAnim(o->h5c.s, lbl_806D8830);
    Sprite_AdvanceAnim(o->h60.s, lbl_806D8830);
    Sprite_AdvanceAnim(o->h64.s, lbl_806D8830);
    Sprite_AdvanceAnim(o->h68.s, lbl_806D8830);
    fn_80160E04(o);
    fn_80160A90(o);
}
}

CoinPopupDetail::CoinPopupDetail(int initialMode, int enabled, int index)
    : active(enabled), sprites(2), state(0), pad14(2), mode(initialMode),
      ax(lbl_806D8818), ay(lbl_806D8850), bx(lbl_806D881C), by(lbl_806D8850),
      idxA(index), idxB(index), credits(-1), creditOn(0), on(0), extra(0),
      nextIdx(0), x40(0), x44(0), creditMgr(-1), changed(1), bufs(4),
      h5c(new ResultPopupSprite(0x12, 1, 0)),
      h60(new ResultPopupSprite(0x9d, 1, 0)),
      h64(new ResultPopupSprite(0x4a, 1, 0)),
      h68(new ResultPopupSprite(0x74, 1, 0)) {
    if (idxA == 4 || idxA == 5 || idxA == 7 || idxA == 8) {
        creditOn = 1;
        nextIdx = idxA;
        int idx = 3;
        if (!lbl_80598A60[0x27]) idx = 2;
        idxA = idx;
        switch (nextIdx) {
        case 4: creditMgr = 2; break;
        case 5: creditMgr = 3; break;
        case 7: creditMgr = 1; break;
        case 8: creditMgr = 1; break;
        }
    }
    void **it;
    for (it = sprites.data; it != sprites.data + sprites.b; ++it) *it = 0;
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) *it = 0;
    *fn_80146000(&sprites, 0) = new ResultPopupSprite(
        mode == 0 ? resultscene_nm1_rodata_80368D80[PopupInfo_Get(idxA)->a].pad0 : resultscene_nm1_rodata_80368D80[PopupInfo_Get(idxA)->a].anim10,
        1, 0);
    *fn_80146000(&sprites, 1) = new ResultPopupSprite(
        mode == 1 ? resultscene_nm1_rodata_80368D80[PopupInfo_Get(idxB)->b].pad0 : resultscene_nm1_rodata_80368D80[PopupInfo_Get(idxB)->b].anim10,
        1, 0);
    Sprite_SetAnimParam(*fn_80146000(&sprites, 0), 0x23e7, 0x1ecd);
    Sprite_SetAnimParam(*fn_80146000(&sprites, 1), 0x23e7, 0x1ecd);
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) {
        *it = new ResultPopupText;
        TexMgr_SetTexture(*it, lbl_806D884C);
        ((ResultPopupText *)*it)->font = 1;
        fn_801F8FCC(*it, 1);
        ((ResultPopupText *)*it)->advance = lbl_806D8854;
    }
    {
        PopupInfo *info = PopupInfo_Get(idxA);
        TexMgr_SetTexture(*fn_80146000(&bufs, 0), info->textA);
    }
    {
        PopupInfo *info = PopupInfo_Get(idxA);
        TexMgr_SetTexture(*fn_80146000(&bufs, 1), info->textB);
    }
    {
        PopupInfo *info = PopupInfo_Get(idxB);
        TexMgr_SetTexture(*fn_80146000(&bufs, 2), info->textC);
    }
    {
        PopupInfo *info = PopupInfo_Get(idxB);
        TexMgr_SetTexture(*fn_80146000(&bufs, 3), info->textD);
    }
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) fn_801F8E90(*it);
    fn_80160E04(this);
    PopupSprite_SetPos((PopupSprite *)h5c.s, lbl_806D87D4, lbl_806D8850);
    PopupSprite_SetPos((PopupSprite *)h60.s, lbl_806D87D4, lbl_806D8850);
    ((ResultPopupSprite *)h60.s)->angle = mode == 0 ? lbl_806D87C8 : lbl_806D8838;
    PopupSprite_SetPos((PopupSprite *)h64.s, lbl_806D8804, lbl_806D87E8);
    fn_8019FF6C(h64.s, 1);
    PopupSprite_SetPos((PopupSprite *)h68.s, lbl_806D87FC, lbl_806D8800);
    fn_8019FF6C(h68.s, 1);
    fn_80161128(this);
}

ResultSub::ResultSub(int a, int b) : ResultMid(b) {
    mode = a;
    state = 0;
    timer = lbl_806D87C8;
    flag = fn_80169DF0();
    timer2 = lbl_806D87C8;
    hasTitle = 1;
    titleChanged = 0;
    resource = 0x1ad9;
    title = 0;
    rank = 0;
    character = 0;
    sprite = (void *)-1;
    scale = lbl_806D8828;
    alpha = lbl_806D87C8;
    detail = 0;
    if (!g_playerData[0x19b]) hasTitle = 0;
    void *tracker = TitleTracker_Get();
    if (tracker) get_title_result(tracker, &title, &rank, &character);
    InitRumbleController(1);
    PreloadResource(0x1ad9);
    PreloadResource(0x1ada);
    anims[0] = 0;
    anims[1] = 0;
    anims[2] = 0;
    SpriteGroup_CreateOrInit(&anims[0], resultscene_nm1_data_806CF914, 0, lbl_806D87D4, lbl_806D87D8);
    SpriteGroup_CreateOrInit(&anims[1], resultscene_nm1_data_806CF918, 0, lbl_806D87D4, lbl_806D87D8);
    SpriteGroup_CreateOrInit(&anims[2], resultscene_nm1_data_806CF91C, 0, lbl_806D8858, lbl_806D885C);
    SpriteAnimParamBlock_SetAnimParamCached(anims[2], 0x1ad4, 0x1ad9);
    ((ResultPopupSprite *)*(void **)anims[1])->alpha = lbl_806D87C8;
    fn_8019FF6C(*(void **)anims[1], 1);
    texts[0] = new ResultPopupText;
    int charId = g_characterId;
    TexMgr_SetTexture(texts[0], get_title_name(TitleTracker_Get(), title, rank, charId, character));
    texts[0]->color = 0xFFFFFF00;
    texts[0]->font = 1;
    fn_801F8FCC(texts[0], 1);
    if (isJapanese() == 1) {
        fn_801F93D0(texts[0], lbl_806D8860, lbl_806D8860);
        texts[0]->advance = lbl_806D8864;
    }
    fn_801F8E90(texts[0]);
    texts[1] = new ResultPopupText;
    TexMgr_SetTexture(texts[1], get_title_name_global(TitleTracker_Get()));
    texts[1]->color = 0xFFFFFF00;
    fn_801F8FCC(texts[1], 1);
    texts[1]->advance = lbl_806D8828;
    if (!isJapanese()) fn_801F93EC(texts[1], lbl_806D8868, lbl_806D886C);
    else fn_801F93EC(texts[1], lbl_806D8870, lbl_806D886C);
    fn_801F8E90(texts[1]);
    PreloadResource(0x152c);
    ResCtrlR r;
    r.id = 0x152c;
    sprite = SpriteHandle_CreateDefault(&r, 1);
    SpriteHandle_SetActiveFlag(sprite, 0);
    fn_8011F804(sprite, lbl_806D87D4, lbl_806D886C);
    SpriteHandle_RecomputeCull(sprite);
    prompt = new CoinPrompt(0x74, -1, 0x1872, -1, 5);
    fn_8023CD3C(prompt, lbl_806D8874, lbl_806D8800);
    fn_8023CCF8(prompt, lbl_806D8878, lbl_806D87E8);
    fn_8023CCA0(prompt, 0);
}

extern "C" {
void result_screen_update(ResultSub *s) {
    PopupInputState *in = PopupInput_Get();
    bool pressed = RSInput_Pressed(in);
    int i;
    if (pressed == 1) SetRumbleMode(0, 1, 1);
    switch (s->state) {
    case 0:
        if (lbl_806D87C8 == s->timer) fn_8023CCA0(s->prompt, 1);
        {
            float a = s->timer / lbl_806D87F0;
            ((ResultPopupSprite *)*(void **)s->anims[1])->alpha = a;
            s->texts[0]->color = (0xFFFFFF00 | (unsigned char)((int)(lbl_806D87F4 * a)));
        }
        if (s->timer >= lbl_806D87F0) {
            SpriteAnimParamBlock_Reload(s->anims[2], 0x1dd);
            SpriteAnimParamBlock_SetAnimParamCached(s->anims[2], 0x1ad4, 0x1ad9);
            SpriteAnimParamBlock_Reload(s->anims[0], 0x1c1);
            ((ResultPopupSprite *)*(void **)s->anims[1])->alpha = lbl_806D87DC;
            s->texts[0]->color = 0xFFFFFFFF;
            s->state = 1;
            s->timer = lbl_806D87C8;
        }
        break;
    case 1:
        fn_801699D8(0, 1);
        s->state = 2;
        s->timer = lbl_806D87C8;
        break;
    case 2:
        if (s->timer >= lbl_806D87F8 || pressed) {
            RSSub_DeletePrompt(s);
            if (s->hasTitle) {
                s->state = 5;
                SpriteHandle_SetCornerAlpha(s->sprite, 0);
                SpriteHandle_SetActiveFlag(s->sprite, 1);
                SpriteAnimParamBlock_Reload(s->anims[2], 0xc7);
                SpriteAnimParamBlock_SetAnimParamCached(s->anims[2], 0x1ad4, 0x1ad9);
                s->prompt = new CoinPrompt(0x74, 0x4a, 0x1874, 0x1875, 5);
                fn_8023CD3C(s->prompt, lbl_806D87FC, lbl_806D8800);
                fn_8023CCF8(s->prompt, lbl_806D87EC, lbl_806D87E8);
                fn_8023CD24(s->prompt, lbl_806D8804, lbl_806D87E8);
                fn_8023CCCC(s->prompt, lbl_806D87E4, lbl_806D87E8);
            } else {
                s->state = 3;
            }
            s->timer = lbl_806D87C8;
        }
        break;
    case 3:
        s->alpha = s->timer / lbl_806D8808;
        if (s->timer >= lbl_806D8808) {
            s->state = 4;
            fn_8021A0B0(lbl_806D1A60);
        }
        break;
    case 4:
        s->titleChanged = 1;
        s->state = 99;
        s->timer = lbl_806D87C8;
        RSSub_SaveTitle(s);
        break;
    case 5:
        if (s->timer <= lbl_806D880C) {
            float y = lbl_806D8810 * (s->timer / lbl_806D880C) + lbl_806D87D8;
            ((ResultPopupSprite *)*(void **)s->anims[0])->y = y;
            ((ResultPopupSprite *)*(void **)s->anims[1])->y = y;
        }
        if (lbl_806D87F0 == s->timer) {
            SpriteAnimParamBlock_Reload(s->anims[2], 0xc8);
            SpriteAnimParamBlock_SetAnimParamCached(s->anims[2], 0x1ad4, 0x1ada);
        }
        if (s->timer >= lbl_806D8808) {
            int v = (int)(lbl_806D87F4 * ((s->timer - lbl_806D8808) / lbl_806D880C));
            s->texts[1]->color = (0xFFFFFF00 | (unsigned char)(v));
            SpriteHandle_SetCornerAlpha(s->sprite, v);
        }
        if (s->timer >= lbl_806D8814) {
            s->state = 6;
            s->timer = lbl_806D87C8;
            SpriteAnimParamBlock_Reload(s->anims[2], 0x1dd);
            SpriteAnimParamBlock_SetAnimParamCached(s->anims[2], 0x1ad4, 0x1ada);
            s->detail = new CoinPopupDetail(0, 1, 0);
            RSDetail_SetPos(s->detail, lbl_806D8818, lbl_806D87D4, lbl_806D881C, lbl_806D87D4);
            s->scale = lbl_806D880C;
        }
        break;
    case 6:
        if (!s->detail) {
            s->detail = new CoinPopupDetail(0, 1, 0);
            RSDetail_SetPos(s->detail, lbl_806D8818, lbl_806D87D4, lbl_806D881C, lbl_806D87D4);
        }
        s->scale -= lbl_806D8824;
        if (s->scale <= lbl_806D87C8) {
            s->scale = lbl_806D8828;
            fn_801618CC((Obj80161888 *)s->detail, 1, 0);
            fn_80161888((Obj80161888 *)s->detail);
        }
        if (RSDetail_Mode(s->detail) != 2 || s->scale <= lbl_806D87C8) {
            s->titleChanged = RSDetail_Accept(s->detail);
            s->state = 7;
            s->timer = lbl_806D87C8;
            s->scale = lbl_806D8828;
            RSSub_SaveTitle(s);
        }
        break;
    case 7:
        if (s->timer >= lbl_806D882C && RSDetail_Done(s->detail) == 1) {
            s->state = 8;
            s->timer = lbl_806D87C8;
        }
        break;
    case 8:
        s->alpha = s->timer / lbl_806D8808;
        if (s->timer >= lbl_806D8808) {
            SpriteHandle_SetActiveFlag(s->sprite, 0);
            s->state = 99;
            s->timer = lbl_806D87C8;
            fn_8021A0B0(lbl_806D1A60);
            RSSub_DeletePrompt(s);
            s->scale = lbl_806D8828;
        }
        break;
    }
    s->timer += lbl_806D87DC;
    for (i = 0; i < 3; i++) {
        if (s->anims[i]) Sprite_AdvanceAnim(*(void **)s->anims[i], lbl_806D8830);
    }
    if (s->prompt) fn_8023CDA8(s->prompt);
    if (s->detail) {
        if (s->state == 6) fn_80160588(s->detail, in->x14, RSInput_Pressed(in));
        else fn_80160588(s->detail, 0, 0);
    }
    SpriteHandle_RecomputeCull(s->sprite);
    RumbleUpdate();
    fn_80232284(ItemMsg_Get(), s->scale);
}
}

extern "C" {
void fn_80161888(Obj80161888 *o) {
    o->active = 1;
    fn_801618CC(o, o->next, 1);
    fn_80161720((CoinPopupDetail *)o);
}
}

extern "C" {
int fn_801618CC(Obj80161888 *o, int v, bool unused) {
    if (o->ready == 0) return 0;
    o->next = v;
    o->cur = -1;
    fn_80160588(o, 0, unused);
    return 1;
}
}
