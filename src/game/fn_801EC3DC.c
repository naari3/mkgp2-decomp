typedef int s32;

s32 fn_801DE7C4();
extern s32 lbl_806D1920;

void fn_801EC3DC(void) {
    lbl_806D1920 = fn_801DE7C4() * 0x3C;
}

__declspec(section ".ctors") static void (*const s_fn_801EC3DC_ctor)(void) = fn_801EC3DC;
