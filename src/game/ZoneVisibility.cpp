/*
 * 0x80174090..0x80174698: the zone visibility table that shows or hides
 * course joints depending on which floor zone the camera is in. The
 * constructor picks a joint-name list and a
 * zone list for the current cup and round, resolves the joints, and builds a
 * linked list of zones; each frame the first zone containing the camera
 * decides which joints are visible (Update, 0x80173FA4, is still asm).
 * Real C++ for the inlined zone deletes; mangled names are bridged in
 * tools/extab_user_renames.json.
 */

struct Vec3f {
    float x, y, z;
};

struct ZoneDesc {
    Vec3f corners[4];
    float height[3];
    unsigned int mask;
};

extern const char lbl_8036E978[0x1C] = "WC_dcity_WC_southtown_joint";
extern const char lbl_8036E994[0x1C] = "WC_dcity_WC_easttown_joint";
extern const char lbl_8036E9B0[0x1C] = "WC_dcity_WC_westtown_joint";
extern const char lbl_8036E9CC[0x1C] = "WC_dcity_WC_downtown_joint";
extern const char lbl_8036E9E8[0x1C] = "WC_dcity_WC_wcshop_joint";
extern const char lbl_8036EA04[0x1C] = "WC_dcity_WC_oyama_wc_joint";
extern const char lbl_8036EA20[0x1C] = "WC_dcity_WC_snowzone_joint";
extern const char lbl_8036EA3C[0x1C] = "WC_dcity_WC_ground_joint";
extern const char lbl_8036EA58[0x20] = "WC_dcity_WC_oyama_shop_joint";
extern const char lbl_8036EA78[0x1C] = "WC_dcity_wc_neon_na_joint";
extern const char lbl_8036EA94[0x1C] = "WC_dcity_wc_neon_nb_joint";
extern const char lbl_8036EAB0[0x1C] = "WC_dcity_wc_neon_nc_joint";
extern const char lbl_8036EACC[0x1C] = "WC_dcity_wc_neon_ra_joint";
extern const char lbl_8036EAE8[0x1C] = "WC_dcity_wc_neon_rb_joint";
extern const char lbl_8036EB04[0x1C] = "WC_dcity_wc_neon_rc_joint";
extern const ZoneDesc lbl_8036EB20[11] = {
    {{{-140.0f, 0.0f, -1190.0f}, {140.0f, 0.0f, -1190.0f}, {140.0f, 0.0f, 10.0f}, {-140.0f, 0.0f, 10.0f}}, {0.0f, 0.0f, 0.0f}, 0x2A7},
    {{{-300.0f, 0.0f, -3300.0f}, {160.0f, 0.0f, -3300.0f}, {160.0f, 0.0f, -1180.0f}, {-300.0f, 0.0f, -1180.0f}}, {0.0f, 0.0f, 0.0f}, 0xA7},
    {{{-1100.0f, 0.0f, -5120.0f}, {520.0f, 0.0f, -5120.0f}, {520.0f, 0.0f, -3290.0f}, {-1100.0f, 0.0f, -3290.0f}}, {0.0f, 0.0f, 0.0f}, 0x5B3},
    {{{510.0f, 0.0f, -3560.0f}, {1490.0f, 0.0f, -3560.0f}, {1490.0f, 0.0f, -2630.0f}, {510.0f, 0.0f, -2630.0f}}, {0.0f, 0.0f, 0.0f}, 0x530},
    {{{1480.0f, 0.0f, -3100.0f}, {1960.0f, 0.0f, -3100.0f}, {1960.0f, 0.0f, -1890.0f}, {1480.0f, 0.0f, -1890.0f}}, {0.0f, 0.0f, 0.0f}, 0x5B5},
    {{{1220.0f, 0.0f, -1900.0f}, {1940.0f, 0.0f, -1900.0f}, {1940.0f, 0.0f, -1000.0f}, {1220.0f, 0.0f, -1000.0f}}, {0.0f, 0.0f, 0.0f}, 0x4B5},
    {{{650.0f, 0.0f, -1010.0f}, {1550.0f, 0.0f, -1010.0f}, {1550.0f, 0.0f, 90.0f}, {650.0f, 0.0f, 90.0f}}, {0.0f, 0.0f, 0.0f}, 0x4A5},
    {{{360.0f, 0.0f, 80.0f}, {960.0f, 0.0f, 80.0f}, {960.0f, 0.0f, 1850.0f}, {360.0f, 0.0f, 1850.0f}}, {0.0f, 0.0f, 0.0f}, 0xA4},
    {{{-360.0f, 0.0f, 1100.0f}, {370.0f, 0.0f, 1100.0f}, {370.0f, 0.0f, 1900.0f}, {-360.0f, 0.0f, 1900.0f}}, {0.0f, 0.0f, 0.0f}, 0x2A7},
    {{{-330.0f, 0.0f, 0.0f}, {150.0f, 0.0f, 0.0f}, {150.0f, 0.0f, 1110.0f}, {-330.0f, 0.0f, 1110.0f}}, {0.0f, 0.0f, 0.0f}, 0x2A3},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const ZoneDesc lbl_8036EDE0[11] = {
    {{{-140.0f, 0.0f, -1190.0f}, {140.0f, 0.0f, -1190.0f}, {140.0f, 0.0f, 10.0f}, {-140.0f, 0.0f, 10.0f}}, {0.0f, 0.0f, 0.0f}, 0x10A7},
    {{{-300.0f, 0.0f, -3300.0f}, {160.0f, 0.0f, -3300.0f}, {160.0f, 0.0f, -1180.0f}, {-300.0f, 0.0f, -1180.0f}}, {0.0f, 0.0f, 0.0f}, 0x10A7},
    {{{-1100.0f, 0.0f, -5120.0f}, {520.0f, 0.0f, -5120.0f}, {520.0f, 0.0f, -3290.0f}, {-1100.0f, 0.0f, -3290.0f}}, {0.0f, 0.0f, 0.0f}, 0x31B3},
    {{{510.0f, 0.0f, -3560.0f}, {1490.0f, 0.0f, -3560.0f}, {1490.0f, 0.0f, -2630.0f}, {510.0f, 0.0f, -2630.0f}}, {0.0f, 0.0f, 0.0f}, 0x2130},
    {{{1480.0f, 0.0f, -3100.0f}, {1960.0f, 0.0f, -3100.0f}, {1960.0f, 0.0f, -1890.0f}, {1480.0f, 0.0f, -1890.0f}}, {0.0f, 0.0f, 0.0f}, 0x21B5},
    {{{1220.0f, 0.0f, -1900.0f}, {1940.0f, 0.0f, -1900.0f}, {1940.0f, 0.0f, -1000.0f}, {1220.0f, 0.0f, -1000.0f}}, {0.0f, 0.0f, 0.0f}, 0x20B5},
    {{{650.0f, 0.0f, -1010.0f}, {1550.0f, 0.0f, -1010.0f}, {1550.0f, 0.0f, 90.0f}, {650.0f, 0.0f, 90.0f}}, {0.0f, 0.0f, 0.0f}, 0x20A5},
    {{{360.0f, 0.0f, 80.0f}, {960.0f, 0.0f, 80.0f}, {960.0f, 0.0f, 1850.0f}, {360.0f, 0.0f, 1850.0f}}, {0.0f, 0.0f, 0.0f}, 0xA4},
    {{{-360.0f, 0.0f, 1100.0f}, {370.0f, 0.0f, 1100.0f}, {370.0f, 0.0f, 1900.0f}, {-360.0f, 0.0f, 1900.0f}}, {0.0f, 0.0f, 0.0f}, 0x10A7},
    {{{-330.0f, 0.0f, 0.0f}, {150.0f, 0.0f, 0.0f}, {150.0f, 0.0f, 1110.0f}, {-330.0f, 0.0f, 1110.0f}}, {0.0f, 0.0f, 0.0f}, 0x10A3},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const ZoneDesc lbl_8036F0A0[11] = {
    {{{-140.0f, 0.0f, -1210.0f}, {140.0f, 0.0f, -1210.0f}, {140.0f, 0.0f, 10.0f}, {-140.0f, 0.0f, 10.0f}}, {0.0f, 0.0f, 0.0f}, 0x2A7},
    {{{-300.0f, 0.0f, -3210.0f}, {160.0f, 0.0f, -3210.0f}, {160.0f, 0.0f, -1200.0f}, {-300.0f, 0.0f, -1200.0f}}, {0.0f, 0.0f, 0.0f}, 0xA7},
    {{{-1100.0f, 0.0f, -5120.0f}, {520.0f, 0.0f, -5120.0f}, {520.0f, 0.0f, -3200.0f}, {-1100.0f, 0.0f, -3200.0f}}, {0.0f, 0.0f, 0.0f}, 0x5B3},
    {{{500.0f, 0.0f, -3560.0f}, {1860.0f, 0.0f, -3560.0f}, {1860.0f, 0.0f, -3000.0f}, {500.0f, 0.0f, -3000.0f}}, {0.0f, 0.0f, 0.0f}, 0x570},
    {{{1840.0f, 0.0f, -3870.0f}, {3830.0f, 0.0f, -3870.0f}, {3830.0f, 0.0f, -2540.0f}, {1840.0f, 0.0f, -2540.0f}}, {0.0f, 0.0f, 0.0f}, 0x478},
    {{{2050.0f, 0.0f, -2550.0f}, {3440.0f, 0.0f, -2550.0f}, {3440.0f, 0.0f, -1300.0f}, {2050.0f, 0.0f, -1300.0f}}, {0.0f, 0.0f, 0.0f}, 0xCC},
    {{{1250.0f, 0.0f, -1310.0f}, {2320.0f, 0.0f, -1310.0f}, {2320.0f, 0.0f, 300.0f}, {1250.0f, 0.0f, 300.0f}}, {0.0f, 0.0f, 0.0f}, 0xAD},
    {{{360.0f, 0.0f, -920.0f}, {1650.0f, 0.0f, -920.0f}, {1650.0f, 0.0f, 640.0f}, {360.0f, 0.0f, 640.0f}}, {0.0f, 0.0f, 0.0f}, 0xAC},
    {{{-370.0f, 0.0f, 1100.0f}, {370.0f, 0.0f, 1100.0f}, {370.0f, 0.0f, 1900.0f}, {-370.0f, 0.0f, 1900.0f}}, {0.0f, 0.0f, 0.0f}, 0x2AF},
    {{{-330.0f, 0.0f, 0.0f}, {150.0f, 0.0f, 0.0f}, {150.0f, 0.0f, 1110.0f}, {-330.0f, 0.0f, 1110.0f}}, {0.0f, 0.0f, 0.0f}, 0x2A3},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const ZoneDesc lbl_8036F360[11] = {
    {{{-140.0f, 0.0f, -1210.0f}, {140.0f, 0.0f, -1210.0f}, {140.0f, 0.0f, 10.0f}, {-140.0f, 0.0f, 10.0f}}, {0.0f, 0.0f, 0.0f}, 0x10A7},
    {{{-300.0f, 0.0f, -3210.0f}, {160.0f, 0.0f, -3210.0f}, {160.0f, 0.0f, -1200.0f}, {-300.0f, 0.0f, -1200.0f}}, {0.0f, 0.0f, 0.0f}, 0x10A7},
    {{{-1100.0f, 0.0f, -5120.0f}, {520.0f, 0.0f, -5120.0f}, {520.0f, 0.0f, -3200.0f}, {-1100.0f, 0.0f, -3200.0f}}, {0.0f, 0.0f, 0.0f}, 0x31B3},
    {{{500.0f, 0.0f, -3560.0f}, {1860.0f, 0.0f, -3560.0f}, {1860.0f, 0.0f, -3000.0f}, {500.0f, 0.0f, -3000.0f}}, {0.0f, 0.0f, 0.0f}, 0x2170},
    {{{1840.0f, 0.0f, -3870.0f}, {3830.0f, 0.0f, -3870.0f}, {3830.0f, 0.0f, -2540.0f}, {1840.0f, 0.0f, -2540.0f}}, {0.0f, 0.0f, 0.0f}, 0x2078},
    {{{2050.0f, 0.0f, -2550.0f}, {3440.0f, 0.0f, -2550.0f}, {3440.0f, 0.0f, -1300.0f}, {2050.0f, 0.0f, -1300.0f}}, {0.0f, 0.0f, 0.0f}, 0xCC},
    {{{1250.0f, 0.0f, -1310.0f}, {2320.0f, 0.0f, -1310.0f}, {2320.0f, 0.0f, 300.0f}, {1250.0f, 0.0f, 300.0f}}, {0.0f, 0.0f, 0.0f}, 0xAD},
    {{{360.0f, 0.0f, -920.0f}, {1650.0f, 0.0f, -920.0f}, {1650.0f, 0.0f, 640.0f}, {360.0f, 0.0f, 640.0f}}, {0.0f, 0.0f, 0.0f}, 0xAC},
    {{{-370.0f, 0.0f, 1100.0f}, {370.0f, 0.0f, 1100.0f}, {370.0f, 0.0f, 1900.0f}, {-370.0f, 0.0f, 1900.0f}}, {0.0f, 0.0f, 0.0f}, 0x10AF},
    {{{-330.0f, 0.0f, 0.0f}, {150.0f, 0.0f, 0.0f}, {150.0f, 0.0f, 1110.0f}, {-330.0f, 0.0f, 1110.0f}}, {0.0f, 0.0f, 0.0f}, 0x10A3},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const char lbl_8036F620[0x1C] = "PC_land_x_share_alfa_joint";
extern const char lbl_8036F63C[0x18] = "PC_land_ac_share_joint";
extern const char lbl_8036F654[0x18] = "PC_land_aa_sora_joint";
extern const char lbl_8036F66C[0x1C] = "PC_land_share_road_joint";
extern const char lbl_8036F688[0x20] = "PC_land_ab_long_pacland_joint";
extern const char lbl_8036F6A8[0x1C] = "PC_land_long_pacman_joint";
extern const char lbl_8036F6C4[0x18] = "PC_land_long_road_joint";
extern const char lbl_8036F6DC[0x1C] = "PC_land_long_normal_joint";
extern const char lbl_8036F6F8[0x1C] = "PC_land_long_reverse_joint";
extern const ZoneDesc lbl_8036F714[3] = {
    {{{5860.0f, 0.0f, -14175.0f}, {12040.0f, 0.0f, -14175.0f}, {12040.0f, 0.0f, 4254.0f}, {5860.0f, 0.0f, 4254.0f}}, {0.0f, 0.0f, 0.0f}, 0x60},
    {{{-5177.0f, 0.0f, -7943.0f}, {1004.0f, 0.0f, -7943.0f}, {1004.0f, 0.0f, 888.0f}, {-5177.0f, 0.0f, 888.0f}}, {0.0f, 0.0f, 0.0f}, 0x9F},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const ZoneDesc lbl_8036F7D4[3] = {
    {{{5860.0f, 0.0f, -14175.0f}, {12040.0f, 0.0f, -14175.0f}, {12040.0f, 0.0f, 4254.0f}, {5860.0f, 0.0f, 4254.0f}}, {0.0f, 0.0f, 0.0f}, 0x60},
    {{{-5177.0f, 0.0f, -7943.0f}, {1004.0f, 0.0f, -7943.0f}, {1004.0f, 0.0f, 888.0f}, {-5177.0f, 0.0f, 888.0f}}, {0.0f, 0.0f, 0.0f}, 0x11F},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const char lbl_8036F894[0x1C] = "KP_castle_kp_obj01_joint";
extern const char lbl_8036F8B0[0x1C] = "KP_castle_kp_obj02_joint";
extern const char lbl_8036F8CC[0x1C] = "KP_castle_kp_obj03_joint";
extern const char lbl_8036F8E8[0x1C] = "KP_castle_kp_obj04_joint";
extern const char lbl_8036F904[0x1C] = "KP_castle_kp_obj05_joint";
extern const char lbl_8036F920[0x1C] = "KP_castle_kp_obj06_joint";
extern const char lbl_8036F93C[0x1C] = "KP_castle_kp_obj07_joint";
extern const char lbl_8036F958[0x1C] = "KP_castle_kp_obj08_joint";
extern const char lbl_8036F974[0x1C] = "KP_castle_kp_obj09_joint";
extern const char lbl_8036F990[0x1C] = "KP_castle_kp_obj10_joint";
extern const char lbl_8036F9AC[0x1C] = "KP_castle_kp_obj11_joint";
extern const ZoneDesc lbl_8036F9C8[11] = {
    {{{-1440.0f, 0.0f, 65.0f}, {-801.0f, 0.0f, 65.0f}, {-801.0f, 0.0f, 2300.0f}, {-1440.0f, 0.0f, 2300.0f}}, {0.0f, 0.0f, 0.0f}, 0x607},
    {{{-1350.0f, 0.0f, -1200.0f}, {-950.0f, 0.0f, -1200.0f}, {-950.0f, 0.0f, 75.0f}, {-1350.0f, 0.0f, 75.0f}}, {0.0f, 0.0f, 0.0f}, 0x407},
    {{{-1380.0f, 0.0f, -2760.0f}, {-200.0f, 0.0f, -2760.0f}, {-200.0f, 0.0f, -1180.0f}, {-1380.0f, 0.0f, -1180.0f}}, {0.0f, 0.0f, 0.0f}, 0x41F},
    {{{-225.0f, 0.0f, -1994.0f}, {1550.0f, 0.0f, -1994.0f}, {1550.0f, 0.0f, -1320.0f}, {-225.0f, 0.0f, -1320.0f}}, {0.0f, 0.0f, 0.0f}, 0x1E},
    {{{1500.0f, 0.0f, -1726.0f}, {1970.0f, 0.0f, -1726.0f}, {1970.0f, 0.0f, -670.0f}, {1500.0f, 0.0f, -670.0f}}, {0.0f, 0.0f, 0.0f}, 0x3C},
    {{{195.0f, 0.0f, -700.0f}, {1970.0f, 0.0f, -700.0f}, {1970.0f, 0.0f, -130.0f}, {195.0f, 0.0f, -130.0f}}, {0.0f, 0.0f, 0.0f}, 0x70},
    {{{-500.0f, 0.0f, -600.0f}, {216.0f, 0.0f, -600.0f}, {216.0f, 0.0f, 633.0f}, {-500.0f, 0.0f, 633.0f}}, {0.0f, 0.0f, 0.0f}, 0x1F0},
    {{{195.0f, 0.0f, 200.0f}, {2260.0f, 0.0f, 200.0f}, {2260.0f, 0.0f, 987.0f}, {195.0f, 0.0f, 987.0f}}, {0.0f, 0.0f, 0.0f}, 0x3C0},
    {{{1450.0f, 0.0f, 950.0f}, {2260.0f, 0.0f, 950.0f}, {2260.0f, 0.0f, 2437.0f}, {1450.0f, 0.0f, 2437.0f}}, {0.0f, 0.0f, 0.0f}, 0x700},
    {{{-860.0f, 0.0f, 1823.0f}, {1496.0f, 0.0f, 1823.0f}, {1496.0f, 0.0f, 2370.0f}, {-860.0f, 0.0f, 2370.0f}}, {0.0f, 0.0f, 0.0f}, 0x601},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const ZoneDesc lbl_8036FC88[8] = {
    {{{-1383.0f, 0.0f, 65.0f}, {710.0f, 0.0f, 95.0f}, {710.0f, 0.0f, 2283.0f}, {-1383.0f, 0.0f, 2283.0f}}, {0.0f, 0.0f, 0.0f}, 0x1C7},
    {{{-1335.0f, 0.0f, -1200.0f}, {-943.0f, 0.0f, -1200.0f}, {-943.0f, 0.0f, 74.0f}, {-1335.0f, 0.0f, 74.0f}}, {0.0f, 0.0f, 0.0f}, 0x8F},
    {{{-1352.0f, 0.0f, -3150.0f}, {1046.0f, 0.0f, -3150.0f}, {1046.0f, 0.0f, -1170.0f}, {-1352.0f, 0.0f, -1170.0f}}, {0.0f, 0.0f, 0.0f}, 0x9F},
    {{{655.0f, 0.0f, -4500.0f}, {3188.0f, 0.0f, -4500.0f}, {3188.0f, 0.0f, -3112.0f}, {655.0f, 0.0f, -3112.0f}}, {0.0f, 0.0f, 0.0f}, 0x3C},
    {{{2305.0f, 0.0f, -3140.0f}, {2875.0f, 0.0f, -3140.0f}, {2875.0f, 0.0f, -1753.0f}, {2305.0f, 0.0f, -1753.0f}}, {0.0f, 0.0f, 0.0f}, 0x30},
    {{{2280.0f, 0.0f, -1786.0f}, {3135.0f, 0.0f, -1786.0f}, {3135.0f, 0.0f, 2278.0f}, {2280.0f, 0.0f, 2278.0f}}, {0.0f, 0.0f, 0.0f}, 0x170},
    {{{337.0f, 0.0f, 2265.0f}, {3223.0f, 0.0f, 2265.0f}, {3223.0f, 0.0f, 3390.0f}, {337.0f, 0.0f, 3390.0f}}, {0.0f, 0.0f, 0.0f}, 0x1E1},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const char lbl_8036FE88[0x14] = "RB_road_share_joint";
extern const char lbl_8036FE9C[0x1C] = "RB_road_share_road_joint";
extern const char lbl_8036FEB8[0x1C] = "RB_road_zzzalpha_01_joint";
extern const char lbl_8036FED4[0x18] = "RB_road_asky_01_joint";
extern const char lbl_8036FEEC[0x14] = "RB_road_short_joint";
extern const char lbl_8036FF00[0x1C] = "RB_road_short_road_joint";
extern const char lbl_8036FF1C[0x1C] = "RB_road_zzalpha_02_joint";
extern const char lbl_8036FF38[0x18] = "RB_road_asky_02_joint";
extern const char lbl_8036FF50[0x1C] = "RB_road_share_normal_joint";
extern const char lbl_8036FF6C[0x18] = "RB_road_ss_normal_joint";
extern const char lbl_8036FF84[0x1C] = "RB_road_neon_normal_joint";
extern const char lbl_8036FFA0[0x1C] = "RB_road_neon_reverse_joint";
extern const char lbl_8036FFBC[0x1C] = "RB_road_share_reverse_joint";
extern const char lbl_8036FFD8[0x1C] = "RB_road_sr_reverse_joint";
extern const char lbl_8036FFF4[0x14] = "RB_road_long_joint";
extern const char lbl_80370008[0x18] = "RB_road_long_road_joint";
extern const char lbl_80370020[0x1C] = "RB_road_long_normal_joint";
extern const char lbl_8037003C[0x1C] = "RB_road_long_reverse_joint";
extern const ZoneDesc lbl_80370058[5] = {
    {{{3008.0f, 0.0f, -3537.0f}, {5323.0f, 0.0f, -3537.0f}, {5323.0f, 0.0f, 2694.0f}, {3008.0f, 0.0f, 2694.0f}}, {0.0f, 0.0f, 0.0f}, 0x50F},
    {{{-7603.0f, 0.0f, -2549.0f}, {-2567.0f, 0.0f, -2549.0f}, {-2567.0f, 0.0f, -226.0f}, {-7603.0f, 0.0f, -226.0f}}, {0.0f, 0.0f, 0.0f}, 0x2F0},
    {{{-4400.0f, 0.0f, -236.0f}, {-3628.0f, 0.0f, -236.0f}, {-3628.0f, 0.0f, 4010.0f}, {-4400.0f, 0.0f, 4010.0f}}, {0.0f, 0.0f, 0.0f}, 0x2F0},
    {{{-6180.0f, 0.0f, 4000.0f}, {-2643.0f, 0.0f, 4000.0f}, {-2643.0f, 0.0f, 6585.0f}, {-6180.0f, 0.0f, 6585.0f}}, {0.0f, 0.0f, 0.0f}, 0x2F0},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const ZoneDesc lbl_80370198[5] = {
    {{{3008.0f, 0.0f, -3537.0f}, {5323.0f, 0.0f, -3537.0f}, {5323.0f, 0.0f, 2694.0f}, {3008.0f, 0.0f, 2694.0f}}, {0.0f, 0.0f, 0.0f}, 0x90F},
    {{{-7603.0f, 0.0f, -2549.0f}, {-2567.0f, 0.0f, -2549.0f}, {-2567.0f, 0.0f, -226.0f}, {-7603.0f, 0.0f, -226.0f}}, {0.0f, 0.0f, 0.0f}, 0x2F0},
    {{{-4400.0f, 0.0f, -236.0f}, {-3628.0f, 0.0f, -236.0f}, {-3628.0f, 0.0f, 4010.0f}, {-4400.0f, 0.0f, 4010.0f}}, {0.0f, 0.0f, 0.0f}, 0x2F0},
    {{{-6180.0f, 0.0f, 4000.0f}, {-2643.0f, 0.0f, 4000.0f}, {-2643.0f, 0.0f, 6585.0f}, {-6180.0f, 0.0f, 6585.0f}}, {0.0f, 0.0f, 0.0f}, 0x2F0},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const ZoneDesc lbl_803702D8[11] = {
    {{{3008.0f, 0.0f, -3537.0f}, {5323.0f, 0.0f, -3537.0f}, {5323.0f, 0.0f, 2694.0f}, {3008.0f, 0.0f, 2694.0f}}, {0.0f, 0.0f, 0.0f}, 0x30F},
    {{{-3385.0f, 0.0f, -4010.0f}, {-2910.0f, 0.0f, -4010.0f}, {-2910.0f, 0.0f, -1192.0f}, {-3385.0f, 0.0f, -1192.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-6203.0f, 0.0f, -1202.0f}, {-2910.0f, 0.0f, -1202.0f}, {-2910.0f, 0.0f, -15.0f}, {-6203.0f, 0.0f, -15.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-6203.0f, 0.0f, -25.0f}, {-2811.0f, 0.0f, -25.0f}, {-2811.0f, 0.0f, 643.0f}, {-6203.0f, 0.0f, 643.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-4316.0f, 0.0f, 633.0f}, {-2858.0f, 0.0f, 633.0f}, {-2858.0f, 0.0f, 1637.0f}, {-4316.0f, 0.0f, 1637.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-6022.0f, 0.0f, 633.0f}, {-4306.0f, 0.0f, 633.0f}, {-4306.0f, 0.0f, 1874.0f}, {-6022.0f, 0.0f, 1874.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-4790.0f, 0.0f, 1649.0f}, {-3312.0f, 0.0f, 1649.0f}, {-3312.0f, 0.0f, 2720.0f}, {-4790.0f, 0.0f, 2720.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-5810.0f, 0.0f, 1874.0f}, {-4780.0f, 0.0f, 1874.0f}, {-4780.0f, 0.0f, 3306.0f}, {-5810.0f, 0.0f, 3306.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-4790.0f, 0.0f, 2779.0f}, {-3312.0f, 0.0f, 2779.0f}, {-3312.0f, 0.0f, 3470.0f}, {-4790.0f, 0.0f, 3470.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-6787.0f, 0.0f, 3460.0f}, {-3312.0f, 0.0f, 3460.0f}, {-3312.0f, 0.0f, 5366.0f}, {-6787.0f, 0.0f, 5366.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};
extern const ZoneDesc lbl_80370598[11] = {
    {{{3008.0f, 0.0f, -3537.0f}, {5323.0f, 0.0f, -3537.0f}, {5323.0f, 0.0f, 2694.0f}, {3008.0f, 0.0f, 2694.0f}}, {0.0f, 0.0f, 0.0f}, 0x30F},
    {{{-3385.0f, 0.0f, -4010.0f}, {-2910.0f, 0.0f, -4010.0f}, {-2910.0f, 0.0f, -1192.0f}, {-3385.0f, 0.0f, -1192.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-6203.0f, 0.0f, -1202.0f}, {-2910.0f, 0.0f, -1202.0f}, {-2910.0f, 0.0f, -15.0f}, {-6203.0f, 0.0f, -15.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-6203.0f, 0.0f, -25.0f}, {-2811.0f, 0.0f, -25.0f}, {-2811.0f, 0.0f, 643.0f}, {-6203.0f, 0.0f, 643.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-4316.0f, 0.0f, 633.0f}, {-2858.0f, 0.0f, 633.0f}, {-2858.0f, 0.0f, 1637.0f}, {-4316.0f, 0.0f, 1637.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-6022.0f, 0.0f, 633.0f}, {-4306.0f, 0.0f, 633.0f}, {-4306.0f, 0.0f, 1874.0f}, {-6022.0f, 0.0f, 1874.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-4790.0f, 0.0f, 1649.0f}, {-3312.0f, 0.0f, 1649.0f}, {-3312.0f, 0.0f, 2720.0f}, {-4790.0f, 0.0f, 2720.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-5810.0f, 0.0f, 1874.0f}, {-4780.0f, 0.0f, 1874.0f}, {-4780.0f, 0.0f, 3306.0f}, {-5810.0f, 0.0f, 3306.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-4790.0f, 0.0f, 2779.0f}, {-3312.0f, 0.0f, 2779.0f}, {-3312.0f, 0.0f, 3470.0f}, {-4790.0f, 0.0f, 3470.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{-6787.0f, 0.0f, 3460.0f}, {-3312.0f, 0.0f, 3460.0f}, {-3312.0f, 0.0f, 5366.0f}, {-6787.0f, 0.0f, 5366.0f}}, {0.0f, 0.0f, 0.0f}, 0xF0},
    {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}, {0.0f, 0.0f, 0.0f}, 0x0},
};

static const char *sCityNames[16] = {
    lbl_8036E978,
    lbl_8036E994,
    lbl_8036E9B0,
    lbl_8036E9CC,
    lbl_8036E9E8,
    lbl_8036EA04,
    lbl_8036EA20,
    lbl_8036EA3C,
    lbl_8036EA58,
    lbl_8036EA78,
    lbl_8036EA94,
    lbl_8036EAB0,
    lbl_8036EACC,
    lbl_8036EAE8,
    lbl_8036EB04,
    0,
};

static const char *sPacNormalNames[10] = {
    lbl_8036F620,
    lbl_8036F63C,
    lbl_8036F654,
    lbl_8036F66C,
    lbl_8036F688,
    lbl_8036F6A8,
    lbl_8036F6C4,
    lbl_8036F6DC,
    lbl_8036F6F8,
    0,
};

static const char *sPacReverseNames[10] = {
    lbl_8036F620,
    lbl_8036F63C,
    lbl_8036F654,
    lbl_8036F66C,
    lbl_8036F688,
    lbl_8036F6A8,
    lbl_8036F6C4,
    lbl_8036F6DC,
    lbl_8036F6F8,
    0,
};

static const char *sCastleNames[12] = {
    lbl_8036F894,
    lbl_8036F8B0,
    lbl_8036F8CC,
    lbl_8036F8E8,
    lbl_8036F904,
    lbl_8036F920,
    lbl_8036F93C,
    lbl_8036F958,
    lbl_8036F974,
    lbl_8036F990,
    lbl_8036F9AC,
    0,
};

static const char *sRoadNames[13] = {
    lbl_8036FE88,
    lbl_8036FE9C,
    lbl_8036FEB8,
    lbl_8036FED4,
    lbl_8036FEEC,
    lbl_8036FF00,
    lbl_8036FF1C,
    lbl_8036FF38,
    lbl_8036FF50,
    lbl_8036FF6C,
    lbl_8036FF84,
    lbl_8036FFA0,
    0,
};

static const char *sRoadReverseNames[13] = {
    lbl_8036FE88,
    lbl_8036FE9C,
    lbl_8036FEB8,
    lbl_8036FED4,
    lbl_8036FEEC,
    lbl_8036FF00,
    lbl_8036FF1C,
    lbl_8036FF38,
    lbl_8036FFBC,
    lbl_8036FFD8,
    lbl_8036FF84,
    lbl_8036FFA0,
    0,
};

static const char *sRoadLongNames[11] = {
    lbl_8036FE88,
    lbl_8036FE9C,
    lbl_8036FEB8,
    lbl_8036FED4,
    lbl_8036FFF4,
    lbl_80370008,
    lbl_8036FF1C,
    lbl_8036FF38,
    lbl_80370020,
    lbl_8036FF84,
    0,
};

static const char *sRoadLongReverseNames[11] = {
    lbl_8036FE88,
    lbl_8036FE9C,
    lbl_8036FEB8,
    lbl_8036FED4,
    lbl_8036FFF4,
    lbl_80370008,
    lbl_8036FF1C,
    lbl_8036FF38,
    lbl_8037003C,
    lbl_8036FFA0,
    0,
};

struct ZoneVolume {
    ZoneVolume(const ZoneDesc *desc, int closed);
    ~ZoneVolume();
    unsigned char Contains(Vec3f *pos);
    char pad00[0x4];
};

struct Zone {
    Zone *next;
    ZoneVolume *vol;
    unsigned int mask;
    int id;

    Zone(const ZoneDesc *desc, int id) {
        next = 0;
        vol = 0;
        mask = 0;
        this->id = id;
        if (desc) {
            vol = new ZoneVolume(desc, 1);
            mask = desc->mask;
        }
    }

    ~Zone() {
        if (next) {
            delete next;
        }
        if (vol) {
            delete vol;
        }
    }

    unsigned char Contains(Vec3f *pos) {
        if (vol) {
            return vol->Contains(pos);
        }
        return 0;
    }

    void Append(Zone *zone) {
        if (next) {
            next->Append(zone);
        } else {
            next = zone;
        }
    }
};

struct JObj;

struct ZoneVisibility {
    Zone *zones;
    JObj **joints;
    int count;
    int cur;

    void Update();
    ~ZoneVisibility();
    ZoneVisibility(JObj *root);
};

extern "C" {
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
JObj *ResolveJointByName(JObj *, const char *);
}

#pragma exceptions on

ZoneVisibility::~ZoneVisibility() {
    if (zones) {
        delete zones;
    }
    if (joints) {
        int i;

        for (i = 0; i < count; i++) {
            joints[i] = 0;
        }
        delete[] joints;
    }
}

ZoneVisibility::ZoneVisibility(JObj *root) {
    const ZoneDesc *desc;
    int i;
    int j;
    const char **names;
    const ZoneDesc *descs;

    zones = 0;
    joints = 0;
    count = 0;
    cur = -1;
    if (!root) {
        return;
    }
    switch (g_cupId) {
    case 1:
        return;
    case 2:
        return;
    case 3:
        if (!g_longRoundFlag) {
            if (!g_reverseRoundFlag) {
                names = sCityNames;
                descs = lbl_8036EB20;
            } else {
                names = sCityNames;
                descs = lbl_8036EDE0;
            }
        } else {
            if (!g_reverseRoundFlag) {
                names = sCityNames;
                descs = lbl_8036F0A0;
            } else {
                names = sCityNames;
                descs = lbl_8036F360;
            }
        }
        break;
    case 4:
        if (g_longRoundFlag == 1) {
            if (!g_reverseRoundFlag) {
                names = sPacNormalNames;
                descs = lbl_8036F714;
            } else {
                names = sPacReverseNames;
                descs = lbl_8036F7D4;
            }
            break;
        }
        return;
    case 5:
        names = sCastleNames;
        if (!g_longRoundFlag) {
            descs = lbl_8036F9C8;
        } else {
            descs = lbl_8036FC88;
        }
        break;
    case 6:
        if (!g_longRoundFlag) {
            if (!g_reverseRoundFlag) {
                names = sRoadNames;
                descs = lbl_80370058;
            } else {
                names = sRoadReverseNames;
                descs = lbl_80370198;
            }
        } else {
            if (!g_reverseRoundFlag) {
                names = sRoadLongNames;
                descs = lbl_803702D8;
            } else {
                names = sRoadLongReverseNames;
                descs = lbl_80370598;
            }
        }
        break;
    case 9:
        return;
    case 10:
        return;
    case 11:
        return;
    case 12:
        return;
    case 13:
        return;
    case 14:
        names = sRoadNames;
        descs = lbl_80370058;
        break;
    default:
        return;
    }
    if (!names || !descs) {
        return;
    }
    for (count = 0; names[count]; count++) {
    }
    joints = new JObj *[count];
    for (j = 0; j < count; j++) {
        joints[j] = ResolveJointByName(root, names[j]);
    }
    for (i = 0, desc = descs;; desc++, i++) {
        Zone *zone;

        if (!desc->mask) {
            break;
        }
        zone = new Zone(desc, i);

        if (zones) {
            zones->Append(zone);
        } else {
            zones = zone;
        }
    }
}

#pragma exceptions reset
