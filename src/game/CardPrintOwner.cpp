/* Card-print scene owner, reconstructed from the target lifetime paths.
 * Local child view follows the existing NameEntry composition; no live
 * Ghidra type service was available. Shared list/fader/input ABI is canonical. */
#include "game/FlowScene.h"

struct CardPrintBase {
    virtual void ExternalKey();
    ~CardPrintBase() {}
    unsigned char done;
    CardPrintBase() : done(false) {}
};
struct PrintPanel {
    char pad00[0x20];
    unsigned char visible, active;
    char pad22[0x68 - 0x22];
    PrintPanel();
};
extern "C" void fn_801D9F88(PrintPanel *, short);
struct PrintPanelHolder {
    PrintPanel *p;
    PrintPanelHolder(PrintPanel *q) : p(q) {}
    ~PrintPanelHolder() throw() { fn_801D9F88(p, 1); }
};
struct PrintSprite { ~PrintSprite(); };
template <class T> struct PrintOwn {
    T *p;
    ~PrintOwn() throw() { delete p; }
};
template <class T> struct PrintVecData {
    int cap, count;
    T *data;
    ~PrintVecData() { if (data) operator delete(data); }
};
template <class T> struct PrintVecBase : PrintVecData<T> { ~PrintVecBase() {} };
template <class T> struct PrintVec : PrintVecBase<T> {
    ~PrintVec() {}
    T *begin() { return this->data; }
    T *end() { return this->data + this->count; }
};
struct PrintKeyData { int cap, count; void *data; ~PrintKeyData(); };
struct PrintKeyMid : PrintKeyData { ~PrintKeyMid() {} };
struct PrintKeyVec : PrintKeyMid { ~PrintKeyVec() {} };
struct PrintKeyboard {
    unsigned char english;
    PrintKeyVec groups;
    char tail[0x40 - 0x10];
};
struct PrintName {
    PrintKeyboard keyboard;
    PrintOwn<PrintSprite> cursor;
    char *bufs[4][15];
    int state;
    char pad138[0x10];
    PrintVec<VObject *> objs;
    PrintName(bool english);
    ~PrintName();
};
struct PrintMessage { ~PrintMessage(); };
extern "C" {
extern PrintMessage *lbl_806D1A88;
extern int lbl_806D1AB0;
void fn_801699D8(int, int);
}
static inline void SetInput(unsigned char enabled) {
    InputState *in = GetInput();
    in->enabled = enabled;
    in->held = 0;
    in->edge = 0;
}
inline PrintName::~PrintName() {
    for (VObject **it = objs.begin(); it != objs.end(); it++) delete *it;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 15; j++) operator delete(bufs[i][j]);
    }
    SetInput(0);
    if (lbl_806D1A88) {
        delete lbl_806D1A88;
        lbl_806D1A88 = 0;
    }
    fn_801699D8(0, 0);
    fn_801699D8(1, 0);
}
struct CardPrintOwner : CardPrintBase {
    VHolder<SceneListImpl> list;
    VHolder<FlowFaderI> fader;
    int state, timer;
    PrintName *name;
    PrintPanelHolder panel;
    int tail;
    CardPrintOwner();
    ~CardPrintOwner();
    virtual void ExternalKey();
};
extern "C" void fn_8024B0A0(VObject *object) { delete object; }
extern "C" CardPrintOwner *fn_8024B0D8() { return new CardPrintOwner; }
CardPrintOwner::~CardPrintOwner() {
    if (GetInput()) SetInput(0);
    delete name;
    fn_801F4D3C(list.p);
}
CardPrintOwner::CardPrintOwner() : list(new SceneListImpl), fader(new FlowFaderI),
    state(0), timer(0), name(0), panel(new PrintPanel), tail(0) {
    if (GetInput()) SetInput(1);
    fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
    name = new PrintName(!isJapanese());
    panel.p->visible = 1;
    panel.p->active = 0;
}
