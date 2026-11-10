#ifndef GAME_SUIKABALLOBJ_PHYSICS_PRIVATE_H
#define GAME_SUIKABALLOBJ_PHYSICS_PRIVATE_H

/* Layout consumed by SuikaBallObj_UpdatePhysics (0x801240E4).
 * Vec/Mtx mirror dolphin/mtx.h; that header currently requires unavailable
 * standard headers through dolphin/types.h in this TU flag recipe. */
typedef struct { float x, y, z; } Vec;
typedef float Mtx[3][4];
extern void PSMTXRotRad(Mtx, char, float);
extern void PSMTXRotAxisRad(Mtx, const Vec *, float);
extern void PSMTXConcat(const Mtx, const Mtx, Mtx);
extern void PSVECScale(const Vec *, Vec *, float);
extern void PSVECAdd(const Vec *, const Vec *, Vec *);
typedef struct {
 void *object; float radius; Mtx matrix; Vec position, velocity; float spin; Vec spin_axis;
 unsigned char hit, damp; unsigned short unused;
 float inner, outer, restitution, gravity, air_drag, ground_drag;
} SuikaBallPhysics;
typedef struct { Vec v[4]; } BallProbes;
extern const BallProbes SuikaBallObj_UpdatePhysics_rodata_80355918, SuikaBallObj_UpdatePhysics_rodata_80355948;
extern void Vec3_Subtract(const Vec *, const Vec *, Vec *);
extern float Vec3_Magnitude(const Vec *);
extern float Vec3_Dot(const Vec *, const Vec *);
extern void Vec3_Normalize(const Vec *, Vec *);
extern unsigned char Terrain_RaycastWall(const Vec *, const Vec *, Vec *, Vec *);
extern unsigned char Terrain_GetGroundHeight(const Vec *, float *, void *, void *);
extern void Object_DriveAnimMatrix(void *);

#endif
