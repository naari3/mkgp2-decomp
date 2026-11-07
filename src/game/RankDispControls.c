/* NonMatching: secondary-base destructor thunk; C emits a call/return wrapper. */
extern void *dtor_80249274(void *, int);
void *fn_802494B4(void *p, int mode) { return dtor_80249274((char *)p - 8, mode); }
