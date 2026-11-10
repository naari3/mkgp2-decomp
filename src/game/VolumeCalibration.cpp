/* clCab (0x80039E10..0x8003A154): operator-menu "volume calibration" job.
 * Tracks the raw JVS analog channels (steering / accel / brake), records
 * the min/max excursion of each, and on teardown publishes the calibration
 * to the JVS input layer and the backup shadow block.
 *
 * Built with RTTI: the clJobRunner / clCab type_info objects, the vtable
 * and the TU's string pool (pedal names, "clJobRunner", overlay formats)
 * are all owned here. */

struct JvsOperatorInput {
    unsigned char pad_0x00[0x8];
    unsigned short steer; /* 0x08 */
    unsigned short accel; /* 0x0A */
    unsigned short brake; /* 0x0C */
};

/* backup shadow block @ lbl_80598A60, calibration slice */
struct BackupCalibView {
    unsigned char pad_0x00[0x34];
    int steer; /* 0x34 */
    int pos;   /* 0x38 */
    int brake; /* 0x3C */
    int accel; /* 0x40 */
};

#include "game/types/InputPlayer.h"

extern "C" {
void OverlayText(int layer, int flag, int row, const char *fmt, ...);
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void *StrPcb_GetInstance(void);
int StrPcb_GetReceivedPosData(void *pcb);
void StrPcb_SetStatusBits(void *pcb, int bits, int arg);
void StrPcb_SetPositionTarget(void *pcb, short target);
void JvsInput_SetSteeringCalibration(int value);
void JvsInput_SetAccelCalibration(int value);
void JvsInput_SetBrakeCalibration(int value);
void Backup_PublishShadowCopy_Inline(void);

extern BackupCalibView lbl_80598A60;
extern JvsOperatorInput g_jvsOperatorBits;
}

static const char *const s_pedalNames[2] = { "RIGHT PEDAL", "LEFT  PEDAL" };
static const char *const s_jobRunnerName = "clJobRunner";

#include "game/types/clJobRunner.h"

struct clCab : clJobRunner {
    int steer;     /* 0x04 */
    int posData;   /* 0x08 */
    int field_0c;  /* 0x0C */
    int steerMin;  /* 0x10 */
    int steerMax;  /* 0x14 */
    int accelMin;  /* 0x18 */
    int accelMax;  /* 0x1C */
    int brakeMin;  /* 0x20 */
    int brakeMax;  /* 0x24 */

    clCab() {
        int accel;
        int brake;

        steer = 0x7A40;
        posData = 0x1FF;
        steerMin = 0x7A3F;
        steerMax = 0x7A41;
        field_0c = 1;
        brake = g_jvsOperatorBits.brake;
        accel = g_jvsOperatorBits.accel;
        accelMin = accel;
        accelMax = accel;
        brakeMin = brake;
        brakeMax = brake;
    }
    virtual int Update();
    virtual void Draw();
    virtual ~clCab();
};

void clCab::Draw()
{
    clCab *cur;
    const char *const *name;
    int row;
    int i;

    OverlayText(2, 1, 0, "Volume caribration");
    OverlayText(2, 1, 10, "===== Now Setting Parameter");
    OverlayText(2, 1, 11, "HANDLE NOW    %d", steer / 64);
    cur = this;
    i = 0;
    name = s_pedalNames;
    row = 15;
    for (; i < 2; i++) {

        OverlayText(2, 1, row + 1, "%s NOW %08x", *name, cur->accelMax);
        cur = (clCab *)((char *)cur + 8);
        name++;
        row += 3;

    }
}

#ifdef NON_MATCHING
/* NON_MATCHING: equivalent C++, instruction-identical except a register
 * permutation in the jvs-load head (see below). */
int clCab::Update()
{
    InputPlayer *pad;
    int accel = g_jvsOperatorBits.accel;
    int brake = g_jvsOperatorBits.brake;
    int s = g_jvsOperatorBits.steer;

    steer = s;
    if (steerMin > s) {
        steerMin = s;
    } else if (steerMax < s) {
        steerMax = s;
    }
    if (accelMin > accel) {
        accelMin = accel;
    } else if (accelMax < accel) {
        accelMax = accel;
    }
    if (brakeMin > brake) {
        brakeMin = brake;
    } else if (brakeMax < brake) {
        brakeMax = brake;
    }
    pad = InputMgr_GetPlayer(GetInputManager(), 0);
    if (pad->Pressed(0x401) == 1) {
        return -4;
    }
    posData = StrPcb_GetReceivedPosData(StrPcb_GetInstance());
    if (pad->Pressed(0x40) == 1) {
        StrPcb_SetStatusBits(StrPcb_GetInstance(), 0xC, 0);
    }
    return -2;
}
#else
/* Update stays asm: the C body above is instruction-identical except a
 * register permutation in the jvs-load head (target keeps `this` in r3 for
 * the first store/load and loads the channels into base=r5/accel=r4/
 * brake=r0; CW moves `this` to r30 at entry, so base=r3/brake=r5/temp=r0).
 */
