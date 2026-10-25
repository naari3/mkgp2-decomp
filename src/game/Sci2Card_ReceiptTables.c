/* Receipt string and font-page table lookups, 0x80099958..0x80099994. */
extern char lbl_80318138[][0xD];
extern void *lbl_80401018[];

char *Sci2Card_GetReceiptStringEntry(int index)
{
    return lbl_80318138[index];
}

void *CardPrintJob_GetFontPagePayload(int page)
{
    page++;
    if (page >= 0x3F) {
        return 0;
    }
    return lbl_80401018[page];
}
