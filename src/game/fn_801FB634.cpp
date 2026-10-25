/*
 * 0x801FB634..0x801FB6C0: factory for a small flow scene (vtable
 * lbl_804EBECC) whose timer starts one past the first table entry.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

extern "C" const int lbl_803BFF40[];

struct FlowScene {
    virtual void _key();
    char pad04[0x14];
    int state;
    int subState;
    int timer;
    int cursor;
    FlowScene(int arg);
    ~FlowScene();
};

struct WaitFlowScene : FlowScene {
    int kind;
    int field2C;
    unsigned char field30;
    char pad31[3];
    int field34;
    WaitFlowScene(int arg) : FlowScene(arg), kind(2), field2C(0), field30(0), field34(0) {
        state = 0;
        subState = 0;
        timer = lbl_803BFF40[0] + 1;
    }
    virtual void _key2();
};

extern "C" WaitFlowScene *fn_801FB634(int arg) {
    return new WaitFlowScene(arg);
}
