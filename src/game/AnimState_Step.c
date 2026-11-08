/* AnimState (0x800AE854..0x800AF088): keyframed parameter tracks.
 * NonMatching: Step 100%, Init 98.867% (objdiff, 2026-11-08).
 * The counter initializer below emits Init's templates before Step's,
 * preserving the original .sbss2 order without changing the instructions.
 * Init still emits an extra zero load before clearing its track state.
 * Opposite text/template orders prevent splitting Step into a separate TU.
 */
#include "game/AnimState_Step_private.h"

typedef struct Vec { float x, y, z; } Vec;

typedef struct AnimEntry {
    char type;
    unsigned char pad[3];
    void *data;
} AnimEntry;

typedef struct AnimState {
    AnimEntry *entries;     /* 0x00 */
    int value4;             /* 0x04 */
    float time[8];          /* 0x08 */
    float speed;            /* 0x28 */
    signed char keyCount[8];  /* 0x2C */
    signed char lastKey[8];   /* 0x34 */
    signed char state[8];     /* 0x3C */
    int value44;            /* 0x44 */
    Vec a[4];               /* 0x48 */
    Vec b[4];               /* 0x78 */
    Vec c[4];               /* 0xA8 */
    float d[8];             /* 0xD8 */
} AnimState;

extern float BuildOrientationFromYaw(float yaw);

static inline void AnimState_InitCounters(AnimCounter *a, AnimCounter *b, AnimCounter *c)
{
    AnimCounter av = {{0}};
    AnimCounter bv = {{0}};
    AnimCounter cv = {{0}};
    *a = av;
    *b = bv;
    *c = cv;
}

static inline void AnimState_Apply(AnimState *s, AnimEntry *e, char type,
                                   signed char key, float t, signed char *a,
                                   signed char *b, signed char *c, signed char *j)
{
    float v;
    if (t == 0.0f) {
        v = ((float *)e->data)[key];
    } else {
        v = ((float *)e->data)[key] + t * (((float *)e->data)[key + 1] - ((float *)e->data)[key]);
    }
    switch ((signed char)type) {
    case 2:
        s->a[a[0]++].x = v;
        break;
    case 3:
        s->a[a[1]++].y = v;
        break;
    case 4:
        s->a[a[2]++].z = v;
        break;
    case 5:
        s->b[b[0]++].x = BuildOrientationFromYaw(v);
        break;
    case 6:
        s->b[b[1]++].y = BuildOrientationFromYaw(v);
        break;
    case 7:
        s->b[b[2]++].z = BuildOrientationFromYaw(v);
        break;
    case 8:
        s->c[c[0]++].x = v;
        break;
    case 9:
        s->c[c[1]++].y = v;
        break;
    case 10:
        s->c[c[2]++].z = v;
        break;
    case 11:
        s->d[(*j)++] = v;
        break;
    }
}

int AnimState_Step(AnimState *s)
{
    signed char i;
    signed char j;
    signed char key;
    signed char res;
    int k;
    AnimEntry *e;
    signed char n;
    int m;
    float t;
    int *data;

    if (s->entries == 0) {
        return 0;
    }
    {
    signed char a[3] = {0};
    signed char b[3] = {0};
    signed char c[3] = {0};

    e = s->entries;
    k = 0;
    i = 0;
    j = 0;
    res = -1;
    while (e->type != 13) {
        if ((signed char)e->type == 0) {
            switch (s->state[i]) {
            case 0:
                t = 0.0f;
                key = 0;
                break;
            case 2:
                t = 0.0f;
                key = s->keyCount[i] - 1;
                break;
            case 1:
                s->time[i] += s->speed;
                n = s->keyCount[i];
                for (m = 0; m < n; m++) {
                    if ((float)((int *)e->data)[m] <= s->time[i]) {
                        key = m;
                    }
                }
                if (n - 1 <= key) {
                    t = 0.0f;
                    if (s->lastKey[i] == -2) {
                        s->state[i] = 3;
                    } else {
                        s->state[i] = 2;
                    }
                } else {
                    int first;
                    data = (int *)e->data;
                    first = data[key];
                    t = (s->time[i] - (float)first) * (1.0f / (float)(data[key + 1] - first));
                }
                break;
            case 3:
                s->state[i] = 1;
                key = 0;
                t = s->time[i] = 0.0f;
                break;
            }
            if (res == -1) {
                if (*(char *)&s->state[i] == 1) {
                    res = 0;
                } else {
                    res = 1;
                }
            }
            i++;
        }
        if (i == 0) {
            switch ((signed char)e->type) {
            case 2:
                a[0]++;
                break;
            case 3:
                a[1]++;
                break;
            case 4:
                a[2]++;
                break;
            case 5:
                b[0]++;
                break;
            case 6:
                b[1]++;
                break;
            case 7:
                b[2]++;
                break;
            case 8:
                c[0]++;
                break;
            case 9:
                c[1]++;
                break;
            case 10:
                c[2]++;
                break;
            case 11:
                j++;
                break;
            }
        } else if ((signed char)e->type != 12) {
            if ((signed char)e->type == 1) {
                s->value44 = ((int *)e->data)[key];
            } else {
                AnimState_Apply(s, e, e->type, key, t, a, b, c, &j);
            }
        }
        k++;
        /* Keep address arithmetic in the stream's 32-bit address domain. */
        e = (AnimEntry *)((unsigned int)s->entries + k * sizeof(AnimEntry));
    }
    }
    return res != 0;
}

void AnimState_Init(AnimState *s, AnimEntry *entries)
{
    int i;
    int k;
    AnimEntry *e;
    signed char n;
    signed char j;

    k = 0;
    s->entries = entries;
    s->value4 = 0;
    for (i = 0; i < 8; i++) {
        s->time[i] = 0.0f;
        s->keyCount[i] = 0;
        s->lastKey[i] = 0;
        s->state[i] = 0;
    }
    if (entries != 0) {
        AnimCounter a, b, c;
        AnimState_InitCounters(&a, &b, &c);

        n = 0;
        j = 0;
        e = entries;
        while (e->type != 13) {
            switch ((signed char)e->type) {
            case 0:
                for (s->keyCount[n] = 0;
                     ((int *)e->data)[s->keyCount[n]] != -1 && ((int *)e->data)[s->keyCount[n]] != -2;
                     s->keyCount[n]++) {
                }
                s->lastKey[n] = ((int *)e->data)[s->keyCount[n]];
                s->state[n] = 1;
                n++;
                break;
            case 1:
                s->value44 = *(int *)e->data;
                break;
            case 2:
                s->a[a.v[0]++].x = *(float *)e->data;
                break;
            case 3:
                s->a[a.v[1]++].y = *(float *)e->data;
                break;
            case 4:
                s->a[a.v[2]++].z = *(float *)e->data;
                break;
            case 5:
                s->b[b.v[0]++].x = *(float *)e->data;
                break;
            case 6:
                s->b[b.v[1]++].y = *(float *)e->data;
                break;
            case 7:
                s->b[b.v[2]++].z = *(float *)e->data;
                break;
            case 8:
                s->c[c.v[0]++].x = *(float *)e->data;
                break;
            case 9:
                s->c[c.v[1]++].y = *(float *)e->data;
                break;
            case 10:
                s->c[c.v[2]++].z = *(float *)e->data;
                break;
            case 11:
                s->d[j++] = *(float *)e->data;
                break;
            case 12:
                s->value4 = (int)e->data;
                break;
            }
            k += sizeof(AnimEntry);
            e = (AnimEntry *)((unsigned int)entries + k);
        }
    }
}
