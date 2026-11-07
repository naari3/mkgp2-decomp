/* fn_80248CE4 (0x80248CE4): `this -= 8` adjustment thunk for the destructor of a
 * HUD object whose second base sits at +8. CW emits the thunk with the
 * class vtable, which the key function below forces into this TU; the
 * mangled names are mapped in tools/extab_user_renames.json.
 * NonMatching TU: the vtable and key function are extra objects here. */
struct HudThunkBBase0 {
    int a;
    virtual void key();
};

struct HudThunkBBase1 {
    virtual ~HudThunkBBase1();
};

struct HudThunkB : HudThunkBBase0, HudThunkBBase1 {
    virtual void key();
    virtual ~HudThunkB();
};

void HudThunkB::key() { delete this; }
