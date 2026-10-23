/* Native manager lifetime and camera update. Layout follows target accesses. */
struct Vec {
    float x,y,z;
    Vec() {}
    Vec(const Vec& other) { *(int*)&x=*(const int*)&other.x; *(int*)&y=*(const int*)&other.y; *(int*)&z=*(const int*)&other.z; }
};
struct Matrix { float m[16]; };
struct Camera { Matrix view,inverse; Vec position,target; };
struct Slot {
    signed char active; char pad1[3]; void (*tick)(Slot*);
    char pad8[0x84]; Vec position; char pad98[0x18]; float scale;
    char padB4[4]; Vec renderPosition; float renderScale; char padC8[0x104];
};
class Resource { public: virtual ~Resource(); };
extern "C" {
unsigned int OSGetTick();
void Profiler_RecordFrame(int,float);
void VfxSlot_Release(void*);
void fn_8022B1C8();
void Vec3_Subtract_DestFirst(Vec*,const Vec*,const Vec*);
void Vec3_ToYawPitch(const Vec*,float*,float*);
void Mtx44_FromEulerXYZTrans(Matrix*,Vec,Vec);
void Mtx44_Inverse_GaussJordan(Matrix*,const Matrix*);
void Vec3_Copy(Vec*,const Vec*);
extern Slot lbl_805DF468[512];
extern Resource *lbl_806D14A8;
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
static inline void SetCamera(Vec target,Vec position) {
    Vec rotation;
    Vec direction;
    Vec origin=position;
    Vec3_Subtract_DestFirst(&direction,&target,&origin);
    Vec3_ToYawPitch(&direction,&rotation.x,&rotation.y);
    rotation.z=lbl_806D4FE8;
    Mtx44_FromEulerXYZTrans(&lbl_805DF3D0.view,origin,rotation);
    Mtx44_Inverse_GaussJordan(&lbl_805DF3D0.inverse,&lbl_805DF3D0.view);
    Vec3_Copy(&lbl_805DF3D0.position,&origin);
    Vec3_Copy(&lbl_805DF3D0.target,&target);
}
extern "C" void VfxSlotMgr_Update(const Vec *position,const Vec *target) {
    ScopedTimer timer(25);
    SetCamera(*target,*position);
    for(int i=0;i<512;++i) {
        Slot *slot=&lbl_805DF468[i];
        if(slot->active) {
            if(slot->tick) slot->tick(slot);
            Vec3_Copy(&slot->renderPosition,&slot->position);
            slot->renderScale=lbl_806D4FEC*slot->scale;
            if(slot->renderScale<lbl_806D4FE8) slot->renderScale=lbl_806D4FF0;
        }
    }
}
