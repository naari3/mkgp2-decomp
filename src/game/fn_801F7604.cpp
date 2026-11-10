/*
 * Sprite/quad draw nodes, 0x801F7604..0x801F89F0 (one original TU; it most
 * likely starts earlier, see docs/gave_up.md "Data layout / TU split").
 * Merged from fn_801F7604.cpp, dtor_801F7A74.c, dtor_801F7AD0.c,
 * fn_801F7B2C.c, fn_801F7B74.c, GX_BeginDraw.c, GX_EndDraw.c,
 * fn_801F7CD8.cpp, fn_801F7D50.cpp, fn_801F7DAC.cpp, fn_801F7E98.cpp,
 * fn_801F7F50.cpp, dtor_801F8214.cpp and dtor_801F8214_nm1.cpp: fn_801F7604
 * and fn_801F8250..fn_801F894C address the same .rodata pool
 * (0x803BEDC0..0x803BF020) through its section anchor.
 */

#include "game/SpriteTex801F_private.h"
extern "C" {
extern void *lbl_804E5538[],*lbl_804E5578[],*lbl_804E5558[],*lbl_804E5524[];
extern unsigned char lbl_806D1968;
struct CachedDraw801F { int mode; TextureEntry801F *texture; };
extern CachedDraw801F lbl_806D196C;
// GX descriptor pairs and four-word vertex attribute formats share this pool.
struct DrawFormatS56 { unsigned int words[4]; };
#pragma force_active on
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
void GXSetBlendMode(int,int,int,int);
void GXSetNumTexGens(int); void GXSetNumChans(int); void GXSetNumTevStages(int);
void GXSetTevOrder(int,int,int,int); void GXSetTevOp(int,int);
void GXClearVtxDesc(); void GXSetVtxDescv(const void *); void GXSetVtxAttrFmtv(int,const void *);
void GXSetTexCoordGen2(int,int,int,int,int,int);
struct PaletteEntry801F { void *texture; void *tlut; };
PaletteEntry801F *TEXGetPaletteEntry(void *,unsigned int);
void GXLoadTexObj(void *,int); void GXLoadTlut(void *,int);
void GXSetTevColorIn(int,int,int,int,int); void GXSetTevColorOp(int,int,int,int,int,int);
void GXSetTevAlphaIn(int,int,int,int,int); void GXSetTevAlphaOp(int,int,int,int,int,int);
void fn_801F8728(DrawNode801F *); void fn_801F8404(DrawNode801F *); void fn_801F7F50(DrawNode801F *);
}
struct DrawBaseS56 {
    void *vt; SpriteTex801F *desc; unsigned char depth;
    DrawBaseS56(SpriteTex801F *d,unsigned char z) {vt=lbl_804E5538;desc=d;depth=z;}
    ~DrawBaseS56(){vt=lbl_804E5538;}
};
struct ColorDrawS56:DrawBaseS56 {
    ColorDrawS56(SpriteTex801F *d,unsigned char z):DrawBaseS56(d,z){vt=lbl_804E5578;}
    ~ColorDrawS56(){vt=lbl_804E5578;}
};
struct TexDrawS56:DrawBaseS56 {
    TexDrawS56(SpriteTex801F *d,unsigned char z):DrawBaseS56(d,z){vt=lbl_804E5558;}
    ~TexDrawS56(){vt=lbl_804E5558;}
};
struct MixDrawS56:DrawBaseS56 {
    int mode;
    MixDrawS56(SpriteTex801F *d,unsigned char z):DrawBaseS56(d,z){vt=lbl_804E5524;mode=d->i2C;}
    ~MixDrawS56(){vt=lbl_804E5524;}
};
static inline void SetMixFormatS56(MixDrawS56 *node) {
    int offset=0;
    if(node->mode==1 || node->mode==2) offset=4;
    GXSetVtxDescv(mixDescS56);
    if(node->depth) { const DrawFormatS56 *table=mixDepthS56; GXSetVtxAttrFmtv(0,&table[offset]); }
    else { const DrawFormatS56 *table=mixFlatS56; GXSetVtxAttrFmtv(0,&table[offset]); }
}
static inline TextureEntry801F *GetTextureEntriesS56(const TextureBank801F *bank) { return bank->textures; }
static inline void LoadTextureS56(TextureOwner801F *owner,SpriteTex801F *s) {
    TextureBank801F *bank=owner->bank;
    TextureEntry801F *entries=GetTextureEntriesS56(bank);
    if(lbl_806D196C.texture!=&entries[s->i14]) {
        lbl_806D196C.texture=&entries[s->i14];
        PaletteEntry801F *entry=TEXGetPaletteEntry(bank->palette,s->i14);
        if(!entry->tlut) GXLoadTexObj(&entries[s->i14],7);
        else {GXLoadTlut((char *)&entries[s->i14]+0x20,0);GXLoadTexObj(&entries[s->i14],7);}
    }
}
extern "C" void fn_801F7604(TextureOwner801F *owner,SpriteTex801F *s) {
    unsigned char changed=0;
    if(lbl_806D196C.mode!=s->i2C){lbl_806D196C.mode=s->i2C;changed=1;}
    GXSetBlendMode(s->blend,s->src,s->dst,s->logic);
    if(lbl_806D196C.mode==4) {
        ColorDrawS56 node(s,lbl_806D1968);
        if(changed){
            GXSetNumTexGens(0);GXSetNumChans(1);GXSetNumTevStages(1);
            GXSetTevOrder(0,255,255,4);GXSetTevOp(0,4);
            GXClearVtxDesc();GXSetVtxDescv(lbl_803BEDC0);
            if(node.depth) GXSetVtxAttrFmtv(0,colorDepthS56);else GXSetVtxAttrFmtv(0,colorFlatS56);
        }
        fn_801F8728((DrawNode801F *)&node);
    } else {
        LoadTextureS56(owner,s);
        if(lbl_806D196C.mode==3) {
            TexDrawS56 node(s,lbl_806D1968);
            if(changed){
                GXSetNumTexGens(1);GXSetTexCoordGen2(0,1,4,60,0,125);
                GXSetNumChans(0);GXSetNumTevStages(1);GXSetTevOrder(0,0,7,255);GXSetTevOp(0,3);
                GXClearVtxDesc();GXSetVtxDescv(texDescS56);
                if(node.depth) GXSetVtxAttrFmtv(0,texDepthS56);else GXSetVtxAttrFmtv(0,texFlatS56);
            }
            fn_801F8404((DrawNode801F *)&node);
        } else {
            MixDrawS56 node(s,lbl_806D1968);
            if(changed){
                GXSetNumTexGens(1);GXSetTexCoordGen2(0,1,4,60,0,125);
                GXSetNumChans(1);GXSetNumTevStages(1);
                switch(node.mode){
                case 1: GXSetTevColorIn(0,8,9,11,10);GXSetTevColorOp(0,0,0,0,1,0);break;
                case 2: GXSetTevColorIn(0,15,15,11,10);GXSetTevColorOp(0,0,0,0,1,0);
                    GXSetTevAlphaIn(0,7,4,5,7);GXSetTevAlphaOp(0,0,0,0,1,0);break;
                default: GXSetTevOp(0,0);break;
                }
                GXSetTevOrder(0,0,7,4);GXClearVtxDesc();
                SetMixFormatS56(&node);
            }
            fn_801F7F50((DrawNode801F *)&node);
        }
    }
}

