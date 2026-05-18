extern void *fn_800A58A0(int key);

#pragma exceptions on
void *ItemRes_LookupByKey_Thunk(int key) {
    return fn_800A58A0(key);
}
#pragma exceptions reset
