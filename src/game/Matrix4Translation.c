/* Authoritative target/callee assembly reconstruction; Ghidra unavailable. */
typedef float Matrix4[4][4];

extern const float lbl_806D592C;
extern const float lbl_806D5930;

static inline void Matrix4_Identity(Matrix4 matrix)
{
    matrix[0][0] = lbl_806D5930;
    matrix[0][1] = lbl_806D592C;
    matrix[0][2] = lbl_806D592C;
    matrix[0][3] = lbl_806D592C;
    matrix[1][0] = lbl_806D592C;
    matrix[1][1] = lbl_806D5930;
    matrix[1][2] = lbl_806D592C;
    matrix[1][3] = lbl_806D592C;
    matrix[2][0] = lbl_806D592C;
    matrix[2][1] = lbl_806D592C;
    matrix[2][2] = lbl_806D5930;
    matrix[2][3] = lbl_806D592C;
    matrix[3][0] = lbl_806D592C;
    matrix[3][1] = lbl_806D592C;
    matrix[3][2] = lbl_806D592C;
    matrix[3][3] = lbl_806D5930;
}

static inline void Matrix4_Multiply(const Matrix4 left, const Matrix4 right,
                                    Matrix4 output)
{
    int row;
    int column;
    for (row = 0; row < 4; ++row) {
        for (column = 0; column < 4; ++column) {
            output[row][column] = left[row][0] * right[0][column]
                + right[1][column] * left[row][1]
                + right[2][column] * left[row][2]
                + right[3][column] * left[row][3];
        }
    }
}

static inline void Matrix4_SetTranslation(Matrix4 matrix, float x, float y, float z)
{
    matrix[3][0] = x;
    matrix[3][1] = y;
    matrix[3][2] = z;
}

void Matrix4_PreMultiplyTranslation(Matrix4 destination, const Matrix4 source,
                                    float x, float y, float z)
{
    Matrix4 translation;
    Matrix4 product;
    int row;
    int column;

    Matrix4_Identity(translation);
    Matrix4_SetTranslation(translation, x, y, z);
    Matrix4_Multiply(source, translation, product);
    for (row = 0; row < 4; ++row) {
        for (column = 0; column < 4; ++column) {
            destination[row][column] = product[(unsigned int)row][column];
        }
    }
}
