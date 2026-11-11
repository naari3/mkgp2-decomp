#ifndef GAME_TYPES_HSD_DESC_H
#define GAME_TYPES_HSD_DESC_H

/*
 * Layouts of the HSD descriptors the game defines as static data and hands
 * to HSD_LObjLoadDesc / HSD_CObjLoadDesc (the same layouts as HSD_WObjDesc,
 * HSD_LightDesc and HSD_CObjDesc in libs/melee/src/sysdolphin/baselib).
 * Plain C types, so a data unit can use them without the HSD headers. The
 * 16-bit and 8-bit members are why these objects must not be written as
 * arrays of words: docs/notes/port_abi.md, "Static HSD descriptors".
 */
typedef struct BuiltinWObjDesc {
    /* 0x00 */ char *class_name;
    /* 0x04 */ float pos[3];
    /* 0x10 */ void *robjdesc;
} BuiltinWObjDesc;

typedef struct BuiltinLightDesc {
    /* 0x00 */ char *class_name;
    /* 0x04 */ struct BuiltinLightDesc *next;
    /* 0x08 */ unsigned short flags;
    /* 0x0A */ unsigned short attnflags;
    /* 0x0C */ unsigned char color[4];
    /* 0x10 */ BuiltinWObjDesc *position;
    /* 0x14 */ BuiltinWObjDesc *interest;
    /* 0x18 */ void *u; /* shininess / point / spot / attenuation */
} BuiltinLightDesc;

/* Perspective camera (projection_type 1). */
typedef struct BuiltinCObjDesc {
    /* 0x00 */ char *class_name;
    /* 0x04 */ unsigned short flags;
    /* 0x06 */ unsigned short projection_type;
    /* 0x08 */ short viewport[4];          /* xmin, xmax, ymin, ymax */
    /* 0x10 */ unsigned short scissor[4];  /* left, right, top, bottom */
    /* 0x18 */ BuiltinWObjDesc *eyepos;
    /* 0x1C */ BuiltinWObjDesc *interest;
    /* 0x20 */ float roll;
    /* 0x24 */ float *up_vector;
    /* 0x28 */ float nnear;
    /* 0x2C */ float ffar;
    /* 0x30 */ float fov;
    /* 0x34 */ float aspect;
} BuiltinCObjDesc;

/*
 * Static material description handed to HSD (the same layouts as
 * HSD_ImageDesc, HSD_TObjDesc, HSD_Material and HSD_MObjDesc). The image
 * itself is texture data, so it is an array of bytes.
 */
typedef struct BuiltinImageDesc {
    /* 0x00 */ void *img_ptr;
    /* 0x04 */ unsigned short width;
    /* 0x06 */ unsigned short height;
    /* 0x08 */ unsigned int format;
    /* 0x0C */ unsigned int mipmap;
    /* 0x10 */ float minLOD;
    /* 0x14 */ float maxLOD;
} BuiltinImageDesc;

typedef struct BuiltinTObjDesc {
    /* 0x00 */ char *class_name;
    /* 0x04 */ struct BuiltinTObjDesc *next;
    /* 0x08 */ int id;
    /* 0x0C */ int src;
    /* 0x10 */ float rotate[3];
    /* 0x1C */ float scale[3];
    /* 0x28 */ float translate[3];
    /* 0x34 */ int wrap_s;
    /* 0x38 */ int wrap_t;
    /* 0x3C */ unsigned char repeat_s;
    /* 0x3D */ unsigned char repeat_t;
    /* 0x3E */ unsigned char pad_3E[2];
    /* 0x40 */ unsigned int blend_flags;
    /* 0x44 */ float blending;
    /* 0x48 */ int magFilt;
    /* 0x4C */ BuiltinImageDesc *imagedesc;
    /* 0x50 */ void *tlutdesc;
    /* 0x54 */ void *lod;
    /* 0x58 */ void *tev;
} BuiltinTObjDesc;

typedef struct BuiltinMaterial {
    /* 0x00 */ unsigned char ambient[4];
    /* 0x04 */ unsigned char diffuse[4];
    /* 0x08 */ unsigned char specular[4];
    /* 0x0C */ float alpha;
    /* 0x10 */ float shininess;
} BuiltinMaterial;

typedef struct BuiltinMObjDesc {
    /* 0x00 */ char *class_name;
    /* 0x04 */ unsigned int rendermode;
    /* 0x08 */ BuiltinTObjDesc *texdesc;
    /* 0x0C */ BuiltinMaterial *mat;
    /* 0x10 */ void *renderdesc;
    /* 0x14 */ void *pedesc;
} BuiltinMObjDesc;

#endif
