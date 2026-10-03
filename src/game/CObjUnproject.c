/* Field views are limited to offsets used by this wrapper. */
typedef struct CObjUnprojectView {
    unsigned char pad00[4];
    void *camera;
    unsigned char pad08[0x20];
    unsigned int ready;
} CObjUnprojectView;

extern const void *fn_802C7E30(void *camera);
extern void fn_8025D1B8(const void *source, void *destination);
extern void fn_8025DF40(const void *matrix, const void *source, void *destination);

void CObj_UnprojectPoint(CObjUnprojectView *self, float x, float y, float z,
                         float *outX, float *outY, float *outZ) {
    float matrix[3][4];
    float vector[3];
    const void *source;

    if (self->ready == 0) source = 0;
    else source = fn_802C7E30(self->camera);
    fn_8025D1B8(source, matrix);
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    fn_8025DF40(matrix, vector, vector);
    if (outX != 0) *outX = vector[0];
    if (outY != 0) *outY = vector[1];
    if (outZ != 0) *outZ = vector[2];
}
