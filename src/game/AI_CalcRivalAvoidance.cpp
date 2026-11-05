/* Native reconstruction. The complete body and cleanup locals are retained;
 * the first EH interval and register allocation remain NonMatching. */
#include "game/RivalAvoidancePrivate.h"
extern "C" {
extern void *g_pathSystem;
extern AIPairRecord lbl_806793D8[8];
extern float lbl_806DA4E0,lbl_806DA4E4,lbl_806DA4E8,lbl_806DA4EC,lbl_806DA4F0;
extern float lbl_806DA4F4,lbl_806DA4F8,lbl_806DA448;
extern float lbl_806D1934,lbl_806D1938,lbl_806D194C,lbl_806D1954;
extern signed char lbl_806D1950,lbl_806D1958;
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
static inline float normalizeRivalAngle(float angle) {
    while(lbl_806DA488<=angle) angle-=lbl_806DA484;
    while(angle<lbl_806DA48C) angle+=lbl_806DA484;
    return angle;
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
extern "C" float AI_CalcRivalAvoidance(RivalAvoidanceState *self) {
    const char *constants=lbl_803BD920;
    RivalPathEntry *entry=PathManager_GetEntrySubStruct(g_pathSystem,self->pathId);
    if(!entry || entry->valid<0) return lbl_806DA42C;
    self->avoiding=0;
    RivalAvoidanceCandidate candidate;
    unsigned char found=findRival(self,candidate);
    if(!found) return lbl_806DA42C;
    if(lbl_806DA4E0<candidate.distance || candidate.distance<lbl_806DA4E4) return lbl_806DA42C;
    self->avoiding=1;
    float amount=lbl_806D1938*((lbl_806DA4E8-(candidate.distance-lbl_806DA4E4))/lbl_806DA4E8+lbl_806DA4EC);
    if(!lbl_806D1950) { lbl_806D194C=lbl_806DA4F0*lbl_806D1934; lbl_806D1950=1; }
    if(!lbl_806D1958) { lbl_806D1954=-lbl_806D194C; lbl_806D1958=1; }
    if(candidate.angle>lbl_806D194C) return -amount;
    if(lbl_806D1954>candidate.angle) return amount;
    void *path=fn_801DBA2C(self->follower);
    int nearest=Waypoint_FindNearest(path,0,candidate.position.x,candidate.position.y,candidate.position.z,lbl_806DA4F4);
    float yaw;
    if(nearest>=0) {
        RivalWaypoint *a=Path_GetWaypointPtr(path,nearest);
        RivalWaypoint *b=Path_GetWaypointPtr(path,(nearest+1)%Path_GetTotalCount(path));
        if(b->valid<0) b=Path_GetWaypointPtr(path,0);
        yaw=(float)atan2(b->x-a->x,b->z-a->z);
    } else yaw=GetCourseStartYaw();
    yaw=lbl_806DA4F8+yaw;
    float c=LUT_Cosine(yaw);
    float s=LUT_Sine(yaw);
    float distance=lbl_806DA448;
    float dx=distance*c;
    float dz=distance*s;
    PhysicsCollisionVec endpoint;
    endpoint.set(candidate.position.x+dx,candidate.position.y,candidate.position.z+dz);
    PhysicsCollisionVec hit;
    PhysicsCollisionVec normal;
    if(Terrain_RaycastWall(&candidate.position,&endpoint,&hit,&normal)) {
        PhysicsPlainVec from=*(PhysicsPlainVec *)(constants+0x4d4);
        PhysicsPlainVec to=*(PhysicsPlainVec *)(constants+0x4e0);
        from.set(candidate.position.x,candidate.position.y,candidate.position.z);
        to.set(hit.x,hit.y,hit.z);
        distance=PSVECSquareDistance(&from,&to);
    }
    endpoint.set(candidate.position.x-dx,candidate.position.y,candidate.position.z-dz);
    if(Terrain_RaycastWall(&candidate.position,&endpoint,&hit,&normal)) {
        PhysicsPlainVec from=*(PhysicsPlainVec *)(constants+0x4ec);
        PhysicsPlainVec to=*(PhysicsPlainVec *)(constants+0x4f8);
        from.set(candidate.position.x,candidate.position.y,candidate.position.z);
        to.set(hit.x,hit.y,hit.z);
        distance=PSVECSquareDistance(&from,&to);
    }
    if(distance>lbl_806DA448) return amount;
    return -amount;
}
