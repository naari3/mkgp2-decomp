#ifndef FLASH_FADE_OVERLAY_PRIVATE_H
#define FLASH_FADE_OVERLAY_PRIVATE_H
#include <dolphin/mtx.h>
struct FlashOverlay { unsigned char unused, enabled; unsigned short pad; void *texture; };
struct FlashVectors { unsigned char prefix[0x80]; Vec eye, up, target; };
extern struct FlashVectors lbl_8030E598;
#endif
