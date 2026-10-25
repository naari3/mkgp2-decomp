extern "C" {
extern const float lbl_806D8894;
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
int *fn_8024F588(void);
void *fn_801F98CC(void);
int fn_801F9868(void *p, int a, int b);
int fn_801F9844(void *p, int a, int b);
int fn_80209AC4(int a, int b);
void fn_801F9888(void);
void CreditMgr_SetActiveSlot(int slot);
void InitRumbleController(int on);
}

struct SceneBase {
    SceneBase() { done = 0; }
    virtual ~SceneBase();
    unsigned char done;
};

struct Scene80162C3C : SceneBase {
    int x8;
    int pad;
    unsigned char x10;
    int x14;
    float x18;
    unsigned char service;
    int a;
    int b;
    int x28;
    int x2c;
    int x30;

    Scene80162C3C() {
        void *p;
        x8 = 0;
        x10 = 0;
        x14 = 0;
        x18 = lbl_806D8894;
        service = 1;
        if (!ServiceEnable_Get() || ServiceValue_Get() == 1) service = 0;
        a = fn_8024F588()[1];
        b = fn_8024F588()[2];
        x28 = -1;
        x2c = -1;
        x30 = 0;
        p = fn_801F98CC();
        if (p != 0) {
            x28 = fn_801F9868(p, a, b);
            x2c = fn_801F9844(p, a, b);
            x30 = fn_80209AC4(a, b);
            if (x30 <= 0 || x30 >= 0x115) {
                x30 = 0;
            } else if (service == 0) {
                x30 = 0;
            }
            fn_801F9888();
        }
        CreditMgr_SetActiveSlot(1);
        InitRumbleController(1);
    }
    virtual ~Scene80162C3C();
};

extern "C" Scene80162C3C *fn_80162C3C(void) {
    return new Scene80162C3C;
}
