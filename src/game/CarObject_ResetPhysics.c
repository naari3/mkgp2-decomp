extern void fn_801999D0(int);

#pragma exceptions on
void CarObject_ResetPhysics(int self) {
    fn_801999D0(*(int *)((char *)self + 0x28));
}
#pragma exceptions reset
