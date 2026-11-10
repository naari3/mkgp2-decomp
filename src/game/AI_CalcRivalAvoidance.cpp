/* Native reconstruction. Segment yaw is rounded within its inline helper;
 * candidate-position lifetime and FP allocation remain NonMatching. */
#include "game/RivalAvoidanceUnlockPrivate.h"
extern "C" {
extern void *g_pathSystem;
extern AIPairRecord lbl_806793D8[8];
extern const float lbl_806DA4E0,lbl_806DA4E8,lbl_806DA4EC,lbl_806DA4F0;
extern const float lbl_806DA4E4;
extern float lbl_806DA4F4,lbl_806DA4F8,lbl_806DA448;
extern float lbl_806D1934,lbl_806D1938,AI_CalcRivalAvoidance_bss_806D194C,AI_CalcRivalAvoidance_bss_806D1954;
extern signed char AI_CalcRivalAvoidance_bss_806D1950,AI_CalcRivalAvoidance_bss_806D1958;
RivalPathEntry *PathManager_GetEntrySubStruct(void *, int);
void *fn_801DBA2C(void *);
int Waypoint_FindNearest(void *, int, float,float,float,float);
RivalWaypoint *Path_GetWaypointPtr(void *,int);
int Path_GetTotalCount(void *);
float GetCourseStartYaw();
float LUT_Cosine(float);
float LUT_Sine(float);
float PSVECSquareDistance(const void *,const void *);
}
static inline float rivalSegmentYaw(const RivalWaypoint *a, const RivalWaypoint *b) {
    float angle=(float)atan2(b->x-a->x,b->z-a->z);
    return angle;
}
static inline float reduceRivalAngle(float angle, float bound, float turn) {
    while(bound<=angle) angle-=turn;
    return angle;
}
static inline float raiseRivalAngle(float angle, float bound, float turn) {
    while(angle<bound) angle+=turn;
    return angle;
}
static inline float normalizeRivalAngle(float angle) {
    angle=reduceRivalAngle(angle,3.1415927f,6.2831855f);
    return raiseRivalAngle(angle,-3.1415927f,6.2831855f);
}
static inline unsigned char findRival(RivalAvoidanceState *self,RivalAvoidanceCandidate &candidate) {
    AIPairRecord *tracking=&lbl_806793D8[self->kartId];
    if(tracking->nearestKart<0) return 0;
    {
        RivalPathEntry *rival=PathManager_GetEntrySubStruct(g_pathSystem,tracking->nearestKart);
        if(rival->valid<0) return 0;
        else {
            RivalPathEntry *entry=PathManager_GetEntrySubStruct(g_pathSystem,self->pathId);
            float yaw=self->yaw;
            float angle=normalizeRivalAngle((float)atan2(*rival->x-*entry->x,*rival->z-*entry->z)-yaw);
            if(-lbl_806D1934<angle && angle<lbl_806D1934) {
                candidate.distance=tracking->distanceSquared;
                candidate.position.set(*rival->x,*rival->y,*rival->z);
                candidate.id=tracking->nearestKart;
                candidate.angle=angle;
                return 1;
            } else return 0;
        }
    }
    return 0;
}
static inline float rivalAvoidanceAmount(float distance, float lower) {
    float amount=distance-lower;
    amount=269808.0f-amount;
    amount=amount/269808.0f;
    amount=amount+0.02f;
    return lbl_806D1938*amount;
}
static inline int nearestRivalWaypoint(void *path, const PhysicsPlainVec &position) {
    int nearest = Waypoint_FindNearest(path, 0, position.x, position.y, position.z, 6e+02f);
    return nearest;
}
struct RivalProbeOffset {
    float x, z;
    RivalProbeOffset(float distance, float cosine, float sine)
        : x(distance * cosine), z(distance * sine) {}
};
extern "C" float AI_CalcRivalAvoidance(RivalAvoidanceState *self) {
    const char *constants=lbl_803BD920;
    RivalPathEntry *entry=PathManager_GetEntrySubStruct(g_pathSystem,self->pathId);
    if(!entry || entry->valid<0) return 0.0f;
    self->avoiding=0;
    RivalAvoidanceCandidate candidate;
    unsigned char found=findRival(self,candidate);
    if(!found) return 0.0f;
    if(2.7e+05f<candidate.distance || candidate.distance<192.0f) return 0.0f;
    self->avoiding=1;
    float amount=rivalAvoidanceAmount(candidate.distance,192.0f);
    if(!AI_CalcRivalAvoidance_bss_806D1950) { AI_CalcRivalAvoidance_bss_806D194C=0.7f*lbl_806D1934; AI_CalcRivalAvoidance_bss_806D1950=1; }
    if(!AI_CalcRivalAvoidance_bss_806D1958) { AI_CalcRivalAvoidance_bss_806D1954=-AI_CalcRivalAvoidance_bss_806D194C; AI_CalcRivalAvoidance_bss_806D1958=1; }
    if(candidate.angle>AI_CalcRivalAvoidance_bss_806D194C) return -amount;
    if(AI_CalcRivalAvoidance_bss_806D1954>candidate.angle) return amount;
    void *path=fn_801DBA2C(self->follower);
    int nearest=nearestRivalWaypoint(path,candidate.position);
    float yaw;
    if(nearest>=0) {
        RivalWaypoint *a=Path_GetWaypointPtr(path,nearest);
        RivalWaypoint *b=Path_GetWaypointPtr(path,(nearest+1)%Path_GetTotalCount(path));
        if(b->valid<0) b=Path_GetWaypointPtr(path,0);
        yaw=rivalSegmentYaw(a,b);
    } else yaw=GetCourseStartYaw();
    yaw=1.5707964f+yaw;
    float c=LUT_Cosine(yaw);
    float s=LUT_Sine(yaw);
    float distance=1e+03f;
    RivalProbeOffset offset(distance,c,s);
    PhysicsCollisionVec endpoint;
    endpoint.set(candidate.position.x+offset.x,candidate.position.y,candidate.position.z+offset.z);
    PhysicsCollisionVec hit;
    PhysicsCollisionVec normal;
    if(Terrain_RaycastWall(&candidate.position,&endpoint,&hit,&normal)) {
        PhysicsPlainVec from=*(PhysicsPlainVec *)(constants+0x4d4);
        PhysicsPlainVec to=*(PhysicsPlainVec *)(constants+0x4e0);
        from.set(candidate.position.x,candidate.position.y,candidate.position.z);
        to.set(hit.x,hit.y,hit.z);
        distance=PSVECSquareDistance(&from,&to);
    }
    endpoint.set(candidate.position.x-offset.x,candidate.position.y,candidate.position.z-offset.z);
    if(Terrain_RaycastWall(&candidate.position,&endpoint,&hit,&normal)) {
        PhysicsPlainVec from=*(PhysicsPlainVec *)(constants+0x4ec);
        PhysicsPlainVec to=*(PhysicsPlainVec *)(constants+0x4f8);
        from.set(candidate.position.x,candidate.position.y,candidate.position.z);
        to.set(hit.x,hit.y,hit.z);
        distance=PSVECSquareDistance(&from,&to);
    }
    if(distance>1e+03f) return amount;
    return -amount;
}

