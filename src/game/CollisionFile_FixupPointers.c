/* Relocate the pointer pairs in the collision file's 16-byte table entries. */
unsigned int CollisionFile_FixupPointers(unsigned int file_base) {
    int offset;
    int second_offset;
    unsigned int *table;
    unsigned int first;

    *(unsigned int *)(file_base + 0x28) += file_base;
    offset = 0;
    while (table = *(unsigned int **)(file_base + 0x28),
           (first = *(unsigned int *)((char *)table + offset)) != 0) {
        *(unsigned int *)((char *)table + offset) = first + file_base;
        second_offset = offset + 8;
        offset += 0x10;
        table = *(unsigned int **)(file_base + 0x28);
        *(unsigned int *)((char *)table + second_offset) += file_base;
    }
    return file_base;
}
