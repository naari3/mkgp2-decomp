#include "alloc.h"
#include "critical_regions.h"
#include <cstring>

#include "global.h"

typedef struct Block {
    struct Block* prev;
    struct Block* next;
    unsigned long max_size;
    unsigned long size;
} Block;

typedef struct SubBlock {
    unsigned long size;
    Block* block;
    struct SubBlock* prev;
    struct SubBlock* next;
} SubBlock;

struct FixSubBlock;

typedef struct FixBlock {
    struct FixBlock* prev_;
    struct FixBlock* next_;
    unsigned long client_size_;
    struct FixSubBlock* start_;
    unsigned long n_allocated_;
} FixBlock;

typedef struct FixSubBlock {
    FixBlock* block_;
    struct FixSubBlock* next_;
} FixSubBlock;

typedef struct FixStart {
    FixBlock* tail_;
    FixBlock* head_;
} FixStart;

typedef struct __mem_pool_obj {
    Block* start_;
    FixStart fix_start[6];
} __mem_pool_obj;

typedef struct __mem_pool {
    void* reserved[14];
} __mem_pool;

typedef long tag_word;

typedef struct block_header {
    tag_word tag;
    struct block_header* prev;
    struct block_header* next;
} block_header;

typedef struct list_header {
    block_header* rover;
    block_header header;
} list_header;

typedef struct heap_header {
    struct heap_header* prev;
    struct heap_header* next;
} heap_header;

struct mem_pool_obj;
typedef void* (*sys_alloc_ptr)(unsigned long, struct mem_pool_obj*);
typedef void (*sys_free_ptr)(void*, struct mem_pool_obj*);

typedef struct pool_options {
    sys_alloc_ptr sys_alloc_func;
    sys_free_ptr sys_free_func;
    unsigned long min_heap_size;
    int always_search_first;
} pool_options;

typedef struct mem_pool_obj {
    list_header free_list;
    pool_options options;
    heap_header* heap_list;
    void* userData;

} mem_pool_obj;


static SubBlock* SubBlock_merge_prev(SubBlock*, SubBlock**);
static void SubBlock_merge_next(SubBlock*, SubBlock**);

static const unsigned long fix_pool_sizes[] = {4, 12, 20, 36, 52, 68};

#define SubBlock_size(ths) ((ths)->size & 0xFFFFFFF8)
#define SubBlock_block(ths) ((Block*)((unsigned long)((ths)->block) & ~0x1))
#define Block_size(ths) ((ths)->size & 0xFFFFFFF8)
#define Block_start(ths) (*(SubBlock**)((char*)(ths) + Block_size((ths)) - sizeof(unsigned long)))

#define SubBlock_set_free(ths)                                                                     \
    unsigned long this_size = SubBlock_size((ths));                                                \
    (ths)->size &= ~0x2;                                                                           \
    *(unsigned long*)((char*)(ths) + this_size) &= ~0x4;                                           \
    *(unsigned long*)((char*)(ths) + this_size - sizeof(unsigned long)) = this_size

#define SubBlock_is_free(ths) !((ths)->size & 2)
#define SubBlock_set_size(ths, sz)                                                                 \
    (ths)->size &= ~0xFFFFFFF8;                                                                    \
    (ths)->size |= (sz) & 0xFFFFFFF8;                                                              \
    if (SubBlock_is_free((ths)))                                                                   \
    *(unsigned long*)((char*)(ths) + (sz) - sizeof(unsigned long)) = (sz)

#define SubBlock_from_pointer(ptr) ((SubBlock*)((char*)(ptr)-8))
#define FixSubBlock_from_pointer(ptr) ((FixSubBlock*)((char*)(ptr)-4))

#define FixBlock_client_size(ths) ((ths)->client_size_)
#define FixSubBlock_size(ths) (FixBlock_client_size((ths)->block_))

