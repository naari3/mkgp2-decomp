/* Native manager lifetime and camera update. Layout follows target accesses. */
struct Vec {
    float x,y,z;
    Vec() {}
    Vec& operator=(const Vec& other) {
        *(int*)&x=*(const int*)&other.x;
        *(int*)&y=*(const int*)&other.y;
        *(int*)&z=*(const int*)&other.z;
        return *this;
    }
    Vec(const Vec& other) { *(int*)&x=*(const int*)&other.x; *(int*)&y=*(const int*)&other.y; *(int*)&z=*(const int*)&other.z; }
};
struct EulerAngles { float x,y,z; };
#include "game/types/Matrix.h"
struct Camera { Matrix view,inverse; Vec position,target; };
struct Slot {
    signed char active; char pad1[3]; void (*tick)(Slot*);
    char pad8[0x84]; Vec position; char pad98[0x18]; float scale;
    char padB4[4]; Vec renderPosition; float renderScale; char padC8[0x104];
};
#include "game/types/Resource.h"
extern "C" {
unsigned int OSGetTick();
void Profiler_RecordFrame(int,float);
void VfxSlot_Release(void*);
void fn_8022B1C8();
void Vec3_Subtract_DestFirst(Vec*,const Vec*,const Vec*);
void Vec3_ToYawPitch(const Vec*,float*,float*);
#ifdef __MWERKS__
void Mtx44_FromEulerXYZTrans(Matrix*,Vec,EulerAngles);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_FromEulerXYZTrans(Matrix*,Vec*,EulerAngles*);
static inline void Mtx44_FromEulerXYZTrans_ByValue(Matrix*m,Vec v,EulerAngles e) { Mtx44_FromEulerXYZTrans(m,&v,&e); }
#define Mtx44_FromEulerXYZTrans Mtx44_FromEulerXYZTrans_ByValue
#endif
void Mtx44_Inverse_GaussJordan(Matrix*,const Matrix*);
void Vec3_Copy(Vec*,const Vec*);
extern Slot g_drawEffectSlots[512];
extern Resource *g_normal3DWrapMgr;
extern Camera lbl_805DF3D0;
extern const float lbl_806D4FDC,lbl_806D4FE8,lbl_806D4FEC,lbl_806D4FF0;
}
class ScopedTimer {
public:
    inline ScopedTimer(int slot) { m_slot=slot; m_startTick=OSGetTick(); }
    inline ~ScopedTimer() {
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick()-m_startTick)*8)/
            ((*(unsigned int*)0x800000F8/4)/125000))/lbl_806D4FDC);
    }
private:
    unsigned int m_startTick;
    volatile int m_slot;
};
static inline void BuildCamera(Vec origin,const Vec& target) {
    EulerAngles rotation;
    Vec direction;
    Vec3_Subtract_DestFirst(&direction,&target,&origin);
    Vec3_ToYawPitch(&direction,&rotation.x,&rotation.y);
    rotation.z=lbl_806D4FE8;
    Mtx44_FromEulerXYZTrans(&lbl_805DF3D0.view,origin,rotation);
    Mtx44_Inverse_GaussJordan(&lbl_805DF3D0.inverse,&lbl_805DF3D0.view);
    Vec3_Copy(&lbl_805DF3D0.position,&origin);
    Vec3_Copy(&lbl_805DF3D0.target,&target);
}
/* Retain both input vectors while the camera matrices are rebuilt. */
struct CameraInputs {
    Vec target;
    Vec position;
    CameraInputs(const Vec* positionIn,const Vec* targetIn) {
        position=*positionIn;
        target=*targetIn;
    }
};
static inline void SetCamera(const Vec* position,const Vec* target) {
    CameraInputs inputs(position,target);
    BuildCamera(inputs.position,inputs.target);
}
static inline void UpdateSlots(Slot *slot) {
    int i=0;
    do {
        if(slot->active) {
            if(slot->tick) slot->tick(slot);
            Vec3_Copy(&slot->renderPosition,&slot->position);
            slot->renderScale=lbl_806D4FEC*slot->scale;
            if(slot->renderScale<lbl_806D4FE8) slot->renderScale=lbl_806D4FF0;
        }
        ++i;
        ++slot;
    } while(i<512);
}
extern "C" void VfxSlotMgr_Update(const Vec *position,const Vec *target) {
    ScopedTimer timer(25);
    SetCamera(position,target);
    UpdateSlots(g_drawEffectSlots);
}
