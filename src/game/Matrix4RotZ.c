/* Authoritative target/callee assembly reconstruction; Ghidra unavailable. */
typedef float Matrix4[4][4];

extern float LUT_Sine(float angle);
extern float LUT_Cosine(float angle);
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

void Matrix4_PreMultiplyRotZ(Matrix4 destination, const Matrix4 source,
                             float angle)
{
    Matrix4 rotation;
    Matrix4 product;
    float sine;
    float cosine;
    int row;
    int column;

    Matrix4_Identity(rotation);
    sine = LUT_Sine(angle);
    cosine = LUT_Cosine(angle);
    rotation[0][0] = sine;
    rotation[0][1] = cosine;
    rotation[1][0] = -cosine;
    rotation[1][1] = sine;
    Matrix4_Multiply(source, rotation, product);
    for (row = 0; row < 4; ++row) {
        for (column = 0; column < 4; ++column) {
            destination[row][column] = product[row][column];
        }
    }
}
