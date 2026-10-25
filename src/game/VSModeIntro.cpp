/* clGameRuleSelector (0x800A5578..0x800A58A0): the debug stage/type/player
 * selector job that runs before a VS race. Destroying it applies the chosen
 * course and seats the chosen player. Built with RTTI, so the class names
 * of the selector and its clJobRunner base lead this TU's .rodata; with
 * -inline deferred the functions are written in reverse .text order. */

extern "C" {
void SetCourseParams(int course, int type, int param3, int flag);
void RaceSlot_InitSlot(int a, int b, int c, int d, int e);
int WrapInRange(int v, int lo, int hi);
void OverlayText(int a, int b, int line, const char *fmt, ...);
}

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
};

extern "C" {
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
}

struct clJobRunner {
    clJobRunner();
    virtual int Update();
    virtual void Draw();
    virtual ~clJobRunner();
};

struct clGameRuleSelector : clJobRunner {
    int cursor;
    int course;
    int type;
    int param3;
    int player;

    clGameRuleSelector() {
        cursor = 0;
        course = 0;
        type = 0;
        param3 = 0;
        player = 0;
    }
    virtual int Update();
    virtual void Draw();
    virtual ~clGameRuleSelector();
};

extern "C" clGameRuleSelector *VSModeIntro_Ctor(void)
{
    return new clGameRuleSelector;
}

int clGameRuleSelector::Update()
{
    InputPlayer *pad = InputMgr_GetPlayer(GetInputManager(), 0);
    unsigned char pressed = pad->Pressed(1);

    switch (cursor) {
    case 0:
        if (pressed == 1) {
            course++;
            course = WrapInRange(course, 0, 0x10);
        }
        break;
    case 1:
        if (pressed == 1) {
            type++;
            type = WrapInRange(type, 0, 1);
        }
        break;
    case 2:
        if (pressed == 1) {
            player++;
            player = WrapInRange(player, 0, 0xE);
        }
        break;
    }

    if (pad->Pressed(0x40) == 1) {
        cursor--;
    } else if (pad->Pressed(0x80) == 1) {
        cursor++;
    }
    cursor = WrapInRange(cursor, 0, 2);

    if (pad->Pressed(0x400) == 1) {
        return -1;
    }
    OverlayText(2, 2, 4, "Select stage %d max %d", course, 0x11);
    OverlayText(2, 2, 5, "Select type  0 is short 1 is long %d", type);
    OverlayText(2, 2, 6, "Select player %d", player);
    OverlayText(2, 0, cursor + 4, "=>");
    return -2;
}

void clGameRuleSelector::Draw()
{
}

clGameRuleSelector::~clGameRuleSelector()
{
    SetCourseParams(course, type, param3, 0);
    RaceSlot_InitSlot(7, 0, player, 1, 0);
}
