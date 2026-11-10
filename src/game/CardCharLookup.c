#include "game/types/CardCharEntry.h"
extern CardCharEntry lbl_804E5590[];
unsigned short wchar_to_card_char(const unsigned short *text) {
    unsigned short result = 0;
    int i;
    for (i = 0; i < 0x28E; ++i) {
        if (*text == lbl_804E5590[i].code) {
            result = lbl_804E5590[i].card;
            break;
        }
    }
    return result;
}
