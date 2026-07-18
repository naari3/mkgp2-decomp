extern void *g_playerCarObject;

extern void DebugOverlay_KartPhysics(void *physics);

void DebugOverlay_KartPhysicsForLocalPlayer(void) {
    if (g_playerCarObject != 0) {
        DebugOverlay_KartPhysics(*(void **)((char *)g_playerCarObject + 0x28));
    }
}
