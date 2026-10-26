/* Play an SE id, tagging it with a channel number in bits 27..30. Ids 0 and
 * 0xBF are "no sound". */
extern void fn_8016C288(unsigned int id);

void SoundMgr_PlaySE_WithChannel(unsigned int id, int unused, int channel)
{
    if (id != 0 && id != 0xbf) {
        if (channel > 0) {
            id |= (channel & 0xf) << 27;
        }
        fn_8016C288(id);
    }
}
