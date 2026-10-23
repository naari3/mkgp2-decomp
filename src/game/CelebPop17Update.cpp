/* NonMatching: 84.17% instruction match. Native EH matches; table addressing
 * remains add+displacement rather than target addi+indexed loads.
 * Layout follows target accesses; Ghidra exposes an untyped self pointer.
 */
struct Vec { float x,y,z; };
struct Effect { char p0[16]; int index; char slot[20]; char visible; char p29[3]; float alpha; char p30[0x5c]; Vec pos; char p98[12]; Vec velocity; float scale; signed char state; char pb5[0xcb]; int timer; };
struct Tables { char pad[0x74c]; int delay[17], anim[17], duration[17], x0[17], x1[17], y0[17], y1[17]; };
extern "C" {
extern Tables lbl_80328EB8;
extern const float lbl_806D5028,lbl_806D5034,lbl_806D5044,lbl_806D5048,lbl_806D504C,lbl_806D5050,lbl_806D5054,lbl_806D5058,lbl_806D505C;
void VfxSlot_BindResourceEx(void*,int,int);
void VfxSlot_SetPositionFromVec(void*,Vec);
void VfxSlot_SetScaleUniform(void*,float);
void Vec3_Add_DestFirst(Vec*,const Vec*,const Vec*);
void DrawEffect_Free(Effect*);
void CelebPop17_Update(Effect *e) {
    Tables *t=&lbl_80328EB8;
    switch(e->state) {
    case 0:
        if(t->anim[e->index]==0) VfxSlot_BindResourceEx(e->slot,0x95,0);
        else VfxSlot_BindResourceEx(e->slot,0x96,0);
        e->timer=t->delay[e->index]-1;
        e->alpha=lbl_806D5028;
        e->scale=lbl_806D5048;
        e->visible=0;
        e->pos.x+=lbl_806D5044*((float)t->x0[e->index]-lbl_806D504C);
        e->pos.y+=lbl_806D5044*((float)t->y0[e->index]-lbl_806D5050);
        e->pos.y+=lbl_806D5054;
        e->velocity.x=lbl_806D5044*((float)(t->x1[e->index]-t->x0[e->index])/(float)t->duration[e->index]);
        e->velocity.y=lbl_806D5044*((float)(t->y1[e->index]-t->y0[e->index])/(float)t->duration[e->index]);
        e->velocity.z=lbl_806D5034;
        ++e->state;
    case 1:
        if(e->timer) --e->timer;
        if(!e->timer) { e->timer=t->duration[e->index]; ++e->state; }
        break;
    case 2:
        e->visible=1;
        if(t->duration[e->index]-e->timer<5) {
            e->scale+=lbl_806D5048;
            if(e->scale>lbl_806D5028) e->scale=lbl_806D5028;
        } else {
            e->scale+=lbl_806D5058/(float)(t->duration[e->index]-5);
            e->alpha-=lbl_806D5028/(float)(t->duration[e->index]-5);
            if(e->alpha<lbl_806D5034) e->alpha=lbl_806D5034;
        }
        Vec3_Add_DestFirst(&e->pos,&e->pos,&e->velocity);
        VfxSlot_SetPositionFromVec(e->slot,e->pos);
        VfxSlot_SetScaleUniform(e->slot,lbl_806D505C*e->scale);
        if(e->timer) --e->timer;
        if(!e->timer) DrawEffect_Free(e);
        break;
    }
}
}
