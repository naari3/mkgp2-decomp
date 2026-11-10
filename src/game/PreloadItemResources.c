/* Item resource dependencies, 0x800DD940..0x800DEF74. */
#include "game/PreloadItemResources_private.h"

void PreloadItemResources(unsigned int item) {
    switch (ItemAlias_DestToSource(item, 0)) {
    case 1:
        FileLoader_Open(g_itemDescriptorTable[0x5]);
        break;
    case 2:
        FileLoader_Open(g_itemDescriptorTable[0xA]);
        break;
    case 3:
        FileLoader_Open(g_itemDescriptorTable[0xF]);
        break;
    case 4:
        FileLoader_Open(g_itemDescriptorTable[0x14]);
        break;
    case 5:
        FileLoader_Open(g_itemDescriptorTable[0x19]);
        break;
    case 6:
        FileLoader_Open(g_itemDescriptorTable[0x1E]);
        break;
    case 7:
        FileLoader_Open(g_itemDescriptorTable[0x23]);
        break;
    case 8:
        FileLoader_Open(g_itemDescriptorTable[0x28]);
        FileLoader_Open(lbl_8041BC00[0xCD]);
        FileLoader_Open(lbl_8041BC00[0xC8]);
        PreloadEffectResources(0x14);
        PreloadEffectResources(0x12);
        break;
    case 9:
        FileLoader_Open(g_itemDescriptorTable[0x2D]);
        break;
    case 10:
        FileLoader_Open(g_itemDescriptorTable[0x32]);
        break;
    case 11:
        FileLoader_Open(g_itemDescriptorTable[0x37]);
        break;
    case 12:
        FileLoader_Open(g_itemDescriptorTable[0x3C]);
        PreloadEffectResources(0x1e);
        break;
    case 13:
        FileLoader_Open(g_itemDescriptorTable[0x41]);
        PreloadEffectResources(0x1e);
        break;
    case 14:
        FileLoader_Open(g_itemDescriptorTable[0x46]);
        PreloadEffectResources(0x1f);
        break;
    case 15:
        FileLoader_Open(g_itemDescriptorTable[0x4B]);
        PreloadEffectResources(0x1e);
        break;
    case 16:
        FileLoader_Open(g_itemDescriptorTable[0x50]);
        PreloadEffectResources(0x1f);
        break;
    case 17:
        FileLoader_Open(g_itemDescriptorTable[0x55]);
        PreloadEffectResources(0x1e);
        break;
    case 18:
        FileLoader_Open(g_itemDescriptorTable[0x5A]);
        PreloadItemResources(0x45);
        break;
    case 19:
        FileLoader_Open(g_itemDescriptorTable[0x5F]);
        PreloadEffectResources(0x1e);
        break;
    case 20:
        FileLoader_Open(g_itemDescriptorTable[0x64]);
        PreloadEffectResources(0x1e);
        break;
    case 21:
        FileLoader_Open(g_itemDescriptorTable[0x69]);
        PreloadEffectResources(0x1f);
        break;
    case 22:
        FileLoader_Open(g_itemDescriptorTable[0x6E]);
        PreloadEffectResources(0x1f);
        break;
    case 23:
        FileLoader_Open(g_itemDescriptorTable[0x73]);
        break;
    case 24:
        FileLoader_Open(g_itemDescriptorTable[0x78]);
        PreloadEffectResources(0x1e);
        break;
    case 25:
        FileLoader_Open(g_itemDescriptorTable[0x7D]);
        break;
    case 26:
        FileLoader_Open(g_itemDescriptorTable[0x82]);
        FileLoader_Open(lbl_8041BC00[0xD2]);
        FileLoader_Open(lbl_8041BC00[0xD7]);
        FileLoader_Open(lbl_8041BC00[0xDC]);
        break;
    case 27:
        FileLoader_Open(g_itemDescriptorTable[0x87]);
        FileLoader_Open(lbl_8041BC00[0x23]);
        break;
    case 28:
        FileLoader_Open(g_itemDescriptorTable[0x8C]);
        break;
    case 29:
        FileLoader_Open(g_itemDescriptorTable[0x91]);
        break;
    case 30:
        FileLoader_Open(g_itemDescriptorTable[0x96]);
        PreloadEffectResources(0x1f);
        PreloadEffectResources(0x13);
        break;
    case 31:
        FileLoader_Open(g_itemDescriptorTable[0x9B]);
        PreloadEffectResources(0x1f);
        PreloadEffectResources(0x13);
        break;
    case 32:
        FileLoader_Open(g_itemDescriptorTable[0xA0]);
        PreloadEffectResources(0x1f);
        PreloadEffectResources(0x13);
        break;
    case 33:
        FileLoader_Open(g_itemDescriptorTable[0xA5]);
        break;
    case 34:
        FileLoader_Open(g_itemDescriptorTable[0xAA]);
        FileLoader_Open(lbl_8041BC00[0xF5]);
        break;
    case 35:
        FileLoader_Open(g_itemDescriptorTable[0xAF]);
        FileLoader_Open(lbl_8041BC00[0x104]);
        FileLoader_Open(lbl_8041BC00[0xFA]);
        FileLoader_Open(lbl_8041BC00[0xFF]);
        break;
    case 36:
        FileLoader_Open(g_itemDescriptorTable[0xB4]);
        PreloadEffectResources(0x1f);
        break;
    case 37:
        FileLoader_Open(g_itemDescriptorTable[0xB9]);
        PreloadEffectResources(0x1e);
        break;
    case 38:
        FileLoader_Open(g_itemDescriptorTable[0xBE]);
        PreloadEffectResources(0x1e);
        break;
    case 39:
        FileLoader_Open(g_itemDescriptorTable[0xC3]);
        PreloadEffectResources(0x1a);
        PreloadEffectResources(0x1e);
        break;
    case 40:
        FileLoader_Open(g_itemDescriptorTable[0xC8]);
        PreloadEffectResources(0x1f);
        break;
    case 41:
        FileLoader_Open(g_itemDescriptorTable[0xCD]);
        FileLoader_Open(lbl_8041BC00[0x109]);
        FileLoader_Open(lbl_8041BC00[0x10E]);
        break;
    case 42:
        FileLoader_Open(g_itemDescriptorTable[0xD2]);
        break;
    case 43:
        FileLoader_Open(g_itemDescriptorTable[0xD7]);
        PreloadEffectResources(0x1b);
        break;
    case 44:
        FileLoader_Open(g_itemDescriptorTable[0xDC]);
        FileLoader_Open(lbl_8041BC00[0x122]);
        FileLoader_Open(lbl_8041BC00[0x122]);
        FileLoader_Open(lbl_8041BC00[0x113]);
        FileLoader_Open(lbl_8041BC00[0x118]);
        FileLoader_Open(lbl_8041BC00[0x11D]);
        FileLoader_Open(lbl_8041BC00[0x127]);
        break;
    case 45:
        FileLoader_Open(g_itemDescriptorTable[0xE1]);
        FileLoader_Open(g_itemDescriptorTable[0xE6]);
        FileLoader_Open(g_itemDescriptorTable[0xEB]);
        FileLoader_Open(lbl_8041BC00[0x55]);
        PreloadEffectResources(0x17);
        break;
    case 46:
        FileLoader_Open(g_itemDescriptorTable[0xF0]);
        FileLoader_Open(g_itemDescriptorTable[0xF5]);
        PreloadEffectResources(0x20);
        PreloadItemResources(0x64);
        break;
    case 47:
        FileLoader_Open(g_itemDescriptorTable[0xFA]);
        FileLoader_Open(g_itemDescriptorTable[0xF5]);
        PreloadEffectResources(0x20);
        PreloadItemResources(0x63);
        break;
    case 48:
        FileLoader_Open(g_itemDescriptorTable[0x104]);
        FileLoader_Open(g_itemDescriptorTable[0x109]);
        PreloadEffectResources(0x1b);
        break;
    case 49:
        FileLoader_Open(g_itemDescriptorTable[0x10E]);
        FileLoader_Open(lbl_8041BC00[0x12C]);
        FileLoader_Open(lbl_8041BC00[0x131]);
        PreloadEffectResources(0x1b);
        break;
    case 50:
        FileLoader_Open(g_itemDescriptorTable[0x113]);
        PreloadEffectResources(0x12);
        break;
    case 51:
        FileLoader_Open(g_itemDescriptorTable[0x118]);
        PreloadEffectResources(0x1a);
        PreloadEffectResources(0x12);
        PreloadEffectResources(0x16);
        break;
    case 52:
        FileLoader_Open(g_itemDescriptorTable[0x11D]);
        PreloadEffectResources(0x12);
        break;
    case 53:
        FileLoader_Open(g_itemDescriptorTable[0x113]);
        PreloadEffectResources(0x12);
        break;
    case 54:
        FileLoader_Open(g_itemDescriptorTable[0x122]);
        PreloadEffectResources(0x12);
        PreloadEffectResources(0x1c);
        break;
    case 55:
        FileLoader_Open(g_itemDescriptorTable[0x127]);
        PreloadEffectResources(0x1b);
        break;
    case 56:
        FileLoader_Open(g_itemDescriptorTable[0x12C]);
        PreloadEffectResources(0x1b);
        break;
    case 57:
        FileLoader_Open(g_itemDescriptorTable[0x131]);
        FileLoader_Open(lbl_8041BC00[0x267]);
        FileLoader_Open(lbl_8041BC00[0x55]);
        break;
    case 58:
        FileLoader_Open(g_itemDescriptorTable[0x136]);
        FileLoader_Open(lbl_8041BC00[0x267]);
        FileLoader_Open(lbl_8041BC00[0x55]);
        break;
    case 59:
        FileLoader_Open(g_itemDescriptorTable[0x13B]);
        FileLoader_Open(lbl_8041BC00[0x2C1]);
        FileLoader_Open(lbl_8041BC00[0x2C6]);
        break;
    case 60:
        FileLoader_Open(g_itemDescriptorTable[0x140]);
        FileLoader_Open(lbl_8041BC00[0x136]);
        FileLoader_Open(lbl_8041BC00[0x113]);
        FileLoader_Open(lbl_8041BC00[0x118]);
        FileLoader_Open(lbl_8041BC00[0x11D]);
        FileLoader_Open(lbl_8041BC00[0x136]);
        break;
    case 61:
        FileLoader_Open(g_itemDescriptorTable[0x145]);
        PreloadEffectResources(0x19);
        FileLoader_Open(lbl_8041BC00[0x13B]);
        FileLoader_Open(lbl_8041BC00[0x140]);
        FileLoader_Open(lbl_8041BC00[0x145]);
        FileLoader_Open(lbl_8041BC00[0x14A]);
        FileLoader_Open(lbl_8041BC00[0x14F]);
        break;
    case 62:
        FileLoader_Open(g_itemDescriptorTable[0x14A]);
        PreloadEffectResources(0x19);
        PreloadItemResources(0x63);
        break;
    case 63:
        FileLoader_Open(g_itemDescriptorTable[0x14F]);
        PreloadEffectResources(0x19);
        PreloadEffectResources(0x1a);
        FileLoader_Open(lbl_8041BC00[0x154]);
        FileLoader_Open(lbl_8041BC00[0x159]);
        FileLoader_Open(lbl_8041BC00[0x15E]);
        FileLoader_Open(lbl_8041BC00[0x163]);
        FileLoader_Open(lbl_8041BC00[0x168]);
        break;
    case 64:
        FileLoader_Open(g_itemDescriptorTable[0x154]);
        FileLoader_Open(lbl_8041BC00[0x221]);
        PreloadItemResources(0x65);
        break;
    case 65:
        FileLoader_Open(g_itemDescriptorTable[0x159]);
        PreloadEffectResources(0x1b);
        break;
    case 66:
        FileLoader_Open(g_itemDescriptorTable[0x15E]);
        FileLoader_Open(lbl_8041BC00[0x16D]);
        break;
    case 67:
        FileLoader_Open(g_itemDescriptorTable[0x163]);
        PreloadEffectResources(0x1b);
        break;
    case 68:
        FileLoader_Open(g_itemDescriptorTable[0x168]);
        PreloadEffectResources(0x1b);
        break;
    case 69:
        FileLoader_Open(lbl_8041BC00[0x177]);
        FileLoader_Open(lbl_8041BC00[0x172]);
        PreloadEffectResources(0x18);
        break;
    case 70:
        FileLoader_Open(g_itemDescriptorTable[0x16D]);
        FileLoader_Open(lbl_8041BC00[0x27B]);
        PreloadEffectResources(0x17);
        break;
    case 71:
        FileLoader_Open(g_itemDescriptorTable[0x172]);
        break;
    case 72:
        FileLoader_Open(g_itemDescriptorTable[0x177]);
        break;
    case 73:
        FileLoader_Open(g_itemDescriptorTable[0x73]);
        break;
    case 74:
        FileLoader_Open(g_itemDescriptorTable[0x17C]);
        PreloadItemResources(0x4b);
        FileLoader_Open(lbl_8041BC00[0x181]);
        PreloadEffectResources(0x16);
        break;
    case 75:
        FileLoader_Open(lbl_8041BC00[0x186]);
        break;
    case 76:
        FileLoader_Open(g_itemDescriptorTable[0x181]);
        PreloadEffectResources(0x20);
        PreloadItemResources(0x63);
        break;
    case 77:
        FileLoader_Open(g_itemDescriptorTable[0x186]);
        break;
    case 78:
        FileLoader_Open(g_itemDescriptorTable[0x18B]);
        PreloadItemResources(0x4f);
        break;
    case 79:
        FileLoader_Open(g_itemDescriptorTable[0x190]);
        break;
    case 80:
        FileLoader_Open(g_itemDescriptorTable[0x195]);
        FileLoader_Open(lbl_8041BC00[0x280]);
        FileLoader_Open(lbl_8041BC00[0x23F]);
        FileLoader_Open(lbl_8041BC00[0x244]);
        PreloadResource(0xc68);
        break;
    case 81:
        FileLoader_Open(lbl_8041BC00[0x1F4]);
        PreloadItemResources(0x67);
        break;
    case 82:
        FileLoader_Open(g_itemDescriptorTable[0x19A]);
        PreloadItemResources(0x53);
        break;
    case 83:
        FileLoader_Open(lbl_8041BC00[0x18B]);
        FileLoader_Open(lbl_8041BC00[0x2B2]);
        break;
    case 84:
        FileLoader_Open(g_itemDescriptorTable[0x19F]);
        break;
    case 85:
        FileLoader_Open(g_itemDescriptorTable[0x1A4]);
        FileLoader_Open(lbl_8041BC00[0x285]);
        FileLoader_Open(lbl_8041BC00[0x190]);
        FileLoader_Open(lbl_8041BC00[0x195]);
        FileLoader_Open(lbl_8041BC00[0x19A]);
        FileLoader_Open(lbl_8041BC00[0x19F]);
        FileLoader_Open(lbl_8041BC00[0x28A]);
        PreloadResource(0xc66);
        break;
    case 86:
        FileLoader_Open(g_itemDescriptorTable[0x1A9]);
        PreloadItemResources(0x57);
        break;
    case 87:
        FileLoader_Open(g_itemDescriptorTable[0x1AE]);
        break;
    case 88:
        FileLoader_Open(g_itemDescriptorTable[0x1B3]);
        PreloadItemResources(0x66);
        break;
    case 89:
        FileLoader_Open(g_itemDescriptorTable[0x1B8]);
        break;
    case 90:
        FileLoader_Open(g_itemDescriptorTable[0x1BD]);
        break;
    case 91:
        FileLoader_Open(g_itemDescriptorTable[0x1C2]);
        PreloadEffectResources(0x1c);
        break;
    case 92:
        FileLoader_Open(g_itemDescriptorTable[0x1C7]);
        PreloadEffectResources(0x1c);
        break;
    case 93:
        FileLoader_Open(g_itemDescriptorTable[0x1CC]);
        PreloadEffectResources(0x1c);
        break;
    case 94:
        FileLoader_Open(g_itemDescriptorTable[0x1D1]);
        FileLoader_Open(lbl_8041BC00[0x1AE]);
        break;
    case 95:
        FileLoader_Open(g_itemDescriptorTable[0x1D6]);
        FileLoader_Open(lbl_8041BC00[0x1B3]);
        FileLoader_Open(lbl_8041BC00[0x1B3]);
        PreloadEffectResources(0x18);
        break;
    case 96:
        FileLoader_Open(g_itemDescriptorTable[0x1DB]);
        FileLoader_Open(lbl_8041BC00[0x1B8]);
        FileLoader_Open(lbl_8041BC00[0x1B8]);
        PreloadEffectResources(0x18);
        break;
    case 97:
        FileLoader_Open(g_itemDescriptorTable[0x1E0]);
        PreloadItemResources(0x62);
        break;
    case 98:
        FileLoader_Open(g_itemDescriptorTable[0x1E5]);
        FileLoader_Open(lbl_8041BC00[0x230]);
        PreloadEffectResources(0x12);
        break;
    case 99:
    case 100:
        FileLoader_Open(lbl_8041BC00[0x253]);
        FileLoader_Open(lbl_8041BC00[0x258]);
        FileLoader_Open(lbl_8041BC00[0x25D]);
        FileLoader_Open(lbl_8041BC00[0x262]);
        FileLoader_Open(lbl_8041BC00[0x23A]);
        PreloadEffectResources(0x1b);
        break;
    case 101:
    case 102:
    case 103:
        FileLoader_Open(lbl_8041BC00[0x221]);
        break;
    case 104:
        FileLoader_Open(lbl_8041BC00[0x20D]);
        FileLoader_Open(lbl_8041BC00[0x217]);
        FileLoader_Open(lbl_8041BC00[0x212]);
        FileLoader_Open(lbl_8041BC00[0x21C]);
        break;
    case 105:
        FileLoader_Open(g_itemDescriptorTable[0x1EA]);
        FileLoader_Open(g_itemDescriptorTable[0x1EF]);
        FileLoader_Open(g_itemDescriptorTable[0x1F4]);
        FileLoader_Open(g_itemDescriptorTable[0x1F9]);
        FileLoader_Open(g_itemDescriptorTable[0x1FE]);
        FileLoader_Open(g_itemDescriptorTable[0x203]);
        FileLoader_Open(g_itemDescriptorTable[0x208]);
        FileLoader_Open(lbl_8041BC00[0x1BD]);
        break;
    case 106:
        FileLoader_Open(g_itemDescriptorTable[0x20D]);
        break;
    case 107:
        FileLoader_Open(g_itemDescriptorTable[0x212]);
        FileLoader_Open(lbl_8041BC00[0x1C2]);
        FileLoader_Open(lbl_8041BC00[0x1C7]);
        break;
    case 108:
        PreloadEffectResources(0x1d);
        PreloadItemResources(0x35);
        break;
    case 109:
        PreloadEffectResources(0x1d);
        PreloadItemResources(0x36);
        break;
    case 110:
        PreloadEffectResources(0x1d);
        PreloadItemResources(0x49);
        break;
    case 111:
        PreloadEffectResources(0x1d);
        PreloadItemResources(0x70);
        break;
    case 112:
        FileLoader_Open(g_itemDescriptorTable[0x217]);
        FileLoader_Open(lbl_8041BC00[0x24E]);
        PreloadItemResources(0x64);
        PreloadEffectResources(0x18);
        break;
    case 113:
        FileLoader_Open(g_itemDescriptorTable[0x21C]);
        FileLoader_Open(lbl_8041BC00[0x1DB]);
        PreloadEffectResources(0x1b);
        PreloadEffectResources(0x14);
        break;
    case 114:
        FileLoader_Open(g_itemDescriptorTable[0x221]);
        FileLoader_Open(lbl_8041BC00[0x1EA]);
        PreloadEffectResources(0x1b);
        FileLoader_Open(lbl_8041BC00[0x3C]);
        break;
    case 115:
        FileLoader_Open(g_itemDescriptorTable[0x226]);
        FileLoader_Open(lbl_8041BC00[0x276]);
        PreloadEffectResources(0x1b);
        FileLoader_Open(lbl_8041BC00[0x29E]);
        FileLoader_Open(lbl_8041BC00[0x294]);
        FileLoader_Open(lbl_8041BC00[0x299]);
        break;
    case 116:
        FileLoader_Open(g_itemDescriptorTable[0x22B]);
        FileLoader_Open(lbl_8041BC00[0x1EF]);
        break;
    case 117:
        FileLoader_Open(g_itemDescriptorTable[0x230]);
        PreloadResource(0xc6b);
        break;
    case 118:
        FileLoader_Open(g_itemDescriptorTable[0x235]);
        FileLoader_Open(lbl_8041BC00[0x208]);
        FileLoader_Open(lbl_8041BC00[0x1F9]);
        FileLoader_Open(lbl_8041BC00[0x1FE]);
        FileLoader_Open(lbl_8041BC00[0x203]);
        break;
    case 119:
        FileLoader_Open(g_itemDescriptorTable[0x23A]);
        PreloadEffectResources(0x1b);
        PreloadItemResources(0x2b);
        PreloadItemResources(0x63);
        break;
    case 120:
        FileLoader_Open(g_itemDescriptorTable[0x23F]);
        FileLoader_Open(lbl_8041BC00[0x2A8]);
        break;
    case 121:
        FileLoader_Open(g_itemDescriptorTable[0x244]);
        PreloadItemResources(0x68);
        break;
    case 123:
        PreloadItemResources(0x3d);
        break;
    case 124:
        PreloadItemResources(0x32);
        break;
    case 125:
        PreloadItemResources(0x17);
        break;
    case 126:
        PreloadItemResources(0x50);
        break;
    case 127:
        PreloadItemResources(0x39);
        break;
    case 128:
        PreloadItemResources(0x40);
        break;
    case 129:
        PreloadItemResources(0x2b);
        break;
    case 130:
        PreloadItemResources(0x46);
        break;
    case 131:
        PreloadItemResources(0x5d);
        break;
    case 132:
        PreloadItemResources(0x2d);
        break;
    case 133:
        PreloadItemResources(0x55);
        break;
    case 134:
        PreloadItemResources(0x4e);
        break;
    case 135:
        PreloadItemResources(0x3e);
        break;
    case 136:
        FileLoader_Open(g_itemDescriptorTable[0x280]);
        FileLoader_Open(lbl_8041BC00[0x24E]);
        PreloadEffectResources(0x1b);
        PreloadResource(0xc6a);
        break;
    case 137:
        FileLoader_Open(g_itemDescriptorTable[0x285]);
        break;
    case 138:
        FileLoader_Open(g_itemDescriptorTable[0x28A]);
        PreloadItemResources(0x63);
        break;
    case 139:
        FileLoader_Open(g_itemDescriptorTable[0x28F]);
        PreloadEffectResources(0x1e);
        break;
    case 140:
    case 141:
        FileLoader_Open(g_itemDescriptorTable[0x294]);
        PreloadEffectResources(0x17);
        break;
    case 142:
        FileLoader_Open(g_itemDescriptorTable[0x299]);
        break;
    case 143:
        FileLoader_Open(g_itemDescriptorTable[0x29E]);
        PreloadResource(0xc67);
        break;
    case 144:
        FileLoader_Open(g_itemDescriptorTable[0x2A3]);
        break;
    case 145:
        FileLoader_Open(g_itemDescriptorTable[0x2A8]);
        PreloadEffectResources(0x1e);
        break;
    case 146:
        FileLoader_Open(g_itemDescriptorTable[0x2AD]);
        PreloadEffectResources(0x1b);
        break;
    case 147:
        FileLoader_Open(g_itemDescriptorTable[0x2B2]);
        FileLoader_Open(g_itemDescriptorTable[0x2B7]);
        FileLoader_Open(g_itemDescriptorTable[0x2BC]);
        PreloadEffectResources(0x1b);
        PreloadResource(0xc63);
        PreloadResource(0xc64);
        PreloadResource(0xc65);
        break;
    case 148:
        FileLoader_Open(g_itemDescriptorTable[0x2C1]);
        break;
    case 149:
        FileLoader_Open(g_itemDescriptorTable[0x2C6]);
        PreloadEffectResources(0x1b);
        break;
    case 150:
        FileLoader_Open(g_itemDescriptorTable[0x2CB]);
        PreloadEffectResources(0x20);
        PreloadItemResources(0x64);
        break;
    case 151:
        FileLoader_Open(g_itemDescriptorTable[0x2D0]);
        FileLoader_Open(g_itemDescriptorTable[0x2D5]);
        break;
    case 152:
        FileLoader_Open(g_itemDescriptorTable[0x2DA]);
        PreloadEffectResources(0x1b);
        break;
    case 153:
        FileLoader_Open(g_itemDescriptorTable[0x2DF]);
        PreloadResource(0x14ab);
        PreloadEffectResources(0x1a);
        break;
    case 154:
        FileLoader_Open(g_itemDescriptorTable[0x2E4]);
        FileLoader_Open(lbl_8041BC00[0x2D0]);
        FileLoader_Open(lbl_8041BC00[0x2D5]);
        FileLoader_Open(lbl_8041BC00[0xD2]);
        FileLoader_Open(lbl_8041BC00[0xD7]);
        FileLoader_Open(lbl_8041BC00[0xDC]);
        break;
    case 155:
    case 156:
        FileLoader_Open(g_itemDescriptorTable[0x2E9]);
        FileLoader_Open(g_itemDescriptorTable[0x2EE]);
        PreloadEffectResources(0x12);
        break;
    case 157:
    case 158:
        FileLoader_Open(g_itemDescriptorTable[0x2F3]);
        FileLoader_Open(g_itemDescriptorTable[0x2F8]);
        FileLoader_Open(g_itemDescriptorTable[0x2FD]);
        FileLoader_Open(lbl_8041BC00[0x2DA]);
        FileLoader_Open(lbl_8041BC00[0x285]);
        FileLoader_Open(lbl_8041BC00[0x190]);
        FileLoader_Open(lbl_8041BC00[0x195]);
        FileLoader_Open(lbl_8041BC00[0x19A]);
        FileLoader_Open(lbl_8041BC00[0x19F]);
        FileLoader_Open(lbl_8041BC00[0x28A]);
        FileLoader_Open(lbl_8041BC00[0x2E4]);
        PreloadResource(0xc69);
        break;
    }
}
