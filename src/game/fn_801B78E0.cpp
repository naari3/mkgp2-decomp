struct InputView {
    void *vt;
    unsigned char enabled;
    unsigned char flag5;
    unsigned char flag6;
    char pad_7;
    int fields[8];
};

class SceneChild {
public:
    virtual void v8();
    virtual void vC();
    virtual ~SceneChild();
};

struct RaceFlow {
    void *vt;
    char pad_4[0xC];
    SceneChild *child;
};

extern "C" {
extern InputView *g_pInputState;
extern void *lbl_8049A234[];
extern void *lbl_803FDF28[];
extern void *lbl_803FDF40[];
extern signed char lbl_806D1193;
void *Alloc(unsigned long size);
void MemoryManager_TimedFree(void *p);
void RaceFlow_ResetState_FullColdInit(void);
void RaceSlot_ResetAll(void);
void *StrPcb_GetInstance(void);
void StrPcb_ForceRun_Neutral(void *pcb);
void StrPcb_ResetCommands_Neutral(void *pcb, int arg);
void dtor_801BA14C(void *self, int flag);
void fn_80121210(void);
}

static inline InputView *input_state() {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

static inline void CreateInputState() {
    InputView *p = (InputView *)Alloc(0x28);
    if (p != 0) {
        p->vt = lbl_803FDF28;
        g_pInputState = p;
        p->vt = lbl_803FDF40;
        p->enabled = 0;
        p->flag5 = 1;
        p->flag6 = 1;
        p->fields[0] = 0;
        p->fields[1] = 0;
        p->fields[2] = 0;
        p->fields[3] = 0;
        p->fields[4] = 0;
        p->fields[5] = 0;
        p->fields[6] = 0;
        p->fields[7] = 0;
    }
}

extern "C" RaceFlow *fn_801B78E0(RaceFlow *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8049A234;
        if (self->child != 0) {
            delete self->child;
        }
        RaceFlow_ResetState_FullColdInit();
        RaceSlot_ResetAll();
        if (input_state() == 0) {
            CreateInputState();
        }
        StrPcb_ForceRun_Neutral(StrPcb_GetInstance());
        StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
        fn_80121210();
        lbl_806D1193 = 0;
        dtor_801BA14C(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
