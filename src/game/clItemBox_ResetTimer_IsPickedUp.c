/* clItemBox timer reset and picked-up state query. */

typedef struct clItemBox {
    unsigned char pad00[0x24];
    int state;   /* 0x24 */
    unsigned char pad28[0x4];
    float timer; /* 0x2C */
} clItemBox;

extern const float lbl_806D29A8;

void clItemBox_ResetTimer(clItemBox *self)
{
    self->timer = lbl_806D29A8;
}

int clItemBox_IsPickedUp(clItemBox *self)
{
    return self->state == 3;
}
