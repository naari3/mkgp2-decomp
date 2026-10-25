/*
 * Asset_LoadAndDecompressByType, 0x80048C34..0x80048E0C: decodes a THP
 * still image into one of four output layouts.
 */

typedef struct THPDecHandle {
    void *data;
    void *info;
} THPDecHandle;

extern const char lbl_802EB4E0[]; /* string pool */
extern const char lbl_806D26B8[8]; /* "[%02X]\n" */
extern unsigned char *lbl_806D1070;
extern volatile int lbl_806CF010; /* __OSCurrHeap */

void DebugPrintf(const char *fmt, ...);
long THPDecGetInfo(unsigned char *data, void *desc);
unsigned long THPDecGetWorkSize(void *desc);
long THPVideoDecode(THPDecHandle *handle, unsigned char *statusOut, void *work, void *data, void *desc);
void THPDecDecode(THPDecHandle *handle, void *tileY, void *tileU, void *tileV);
void fn_8029B54C(THPDecHandle *handle, unsigned char *dst, unsigned long width, unsigned long height);
void fn_8029BA2C(THPDecHandle *handle, unsigned char *tileY, unsigned char *tileU, unsigned char *tileV);
void fn_8029BCF0(THPDecHandle *handle, unsigned char *dst, unsigned char alpha);
void *OSAllocFromHeap(int heap, unsigned long size);
void OSFreeToHeap(int heap, void *ptr);

#pragma exceptions on

int Asset_LoadAndDecompressByType(unsigned char *data, void *desc, void *dst, void *tileU, void *tileV,
                                  signed char type, unsigned long width, unsigned long height,
                                  unsigned char alpha)
{
    const char *strings = lbl_802EB4E0;
    THPDecHandle handle;
    unsigned char status;
    void *work;

    if ((signed char)lbl_806D1070[0x80018] == 0) {
        return 0;
    }
    if ((int)data[0] == 0x3C) {
        DebugPrintf(strings + 0x3B8, data);
        return 0;
    }
    if (data[0] != 0xFF) {
        DebugPrintf(lbl_806D26B8, data[0]);
        return 0;
    }
    if (THPDecGetInfo(data, desc) == 0) {
        DebugPrintf(strings + 0x3C4);
        return 0;
    }
    work = OSAllocFromHeap(lbl_806CF010, THPDecGetWorkSize(desc));
    if (work == 0) {
        DebugPrintf(strings + 0x3EC);
        return 0;
    }
    if (THPVideoDecode(&handle, &status, work, data, desc) == 0) {
        OSFreeToHeap(lbl_806CF010, work);
        DebugPrintf(strings + 0x410, status);
        return 0;
    }
    switch (type) {
    case 0:
        THPDecDecode(&handle, dst, tileU, tileV);
        break;
    case 1:
        fn_8029B54C(&handle, dst, width, height);
        break;
    case 2:
        fn_8029BA2C(&handle, dst, tileU, tileV);
        break;
    case 3:
        fn_8029BCF0(&handle, dst, alpha);
        break;
    }
    OSFreeToHeap(lbl_806CF010, work);
    return 1;
}

#pragma exceptions reset
