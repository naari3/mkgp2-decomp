struct OptionDrawPrefix { int layer, pad4; float x, y, alpha; };
struct OptionDrawPanel : OptionDrawPrefix {
    virtual void v8(); virtual void vC(); virtual void v10(); virtual void v14(); virtual void Draw();
};
struct OptionDrawTarget { char pad[0x198]; signed char count; };
struct OptionDrawScene {
    char pad0[0x20]; OptionDrawTarget *target; void *preview;
    char pad28[0x10]; OptionDrawPanel *panel38; OptionDrawPanel *panel3C;
    char pad40[8]; int texture; unsigned char toggle; char pad4D[3];
    float fade50, fade54; unsigned char selection;
};
struct OptionDrawPoint { float x, y; };
static inline RankLog *GetRankLog() { RankLog **pp = (RankLog **)&lbl_806D10A0; return (*pp == 0 ? 0 : *pp); }
extern "C" void fn_8015A6E4(OptionMenu *self_, int layer, float x, float y, float alpha) {
    OptionDrawScene *self = (OptionDrawScene *)self_;
    OptionDrawPoint rowOrigin;
    float nameX, rowY, imageX, nameY, titleY; OptionDrawPoint tp;
    float pulseScale, pulseAlpha;
    const float *positions;
    int count, i;
    const char *title;
    if (isJapanese() == 1) {
        fn_80168798(layer, (const char *)lbl_806D8574, F3D4+x, F3D0+y, alpha);
        fn_80168D84(layer, (const char *)lbl_806D83E4, F3DC+x, F3E0+y, alpha);
    } else {
        fn_80168798(layer, optionText658, F3CC+x, rowOrigin.y=F3D0+y, alpha);
        fn_80168798(layer, (const char *)lbl_806D8574, F3EC+x, rowOrigin.y, alpha);
        fn_80168D84(layer, (const char *)lbl_806D83F0, F3DC+x, F3E0+y, alpha);
    }
    const char *texture = GetTextureByIdAndLang(0x46,-1);
    fn_80168D84(layer, texture, F3B4+x, tp.y=F578+y, alpha);
    texture = fn_8013C26C(self->texture,-1);
    fn_80168798(layer, texture, F4E8+x, nameY=F454+y, alpha);
    fn_8013C7B0(self->preview,F57C+x,F580+y);
    fn_8013C5FC(self->preview,F584);
    fn_8013C674(self->preview,F588);
    fn_8013C6EC(self->preview,F58C,F58C,F58C);
    fn_8013C4A4(self->preview,alpha);
    fn_8013C91C(self->preview);
    fn_8013DAC8(self->preview,layer);
    texture=GetTextureByIdAndLang(0x44,-1);
    imageX=F590+x;
    fn_80168D84(layer,texture,imageX,tp.y,alpha);
    nameX=F3D4+x;
    fn_80167C60(layer,self->target,nameX,F594+y,alpha);
    fn_80168D84(layer,GetTextureByIdAndLang(0x45,-1),imageX,F598+y,alpha);
    RankLog *global=GetRankLog();
    title=(const char *)lbl_806D859C;
    if (global) title=get_title_name_global(global);
    if (isJapanese()==1)
        fn_80168404(layer,title,nameX,nameY,F3B0,F3B0,alpha);
    else
        fn_80168404(layer,title,nameX,nameY,F5A0,F3B0,alpha);
    fn_80168D84(layer,GetTextureByIdAndLang(0x48,-1),imageX,F5A4+y,alpha);
    count=self->target->count-1;
    count=count & (((unsigned int)count >> 31)-1);
    fn_80168798(layer,GetTextureByIdAndLang(0x49,-1),nameX,F5A8+y,alpha,count);
    rowOrigin.x=F5AC+x;
    fn_801695E0(layer,0x643,0,rowOrigin.x,F5B0+y,alpha);
    if (self->toggle) {
        fn_801695E0(layer,0x67D,0,F5B4+x,rowY=F5B8+y,alpha);
        fn_801695E0(layer,0x67C,0,F5BC+x,rowY,alpha);
    } else {
        fn_801695E0(layer,0x67B,0,F5B4+x,rowY=F5B8+y,alpha);
        fn_801695E0(layer,0x67E,0,F5BC+x,rowY,alpha);
    }
    OptionDrawPanel *panel=self->panel38;
    if(layer>=0 && layer<8)panel->layer=layer;
    panel=self->panel38; panel->x=F5C0+x;panel->y=F5C4+y;
    self->panel38->alpha=alpha;
    self->panel38->Draw();
    rowY=F504+y;
    fn_801695E0(layer,0x642,0,rowOrigin.x,rowY,alpha);
    rowOrigin.y=F410+rowY;
    positions=optionPositions;
    for(i=0;i<5;i++,positions++) {
        if(self->selection==i)
            fn_801695E0(layer,0x676+i,0,rowOrigin.x+*positions,rowOrigin.y,alpha);
        else
            fn_801695E0(layer,0x671+i,0,rowOrigin.x+*positions,rowOrigin.y,alpha);
    }
    if(self->fade50<F398) {
        texture=GetTextureByIdAndLang(0x4B,-1);
        fn_80168B90(layer,texture,F5C8+x,rowY,F3B0,0.0f,0.0f,alpha);
    } else if(isJapanese()==0)
        fn_80168D84(layer,optionText664,F5C8+x,rowY,alpha);
    panel=self->panel3C;
    if(layer>=0 && layer<8)panel->layer=layer;
    panel=self->panel3C;panel->x=F5CC+x;panel->y=F3D4+y;
    self->panel3C->alpha=alpha;
    self->panel3C->Draw();
    if(self->fade54<F39C) {
        float t=self->fade54;
        if(t<F428) {
            pulseAlpha=t/F428;
            pulseScale=F414+(F414*t)/F428;
        } else if(t<F55C) {
            pulseScale=F3B0+(t-F428)/F428;
            pulseAlpha=F3B0-(t-F428)/F428;
        }
        fn_80169334(layer,0x67F,0,rowOrigin.x+optionPositions[self->selection],rowOrigin.y,pulseScale,pulseScale,pulseAlpha*alpha);
        t=self->fade54;
        if(t>F418) {
            if(t<F3B8) {
                float d=t-F418;
                pulseScale=F414+(F414*d)/F428;
                pulseAlpha=d/F428;
            } else if(t<F39C) {
                pulseScale=F3B0+(t-F3B8)/F428;
                pulseAlpha=F3B0-(t-F3B8)/F428;
            }
            fn_80169334(layer,0x67F,0,rowOrigin.x+optionPositions[self->selection],rowOrigin.y,pulseScale,pulseScale,pulseAlpha*alpha);
        }
    }
}
