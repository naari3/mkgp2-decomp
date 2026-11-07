/* fn_8020D1B8: `this -= 0x5c` adjustment thunk for the destructor of the
 * race-setup object (fn_8020CEE8), whose second base sits at +0x5c. CW emits
 * the thunk with the class vtable, which the key function below forces into
 * this TU; the mangled names are mapped in tools/extab_user_renames.json.
 * NonMatching TU: the vtable and key function are extra objects here. */
struct RaceSetupBase0 {
    char pad4[0x5c - 4];
    virtual void key();
};

struct RaceSetupBase1 {
    virtual ~RaceSetupBase1();
};

struct RaceSetupMI : RaceSetupBase0, RaceSetupBase1 {
    virtual void key();
    virtual ~RaceSetupMI();
};

void RaceSetupMI::key() { delete this; }
