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
void *lbl_803FDB58[16] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&card_send_cleaning_cmd_init,
    (void *)0x0,
    (void *)&card_cleaning_state_machine,
    (void *)0x1000000,
    (void *)&Sci2Card_BeginReset,
    (void *)0x0,
    (void *)&Sci2Card_WaitCleaningComplete,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x1000000,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDB98[20] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&Sci2Card_BeginCleaning,
    (void *)0x0,
    (void *)&Sci2Card_WaitResetComplete,
    (void *)0x1000000,
    (void *)&Sci2Card_WriteTrackData_StartFlow,
    (void *)0x0,
    (void *)&Sci2Card_WriteTrackData_PollState,
    (void *)0x1000000,
    (void *)&card_send_read_cmd_init_dup_unused,
    (void *)0x0,
    (void *)&card_read_state_machine,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x1000000,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDBE8[12] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&Sci2Card_BeginCleaning,
    (void *)0x0,
    (void *)&Sci2Card_WaitResetComplete,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x1000000,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDC18[16] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&Sci2Card_BeginCleaning,
    (void *)0x0,
    (void *)&Sci2Card_WaitResetComplete,
    (void *)0x1000000,
    (void *)&PostRace_StartScoreEntryFlow_WithCardSave,
    (void *)0x0,
    (void *)&Sci2Card_PrintReceipt_PollState,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x1000000,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDC58[16] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&card_send_cleaning_cmd_init,
    (void *)0x0,
    (void *)&card_cleaning_state_machine,
    (void *)0x0,
    (void *)&card_send_read_cmd_init_dup_unused,
    (void *)0x0,
    (void *)&card_read_state_machine,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDC98[40] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&card_send_cleaning_cmd_init,
    (void *)0x0,
    (void *)&card_cleaning_state_machine,
    (void *)0x0,
    (void *)&card_send_read_cmd_init_dup_unused,
    (void *)0x0,
    (void *)&card_read_state_machine,
    (void *)0x1000000,
    (void *)&Sci2Card_WriteTrackData_StartFlow,
    (void *)0x0,
    (void *)&Sci2Card_WriteTrackData_PollState,
    (void *)0x1000000,
    (void *)&PostRace_StartScoreEntryFlow,
    (void *)0x0,
    (void *)&Sci2Card_PrintReceipt_PollState,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x0,
    (void *)&Sci2Card_BeginCleaning,
    (void *)0x0,
    (void *)&Sci2Card_WaitResetComplete,
    (void *)0x1000000,
    (void *)&Sci2Card_WriteTrackData_StartFlow,
    (void *)0x0,
    (void *)&Sci2Card_WriteTrackData_PollState,
    (void *)0x1000000,
    (void *)&PostRace_StartScoreEntryFlow,
    (void *)0x0,
    (void *)&Sci2Card_PrintReceipt_PollState,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDD38[20] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&card_send_cleaning_cmd_init,
    (void *)0x0,
    (void *)&card_cleaning_state_machine,
    (void *)0x0,
    (void *)&Sci2Card_WriteTrackData_StartFlow,
    (void *)0x0,
    (void *)&Sci2Card_WriteTrackData_PollState,
    (void *)0x1000000,
    (void *)&PostRace_StartScoreEntryFlow,
    (void *)0x0,
    (void *)&Sci2Card_PrintReceipt_PollState,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDD88[20] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&card_send_cleaning_cmd_init,
    (void *)0x0,
    (void *)&card_cleaning_state_machine,
    (void *)0x0,
    (void *)&card_send_read_cmd_init_dup_unused,
    (void *)0x0,
    (void *)&card_read_state_machine,
    (void *)0x1000000,
    (void *)&PostRace_StartScoreEntryFlow,
    (void *)0x0,
    (void *)&Sci2Card_PrintReceipt_PollState,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
};
void *lbl_803FDDD8[32] = {
    (void *)0x0,
    (void *)0x0,
    (void *)&card_send_cleaning_cmd_init,
    (void *)0x0,
    (void *)&card_cleaning_state_machine,
    (void *)0x0,
    (void *)&card_send_read_cmd_init_dup_unused,
    (void *)0x0,
    (void *)&card_read_state_machine,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x0,
    (void *)&Sci2Card_BeginCleaning,
    (void *)0x0,
    (void *)&Sci2Card_WaitResetComplete,
    (void *)0x1000000,
    (void *)&Sci2Card_WriteTrackData_StartFlow,
    (void *)0x0,
    (void *)&Sci2Card_WriteTrackData_PollState,
    (void *)0x1000000,
    (void *)&PostRace_StartScoreEntryFlow,
    (void *)0x0,
    (void *)&Sci2Card_PrintReceipt_PollState,
    (void *)0x1000000,
    (void *)&card_eject_init,
    (void *)0x0,
    (void *)&card_eject_state_machine,
    (void *)0x0,
    (void *)0x0,
    (void *)0x0
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
#pragma exceptions off
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
#pragma exceptions off
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
#pragma exceptions off
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
#pragma exceptions off
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
#pragma exceptions off
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
#pragma exceptions off
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
#pragma exceptions off
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
#pragma exceptions off
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
#pragma exceptions off
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
#pragma exceptions off
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

