#pragma readonly_strings on
typedef struct { float x, y, z; } V;
extern void use(void*, float, float, float);
extern void *Alloc(int);
extern void ini(void*, const char*, int);
extern float K;
typedef struct { int a; void *m[2]; } H;
void t1(H *h, float s) {
    static const V sc[2] = {{1,2,3},{4,5,6}};
    static const V rot = {7,8,9};
    int i;
    void *p = Alloc(0x20); if (p) ini(p, "a long string name one", 1); h->m[0] = p;
    p = Alloc(0x20); if (p) ini(p, "a long string name two", 1); h->m[1] = p;
    for (i = 0; i < 2; i++) {
        use(h->m[i], sc[i].x * s, sc[i].y * s, sc[i].z * s);
        use(h->m[i], K * rot.x, K * rot.y, K * rot.z);
    }
}
