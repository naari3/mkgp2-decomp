/* Secondary-base adjustment thunks for the AI controller (0x801E8C90).
 * The controller's second base sits at +12; CW emits these `this -= 12`
 * thunks next to the class vtable. The key function below forces the vtable
 * (and so the thunks) into this TU; the mangled names are mapped to the
 * target symbols in tools/extab_user_renames.json.
 * CW emits the thunks in reverse base-vtable order, so AIBase1's virtuals
 * are declared last-to-first to lay them out 0x801E8C90..0x801E8CB0. */
struct AIBase0 {
    int a, b;
    virtual void key();
};

struct AIBase1 {
    virtual int f68B4(void *other);
    virtual int f66B4(void *other);
    virtual int f6670();
    virtual unsigned int GrantItem(int item, unsigned char force);
    virtual ~AIBase1();
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
