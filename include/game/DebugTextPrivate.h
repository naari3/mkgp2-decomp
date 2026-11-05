#ifndef GAME_DEBUGTEXTPRIVATE_H
#define GAME_DEBUGTEXTPRIVATE_H
/* OSFontHeader layout from dolphin/os/OSFont.h, restricted to used fields.
 * dolphin/types.h currently includes libc headers unavailable to this TU. */
typedef struct DebugFontHeader {
    unsigned short fontType, firstChar, lastChar, invalChar;
    unsigned short ascent, descent, width, leading, cellWidth, cellHeight;
    unsigned int sheetSize;
    unsigned short sheetFormat, sheetColumn, sheetRow, sheetWidth, sheetHeight;
} DebugFontHeader;
typedef float Mtx[3][4];
typedef float Mtx44[4][4];

typedef struct DebugTextEntry {
    int x, y;
    unsigned char color;
    char pad09[3];
    float scale;
    char text[0x74];
} DebugTextEntry;

typedef struct DebugDisplayContext {
    DebugFontHeader *font;
    DebugTextEntry current;
    DebugTextEntry *entries;
    int count;
    int cull;
    float projection[7];
    float viewport[6];
    unsigned int scissor[4];
} DebugDisplayContext;

extern const unsigned char kDbgColorPalette[0x78];
extern const float lbl_806DA278, lbl_806DA27C, lbl_806DA280;
extern const float lbl_806DA284, lbl_806DA288;
void GXGetCullMode(int *);
void GXGetProjectionv(float *);
void GXGetViewportv(float *);
void GXGetScissor(unsigned int *, unsigned int *, unsigned int *, unsigned int *);
void GXSetChanCtrl(int, int, int, int, unsigned int, int, int);
void C_MTXOrtho(Mtx44, float, float, float, float, float, float);
void GXSetProjection(const Mtx44, int);
void GXSetViewport(float, float, float, float, float, float);
void GXSetScissor(unsigned int, unsigned int, unsigned int, unsigned int);
void PSMTXIdentity(Mtx);
void GXLoadPosMtxImm(const Mtx, unsigned int);
void GXSetCurrentMtx(unsigned int);
void PSMTXScale(Mtx, float, float, float);
void GXLoadTexMtxImm(const Mtx, unsigned int, int);
void GXSetNumTexGens(unsigned char);
void GXSetTexCoordGen2(int, int, int, unsigned int, unsigned char, unsigned int);
void GXSetCullMode(int);
void GXSetZMode(unsigned char, int, unsigned char);
void GXSetNumChans(unsigned char);
void GXSetNumTevStages(unsigned char);
void GXSetTevOp(int, int);
void GXSetTevOrder(int, int, int, int);
void GXSetBlendMode(int, int, int, int);
void GXClearVtxDesc(void);
void GXSetVtxDescv(const void *);
void GXSetVtxAttrFmtv(int, const void *);
void GXSetArray(int, void *, unsigned char);
void GXSetProjectionv(const float *);
void TextRenderer_DrawEntry(DebugDisplayContext *, DebugTextEntry *);
#endif
