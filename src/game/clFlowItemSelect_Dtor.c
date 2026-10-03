/* Observed destructor-only layouts; runtime class identities remain unverified. */
#pragma cplusplus on
void operator delete(void*) throw();
struct FlowInputView {
    unsigned char opaque[4], enabled, opaque5[0x13];
    int held, edge;
};
extern "C" {
extern FlowInputView* g_pInputState;
extern unsigned char lbl_806D1264[4];
extern const float lbl_806D9DF8;
void fn_80169C44();
unsigned char SetScreenBrightness(float);
void* ItemDisplay_GetOrCreate();
void ItemDisplay_Stop(void*);
void ItemDisplay_Destroy();
void SpriteHandle_Destroy(int);
void fn_80121210();
void* fn_8023CFE0(void*, short);
}
struct FlowAnimDtor { ~FlowAnimDtor(); };
struct FlowFreeDtor { ~FlowFreeDtor() {} };
struct FlowBaseDtor {
    virtual void identity();
    ~FlowBaseDtor();
};
struct FlowMemberDtor {
    void* payload;
    ~FlowMemberDtor() throw() {
        fn_8023CFE0(payload, 1);
    }
};
static inline FlowInputView* input_state()
{
    if (g_pInputState == 0) return 0;
    return g_pInputState;
}
struct FlowOwnerDtor : FlowBaseDtor {
    int restore[3];
    unsigned char opaque10[0x70];
    FlowAnimDtor* animations[5];
    int handles[1];
    FlowFreeDtor* grid[3][4];
    unsigned char opaqueC8[0x14];
    FlowFreeDtor* extra[3];
    FlowMemberDtor member;
    virtual void identity();
    ~FlowOwnerDtor();
};
FlowOwnerDtor::~FlowOwnerDtor()
{
    fn_80169C44();
    SetScreenBrightness(lbl_806D9DF8);
    ItemDisplay_Stop(ItemDisplay_GetOrCreate());
    ItemDisplay_Destroy();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j]) {
                delete grid[i][j];
                grid[i][j] = 0;
            }
        }
    }
    if (input_state()) {
        FlowInputView* input = input_state();
        input->enabled = 0;
        input->held = 0;
        input->edge = 0;
    }
    lbl_806D1264[0] = restore[0];
    lbl_806D1264[1] = restore[1];
    lbl_806D1264[2] = restore[2];
    for (int i = 0; i < 5; ++i) {
        if (animations[i]) {
            delete animations[i];
            animations[i] = 0;
        }
    }
    for (int i = 0; i < 1; ++i) SpriteHandle_Destroy(handles[i]);
    for (int i = 0; i < 3; ++i) {
        if (extra[i]) {
            delete extra[i];
            extra[i] = 0;
        }
    }
    fn_80121210();
}
#pragma cplusplus off

