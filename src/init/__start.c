#pragma scheduling off

extern void __init_hardware(void);
extern void __check_pad3(void);
extern void DBInit(void);
extern void OSInit(void);
extern void __init_user(void);
extern void InitMetroTRK(void);
extern void InitMetroTRK_BBA(void);
extern void __set_debug_bba(void);
extern int __get_debug_bba(void);
extern int main(int argc, char *argv[]);
extern void exit(int);
extern void memcpy(void *dst, const void *src, unsigned long n);
extern void memset(void *dst, int c, unsigned long n);
extern void __flush_cache(void *addr, unsigned long size);

__declspec(section ".init") extern char _stack_addr[];
__declspec(section ".init") extern char _SDA_BASE_[];
__declspec(section ".init") extern char _SDA2_BASE_[];

typedef struct __rom_copy_info {
    char *rom;
    char *addr;
    unsigned int size;
} __rom_copy_info;

typedef struct __bss_init_info {
    char *addr;
    unsigned int size;
} __bss_init_info;

__declspec(section ".init") extern __rom_copy_info _rom_copy_info[];
__declspec(section ".init") extern __bss_init_info _bss_init_info[];

__declspec(section ".init") static void __init_registers(void);
__declspec(section ".init") static void __init_data(void);

__declspec(section ".init") __declspec(weak) asm void __start(void) {
    nofralloc
    bl __init_registers
    bl __init_hardware
    li r0, -1
    stwu r1, -8(r1)
    stw r0, 4(r1)
    stw r0, 0(r1)
    bl __init_data
    li r0, 0
    lis r6, 0x8000
    addi r6, r6, 0x44
    stw r0, 0(r6)
    lis r6, 0x8000
    addi r6, r6, 0xf4
    lwz r6, 0(r6)
    cmplwi r6, 0
    beq _no_bi2
    lwz r7, 0xc(r6)
    b _check_debug_flag

_no_bi2:
    lis r5, 0x8000
    addi r5, r5, 0x34
    lwz r5, 0(r5)
    cmplwi r5, 0
    beq _goto_main
    lis r7, 0x8000
    addi r7, r7, 0x30e8
    lwz r7, 0(r7)

_check_debug_flag:
    li r5, 0
    cmplwi r7, 2
    beq _goto_inittrk
    cmplwi r7, 3
    li r5, 1
    beq _goto_inittrk
    cmplwi r7, 4
    bne _goto_main
    li r5, 2
    bl __set_debug_bba
    b _goto_main

_goto_inittrk:
    lis r6, InitMetroTRK@ha
    addi r6, r6, InitMetroTRK@l
    mtlr r6
    blrl

_goto_main:
    lis r6, 0x8000
    addi r6, r6, 0xf4
    lwz r5, 0(r6)
    cmplwi r5, 0
    beq+ _no_args
    lwz r6, 8(r5)
    cmplwi r6, 0
    beq+ _no_args
    add r6, r5, r6
    lwz r14, 0(r6)
    cmplwi r14, 0
    beq _no_args
    addi r15, r6, 4
    mtctr r14

_args_loop:
    addi r6, r6, 4
    lwz r7, 0(r6)
    add r7, r7, r5
    stw r7, 0(r6)
    bdnz _args_loop
    lis r5, 0x8000
    addi r5, r5, 0x34
    clrrwi r7, r15, 5
    stw r7, 0(r5)
    b _end_of_parseargs

_no_args:
    li r14, 0
    li r15, 0

_end_of_parseargs:
    bl DBInit
    bl OSInit
    lis r4, 0x8000
    addi r4, r4, 0x30e6
    lhz r3, 0(r4)
    andi. r5, r3, 0x8000
    beq _do_pad3
    andi. r3, r3, 0x7fff
    cmplwi r3, 1
    bne _check_bba

_do_pad3:
    bl __check_pad3

_check_bba:
    bl __get_debug_bba
    cmplwi r3, 1
    bne _skip_bba_trk
    bl InitMetroTRK_BBA

_skip_bba_trk:
    bl __init_user
    mr r3, r14
    mr r4, r15
    bl main
    b exit
}

asm static void __init_registers(void) {
    nofralloc
    li r0, 0
    li r3, 0
    li r4, 0
    li r5, 0
    li r6, 0
    li r7, 0
    li r8, 0
    li r9, 0
    li r10, 0
    li r11, 0
    li r12, 0
    li r14, 0
    li r15, 0
    li r16, 0
    li r17, 0
    li r18, 0
    li r19, 0
    li r20, 0
    li r21, 0
    li r22, 0
    li r23, 0
    li r24, 0
    li r25, 0
    li r26, 0
    li r27, 0
    li r28, 0
    li r29, 0
    li r30, 0
    li r31, 0
    lis r1, _stack_addr@h
    ori r1, r1, _stack_addr@l
    lis r2, _SDA2_BASE_@h
    ori r2, r2, _SDA2_BASE_@l
    lis r13, _SDA_BASE_@h
    ori r13, r13, _SDA_BASE_@l
    blr
}

__declspec(section ".init") __inline static void
__copy_rom_section(void *dst, const void *src, unsigned long size) {
    if (size && (dst != src)) {
        memcpy(dst, src, size);
        __flush_cache(dst, size);
    }
}

__declspec(section ".init") __inline static void
__init_bss_section(void *dst, unsigned long size) {
    if (size) {
        memset(dst, 0, size);
    }
}

static void __init_data(void) {
    __rom_copy_info *dci;
    __bss_init_info *bii;

    dci = _rom_copy_info;
    while (1) {
        if (dci->size == 0) {
            break;
        }
        __copy_rom_section(dci->addr, dci->rom, dci->size);
        dci++;
    }

    bii = _bss_init_info;
    while (1) {
        if (bii->size == 0) {
            break;
        }
        __init_bss_section(bii->addr, bii->size);
        bii++;
    }
}
