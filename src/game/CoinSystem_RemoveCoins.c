/* CoinSystem_RemoveCoins (0x8013A5BC): take up to `n` coins away from
 * `owner`. Coins in state 4 that belong to the owner are counted; every coin
 * of the owner then loses that many from its counter, and coins whose counter
 * drops below zero are released (state 5) with staggered timers following the
 * already released ones. Stores the number of coins the owner still holds in
 * owner+0x2CC and returns the number removed. */

typedef struct Coin {
    int active;                /* 0x00 */
    unsigned char pad04[0xC];
    struct CoinOwner *owner;   /* 0x10 */
    int count;                 /* 0x14 */
    int state;                 /* 0x18 */
    float timer;               /* 0x1C */
    unsigned char pad20[0x14];
    float t34;                 /* 0x34 */
    unsigned char pad38[0x88];
} Coin;

typedef struct CoinOwner {
    unsigned char pad000[0x2CC];
    int coinsHeld; /* 0x2CC */
} CoinOwner;

extern Coin *lbl_806D1534;
extern int lbl_806D1538;

int CoinSystem_RemoveCoins(CoinOwner *owner, int n)
{
    int removed;
    int held;
    float t;
    Coin *c;

    if (lbl_806D1538 == 0) {
        return 0;
    }
    if (owner == 0 || n <= 0) {
        return 0;
    }
    removed = 0;
    held = 0;
    t = 0.0f;
    for (c = lbl_806D1534; c < lbl_806D1534 + lbl_806D1538; c++) {
        if (c->owner == owner) {
            if (c->state == 4) {
                removed++;
            } else if (c->state == 5 && c->timer >= t) {
                t = 5.0f + c->timer;
            }
        }
    }
    if (removed > n) {
        removed = n;
    }
    for (c = lbl_806D1534; c < lbl_806D1534 + lbl_806D1538; c++) {
        if (c->owner == owner && c->count >= 0) {
            c->count -= removed;
            if (c->count < 0) {
                c->active = 1;
                c->state = 5;
                c->timer = t;
                c->t34 = 0.0f;
                t += 5.0f;
            } else {
                held++;
            }
        }
    }
    owner->coinsHeld = held;
    return removed;
}