#define classify(ptr) (*(unsigned long*)((char*)(ptr) - sizeof(unsigned long)) & 1)
#define __msize_inline(ptr)                                                                        \
    (!classify(ptr) ? FixSubBlock_size(FixSubBlock_from_pointer(ptr)) :                            \
                      SubBlock_size(SubBlock_from_pointer(ptr)) - 8)

#define Block_empty(ths)                                                                           \
    (_sb = (SubBlock*)((char*)(ths) + 16)),                                                        \
        SubBlock_is_free(_sb) && SubBlock_size(_sb) == Block_size((ths)) - 24

void* __sys_alloc(unsigned long size);
void __sys_free(void* ptr);

#define SubBlock_set_not_free(ths)                                                                 \
    unsigned long this_size = SubBlock_size((ths));                                                \
    (ths)->size |= 0x2;                                                                            \
    *(unsigned long*)((char*)(ths) + this_size) |= 0x4

static void Block_link(Block* ths, SubBlock* sb);

static inline void SubBlock_construct(SubBlock* ths, unsigned long size, Block* bp, int prev_alloc,
                                      int this_alloc) {
    ths->block = (Block*)((unsigned long)bp | 1);
    ths->size = size;
    if (prev_alloc)
        ths->size |= 4;
    if (this_alloc) {
        ths->size |= 2;
        *(unsigned long*)((char*)ths + size) |= 4;
    } else {
        *(unsigned long*)((char*)ths + size - sizeof(unsigned long)) = size;
    }
}

static inline SubBlock* SubBlock_split(SubBlock* ths, unsigned long sz) {
    unsigned long origsize = SubBlock_size(ths);
    int isfree = SubBlock_is_free(ths);
    int isprevalloc = ths->size & 4;
    Block* bp = SubBlock_block(ths);
    SubBlock* np = (SubBlock*)((char*)ths + sz);
    SubBlock_construct(ths, sz, bp, isprevalloc, !isfree);
    SubBlock_construct(np, origsize - sz, bp, !isfree, !isfree);
    if (isfree) {
        np->next = ths->next;
        np->next->prev = np;
        np->prev = ths;
        ths->next = np;
    }
    return np;
}

static void Block_construct(Block* ths, unsigned long size) {
    SubBlock* sb;

    ths->size = size | 3;
    *(unsigned long*)((char*)ths + size - 2 * sizeof(unsigned long)) = ths->size;
    sb = (SubBlock*)((char*)ths + 16);
    SubBlock_construct(sb, size - 24, ths, 0, 0);
    ths->max_size = size - 24;
    Block_start(ths) = 0;
    Block_link(ths, sb);
}

static inline void Block_unlink(Block* ths, SubBlock* sb) {
    SubBlock** st;
    SubBlock_set_not_free(sb);
    st = &Block_start(ths);

    if (*st == sb)
        *st = sb->next;
    if (*st == sb) {
        *st = 0;
        ths->max_size = 0;
    } else {
        sb->next->prev = sb->prev;
        sb->prev->next = sb->next;
    }
}

static SubBlock* Block_subBlock(Block* ths, unsigned long size) {
    SubBlock* st;
    SubBlock* sb;
    unsigned long sb_size;
    unsigned long max_found;

    st = Block_start(ths);
    if (st == 0) {
        ths->max_size = 0;
        return 0;
    }

    sb = st;
    sb_size = SubBlock_size(sb);
    max_found = sb_size;
    while (sb_size < size) {
        sb = sb->next;
        sb_size = SubBlock_size(sb);
        if (max_found < sb_size)
            max_found = sb_size;
        if (sb == st) {
            ths->max_size = max_found;
            return 0;
        }
    }

    if (sb_size - size >= 0x50)
        SubBlock_split(sb, size);

    Block_start(ths) = sb->next;
    Block_unlink(ths, sb);
    return sb;
}

