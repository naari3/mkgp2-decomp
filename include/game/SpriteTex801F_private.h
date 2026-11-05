#ifndef SPRITE_TEX_801F_PRIVATE_H
#define SPRITE_TEX_801F_PRIVATE_H
#include "game/DrawQuad801F.h"
struct SpriteTex801F : DrawDesc801F {
    int blend, src, dst, logic;
    float matrix[3][4];
};
struct TextureEntry801F { char pad[0x30]; unsigned short width,height; char tail[0x10]; };
struct TextureBank801F { void *p0,*palette,*p8; unsigned int count; TextureEntry801F *textures; };
struct TextureOwner801F { TextureBank801F *bank; };
struct TextureRect801F { float x,y,width,height; };
extern "C" {
extern const float lbl_806DA710, lbl_806DA728, lbl_806DA72C, lbl_806DA730;
extern char lbl_803BF050[], lbl_803BF05C[];
void __assert(const char *,int,const char *);
void PSMTXScale(float [3][4],float,float,float);
void PSMTXTransApply(const float [3][4],float [3][4],float,float,float);
void GXLoadTexMtxImm(const float [3][4],int,int);
void fn_801F6574(float *,float *);
double sin(double); double cos(double);
}
static inline void LoadSpriteMatrix801F(SpriteTex801F *s) {
    PSMTXScale(s->matrix,s->u1-s->u0,s->v0-s->v1,lbl_806DA710);
    PSMTXTransApply(s->matrix,s->matrix,s->u0,s->v1,lbl_806DA718);
    GXLoadTexMtxImm(s->matrix,30,1);
}
static inline void SelectSpriteTexture801F(TextureOwner801F *owner,SpriteTex801F *s,unsigned int index) {
    unsigned int count=owner->bank->count;
    if ((unsigned char)(index >= count) == 1) __assert(lbl_803BF050,0x476,lbl_803BF05C);
    unsigned int last=count-1;
    while(index>=count) index=last;
    s->i14=index;
    TextureEntry801F *entries=owner->bank->textures;
    s->h18=entries[s->i14].width;
    s->h1A=entries[s->i14].height;
    float w=s->h18;
    float h=s->h1A;
    float invW=lbl_806DA710 / s->h18;
    float invH=lbl_806DA710 / s->h1A;
    s->width=w;
    s->height=h;
    s->u0=lbl_806DA714 * invW;
    s->u1=invW*((lbl_806DA718+w)-lbl_806DA714);
    s->v1=lbl_806DA714 * invH;
    s->v0=invH*((lbl_806DA718+h)-lbl_806DA714);
    LoadSpriteMatrix801F(s);
}
#endif
