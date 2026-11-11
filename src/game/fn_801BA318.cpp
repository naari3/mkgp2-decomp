/* clFlowEntry: Draw, Update, destructor and constructor, 0x801BA318..0x801BA9A0.
 * Deferred compilation emits the definitions below in reverse source order.
 * The compiler owns the vtable, base list, RTTI records and class-name pool;
 * per-TU symbol bridges retain the names used by the other flow units.
 */
#include "game/FlowScene.h"
class EntryPad {
public:
    virtual ~EntryPad();
    virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void *IsPressed(int);
};
struct EntryCard {
    char pad0[0x10]; int stage; char pad14[0x25]; unsigned char flag39; char pad3A[0x52];
    EntryCard(int, int, int);
    bool Done() { return stage == 6; }
};
#include "game/types/clFlowProcess.h"
#include "game/singleton.h"
struct SpriteObj {
    char pad0[0x30];
    SpriteObj(int, int, float, float);
    SpriteObj(int, int, float, float, float, float, float, float);
};
class clFlowEntry : public clFlowProcess {
public:
    virtual ~clFlowEntry();
    virtual int Update();
    virtual void Draw();
    clFlowEntry();
    unsigned char done, cardMode, cardDone, clean;
    int peers; float brightness; int next;
    void *sprite, *fade;
    EntryCard *card;
};
extern "C" {
extern int lbl_8049A858[];
extern const float lbl_806D9968, lbl_806D996C, lbl_806D9978, lbl_806D997C;
extern int g_gameMode, g_localPcbRole;
void RumbleUpdate(); void card_cleaning_state_machine(); int CountPeersWithRole(int);

float PcbSyncTable_GetMyValue(); void SetScreenBrightness(float);
void Sprite_SetAnimTime(void *, float); void Sprite_AdvanceAnim(void *, float);
void *GetInputManager(); EntryPad *InputMgr_GetPlayer(void *, int);
void fn_80161F28(EntryCard *, int); void fn_801618CC(EntryCard *, int, int);
void fn_80161888(EntryCard *); void SetRumbleMode(int, int, int);
void fn_80160588(EntryCard *, int, int); int fn_801BA1A4(clFlowEntry *);
void SetSyncTarget(int); unsigned char PCBComm_ConfirmHostLobby(); void SetTimerModeEnabled(int);
extern InputState *g_pInputState;
extern unsigned char lbl_80598A60[];
extern const float lbl_806D9960, lbl_806D9964, lbl_806D9970, lbl_806D9974, lbl_806D9980;
int CountPeersWithRole(int); void InitRumbleController(int);
unsigned char ServiceEnable_Get(); unsigned char ServiceValue_Get();
void SetLocalPcbRole(int); int SetupBgSprites(unsigned char);
void card_send_cleaning_cmd_init(); void fn_801699D8(int,int); void fn_80169C44();
void Sprite_Destroy(void *, int);
void fn_801A0004(void *); void fn_8016039C(void *);
}
extern "C" void Sprite_SetAnimParam(void *, int, int);
static inline InputState *input_state() { return SINGLETON_INSTANCE(g_pInputState); }

clFlowEntry::clFlowEntry() {
    SetSyncTarget(7);
    SetLocalPcbRole(1);
    done = 0;
    cardMode = 0;
    cardDone = 0;
    card = 0;
    brightness = PcbSyncTable_GetMyValue();
    peers = CountPeersWithRole(1);
    sprite = new SpriteObj(0x1E5, 1, lbl_806D9960, lbl_806D9960);
    fade = new SpriteObj(0x5B, 0, lbl_806D9970, lbl_806D9974, lbl_806D9964, lbl_806D9964, lbl_806D9960, lbl_806D9964);
    next = -1;
    clean = 1;
    Sprite_SetAnimParam(sprite, 0x1B18, (short)lbl_8049A858[peers]);
    if (!ServiceEnable_Get() || ServiceValue_Get()) {
        clean = 0;
    } else if (!lbl_80598A60[0x23] || !lbl_80598A60[0x24]) {
        clean = 0;
    }
    if (input_state()) {
        InputState *input = input_state();
        input->enabled = 1;
        input->held = 0;
        input->edge = 0;
    }
    SetupBgSprites(1);
    InitRumbleController(1);
    fn_801699D8(0, 1);
    fn_801699D8(1, 1);
    if (clean) {
        card_send_cleaning_cmd_init();
    } else {
        Sprite_SetAnimParam(sprite, 0x1B21, 0x1B20);
    }
}

