extern void fn_802C84A4(void *p);

/* 0x800302EC, size 0x30. Conditional tail-call wrapper.
 * If scene3d->_28 != 0, call fn_802C84A4(scene3d->_04).
 * Has extab/extabindex entry (large-frame flag): emit via #pragma exceptions on/reset. */
#pragma exceptions on
void Scene3D_GetCameraPos(void *scene3d) {
    if (*(unsigned int *)((char *)scene3d + 0x28) != 0) {
        fn_802C84A4(*(void **)((char *)scene3d + 0x4));
    }
}
#pragma exceptions reset
