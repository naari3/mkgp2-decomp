#ifndef GAME_TYPES_CLCAMERA_H
#define GAME_TYPES_CLCAMERA_H

struct HSDObj;
struct Scene3DDesc;

struct clCamera {
    virtual ~clCamera();
    virtual int Ready();
    virtual void Render();
    void DebugFlush();
    void PrintTypeName();
    clCamera(const char *name);
    HSDObj *cobj; /* 0x04 */
    unsigned char flag8; /* 0x08 */
    unsigned char flag9; /* 0x09 */
    unsigned char flagA; /* 0x0A */
    float c; /* 0x0C */
    float d; /* 0x10 */
    unsigned char pad14[0x10];
    unsigned int ready; /* 0x24 */
    void *archive; /* 0x28 */
    Scene3DDesc *desc; /* 0x2C */
    unsigned char pad30[0x3004];
    unsigned char projection[0x48]; /* 0x3034 */
    float nearClip; /* 0x307C */
    float farClip; /* 0x3080 */
};

#endif
