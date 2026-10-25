/* ItemObject_CheckKartCollision (0x800D78FC): item sphere vs kart cone hull.
 * The kart is a vertical cone of height 60*scale whose radius blends from
 * 10*scale*k at the base to 40*scale*k at the top. On contact, item kinds
 * 1..3 are knocked upward and remember the kart; kind 4 stops the kart. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5A80; /* 60.0 */
extern const float lbl_806D5A84; /* 10.0 */
extern const float lbl_806D5A88; /* 40.0 */
extern const float lbl_806D5A8C; /* 0.0 */
extern const float lbl_806D5A90; /* 1.0 */
extern float Vec3_HorizontalDistance(const Vec *a, const Vec *b);

void ItemObject_CheckKartCollision(unsigned char *kart, unsigned char *item)
{
    Vec kartPos;
    Vec itemPos;
    float kartY;
    float height;
    float baseR;
    float topR;
    float itemR;
    float y;
    float scale;
    float k;
    float itemY;
    float top;
    float dist;

    if (kart == 0 || item == 0) {
        return;
    }

    Vec3_Copy(&kartPos, (Vec *)(kart + 0xA0));
    scale = *(float *)(kart + 0xC4);
    k = *(float *)(kart + 0x10C);
    height = lbl_806D5A80 * scale;
    baseR = k * (lbl_806D5A84 * scale);
    topR = k * (lbl_806D5A88 * scale);
    Vec3_Copy(&itemPos, (Vec *)(item + 0xCC));

    kartY = kartPos.y;
    itemR = *(float *)(item + 0xD8);
    itemY = itemPos.y;
    top = kartY + height;
    if (top < itemY - itemR) {
        return;
    }
    if (itemY + itemR < kartY) {
        return;
    }
    if (top < itemY) {
        y = top;
    } else if (itemY < kartY) {
        y = kartY;
    } else {
        y = itemY;
    }

    dist = Vec3_HorizontalDistance(&kartPos, &itemPos);
    if (lbl_806D5A8C < dist - ((topR - baseR) / height * (y - kartY) + baseR) - itemR) {
        return;
    }

    {
        if ((signed char)item[0x8C] == 1 || (signed char)item[0x8C] == 2 || (signed char)item[0x8C] == 3) {
            item[0x8D] = 2;
            item[0x8E] = 2;
            GetSpawnPosition((Vec *)(item + 0x90), lbl_806D5A8C, lbl_806D5A90, lbl_806D5A8C);
            *(unsigned char **)(item + 0x9C) = kart;
        } else if ((signed char)item[0x8C] == 4) {
            kart[0x8D] = 2;
            kart[0x8E] = 1;
            GetSpawnPosition((Vec *)(kart + 0x90), lbl_806D5A8C, lbl_806D5A8C, lbl_806D5A8C);
        }
    }
}
