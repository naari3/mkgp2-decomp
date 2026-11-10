#include "game/anon_8021BC44Types.h"

// Integer and floating-point arguments occupy independent ABI register banks.
void DrawResultSprite(int layer, float x, float y, float alpha, int resource, int flags);
#include "src/game/anon_8021BC44_nm1_rodata.inc"

static inline int TA_isReverse() { return g_reverseRoundFlag == 1 ? 1 : 0; }
/* The digit loop is an inline in the original: only then is the strength-
 * reduced offset counter initialised with `mr` from `i` (regalloc_patterns 94).
 * `res` is the caller's local (reference parameter), so it is coloured after
 * the inline temps. */
static inline void TA_makeDigits(TimeAttackResult *self, int &res) {
    for (int i = 0; i < 9; i++) {
        res = fn_80167744(8 - i, self->time) + 0x1531;
        self->digits[i] = new clCSPartsResultTimeNum(res);
        self->digits[i]->obj = 1;
        self->digits[i]->m0C();
    }
}

TimeAttackResult::TimeAttackResult()
    : state(0), timer(lbl_806DB074), x18(0), noRecord(0), rank(-1), showBanner(0), time(lbl_806DB074), best(lbl_806DB078), fade(lbl_806DB07C),
      credit(0), record(0), banner(0), title(0), coin(0), entry(0), prompt(new CoinPrompt(0x74, -1, 0x1872, -1, 4)),
      course(new Sprite(0x14F, 0, 0)), blink(new Blink) {
    rank = TaRecord_GetLastInsertedRank();
    noRecord = fn_80169DF0();
    showBanner = fn_8024F588()->flag;
    time = g_totalRaceTime;
    name.c[0] = 0;
    name.c[1] = 0;
    name.c[2] = 0;
    name.c[3] = 0;
    name.c[4] = 0;
    name.c[5] = 0;
    best = time;
    lbl_80679C88.Set(g_kartVariant, g_characterId, g_ccClass, TA_isReverse(), g_longRoundFlag, g_cupId, lbl_806DB084 * g_totalRaceTime);
    if (fn_8018B300() != 0) {
        DebugPrintf(lbl_806DB088, fn_8018B300());
        unsigned short buf[5];
        fn_8018B14C(buf);
        for (int i = 0; i < 5; i++) {
            DebugPrintf(s_fmtName, i, buf[i]);
        }
        DebugPrintf(s_fmt1, fn_8018B088());
        DebugPrintf(s_fmt2, fn_8018AFC0());
        DebugPrintf(s_fmt3, fn_8018AEF8());
        DebugPrintf(s_fmt4, fn_8018AE34());
        DebugPrintf(s_fmt5, fn_8018AD70());
        DebugPrintf(s_fmt6, fn_8018A8D4());
    }
    if (noRecord == 0) {
        g_playerData.last = lbl_80679C88;
    }
    int res;
    TA_makeDigits(this, res);
    record = new clCSPartsResultRecord;
    record->obj = 1;
    record->m0C();
    title = (TitlePart *)fn_80271340(fn_80160238(), 0, lbl_806D04B0, lbl_806D04A8, 0);
    showBanner = fn_8024F588()->flag;
    fn_8023CEB4(prompt.p);
    fn_8023CD3C(prompt.p, lbl_806DB08C, lbl_806DB090);
    fn_8023CCF8(prompt.p, lbl_806DB094, lbl_806DB098);
    entry = 0;
    course.p->layer = 0;
    course.p->SetPos(lbl_806DB09C, lbl_806DB0A0);
    SetCourseAnim(course.p, 0xA9C, 0);
    SetCourseAnim(course.p, 0xA9D, 1);
    fn_801A0550(course.p);
    course.p->alpha = lbl_806DB07C;
    blink.p->spr->layer = 5;
    blink.p->spr->x = fn_801D8D3C(g_cupId, g_longRoundFlag);
    blink.p->spr->y = lbl_806DB0A4;
    SetInput(1);
}

