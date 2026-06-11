extern int src(void);
extern void sink5(int,int,int,int,int);
/* R0: volatile clique - 5 webs all live at sink, NONE crossing a call
 * (defined by cheap exprs from a param array). Reveals volatile-pool order. */
int r0_vol_clique(int *p){
    int a=p[0]^1, b=p[1]^2, c=p[2]^3, d=p[3]^4, e=p[4]^5;
    sink5(a,b,c,d,e); return a+b+c+d+e;
}
/* R1: decl order d,c,b,a (reverse names) but def order via calls in that decl
 * order; arg order a,b,c,d. If decl-order rule: d=r31. */
int r1_declrev(void){
    int d=src(), c=src(), b=src(), a=src();
    sink5(a,b,c,d,0); return 0;
}
