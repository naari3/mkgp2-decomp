#include "game/LakituStartPrivate.h"
LakituStart::LakituStart(const void *desc, int start, float px, float py, float pz) {
    model = 0;
    PSMTXIdentity(matrix);
    g_lakituDropStarted = 0;
    model = new clNormal3D(desc, 0);
    if (model) {
        clNormal3D_SetScale(model, 0, lbl_806D2510, LakituStart_Init_data_806CEDD0, lbl_806D2510, lbl_806D2510);
        float sz, sx;
        GetStartPosition(start, &sx, 0, &sz);
        matrix[0][3] = sx + LakituStart_data_806CEDC0;
        matrix[1][3] = lbl_806D2510;
        matrix[2][3] = sz + LakituStart_data_806CEDC8;
        Vec3f p;
        p.x = sx;
        p.z = sz;
        Terrain_GetGroundHeight(&p, &p.y, 0, 0);
        frame = lbl_806D2510;
        released = lbl_806D2510;
        ground = p.y + LakituStart_data_806CEDC4;
        angle = lbl_806D2538;
        phase = 0;
        SetRaceStartFlag(0);
        g_countdownPhase = 4;
    }
    x = px; y = py; z = pz;
    holdFrames = 0;
}

