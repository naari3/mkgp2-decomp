struct KartVariant;
extern "C" {
KartVariant *GetKartSlotKartVariant(int slot);
void fn_8022B39C(KartVariant *variant, int resource, int value);
extern int lbl_804EE5D8[8];
extern int lbl_804EE5F8[8];
int fn_8023D1B4(KartVariant *variant) {
    for (int i=0; i<8; ++i) if (GetKartSlotKartVariant(i)==variant) return lbl_804EE5F8[i];
    return 0;
}
void fn_8023D21C(KartVariant *variant, int resource, int value) {
    fn_8022B39C(variant,resource,value);
    for (int i=0; i<8; ++i) {
        if (GetKartSlotKartVariant(i)==variant) {
            lbl_804EE5D8[i]=value;
            if (resource==0x93) lbl_804EE5F8[i]=value-0x8A;
            break;
        }
    }
}
}
