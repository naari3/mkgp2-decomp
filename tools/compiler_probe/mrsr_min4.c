/* mr-SR-init probe TU #4: replicate the clNormal3D_Exec / OSInitAlloc
 * compiler-created byte-IV mr inits, then bisect the trigger. */

#pragma exceptions off

typedef struct Obj {
    char pad0[0x20];
    void *list20;        /* 0x20 */
    char pad24[0x1c];
    void **table;        /* 0x40 */
    int count;           /* 0x44 */
} Obj;

extern void extfn(void *p, int flags);

/* o1: clNormal3D window-190 shape: ptr table, stride 4, call in body */
void o1_clnormal(Obj *self) {
    int i;
    for (i = 0; i < self->count; i++) {
        if (self->table[i]) {
            extfn(self->table[i], 0x20000);
        }
    }
}

/* o2: same loop, no call (pure flag set) */
void o2_nocall(Obj *self) {
    int i;
    for (i = 0; i < self->count; i++) {
        if (self->table[i]) {
            *(int *)self->table[i] = 1;
        }
    }
}

/* o3: OSInitAlloc exact shape */
typedef struct Heap { int size; void *free; void *allocated; } Heap;
extern Heap *HeapArray;
extern int NumHeaps;
void o3_osinitalloc(void) {
    int i;
    for (i = 0; i < NumHeaps; i++) {
        Heap *heap = &HeapArray[i];
        heap->size = -1;
        heap->free = heap->allocated = (void *)0;
    }
}

/* o4: stride-8 version of o1 (struct elements, float read + call) */
typedef struct Pair { float key; float value; } Pair;
typedef struct Obj8 {
    char pad0[0x40];
    Pair *pairs;  /* 0x40 */
    int count;    /* 0x44 */
} Obj8;
extern void extfnf(float f);
void o4_stride8(Obj8 *self) {
    int i;
    for (i = 0; i < self->count; i++) {
        if (self->pairs[i].key > 0.0f) {
            extfnf(self->pairs[i].value);
        }
    }
}

/* o5: o1 with stride 8 ptr table (every other entry) - index expr i*8 once */
void o5_stride8once(Obj8 *self) {
    int i;
    for (i = 0; i < self->count; i++) {
        extfnf(self->pairs[i].key);
    }
}