static void Block_link(Block* ths, SubBlock* sb) {
    SubBlock** st;
    SubBlock_set_free(sb);
    st = &Block_start(ths);

    if (*st != 0) {
        sb->prev = (*st)->prev;
        sb->prev->next = sb;
        sb->next = *st;
        (*st)->prev = sb;
        *st = sb;
        *st = SubBlock_merge_prev(*st, st);
        SubBlock_merge_next(*st, st);
    } else {
        *st = sb;
        sb->prev = sb;
        sb->next = sb;
    }
    if (ths->max_size < SubBlock_size(*st))
        ths->max_size = SubBlock_size(*st);
}

static SubBlock* SubBlock_merge_prev(SubBlock* ths, SubBlock** start) {
    unsigned long prevsz;
    SubBlock* p;

    if (!(ths->size & 0x04)) {
        prevsz = *(unsigned long*)((char*)ths - sizeof(unsigned long));
        if (prevsz & 0x2)
            return ths;
        p = (SubBlock*)((char*)ths - prevsz);
        SubBlock_set_size(p, prevsz + SubBlock_size(ths));

        if (*start == ths)
            *start = (*start)->next;
        ths->next->prev = ths->prev;
        ths->next->prev->next = ths->next;
        return p;
    }
    return ths;
}

static void SubBlock_merge_next(SubBlock* pBlock, SubBlock** pStart) {
    SubBlock* next_sub_block;
    unsigned long this_cur_size;

    next_sub_block = (SubBlock*)((char*)pBlock + (pBlock->size & 0xFFFFFFF8));

    if (!(next_sub_block->size & 2)) {
        this_cur_size = (pBlock->size & 0xFFFFFFF8) + (next_sub_block->size & 0xFFFFFFF8);

        pBlock->size &= ~0xFFFFFFF8;
        pBlock->size |= this_cur_size & 0xFFFFFFF8;

        if (!(pBlock->size & 2)) {
            *(unsigned long*)((char*)(pBlock) + (this_cur_size)-4) = (this_cur_size);
        }

        if (!(pBlock->size & 2)) {
            *(unsigned long*)((char*)pBlock + this_cur_size) &= ~4;
        } else {
            *(unsigned long*)((char*)pBlock + this_cur_size) |= 4;
        }

        if (*pStart == next_sub_block) {
            *pStart = (*pStart)->next;
        }

        if (*pStart == next_sub_block) {
            *pStart = 0;
        }

        next_sub_block->next->prev = next_sub_block->prev;
        next_sub_block->prev->next = next_sub_block->next;
    }
}

static Block* __unlink(__mem_pool_obj* pool_obj, Block* bp) {
    Block* result = bp->next;
    if (result == bp) {
        result = 0;
    }

    if (pool_obj->start_ == bp) {
        pool_obj->start_ = result;
    }

    if (result != 0) {
        result->prev = bp->prev;
        result->prev->next = result;
    }

    bp->next = 0;
    bp->prev = 0;
    return result;
}

static inline void link(__mem_pool_obj* pool_obj, Block* bp) {
    if (pool_obj->start_ != 0) {
        bp->prev = pool_obj->start_->prev;
        bp->prev->next = bp;
        bp->next = pool_obj->start_;
        pool_obj->start_->prev = bp;
        pool_obj->start_ = bp;
    } else {
        pool_obj->start_ = bp;
        bp->prev = bp;
        bp->next = bp;
    }
}

static Block* link_new_block(__mem_pool_obj* pool_obj, unsigned long size) {
    Block* bp;

    size = (size + 24 + 7) & ~7;
    if (size < 0x10000)
        size = 0x10000;

    bp = (Block*)__sys_alloc(size);
    if (bp == 0)
        return 0;

    Block_construct(bp, size);
    link(pool_obj, bp);
    return bp;
}

