/* Build the repeated horizontal/vertical offsets used by the digit HUD.
 * NonMatching: registration at .ctors:802E8960 remains in the target fallback.
 */
#include "game/RaceDigitsPrivate.h"
extern "C" {
extern const float lbl_806DBF40, lbl_806DBF44, lbl_806DBF48;
extern const float lbl_806DBF4C, lbl_806DBF50, lbl_806DBF54;
}

extern "C" void fn_80247DAC() {
    lbl_804EE8F0[0][1][0]=lbl_806DBF40+lbl_804EE8F0[0][0][0];
    lbl_804EE8F0[0][2][0]=lbl_806DBF40+lbl_804EE8F0[0][1][0];
    lbl_804EE8F0[0][3][0]=lbl_806DBF44+lbl_804EE8F0[0][2][0];
    lbl_804EE8F0[0][4][0]=lbl_806DBF40+lbl_804EE8F0[0][3][0];
    lbl_804EE8F0[0][5][0]=lbl_806DBF40+lbl_804EE8F0[0][4][0];
    lbl_804EE8F0[0][6][0]=lbl_806DBF44+lbl_804EE8F0[0][5][0];
    lbl_804EE8F0[0][7][0]=lbl_806DBF40+lbl_804EE8F0[0][6][0];
    lbl_804EE8F0[0][8][0]=lbl_806DBF40+lbl_804EE8F0[0][7][0];
    lbl_804EE8F0[0][9][0]=lbl_806DBF40+lbl_804EE8F0[0][8][0];
    lbl_804EE8F0[1][1][0]=lbl_806DBF40+lbl_804EE8F0[1][0][0];
    lbl_804EE8F0[1][2][0]=lbl_806DBF40+lbl_804EE8F0[1][1][0];
    lbl_804EE8F0[1][3][0]=lbl_806DBF44+lbl_804EE8F0[1][2][0];
    lbl_804EE8F0[1][4][0]=lbl_806DBF40+lbl_804EE8F0[1][3][0];
    lbl_804EE8F0[1][5][0]=lbl_806DBF40+lbl_804EE8F0[1][4][0];
    lbl_804EE8F0[1][6][0]=lbl_806DBF44+lbl_804EE8F0[1][5][0];
    lbl_804EE8F0[1][7][0]=lbl_806DBF40+lbl_804EE8F0[1][6][0];
    lbl_804EE8F0[1][8][0]=lbl_806DBF40+lbl_804EE8F0[1][7][0];
    lbl_804EE8F0[1][9][0]=lbl_806DBF40+lbl_804EE8F0[1][8][0];
    lbl_804EE8F0[2][1][0]=lbl_806DBF48+lbl_804EE8F0[2][0][0];
    lbl_804EE8F0[2][2][0]=lbl_806DBF4C+lbl_804EE8F0[2][1][0];
    lbl_804EE8F0[2][3][0]=lbl_806DBF4C+lbl_804EE8F0[2][2][0];
    lbl_804EE8F0[2][4][0]=lbl_806DBF48+lbl_804EE8F0[2][3][0];
    lbl_804EE8F0[2][5][0]=lbl_806DBF4C+lbl_804EE8F0[2][4][0];
    lbl_804EE8F0[2][6][0]=lbl_806DBF50+lbl_804EE8F0[2][5][0];
    lbl_804EE8F0[2][7][0]=lbl_806DBF54+lbl_804EE8F0[2][6][0];
    lbl_804EE8F0[2][8][0]=lbl_806DBF54+lbl_804EE8F0[2][7][0];
    lbl_804EE8F0[2][9][0]=lbl_806DBF54+lbl_804EE8F0[2][8][0];
    lbl_804EE9E0[0][3].y=lbl_806DBF4C+lbl_804EE9E0[0][2].y;
    lbl_804EE9E0[0][4].y=lbl_806DBF4C+lbl_804EE9E0[0][3].y;
    lbl_804EE9E0[0][5].y=lbl_806DBF4C+lbl_804EE9E0[0][4].y;
    lbl_804EE9E0[0][6].y=lbl_806DBF4C+lbl_804EE9E0[0][5].y;
    lbl_804EE9E0[0][7].y=lbl_806DBF4C+lbl_804EE9E0[0][6].y;
    lbl_804EE9E0[0][8].y=lbl_806DBF4C+lbl_804EE9E0[0][7].y;
    lbl_804EE9E0[0][9].y=lbl_806DBF4C+lbl_804EE9E0[0][8].y;
    lbl_804EE9E0[1][3].y=lbl_806DBF4C+lbl_804EE9E0[1][2].y;
    lbl_804EE9E0[1][4].y=lbl_806DBF4C+lbl_804EE9E0[1][3].y;
    lbl_804EE9E0[1][5].y=lbl_806DBF4C+lbl_804EE9E0[1][4].y;
    lbl_804EE9E0[1][6].y=lbl_806DBF4C+lbl_804EE9E0[1][5].y;
    lbl_804EE9E0[1][7].y=lbl_806DBF4C+lbl_804EE9E0[1][6].y;
    lbl_804EE9E0[1][8].y=lbl_806DBF4C+lbl_804EE9E0[1][7].y;
    lbl_804EE9E0[1][9].y=lbl_806DBF4C+lbl_804EE9E0[1][8].y;
}
