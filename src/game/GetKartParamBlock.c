/* GetKartParamBlock @ 0x80090FF0, 140 bytes.
 * Character tables and the explicit cc-variant table both have three columns.
 */
extern unsigned int g_kartParamCcVariantTable[][3];
extern unsigned int (*g_kartParamPtrTable[])[3];

unsigned int GetKartParamBlock(int charId, int ccClass, int kartVariant, int ccVariant) {
    int normalizedVariant;

    switch (kartVariant) {
    default:
    case 0:
        normalizedVariant = 0;
        break;
    case 1:
        normalizedVariant = 0;
        break;
    case 2:
        normalizedVariant = 1;
        break;
    case 3:
        normalizedVariant = 2;
        break;
    }
    if (ccVariant < 0) {
        return g_kartParamPtrTable[charId][ccClass][normalizedVariant];
    }
    return g_kartParamCcVariantTable[ccVariant][ccClass];
}
