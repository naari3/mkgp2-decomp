/* Grounded AI movement, reconstructed from 0x801EED14..0x801EFFA4.
 * NonMatching: see HANDOFF.md for measured code-generation differences. */
#include "game/GroundedMovementPrivate.h"
#include "game/singleton.h"

extern "C" {
extern AIPairRecord lbl_806793D8[8];
extern void *g_courseData;
extern const float lbl_806DA428, lbl_806DA430, lbl_806DA43C, lbl_806DA44C;
extern const float lbl_806DA4D0, lbl_806DA4FC, lbl_806DA500, lbl_806DA504;
extern const float lbl_806DA508, lbl_806DA50C, lbl_806DA510, lbl_806DA514;
extern const float lbl_806DA518, lbl_806DA51C, lbl_806DA520, lbl_806DA524;
extern const float lbl_806DA528, lbl_806DA52C;
extern float lbl_806D1930, lbl_806D193C;
float PseudoRandom_Next();
float LateralOffset_GetMagnitude(void *);
int fn_801EB708();
void fn_801DB994(void *, int);
int RaceSlot_GetDriverId(int);
int RivalAvoidance_CalcPattern(void *, int, float);
int fn_801DDADC(int);
int fn_801DDAB4(int);
float fn_801DDA8C(int);
void GetSpawnPosition(PhysicsPlainVec *, float,float,float);
void *KartDriver_GetKartRootMtx(void *);
void Mtx44_GetTranslation_RowMajor(PhysicsPlainVec *, const void *);
void Vec3_Subtract_DestFirst(PhysicsPlainVec *, const PhysicsPlainVec *, const PhysicsPlainVec *);
void Vec3_Add_DestFirst(PhysicsPlainVec *, const PhysicsPlainVec *, const PhysicsPlainVec *);
void Vec2_RotateY(PhysicsPlainVec *, const PhysicsPlainVec *, float);
GroundedWaypoint *CourseData_GetPath(void *, int);
int CourseData_ResolveByKey(void *, const void *);
int fn_801DBA58(void *);
int fn_801DBA34(void *);
GroundedWaypoint *fn_801DB9C4(void *, int);
void *fn_801DBA2C(void *);
int PathIndex_AdvanceCircular(void *, int);
GroundedWaypoint *Path_GetWaypointPtr(void *, int);
float fn_800D3184(const PhysicsPlainVec *, const PhysicsPlainVec *);
void Vec3_Lerp(PhysicsPlainVec *, PhysicsPlainVec, PhysicsPlainVec, float);
float Vec3_HorizontalYawTo(const PhysicsPlainVec *, const PhysicsPlainVec *);
void Vec3_Copy(PhysicsPlainVec *, const PhysicsPlainVec *);
float LUT_Sine(float);
float LUT_Cosine(float);
void fn_801DBA84(void *);
float AI_CalcRivalAvoidance(void *);
float fn_801DE7B0();
}

static inline void groundedSqrt(float &v) {
    if (v > lbl_806DA42C) {
        double e=__frsqrte(v);
        e=lbl_806DA458*e*(lbl_806DA460-v*(e*e));
        e=lbl_806DA458*e*(lbl_806DA460-v*(e*e));
        e=lbl_806DA458*e*(lbl_806DA460-v*(e*e));
        volatile float result=v*e;
        v=result;
    }
}
static inline void groundedAngle(float &a) {
    while (lbl_806DA488 <= a) a-=lbl_806DA484;
    while (a < lbl_806DA48C) a+=lbl_806DA484;
}
static inline float groundedTargetSpeed(float angle, float maximum, float minimum) {
    return (maximum-minimum)/lbl_806DA4FC*(lbl_806DA4FC-angle)+minimum;
}
/* The singleton accessor keeps its null fallback in the target. */
static inline void *courseData() {
    return SINGLETON_INSTANCE(g_courseData);
}

