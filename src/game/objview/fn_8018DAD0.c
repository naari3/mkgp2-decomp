typedef struct Vec3 { float x,y,z; } Vec3;
typedef struct Joint { char pad[0x38]; Vec3 pos; } Joint;
typedef struct Emitter { Joint *joint; unsigned char delay, burst; char pad[2]; } Emitter;
typedef struct Particle {
    unsigned char type; char pad[3]; Vec3 pos;
    float age, scale, speed, frequency, amplitude, offset, alpha;
} Particle;
typedef struct Owner { void *vt; Emitter *emitters; int count; void *models; Particle *parts; int rand64, rand48; } Owner;
extern const char lbl_80377F70[];
extern const float lbl_806D93F0, lbl_806D93F8, lbl_806D940C, lbl_806D9410, lbl_806D9414, lbl_806D9418, lbl_806D941C;
extern const float lbl_80495994[64], lbl_80495A94[48];
extern char lbl_806D93FC[7], lbl_806D9404[5];
extern void *GetCourseScene3D(void);
extern void CObj_LoadProjMatrix(void *, Vec3 *);
extern void Vec3_Subtract(const Vec3 *, const Vec3 *, Vec3 *);
extern float PSVECSquareMag(const Vec3 *);
extern float LUT_Sin12Bit(float);
extern void __assert(char *,int,char *);
extern unsigned char fn_8016C360(int);
extern void SoundMgr_PlaySE(int);
extern void fn_8016C288(int,const Vec3 *);
static inline Particle *FreeParticle(Owner *o) {
    int i;
    for(i=0;i<60;i++) if(o->parts[i].type==3) return &o->parts[i];
    return 0;
}
void fn_8018DAD0(Owner *o) {
    void *camera;
    Vec3 eye, pos, delta, nearest;
    float zero, best, dist, r;
    int i;
    Emitter *e;
    Particle *p;
    const char *data=lbl_80377F70;
    if (!o->count) return;
    camera=GetCourseScene3D();
    if (!camera) return;
    CObj_LoadProjMatrix(camera,&eye);
    nearest=*(const Vec3 *)(data+0x9c);
    best=lbl_806D93F8;
    zero=lbl_806D93F0;
    for(i=0;i<o->count;i++) {
        Joint *joint;
        e=&o->emitters[i];
        joint=e->joint;
        if(!joint) __assert(lbl_806D93FC,0x3e4,lbl_806D9404);
        pos.x=joint->pos.x; pos.y=joint->pos.y; pos.z=joint->pos.z;
        Vec3_Subtract(&pos,&eye,&delta);
        dist=PSVECSquareMag(&delta);
        if(best<zero || dist<best) { best=dist; nearest.x=pos.x; nearest.y=pos.y; nearest.z=pos.z; }
        if(e->delay) { e->delay--; continue; }
        if (!(dist<lbl_806D940C)) continue;
        p=FreeParticle(o);
        if(!p) continue;
        if(++o->rand64>=64) o->rand64=0;
        r=lbl_806D9410*lbl_80495994[o->rand64]-lbl_806D9414;
        p->pos.x=pos.x; p->pos.y=pos.y; p->pos.z=pos.z;
        if(++o->rand48>=48) o->rand48=0;
        p->type=(int)(lbl_806D9418*lbl_80495A94[o->rand48]);
        p->age=lbl_806D93F0;
        p->scale=r*((const float *)(data+0x3c))[p->type]+((const float *)(data+0x3c))[p->type];
        p->speed=r*((const float *)(data+0x48))[p->type]+((const float *)(data+0x48))[p->type];
        p->frequency=((const float *)(data+0x54))[p->type]-r*((const float *)(data+0x54))[p->type];
        p->amplitude=((const float *)(data+0x60))[p->type]-r*((const float *)(data+0x60))[p->type];
        p->offset=lbl_806D93F0;
        p->alpha=lbl_806D941C;
        e->burst++;
        if(e->burst>=15) { e->burst=0; e->delay=60; }
        else e->delay=10;
    }
    if(!fn_8016C360(0x38)) SoundMgr_PlaySE(0x38);
    fn_8016C288(0x38,&nearest);
    for(i=0;i<60;i++) {
        float start;
        p=&o->parts[i];
        if(p->type==3) continue;
        p->pos.y+=p->speed;
        p->offset=p->amplitude*LUT_Sin12Bit(p->age*p->frequency);
        start=((const float *)(data+0x6c))[p->type];
        if(p->age<start) p->alpha=lbl_806D941C;
        else p->alpha=lbl_806D941C-(p->age-start)/(((const float *)(data+0x78))[p->type]-start);
        { float age=p->age+lbl_806D941C;
        p->age=age;
        if(age>=((const float *)(data+0x78))[p->type]) p->type=3; }
    }
}
