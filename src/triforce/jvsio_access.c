#include <triforce/jvsio_private.h>

u8* fn_80285778(void) {
    return &jvsio_bss_8067E2A0.nodeCount;
}

u8* fn_80285788(void) {
    return &jvsio_bss_80683280.unk12A;
}

JvsRing* fn_80285798(void) {
    return jvsio_bss_80683280.ring;
}

u8* fn_802857A8(void) {
    return &jvsio_bss_80683280.result;
}

JvsNode* fn_802857B8(void) {
    return jvsio_bss_8067E2A0.node;
}

void* fn_802857C8(void) {
    return &jvsio_bss_8067E2A0;
}

void* fn_802857D4(void) {
    return &jvsio_bss_80683280;
}
