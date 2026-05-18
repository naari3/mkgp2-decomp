// Resource loading singleton flag.
//
// SetResourceLoadingFlag (0x80034D1C, size 0x8): writes the low byte of `flag`
// to the first byte of an 8-byte sdata slot at 0x806D0FF0.
//
// The slot is sized 0x8 in symbols.txt (`data:byte`) so it is sdata-resident
// (CW emits `stb r3, lbl@sda21(r0)`), but the only known access is the first
// byte. The remaining 7 bytes are likely padding / future-use; we honour the
// layout with `unsigned char [8]`.

extern unsigned char g_resourceLoadingFlag[8];

void SetResourceLoadingFlag(unsigned char flag) {
    g_resourceLoadingFlag[0] = flag;
}

