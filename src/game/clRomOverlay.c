/* Observed list fields only; no assumptions about the remainder of clRom. */
typedef struct RomOverlayNode {
    int value;
    const char *name;
    unsigned char unknown08[4];
    struct RomOverlayNode *next;
} RomOverlayNode;

extern RomOverlayNode *g_romListHead;
extern const char lbl_802E9810[];
extern void OverlayText(int layer, int x, int y, const char *format, ...);

#pragma exceptions on
void clRom_DumpListOverlay(void)
{
    int index = 0;
    RomOverlayNode *node = g_romListHead;

    while (node != 0) {
        OverlayText(3, 1, index + 1, lbl_802E9810,
                    index, node->value, node->name);
        node = node->next;
        ++index;
    }
}
