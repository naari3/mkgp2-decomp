/* 13 TUs merged by tools/merge_tus.py, .text 0x800668fc..0x8006b32c.
 * Each section is the preprocessed original TU with its names suffixed _pN
 * (tools/extab_user_renames.json maps the symbols back). */
/* ==== pool (tools/data2c.py) ==== */
#pragma cplusplus off
void CardSavedata_LoadShadow_TriggerUnused();
void CardSession_PollFsmStatus();
void PostRace_StartScoreEntryFlow();
void PostRace_StartScoreEntryFlow_WithCardSave();
void Sci2Card_BeginCleaning();
void Sci2Card_BeginReset();
void Sci2Card_PrintReceipt_PollState();
void Sci2Card_WaitCleaningComplete();
void Sci2Card_WaitResetComplete();
void Sci2Card_WriteTrackData_PollState();
void Sci2Card_WriteTrackData_StartFlow();
void ServiceMenu_Draw();
void ServiceMenu_Dtor();
void ServiceMenu_Tick();
void card_cleaning_state_machine();
void card_eject_init();
void card_eject_state_machine();
void card_read_state_machine();
void card_send_cleaning_cmd_init();
void card_send_read_cmd_init_dup_unused();
extern char lbl_8030E598[];
extern char lbl_8030E5A4[];
extern char lbl_8030E5B0[];
extern char lbl_8030E5E4[];
extern char lbl_8030E5F0[];
extern char lbl_8030EA38[];
extern char lbl_8030EA5C[];
extern char lbl_8030EA80[];
extern char lbl_8030EAA4[];
extern char lbl_8030EAC8[];
extern char lbl_8030EAEC[];
extern char lbl_8030EB10[];
extern char lbl_8030EB34[];
extern char lbl_8030EB58[];
extern char lbl_8030EB7C[];
extern char lbl_8030EBA0[];
extern char lbl_8030EBC4[];
extern char lbl_8030EBE8[];
extern char lbl_8030EC0C[];
extern char lbl_8030EC30[];
extern char lbl_8030EC54[];
extern char lbl_8030EC78[];
extern char lbl_8030EC9C[];
extern char lbl_8030ECC0[];
extern char lbl_8030ECE4[];
extern char lbl_8030ED08[];
extern char lbl_8030ED2C[];
extern char lbl_8030ED50[];
extern char lbl_8030ED74[];
extern char lbl_8030ED98[];
extern char lbl_8030EDBC[];
extern char lbl_8030EDE0[];
extern char lbl_8030EE04[];
extern char lbl_8030EE28[];
extern char lbl_8030EE4C[];
extern char lbl_8030EE70[];
extern char lbl_8030EE94[];
extern char lbl_8030EEB8[];
extern char lbl_8030EEDC[];
extern char lbl_8030EF00[];
extern char lbl_8030EF24[];
extern char lbl_8030EF50[];
extern char lbl_8030EF74[];
extern char lbl_8030EF98[];
extern char lbl_8030EFBC[];
extern char lbl_8030EFE0[];
extern char lbl_8030F004[];
extern char lbl_8030F028[];
extern char lbl_8030F04C[];
extern char lbl_8030F070[];
extern char lbl_8030F094[];
extern char lbl_8030F0B8[];
extern char lbl_8030F0DC[];
extern char lbl_8030F100[];
extern char lbl_8030F114[];
extern char lbl_8030F128[];
extern char lbl_8030F150[];
extern char lbl_8030F174[];
extern char lbl_8030F198[];
extern char lbl_8030F1BC[];
extern char lbl_8030F1E0[];
extern char lbl_8030F204[];
extern char lbl_8030F228[];
extern char lbl_8030F24C[];
extern char lbl_8030F270[];
extern char lbl_8030F294[];
extern char lbl_8030F2B8[];
extern char lbl_8030F2DC[];
extern char lbl_8030F300[];
extern char lbl_8030F324[];
extern char lbl_8030F348[];
extern char lbl_8030F36C[];
extern char lbl_8030F390[];
extern char lbl_8030F3B4[];
extern char lbl_8030F3D8[];
extern char lbl_8030F3FC[];
extern char lbl_8030F420[];
extern char lbl_8030F444[];
extern char lbl_8030F468[];
extern char lbl_8030F48C[];
extern char lbl_8030F4B0[];
extern char lbl_8030F4D4[];
extern char lbl_8030F4F8[];
extern char lbl_8030F51C[];
extern char lbl_8030F540[];
extern char lbl_8030F564[];
extern char lbl_8030F588[];
extern char lbl_8030F5AC[];
extern char lbl_8030F5D0[];
extern char lbl_8030F5F4[];
extern char lbl_8030F618[];
extern char lbl_8030F63C[];
extern char lbl_8030F660[];
extern char lbl_8030F684[];
extern char lbl_8030F6A8[];
extern char lbl_8030F6CC[];
extern char lbl_8030F6F0[];
extern char lbl_8030F714[];
extern char lbl_8030F738[];
extern char lbl_8030F75C[];
extern char lbl_8030F780[];
extern char lbl_8030F7A4[];
extern char lbl_8030F7C8[];
extern char lbl_8030F7EC[];
extern char lbl_8030F810[];
extern char lbl_8030F834[];
extern char lbl_8030F858[];
extern char lbl_8030F87C[];
extern char lbl_8030F8A0[];
extern char lbl_8030F8C4[];
extern char lbl_8030F8E8[];
extern char lbl_8030F90C[];
extern char lbl_8030F930[];
extern char lbl_8030F954[];
extern char lbl_8030F978[];
extern char lbl_8030F99C[];
extern char lbl_8030F9C0[];
extern char lbl_8030F9E4[];
extern char lbl_8030FA08[];
extern char lbl_8030FA2C[];
extern char lbl_8030FA50[];
extern char lbl_8030FA74[];
extern char lbl_8030FA98[];
extern char lbl_8030FABC[];
extern char lbl_8030FAE0[];
extern char lbl_8030FB04[];
extern char lbl_8030FB28[];
extern char lbl_8030FB4C[];
extern char lbl_8030FB70[];
extern char lbl_8030FB94[];
extern char lbl_8030FBB8[];
extern char lbl_8030FBDC[];
extern char lbl_8030FC00[];
extern char lbl_8030FC24[];
extern char lbl_8030FC48[];
extern char lbl_8030FC6C[];
extern char lbl_8030FC90[];
extern char lbl_8030FCB4[];
extern char lbl_8030FCD8[];
extern char lbl_8030FCFC[];
extern char lbl_8030FD20[];
extern char lbl_8030FD44[];
extern char lbl_8030FD68[];
extern char lbl_8030FD8C[];
extern char lbl_8030FDB0[];
extern char lbl_8030FDD4[];
extern char lbl_8030FDF8[];
extern char lbl_8030FE1C[];
extern char lbl_8030FE40[];
extern char lbl_8030FE64[];
extern char lbl_8030FE8C[];
extern char lbl_8030FEB0[];
extern char lbl_8030FED4[];
extern char lbl_8030FEF8[];
extern char lbl_8030FF1C[];
extern char lbl_8030FF40[];
extern char lbl_8030FF64[];
extern char lbl_8030FF88[];
extern char lbl_8030FFAC[];
extern char lbl_8030FFD0[];
extern char lbl_8030FFF4[];
extern char lbl_80310018[];
extern char lbl_8031003C[];
extern char lbl_80310060[];
extern char lbl_80310084[];
extern char lbl_806CEF48[];
extern char lbl_806CEF50[];
extern char lbl_806D2C70[];
extern char lbl_806D2C74[];
extern char lbl_806D2C7C[];
extern char lbl_806D2C84[];
extern char lbl_806D2C9C[];
extern char lbl_806D2CA4[];
extern char lbl_806D2CAC[];
extern char lbl_806D2CB4[];
extern char lbl_806D2CBC[];
extern char lbl_806D2CC4[];
extern char lbl_806D2CCC[];
extern char lbl_806D2CD4[];
extern char lbl_806D2CDC[];
extern char lbl_806D2CE4[];
extern char lbl_806D2CEC[];
extern char lbl_806D2CF4[];
static const char * lbl_803FBF80[3] = {
    (const char *)&lbl_806D2C70,
    (const char *)&lbl_806D2C74,
    (const char *)&lbl_8030E598,
};
static const char * lbl_803FBF8C[3] = {
    (const char *)&lbl_806D2C70,
    (const char *)&lbl_806D2C7C,
    (const char *)&lbl_8030E5A4,
};
static const char * lbl_803FBF98[3] = {
    (const char *)&lbl_806D2C70,
    (const char *)&lbl_806D2C84,
    (const char *)&lbl_8030E5B0,
};
static const char * lbl_803FBFA4[13] = {
    (const char *)&lbl_806D2C9C,
    (const char *)&lbl_806D2CA4,
    (const char *)&lbl_806D2CAC,
    (const char *)&lbl_806D2CB4,
    (const char *)&lbl_806D2CBC,
    (const char *)&lbl_806D2CC4,
    (const char *)&lbl_8030E5E4,
    (const char *)&lbl_806D2CCC,
    (const char *)&lbl_806D2CD4,
    (const char *)&lbl_8030E5F0,
    (const char *)&lbl_806D2CDC,
    (const char *)&lbl_806D2CE4,
    (const char *)&lbl_806D2CEC,
};
static int lbl_803FBFD8[16] = {
    (int)0x0,
    (int)0x4,
    (int)0x9,
    (int)0xE,
    (int)0x13,
    (int)0x18,
    (int)0x1D,
    (int)0x22,
    (int)0x27,
    (int)0x2C,
    (int)0x31,
    (int)0x3B,
    (int)0x45,
    (int)0x4F,
    (int)0x59,
    (int)0x63,
};

