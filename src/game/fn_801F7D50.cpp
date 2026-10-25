/* Holder constructor: allocates its owned object with new. */
struct Obj801F7D50 {
    char pad_0[0x14];
    Obj801F7D50(int arg);
};

struct Holder801F7D50 {
    Obj801F7D50 *p;
    Holder801F7D50(int arg);
};

Holder801F7D50::Holder801F7D50(int arg) {
    p = new Obj801F7D50(arg);
}