void TimeAttackResult::Draw() {
    ResCtrl bg;
    unsigned int c = lbl_806DB0A8 * fade;
    bg.mode = 2;
    bg.SetSize(lbl_806DB0AC, lbl_806DB0B0);
    bg.Show(lbl_806DB09C, lbl_806DB0A0, lbl_806DB07C);
    bg.SetColor(c);
    fn_8011FAFC(&bg, 7);
    if (done != 1) {
        fn_801A0004(course.p);
        ResCtrl band;
        unsigned int c2 = PackColor(0x3C, 0x28, 0x0A, (int)(lbl_806DB0B4 * course.p->alpha));
        band.mode = 2;
        band.SetSize(lbl_806DB0AC, lbl_806DB0B0);
        band.Show(lbl_806DB09C, lbl_806DB0A0, lbl_806DB07C);
        band.SetColor(c2);
        fn_8011FAFC(&band, 0);
        fn_8023CD54(prompt.p);
        if (banner != 0) {
            banner->Draw();
        }
        if (state >= 16 && state <= 18) {
            title->Draw();
        }
        if (state >= 19 && state <= 21 && coin != 0) {
            coin->Draw();
        }
        if (entry != 0) {
            fn_801BDB60(entry);
        }
        if (state >= 10 && state <= 12) {
            record->Draw();
        }
        Blink *b = blink.p;
        if (b->active) {
            fn_801A0004(b->spr);
        }
        HSD_StateInvalidate(-1);
    }
}

static inline void StripNameSpaces(unsigned short *buf) {
    for (int i = 0; i < 5; buf++, i++) {
        if (*buf == 0x8162) {
            *buf = 0;
        }
    }
}

static inline int TA_rev() { return g_reverseRoundFlag; }
static inline int TA_lng() { return g_longRoundFlag; }
static inline int TA_cup() { return g_cupId; }
static inline int TA_cc() { return g_ccClass; }
static inline int TA_kart() { return g_kartVariant; }
static inline int TA_chara() { return g_characterId; }

