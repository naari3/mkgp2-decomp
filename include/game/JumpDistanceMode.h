#ifndef GAME_JUMPDISTANCEMODE_H
#define GAME_JUMPDISTANCEMODE_H

/*
 * Jump-distance minigame mode (ctor JumpDistanceMode_Init, vtable
 * lbl_804ECC08). Field names follow src/game/JumpDistanceMode_Init.c.
 *
 *   GameModeBase (ctor GameMode_BaseInit, dtor dtor_8002CDF4)
 *     ModeBase (vtable lbl_8048E144, dtor dtor_80122FD8)
 *       JumpDistanceMode
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct CarObject;
struct KartMovement;
struct LakituStart;
struct CourseEnvironment;
struct ChallengeGoalCamera;
struct ItemSlot;
struct HsdObj;
struct HUD;
struct TimerDisplay;
struct GoalLine;
struct ScenePos;

extern "C" {
unsigned char fn_8016C360(int se);
void fn_8016C394(int se);
}

/* 2D sprite model (fn_8013D4B0 alpha, fn_8013D570 rotation, fn_8013D660 position). */
struct LandingMarker {
    virtual ~LandingMarker();
    virtual void Draw();
};

extern "C" {
void fn_8013D660(LandingMarker *m, float x, float y);
void fn_8013D570(LandingMarker *m, float deg);
void fn_8013D4B0(LandingMarker *m, float alpha);
}

/* Sparkle that rises from a cell for 10 frames (age < 0 = unused). */
struct GridSlot {
    int age;
    float x;
    float y;
    int pad;
};

struct GridCell {
    float x;
    float y;
    float rot;
    float alpha;
    int frame;
    int visible;
    GridSlot slots[5];
};

/* Result grid: 15 cells pop in one by one, then swap to the settled cells2. */
struct LandingGrid {
    LandingMarker *markers[2];
    int next;
    int pending;
    int delay;
    float spin;
    int sparkle;
    GridCell cells[15];
    GridCell cells2[15];
    ~LandingGrid() {
        delete markers[0];
        delete markers[1];
    }
};

/* Kart launch helper: plays the kart forward in steps of `div` frames. */
struct JumpGauge {
    unsigned char start;
    unsigned char running;
    unsigned char landed;
    int count;
    int div;
    float step;
    float spin;
    float lift;
    float delta[16];
    float mtx[16];
    ~JumpGauge() {
        if (fn_8016C360(0x42)) {
            fn_8016C394(0x42);
        }
    }
};

struct Scene3D {
    virtual ~Scene3D();
    virtual unsigned char Ready();
    virtual void Render();
};

struct VObj {
    virtual ~VObj();
};

struct GameModeBase {
    virtual int Update();
    virtual void Draw();
    virtual ~GameModeBase();
};

struct ModeBase : GameModeBase {
    float x4;
    virtual ~ModeBase();
};

struct JumpDistanceMode : ModeBase {
    CarObject *car;
    LakituStart *lakitu;
    CourseEnvironment *env;
    Scene3D *scene;
    ChallengeGoalCamera *goalCam;
    ItemSlot *itemSlot;
    VObj *camera;
    HsdObj *lights;
    HUD *hud;
    TimerDisplay *timer;
    GoalLine *lines[3];
    JumpGauge *gauge;
    ScenePos *scenePos;
    unsigned char ready;
    unsigned char x45;
    int x48, x4C, x50;
    float x54, x58, x5C, x60, x64, x68;
    unsigned char x6C, x6D;
    KartMovement *movement;
    float x74;
    unsigned char x78;
    LandingGrid *grid;
    int x80, x84;
    unsigned char x88;
    virtual void Draw();
    virtual ~JumpDistanceMode();
};

#endif
