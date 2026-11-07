#include "game/SpriteTex801F_private.h"
extern "C" {
extern void *lbl_804E5538[],*lbl_804E5578[],*lbl_804E5558[],*lbl_804E5524[];
extern unsigned char lbl_806D1968;
struct CachedDraw801F { int mode; TextureEntry801F *texture; };
extern CachedDraw801F lbl_806D196C;
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
void fn_801F8728(void *); void fn_801F8404(void *); void fn_801F7F50(void *);
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
static inline void LoadTextureS56(TextureOwner801F *owner,SpriteTex801F *s) {
    TextureBank801F *bank=owner->bank;
    TextureEntry801F *entries=bank->textures;
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
        fn_801F8728(&node);
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
            fn_801F8404(&node);
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
            fn_801F7F50(&node);
        }
    }
}
