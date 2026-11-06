/* Build the repeated horizontal/vertical offsets used by the digit HUD. */
#include "game/RaceDigitsPrivate.h"
extern "C" void fn_80247DAC() {
    lbl_804EE8F0[0][1][0]=11.0f+lbl_804EE8F0[0][0][0];
    lbl_804EE8F0[0][2][0]=11.0f+lbl_804EE8F0[0][1][0];
    lbl_804EE8F0[0][3][0]=7.0f+lbl_804EE8F0[0][2][0];
    lbl_804EE8F0[0][4][0]=11.0f+lbl_804EE8F0[0][3][0];
    lbl_804EE8F0[0][5][0]=11.0f+lbl_804EE8F0[0][4][0];
    lbl_804EE8F0[0][6][0]=7.0f+lbl_804EE8F0[0][5][0];
    lbl_804EE8F0[0][7][0]=11.0f+lbl_804EE8F0[0][6][0];
    lbl_804EE8F0[0][8][0]=11.0f+lbl_804EE8F0[0][7][0];
    lbl_804EE8F0[0][9][0]=11.0f+lbl_804EE8F0[0][8][0];
    lbl_804EE8F0[1][1][0]=11.0f+lbl_804EE8F0[1][0][0];
    lbl_804EE8F0[1][2][0]=11.0f+lbl_804EE8F0[1][1][0];
    lbl_804EE8F0[1][3][0]=7.0f+lbl_804EE8F0[1][2][0];
    lbl_804EE8F0[1][4][0]=11.0f+lbl_804EE8F0[1][3][0];
    lbl_804EE8F0[1][5][0]=11.0f+lbl_804EE8F0[1][4][0];
    lbl_804EE8F0[1][6][0]=7.0f+lbl_804EE8F0[1][5][0];
    lbl_804EE8F0[1][7][0]=11.0f+lbl_804EE8F0[1][6][0];
    lbl_804EE8F0[1][8][0]=11.0f+lbl_804EE8F0[1][7][0];
    lbl_804EE8F0[1][9][0]=11.0f+lbl_804EE8F0[1][8][0];
    lbl_804EE8F0[2][1][0]=24.0f+lbl_804EE8F0[2][0][0];
    lbl_804EE8F0[2][2][0]=18.0f+lbl_804EE8F0[2][1][0];
    lbl_804EE8F0[2][3][0]=18.0f+lbl_804EE8F0[2][2][0];
    lbl_804EE8F0[2][4][0]=24.0f+lbl_804EE8F0[2][3][0];
    lbl_804EE8F0[2][5][0]=18.0f+lbl_804EE8F0[2][4][0];
    lbl_804EE8F0[2][6][0]=12.0f+lbl_804EE8F0[2][5][0];
    lbl_804EE8F0[2][7][0]=16.8f+lbl_804EE8F0[2][6][0];
    lbl_804EE8F0[2][8][0]=16.8f+lbl_804EE8F0[2][7][0];
    lbl_804EE8F0[2][9][0]=16.8f+lbl_804EE8F0[2][8][0];
    lbl_804EE9E0[0][3].y=18.0f+lbl_804EE9E0[0][2].y;
    lbl_804EE9E0[0][4].y=18.0f+lbl_804EE9E0[0][3].y;
    lbl_804EE9E0[0][5].y=18.0f+lbl_804EE9E0[0][4].y;
    lbl_804EE9E0[0][6].y=18.0f+lbl_804EE9E0[0][5].y;
    lbl_804EE9E0[0][7].y=18.0f+lbl_804EE9E0[0][6].y;
    lbl_804EE9E0[0][8].y=18.0f+lbl_804EE9E0[0][7].y;
    lbl_804EE9E0[0][9].y=18.0f+lbl_804EE9E0[0][8].y;
    lbl_804EE9E0[1][3].y=18.0f+lbl_804EE9E0[1][2].y;
    lbl_804EE9E0[1][4].y=18.0f+lbl_804EE9E0[1][3].y;
    lbl_804EE9E0[1][5].y=18.0f+lbl_804EE9E0[1][4].y;
    lbl_804EE9E0[1][6].y=18.0f+lbl_804EE9E0[1][5].y;
    lbl_804EE9E0[1][7].y=18.0f+lbl_804EE9E0[1][6].y;
    lbl_804EE9E0[1][8].y=18.0f+lbl_804EE9E0[1][7].y;
    lbl_804EE9E0[1][9].y=18.0f+lbl_804EE9E0[1][8].y;
}

/* Register the digit-position initialization at startup. */
__declspec(section ".ctors") static void (*const initDigitPositions)() = fn_80247DAC;
