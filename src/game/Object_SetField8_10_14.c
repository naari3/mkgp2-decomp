extern const float lbl_806D2340;

typedef struct Object_SetField8_10_14_Obj {
    unsigned char pad_0[8];
    float f8;
    unsigned char pad_C[4];
    float f10;
    float f14;
    unsigned char pad_18[0x14];
    void *p2C;
} Object_SetField8_10_14_Obj;

/* 0x80032A70: set three float fields if the object is bound and a >= min. */
int Object_SetField8_10_14(Object_SetField8_10_14_Obj *obj, float a, float b, float c)
{
    if (obj->p2C == 0) {
        return 0;
    }
    if (a < lbl_806D2340) {
        return 0;
    }
    obj->f8 = a;
    obj->f14 = b;
    obj->f10 = c;
    return 1;
}
