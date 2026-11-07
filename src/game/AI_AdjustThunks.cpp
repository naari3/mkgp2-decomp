/* Secondary-base adjustment thunks for the AI controller (0x801E8C90).
 * The controller's second base sits at +12; CW emits these `this -= 12`
 * thunks next to the class vtable. The key function below forces the vtable
 * (and so the thunks) into this TU; the mangled names are mapped to the
 * target symbols in tools/extab_user_renames.json.
 * NonMatching TU: the vtable and key function are extra objects here. */
struct AIBase0 {
    int a, b;
    virtual void key();
};

struct AIBase1 {
    virtual ~AIBase1();
    virtual unsigned int GrantItem(int item, unsigned char force);
    virtual int f6670();
    virtual int f66B4(void *other);
    virtual int f68B4(void *other);
};

struct AIController : AIBase0, AIBase1 {
    virtual void key();
    virtual ~AIController();
    virtual unsigned int GrantItem(int item, unsigned char force);
    virtual int f6670();
    virtual int f66B4(void *other);
    virtual int f68B4(void *other);
};

void AIController::key() { f6670(); }
