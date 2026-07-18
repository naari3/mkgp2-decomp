typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void Vec3_Copy(Vec3 *dst, const Vec3 *src);

void ItemObject_WritePositionTo(void *item, const Vec3 *position)
{
    if (item != 0) {
        Vec3_Copy((Vec3 *)((char *)item + 0xA0), position);
    }
}

void ItemObject_WriteVec3At0x190To(void *item, const Vec3 *value)
{
    if (item != 0) {
        Vec3_Copy((Vec3 *)((char *)item + 0x190), value);
    }
}
