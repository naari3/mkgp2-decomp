#ifndef GAME_RACEHUDMETHODSPRIVATE_H
#define GAME_RACEHUDMETHODSPRIVATE_H
#include "game/RaceHudSceneCtorPrivate.h"
/* Dispatch view of the scene prefix; secondary host starts at +8. */
struct HudMethodScene : SceneBase {
    virtual void Slot18(); virtual void Slot1C(); virtual void Slot20();
    virtual void Enter(int); virtual void Leave(int);
    void *host; int hostData; int position; SceneBase *child;
};
extern "C" {
extern void *lbl_806D1A60;
extern void *RaceHudScene_vtable_804EECA4[], *lbl_803FE0C8[];
void fn_8021A17C(void *); void fn_8021A1C4(void *);
void fn_8020AC34(void *); void ItemDisplay_Update(void *);
void fn_802321F8(ItemMsgWnd *);
void fn_801FD800(void *); void fn_801FD830(void *);
unsigned char fn_801FD924(void *);
void fn_8011F994(int); void fn_8013D940(int);
void CGameCoin_ProcessInput(InputState *);
void fn_801DABFC(void *); void fn_80232550(ItemMsgWnd *,int);
void fn_8011F86C(); void fn_801DAE54(); void fn_8021A2B4();
void ItemDisplay_Destroy(); void dtor_801FD958(void *,int);
void MemoryManager_TimedFree(void *);
}
#endif
