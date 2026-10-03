/* Observed JObj links; no complete SDK layout is implied. */
typedef unsigned int u32;
typedef struct JObj JObj;
struct JObj {
    char pad0[8];
    JObj* next;
    char padC[4];
    JObj* child;
    u32 flags;
};

int clNormal3D_FlattenJObjTree(JObj* jobj, JObj** table, int index)
{
    JObj* child;
    if (jobj != 0) {
        table[index++] = jobj;
        if (!(jobj->flags & 0x1000)) {
            for (child = jobj->child; child != 0; child = child->next) {
                index = clNormal3D_FlattenJObjTree(child, table, index);
            }
        }
    }
    return index;
}
