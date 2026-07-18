extern void *GetItemDataEntry(int id);

void *GetItemDataEntry_Bounded(int id)
{
    if (id >= 0x115) {
        return 0;
    }
    return GetItemDataEntry(id);
}
