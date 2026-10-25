#ifndef GAME_HUDMANAGER_H
#define GAME_HUDMANAGER_H

/*
 * HUD manager (built by HUD_Init.c): a FlowSceneList at +0x00 and 23 HUD
 * part slots at +0x10.
 */

#include "game/FlowScene.h"

struct HudPart {
    virtual ~HudPart();
    virtual void Update();
    virtual void Draw();
    virtual void SetDelay(int n);
};

/* FlowTask as seen through the manager's list (Draw at vtable +0x14). */
struct HudTask {
    virtual void _key();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
    int id;
    int wait;
    int state;
    bool Ready() {
        if (wait > 0) {
            wait--;
            return 0;
        }
        if (state == 1) {
            state = 2;
        }
        return state <= 0;
    }
};

struct HudManager {
    VHolder<FlowSceneList> list;
    int phase;
    int field08;
    int mode;
    HudPart *parts[23];
    int field6C;
    float field70;
    float field74;
    float field78;
    int style;
    HudPart *CreatePart(int idx, unsigned char force);
    void DrawMasked(unsigned int mask);
    void DrawAll();
    void Delay(int i, int n) {
        if (parts[i]) {
            parts[i]->SetDelay(n);
        }
    }
    void HideAll();
    ~HudManager();
    void SetLapScale(float v);
    void SetSpeed(float v);
};

#endif
