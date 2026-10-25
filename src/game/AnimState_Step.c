/* AnimState (0x800AE854..0x800AF088): keyframed parameter tracks. Init scans
 * the entry list (terminated by type 13) and sets up the key sequences; Step
 * advances each sequence and writes the interpolated values back.
 * NonMatching: Step ~98% (callee-saved register permutation: the target keeps
 * the entry offset in r25 below `s`), Init ~93% (the target keeps `entries`
 * and the byte offset in separate registers instead of a moving pointer). */
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

int AnimState_Step(AnimState *s)
{
    signed char res;
    signed char key;
    signed char j;
    signed char i;
    int k;
    AnimEntry *e;
    signed char n;
    int m;
    float t;
    float v;
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
                    data = (int *)e->data;
                    t = (s->time[i] - (float)data[key]) * (1.0f / (float)(data[key + 1] - data[key]));
                }
                break;
            case 3:
                s->state[i] = 1;
                key = 0;
                t = 0.0f;
                s->time[i] = 0.0f;
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
                if (t == 0.0f) {
                    v = ((float *)e->data)[key];
                } else {
                    v = ((float *)e->data)[key] + t * (((float *)e->data)[key + 1] - ((float *)e->data)[key]);
                }
                switch ((signed char)e->type) {
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
                    s->d[j++] = v;
                    break;
                }
            }
        }
        k++;
        e = &s->entries[k];
    }
    }
    return res != 0;
}

void AnimState_Init(AnimState *s, AnimEntry *entries)
{
    int i;
    int k;
    signed char n;
    signed char j;

    s->entries = entries;
    s->value4 = 0;
    for (i = 0; i < 8; i++) {
        s->time[i] = 0.0f;
        s->keyCount[i] = 0;
        s->lastKey[i] = 0;
        s->state[i] = 0;
    }
    if (entries != 0) {
        signed char a[3] = {0};
        signed char b[3] = {0};
        signed char c[3] = {0};

        n = 0;
        j = 0;
        k = 0;
        while (entries[k].type != 13) {
            switch ((signed char)entries[k].type) {
            case 0:
                for (s->keyCount[n] = 0;
                     ((int *)entries[k].data)[s->keyCount[n]] != -1 && ((int *)entries[k].data)[s->keyCount[n]] != -2;
                     s->keyCount[n]++) {
                }
                s->lastKey[n] = ((int *)entries[k].data)[s->keyCount[n]];
                s->state[n] = 1;
                n++;
                break;
            case 1:
                s->value44 = *(int *)entries[k].data;
                break;
            case 2:
                s->a[a[0]++].x = *(float *)entries[k].data;
                break;
            case 3:
                s->a[a[1]++].y = *(float *)entries[k].data;
                break;
            case 4:
                s->a[a[2]++].z = *(float *)entries[k].data;
                break;
            case 5:
                s->b[b[0]++].x = *(float *)entries[k].data;
                break;
            case 6:
                s->b[b[1]++].y = *(float *)entries[k].data;
                break;
            case 7:
                s->b[b[2]++].z = *(float *)entries[k].data;
                break;
            case 8:
                s->c[c[0]++].x = *(float *)entries[k].data;
                break;
            case 9:
                s->c[c[1]++].y = *(float *)entries[k].data;
                break;
            case 10:
                s->c[c[2]++].z = *(float *)entries[k].data;
                break;
            case 11:
                s->d[j++] = *(float *)entries[k].data;
                break;
            case 12:
                s->value4 = (int)entries[k].data;
                break;
            }
            k++;
        }
    }
}
