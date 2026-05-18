/*
 * bitpack getters
 *
 * dtk reversed-extab group auto_03_80088BA8_text (eg_sz=2, no extab entries).
 * Both fns are simple `return self->field` getters on the bitpack object.
 *
 * Ghidra has no struct type for the bitpack object yet, so we use opaque
 * pointer + raw offset.
 */

unsigned int bitpack_get_used_bytes(int self) {
    return *(unsigned int *)(self + 0x14);
}

unsigned int bitpack_get_used_bits(int self) {
    return *(unsigned int *)(self + 0x10);
}
