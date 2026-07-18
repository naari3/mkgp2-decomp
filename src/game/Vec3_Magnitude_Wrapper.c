extern float Vec3_Magnitude(void *vec);

#pragma exceptions on
float Vec3_Magnitude_Wrapper(void *vec) {
    return Vec3_Magnitude(vec);
}
#pragma exceptions reset
