/* fn_8018E510: constructor of an object-view entry (ObjBase subclass that
 * holds an object pointer and a float, initialised to lbl_806D9438).
 * The mangled names are mapped in tools/extab_user_renames.json.
 * NonMatching TU: the out-of-line dtor (key function) also emits the
 * vtable and an extab entry, which this TU does not own in the target. */
struct ObjBase {
    ObjBase() {}
    virtual ~ObjBase();
};

struct ObjViewEntry : ObjBase {
    ObjViewEntry(void *o);
    virtual ~ObjViewEntry();
    void *object;
    float value;
};

extern const float lbl_806D9438;

ObjViewEntry::ObjViewEntry(void *o) : object(o), value(lbl_806D9438) {}

ObjViewEntry::~ObjViewEntry() {}
