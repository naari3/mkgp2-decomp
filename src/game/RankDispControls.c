/* Rank display controls. NonMatching: secondary-base destructor thunk. */
typedef struct RankDispControls { int vt; int request; int unused[3]; int state; } RankDispControls;
extern void *dtor_80249274(void *, int);
void *fn_802494B4(void *p, int mode) { return dtor_80249274((char *)p - 8, mode); }
void fn_802494BC(RankDispControls *p) { if (p->state < 4) p->request = 1; }
void fn_802494D4(RankDispControls *p) { if (p->state == 8) return; }
