/* Raw item-unlock table queries. The 13 rows each contain six item IDs. */
extern const int lbl_803E56B0[13][6];

int fn_8023D7A8(int id)
{
    int row, column;
    for (row = 0; row < 13; ++row) {
        for (column = 0; column < 6; ++column) {
            if (id == lbl_803E56B0[row][column]) return column;
        }
    }
    return 0;
}

int fn_8023D844(int row, int column)
{
    return lbl_803E56B0[row][column];
}

unsigned char fn_8023D860(int id)
{
    int row, column;
    for (row = 0; row < 13; ++row) {
        for (column = 1; column < 6; ++column) {
            if (id == lbl_803E56B0[row][column]) return 1;
        }
    }
    return id == lbl_803E56B0[0][0];
}
