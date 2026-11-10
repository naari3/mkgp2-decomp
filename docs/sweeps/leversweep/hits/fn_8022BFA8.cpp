/* Native reconstruction of 0x8022BFA8; retained NonMatching (86.82437%). */
#include "game/EnemyFaceDraw_private.h"
union FaceDrawPipe { float f32; unsigned int u32; };
#define FIFO (*(volatile FaceDrawPipe *)0xCC008000)
extern "C" {
extern const unsigned char EnmyFaceEffect_rodata_803DA710[0x710];
extern const float lbl_806D6DE4, lbl_806D6DE8;
extern const float lbl_806DB5E0, lbl_806DB5E8, lbl_806DB5EC, lbl_806DB5F0, lbl_806DB5F4;
void GXSetCullMode(int); void GXClearVtxDesc();
void GXSetVtxDesc(int,int); void GXSetVtxAttrFmt(int,int,int,int,int);
void GXSetNumChans(int); void GXSetChanCtrl(int,int,int,int,int,int,int);
void GXSetNumTevStages(int); void GXSetBlendMode(int,int,int,int);
void GXSetTevOrder(int,int,int,int); void GXSetTevOp(int,int);
void GXSetNumTexGens(int); void GXSetTexCoordGen2(int,int,int,int,int,int);
void GXSetCurrentMtx(int); void GXLoadPosMtxImm(FaceMtx,int);
void GXBegin(int,int,int); void HSD_StateInvalidate(int);
void *GetCourseScene3D(); void HSD_CObjGetViewingMtx(void *,FaceMtx);
float (*CObj_GetProjMatrix_Cached(void *))[4];
void CObj_LoadProjMatrix(void *,FaceDrawVec *);
void PSMTXScale(FaceMtx,float,float,float); void PSMTXTrans(FaceMtx,float,float,float);
void PSMTXCopy(const float (*)[4],FaceMtx);
void PSMTXConcat(const float (*)[4],const float (*)[4],FaceMtx);
void PSMTXMultVec(const float (*)[4],const FaceDrawVec *,FaceDrawVec *);
void Vec3_Normalize(FaceDrawVec *,FaceDrawVec *);
unsigned char fn_8011D890(int,float *,float *);
void DebugPrintf(const char *,...);
void Object_SetAnimBinding(void *,FaceMtx,int);
void Object_SetField8_AndDirty(void *,float);
void clNormal3D_Exec(void *); void Object_DriveAnimMatrix(void *);
void Object_RenderJObjTree(void *,int);
}

static inline void FillFaceUV(float *uv, const float *rect) {
    float mid = lbl_806DB5EC * (rect[3] - rect[1]) + rect[1];
    uv[0]=rect[0]; uv[1]=mid; uv[2]=rect[2]; uv[3]=mid;
    uv[4]=rect[2]; uv[5]=rect[1]; uv[6]=rect[0]; uv[7]=rect[1];
    uv[8]=rect[0]; uv[9]=rect[3]; uv[10]=rect[2]; uv[11]=rect[3];
    uv[12]=rect[2]; uv[13]=mid; uv[14]=rect[0]; uv[15]=mid;
}

/* Keep each vertex attribute write together; snapshot displacement after GXBegin. */
static inline void WriteFaceVertex(FaceDrawVec *p, float *uv, float x, float z, unsigned int color) {
    FIFO.f32=x+p->x; FIFO.f32=p->y; FIFO.f32=z+p->z;
    FIFO.u32=color; FIFO.f32=uv[0]; FIFO.f32=uv[1];
}
static inline void WriteFaceVertexPlain(FaceDrawVec *p, float *uv, unsigned int color) {
    FIFO.f32=p->x; FIFO.f32=p->y; FIFO.f32=p->z;
    FIFO.u32=color; FIFO.f32=uv[0]; FIFO.f32=uv[1];
}
static inline void DrawFaceQuad(FaceDrawVec *p, float *uv, FaceDrawVec *offset, unsigned int color) {
    GXBegin(0x80,0,4);
    float x=offset->x, z=offset->z;
    WriteFaceVertex(p,uv,x,z,color);
    WriteFaceVertex(p+1,uv+2,x,z,color);
    WriteFaceVertex(p+2,uv+4,x,z,color);
    WriteFaceVertex(p+3,uv+6,x,z,color);
}
static inline void DrawFaceQuadCached(FaceDrawVec *p, float *uv, FaceDrawVec *offset, unsigned int color) {
    DrawFaceQuad(p,uv,offset,color);
}
static inline void DrawFaceQuadPlain(FaceDrawVec *p, float *uv, FaceDrawVec *offset, unsigned int color) {
    GXBegin(0x80,0,4);
    WriteFaceVertexPlain(p,uv,color);
    WriteFaceVertexPlain(p+1,uv+2,color);
    WriteFaceVertexPlain(p+2,uv+4,color);
    WriteFaceVertexPlain(p+3,uv+6,color);
}

