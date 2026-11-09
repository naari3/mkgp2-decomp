#include "game/DrawQuad8214Private.h"
#include "game/DrawQuad7F50MatchPrivate.h"

extern "C" {
#pragma force_active on
// GX descriptor pairs and four-word vertex attribute formats share this pool.
struct DrawFormatS56 { unsigned int words[4]; };
extern const unsigned int lbl_803BEDC0[8] = {9, 1, 11, 1, 255, 1, 0, 0};
static const unsigned int colorFlatS56[16] = {9, 0, 4, 0, 11, 1, 5, 0, 255, 1, 4, 0, 0, 0, 0, 0};
static const unsigned int colorDepthS56[16] = {9, 1, 4, 0, 11, 1, 5, 0, 255, 1, 4, 0, 0, 0, 0, 0};
static const unsigned int texDescS56[8] = {9, 1, 13, 1, 255, 1, 0, 0};
static const unsigned int texFlatS56[16] = {9, 0, 4, 0, 13, 1, 4, 0, 255, 1, 5, 0, 0, 0, 0, 0};
static const unsigned int texDepthS56[16] = {9, 1, 4, 0, 13, 1, 4, 0, 255, 1, 5, 0, 0, 0, 0, 0};
static const unsigned int mixDescS56[8] = {9, 1, 11, 1, 13, 1, 255, 1};
static const DrawFormatS56 mixFlatS56[8] = {
        {{9, 0, 4, 0}},
        {{11, 1, 5, 0}},
        {{13, 1, 4, 0}},
        {{255, 1, 4, 0}},
        {{9, 0, 4, 0}},
        {{11, 1, 5, 0}},
        {{13, 1, 4, 0}},
        {{255, 1, 4, 0}}
    };
static const DrawFormatS56 mixDepthS56[8] = {
        {{9, 1, 4, 0}},
        {{11, 1, 5, 0}},
        {{13, 1, 4, 0}},
        {{255, 1, 4, 0}},
        {{9, 1, 4, 0}},
        {{11, 1, 5, 0}},
        {{13, 1, 4, 0}},
        {{255, 1, 4, 0}}
    };
#pragma force_active reset

void GXSetNumTexGens(int); void GXSetNumChans(int); void GXSetNumTevStages(int);
void GXSetTexCoordGen2(int,int,int,int,int,int);
void GXSetTevOrder(int,int,int,int); void GXSetTevOp(int,int);
void GXSetTevColorIn(int,int,int,int,int); void GXSetTevColorOp(int,int,int,int,int,int);
void GXSetTevAlphaIn(int,int,int,int,int); void GXSetTevAlphaOp(int,int,int,int,int,int);
void GXClearVtxDesc(); void GXSetVtxDescv(const void *); void GXSetVtxAttrFmtv(int,const void *);
}
extern "C" {

void fn_801F8250(DrawNode801F *self) {
    int offset;
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 60, 0, 125);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    switch (self->mode) {
    case 1:
        GXSetTevColorIn(0,8,9,11,10);
        GXSetTevColorOp(0,0,0,0,1,0);
        break;
    case 2:
        GXSetTevColorIn(0,15,15,11,10);
        GXSetTevColorOp(0,0,0,0,1,0);
        GXSetTevAlphaIn(0,7,4,5,7);
        GXSetTevAlphaOp(0,0,0,0,1,0);
        break;
    default:
        GXSetTevOp(0,0);
        break;
    }
    GXSetTevOrder(0,0,7,4);
    GXClearVtxDesc();
    offset = 0;
    if (self->mode == 1 || self->mode == 2) offset = 4;
    GXSetVtxDescv(mixDescS56);
    if (self->depth) {
        GXSetVtxAttrFmtv(0,&mixDepthS56[offset]);
    } else {
        GXSetVtxAttrFmtv(0,&mixFlatS56[offset]);
    }
}


static inline void DrawPositionDepth8404(float x, float y, const DrawDesc801F *description) {
    float z = description->z;
    DrawPositionDepth801F(x, y, z);
}
void fn_801F8404(DrawNode801F *self) {
    DrawQuadLocal8214 quad(self->description);
    GXBegin(128,0,4);
    if (!self->depth) {
        DrawPosition801F(quad.x0,quad.y0);
        DrawUV801F(self->description->u0,self->description->v0);
        DrawPosition801F(quad.x1,quad.y1);
        DrawUV801F(self->description->u0,self->description->v1);
        DrawPosition801F(quad.x2,quad.y2);
        DrawUV801F(self->description->u1,self->description->v1);
        DrawPosition801F(quad.x3,quad.y3);
        DrawUV801F(self->description->u1,self->description->v0);
    } else {
        DrawPositionDepth8404(quad.x0,quad.y0,self->description);
        DrawUV801F(self->description->u0,self->description->v0);
        DrawPositionDepth8404(quad.x1,quad.y1,self->description);
        DrawUV801F(self->description->u0,self->description->v1);
        DrawPositionDepth8404(quad.x2,quad.y2,self->description);
        DrawUV801F(self->description->u1,self->description->v1);
        DrawPositionDepth8404(quad.x3,quad.y3,self->description);
        DrawUV801F(self->description->u1,self->description->v0);
    }
}


#pragma exceptions on
void fn_801F8668(DrawNode801F *self) {
    const unsigned char *tables = (const unsigned char *)lbl_803BEDC0;
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 60, 0, 125);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 7, 255);
    GXSetTevOp(0, 3);
    GXClearVtxDesc();
    GXSetVtxDescv((const void *)(tables + 0xA0));
    if (self->depth) {
        GXSetVtxAttrFmtv(0, (const void *)(tables + 0x100));
    } else {
        GXSetVtxAttrFmtv(0, (const void *)(tables + 0xC0));
    }
}
#pragma exceptions reset


static inline void DrawPositionDepth8728(float x, float y, const DrawDesc801F *description) {
    float z = description->z;
    DrawPositionDepth801F(x, y, z);
}
#pragma push
#pragma opt_common_subs off
void fn_801F8728(DrawNode801F *self) {
    DrawQuad7F50 quad(self->description);  /* same quad as fn_801F7F50 */
    GXBegin(128,0,4);
    if (!self->depth) {
        DrawPosition801F(quad.x0,quad.y0);
        DrawColor801F(self->description->colors[0]);
        DrawPosition801F(quad.x1,quad.y1);
        DrawColor801F(self->description->colors[1]);
        DrawPosition801F(quad.x2,quad.y2);
        DrawColor801F(self->description->colors[2]);
        DrawPosition801F(quad.x3,quad.y3);
        DrawColor801F(self->description->colors[3]);
    } else {
        DrawPositionDepth8728(quad.x0,quad.y0,self->description);
        DrawColor801F(self->description->colors[0]);
        DrawPositionDepth8728(quad.x1,quad.y1,self->description);
        DrawColor801F(self->description->colors[1]);
        DrawPositionDepth8728(quad.x2,quad.y2,self->description);
        DrawColor801F(self->description->colors[2]);
        DrawPositionDepth8728(quad.x3,quad.y3,self->description);
        DrawColor801F(self->description->colors[3]);
    }
}
#pragma pop



#pragma exceptions on
void fn_801F894C(DrawNode801F *self) {
    GXSetNumTexGens(0);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 255, 255, 4);
    GXSetTevOp(0, 4);
    GXClearVtxDesc();
    GXSetVtxDescv(lbl_803BEDC0);
    if (self->depth) {
        GXSetVtxAttrFmtv(0, colorDepthS56);
    } else {
        GXSetVtxAttrFmtv(0, colorFlatS56);
    }
}
#pragma exceptions reset

}
