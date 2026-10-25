/* Plays the course-name voice for a course index. */
void SoundMgr_Play(int id);
int isJapanese(void);

void fn_801B7B64(unsigned int course) {
    int id;

    switch (course) {
    case 1:
        id = 0xEC;
        break;
    case 2:
        id = 0x101;
        break;
    case 3:
        id = 0x116;
        break;
    case 4:
        id = 0x12B;
        break;
    case 5:
        id = 0x141;
        break;
    case 6:
        id = 0x156;
        break;
    case 7:
        id = 0x16B;
        break;
    case 8:
        id = 0x180;
        break;
    case 9:
        id = 0x195;
        break;
    case 10:
        if (isJapanese() == 0) {
            id = 0x1AA;
        } else {
            id = 0x1BF;
        }
        break;
    case 11:
        id = 0x1C0;
        break;
    case 12:
        id = 0x1D5;
        break;
    case 0:
    default:
        id = 0xD7;
        break;
    }
    SoundMgr_Play(id);
}
