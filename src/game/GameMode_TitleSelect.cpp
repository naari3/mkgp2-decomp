/* Title / stage-select / character-select game modes (0x800AC94C..0x800ACD60).
 * NonMatching: these are C++ classes deriving GMRoot with RTTI on; the
 * target extab has new/ctor cleanup actions and the vtables + RTTI
 * (.data 0x80419DF0.., .sdata 0x806CF290..) belong to this TU. */

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

typedef struct GameModeTitle {
    void *vtable;
    int counter;
} GameModeTitle;

typedef struct GameModeSelect {
    void *vtable;
    int state;
    VObj *scene;
} GameModeSelect;

extern "C" {
extern void MemoryManager_TimedFree(void *);
extern void dtor_8002CDF4(void *, int);
extern void *Alloc(unsigned long size);
extern void GameMode_BaseInit(void *self);
extern void fn_8026031C(int x, int y, int color, const char *text);
extern VObj *fn_8015CB5C(int arg);
extern void fn_801A1280(void);
extern void fn_8011FAB8(void);
extern char lbl_80419E3C[];
extern char lbl_80419E1C[];
extern char lbl_80419DFC[];
extern char lbl_80328DC8[];
extern char lbl_80328DB8[];
extern void *lbl_803FDF28[];
extern void *lbl_803FDF40[];
extern InputView *g_pInputState;
extern int g_characterId;
}

static inline InputView *input_state(void)
{
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
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

#pragma exceptions on
extern "C" GameModeTitle *GameMode_Title_Dtor(GameModeTitle *self, short flag)
{
    if (self != 0) {
        self->vtable = lbl_80419E3C;
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset

extern "C" int fn_800AC9AC(GameModeTitle *self)
{
    self->counter++;
    return self->counter < 180 ? -1 : -2;
}

#pragma exceptions on
extern "C" void GameMode_Title_DrawDebugLabel(void)
{
    fn_8026031C(10, 10, 0, lbl_80328DC8);
}

extern "C" GameModeTitle *GameMode_StageSelect_Ctor(void)
{
    GameModeTitle *self = (GameModeTitle *)Alloc(8);
    if (self != 0) {
        GameMode_BaseInit(self);
        self->vtable = lbl_80419E1C;
        self->counter = 0;
    }
    return self;
}

extern "C" GameModeTitle *GameMode_StageSelect_Dtor(GameModeTitle *self, short flag)
{
    if (self != 0) {
        self->vtable = lbl_80419E1C;
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset

extern "C" int fn_800ACAC0(void)
{
    return -1;
}

#pragma exceptions on
extern "C" void GameMode_StageSelect_DrawDebugLabel(void)
{
    fn_8026031C(10, 10, 0, lbl_80328DB8);
}

extern "C" GameModeSelect *GameMode_CharacterSelect_Ctor(void)
{
    GameModeSelect *self = (GameModeSelect *)Alloc(0xC);
    if (self != 0) {
        GameMode_BaseInit(self);
        self->vtable = lbl_80419DFC;
        self->state = 0;
        self->scene = 0;
        if (input_state() == 0) {
            CreateInputState();
        }
        g_characterId = 0;
        self->scene = fn_8015CB5C(0);
    }
    return self;
}

extern "C" GameModeSelect *GameMode_CharacterSelect_Dtor(GameModeSelect *self, short flag)
{
    if (self != 0) {
        self->vtable = lbl_80419DFC;
        delete (VObj *)g_pInputState;
        g_pInputState = 0;
        delete self->scene;
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" int GameMode_CharacterSelect_TickStateMachine(GameModeSelect *self)
{
    fn_801A1280();
    switch (self->state) {
    case 0:
        self->state++;
        break;
    case 1:
        self->scene->Update();
        if (self->scene->done == 1) {
            self->state++;
        }
        break;
    case 2:
        return -4;
    }
    return -2;
}

extern "C" void GameMode_CharacterSelect_Draw(GameModeSelect *self)
{
    self->scene->Draw();
    fn_8011FAB8();
}
#pragma exceptions reset
