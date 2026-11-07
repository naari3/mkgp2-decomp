/* fn_8018E510: constructor of an object-view entry (ObjBase subclass that
 * holds an object pointer and a float, initialised to lbl_806D9438).
 * The mangled names are mapped in tools/extab_user_renames.json.
 * Only the ctor lives in this TU: the dtors are declared, not defined, so
 * no vtable/extab is emitted here.  EH-free, so the TU uses the
 * ctor-bridge rule in configure.py. */
struct ObjBase {
    virtual ~ObjBase();
};

struct ObjViewEntry : ObjBase {
    void *object;
    float value;
    ObjViewEntry(void *o);
    virtual void _key1();
};

extern const float lbl_806D9438;

ObjViewEntry::ObjViewEntry(void *o) : object(o), value(lbl_806D9438) {}
