extern void fn_801999D0(int, int);

#pragma exceptions on
void CarObject_ResetPhysics(int self, int v) {
    fn_801999D0(*(int *)((char *)self + 0x28), v);
}
#pragma exceptions reset
