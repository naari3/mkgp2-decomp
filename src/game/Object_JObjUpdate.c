/* Small Object wrappers around the HSD_JObj flag update helpers. */

extern void fn_802D0BE4(void *jobj, unsigned int flags);
extern void fn_802D0870(void *jobj, unsigned int flags);

typedef struct ObjectJObjView {
    unsigned char pad[0x2C];
    void *jobj;
} ObjectJObjView;

#pragma exceptions on
void Object_JObjUpdate_be4(ObjectJObjView *object, unsigned int flags) {
    if (object->jobj != 0) {
        fn_802D0BE4(object->jobj, flags);
    }
}

void Object_JObjUpdate_870(ObjectJObjView *object, unsigned int flags) {
    if (object->jobj != 0) {
        fn_802D0870(object->jobj, flags);
    }
}
#pragma exceptions reset
