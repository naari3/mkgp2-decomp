/* 0x801F5A9C..0x801F6454. Menu configuration scene and owning game mode.
 * The reversed EH group remains NonMatching: fn_801F6178 has scheduling
 * differences, while the other seven primary functions match exactly.
 */
#include "game/MenuModeLane_private.h"

extern "C" void *fn_801F5A9C(MenuScene *self, short flag) {
    if (self) {
        *(void **)self = MenuScene_vtable_804E5444;
        fn_8023E808(self->widgets[2], 1);
        fn_8023E808(self->widgets[1], 1);
        fn_8023E808(self->widgets[0], 1);
        fn_80209FA4();
        fn_801F9888();
        g_ccClass = self->cc;
        InputCmd_SetGlobalConfig(self->input);
        if (self) {
            *(void **)self = MenuModeBase_vtable_804E549C;
            if (self) *(void **)self = lbl_803FE0C8;
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

MenuModeBase::MenuModeBase() {
    cup=g_cupId; course=0; variant=0; round=0; startAnim=1; randomItem=0;
    role=g_localPcbRole; timer=1; itemCount=5; modeFlag=1;
    character=g_characterId; mode=g_gameMode; roundIndex=g_roundIndex;
    cc=g_ccClass; gate=g_rendererGateFlag; kart=g_kartVariant; selection=1;
    if (kart<0) kart=0;
}

inline MenuScene::MenuScene() {
    state2=0;
    fn_801F98CC(); fn_80209FE8(); state=0;
    widgets[0]=new MenuWidget(0); widgets[1]=new MenuWidget(0); widgets[2]=new MenuWidget(0);
    widgets[0]->SetPosition(lbl_806DA690,lbl_806DA694);
    widgets[1]->SetPosition(lbl_806DA698,lbl_806DA694);
    widgets[2]->SetPosition(lbl_806DA69C,lbl_806DA694);
    input=InputCmd_GetGlobalConfig();
}

MenuMode::MenuMode() {
    vt=MenuModeLane_data_804E54D8;
    scene=0;
    fn_801F6494();
    cup=g_cupId; course=0; variant=0; round=0; startAnim=1; randomItem=0;
    role=g_localPcbRole; timer=1; itemCount=5; character=g_characterId;
    modeFlag=1; menuId=43; mode=g_gameMode; roundIndex=g_roundIndex;
    gate=g_rendererGateFlag; kart=g_kartVariant;
    if (kart<0) kart=0;
    switch(fn_801DC868()) {
    case 0: selection=1; break;
    case 1: selection=0; break;
    case 2: selection=2; break;
    default: selection=1; break;
    }
    display=new MenuDisplay(0);
    if (lbl_806D0051) scene=fn_80271340(fn_8020CEAC(),0,lbl_806D005C,lbl_806D0054,0);
    else scene=fn_80271340(new MenuScene,0,lbl_806D005C,lbl_806D0054,0);
    if (scene) {
        scene->timer=timer; scene->cup=cup; scene->course=course;
        scene->variant=variant; scene->round=round; scene->character=character;
        scene->itemCount=itemCount; scene->startAnim=startAnim;
        scene->randomItem=randomItem; scene->role=role; scene->modeFlag=modeFlag;
        scene->items[0]=DebugOverlay_RaceConfig_data_804E53B0[0]; scene->items[1]=DebugOverlay_RaceConfig_data_804E53B0[1];
        scene->items[2]=DebugOverlay_RaceConfig_data_804E53B0[2]; scene->kart=kart; scene->selection=selection;
    }
}

extern "C" void fn_801F5FB0(MenuMode *self) {
    if (self->scene) {
        if (!self->scene->done) self->scene->Draw();
        fn_80218B5C(self->display);
    }
}

extern "C" int fn_801F6008(MenuMode *self) {
    if (!self->scene) return 4;
    if (!self->scene->done) self->scene->Update();
    else {
        if (self->scene) {
            self->timer=self->scene->timer; self->cup=self->scene->cup;
            self->course=self->scene->course; self->variant=self->scene->variant;
            self->round=self->scene->round; self->character=self->scene->character;
            self->itemCount=self->scene->itemCount; self->startAnim=self->scene->startAnim;
            self->randomItem=self->scene->randomItem; self->role=self->scene->role;
            self->modeFlag=self->scene->modeFlag;
            DebugOverlay_RaceConfig_data_804E53B0[0]=self->scene->items[0]; DebugOverlay_RaceConfig_data_804E53B0[1]=self->scene->items[1];
            DebugOverlay_RaceConfig_data_804E53B0[2]=self->scene->items[2];
            self->mode=self->scene->mode; self->roundIndex=self->scene->roundIndex;
            self->gate=self->scene->gate; self->kart=self->scene->kart;
            self->selection=self->scene->selection; g_humanPlayerCount=DebugOverlay_RaceConfig_data_804E53B0[0];
        }
        self->scene->Destroy();
        self->scene=0;
    }
    fn_80218B80(self->display);
    return -2;
}

extern "C" void *fn_801F6178(MenuMode *self, short flag) {
    if (self) {
        self->vt=MenuModeLane_data_804E54D8;
        fn_80218D98(self->display,1);
        SetTimerModeEnabled(self->timer);
        SetCourseParams(self->cup,self->course,self->variant,self->round);
        int slot=VSMode_SeedRandomItemSequence(0,self->character,self->itemCount);
        g_lakituStartAnimDone=self->startAnim != 0;
        lbl_806D1290=self->role == 0 ? self->randomItem != 0 : false;
        RaceSlot_InitSlot(slot,GetDisplayBufferIndex(),self->character,1,0);
        g_characterId=self->character;
        int firstItem=DebugOverlay_RaceConfig_data_804E53B0[0];
        lbl_806CF110=self->modeFlag;
        RaceSlot_SetItemSlotByte(slot,0,firstItem);
        signed char item=DebugOverlay_RaceConfig_data_804E53B0[1];
        RaceSlot_SetItemSlotByte(slot,1,item);
        item=DebugOverlay_RaceConfig_data_804E53B0[2];
        RaceSlot_SetItemSlotByte(slot,2,item);
        lbl_806D1264[0]=DebugOverlay_RaceConfig_data_804E53B0[0]; lbl_806D1264[1]=DebugOverlay_RaceConfig_data_804E53B0[1];
        lbl_806D1264[2]=DebugOverlay_RaceConfig_data_804E53B0[2];
        g_gameMode=self->mode; g_roundIndex=self->roundIndex;
        g_rendererGateFlag=self->gate != 0;
        SetKartVariant(self->kart);
        g_namCamFlag=1;
        if (self->selection==0) { lbl_806D12C0=0; lbl_806D12C0=1; fn_801DC870(1); }
        else if (self->selection==1) { lbl_806D12C0=0; fn_801DC870(0); }
        else { lbl_806D12C0=0; lbl_806D12C0=1; fn_801DC870(2); }
        g_playerData[0x1b8]=self->character;
        fn_80121210(); clRom_PurgeAll();
        dtor_8002CDF4(self,0);
        if (flag>0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" MenuMode *fn_801F63A4() {
    if (MenuModeLane_data_806D0050==1) { lbl_806D0051=0; MenuModeLane_data_806D0050=0; }
    return new MenuMode;
}

MenuModeBase::~MenuModeBase() {}

