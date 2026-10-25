/* UI_PageDispatcher @ 0x800668FC..0x80066B74: runs the current test-menu
 * page handler (self->page) for one phase. Owns its jump table in .data. */

typedef struct TestPage {
    unsigned char pad_0[0x10];
    unsigned int page;    /* 0x10 */
    unsigned char pad_14[0x20];
    int variant;          /* 0x34 */
} TestPage;

extern void BackupMemoryInitialize_Page(TestPage *self, int phase, int arg);
extern void CabinetSetting_Page(TestPage *self, int phase, int arg);
extern void CameraTest_Page(TestPage *self, int phase, int arg);
extern void CardCreate_Page(TestPage *self, int phase, int arg);
extern void CardDataCheck_UI(TestPage *self, int phase, int arg);
extern void CardDataTransfer_UI(TestPage *self, int phase, int arg);
extern void CardRW_CleaningTest_Page(TestPage *self, int phase, int arg);
extern void CardRW_DataRepair_Page(TestPage *self, int phase, int arg);
extern void CardRW_DispenseTest_Page(TestPage *self, int phase, int arg);
extern void CardRW_HardwareInit_Page(TestPage *self, int phase, int arg);
extern void CardRW_PrintTest_Page(TestPage *self, int phase, int arg);
extern void CardRW_ReadWriteTest_Page(TestPage *self, int phase, int arg);
extern void CardRW_Renew_Page(TestPage *self, int phase, int arg);
extern void CardRW_Reprint_Page(TestPage *self, int phase, int arg);
extern void CardRW_TestTopMenu_Page(TestPage *self, int phase, int arg);
extern void ClockSetting_Page(TestPage *self, int phase, int arg);
extern void GameSetting_Page(TestPage *self, int phase, int arg);
extern void GameSetting_Page_VariantA(TestPage *self, int phase, int arg);
extern void GameSetting_Page_VariantB(TestPage *self, int phase, int arg);
extern void GameTestTopMenu_Page(TestPage *self, int phase, int arg);
extern void HandleInitialize_Page(TestPage *self, int phase, int arg);
extern void LampTestIndiv_Page(TestPage *self, int phase, int arg);
extern void LampTest_Page(TestPage *self, int phase, int arg);
extern void MonitorTest_Page(TestPage *self, int phase, int arg);
extern void NetDiag_CounterPage(TestPage *self, int phase, int arg);
extern void NetDiag_PacketPage(TestPage *self, int phase, int arg);
extern void NetDiag_PacketRatioPage(TestPage *self, int phase, int arg);
extern void NetDiag_QualityPage(TestPage *self, int phase, int arg);
extern void OperationTime_Page(TestPage *self, int phase, int arg);
extern void SpeakerTest_Page(TestPage *self, int phase, int arg);
extern void Stats_Display_UI(TestPage *self, int phase, int arg);
extern void Stats_PacketStats_UI(TestPage *self, int phase, int arg);
extern void SwitchTest_Page(TestPage *self, int phase, int arg);
extern void SystemInfo_UI(TestPage *self, int phase, int arg);

#pragma exceptions on

int UI_PageDispatcher(TestPage *self, int phase)
{
    switch (self->page) {
    case 0:
        GameTestTopMenu_Page(self, phase, -1);
        return 1;
    case 1:
        if (self->variant == 0) {
            GameSetting_Page(self, phase, -1);
        } else if (self->variant == 1) {
            GameSetting_Page_VariantB(self, phase, -1);
        } else {
            GameSetting_Page_VariantA(self, phase, -1);
        }
        return 1;
    case 2:
        MonitorTest_Page(self, phase, -1);
        return 1;
    case 11:
        HandleInitialize_Page(self, phase, -1);
        return 1;
    case 12:
        SwitchTest_Page(self, phase, -1);
        return 1;
    case 13:
        LampTestIndiv_Page(self, phase, -1);
        return 1;
    case 14:
        CameraTest_Page(self, phase, -1);
        return 1;
    case 3:
        LampTest_Page(self, phase, -1);
        return 1;
    case 4:
        SpeakerTest_Page(self, phase, -1);
        return 1;
    case 5:
        CardRW_TestTopMenu_Page(self, phase, -1);
        return 1;
    case 15:
        CardRW_CleaningTest_Page(self, phase, -1);
        return 1;
    case 16:
        CardRW_ReadWriteTest_Page(self, phase, -1);
        return 1;
    case 17:
        CardRW_DispenseTest_Page(self, phase, -1);
        return 1;
    case 18:
        CardRW_PrintTest_Page(self, phase, -1);
        return 1;
    case 19:
        CardDataCheck_UI(self, phase, -1);
        return 1;
    case 20:
        CardDataTransfer_UI(self, phase, -1);
        return 1;
    case 21:
        CardRW_DataRepair_Page(self, phase, -1);
        return 1;
    case 22:
        CardRW_Reprint_Page(self, phase, -1);
        return 1;
    case 23:
        CardRW_HardwareInit_Page(self, phase, -1);
        return 1;
    case 24:
        CardRW_Renew_Page(self, phase, -1);
        return 1;
    case 25:
        CardCreate_Page(self, phase, -1);
        return 1;
    case 6:
        CabinetSetting_Page(self, phase, -1);
        return 1;
    case 7:
        ClockSetting_Page(self, phase, -1);
        return 1;
    case 8:
        OperationTime_Page(self, phase, -1);
        return 1;
    case 26:
        NetDiag_PacketRatioPage(self, phase, -1);
        return 1;
    case 27:
        Stats_Display_UI(self, phase, -1);
        return 1;
    case 28:
        NetDiag_PacketPage(self, phase, -1);
        return 1;
    case 29:
        Stats_PacketStats_UI(self, phase, -1);
        return 1;
    case 30:
        NetDiag_CounterPage(self, phase, -1);
        return 1;
    case 31:
        NetDiag_QualityPage(self, phase, -1);
        return 1;
    case 9:
        BackupMemoryInitialize_Page(self, phase, -1);
        return 1;
    case 10:
        SystemInfo_UI(self, phase, -1);
        return 1;
    case 32:
        return 1;
    }
    return 0;
}

#pragma exceptions reset
