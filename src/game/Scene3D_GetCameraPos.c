extern void HSD_CObjGetPerspective(void *p);

/* 0x800302EC, size 0x30. Conditional tail-call wrapper.
 * If scene3d->_28 != 0, call HSD_CObjGetPerspective(scene3d->_04).
 * Has extab/extabindex entry (large-frame flag): emit via #pragma exceptions on/reset. */
#pragma exceptions on
void Scene3D_GetCameraPos(void *scene3d) {
    if (*(unsigned int *)((char *)scene3d + 0x28) != 0) {
        HSD_CObjGetPerspective(*(void **)((char *)scene3d + 0x4));
    }
}
#pragma exceptions reset
