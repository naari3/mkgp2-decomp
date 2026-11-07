/* fn_8024904C (0x8024904C): `this -= 8` adjustment thunk for the destructor of a
 * HUD object whose second base sits at +8. CW emits the thunk with the
 * class vtable, which the key function below forces into this TU; the
 * mangled names are mapped in tools/extab_user_renames.json.
 * NonMatching TU: the vtable and key function are extra objects here. */
struct RaceHudRootBase0 {
    int a;
    virtual void key();
};

struct RaceHudRootBase1 {
    virtual ~RaceHudRootBase1();
};

struct RaceHudRoot : RaceHudRootBase0, RaceHudRootBase1 {
    virtual void key();
    virtual ~RaceHudRoot();
};

void RaceHudRoot::key() { delete this; }
