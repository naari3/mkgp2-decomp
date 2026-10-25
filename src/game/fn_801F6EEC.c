typedef struct Spinner {
    char pad00[0x8];
    float sinA;
    float cosA;
    char pad10[0x38 - 0x10];
    float angle;
} Spinner;

extern double sin(double);
extern double cos(double);

void fn_801F6EEC(Spinner *self, float angle)
{
    self->angle = angle;
    while (self->angle > 6.283184f) {
        self->angle -= 6.283184f;
    }
    while (self->angle < 0.0f) {
        self->angle += 6.283184f;
    }
    self->sinA = sin(self->angle);
    self->cosA = -(float)cos(self->angle);
}
