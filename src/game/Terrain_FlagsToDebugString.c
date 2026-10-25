/* Terrain_FlagsToDebugString (0x800A5384): debug name for a terrain flag
 * word ("ROAD_ISIDATAMI_..."). In cup 2 a bit-0x80 surface reads as 0x40
 * and the slip bits are remapped. */


#pragma cplusplus on
extern "C" {
extern int g_cupId;
extern char lbl_805D2B40[0x400];
extern void *memset(void *dst, int c, unsigned long n);
extern char *strcat(char *dst, const char *src);

}

extern "C" char *Terrain_FlagsToDebugString(unsigned int flags)
{
    unsigned int f;
    char *buf = lbl_805D2B40;
    unsigned int g;

    memset(buf, 0, 0x400);
    g = flags;
    f = flags & ~0x00F00000;
    if (g_cupId == 2 && (f & 0x80)) {
        unsigned int set;
        unsigned int keep;
        keep = set = 0;
        f &= ~0x80;
        f |= 0x40;
        if (flags & 0x00800000) {
            keep |= 0x00800000;
            set |= 0x00100000;
        }
        g &= keep;
        g |= set;
    }
    f |= g & 0x00F00000;

    if (f & 0x1) strcat(buf, "ROAD_");
    if (f & 0x800) strcat(buf, "ISIDATAMI_");
    if (f & 0x2) strcat(buf, "_RUNOFF");
    if (f & 0x4) strcat(buf, "_WOODROAD");
    if (f & 0x8) strcat(buf, "_WATER");
    if (f & 0x10) strcat(buf, "_SAND");
    if (f & 0x20) strcat(buf, "_MUD");
    if (f & 0x40) strcat(buf, "_WATER_SPLASH");
    if (f & 0x80) strcat(buf, "_MUD_SPLASH");
    if (f & 0x100) strcat(buf, "_KANAAMI1");
    if (f & 0x200) strcat(buf, "_KANAAMI2");
    if (f & 0x400) strcat(buf, "_GRASS");
    if (f & 0x100000) strcat(buf, "_SLOWDOWN");
    if (f & 0x200000) strcat(buf, "_SLIP");
    if (f & 0x400000) strcat(buf, "_SLOWDOWN2");
    if (f & 0x800000) strcat(buf, "_SLIP2");
    return buf;
}
