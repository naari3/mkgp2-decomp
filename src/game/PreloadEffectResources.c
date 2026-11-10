/* Resource-set dependencies, 0x800DEF74..0x800DF56C. */
extern void FileLoader_Open(const char *);
extern const char *lbl_8041BC00[];
extern const char *g_itemDescriptorTable[];

void PreloadEffectResources(int set) {
    switch (set) {
    case 1:
        FileLoader_Open(lbl_8041BC00[0x221]);
        PreloadEffectResources(12);
        PreloadEffectResources(13);
        PreloadEffectResources(14);
        break;
    case 2:
        FileLoader_Open(lbl_8041BC00[0x221]);
        FileLoader_Open(lbl_8041BC00[0x249]);
        FileLoader_Open(lbl_8041BC00[0x5A]);
        PreloadEffectResources(14);
        PreloadEffectResources(15);
        PreloadEffectResources(12);
        PreloadEffectResources(16);
        break;
    case 4:
        PreloadEffectResources(12);
        PreloadEffectResources(13);
        PreloadEffectResources(17);
        break;
    case 5:
        FileLoader_Open(lbl_8041BC00[0x249]);
        PreloadEffectResources(12);
        PreloadEffectResources(14);
        break;
    case 8:
        PreloadEffectResources(13);
        PreloadEffectResources(15);
        break;
    case 9:
        FileLoader_Open(lbl_8041BC00[0x2BC]);
        FileLoader_Open(lbl_8041BC00[0x23A]);
        FileLoader_Open(lbl_8041BC00[0x28F]);
        FileLoader_Open(lbl_8041BC00[0x1CC]);
        FileLoader_Open(lbl_8041BC00[0x1D1]);
        FileLoader_Open(lbl_8041BC00[0x1D6]);
        FileLoader_Open(lbl_8041BC00[0x2D]);
        FileLoader_Open(lbl_8041BC00[0x32]);
        FileLoader_Open(lbl_8041BC00[0x37]);
        FileLoader_Open(lbl_8041BC00[0xEB]);
        FileLoader_Open(lbl_8041BC00[0xE1]);
        FileLoader_Open(lbl_8041BC00[0xE6]);
        FileLoader_Open(lbl_8041BC00[0xF0]);
        FileLoader_Open(lbl_8041BC00[0x8C]);
        break;
    case 10:
        FileLoader_Open(lbl_8041BC00[0x9B]);
        FileLoader_Open(lbl_8041BC00[0xA0]);
        FileLoader_Open(lbl_8041BC00[0xA5]);
        FileLoader_Open(lbl_8041BC00[0xAA]);
        FileLoader_Open(lbl_8041BC00[0xAF]);
        FileLoader_Open(lbl_8041BC00[0xB4]);
        FileLoader_Open(lbl_8041BC00[0x87]);
        FileLoader_Open(lbl_8041BC00[0x46]);
        FileLoader_Open(g_itemDescriptorTable[0x30C]);
        PreloadEffectResources(21);
        break;
    case 12:
        FileLoader_Open(lbl_8041BC00[0x8C]);
        PreloadEffectResources(27);
        break;
    case 13:
        FileLoader_Open(lbl_8041BC00[0x221]);
        FileLoader_Open(lbl_8041BC00[0x8C]);
        PreloadEffectResources(27);
        break;
    case 14:
        FileLoader_Open(lbl_8041BC00[0x221]);
        FileLoader_Open(lbl_8041BC00[0x8C]);
        PreloadEffectResources(27);
        break;
    case 15:
        FileLoader_Open(lbl_8041BC00[0x91]);
        FileLoader_Open(lbl_8041BC00[0x96]);
        FileLoader_Open(lbl_8041BC00[0x294]);
        FileLoader_Open(lbl_8041BC00[0x299]);
        FileLoader_Open(lbl_8041BC00[0x29E]);
        break;
    case 16:
        FileLoader_Open(lbl_8041BC00[0x64]);
        FileLoader_Open(lbl_8041BC00[0x5F]);
        break;
    case 17:
        FileLoader_Open(lbl_8041BC00[0x4B]);
        FileLoader_Open(lbl_8041BC00[0x50]);
        break;
    case 18:
        FileLoader_Open(lbl_8041BC00[0x26C]);
        break;
    case 19:
        FileLoader_Open(lbl_8041BC00[0x5]);
        break;
    case 20:
        FileLoader_Open(lbl_8041BC00[0x271]);
        FileLoader_Open(lbl_8041BC00[0x235]);
        break;
    case 21:
        FileLoader_Open(lbl_8041BC00[0xA]);
        FileLoader_Open(lbl_8041BC00[0x226]);
        FileLoader_Open(lbl_8041BC00[0x1A9]);
        FileLoader_Open(lbl_8041BC00[0x1A4]);
        FileLoader_Open(lbl_8041BC00[0x226]);
        break;
    case 22:
        FileLoader_Open(lbl_8041BC00[0x181]);
        break;
    case 23:
        FileLoader_Open(lbl_8041BC00[0x41]);
        break;
    case 24:
        FileLoader_Open(lbl_8041BC00[0x17C]);
        FileLoader_Open(lbl_8041BC00[0x221]);
        break;
    case 25:
        FileLoader_Open(lbl_8041BC00[0x2B2]);
        FileLoader_Open(lbl_8041BC00[0x2AD]);
        break;
    case 26:
        FileLoader_Open(lbl_8041BC00[0x27B]);
        break;
    case 27:
        FileLoader_Open(lbl_8041BC00[0x221]);
        FileLoader_Open(lbl_8041BC00[0x22B]);
        FileLoader_Open(lbl_8041BC00[0x226]);
        break;
    case 28:
        FileLoader_Open(lbl_8041BC00[0x1A9]);
        FileLoader_Open(lbl_8041BC00[0x1A4]);
        PreloadEffectResources(25);
        PreloadEffectResources(27);
        break;
    case 29:
        PreloadEffectResources(27);
        FileLoader_Open(lbl_8041BC00[0x1CC]);
        FileLoader_Open(lbl_8041BC00[0x1D1]);
        FileLoader_Open(lbl_8041BC00[0x1D6]);
        break;
    case 30:
        FileLoader_Open(lbl_8041BC00[0xB9]);
        FileLoader_Open(lbl_8041BC00[0x14]);
        FileLoader_Open(lbl_8041BC00[0x19]);
        FileLoader_Open(lbl_8041BC00[0x1E]);
        break;
    case 31:
        FileLoader_Open(lbl_8041BC00[0xBE]);
        FileLoader_Open(lbl_8041BC00[0xC3]);
        PreloadEffectResources(26);
        FileLoader_Open(lbl_8041BC00[0xF]);
        break;
    case 32:
        FileLoader_Open(lbl_8041BC00[0x2CB]);
        break;
    }
}