void TimeAttackResult::Update() {
    if (done) {
        return;
    }
    unsigned char pressed = 0;
    if (state == 23) {
        done = 1;
        return;
    }
    if (GetInput()->held == 1) {
        SetRumbleMode(0, 1, 1);
        pressed = 1;
    }
    switch (state) {
    case 0:
        fade = lbl_806DB07C - timer / lbl_806DB0D0;
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            state = 1;
            fn_801699D8(0, 1);
            if (g_reverseRoundFlag == 1) {
                blink.p->Open();
            }
        }
        break;
    case 1:
        DrawResult(timer / lbl_806DB0D0);
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            state = 2;
            fn_8023CFD4(prompt.p);
        }
        break;
    case 2:
        DrawResult(lbl_806DB07C);
        if (timer >= lbl_806DB0D4 || pressed) {
            fn_8023CFC8(prompt.p);
            timer = lbl_806DB074;
            if (showBanner == 1) {
                state = 4;
            } else {
                state = 3;
            }
            if (g_reverseRoundFlag == 1) {
                blink.p->Close();
            }
        }
        break;
    case 3:
        DrawResult(lbl_806DB07C - timer / lbl_806DB0D0);
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            if (rank >= 0 && rank < 10) {
                if (noRecord == 1) {
                    state = 10;
                } else {
                    state = 7;
                }
            } else {
                state = 13;
            }
        }
        break;
    case 4:
        if (banner == 0) {
            banner = new RecordBanner;
        }
        DrawResult(lbl_806DB07C);
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            state = 5;
        }
        break;
    case 5:
        DrawResult(lbl_806DB07C);
        if (banner->done) {
            timer = lbl_806DB074;
            state = 6;
        }
        break;
    case 6:
        DrawResult(lbl_806DB07C);
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            if (banner != 0) {
                delete banner;
                banner = 0;
            }
            if (rank >= 0 && rank < 10) {
                if (noRecord == 0) {
                    state = 7;
                } else {
                    state = 10;
                }
            } else {
                state = 13;
            }
        }
        break;
    case 7:
        entry = new NameEntry(isJapanese() == 0);
        ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AD8);
        state = 8;
        break;
    case 8:
        fn_801BE170(entry);
        if (entry->Done() == 1) {
            unsigned short buf[5];
            wcsncpy(buf, entry->name, 5);
            unsigned short *p = buf;
            StripNameSpaces(p);
            name.c[0] = *p;
            name.c[1] = buf[1];
            name.c[2] = buf[2];
            name.c[3] = buf[3];
            name.c[4] = buf[4];
            delete entry;
            entry = 0;
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            RecName *rec = TaRecord_GetEntry_Current(rank);
            rec->c[0] = name.c[0];
            rec->c[1] = name.c[1];
            rec->c[2] = name.c[2];
            rec->c[3] = name.c[3];
            rec->c[4] = name.c[4];
            rec->c[5] = name.c[5];
            SetInput(1);
            state = 9;
            timer = lbl_806DB074;
        }
        break;
    case 9:
        timer = lbl_806DB074;
        state = 10;
        break;
    case 10:
        fn_80144C1C(record);
        timer = lbl_806DB074;
        state = 11;
        break;
    case 11:
        record->Update();
        if (timer >= lbl_806DB0D8 || (timer >= lbl_806DB0DC && pressed)) {
            record->m10();
            timer = lbl_806DB074;
            state = 12;
        }
        break;
    case 12:
        record->Update();
        if (record->done == 1) {
            state = 13;
            timer = lbl_806DB074;
        }
        break;
    case 13:
        fade = timer / lbl_806DB0E0;
        if (timer >= lbl_806DB0E0) {
            timer = lbl_806DB074;
            fade = lbl_806DB07C;
            state = 14;
        }
        break;
    case 14:
        course.p->alpha = lbl_806DB074;
        timer = lbl_806DB074;
        state = 15;
        if (has_title_changed() == 1 || noRecord != 0) {
            state = 15;
        } else {
            state = 22;
        }
        fn_8021A0DC(lbl_806D1A60);
        break;
    case 15:
        fade = lbl_806DB07C - timer / lbl_806DB0D0;
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            fade = lbl_806DB074;
            if (has_title_changed() == 1) {
                state = 16;
            } else if (noRecord != 0) {
                state = 19;
            } else {
                state = 22;
            }
        }
        break;
    case 16:
        if (timer <= lbl_806DB07C) {
            fn_801699D8(0, 0);
        }
        title->Update();
        if (timer >= lbl_806DB0E0) {
            state = 17;
            timer = lbl_806DB074;
        }
        break;
    case 17:
        title->Update();
        if (title->done == 1) {
            state = 18;
            timer = lbl_806DB074;
            fn_801699D8(0, 1);
        }
        break;
    case 18:
        title->Update();
        if (timer >= lbl_806DB0E0) {
            if (noRecord != 0) {
                state = 19;
            } else {
                state = 22;
            }
            timer = lbl_806DB074;
            fade = lbl_806DB07C;
            fn_8021A0DC(lbl_806D1A60);
        }
        break;
    case 19:
        if (coin == 0) {
            fn_8018CC64();
            /* inline getters: these six are coloured before the loop temps
             * (regalloc_patterns 89) */
            int rev = TA_rev();
            int lng = TA_lng();
            int cup = TA_cup();
            int cc = TA_cc();
            int kart = TA_kart();
            int chara = TA_chara();
            fn_8018B31C(&g_playerData, chara, kart, cc, cup, lng, rev, GetCoinMilage(&g_playerData) + GetEarnedCoins(),
                        g_playerData.b19B, g_playerData.b19C, g_playerData.b1B1, 1, g_totalRaceTime);
            DebugPrintf(lbl_803C63F8, fn_8018B300());
            coin = new CoinContinue;
        }
        if (fade > lbl_806DB074) {
            fade = lbl_806DB07C - timer / lbl_806DB0E0;
        }
        coin->Update();
        if (timer >= lbl_806DB0E0) {
            state = 20;
            timer = lbl_806DB074;
        }
        break;
    case 20:
        coin->Update();
        if (coin->state == 3) {
            state = 21;
            timer = lbl_806DB074;
        }
        break;
    case 21:
        fade = timer / lbl_806DB0E0;
        if (timer >= lbl_806DB0E0) {
            state = 22;
            timer = lbl_806DB074;
        }
        break;
    case 22:
        fn_801699D8(0, 0);
        fn_8021A0B0(lbl_806D1A60);
        state = 23;
        break;
    }
    if (banner != 0) {
        banner->Update();
    }
    timer += lbl_806DB07C;
    Sprite_AdvanceAnim(course.p, lbl_806DB0E4);
    fn_8023CDA8(prompt.p);
    RumbleUpdate();
    Blink *b = blink.p;
    if (b->active) {
        if (b->t <= 8) {
            float a = b->closing == 0 ? b->t * lbl_806DB0E8
                                      : lbl_806DB07C - b->t * lbl_806DB0E8;
            b->spr->alpha = a;
            if (b->t++ == 8 && b->closing) {
                b->active = 0;
                b->closing = 0;
            }
        }
        Sprite_AdvanceAnim(b->spr, lbl_806DB0E4);
    }
}

