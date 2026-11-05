#include "game/AIFramePrivate.h"
static inline void UpdateFlags(AIFrameOwner *self, AISpeedRender *player, int waypoint) {
    self->flag18 = 0;
    if (player->rank == 0) {
        AISpeedRender *driver=0;
        AIPairRecord *p=lbl_806793D8;
        for (int i=0;i<8;++i,++p) {
            if (p && p->driver && ((AISpeedRender *)p->driver)->rank == 1) {
                driver=(AISpeedRender *)p->driver; break;
            }
        }
        if (driver) {
            int count=Path_GetTotalCount(g_pathSystem);
            int a=waypoint+(g_totalLaps-player->lap)*count;
            int b=p->waypoint+(g_totalLaps-driver->lap)*count;
            fn_801DE1B0();
            if (fn_801DE074() <= lbl_806DA3E0*(float)a-lbl_806DA3E0*(float)b) self->flag18=1;
        }
    }
    self->flag19 = 0;
    if (player->rank == 5) {
        AISpeedRender *driver=0;
        AIPairRecord *p=lbl_806793D8;
        for (int i=0;i<8;++i,++p) {
            if (p && p->driver && ((AISpeedRender *)p->driver)->rank == 4) {
                driver=(AISpeedRender *)p->driver; break;
            }
        }
        if (driver) {
            int count=Path_GetTotalCount(g_pathSystem);
            int a=waypoint+(g_totalLaps-player->lap)*count;
            int b=p->waypoint+(g_totalLaps-driver->lap)*count;
            fn_801DE1B0();
            if (fn_801DDF8C() <= lbl_806DA3E0*(float)b-lbl_806DA3E0*(float)a) self->flag19=1;
        }
    }
}
extern "C" void AI_UpdatePerFrameState(AIFrameOwner *self) {
    int maxFrames = lbl_806D1920;
    ++self->frame;
    if (maxFrames < self->frame) self->frame=maxFrames;
    AISpeedRender *player = CarObject_GetRenderObj(self->car);
    float *mtx = KartDriver_GetKartRootMtx(player);
    float px=mtx[3],py=mtx[7],pz=mtx[11];
    for (int i=0;i<8;++i) {
        AIPairRecord *p=&lbl_806793D8[i];
    if (p && p->driver) {
        AISpeedRender *driver = (AISpeedRender *)p->driver;
        float *mtx = KartDriver_GetKartRootMtx(driver);
        float z, y, x;
        x=mtx[3]; y=mtx[7]; z=mtx[11];
        p->field08 = (void *)(driver->rank - player->rank);
        p->waypoint = Waypoint_FindNearest(g_pathSystem, 0, x,y,z,lbl_806DA3E8);
        p->nearestKart = -1;
        p->nearestDriver = 0;
        p->distanceSquared = lbl_806DA3EC;
        p->distanceSquared *= p->distanceSquared;
        p->distanceSquared *= lbl_806DA3F0;
        Vec pos; pos.x=x;pos.y=y;pos.z=z;
        for (int j=0;j<8;++j) {
            AIPairRecord *other = &lbl_806793D8[j];
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
        PlayerDistance(p)=dx*dx+dz*dz;
    }
    }
    int waypoint;
    if (self->selectedKart < 0) waypoint=Waypoint_FindNearest(g_pathSystem,0,px,py,pz,lbl_806DA3E8);
    else waypoint=lbl_806793D8[self->selectedKart].waypoint;
    {
        int nearest=-1;
        AIFramePosition pos(mtx[3],mtx[7],mtx[11]);
        float distance=lbl_806DA414;
        for (int i=0;i<8;++i) {
            AIPairRecord *p=&lbl_806793D8[i];
            if (p && p->driver && p->driver != player && p->field1C >= 0) {
                float *m=KartDriver_GetKartRootMtx(p->driver);
                Vec v;
                float y=m[7],x=m[3],z=m[11];
                v.x=x;v.y=y;v.z=z;
                v.x-=pos.x;v.y-=pos.y;v.z-=pos.z;
                float d=(v.x*v.x+v.y*v.y)+v.z*v.z;
                if (d <= distance) { nearest=i;distance=d; }
            }
        }
        if (nearest >= 0) {
            AIPairRecord *p=&lbl_806793D8[nearest];
            int round=g_roundIndex,cup=g_cupId;
            struct Tuning { char pad[0x18];float duration; };
            Tuning *t=(Tuning *)GetKartTuningGPSpeedParams(GetEnemyParam(),cup,round,nearest);
            if (p->field1C == 0) p->field1C=(int)(lbl_806DA40C*t->duration);
            p->field20=distance;
        } else {
            for (int i=0;i<8;++i) {
                AIPairRecord *p=&lbl_806793D8[i];
                if (p->field1C > 0) p->field1C=0;
                p->field20=lbl_806DA3F4;
            }
        }
    }
    UpdateFlags(self,player,waypoint);
    int mode=fn_801DCCE4();
    if (mode >= 0) {
        int count=0;
        float radius=fn_801DCCBC();
        float radius2=radius*radius;
        int state[8];
        for (int i=0;i<8;++i) {
            AIPairRecord *p=&lbl_806793D8[i];
            state[i]=0;
            if (p && p->driver) {
                unsigned char old=InSpeedRange(p);
                float bonus=p->speedBonus;
                p->speedBonus=lbl_806DA3F4;
                InSpeedRange(p)=0;
                if (PlayerDistance(p) < radius2) {
                    ++count;
                    if (!old) state[i]=2; else state[i]=1;
                    if (lbl_806DA3F4 != bonus) state[i]=2;
                    InSpeedRange(p)=1;
                }
            }
        }
        if (count > fn_801DCC94(mode)) {
            float bonus=fn_801DCC6C(mode);
            for (int i=0;i<8;++i) {
                AIPairRecord *p=&lbl_806793D8[i];
                if (p && state[i]==2) p->speedBonus=bonus;
            }
        }
    } else {
        for (int i=0;i<8;++i) {
            AIPairRecord *p=&lbl_806793D8[i];
            if (p) p->speedBonus=lbl_806DA3F4;
        }
    }
}
