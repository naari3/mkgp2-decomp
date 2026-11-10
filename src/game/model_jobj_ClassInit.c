typedef struct HSD_ClassInfo {
    unsigned char pad[0x2C];
    void *init_member;
} HSD_ClassInfo;

extern HSD_ClassInfo g_mjobjClassInfo;
extern char hsdJObj[];
extern char lbl_802E9CC8[];
extern char lbl_802E9CF8[];
extern void hsdInitClassInfo(HSD_ClassInfo *, void *, char *, char *, int, int);
extern void MJObj_InitMember_RGBA(void);

void model_jobj_ClassInit(void) {
    hsdInitClassInfo(&g_mjobjClassInfo, hsdJObj, lbl_802E9CC8, lbl_802E9CF8, 0x54, 0x8C);
    g_mjobjClassInfo.init_member = MJObj_InitMember_RGBA;
}
