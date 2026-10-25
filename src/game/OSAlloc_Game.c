/*
 * Game-side copy of the Dolphin OS heap allocator, 0x8008E9A0..0x8008F07C.
 * Same layout as the SDK OSAlloc.c, but OSAllocFromHeap is best-fit and
 * OSCheckHeap reports through DebugPrintf.
 */

typedef struct Cell {
    struct Cell *prev;
    struct Cell *next;
    long size;
} Cell;

typedef struct HeapDesc {
    long size;
    Cell *free;
    Cell *allocated;
} HeapDesc;

extern void *lbl_806D11F8; /* TEXPalette total loaded size */
extern HeapDesc *lbl_806D1200; /* HeapArray */
extern int lbl_806D1204; /* NumHeaps */
extern void *lbl_806D1208; /* ArenaStart */
extern void *lbl_806D120C; /* ArenaEnd */
extern volatile int lbl_806CF010; /* __OSCurrHeap */
extern const char lbl_80313048[];

void DebugPrintf(const char *fmt, ...);

#define HeapArray lbl_806D1200
#define NumHeaps lbl_806D1204
#define ArenaStart lbl_806D1208
#define ArenaEnd lbl_806D120C
#define __OSCurrHeap lbl_806CF010

#define InRange(cell, arenaStart, arenaEnd) \
    ((unsigned long)arenaStart <= (unsigned long)cell) && ((unsigned long)cell < (unsigned long)arenaEnd)
#define OFFSET(n, a) (((unsigned long)(n)) & ((a)-1))

#define ASSERTREPORT(line, msg, cond) \
    if (!(cond)) { DebugPrintf(strings + (msg), line); return -1; }

void *TEXPalette_GetTotalLoadedSize(void)
{
    return lbl_806D11F8;
}

void MemoryHeap_GetStats(int heap, long *total, long *largest, long *count)
{
    Cell *cell;
    long sum = 0;
    long max = 0;
    long n = 0;

    for (cell = *(Cell **)((char *)HeapArray + heap * 12 + 4); cell != 0; cell = cell->next) {
        n++;
        sum += cell->size;
        if (max <= cell->size) {
            max = cell->size;
        }
    }
    *total = sum;
    *largest = max;
    *count = n;
}

#pragma exceptions on
long OSCheckHeap(int heap)
{
    HeapDesc *hd;
    Cell *cell;
    const char *strings = lbl_80313048;
    long total = 0;
    long free = 0;

    ASSERTREPORT(0x3BF, 0x78, HeapArray);
    ASSERTREPORT(0x3C0, 0x9C, 0 <= heap && heap < NumHeaps);
    hd = &HeapArray[heap];
    ASSERTREPORT(0x3C3, 0xD4, 0 <= hd->size);

    ASSERTREPORT(0x3C5, 0xFC, hd->allocated == 0 || hd->allocated->prev == 0);
    for (cell = hd->allocated; cell; cell = cell->next) {
        ASSERTREPORT(0x3C8, 0x14C, InRange(cell, ArenaStart, ArenaEnd));
        ASSERTREPORT(0x3C9, 0x18C, OFFSET(cell, 32) == 0);
        ASSERTREPORT(0x3CA, 0x1C4, cell->next == 0 || cell->next->prev == cell);
        ASSERTREPORT(0x3CB, 0x210, 64u <= cell->size);
        ASSERTREPORT(0x3CC, 0x244, OFFSET(cell->size, 32) == 0);
        total += cell->size;
        ASSERTREPORT(0x3CF, 0x284, 0 < total && total <= hd->size);
    }

    ASSERTREPORT(0x3D7, 0x2C0, hd->free == 0 || hd->free->prev == 0);
    for (cell = hd->free; cell; cell = cell->next) {
        ASSERTREPORT(0x3DA, 0x14C, InRange(cell, ArenaStart, ArenaEnd));
        ASSERTREPORT(0x3DB, 0x18C, OFFSET(cell, 32) == 0);
        ASSERTREPORT(0x3DC, 0x1C4, cell->next == 0 || cell->next->prev == cell);
        ASSERTREPORT(0x3DD, 0x210, 64u <= cell->size);
        ASSERTREPORT(0x3DE, 0x244, OFFSET(cell->size, 32) == 0);
        ASSERTREPORT(0x3DF, 0x308, cell->next == 0 || (char *)cell + cell->size < (char *)cell->next);
        total += cell->size;
        free = (cell->size + free);
        free -= 32;
        ASSERTREPORT(0x3E3, 0x284, 0 < total && total <= hd->size);
    }

    ASSERTREPORT(0x3EA, 0x368, total == hd->size);
    return free;
}
#pragma exceptions reset

