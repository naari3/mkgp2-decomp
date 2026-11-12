#include "game/types/clRsCardT1.h"
#include "game/types/clRsContinue.h"
struct ContinueSettings { char pad[12]; float value; };
extern "C" {
extern ContinueSettings *lbl_806D1A60;
extern const float lbl_806DBFC8, lbl_806DBFCC, lbl_806DBFD0, lbl_806DBFD4, lbl_806DBFD8, lbl_806DBFDC;
extern unsigned char lbl_806D17F0, lbl_806D17F1, lbl_806D17F2;
extern unsigned char g_playerData[0x1DC];
void PreloadResource(int);
void card_force_backup_now();
void fn_8020F3F0();
void *ItemDisplay_GetOrCreate();
void fn_8020AAD4(void *);
void fn_80120A08(int);
unsigned char ServiceEnable_Get();
unsigned char ServiceValue_Get();
clSceneInterface *fn_80225F6C();
clSceneInterface *fn_8024D140();
clSceneInterface *fn_8021EFB4();
clSceneInterface *fn_8024B0D8();
clSceneInterface *fn_80226860();
void SetLocalPcbRole(int);
void SetSyncTarget(int);
void fn_801D6DF0(void *);
void HSD_StateInvalidate(unsigned int);
void fn_8021A0D0(ContinueSettings *);
void fn_802043B8(FlowSceneList *, int);
void fn_8011FAFC(ResCtrl *, int);
}
inline clRsContinue::clRsContinue()
    : child(0), route(5), list(new SceneListImpl), fader(new FlowFaderI)
{
    PreloadResource(0x1ECD);
    PreloadResource(0x72F);
    PreloadResource(0x734);
    PreloadResource(0x730);
    if ((lbl_806DBFC8 == lbl_806D1A60->value) == 1)
        fader.p->Set(255, 0, 15);
    card_force_backup_now();
    fn_8020F3F0();
}
inline clRsContinueBT::clRsContinueBT() {
    if (lbl_806D17F2) route = 4;
    else route = 5;
    Start(route);
}
inline clRsContinueTA::clRsContinueTA() { fader.p->Set(255, 0, 15); route = 5; Start(route); }
inline clRsContinueGP::clRsContinueGP() {
    fn_801D6DF0(g_playerData);
    if (lbl_806D17F2 && lbl_806D17F0)
        route = 4;
    else
        route = 5;
    Start(route);
}

/* Deferred generation: reverse target order. */
clRsContinue::~clRsContinue() {
    fn_801F4D3C(list.p);
    fn_8020AAD4(ItemDisplay_GetOrCreate());
    fn_80120A08(0x72F);
    fn_80120A08(0x734);
    fn_80120A08(0x730);
}

void clRsContinue::Update() {
    list.p->Update();
    if (!child) {
        if (route == 10) {
            fn_8021A0D0(lbl_806D1A60);
            if (lbl_806DBFC8 == lbl_806D1A60->value && fader.p->Value() == 255) {
                fn_802043B8(list.p, 0);
                done = 1;
            }
        } else Start(route);
    }
    if (child) {
        if (!child->done) child->Update();
        else Finish(route);
    }
    ResCtrl ctrl;
    unsigned char color = fader.p->Value();
    ctrl.mode = 2;
    ctrl.SetSize(lbl_806DBFCC, lbl_806DBFD0);
    ctrl.Show(lbl_806DBFD4, lbl_806DBFD8, lbl_806DBFDC);
    ctrl.SetColor(color);
    fn_8011FAFC(&ctrl, 7);
    fader.p->Step();
}

void clRsContinue::Draw() {
    if (!done) {
        list.p->Draw();
        if (child)
            child->Draw();
        HSD_StateInvalidate(~0U);
    }
}

clRsContinueGP::~clRsContinueGP() {}

extern "C" clRsContinueGP *fn_8024CA18() { return new clRsContinueGP; }

void clRsContinueGP::Destroy() { delete this; }

void clRsContinueGP::Start(int route) {
    if (!child) {
        switch (route) {
        case 4: child = fn_80226860(); break;
        case 5:
            fader.p->Set(255, 0, 15);
            child = fn_8024D140(); break;
        case 7: child = fn_8024B0D8(); break;
        default: child = 0; break;
        }
    }
}

void clRsContinueGP::Finish(int route) {
    if (child) {
        switch (route) {
        case 4:
            fader.p->Set(0, 255, 15);
            this->route = 10;
            break;
        case 5:
            if (lbl_806D17F0) {
                fader.p->Set(0, 255, 15);
                this->route = 10;
            } else {
                if (ServiceEnable_Get() && !ServiceValue_Get()) this->route = 7;
                else {
                    fader.p->Set(0, 255, 15);
                    this->route = 10;
                }
            }
            break;
        case 7:
            fader.p->Set(0, 255, 15);
            this->route = 10;
            break;
        }
        if (child) {
            child->Destroy();
            child = 0;
        }
    }
}

clRsContinueTA::~clRsContinueTA() {}

extern "C" clRsContinueTA *fn_8024C564() { return new clRsContinueTA; }

void clRsContinueTA::Destroy() { delete this; }

void clRsContinueTA::Start(int route) {
    if (!child) {
        switch (route) {
        case 5: child = fn_8024D140(); break;
        case 7: child = fn_8024B0D8(); break;
        case 6:
        default: child = 0; break;
        }
    }
}

void clRsContinueTA::Finish(int route) {
    if (child) {
        switch (route) {
        case 5:
            if (lbl_806D17F0) {
                fader.p->Set(0, 255, 15);
                this->route = 10;
            } else if (ServiceEnable_Get() && !ServiceValue_Get()) {
                this->route = 7;
            } else {
                fader.p->Set(0, 255, 15);
                this->route = 10;
            }
            break;
        case 6: break;
        case 7:
            fader.p->Set(0, 255, 15);
            this->route = 10;
            break;
        }
        if (child) {
            child->Destroy();
            child = 0;
        }
    }
}

clRsContinueBT::~clRsContinueBT() {}

extern "C" clRsContinueBT *fn_8024C0F4() { return new clRsContinueBT; }

void clRsContinueBT::Destroy() { delete this; }

void clRsContinueBT::Start(int route) {
    if (!child) {
        switch (route) {
        case 4: child = fn_80225F6C(); break;
        case 5: child = fn_8024D140(); break;
        case 6: child = fn_8021EFB4(); break;
        case 7:
            SetLocalPcbRole(0);
            SetSyncTarget(0x33);
            child = fn_8024B0D8();
            break;
        default: child = 0; break;
        }
    }
}

void clRsContinueBT::Finish(int route) {
    if (child) {
        switch (route) {
        case 4:
            if (lbl_806D17F1) {
                fader.p->Set(0, 255, 15);
                this->route = 10;
            } else this->route = 6;
            break;
        case 5:
            if (lbl_806D17F0) {
                if (lbl_806D17F1) {
                    fader.p->Set(0, 255, 15);
                    this->route = 10;
                } else this->route = 6;
            } else {
                if (ServiceEnable_Get() && !ServiceValue_Get()) {
                    this->route = 7;
                } else {
                    fader.p->Set(0, 255, 15);
                    this->route = 10;
                }
            }
            break;
        case 6:
            fader.p->Set(0, 255, 15);
            this->route = 10;
            break;
        case 7:
            fader.p->Set(0, 255, 15);
            this->route = 10;
            break;
        }
        if (child) {
            child->Destroy();
            child = 0;
        }
    }
}

void clRsCardT1::Finish() { delete this; }
