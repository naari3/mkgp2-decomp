extern void *ItemRes_LookupDatPathByKey(int key);

#pragma exceptions on
void *ItemRes_LookupByKey_Thunk(int key) {
    return ItemRes_LookupDatPathByKey(key);
}
#pragma exceptions reset
