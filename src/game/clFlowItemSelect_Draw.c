/* clFlowItemSelect_Draw (0x801CBCAC). Local declaration order drives register allocation. */

extern void ItemDisplay_GetOrCreate(void);
extern void fn_801A0004(void *);
extern void fn_801F8A34(void *, void *, int);
extern void *fn_801F8E58(void);
extern void fn_8020AC34(void);
extern void fn_8023CD54(void *);
typedef struct {
    char pad[0x80]; void **slots[5]; char pad2[0x98-0x94]; void *grid[3][4]; char pad3[0xE8-0xC8]; void *xE8; } FIS;
#pragma exceptions on
void clFlowItemSelect_Draw(FIS *self) {
    int k;
    void *ctx;
    int i;
    int j;

    for (k = 0; k < 5; k++) {
        if (self->slots[k]) fn_801A0004(*self->slots[k]);
    }
    ctx = fn_801F8E58();
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) fn_801F8A34(ctx, self->grid[i][j], 5);
    }
    fn_8023CD54(self->xE8);
    ItemDisplay_GetOrCreate();
    fn_8020AC34();
}
#pragma exceptions reset
