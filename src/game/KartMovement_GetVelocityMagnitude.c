extern float Vec3_Magnitude(void *vec);

#pragma exceptions on
float KartMovement_GetVelocityMagnitude(void *km) {
    return Vec3_Magnitude((char *)km + 0x338);
}
#pragma exceptions reset
