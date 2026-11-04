/* Overlay projection and camera setup. NonMatching native draft. */
struct OverlayRotation {
    float a,b,c,d;
    OverlayRotation(double a_,double b_,double c_,double d_) : a(a_),b(b_),c(c_),d(d_) {}
    OverlayRotation &operator=(const OverlayRotation &r) { a=r.a; b=r.b; c=r.c; d=r.d; return *this; }
};
typedef struct OverlayView {
    unsigned short x,y,width,height;
    float left,right,bottom,top;
    OverlayRotation rotation;
    float view[3][4];
} OverlayView;
extern "C" OverlayView lbl_80679698;
extern "C" const float lbl_806DA6B0, lbl_806DA6B4, lbl_806DA6B8, lbl_806DA6BC;
extern "C" const float lbl_806DA6C0, lbl_806DA6C4, lbl_806DA6C8, lbl_806DA6CC, lbl_806DA6D0;
extern "C" const float lbl_806DA6D4, lbl_806DA6D8, lbl_806DA6DC, lbl_806DA6E0, lbl_806DA6E4, lbl_806DA6E8;
extern "C" const float lbl_806DA6EC, lbl_806DA6F0;
extern "C" void GXSetCullMode(int);
extern "C" void GXSetViewport(float,float,float,float,float,float);
extern "C" void C_MTXOrtho(float [4][4],float,float,float,float,float,float);
extern "C" void GXSetProjection(float [4][4],int);
extern "C" void GXSetScissor(unsigned int,unsigned int,unsigned int,unsigned int);
extern "C" void C_MTXLookAt(float [3][4],const float *,const float *,const float *);
extern "C" void GXLoadPosMtxImm(float [3][4],int);
extern "C" void GXSetCurrentMtx(int);
#pragma exceptions on
extern "C" void fn_801F6588(unsigned int mode) {
    float projection[4][4];
    float target[3];
    float up[3];
    float eye[3];
    OverlayView *v = &lbl_80679698;
    GXSetCullMode(2);
    GXSetViewport(lbl_806DA6C0,lbl_806DA6C0,lbl_806DA6B0,lbl_806DA6B4,lbl_806DA6C0,lbl_806DA6C4);
    v->left=lbl_806DA6B8; v->right=lbl_806DA6BC; v->bottom=lbl_806DA6BC; v->top=lbl_806DA6C8;
    if (!(mode & 255)) {
        C_MTXOrtho(projection,lbl_806DA6CC,lbl_806DA6D0,lbl_806DA6D4,lbl_806DA6D8,lbl_806DA6DC,lbl_806DA6E0);
        GXSetProjection(projection,1);
    } else {
        C_MTXOrtho(projection,lbl_806DA6CC,lbl_806DA6D0,lbl_806DA6D4,lbl_806DA6D8,lbl_806DA6E4,lbl_806DA6E8);
        GXSetProjection(projection,1);
    }
    v->x=0; v->y=0; v->width=640; v->height=480;
    GXSetScissor(0,0,640,480);
    {
        float dx=((640-v->width)>>1)-v->x;
        float dy=((480-v->height)>>1)-v->y;
        float a=lbl_806DA6C0;
        float b=lbl_806DA6EC;
        float c=lbl_806DA6D8;
        float d=lbl_806DA6CC;
        OverlayRotation rotation(c,d,a,b);
        v->rotation=rotation;
        up[0]=a; up[1]=b; up[2]=a;
        eye[0]=rotation.a-rotation.c*dy-rotation.d*dx;
        eye[1]=rotation.b+rotation.c*dx-rotation.d*dy;
        eye[2]=lbl_806DA6F0;
        target[0]=eye[0]; target[1]=eye[1]; target[2]=a;
        C_MTXLookAt(v->view,eye,up,target);
    }
    GXLoadPosMtxImm(v->view,0);
    GXSetCurrentMtx(0);
}
#pragma exceptions reset
