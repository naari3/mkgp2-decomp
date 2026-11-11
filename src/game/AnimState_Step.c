/* AnimState (0x800AE854..0x800AF088): keyframed parameter tracks.
 * Step, Init and all owned sections match (objdiff, 2026-11-09).
 * The counter initializer emits Init's templates before Step's. The entry
 * walker keeps its stream offset separate from the caller's track/scalar
 * counters, preserving the original zero sharing and counter initialization.
 */
#include "game/AnimState_Step_private.h"

#include "game/types/Vec.h"

#include "game/types/AnimEntry.h"

#include "game/types/AnimState.h"

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
        s->pos[a[0]++].x = v;
        break;
    case 3:
        s->pos[a[1]++].y = v;
        break;
    case 4:
        s->pos[a[2]++].z = v;
        break;
    case 5:
        s->rot[b[0]++].x = BuildOrientationFromYaw(v);
        break;
    case 6:
        s->rot[b[1]++].y = BuildOrientationFromYaw(v);
        break;
    case 7:
        s->rot[b[2]++].z = BuildOrientationFromYaw(v);
        break;
    case 8:
        s->scale[c[0]++].x = v;
        break;
    case 9:
        s->scale[c[1]++].y = v;
        break;
    case 10:
        s->scale[c[2]++].z = v;
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
            switch (s->timerOn[i]) {
            case 0:
                t = 0.0f;
                key = 0;
                break;
            case 2:
                t = 0.0f;
                key = s->keyCount[i] - 1;
                break;
            case 1:
                s->timer[i] += s->weight;
                n = s->keyCount[i];
                for (m = 0; m < n; m++) {
                    if ((float)((int *)e->data)[m] <= s->timer[i]) {
                        key = m;
                    }
                }
                if (n - 1 <= key) {
                    t = 0.0f;
                    if (s->lastKey[i] == -2) {
                        s->timerOn[i] = 3;
                    } else {
                        s->timerOn[i] = 2;
                    }
                } else {
                    int first;
                    data = (int *)e->data;
                    first = data[key];
                    t = (s->timer[i] - (float)first) * (1.0f / (float)(data[key + 1] - first));
                }
                break;
            case 3:
                s->timerOn[i] = 1;
                key = 0;
                t = s->timer[i] = 0.0f;
                break;
            }
            if (res == -1) {
                if (*(char *)&s->timerOn[i] == 1) {
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
                s->current = ((int *)e->data)[key];
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

static inline void AnimState_InitEntries(AnimState *s, AnimEntry *entries,
                                         signed char *n, signed char *j)
{
    AnimEntry *e;
    int k;
    AnimCounter c, b, a;

    k = 0;
    AnimState_InitCounters(&a, &b, &c);

    e = entries;
    while (e->type != 13) {
        switch ((signed char)e->type) {
        case 0:
            for (s->keyCount[*n] = 0;
                 ((int *)e->data)[s->keyCount[*n]] != -1 && ((int *)e->data)[s->keyCount[*n]] != -2;
                 s->keyCount[*n]++) {
            }
            s->lastKey[*n] = ((int *)e->data)[s->keyCount[*n]];
            s->timerOn[*n] = 1;
            (*n)++;
            break;
        case 1:
            s->current = *(int *)e->data;
            break;
        case 2:
            s->pos[a.v[0]++].x = *(float *)e->data;
            break;
        case 3:
            s->pos[a.v[1]++].y = *(float *)e->data;
            break;
        case 4:
            s->pos[a.v[2]++].z = *(float *)e->data;
            break;
        case 5:
            s->rot[b.v[0]++].x = *(float *)e->data;
            break;
        case 6:
            s->rot[b.v[1]++].y = *(float *)e->data;
            break;
        case 7:
            s->rot[b.v[2]++].z = *(float *)e->data;
            break;
        case 8:
            s->scale[c.v[0]++].x = *(float *)e->data;
            break;
        case 9:
            s->scale[c.v[1]++].y = *(float *)e->data;
            break;
        case 10:
            s->scale[c.v[2]++].z = *(float *)e->data;
            break;
        case 11:
            s->d[(*j)++] = *(float *)e->data;
            break;
        case 12:
            s->value4 = (int)e->data;
            break;
        }
        k += sizeof(AnimEntry);
        e = (AnimEntry *)((unsigned int)entries + k);
    }
}

void AnimState_Init(AnimState *s, AnimEntry *entries)
{
    int i;

    s->entries = entries;
    s->value4 = 0;
    for (i = 0; i < 8; i++) {
        s->timer[i] = 0.0f;
        s->keyCount[i] = 0;
        s->lastKey[i] = 0;
        s->timerOn[i] = 0;
    }
    if (entries != 0) {
        signed char n = 0;
        signed char j = 0;
        AnimState_InitEntries(s, entries, &n, &j);
    }
}