void RecordBanner::Update() {
    InputState *in = GetInput();
    switch (state) {
    case 0: {
        int a = lbl_806DB0B8 * (timer / lbl_806DB0EC);
        if (a >= 128) {
            a = 128;
        }
        if (back->id >= 0) {
            SpriteHandle_SetCornerAlpha(back->id, a);
        }
        if (!fn_8019FE78(flash.p)) {
            state++;
            if (glow->id >= 0) {
                SpriteHandle_SetActiveFlag(glow->id, 1);
            }
            if (label->id >= 0) {
                SpriteHandle_SetActiveFlag(label->id, 1);
            }
            timer = 0;
            if (back->id >= 0) {
                SpriteHandle_SetCornerAlpha(back->id, 128);
            }
        }
        break;
    }
    case 1:
        if (timer <= 10) {
            int a = lbl_806DB0A8 * (timer / lbl_806DB0F0);
            fn_802170F0(&rows[0], a);
            fn_802170F0(&rows[1], a);
        }
        if (in->held == 1 || timer >= 240) {
            state++;
            timer = 0;
            if (glow->id >= 0) {
                SpriteHandle_SetActiveFlag(glow->id, 0);
            }
            if (label->id >= 0) {
                SpriteHandle_SetActiveFlag(label->id, 0);
            }
            Sprite_SetupAnim(flash.p, 0x48, 1, 0);
        }
        break;
    case 2: {
        if (timer <= 10) {
            int a = lbl_806DB0A8 * (lbl_806DB07C - timer / lbl_806DB0F0);
            fn_802170F0(&rows[0], a);
            fn_802170F0(&rows[1], a);
        }
        int a = lbl_806DB0B8 * (lbl_806DB07C - timer / lbl_806DB0EC);
        if (a < 0) {
            a = 0;
        }
        if (back->id >= 0) {
            SpriteHandle_SetCornerAlpha(back->id, a);
        }
        if (!fn_8019FE78(flash.p)) {
            state++;
            timer = 0;
            done = 1;
        }
        break;
    }
    case 3:
        return;
    }
    if (label->id >= 0) {
        SpriteHandle_RecomputeCull(label->id);
    }
    if (glow->id >= 0) {
        SpriteHandle_RecomputeCull(glow->id);
    }
    if (back->id >= 0) {
        SpriteHandle_RecomputeCull(back->id);
    }
    Sprite_AdvanceAnim(flash.p, lbl_806DB0E4);
    timer++;
}

RecordBanner::RecordBanner() : flash(new Sprite(0x49, 1, 0)), glow(0), label(0), state(0), timer(0), done(0) {

    rows[0].SetPos(lbl_806DB128, lbl_806DB12C);
    rows[1].SetPos(lbl_806DB128, lbl_806DB130);
    if (isJapanese() == 1) {
        fn_80217298(&rows[0], s_recJa1, 0xE0, 0x20, 0x20, lbl_806DB134);
        fn_80217298(&rows[1], s_recJa2, 0xFF, 0xFF, 0xFF, lbl_806DB134);
    } else {
        fn_80217298(&rows[0], s_recEn1, 0xE0, 0x20, 0x20, lbl_806DB134);
        fn_80217298(&rows[0], lbl_806DB138, 0xFF, 0xFF, 0xFF, lbl_806DB134);
        fn_80217298(&rows[1], s_recEn2, 0xFF, 0xFF, 0xFF, lbl_806DB134);
    }
    for (int i = 0; i < 2; i++) {
        rows[i].SetVisible(1);
        rows[i].SetLayer(6);
        fn_802170F0(&rows[i], 0);
        fn_8021713C(&rows[i]);
    }
    flash.p->SetPos(lbl_806DB09C, lbl_806DB140);
    flash.p->layer = 5;
    ResCtrl rc;
    rc.resId = 0x192A;
    rc.Show(lbl_806DB09C, lbl_806DB140, lbl_806DB07C);
    label = new SpriteBox(&rc, 6);
    if (label->id >= 0) {
        SpriteHandle_SetActiveFlag(label->id, 0);
    }
    fn_80121E10(&rc);
    rc.resId = 0x1D08;
    rc.Show(lbl_806DB144, lbl_806DB148, lbl_806DB07C);
    glow = new SpriteBox(&rc, 6);
    if (glow->id >= 0) {
        SpriteHandle_SetActiveFlag(glow->id, 0);
    }
    fn_80121E10(&rc);
    rc.mode = 2;
    rc.SetSize(lbl_806DB0AC, lbl_806DB0B0);
    rc.Show(lbl_806DB09C, lbl_806DB0A0, lbl_806DB07C);
    rc.SetColor(0);
    back = new SpriteBox(&rc, 5);
}

