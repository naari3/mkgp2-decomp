/*
 * AcError_LogIfError, 0x8004895C..0x80048BEC: prints the result of an
 * ac socket call and, for -1, the socket's last error. Owns its jump table
 * (.data 0x803F74A8..0x803F75D0).
 */

extern const char lbl_802EB4E0[]; /* string pool */

void DebugPrintf(const char *fmt, ...);
int acGetLastError(int sock);

#pragma exceptions on

void AcError_LogIfError(int sock, int result)
{
    const char *strings = lbl_802EB4E0;

    switch (result) {
    case -1:
        DebugPrintf(strings + 0x38);
        break;
    case -2:
        DebugPrintf(strings + 0x48);
        break;
    case -3:
        DebugPrintf(strings + 0x7C);
        break;
    case -4:
        DebugPrintf(strings + 0x90);
        break;
    }
    if (result == -1) {
        switch (acGetLastError(sock)) {
        case -1:
            DebugPrintf(strings + 0x38);
            break;
        case -2:
            DebugPrintf(strings + 0x48);
            break;
        case -3:
            DebugPrintf(strings + 0x7C);
            break;
        case -4:
            DebugPrintf(strings + 0x90);
            break;
        case 24:
            DebugPrintf(strings + 0xA4);
            break;
        case 23:
            DebugPrintf(strings + 0xC0);
            break;
        case 55:
            DebugPrintf(strings + 0xD4);
            break;
        case 9:
            DebugPrintf(strings + 0xE0);
            break;
        case 50:
            DebugPrintf(strings + 0xF0);
            break;
        case 49:
            DebugPrintf(strings + 0x104);
            break;
        case 47:
            DebugPrintf(strings + 0x118);
            break;
        case 56:
            DebugPrintf(strings + 0x134);
            break;
        case 60:
            DebugPrintf(strings + 0x14C);
            break;
        case 61:
            DebugPrintf(strings + 0x158);
            break;
        case 51:
            DebugPrintf(strings + 0x178);
            break;
        case 48:
            DebugPrintf(strings + 0x198);
            break;
        case 14:
            DebugPrintf(strings + 0x1AC);
            break;
        case 68:
            DebugPrintf(strings + 0x1E0);
            break;
        case 69:
            DebugPrintf(strings + 0x210);
            break;
        case 13:
            DebugPrintf(strings + 0x264);
            break;
        case 36:
            DebugPrintf(strings + 0x2B0);
            break;
        case 11:
            DebugPrintf(strings + 0x2F4);
            break;
        case 65:
            DebugPrintf(strings + 0x320);
            break;
        case 67:
            DebugPrintf(strings + 0x33C);
            break;
        case 57:
            DebugPrintf(strings + 0x354);
            break;
        case 4:
            DebugPrintf(strings + 0x378);
            break;
        default:
            DebugPrintf(strings + 0x39C, acGetLastError(sock));
            break;
        }
    }
}

#pragma exceptions reset
