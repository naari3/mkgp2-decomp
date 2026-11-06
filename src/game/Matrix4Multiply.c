typedef float Matrix4[4][4];

/* Compute into a separate matrix so either input may alias the output. */
void Matrix4_Multiply(Matrix4 out, const Matrix4 left, const Matrix4 right)
{
    Matrix4 result;
    int row;
    int column;

    for (row = 0; row < 4; ++row) {
        for (column = 0; column < 4; ++column) {
            result[row][column] = left[row][0] * right[0][column]
                + right[1][column] * left[row][1]
                + right[2][column] * left[row][2]
                + right[3][column] * left[row][3];
        }
    }
    for (row = 0; row < 4; ++row) {
        for (column = 0; column < 4; ++column) {
            out[row][column] = result[(unsigned int)row][column];
        }
    }
}
