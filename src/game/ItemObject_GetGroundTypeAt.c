extern unsigned char Terrain_GetGroundHeightWithPenetration(void *a, void *b, int *pos, int *flags, float depth);
extern int Terrain_ApplyCup2FlagPatch(int flags);
extern int Terrain_FlagsToTypeId(int flags);

signed char ItemObject_GetGroundTypeAt(void *a, void *b, int pos)
{
    int flags;

    if (!Terrain_GetGroundHeightWithPenetration(a, b, &pos, &flags, 10.0f)) {
        return 0;
    }
    flags = Terrain_ApplyCup2FlagPatch(flags);
    return (signed char)Terrain_FlagsToTypeId(flags);
}
