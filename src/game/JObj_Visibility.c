/* JObj_Show / JObj_Hide
 *
 * 0x800316B8 (size 0x30) and 0x800316E8 (size 0x30). Conditional tail-call
 * wrappers around HSD_JObj show/hide implementations.
 *
 * Calling convention quirk: r3 (first arg) is passed in but unused, and the
 * callee is invoked with the JObj pointer in r3 and flags in r4. To reproduce
 * this CW codegen, declare a leading unused argument so the parameters land in
 * r4 / r5 and CW emits the mr r3,r4 / mr r4,r5 shift before the bl.
 *
 * Both fns have extab/extabindex entries with the "Large Frame: Yes" flag, so
 * emit via #pragma exceptions on / reset.
 */

extern void fn_802D0BE4(void *jobj, unsigned int flags);
extern void fn_802D0870(void *jobj, unsigned int flags);

#pragma exceptions on
void JObj_Show(void *unused, void *jobj, unsigned int flags) {
    if (jobj != 0) {
        fn_802D0BE4(jobj, flags);
    }
}

void JObj_Hide(void *unused, void *jobj, unsigned int flags) {
    if (jobj != 0) {
        fn_802D0870(jobj, flags);
    }
}
#pragma exceptions reset
