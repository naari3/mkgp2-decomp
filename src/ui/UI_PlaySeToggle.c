extern void SoundMgr_Play(int);

#pragma exceptions on
void UI_PlaySeToggle(int flag) {
    if (flag == 0) {
        SoundMgr_Play(0x4E);
    } else {
        SoundMgr_Play(0x4F);
    }
}
#pragma exceptions reset
