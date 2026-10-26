/* Index of the first of the 8 channels on which the SE id is not playing,
 * or -1 if it plays on all of them (or id is 0). */
extern unsigned char fn_8016C360(unsigned int id);

int SoundMgr_CountActiveSEInstances(unsigned int id)
{
    int i;

    if (id == 0) {
        return -1;
    }
    for (i = 0; i < 8; i++) {
        if (!fn_8016C360(id | ((i << 27) & 0x78000000))) {
            return i;
        }
    }
    return -1;
}
