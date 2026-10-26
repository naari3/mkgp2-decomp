/* Redraw the item box debris through GX channel 2, unbinding whatever
 * channel was bound before and after. */
typedef struct GXChannel GXChannel;

typedef struct clItemBoxResponder {
    void *debris; /* 0x00 */
} clItemBoxResponder;

extern int lbl_806CEEA0; /* bound channel index, -1 = none */
extern GXChannel *lbl_806D10B0;
extern GXChannel *lbl_806D10B4;
extern GXChannel *lbl_806D10B8;
extern char lbl_802EDEF8[];
extern char lbl_802EDF14[];
extern void DebugPrintf(const char *fmt, ...);
extern int GXChannel_Bind(GXChannel *ch);
extern int GXChannel_Unbind(GXChannel *ch);
extern void clItemBoxResponder_DrawDebris(void *debris);

static inline void GXChannel_UnbindCurrent(void)
{
    switch (lbl_806CEEA0) {
    case 0:
        GXChannel_Unbind(lbl_806D10B4);
        break;
    case 1:
        GXChannel_Unbind(lbl_806D10B0);
        break;
    case 2:
        GXChannel_Unbind(lbl_806D10B8);
        break;
    default:
        DebugPrintf(lbl_802EDF14);
        break;
    }
    lbl_806CEEA0 = -1;
}

void clItemBoxResponder_Rebind(clItemBoxResponder *self)
{
    if (lbl_806CEEA0 != -1) {
        DebugPrintf(lbl_802EDEF8);
        GXChannel_UnbindCurrent();
    }
    GXChannel_Bind(lbl_806D10B8);
    lbl_806CEEA0 = 2;
    clItemBoxResponder_DrawDebris(self->debris);
    GXChannel_UnbindCurrent();
}
