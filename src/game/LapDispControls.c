/* Lap display timeout request and completion-state probe. */
typedef struct LapDispControls { int vt; int timer; int unused[4]; int state; } LapDispControls;
void fn_8023F76C(LapDispControls *p, int time) { if (p->state < 5) p->timer = time + 1; }
void fn_8023F784(LapDispControls *p) { if (p->state == 6) return; }
