/* Mode destructor: releases its sounds, shared sprites and the input state. */
struct SpriteObj {
    ~SpriteObj();
};

class InputState {
public:
    virtual ~InputState();
};

struct GameModeBase {
    void *vt;
    GameModeBase();
    ~GameModeBase();
};

extern "C" {
extern void *lbl_8049A734[];
extern unsigned char lbl_806D17F4;
extern unsigned char lbl_806D17F3;
extern int lbl_806CFD60;
extern SpriteObj *lbl_806D1820;
extern SpriteObj *lbl_806D17F8;
extern SpriteObj *lbl_806D17FC;
extern SpriteObj *lbl_806D1800;
extern SpriteObj *lbl_806D180C;
extern SpriteObj *lbl_806D1840;
extern SpriteObj *lbl_806D1844;
extern SpriteObj *lbl_80679280[3];
extern SpriteObj *lbl_8067928C[4];
extern InputState *g_pInputState;
void fn_80120A08(int id);
unsigned char fn_8019083C(int arg);
void fn_801909A4(int arg);
void fn_801908F0(void);
void fn_801B7CD0(int arg);
void fn_801DAE54(void);
void fn_80121210(void);
void clRom_PurgeAll(void);
}

struct Mode801B9740 : GameModeBase {
    ~Mode801B9740();
};

Mode801B9740::~Mode801B9740() {
    vt = lbl_8049A734;
    fn_80120A08(0x186E);
    fn_80120A08(0x186F);
    fn_80120A08(0x1870);
    fn_80120A08(0x1871);
    fn_80120A08(0x1872);
    fn_80120A08(0x1873);
    fn_80120A08(0x1874);
    fn_80120A08(0x1875);
    if (lbl_806D17F4) {
        if (fn_8019083C(1)) {
            fn_801909A4(1);
        }
        fn_801908F0();
        lbl_806D17F4 = 0;
    }
    fn_801B7CD0(-1);
    delete lbl_806D1820;
    delete lbl_806D17F8;
    delete lbl_806D17FC;
    delete lbl_806D1800;
    delete lbl_806D180C;
    lbl_806D1820 = 0;
    lbl_806CFD60 = -1;
    lbl_806D17F8 = 0;
    lbl_806D17FC = 0;
    lbl_806D1800 = 0;
    lbl_806D180C = 0;
    lbl_806D17F3 = 0;
    delete lbl_806D1840;
    delete lbl_806D1844;
    lbl_806D1840 = 0;
    lbl_806D1844 = 0;
    for (int i = 0; i < 3; i++) {
        delete lbl_80679280[i];
        lbl_80679280[i] = 0;
    }
    for (int j = 0; j < 4; j++) {
        delete lbl_8067928C[j];
        lbl_8067928C[j] = 0;
    }
    delete g_pInputState;
    g_pInputState = 0;
    fn_801DAE54();
    fn_80121210();
    clRom_PurgeAll();
}
