extern float lbl_8039EC84[];
extern short lbl_8039EC64[][2];
extern short lbl_8039EC54[];
extern short lbl_8039EC30[];
extern short lbl_8039EA10[][8][2];

float fn_801D8D3C(int cup, int mirror) {
    return lbl_8039EC84[(cup - 1) * 2 + mirror];
}

int GetCourseShortIdByCupAndMirror(int cup, int round) {
    return lbl_8039EC64[cup - 1][round % 2];
}

int fn_801D8D8C(int i) {
    return lbl_8039EC54[i];
}

int fn_801D8DA0(int i) {
    return lbl_8039EC30[i];
}

int fn_801D8DB4(int a, int b, int mirror) {
    if (mirror == 0) {
        return lbl_8039EA10[a][b][0];
    }
    return lbl_8039EA10[a][b][1];
}
