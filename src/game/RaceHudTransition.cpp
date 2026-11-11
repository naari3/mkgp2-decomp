/* Deferred generation: definitions are in reverse target-address order. */
#include "game/types/clResult.h"
struct HudModeInput { virtual void Destroy(int); };
extern "C" {
void fn_801A1280(); void fn_8011F994(int); void fn_8012094C(); void fn_801A0B70(int); void fn_8020F290();
extern HudModeInput *g_pInputState;
extern void *lbl_806D1A88;
void fn_801F9888(); void fn_80209FA4(); void fn_8013DB9C();
void fn_801FE3BC(); void fn_80202BCC(); void fn_802040B0(); void fn_80207D38();
void ItemDisplay_Destroy(); void fn_80232550(void *,int);
void fn_8021A2B4(); void fn_8013C3C0(); void fn_801F8E54(); void fn_8018B248();
void PlayStats_TickActiveSessionSeconds();
void dtor_8002CDF4(void *,int);
}
extern "C" clResult *fn_80248248() { return new clResult; }
clResult::~clResult() {
    fn_801F9888(); fn_80209FA4(); fn_8013DB9C(); fn_801FE3BC();
        fn_80202BCC(); fn_802040B0(); fn_80207D38(); ItemDisplay_Destroy();
        if(lbl_806D1A88) { fn_80232550(lbl_806D1A88,1); lbl_806D1A88=0; }
        fn_8021A2B4(); fn_8024F530(); fn_8013C3C0(); fn_801F8E54();
        if(g_pInputState) g_pInputState->Destroy(1);
        g_pInputState=0;
        fn_8018B248(); fn_80218D98((MenuDisplay *)display,1);
        if(lbl_806D17F0==1) PlayStats_TickActiveSessionSeconds();
}
int clResult::Update() {
    fn_801A1280();
    if (scene->done) {
        if (scene) {
            if (scene) {
                scene->Destroy();
                scene=0;
            }
        }
        fn_80121210();
        fn_8012094C();
        clRom_PurgeAll();
        fn_801A0B70(1);
        fn_801F8E54();
        if (fn_8024F588()->flag) {
            g_cupId+=8;
            return 4;
        }
        fn_8024F530();
        return 3;
    }
    scene->Update();
    fn_8020F290();
    fn_80218B80((MenuDisplay *)display);
    return -2;
}
void clResult::Draw() {
    if (scene) {
        if (!scene->done) scene->Draw();
        fn_80218B5C((MenuDisplay *)display);
        fn_8011F994(7);
    }
}
