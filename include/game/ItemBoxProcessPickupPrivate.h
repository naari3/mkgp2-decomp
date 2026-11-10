#ifndef GAME_ITEMBOXPROCESSPICKUPPRIVATE_H
#define GAME_ITEMBOXPROCESSPICKUPPRIVATE_H
/* Slot item IDs are at +4+8*i; usage values are at +8+8*i.
 * Slot 3 is also used as the direct-give staging slot. */
typedef struct PickupSlot { int uses; int itemId; } PickupSlot;
typedef struct PickupState {
    PickupSlot slots[10];
    int field50;
    int slot, lastSlot, result;
    unsigned char spinning, active, pad62[2];
    int timer, field68, state, queuedItem, field74;
    void *hud;
    unsigned char playSE, pad7d[3];
    int cooldown;
    unsigned char visible;
} PickupState;
extern int g_gameMode, lbl_806CF110;
extern unsigned char g_isCommHost, lbl_80598A60[0x4a];
extern int ItemBox_ProcessPickup_data_803F9D10[39];
extern void *CarObject_GetRenderObj(void *);
extern int KartMovement_GetCurrentItemId(void *);
extern unsigned char KartMovement_EquipItem(void *, int);
extern unsigned char KartItem_GetCarObjectState_2bc(void *);
extern unsigned char Input_IsItemButtonPressed(void *);
extern unsigned char ItemUse_Gateway(void *, int, float);
extern void *StrPcb_GetInstance(void);
extern void StrPcb_ClearStatusBits(void *, int);
extern void StrPcb_SetStatusBits(void *, int, int);
extern void fn_8023E324(void *, int);
extern void fn_8023E154(void *);
extern void fn_8023E1E4(void *, int, int);
extern void KartItem_PlaySE_0x09(void *);
extern void fn_8016C394(int);
extern void SoundMgr_PlaySE(int);
#endif
