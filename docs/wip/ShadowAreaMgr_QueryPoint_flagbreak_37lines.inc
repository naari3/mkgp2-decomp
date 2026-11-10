static inline const Vec3f &ShadowAreaMgr_GetEdgePoint(ShadowAreaMgr *mgr, int entry, int edge)
{
    return mgr->entries[entry].edges[edge].point;
}

static inline u8 ShadowAreaEntry_Contains(ShadowAreaMgr *mgr, int index, ShadowAreaEntry *self, const Vec3f &p)
{
    int i;
    u8 ok = TRUE;

    if (!self->valid) {
        return FALSE;
    }
    for (i = 0; i < 6; i++) {
        Vec3f d;
        d.Sub(p, ShadowAreaMgr_GetEdgePoint(mgr, index, i));
        if (d.Dot(self->edges[i].normal) < 0.0f) {
            ok = FALSE;
            break;
        }
    }
    return ok;
}

extern "C" int ShadowAreaMgr_QueryPoint(ShadowAreaMgr *self, float x, float y, float z)
{
    Vec3f p(x, y, z);
    int i;

    i = self->count;
    while (i > 0) {
        i--;
        if (ShadowAreaEntry_Contains(self, i, &self->entries[i], p) == TRUE) {
            return 1;
        }
    }
    return 0;
}

