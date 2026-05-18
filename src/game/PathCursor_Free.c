extern void dtor_8003AFB8(void *p);

#pragma exceptions on
void *PathCursor_Free(void *p, short should_delete) {
    if ((p != 0) && (0 < should_delete)) {
        dtor_8003AFB8(p);
    }
    return p;
}
#pragma exceptions reset
