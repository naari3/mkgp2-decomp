struct Vec3f {
    float x, y, z;
};

struct clPathNode {
    Vec3f a;
    Vec3f b;
    Vec3f c;
    Vec3f d;
    int x30;
    clPathNode *next;

    clPathNode() {
        next = 0;
        a.x = 0.0f;
        a.y = 0.0f;
        a.z = 0.0f;
        b.x = 0.0f;
        b.y = 0.0f;
        b.z = 0.0f;
        c.x = 0.0f;
        c.y = 0.0f;
        c.z = 0.0f;
        d.x = 0.0f;
        d.y = 0.0f;
        d.z = 0.0f;
        x30 = 0;
    }
    void Append(clPathNode *n);
};

extern "C" {
extern clPathNode *lbl_806D163C;
extern clPathNode *lbl_806D1640;
}

extern "C" int fn_8017E6A8(void) {
    clPathNode *n = new clPathNode;
    if (n != 0) {
        if (lbl_806D163C == 0) {
            lbl_806D163C = n;
        } else {
            lbl_806D163C->Append(n);
        }
        lbl_806D1640 = n;
        return 1;
    }
    return 0;
}
