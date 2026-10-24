class ItemBehavior {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual int GetState();
    virtual void Dispatch(int id, int arg);
};

struct ItemObject {
    unsigned char pad[0x308];
    ItemBehavior *behavior;
};

extern "C" {
int ItemAlias_DestToSource(int, int);
unsigned char ItemAliasTable_LookupSlotIndex(unsigned char);

void ItemObject_DispatchVtable1C_IfBoundedItem(ItemObject *item, int id, int arg) {
    if (item != 0 && id != -1) {
        if (ItemAliasTable_LookupSlotIndex(ItemAlias_DestToSource(id, 0)) < 0x44) {
            item->behavior->Dispatch(id, arg);
        }
    }
}

int ItemObject_DispatchVtable18_GetState(ItemObject *item) {
    if (item != 0) {
        return item->behavior->GetState();
    }
    return -1;
}
}