struct WeakDtorFlush801F7604 { int unused; };
extern "C" {

/* dtor_801F7A74 (~TexDrawS56), dtor_801F7AD0 (~ColorDrawS56) and fn_801F7B2C
 * (~DrawBaseS56) are the weak inline destructor copies of fn_801F7604. */
void fn_801F7B74(void *owner, char *self, float value) {
    *(float *)(self + 0x10) = value;
    fn_801F7604((TextureOwner801F *)owner, (SpriteTex801F *)self);
}

/*
 * GX_BeginDraw @ 0x801F7B98 (size 0x80).
 *
 * Singleton TU (extab_group=None per orchestrator, but eg=1: has its own
 * extab/extabindex entry -- emit via #pragma exceptions on / reset).
 *
 * Linear render-state setup: invokes seven Dolphin GX-ish helpers with
 * immediate args, then forwards 0xFFFFFFFF to the final teardown. All
 * callees take int args only, so CW emits a straight `li ; ... ; bl`
 * sequence with no spilling.
 *
 * lbl_806796FC: .bss object at 0x806796FC (size 0x4C). Loaded as
 * `lis r3, lbl@ha ; addi r3, r3, lbl@l` (non-sda, ha-pair). The
 * disassembler renders the negative @l as `subi r3, r3, 0x6904`.
 */

extern void GXSetChanCtrl(int, int, int, int, int, int, int);
extern void GXSetAlphaCompare(int, int, int, int, int);
extern void GXSetZCompLoc(int);
extern void GXSetZMode(int, int, int);
extern void fn_801F6790(void *);
extern void HSD_StateInvalidate(unsigned int);

extern char lbl_806796FC[];

#pragma exceptions on
void GX_BeginDraw(void) {
    GXSetChanCtrl(4, 1, 1, 1, 1, 2, 2);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZCompLoc(1);
    GXSetZMode(1, 3, 1);
    fn_801F6790(&lbl_806796FC);
    HSD_StateInvalidate(0xFFFFFFFF);
}
#pragma exceptions reset

/*
 * GX_EndDraw @ 0x801F7C18 (size 0xC0).
 *
 * Sibling of GX_BeginDraw (extab_group=None but eg=1: own extab/extabindex
 * entry, emitted via #pragma exceptions on / reset).
 *
 * Takes a single uint mode. Writes the low byte to a sbss flag, runs a
 * teardown helper, then dispatches GXSetZMode with two distinct
 * argument triples depending on whether mode is zero. The mode != 0 case is
 * the if-branch in source so CW lays it out before the zero branch with a
 * forward `beq` (matches target). Final block sequentially writes 5 and 0 to
 * two adjacent sdata words.
 *
 * lbl_806D1968 (sbss, 1 byte): mode flag.
 * lbl_806D196C (sbss, 0xC = three 4-byte slots): [0]=5, [1]=0 at exit.
 * lbl_806796FC (bss, 0x4C): shared with GX_BeginDraw, loaded via ha/lo pair.
 *
 * lbl_806D196C is the 8-byte CachedDraw801F {mode, texture} of this TU.
 */

extern void GXSetZCompLoc(int);
extern void GXSetZMode(int, int, int);
extern void fn_801F6804(void *);
extern void fn_801F6588(unsigned int);
extern void GXSetAlphaCompare(int, int, int, int, int);
extern void GXSetChanCtrl(int, int, int, int, int, int, int);

extern char lbl_806796FC[];

#pragma exceptions on
void GX_EndDraw(unsigned int mode) {
    lbl_806D1968 = (unsigned char)mode;
    GXSetZCompLoc(0);
    if (mode & 0xFF) {
        GXSetZMode(1, 3, 1);
    } else {
        GXSetZMode(0, 7, 1);
    }
    fn_801F6804(&lbl_806796FC);
    fn_801F6588(mode);
    GXSetAlphaCompare(4, 0, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    lbl_806D196C.mode = 5;
    lbl_806D196C.texture = 0;
}
#pragma exceptions reset
}

/* Holder destructor: deletes the owned object through its virtual destructor. */
class Owned801F7CD8 {
public:
    virtual ~Owned801F7CD8();
};

struct Holder801F7CD8 {
    Owned801F7CD8 *p;
    ~Holder801F7CD8();
};

Holder801F7CD8::~Holder801F7CD8() {
    if (p != 0) {
        delete p;
        p = 0;
    }
}

/* Holder constructor: allocates its owned object with new. */
struct Obj801F7D50 {
    char pad_0[0x14];
    Obj801F7D50(int arg);
};

struct Holder801F7D50 {
    Obj801F7D50 *p;
    Holder801F7D50(int arg);
};

Holder801F7D50::Holder801F7D50(int arg) {
    p = new Obj801F7D50(arg);
}

/* Copy-assignment for a draw-node description (name, params and matrix). */
extern "C" {
void *memcpy(void *dst, const void *src, unsigned long n);
void PSMTXCopy(const float src[3][4], float dst[3][4]);
}

#include "game/types/Vec2f.h"

#include "game/types/Vec3f.h"

struct Rect4f {
    float a, b, c, d;
};

struct Pair16 {
    unsigned short a, b;
};

struct Quad32 {
    int a, b, c, d;
};

struct NodeDesc {
    char name[16];
    float f10;
    int i14;
    Pair16 h18;
    Rect4f r1C;
    int i2C;
    Vec2f v30;
    Vec3f v38;
    char tag[16];
    Quad32 q54;
    float mtx[3][4];

    NodeDesc &operator=(const NodeDesc &o);
};

NodeDesc &NodeDesc::operator=(const NodeDesc &o) {
    i2C = o.i2C;
    v38 = o.v38;
    v30 = o.v30;
    memcpy(name, o.name, 16);
    f10 = o.f10;
    i14 = o.i14;
    h18 = o.h18;
    r1C = o.r1C;
    memcpy(tag, o.tag, 16);
    q54 = o.q54;
    PSMTXCopy(o.mtx, mtx);
    return *this;
}

/* Default constructor for a draw-node description. */
extern "C" {
void *memset(void *dst, int c, unsigned long n);
void PSMTXIdentity(float m[3][4]);
}

struct NodeDescInit {
    float color[4];
    float f10;
    int i14;
    unsigned short h18;
    unsigned short h1A;
    float f1C;
    float f20;
    float f24;
    float f28;
    int i2C;
    float f30;
    float f34;
    float f38;
    float f3C;
    float f40;
    char tag[16];
    int i54;
    int i58;
    int i5C;
    int i60;
    float mtx[3][4];

    NodeDescInit();
};

NodeDescInit::NodeDescInit() {
    i2C = 0;
    f38 = lbl_806DA718;
    f3C = lbl_806DA710;
    f40 = lbl_806DA710;
    i54 = 1;
    i58 = 4;
    i5C = 5;
    i60 = 15;
    f34 = lbl_806DA710;
    f30 = lbl_806DA710;
    color[3] = lbl_806DA718;
    color[2] = lbl_806DA718;
    color[1] = lbl_806DA718;
    color[0] = lbl_806DA718;
    f10 = lbl_806DA718;
    i14 = 0;
    h1A = 1;
    h18 = 1;
    f20 = lbl_806DA718;
    f1C = lbl_806DA718;
    f28 = lbl_806DA710;
    f24 = lbl_806DA710;
    memset(tag, -1, 16);
    PSMTXIdentity(mtx);
}

#include "game/DrawQuad7F50MatchPrivate.h"
static inline void DrawPositionDepth7F50(float x, float y, const DrawDesc801F *description) {
    float z = description->z;
    DrawPositionDepth801F(x, y, z);
}
#pragma push
#pragma opt_common_subs off
extern "C" void fn_801F7F50(DrawNode801F *self) {
    DrawQuad7F50 quad(self->description);
    GXBegin(128, 0, 4);
    if (!self->depth) {
        DrawPosition801F(quad.x0, quad.y0);
        DrawColor801F(self->description->colors[0]);
        DrawUV801F(self->description->u0, self->description->v0);
        DrawPosition801F(quad.x1, quad.y1);
        DrawColor801F(self->description->colors[1]);
        DrawUV801F(self->description->u0, self->description->v1);
        DrawPosition801F(quad.x2, quad.y2);
        DrawColor801F(self->description->colors[2]);
        DrawUV801F(self->description->u1, self->description->v1);
        DrawPosition801F(quad.x3, quad.y3);
        DrawColor801F(self->description->colors[3]);
        DrawUV801F(self->description->u1, self->description->v0);
    } else {
        DrawPositionDepth7F50(quad.x0, quad.y0, self->description);
        DrawColor801F(self->description->colors[0]);
        DrawUV801F(self->description->u0, self->description->v0);
        DrawPositionDepth7F50(quad.x1, quad.y1, self->description);
        DrawColor801F(self->description->colors[1]);
        DrawUV801F(self->description->u0, self->description->v1);
        DrawPositionDepth7F50(quad.x2, quad.y2, self->description);
        DrawColor801F(self->description->colors[2]);
        DrawUV801F(self->description->u1, self->description->v1);
        DrawPositionDepth7F50(quad.x3, quad.y3, self->description);
        DrawColor801F(self->description->colors[3]);
        DrawUV801F(self->description->u1, self->description->v0);
    }
}
#pragma pop

#include "game/DrawQuad801F.h"

/* dtor_801F8214 is the weak copy of ~DrawQuad7F50, emitted here. */
struct WeakDtorFlush801F7F50 { int unused; };

#include "game/DrawQuad7F50MatchPrivate.h"

extern "C" {

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
    DrawQuad7F50 quad(self->description, 0);  /* fn_801F8404 form */
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
