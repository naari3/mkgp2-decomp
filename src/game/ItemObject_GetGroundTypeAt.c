extern unsigned char Terrain_GetGroundHeightWithPenetration(void *a, void *b, int *pos, int *flags, float depth);
extern int Terrain_ApplyCup2FlagPatch(int flags);
extern int Terrain_FlagsToTypeId(int flags);

signed char ItemObject_GetGroundTypeAt(void *a, void *b, int pos)
{
    int flags;

    /*
     * The callee writes a three-float normal through its third argument.
     * The original passes the address of the saved third parameter, so two
     * of the floats land in stack space nothing else uses. Another compiler
     * may keep live values there, so it gets a real home for the normal.
     */
#ifdef __MWERKS__
    if (!Terrain_GetGroundHeightWithPenetration(a, b, &pos, &flags, 10.0f)) {
        return 0;
    }
#else
    float normal[3];

    (void)pos;
    if (!Terrain_GetGroundHeightWithPenetration(a, b, (int *)normal, &flags, 10.0f)) {
        return 0;
    }
#endif
    flags = Terrain_ApplyCup2FlagPatch(flags);
    return (signed char)Terrain_FlagsToTypeId(flags);
}
