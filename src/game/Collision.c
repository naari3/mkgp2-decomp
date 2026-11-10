extern void *g_collisionData[2];

void Collision_SetGlobalData(void *a, void *b) {
    g_collisionData[0] = a;
    g_collisionData[1] = b;
}
