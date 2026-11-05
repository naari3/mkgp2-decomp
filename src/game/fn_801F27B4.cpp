/* Copies the two default menu-method tables into their live tables.
 * The original also registers this function in .ctors; this NonMatching
 * reconstruction leaves startup registration in the reference object. */
struct MenuReceiver801F;
typedef void (MenuReceiver801F::*MenuMethod801F)();
struct MenuMethodTable801F {
    MenuMethod801F method0;
    MenuMethod801F method1;
    MenuMethod801F method2;
    MenuMethod801F method3;
    MenuMethod801F method4;
    MenuMethod801F method5;
    MenuMethod801F method6;
    MenuMethod801F method7;
    MenuMethod801F method8;
    MenuMethod801F method9;
    MenuMethod801F method10;
    MenuMethod801F method11;
    MenuMethod801F method12;
    MenuMethod801F method13;
};
struct MenuMethodTables801F {
    char preceding[0x380];
    MenuMethodTable801F defaultsA, liveA, defaultsB, liveB;
};
extern "C" MenuMethodTables801F lbl_804E4C28;
extern "C" void fn_801F27B4() {
    MenuMethodTable801F first = lbl_804E4C28.defaultsA;
    lbl_804E4C28.liveA = first;
    MenuMethodTable801F second = lbl_804E4C28.defaultsB;
    lbl_804E4C28.liveB = second;
}