asm int clCab::Update()
{
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, g_jvsOperatorBits@ha
    stw r0, 0x14(r1)
    addi r5, r4, g_jvsOperatorBits@l
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lhz r4, 0xa(r5)
    lhz r0, 0xc(r5)
    lhz r5, 0x8(r5)
    stw r5, 0x4(r3)
    lwz r3, 0x10(r3)
    cmpw r3, r5
    ble VolumeCalibration_Tick_L_80039F20
    stw r5, 0x10(r30)
    b VolumeCalibration_Tick_L_80039F30
    VolumeCalibration_Tick_L_80039F20:
    lwz r3, 0x14(r30)
    cmpw r3, r5
    bge VolumeCalibration_Tick_L_80039F30
    stw r5, 0x14(r30)
    VolumeCalibration_Tick_L_80039F30:
    lwz r3, 0x18(r30)
    cmpw r3, r4
    ble VolumeCalibration_Tick_L_80039F44
    stw r4, 0x18(r30)
    b VolumeCalibration_Tick_L_80039F54
    VolumeCalibration_Tick_L_80039F44:
    lwz r3, 0x1c(r30)
    cmpw r3, r4
    bge VolumeCalibration_Tick_L_80039F54
    stw r4, 0x1c(r30)
    VolumeCalibration_Tick_L_80039F54:
    lwz r3, 0x20(r30)
    cmpw r3, r0
    ble VolumeCalibration_Tick_L_80039F68
    stw r0, 0x20(r30)
    b VolumeCalibration_Tick_L_80039F78
    VolumeCalibration_Tick_L_80039F68:
    lwz r3, 0x24(r30)
    cmpw r3, r0
    bge VolumeCalibration_Tick_L_80039F78
    stw r0, 0x24(r30)
    VolumeCalibration_Tick_L_80039F78:
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r31, r3
    li r4, 0x401
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne VolumeCalibration_Tick_L_80039FB0
    li r3, -0x4
    b VolumeCalibration_Tick_L_80039FF4
    VolumeCalibration_Tick_L_80039FB0:
    bl StrPcb_GetInstance
    bl StrPcb_GetReceivedPosData
    stw r3, 0x8(r30)
    mr r3, r31
    li r4, 0x40
    lwz r12, 0x0(r31)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne VolumeCalibration_Tick_L_80039FF0
    bl StrPcb_GetInstance
    li r4, 0xc
    li r5, 0x0
    bl StrPcb_SetStatusBits
    VolumeCalibration_Tick_L_80039FF0:
    li r3, -0x2
    VolumeCalibration_Tick_L_80039FF4:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
#endif

clCab::~clCab()
{
    JvsInput_SetSteeringCalibration(steer);
    JvsInput_SetAccelCalibration(accelMin);
    JvsInput_SetBrakeCalibration(brakeMin);
    StrPcb_SetPositionTarget(StrPcb_GetInstance(), (short)posData);
    lbl_80598A60.steer = steer;
    lbl_80598A60.pos = posData;
    lbl_80598A60.accel = accelMin;
    lbl_80598A60.brake = brakeMin;
    Backup_PublishShadowCopy_Inline();
}

extern "C" clCab *VolumeCalibration_Ctor(void)
{
    return new clCab;
}

/* Update is asm, so CW emits no extab for it; its entry is emitted by hand
 * (renamed into extab/extabindex by tools/postprocess_extab_user.py and put
 * in place by tools/extab_order.json). */
extern "C" void Update__5clCabFv(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned int extab_clCab_Update[2] = {
    0x10080000, 0x00000000
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    const void *extab;
} extabindex_clCab_Update = {
    (void *)&Update__5clCabFv, 0x00000130, extab_clCab_Update
};
