/* BananaField_CheckCollision (0x80196C5C): tests each idle banana against the kart
 * and starts its hit animation. */

typedef struct { float x, y, z; } Vec;
typedef struct {
    int state;
    float x, y, z;
    float angle;
    float timer;
} Banana;
typedef struct {
    unsigned int active;
    Banana *items;
    int count;
    unsigned char hit;
} BananaField;

extern int g_characterId;
extern const float lbl_806D95B8;
extern const float lbl_806D95BC;
extern const float lbl_806D95D0;
extern const float lbl_806D95D8;
extern unsigned char BananaField_TestHitBox(int chara, void *kart, Vec *pos);
extern double atan2(double, double);

#pragma exceptions on
void BananaField_CheckCollision(BananaField *self, char *kart) {
    Banana *b;
    Vec pos;

    if (self->active == 0 || self->items == 0 || self->count == 0) {
        return;
    }
    self->hit = 0;
    for (b = self->items; b < self->items + self->count; b++) {
        if (b->state == 0) {
            pos.x = b->x;
            pos.y = lbl_806D95D0 + b->y;
            pos.z = b->z;
            if (BananaField_TestHitBox(g_characterId, kart, &pos)) {
                self->hit = 1;
                b->state = 1;
                b->timer = lbl_806D95B8;
                b->angle = atan2(*(float *)(kart + 0xC) - b->x, *(float *)(kart + 0x2C) - b->z);
            }
        } else if (b->state == 1) {
            b->timer += lbl_806D95BC;
            if (b->timer > lbl_806D95D8) {
                b->state = 2;
            }
        }
    }
}
#pragma exceptions reset
