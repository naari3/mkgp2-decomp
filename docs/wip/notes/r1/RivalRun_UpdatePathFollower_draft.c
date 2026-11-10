static inline int RRFindNearest(RRVec3 *pts, int count, const RRVec3 *pos) {
    int best;
    float bestDist;
    int i;
    RRVec3 d;
    float sx, sy, sz;

    best = 0;
    bestDist = lbl_806D738C;
    sx = pos->x;
    sy = pos->y;
    sz = pos->z;
    for (i = best; i < count; i++) {
        float dist;

        d.x = pts[i].x - sx;
        d.y = pts[i].y - sy;
        d.z = pts[i].z - sz;
        dist = PSVECSquareMag(&d);
        if (i == 0 || dist < bestDist) {
            best = i;
            bestDist = dist;
        }
    }
    return best;
}

static inline void RRAdvance(RRPathFollower *pf, RRVec3 *pts, int last, float x, float z, RRVec3 *rel) {
    float dot;

    for (;;) {
        pf->target.x = pts[pf->seg].x;
        pf->target.y = lbl_806D738C;
        pf->target.z = pts[pf->seg].z;
        if (pf->seg == last) {
            RRVec3 *p = &pts[pf->seg];
            pf->dir.x = p[0].x - p[-1].x;
            pf->dir.y = lbl_806D738C;
            pf->dir.z = p[0].z - p[-1].z;
        } else {
            RRVec3 *p = &pts[pf->seg];
            pf->dir.x = p[1].x - p[0].x;
            pf->dir.y = lbl_806D738C;
            pf->dir.z = p[1].z - p[0].z;
        }
        Vec3_Normalize(&pf->dir, &pf->dir);
        rel->x = pf->target.x - x;
        rel->y = lbl_806D738C;
        rel->z = pf->target.z - z;
        dot = Vec3_Dot(rel, &pf->dir);
        if (pf->seg == last) {
            if (dot < pf->endDist) {
                float k = lbl_806D73A0 - dot;
                pf->target.x = pf->dir.x * k + pf->target.x;
                pf->target.z = pf->dir.z * k + pf->target.z;
            }
            break;
        }
        if (!(dot < lbl_806D73A0)) {
            break;
        }
        pf->seg++;
    }
}

void RivalRun_UpdatePathFollower(RRPathFollower *pf, const RRVec3 *pos) {
    RRVec3 *pts = RivalRun_rodata_8035C1E4[pf->lane][pf->route].pts;
    int count = RivalRun_rodata_8035C1E4[pf->lane][pf->route].count;
    RRVec3 rel;

    if (pf->needsSearch) {
        pf->needsSearch = 0;
        pf->seg = RRFindNearest(pts, count, pos);
    }

    RRAdvance(pf, pts, count - 1, pos->x, pos->z, &rel);
}
