#include "game/types/reg_args.h"
#include "game/AIFramePairPrivate.h"
static inline FramePairRecord *FramePairs() {
    return reinterpret_cast<FramePairRecord *>(lbl_806793D8);
}
static inline void FrameVecSubtract(Vec *v, const Vec *p) {
    v->x -= p->x; v->y -= p->y; v->z -= p->z;
}
static inline float FrameVecSquare(const Vec *v) {
    float x=v->x*v->x, y=v->y*v->y, z=v->z*v->z;
    return (x+y)+z;
}
static inline void FrameUpdatePairs(AISpeedRender *player, float px, float py, float pz) {
    AISpeedRender *driver;
    FramePairRecord *p;
    int i;
    for (i=0;i<8;++i) {
        p=&FramePairs()[i];
    if (p && p->driver) {
        driver = (AISpeedRender *)p->driver;
        float *mtx = KartDriver_GetKartRootMtx(driver);
        float z, y, x;
        x=mtx[3]; y=mtx[7]; z=mtx[11];
        p->rankDifference = driver->rank - player->rank;
        p->waypoint = Waypoint_FindNearest(g_pathSystem, 0, x,y,z,lbl_806DA3E8);
        p->nearestKart = -1;
        p->nearestDriver = 0;
        p->distanceSquared = lbl_806DA3EC;
        p->distanceSquared *= p->distanceSquared;
        p->distanceSquared *= lbl_806DA3F0;
        Vec pos; pos.x=x;pos.y=y;pos.z=z;
        for (int j=0;j<8;++j) {
            FramePairRecord *other = &FramePairs()[j];
            if (p != other && other->driver) {
                float *m = KartDriver_GetKartRootMtx(other->driver);
                Vec v;
                float y=m[7],z=m[11],x=m[3];
                v.x=x;v.y=y;v.z=z;
                float d = PSVECSquareDistance(&v,&pos);
                if (d < p->distanceSquared) {
                    p->distanceSquared=d;
                    p->nearestKart=j;
                    p->nearestDriver=other->driver;
                }
            }
        }
        float dz=z-pz;
        float dx=x-px;
        p->playerDistance=dx*dx+dz*dz;
    }
    }
}
static inline FramePairRecord *FrameFindRank(FramePairRecord *pairs, int rank, AISpeedRender *&driver) {
    FramePairRecord *record;
    FramePairRecord *cursor=pairs;
    driver=0;
    for (int i=0; i<8; ++i,++cursor) {
        record=cursor;
        if (cursor && cursor->driver && cursor->driver->rank == rank) {
            driver=cursor->driver;
            break;
        }
    }
    return record;
}
static inline void UpdateFlags(AIFrameOwner *self, AISpeedRender *player, int waypoint, FramePairRecord *pairs) {
    AISpeedRender *driver;
    FramePairRecord *p;
    self->flag18 = 0;
    if (player->rank == 0) {
        p=FrameFindRank(pairs,1,driver);
        if (driver) {
            int count=Path_GetTotalCount(g_pathSystem);
            int playerLap=player->lap;
            int total=g_totalLaps;
            int driverLap=driver->lap;
            int a=total-playerLap;
            int b=p->waypoint;
            int laps=total-driverLap;
            a=a*count;
            laps=laps*count;
            a=waypoint+a;
            b=b+laps;
            fn_801DE1B0();
            if (fn_801DE074() <= lbl_806DA3E0*(float)a-lbl_806DA3E0*(float)b) self->flag18=1;
        }
    }
    self->flag19 = 0;
    if (player->rank == 5) {
        p=FrameFindRank(pairs,4,driver);
        if (driver) {
            int count=Path_GetTotalCount(g_pathSystem);
            int playerLap=player->lap;
            int total=g_totalLaps;
            int driverLap=driver->lap;
            int a=total-playerLap;
            int b=p->waypoint;
            int laps=total-driverLap;
            a=a*count;
            laps=laps*count;
            a=waypoint+a;
            b=b+laps;
            fn_801DE1B0();
            if (fn_801DDF8C() <= lbl_806DA3E0*(float)b-lbl_806DA3E0*(float)a) self->flag19=1;
        }
    }
}
extern "C" void AI_UpdatePerFrameState(AIFrameOwner *self) {
    float distance;
    int maxFrames = lbl_806D1920;
    ++self->frame;
    if (maxFrames < self->frame) self->frame=maxFrames;
    AISpeedRender *player = CarObject_GetRenderObj(self->car);
    float *mtx = KartDriver_GetKartRootMtx(player);
    float px=mtx[3],py=mtx[7],pz=mtx[11];
    FrameUpdatePairs(player,px,py,pz);
    int waypoint;
    if (self->selectedKart < 0) waypoint=Waypoint_FindNearest(g_pathSystem,0,px,py,pz,lbl_806DA3E8);
    else waypoint=lbl_806793D8[self->selectedKart].waypoint;
    {
        int nearest=-1;
        AIFramePosition pos(mtx[3],mtx[7],mtx[11]);
        distance=lbl_806DA414;
        for (int i=0;i<8;++i) {
            FramePairRecord *p=&FramePairs()[i];
            if (p && p->driver && p->driver != player && p->field1C >= 0) {
                float *m=KartDriver_GetKartRootMtx(p->driver);
                float y=m[7],x=m[3],z=m[11];
                AIFramePosition v(x,y,z);
                FrameVecSubtract(&v,&pos);
                float d=FrameVecSquare(&v);
                if (d <= distance) { nearest=i;distance=d; }
            }
        }
        if (nearest >= 0) {
            FramePairRecord *p=&FramePairs()[nearest];
            int cup, round;
            round=g_roundIndex; cup=g_cupId;
            struct Tuning { char pad[0x18];float duration; };
            Tuning *t=(Tuning *)GetKartTuningGPSpeedParams(GetEnemyParam(),cup,round,nearest);
            if (p->field1C == 0) p->field1C=(int)(lbl_806DA40C*t->duration);
            p->field20=distance;
        } else {
            for (int i=0;i<8;++i) {
                FramePairRecord *p=&FramePairs()[i];
                if (p->field1C > 0) p->field1C=0;
                p->field20=lbl_806DA3F4;
            }
        }
    }
    UpdateFlags(self,player,waypoint,FramePairs());
    int mode=fn_801DCCE4();
    if (mode >= 0) {
        int count=0;
        float radius=fn_801DCCBC(REG_ARGS1(mode)); /* r3 still holds mode */
        float radius2=radius*radius;
        int state[8];
        for (int i=0;i<8;++i) {
            FramePairRecord *p=&FramePairs()[i];
            state[i]=0;
            if (p && p->driver) {
                unsigned char old=p->inSpeedRange;
                float bonus=p->speedBonus;
                p->speedBonus=lbl_806DA3F4;
                p->inSpeedRange=0;
                if (p->playerDistance < radius2) {
                    ++count;
                    if (!old) state[i]=2; else state[i]=1;
                    if (lbl_806DA3F4 != bonus) state[i]=2;
                    p->inSpeedRange=1;
                }
            }
        }
        if (count > fn_801DCC94(mode)) {
            float bonus=fn_801DCC6C(mode);
            for (int i=0;i<8;++i) {
                FramePairRecord *p=&FramePairs()[i];
                if (p && state[i]==2) p->speedBonus=bonus;
            }
        }
    } else {
        for (int i=0;i<8;++i) {
            FramePairRecord *p=&FramePairs()[i];
            if (p) p->speedBonus=lbl_806DA3F4;
        }
    }
}
