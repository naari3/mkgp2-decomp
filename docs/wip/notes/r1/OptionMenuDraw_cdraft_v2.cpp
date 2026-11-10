// fn_8015A6E4 ported to the current TU game/SceneList_80157EA8.cpp (n3 11-10).
// Body only. Harness changes needed in the TU: real prototypes instead of the
// asm `()` externs (fn_80168B90 must be variadic-style direct call, a function
// pointer cast gives an indirect call), `extern const float` for lbl_806D858C..85CC,
// `struct OptionDrawPoint { float x, y; };`, OptionDrawScene/OptionDrawPanel as in
// OptionMenuDraw_cdraft.cpp.
//
// Scores (objdiff, current TU):
//   this body with every float as extern (the only linkable form today): 99.84
//   mixed literal 10.0f/0.5f in the first pulse (old draft trick):        99.947
//     -> NOT landable: the TU does not own .sdata2 0x806D8390..0x806D85D0, a
//        literal emits an extra TU-local constant and main.dol breaks.
//   every float as a literal (needs sdata2 ownership of the whole TU):    99.72
//
// Finding: the English heading Y and the title Y must be members of local
// point structs (hp.y / tp.y), not one float local assigned twice. A float local
// with two webs keeps the variable identity on its first web (low vreg, f24);
// struct members are promoted as temps and both land in f30 like the target.
extern "C" void fn_8015A6E4(OptionMenu *self_, int layer, float x, float y, float alpha) {
    OptionDrawScene *self = (OptionDrawScene *)self_;
    OptionDrawPoint rowOrigin;
    float nameX, rowY, imageX, nameY, titleY; OptionDrawPoint tp;
    float pulseScale, pulseAlpha;
    const float *positions;
    int count, i;
    const char *title;
    if (isJapanese() == 1) {
        fn_80168798(layer, (const char *)lbl_806D8574, lbl_806D83D4+x, lbl_806D83D0+y, alpha);
        fn_80168D84(layer, (const char *)lbl_806D83E4, lbl_806D83DC+x, lbl_806D83E0+y, alpha);
    } else {
        fn_80168798(layer, optionText658, lbl_806D83CC+x, rowOrigin.y=lbl_806D83D0+y, alpha);
        fn_80168798(layer, (const char *)lbl_806D8574, lbl_806D83EC+x, rowOrigin.y, alpha);
        fn_80168D84(layer, (const char *)lbl_806D83F0, lbl_806D83DC+x, lbl_806D83E0+y, alpha);
    }
    const char *texture = GetTextureByIdAndLang(0x46,-1);
    fn_80168D84(layer, texture, lbl_806D83B4+x, tp.y=lbl_806D8578+y, alpha);
    texture = fn_8013C26C(self->texture,-1);
    fn_80168798(layer, texture, lbl_806D84E8+x, nameY=lbl_806D8454+y, alpha);
    fn_8013C7B0(self->preview,lbl_806D857C+x,lbl_806D8580+y);
    fn_8013C5FC(self->preview,lbl_806D8584);
    fn_8013C674(self->preview,lbl_806D8588);
    fn_8013C6EC(self->preview,lbl_806D858C,lbl_806D858C,lbl_806D858C);
    fn_8013C4A4(self->preview,alpha);
    fn_8013C91C(self->preview);
    fn_8013DAC8(self->preview,layer);
    texture=GetTextureByIdAndLang(0x44,-1);
    imageX=lbl_806D8590+x;
    fn_80168D84(layer,texture,imageX,tp.y,alpha);
    nameX=lbl_806D83D4+x;
    fn_80167C60(layer,self->target,nameX,lbl_806D8594+y,alpha);
    fn_80168D84(layer,GetTextureByIdAndLang(0x45,-1),imageX,lbl_806D8598+y,alpha);
    RankLog *global=GetRankLog();
    title=(const char *)lbl_806D859C;
    if (global) title=get_title_name_global(global);
    if (isJapanese()==1)
        fn_80168404(layer,title,nameX,nameY,lbl_806D83B0,lbl_806D83B0,alpha);
    else
        fn_80168404(layer,title,nameX,nameY,lbl_806D85A0,lbl_806D83B0,alpha);
    fn_80168D84(layer,GetTextureByIdAndLang(0x48,-1),imageX,lbl_806D85A4+y,alpha);
    count=self->target->count-1;
    count=count & (((unsigned int)count >> 31)-1);
    fn_80168798(layer,GetTextureByIdAndLang(0x49,-1),nameX,lbl_806D85A8+y,alpha,count);
    rowOrigin.x=lbl_806D85AC+x;
    fn_801695E0(layer,0x643,0,rowOrigin.x,lbl_806D85B0+y,alpha);
    if (self->toggle) {
        fn_801695E0(layer,0x67D,0,lbl_806D85B4+x,rowY=lbl_806D85B8+y,alpha);
        fn_801695E0(layer,0x67C,0,lbl_806D85BC+x,rowY,alpha);
    } else {
        fn_801695E0(layer,0x67B,0,lbl_806D85B4+x,rowY=lbl_806D85B8+y,alpha);
        fn_801695E0(layer,0x67E,0,lbl_806D85BC+x,rowY,alpha);
    }
    OptionDrawPanel *panel=self->panel38;
    if(layer>=0 && layer<8)panel->layer=layer;
    panel=self->panel38; panel->x=lbl_806D85C0+x;panel->y=lbl_806D85C4+y;
    self->panel38->alpha=alpha;
    self->panel38->Draw();
    rowY=lbl_806D8504+y;
    fn_801695E0(layer,0x642,0,rowOrigin.x,rowY,alpha);
    rowOrigin.y=lbl_806D8410+rowY;
    positions=optionPositions;
    for(i=0;i<5;i++,positions++) {
        if(self->selection==i)
            fn_801695E0(layer,0x676+i,0,rowOrigin.x+*positions,rowOrigin.y,alpha);
        else
            fn_801695E0(layer,0x671+i,0,rowOrigin.x+*positions,rowOrigin.y,alpha);
    }
    if(self->fade50<lbl_806D8398) {
        texture=GetTextureByIdAndLang(0x4B,-1);
        fn_80168B90(layer,texture,lbl_806D85C8+x,rowY,lbl_806D83B0,0.0f,0.0f,alpha);
    } else if(isJapanese()==0)
        fn_80168D84(layer,optionText664,lbl_806D85C8+x,rowY,alpha);
    panel=self->panel3C;
    if(layer>=0 && layer<8)panel->layer=layer;
    panel=self->panel3C;panel->x=lbl_806D85CC+x;panel->y=lbl_806D83D4+y;
    self->panel3C->alpha=alpha;
    self->panel3C->Draw();
    if(self->fade54<lbl_806D839C) {
        float t=self->fade54;
        if(t<lbl_806D8428) {
            pulseAlpha=t/lbl_806D8428;
            pulseScale=lbl_806D8414+(lbl_806D8414*t)/lbl_806D8428;
        } else if(t<lbl_806D855C) {
            float fraction=(t-lbl_806D8428)/lbl_806D8428;
            pulseScale=lbl_806D83B0+fraction;
            pulseAlpha=lbl_806D83B0-fraction;
        }
        fn_80169334(layer,0x67F,0,rowOrigin.x+optionPositions[self->selection],rowOrigin.y,pulseScale,pulseScale,pulseAlpha*alpha);
        t=self->fade54;
        if(t>lbl_806D8418) {
            if(t<lbl_806D83B8) {
                float d=t-lbl_806D8418;
                pulseAlpha=d/lbl_806D8428;
                pulseScale=lbl_806D8414+(lbl_806D8414*d)/lbl_806D8428;
            } else if(t<lbl_806D839C) {
                float fraction=(t-lbl_806D83B8)/lbl_806D8428;
                pulseScale=lbl_806D83B0+fraction;
                pulseAlpha=lbl_806D83B0-fraction;
            }
            fn_80169334(layer,0x67F,0,rowOrigin.x+optionPositions[self->selection],rowOrigin.y,pulseScale,pulseScale,pulseAlpha*alpha);
        }
    }
}
