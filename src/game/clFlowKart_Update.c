/* Observed FlowKart update layout only; Sprite lifetime supplies automatic EH. */
class FlowSprite {
    unsigned char observed[48];
public:
    FlowSprite(int id, int loop, float x, float y, float sx, float sy, float yaw, float step);
};
struct FlowInput {
    unsigned char pad[0x14];
    int delta;
};
struct FlowUpdateView {
    unsigned int unknown;
    int selection;
    int result;
    int state;
    unsigned char pending;
    unsigned char pad11[3];
    int frame;
    float brightness;
    unsigned char pad1C[8];
    void* drivers[2];
    unsigned char pad2C[0x3C];
    FlowSprite* sprites[6];
};
extern "C" {
extern FlowInput* g_pInputState;
extern int g_characterId;
extern signed char lbl_806D184C, lbl_806D184D;
extern const float lbl_806DA13C, lbl_806DA148, lbl_806DA158, lbl_806DA15C;
extern const float lbl_806DA160, lbl_806DA164, lbl_806DA168, lbl_806DA16C, lbl_806DA170;
void RumbleUpdate();
void fn_801699D8(unsigned int, unsigned char);
int SetScreenBrightness(float);
void fn_801B7CAC();
int fn_801B87D8();
int fn_801B8398(int);
int clFlowKart_HandleConfirm(FlowUpdateView*);
void clFlowKart_UpdateDisplay(FlowUpdateView*, int);
void KartMovement_ResetOnGoal(void*);
void* KartDriver_Dtor(void*, short);
FlowSprite* Sprite_Destroy(FlowSprite*, short);
int Sprite_AdvanceAnim(FlowSprite*, float);
int RenderObj_ItemStateMachine_Timed(void*, int, float, float);
}
static inline FlowInput* CurrentFlowInput()
{
    return g_pInputState == 0 ? (FlowInput*)0 : g_pInputState;
}
/* Evaluate the nullable input getter before reading the current selection. */
static inline void ApplyFlowInput(FlowUpdateView* self, FlowInput* input)
{
    self->selection += input->delta;
}
extern "C" int clFlowKart_Update(FlowUpdateView* self)
{
    RumbleUpdate();
    if (self->pending) {
        self->state += 1;
        self->pending = 0;
    }
    self->frame += 1;
    switch (self->state) {
    case 0:
        if (self->frame == 1) {
            self->sprites[0] = new FlowSprite(0x16A, 1, lbl_806DA148, lbl_806DA158,
                lbl_806DA15C, lbl_806DA15C, lbl_806DA13C, lbl_806DA15C);
            self->sprites[1] = new FlowSprite(0x9C, 1, lbl_806DA160, lbl_806DA164,
                lbl_806DA15C, lbl_806DA15C, lbl_806DA168, lbl_806DA15C);
            self->sprites[2] = new FlowSprite(0x9C, 1, lbl_806DA16C, lbl_806DA164,
                lbl_806DA15C, lbl_806DA15C, lbl_806DA13C, lbl_806DA15C);
            clFlowKart_UpdateDisplay(self, g_characterId);
            SetScreenBrightness(self->brightness);
        }
        if (self->frame > 30) {
            fn_801699D8(0, 1);
            lbl_806D184C = 1;
            lbl_806D184D = 0;
            self->pending = 1;
        }
        break;
    case 1: {
        int previous = self->selection;
        if (CurrentFlowInput()) {
            ApplyFlowInput(self, CurrentFlowInput());
            if (self->selection > 1)
                self->selection = 1;
            if (self->selection < 0)
                self->selection = 0;
            if (previous != self->selection)
                fn_801B7CAC();
            clFlowKart_UpdateDisplay(self, g_characterId);
        }
        if (clFlowKart_HandleConfirm(self) != -1) {
            self->frame = 0;
            self->pending = 1;
            KartMovement_ResetOnGoal(self->drivers[self->selection]);
            fn_801B87D8();
            lbl_806D184C = -1;
            Sprite_Destroy(self->sprites[1], 1);
            Sprite_Destroy(self->sprites[2], 1);
            self->sprites[1] = 0;
            self->sprites[2] = 0;
        }
        break;
    }
    case 2:
        if (self->frame == 50) {
            fn_801B87D8();
            fn_801B8398(0);
            KartDriver_Dtor(self->drivers[0], 1);
            KartDriver_Dtor(self->drivers[1], 1);
            Sprite_Destroy(self->sprites[0], 1);
            Sprite_Destroy(self->sprites[1], 1);
            Sprite_Destroy(self->sprites[2], 1);
            Sprite_Destroy(self->sprites[3], 1);
            Sprite_Destroy(self->sprites[4], 1);
            Sprite_Destroy(self->sprites[5], 1);
            self->drivers[0] = 0;
            self->drivers[1] = 0;
            self->sprites[0] = 0;
            self->sprites[1] = 0;
            self->sprites[2] = 0;
            self->frame = 0;
            self->sprites[3] = 0;
            self->sprites[4] = 0;
            self->sprites[5] = 0;
            self->pending = 1;
            fn_801699D8(0, 0);
        }
        break;
    case 3:
        if (self->frame == 52)
            self->pending = 1;
        break;
    case 4:
        return self->result;
    }
    if (self->sprites[0])
        Sprite_AdvanceAnim(self->sprites[0], lbl_806DA170);
    if (self->sprites[1])
        Sprite_AdvanceAnim(self->sprites[1], lbl_806DA170);
    if (self->sprites[2])
        Sprite_AdvanceAnim(self->sprites[2], lbl_806DA170);
    if (self->drivers[0])
        RenderObj_ItemStateMachine_Timed(self->drivers[0], 0, lbl_806DA13C, lbl_806DA13C);
    if (self->drivers[1])
        RenderObj_ItemStateMachine_Timed(self->drivers[1], 0, lbl_806DA13C, lbl_806DA13C);
    if (self->sprites[3])
        Sprite_AdvanceAnim(self->sprites[3], lbl_806DA170);
    if (self->sprites[4])
        Sprite_AdvanceAnim(self->sprites[4], lbl_806DA170);
    if (self->sprites[5])
        Sprite_AdvanceAnim(self->sprites[5], lbl_806DA170);
    return -1;
}

