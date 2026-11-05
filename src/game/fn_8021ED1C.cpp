extern "C" {
extern const unsigned int lbl_806DB018, lbl_806DB01C, lbl_806DB020, lbl_806DB024;
extern const unsigned int lbl_806DB028, lbl_806DB02C, lbl_806DB030, lbl_806DB034;
extern unsigned int lbl_806D1A68, lbl_806D1A6C, lbl_806D1A70, lbl_806D1A74;
extern unsigned int lbl_804EDD50[12];
}
struct SceneChangeDefaults {
    SceneChangeDefaults() {
        lbl_806D1A68 = lbl_806DB030;
        lbl_806D1A6C = lbl_806DB030;
        lbl_806D1A70 = lbl_806DB034;
        lbl_806D1A74 = lbl_806DB034;
        lbl_804EDD50[0] = lbl_806DB018;
        lbl_804EDD50[1] = lbl_806DB01C;
        lbl_804EDD50[2] = lbl_806DB020;
        lbl_804EDD50[3] = lbl_806DB024;
        lbl_804EDD50[4] = lbl_806DB028;
        lbl_804EDD50[5] = lbl_806DB02C;
        lbl_804EDD50[6] = lbl_806DB030;
        lbl_804EDD50[7] = lbl_806DB030;
        lbl_804EDD50[8] = lbl_806DB030;
        lbl_804EDD50[9] = lbl_806DB034;
        lbl_804EDD50[10] = lbl_806DB034;
        lbl_804EDD50[11] = lbl_806DB034;
    }
};
static SceneChangeDefaults sceneChangeDefaults;
#pragma force_active on