void TimeAttackResult::DrawResult(float alpha) {
    float k;
    float pulse = 1.0f - LUT_Sin12Bit(3.0f * x14);
    fn_80169334(1, 0x152F, 0, 320.0f, 154.0f, 1.25f, 1.0f, alpha);
    DrawResultSprite(1, lbl_806DB158, lbl_806DB0A4, alpha, s_courseRes[g_cupId - 1][g_longRoundFlag], 0);
    DrawResultSprite(1, 173.0f, 132.0f, alpha, 0x1530, 0);
    for (int i = 0; i < 9; i++) {
        if (0.0f == k) {
            digits[i]->m0C();
        }
        digits[i]->SetPos(s_partX[i], 177.0f);
        digits[i]->alpha = alpha;
        digits[i]->Update();
        digits[i]->Draw();
    }
    fn_80169334(1, 0x1540, 1, 320.0f, 102.0f, 1.25f, 1.0f, alpha);
    fn_80169334(1, 0x1540, 1, 320.0f, 207.0f, 1.25f, 1.0f, alpha);
    const float *lx = &lbl_806DB064[isJapanese()];
    const float *vx = &lbl_806DB06C[isJapanese()];
    if (rank >= 0) {
        if (rank < 10) {
            fn_801685A4(1, GetTextureByIdAndLang(0x3A, -1), *lx, s_rowY[0], 1.0f, pulse, pulse,
                        alpha);
            fn_801685A4(1, GetTextureByIdAndLang(0x3B, -1), *vx, s_rowY[0], 1.0f, pulse, pulse,
                        alpha, rank + 1);
        } else {
            fn_801685A4(1, GetTextureByIdAndLang(0x3A, -1), *lx, s_rowY[0], 1.0f, 1.0f, 1.0f,
                        alpha);
            fn_801685A4(1, GetTextureByIdAndLang(0x3B, -1), *vx, s_rowY[0], 1.0f, 1.0f, 1.0f,
                        alpha, rank + 1);
        }
    }
    if (time < best || best < 0.0f) {
        fn_801685A4(1, GetTextureByIdAndLang(0x40, -1), *lx, s_rowY[1], 1.0f, pulse, pulse,
                    alpha);
        fn_80167A24(1, 0, *vx, s_rowY[1], 1.0f, pulse, pulse, alpha, time);
    } else {
        fn_801685A4(1, GetTextureByIdAndLang(0x40, -1), *lx, s_rowY[1], 1.0f, 1.0f, 1.0f,
                    alpha);
        fn_80167A24(1, 0, *vx, s_rowY[1], 1.0f, 1.0f, 1.0f, alpha, best);
    }
    if (g_ccClass != 0) {
        Saturate_Double((x10 - 125.0f) / 25.0f, 0.0f, 1.0f);
        if (rank == 0) {
            if (isJapanese() == 1) {
                fn_801685A4(1, GetTextureByIdAndLang(0x3C, -1), *lx, s_rowY[2], 1.0f, pulse,
                            pulse, alpha);
            } else {
                fn_801685A4(1, GetTextureByIdAndLang(0x3C, -1), *lx, s_rowY[2], 1.0f, pulse,
                            pulse, alpha);
            }
            fn_80167A24(1, 0, *vx, s_rowY[2], 1.0f, pulse, pulse, alpha,
                        TaRecord_GetTime_Current(0));
        } else {
            if (isJapanese() == 1) {
                fn_801685A4(1, GetTextureByIdAndLang(0x3C, -1), *lx, s_rowY[2], 1.0f, 1.0f,
                            1.0f, alpha);
            } else {
                fn_801685A4(1, GetTextureByIdAndLang(0x3C, -1), *lx, s_rowY[2], 1.0f, 1.0f,
                            1.0f, alpha);
            }
            fn_80167A24(1, 0, *vx, s_rowY[2], 1.0f, 1.0f, 1.0f, alpha,
                        TaRecord_GetTime_Current(0));
        }
    }
    if (rank == 0) {
        DrawResultSprite(1, 298.0f, 363.0f, alpha, 0x153D, 0);
        DrawResultSprite(1, 504.0f, 363.0f, alpha, 0x153E, 0);
        DrawResultSprite(1, 320.0f, 362.0f, alpha, 0x153F, 0);
    }
}

void TimeAttackResult::Destroy() {
    delete this;
}

