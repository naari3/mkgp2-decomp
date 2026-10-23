/* Narrow target-observed views; live Ghidra types unavailable. */
struct YawPitchVec { float x, y, z; };
struct YawPitchMatrix { float m[16]; };
struct YawPitchCamera { char pad00[0x80]; YawPitchVec position; };
struct YawPitchEffect {
    char pad00[0x28];
    unsigned char visible;
    char pad29[3];
    float alpha;
    char pad30[0x18];
    float matrix[12];
    char pad78[0x14];
    YawPitchVec position;
    char pad98[0x18];
    float scale;
    char padB4[0x9C];
    float phase;
};
extern "C" {
extern YawPitchCamera lbl_805DF3D0;
extern const float lbl_806D5790, lbl_806D57D8, lbl_806D57DC, lbl_806D57E0, lbl_806D57E4;
void Vec3_Copy(YawPitchVec *, const YawPitchVec *);
void Vec3_Subtract_DestFirst(YawPitchVec *, const YawPitchVec *, const YawPitchVec *);
float Vec3_Magnitude_Wrapper(const YawPitchVec *);
void Vec3_Scale(YawPitchVec *, const YawPitchVec *, float);
void Vec3_Add_DestFirst(YawPitchVec *, const YawPitchVec *, const YawPitchVec *);
float BuildOrientationFromYaw(float);
float Vec3_HorizontalYawTo(const YawPitchVec *, const YawPitchVec *);
void Matrix4_Identity(YawPitchMatrix *);
void Mtx44_Scale_Uniform(YawPitchMatrix *, const YawPitchMatrix *, float);
void Matrix4_PreMultiplyRotY(YawPitchMatrix *, const YawPitchMatrix *, float);
void Matrix4_PreMultiplyRotX(YawPitchMatrix *, const YawPitchMatrix *, float);
void Mtx44_Translate(YawPitchMatrix *, const YawPitchMatrix *, YawPitchVec);
void DbgScene_CopyMatrix3x4Transpose(float *, const YawPitchMatrix *);
void Effect_BuildYawPitchScaleMtx_48(YawPitchEffect *effect, const YawPitchVec *position, float scale, float alpha) {
    if (effect) {
        YawPitchMatrix matrix;
        YawPitchVec delta;
        Vec3_Copy(&effect->position, position);
        YawPitchVec *camera = &lbl_805DF3D0.position;
        Vec3_Subtract_DestFirst(&delta, camera, &effect->position);
        Vec3_Scale(&delta, &delta, lbl_806D57D8 * (lbl_806D5790 / Vec3_Magnitude_Wrapper(&delta)));
        Vec3_Add_DestFirst(&effect->position, &effect->position, &delta);
        effect->scale = lbl_806D57D8 * scale;
        effect->alpha = alpha;
        effect->visible = 1;
        effect->phase = BuildOrientationFromYaw(lbl_806D57DC + effect->phase);
        float yaw = BuildOrientationFromYaw(lbl_806D57E0 + Vec3_HorizontalYawTo(&effect->position, camera));
        Matrix4_Identity(&matrix);
        Mtx44_Scale_Uniform(&matrix, &matrix, effect->scale);
        Matrix4_PreMultiplyRotY(&matrix, &matrix, effect->phase);
        Matrix4_PreMultiplyRotX(&matrix, &matrix, lbl_806D57E4);
        Matrix4_PreMultiplyRotY(&matrix, &matrix, yaw);
        Mtx44_Translate(&matrix, &matrix, effect->position);
        DbgScene_CopyMatrix3x4Transpose(effect->matrix, &matrix);
    }
}
}
