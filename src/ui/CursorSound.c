extern void SoundMgr_Play(int);

#pragma exceptions on
void PlayCursorMoveSE(void) {
    SoundMgr_Play(6);
}
#pragma exceptions reset
