#include "game/CourseModeInit_private.h"
CourseModeInit::CourseModeInit() {
    CourseSharedUI *ui = &lbl_80679280;
    vt=lbl_8049A734;
    fn_8002CFB8(0,0,0,0);
    delete (VObject *)g_pInputState;
    g_pInputState=0;
    fn_801DAE54(); fn_80121210(); clRom_PurgeAll(); ProcessSystemTick(0);
    PcbSlot_ResetScratchAreas(); CommBroadcast_ClearTable(); SyncSlot_Reset();
    PreloadResource(0x186E); PreloadResource(0x186F); PreloadResource(0x1870); PreloadResource(0x1871);
    PreloadResource(0x1872); PreloadResource(0x1873); PreloadResource(0x1874); PreloadResource(0x1875);
    ProcessSystemTick(0);
    done=0; lbl_806D17F3=1; lbl_806D17F4=0; lbl_806CFD60=-1;
    lbl_806D17F8=0; lbl_806D17FC=0; lbl_806D1800=0; lbl_806D1804=0;
    lbl_806D1808=0; lbl_806D180C=0; lbl_806D1810=0;
    lbl_806D1818=0; lbl_806D1819=0; lbl_806D1820=0;
    lbl_806D184F=0; lbl_806D1850=0; lbl_806D1854=lbl_806D9890; lbl_806D1858=0;
    SetScreenBrightness(lbl_806D98B8);
    ui->top[0]=new CourseSprite(0xA2,1,0);
    ui->top[1]=new CourseSprite(0xA1,1,0);
    ui->top[2]=new CourseSprite(0xA0,1,0);
    ui->handles[0]=fn_801A0310(ui->top[0],0x1842);
    ui->handles[1]=fn_801A0310(ui->top[0],0x1843);
    ui->handles[2]=fn_801A0310(ui->top[1],0x1842);
    ui->handles[4]=fn_801A0310(ui->top[2],0x184C);
    ui->bottom[0]=new CourseSprite(0xA6,1,0);
    ui->bottom[1]=new CourseSprite(0xA5,1,0);
    ui->bottom[2]=new CourseSprite(0xA4,1,0);
    ui->bottom[3]=new CourseSprite(0xA3,1,0);
    ui->top[0]->SetPosition(lbl_806D9948,lbl_806D994C);
    ui->top[1]->SetPosition(lbl_806D9948,lbl_806D994C);
    ui->top[2]->SetPosition(lbl_806D9948,lbl_806D994C);
    ui->bottom[0]->SetPosition(lbl_806D9948,lbl_806D9950);
    ui->bottom[1]->SetPosition(lbl_806D9948,lbl_806D9950);
    ui->bottom[2]->SetPosition(lbl_806D9948,lbl_806D9950);
    ui->bottom[3]->SetPosition(lbl_806D9948,lbl_806D9950);
    lbl_806D1840=new CourseSprite(0x74,1,lbl_806D9954,lbl_806D9958);
    lbl_806D1844=new CourseSprite(0x4A,1,lbl_806D995C,lbl_806D991C);
    lbl_806D1848=lbl_806D9890; lbl_806D184C=0; lbl_806D184D=9;
    ProcessSystemTick(0);
    if (lbl_806D17F0) {
        if (lbl_806D17F1) {
            CourseEnsureInput();
            if (CountPeersWithRole(-1)==1) { SetLocalPcbRole(0); g_gameMode=0; SetTimerModeEnabled(0); }
            task=new CourseClassTask;
        } else if (g_gameMode==2) {
            CourseEnsureInput(); g_gameMode=0;
            task=new CourseClassTask;
        } else if (lbl_806D17F2) {
            CourseEnsureInput();
            if (fn_801D5A68(g_playerData)) task=new CourseCupTask;
            else task=new CourseRoundTask;
        } else {
            CourseEnsureInput(); task=new CourseFrameTask;
        }
    } else task=new CourseEntryTask;
    lbl_806D17F0=0; lbl_806D17F1=0; lbl_806D17F2=0;
    fn_801B7CD0(0);
    CourseSetFlag(fn_801DAEC0());
    CourseSetFlag(fn_801DAEC0()+0x12);
}
