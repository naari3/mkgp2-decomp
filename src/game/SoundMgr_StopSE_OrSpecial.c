/* Stop an SE id (tagged with its channel in bits 27..30); id 0xBF stops the
 * special channel instead. Id 0 is "no sound". */
extern void fn_8016C394(unsigned int id);
extern void fn_8016C444(int arg);

void SoundMgr_StopSE_OrSpecial(unsigned int id, int channel)
{
    if (id != 0) {
        if (id == 0xbf) {
            fn_8016C444(0);
        } else {
            if (channel > 0) {
                id |= (channel & 0xf) << 27;
            }
            fn_8016C394(id);
        }
    }
}