static void* allocate_from_var_pools(__mem_pool_obj* pool_obj, unsigned long size) {
    Block* bp;
    void* ptr;

    size = (size + 8 + 7) & ~7;
    if (size < 0x50)
        size = 0x50;

    bp = pool_obj->start_ != 0 ? pool_obj->start_ : link_new_block(pool_obj, size);
    if (bp == 0)
        return 0;

    do {
        if (size <= bp->max_size) {
            ptr = Block_subBlock(bp, size);
            if (ptr != 0) {
                pool_obj->start_ = bp;
                goto found;
            }
        }
        bp = bp->next;
    } while (bp != pool_obj->start_);

    bp = link_new_block(pool_obj, size);
    if (bp == 0)
        return 0;
    ptr = Block_subBlock(bp, size);
found:
    return (char*)ptr + 8;
}

static void* soft_allocate_from_var_pools(__mem_pool_obj* pool_obj, unsigned long size,
                                          unsigned long* max_size) {
    Block* bp;
    void* ptr;

    size = (size + 8 + 7) & ~7;
    if (size < 0x50)
        size = 0x50;

    *max_size = 0;
    bp = pool_obj->start_;
    if (bp == 0)
        return 0;

    do {
        if (size <= bp->max_size) {
            ptr = Block_subBlock(bp, size);
            if (ptr != 0) {
                pool_obj->start_ = bp;
                goto found;
            }
        }
        if (bp->max_size > 8 && *max_size < bp->max_size - 8)
            *max_size = bp->max_size - 8;
        bp = bp->next;
    } while (bp != pool_obj->start_);

    return 0;
found:
    return (char*)ptr + 8;
}

static void deallocate_from_var_pools(__mem_pool_obj* pool_obj, void* ptr) {
    SubBlock* sb = SubBlock_from_pointer(ptr);
    SubBlock* _sb;

    Block* bp = SubBlock_block(sb);
    Block_link(bp, sb);

    if (Block_empty(bp)) {
        __unlink(pool_obj, bp);
        __sys_free(bp);
    }
}

inline void __init_pool_obj(__mem_pool* pool_obj) {
    memset(pool_obj, 0, sizeof(__mem_pool_obj));
}

static inline __mem_pool* get_malloc_pool(void) {
    static __mem_pool protopool;
    static unsigned char init = 0;
    if (!init) {
        __init_pool_obj(&protopool);
        init = 1;
    }

    return &protopool;
}

static inline void FixBlock_construct(FixBlock* ths, unsigned long client_size, void* chunk,
                                      unsigned long chunk_size, FixBlock* prev, FixBlock* next) {
    unsigned long fixSubBlock_size;
    unsigned long n;
    char* p;
    unsigned long i;
    char* np;

    ths->prev_ = prev;
    ths->next_ = next;
    prev->next_ = ths;
    next->prev_ = ths;
    ths->client_size_ = client_size;
    fixSubBlock_size = client_size + 4;
    n = (chunk_size - sizeof(FixBlock)) / fixSubBlock_size;
    p = (char*)chunk + sizeof(FixBlock);
    for (i = 0; i < n - 1; ++i) {
        np = p + fixSubBlock_size;
        ((FixSubBlock*)p)->block_ = ths;
        ((FixSubBlock*)p)->next_ = (FixSubBlock*)np;
        p = np;
    }
    ((FixSubBlock*)p)->block_ = ths;
    ((FixSubBlock*)p)->next_ = 0;
    ths->start_ = (FixSubBlock*)((char*)ths + sizeof(FixBlock));
    ths->n_allocated_ = 0;
}

