/*
 * 0x8016FC14..0x8016FC70: draw a single course model when on screen.
 */

struct Vec3f {
    float x, y, z;
};

struct CourseModel {
    void *vtable;
    void *model;
};

extern "C" {
void Object_GetJObjPositionVec(void *, Vec3f *);
unsigned char fn_801379F0(Vec3f *, float);
void Object_RenderJObjTree(void *, int);

void fn_8016FC14(CourseModel *self) {
    Vec3f pos;

    if (self->model) {
        Object_GetJObjPositionVec(self->model, &pos);
        if (fn_801379F0(&pos, 450.0f)) {
            Object_RenderJObjTree(self->model, 7);
        }
    }
}

}
