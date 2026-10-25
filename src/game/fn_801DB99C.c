typedef struct Obj {
    unsigned char pad_0[0xC];
    int f_C;
} Obj;

extern void Waypoint_FindNearest(int, int);

void fn_801DB99C(void *p0, int p1) {
    Waypoint_FindNearest(((Obj *)p0)->f_C, 0);
}
