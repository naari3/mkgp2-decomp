extern void Object_RenderJObjTree(void *jobj, int flags);

void TornadoEffect_RenderCallback(void *jobj)
{
    Object_RenderJObjTree(jobj, 7);
}
