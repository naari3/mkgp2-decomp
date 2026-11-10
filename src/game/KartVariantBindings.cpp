/* --- owned .data 0x804EE5D8..0x804EE618 (tools/own_data.py) --- */
#pragma force_active on
extern "C" unsigned int KartVariantBindings_data_804EE5D8[8] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000 };
extern "C" unsigned int KartVariantBindings_data_804EE5F8[8] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000 };
#pragma force_active reset
extern "C" struct KartVariant;
extern "C" {
KartVariant *GetKartSlotKartVariant(int slot);
void fn_8022B39C(KartVariant *variant, int resource, int value);
int fn_8023D1B4(KartVariant *variant) {
    for (int i=0; i<8; ++i) if (GetKartSlotKartVariant(i)==variant) return KartVariantBindings_data_804EE5F8[i];
    return 0;
}
void fn_8023D21C(KartVariant *variant, int resource, int value) {
    fn_8022B39C(variant,resource,value);
    for (int i=0; i<8; ++i) {
        if (GetKartSlotKartVariant(i)==variant) {
            KartVariantBindings_data_804EE5D8[i]=value;
            if (resource==0x93) KartVariantBindings_data_804EE5F8[i]=value-0x8A;
            break;
        }
    }
}
}