#pragma use_lmw_stmw on
#pragma push
#pragma opt_common_subs off
extern "C" void KartPhysics_GroundedMovement(GroundedMovementState *self) {
    const char *constants=lbl_803BD920;
    if (self->steeringLock>0) --self->steeringLock;
    if (!self->enabled) return;

    if (self->wanderTimer>0) --self->wanderTimer;
    else {
        void *lateral=self->controller->lateralOffset;
        float random=PseudoRandom_Next();
        self->lateralWander=random*LateralOffset_GetMagnitude(lateral);
        self->wanderTimer=fn_801EB708()%120+160;
    }
    if (self->avoidanceTimer>0) --self->avoidanceTimer;
    switch (self->avoidanceMode) {
    case 0: case 1: case 2: case 3:
        if (self->avoidanceTimer<=0) {
            if (self->selectedPath!=-1) fn_801DB994(self->follower,self->previousSelectedPath);
            self->avoidanceOffset=lbl_806DA42C;
            self->selectedPath=-1;
            self->previousSelectedPath=-1;
            self->avoidanceMode=-1;
        }
        break;
    case -1: default:
        if (self->avoidanceTimer<=0) {
            void *lateral;
            AIPairRecord *pair=&lbl_806793D8[self->kartId];
            float magnitude=lbl_806DA450;
            if (pair->nearestKart>=0) {
                float distance=pair->distanceSquared;
                lateral=self->controller->lateralOffset;
                groundedSqrt(distance);
                int driver=RaceSlot_GetDriverId(pair->nearestKart);
                int pattern=RivalAvoidance_CalcPattern(lateral,driver,distance);
                if (pattern>=0) {
                    self->avoidanceMode=fn_801DDADC(pattern);
                    self->avoidanceTimer=fn_801DDAB4(pattern);
                    magnitude=fn_801DDA8C(pattern);
                }
            }
            switch (self->avoidanceMode) {
            case 0: case 1: {
                PhysicsPlainVec position;
                GetSpawnPosition(&position,self->position.x,self->position.y,self->position.z);
                PhysicsPlainVec other;
                Mtx44_GetTranslation_RowMajor(&other,KartDriver_GetKartRootMtx(pair->nearestDriver));
                Vec3_Subtract_DestFirst(&other,&other,&position);
                Vec2_RotateY(&other,&other,-self->matrixYaw);
                if (self->avoidanceMode==0) {
                    if (lbl_806DA42C<other.x) self->avoidanceOffset=magnitude;
                    else self->avoidanceOffset=-magnitude;
                } else {
                    if (lbl_806DA42C<other.x) self->avoidanceOffset=-magnitude;
                    else self->avoidanceOffset=magnitude;
                }
                break;
            }
            case 2: case 3: {
                PhysicsPlainVec other;
                Mtx44_GetTranslation_RowMajor(&other,KartDriver_GetKartRootMtx(pair->nearestDriver));
                float leftDistance=lbl_806DA42C;
                int left=-1, right=-1;
                float rightDistance=leftDistance;
                void *course=courseData();
                GroundedWaypoint *path=CourseData_GetPath(course,fn_801DBA58(self->follower));
                int count=CourseData_ResolveByKey(courseData(),path);
                int index=fn_801DBA34(self->follower)%count;
                PhysicsPlainVec start=*(const PhysicsPlainVec *)(constants+0x444);
                PhysicsPlainVec end=*(const PhysicsPlainVec *)(constants+0x450);
                PhysicsPlainVec direction=*(const PhysicsPlainVec *)(constants+0x45c);
                start.set(path[index].x,path[index].y,path[index].z);
                index=(index+1)%count;
                end.set(path[index].x,path[index].y,path[index].z);
                direction.set(end.x-start.x,end.y-start.y,end.z-start.z);
                for (int i=0;i<5;i++) {
                    GroundedWaypoint *candidate=CourseData_GetPath(courseData(),i);
                    if (candidate && i!=fn_801DBA58(self->follower)) {
                        int n=CourseData_ResolveByKey(courseData(),candidate);
                        int j=fn_801DBA34(self->follower)%n;
                        PhysicsPlainVec point=*(const PhysicsPlainVec *)(constants+0x468);
                        /* Target reads +0x10 for this z, across the record boundary. */
                        GroundedWaypoint *record=candidate+j;
                        point.x=record->x;
                        point.y=record->y;
                        point.z=record[1].metadata;
                        float distance=fn_800D3184(&other,&point);
                        PhysicsPlainVec delta=*(const PhysicsPlainVec *)(constants+0x474);
                        delta.set(point.x-start.x,point.y-start.y,point.z-start.z);
                        if (direction.x*delta.z-direction.z*delta.x>lbl_806DA42C) {
                            if (left<0) { left=i; leftDistance=distance; }
                            if (leftDistance>distance) { leftDistance=distance; left=i; }
                        } else {
                            if (right<0) { right=i; rightDistance=distance; }
                            if (rightDistance>distance) { right=i; rightDistance=distance; }
                        }
                    }
                }
                self->previousSelectedPath=self->selectedPath;
                if (direction.x*(other.z-start.z)-direction.z*(other.x-start.x)>lbl_806DA42C) {
                    if (self->avoidanceMode==2) self->selectedPath=left;
                    else self->selectedPath=right;
                } else {
                    if (self->avoidanceMode==2) self->selectedPath=right;
                    else self->selectedPath=left;
                }
                if (self->selectedPath!=-1) {
                    fn_801DB994(self->follower,self->selectedPath);
                    self->lateralWander=lbl_806DA42C;
                    self->wanderTimer=self->avoidanceTimer;
                }
                break;
            }
            case -1: default: self->avoidanceTimer=30; break;
            }
        }
        break;
    }

    void *path=fn_801DBA2C(self->follower);
    GroundedWaypoint *ahead=Path_GetWaypointPtr(path,PathIndex_AdvanceCircular(path,2));
    float yaw=self->yaw;
    float bend=(float)atan2(ahead->x-self->position.x,ahead->z-self->position.z)-yaw;
    groundedAngle(bend);
    float angle=(float)__fabs(lbl_806DA490*bend);
    if (lbl_806DA4FC<=angle) angle=lbl_806DA4FC;
    float target=groundedTargetSpeed(angle,self->maximumSpeed,self->minimumSpeed);
    float delta=target-self->speed;
    float limit=lbl_806D1930;
    if (limit<=delta) delta=limit;
    else if (delta<=-limit) delta=-limit;
    self->speed+=delta/lbl_806DA500;
    if (self->maximumSpeed<=self->speed) self->speed=self->maximumSpeed;
    else if (self->speed<=self->minimumSpeed) self->speed=self->minimumSpeed;

    int selected=fn_801DBA58(self->follower);
    if (self->selectedPath!=-1) selected=self->selectedPath;
    if (self->currentPath!=selected) {
        self->previousPath=self->currentPath;
        self->currentPath=selected;
        self->pathBlend=lbl_806DA42C;
    }
    self->pathBlend+=lbl_806DA504;
    if (lbl_806DA450<self->pathBlend) self->pathBlend=lbl_806DA450;

    PhysicsPlainVec current=*(const PhysicsPlainVec *)(constants+0x480);
    int currentPath=self->currentPath;
    if (currentPath==-1) {
        void *follower=self->follower;
        GroundedWaypoint *p=fn_801DB9C4(follower,fn_801DBA34(follower));
        GetSpawnPosition(&current,p->x,p->y,p->z);
    } else {
        GroundedWaypoint *p=CourseData_GetPath(courseData(),currentPath);
        int count=CourseData_ResolveByKey(courseData(),p);
        int index=fn_801DBA34(self->follower)%count;
        GetSpawnPosition(&current,p[index].x,p[index].y,p[index].z);
        int previousPath=self->previousPath;
        if (previousPath!=-1 && lbl_806DA450!=self->pathBlend) {
            p=CourseData_GetPath(courseData(),previousPath);
            count=CourseData_ResolveByKey(courseData(),p);
            index=fn_801DBA34(self->follower)%count;
            PhysicsPlainVec previous=*(const PhysicsPlainVec *)(constants+0x48c);
            previous.x=p[index].x;
            previous.y=p[index].y;
            previous.z=p[index].z;
            Vec3_Lerp(&current,current,previous,self->pathBlend);
        }
    }
    PhysicsPlainVec next=*(const PhysicsPlainVec *)(constants+0x498);
    currentPath=self->currentPath;
    if (currentPath==-1) {
        void *follower=self->follower;
        GroundedWaypoint *p=fn_801DB9C4(follower,fn_801DBA34(follower)+1);
        GetSpawnPosition(&next,p->x,p->y,p->z);
    } else {
        GroundedWaypoint *p=CourseData_GetPath(courseData(),currentPath);
        int count=CourseData_ResolveByKey(courseData(),p);
        int index=(fn_801DBA34(self->follower)+1)%count;
        GetSpawnPosition(&next,p[index].x,p[index].y,p[index].z);
        int previousPath=self->previousPath;
        if (previousPath!=-1 && lbl_806DA450!=self->pathBlend) {
            p=CourseData_GetPath(courseData(),previousPath);
            count=CourseData_ResolveByKey(courseData(),p);
            index=fn_801DBA34(self->follower)%count;
            PhysicsPlainVec previous=*(const PhysicsPlainVec *)(constants+0x4a4);
            previous.x=p[index].x;
            previous.y=p[index].y;
            previous.z=p[index].z;
            Vec3_Lerp(&next,next,previous,self->pathBlend);
        }
    }
    float pathYaw=Vec3_HorizontalYawTo(&current,&next);
    PhysicsPlainVec localPosition;
    GetSpawnPosition(&localPosition,self->position.x,self->position.y,self->position.z);
    Vec3_Subtract_DestFirst(&localPosition,&localPosition,&current);
    Vec2_RotateY(&localPosition,&localPosition,-pathYaw);
    PhysicsPlainVec offset;
    if (lbl_806DA42C==self->avoidanceOffset) {
        if (lbl_806DA42C<localPosition.x) GetSpawnPosition(&offset,self->lateralWander,lbl_806DA42C,lbl_806DA42C);
        else GetSpawnPosition(&offset,-self->lateralWander,lbl_806DA42C,lbl_806DA42C);
    } else GetSpawnPosition(&offset,self->avoidanceOffset,lbl_806DA42C,lbl_806DA42C);
    float difference=offset.x-self->lateralPosition;
    if (self->lateralWander<(float)__fabs(difference)) {
        if (difference>lbl_806DA42C) offset.x-=self->lateralWander;
        else offset.x+=self->lateralWander;
    }
    int pathId=self->follower ? fn_801DBA58(self->follower) : -1;
    if (pathId==1 && offset.x>lbl_806DA42C) offset.x=lbl_806DA42C;
    pathId=self->follower ? fn_801DBA58(self->follower) : -1;
    if (pathId==5 && offset.x<lbl_806DA42C) offset.x=lbl_806DA42C;
    Vec2_RotateY(&offset,&offset,pathYaw);
    Vec3_Add_DestFirst(&current,&current,&offset);
    PhysicsPlainVec toward=*(const PhysicsPlainVec *)(constants+0x4b0);
    toward.set(current.x-self->position.x,current.y-self->position.y,current.z-self->position.z);
    float heading=(float)atan2(toward.x,toward.z)-self->yaw;
    groundedAngle(heading);
    float distance=toward.x*toward.x+toward.z*toward.z;
    groundedSqrt(distance);
    float side=toward.x*LUT_Sine(heading);
    side=toward.z*LUT_Cosine(heading)-side;
    Vec3_Copy(&self->targetPosition,&current);
    int advanced=0;
    if (distance<lbl_806DA508 || (side<=lbl_806DA42C && distance<lbl_806DA50C)) {
        fn_801DBA84(self->follower);
        advanced=1;
    } else {
        void *follower=self->follower;
        GroundedWaypoint *p=fn_801DB9C4(follower,fn_801DBA34(follower)-1);
        PhysicsPlainVec previous=*(const PhysicsPlainVec *)(constants+0x4bc);
        previous.x=p->x;
        previous.y=p->y;
        previous.z=p->z;
        follower=self->follower;
        p=fn_801DB9C4(follower,fn_801DBA34(follower));
        PhysicsPlainVec point=*(const PhysicsPlainVec *)(constants+0x4c8);
        point.x=p->x;
        point.y=p->y;
        point.z=p->z;
        float angle=-Vec3_HorizontalYawTo(&previous,&point);
        PhysicsPlainVec passed;
        passed.x=self->position.x-current.x;
        passed.y=self->position.y-current.y;
        passed.z=self->position.z-current.z;
        Vec2_RotateY(&passed,&passed,angle);
        if (lbl_806DA42C<passed.z) { fn_801DBA84(self->follower); advanced=1; }
    }
    float steering=heading;
    if (self->avoidanceEnabled && lbl_806793D8[self->kartId].field24!=2) steering=heading+AI_CalcRivalAvoidance(self);
    if (self->steeringLock<=0) steering+=self->SteeringCorrection(steering);
    steering+=self->yawBias;
    float normalized=steering;
    groundedAngle(normalized);
    float speed=self->speed;
    speed/=lbl_806DA44C; speed/=lbl_806DA44C; speed/=lbl_806DA44C;
    float speedFactor=lbl_806DA510*speed;
    if (lbl_806DA450<speedFactor) speedFactor=lbl_806DA450;
    float distanceFactor=lbl_806DA428/distance;
    if (lbl_806DA450<distanceFactor) distanceFactor=lbl_806DA450;
    float turn=lbl_806DA43C*(speedFactor*(normalized*distanceFactor));
    if (self->turnStep!=lbl_806DA42C) {
        float old=self->turnVelocity;
        float step=self->turnStep;
        float retainedTurn=lbl_806DA470*old;
        turn=(turn-retainedTurn)/step;
        float fraction=turn;
        while (lbl_806DA450<=fraction) fraction-=lbl_806DA450;
        while (fraction<=lbl_806DA514) fraction+=lbl_806DA450;
        turn-=fraction;
        if (lbl_806DA4A0<=fraction) turn+=lbl_806DA450;
        else if (fraction<=lbl_806DA518) turn-=lbl_806DA450;
        retainedTurn=lbl_806DA470*old;
        turn=turn*step;
        turn+=retainedTurn;
    }
    self->turnVelocity=lbl_806DA490*turn;
    if (self->steeringEnabled) self->yaw+=turn;
    if (advanced) {
        self->slipStrength=(float)__fabs(lbl_806DA490*normalized);
        self->slipStrength-=lbl_806DA51C;
        if (self->slipStrength<lbl_806DA42C) self->slipStrength=lbl_806DA42C;
        self->slipStrength*=lbl_806DA4D0;
    }
    speed=self->speed;
    if (lbl_806D193C<=speed) speed=lbl_806D193C;
    float scale=lbl_806DA430*fn_801DE7B0();
    scale=lbl_806DA520*scale;
    float slip=self->slipStrength*(speed/(lbl_806D193C/scale));
    if (self->turnVelocity<lbl_806DA42C) slip=-slip;
    float step=lbl_806DA4D0;
    if (self->fastSlip) step=lbl_806DA524;
    if (lbl_806DA42C!=self->yawBias) step=lbl_806DA524;
    if (self->collisionTimer>0) step=lbl_806DA524;
    if (slip<self->slip) self->slip-=step;
    if (self->slip<slip) self->slip+=step;
    if (lbl_806DA528<self->slip) self->slip=lbl_806DA528;
    if (self->slip<lbl_806DA52C) self->slip=lbl_806DA52C;
    float slipYaw=lbl_806DA470*self->slip;
    self->matrixYaw=self->yaw+slipYaw;
    speed=self->speed;
    speed/=lbl_806DA44C; speed/=lbl_806DA44C; speed/=lbl_806DA44C;
    if (speed<lbl_806DA450) speed=lbl_806DA450;
    float length=speed*speed+self->velocity.y*self->velocity.y;
    groundedSqrt(length);
    float loss=length-speed;
    if (lbl_806DA42C<speed) {
        speed-=loss;
        if (speed<lbl_806DA42C) speed=lbl_806DA42C;
    }
    self->position.x+=speed*LUT_Cosine(self->yaw);
    self->position.z+=speed*LUT_Sine(self->yaw);
}
#pragma pop

#pragma use_lmw_stmw reset
