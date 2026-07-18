typedef struct ItemSelect {
    unsigned char _pad[0x78];
    void *ui_helper;
} ItemSelect;

extern void fn_8023E2F8(void *);

void ItemSelect_DrawUIHelperIfActive(ItemSelect *item_select)
{
    if (item_select->ui_helper != 0) {
        fn_8023E2F8(item_select->ui_helper);
    }
}
