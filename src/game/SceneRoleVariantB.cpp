#include "game/FlowScene.h"

/* Target-observed role variant B owner, 24 bytes.
 * Shared list/fader types preserve their native owning-member EH. */
struct RoleBRoot {
    virtual ~RoleBRoot() {}
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
    virtual void Start(int);
    unsigned char flag;
    RoleBRoot() : flag(0) {}
};
struct RoleBFlash { char pad[12]; float value; };
extern "C" {
void PreloadResource(int);
void fn_80120A08(int);
void card_force_backup_now();
void fn_8020F3F0();
void *ItemDisplay_GetOrCreate();
void fn_8020AAD4(void *);
extern RoleBFlash *lbl_806D1A60;
extern const float lbl_806DBFC8;
extern unsigned char lbl_806D17F0;
unsigned char ServiceEnable_Get();
unsigned char ServiceValue_Get();
RoleBRoot *fn_80226860();
RoleBRoot *fn_8024D140();
RoleBRoot *fn_8024B0D8();
}
struct RoleBBase : RoleBRoot {
    RoleBRoot *child;
    int route;
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    virtual void Key();
    RoleBBase() : child(0), route(5), list(new SceneListImpl), fader(new FlowFaderI) {
        PreloadResource(0x1ecd);
        PreloadResource(0x72f);
        PreloadResource(0x734);
        PreloadResource(0x730);
        if ((lbl_806DBFC8 == lbl_806D1A60->value) == 1) fader.p->Set(255, 0, 15);
        card_force_backup_now();
        fn_8020F3F0();
    }
    ~RoleBBase() {
        fn_801F4D3C(list.p);
        fn_8020AAD4(ItemDisplay_GetOrCreate());
        fn_80120A08(0x72f);
        fn_80120A08(0x734);
        fn_80120A08(0x730);
    }
};
struct RoleB : RoleBBase {
    virtual void Key();
    RoleB() {
        fader.p->Set(255, 0, 15);
        route = 5;
        Start(route);
    }
    ~RoleB();
};
extern "C" RoleB *fn_8024C564() { return new RoleB; }
RoleB::~RoleB() {}

extern "C" void fn_8024C818(RoleBBase *self, int route) {
    if (self->child) {
        switch (route) {
        case 4:
            self->fader.p->Set(0, 255, 15);
            self->route = 10;
            break;
        case 5:
            if (lbl_806D17F0) {
                self->fader.p->Set(0, 255, 15);
                self->route = 10;
            } else {
                if (ServiceEnable_Get() && !ServiceValue_Get()) self->route = 7;
                else {
                    self->fader.p->Set(0, 255, 15);
                    self->route = 10;
                }
            }
            break;
        case 7:
            self->fader.p->Set(0, 255, 15);
            self->route = 10;
            break;
        }
        if (self->child) {
            self->child->Finish();
            self->child = 0;
        }
    }
}
extern "C" void fn_8024C944(RoleBBase *self, int route) {
    if (!self->child) {
        switch (route) {
        case 4: self->child = fn_80226860(); break;
        case 5:
            self->fader.p->Set(255, 0, 15);
            self->child = fn_8024D140(); break;
        case 7: self->child = fn_8024B0D8(); break;
        default: self->child = 0; break;
        }
    }
}
extern "C" void fn_8024C9E0(VObject *p) { delete p; }