clFlowEntry::~clFlowEntry() {
    fn_801699D8(0, 0);
    fn_801699D8(1, 0);
    fn_80169C44();
    if (input_state()) {
        InputState *input = input_state();
        input->enabled = 0; input->held = 0; input->edge = 0;
    }
    if (sprite) Sprite_SetAnimParam(sprite, (short)lbl_8049A858[peers], 0x1B18);
    fn_80161F28(card, 1);
    Sprite_Destroy(sprite, 1);
    Sprite_Destroy(fade, 1);
    SetScreenBrightness(lbl_806D9980);
}

int clFlowEntry::Update() {
    RumbleUpdate();
    if (this->clean) card_cleaning_state_machine();
    int peers = CountPeersWithRole(1);
    if (this->peers != peers) {
        if (this->sprite) Sprite_SetAnimParam(this->sprite, (short)lbl_8049A858[this->peers], (short)lbl_8049A858[peers]);
        this->peers = peers;
    }
    this->brightness = PcbSyncTable_GetMyValue();
    SetScreenBrightness(this->brightness);
    float brightness = this->brightness;
    if (brightness < lbl_806D996C && this->fade) Sprite_SetAnimTime(this->fade, lbl_806D996C - brightness);
    if (this->sprite) Sprite_AdvanceAnim(this->sprite, lbl_806D9968);
    if (this->next == -1) {
        EntryPad *pad = InputMgr_GetPlayer(GetInputManager(), 0);
        if (this->cardMode) {
            int dir = 0;
            int held = 0;
            if (this->cardDone) {
                int finished = (unsigned char)this->card->Done();
                if (finished) {
                    fn_80161F28(this->card, 1);
                    this->card = 0;
                    this->cardMode = 0;
                }
            } else if (this->brightness < lbl_806D9978) {
                fn_801618CC(this->card, 1, 0);
                fn_80161888(this->card);
                this->cardDone = 1;
            } else {
                InputState *input = GetInput();
                if (input) {
                    dir = input->dir;
                    held = (unsigned char)(input->held == 1);
                    if (held) SetRumbleMode(0, 1, 1);
                }
            }
            if (this->card) fn_80160588(this->card, dir, held);
        } else if (!this->done && this->brightness > lbl_806D997C) {
            if (pad->IsPressed(0x400)) {
                SetRumbleMode(1, 1, 1);
                this->cardMode = 1;
                this->card = new EntryCard(1, 0, 9);
                this->card->flag39 = 1;
                this->cardDone = 0;
            }
        }
        if (!this->done && this->next == -1) fn_801BA1A4(this);
    } else {
        if (this->card) {
            if (this->card->stage == 6) return this->next;
            else fn_80160588(this->card, 0, 0);
        } else return this->next;
    }
    if (this->done) {
        SetSyncTarget(8);
        if (PCBComm_ConfirmHostLobby() == 1) {
            if (g_localPcbRole) { g_gameMode = 2; SetTimerModeEnabled(1); }
            else { g_gameMode = 0; SetTimerModeEnabled(0); }
            this->next = 9;
        }
        return this->next;
    }
    return -1;
}
void clFlowEntry::Draw() {
    if (sprite) fn_801A0004(sprite);
    if (brightness < 6.0f && fade) fn_801A0004(fade);
    if (card) fn_8016039C(card);
}
