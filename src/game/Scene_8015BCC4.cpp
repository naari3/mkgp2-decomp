#include "game/Scene_8015BCC4_private.h"

extern "C" {
extern ViewerScene3D *lbl_806D1588;
extern ViewerNormal3D *lbl_806D158C;
extern ViewerVec lbl_80677CD8;
extern float Scene_8015BCC4_bss_806D1590;
extern const float lbl_806D85EC, lbl_806D8648;
void GXDrawDone();
void Object_DtorWithGXSync(void *, int);
void HSD_CObjSetEyePosition(void *, const ViewerVec *);
void HSD_CObjSetInterest(void *, const ViewerVec *);
void HSD_CObjSetRoll(void *, float);
float HSD_CObjGetFov(void *);
}
#pragma exceptions on
extern "C" void fn_8015BCC4(unsigned int resId, float scale) {
    GXDrawDone();
    if (lbl_806D1588) {
        delete lbl_806D1588;
        lbl_806D1588 = 0;
    }
    if (lbl_806D158C) {
        Object_DtorWithGXSync(lbl_806D158C, 1);
        lbl_806D158C = 0;
    }
    if (resId) {
        lbl_806D1588 = new ViewerScene3D(resId);
        lbl_806D158C = new ViewerNormal3D(resId, 0);

        if (!lbl_806D1588 || !lbl_806D158C) return;
        lbl_80677CD8.x = lbl_806D85EC;
        lbl_80677CD8.y = scale;
        lbl_80677CD8.z = lbl_806D85EC;
        void *camera = lbl_806D1588->camera;
        if (camera) {
            ViewerVec interest;
            interest.x = lbl_806D85EC;
            interest.y = lbl_806D85EC;
            interest.z = lbl_806D85EC;
            HSD_CObjSetEyePosition(camera, &lbl_80677CD8);
            HSD_CObjSetInterest(camera, &interest);
            HSD_CObjSetRoll(camera, lbl_806D8648);
            Scene_8015BCC4_bss_806D1590 = HSD_CObjGetFov(camera);
        }
    }
}
#pragma exceptions reset
