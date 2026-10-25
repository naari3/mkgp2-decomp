typedef struct GameCfg { unsigned char pad[0x20]; signed char region; unsigned char pad21[2]; unsigned char b23; } GameCfg;
extern GameCfg lbl_80598A60;

unsigned char fn_80169E10(void) {
    return lbl_80598A60.b23;
}
