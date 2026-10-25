typedef struct GameCfg { unsigned char pad[0x20]; signed char region; } GameCfg;
extern GameCfg lbl_80598A60;

int fn_80169E20(void) {
    return lbl_80598A60.region;
}
