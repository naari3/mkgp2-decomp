typedef struct HSD_ClassInfo {
    unsigned char pad[0x2C];
    void *init_member;
} HSD_ClassInfo;

extern HSD_ClassInfo lbl_803F57E0;
extern char lbl_804FC9A8[];
extern char lbl_802E9CC8[];
extern char lbl_802E9CF8[];
extern void hsdInitClassInfo(HSD_ClassInfo *, void *, char *, char *, int, int);
extern void MJObj_InitMember_RGBA(void);

void model_jobj_ClassInit(void) {
    hsdInitClassInfo(&lbl_803F57E0, lbl_804FC9A8, lbl_802E9CC8, lbl_802E9CF8, 0x54, 0x8C);
    lbl_803F57E0.init_member = MJObj_InitMember_RGBA;
}
