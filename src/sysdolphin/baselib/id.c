typedef unsigned int u32;
typedef int s32;
typedef u32 HSD_IDKey;

#define NULL ((void*)0)

extern void __assert(const char* file, int line, const char* cond);
extern void* memset(void* dest, int ch, unsigned long count);

typedef struct _HSD_ObjAllocData {
    u32 num_limit_flag : 1;
    u32 heap_limit_flag : 1;
    void* freehead;
    u32 used;
    u32 free;
    u32 peak;
    u32 num_limit;
    u32 heap_limit_size;
    u32 heap_limit_num;
    u32 size;
    u32 align;
    struct _HSD_ObjAllocData* next;
} HSD_ObjAllocData;

void HSD_ObjAllocInit(HSD_ObjAllocData* data, u32 size, u32 align);
void* HSD_ObjAlloc(HSD_ObjAllocData* data);
void HSD_ObjFree(HSD_ObjAllocData* data, void* obj);

typedef struct _IDEntry {
    struct _IDEntry* next;
    HSD_IDKey id;
    void* data;
} IDEntry;

typedef struct _HSD_IDTable {
    struct _IDEntry* table[101];
} HSD_IDTable;

HSD_ObjAllocData hsd_iddata;

HSD_IDTable default_table;

static inline HSD_ObjAllocData* HSD_IDGetAllocData(void)
{
    return &hsd_iddata;
}

void HSD_IDInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_IDGetAllocData(), sizeof(IDEntry), 4);
}

void HSD_IDSetup(void)
{
    memset(&default_table, 0, sizeof(HSD_IDTable));
}

static inline u32 hash(HSD_IDKey id)
{
    return id % 0x65;
}

static inline IDEntry* IDEntryAlloc(void)
{
    IDEntry* entry;

    entry = HSD_ObjAlloc(HSD_IDGetAllocData());
    if (!entry) {
        __assert("id.c", 67, "entry");
    }
    memset(entry, 0, sizeof(IDEntry));

    return entry;
}

void HSD_IDInsertToTable(HSD_IDTable* table, HSD_IDKey id, void* data)
{
    IDEntry* entry;

    if (table == NULL) {
        table = &default_table;
    }

    entry = table->table[hash(id)];
    while (entry != NULL) {
        if (entry->id == id) {
            break;
        }
        entry = entry->next;
    }

    if (entry != NULL) {
        entry->id = id;
        entry->data = data;
    } else {
        entry = IDEntryAlloc();
        entry->id = id;
        entry->data = data;
        entry->next = table->table[hash(id)];
        table->table[hash(id)] = entry;
    }
}

static inline void IDEntryFree(IDEntry* entry)
{
    HSD_ObjFree(HSD_IDGetAllocData(), entry);
}

void HSD_IDRemoveByIDFromTable(HSD_IDTable* table, HSD_IDKey id)
{
    IDEntry* entry;
    IDEntry* prev;

    if (table == NULL) {
        table = &default_table;
    }

    prev = NULL;
    for (entry = table->table[hash(id)]; entry != NULL; entry = entry->next) {
        if (entry->id == id) {
            if (prev != NULL) {
                prev->next = entry->next;
            } else {
                table->table[hash(id)] = entry->next;
            }
            IDEntryFree(entry);
            return;
        }
        prev = entry;
    }
}

void* HSD_IDGetDataFromTable(HSD_IDTable* table, HSD_IDKey id, s32* success)
{
    IDEntry* entry;

    if (table == NULL) {
        table = &default_table;
    }

    entry = table->table[hash(id)];
    while (entry != NULL) {
        if (entry->id == id) {
            if (success != NULL) {
                *success = 1;
            }
            return entry->data;
        }
        entry = entry->next;
    }

    if (success != NULL) {
        *success = 0;
    }
    return NULL;
}
