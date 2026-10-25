/* Flow scene destructor: frees its sprites, buffers and owned helpers. */
struct SpriteObj {
    ~SpriteObj();
};

struct SpriteBox {
    SpriteObj *sprite;

    ~SpriteBox() {
        delete sprite;
    }
};

struct Owned801CE1EC {
    ~Owned801CE1EC();
};

struct InputView {
    unsigned char opaque[4];
    unsigned char enabled;
    unsigned char opaque5[0x13];
    int held;
    int edge;
};

struct FlowBase {
    void *vt;
    FlowBase();
    ~FlowBase();
};

extern "C" {
extern InputView *g_pInputState;
extern void *lbl_8049B1CC[];
void fn_80169C44(void);
void PcbSlot_ResetScratchAreas(void);
void CommBroadcast_ClearTable(void);
}

static inline InputView *input_state() {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

struct OwnedHolder801CE1EC {
    Owned801CE1EC *p;
    ~OwnedHolder801CE1EC() throw() {
        delete p;
    }
};

struct BoxHolder801CE1EC {
    SpriteBox *p;
    ~BoxHolder801CE1EC() throw() {
        delete p;
    }
};

struct Scene801CE1EC : FlowBase {
    char pad4[8];
    SpriteObj *sprite;
    char *buf;
    char *bufs[3];
    char pad20[0x14];
    OwnedHolder801CE1EC owned;
    BoxHolder801CE1EC box;

    ~Scene801CE1EC();
};

Scene801CE1EC::~Scene801CE1EC() {
    int i;

    vt = lbl_8049B1CC;
    fn_80169C44();
    PcbSlot_ResetScratchAreas();
    CommBroadcast_ClearTable();
    delete sprite;
    if (buf) {
        delete buf;
    }
    for (i = 0; i < 3; i++) {
        if (bufs[i]) {
            delete bufs[i];
        }
    }
    InputView *input = input_state();
    input->enabled = 0;
    input->held = 0;
    input->edge = 0;
}