static void* allocate_from_fixed_pools(__mem_pool_obj* pool_obj, unsigned long size) {
    unsigned long i = 0;
    FixSubBlock* p;
    FixStart* fs;

    while (size > fix_pool_sizes[i])
        ++i;

    fs = &pool_obj->fix_start[i];
    if (fs->head_ == 0 || fs->head_->start_ == 0) {
        void* newblock;
        unsigned long size_received;
        unsigned long n = 0xFEC / (fix_pool_sizes[i] + 4);
        unsigned long nsave;

        if (n > 256)
            n = 256;
        nsave = n;
        while (n >= 10) {
            newblock = soft_allocate_from_var_pools(
                pool_obj, n * (fix_pool_sizes[i] + 4) + sizeof(FixBlock),
                &size_received);
            if (newblock != 0)
                break;
            if (size_received > sizeof(FixBlock))
                n = (size_received - sizeof(FixBlock)) / (fix_pool_sizes[i] + 4);
            else
                n = 0;
        }
        if (newblock == 0 && n < nsave) {
            newblock = allocate_from_var_pools(
                pool_obj, nsave * (fix_pool_sizes[i] + 4) + sizeof(FixBlock));
            if (newblock == 0)
                return 0;
        }

        size = __msize_inline(newblock);
        if (fs->head_ == 0) {
            fs->head_ = (FixBlock*)newblock;
            fs->tail_ = (FixBlock*)newblock;
        }
        FixBlock_construct((FixBlock*)newblock, fix_pool_sizes[i], newblock, size, fs->tail_,
                           fs->head_);
        fs->head_ = (FixBlock*)newblock;
    }

    p = fs->head_->start_;
    fs->head_->start_ = p->next_;
    ++fs->head_->n_allocated_;
    if (fs->head_->start_ == 0) {
        fs->head_ = fs->head_->next_;
        fs->tail_ = fs->tail_->next_;
    }
    return (char*)p + 4;
}

void deallocate_from_fixed_pools(__mem_pool_obj* pool_obj, void* ptr, unsigned long size) {
    unsigned long i = 0;
    FixSubBlock* p;
    FixBlock* b;
    FixStart* fs;

    while (size > fix_pool_sizes[i]) {
        ++i;
    }

    fs = &pool_obj->fix_start[i];
    p = FixSubBlock_from_pointer(ptr);
    b = p->block_;

    if (b->start_ == 0 && fs->head_ != b) {
        if (fs->tail_ == b) {
            fs->head_ = fs->head_->prev_;
            fs->tail_ = fs->tail_->prev_;
        } else {
            b->prev_->next_ = b->next_;
            b->next_->prev_ = b->prev_;
            b->next_ = fs->head_;
            b->prev_ = b->next_->prev_;
            b->prev_->next_ = b;
            b->next_->prev_ = b;
            fs->head_ = b;
        }
    }

    p->next_ = b->start_;
    b->start_ = p;

    if (--b->n_allocated_ == 0) {
        if (fs->head_ == b) {
            fs->head_ = b->next_;
        }

        if (fs->tail_ == b) {
            fs->tail_ = b->prev_;
        }

        b->prev_->next_ = b->next_;
        b->next_->prev_ = b->prev_;

        if (fs->head_ == b) {
            fs->head_ = 0;
        }

        if (fs->tail_ == b) {
            fs->tail_ = 0;
        }

        deallocate_from_var_pools(pool_obj, b);
    }
}

void* __pool_alloc(__mem_pool* pool, size_t size) {
    __mem_pool_obj* pool_obj;

    if (size == 0)
        return 0;
    if (size > (size_t)-0x31)
        return 0;

    pool_obj = (__mem_pool_obj*)pool;
    if (size <= 68)
        return allocate_from_fixed_pools(pool_obj, size);
    return allocate_from_var_pools(pool_obj, size);
}

void __pool_free(__mem_pool* pool, void* ptr) {
    __mem_pool_obj* pool_obj;
    unsigned long size;

    if (ptr == 0) {
        return;
    }

    pool_obj = (__mem_pool_obj*)pool;
    size = __msize_inline(ptr);

    if (size <= 68) {
        deallocate_from_fixed_pools(pool_obj, ptr, size);
    } else {
        deallocate_from_var_pools(pool_obj, ptr);
    }
}

void* malloc(size_t size) {
    void* result;
    __begin_critical_region(malloc_pool_access);
    result = __pool_alloc(get_malloc_pool(), size);
    __end_critical_region(malloc_pool_access);
    return result;
}

void free(void* ptr) {
    __begin_critical_region(malloc_pool_access);
    __pool_free(get_malloc_pool(), ptr);
    __end_critical_region(malloc_pool_access);
}
