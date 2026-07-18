typedef struct Object {
    unsigned char pad[0x24];
    void *anim_resource;
} Object;

extern void Object_ReleaseAnimResource_Impl(void *anim_resource);

void Object_ReleaseAnimResource(Object *object)
{
    if (object->anim_resource != 0) {
        Object_ReleaseAnimResource_Impl(object->anim_resource);
    }
}
