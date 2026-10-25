/*
 * 0x80165E90..0x801660EC: title-name debug page input handler, an empty
 * virtual stub, and a virtual-delete thunk.
 */

struct VObj {
    virtual ~VObj();
};

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
    virtual unsigned char Held(int mask);
};

struct TitleDebugPage {
    void *vtable;
    char pad04[8];
    int done;
    unsigned char quit;
    char pad11[3];
    void *text;
    int titleId;
    int variant;
    int repeat;
};

extern "C" {
extern void *lbl_806D10A0;
extern void *GetInputManager(void);
extern InputPlayer *InputMgr_GetPlayer(void *, int);
extern char *get_title_name(void *, int, unsigned char, int, int);
extern void fn_80168A4C(void *, char *, float, float, ...);

#pragma exceptions on

void fn_80165E90(TitleDebugPage *self) {
    void *db;

    if (self->quit == 1) {
        self->done = 1;
        return;
    }
    if (InputMgr_GetPlayer(GetInputManager(), 0)->StickRight() > 0.7f) {
        if (self->repeat < 0) {
            self->repeat = 0;
        } else {
            if (++self->repeat > 20) {
                self->repeat = 18;
            }
        }
    } else if (InputMgr_GetPlayer(GetInputManager(), 0)->StickLeft() > 0.7f) {
        if (self->repeat > 0) {
            self->repeat = 0;
        } else {
            if (--self->repeat < -20) {
                self->repeat = -18;
            }
        }
    } else {
        self->repeat = 0;
    }
    if (self->repeat == 1 || self->repeat == 20) {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Held(0x2000)) {
            self->titleId += 10;
        } else {
            self->titleId += 1;
        }
    }
    if (self->repeat == -1 || self->repeat == -20) {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Held(0x2000)) {
            self->titleId -= 10;
        } else {
            self->titleId -= 1;
        }
    }
    if (self->titleId < 0) {
        self->titleId = 255;
    }
    if (self->titleId > 255) {
        self->titleId = 0;
    }
    if ((db = lbl_806D10A0) == 0) {
        db = 0;
    }
    if (db) {
        fn_80168A4C(self->text, get_title_name(db, self->titleId, self->variant, 0, 0),
                    20.0f, 20.0f);
    }
}

void fn_801660B0(void) {
}

void fn_801660B4(VObj *p) {
    delete p;
}

#pragma exceptions reset
}
