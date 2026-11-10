#ifndef GAME_PHYSICS_COLLISION_PRIVATE_H
#define GAME_PHYSICS_COLLISION_PRIVATE_H

/* Private views recovered from the PhysicsState collision disassembly. */
struct PhysicsPlainVec {
    float x, y, z;
    void set(float a, float b, float c) { x = a; y = b; z = c; }
};
struct PhysicsCollisionVec {
    float x, y, z;
    PhysicsCollisionVec() {}
    PhysicsCollisionVec(const PhysicsCollisionVec &v) : x(v.x), y(v.y), z(v.z) {}
    ~PhysicsCollisionVec() {}
    void set(float a, float b, float c) { x = a; y = b; z = c; }
};
struct PhysicsCollisionShape {
    char storage[0x58];
    PhysicsCollisionShape(int, int);
    ~PhysicsCollisionShape();
};
struct PhysicsCollisionCar {
    virtual void Slot08();
    virtual void Slot0C();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void OnKartHit(void *);
};

#define PH_F(p, o) (*(float *)((char *)(p) + (o)))
#define PH_I(p, o) (*(int *)((char *)(p) + (o)))
#define PH_B(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define PH_P(p, o) (*(void **)((char *)(p) + (o)))
#define PH_V(p, o) (*(PhysicsCollisionVec *)((char *)(p) + (o)))

extern "C" {
extern char lbl_803BD920[];
extern PhysicsCollisionVec lbl_803BDD28[4];
extern void *Read_U32[];
extern void *g_objCollChecker;
extern float lbl_806DA42C, lbl_806DA444, lbl_806DA450;
extern float lbl_806DA470, lbl_806DA474, lbl_806DA478, lbl_806DA47C;
extern float lbl_806DA480, lbl_806DA484, lbl_806DA488, lbl_806DA48C;
extern float lbl_806DA490, lbl_806DA494, lbl_806DA498;
extern float lbl_806DA49C, lbl_806DA4A0, lbl_806DA4A4;
extern double lbl_806DA458, lbl_806DA460;
void *KartController_GetRenderObj(void *);
PhysicsCollisionCar *GetPlayerCarBySlot(int);
float *CarObject_GetTransformMatrix(void *);
void *CarObject_GetRenderObj(void *);
void Mtx4x4_TransposeTo4x3(const void *, void *);
void HSD_MtxGetRotation(const void *, void *);
#ifdef __MWERKS__
void fn_802090F0(PhysicsCollisionShape *, PhysicsPlainVec *, PhysicsPlainVec *, float, float, float);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_802090F0(PhysicsCollisionShape *, float, float, float, PhysicsPlainVec *, PhysicsPlainVec *);
static inline void fn_802090F0_Reordered(PhysicsCollisionShape *a0, PhysicsPlainVec *a1, PhysicsPlainVec *a2, float a3, float a4, float a5) { fn_802090F0(a0, a3, a4, a5, a1, a2); }
#define fn_802090F0 fn_802090F0_Reordered
#endif
float CollisionTest_CalcPenetration(void *, PhysicsCollisionShape *, void *);
void Vec3_Subtract(const void *, const void *, void *);
void Vec3_Normalize(const void *, void *);
float Vec3_Distance(const void *, const void *);
void fn_80057960(void *, float, float, float, float, float, float, float);
double atan2(double, double);
void KartReaction_Front(void *);
void KartReaction_Side(void *);
void KartReaction_Rear(void *);
unsigned char Terrain_RaycastWall(const void *, const void *, void *, void *);
double cos(double);
double sin(double);
}
#endif
