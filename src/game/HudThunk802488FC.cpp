/* fn_802488FC (0x802488FC): `this -= 8` adjustment thunk for the destructor of a
 * HUD object whose second base sits at +8. CW emits the thunk with the
 * class vtable, which the key function below forces into this TU; the
 * mangled names are mapped in tools/extab_user_renames.json.
 * NonMatching TU: the vtable and key function are extra objects here. */
struct HudThunkABase0 {
    int a;
    virtual void key();
};

struct HudThunkABase1 {
    virtual ~HudThunkABase1();
};

struct HudThunkA : HudThunkABase0, HudThunkABase1 {
    virtual void key();
    virtual ~HudThunkA();
};

void HudThunkA::key() { delete this; }
