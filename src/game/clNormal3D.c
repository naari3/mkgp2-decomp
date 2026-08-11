typedef unsigned int u32;

typedef struct JObj JObj;
struct JObj {
    char pad0[8];
    JObj *next;
    char padC[4];
    JObj *child;
    u32 flags;
};

int clNormal3D_CountJObjs(void *self, JObj *jobj, int count)
{
    JObj *child;

    if (jobj != 0) {
        count++;
        if (!(jobj->flags & 0x1000)) {
            for (child = jobj->child; child != 0; child = child->next) {
                count = clNormal3D_CountJObjs(self, child, count);
            }
        }
    }
    return count;
}
