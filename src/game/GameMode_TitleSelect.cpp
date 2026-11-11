/* clTitle, clStageSelect and clSeqEnding modes.
 * Nondeferred generation preserves text order and emits class data in reverse. */
#include "game/singleton.h"

struct VObj {
    virtual ~VObj();
    virtual void Vf0C();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
};

typedef struct InputView {
    void **vt;
    unsigned char enabled;
    unsigned char flag5;
    unsigned char flag6;
    unsigned char pad7;
    int fields[8];
} InputView;

#include "game/types/clJobRunner.h"
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void *);

extern "C" {
extern void *Alloc(unsigned long size);
extern void DEMOPuts(int x, int y, int color, const char *text);
extern VObj *fn_8015CB5C(int arg);
extern void fn_801A1280(void);
extern void fn_8011FAB8(void);
extern char lbl_80328DC8[];
extern char lbl_80328DB8[];
extern void *lbl_803FDF28[];
extern void *lbl_803FDF40[];
extern InputView *g_pInputState;
extern int g_characterId;
}

static inline InputView *input_state(void)
{
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline void CreateInputState(void)
{
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

struct clSeqEnding : clJobRunner {
    virtual int Update();
    virtual void Draw();
    virtual ~clSeqEnding();
    int state;
    VObj *scene;
    clSeqEnding() {
        state = 0;
        scene = 0;
        if (input_state() == 0) CreateInputState();
        g_characterId = 0;
        scene = fn_8015CB5C(0);
    }
};
struct clStageSelect : clJobRunner {
    virtual int Update();
    virtual void Draw();
    virtual ~clStageSelect();
    int counter;
    clStageSelect() : counter(0) {}
};
struct clTitle : clJobRunner {
    virtual int Update();
    virtual void Draw();
    virtual ~clTitle();
    int counter;
    clTitle() : counter(0) {}
};

extern "C" clTitle *GameMode_Title_Ctor(void)
{
    return new clTitle;
}

clTitle::~clTitle() {}

int clTitle::Update()
{
    counter++;
    return counter > 180 ? -1 : -2;
}

void clTitle::Draw()
{
    DEMOPuts(10, 10, 0, lbl_80328DC8);
}

extern "C" clStageSelect *GameMode_StageSelect_Ctor(void)
{
    return new clStageSelect;
}

clStageSelect::~clStageSelect() {}

int clStageSelect::Update()
{
    return -1;
}

void clStageSelect::Draw()
{
    DEMOPuts(10, 10, 0, lbl_80328DB8);
}

extern "C" clSeqEnding *GameMode_CharacterSelect_Ctor(void)
{
    return new clSeqEnding;
}

clSeqEnding::~clSeqEnding() {
    delete (VObj *)g_pInputState;
    g_pInputState = 0;
    delete scene;
}

int clSeqEnding::Update()
{
    fn_801A1280();
    switch (state) {
    case 0:
        state++;
        break;
    case 1:
        scene->Update();
        if (scene->done == 1) {
            state++;
        }
        break;
    case 2:
        return -4;
    }
    return -2;
}

void clSeqEnding::Draw()
{
    scene->Draw();
    fn_8011FAB8();
}
