/* 0x801A1798: remaps sprite ids 0x7B..0x87 to their alternate ids.
 * Nothing calls it, so it is kept with force_active. */

#pragma force_active on
short fn_801A1798(short id) {
    switch (id) {
    case 0x7b: return 0x3d;
    case 0x7c: return 0x32;
    case 0x7d: return 0x17;
    case 0x7e: return 0x50;
    case 0x7f: return 0x39;
    case 0x80: return 0x40;
    case 0x81: return 0x2b;
    case 0x82: return 0x46;
    case 0x83: return 0x5d;
    case 0x84: return 0x2d;
    case 0x85: return 0x55;
    case 0x86: return 0x4e;
    case 0x87: return 0x3e;
    }
    return id;
}
