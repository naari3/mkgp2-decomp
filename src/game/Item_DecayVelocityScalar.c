extern const float lbl_806D5AF8;
extern const float lbl_806D5AFC;

void Item_DecayVelocityScalar(void *item, float scalar)
{
    if (item != 0) {
        float *velocity = (float *)((char *)item + 0xC4);
        *velocity = lbl_806D5AF8 * *velocity + lbl_806D5AFC * scalar;
    }
}
