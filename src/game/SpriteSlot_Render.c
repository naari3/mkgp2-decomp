extern void Object_RenderJObjTree(void *object, int flags);

void SpriteSlot_Render(void *object)
{
    Object_RenderJObjTree(object, 7);
}
