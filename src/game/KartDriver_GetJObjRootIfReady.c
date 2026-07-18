typedef struct KartDriverJObjView {
    void *root;
    char pad4[8];
    void *ready;
} KartDriverJObjView;

void *KartDriver_GetJObjRootIfReady(KartDriverJObjView *self)
{
    void *root = self->root;

    if (root == 0 || self->ready == 0) {
        return 0;
    }
    return root;
}