void *lbl_803FC018[48] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EA38,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EA5C,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EA80,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030EAA4,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030EAC8,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030EAEC,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030EB10,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030EB34,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030EB58,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030EB7C,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030EBA0,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030EBC4,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC0D8[39] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EA38,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EA5C,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EA80,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030EAA4,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030EAC8,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030EAEC,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030EB7C,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030EBA0,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030EBC4,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC174[87] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EC54,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EC78,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EC9C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030ECC0,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030ED08,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030ED2C,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030ED50,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030ED74,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EC54,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EC78,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EC9C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030ECC0,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030ED08,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030ED2C,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030ED50,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030ED74,
    (void *)0x2,
    (void *)0xF,
    (void *)&lbl_8030ED98,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC2D0[93] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EC54,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EC78,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EC9C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030ECC0,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030ED08,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030ED2C,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030EDBC,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xE,
    (void *)&lbl_8030ED74,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EC54,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EC78,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EC9C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030ECC0,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030ED08,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030ED2C,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030EDBC,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xE,
    (void *)&lbl_8030ED74,
    (void *)0x2,
    (void *)0xF,
    (void *)&lbl_8030ED98,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC444[81] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EC54,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EC78,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EC9C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030ECC0,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030ED08,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030ED2C,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030EDBC,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030ED74,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EC54,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EC78,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EC9C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030ECC0,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030ED08,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030ED2C,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030EDBC,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030ED74,
    (void *)0x2,
    (void *)0xF,
    (void *)&lbl_8030ED98,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC588[27] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EDE0,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EE04,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030EE28,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030EE4C,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC5F4[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EDE0,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EE70,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030EE94,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030EEB8,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030EEDC,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030EF00,
    (void *)0x2,
    (void *)0xB,
    (void *)&lbl_8030EF24,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC654[45] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EDE0,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EF50,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030EF74,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030ED50,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030EF98,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030EFBC,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030EFE0,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030F004,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030F028,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030ED74,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030F04C,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F070,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030F094,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030F0B8,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC708[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030EDE0,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F0DC,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030ED74,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030F04C,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC768[18] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F100,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F114,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030F128,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC7B0[27] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F150,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F174,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F198,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F1BC,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030F1E0,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC81C[39] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F204,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EC78,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F228,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F24C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030ECE4,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FC8B8[90] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F294,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F2B8,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F2DC,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030F300,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030F324,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030F348,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030F36C,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030F390,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030F3B4,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F294,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F2B8,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F2DC,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030F300,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030F324,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030F348,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030F36C,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030F390,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030F3B4,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030F3D8,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030F3FC,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCA20[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F420,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F468,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCA80[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F48C,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F4B0,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCAE0[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F4D4,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F4B0,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCB40[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F4F8,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F51C,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCBA0[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F540,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F564,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCC00[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F588,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030F5AC,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCC60[27] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F5D0,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F5F4,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F618,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCCCC[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F63C,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F618,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCD2C[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F660,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F684,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCD8C[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F270,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F6A8,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F444,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030F6CC,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCDEC[24] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F6F0,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030EC78,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F714,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F738,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCE4C[15] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030F75C,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F780,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCE88[39] = {
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030F7A4,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F7C8,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F7EC,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F810,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F834,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030F858,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030F87C,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030F8A0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FCF24[60] = {
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030F8E8,
    (void *)0x3,
    (void *)0x2,
    (void *)&lbl_8030F90C,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F930,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F954,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030F978,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030F99C,
    (void *)0x2,
    (void *)0x7,
    (void *)&lbl_8030F9C0,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030F9E4,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FA08,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FA2C,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FA50,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030FA74,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030FA98,
    (void *)0x3,
    (void *)0xE,
    (void *)&lbl_8030FABC,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030FAE0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FD014[45] = {
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030F8E8,
    (void *)0x2,
    (void *)0x2,
    (void *)&lbl_8030F9C0,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F9E4,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030FA08,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030FA2C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030FA50,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FA74,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FA98,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FABC,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FAE0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FD0C8[45] = {
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FB04,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FB28,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F858,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F930,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030FB4C,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FB70,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FB94,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FBB8,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FBDC,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030FC00,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FD17C[360] = {
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FB04,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FB28,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F858,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030FB4C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030FB70,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FB94,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FBB8,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FBDC,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FC00,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FC24,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FC48,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F858,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030FC6C,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FC90,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FCB4,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FCD8,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FCFC,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FD20,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030FD44,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030FD68,
    (void *)0x3,
    (void *)0xE,
    (void *)&lbl_8030FD8C,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030FDB0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FC24,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FC48,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F858,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030FC6C,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FC90,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FCB4,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FCD8,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FCFC,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FD20,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030FD44,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030FD68,
    (void *)0x3,
    (void *)0xE,
    (void *)&lbl_8030FDD4,
    (void *)0x3,
    (void *)0xF,
    (void *)&lbl_8030FDB0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FC24,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FC48,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F858,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030FC90,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030FCB4,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FCD8,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FCFC,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FD20,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FD44,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FD68,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030FDD4,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030FDB0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FDF8,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FE1C,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F858,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F930,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030FC90,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FCB4,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FCD8,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FCFC,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FD20,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FD44,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030FD68,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030FD8C,
    (void *)0x3,
    (void *)0xE,
    (void *)&lbl_8030FDB0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FDF8,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FE1C,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F858,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030F930,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030FC90,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FCB4,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FCD8,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FCFC,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FD20,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FD44,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030FD68,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030FDD4,
    (void *)0x3,
    (void *)0xE,
    (void *)&lbl_8030FDB0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FDF8,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FE1C,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030F858,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030FC90,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030FCB4,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FCD8,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FCFC,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FD20,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FD44,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FD68,
    (void *)0x3,
    (void *)0xC,
    (void *)&lbl_8030FDD4,
    (void *)0x3,
    (void *)0xD,
    (void *)&lbl_8030FDB0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FD71C[48] = {
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FE40,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FE1C,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030FE64,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030FCB4,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030FCD8,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030FCFC,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FD20,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FD44,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FD68,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FD8C,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FDB0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FD7DC[174] = {
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FE40,
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FE1C,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_8030FE64,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8030FCB4,
    (void *)0x3,
    (void *)0x5,
    (void *)&lbl_8030FCD8,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_8030FCFC,
    (void *)0x3,
    (void *)0x7,
    (void *)&lbl_8030FD20,
    (void *)0x3,
    (void *)0x8,
    (void *)&lbl_8030FD44,
    (void *)0x3,
    (void *)0x9,
    (void *)&lbl_8030FD68,
    (void *)0x3,
    (void *)0xA,
    (void *)&lbl_8030FDD4,
    (void *)0x3,
    (void *)0xB,
    (void *)&lbl_8030FDB0,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FE8C,
    (void *)0x1,
    (void *)0x2,
    (void *)&lbl_8030FEB0,
    (void *)0x2,
    (void *)0x4,
    (void *)&lbl_8030FED4,
    (void *)0x4,
    (void *)0x5,
    (void *)&lbl_8030FEF8,
    (void *)0x4,
    (void *)0x6,
    (void *)&lbl_8030FF1C,
    (void *)0x4,
    (void *)0x7,
    (void *)&lbl_8030FF40,
    (void *)0x4,
    (void *)0x8,
    (void *)&lbl_806D2CF4,
    (void *)0x2,
    (void *)0x9,
    (void *)&lbl_8030FF64,
    (void *)0x4,
    (void *)0xA,
    (void *)&lbl_8030FEF8,
    (void *)0x4,
    (void *)0xB,
    (void *)&lbl_8030FF1C,
    (void *)0x4,
    (void *)0xC,
    (void *)&lbl_8030FF40,
    (void *)0x4,
    (void *)0xD,
    (void *)&lbl_806D2CF4,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030F094,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FE8C,
    (void *)0x1,
    (void *)0x2,
    (void *)&lbl_8030FEB0,
    (void *)0x2,
    (void *)0x4,
    (void *)&lbl_8030FED4,
    (void *)0x4,
    (void *)0x5,
    (void *)&lbl_8030FF88,
    (void *)0x4,
    (void *)0x6,
    (void *)&lbl_8030FFAC,
    (void *)0x4,
    (void *)0x7,
    (void *)&lbl_8030FFD0,
    (void *)0x4,
    (void *)0x8,
    (void *)&lbl_806D2CF4,
    (void *)0x2,
    (void *)0x9,
    (void *)&lbl_8030FF64,
    (void *)0x4,
    (void *)0xA,
    (void *)&lbl_8030FF88,
    (void *)0x4,
    (void *)0xB,
    (void *)&lbl_8030FFAC,
    (void *)0x4,
    (void *)0xC,
    (void *)&lbl_8030FFD0,
    (void *)0x4,
    (void *)0xD,
    (void *)&lbl_806D2CF4,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030F094,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0,
    (void *)0x3,
    (void *)0x0,
    (void *)&lbl_8030FE8C,
    (void *)0x1,
    (void *)0x2,
    (void *)&lbl_8030FEB0,
    (void *)0x4,
    (void *)0x4,
    (void *)&lbl_8030FF88,
    (void *)0x4,
    (void *)0x5,
    (void *)&lbl_8030FFAC,
    (void *)0x4,
    (void *)0x6,
    (void *)&lbl_8030FFD0,
    (void *)0x4,
    (void *)0x7,
    (void *)&lbl_806D2CF4,
    (void *)0x3,
    (void *)0x10,
    (void *)&lbl_8030F8C4,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030F094,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDA94[21] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_8030FFF4,
    (void *)0x3,
    (void *)0x3,
    (void *)&lbl_80310018,
    (void *)0x3,
    (void *)0x4,
    (void *)&lbl_8031003C,
    (void *)0x3,
    (void *)0x6,
    (void *)&lbl_80310060,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EBE8,
    (void *)0x3,
    (void *)0x13,
    (void *)&lbl_8030F094,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDAE8[12] = {
    (void *)0x3,
    (void *)0x1,
    (void *)&lbl_80310084,
    (void *)0x3,
    (void *)0x11,
    (void *)&lbl_8030EC0C,
    (void *)0x3,
    (void *)0x12,
    (void *)&lbl_8030EC30,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
typedef unsigned char (*RenewTick_p13)();
struct RenewStep_p13 { RenewTick_p13 tick_p13; unsigned char checkError_p13; unsigned char pad_p13[3]; };
typedef unsigned char (*ReprintTick_p15)();
struct ReprintStep_p15 { ReprintTick_p15 tick_p15; unsigned char checkError_p15; unsigned char pad_p15[3]; };
typedef unsigned char (*ReprintTick_p16)();
struct ReprintStep_p16 { ReprintTick_p16 tick_p16; unsigned char checkError_p16; unsigned char pad_p16[3]; };
struct CardStep_p17 {
unsigned char (*fn_p17)(void);
unsigned char checkError_p17;
};
struct CardCheckStep_p18 {
unsigned char (*fn_p18)(void);
unsigned char checkError_p18;
};
typedef unsigned char (*PrintTick_p19)();
struct PrintStep_p19 { PrintTick_p19 tick_p19; unsigned char checkError_p19; unsigned char pad_p19[3]; };
typedef unsigned char (*DispenseTick_p20)();
struct DispenseStep_p20 { DispenseTick_p20 tick_p20; unsigned char checkError_p20; unsigned char pad_p20[3]; };
typedef unsigned char (*ReadWriteTick_p21)();
struct ReadWriteStep_p21 { ReadWriteTick_p21 tick_p21; unsigned char checkError_p21; unsigned char pad_p21[3]; };
typedef unsigned char (*CleaningTick_p22)();
struct CleaningStep_p22 {
CleaningTick_p22 tick_p22;
unsigned char checkError_p22;
unsigned char pad_p22[3];
};
void *lbl_803FDB18[16] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&CardSavedata_LoadShadow_TriggerUnused,
    (void *)0x0,
    (void *)&CardSession_PollFsmStatus,
    (void *)0x1000000,
    (void *)&PostRace_StartScoreEntryFlow,
    (void *)0x0,
    (void *)&Sci2Card_PrintReceipt_PollState,
    (void *)0x0,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
struct CleaningStep_p22 lbl_803FDB58[8] = {
    { 0, 0 },
    { (unsigned char (*)())&card_send_cleaning_cmd_init, 0 },
    { (unsigned char (*)())&card_cleaning_state_machine, 1 },
    { (unsigned char (*)())&Sci2Card_BeginReset, 0 },
    { (unsigned char (*)())&Sci2Card_WaitCleaningComplete, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 1 },
    { 0, 0 }
};
struct ReadWriteStep_p21 lbl_803FDB98[10] = {
    { 0, 0 },
    { (unsigned char (*)())&Sci2Card_BeginCleaning, 0 },
    { (unsigned char (*)())&Sci2Card_WaitResetComplete, 1 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_StartFlow, 0 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_PollState, 1 },
    { (unsigned char (*)())&card_send_read_cmd_init_dup_unused, 0 },
    { (unsigned char (*)())&card_read_state_machine, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 1 },
    { 0, 0 }
};
struct DispenseStep_p20 lbl_803FDBE8[6] = {
    { 0, 0 },
    { (unsigned char (*)())&Sci2Card_BeginCleaning, 0 },
    { (unsigned char (*)())&Sci2Card_WaitResetComplete, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 1 },
    { 0, 0 }
};
struct PrintStep_p19 lbl_803FDC18[8] = {
    { 0, 0 },
    { (unsigned char (*)())&Sci2Card_BeginCleaning, 0 },
    { (unsigned char (*)())&Sci2Card_WaitResetComplete, 1 },
    { (unsigned char (*)())&PostRace_StartScoreEntryFlow_WithCardSave, 0 },
    { (unsigned char (*)())&Sci2Card_PrintReceipt_PollState, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 1 },
    { 0, 0 }
};
struct CardCheckStep_p18 lbl_803FDC58[8] = {
    { 0, 0 },
    { (unsigned char (*)())&card_send_cleaning_cmd_init, 0 },
    { (unsigned char (*)())&card_cleaning_state_machine, 0 },
    { (unsigned char (*)())&card_send_read_cmd_init_dup_unused, 0 },
    { (unsigned char (*)())&card_read_state_machine, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 0 },
    { 0, 0 }
};
struct CardStep_p17 lbl_803FDC98[20] = {
    { 0, 0 },
    { (unsigned char (*)())&card_send_cleaning_cmd_init, 0 },
    { (unsigned char (*)())&card_cleaning_state_machine, 0 },
    { (unsigned char (*)())&card_send_read_cmd_init_dup_unused, 0 },
    { (unsigned char (*)())&card_read_state_machine, 1 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_StartFlow, 0 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_PollState, 1 },
    { (unsigned char (*)())&PostRace_StartScoreEntryFlow, 0 },
    { (unsigned char (*)())&Sci2Card_PrintReceipt_PollState, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 0 },
    { (unsigned char (*)())&Sci2Card_BeginCleaning, 0 },
    { (unsigned char (*)())&Sci2Card_WaitResetComplete, 1 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_StartFlow, 0 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_PollState, 1 },
    { (unsigned char (*)())&PostRace_StartScoreEntryFlow, 0 },
    { (unsigned char (*)())&Sci2Card_PrintReceipt_PollState, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 0 },
    { 0, 0 }
};
struct ReprintStep_p16 lbl_803FDD38[10] = {
    { 0, 0 },
    { (unsigned char (*)())&card_send_cleaning_cmd_init, 0 },
    { (unsigned char (*)())&card_cleaning_state_machine, 0 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_StartFlow, 0 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_PollState, 1 },
    { (unsigned char (*)())&PostRace_StartScoreEntryFlow, 0 },
    { (unsigned char (*)())&Sci2Card_PrintReceipt_PollState, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 0 },
    { 0, 0 }
};
struct ReprintStep_p15 lbl_803FDD88[10] = {
    { 0, 0 },
    { (unsigned char (*)())&card_send_cleaning_cmd_init, 0 },
    { (unsigned char (*)())&card_cleaning_state_machine, 0 },
    { (unsigned char (*)())&card_send_read_cmd_init_dup_unused, 0 },
    { (unsigned char (*)())&card_read_state_machine, 1 },
    { (unsigned char (*)())&PostRace_StartScoreEntryFlow, 0 },
    { (unsigned char (*)())&Sci2Card_PrintReceipt_PollState, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 0 },
    { 0, 0 }
};
struct RenewStep_p13 lbl_803FDDD8[16] = {
    { 0, 0 },
    { (unsigned char (*)())&card_send_cleaning_cmd_init, 0 },
    { (unsigned char (*)())&card_cleaning_state_machine, 0 },
    { (unsigned char (*)())&card_send_read_cmd_init_dup_unused, 0 },
    { (unsigned char (*)())&card_read_state_machine, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 0 },
    { (unsigned char (*)())&Sci2Card_BeginCleaning, 0 },
    { (unsigned char (*)())&Sci2Card_WaitResetComplete, 1 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_StartFlow, 0 },
    { (unsigned char (*)())&Sci2Card_WriteTrackData_PollState, 1 },
    { (unsigned char (*)())&PostRace_StartScoreEntryFlow, 0 },
    { (unsigned char (*)())&Sci2Card_PrintReceipt_PollState, 1 },
    { (unsigned char (*)())&card_eject_init, 0 },
    { (unsigned char (*)())&card_eject_state_machine, 0 },
    { 0, 0 }
};
void *lbl_803FDE58[3] = {
    (void *)&lbl_806CEF48,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDE64[5] = {
    (void *)&lbl_806CEF50,
    (void *)0x0,
    (void *)&ServiceMenu_Tick,
    (void *)&ServiceMenu_Draw,
    (void *)&ServiceMenu_Dtor
};
#pragma cplusplus reset

/* ==== game/UI_PageDispatcher.c (0x800668fc) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
typedef struct TestPage_p0 {
unsigned char pad_0_p0[0x10];
unsigned int page_p0;
unsigned char pad_14_p0[0x20];
int variant_p0;
} TestPage_p0;
extern void BackupMemoryInitialize_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CabinetSetting_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CameraTest_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardCreate_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardDataCheck_UI_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardDataTransfer_UI_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardRW_CleaningTest_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardRW_DataRepair_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardRW_DispenseTest_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardRW_HardwareInit_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardRW_PrintTest_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardRW_ReadWriteTest_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardRW_Renew_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardRW_Reprint_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void CardRW_TestTopMenu_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void ClockSetting_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void GameSetting_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void GameSetting_Page_VariantA_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void GameSetting_Page_VariantB_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void GameTestTopMenu_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void HandleInitialize_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void LampTestIndiv_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void LampTest_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void MonitorTest_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void NetDiag_CounterPage_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void NetDiag_PacketPage_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void NetDiag_PacketRatioPage_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void NetDiag_QualityPage_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void OperationTime_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void SpeakerTest_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void Stats_Display_UI_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void Stats_PacketStats_UI_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void SwitchTest_Page_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);
extern void SystemInfo_UI_p0(TestPage_p0 *self_p0, int phase_p0, int arg_p0);

#pragma exceptions on

int UI_PageDispatcher(TestPage_p0 *self_p0, int phase_p0)
{
switch (self_p0->page_p0) {
case 0:
GameTestTopMenu_Page_p0(self_p0, phase_p0, -1);
return 1;
case 1:
if (self_p0->variant_p0 == 0) {
GameSetting_Page_p0(self_p0, phase_p0, -1);
} else if (self_p0->variant_p0 == 1) {
GameSetting_Page_VariantB_p0(self_p0, phase_p0, -1);
} else {
GameSetting_Page_VariantA_p0(self_p0, phase_p0, -1);
}
return 1;
case 2:
MonitorTest_Page_p0(self_p0, phase_p0, -1);
return 1;
case 11:
HandleInitialize_Page_p0(self_p0, phase_p0, -1);
return 1;
case 12:
SwitchTest_Page_p0(self_p0, phase_p0, -1);
return 1;
case 13:
LampTestIndiv_Page_p0(self_p0, phase_p0, -1);
return 1;
case 14:
CameraTest_Page_p0(self_p0, phase_p0, -1);
return 1;
case 3:
LampTest_Page_p0(self_p0, phase_p0, -1);
return 1;
case 4:
SpeakerTest_Page_p0(self_p0, phase_p0, -1);
return 1;
case 5:
CardRW_TestTopMenu_Page_p0(self_p0, phase_p0, -1);
return 1;
case 15:
CardRW_CleaningTest_Page_p0(self_p0, phase_p0, -1);
return 1;
case 16:
CardRW_ReadWriteTest_Page_p0(self_p0, phase_p0, -1);
return 1;
case 17:
CardRW_DispenseTest_Page_p0(self_p0, phase_p0, -1);
return 1;
case 18:
CardRW_PrintTest_Page_p0(self_p0, phase_p0, -1);
return 1;
case 19:
CardDataCheck_UI_p0(self_p0, phase_p0, -1);
return 1;
case 20:
CardDataTransfer_UI_p0(self_p0, phase_p0, -1);
return 1;
case 21:
CardRW_DataRepair_Page_p0(self_p0, phase_p0, -1);
return 1;
case 22:
CardRW_Reprint_Page_p0(self_p0, phase_p0, -1);
return 1;
case 23:
CardRW_HardwareInit_Page_p0(self_p0, phase_p0, -1);
return 1;
case 24:
CardRW_Renew_Page_p0(self_p0, phase_p0, -1);
return 1;
case 25:
CardCreate_Page_p0(self_p0, phase_p0, -1);
return 1;
case 6:
CabinetSetting_Page_p0(self_p0, phase_p0, -1);
return 1;
case 7:
ClockSetting_Page_p0(self_p0, phase_p0, -1);
return 1;
case 8:
OperationTime_Page_p0(self_p0, phase_p0, -1);
return 1;
case 26:
NetDiag_PacketRatioPage_p0(self_p0, phase_p0, -1);
return 1;
case 27:
Stats_Display_UI_p0(self_p0, phase_p0, -1);
return 1;
case 28:
NetDiag_PacketPage_p0(self_p0, phase_p0, -1);
return 1;
case 29:
Stats_PacketStats_UI_p0(self_p0, phase_p0, -1);
return 1;
case 30:
NetDiag_CounterPage_p0(self_p0, phase_p0, -1);
return 1;
case 31:
NetDiag_QualityPage_p0(self_p0, phase_p0, -1);
return 1;
case 9:
BackupMemoryInitialize_Page_p0(self_p0, phase_p0, -1);
return 1;
case 10:
SystemInfo_UI_p0(self_p0, phase_p0, -1);
return 1;
case 32:
return 1;
}
return 0;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/SystemInfo_UI.cpp (0x80066b74) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus on
struct InputPlayer_p1 {
virtual void v0_p1();
virtual void v1_p1();
virtual float v2_p1();
virtual void v3_p1();
virtual float StickRight_p1();
virtual float StickLeft_p1();
virtual unsigned char Pressed_p1(int mask_p1);
virtual unsigned char Held_p1(int mask_p1);
};
struct MenuItem_p1 {
int x_p1;
int y_p1;
const char *text_p1;
};
struct TestPage_p1 {
unsigned char pad_0_p1[8];
int blink_p1;
unsigned char pad_C_p1[4];
int next_p1;
unsigned char pad_14_p1[4];
int cursor_p1;
int sub_p1;
unsigned char pad_20_p1[0x14];
int variant_p1;
unsigned char pad_38_p1[0x238];
void *text_p1;
void *data_p1;
};
extern "C"{
extern char lbl_8030E598_p1[];
void *GetInputManager_p1(void);
InputPlayer_p1 *InputMgr_GetPlayer_p1(void *, int);
void DrawText_p1(void *ctx_p1, int x_p1, int y_p1, int color_p1, float scale_p1, const char *fmt_p1, ...);
}
static inline void TestPage_DrawItems_p1(TestPage_p1 *self_p1, MenuItem_p1 *it_p1, int sel_p1)
{
int i_p1;
for (i_p1 = 0; it_p1[i_p1].text_p1 != 0; i_p1++) {
if (i_p1 != sel_p1 || self_p1->blink_p1 <= 0x1E) {
if (self_p1->text_p1 != 0) {
DrawText_p1(self_p1->text_p1, it_p1[i_p1].x_p1 * 14, it_p1[i_p1].y_p1 * 24, 7, 1.0f, it_p1[i_p1].text_p1);
}
}
}
}
typedef long long OSTime_p1;
struct OSCalendarTime_p1 {
int sec_p1;
int min_p1;
int hour_p1;
int mday_p1;
int mon_p1;
int year_p1;
int wday_p1;
int yday_p1;
int msec_p1;
int usec_p1;
};
struct DayNames_p1 {
const char *name_p1[7];
};
struct VariantNames_p1 {
const char *name_p1[3];
};
extern "C"{

extern const char lbl_806D2D5C_p1[6];
extern const char lbl_806D2D64_p1[3];
extern int lbl_806D1118_p1;
extern int lbl_806D111C_p1;
void *BootStateStruct_Get_p1(void);
OSTime_p1 OSGetTime_p1(void);
void OSTicksToCalendarTime_p1(OSTime_p1 ticks_p1, OSCalendarTime_p1 *td_p1);
}

#pragma exceptions on

extern "C"int SystemInfo_UI(TestPage_p1 *self_p1, int phase_p1)
{
char *pool_p1 = lbl_8030E598_p1;
DayNames_p1 days_p1;
VariantNames_p1 variants_p1;
OSCalendarTime_p1 t_p1;
void *boot_p1;
if (phase_p1 == 1) {
if (InputMgr_GetPlayer_p1(GetInputManager_p1(), 0)->Pressed_p1(0x1000)) {
self_p1->next_p1 = 0;
}
}
if (phase_p1 == 2) {
TestPage_DrawItems_p1(self_p1, (*(MenuItem_p1 (*)[])&lbl_803FDA94), 4);
if (self_p1->text_p1 != 0) {
days_p1 = *(DayNames_p1 *)(pool_p1 + 0x1B2C);
variants_p1 = *(VariantNames_p1 *)(pool_p1 + 0x1B48);
boot_p1 = BootStateStruct_Get_p1();
OSTicksToCalendarTime_p1(OSGetTime_p1(), &t_p1);
DrawText_p1(self_p1->text_p1, 0xB6, 0x48, 7, 1.0f, pool_p1 + 0x1C90, t_p1.year_p1, t_p1.mon_p1 + 1, t_p1.mday_p1,
days_p1.name_p1[t_p1.wday_p1], t_p1.hour_p1, t_p1.min_p1, t_p1.sec_p1);
if (boot_p1 != 0) {
if (self_p1->variant_p1 == 0) {
DrawText_p1(self_p1->text_p1, 0xB6, 0x60, 7, 1.0f, pool_p1 + 0x1CB4);
} else if (self_p1->variant_p1 == 1) {
DrawText_p1(self_p1->text_p1, 0xB6, 0x60, 7, 1.0f, pool_p1 + 0x1CCC);
} else {
DrawText_p1(self_p1->text_p1, 0xB6, 0x60, 7, 1.0f, pool_p1 + 0x1CE4);
}
DrawText_p1(self_p1->text_p1, 0xB6, 0x78, 7, 1.0f, lbl_806D2D5C_p1, lbl_806D111C_p1, lbl_806D1118_p1);
}
DrawText_p1(self_p1->text_p1, 0xB6, 0x90, 7, 1.0f, lbl_806D2D64_p1, variants_p1.name_p1[self_p1->variant_p1]);
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/BackupMemoryInitialize_Page.cpp (0x80066e10) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus on
struct InputPlayer_p2 {
virtual void v0_p2();
virtual void v1_p2();
virtual float v2_p2();
virtual void v3_p2();
virtual float StickRight_p2();
virtual float StickLeft_p2();
virtual unsigned char Pressed_p2(int mask_p2);
virtual unsigned char Held_p2(int mask_p2);
};
struct MenuItem_p2 {
int x_p2;
int y_p2;
const char *text_p2;
};
struct TestPage_p2 {
unsigned char pad_0_p2[8];
int blink_p2;
unsigned char pad_C_p2[4];
int next_p2;
unsigned char pad_14_p2[4];
int cursor_p2;
int sub_p2;
unsigned char pad_20_p2[0x14];
int variant_p2;
unsigned char pad_38_p2[0x238];
void *text_p2;
void *data_p2;
};
extern "C"{
extern char lbl_8030E598_p2[];
void *GetInputManager_p2(void);
InputPlayer_p2 *InputMgr_GetPlayer_p2(void *, int);
void DrawText_p2(void *ctx_p2, int x_p2, int y_p2, int color_p2, float scale_p2, const char *fmt_p2, ...);
}
static inline void TestPage_DrawItems_p2(TestPage_p2 *self_p2, MenuItem_p2 *it_p2, int sel_p2)
{
int i_p2;
for (i_p2 = 0; it_p2[i_p2].text_p2 != 0; i_p2++) {
if (i_p2 != sel_p2 || self_p2->blink_p2 <= 0x1E) {
if (self_p2->text_p2 != 0) {
DrawText_p2(self_p2->text_p2, it_p2[i_p2].x_p2 * 14, it_p2[i_p2].y_p2 * 24, 7, 1.0f, it_p2[i_p2].text_p2);
}
}
}
}
extern "C"{

extern const char lbl_806D2D68_p2[5];
void Backup_ClearHiScores_p2(void);
void Backup_ClearBookkeeping_p2(void);
void Backup_ClearAll_p2(void);
void Backup_PublishShadowCopy_Inline_p2(void);
}

#pragma exceptions on

extern "C"int BackupMemoryInitialize_Page(TestPage_p2 *self_p2, int phase_p2)
{
char *pool_p2 = lbl_8030E598_p2;
InputPlayer_p2 *pl_p2;
if (phase_p2 == 0) {
self_p2->cursor_p2 = 3;
self_p2->sub_p2 = 0;
}
if (phase_p2 == 1) {
pl_p2 = InputMgr_GetPlayer_p2(GetInputManager_p2(), 0);
if (self_p2->sub_p2 == 0) {
if (pl_p2->Pressed_p2(0x800)) {
self_p2->blink_p2 = 0x1F;
if (++self_p2->cursor_p2 > 3) {
self_p2->cursor_p2 = 0;
}
}
if (pl_p2->Pressed_p2(0x1000)) {
self_p2->blink_p2 = 0x1F;
if (self_p2->cursor_p2 == 3) {
self_p2->next_p2 = 0;
} else {
self_p2->sub_p2 = 1;
}
}
} else if (self_p2->sub_p2 == 1 || self_p2->sub_p2 == 2) {
if (pl_p2->Pressed_p2(0x800)) {
self_p2->blink_p2 = 0x1F;
if (++self_p2->sub_p2 > 2) {
self_p2->sub_p2 = 1;
}
}
if (pl_p2->Pressed_p2(0x1000)) {
self_p2->blink_p2 = 0x1F;
if (self_p2->sub_p2 == 1) {
self_p2->sub_p2 = 0;
} else {
self_p2->sub_p2 = 3;
if (self_p2->cursor_p2 == 0) {
Backup_ClearHiScores_p2();
}
if (self_p2->cursor_p2 == 1) {
Backup_ClearBookkeeping_p2();
}
if (self_p2->cursor_p2 == 2) {
Backup_ClearAll_p2();
}
Backup_PublishShadowCopy_Inline_p2();
}
}
} else if (++self_p2->sub_p2 > 0x5A) {
self_p2->sub_p2 = 0;
}
}
if (phase_p2 == 2) {
TestPage_DrawItems_p2(self_p2, (*(MenuItem_p2 (*)[])&lbl_803FDAE8), -1);
if (self_p2->text_p2 != 0) {
if (self_p2->cursor_p2 == 0) {
if (self_p2->sub_p2 == 0) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0x48, 7, 1.0f, pool_p2 + 0x1CFC);
}
} else if (self_p2->sub_p2 == 1) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0x48, 7, 1.0f, pool_p2 + 0x1D10);
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0x48, 7, 1.0f, pool_p2 + 0x1D2C);
}
} else if (self_p2->sub_p2 == 2) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0x48, 7, 1.0f, pool_p2 + 0x1D44);
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0x48, 7, 1.0f, pool_p2 + 0x1D2C);
}
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0x48, 7, 1.0f, pool_p2 + 0x1D60);
}
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0x48, 7, 1.0f, pool_p2 + 0x1CFC);
}
if (self_p2->cursor_p2 == 1) {
if (self_p2->sub_p2 == 0) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0x78, 7, 1.0f, pool_p2 + 0x1D80);
}
} else if (self_p2->sub_p2 == 1) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0x78, 7, 1.0f, pool_p2 + 0x1D98);
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0x78, 7, 1.0f, pool_p2 + 0x1DB4);
}
} else if (self_p2->sub_p2 == 2) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0x78, 7, 1.0f, pool_p2 + 0x1DCC);
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0x78, 7, 1.0f, pool_p2 + 0x1DB4);
}
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0x78, 7, 1.0f, pool_p2 + 0x1DEC);
}
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0x78, 7, 1.0f, pool_p2 + 0x1D80);
}
if (self_p2->cursor_p2 == 2) {
if (self_p2->sub_p2 == 0) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0xA8, 7, 1.0f, pool_p2 + 0x1E10);
}
} else if (self_p2->sub_p2 == 1) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0xA8, 7, 1.0f, pool_p2 + 0x1E2C);
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0xA8, 7, 1.0f, pool_p2 + 0x1E4C);
}
} else if (self_p2->sub_p2 == 2) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0xA8, 7, 1.0f, pool_p2 + 0x1E68);
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0xA8, 7, 1.0f, pool_p2 + 0x1E4C);
}
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0xA8, 7, 1.0f, pool_p2 + 0x1E88);
}
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0xA8, 7, 1.0f, pool_p2 + 0x1E10);
}
if (self_p2->cursor_p2 == 3) {
if (self_p2->blink_p2 <= 0x1E) {
DrawText_p2(self_p2->text_p2, 0x2A, 0xF0, 7, 1.0f, lbl_806D2D68_p2);
}
} else {
DrawText_p2(self_p2->text_p2, 0x2A, 0xF0, 7, 1.0f, lbl_806D2D68_p2);
}
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/NetDiag_QualityPage.c (0x80067494) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on

struct InputPlayer_p3 {
virtual void v0_p3();
virtual void v1_p3();
virtual float v2_p3();
virtual void v3_p3();
virtual float StickRight_p3();
virtual float StickLeft_p3();
virtual unsigned char Pressed_p3(int mask_p3);
virtual unsigned char Held_p3(int mask_p3);
};
struct MenuItem_p3 {
int x_p3;
int y_p3;
const char *text_p3;
};
struct TestPage_p3 {
unsigned char pad_0_p3[8];
int blink_p3;
unsigned char pad_C_p3[4];
int next_p3;
unsigned char pad_14_p3[4];
int cursor_p3;
int sub_p3;
unsigned char pad_20_p3[0x14];
int variant_p3;
unsigned char pad_38_p3[0x238];
void *text_p3;
void *data_p3;
};
extern "C"{
extern char lbl_8030E598_p3[];
void *GetInputManager_p3(void);
InputPlayer_p3 *InputMgr_GetPlayer_p3(void *, int);
void DrawText_p3(void *ctx_p3, int x_p3, int y_p3, int color_p3, float scale_p3, const char *fmt_p3, ...);
}
static inline void TestPage_DrawItems_p3(TestPage_p3 *self_p3, MenuItem_p3 *it_p3, int sel_p3)
{
int i_p3;
for (i_p3 = 0; it_p3[i_p3].text_p3 != 0; i_p3++) {
if (i_p3 != sel_p3 || self_p3->blink_p3 <= 0x1E) {
if (self_p3->text_p3 != 0) {
DrawText_p3(self_p3->text_p3, it_p3[i_p3].x_p3 * 14, it_p3[i_p3].y_p3 * 24, 7, 1.0f, it_p3[i_p3].text_p3);
}
}
}
}
extern "C"{

extern const char lbl_80310448_p3[], lbl_80310478_p3[];
extern const float lbl_806D2D44_p3, lbl_806D2D70_p3, lbl_806D2D74_p3;
int OperationTime_Page_p3(TestPage_p3 *self_p3, int phase_p3, int arg_p3);
int NetDiag_QualityPage(TestPage_p3 *self_p3, int phase_p3, int arg_p3)
{
char *tables_p3 = (*(char (*)[])&lbl_803FBF80);
if (phase_p3 == 0) self_p3->cursor_p3 = 0;
if (phase_p3 == 1) {
InputPlayer_p3 *input_p3 = InputMgr_GetPlayer_p3(GetInputManager_p3(), 0);
if (input_p3->Pressed_p3(0x800)) {
self_p3->blink_p3 = 31;
if (++self_p3->cursor_p3 > 1) self_p3->cursor_p3 = 0;
}
if (input_p3->Pressed_p3(0x1000)) {
if (self_p3->cursor_p3 == 0) {
self_p3->next_p3 = 8;
OperationTime_Page_p3(self_p3, 0, -1);
} else self_p3->next_p3 = 0;
}
}
if (phase_p3 == 2) {
unsigned int *stats_p3 = (unsigned int *)self_p3->data_p3;
float a0_p3 = (float)stats_p3[0x47C/4] / (float)stats_p3[0x288/4];
float a1_p3 = (float)stats_p3[0x484/4] / (float)stats_p3[0x288/4];
float a2_p3 = (float)stats_p3[0x48C/4] / (float)stats_p3[0x288/4];
float a3_p3 = (float)stats_p3[0x494/4] / (float)stats_p3[0x288/4];
float a4_p3 = (float)stats_p3[0x49C/4] / (float)stats_p3[0x288/4];
float a5_p3 = (float)stats_p3[0x4A4/4] / (float)stats_p3[0x288/4];
float a6_p3 = (float)stats_p3[0x4AC/4] / (float)stats_p3[0x288/4];
float a7_p3 = (float)stats_p3[0x4B4/4] / (float)stats_p3[0x288/4];
float a8_p3 = (float)stats_p3[0x4BC/4] / (float)stats_p3[0x288/4];
float a9_p3 = (float)stats_p3[0x4C4/4] / (float)stats_p3[0x288/4];
float a10_p3 = (float)stats_p3[0x4CC/4] / (float)stats_p3[0x288/4];
float a11_p3 = (float)stats_p3[0x4D4/4] / (float)stats_p3[0x288/4];
float a12_p3 = (float)stats_p3[0x4DC/4] / (float)stats_p3[0x288/4];
if (stats_p3[0x288/4] == 0) {
a0_p3 = a1_p3 = a2_p3 = a3_p3 = a4_p3 = a5_p3 = a6_p3 = a7_p3 = a8_p3 = a9_p3 = a10_p3 = a11_p3 = a12_p3 = lbl_806D2D70_p3;
}
if (self_p3->variant_p3 != 2) {
unsigned int *s_p3 = (unsigned int *)self_p3->data_p3;
float b0_p3 = (float)s_p3[0x478/4] / (float)s_p3[0x290/4];
float b1_p3 = (float)s_p3[0x480/4] / (float)s_p3[0x290/4];
float b2_p3 = (float)s_p3[0x488/4] / (float)s_p3[0x290/4];
float b3_p3 = (float)s_p3[0x490/4] / (float)s_p3[0x290/4];
float b4_p3 = (float)s_p3[0x498/4] / (float)s_p3[0x290/4];
float b5_p3 = (float)s_p3[0x4A0/4] / (float)s_p3[0x290/4];
float b6_p3 = (float)s_p3[0x4A8/4] / (float)s_p3[0x290/4];
float b7_p3 = (float)s_p3[0x4B0/4] / (float)s_p3[0x290/4];
float b8_p3 = (float)s_p3[0x4B8/4] / (float)s_p3[0x290/4];
float b9_p3 = (float)s_p3[0x4C0/4] / (float)s_p3[0x290/4];
float b10_p3 = (float)s_p3[0x4C8/4] / (float)s_p3[0x290/4];
float b11_p3 = (float)s_p3[0x4D0/4] / (float)s_p3[0x290/4];
float b12_p3 = (float)s_p3[0x4D8/4] / (float)s_p3[0x290/4];
if (s_p3[0x290/4] == 0) {
b0_p3 = b1_p3 = b2_p3 = b3_p3 = b4_p3 = b5_p3 = b6_p3 = b7_p3 = b8_p3 = b9_p3 = b10_p3 = b11_p3 = b12_p3 = lbl_806D2D70_p3;
}
if (self_p3->variant_p3 == 0)
TestPage_DrawItems_p3(self_p3, (MenuItem_p3 *)(tables_p3 + 0x191C), self_p3->cursor_p3 + 12);
else
TestPage_DrawItems_p3(self_p3, (MenuItem_p3 *)(tables_p3 + 0x19DC), self_p3->cursor_p3 + 12);
DrawText_p3(self_p3->text_p3, 98, 120, 7, lbl_806D2D44_p3, lbl_80310448_p3, lbl_806D2D74_p3 * b0_p3, lbl_806D2D74_p3 * b1_p3, lbl_806D2D74_p3 * b2_p3, lbl_806D2D74_p3 * b3_p3);
DrawText_p3(self_p3->text_p3, 98, 144, 7, lbl_806D2D44_p3, lbl_80310448_p3, lbl_806D2D74_p3 * b4_p3, lbl_806D2D74_p3 * b5_p3, lbl_806D2D74_p3 * b6_p3, lbl_806D2D74_p3 * b7_p3);
DrawText_p3(self_p3->text_p3, 98, 168, 7, lbl_806D2D44_p3, lbl_80310448_p3, lbl_806D2D74_p3 * b8_p3, lbl_806D2D74_p3 * b9_p3, lbl_806D2D74_p3 * b10_p3, lbl_806D2D74_p3 * b11_p3);
DrawText_p3(self_p3->text_p3, 98, 192, 7, lbl_806D2D44_p3, lbl_80310478_p3, lbl_806D2D74_p3 * b12_p3);
DrawText_p3(self_p3->text_p3, 98, 240, 7, lbl_806D2D44_p3, lbl_80310448_p3, lbl_806D2D74_p3 * a0_p3, lbl_806D2D74_p3 * a1_p3, lbl_806D2D74_p3 * a2_p3, lbl_806D2D74_p3 * a3_p3);
DrawText_p3(self_p3->text_p3, 98, 264, 7, lbl_806D2D44_p3, lbl_80310448_p3, lbl_806D2D74_p3 * a4_p3, lbl_806D2D74_p3 * a5_p3, lbl_806D2D74_p3 * a6_p3, lbl_806D2D74_p3 * a7_p3);
DrawText_p3(self_p3->text_p3, 98, 288, 7, lbl_806D2D44_p3, lbl_80310448_p3, lbl_806D2D74_p3 * a8_p3, lbl_806D2D74_p3 * a9_p3, lbl_806D2D74_p3 * a10_p3, lbl_806D2D74_p3 * a11_p3);
DrawText_p3(self_p3->text_p3, 98, 312, 7, lbl_806D2D44_p3, lbl_80310478_p3, lbl_806D2D74_p3 * a12_p3);
} else {
TestPage_DrawItems_p3(self_p3, (MenuItem_p3 *)(tables_p3 + 0x1A9C), self_p3->cursor_p3 + 6);
DrawText_p3(self_p3->text_p3, 98, 96, 7, lbl_806D2D44_p3, lbl_80310448_p3, lbl_806D2D74_p3 * a0_p3, lbl_806D2D74_p3 * a1_p3, lbl_806D2D74_p3 * a2_p3, lbl_806D2D74_p3 * a3_p3);
DrawText_p3(self_p3->text_p3, 98, 120, 7, lbl_806D2D44_p3, lbl_80310448_p3, lbl_806D2D74_p3 * a4_p3, lbl_806D2D74_p3 * a5_p3, lbl_806D2D74_p3 * a6_p3, lbl_806D2D74_p3 * a7_p3);
DrawText_p3(self_p3->text_p3, 98, 144, 7, lbl_806D2D44_p3, lbl_80310448_p3, lbl_806D2D74_p3 * a8_p3, lbl_806D2D74_p3 * a9_p3, lbl_806D2D74_p3 * a10_p3, lbl_806D2D74_p3 * a11_p3);
DrawText_p3(self_p3->text_p3, 98, 168, 7, lbl_806D2D44_p3, lbl_80310478_p3, lbl_806D2D74_p3 * a12_p3);
}
}
return 1;
}
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/NetDiag_CounterPage.c (0x80067f74) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

typedef struct MenuItem_p4 {
int x_p4;
int y_p4;
const char *text_p4;
} MenuItem_p4;
class InputPlayer_p4 {
public:
virtual void vf08_p4();
virtual void vf0C_p4();
virtual void vf10_p4();
virtual void vf14_p4();
virtual void vf18_p4();
virtual void vf1C_p4();
virtual unsigned char isTriggered_p4(int mask_p4);
};
typedef struct NetStats_p4 {
char pad_0x000_p4[0x37C];
int link_p4[8][8];
} NetStats_p4;
typedef struct ServiceMenuRec_p4 {
void *vtbl_p4;
int isJapanese_p4;
int blinkTimer_p4;
int clockTimer_p4;
int pageId_p4;
int cursor_p4;
int field_0x18_p4;
char pad_0x1C_p4[0x34 - 0x1C];
int cabinetType_p4;
char pad_0x38_p4[0x270 - 0x38];
void *displayCtx_p4;
NetStats_p4 *stats_p4;
} ServiceMenuRec_p4;
extern "C"{


extern const char lbl_80310484_p4[];
extern const float lbl_806D2D44_p4;
void *GetInputManager_p4(void);
InputPlayer_p4 *InputMgr_GetPlayer_p4(void *mgr_p4, int index_p4);
void NetDiag_QualityPage_p4(void *self_p4, int mode_p4, int arg_p4);
void DrawText_p4(void *ctx_p4, int x_p4, int y_p4, int color_p4, float scale_p4, const char *fmt_p4, ...);
static inline void DrawMenu_p4(ServiceMenuRec_p4 *self_p4, MenuItem_p4 *items_p4)
{
int selected_p4 = self_p4->field_0x18_p4 + 11;
int i_p4;
for (i_p4 = 0; items_p4[i_p4].text_p4 != 0; i_p4++) {
if (i_p4 == selected_p4 && self_p4->blinkTimer_p4 > 30) {
continue;
}
if (self_p4->displayCtx_p4 != 0) {
DrawText_p4(self_p4->displayCtx_p4, items_p4[i_p4].x_p4 * 14, items_p4[i_p4].y_p4 * 24, 7, lbl_806D2D44_p4, items_p4[i_p4].text_p4);
}
}
}
int NetDiag_CounterPage(ServiceMenuRec_p4 *self_p4, int mode_p4)
{
NetStats_p4 *s_p4;
if (mode_p4 == 0) {
self_p4->field_0x18_p4 = 0;
}
if (mode_p4 == 1) {
InputPlayer_p4 *player_p4 = InputMgr_GetPlayer_p4(GetInputManager_p4(), 0);
if (player_p4->isTriggered_p4(0x800)) {
self_p4->blinkTimer_p4 = 0x1F;
if (++self_p4->field_0x18_p4 > 1) {
self_p4->field_0x18_p4 = 0;
}
}
if (player_p4->isTriggered_p4(0x1000)) {
if (self_p4->field_0x18_p4 == 0) {
self_p4->pageId_p4 = 0x1F;
NetDiag_QualityPage_p4(self_p4, 0, -1);
} else {
self_p4->pageId_p4 = 0;
}
}
}
if (mode_p4 == 2) {
s_p4 = self_p4->stats_p4;
if (self_p4->cabinetType_p4 == 0) {
DrawMenu_p4(self_p4, (*(MenuItem_p4 (*)[])&lbl_803FD71C));
} else {
DrawMenu_p4(self_p4, (*(MenuItem_p4 (*)[])&lbl_803FD7DC));
}
DrawText_p4(self_p4->displayCtx_p4, 126, 96, 7, lbl_806D2D44_p4, lbl_80310484_p4,
s_p4->link_p4[6][0], s_p4->link_p4[6][2], s_p4->link_p4[6][4], s_p4->link_p4[6][6]);
DrawText_p4(self_p4->displayCtx_p4, 126, 120, 7, lbl_806D2D44_p4, lbl_80310484_p4,
s_p4->link_p4[0][0], s_p4->link_p4[0][2], s_p4->link_p4[0][4], s_p4->link_p4[0][6]);
DrawText_p4(self_p4->displayCtx_p4, 126, 144, 7, lbl_806D2D44_p4, lbl_80310484_p4,
s_p4->link_p4[7][0], s_p4->link_p4[7][2], s_p4->link_p4[7][4], s_p4->link_p4[7][6]);
DrawText_p4(self_p4->displayCtx_p4, 126, 168, 7, lbl_806D2D44_p4, lbl_80310484_p4,
s_p4->link_p4[1][0], s_p4->link_p4[1][2], s_p4->link_p4[1][4], s_p4->link_p4[1][6]);
DrawText_p4(self_p4->displayCtx_p4, 126, 192, 7, lbl_806D2D44_p4, lbl_80310484_p4,
s_p4->link_p4[2][0], s_p4->link_p4[2][2], s_p4->link_p4[2][4], s_p4->link_p4[2][6]);
DrawText_p4(self_p4->displayCtx_p4, 126, 216, 7, lbl_806D2D44_p4, lbl_80310484_p4,
s_p4->link_p4[3][0], s_p4->link_p4[3][2], s_p4->link_p4[3][4], s_p4->link_p4[3][6]);
DrawText_p4(self_p4->displayCtx_p4, 126, 240, 7, lbl_806D2D44_p4, lbl_80310484_p4,
s_p4->link_p4[4][0], s_p4->link_p4[4][2], s_p4->link_p4[4][4], s_p4->link_p4[4][6]);
DrawText_p4(self_p4->displayCtx_p4, 126, 264, 7, lbl_806D2D44_p4, lbl_80310484_p4,
s_p4->link_p4[5][0], s_p4->link_p4[5][2], s_p4->link_p4[5][4], s_p4->link_p4[5][6]);
}
return 1;
}
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Stats_PacketStats_UI.cpp (0x8006830c) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
#pragma cplusplus on
struct InputPlayer_p5 {
virtual void v0_p5();
virtual void v1_p5();
virtual float v2_p5();
virtual void v3_p5();
virtual float StickRight_p5();
virtual float StickLeft_p5();
virtual unsigned char Pressed_p5(int mask_p5);
virtual unsigned char Held_p5(int mask_p5);
};
struct MenuItem_p5 {
int x_p5;
int y_p5;
const char *text_p5;
};
struct TestPage_p5 {
unsigned char pad_0_p5[8];
int blink_p5;
unsigned char pad_C_p5[4];
int next_p5;
unsigned char pad_14_p5[4];
int cursor_p5;
int sub_p5;
unsigned char pad_20_p5[0x14];
int variant_p5;
unsigned char pad_38_p5[0x238];
void *text_p5;
void *data_p5;
};
extern "C"{
extern char lbl_8030E598_p5[];
void *GetInputManager_p5(void);
InputPlayer_p5 *InputMgr_GetPlayer_p5(void *, int);
void DrawText_p5(void *ctx_p5, int x_p5, int y_p5, int color_p5, float scale_p5, const char *fmt_p5, ...);
}
static inline void TestPage_DrawItems_p5(TestPage_p5 *self_p5, MenuItem_p5 *it_p5, int sel_p5)
{
int i_p5;
for (i_p5 = 0; it_p5[i_p5].text_p5 != 0; i_p5++) {
if (i_p5 != sel_p5 || self_p5->blink_p5 <= 0x1E) {
if (self_p5->text_p5 != 0) {
DrawText_p5(self_p5->text_p5, it_p5[i_p5].x_p5 * 14, it_p5[i_p5].y_p5 * 24, 7, 1.0f, it_p5[i_p5].text_p5);
}
}
}
}
extern "C"{

extern const char lbl_80310478_p5[], lbl_8031049C_p5[], lbl_806D2D80_p5[5];
extern const float lbl_806D2D44_p5, lbl_806D2D70_p5, lbl_806D2D74_p5;
int NetDiag_CounterPage_p5(TestPage_p5 *, int, int);
}

#pragma exceptions on

extern "C"int Stats_PacketStats_UI(TestPage_p5 *self_p5, int phase_p5, int unused_p5)
{
char *tables_p5 = (*(char (*)[])&lbl_803FBF80);
if (phase_p5 == 0) self_p5->cursor_p5 = 0;
if (phase_p5 == 1) {
InputPlayer_p5 *input_p5 = InputMgr_GetPlayer_p5(GetInputManager_p5(), 0);
if (input_p5->Pressed_p5(0x800)) {
self_p5->blink_p5 = 31;
if (++self_p5->cursor_p5 > 1) self_p5->cursor_p5 = 0;
}
if (input_p5->Pressed_p5(0x1000)) {
if (self_p5->cursor_p5 == 0) {
self_p5->next_p5 = 30;
NetDiag_CounterPage_p5(self_p5, 0, -1);
} else self_p5->next_p5 = 0;
}
}
if (phase_p5 == 2) {
unsigned int *stats_p5 = (unsigned int *)self_p5->data_p5;
float total_p5 = (float)(stats_p5[0x2B8/4] + stats_p5[0x2BC/4]);
float ratio0_p5 = (float)stats_p5[0x374/4] / total_p5;
float ratio1_p5 = (float)stats_p5[0x378/4] / total_p5;
float ratio2_p5 = (float)stats_p5[0x380/4] / total_p5;
float ratio3_p5 = (float)stats_p5[0x388/4] / total_p5;
float ratio4_p5 = (float)stats_p5[0x390/4] / total_p5;
float ratio5_p5 = (float)stats_p5[0x398/4] / total_p5;
float ratio6_p5 = (float)stats_p5[0x3A0/4] / total_p5;
float ratio7_p5 = (float)stats_p5[0x3A8/4] / total_p5;
float ratio8_p5 = (float)stats_p5[0x3B0/4] / total_p5;
float ratio9_p5 = (float)stats_p5[0x3B8/4] / total_p5;
float ratio10_p5 = (float)stats_p5[0x3C0/4] / total_p5;
float ratio11_p5 = (float)stats_p5[0x3C8/4] / total_p5;
float ratio12_p5 = (float)stats_p5[0x3D0/4] / total_p5;
float ratio13_p5 = (float)stats_p5[0x3D8/4] / total_p5;
float ratio14_p5 = (float)stats_p5[0x3E0/4] / total_p5;
float ratio15_p5 = (float)stats_p5[0x3E8/4] / total_p5;
float ratio16_p5 = (float)stats_p5[0x3F0/4] / total_p5;
float ratio17_p5 = (float)stats_p5[0x3F8/4] / total_p5;
float ratio18_p5 = (float)stats_p5[0x400/4] / total_p5;
float ratio19_p5 = (float)stats_p5[0x408/4] / total_p5;
float ratio20_p5 = (float)stats_p5[0x410/4] / total_p5;
float ratio21_p5 = (float)stats_p5[0x418/4] / total_p5;
float ratio22_p5 = (float)stats_p5[0x420/4] / total_p5;
float ratio23_p5 = (float)stats_p5[0x428/4] / total_p5;
float ratio24_p5 = (float)stats_p5[0x430/4] / total_p5;
float ratio25_p5 = (float)stats_p5[0x438/4] / total_p5;
float ratio26_p5 = (float)stats_p5[0x440/4] / total_p5;
float ratio27_p5 = (float)stats_p5[0x448/4] / total_p5;
float ratio28_p5 = (float)stats_p5[0x450/4] / total_p5;
float ratio29_p5 = (float)stats_p5[0x458/4] / total_p5;
float ratio30_p5 = (float)stats_p5[0x460/4] / total_p5;
float ratio31_p5 = (float)stats_p5[0x468/4] / total_p5;
float ratio32_p5 = (float)stats_p5[0x470/4] / total_p5;
if (lbl_806D2D70_p5 == total_p5) {
ratio0_p5 = lbl_806D2D70_p5;
ratio1_p5 = ratio2_p5 = ratio3_p5 = ratio4_p5 = ratio5_p5 = ratio6_p5 = ratio7_p5 = ratio8_p5 = lbl_806D2D70_p5;
ratio9_p5 = ratio10_p5 = ratio11_p5 = ratio12_p5 = ratio13_p5 = ratio14_p5 = ratio15_p5 = ratio16_p5 = lbl_806D2D70_p5;
ratio17_p5 = ratio18_p5 = ratio19_p5 = ratio20_p5 = ratio21_p5 = ratio22_p5 = ratio23_p5 = ratio24_p5 = lbl_806D2D70_p5;
ratio25_p5 = ratio26_p5 = ratio27_p5 = ratio28_p5 = ratio29_p5 = ratio30_p5 = ratio31_p5 = ratio32_p5 = lbl_806D2D70_p5;
}
int row_p5;
if (self_p5->variant_p5 != 2) {
if (self_p5->variant_p5 == 0)
TestPage_DrawItems_p5(self_p5, (MenuItem_p5 *)(tables_p5 + 0x1520), self_p5->cursor_p5 + 13);
else
TestPage_DrawItems_p5(self_p5, (MenuItem_p5 *)(tables_p5 + 0x15F8), self_p5->cursor_p5 + 13);
DrawText_p5(self_p5->text_p5, 420, 96, 7, lbl_806D2D44_p5, lbl_80310478_p5, lbl_806D2D74_p5 * ratio0_p5);
row_p5 = 7;
} else {
TestPage_DrawItems_p5(self_p5, (MenuItem_p5 *)(tables_p5 + 0x16D0), self_p5->cursor_p5 + 12);
row_p5 = 6;
}
DrawText_p5(self_p5->text_p5, 420, 72, 7, lbl_806D2D44_p5, lbl_806D2D80_p5, (int)total_p5);
DrawText_p5(self_p5->text_p5, 126, (row_p5)*24, 7, lbl_806D2D44_p5, lbl_8031049C_p5, lbl_806D2D74_p5 * ratio25_p5, lbl_806D2D74_p5 * ratio26_p5, lbl_806D2D74_p5 * ratio27_p5, lbl_806D2D74_p5 * ratio28_p5);
DrawText_p5(self_p5->text_p5, 126, (row_p5 + 1)*24, 7, lbl_806D2D44_p5, lbl_8031049C_p5, lbl_806D2D74_p5 * ratio1_p5, lbl_806D2D74_p5 * ratio2_p5, lbl_806D2D74_p5 * ratio3_p5, lbl_806D2D74_p5 * ratio4_p5);
DrawText_p5(self_p5->text_p5, 126, (row_p5 + 2)*24, 7, lbl_806D2D44_p5, lbl_8031049C_p5, lbl_806D2D74_p5 * ratio29_p5, lbl_806D2D74_p5 * ratio30_p5, lbl_806D2D74_p5 * ratio31_p5, lbl_806D2D74_p5 * ratio32_p5);
DrawText_p5(self_p5->text_p5, 126, (row_p5 + 3)*24, 7, lbl_806D2D44_p5, lbl_8031049C_p5, lbl_806D2D74_p5 * ratio5_p5, lbl_806D2D74_p5 * ratio6_p5, lbl_806D2D74_p5 * ratio7_p5, lbl_806D2D74_p5 * ratio8_p5);
DrawText_p5(self_p5->text_p5, 126, (row_p5 + 4)*24, 7, lbl_806D2D44_p5, lbl_8031049C_p5, lbl_806D2D74_p5 * ratio9_p5, lbl_806D2D74_p5 * ratio10_p5, lbl_806D2D74_p5 * ratio11_p5, lbl_806D2D74_p5 * ratio12_p5);
DrawText_p5(self_p5->text_p5, 126, (row_p5 + 5)*24, 7, lbl_806D2D44_p5, lbl_8031049C_p5, lbl_806D2D74_p5 * ratio13_p5, lbl_806D2D74_p5 * ratio14_p5, lbl_806D2D74_p5 * ratio15_p5, lbl_806D2D74_p5 * ratio16_p5);
DrawText_p5(self_p5->text_p5, 126, (row_p5 + 6)*24, 7, lbl_806D2D44_p5, lbl_8031049C_p5, lbl_806D2D74_p5 * ratio17_p5, lbl_806D2D74_p5 * ratio18_p5, lbl_806D2D74_p5 * ratio19_p5, lbl_806D2D74_p5 * ratio20_p5);
DrawText_p5(self_p5->text_p5, 126, (row_p5 + 7)*24, 7, lbl_806D2D44_p5, lbl_8031049C_p5, lbl_806D2D74_p5 * ratio21_p5, lbl_806D2D74_p5 * ratio22_p5, lbl_806D2D74_p5 * ratio23_p5, lbl_806D2D74_p5 * ratio24_p5);
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/NetDiag_PacketPage.c (0x80068d00) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

struct InputPlayer_p6 {
virtual void v0_p6();
virtual void v1_p6();
virtual float v2_p6();
virtual void v3_p6();
virtual float StickRight_p6();
virtual float StickLeft_p6();
virtual unsigned char Pressed_p6(int mask_p6);
virtual unsigned char Held_p6(int mask_p6);
};
struct MenuItem_p6 {
int x_p6;
int y_p6;
const char *text_p6;
};
struct TestPage_p6 {
unsigned char pad_0_p6[8];
int blink_p6;
unsigned char pad_C_p6[4];
int next_p6;
unsigned char pad_14_p6[4];
int cursor_p6;
int sub_p6;
unsigned char pad_20_p6[0x14];
int variant_p6;
unsigned char pad_38_p6[0x238];
void *text_p6;
void *data_p6;
};
extern "C"{
extern char lbl_8030E598_p6[];
void *GetInputManager_p6(void);
InputPlayer_p6 *InputMgr_GetPlayer_p6(void *, int);
void DrawText_p6(void *ctx_p6, int x_p6, int y_p6, int color_p6, float scale_p6, const char *fmt_p6, ...);
}
static inline void TestPage_DrawItems_p6(TestPage_p6 *self_p6, MenuItem_p6 *it_p6, int sel_p6)
{
int i_p6;
for (i_p6 = 0; it_p6[i_p6].text_p6 != 0; i_p6++) {
if (i_p6 != sel_p6 || self_p6->blink_p6 <= 0x1E) {
if (self_p6->text_p6 != 0) {
DrawText_p6(self_p6->text_p6, it_p6[i_p6].x_p6 * 14, it_p6[i_p6].y_p6 * 24, 7, 1.0f, it_p6[i_p6].text_p6);
}
}
}
}
extern "C"{

extern const char lbl_80310478_p6[], lbl_8031049C_p6[], lbl_806D2D80_p6[5];
extern const float lbl_806D2D44_p6, lbl_806D2D70_p6, lbl_806D2D74_p6;
int Stats_PacketStats_UI_p6(TestPage_p6 *self_p6, int phase_p6, int arg_p6);
static inline unsigned int PacketTotal_p6(TestPage_p6 *self_p6)
{
unsigned int *stats_p6 = (unsigned int *)self_p6->data_p6;
return stats_p6[0x2AC/4] + stats_p6[0x2B0/4] + stats_p6[0x2B4/4];
}
int NetDiag_PacketPage(TestPage_p6 *self_p6, int phase_p6, int arg_p6)
{
char *tables_p6 = (*(char (*)[])&lbl_803FBF80);
if (phase_p6 == 0) self_p6->cursor_p6 = 0;
if (phase_p6 == 1) {
InputPlayer_p6 *input_p6 = InputMgr_GetPlayer_p6(GetInputManager_p6(), 0);
if (input_p6->Pressed_p6(0x800)) {
self_p6->blink_p6 = 31;
if (++self_p6->cursor_p6 > 1) self_p6->cursor_p6 = 0;
}
if (input_p6->Pressed_p6(0x1000)) {
if (self_p6->cursor_p6 == 0) {
self_p6->next_p6 = 29;
Stats_PacketStats_UI_p6(self_p6, 0, -1);
} else self_p6->next_p6 = 0;
}
}
if (phase_p6 == 2) {
float total_p6 = (float)PacketTotal_p6(self_p6);
unsigned int *stats_p6 = (unsigned int *)self_p6->data_p6;
float ratio0_p6 = (float)stats_p6[0x2E0/4] / total_p6;
float ratio1_p6 = (float)stats_p6[0x2F4/4] / total_p6;
float ratio2_p6 = (float)stats_p6[0x2F8/4] / total_p6;
float ratio3_p6 = (float)stats_p6[0x2FC/4] / total_p6;
float ratio4_p6 = (float)stats_p6[0x300/4] / total_p6;
float ratio5_p6 = (float)stats_p6[0x304/4] / total_p6;
float ratio6_p6 = (float)stats_p6[0x308/4] / total_p6;
float ratio7_p6 = (float)stats_p6[0x30C/4] / total_p6;
float ratio8_p6 = (float)stats_p6[0x310/4] / total_p6;
float ratio9_p6 = (float)stats_p6[0x314/4] / total_p6;
float ratio10_p6 = (float)stats_p6[0x318/4] / total_p6;
float ratio11_p6 = (float)stats_p6[0x31C/4] / total_p6;
float ratio12_p6 = (float)stats_p6[0x320/4] / total_p6;
float ratio13_p6 = (float)stats_p6[0x324/4] / total_p6;
float ratio14_p6 = (float)stats_p6[0x328/4] / total_p6;
float ratio15_p6 = (float)stats_p6[0x32C/4] / total_p6;
float ratio16_p6 = (float)stats_p6[0x330/4] / total_p6;
float ratio17_p6 = (float)stats_p6[0x334/4] / total_p6;
float ratio18_p6 = (float)stats_p6[0x338/4] / total_p6;
float ratio19_p6 = (float)stats_p6[0x33C/4] / total_p6;
float ratio20_p6 = (float)stats_p6[0x340/4] / total_p6;
float ratio21_p6 = (float)stats_p6[0x344/4] / total_p6;
float ratio22_p6 = (float)stats_p6[0x348/4] / total_p6;
float ratio23_p6 = (float)stats_p6[0x34C/4] / total_p6;
float ratio24_p6 = (float)stats_p6[0x350/4] / total_p6;
float ratio25_p6 = (float)stats_p6[0x354/4] / total_p6;
float ratio26_p6 = (float)stats_p6[0x358/4] / total_p6;
float ratio27_p6 = (float)stats_p6[0x35C/4] / total_p6;
float ratio28_p6 = (float)stats_p6[0x360/4] / total_p6;
float ratio29_p6 = (float)stats_p6[0x364/4] / total_p6;
float ratio30_p6 = (float)stats_p6[0x368/4] / total_p6;
float ratio31_p6 = (float)stats_p6[0x36C/4] / total_p6;
float ratio32_p6 = (float)stats_p6[0x370/4] / total_p6;
int row_p6;
if (lbl_806D2D70_p6 == total_p6) {
ratio0_p6 = lbl_806D2D70_p6;
ratio1_p6 = ratio2_p6 = ratio3_p6 = ratio4_p6 = ratio5_p6 = ratio6_p6 = ratio7_p6 = ratio8_p6 = lbl_806D2D70_p6;
ratio9_p6 = ratio10_p6 = ratio11_p6 = ratio12_p6 = ratio13_p6 = ratio14_p6 = ratio15_p6 = ratio16_p6 = lbl_806D2D70_p6;
ratio17_p6 = ratio18_p6 = ratio19_p6 = ratio20_p6 = ratio21_p6 = ratio22_p6 = ratio23_p6 = ratio24_p6 = lbl_806D2D70_p6;
ratio25_p6 = ratio26_p6 = ratio27_p6 = ratio28_p6 = ratio29_p6 = ratio30_p6 = ratio31_p6 = ratio32_p6 = lbl_806D2D70_p6;
}
if (self_p6->variant_p6 != 2) {
if (self_p6->variant_p6 == 0)
TestPage_DrawItems_p6(self_p6, (MenuItem_p6 *)(tables_p6 + 0x12A4), self_p6->cursor_p6 + 13);
else
TestPage_DrawItems_p6(self_p6, (MenuItem_p6 *)(tables_p6 + 0x137C), self_p6->cursor_p6 + 13);
DrawText_p6(self_p6->text_p6, 420, 72, 7, lbl_806D2D44_p6, lbl_806D2D80_p6, (int)total_p6);
DrawText_p6(self_p6->text_p6, 420, 96, 7, lbl_806D2D44_p6, lbl_80310478_p6, lbl_806D2D74_p6 * ratio0_p6);
row_p6 = 8;
} else {
TestPage_DrawItems_p6(self_p6, (MenuItem_p6 *)(tables_p6 + 0x1454), self_p6->cursor_p6 + 12);
DrawText_p6(self_p6->text_p6, 420, 72, 7, lbl_806D2D44_p6, lbl_806D2D80_p6, total_p6);
row_p6 = 6;
}
DrawText_p6(self_p6->text_p6, 126, (row_p6) * 24, 7, lbl_806D2D44_p6, lbl_8031049C_p6, lbl_806D2D74_p6 * ratio25_p6, lbl_806D2D74_p6 * ratio26_p6, lbl_806D2D74_p6 * ratio27_p6, lbl_806D2D74_p6 * ratio28_p6);
DrawText_p6(self_p6->text_p6, 126, (row_p6 + 1) * 24, 7, lbl_806D2D44_p6, lbl_8031049C_p6, lbl_806D2D74_p6 * ratio1_p6, lbl_806D2D74_p6 * ratio2_p6, lbl_806D2D74_p6 * ratio3_p6, lbl_806D2D74_p6 * ratio4_p6);
DrawText_p6(self_p6->text_p6, 126, (row_p6 + 2) * 24, 7, lbl_806D2D44_p6, lbl_8031049C_p6, lbl_806D2D74_p6 * ratio29_p6, lbl_806D2D74_p6 * ratio30_p6, lbl_806D2D74_p6 * ratio31_p6, lbl_806D2D74_p6 * ratio32_p6);
DrawText_p6(self_p6->text_p6, 126, (row_p6 + 3) * 24, 7, lbl_806D2D44_p6, lbl_8031049C_p6, lbl_806D2D74_p6 * ratio5_p6, lbl_806D2D74_p6 * ratio6_p6, lbl_806D2D74_p6 * ratio7_p6, lbl_806D2D74_p6 * ratio8_p6);
DrawText_p6(self_p6->text_p6, 126, (row_p6 + 4) * 24, 7, lbl_806D2D44_p6, lbl_8031049C_p6, lbl_806D2D74_p6 * ratio9_p6, lbl_806D2D74_p6 * ratio10_p6, lbl_806D2D74_p6 * ratio11_p6, lbl_806D2D74_p6 * ratio12_p6);
DrawText_p6(self_p6->text_p6, 126, (row_p6 + 5) * 24, 7, lbl_806D2D44_p6, lbl_8031049C_p6, lbl_806D2D74_p6 * ratio13_p6, lbl_806D2D74_p6 * ratio14_p6, lbl_806D2D74_p6 * ratio15_p6, lbl_806D2D74_p6 * ratio16_p6);
DrawText_p6(self_p6->text_p6, 126, (row_p6 + 6) * 24, 7, lbl_806D2D44_p6, lbl_8031049C_p6, lbl_806D2D74_p6 * ratio17_p6, lbl_806D2D74_p6 * ratio18_p6, lbl_806D2D74_p6 * ratio19_p6, lbl_806D2D74_p6 * ratio20_p6);
DrawText_p6(self_p6->text_p6, 126, (row_p6 + 7) * 24, 7, lbl_806D2D44_p6, lbl_8031049C_p6, lbl_806D2D74_p6 * ratio21_p6, lbl_806D2D74_p6 * ratio22_p6, lbl_806D2D74_p6 * ratio23_p6, lbl_806D2D74_p6 * ratio24_p6);
}
return 1;
}
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/Stats_Display_UI.cpp (0x80069720) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
#pragma cplusplus on
struct InputPlayer_p7 {
virtual void v0_p7();
virtual void v1_p7();
virtual float v2_p7();
virtual void v3_p7();
virtual float StickRight_p7();
virtual float StickLeft_p7();
virtual unsigned char Pressed_p7(int mask_p7);
virtual unsigned char Held_p7(int mask_p7);
};
struct MenuItem_p7 {
int x_p7;
int y_p7;
const char *text_p7;
};
struct TestPage_p7 {
unsigned char pad_0_p7[8];
int blink_p7;
unsigned char pad_C_p7[4];
int next_p7;
unsigned char pad_14_p7[4];
int cursor_p7;
int sub_p7;
unsigned char pad_20_p7[0x14];
int variant_p7;
unsigned char pad_38_p7[0x238];
void *text_p7;
void *data_p7;
};
extern "C"{
extern char lbl_8030E598_p7[];
void *GetInputManager_p7(void);
InputPlayer_p7 *InputMgr_GetPlayer_p7(void *, int);
void DrawText_p7(void *ctx_p7, int x_p7, int y_p7, int color_p7, float scale_p7, const char *fmt_p7, ...);
}
static inline void TestPage_DrawItems_p7(TestPage_p7 *self_p7, MenuItem_p7 *it_p7, int sel_p7)
{
int i_p7;
for (i_p7 = 0; it_p7[i_p7].text_p7 != 0; i_p7++) {
if (i_p7 != sel_p7 || self_p7->blink_p7 <= 0x1E) {
if (self_p7->text_p7 != 0) {
DrawText_p7(self_p7->text_p7, it_p7[i_p7].x_p7 * 14, it_p7[i_p7].y_p7 * 24, 7, 1.0f, it_p7[i_p7].text_p7);
}
}
}
}
struct NetStats_p7 {
unsigned char pad_0_p7[0x2A0];
unsigned int received_p7;
unsigned int dropped_p7;
unsigned int corrupted_p7;
unsigned char pad_2AC_p7[0x18];
unsigned int errors_p7;
int counters_p7[6];
};
extern "C"{


extern const char lbl_80310478_p7[];
extern const char lbl_806D2D80_p7[5];
extern const char lbl_806D2D88_p7[5];
void NetDiag_PacketPage_p7(TestPage_p7 *self_p7, int phase_p7, int arg_p7);
}

#pragma exceptions on

extern "C"int Stats_Display_UI(TestPage_p7 *self_p7, int phase_p7)
{
InputPlayer_p7 *pl_p7;
NetStats_p7 *st_p7;
unsigned int total_p7;
float ratio_p7;
int row_p7;
if (phase_p7 == 0) {
self_p7->cursor_p7 = 0;
}
if (phase_p7 == 1) {
pl_p7 = InputMgr_GetPlayer_p7(GetInputManager_p7(), 0);
if (pl_p7->Pressed_p7(0x800)) {
self_p7->blink_p7 = 0x1F;
if (++self_p7->cursor_p7 > 1) {
self_p7->cursor_p7 = 0;
}
}
if (pl_p7->Pressed_p7(0x1000)) {
if (self_p7->cursor_p7 == 0) {
self_p7->next_p7 = 0x1C;
NetDiag_PacketPage_p7(self_p7, 0, -1);
} else {
self_p7->next_p7 = 0;
}
}
}
if (phase_p7 == 2) {
st_p7 = (NetStats_p7 *)self_p7->data_p7;
total_p7 = st_p7->received_p7 + st_p7->dropped_p7 + st_p7->corrupted_p7;
ratio_p7 = (float)st_p7->errors_p7 / (float)total_p7;
if (total_p7 == 0) {
ratio_p7 = 0.0f;
}
if (self_p7->variant_p7 != 2) {
TestPage_DrawItems_p7(self_p7, (*(MenuItem_p7 (*)[])&lbl_803FD0C8), self_p7->cursor_p7 + 10);
DrawText_p7(self_p7->text_p7, 0x1A4, 0x60, 7, 1.0f, lbl_80310478_p7, 100.0f * ratio_p7);
row_p7 = 6;
} else {
TestPage_DrawItems_p7(self_p7, (*(MenuItem_p7 (*)[])&lbl_803FD17C), self_p7->cursor_p7 + 9);
row_p7 = 5;
}
DrawText_p7(self_p7->text_p7, 0x1A4, 0x48, 7, 1.0f, lbl_806D2D80_p7, total_p7);
DrawText_p7(self_p7->text_p7, 0x1C0, row_p7 * 24, 7, 1.0f, lbl_806D2D88_p7, ((NetStats_p7 *)self_p7->data_p7)->counters_p7[0]);
DrawText_p7(self_p7->text_p7, 0x1C0, (row_p7 + 1) * 24, 7, 1.0f, lbl_806D2D88_p7, ((NetStats_p7 *)self_p7->data_p7)->counters_p7[1]);
DrawText_p7(self_p7->text_p7, 0x1C0, (row_p7 + 2) * 24, 7, 1.0f, lbl_806D2D88_p7, ((NetStats_p7 *)self_p7->data_p7)->counters_p7[2]);
DrawText_p7(self_p7->text_p7, 0x1C0, (row_p7 + 4) * 24, 7, 1.0f, lbl_806D2D88_p7, ((NetStats_p7 *)self_p7->data_p7)->counters_p7[3]);
DrawText_p7(self_p7->text_p7, 0x1C0, (row_p7 + 5) * 24, 7, 1.0f, lbl_806D2D88_p7, ((NetStats_p7 *)self_p7->data_p7)->counters_p7[4]);
DrawText_p7(self_p7->text_p7, 0x1C0, (row_p7 + 6) * 24, 7, 1.0f, lbl_806D2D88_p7, ((NetStats_p7 *)self_p7->data_p7)->counters_p7[5]);
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/NetDiag_PacketRatioPage.c (0x80069ab0) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma exceptions on

struct InputPlayer_p8 {
virtual void v0_p8();
virtual void v1_p8();
virtual float v2_p8();
virtual void v3_p8();
virtual float StickRight_p8();
virtual float StickLeft_p8();
virtual unsigned char Pressed_p8(int mask_p8);
virtual unsigned char Held_p8(int mask_p8);
};
struct MenuItem_p8 {
int x_p8;
int y_p8;
const char *text_p8;
};
struct TestPage_p8 {
unsigned char pad_0_p8[8];
int blink_p8;
unsigned char pad_C_p8[4];
int next_p8;
unsigned char pad_14_p8[4];
int cursor_p8;
int sub_p8;
unsigned char pad_20_p8[0x14];
int variant_p8;
unsigned char pad_38_p8[0x238];
void *text_p8;
void *data_p8;
};
extern "C"{
extern char lbl_8030E598_p8[];
void *GetInputManager_p8(void);
InputPlayer_p8 *InputMgr_GetPlayer_p8(void *, int);
void DrawText_p8(void *ctx_p8, int x_p8, int y_p8, int color_p8, float scale_p8, const char *fmt_p8, ...);
}
static inline void TestPage_DrawItems_p8(TestPage_p8 *self_p8, MenuItem_p8 *it_p8, int sel_p8)
{
int i_p8;
for (i_p8 = 0; it_p8[i_p8].text_p8 != 0; i_p8++) {
if (i_p8 != sel_p8 || self_p8->blink_p8 <= 0x1E) {
if (self_p8->text_p8 != 0) {
DrawText_p8(self_p8->text_p8, it_p8[i_p8].x_p8 * 14, it_p8[i_p8].y_p8 * 24, 7, 1.0f, it_p8[i_p8].text_p8);
}
}
}
}
extern "C"{

extern const char lbl_80310478_p8[], lbl_806D2D80_p8[5];
extern const float lbl_806D2D44_p8, lbl_806D2D70_p8, lbl_806D2D74_p8;
int Stats_Display_UI_p8(TestPage_p8 *self_p8, int phase_p8, int arg_p8);
int NetDiag_PacketRatioPage(TestPage_p8 *self_p8, int phase_p8, int arg_p8)
{
if (phase_p8 == 0) self_p8->cursor_p8 = 0;
if (phase_p8 == 1) {
InputPlayer_p8 *input_p8 = InputMgr_GetPlayer_p8(GetInputManager_p8(), 0);
if (input_p8->Pressed_p8(0x800)) {
self_p8->blink_p8 = 31;
if (++self_p8->cursor_p8 > 1) self_p8->cursor_p8 = 0;
}
if (input_p8->Pressed_p8(0x1000)) {
if (self_p8->cursor_p8 == 0) {
self_p8->next_p8 = 27;
Stats_Display_UI_p8(self_p8, 0, -1);
} else self_p8->next_p8 = 0;
}
}
if (phase_p8 == 2) {
unsigned int *stats_p8 = (unsigned int *)self_p8->data_p8;
unsigned int total_p8 = stats_p8[0x27C/4];
float r0_p8 = (float)stats_p8[0x28C/4] / (float)total_p8;
float r1_p8 = (float)stats_p8[0x294/4] / (float)total_p8;
float r2_p8 = (float)stats_p8[0x2A0/4] / (float)total_p8;
float r3_p8 = (float)stats_p8[0x2A4/4] / (float)total_p8;
float r4_p8 = (float)stats_p8[0x2A8/4] / (float)total_p8;
float r5_p8 = (float)stats_p8[0x2AC/4] / (float)total_p8;
float r6_p8 = (float)stats_p8[0x2B0/4] / (float)total_p8;
float r7_p8 = (float)stats_p8[0x2B4/4] / (float)total_p8;
float r8_p8 = (float)stats_p8[0x2B8/4] / (float)total_p8;
float r9_p8 = (float)stats_p8[0x2BC/4] / (float)total_p8;
int row_p8;
if (total_p8 == 0) {
r0_p8 = r1_p8 = r8_p8 = r9_p8 = r5_p8 = r6_p8 = r7_p8 = r2_p8 = r3_p8 = r4_p8 = lbl_806D2D70_p8;
}
if (self_p8->variant_p8 != 2) {
TestPage_DrawItems_p8(self_p8, (*(MenuItem_p8 (*)[])&lbl_803FCF24), self_p8->cursor_p8 + 15);
DrawText_p8(self_p8->text_p8, 420, 48, 7, lbl_806D2D44_p8, lbl_806D2D80_p8, ((unsigned int *)self_p8->data_p8)[0x28C/4]);
DrawText_p8(self_p8->text_p8, 420, 72, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r0_p8);
DrawText_p8(self_p8->text_p8, 420, 96, 7, lbl_806D2D44_p8, lbl_806D2D80_p8, ((unsigned int *)self_p8->data_p8)[0x294/4]);
DrawText_p8(self_p8->text_p8, 420, 120, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r1_p8);
DrawText_p8(self_p8->text_p8, 420, 144, 7, lbl_806D2D44_p8, lbl_806D2D80_p8, ((unsigned int *)self_p8->data_p8)[0x29C/4]);
row_p8 = 8;
} else {
TestPage_DrawItems_p8(self_p8, (*(MenuItem_p8 (*)[])&lbl_803FD014), self_p8->cursor_p8 + 10);
row_p8 = 3;
}
DrawText_p8(self_p8->text_p8, 420, row_p8 * 24, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r2_p8);
DrawText_p8(self_p8->text_p8, 420, (row_p8 + 1) * 24, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r3_p8);
DrawText_p8(self_p8->text_p8, 420, (row_p8 + 2) * 24, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r4_p8);
DrawText_p8(self_p8->text_p8, 420, (row_p8 + 3) * 24, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r5_p8);
DrawText_p8(self_p8->text_p8, 420, (row_p8 + 4) * 24, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r6_p8);
DrawText_p8(self_p8->text_p8, 420, (row_p8 + 5) * 24, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r7_p8);
DrawText_p8(self_p8->text_p8, 420, (row_p8 + 6) * 24, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r8_p8);
DrawText_p8(self_p8->text_p8, 420, (row_p8 + 7) * 24, 7, lbl_806D2D44_p8, lbl_80310478_p8, lbl_806D2D74_p8 * r9_p8);
}
return 1;
}
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/OperationTime_Page.cpp (0x8006a160) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus on
struct InputPlayer_p9 {
virtual void v0_p9();
virtual void v1_p9();
virtual float v2_p9();
virtual void v3_p9();
virtual float StickRight_p9();
virtual float StickLeft_p9();
virtual unsigned char Pressed_p9(int mask_p9);
virtual unsigned char Held_p9(int mask_p9);
};
struct MenuItem_p9 {
int x_p9;
int y_p9;
const char *text_p9;
};
struct TestPage_p9 {
unsigned char pad_0_p9[8];
int blink_p9;
unsigned char pad_C_p9[4];
int next_p9;
unsigned char pad_14_p9[4];
int cursor_p9;
int sub_p9;
unsigned char pad_20_p9[0x14];
int variant_p9;
unsigned char pad_38_p9[0x238];
void *text_p9;
void *data_p9;
};
extern "C"{
extern char lbl_8030E598_p9[];
void *GetInputManager_p9(void);
InputPlayer_p9 *InputMgr_GetPlayer_p9(void *, int);
void DrawText_p9(void *ctx_p9, int x_p9, int y_p9, int color_p9, float scale_p9, const char *fmt_p9, ...);
}
static inline void TestPage_DrawItems_p9(TestPage_p9 *self_p9, MenuItem_p9 *it_p9, int sel_p9)
{
int i_p9;
for (i_p9 = 0; it_p9[i_p9].text_p9 != 0; i_p9++) {
if (i_p9 != sel_p9 || self_p9->blink_p9 <= 0x1E) {
if (self_p9->text_p9 != 0) {
DrawText_p9(self_p9->text_p9, it_p9[i_p9].x_p9 * 14, it_p9[i_p9].y_p9 * 24, 7, 1.0f, it_p9[i_p9].text_p9);
}
}
}
}
struct OperationStats_p9 {
unsigned char pad_0_p9[0x278];
unsigned int playSeconds_p9;
unsigned int counters_p9[3];
};
extern "C"{

extern const char lbl_80310478_p9[];
extern const char lbl_803104C4_p9[];
extern const char lbl_806D2D80_p9[5];
unsigned int OperationClock_GetLifetimeSeconds_p9(void);
void OperationClock_Commit_p9(void);
void NetDiag_PacketRatioPage_p9(TestPage_p9 *self_p9, int phase_p9, int arg_p9);
}
static inline void OperationTime_DrawHMS_p9(TestPage_p9 *self_p9, int y_p9, unsigned int secs_p9)
{
DrawText_p9(self_p9->text_p9, 0x1A4, y_p9, 7, 1.0f, lbl_803104C4_p9, secs_p9 / 3600, (secs_p9 / 60) % 60, secs_p9 % 60);
}

#pragma exceptions on

extern "C"int OperationTime_Page(TestPage_p9 *self_p9, int phase_p9)
{
InputPlayer_p9 *pl_p9;
OperationStats_p9 *st_p9;
unsigned int life_p9;
unsigned int play_p9;
unsigned int avg_p9;
float ratio_p9;
if (phase_p9 == 0) {
self_p9->cursor_p9 = 0;
}
if (phase_p9 == 1) {
pl_p9 = InputMgr_GetPlayer_p9(GetInputManager_p9(), 0);
if (pl_p9->Pressed_p9(0x800)) {
self_p9->blink_p9 = 0x1F;
if (++self_p9->cursor_p9 > 1) {
self_p9->cursor_p9 = 0;
}
}
if (pl_p9->Pressed_p9(0x1000)) {
OperationClock_Commit_p9();
if (self_p9->cursor_p9 == 0) {
self_p9->next_p9 = 0x1A;
NetDiag_PacketRatioPage_p9(self_p9, 0, -1);
} else {
self_p9->next_p9 = 0;
}
}
}
if (phase_p9 == 2) {
TestPage_DrawItems_p9(self_p9, (*(MenuItem_p9 (*)[])&lbl_803FCE88), self_p9->cursor_p9 + 8);
if (self_p9->text_p9 != 0) {
life_p9 = OperationClock_GetLifetimeSeconds_p9();
st_p9 = (OperationStats_p9 *)self_p9->data_p9;
play_p9 = st_p9->playSeconds_p9;
avg_p9 = play_p9 / st_p9->counters_p9[0];
ratio_p9 = (float)play_p9 / (float)life_p9;
if (life_p9 == 0) {
ratio_p9 = 0.0f;
}
if (st_p9->counters_p9[0] == 0) {
avg_p9 = 0;
}
OperationTime_DrawHMS_p9(self_p9, 0x30, life_p9);
OperationTime_DrawHMS_p9(self_p9, 0x48, play_p9);
OperationTime_DrawHMS_p9(self_p9, 0x60, avg_p9);
DrawText_p9(self_p9->text_p9, 0x1A4, 0x78, 7, 1.0f, lbl_80310478_p9, 100.0f * ratio_p9);
DrawText_p9(self_p9->text_p9, 0x1A4, 0x90, 7, 1.0f, lbl_806D2D80_p9, ((OperationStats_p9 *)self_p9->data_p9)->counters_p9[0]);
DrawText_p9(self_p9->text_p9, 0x1A4, 0xA8, 7, 1.0f, lbl_806D2D80_p9, ((OperationStats_p9 *)self_p9->data_p9)->counters_p9[1]);
DrawText_p9(self_p9->text_p9, 0x1A4, 0xC0, 7, 1.0f, lbl_806D2D80_p9, ((OperationStats_p9 *)self_p9->data_p9)->counters_p9[2]);
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/ClockSetting_Page.cpp (0x8006a500) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
#pragma cplusplus on
struct InputPlayer_p10 {
virtual void v0_p10();
virtual void v1_p10();
virtual float v2_p10();
virtual void v3_p10();
virtual float StickRight_p10();
virtual float StickLeft_p10();
virtual unsigned char Pressed_p10(int mask_p10);
virtual unsigned char Held_p10(int mask_p10);
};
struct MenuItem_p10 {
int x_p10;
int y_p10;
const char *text_p10;
};
struct TestPage_p10 {
unsigned char pad_0_p10[8];
int blink_p10;
unsigned char pad_C_p10[4];
int next_p10;
unsigned char pad_14_p10[4];
int cursor_p10;
int sub_p10;
unsigned char pad_20_p10[0x14];
int variant_p10;
unsigned char pad_38_p10[0x238];
void *text_p10;
void *data_p10;
};
extern "C"{
extern char lbl_8030E598_p10[];
void *GetInputManager_p10(void);
InputPlayer_p10 *InputMgr_GetPlayer_p10(void *, int);
void DrawText_p10(void *ctx_p10, int x_p10, int y_p10, int color_p10, float scale_p10, const char *fmt_p10, ...);
}
static inline void TestPage_DrawItems_p10(TestPage_p10 *self_p10, MenuItem_p10 *it_p10, int sel_p10)
{
int i_p10;
for (i_p10 = 0; it_p10[i_p10].text_p10 != 0; i_p10++) {
if (i_p10 != sel_p10 || self_p10->blink_p10 <= 0x1E) {
if (self_p10->text_p10 != 0) {
DrawText_p10(self_p10->text_p10, it_p10[i_p10].x_p10 * 14, it_p10[i_p10].y_p10 * 24, 7, 1.0f, it_p10[i_p10].text_p10);
}
}
}
}
typedef long long OSTime_p10;
struct OSCalendarTime_p10 {
int sec_p10;
int min_p10;
int hour_p10;
int mday_p10;
int mon_p10;
int year_p10;
int wday_p10;
int yday_p10;
int msec_p10;
int usec_p10;
};
struct DayNames_p10 {
const char *name_p10[7];
};
struct ClockEntry_p10 {
signed char hour_p10;
signed char min_p10;
};
struct ClockSettings_p10 {
unsigned char pad_0_p10[0x53];
ClockEntry_p10 day_p10[7];
};
extern "C"{

extern const char lbl_806D2D64_p10[3];
extern const char lbl_806D2D68_p10[5];
extern const char lbl_806D2D90_p10[2];
extern const char lbl_806D2D94_p10[4];
extern const char lbl_806D2D98_p10[4];
extern const char lbl_806D2D9C_p10[5];
void Backup_PublishShadowCopy_Inline_p10(void);
OSTime_p10 OSGetTime_p10(void);
void OSTicksToCalendarTime_p10(OSTime_p10 ticks_p10, OSCalendarTime_p10 *td_p10);
}
static inline ClockEntry_p10 *ClockSetting_Entry_p10(TestPage_p10 *self_p10)
{
return &((ClockSettings_p10 *)self_p10->data_p10)->day_p10[self_p10->cursor_p10];
}

#pragma exceptions on

extern "C"int ClockSetting_Page(TestPage_p10 *self_p10, int phase_p10)
{
char *pool_p10 = lbl_8030E598_p10;
DayNames_p10 days_p10;
OSCalendarTime_p10 t_p10;
int y_p10;
InputPlayer_p10 *pl_p10;
int i_p10;
if (phase_p10 == 0) {
self_p10->cursor_p10 = 7;
self_p10->sub_p10 = 0;
}
if (phase_p10 == 1) {
pl_p10 = InputMgr_GetPlayer_p10(GetInputManager_p10(), 0);
if (self_p10->sub_p10 == 0) {
if (pl_p10->Pressed_p10(0x800)) {
self_p10->blink_p10 = 0x1F;
if (++self_p10->cursor_p10 > 7) {
self_p10->cursor_p10 = 0;
}
}
if (pl_p10->Pressed_p10(0x1000)) {
if (self_p10->cursor_p10 != 7) {
self_p10->sub_p10 = 1;
} else {
Backup_PublishShadowCopy_Inline_p10();
self_p10->next_p10 = 0;
}
}
} else {
if (pl_p10->Pressed_p10(0x800)) {
if (self_p10->sub_p10 == 1) {
if (++(((ClockEntry_p10 *)((char *)(self_p10)->data_p10 + 0x53))[self_p10->cursor_p10]) .hour_p10 > 0x18) {
(((ClockEntry_p10 *)((char *)(self_p10)->data_p10 + 0x53))[self_p10->cursor_p10]) .hour_p10 = 0;
}
} else if (((((ClockEntry_p10 *)((char *)(self_p10)->data_p10 + 0x53))[self_p10->cursor_p10]) .min_p10 += 15) >= 60) {
(((ClockEntry_p10 *)((char *)(self_p10)->data_p10 + 0x53))[self_p10->cursor_p10]) .min_p10 = 0;
}
}
if (pl_p10->Pressed_p10(0x1000)) {
if (self_p10->sub_p10 == 1 && (((ClockEntry_p10 *)((char *)(self_p10)->data_p10 + 0x53))[self_p10->cursor_p10]) .hour_p10 == 0) {
self_p10->sub_p10 = 0;
} else {
self_p10->sub_p10 = (self_p10->sub_p10 + 1) % 3;
}
}
}
}
if (phase_p10 == 2) {
days_p10 = *(DayNames_p10 *)(pool_p10 + 0x1B10);
TestPage_DrawItems_p10(self_p10, (*(MenuItem_p10 (*)[])&lbl_803FCE4C), -1);
if (self_p10->text_p10 != 0) {
for (i_p10 = 0; i_p10 < 7; i_p10++) {
if (i_p10 != self_p10->cursor_p10 || self_p10->sub_p10 != 0 || self_p10->blink_p10 <= 0x1E) {
DrawText_p10(self_p10->text_p10, 0x2A, (i_p10 + 5) * 24, 7, 1.0f, lbl_806D2D64_p10, days_p10.name_p10[i_p10]);
}
y_p10 = (i_p10 + 5) * 24;
DrawText_p10(self_p10->text_p10, 0x7E, y_p10, 7, 1.0f, lbl_806D2D90_p10);
if (i_p10 != self_p10->cursor_p10 || self_p10->sub_p10 != 1 || self_p10->blink_p10 <= 0x1E) {
int h_p10 = (((ClockSettings_p10 *)(self_p10)->data_p10)->day_p10[i_p10]) .hour_p10;
if ((((ClockSettings_p10 *)(self_p10)->data_p10)->day_p10[i_p10]) .hour_p10 == 0) {
DrawText_p10(self_p10->text_p10, 0xE0, y_p10, 7, 1.0f, lbl_806D2D94_p10);
} else {
DrawText_p10(self_p10->text_p10, 0xE0, y_p10, 4, 1.0f, lbl_806D2D98_p10, h_p10);
}
}
if ((((ClockSettings_p10 *)(self_p10)->data_p10)->day_p10[i_p10]) .hour_p10 != 0) {
DrawText_p10(self_p10->text_p10, 0xFC, y_p10, 4, 1.0f, lbl_806D2D90_p10);
}
if (i_p10 != self_p10->cursor_p10 || self_p10->sub_p10 != 2 || self_p10->blink_p10 <= 0x1E) {
if ((((ClockSettings_p10 *)(self_p10)->data_p10)->day_p10[i_p10]) .hour_p10 != 0) {
DrawText_p10(self_p10->text_p10, 0x10A, y_p10, 4, 1.0f, lbl_806D2D9C_p10, (((ClockSettings_p10 *)(self_p10)->data_p10)->day_p10[i_p10]) .min_p10);
}
}
if ((((ClockSettings_p10 *)(self_p10)->data_p10)->day_p10[i_p10]) .hour_p10 != 0) {
int h_p10 = (((ClockSettings_p10 *)(self_p10)->data_p10)->day_p10[i_p10]) .hour_p10;
int m_p10 = (((ClockSettings_p10 *)(self_p10)->data_p10)->day_p10[i_p10]) .min_p10;
int startH_p10 = h_p10;
int startM_p10 = m_p10 - 10;
int endH_p10 = h_p10;
int endM_p10 = m_p10 + 10;
if (startM_p10 < 0) {
startM_p10 = 50;
startH_p10 = h_p10 - 1;
}
if (endM_p10 >= 60) {
endM_p10 = 0;
endH_p10 = endH_p10 + 1;
}
DrawText_p10(self_p10->text_p10, 0x142, y_p10, 7, 1.0f, pool_p10 + 0x1F3C, startH_p10, startM_p10, endH_p10, endM_p10);
}
}
if (self_p10->cursor_p10 != 7 || self_p10->blink_p10 <= 0x1E) {
DrawText_p10(self_p10->text_p10, 0x2A, 0x138, 7, 1.0f, lbl_806D2D68_p10);
}
OSTicksToCalendarTime_p10(OSGetTime_p10(), &t_p10);
DrawText_p10(self_p10->text_p10, 0xE0, 0x48, 7, 1.0f, pool_p10 + 0x1C90, t_p10.year_p10, t_p10.mon_p10 + 1, t_p10.mday_p10,
days_p10.name_p10[t_p10.wday_p10], t_p10.hour_p10, t_p10.min_p10, t_p10.sec_p10);
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CabinetSetting_Page.cpp (0x8006aa84) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus on
struct InputPlayer_p11 {
virtual void v0_p11();
virtual void v1_p11();
virtual float v2_p11();
virtual void v3_p11();
virtual float StickRight_p11();
virtual float StickLeft_p11();
virtual unsigned char Pressed_p11(int mask_p11);
virtual unsigned char Held_p11(int mask_p11);
};
struct MenuItem_p11 {
int x_p11;
int y_p11;
const char *text_p11;
};
struct TestPage_p11 {
unsigned char pad_0_p11[8];
int blink_p11;
unsigned char pad_C_p11[4];
int next_p11;
unsigned char pad_14_p11[4];
int cursor_p11;
int sub_p11;
unsigned char pad_20_p11[0x14];
int variant_p11;
unsigned char pad_38_p11[0x238];
void *text_p11;
void *data_p11;
};
extern "C"{
extern char lbl_8030E598_p11[];
void *GetInputManager_p11(void);
InputPlayer_p11 *InputMgr_GetPlayer_p11(void *, int);
void DrawText_p11(void *ctx_p11, int x_p11, int y_p11, int color_p11, float scale_p11, const char *fmt_p11, ...);
}
static inline void TestPage_DrawItems_p11(TestPage_p11 *self_p11, MenuItem_p11 *it_p11, int sel_p11)
{
int i_p11;
for (i_p11 = 0; it_p11[i_p11].text_p11 != 0; i_p11++) {
if (i_p11 != sel_p11 || self_p11->blink_p11 <= 0x1E) {
if (self_p11->text_p11 != 0) {
DrawText_p11(self_p11->text_p11, it_p11[i_p11].x_p11 * 14, it_p11[i_p11].y_p11 * 24, 7, 1.0f, it_p11[i_p11].text_p11);
}
}
}
}
struct CabinetSettings_p11 {
unsigned char pad_0_p11[0x50];
unsigned char flagA_p11;
unsigned char flagB_p11;
};
extern "C"{

extern const char lbl_806D2D94_p11[4];
extern const char lbl_806D2DA4_p11[6];
extern const char lbl_806D2DAC_p11[3];
void Backup_PublishShadowCopy_Inline_p11(void);
}

#pragma exceptions on

extern "C"int CabinetSetting_Page(TestPage_p11 *self_p11, int phase_p11)
{
InputPlayer_p11 *pl_p11;
CabinetSettings_p11 *cs_p11;
if (phase_p11 == 0) {
self_p11->cursor_p11 = 2;
}
if (phase_p11 == 1) {
pl_p11 = InputMgr_GetPlayer_p11(GetInputManager_p11(), 0);
if (pl_p11->Pressed_p11(0x800)) {
self_p11->blink_p11 = 0x1F;
if (++self_p11->cursor_p11 > 2) {
self_p11->cursor_p11 = 0;
}
}
if (pl_p11->Pressed_p11(0x1000)) {
if (self_p11->cursor_p11 == 0) {
cs_p11 = (CabinetSettings_p11 *)self_p11->data_p11;
if (cs_p11->flagA_p11 != 0) {
cs_p11->flagA_p11 = 0;
} else {
cs_p11->flagA_p11 = 1;
}
}
if (self_p11->cursor_p11 == 1) {
cs_p11 = (CabinetSettings_p11 *)self_p11->data_p11;
if (cs_p11->flagB_p11 != 0) {
cs_p11->flagB_p11 = 0;
} else {
cs_p11->flagB_p11 = 1;
}
}
if (self_p11->cursor_p11 == 2) {
Backup_PublishShadowCopy_Inline_p11();
self_p11->next_p11 = 0;
}
}
}
if (phase_p11 == 2) {
TestPage_DrawItems_p11(self_p11, (*(MenuItem_p11 (*)[])&lbl_803FCDEC), self_p11->cursor_p11 + 2);
if (self_p11->text_p11 != 0) {
DrawText_p11(self_p11->text_p11, 0x16C, 0x30, 2, 1.0f, lbl_806D2DA4_p11);
if (((CabinetSettings_p11 *)self_p11->data_p11)->flagA_p11 != 0) {
DrawText_p11(self_p11->text_p11, 0x1DC, 0x60, 4, 1.0f, lbl_806D2DAC_p11);
} else {
DrawText_p11(self_p11->text_p11, 0x1DC, 0x60, 2, 1.0f, lbl_806D2D94_p11);
}
if (((CabinetSettings_p11 *)self_p11->data_p11)->flagB_p11 != 0) {
DrawText_p11(self_p11->text_p11, 0x1DC, 0x78, 4, 1.0f, lbl_806D2DAC_p11);
} else {
DrawText_p11(self_p11->text_p11, 0x1DC, 0x78, 2, 1.0f, lbl_806D2D94_p11);
}
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardCreate_Page.cpp (0x8006ad0c) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
#pragma cplusplus on
struct InputPlayer_p12 {
virtual void v0_p12();
virtual void v1_p12();
virtual float v2_p12();
virtual void v3_p12();
virtual float StickRight_p12();
virtual float StickLeft_p12();
virtual unsigned char Pressed_p12(int mask_p12);
virtual unsigned char Held_p12(int mask_p12);
};
struct MenuItem_p12 {
int x_p12;
int y_p12;
const char *text_p12;
};
struct TestPage_p12 {
unsigned char pad_0_p12[8];
int blink_p12;
unsigned char pad_C_p12[4];
int next_p12;
unsigned char pad_14_p12[4];
int cursor_p12;
int sub_p12;
unsigned char pad_20_p12[0x14];
int variant_p12;
unsigned char pad_38_p12[0x238];
void *text_p12;
void *data_p12;
};
extern "C"{
extern char lbl_8030E598_p12[];
void *GetInputManager_p12(void);
InputPlayer_p12 *InputMgr_GetPlayer_p12(void *, int);
void DrawText_p12(void *ctx_p12, int x_p12, int y_p12, int color_p12, float scale_p12, const char *fmt_p12, ...);
}
static inline void TestPage_DrawItems_p12(TestPage_p12 *self_p12, MenuItem_p12 *it_p12, int sel_p12)
{
int i_p12;
for (i_p12 = 0; it_p12[i_p12].text_p12 != 0; i_p12++) {
if (i_p12 != sel_p12 || self_p12->blink_p12 <= 0x1E) {
if (self_p12->text_p12 != 0) {
DrawText_p12(self_p12->text_p12, it_p12[i_p12].x_p12 * 14, it_p12[i_p12].y_p12 * 24, 7, 1.0f, it_p12[i_p12].text_p12);
}
}
}
}
struct CardCreateState_p12 {
int phase_p12;
int cursor_p12;
int timer_p12;
int character_p12;
int cc_p12[3];
unsigned char flag_p12[3];
unsigned char pad_1F_p12;
int rank_p12;
int coins_p12;
unsigned char extra_p12;
};
struct CardCreatePage_p12 {
TestPage_p12 base_p12;
unsigned char pad_278_p12[8];
CardCreateState_p12 *state_p12;
};
struct CardCreateNames_p12 {
const char *cc0_p12[3];
const char *cc1_p12[3];
const char *cc2_p12[3];
const char *character_p12[13];
int rank_p12[16];
};
extern "C"{

extern const float lbl_806D2D44_p12;
extern const char *lbl_806CEF28_p12[2];
extern const char *lbl_806CEF30_p12[2];
extern const char *lbl_806CEF38_p12[2];
extern const char *lbl_806CEF40_p12[2];
extern const char lbl_806D2D68_p12[5];
extern const char lbl_806D2DB0_p12[2];
extern unsigned char g_playerData_p12[];
void *Alloc_p12(unsigned long size_p12);
void MemoryManager_TimedFree_p12(void *p_p12);
int WrapInRange_p12(int v_p12, int lo_p12, int hi_p12);
void PlayerData_Construct_p12(void *, int, int, int, int, unsigned char, unsigned char, unsigned char,
int, int, unsigned char);
void card_save_trigger_p12(int);
unsigned char CardSave_Tick_p12(void);
void card_rw_kick_state_machine_p12(void);
unsigned char card_rw_state_machine_p12(void);
void CardRW_TestTopMenu_Page_p12(CardCreatePage_p12 *self_p12, int phase_p12, int arg_p12);
}

#pragma exceptions on

extern "C"int CardCreate_Page(CardCreatePage_p12 *self_p12, int phase_p12)
{

char *pool_p12 = lbl_8030E598_p12;
CardCreateState_p12 *st_p12;
InputPlayer_p12 *pl_p12;
unsigned char up_p12;
unsigned char ok_p12;
void *text_p12;
int coins_p12;
int y_p12;
if (phase_p12 == 0) {
st_p12 = (CardCreateState_p12 *)Alloc_p12(sizeof(CardCreateState_p12));
if (st_p12 != 0) {
st_p12->character_p12 = 0;
st_p12->cc_p12[0] = 0;
st_p12->cc_p12[1] = 0;
st_p12->cc_p12[2] = 0;
st_p12->flag_p12[0] = 0;
st_p12->flag_p12[1] = 0;
st_p12->flag_p12[2] = 0;
st_p12->rank_p12 = 0;
st_p12->coins_p12 = 0;
st_p12->cursor_p12 = 0;
st_p12->extra_p12 = 0;
st_p12->phase_p12 = 0;
st_p12->timer_p12 = 0;
}
self_p12->state_p12 = st_p12;
}
if (phase_p12 == 1) {
up_p12 = 0;
ok_p12 = 0;
pl_p12 = InputMgr_GetPlayer_p12(GetInputManager_p12(), 0);
if (pl_p12->Pressed_p12(0x800)) {
up_p12 = 1;
}
if (pl_p12->Pressed_p12(0x1000)) {
ok_p12 = 1;
}
st_p12 = self_p12->state_p12;
if (st_p12->phase_p12 == 0) {
if (up_p12 == 1) {
st_p12->cursor_p12 = WrapInRange_p12(st_p12->cursor_p12 + 1, 0, 10);
} else if (ok_p12 == 1) {
switch (st_p12->cursor_p12) {
case 0:
st_p12->character_p12 = WrapInRange_p12(st_p12->character_p12 + 1, 0, 12);
break;
case 1:
st_p12->cc_p12[0] = WrapInRange_p12(st_p12->cc_p12[0] + 1, 0, 2);
break;
case 2:
st_p12->cc_p12[1] = WrapInRange_p12(st_p12->cc_p12[1] + 1, 0, 2);
break;
case 3:
st_p12->cc_p12[2] = WrapInRange_p12(st_p12->cc_p12[2] + 1, 0, 2);
break;
case 4:
st_p12->flag_p12[0] = st_p12->flag_p12[0] != 1;
break;
case 5:
st_p12->flag_p12[1] = st_p12->flag_p12[1] != 1;
break;
case 6:
st_p12->flag_p12[2] = st_p12->flag_p12[2] != 1;
break;
case 7:
st_p12->rank_p12 = WrapInRange_p12(st_p12->rank_p12 + 1, 0, 16);
break;
case 8:
st_p12->coins_p12 = WrapInRange_p12(st_p12->coins_p12 + 1, 0, 40);
break;
case 9:
st_p12->extra_p12 = st_p12->extra_p12 != 1;
break;
case 10:
if (st_p12->coins_p12 <= 0) {
coins_p12 = 0;
} else {
coins_p12 = st_p12->coins_p12 * 100 - 1;
}
PlayerData_Construct_p12(g_playerData_p12, st_p12->character_p12, st_p12->cc_p12[0], st_p12->cc_p12[1], st_p12->cc_p12[2],
st_p12->flag_p12[0], st_p12->flag_p12[1], st_p12->flag_p12[2], lbl_803FBFD8[st_p12->rank_p12],
coins_p12, st_p12->extra_p12);
card_save_trigger_p12(0);
st_p12->phase_p12 = 1;
break;
}
}
} else if (st_p12->phase_p12 == 1) {
if (CardSave_Tick_p12() == 1) {
st_p12->phase_p12 = 2;
card_rw_kick_state_machine_p12();
}
} else if (st_p12->phase_p12 == 2) {
if (card_rw_state_machine_p12() == 1) {
st_p12->phase_p12 = 3;
}
}
st_p12->timer_p12++;
if (st_p12->phase_p12 == 3) {
MemoryManager_TimedFree_p12(self_p12->state_p12);
self_p12->base_p12.next_p12 = 5;
CardRW_TestTopMenu_Page_p12(self_p12, 0, 10);
}
}
if (phase_p12 == 2) {
text_p12 = self_p12->base_p12.text_p12;
if (text_p12 != 0) {
st_p12 = self_p12->state_p12;
DrawText_p12(text_p12, 0xE, 0x18, 7, lbl_806D2D44_p12, pool_p12 + 0x1F50);
DrawText_p12(text_p12, 0x1C, 0x48, 7, lbl_806D2D44_p12, pool_p12 + 0x1F5C, lbl_803FBFA4[st_p12->character_p12]);
DrawText_p12(text_p12, 0x1C, 0x60, 7, lbl_806D2D44_p12, pool_p12 + 0x1F70, lbl_803FBF80[st_p12->cc_p12[0]]);
DrawText_p12(text_p12, 0x1C, 0x78, 7, lbl_806D2D44_p12, pool_p12 + 0x1F84, lbl_803FBF8C[st_p12->cc_p12[1]]);
DrawText_p12(text_p12, 0x1C, 0x90, 7, lbl_806D2D44_p12, pool_p12 + 0x1F98, lbl_803FBF98[st_p12->cc_p12[2]]);
DrawText_p12(text_p12, 0x1C, 0xA8, 7, lbl_806D2D44_p12, pool_p12 + 0x1FAC, lbl_806CEF28_p12[st_p12->flag_p12[0] != 0]);
DrawText_p12(text_p12, 0x1C, 0xC0, 7, lbl_806D2D44_p12, pool_p12 + 0x1FC0, lbl_806CEF30_p12[st_p12->flag_p12[1] != 0]);
DrawText_p12(text_p12, 0x1C, 0xD8, 7, lbl_806D2D44_p12, pool_p12 + 0x1FD4, lbl_806CEF38_p12[st_p12->flag_p12[2] != 0]);
DrawText_p12(text_p12, 0x1C, 0xF0, 7, lbl_806D2D44_p12, pool_p12 + 0x1FE8, lbl_803FBFD8[st_p12->rank_p12]);
if (st_p12->coins_p12 <= 0) {
coins_p12 = 0;
} else {
coins_p12 = st_p12->coins_p12 * 100 - 1;
}
DrawText_p12(text_p12, 0x1C, 0x108, 7, lbl_806D2D44_p12, pool_p12 + 0x1FFC, coins_p12);
DrawText_p12(text_p12, 0x1C, 0x120, 7, lbl_806D2D44_p12, pool_p12 + 0x2010, lbl_806CEF40_p12[st_p12->extra_p12 != 0]);
DrawText_p12(text_p12, 0x1C, 0x138, 7, lbl_806D2D44_p12, lbl_806D2D68_p12);
if (st_p12->cursor_p12 == 10) {
y_p12 = 0x138;
} else {
y_p12 = (st_p12->cursor_p12 + 3) * 24;
}
st_p12->timer_p12 &= 0x1F;
if (st_p12->timer_p12 < 0x18) {
DrawText_p12(text_p12, 0xE, y_p12, 7, lbl_806D2D44_p12, lbl_806D2DB0_p12);
}
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset


/* ==== game/CardRW_Renew_Page.c (0x8006b32c) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

struct InputPlayer_p13 {
virtual void v0_p13();
virtual void v1_p13();
virtual float v2_p13();
virtual void v3_p13();
virtual float StickRight_p13();
virtual float StickLeft_p13();
virtual unsigned char Pressed_p13(int mask_p13);
virtual unsigned char Held_p13(int mask_p13);
};
struct MenuItem_p13 {
int x_p13;
int y_p13;
const char *text_p13;
};
struct TestPage_p13 {
unsigned char pad_0_p13[8];
int blink_p13;
unsigned char pad_C_p13[4];
int next_p13;
unsigned char pad_14_p13[4];
int cursor_p13;
int sub_p13;
unsigned char pad_20_p13[0x14];
int variant_p13;
unsigned char pad_38_p13[0x238];
void *text_p13;
void *data_p13;
};
extern "C"{
extern char lbl_8030E598_p13[];
void *GetInputManager_p13(void);
InputPlayer_p13 *InputMgr_GetPlayer_p13(void *, int);
void DrawText_p13(void *ctx_p13, int x_p13, int y_p13, int color_p13, float scale_p13, const char *fmt_p13, ...);
}
static inline void TestPage_DrawItems_p13(TestPage_p13 *self_p13, MenuItem_p13 *it_p13, int sel_p13)
{
int i_p13;
for (i_p13 = 0; it_p13[i_p13].text_p13 != 0; i_p13++) {
if (i_p13 != sel_p13 || self_p13->blink_p13 <= 0x1E) {
if (self_p13->text_p13 != 0) {
DrawText_p13(self_p13->text_p13, it_p13[i_p13].x_p13 * 14, it_p13[i_p13].y_p13 * 24, 7, 1.0f, it_p13[i_p13].text_p13);
}
}
}
}
struct RenewPage_p13 {
unsigned char pad0_p13[8];
int blink_p13;
unsigned char padC_p13[4];
int next_p13;
unsigned char pad14_p13[8];
int selection_p13;
unsigned char pad20_p13[12];
int step_p13;
unsigned char pad30_p13[0x2b];
unsigned char failed_p13;
unsigned char pad5C_p13[0x214];
void *text_p13;
unsigned char pad274_p13[8];
RenewTick_p13 tick_p13;
int field280_p13;
int error_p13;
};
struct RenewCount_p13 {
unsigned char remaining_p13;
unsigned char used_p13;
};
struct RenewPlayerData_p13 {
unsigned char pad0_p13[0x198];
RenewCount_p13 renew_p13;
};
extern "C"{
extern RenewPlayerData_p13 g_playerData_p13;


void CardRW_TestTopMenu_Page_p13(RenewPage_p13 *, int, int);
unsigned char CardRW_ErrorDisplay_p13(RenewPage_p13 *, int, int, int);
int Sci2Card_GetPrintErrorCode_p13();
unsigned char Sci2Card_GetByteFlag1224_p13();
void *Sci2Card_Singleton_Get_p13();
void Sci2Card_GetResponseStatus_p13(void *, unsigned char *, unsigned char *, unsigned char *);
unsigned char Sci2Card_IsRetryExhausted_p13(void *);
unsigned char Sci2Card_IsStatus2Two_p13(void *);
unsigned char Sci2Card_IsStatus2Three_p13(void *);
unsigned char Sci2Card_IsStatus2Five_p13(void *);
unsigned char Sci2Card_IsStatus2A_p13(void *);
unsigned char Sci2Card_IsStatus3Five_p13(void *);
}
static inline int Renew_CheckError_p13()
{
int error_p13 = 1;
void *card_p13 = Sci2Card_Singleton_Get_p13();
if (Sci2Card_IsRetryExhausted_p13(card_p13) == 1) error_p13 = 101;
else if (Sci2Card_IsStatus2Two_p13(card_p13) == 1) error_p13 = 102;
else if (Sci2Card_IsStatus2Three_p13(card_p13) == 1) error_p13 = 104;
else if (Sci2Card_IsStatus2Five_p13(card_p13) == 1) error_p13 = 105;
else if (Sci2Card_IsStatus2A_p13(card_p13) == 1) error_p13 = 106;
else if (Sci2Card_IsStatus3Five_p13(card_p13) == 1) error_p13 = 2;
return error_p13;
}
static inline void Renew_DrawItems_p13(RenewPage_p13 *self_p13, MenuItem_p13 *it_p13, int sel_p13)
{
int i_p13;
for (i_p13 = 0; it_p13[i_p13].text_p13 != 0; i_p13++) {
if (i_p13 != sel_p13 || self_p13->blink_p13 <= 30) {
if (self_p13->text_p13 != 0)
DrawText_p13(self_p13->text_p13, it_p13[i_p13].x_p13 * 14, it_p13[i_p13].y_p13 * 24, 7, 1.0f, it_p13[i_p13].text_p13);
}
}
}
static inline unsigned char Renew_HasFatalError_p13(RenewPage_p13 *self_p13)
{
int error_p13 = self_p13->error_p13;
if (error_p13 == 1) return 0;
if (self_p13->text_p13 == 0) return 0;
if (error_p13 == 101) return 1;
if (error_p13 == 102) return 1;
if (error_p13 == 104) return 1;
if (error_p13 == 100) return 1;
if (error_p13 == 105) return 1;
if (error_p13 == 106) return 1;
if (error_p13 == 2) return 1;
if (error_p13 == 6) return 1;
if (error_p13 == 7) return 1;
if (error_p13 == 255) return 1;
return 0;
}
extern "C"int CardRW_Renew_Page(RenewPage_p13 *self_p13, int phase_p13, int arg_p13)
{
char *strings_p13 = lbl_8030E598_p13;
if (phase_p13 == 0) {
self_p13->selection_p13 = 1;
self_p13->step_p13 = 0;
self_p13->tick_p13 = 0;
self_p13->error_p13 = 1;
self_p13->failed_p13 = 0;
}
if (phase_p13 == 1) {
InputPlayer_p13 *input_p13 = InputMgr_GetPlayer_p13(GetInputManager_p13(), 0);
if (self_p13->step_p13 == 0) {
if (self_p13->error_p13 == 1 && input_p13->Pressed_p13(0x800)) {
self_p13->blink_p13 = 31;
if (++self_p13->selection_p13 > 1) self_p13->selection_p13 = 0;
}
if (input_p13->Pressed_p13(0x1000)) {
if (self_p13->selection_p13 == 0) {
self_p13->selection_p13 = 100;
self_p13->step_p13 = 1;
self_p13->blink_p13 = 0;
self_p13->tick_p13 = lbl_803FDDD8[self_p13->step_p13].tick_p13;
self_p13->error_p13 = 1;
self_p13->failed_p13 = 0;
self_p13->error_p13 = Renew_CheckError_p13();
if (self_p13->error_p13 != 1) {
self_p13->failed_p13 = 1;
self_p13->blink_p13 = 31;
self_p13->step_p13 = 0;
}
} else {
self_p13->next_p13 = 5;
CardRW_TestTopMenu_Page_p13(self_p13, 0, 9);
}
}
} else {
if (self_p13->tick_p13 != 0) {
if (self_p13->tick_p13() == 1) {
if (!self_p13->failed_p13 && lbl_803FDDD8[self_p13->step_p13].checkError_p13) {
self_p13->error_p13 = Sci2Card_GetPrintErrorCode_p13();
if (CardRW_ErrorDisplay_p13(self_p13, 0, 1, 1)) {
self_p13->step_p13 = 12;
self_p13->failed_p13 = 1;
}
}
if (self_p13->step_p13 == 2 && !Sci2Card_GetByteFlag1224_p13()) {
self_p13->step_p13 = 0;
self_p13->failed_p13 = 0;
}
if (self_p13->step_p13 == 4) {
RenewCount_p13 *count_p13 = &g_playerData_p13.renew_p13;
count_p13->remaining_p13 = 50;
count_p13->used_p13 = 0;
}
++self_p13->step_p13;
self_p13->tick_p13 = lbl_803FDDD8[self_p13->step_p13].tick_p13;
}
if (self_p13->failed_p13 && Renew_HasFatalError_p13(self_p13)) self_p13->blink_p13 = 31;
} else {
unsigned char leave_p13 = 1;
if (CardRW_ErrorDisplay_p13(self_p13, 0, 1, 0) && !input_p13->Pressed_p13(0x1000)) leave_p13 = 0;
if (!Renew_HasFatalError_p13(self_p13) || leave_p13) {
self_p13->next_p13 = 5;
CardRW_TestTopMenu_Page_p13(self_p13, 0, 9);
}
}
}
}
if (phase_p13 == 2) {
Renew_DrawItems_p13(self_p13, (*(MenuItem_p13 (*)[])&lbl_803FCD8C), self_p13->selection_p13 + 3);
if (self_p13->text_p13 != 0) {
unsigned char c_p13, b_p13, a_p13;
Sci2Card_GetResponseStatus_p13(Sci2Card_Singleton_Get_p13(), &a_p13, &b_p13, &c_p13);
DrawText_p13(self_p13->text_p13, 168, 72, 7, 1.0f, strings_p13 + 0x1c78, a_p13, b_p13, c_p13);
}
if (!CardRW_ErrorDisplay_p13(self_p13, 1, 1, 1) && self_p13->text_p13 != 0) {
switch (self_p13->step_p13) {
case 1: case 2:
DrawText_p13(self_p13->text_p13, 84, 264, 7, 1.0f, strings_p13 + 0x2024);
if (self_p13->blink_p13 <= 30)
DrawText_p13(self_p13->text_p13, 84, 312, 7, 1.0f, strings_p13 + 0x2038);
break;
case 3: case 4:
DrawText_p13(self_p13->text_p13, 84, 264, 7, 1.0f, strings_p13 + 0x204c);
if (self_p13->blink_p13 <= 30)
DrawText_p13(self_p13->text_p13, 84, 312, 7, 1.0f, strings_p13 + 0x2064);
break;
case 5: case 6:
DrawText_p13(self_p13->text_p13, 84, 264, 7, 1.0f, strings_p13 + 0x207c);
if (self_p13->blink_p13 <= 30)
DrawText_p13(self_p13->text_p13, 84, 312, 7, 1.0f, strings_p13 + 0x1c58);
break;
case 7: case 8: case 9: case 10: case 11: case 12:
DrawText_p13(self_p13->text_p13, 84, 264, 7, 1.0f, strings_p13 + 0x2090);
if (self_p13->blink_p13 <= 30)
DrawText_p13(self_p13->text_p13, 84, 288, 7, 1.0f, strings_p13 + 0x2064);
break;
case 13: case 14:
if (self_p13->error_p13 == 1)
DrawText_p13(self_p13->text_p13, 84, 264, 7, 1.0f, strings_p13 + 0x20a4);
if (self_p13->blink_p13 <= 30)
DrawText_p13(self_p13->text_p13, 84, 288, 7, 1.0f, strings_p13 + 0x1c58);
break;
}
}
}
return 1;
}

#pragma use_lmw_stmw reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardRW_HardwareInit_Page.c (0x8006bb04) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

struct InputPlayer_p14 {
virtual void v0_p14();
virtual void v1_p14();
virtual float v2_p14();
virtual void v3_p14();
virtual float StickRight_p14();
virtual float StickLeft_p14();
virtual unsigned char Pressed_p14(int mask_p14);
virtual unsigned char Held_p14(int mask_p14);
};
struct MenuItem_p14 {
int x_p14;
int y_p14;
const char *text_p14;
};
struct TestPage_p14 {
unsigned char pad_0_p14[8];
int blink_p14;
unsigned char pad_C_p14[4];
int next_p14;
unsigned char pad_14_p14[4];
int cursor_p14;
int sub_p14;
unsigned char pad_20_p14[0x14];
int variant_p14;
unsigned char pad_38_p14[0x238];
void *text_p14;
void *data_p14;
};
extern "C"{
extern char lbl_8030E598_p14[];
void *GetInputManager_p14(void);
InputPlayer_p14 *InputMgr_GetPlayer_p14(void *, int);
void DrawText_p14(void *ctx_p14, int x_p14, int y_p14, int color_p14, float scale_p14, const char *fmt_p14, ...);
}
static inline void TestPage_DrawItems_p14(TestPage_p14 *self_p14, MenuItem_p14 *it_p14, int sel_p14)
{
int i_p14;
for (i_p14 = 0; it_p14[i_p14].text_p14 != 0; i_p14++) {
if (i_p14 != sel_p14 || self_p14->blink_p14 <= 0x1E) {
if (self_p14->text_p14 != 0) {
DrawText_p14(self_p14->text_p14, it_p14[i_p14].x_p14 * 14, it_p14[i_p14].y_p14 * 24, 7, 1.0f, it_p14[i_p14].text_p14);
}
}
}
}
struct HardwareInitPage_p14 {
unsigned char pad0_p14[8];
int blink_p14;
unsigned char padC_p14[4];
int next_p14;
unsigned char pad14_p14[8];
int selection_p14;
unsigned char pad20_p14[12];
int step_p14;
int error_p14;
unsigned char pad34_p14[0x23C];
void *text_p14;
unsigned char pad274_p14[8];
int field27C_p14;
};
extern "C"{

extern char lbl_806D2DB4_p14[5];
void CardRW_TestTopMenu_Page_p14(HardwareInitPage_p14 *, int, int);
unsigned char CardRW_ErrorDisplay_p14(HardwareInitPage_p14 *, int, int, int);
void *Sci2Card_Singleton_Get_p14();
void Sci2Card_SendCmdRetry_p14(void *, int);
unsigned char Sci2Card_IsIdleOrExhausted_p14(void *);
unsigned char Sci2Card_IsStatusOkNonTerm_p14(void *);
unsigned char Sci2Card_IsRetryExhausted_p14(void *);
unsigned char Sci2Card_IsStatus2Two_p14(void *);
unsigned char Sci2Card_IsStatus2Three_p14(void *);
unsigned char Sci2Card_IsStatus2Five_p14(void *);
unsigned char Sci2Card_IsStatus2A_p14(void *);
unsigned char Sci2Card_IsStatus3Five_p14(void *);
unsigned char CardPrintJob_KickFontTransfer_p14();
unsigned char CardPrintJob_TickFontTransfer_p14();
void Sci2Card_GetResponseStatus_p14(void *, unsigned char *, unsigned char *, unsigned char *);
}
static inline void HardwareInit_DrawItems_p14(HardwareInitPage_p14 *self_p14, MenuItem_p14 *it_p14, int sel_p14)
{
int i_p14;
for (i_p14 = 0; it_p14[i_p14].text_p14 != 0; i_p14++) {
if (i_p14 != sel_p14 || self_p14->blink_p14 <= 30) {
if (self_p14->text_p14 != 0)
DrawText_p14(self_p14->text_p14, it_p14[i_p14].x_p14 * 14, it_p14[i_p14].y_p14 * 24, 7, 1.0f, it_p14[i_p14].text_p14);
}
}
}
extern "C"int CardRW_HardwareInit_Page(HardwareInitPage_p14 *self_p14, int phase_p14, int arg_p14)
{
char *strings_p14 = lbl_8030E598_p14;
if (phase_p14 == 0) {
self_p14->selection_p14 = 1;
self_p14->step_p14 = 0;
self_p14->error_p14 = 0;
self_p14->field27C_p14 = 0;
}
if (phase_p14 == 1) {
if (self_p14->step_p14 == 0) {
InputPlayer_p14 *input_p14 = InputMgr_GetPlayer_p14(GetInputManager_p14(), 0);
if (input_p14->Pressed_p14(0x800)) {
self_p14->blink_p14 = 31;
if (++self_p14->selection_p14 > 1) self_p14->selection_p14 = 0;
}
if (input_p14->Pressed_p14(0x1000)) {
if (self_p14->selection_p14 == 0) {
self_p14->selection_p14 = 100;
self_p14->step_p14 = 1;
self_p14->blink_p14 = 0;
} else {
self_p14->next_p14 = 5;
CardRW_TestTopMenu_Page_p14(self_p14, 0, 8);
}
}
} else if (self_p14->error_p14 != 0) {
InputPlayer_p14 *input_p14 = InputMgr_GetPlayer_p14(GetInputManager_p14(), 0);
if (input_p14->Pressed_p14(0x1000)) {
self_p14->next_p14 = 5;
CardRW_TestTopMenu_Page_p14(self_p14, 0, 8);
}
} else if (self_p14->step_p14 == 1) {
Sci2Card_SendCmdRetry_p14(Sci2Card_Singleton_Get_p14(), 1);
++self_p14->step_p14;
} else if (self_p14->step_p14 == 2) {
void *card_p14 = Sci2Card_Singleton_Get_p14();
if (Sci2Card_IsIdleOrExhausted_p14(card_p14) == 1) {
if (Sci2Card_IsStatusOkNonTerm_p14(card_p14)) ++self_p14->step_p14;
else {
if (Sci2Card_IsRetryExhausted_p14(card_p14) == 1) self_p14->error_p14 = 1;
else if (Sci2Card_IsStatus2Two_p14(card_p14) == 1) self_p14->error_p14 = 2;
else if (Sci2Card_IsStatus2Three_p14(card_p14) == 1) self_p14->error_p14 = 3;
else if (Sci2Card_IsStatus2Five_p14(card_p14) == 1) self_p14->error_p14 = 4;
else if (Sci2Card_IsStatus2A_p14(card_p14) == 1) self_p14->error_p14 = 5;
else if (Sci2Card_IsStatus3Five_p14(card_p14) == 1) self_p14->error_p14 = 6;
self_p14->step_p14 = 5;
self_p14->selection_p14 = 1;
}
}
} else if (self_p14->step_p14 == 3) {
if (CardPrintJob_KickFontTransfer_p14() == 1) ++self_p14->step_p14;
} else if (self_p14->step_p14 == 4) {
if (CardPrintJob_TickFontTransfer_p14() == 1) ++self_p14->step_p14;
} else {
if (++self_p14->step_p14 >= 63) {
self_p14->next_p14 = 5;
CardRW_TestTopMenu_Page_p14(self_p14, 0, 8);
}
}
}
if (phase_p14 == 2) {
HardwareInit_DrawItems_p14(self_p14, (*(MenuItem_p14 (*)[])&lbl_803FCD2C), self_p14->selection_p14 + 3);
if (self_p14->text_p14 != 0) {
unsigned char c_p14, b_p14, a_p14;
Sci2Card_GetResponseStatus_p14(Sci2Card_Singleton_Get_p14(), &a_p14, &b_p14, &c_p14);
DrawText_p14(self_p14->text_p14, 168, 72, 7, 1.0f, strings_p14 + 0x1c78, a_p14, b_p14, c_p14);
}
if (!CardRW_ErrorDisplay_p14(self_p14, 1, 1, 0) && self_p14->text_p14 != 0) {
if (self_p14->step_p14 == 1 || self_p14->step_p14 == 2 || self_p14->step_p14 == 3 || self_p14->step_p14 == 4) {
DrawText_p14(self_p14->text_p14, 84, 192, 7, 1.0f, strings_p14 + 0x20bc);
if (self_p14->blink_p14 <= 30)
DrawText_p14(self_p14->text_p14, 84, 240, 7, 1.0f, strings_p14 + 0x2064);
} else if (self_p14->step_p14 >= 5) {
if (self_p14->error_p14 == 0) {
DrawText_p14(self_p14->text_p14, 84, 192, 7, 1.0f, strings_p14 + 0x20d0);
} else {
DrawText_p14(self_p14->text_p14, 84, 168, 7, 1.0f, lbl_806D2DB4_p14, self_p14->error_p14);
if (self_p14->error_p14 == 1)
DrawText_p14(self_p14->text_p14, 84, 192, 7, 1.0f, strings_p14 + 0x1b6c);
if (self_p14->error_p14 == 2)
DrawText_p14(self_p14->text_p14, 84, 192, 7, 1.0f, strings_p14 + 0x1b9c);
if (self_p14->error_p14 == 3)
DrawText_p14(self_p14->text_p14, 84, 192, 7, 1.0f, strings_p14 + 0x1bb8);
if (self_p14->error_p14 == 4)
DrawText_p14(self_p14->text_p14, 84, 192, 7, 1.0f, strings_p14 + 0x1bd0);
if (self_p14->error_p14 == 5)
DrawText_p14(self_p14->text_p14, 84, 192, 7, 1.0f, strings_p14 + 0x1be8);
if (self_p14->error_p14 == 6)
DrawText_p14(self_p14->text_p14, 84, 192, 7, 1.0f, strings_p14 + 0x1c00);
if (self_p14->blink_p14 <= 30)
DrawText_p14(self_p14->text_p14, 84, 240, 7, 1.0f, strings_p14 + 0x1b80);
}
}
}
}
return 1;
}

#pragma use_lmw_stmw reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardRW_Reprint_Page.c (0x8006c0f4) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

struct InputPlayer_p15 {
virtual void v0_p15();
virtual void v1_p15();
virtual float v2_p15();
virtual void v3_p15();
virtual float StickRight_p15();
virtual float StickLeft_p15();
virtual unsigned char Pressed_p15(int mask_p15);
virtual unsigned char Held_p15(int mask_p15);
};
struct MenuItem_p15 {
int x_p15;
int y_p15;
const char *text_p15;
};
struct TestPage_p15 {
unsigned char pad_0_p15[8];
int blink_p15;
unsigned char pad_C_p15[4];
int next_p15;
unsigned char pad_14_p15[4];
int cursor_p15;
int sub_p15;
unsigned char pad_20_p15[0x14];
int variant_p15;
unsigned char pad_38_p15[0x238];
void *text_p15;
void *data_p15;
};
extern "C"{
extern char lbl_8030E598_p15[];
void *GetInputManager_p15(void);
InputPlayer_p15 *InputMgr_GetPlayer_p15(void *, int);
void DrawText_p15(void *ctx_p15, int x_p15, int y_p15, int color_p15, float scale_p15, const char *fmt_p15, ...);
}
static inline void TestPage_DrawItems_p15(TestPage_p15 *self_p15, MenuItem_p15 *it_p15, int sel_p15)
{
int i_p15;
for (i_p15 = 0; it_p15[i_p15].text_p15 != 0; i_p15++) {
if (i_p15 != sel_p15 || self_p15->blink_p15 <= 0x1E) {
if (self_p15->text_p15 != 0) {
DrawText_p15(self_p15->text_p15, it_p15[i_p15].x_p15 * 14, it_p15[i_p15].y_p15 * 24, 7, 1.0f, it_p15[i_p15].text_p15);
}
}
}
}
struct ReprintPage_p15 {
unsigned char pad0_p15[8];
int blink_p15;
unsigned char padC_p15[4];
int next_p15;
unsigned char pad14_p15[8];
int selection_p15;
unsigned char pad20_p15[12];
int step_p15;
unsigned char pad30_p15[0x2b];
unsigned char failed_p15;
unsigned char pad5C_p15[0x214];
void *text_p15;
unsigned char pad274_p15[8];
ReprintTick_p15 tick_p15;
int field280_p15;
int error_p15;
};
extern "C"{


void CardRW_TestTopMenu_Page_p15(ReprintPage_p15 *, int, int);
unsigned char CardRW_ErrorDisplay_p15(ReprintPage_p15 *, int, int, int);
int Sci2Card_GetPrintErrorCode_p15();
unsigned char Sci2Card_GetByteFlag1224_p15();
void *Sci2Card_Singleton_Get_p15();
void Sci2Card_GetResponseStatus_p15(void *, unsigned char *, unsigned char *, unsigned char *);
unsigned char Sci2Card_IsRetryExhausted_p15(void *);
unsigned char Sci2Card_IsStatus2Two_p15(void *);
unsigned char Sci2Card_IsStatus2Three_p15(void *);
unsigned char Sci2Card_IsStatus2Five_p15(void *);
unsigned char Sci2Card_IsStatus2A_p15(void *);
unsigned char Sci2Card_IsStatus3Five_p15(void *);
}
static inline int Reprint_CheckError_p15()
{
int error_p15 = 1;
void *card_p15 = Sci2Card_Singleton_Get_p15();
if (Sci2Card_IsRetryExhausted_p15(card_p15) == 1) error_p15 = 101;
else if (Sci2Card_IsStatus2Two_p15(card_p15) == 1) error_p15 = 102;
else if (Sci2Card_IsStatus2Three_p15(card_p15) == 1) error_p15 = 104;
else if (Sci2Card_IsStatus2Five_p15(card_p15) == 1) error_p15 = 105;
else if (Sci2Card_IsStatus2A_p15(card_p15) == 1) error_p15 = 106;
else if (Sci2Card_IsStatus3Five_p15(card_p15) == 1) error_p15 = 2;
return error_p15;
}
static inline void Reprint_DrawItems_p15(ReprintPage_p15 *self_p15, MenuItem_p15 *it_p15, int sel_p15)
{
int i_p15;
for (i_p15 = 0; it_p15[i_p15].text_p15 != 0; i_p15++) {
if (i_p15 != sel_p15 || self_p15->blink_p15 <= 30) {
if (self_p15->text_p15 != 0)
DrawText_p15(self_p15->text_p15, it_p15[i_p15].x_p15 * 14, it_p15[i_p15].y_p15 * 24, 7, 1.0f, it_p15[i_p15].text_p15);
}
}
}
static inline unsigned char Reprint_HasFatalError_p15(ReprintPage_p15 *self_p15)
{
int error_p15 = self_p15->error_p15;
if (error_p15 == 1) return 0;
if (self_p15->text_p15 == 0) return 0;
if (error_p15 == 101) return 1;
if (error_p15 == 102) return 1;
if (error_p15 == 104) return 1;
if (error_p15 == 100) return 1;
if (error_p15 == 105) return 1;
if (error_p15 == 106) return 1;
if (error_p15 == 2) return 1;
if (error_p15 == 6) return 1;
if (error_p15 == 7) return 1;
if (error_p15 == 255) return 1;
return 0;
}
extern "C"int CardRW_Reprint_Page(ReprintPage_p15 *self_p15, int phase_p15, int arg_p15)
{
char *strings_p15 = lbl_8030E598_p15;
if (phase_p15 == 0) {
self_p15->selection_p15 = 1;
self_p15->step_p15 = 0;
self_p15->tick_p15 = 0;
self_p15->error_p15 = 1;
self_p15->failed_p15 = 0;
}
if (phase_p15 == 1) {
InputPlayer_p15 *input_p15 = InputMgr_GetPlayer_p15(GetInputManager_p15(), 0);
if (self_p15->step_p15 == 0) {
if (self_p15->error_p15 == 1 && input_p15->Pressed_p15(0x800)) {
self_p15->blink_p15 = 31;
if (++self_p15->selection_p15 > 1) self_p15->selection_p15 = 0;
}
if (input_p15->Pressed_p15(0x1000)) {
if (self_p15->selection_p15 == 0) {
self_p15->selection_p15 = 100;
self_p15->step_p15 = 1;
self_p15->blink_p15 = 0;
self_p15->tick_p15 = lbl_803FDD88[self_p15->step_p15].tick_p15;
self_p15->error_p15 = 1;
self_p15->failed_p15 = 0;
self_p15->error_p15 = Reprint_CheckError_p15();
if (self_p15->error_p15 != 1) {
self_p15->failed_p15 = 1;
self_p15->blink_p15 = 31;
self_p15->step_p15 = 0;
}
} else {
self_p15->next_p15 = 5;
CardRW_TestTopMenu_Page_p15(self_p15, 0, 7);
}
}
} else {
if (self_p15->tick_p15 != 0) {
if (self_p15->tick_p15() == 1) {
if (!self_p15->failed_p15 && lbl_803FDD88[self_p15->step_p15].checkError_p15) {
self_p15->error_p15 = Sci2Card_GetPrintErrorCode_p15();
if (CardRW_ErrorDisplay_p15(self_p15, 0, 1, 1)) {
self_p15->step_p15 = 6;
self_p15->failed_p15 = 1;
}
}
if (self_p15->step_p15 == 2 && !Sci2Card_GetByteFlag1224_p15()) {
self_p15->step_p15 = 0;
self_p15->failed_p15 = 0;
}
++self_p15->step_p15;
self_p15->tick_p15 = lbl_803FDD88[self_p15->step_p15].tick_p15;
}
if (self_p15->failed_p15 && Reprint_HasFatalError_p15(self_p15)) self_p15->blink_p15 = 31;
} else {
unsigned char leave_p15 = 1;
if (CardRW_ErrorDisplay_p15(self_p15, 0, 1, 0) && !input_p15->Pressed_p15(0x1000)) leave_p15 = 0;
if (!Reprint_HasFatalError_p15(self_p15) || leave_p15) {
self_p15->next_p15 = 5;
CardRW_TestTopMenu_Page_p15(self_p15, 0, 7);
}
}
}
}
if (phase_p15 == 2) {
Reprint_DrawItems_p15(self_p15, (*(MenuItem_p15 (*)[])&lbl_803FCCCC), self_p15->selection_p15 + 3);
if (self_p15->text_p15 != 0) {
unsigned char c_p15, b_p15, a_p15;
Sci2Card_GetResponseStatus_p15(Sci2Card_Singleton_Get_p15(), &a_p15, &b_p15, &c_p15);
DrawText_p15(self_p15->text_p15, 168, 72, 7, 1.0f, strings_p15 + 0x1c78, a_p15, b_p15, c_p15);
}
if (!CardRW_ErrorDisplay_p15(self_p15, 1, 1, 1) && self_p15->text_p15 != 0) {
switch (self_p15->step_p15) {
case 1: case 2:
DrawText_p15(self_p15->text_p15, 84, 192, 7, 1.0f, strings_p15 + 0x20ec);
if (self_p15->blink_p15 <= 30)
DrawText_p15(self_p15->text_p15, 84, 240, 7, 1.0f, strings_p15 + 0x2038);
break;
case 3: case 4: case 5: case 6:
DrawText_p15(self_p15->text_p15, 84, 192, 7, 1.0f, strings_p15 + 0x2104);
if (self_p15->blink_p15 <= 30)
DrawText_p15(self_p15->text_p15, 84, 240, 7, 1.0f, strings_p15 + 0x2064);
break;
case 7: case 8:
DrawText_p15(self_p15->text_p15, 84, 192, 7, 1.0f, strings_p15 + 0x2114);
if (self_p15->blink_p15 <= 30)
DrawText_p15(self_p15->text_p15, 84, 240, 7, 1.0f, strings_p15 + 0x1c58);
DrawText_p15(self_p15->text_p15, 84, 288, 7, 1.0f, strings_p15 + 0x212c);
break;
}
}
}
return 1;
}

#pragma use_lmw_stmw reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardRW_DataRepair_Page.c (0x8006c810) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

struct InputPlayer_p16 {
virtual void v0_p16();
virtual void v1_p16();
virtual float v2_p16();
virtual void v3_p16();
virtual float StickRight_p16();
virtual float StickLeft_p16();
virtual unsigned char Pressed_p16(int mask_p16);
virtual unsigned char Held_p16(int mask_p16);
};
struct MenuItem_p16 {
int x_p16;
int y_p16;
const char *text_p16;
};
struct TestPage_p16 {
unsigned char pad_0_p16[8];
int blink_p16;
unsigned char pad_C_p16[4];
int next_p16;
unsigned char pad_14_p16[4];
int cursor_p16;
int sub_p16;
unsigned char pad_20_p16[0x14];
int variant_p16;
unsigned char pad_38_p16[0x238];
void *text_p16;
void *data_p16;
};
extern "C"{
extern char lbl_8030E598_p16[];
void *GetInputManager_p16(void);
InputPlayer_p16 *InputMgr_GetPlayer_p16(void *, int);
void DrawText_p16(void *ctx_p16, int x_p16, int y_p16, int color_p16, float scale_p16, const char *fmt_p16, ...);
}
static inline void TestPage_DrawItems_p16(TestPage_p16 *self_p16, MenuItem_p16 *it_p16, int sel_p16)
{
int i_p16;
for (i_p16 = 0; it_p16[i_p16].text_p16 != 0; i_p16++) {
if (i_p16 != sel_p16 || self_p16->blink_p16 <= 0x1E) {
if (self_p16->text_p16 != 0) {
DrawText_p16(self_p16->text_p16, it_p16[i_p16].x_p16 * 14, it_p16[i_p16].y_p16 * 24, 7, 1.0f, it_p16[i_p16].text_p16);
}
}
}
}
struct ReprintPage_p16 {
unsigned char pad0_p16[8];
int blink_p16;
unsigned char padC_p16[4];
int next_p16;
unsigned char pad14_p16[8];
int selection_p16;
unsigned char pad20_p16[12];
int step_p16;
unsigned char pad30_p16[0x2b];
unsigned char failed_p16;
unsigned char pad5C_p16[0x214];
void *text_p16;
unsigned char pad274_p16[8];
ReprintTick_p16 tick_p16;
int field280_p16;
int error_p16;
};
extern "C"{


void CardRW_TestTopMenu_Page_p16(ReprintPage_p16 *, int, int);
unsigned char CardRW_ErrorDisplay_p16(ReprintPage_p16 *, int, int, int);
int Sci2Card_GetPrintErrorCode_p16();
unsigned char Sci2Card_GetByteFlag1224_p16();
void *Sci2Card_Singleton_Get_p16();
void Sci2Card_GetResponseStatus_p16(void *, unsigned char *, unsigned char *, unsigned char *);
unsigned char Sci2Card_IsRetryExhausted_p16(void *);
unsigned char Sci2Card_IsStatus2Two_p16(void *);
unsigned char Sci2Card_IsStatus2Three_p16(void *);
unsigned char Sci2Card_IsStatus2Five_p16(void *);
unsigned char Sci2Card_IsStatus2A_p16(void *);
unsigned char Sci2Card_IsStatus3Five_p16(void *);
}
static inline int Reprint_CheckError_p16()
{
int error_p16 = 1;
void *card_p16 = Sci2Card_Singleton_Get_p16();
if (Sci2Card_IsRetryExhausted_p16(card_p16) == 1) error_p16 = 101;
else if (Sci2Card_IsStatus2Two_p16(card_p16) == 1) error_p16 = 102;
else if (Sci2Card_IsStatus2Three_p16(card_p16) == 1) error_p16 = 104;
else if (Sci2Card_IsStatus2Five_p16(card_p16) == 1) error_p16 = 105;
else if (Sci2Card_IsStatus2A_p16(card_p16) == 1) error_p16 = 106;
else if (Sci2Card_IsStatus3Five_p16(card_p16) == 1) error_p16 = 2;
return error_p16;
}
static inline void Reprint_DrawItems_p16(ReprintPage_p16 *self_p16, MenuItem_p16 *it_p16, int sel_p16)
{
int i_p16;
for (i_p16 = 0; it_p16[i_p16].text_p16 != 0; i_p16++) {
if (i_p16 != sel_p16 || self_p16->blink_p16 <= 30) {
if (self_p16->text_p16 != 0)
DrawText_p16(self_p16->text_p16, it_p16[i_p16].x_p16 * 14, it_p16[i_p16].y_p16 * 24, 7, 1.0f, it_p16[i_p16].text_p16);
}
}
}
static inline unsigned char Reprint_HasFatalError_p16(ReprintPage_p16 *self_p16)
{
int error_p16 = self_p16->error_p16;
if (error_p16 == 1) return 0;
if (self_p16->text_p16 == 0) return 0;
if (error_p16 == 101) return 1;
if (error_p16 == 102) return 1;
if (error_p16 == 104) return 1;
if (error_p16 == 100) return 1;
if (error_p16 == 105) return 1;
if (error_p16 == 106) return 1;
if (error_p16 == 2) return 1;
if (error_p16 == 6) return 1;
if (error_p16 == 7) return 1;
if (error_p16 == 255) return 1;
return 0;
}
struct RepairWords3_p16 {
unsigned int w_p16[3];
};
struct RepairWords16_p16 {
unsigned int w_p16[16];
};

#pragma options align=packed

struct RepairPackedWords_p16 {
unsigned int w_p16[6];
};

#pragma options align=reset

struct RepairPlayerData_p16 {
RepairWords3_p16 head_p16;
unsigned char byte00C_p16, byte00D_p16;
unsigned short half00E_p16, half010_p16;
unsigned int word014_p16;
unsigned char byte018_p16, byte019_p16, byte01A_p16;
unsigned int word01C_p16, word020_p16, word024_p16;
RepairWords16_p16 words028_p16;
RepairWords16_p16 words068_p16;
unsigned char bytes0A8_p16[0x79];
unsigned char bytes121_p16[0x69];
RepairWords3_p16 words18C_p16;
unsigned char byte198_p16, byte199_p16, byte19A_p16, byte19B_p16, byte19C_p16;
unsigned char byte19D_p16, byte19E_p16, byte19F_p16, byte1A0_p16;
unsigned int word1A4_p16;
unsigned char byte1A8_p16;
unsigned int word1AC_p16;
unsigned char byte1B0_p16, byte1B1_p16;
unsigned int word1B4_p16;
unsigned char byte1B8_p16, byte1B9_p16;
RepairPackedWords_p16 words1BA_p16;
unsigned int word1D4_p16;
unsigned char byte1D8_p16, byte1D9_p16, byte1DA_p16;
};
typedef char CheckRepairPlayerSize_p16[sizeof(RepairPlayerData_p16) == 0x1DC ? 1 : -1];
struct RepairBackup_p16 {
unsigned char pad000_p16[0x64];
unsigned char captured_p16;
unsigned char pad065_p16[7];
int minute_p16;
int hour_p16;
int day_p16;
int month_p16;
int year_p16;
unsigned char pad080_p16[0x10];
RepairPlayerData_p16 player_p16;
};
extern "C"{


extern RepairPlayerData_p16 g_playerData_p16;
extern char lbl_806D2DBC_p16[8];
}
static inline RepairBackup_p16 *Repair_GetBackup_p16(ReprintPage_p16 *self_p16)
{
return *(RepairBackup_p16 **)((char *)self_p16 + 0x274);
}
extern "C"int CardRW_DataRepair_Page(ReprintPage_p16 *self_p16, int phase_p16, int arg_p16)
{
char *strings_p16 = lbl_8030E598_p16;
if (phase_p16 == 0) {
self_p16->selection_p16 = 1;
self_p16->step_p16 = 0;
self_p16->tick_p16 = 0;
self_p16->error_p16 = 1;
self_p16->failed_p16 = 0;
}
if (phase_p16 == 1) {
InputPlayer_p16 *input_p16 = InputMgr_GetPlayer_p16(GetInputManager_p16(), 0);
if (self_p16->step_p16 == 0) {
if (self_p16->error_p16 == 1 && input_p16->Pressed_p16(0x800)) {
self_p16->blink_p16 = 31;
if (++self_p16->selection_p16 > 1) self_p16->selection_p16 = 0;
}
if (input_p16->Pressed_p16(0x1000)) {
if (self_p16->selection_p16 == 0) {
if (Repair_GetBackup_p16(self_p16)->captured_p16 == 1) {
self_p16->selection_p16 = 100;
self_p16->step_p16 = 1;
self_p16->blink_p16 = 0;
self_p16->tick_p16 = lbl_803FDD38[self_p16->step_p16].tick_p16;
self_p16->error_p16 = 1;
self_p16->failed_p16 = 0;
g_playerData_p16 = Repair_GetBackup_p16(self_p16)->player_p16;
self_p16->error_p16 = Reprint_CheckError_p16();
if (self_p16->error_p16 != 1) {
self_p16->failed_p16 = 1;
self_p16->step_p16 = 6;
self_p16->blink_p16 = 31;
self_p16->tick_p16 = lbl_803FDD38[self_p16->step_p16].tick_p16;
}
} else {
self_p16->step_p16 = 100;
}
} else {
self_p16->next_p16 = 5;
CardRW_TestTopMenu_Page_p16(self_p16, 0, 6);
}
}
} else if (self_p16->step_p16 >= 100) {
if (++self_p16->step_p16 >= 280) {
self_p16->next_p16 = 5;
CardRW_TestTopMenu_Page_p16(self_p16, 0, 6);
}
} else {
if (self_p16->tick_p16 != 0) {
if (self_p16->tick_p16() == 1) {
if (!self_p16->failed_p16 && lbl_803FDD38[self_p16->step_p16].checkError_p16) {
self_p16->error_p16 = Sci2Card_GetPrintErrorCode_p16();
if (CardRW_ErrorDisplay_p16(self_p16, 0, 1, 0)) {
self_p16->step_p16 = 6;
self_p16->failed_p16 = 1;
}
}
if (self_p16->step_p16 == 2 && !Sci2Card_GetByteFlag1224_p16()) {
self_p16->step_p16 = 0;
self_p16->failed_p16 = 0;
}
++self_p16->step_p16;
self_p16->tick_p16 = lbl_803FDD38[self_p16->step_p16].tick_p16;
}
if (self_p16->failed_p16 && Reprint_HasFatalError_p16(self_p16)) self_p16->blink_p16 = 31;
} else {
unsigned char leave_p16 = 1;
if (CardRW_ErrorDisplay_p16(self_p16, 0, 1, 0) && !input_p16->Pressed_p16(0x1000)) leave_p16 = 0;
if (!Reprint_HasFatalError_p16(self_p16) || leave_p16) {
self_p16->next_p16 = 5;
CardRW_TestTopMenu_Page_p16(self_p16, 0, 6);
}
}
}
}
if (phase_p16 == 2) {
Reprint_DrawItems_p16(self_p16, (*(MenuItem_p16 (*)[])&lbl_803FCC60), self_p16->selection_p16 + 4);
if (self_p16->text_p16 != 0) {
unsigned char c_p16, b_p16, a_p16;
Sci2Card_GetResponseStatus_p16(Sci2Card_Singleton_Get_p16(), &a_p16, &b_p16, &c_p16);
DrawText_p16(self_p16->text_p16, 168, 72, 7, 1.0f, strings_p16 + 0x1c78, a_p16, b_p16, c_p16);
}
if (self_p16->text_p16 != 0) {
RepairBackup_p16 *backup_p16 = Repair_GetBackup_p16(self_p16);
if (backup_p16->captured_p16 == 1) {
DrawText_p16(self_p16->text_p16, 252, 96, 7, 1.0f, strings_p16 + 0x2148, backup_p16->year_p16,
backup_p16->month_p16 + 1, backup_p16->day_p16, backup_p16->hour_p16, backup_p16->minute_p16);
} else if (self_p16->blink_p16 <= 30) {
DrawText_p16(self_p16->text_p16, 252, 96, 7, 1.0f, lbl_806D2DBC_p16);
}
if (!CardRW_ErrorDisplay_p16(self_p16, 1, 1, 0)) {
if (self_p16->step_p16 >= 100) {
if (self_p16->blink_p16 <= 30)
DrawText_p16(self_p16->text_p16, 84, 192, 7, 1.0f, strings_p16 + 0x2164);
if (self_p16->blink_p16 <= 30)
DrawText_p16(self_p16->text_p16, 84, 240, 7, 1.0f, strings_p16 + 0x2184);
} else {
switch (self_p16->step_p16) {
case 1: case 2:
DrawText_p16(self_p16->text_p16, 84, 192, 7, 1.0f, strings_p16 + 0x21a0);
if (self_p16->blink_p16 <= 30)
DrawText_p16(self_p16->text_p16, 84, 240, 7, 1.0f, strings_p16 + 0x2038);
break;
case 3: case 4: case 5: case 6:
DrawText_p16(self_p16->text_p16, 84, 192, 7, 1.0f, strings_p16 + 0x21bc);
if (self_p16->blink_p16 <= 30)
DrawText_p16(self_p16->text_p16, 84, 240, 7, 1.0f, strings_p16 + 0x2064);
break;
case 7: case 8:
if (self_p16->error_p16 == 1)
DrawText_p16(self_p16->text_p16, 84, 192, 7, 1.0f, strings_p16 + 0x21d4);
if (self_p16->blink_p16 <= 30)
DrawText_p16(self_p16->text_p16, 84, 240, 7, 1.0f, strings_p16 + 0x1c58);
break;
}
}
}
}
}
return 1;
}

#pragma use_lmw_stmw reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardDataTransfer_UI.cpp (0x8006d308) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
#pragma cplusplus on
struct InputPlayer_p17 {
virtual void v0_p17();
virtual void v1_p17();
virtual float v2_p17();
virtual void v3_p17();
virtual float StickRight_p17();
virtual float StickLeft_p17();
virtual unsigned char Pressed_p17(int mask_p17);
virtual unsigned char Held_p17(int mask_p17);
};
struct MenuItem_p17 {
int x_p17;
int y_p17;
const char *text_p17;
};
struct TestPage_p17 {
unsigned char pad_0_p17[8];
int blink_p17;
unsigned char pad_C_p17[4];
int next_p17;
unsigned char pad_14_p17[4];
int cursor_p17;
int sub_p17;
unsigned char pad_20_p17[0x14];
int variant_p17;
unsigned char pad_38_p17[0x238];
void *text_p17;
void *data_p17;
};
extern "C"{
extern char lbl_8030E598_p17[];
void *GetInputManager_p17(void);
InputPlayer_p17 *InputMgr_GetPlayer_p17(void *, int);
void DrawText_p17(void *ctx_p17, int x_p17, int y_p17, int color_p17, float scale_p17, const char *fmt_p17, ...);
}
static inline void TestPage_DrawItems_p17(TestPage_p17 *self_p17, MenuItem_p17 *it_p17, int sel_p17)
{
int i_p17;
for (i_p17 = 0; it_p17[i_p17].text_p17 != 0; i_p17++) {
if (i_p17 != sel_p17 || self_p17->blink_p17 <= 0x1E) {
if (self_p17->text_p17 != 0) {
DrawText_p17(self_p17->text_p17, it_p17[i_p17].x_p17 * 14, it_p17[i_p17].y_p17 * 24, 7, 1.0f, it_p17[i_p17].text_p17);
}
}
}
}
extern "C"{


extern unsigned char g_playerData_p17[];
void PlayerData_ResetForFlow_p17(void);
void *Sci2Card_Singleton_Get_p17(void);
unsigned char Sci2Card_IsRetryExhausted_p17(void *card_p17);
unsigned char Sci2Card_IsStatus2Two_p17(void *card_p17);
unsigned char Sci2Card_IsStatus2Three_p17(void *card_p17);
unsigned char Sci2Card_IsStatus2Five_p17(void *card_p17);
unsigned char Sci2Card_IsStatus2A_p17(void *card_p17);
unsigned char Sci2Card_IsStatus3Five_p17(void *card_p17);
int Sci2Card_GetPrintErrorCode_p17(void);
unsigned char Sci2Card_GetByteFlag1224_p17(void);
void Sci2Card_GetResponseStatus_p17(void *card_p17, unsigned char *a_p17, unsigned char *b_p17, unsigned char *c_p17);
unsigned char CardRW_ErrorDisplay_p17(TestPage_p17 *self_p17, int a_p17, int b_p17, int c_p17);
int CardRW_TestTopMenu_Page_p17(TestPage_p17 *self_p17, int phase_p17, int arg_p17);
}
static inline unsigned char CardDataTransfer_IsError_p17(TestPage_p17 *self_p17)
{
int s_p17 = (*(int *)((char *)(self_p17) + 0x284)) ;
if (s_p17 == 1) {
return 0;
}
if (self_p17->text_p17 == 0) {
return 0;
}
if (s_p17 == 0x65) {
return 1;
}
if (s_p17 == 0x66) {
return 1;
}
if (s_p17 == 0x68) {
return 1;
}
if (s_p17 == 0x64) {
return 1;
}
if (s_p17 == 0x69) {
return 1;
}
if (s_p17 == 0x6A) {
return 1;
}
if (s_p17 == 2) {
return 1;
}
if (s_p17 == 6) {
return 1;
}
if (s_p17 == 7) {
return 1;
}
if (s_p17 == 0xFF) {
return 1;
}
return 0;
}
static inline int CardDataTransfer_Begin_p17(TestPage_p17 *self_p17, int st_p17)
{
void *card_p17;
self_p17->sub_p17 = 0x64;
(*(int *)((char *)(self_p17) + 0x2C)) = st_p17;
self_p17->blink_p17 = 0;
(*(unsigned char (**)(void))((char *)(self_p17) + 0x27C)) = lbl_803FDC98[(*(int *)((char *)(self_p17) + 0x2C)) ].fn_p17;
(*(int *)((char *)(self_p17) + 0x284)) = st_p17;
(*(unsigned char *)((char *)(self_p17) + 0x5B)) = 0;
card_p17 = Sci2Card_Singleton_Get_p17();
if (Sci2Card_IsRetryExhausted_p17(card_p17) == 1) {
st_p17 = 0x65;
} else if (Sci2Card_IsStatus2Two_p17(card_p17) == 1) {
st_p17 = 0x66;
} else if (Sci2Card_IsStatus2Three_p17(card_p17) == 1) {
st_p17 = 0x68;
} else if (Sci2Card_IsStatus2Five_p17(card_p17) == 1) {
st_p17 = 0x69;
} else if (Sci2Card_IsStatus2A_p17(card_p17) == 1) {
st_p17 = 0x6A;
} else if (Sci2Card_IsStatus3Five_p17(card_p17) == 1) {
st_p17 = 2;
}
return st_p17;
}
static inline void CardDataTransfer_DrawItems_p17(TestPage_p17 *self_p17, int sel_p17)
{
MenuItem_p17 *it_p17 = (*(MenuItem_p17 (*)[])&lbl_803FCC00);
int i_p17;
for (i_p17 = 0; it_p17[i_p17].text_p17 != 0; i_p17++) {
if (i_p17 != sel_p17 || self_p17->blink_p17 <= 0x1E) {
if (self_p17->text_p17 != 0) {
DrawText_p17(self_p17->text_p17, it_p17[i_p17].x_p17 * 14, it_p17[i_p17].y_p17 * 24, 7, 1.0f, it_p17[i_p17].text_p17);
}
}
}
}

#pragma exceptions on

extern "C"int CardDataTransfer_UI(TestPage_p17 *self_p17, int phase_p17)
{
char *pool_p17 = lbl_8030E598_p17;
InputPlayer_p17 *pl_p17;
if (phase_p17 == 0) {
self_p17->sub_p17 = 1;
(*(int *)((char *)(self_p17) + 0x2C)) = 0;
(*(unsigned char (**)(void))((char *)(self_p17) + 0x27C)) = 0;
(*(int *)((char *)(self_p17) + 0x284)) = 1;
(*(unsigned char *)((char *)(self_p17) + 0x5B)) = 0;
PlayerData_ResetForFlow_p17();
}
if (phase_p17 == 1) {
pl_p17 = InputMgr_GetPlayer_p17(GetInputManager_p17(), 0);
if ((*(int *)((char *)(self_p17) + 0x2C)) == 0) {
if ((*(int *)((char *)(self_p17) + 0x284)) == 1 && pl_p17->Pressed_p17(0x800)) {
self_p17->blink_p17 = 0x1F;
if (++self_p17->sub_p17 > 1) {
self_p17->sub_p17 = 0;
}
}
if (pl_p17->Pressed_p17(0x1000)) {
if (self_p17->sub_p17 == 0) {
int st_p17;
st_p17 = CardDataTransfer_Begin_p17(self_p17, 1);
(*(int *)((char *)(self_p17) + 0x284)) = st_p17;
if ((*(int *)((char *)(self_p17) + 0x284)) != 1) {
(*(unsigned char *)((char *)(self_p17) + 0x5B)) = 1;
self_p17->blink_p17 = 0x1F;
(*(int *)((char *)(self_p17) + 0x2C)) = 0;
}
} else {
self_p17->next_p17 = 5;
CardRW_TestTopMenu_Page_p17(self_p17, 0, 5);
}
}
} else if ((*(unsigned char (**)(void))((char *)(self_p17) + 0x27C)) != 0) {
if ((*(unsigned char (**)(void))((char *)(self_p17) + 0x27C)) () == 1) {
if ((*(unsigned char *)((char *)(self_p17) + 0x5B)) == 0 && lbl_803FDC98[(*(int *)((char *)(self_p17) + 0x2C)) ].checkError_p17) {
(*(int *)((char *)(self_p17) + 0x284)) = Sci2Card_GetPrintErrorCode_p17();
if (CardRW_ErrorDisplay_p17(self_p17, 0, 1, 1)) {
(*(int *)((char *)(self_p17) + 0x2C)) = 0x10;
(*(unsigned char *)((char *)(self_p17) + 0x5B)) = 1;
}
}
if ((*(int *)((char *)(self_p17) + 0x2C)) == 2 && !Sci2Card_GetByteFlag1224_p17()) {
(*(int *)((char *)(self_p17) + 0x2C)) = 0;
(*(unsigned char *)((char *)(self_p17) + 0x5B)) = 0;
}
if ((*(int *)((char *)(self_p17) + 0x2C)) == 4) {
if (g_playerData_p17[0x199] != 0) {
(*(int *)((char *)(self_p17) + 0x2C)) = 0x10;
(*(int *)((char *)(self_p17) + 0x284)) = 5;
(*(unsigned char *)((char *)(self_p17) + 0x5B)) = 1;
} else {
g_playerData_p17[0x199] = 1;
}
}
if ((*(int *)((char *)(self_p17) + 0x2C)) == 8) {
g_playerData_p17[0x199] = 0;
}
(*(int *)((char *)(self_p17) + 0x2C)) ++;
(*(unsigned char (**)(void))((char *)(self_p17) + 0x27C)) = lbl_803FDC98[(*(int *)((char *)(self_p17) + 0x2C)) ].fn_p17;
}
if ((*(unsigned char *)((char *)(self_p17) + 0x5B)) && CardDataTransfer_IsError_p17(self_p17)) {
self_p17->blink_p17 = 0x1F;
}
} else {
unsigned char done_p17 = 1;
if (CardRW_ErrorDisplay_p17(self_p17, 0, 1, 0) && !pl_p17->Pressed_p17(0x1000)) {
done_p17 = 0;
}
if (!CardDataTransfer_IsError_p17(self_p17) || done_p17) {
self_p17->next_p17 = 5;
CardRW_TestTopMenu_Page_p17(self_p17, 0, 5);
}
}
}
if (phase_p17 == 2) {
CardDataTransfer_DrawItems_p17(self_p17, self_p17->sub_p17 + 3);
if (self_p17->text_p17 != 0) {
unsigned char c_p17;
unsigned char b_p17;
unsigned char a_p17;
Sci2Card_GetResponseStatus_p17(Sci2Card_Singleton_Get_p17(), &a_p17, &b_p17, &c_p17);
DrawText_p17(self_p17->text_p17, 0xA8, 0x48, 7, 1.0f, pool_p17 + 0x1C78, a_p17, b_p17, c_p17);
}
if (!CardRW_ErrorDisplay_p17(self_p17, 1, 1, 1) && self_p17->text_p17 != 0) {
DrawText_p17(self_p17->text_p17, 0x2A, 0x60, 4, 1.0f, pool_p17 + 0x21F0);
DrawText_p17(self_p17->text_p17, 0x2A, 0x78, 4, 1.0f, pool_p17 + 0x2214);
DrawText_p17(self_p17->text_p17, 0x2A, 0x90, 4, 1.0f, pool_p17 + 0x2238);
switch ((*(int *)((char *)(self_p17) + 0x2C)) ) {
case 1:
case 2:
DrawText_p17(self_p17->text_p17, 0x54, 0x108, 7, 1.0f, pool_p17 + 0x225C);
if (self_p17->blink_p17 <= 0x1E) {
DrawText_p17(self_p17->text_p17, 0x54, 0x138, 7, 1.0f, pool_p17 + 0x2038);
}
break;
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
DrawText_p17(self_p17->text_p17, 0x54, 0x108, 7, 1.0f, pool_p17 + 0x204C);
if (self_p17->blink_p17 <= 0x1E) {
DrawText_p17(self_p17->text_p17, 0x54, 0x138, 7, 1.0f, pool_p17 + 0x2064);
}
break;
case 9:
case 10:
DrawText_p17(self_p17->text_p17, 0x54, 0x108, 7, 1.0f, pool_p17 + 0x207C);
if (self_p17->blink_p17 <= 0x1E) {
DrawText_p17(self_p17->text_p17, 0x54, 0x138, 7, 1.0f, pool_p17 + 0x1C58);
}
break;
case 11:
case 12:
case 13:
case 14:
case 15:
case 16:
DrawText_p17(self_p17->text_p17, 0x54, 0x108, 7, 1.0f, pool_p17 + 0x2090);
if (self_p17->blink_p17 <= 0x1E) {
DrawText_p17(self_p17->text_p17, 0x54, 0x120, 7, 1.0f, pool_p17 + 0x2064);
}
break;
case 17:
case 18:
if ((*(int *)((char *)(self_p17) + 0x284)) == 1) {
DrawText_p17(self_p17->text_p17, 0x54, 0x108, 7, 1.0f, pool_p17 + 0x2278);
}
if (self_p17->blink_p17 <= 0x1E) {
DrawText_p17(self_p17->text_p17, 0x54, 0x120, 7, 1.0f, pool_p17 + 0x1C58);
}
break;
}
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardDataCheck_UI.cpp (0x8006db90) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
#pragma cplusplus on
struct InputPlayer_p18 {
virtual void v0_p18();
virtual void v1_p18();
virtual float v2_p18();
virtual void v3_p18();
virtual float StickRight_p18();
virtual float StickLeft_p18();
virtual unsigned char Pressed_p18(int mask_p18);
virtual unsigned char Held_p18(int mask_p18);
};
struct MenuItem_p18 {
int x_p18;
int y_p18;
const char *text_p18;
};
struct TestPage_p18 {
unsigned char pad_0_p18[8];
int blink_p18;
unsigned char pad_C_p18[4];
int next_p18;
unsigned char pad_14_p18[4];
int cursor_p18;
int sub_p18;
unsigned char pad_20_p18[0x14];
int variant_p18;
unsigned char pad_38_p18[0x238];
void *text_p18;
void *data_p18;
};
extern "C"{
extern char lbl_8030E598_p18[];
void *GetInputManager_p18(void);
InputPlayer_p18 *InputMgr_GetPlayer_p18(void *, int);
void DrawText_p18(void *ctx_p18, int x_p18, int y_p18, int color_p18, float scale_p18, const char *fmt_p18, ...);
}
static inline void TestPage_DrawItems_p18(TestPage_p18 *self_p18, MenuItem_p18 *it_p18, int sel_p18)
{
int i_p18;
for (i_p18 = 0; it_p18[i_p18].text_p18 != 0; i_p18++) {
if (i_p18 != sel_p18 || self_p18->blink_p18 <= 0x1E) {
if (self_p18->text_p18 != 0) {
DrawText_p18(self_p18->text_p18, it_p18[i_p18].x_p18 * 14, it_p18[i_p18].y_p18 * 24, 7, 1.0f, it_p18[i_p18].text_p18);
}
}
}
}
struct CardCheckSettings_p18 { unsigned int words_p18[10]; };
struct CardCheckRecords_p18 { unsigned int words_p18[119]; };
struct CardCheckData_p18 {
unsigned char enabled_p18;
unsigned char reserved_p18[3];
CardCheckSettings_p18 settings_p18;
CardCheckRecords_p18 records_p18;
int count_p18;
unsigned char flag_p18;
};
static inline CardCheckData_p18 *CardCheck_PageData_p18(TestPage_p18 *self_p18)
{
return (CardCheckData_p18 *)((char *)self_p18 + 0x60);
}
static inline CardCheckData_p18 *CardCheck_BackupData_p18(TestPage_p18 *self_p18)
{
return (CardCheckData_p18 *)((char *)self_p18->data_p18 + 0x64);
}
extern "C"{


extern unsigned char g_playerData_p18[];
void fn_801D7610_p18(void *, int);
void Backup_PublishShadowCopy_Inline_p18(void);
void *Sci2Card_Singleton_Get_p18(void);
unsigned char Sci2Card_IsRetryExhausted_p18(void *card_p18);
unsigned char Sci2Card_IsStatus2Two_p18(void *card_p18);
unsigned char Sci2Card_IsStatus2Three_p18(void *card_p18);
unsigned char Sci2Card_IsStatus2Five_p18(void *card_p18);
unsigned char Sci2Card_IsStatus2A_p18(void *card_p18);
unsigned char Sci2Card_IsStatus3Five_p18(void *card_p18);
int Sci2Card_GetPrintErrorCode_p18(void);
unsigned char Sci2Card_GetByteFlag1224_p18(void);
void Sci2Card_GetResponseStatus_p18(void *card_p18, unsigned char *a_p18, unsigned char *b_p18, unsigned char *c_p18);
unsigned char CardRW_ErrorDisplay_p18(TestPage_p18 *self_p18, int a_p18, int b_p18, int c_p18);
int CardRW_TestTopMenu_Page_p18(TestPage_p18 *self_p18, int phase_p18, int arg_p18);
}
static inline unsigned char CardDataCheck_IsError_p18(TestPage_p18 *self_p18)
{
int s_p18 = (*(int *)((char *)(self_p18) + 0x284)) ;
if (s_p18 == 1) {
return 0;
}
if (self_p18->text_p18 == 0) {
return 0;
}
if (s_p18 == 0x65) {
return 1;
}
if (s_p18 == 0x66) {
return 1;
}
if (s_p18 == 0x68) {
return 1;
}
if (s_p18 == 0x64) {
return 1;
}
if (s_p18 == 0x69) {
return 1;
}
if (s_p18 == 0x6A) {
return 1;
}
if (s_p18 == 2) {
return 1;
}
if (s_p18 == 6) {
return 1;
}
if (s_p18 == 7) {
return 1;
}
if (s_p18 == 0xFF) {
return 1;
}
return 0;
}
static inline void CardDataCheck_DrawItems_p18(TestPage_p18 *self_p18)
{
int i_p18;
int sel_p18 = self_p18->sub_p18 + 3;
MenuItem_p18 *it_p18;
for (it_p18 = (*(MenuItem_p18 (*)[])&lbl_803FCBA0), i_p18 = 0; it_p18->text_p18 != 0; ++it_p18, ++i_p18) {
if (i_p18 != sel_p18 || self_p18->blink_p18 <= 0x1E) {
if (self_p18->text_p18 != 0) {
DrawText_p18(self_p18->text_p18, it_p18->x_p18 * 14, it_p18->y_p18 * 24, 7, 1.0f, it_p18->text_p18);
}
}
}
}

#pragma exceptions on

extern "C"int CardDataCheck_UI(TestPage_p18 *self_p18, int phase_p18)
{
char *pool_p18 = lbl_8030E598_p18;
InputPlayer_p18 *pl_p18;
if (phase_p18 == 0) {
self_p18->sub_p18 = 1;
(*(int *)((char *)(self_p18) + 0x2C)) = 0;
(*(unsigned char (**)(void))((char *)(self_p18) + 0x27C)) = 0;
(*(int *)((char *)(self_p18) + 0x284)) = 1;
CardCheckData_p18 *backup_p18 = CardCheck_BackupData_p18(self_p18);
CardCheckData_p18 *page_p18 = CardCheck_PageData_p18(self_p18);
page_p18->enabled_p18 = backup_p18->enabled_p18;
page_p18->settings_p18 = backup_p18->settings_p18;
page_p18->records_p18 = backup_p18->records_p18;
page_p18->count_p18 = backup_p18->count_p18;
page_p18->flag_p18 = backup_p18->flag_p18;
}
if (phase_p18 == 1) {
pl_p18 = InputMgr_GetPlayer_p18(GetInputManager_p18(), 0);
if ((*(int *)((char *)(self_p18) + 0x2C)) == 0) {
if ((*(int *)((char *)(self_p18) + 0x284)) == 1 && pl_p18->Pressed_p18(0x800)) {
self_p18->blink_p18 = 0x1F;
if (++self_p18->sub_p18 > 1) {
self_p18->sub_p18 = 0;
}
}
if (pl_p18->Pressed_p18(0x1000)) {
if (self_p18->sub_p18 == 0) {
int st_p18;
void *card_p18;
self_p18->sub_p18 = 0x64;
(*(int *)((char *)(self_p18) + 0x2C)) = 1;
self_p18->blink_p18 = 0;
(*(unsigned char (**)(void))((char *)(self_p18) + 0x27C)) = lbl_803FDC58[(*(int *)((char *)(self_p18) + 0x2C)) ].fn_p18;
(*(int *)((char *)(self_p18) + 0x284)) = 1;
fn_801D7610_p18(g_playerData_p18, 1);
st_p18 = 1;
card_p18 = Sci2Card_Singleton_Get_p18();
if (Sci2Card_IsRetryExhausted_p18(card_p18) == 1) {
st_p18 = 0x65;
} else if (Sci2Card_IsStatus2Two_p18(card_p18) == 1) {
st_p18 = 0x66;
} else if (Sci2Card_IsStatus2Three_p18(card_p18) == 1) {
st_p18 = 0x68;
} else if (Sci2Card_IsStatus2Five_p18(card_p18) == 1) {
st_p18 = 0x69;
} else if (Sci2Card_IsStatus2A_p18(card_p18) == 1) {
st_p18 = 0x6A;
} else if (Sci2Card_IsStatus3Five_p18(card_p18) == 1) {
st_p18 = 2;
}
(*(int *)((char *)(self_p18) + 0x284)) = st_p18;
if ((*(int *)((char *)(self_p18) + 0x284)) != 1) {
(*(unsigned char *)((char *)(self_p18) + 0x5B)) = 1;
self_p18->blink_p18 = 0x1F;
(*(int *)((char *)(self_p18) + 0x2C)) = 0;
}
} else {
self_p18->next_p18 = 5;
CardRW_TestTopMenu_Page_p18(self_p18, 0, 4);
}
}
} else if ((*(unsigned char (**)(void))((char *)(self_p18) + 0x27C)) != 0) {
if ((*(unsigned char (**)(void))((char *)(self_p18) + 0x27C)) () == 1) {
if (lbl_803FDC58[(*(int *)((char *)(self_p18) + 0x2C)) ].checkError_p18) {
(*(int *)((char *)(self_p18) + 0x284)) = Sci2Card_GetPrintErrorCode_p18();
}
if ((*(int *)((char *)(self_p18) + 0x2C)) == 2 && !Sci2Card_GetByteFlag1224_p18()) {
(*(int *)((char *)(self_p18) + 0x2C)) = 0;
}
(*(int *)((char *)(self_p18) + 0x2C)) ++;
(*(unsigned char (**)(void))((char *)(self_p18) + 0x27C)) = lbl_803FDC58[(*(int *)((char *)(self_p18) + 0x2C)) ].fn_p18;
}
} else {
unsigned char done_p18 = 1;
if (CardRW_ErrorDisplay_p18(self_p18, 0, 1, 0) && !pl_p18->Pressed_p18(0x1000)) {
done_p18 = 0;
}
if (!CardDataCheck_IsError_p18(self_p18) || done_p18) {
CardCheckData_p18 *backup_p18 = CardCheck_BackupData_p18(self_p18);
CardCheckData_p18 *page_p18 = CardCheck_PageData_p18(self_p18);
backup_p18->enabled_p18 = page_p18->enabled_p18;
backup_p18->settings_p18 = page_p18->settings_p18;
backup_p18->records_p18 = page_p18->records_p18;
backup_p18->count_p18 = page_p18->count_p18;
backup_p18->flag_p18 = page_p18->flag_p18;
Backup_PublishShadowCopy_Inline_p18();
self_p18->next_p18 = 5;
CardRW_TestTopMenu_Page_p18(self_p18, 0, 4);
}
}
}
if (phase_p18 == 2) {
CardDataCheck_DrawItems_p18(self_p18);
if (self_p18->text_p18 != 0) {
unsigned char c_p18;
unsigned char b_p18;
unsigned char a_p18;
Sci2Card_GetResponseStatus_p18(Sci2Card_Singleton_Get_p18(), &a_p18, &b_p18, &c_p18);
DrawText_p18(self_p18->text_p18, 0xA8, 0x48, 7, 1.0f, pool_p18 + 0x1C78, a_p18, b_p18, c_p18);
}
if (!CardRW_ErrorDisplay_p18(self_p18, 1, 1, 1) && self_p18->text_p18 != 0) {
switch ((*(int *)((char *)(self_p18) + 0x2C)) ) {
case 1:
case 2:
DrawText_p18(self_p18->text_p18, 0x54, 0xC0, 7, 1.0f, pool_p18 + 0x2290);
if (self_p18->blink_p18 <= 0x1E) {
DrawText_p18(self_p18->text_p18, 0x54, 0xF0, 7, 1.0f, pool_p18 + 0x2038);
}
break;
case 3:
case 4:
DrawText_p18(self_p18->text_p18, 0x54, 0xC0, 7, 1.0f, pool_p18 + 0x22AC);
if (self_p18->blink_p18 <= 0x1E) {
DrawText_p18(self_p18->text_p18, 0x54, 0xF0, 7, 1.0f, pool_p18 + 0x2064);
}
break;
case 5:
case 6:
if (g_playerData_p18[0x1A0]) {
DrawText_p18(self_p18->text_p18, 0x54, 0xC0, 7, 1.0f, pool_p18 + 0x22BC);
} else if (g_playerData_p18[0x199]) {
DrawText_p18(self_p18->text_p18, 0x54, 0xC0, 7, 1.0f, pool_p18 + 0x22D8);
} else {
DrawText_p18(self_p18->text_p18, 0x54, 0xC0, 7, 1.0f, pool_p18 + 0x22F8);
}
if (self_p18->blink_p18 <= 0x1E) {
DrawText_p18(self_p18->text_p18, 0x54, 0xF0, 7, 1.0f, pool_p18 + 0x1C58);
}
break;
}
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardRW_PrintTest_Page.c (0x8006e308) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

struct InputPlayer_p19 {
virtual void v0_p19();
virtual void v1_p19();
virtual float v2_p19();
virtual void v3_p19();
virtual float StickRight_p19();
virtual float StickLeft_p19();
virtual unsigned char Pressed_p19(int mask_p19);
virtual unsigned char Held_p19(int mask_p19);
};
struct MenuItem_p19 {
int x_p19;
int y_p19;
const char *text_p19;
};
struct TestPage_p19 {
unsigned char pad_0_p19[8];
int blink_p19;
unsigned char pad_C_p19[4];
int next_p19;
unsigned char pad_14_p19[4];
int cursor_p19;
int sub_p19;
unsigned char pad_20_p19[0x14];
int variant_p19;
unsigned char pad_38_p19[0x238];
void *text_p19;
void *data_p19;
};
extern "C"{
extern char lbl_8030E598_p19[];
void *GetInputManager_p19(void);
InputPlayer_p19 *InputMgr_GetPlayer_p19(void *, int);
void DrawText_p19(void *ctx_p19, int x_p19, int y_p19, int color_p19, float scale_p19, const char *fmt_p19, ...);
}
static inline void TestPage_DrawItems_p19(TestPage_p19 *self_p19, MenuItem_p19 *it_p19, int sel_p19)
{
int i_p19;
for (i_p19 = 0; it_p19[i_p19].text_p19 != 0; i_p19++) {
if (i_p19 != sel_p19 || self_p19->blink_p19 <= 0x1E) {
if (self_p19->text_p19 != 0) {
DrawText_p19(self_p19->text_p19, it_p19[i_p19].x_p19 * 14, it_p19[i_p19].y_p19 * 24, 7, 1.0f, it_p19[i_p19].text_p19);
}
}
}
}
struct PrintPage_p19 {
unsigned char pad0_p19[8];
int blink_p19;
unsigned char padC_p19[4];
int next_p19;
unsigned char pad14_p19[8];
int selection_p19;
unsigned char pad20_p19[12];
int step_p19;
unsigned char pad30_p19[0x2b];
unsigned char failed_p19;
unsigned char pad5C_p19[0x214];
void *text_p19;
unsigned char pad274_p19[8];
PrintTick_p19 tick_p19;
int field280_p19;
int error_p19;
};
extern "C"{


void CardRW_TestTopMenu_Page_p19(PrintPage_p19 *, int, int);
unsigned char CardRW_ErrorDisplay_p19(PrintPage_p19 *, int, int, int);
int Sci2Card_GetPrintErrorCode_p19();
void *Sci2Card_Singleton_Get_p19();
void Sci2Card_GetResponseStatus_p19(void *, unsigned char *, unsigned char *, unsigned char *);
unsigned char Sci2Card_IsRetryExhausted_p19(void *);
unsigned char Sci2Card_IsStatus2Two_p19(void *);
unsigned char Sci2Card_IsStatus2Three_p19(void *);
unsigned char Sci2Card_IsStatus2Five_p19(void *);
unsigned char Sci2Card_IsStatus2A_p19(void *);
unsigned char Sci2Card_IsStatus3Five_p19(void *);
}
static inline int Print_CheckError_p19()
{
int error_p19 = 1;
void *card_p19 = Sci2Card_Singleton_Get_p19();
if (Sci2Card_IsRetryExhausted_p19(card_p19) == 1) error_p19 = 101;
else if (Sci2Card_IsStatus2Two_p19(card_p19) == 1) error_p19 = 102;
else if (Sci2Card_IsStatus2Three_p19(card_p19) == 1) error_p19 = 104;
else if (Sci2Card_IsStatus2Five_p19(card_p19) == 1) error_p19 = 105;
else if (Sci2Card_IsStatus2A_p19(card_p19) == 1) error_p19 = 106;
else if (Sci2Card_IsStatus3Five_p19(card_p19) == 1) error_p19 = 2;
return error_p19;
}
static inline void Print_DrawItems_p19(PrintPage_p19 *self_p19, MenuItem_p19 *it_p19, int sel_p19)
{
int i_p19;
for (i_p19 = 0; it_p19[i_p19].text_p19 != 0; i_p19++) {
if (i_p19 != sel_p19 || self_p19->blink_p19 <= 30) {
if (self_p19->text_p19 != 0)
DrawText_p19(self_p19->text_p19, it_p19[i_p19].x_p19 * 14, it_p19[i_p19].y_p19 * 24, 7, 1.0f, it_p19[i_p19].text_p19);
}
}
}
extern "C"int CardRW_PrintTest_Page(PrintPage_p19 *self_p19, int phase_p19, int arg_p19)
{
char *strings_p19 = lbl_8030E598_p19;
if (phase_p19 == 0) {
self_p19->selection_p19 = 1;
self_p19->step_p19 = 0;
self_p19->tick_p19 = 0;
self_p19->error_p19 = 1;
}
if (phase_p19 == 1) {
if (self_p19->step_p19 == 0) {
InputPlayer_p19 *input_p19 = InputMgr_GetPlayer_p19(GetInputManager_p19(), 0);
if (self_p19->error_p19 == 1 && input_p19->Pressed_p19(0x800)) {
self_p19->blink_p19 = 31;
if (++self_p19->selection_p19 > 1) self_p19->selection_p19 = 0;
}
if (input_p19->Pressed_p19(0x1000)) {
if (self_p19->selection_p19 == 0) {
self_p19->selection_p19 = 100;
self_p19->step_p19 = 1;
self_p19->blink_p19 = 0;
self_p19->tick_p19 = lbl_803FDC18[self_p19->step_p19].tick_p19;
self_p19->error_p19 = 1;
self_p19->error_p19 = Print_CheckError_p19();
if (self_p19->error_p19 != 1) {
self_p19->failed_p19 = 1;
self_p19->blink_p19 = 31;
self_p19->step_p19 = 0;
}
} else {
self_p19->next_p19 = 5;
CardRW_TestTopMenu_Page_p19(self_p19, 0, 3);
}
}
} else {
if (self_p19->tick_p19() == 1) {
if (lbl_803FDC18[self_p19->step_p19].checkError_p19)
self_p19->error_p19 = Sci2Card_GetPrintErrorCode_p19();
if (self_p19->error_p19 != 1) self_p19->step_p19 = 0;
else {
++self_p19->step_p19;
self_p19->tick_p19 = lbl_803FDC18[self_p19->step_p19].tick_p19;
if (self_p19->tick_p19 == 0) {
self_p19->next_p19 = 5;
CardRW_TestTopMenu_Page_p19(self_p19, 0, 3);
}
}
}
}
}
if (phase_p19 == 2) {
Print_DrawItems_p19(self_p19, (*(MenuItem_p19 (*)[])&lbl_803FCB40), self_p19->selection_p19 + 3);
if (self_p19->text_p19 != 0) {
unsigned char c_p19, b_p19, a_p19;
Sci2Card_GetResponseStatus_p19(Sci2Card_Singleton_Get_p19(), &a_p19, &b_p19, &c_p19);
DrawText_p19(self_p19->text_p19, 168, 72, 7, 1.0f, strings_p19 + 0x1c78, a_p19, b_p19, c_p19);
}
if (!CardRW_ErrorDisplay_p19(self_p19, 1, 1, 0) && self_p19->text_p19 != 0) {
switch (self_p19->step_p19) {
case 1: case 2:
DrawText_p19(self_p19->text_p19, 84, 192, 7, 1.0f, strings_p19 + 0x2314);
if (self_p19->blink_p19 <= 30)
DrawText_p19(self_p19->text_p19, 84, 240, 7, 1.0f, strings_p19 + 0x2334);
break;
case 3: case 4:
DrawText_p19(self_p19->text_p19, 84, 192, 7, 1.0f, strings_p19 + 0x2104);
if (self_p19->blink_p19 <= 30)
DrawText_p19(self_p19->text_p19, 84, 240, 7, 1.0f, strings_p19 + 0x2064);
break;
case 5: case 6:
DrawText_p19(self_p19->text_p19, 84, 192, 7, 1.0f, strings_p19 + 0x2348);
if (self_p19->blink_p19 <= 30)
DrawText_p19(self_p19->text_p19, 84, 240, 7, 1.0f, strings_p19 + 0x1c58);
DrawText_p19(self_p19->text_p19, 84, 288, 7, 1.0f, strings_p19 + 0x212c);
break;
}
}
}
return 1;
}

#pragma use_lmw_stmw reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardRW_DispenseTest_Page.c (0x8006e7d0) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

struct InputPlayer_p20 {
virtual void v0_p20();
virtual void v1_p20();
virtual float v2_p20();
virtual void v3_p20();
virtual float StickRight_p20();
virtual float StickLeft_p20();
virtual unsigned char Pressed_p20(int mask_p20);
virtual unsigned char Held_p20(int mask_p20);
};
struct MenuItem_p20 {
int x_p20;
int y_p20;
const char *text_p20;
};
struct TestPage_p20 {
unsigned char pad_0_p20[8];
int blink_p20;
unsigned char pad_C_p20[4];
int next_p20;
unsigned char pad_14_p20[4];
int cursor_p20;
int sub_p20;
unsigned char pad_20_p20[0x14];
int variant_p20;
unsigned char pad_38_p20[0x238];
void *text_p20;
void *data_p20;
};
extern "C"{
extern char lbl_8030E598_p20[];
void *GetInputManager_p20(void);
InputPlayer_p20 *InputMgr_GetPlayer_p20(void *, int);
void DrawText_p20(void *ctx_p20, int x_p20, int y_p20, int color_p20, float scale_p20, const char *fmt_p20, ...);
}
static inline void TestPage_DrawItems_p20(TestPage_p20 *self_p20, MenuItem_p20 *it_p20, int sel_p20)
{
int i_p20;
for (i_p20 = 0; it_p20[i_p20].text_p20 != 0; i_p20++) {
if (i_p20 != sel_p20 || self_p20->blink_p20 <= 0x1E) {
if (self_p20->text_p20 != 0) {
DrawText_p20(self_p20->text_p20, it_p20[i_p20].x_p20 * 14, it_p20[i_p20].y_p20 * 24, 7, 1.0f, it_p20[i_p20].text_p20);
}
}
}
}
struct DispensePage_p20 {
unsigned char pad0_p20[8];
int blink_p20;
unsigned char padC_p20[4];
int next_p20;
unsigned char pad14_p20[8];
int selection_p20;
unsigned char pad20_p20[12];
int step_p20;
unsigned char pad30_p20[0x2b];
unsigned char failed_p20;
unsigned char pad5C_p20[0x214];
void *text_p20;
unsigned char pad274_p20[8];
DispenseTick_p20 tick_p20;
int field280_p20;
int error_p20;
};
extern "C"{


void CardRW_TestTopMenu_Page_p20(DispensePage_p20 *, int, int);
unsigned char CardRW_ErrorDisplay_p20(DispensePage_p20 *, int, int, int);
int Sci2Card_GetPrintErrorCode_p20();
void *Sci2Card_Singleton_Get_p20();
void Sci2Card_GetResponseStatus_p20(void *, unsigned char *, unsigned char *, unsigned char *);
unsigned char Sci2Card_IsRetryExhausted_p20(void *);
unsigned char Sci2Card_IsStatus2Two_p20(void *);
unsigned char Sci2Card_IsStatus2Three_p20(void *);
unsigned char Sci2Card_IsStatus2Five_p20(void *);
unsigned char Sci2Card_IsStatus2A_p20(void *);
unsigned char Sci2Card_IsStatus3Five_p20(void *);
}
static inline int Dispense_CheckError_p20()
{
int error_p20 = 1;
void *card_p20 = Sci2Card_Singleton_Get_p20();
if (Sci2Card_IsRetryExhausted_p20(card_p20) == 1) error_p20 = 101;
else if (Sci2Card_IsStatus2Two_p20(card_p20) == 1) error_p20 = 102;
else if (Sci2Card_IsStatus2Three_p20(card_p20) == 1) error_p20 = 104;
else if (Sci2Card_IsStatus2Five_p20(card_p20) == 1) error_p20 = 105;
else if (Sci2Card_IsStatus2A_p20(card_p20) == 1) error_p20 = 106;
else if (Sci2Card_IsStatus3Five_p20(card_p20) == 1) error_p20 = 2;
return error_p20;
}
static inline void Dispense_DrawItems_p20(DispensePage_p20 *self_p20, MenuItem_p20 *it_p20, int sel_p20)
{
int i_p20;
for (i_p20 = 0; it_p20[i_p20].text_p20 != 0; i_p20++) {
if (i_p20 != sel_p20 || self_p20->blink_p20 <= 30) {
if (self_p20->text_p20 != 0)
DrawText_p20(self_p20->text_p20, it_p20[i_p20].x_p20 * 14, it_p20[i_p20].y_p20 * 24, 7, 1.0f, it_p20[i_p20].text_p20);
}
}
}
extern "C"int CardRW_DispenseTest_Page(DispensePage_p20 *self_p20, int phase_p20, int arg_p20)
{
char *strings_p20 = lbl_8030E598_p20;
if (phase_p20 == 0) {
self_p20->selection_p20 = 1;
self_p20->step_p20 = 0;
self_p20->tick_p20 = 0;
self_p20->error_p20 = 1;
}
if (phase_p20 == 1) {
if (self_p20->step_p20 == 0) {
InputPlayer_p20 *input_p20 = InputMgr_GetPlayer_p20(GetInputManager_p20(), 0);
if (self_p20->error_p20 == 1 && input_p20->Pressed_p20(0x800)) {
self_p20->blink_p20 = 31;
if (++self_p20->selection_p20 > 1) self_p20->selection_p20 = 0;
}
if (input_p20->Pressed_p20(0x1000)) {
if (self_p20->selection_p20 == 0) {
self_p20->selection_p20 = 100;
self_p20->step_p20 = 1;
self_p20->blink_p20 = 0;
self_p20->tick_p20 = lbl_803FDBE8[self_p20->step_p20].tick_p20;
self_p20->error_p20 = 1;
self_p20->error_p20 = Dispense_CheckError_p20();
if (self_p20->error_p20 != 1) {
self_p20->failed_p20 = 1;
self_p20->blink_p20 = 31;
self_p20->step_p20 = 0;
}
} else {
self_p20->next_p20 = 5;
CardRW_TestTopMenu_Page_p20(self_p20, 0, 2);
}
}
} else {
if (self_p20->tick_p20() == 1) {
if (lbl_803FDBE8[self_p20->step_p20].checkError_p20)
self_p20->error_p20 = Sci2Card_GetPrintErrorCode_p20();
if (self_p20->error_p20 != 1) self_p20->step_p20 = 0;
else {
++self_p20->step_p20;
self_p20->tick_p20 = lbl_803FDBE8[self_p20->step_p20].tick_p20;
if (self_p20->tick_p20 == 0) {
self_p20->next_p20 = 5;
CardRW_TestTopMenu_Page_p20(self_p20, 0, 2);
}
}
}
}
}
if (phase_p20 == 2) {
Dispense_DrawItems_p20(self_p20, (*(MenuItem_p20 (*)[])&lbl_803FCAE0), self_p20->selection_p20 + 3);
if (self_p20->text_p20 != 0) {
unsigned char c_p20, b_p20, a_p20;
Sci2Card_GetResponseStatus_p20(Sci2Card_Singleton_Get_p20(), &a_p20, &b_p20, &c_p20);
DrawText_p20(self_p20->text_p20, 168, 72, 7, 1.0f, strings_p20 + 0x1c78, a_p20, b_p20, c_p20);
}
if (!CardRW_ErrorDisplay_p20(self_p20, 1, 1, 0) && self_p20->text_p20 != 0) {
switch (self_p20->step_p20) {
case 1: case 2:
DrawText_p20(self_p20->text_p20, 84, 192, 7, 1.0f, strings_p20 + 0x2360);
if (self_p20->blink_p20 <= 30)
DrawText_p20(self_p20->text_p20, 84, 240, 7, 1.0f, strings_p20 + 0x2334);
break;
case 3: case 4:
DrawText_p20(self_p20->text_p20, 84, 192, 7, 1.0f, strings_p20 + 0x2380);
if (self_p20->blink_p20 <= 30)
DrawText_p20(self_p20->text_p20, 84, 240, 7, 1.0f, strings_p20 + 0x1c58);
break;
}
}
}
return 1;
}

#pragma use_lmw_stmw reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardRW_ReadWriteTest_Page.c (0x8006ec24) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

struct InputPlayer_p21 {
virtual void v0_p21();
virtual void v1_p21();
virtual float v2_p21();
virtual void v3_p21();
virtual float StickRight_p21();
virtual float StickLeft_p21();
virtual unsigned char Pressed_p21(int mask_p21);
virtual unsigned char Held_p21(int mask_p21);
};
struct MenuItem_p21 {
int x_p21;
int y_p21;
const char *text_p21;
};
struct TestPage_p21 {
unsigned char pad_0_p21[8];
int blink_p21;
unsigned char pad_C_p21[4];
int next_p21;
unsigned char pad_14_p21[4];
int cursor_p21;
int sub_p21;
unsigned char pad_20_p21[0x14];
int variant_p21;
unsigned char pad_38_p21[0x238];
void *text_p21;
void *data_p21;
};
extern "C"{
extern char lbl_8030E598_p21[];
void *GetInputManager_p21(void);
InputPlayer_p21 *InputMgr_GetPlayer_p21(void *, int);
void DrawText_p21(void *ctx_p21, int x_p21, int y_p21, int color_p21, float scale_p21, const char *fmt_p21, ...);
}
static inline void TestPage_DrawItems_p21(TestPage_p21 *self_p21, MenuItem_p21 *it_p21, int sel_p21)
{
int i_p21;
for (i_p21 = 0; it_p21[i_p21].text_p21 != 0; i_p21++) {
if (i_p21 != sel_p21 || self_p21->blink_p21 <= 0x1E) {
if (self_p21->text_p21 != 0) {
DrawText_p21(self_p21->text_p21, it_p21[i_p21].x_p21 * 14, it_p21[i_p21].y_p21 * 24, 7, 1.0f, it_p21[i_p21].text_p21);
}
}
}
}
struct CardCheckSettings_p21 { unsigned int words_p21[10]; };
struct CardCheckRecords_p21 { unsigned int words_p21[119]; };
struct CardCheckData_p21 {
unsigned char enabled_p21;
unsigned char reserved_p21[3];
CardCheckSettings_p21 settings_p21;
CardCheckRecords_p21 records_p21;
int count_p21;
unsigned char flag_p21;
};
struct CardCheckStep_p21 {
unsigned char (*fn_p21)(void);
unsigned char checkError_p21;
};
static inline CardCheckData_p21 *CardCheck_PageData_p21(TestPage_p21 *self_p21)
{
return (CardCheckData_p21 *)((char *)self_p21 + 0x60);
}
static inline CardCheckData_p21 *CardCheck_BackupData_p21(TestPage_p21 *self_p21)
{
return (CardCheckData_p21 *)((char *)self_p21->data_p21 + 0x64);
}
struct ReadWritePage_p21 {
unsigned char pad0_p21[8];
int blink_p21;
unsigned char padC_p21[4];
int next_p21;
unsigned char pad14_p21[8];
int selection_p21;
unsigned char pad20_p21[12];
int step_p21;
unsigned char pad30_p21[0x2b];
unsigned char failed_p21;
unsigned char pad5C_p21[4];
CardCheckData_p21 cardData_p21;
void *text_p21;
void *data_p21;
int field278_p21;
ReadWriteTick_p21 tick_p21;
int field280_p21;
int error_p21;
};
extern "C"{


void Backup_PublishShadowCopy_Inline_p21();
void CardRW_TestTopMenu_Page_p21(ReadWritePage_p21 *, int, int);
unsigned char CardRW_ErrorDisplay_p21(ReadWritePage_p21 *, int, int, int);
int Sci2Card_GetPrintErrorCode_p21();
void *Sci2Card_Singleton_Get_p21();
void Sci2Card_GetResponseStatus_p21(void *, unsigned char *, unsigned char *, unsigned char *);
unsigned char Sci2Card_IsRetryExhausted_p21(void *);
unsigned char Sci2Card_IsStatus2Two_p21(void *);
unsigned char Sci2Card_IsStatus2Three_p21(void *);
unsigned char Sci2Card_IsStatus2Five_p21(void *);
unsigned char Sci2Card_IsStatus2A_p21(void *);
unsigned char Sci2Card_IsStatus3Five_p21(void *);
}
static inline int ReadWrite_CheckError_p21()
{
int error_p21 = 1;
void *card_p21 = Sci2Card_Singleton_Get_p21();
if (Sci2Card_IsRetryExhausted_p21(card_p21) == 1) error_p21 = 101;
else if (Sci2Card_IsStatus2Two_p21(card_p21) == 1) error_p21 = 102;
else if (Sci2Card_IsStatus2Three_p21(card_p21) == 1) error_p21 = 104;
else if (Sci2Card_IsStatus2Five_p21(card_p21) == 1) error_p21 = 105;
else if (Sci2Card_IsStatus2A_p21(card_p21) == 1) error_p21 = 106;
else if (Sci2Card_IsStatus3Five_p21(card_p21) == 1) error_p21 = 2;
return error_p21;
}
static inline void ReadWrite_DrawItems_p21(ReadWritePage_p21 *self_p21, MenuItem_p21 *it_p21, int sel_p21)
{
int i_p21;
for (i_p21 = 0; it_p21[i_p21].text_p21 != 0; i_p21++) {
if (i_p21 != sel_p21 || self_p21->blink_p21 <= 30) {
if (self_p21->text_p21 != 0)
DrawText_p21(self_p21->text_p21, it_p21[i_p21].x_p21 * 14, it_p21[i_p21].y_p21 * 24, 7, 1.0f, it_p21[i_p21].text_p21);
}
}
}
extern "C"int CardRW_ReadWriteTest_Page(ReadWritePage_p21 *self_p21, int phase_p21, int arg_p21)
{
char *strings_p21 = lbl_8030E598_p21;
if (phase_p21 == 0) {
self_p21->selection_p21 = 1;
self_p21->step_p21 = 0;
self_p21->tick_p21 = 0;
self_p21->error_p21 = 1;
CardCheckData_p21 *backup_p21 = (CardCheckData_p21 *)((char *)self_p21->data_p21 + 0x64);
CardCheckData_p21 *page_p21 = &self_p21->cardData_p21;
page_p21->enabled_p21 = backup_p21->enabled_p21;
page_p21->settings_p21 = backup_p21->settings_p21;
page_p21->records_p21 = backup_p21->records_p21;
page_p21->count_p21 = backup_p21->count_p21;
page_p21->flag_p21 = backup_p21->flag_p21;
}
if (phase_p21 == 1) {
if (self_p21->step_p21 == 0) {
InputPlayer_p21 *input_p21 = InputMgr_GetPlayer_p21(GetInputManager_p21(), 0);
if (self_p21->error_p21 == 1 && input_p21->Pressed_p21(0x800)) {
self_p21->blink_p21 = 31;
if (++self_p21->selection_p21 > 1) self_p21->selection_p21 = 0;
}
if (input_p21->Pressed_p21(0x1000)) {
if (self_p21->selection_p21 == 0) {
self_p21->selection_p21 = 100;
self_p21->step_p21 = 1;
self_p21->blink_p21 = 0;
self_p21->tick_p21 = lbl_803FDB98[self_p21->step_p21].tick_p21;
self_p21->error_p21 = 1;
self_p21->error_p21 = ReadWrite_CheckError_p21();
if (self_p21->error_p21 != 1) {
self_p21->failed_p21 = 1;
self_p21->blink_p21 = 31;
self_p21->step_p21 = 0;
}
} else {
self_p21->next_p21 = 5;
CardRW_TestTopMenu_Page_p21(self_p21, 0, 1);
}
}
} else {
if (self_p21->tick_p21() == 1) {
if (lbl_803FDB98[self_p21->step_p21].checkError_p21)
self_p21->error_p21 = Sci2Card_GetPrintErrorCode_p21();
if (self_p21->error_p21 != 1) self_p21->step_p21 = 0;
else {
++self_p21->step_p21;
self_p21->tick_p21 = lbl_803FDB98[self_p21->step_p21].tick_p21;
if (self_p21->tick_p21 == 0) {
CardCheckData_p21 *backup_p21 = (CardCheckData_p21 *)((char *)self_p21->data_p21 + 0x64);
CardCheckData_p21 *page_p21 = &self_p21->cardData_p21;
backup_p21->enabled_p21 = page_p21->enabled_p21;
backup_p21->settings_p21 = page_p21->settings_p21;
backup_p21->records_p21 = page_p21->records_p21;
backup_p21->count_p21 = page_p21->count_p21;
backup_p21->flag_p21 = page_p21->flag_p21;
Backup_PublishShadowCopy_Inline_p21();
self_p21->next_p21 = 5;
CardRW_TestTopMenu_Page_p21(self_p21, 0, 1);
}
}
}
}
}
if (phase_p21 == 2) {
ReadWrite_DrawItems_p21(self_p21, (*(MenuItem_p21 (*)[])&lbl_803FCA80), self_p21->selection_p21 + 3);
if (self_p21->text_p21 != 0) {
unsigned char c_p21, b_p21, a_p21;
Sci2Card_GetResponseStatus_p21(Sci2Card_Singleton_Get_p21(), &a_p21, &b_p21, &c_p21);
DrawText_p21(self_p21->text_p21, 168, 72, 7, 1.0f, strings_p21 + 0x1c78, a_p21, b_p21, c_p21);
}
if (!CardRW_ErrorDisplay_p21(self_p21, 1, 1, 0) && self_p21->text_p21 != 0) {
switch (self_p21->step_p21) {
case 1: case 2:
DrawText_p21(self_p21->text_p21, 84, 192, 7, 1.0f, strings_p21 + 0x23a0);
if (self_p21->blink_p21 <= 30)
DrawText_p21(self_p21->text_p21, 84, 240, 7, 1.0f, strings_p21 + 0x2334);
break;
case 3: case 4: case 5: case 6:
DrawText_p21(self_p21->text_p21, 84, 192, 7, 1.0f, strings_p21 + 0x23c0);
if (self_p21->blink_p21 <= 30)
DrawText_p21(self_p21->text_p21, 84, 240, 7, 1.0f, strings_p21 + 0x2064);
break;
case 7: case 8:
DrawText_p21(self_p21->text_p21, 84, 192, 7, 1.0f, strings_p21 + 0x23e0);
if (self_p21->blink_p21 <= 30)
DrawText_p21(self_p21->text_p21, 84, 240, 7, 1.0f, strings_p21 + 0x1c58);
break;
}
}
}
return 1;
}

#pragma use_lmw_stmw reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardRW_CleaningTest_Page.c (0x8006f200) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on


#pragma use_lmw_stmw on

struct InputPlayer_p22 {
virtual void v0_p22();
virtual void v1_p22();
virtual float v2_p22();
virtual void v3_p22();
virtual float StickRight_p22();
virtual float StickLeft_p22();
virtual unsigned char Pressed_p22(int mask_p22);
virtual unsigned char Held_p22(int mask_p22);
};
struct MenuItem_p22 {
int x_p22;
int y_p22;
const char *text_p22;
};
struct TestPage_p22 {
unsigned char pad_0_p22[8];
int blink_p22;
unsigned char pad_C_p22[4];
int next_p22;
unsigned char pad_14_p22[4];
int cursor_p22;
int sub_p22;
unsigned char pad_20_p22[0x14];
int variant_p22;
unsigned char pad_38_p22[0x238];
void *text_p22;
void *data_p22;
};
extern "C"{
extern char lbl_8030E598_p22[];
void *GetInputManager_p22(void);
InputPlayer_p22 *InputMgr_GetPlayer_p22(void *, int);
void DrawText_p22(void *ctx_p22, int x_p22, int y_p22, int color_p22, float scale_p22, const char *fmt_p22, ...);
}
static inline void TestPage_DrawItems_p22(TestPage_p22 *self_p22, MenuItem_p22 *it_p22, int sel_p22)
{
int i_p22;
for (i_p22 = 0; it_p22[i_p22].text_p22 != 0; i_p22++) {
if (i_p22 != sel_p22 || self_p22->blink_p22 <= 0x1E) {
if (self_p22->text_p22 != 0) {
DrawText_p22(self_p22->text_p22, it_p22[i_p22].x_p22 * 14, it_p22[i_p22].y_p22 * 24, 7, 1.0f, it_p22[i_p22].text_p22);
}
}
}
}
struct CleaningPage_p22 {
unsigned char pad0_p22[8];
int blink_p22;
unsigned char padC_p22[4];
int next_p22;
unsigned char pad14_p22[8];
int selection_p22;
unsigned char pad20_p22[12];
int step_p22;
unsigned char pad30_p22[0x240];
void *text_p22;
unsigned char pad274_p22[8];
CleaningTick_p22 tick_p22;
int field280_p22;
int error_p22;
};
extern "C"{


void Backup_PublishShadowCopy_p22();
void Backup_PublishShadowCopy_Inline_p22();
void CardRW_TestTopMenu_Page_p22(CleaningPage_p22 *, int, int);
unsigned char CardRW_ErrorDisplay_p22(CleaningPage_p22 *, int, int, int);
int Sci2Card_GetPrintErrorCode_p22();
void *Sci2Card_Singleton_Get_p22();
void Sci2Card_GetResponseStatus_p22(void *, unsigned char *, unsigned char *, unsigned char *);
}
static inline void Cleaning_DrawItems_p22(CleaningPage_p22 *self_p22, MenuItem_p22 *it_p22, int sel_p22)
{
int i_p22;
for (i_p22 = 0; it_p22[i_p22].text_p22 != 0; i_p22++) {
if (i_p22 != sel_p22 || self_p22->blink_p22 <= 30) {
if (self_p22->text_p22 != 0)
DrawText_p22(self_p22->text_p22, it_p22[i_p22].x_p22 * 14, it_p22[i_p22].y_p22 * 24, 7, 1.0f, it_p22[i_p22].text_p22);
}
}
}
extern "C"int CardRW_CleaningTest_Page(CleaningPage_p22 *self_p22, int phase_p22, int arg_p22)
{
char *strings_p22 = lbl_8030E598_p22;
if (phase_p22 == 0) {
self_p22->selection_p22 = 1;
self_p22->step_p22 = 0;
self_p22->tick_p22 = 0;
self_p22->error_p22 = 1;
}
if (phase_p22 == 1) {
if (self_p22->step_p22 == 0) {
InputPlayer_p22 *input_p22 = InputMgr_GetPlayer_p22(GetInputManager_p22(), 0);
if (self_p22->error_p22 == 1 && input_p22->Pressed_p22(0x800)) {
self_p22->blink_p22 = 31;
if (++self_p22->selection_p22 > 1) self_p22->selection_p22 = 0;
}
if (input_p22->Pressed_p22(0x1000)) {
if (self_p22->selection_p22 == 0) {
self_p22->selection_p22 = 100;
self_p22->step_p22 = 1;
self_p22->blink_p22 = 0;
self_p22->tick_p22 = lbl_803FDB58[self_p22->step_p22].tick_p22;
self_p22->error_p22 = 1;
} else {
self_p22->next_p22 = 5;
CardRW_TestTopMenu_Page_p22(self_p22, 0, 0);
}
}
} else {
if (self_p22->tick_p22() == 1) {
if (lbl_803FDB58[self_p22->step_p22].checkError_p22)
self_p22->error_p22 = Sci2Card_GetPrintErrorCode_p22();
if (self_p22->step_p22 == 2 && self_p22->error_p22 == 6) {
self_p22->step_p22 = 0;
self_p22->error_p22 = 1;
}
if (self_p22->error_p22 != 1) self_p22->step_p22 = 0;
else {
++self_p22->step_p22;
self_p22->tick_p22 = lbl_803FDB58[self_p22->step_p22].tick_p22;
if (self_p22->tick_p22 == 0) {
Backup_PublishShadowCopy_p22();
Backup_PublishShadowCopy_Inline_p22();
self_p22->next_p22 = 5;
CardRW_TestTopMenu_Page_p22(self_p22, 0, 0);
}
}
}
}
}
if (phase_p22 == 2) {
Cleaning_DrawItems_p22(self_p22, (*(MenuItem_p22 (*)[])&lbl_803FCA20), self_p22->selection_p22 + 3);
if (self_p22->text_p22 != 0) {
unsigned char c_p22, b_p22, a_p22;
Sci2Card_GetResponseStatus_p22(Sci2Card_Singleton_Get_p22(), &a_p22, &b_p22, &c_p22);
DrawText_p22(self_p22->text_p22, 168, 72, 7, 1.0f, strings_p22 + 0x1c78, a_p22, b_p22, c_p22);
}
if (!CardRW_ErrorDisplay_p22(self_p22, 1, 1, 0) && self_p22->text_p22 != 0) {
switch (self_p22->step_p22) {
case 1: case 2:
DrawText_p22(self_p22->text_p22, 84, 192, 7, 1.0f, strings_p22 + 0x23fc);
if (self_p22->blink_p22 <= 30)
DrawText_p22(self_p22->text_p22, 84, 240, 7, 1.0f, strings_p22 + 0x2418);
break;
case 3: case 4:
DrawText_p22(self_p22->text_p22, 84, 192, 7, 1.0f, strings_p22 + 0x2434);
if (self_p22->blink_p22 <= 30)
DrawText_p22(self_p22->text_p22, 84, 240, 7, 1.0f, strings_p22 + 0x2064);
break;
case 5: case 6:
DrawText_p22(self_p22->text_p22, 84, 192, 7, 1.0f, strings_p22 + 0x2444);
if (self_p22->blink_p22 <= 30)
DrawText_p22(self_p22->text_p22, 84, 240, 7, 1.0f, strings_p22 + 0x2458);
break;
}
}
}
return 1;
}

#pragma use_lmw_stmw reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CardRW_TestTopMenu_Page.c (0x8006f608) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus off
#pragma cplusplus on

struct InputPlayer_p23 {
virtual void v0_p23();
virtual void v1_p23();
virtual float v2_p23();
virtual void v3_p23();
virtual float StickRight_p23();
virtual float StickLeft_p23();
virtual unsigned char Pressed_p23(int mask_p23);
virtual unsigned char Held_p23(int mask_p23);
};
struct MenuItem_p23 {
int x_p23;
int y_p23;
const char *text_p23;
};
struct TestPage_p23 {
unsigned char pad_0_p23[8];
int blink_p23;
unsigned char pad_C_p23[4];
int next_p23;
unsigned char pad_14_p23[4];
int cursor_p23;
int sub_p23;
unsigned char pad_20_p23[0x14];
int variant_p23;
unsigned char pad_38_p23[0x238];
void *text_p23;
void *data_p23;
};
extern "C"{
extern char lbl_8030E598_p23[];
void *GetInputManager_p23(void);
InputPlayer_p23 *InputMgr_GetPlayer_p23(void *, int);
void DrawText_p23(void *ctx_p23, int x_p23, int y_p23, int color_p23, float scale_p23, const char *fmt_p23, ...);
}
static inline void TestPage_DrawItems_p23(TestPage_p23 *self_p23, MenuItem_p23 *it_p23, int sel_p23)
{
int i_p23;
for (i_p23 = 0; it_p23[i_p23].text_p23 != 0; i_p23++) {
if (i_p23 != sel_p23 || self_p23->blink_p23 <= 0x1E) {
if (self_p23->text_p23 != 0) {
DrawText_p23(self_p23->text_p23, it_p23[i_p23].x_p23 * 14, it_p23[i_p23].y_p23 * 24, 7, 1.0f, it_p23[i_p23].text_p23);
}
}
}
}
typedef unsigned char (*CardRWStepFn_p23)(void);
struct CardRWStep_p23 {
CardRWStepFn_p23 run_p23;
const char *name_p23;
};
struct CardRWTestPage_p23 {
char pad_00_p23[8];
int blink_p23;
int timer_p23;
int next_p23;
int field_14_p23;
int cursor_p23;
char pad_1C_p23[0x10];
int field_2C_p23;
char pad_30_p23[8];
int state_p23;
char pad_3C_p23[0x234];
void *text_p23;
void *data_p23;
int field_278_p23;
CardRWStepFn_p23 step_p23;
int field_280_p23;
int error_p23;
};
extern "C"{
extern int lbl_806D1108_p23;
extern const float lbl_806D2D44_p23;
extern const char lbl_80310118_p23[], lbl_80310A0C_p23[];


void CardPrintJob_KickFontTransfer_p23(void);
unsigned char CardPrintJob_TickFontTransfer_p23(void);
int Sci2Card_GetPrintErrorCode_p23(void);
unsigned char Sci2Card_BeginSpace_p23(void);
unsigned char Sci2Card_WaitPingStatus_p23(void);
unsigned char Sci2Card_GetByteFlag1224_p23(void);
void CardRW_ErrorDisplay_p23(CardRWTestPage_p23 *, int, int, int);
void UI_PageDispatcher_p23(CardRWTestPage_p23 *, int, int);
int CardRW_TestTopMenu_Page(CardRWTestPage_p23 *self_p23, int phase_p23, int arg_p23)
{
if (phase_p23 == 0) {
self_p23->step_p23 = 0;
self_p23->error_p23 = 1;
if (arg_p23 == -1) self_p23->cursor_p23 = 9;
else self_p23->cursor_p23 = arg_p23;
if (lbl_806D1108_p23 == 0) CardPrintJob_KickFontTransfer_p23();
}
if (phase_p23 == 1) {
InputPlayer_p23 *input_p23 = InputMgr_GetPlayer_p23(GetInputManager_p23(), 0);
if (self_p23->error_p23 != 1) {
if (input_p23->Pressed_p23(0x1000)) self_p23->next_p23 = 0;
return 1;
}
if (lbl_806D1108_p23 == 0) {
if (!CardPrintJob_TickFontTransfer_p23()) return 1;
self_p23->error_p23 = Sci2Card_GetPrintErrorCode_p23();
if (self_p23->error_p23 != 1) self_p23->state_p23 = -2;
else if (self_p23->state_p23 == -2) {
if (!Sci2Card_BeginSpace_p23()) self_p23->state_p23 = -1;
else self_p23->state_p23 = 0;
}
if (self_p23->error_p23 != 101) {
lbl_806D1108_p23 = 1;
self_p23->error_p23 = 1;
}
return 1;
}
if (self_p23->state_p23 == -1) {
if (Sci2Card_BeginSpace_p23() == 1) self_p23->state_p23 = 0;
return 1;
}
if (self_p23->state_p23 == 0) {
if (!Sci2Card_WaitPingStatus_p23()) return 1;
if (Sci2Card_GetPrintErrorCode_p23() != 1) {
self_p23->state_p23 = -2;
return 1;
}
if (!Sci2Card_GetByteFlag1224_p23()) self_p23->state_p23 = -2;
else {
self_p23->state_p23 = 5;
self_p23->step_p23 = (*(CardRWStep_p23 (*)[])&lbl_803FDB18)[self_p23->state_p23].run_p23;
}
return 1;
}
if (self_p23->state_p23 >= 1) {
if (self_p23->step_p23() == 1) {
++self_p23->state_p23;
self_p23->step_p23 = (*(CardRWStep_p23 (*)[])&lbl_803FDB18)[self_p23->state_p23].run_p23;
if (self_p23->step_p23 == 0) self_p23->state_p23 = -2;
}
return 1;
}
if (input_p23->Pressed_p23(0x800)) {
self_p23->blink_p23 = 31;
if (++self_p23->cursor_p23 > 9) self_p23->cursor_p23 = 0;
}
if (input_p23->Pressed_p23(0x1000)) {
if (self_p23->cursor_p23 == 9) self_p23->next_p23 = 0;
else {
self_p23->field_2C_p23 = 0;
int selected_p23 = self_p23->cursor_p23;
self_p23->next_p23 = selected_p23 + 15;
UI_PageDispatcher_p23(self_p23, 0, selected_p23);
}
}
}
if (phase_p23 == 2) {
if (self_p23->error_p23 != 1) {
int blink_p23 = self_p23->blink_p23;
self_p23->blink_p23 = 31;
CardRW_ErrorDisplay_p23(self_p23, 1, 1, 0);
self_p23->blink_p23 = blink_p23;
if (self_p23->blink_p23 <= 30)
DrawText_p23(self_p23->text_p23, 84, 264, 7, lbl_806D2D44_p23, lbl_80310118_p23);
} else if (lbl_806D1108_p23 == 0) {
if (self_p23->blink_p23 <= 30)
DrawText_p23(self_p23->text_p23, 154, 216, 7, lbl_806D2D44_p23, lbl_80310A0C_p23);
} else {
TestPage_DrawItems_p23((TestPage_p23 *)self_p23, (*(MenuItem_p23 (*)[])&lbl_803FC8B8), self_p23->cursor_p23 + 1);
}
}
return 1;
}
}
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/SpeakerTest_Page.cpp (0x8006fa1c) ==== */
#pragma exceptions on
#pragma use_lmw_stmw on
#pragma cplusplus on
struct InputPlayer_p24 {
virtual void v0_p24();
virtual void v1_p24();
virtual float v2_p24();
virtual void v3_p24();
virtual float StickRight_p24();
virtual float StickLeft_p24();
virtual unsigned char Pressed_p24(int mask_p24);
virtual unsigned char Held_p24(int mask_p24);
};
struct MenuItem_p24 {
int x_p24;
int y_p24;
const char *text_p24;
};
struct TestPage_p24 {
unsigned char pad_0_p24[8];
int blink_p24;
unsigned char pad_C_p24[4];
int next_p24;
unsigned char pad_14_p24[4];
int cursor_p24;
int sub_p24;
unsigned char pad_20_p24[0x14];
int variant_p24;
unsigned char pad_38_p24[0x238];
void *text_p24;
void *data_p24;
};
extern "C"{
extern char lbl_8030E598_p24[];
void *GetInputManager_p24(void);
InputPlayer_p24 *InputMgr_GetPlayer_p24(void *, int);
void DrawText_p24(void *ctx_p24, int x_p24, int y_p24, int color_p24, float scale_p24, const char *fmt_p24, ...);
}
static inline void TestPage_DrawItems_p24(TestPage_p24 *self_p24, MenuItem_p24 *it_p24, int sel_p24)
{
int i_p24;
for (i_p24 = 0; it_p24[i_p24].text_p24 != 0; i_p24++) {
if (i_p24 != sel_p24 || self_p24->blink_p24 <= 0x1E) {
if (self_p24->text_p24 != 0) {
DrawText_p24(self_p24->text_p24, it_p24[i_p24].x_p24 * 14, it_p24[i_p24].y_p24 * 24, 7, 1.0f, it_p24[i_p24].text_p24);
}
}
}
}
extern "C"{

extern const char lbl_806D2DA4_p24[6];
extern const char lbl_806D2DC4_p24[7];
extern const char lbl_806D2DCC_p24[3];
extern const char lbl_806D2DD0_p24[8];
extern const char lbl_806D2DD8_p24[8];
extern const char lbl_806D2DE0_p24[8];
extern const char lbl_806D2DE8_p24[6];
extern const char lbl_806D2DF0_p24[5];
void Backup_PublishShadowCopy_Inline_p24(void);
void fn_801934A0_p24(unsigned char vol_p24);
void fn_8019345C_p24(unsigned char vol_p24);
void fn_80193404_p24(unsigned char vol_p24);
void fn_801951E4_p24(unsigned char v_p24);
void fn_801951CC_p24(unsigned char v_p24);
void fn_801933D0_p24(int on_p24);
void fn_80192348_p24(int id_p24);
void fn_801909A4_p24(int id_p24);
void SoundMgr_Play_p24(int id_p24);
void ClSound_PlayBgmStream_p24(int id_p24, int arg_p24);
}

#pragma exceptions on

extern "C"int SpeakerTest_Page(TestPage_p24 *self_p24, int phase_p24)
{
char *pool_p24 = lbl_8030E598_p24;
int streams_p24[2] = { 5, 0 };
InputPlayer_p24 *pl_p24;
if (phase_p24 == 0) {
self_p24->cursor_p24 = 7;
self_p24->sub_p24 = 0;
(*(int *)((char *)(self_p24) + 0x20)) = -1;
}
if (phase_p24 == 1) {
pl_p24 = InputMgr_GetPlayer_p24(GetInputManager_p24(), 0);
if ((*(int *)((char *)(self_p24) + 0x20)) == -1) {
if (pl_p24->Pressed_p24(0x800)) {
self_p24->blink_p24 = 0x1F;
if (++self_p24->cursor_p24 > 7) {
self_p24->cursor_p24 = 0;
}
if (self_p24->cursor_p24 == 2) {
self_p24->cursor_p24 = 6;
}
}
if (pl_p24->Pressed_p24(0x1000)) {
if (self_p24->cursor_p24 == 0) {
if (++((unsigned char *)(self_p24)->data_p24) [0x2C] > 15) {
((unsigned char *)(self_p24)->data_p24) [0x2C] = 0;
}
}
if (self_p24->cursor_p24 == 1) {
if (++((unsigned char *)(self_p24)->data_p24) [0x2D] > 15) {
((unsigned char *)(self_p24)->data_p24) [0x2D] = 0;
}
}
if (self_p24->cursor_p24 == 6) {
self_p24->blink_p24 = 0x1F;
(*(int *)((char *)(self_p24) + 0x20)) = 0;
}
if (self_p24->cursor_p24 == 7) {
Backup_PublishShadowCopy_Inline_p24();
self_p24->next_p24 = 0;
}
}
} else if ((*(int *)((char *)(self_p24) + 0x20)) == 0) {
if (pl_p24->Pressed_p24(0x800)) {
if (++self_p24->sub_p24 > 3) {
self_p24->sub_p24 = 0;
}
}
if (pl_p24->Pressed_p24(0x1000)) {
if (self_p24->sub_p24 != 0) {
fn_801934A0_p24((((unsigned char *)(self_p24)->data_p24) [0x2C] << 7) / 15);
fn_8019345C_p24((((unsigned char *)(self_p24)->data_p24) [0x2C] << 7) / 15);
fn_80193404_p24((((unsigned char *)(self_p24)->data_p24) [0x2D] << 7) / 15);
fn_801951E4_p24(((unsigned char *)(self_p24)->data_p24) [0x2E]);
fn_801951CC_p24(((unsigned char *)(self_p24)->data_p24) [0x30]);
if (self_p24->sub_p24 == 3) {
fn_801933D0_p24(1);
} else {
fn_801933D0_p24(0);
}
if (self_p24->sub_p24 == 1) {
(*(int *)((char *)(self_p24) + 0x20)) = 0xB4;
SoundMgr_Play_p24(0);
} else {
(*(int *)((char *)(self_p24) + 0x20)) = 0x258;
ClSound_PlayBgmStream_p24(streams_p24[self_p24->sub_p24 - 2], 0);
}
} else {
(*(int *)((char *)(self_p24) + 0x20)) = 0x258;
}
}
} else {
self_p24->blink_p24 = 0;
(*(int *)((char *)(self_p24) + 0x20)) --;
if ((*(int *)((char *)(self_p24) + 0x20)) <= 0 || pl_p24->Pressed_p24(0x1000)) {
self_p24->blink_p24 = 0x1F;
(*(int *)((char *)(self_p24) + 0x20)) = -1;
if (self_p24->sub_p24 != 0) {
if (self_p24->sub_p24 == 1) {
fn_80192348_p24(0);
} else {
fn_801909A4_p24(streams_p24[self_p24->sub_p24 - 2]);
}
}
fn_801933D0_p24(0);
}
}
}
if (phase_p24 == 2) {
TestPage_DrawItems_p24(self_p24, (*(MenuItem_p24 (*)[])&lbl_803FC81C), self_p24->cursor_p24 + 2);
if (self_p24->text_p24 != 0) {
DrawText_p24(self_p24->text_p24, 0x16C, 0x30, 2, 1.0f, lbl_806D2DA4_p24);
DrawText_p24(self_p24->text_p24, 0x2A, 0x60, 7, 1.0f, lbl_806D2DC4_p24);
if (((unsigned char *)(self_p24)->data_p24) [0x2C] == 12) {
DrawText_p24(self_p24->text_p24, 0x1DC, 0x60, 2, 1.0f, lbl_806D2DCC_p24, ((unsigned char *)(self_p24)->data_p24) [0x2C]);
} else {
DrawText_p24(self_p24->text_p24, 0x1DC, 0x60, 4, 1.0f, lbl_806D2DCC_p24, ((unsigned char *)(self_p24)->data_p24) [0x2C]);
}
if (((unsigned char *)(self_p24)->data_p24) [0x2D] == 8) {
DrawText_p24(self_p24->text_p24, 0x1DC, 0x78, 2, 1.0f, lbl_806D2DCC_p24, ((unsigned char *)(self_p24)->data_p24) [0x2D]);
} else {
DrawText_p24(self_p24->text_p24, 0x1DC, 0x78, 4, 1.0f, lbl_806D2DCC_p24, ((unsigned char *)(self_p24)->data_p24) [0x2D]);
}
DrawText_p24(self_p24->text_p24, 0x2A, 0x108, 7, 1.0f, lbl_806D2DD0_p24);
if (self_p24->cursor_p24 != 6 || (*(int *)((char *)(self_p24) + 0x20)) != -1) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x108, 7, 1.0f, lbl_806D2DD8_p24);
} else if (self_p24->blink_p24 <= 0x1E) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x108, 7, 1.0f, lbl_806D2DD8_p24);
}
DrawText_p24(self_p24->text_p24, 0x2A, 0x138, 7, 1.0f, lbl_806D2DE0_p24);
if ((*(int *)((char *)(self_p24) + 0x20)) != 0) {
DrawText_p24(self_p24->text_p24, 0x1DC, 0x108, 7, 1.0f, lbl_806D2DCC_p24, self_p24->sub_p24);
if (self_p24->sub_p24 == 0) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, pool_p24 + 0x248C);
} else if (self_p24->sub_p24 == 1) {
if ((*(int *)((char *)(self_p24) + 0x20)) > 0x78) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, lbl_806D2DE8_p24);
} else if ((*(int *)((char *)(self_p24) + 0x20)) > 0x3C) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, lbl_806D2DF0_p24);
} else {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, pool_p24 + 0x2498);
}
} else if (self_p24->sub_p24 == 2) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, pool_p24 + 0x24A4);
} else {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, pool_p24 + 0x24B4);
}
} else if (self_p24->blink_p24 <= 0x1E) {
DrawText_p24(self_p24->text_p24, 0x1DC, 0x108, 7, 1.0f, lbl_806D2DCC_p24, self_p24->sub_p24);
if (self_p24->sub_p24 == 0) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, pool_p24 + 0x248C);
} else if (self_p24->sub_p24 == 1) {
if ((*(int *)((char *)(self_p24) + 0x20)) > 0x2D) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, lbl_806D2DF0_p24);
} else if ((*(int *)((char *)(self_p24) + 0x20)) > 0x19) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, lbl_806D2DE8_p24);
} else {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, pool_p24 + 0x2498);
}
} else if (self_p24->sub_p24 == 2) {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, pool_p24 + 0x24A4);
} else {
DrawText_p24(self_p24->text_p24, 0xB6, 0x138, 7, 1.0f, pool_p24 + 0x24B4);
}
}
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/LampTest_Page.cpp (0x80070238) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus on
struct InputPlayer_p25 {
virtual void v0_p25();
virtual void v1_p25();
virtual float v2_p25();
virtual void v3_p25();
virtual float StickRight_p25();
virtual float StickLeft_p25();
virtual unsigned char Pressed_p25(int mask_p25);
virtual unsigned char Held_p25(int mask_p25);
};
struct MenuItem_p25 {
int x_p25;
int y_p25;
const char *text_p25;
};
struct TestPage_p25 {
unsigned char pad_0_p25[8];
int blink_p25;
unsigned char pad_C_p25[4];
int next_p25;
unsigned char pad_14_p25[4];
int cursor_p25;
int sub_p25;
unsigned char pad_20_p25[0x14];
int variant_p25;
unsigned char pad_38_p25[0x238];
void *text_p25;
void *data_p25;
};
extern "C"{
extern char lbl_8030E598_p25[];
void *GetInputManager_p25(void);
InputPlayer_p25 *InputMgr_GetPlayer_p25(void *, int);
void DrawText_p25(void *ctx_p25, int x_p25, int y_p25, int color_p25, float scale_p25, const char *fmt_p25, ...);
}
static inline void TestPage_DrawItems_p25(TestPage_p25 *self_p25, MenuItem_p25 *it_p25, int sel_p25)
{
int i_p25;
for (i_p25 = 0; it_p25[i_p25].text_p25 != 0; i_p25++) {
if (i_p25 != sel_p25 || self_p25->blink_p25 <= 0x1E) {
if (self_p25->text_p25 != 0) {
DrawText_p25(self_p25->text_p25, it_p25[i_p25].x_p25 * 14, it_p25[i_p25].y_p25 * 24, 7, 1.0f, it_p25[i_p25].text_p25);
}
}
}
}
class LampTester_p25 {
public:
LampTester_p25(int mode_p25);
virtual ~LampTester_p25();
void Select_p25(int group_p25);
void Update_p25();
void Draw_p25();
unsigned char data_p25[8];
};
extern "C"{

void fn_80121210_p25(void);
void SpriteHandlePool_GC_p25(void);
}

#pragma exceptions on

extern "C"int LampTest_Page(TestPage_p25 *self_p25, int phase_p25)
{
InputPlayer_p25 *pl_p25;
if (phase_p25 == 0) {
self_p25->cursor_p25 = 4;
self_p25->sub_p25 = -1;
(*(LampTester_p25 **)((char *)(self_p25) + 0x278)) = new LampTester_p25(0);
fn_80121210_p25();
}
if (phase_p25 == 1) {
pl_p25 = InputMgr_GetPlayer_p25(GetInputManager_p25(), 0);
if (self_p25->sub_p25 == -1 && pl_p25->Pressed_p25(0x800)) {
self_p25->blink_p25 = 0x1F;
if (++self_p25->cursor_p25 > 4) {
self_p25->cursor_p25 = 0;
}
}
if (pl_p25->Pressed_p25(0x1000)) {
if (self_p25->cursor_p25 == 4) {
delete (*(LampTester_p25 **)((char *)(self_p25) + 0x278)) ;
(*(LampTester_p25 **)((char *)(self_p25) + 0x278)) = 0;
self_p25->next_p25 = 0;
}
if (self_p25->sub_p25 == -1) {
self_p25->sub_p25 = self_p25->cursor_p25;
if ((*(LampTester_p25 **)((char *)(self_p25) + 0x278)) != 0) {
(*(LampTester_p25 **)((char *)(self_p25) + 0x278)) ->Select_p25(self_p25->sub_p25);
}
} else {
self_p25->sub_p25 = -1;
}
}
if ((*(LampTester_p25 **)((char *)(self_p25) + 0x278)) != 0) {
(*(LampTester_p25 **)((char *)(self_p25) + 0x278)) ->Update_p25();
}
}
if (phase_p25 == 2) {
if (self_p25->sub_p25 == -1) {
TestPage_DrawItems_p25(self_p25, (*(MenuItem_p25 (*)[])&lbl_803FC7B0), self_p25->cursor_p25 + 1);
} else if ((*(LampTester_p25 **)((char *)(self_p25) + 0x278)) != 0) {
(*(LampTester_p25 **)((char *)(self_p25) + 0x278)) ->Draw_p25();
}
SpriteHandlePool_GC_p25();
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

/* ==== game/CameraTest_Page.cpp (0x8007044c) ==== */
#pragma exceptions on
#pragma use_lmw_stmw off
#pragma cplusplus on
struct InputPlayer_p26 {
virtual void v0_p26();
virtual void v1_p26();
virtual float v2_p26();
virtual void v3_p26();
virtual float StickRight_p26();
virtual float StickLeft_p26();
virtual unsigned char Pressed_p26(int mask_p26);
virtual unsigned char Held_p26(int mask_p26);
};
struct MenuItem_p26 {
int x_p26;
int y_p26;
const char *text_p26;
};
struct TestPage_p26 {
unsigned char pad_0_p26[8];
int blink_p26;
unsigned char pad_C_p26[4];
int next_p26;
unsigned char pad_14_p26[4];
int cursor_p26;
int sub_p26;
unsigned char pad_20_p26[0x14];
int variant_p26;
unsigned char pad_38_p26[0x238];
void *text_p26;
void *data_p26;
};
extern "C"{
extern char lbl_8030E598_p26[];
void *GetInputManager_p26(void);
InputPlayer_p26 *InputMgr_GetPlayer_p26(void *, int);
void DrawText_p26(void *ctx_p26, int x_p26, int y_p26, int color_p26, float scale_p26, const char *fmt_p26, ...);
}
static inline void TestPage_DrawItems_p26(TestPage_p26 *self_p26, MenuItem_p26 *it_p26, int sel_p26)
{
int i_p26;
for (i_p26 = 0; it_p26[i_p26].text_p26 != 0; i_p26++) {
if (i_p26 != sel_p26 || self_p26->blink_p26 <= 0x1E) {
if (self_p26->text_p26 != 0) {
DrawText_p26(self_p26->text_p26, it_p26[i_p26].x_p26 * 14, it_p26[i_p26].y_p26 * 24, 7, 1.0f, it_p26[i_p26].text_p26);
}
}
}
}
extern "C"{

extern const char *const lbl_806D2D08_p26;
extern const char *const lbl_806D2D0C_p26;
extern const char lbl_806D2D64_p26[3];
extern const char lbl_806D2D68_p26[5];
extern void *lbl_806D1100_p26;
void *Alloc_p26(unsigned long size_p26);
void MemoryManager_Free_p26(void *p_p26);
void MemoryManager_TimedFree_p26(void *p_p26);
void *FUN_8003b120_p26(int size_p26);
unsigned char GetVBlankFlag_p26(void);
void NamCam_Init_p26(void);
void NamCam_End_p26(void);
int NamCam_GetImageHandle_p26(void *out_p26, int arg_p26);
void NamCam_LoadImage_p26(void *handle_p26, void *buf_p26, void *out_p26);
void *StrPcb_GetInstance_p26(void);
unsigned char StrPcb_IsInErrorState_p26(void *pcb_p26);
void Backup_PublishShadowCopy_Inline_p26(void);
int MonitorTest_Page_p26(TestPage_p26 *self_p26, int phase_p26, int arg_p26);
void fn_801A1280_p26(void);
void Sprite_AdvanceAnim_p26(void *sprite_p26, float dt_p26);
void fn_801A0004_p26(void *sprite_p26);
void fn_8011FA98_p26(void);
void SpriteHandlePool_GC_p26(void);
}
class CameraImage_p26 {
public:
CameraImage_p26()
{
active_p26 = 0;
loaded_p26 = 0;
buf_p26 = 0;
buf_p26 = FUN_8003b120_p26(0x4B000);
}
~CameraImage_p26()
{
MemoryManager_Free_p26(buf_p26);
if (GetVBlankFlag_p26()) {
Stop_p26();
buf_p26 = 0;
}
}
void Stop_p26()
{
if (GetVBlankFlag_p26() && active_p26) {
active_p26 = 0;
NamCam_End_p26();
}
}
void Start_p26()
{
if (GetVBlankFlag_p26()) {
if (active_p26 == 1) {
Stop_p26();
}
active_p26 = 1;
loaded_p26 = 0;
NamCam_Init_p26();
}
}
unsigned char active_p26;
unsigned char loaded_p26;
void *buf_p26;
};
extern "C"void FlashFadeOverlay_Draw_p26(CameraImage_p26 *img_p26, float x0_p26, float y0_p26, float x1_p26, float y1_p26, float dx_p26, float dy_p26);
extern "C"{
extern CameraImage_p26 *lbl_806D1104_p26;
}
static inline void DestroyImage_p26(void)
{
CameraImage_p26 *p_p26 = lbl_806D1104_p26;
if (p_p26 != 0) {
delete p_p26;
lbl_806D1104_p26 = 0;
}
}

#pragma exceptions on

extern "C"int CameraTest_Page(TestPage_p26 *self_p26, int phase_p26)
{
char *pool_p26 = lbl_8030E598_p26;
CameraImage_p26 *img_p26;
InputPlayer_p26 *pl_p26;
if (phase_p26 == 0) {
self_p26->cursor_p26 = 2;
self_p26->sub_p26 = 0;
(*(int *)((char *)(self_p26) + 0x20)) = -1;
DestroyImage_p26();
}
if (phase_p26 == 1) {
if (!StrPcb_IsInErrorState_p26(StrPcb_GetInstance_p26())) {
return 1;
}
img_p26 = lbl_806D1104_p26;
if (img_p26 == 0) {
img_p26 = new CameraImage_p26;
lbl_806D1104_p26 = img_p26;
img_p26->Start_p26();
} else if (self_p26->sub_p26 == 0) {
if (GetVBlankFlag_p26() && img_p26->active_p26) {
void *handle_p26;
char info_p26[0x10];
if (NamCam_GetImageHandle_p26(&handle_p26, 0) == 1) {
NamCam_LoadImage_p26(handle_p26, img_p26->buf_p26, info_p26);
img_p26->loaded_p26 = 1;
}
}
} else {
if (GetVBlankFlag_p26() && img_p26->active_p26) {
void *handle_p26;
NamCam_GetImageHandle_p26(&handle_p26, 0);
}
}
pl_p26 = InputMgr_GetPlayer_p26(GetInputManager_p26(), 0);
if (pl_p26->Pressed_p26(0x2000)) {
if (self_p26->sub_p26 == 0) {
self_p26->sub_p26 = 1;
} else {
self_p26->sub_p26 = 0;
}
}
if ((*(int *)((char *)(self_p26) + 0x20)) == -1) {
if (pl_p26->Pressed_p26(0x800)) {
self_p26->blink_p26 = 0x1F;
if (++self_p26->cursor_p26 > 2) {
self_p26->cursor_p26 = 0;
}
}
if (pl_p26->Pressed_p26(0x1000)) {
if (self_p26->cursor_p26 == 0 || self_p26->cursor_p26 == 1) {
(*(int *)((char *)(self_p26) + 0x20)) = 0;
}
if (self_p26->cursor_p26 == 2) {
DestroyImage_p26();
Backup_PublishShadowCopy_Inline_p26();
self_p26->next_p26 = 2;
MonitorTest_Page_p26(self_p26, 0, 3);
}
}
} else {
if (pl_p26->Pressed_p26(0x1000)) {
self_p26->blink_p26 = 0x1F;
if (++(*(int *)((char *)(self_p26) + 0x20)) >= 2) {
(*(int *)((char *)(self_p26) + 0x20)) = -1;
}
}
if (pl_p26->Pressed_p26(0x800)) {
if (self_p26->cursor_p26 == 0) {
if ((*(int *)((char *)(self_p26) + 0x20)) == 0) {
if (--(*(int *)((char *)(self_p26)->data_p26 + 0x48)) < -12) {
(*(int *)((char *)(self_p26)->data_p26 + 0x48)) = -12;
}
} else {
if (++(*(int *)((char *)(self_p26)->data_p26 + 0x48)) > 12) {
(*(int *)((char *)(self_p26)->data_p26 + 0x48)) = 12;
}
}
} else {
if ((*(int *)((char *)(self_p26) + 0x20)) == 0) {
if (--(*(int *)((char *)(self_p26)->data_p26 + 0x4C)) < -16) {
(*(int *)((char *)(self_p26)->data_p26 + 0x4C)) = -16;
}
} else {
if (++(*(int *)((char *)(self_p26)->data_p26 + 0x4C)) > 16) {
(*(int *)((char *)(self_p26)->data_p26 + 0x4C)) = 16;
}
}
}
}
}
}
if (phase_p26 == 2 && self_p26->text_p26 != 0) {
if (!StrPcb_IsInErrorState_p26(StrPcb_GetInstance_p26())) {
if (self_p26->blink_p26 <= 0x1E) {
DrawText_p26(self_p26->text_p26, 0x7E, 0xD8, 7, 1.0f, pool_p26 + 0x24C4);
}
} else {
const char *modes_p26[2];
modes_p26[0] = lbl_806D2D08_p26;
modes_p26[1] = lbl_806D2D0C_p26;
unsigned char colX_p26;
unsigned char colY_p26;
TestPage_DrawItems_p26(self_p26, (*(MenuItem_p26 (*)[])&lbl_803FC768), -1);
DrawText_p26(self_p26->text_p26, 0x118, 0x108, 7, 1.0f, lbl_806D2D64_p26, modes_p26[self_p26->sub_p26]);
colX_p26 = 2;
colY_p26 = 2;
if ((*(int *)((char *)(self_p26)->data_p26 + 0x48)) != 12) {
colX_p26 = 4;
}
if ((*(int *)((char *)(self_p26)->data_p26 + 0x4C)) != -16) {
colY_p26 = 4;
}
if ((*(int *)((char *)(self_p26) + 0x20)) == -1) {
if (self_p26->cursor_p26 != 0) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, 7, 1.0f, pool_p26 + 0x24E0);
} else if (self_p26->blink_p26 <= 0x1E) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, 7, 1.0f, pool_p26 + 0x24E0);
}
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, 7, 1.0f, pool_p26 + 0x24EC);
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, colX_p26, 1.0f, pool_p26 + 0x2514, -(*(int *)((char *)(self_p26)->data_p26 + 0x48)) );
if (self_p26->cursor_p26 != 1) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, 7, 1.0f, pool_p26 + 0x253C);
} else if (self_p26->blink_p26 <= 0x1E) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, 7, 1.0f, pool_p26 + 0x253C);
}
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, 7, 1.0f, pool_p26 + 0x2548);
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, colY_p26, 1.0f, pool_p26 + 0x2514, (*(int *)((char *)(self_p26)->data_p26 + 0x4C)) );
if (self_p26->cursor_p26 != 2) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x180, 7, 1.0f, lbl_806D2D68_p26);
} else if (self_p26->blink_p26 <= 0x1E) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x180, 7, 1.0f, lbl_806D2D68_p26);
}
} else {
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, 7, 1.0f, pool_p26 + 0x2570);
if (self_p26->cursor_p26 != 0) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, 7, 1.0f, pool_p26 + 0x2598);
} else {
if ((*(int *)((char *)(self_p26) + 0x20)) != 0) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, 7, 1.0f, pool_p26 + 0x25B4);
} else if (self_p26->blink_p26 <= 0x1E) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, 7, 1.0f, pool_p26 + 0x25B4);
}
if ((*(int *)((char *)(self_p26) + 0x20)) != 1) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, 7, 1.0f, pool_p26 + 0x25C8);
} else if (self_p26->blink_p26 <= 0x1E) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, 7, 1.0f, pool_p26 + 0x25C8);
}
}
DrawText_p26(self_p26->text_p26, 0x2A, 0x150, colX_p26, 1.0f, pool_p26 + 0x2514, -(*(int *)((char *)(self_p26)->data_p26 + 0x48)) );
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, 7, 1.0f, pool_p26 + 0x25E4);
if (self_p26->cursor_p26 != 1) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, 7, 1.0f, pool_p26 + 0x260C);
} else {
if ((*(int *)((char *)(self_p26) + 0x20)) != 0) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, 7, 1.0f, pool_p26 + 0x2628);
} else if (self_p26->blink_p26 <= 0x1E) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, 7, 1.0f, pool_p26 + 0x2628);
}
if ((*(int *)((char *)(self_p26) + 0x20)) != 1) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, 7, 1.0f, pool_p26 + 0x2640);
} else if (self_p26->blink_p26 <= 0x1E) {
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, 7, 1.0f, pool_p26 + 0x2640);
}
}
DrawText_p26(self_p26->text_p26, 0x2A, 0x168, colY_p26, 1.0f, pool_p26 + 0x2514, (*(int *)((char *)(self_p26)->data_p26 + 0x4C)) );
DrawText_p26(self_p26->text_p26, 0x2A, 0x180, 7, 1.0f, lbl_806D2D68_p26);
}
if (lbl_806D1104_p26 != 0) {
FlashFadeOverlay_Draw_p26(lbl_806D1104_p26, 98.0f, 2.0f, 542.0f, 286.0f,
(float)(*(int *)((char *)(self_p26)->data_p26 + 0x4C)) , (float)(*(int *)((char *)(self_p26)->data_p26 + 0x48)) );
fn_801A1280_p26();
Sprite_AdvanceAnim_p26(lbl_806D1100_p26, 0.0165f);
fn_801A0004_p26(lbl_806D1100_p26);
fn_8011FA98_p26();
SpriteHandlePool_GC_p26();
}
}
}
return 1;
}

#pragma exceptions reset
#pragma cplusplus reset
#pragma use_lmw_stmw reset
#pragma exceptions reset