void OSDestroyHeap(int heap)
{
    HeapDesc *hd = &HeapArray[heap];

    hd->size = -1;
    hd->free = hd->allocated = 0;
}

int OSCreateHeap(void *start, void *end)
{
    int heap;
    HeapDesc *hd;
    Cell *cell;

    start = (void *)(((unsigned long)start + 0x1FU) & ~31);
    end = (void *)(((unsigned long)end) & ~31);

    for (heap = 0; heap < NumHeaps; heap++) {
        hd = &HeapArray[heap];
        if (hd->size < 0) {
            hd->size = (unsigned long)end - (unsigned long)start;
            cell = start;
            cell->prev = 0;
            cell->next = 0;
            cell->size = hd->size;
            hd->free = cell;
            hd->allocated = 0;
            return heap;
        }
    }
    return -1;
}

void *OSInitAlloc(void *arenaStart, void *arenaEnd, int maxHeaps)
{
    unsigned long arraySize;
    int i;
    HeapDesc *hd;

    arraySize = maxHeaps * sizeof(HeapDesc);
    HeapArray = arenaStart;
    NumHeaps = maxHeaps;

    for (i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i];
        hd->size = -1;
        hd->free = hd->allocated = 0;
    }
    __OSCurrHeap = -1;
    arenaStart = (void *)((unsigned long)((char *)HeapArray + arraySize));
    arenaStart = (void *)(((unsigned long)arenaStart + 0x1F) & 0xFFFFFFE0);
    ArenaStart = arenaStart;
    ArenaEnd = (void *)((unsigned long)arenaEnd & 0xFFFFFFE0);
    return arenaStart;
}

int OSSetCurrentHeap(int heap)
{
    int prev;

    prev = __OSCurrHeap;
    __OSCurrHeap = heap;
    return prev;
}

static inline Cell *DLAddFront(Cell *list, Cell *cell)
{
    cell->next = list;
    cell->prev = 0;
    if (list) {
        list->prev = cell;
    }
    return cell;
}

static inline Cell *DLExtract(Cell *list, Cell *cell)
{
    if (cell->next) {
        cell->next->prev = cell->prev;
    }
    if (cell->prev == 0) {
        return cell->next;
    }
    cell->prev->next = cell->next;
    return list;
}

static inline Cell *DLInsert(Cell *list, Cell *cell)
{
    Cell *prev;
    Cell *next;

    for (next = list, prev = 0; next != 0; prev = next, next = next->next) {
        if (cell <= next) {
            break;
        }
    }

    cell->next = next;
    cell->prev = prev;
    if (next) {
        next->prev = cell;
        if ((unsigned char *)cell + cell->size == (unsigned char *)next) {
            cell->size += next->size;
            next = next->next;
            cell->next = next;
            if (next) {
                next->prev = cell;
            }
        }
    }
    if (prev) {
        prev->next = cell;
        if ((unsigned char *)prev + prev->size == (unsigned char *)cell) {
            prev->size += cell->size;
            prev->next = next;
            if (next) {
                next->prev = prev;
            }
        }
        return list;
    }
    return cell;
}

void OSFreeToHeap(int heap, void *ptr)
{
    HeapDesc *hd;
    Cell *cell;

    cell = (void *)((unsigned long)ptr - 0x20);
    hd = &HeapArray[heap];
    hd->allocated = DLExtract(hd->allocated, cell);
    hd->free = DLInsert(hd->free, cell);
}

void *OSAllocFromHeap(int heap, unsigned long size)
{
    HeapDesc *hd;
    Cell *cell;
    Cell *best;
    Cell *newCell;
    long leftoverSize;

    hd = &HeapArray[heap];
    size += 0x20;
    size = (size + 0x1F) & 0xFFFFFFE0;

    best = 0;
    for (cell = hd->free; cell != 0; cell = cell->next) {
        if ((signed)size <= (signed)cell->size) {
            if (best == 0 || best->size > cell->size) {
                best = cell;
            }
        }
    }
    cell = best;

    if (cell == 0) {
        return 0;
    }

    leftoverSize = cell->size - size;
    if (leftoverSize < 0x40U) {
        hd->free = DLExtract(hd->free, cell);
    } else {
        cell->size = size;
        newCell = (void *)((unsigned char *)cell + size);
        newCell->size = leftoverSize;
        newCell->prev = cell->prev;
        newCell->next = cell->next;
        if (newCell->next != 0) {
            newCell->next->prev = newCell;
        }
        if (newCell->prev != 0) {
            newCell->prev->next = newCell;
        } else {
            hd->free = newCell;
        }
    }

    hd->allocated = DLAddFront(hd->allocated, cell);
    return (unsigned char *)cell + 0x20;
}

int fn_8008F074(void)
{
    return 1;
}
