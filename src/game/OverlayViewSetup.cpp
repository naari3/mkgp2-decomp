/* Overlay projection and camera setup (fn_801F6588).
 * Owns the view rectangle, rotation and matrix .bss pool at
 * 0x80679698..0x806796F0, addressed from one section base.
 * The indexed rotation assignment retains the local snapshot; subsequent
 * coefficient reads produce the target single-precision rounding.
 * Named rounded coefficients preserve the single-precision snapshot and
 * keep origin, offset and coefficient lifetimes distinct.
 * Primary text is 520 bytes; owned EH, EH index and .bss are exact. */
struct RotData {
    float values[4];
    RotData &operator=(const RotData &r) {
        for (int i=0; i<4; ++i) values[i]=r.values[i];
        return *this;
    }
};
struct OverlayRotation : RotData {
    OverlayRotation(float a_,float b_,float c_,float d_) {
        values[0]=a_; values[1]=b_; values[2]=c_; values[3]=d_;
    }
};
typedef struct OverlayView {
    unsigned short x,y,width,height;
    float left,right,bottom,top;
} OverlayView;
extern "C" {
OverlayView OverlayViewSetup_bss_80679698;
RotData lbl_806796B0;
float lbl_806796C0[3][4];
}
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
    GXSetCullMode(2);
    GXSetViewport(lbl_806DA6C0,lbl_806DA6C0,lbl_806DA6B0,lbl_806DA6B4,lbl_806DA6C0,lbl_806DA6C4);
    OverlayViewSetup_bss_80679698.left=lbl_806DA6B8; OverlayViewSetup_bss_80679698.right=lbl_806DA6BC; OverlayViewSetup_bss_80679698.bottom=OverlayViewSetup_bss_80679698.right; OverlayViewSetup_bss_80679698.top=lbl_806DA6C8;
    if (!(mode & 255)) {
        C_MTXOrtho(projection,lbl_806DA6CC,lbl_806DA6D0,lbl_806DA6D4,lbl_806DA6D8,lbl_806DA6DC,lbl_806DA6E0);
        GXSetProjection(projection,1);
    } else {
        C_MTXOrtho(projection,lbl_806DA6CC,lbl_806DA6D0,lbl_806DA6D4,lbl_806DA6D8,lbl_806DA6E4,lbl_806DA6E8);
        GXSetProjection(projection,1);
    }
    OverlayViewSetup_bss_80679698.x=0; OverlayViewSetup_bss_80679698.y=0; OverlayViewSetup_bss_80679698.width=640; OverlayViewSetup_bss_80679698.height=480;
    GXSetScissor(0,0,640,480);
    {
        float dy; float d; float c; float dx; float cosine; float sine; float a; float b;
        dx=((640-OverlayViewSetup_bss_80679698.width)>>1)-OverlayViewSetup_bss_80679698.x;
        dy=((480-OverlayViewSetup_bss_80679698.height)>>1)-OverlayViewSetup_bss_80679698.y;
        a=lbl_806DA6C0; b=lbl_806DA6EC; c=lbl_806DA6D8; d=lbl_806DA6CC;
        OverlayRotation rotation(c,d,a,b);
        float target[3]; float up[3]; float eye[3];
        lbl_806796B0=rotation;
        up[0]=a; up[1]=lbl_806DA6EC; up[2]=lbl_806DA6C0;
        sine=lbl_806796B0.values[2]; cosine=lbl_806796B0.values[3];
        eye[0]=c-sine*dy-cosine*dx;
        eye[1]=d+sine*dx-cosine*dy;
        eye[2]=lbl_806DA6F0;
        target[0]=eye[0]; target[1]=eye[1]; target[2]=a;
        C_MTXLookAt(lbl_806796C0,eye,up,target);
    }
    GXLoadPosMtxImm(lbl_806796C0,0);
    GXSetCurrentMtx(0);
}
#pragma exceptions reset
