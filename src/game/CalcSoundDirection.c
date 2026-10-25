typedef struct PathEntry {
    unsigned char pad[0x70];
    int segment;
} PathEntry;

typedef struct PathPoint {
    unsigned char pad[4];
    float x;
    unsigned char pad_08[4];
    float z;
} PathPoint;

extern int lbl_806CEEF8;
extern int lbl_806CEEFC;
extern PathPoint *lbl_806D10E4;
extern PathEntry *PathManager_GetEntrySubStruct(void *path, int index);
extern PathPoint *Path_LookupMaxProgressOffset(void *path, int index, int depth);
extern float (*KartDriver_GetKartRootMtx(void *kart))[4];
extern void fn_8025D1B8(float (*src)[4], float (*dst)[4]);
extern void fn_8025DF40(float (*mtx)[4], float *src, float *dst);
extern double Atan2(double, double);

float CalcSoundDirection(void *kart, void *path, float *outVolume, int index) {
    float out[3];
    float vec[3];
    float mtx[3][4];
    PathEntry *entry;
    PathPoint *point;
    int segment;
    float pan;

    if (kart == 0) {
        return 0.0f;
    }
    entry = PathManager_GetEntrySubStruct(path, index);
    segment = entry->segment;
    if (lbl_806CEEFC != -1 && segment != lbl_806CEEFC && lbl_806CEEF8 > 3) {
        lbl_806CEEF8--;
    }
    lbl_806CEEFC = segment;
    point = Path_LookupMaxProgressOffset(path, index, lbl_806CEEF8);
    lbl_806D10E4 = point;
    vec[0] = point->x;
    vec[1] = 0.0f;
    vec[2] = point->z;
    fn_8025D1B8(KartDriver_GetKartRootMtx(kart), mtx);
    vec[0] = -(vec[0] - mtx[0][3]);
    vec[2] = vec[2] - mtx[2][3];
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    fn_8025DF40(mtx, vec, out);
    pan = 57.29577951308232 * (float)Atan2(out[0], out[2]);
    if (pan > 13.0f) {
        pan = 1.0f;
    } else if (pan < -13.0f) {
        pan = -1.0f;
    } else {
        pan = pan / 13.0f;
    }
    *outVolume = 0.9f - 0.6f * (float)__fabs(pan);
    return pan;
}
