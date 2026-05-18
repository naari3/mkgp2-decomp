/* EnemyRunType1_Init
 *
 * 0x801EC65C (size 0x3C, 15 instr). C++-style ctor: call
 * EnemyRun_BaseInit(self), set the vtable pointer at *self
 * (lbl_804E4C08), return self.
 *
 * Has an extab/extabindex entry with the "Large Frame: Yes" flag
 * (r31-save prologue), so wrap with #pragma exceptions on / reset
 * to let CW auto-emit the singleton extab + extabindex entries.
 */

extern void EnemyRun_BaseInit(void *self);
extern void *lbl_804E4C08[4];

#pragma exceptions on
void *EnemyRunType1_Init(void **self) {
    EnemyRun_BaseInit(self);
    *self = lbl_804E4C08;
    return self;
}
#pragma exceptions reset