extern "C" void fn_8022BFA8(FaceDrawModel *self) {
    float mid;
    const unsigned char *data=EnmyFaceEffect_rodata_803DA710;
    FaceDrawVec vertices[8];
    FaceMtx world[2], view, temporary, scale, translation, projection;
    float uv[16];
    FaceMtx copy;
    float rect[4];
    FaceDrawVec offset, eye;
    FaceDrawVec *out, *q, *draw;
    const FaceDrawVec *src, *p;
    FaceMtx *matrix;
    float *tex;
    int i, j;
    if (!self->kart) return;
    if (self->scale <= lbl_806DB5E0) {
        if (self->sub->anim == 0) {
            if (++self->timer >= 160) self->sub->finished=1;
        } else if (self->sub->anim == 1) {
            if (++self->timer >= 360) self->sub->finished=1;
        }
        return;
    }
    GXSetCullMode(0); GXClearVtxDesc();
    GXSetVtxDesc(9,1); GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetVtxDesc(11,1); GXSetVtxAttrFmt(0,11,0,5,0);
    GXSetVtxDesc(13,1); GXSetVtxAttrFmt(0,13,1,4,0);
    GXSetNumChans(1); GXSetChanCtrl(4,0,1,1,0,0,2);
    GXSetNumTevStages(1); GXSetBlendMode(1,4,5,0);
    GXSetTevOrder(0,0,0,4); GXSetTevOp(0,0);
    GXSetNumTexGens(1); GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    GXSetCurrentMtx(0);
    HSD_CObjGetViewingMtx(*(void **)((char *)GetCourseScene3D()+4),view);
    GXLoadPosMtxImm(view,0);
    PSMTXScale(scale,self->scale*lbl_806D6DE4,self->scale*lbl_806D6DE8,self->scale);
    PSMTXTrans(translation,self->x,self->y,self->z);
    PSMTXCopy(CObj_GetProjMatrix_Cached(GetCourseScene3D()),projection);
    projection[2][3]=lbl_806DB5E0; projection[1][3]=lbl_806DB5E0; projection[0][3]=lbl_806DB5E0;
    PSMTXConcat(projection,scale,scale);
    PSMTXConcat(scale,self->sub->m[0],world[0]);
    PSMTXConcat(translation,world[0],world[0]);
    PSMTXConcat(scale,self->sub->m[1],world[1]);
    PSMTXConcat(translation,world[1],world[1]);
    offset.z=lbl_806DB5E0; offset.y=lbl_806DB5E0; offset.x=lbl_806DB5E0;
    void *scene=GetCourseScene3D();
    if (scene) {
        CObj_LoadProjMatrix(scene,&eye);
        offset.x=eye.x-self->x; offset.z=eye.z-self->z;
        Vec3_Normalize(&offset,&offset);
        offset.x*=lbl_806DB5E8; offset.z*=lbl_806DB5E8;
    }
    if (self->left>0) {
        draw=vertices;
        out=draw;
        src=(const FaceDrawVec *)(data+0x4a4);
        matrix=world;
        for (i=0;i<2;++i) {
            q=out;
            p=src;
            for (j=0;j<4;++j) { PSMTXMultVec(*matrix,p,q); ++p; ++q; }
            src+=4; ++matrix; out+=4;
        }
        if (!fn_8011D890(self->left,rect,0)) {
            DebugPrintf((const char *)data+0x6ec,0x5e2);
            HSD_StateInvalidate(0x7e); return;
        }
        FillFaceUV(uv,rect);
        tex=uv;
        for (i=0;i<2;++i) { DrawFaceQuadPlain(draw,tex,&offset,0xffffffff); tex+=8; draw+=4; }
    }
    if (self->right>0) {
        draw=vertices;
        out=draw;
        src=(const FaceDrawVec *)(data+0x5c4);
        matrix=world;
        for (i=0;i<2;++i) {
            q=out;
            p=src;
            for (j=0;j<4;++j) { PSMTXMultVec(*matrix,p,q); ++p; ++q; }
            src+=4; ++matrix; out+=4;
        }
        fn_8011D890(self->right,rect,0);
        FillFaceUV(uv,rect);
        tex=uv;
        for (i=0;i<2;++i) { DrawFaceQuad(draw,tex,&offset,0xffffffff); tex+=8; draw+=4; }
    }
    FaceDrawVec *vertexBase=vertices;
    float *uvBase;
    const FaceDrawVec *alternateBase=(const FaceDrawVec *)(data+0x624);
    const FaceDrawVec *normal=(const FaceDrawVec *)(data+0x4a4);
    const FaceDrawVec *alternate=alternateBase;
    const FaceDrawVec *standard=(const FaceDrawVec *)(data+0x564);
    out=vertexBase;
    matrix=world;
    for (i=0;i<2;++i) {
        q=out;
        const FaceDrawVec *n=normal, *a=alternate, *s=standard;
        for (j=0;j<4;++j) {
            if (self->left<0) PSMTXMultVec(*matrix,n,q);
            else if (self->variant==1) PSMTXMultVec(*matrix,a,q);
            else PSMTXMultVec(*matrix,s,q);
            ++n; ++a; ++s; ++q;
        }
        normal+=4; alternate+=4; standard+=4; ++matrix; out+=4;
    }
    fn_8011D890(self->face,rect,0);
    uvBase=uv;
    mid = lbl_806DB5EC * (rect[3] - rect[1]) + rect[1];
    uvBase[0]=rect[0];
    uvBase[1]=mid;
    uvBase[2]=rect[2];
    uvBase[3]=mid;
    uvBase[4]=rect[2];
    uvBase[5]=rect[1];
    uvBase[6]=rect[0];
    uvBase[7]=rect[1];
    uvBase[8]=rect[0];
    uvBase[9]=rect[3];
    uvBase[10]=rect[2];
    uvBase[11]=rect[3];
    uvBase[12]=rect[2];
    uvBase[13]=mid;
    uvBase[14]=rect[0];
    uvBase[15]=mid; offset.x+=offset.x; offset.z+=offset.z;
    draw=vertexBase;
    tex=uvBase;
    for (i=0;i<2;++i) { DrawFaceQuad(draw,tex,&offset,0xffffffff); tex+=8; draw+=4; }
    if (self->kart->state==0) {
        p=(const FaceDrawVec *)(data+0x684);
        q=vertexBase;
        for (i=0;i<4;++i) { PSMTXMultVec(world[0],p,q); ++p; ++q; }
        fn_8011D890(((const int *)(data+0x444))[9],rect,0);
        uvBase[0]=rect[0]; uvBase[1]=rect[3]; uvBase[2]=rect[2]; uvBase[3]=rect[3];
        uvBase[4]=rect[2]; uvBase[5]=rect[1]; uvBase[6]=rect[0]; uvBase[7]=rect[1];
        offset.x+=offset.x; offset.z+=offset.z;
        DrawFaceQuad(vertexBase,uvBase,&offset,0xffffffff);
    }
    int overlay=self->sub->overlay;
    if (overlay!=-1) {
        FaceDrawVec *dstRow=vertexBase;
        const FaceDrawVec *srcRow=alternateBase;
        for (i=0;i<2;++i) {
            PSMTXCopy(self->sub->m[i],copy);
            Vec3c localOffset;
            localOffset=self->sub->offset;
            copy[0][3]+=localOffset.value.x; copy[1][3]+=localOffset.value.y; copy[2][3]+=localOffset.value.z;
            PSMTXConcat(scale,copy,temporary);
            PSMTXConcat(translation,temporary,temporary);
            q=dstRow;
            p=srcRow;
            for (j=0;j<4;++j) { PSMTXMultVec(temporary,p,q); ++p; ++q; }
            dstRow+=4; srcRow+=4;
        }
        fn_8011D890(((const int *)(data+0x444))[overlay],rect,0);
        offset.x+=offset.x; offset.z+=offset.z;
        FillFaceUV(uvBase,rect);
        unsigned int color=0xffffff00;
        color=(color&~0xff)|((int)(lbl_806DB5F0*self->sub->alpha)&0xff);
        draw=vertexBase;
        tex=uvBase;
        for (i=0;i<2;++i) { DrawFaceQuadCached(draw,tex,&offset,color); tex+=8; draw+=4; }
    }
    HSD_StateInvalidate(0x7e); GXSetCullMode(2);
    int anim=self->sub->anim;
    if (anim!=-1) {
        float frame=++self->timer;
        if (anim==0) frame+=lbl_806DB5F4;
        PSMTXConcat(projection,self->sub->animMtx,temporary);
        PSMTXConcat(translation,temporary,temporary);
        Object_SetAnimBinding(self->models[anim],temporary,0);
        Object_SetField8_AndDirty(self->models[anim],frame);
        if (anim==0) {
            clNormal3D_Exec(self->models[anim]);
            if (self->timer>=160) self->sub->finished=1;
        } else if (anim==1) {
            clNormal3D_Exec(self->models[anim]);
            if (self->timer>=360) self->sub->finished=1;
        }
        Object_DriveAnimMatrix(self->models[anim]);
        Object_RenderJObjTree(self->models[anim],7);
    }
}

