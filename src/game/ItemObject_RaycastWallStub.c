extern unsigned char Terrain_RaycastWall(float *from, float *to, float *outPos, float *outNormal);

unsigned char ItemObject_RaycastWallStub(float *from, float *to, float *outPos, float *outNormal)
{
    return Terrain_RaycastWall(from, to, outPos, outNormal);
}
