#include "objalloc.h"

#include <string.h>

s32 HSD_GetNbBits(u32 x);

#include "memory.h"

static objheap obj_heap = { 0, 0, -1, -1 };

static HSD_ObjAllocData* alloc_datas;

void HSD_ObjSetHeap(u32 size, void* ptr)
{
    obj_heap.curr = (uintptr_t) ptr;
    obj_heap.top = (uintptr_t) ptr;
    obj_heap.remain = size;
    obj_heap.size = size;
}

void* HSD_ObjAlloc(HSD_ObjAllocData* data)
{
    if (data->num_limit_flag && data->used >= data->num_limit) {
        return NULL;
    }
    data->used++;
    if (data->used > data->peak) {
        data->peak = data->used;
    }
    return HSD_MemAlloc(data->size);
}

void HSD_ObjFree(HSD_ObjAllocData* data, void* obj)
{
    data->used -= 1;
    HSD_Free(obj);
}

static inline void removeAll(HSD_ObjAllocData* data)
{
    HSD_ObjAllocData** cur = &alloc_datas;
    while (*cur != NULL) {
        if (*cur == data) {
            *cur = (*cur)->next;
        } else {
            cur = &(*cur)->next;
        }
    }
}

void HSD_ObjAllocInit(HSD_ObjAllocData* data, size_t size, u32 align)
{
    HSD_ASSERT(235, data);
    if (data != NULL) {
        removeAll(data);
    } else {
        alloc_datas = NULL;
    }
    memset(data, 0, sizeof(HSD_ObjAllocData));
    data->num_limit = -1;
    data->heap_limit_size = 0;
    data->heap_limit_num = -1;
    HSD_ASSERT(246, align <= 32);
    HSD_ASSERT(247, HSD_GetNbBits(align) == 1);
    data->align = align;
    data->size = (size + (data->align - 1)) & ~(data->align - 1);
    data->next = alloc_datas;
    alloc_datas = data;
}