extern "C" TimeAttackResult *fn_8021E0C0(void) {
    return new TimeAttackResult;
}

#pragma push
#pragma opt_propagation off
CoinContinue::~CoinContinue() {
    SetInput(0);
    objs.DeleteAll();
}
#pragma pop


void CoinContinue::Draw() {
    for (FadeObj **it = objs.begin(); it != objs.end(); it++) {
        (*it)->Render();
    }
    fn_8023CD54(prompt.p);
    fn_8016039C(detail.p);
}

void CoinContinue::Update() {
    switch (state) {
    case 0:
        if (detail.p->IsOpen() == 1) {
            state = 1;
        }
        break;
    case 1:
        Select();
        break;
    case 2:
        if (detail.p->state == 6) {
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            FadeObj *o = *(FadeObj **)fn_80146000(&objs, 0);
            o->tracks[0].Set(lbl_806DB07C, lbl_806DB074, lbl_806DB0F4);
            o = *(FadeObj **)fn_80146000(&objs, 1);
            o->tracks[0].Set(lbl_806DB07C, lbl_806DB074, lbl_806DB0F4);
            state = 3;
        }
        break;
    case 3:
        break;
    }
    fn_80232284(ItemMsg_Get(), timer);
    if (state != 1) {
        fn_80160588(detail.p, 0, 0);
    }
    fn_8023CDA8(prompt.p);
    for (FadeObj **it = objs.begin(); it != objs.end(); it++) {
        (*it)->Tick();
    }
}

void CoinContinue::Select() {
    int dir = GetInput()->dir;
    InputState *in = GetInput();
    fn_80160588(detail.p, dir, in->held == 1);
    timer -= 0.016666668f;
    if (timer < 0.0f) {
        timer = 0.0f;
    }
    if (timer <= 0.0f) {
        fn_801618CC(detail.p, 1, 0);
        fn_80161888(detail.p);
        state = 2;
    }
    if (detail.p->Choice() == 1) {
        fn_8018B248();
        state = 2;
    } else if (detail.p->Choice() == 0) {
        g_playerData.last = lbl_80679C88;
        state = 2;
    }
    if (state == 2) {
        fn_8023CFC8(prompt.p);
        timer = -1.0f;
    }
}

CoinContinue::CoinContinue()
    : state(0), timer(lbl_806DB0FC), detail(new CoinPopupDetail(0, 1, 0xB)), prompt(new CoinPrompt(0x74, 0x4A, 0x1874, 0x1875, 5)) {
    SetInput(1);
    CoinPopupDetail *popup = detail.p;
    popup->SetRect(lbl_806DB100, lbl_806DB104, lbl_806DB108, lbl_806DB104);
    ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AE8);
    fn_8023CD3C(prompt.p, lbl_806DB110, lbl_806DB090);
    fn_8023CCF8(prompt.p, lbl_806DB0CC, lbl_806DB098);
    fn_8023CD24(prompt.p, lbl_806DB114, lbl_806DB098);
    fn_8023CCCC(prompt.p, lbl_806DB0C8, lbl_806DB098);
    fn_8023CEB4(prompt.p);
    fn_8023CFD4(prompt.p);
    FadeObj *o = new FadeText((const unsigned short *)GetTextureByIdAndLang(0x75, -1), lbl_806DB118);
    o->tracks[0].Set(lbl_806DB074, lbl_806DB07C, lbl_806DB0F4);
    ((FadeText *)o)->layer = 5;
    ((FadeText *)o)->scale = lbl_806DB11C;
    ((FadeText *)o)->SetSpacing(lbl_806DB120);
    PtrVec_InsertFill(&objs, objs.end(), 1, &o);
    o = new FadeText((const char *)fn_8018B300(), lbl_806DB124);
    o->tracks[0].Set(lbl_806DB074, lbl_806DB07C, lbl_806DB0F4);
    ((FadeText *)o)->layer = 5;
    ((FadeText *)o)->scale = lbl_806DB11C;
    ((FadeText *)o)->SetSpacing(lbl_806DB120);
    PtrVec_InsertFill(&objs, objs.end(), 1, &o);
    TextSprite tmp;
    tmp.visible = 1;
    TexMgr_SetTexture(&tmp, (const char *)GetTextureByIdAndLang(0x75, -1));
    TexMgr_Apply(&tmp);
    TexMgr_SetTexture(&tmp, (const char *)fn_8018B300());
    TexMgr_Apply(&tmp);
}
