/* Overlay projection and camera setup. NonMatching native draft. */
struct OverlayRotation {
    float a,b,c,d;
    OverlayRotation(float a_,float b_,double c_,double d_) : a(a_),b(b_),c(c_),d(d_) {}
    ~OverlayRotation() {}
    OverlayRotation &operator=(const OverlayRotation &r) { a=r.a; b=r.b; c=r.c; d=r.d; return *this; }
};
typedef struct OverlayView {
    unsigned short x,y,width,height;
    float left,right,bottom,top;
} OverlayView;
/* Owned here (.bss 0x80679698..0x806796FC); separate objects so MWCC
 * addresses them from one section anchor. */
extern "C" OverlayView OverlayViewSetup_bss_80679698;
OverlayView OverlayViewSetup_bss_80679698;
static struct { float a,b,c,d; } overlayRotation;
static float overlayView[3][4];
static inline void SetRot(float a_,float b_,double c_,double d_) { overlayRotation.a=a_; overlayRotation.b=b_; overlayRotation.c=c_; overlayRotation.d=d_; }
extern "C" unsigned char lbl_806796F0[0xC];
unsigned char lbl_806796F0[0xC];
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
#define v (&OverlayViewSetup_bss_80679698)
    GXSetCullMode(2);
    GXSetViewport(lbl_806DA6C0,lbl_806DA6C0,lbl_806DA6B0,lbl_806DA6B4,lbl_806DA6C0,lbl_806DA6C4);
    v->left=lbl_806DA6B8; v->right=1024.0f; v->bottom=1024.0f; v->top=lbl_806DA6C8;
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
        float a=0.0f;
        float c=lbl_806DA6D8;
        float dx=((640-v->width)>>1)-v->x;
        float dy=((480-v->height)>>1)-v->y;
        float b=lbl_806DA6EC;
        float d=lbl_806DA6CC;
        OverlayRotation rotation(c,d,a,b);
        float target[3];
        float up[3];
        float eye[3];
        SetRot(c,d,a,b);
        up[0]=a; up[1]=b; up[2]=a;
        eye[0]=rotation.a-rotation.c*dy-rotation.d*dx;
        eye[1]=rotation.b+rotation.c*dx-rotation.d*dy;
        eye[2]=lbl_806DA6F0;
        target[0]=eye[0]; target[1]=eye[1]; target[2]=a;
        C_MTXLookAt(overlayView,eye,up,target);
    }
    GXLoadPosMtxImm(overlayView,0);
    GXSetCurrentMtx(0);
}
#pragma exceptions reset
