extern void SoundMgr_Play(int);

#pragma exceptions on
void UI_PlaySeDecide(void) {
    SoundMgr_Play(0x4D);
}
#pragma exceptions reset
