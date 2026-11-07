/* Rank display controls following the secondary-base destructor thunk. */
typedef struct RankDispControls { int vt; int request; int unused[3]; int state; } RankDispControls;
void fn_802494BC(RankDispControls *p) { if (p->state < 4) p->request = 1; }
void fn_802494D4(RankDispControls *p) { if (p->state == 8) return; }
