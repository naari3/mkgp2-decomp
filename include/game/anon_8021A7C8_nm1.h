#ifndef GAME_ANON_8021A7C8_NM1_H
#define GAME_ANON_8021A7C8_NM1_H

struct KartModelNames {
    const char *drivers[13];
    const char *tires[13];
};

struct KartModelResources {
    int animIds[4];
    char preceding[0x180 - 0x10];
    char name_180[0x1C]; // chara_peach_pony_null_joint
    char name_19C[0xC]; // pony.dat
    char name_1A8[0x18]; // chara_%s_hand_goo_joint
    char name_1C0[0x18]; // chara_%s_hand_pa_joint
    char name_1D8[0x18]; // chara_%s_hand_fin_joint
    char name_1F0[0x10]; // cart_tire.dat
    char name_200[0x18]; // cart_tireset_fl_joint
    char name_218[0x18]; // cart_tireset_fr_joint
    char name_230[0x18]; // cart_tireset_rl_joint
    char name_248[0x18]; // cart_tireset_rr_joint
    char name_260[0x18]; // %s_cart_tire_fl_joint
    char name_278[0x18]; // %s_cart_tire_fr_joint
    char name_290[0x18]; // %s_cart_tire_rl_joint
    char name_2A8[0x18]; // %s_cart_tire_rr_joint
    char name_2C0[0x18]; // cart_big_tire_fl_joint
    char name_2D8[0x18]; // cart_big_tire_fr_joint
    char name_2F0[0x18]; // cart_big_tire_rl_joint
    char name_308[0x18]; // cart_big_tire_rr_joint
    char name_320[0x18]; // cart_kaku_tire_fl_joint
    char name_338[0x18]; // cart_kaku_tire_fr_joint
    char name_350[0x18]; // cart_kaku_tire_rl_joint
    char name_368[0x18]; // cart_kaku_tire_rr_joint
    char name_380[0x18]; // cart_oil_tire_fl_joint
    char name_398[0x18]; // cart_oil_tire_fr_joint
    char name_3B0[0x18]; // cart_oil_tire_rl_joint
    char name_3C8[0x18]; // cart_oil_tire_rr_joint
    char name_3E0[0x18]; // cart_oil_grid_fl_joint
    char name_3F8[0x18]; // cart_oil_grid_fr_joint
    char name_410[0x18]; // cart_oil_grid_rl_joint
    char name_428[0x18]; // cart_oil_grid_rr_joint
    char name_440[0x18]; // cart_punk_grid_fl_joint
    char name_458[0x18]; // cart_punk_grid_fr_joint
    char name_470[0x18]; // cart_punk_grid_rl_joint
    char name_488[0x18]; // cart_punk_grid_rr_joint
    char name_4A0[0x18]; // cart_punk_tire_fl_joint
    char name_4B8[0x18]; // cart_punk_tire_fr_joint
    char name_4D0[0x18]; // cart_punk_tire_rl_joint
    char name_4E8[0x18]; // cart_punk_tire_rr_joint
    char name_500[0x18]; // cart_snow_tire_fl_joint
    char name_518[0x18]; // cart_snow_tire_fr_joint
    char name_530[0x18]; // cart_snow_tire_rl_joint
    char name_548[0x18]; // cart_snow_tire_rr_joint
};

#endif
