/* Character selection draw pass, 801C3AA4. */
struct CharaDrawable { virtual void unused(); virtual unsigned char Draw(); virtual void Finish(); };
struct CharaFrame { short a,pad,b,pad2; int d; float x,y,z; };
struct CharaDrawView {
    int v, selection, state, pending, frame;
    void* sprites[13];
    void *left, *right, *stats[3], *header;
    int result;
    unsigned char complete, display, pad[2];
    int cursor; float brightness;
    CharaDrawable* camera; void* lights;
    char matrix[0x30];
    int variants[13];
    void* normals[13]; void* alternate[13]; void* models[13];
    int extra; char tail[0x24];
};
extern "C" {
extern CharaFrame FrameParam_ARRAY_8049aad0[];
extern const float lbl_806D9B98, lbl_806D9B9C, lbl_806D9BA0, FLOAT_TEX_POS_X;
extern const float lbl_806D9BA8, lbl_806D9BAC;
void fn_801A1174(int,int,int,int,int);
void fn_801A1128(float,float);
void fn_801A0DF0();
void fn_801A0004(void*);
void fn_8011FAB8(); void fn_801A1280();
void LObjList_ApplyForCObj(void*); void CObj_DebugVizPathFlush(void*);
void Object_RenderJObjTree(void*,int);
void* fn_801F8E58(); void fn_801F8A34(void*,int,int); void fn_8011FAFC(void*,int);
void fn_801C3AA4(CharaDrawView* self) {
    int i;
    if (self->state == 1 || self->state == 2 || self->state == 3) {
        fn_801A1174(0x16ac,4,0,0,0);
        fn_801A1128(lbl_806D9B98,lbl_806D9B9C); fn_801A0DF0();
        fn_801A1174(FrameParam_ARRAY_8049aad0[self->selection].b,5,0,0,0);
        fn_801A1128(lbl_806D9BA0,FLOAT_TEX_POS_X); fn_801A0DF0();
    }
    for (i=0;i<13;i++) if(i != self->selection && self->sprites[i]) fn_801A0004(self->sprites[i]);
    if (self->sprites[self->selection]) fn_801A0004(self->sprites[self->selection]);
    if(self->header) fn_801A0004(self->header);
    fn_8011FAB8(); fn_801A1280();
    if(self->display) {
        if(self->left) fn_801A0004(self->left);
        if(self->right) fn_801A0004(self->right);
        if(self->stats[0]) fn_801A0004(self->stats[0]);
        if(self->stats[1]) fn_801A0004(self->stats[1]);
        if(self->stats[2]) fn_801A0004(self->stats[2]);
        if(self->camera && self->camera->Draw()) {
            LObjList_ApplyForCObj(self->lights); CObj_DebugVizPathFlush(self->camera);
            if(self->alternate[self->selection]) Object_RenderJObjTree(self->alternate[self->selection],7);
            if(self->models[self->selection]) ((CharaDrawable*)self->models[self->selection])->Draw();
            if(self->normals[self->selection]) Object_RenderJObjTree(self->normals[self->selection],7);
            self->camera->Finish();
        }
    }
    if(self->state == 1 || self->state == 2 || self->state == 3) {
        fn_801A1174(0x16ad,5,0,0,0);
        fn_801A1128(lbl_806D9BA8,lbl_806D9BAC); fn_801A0DF0();
        fn_801F8A34(fn_801F8E58(),self->extra,6);
        if(self->variants[self->cursor] == 2) fn_8011FAFC((char*)self+0x17c,5);
    }
}
}
