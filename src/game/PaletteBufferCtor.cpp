/* Palette-backed texture descriptors with half-texel UV bounds. */
#include "game/PaletteBufferCtorPrivate.h"
PaletteBuffer::PaletteBuffer(const char *name) : PaletteRef(name), count(palette->count) {
    vt=lbl_804E54FC;
    data=0;
    int i;
    PaletteView *pal=palette;
    int num=count;
    PaletteTextureView *out;
    data=(PaletteTextureView *)FUN_8003b120(num*sizeof(PaletteTextureView));
    out=data;
    for(i=0;i<num;i++,out++) {
        PaletteEntryView *entry=TEXGetPaletteEntry(pal,i);
        if(entry->clut) TEXBindPaletteEntry_CI(pal,out,out->clut,0,i);
        else TEXBindPaletteEntry_RGB(pal,out,i);
        out->x=0; out->y=0;
        out->width=entry->texture->width;
        out->height=entry->texture->height;
        float invH;
        float invW=lbl_806DA6C4/(float)out->width;
        invH=lbl_806DA6C4/(float)out->height;
        float u0=lbl_806DA708+out->x;
        u0 *= invW;
        out->u0=u0;
        out->u1=invW*((float)out->x+out->width-lbl_806DA708);
        float v0=lbl_806DA708+out->y;
        v0 *= invH;
        out->v0=v0;
        out->v1=invH*((float)out->y+out->height-lbl_806DA708);
    }
}
