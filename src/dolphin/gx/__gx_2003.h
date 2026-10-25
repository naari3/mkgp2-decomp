#ifndef _GX_2003_H_
#define _GX_2003_H_

/* Helpers for functions taken from the 2003 GX (projectPiki/pikmin2
   src/Dolphin/gx), which differ from the dolsdk2004 versions. */

#define gx __GXData

#define GX_BITFIELD(field, pos, size, value)       (__rlwimi((field), (value), 31 - (pos) - (size) + 1, (pos), (pos) + (size) - 1))
#define GX_BITFIELD_SET(field, pos, size, value)   ((field) = GX_BITFIELD(field, pos, size, value))
#define GX_BITFIELD_TRUNC(field, pos, size, value) (__rlwimi((field), (value), 0, (pos), (pos) + (size) - 1))
#define GX_BITGET(field, pos, size)                ((field) >> (31 - (pos) - (size) + 1) & ((1 << (size)) - 1))
#define GX_GET_REG(reg, st, end)      GX_BITGET((reg), (st), ((end) - (st) + 1))
#define GX_SET_REG(reg, x, st, end)   GX_BITFIELD_SET((reg), (st), ((end) - (st) + 1), (x))
#define GX_SET_TRUNC(reg, x, st, end) GX_BITFIELD_TRUNC((reg), (st), ((end) - (st) + 1), (x))

#define GX_FIFO_CMD_LOAD_BP_REG 0x61
#define GX_FIFO_CMD_LOAD_CP_REG 0x08
#define GX_FIFO_CMD_LOAD_XF_REG 0x10

#define GX_BP_LOAD_REG(data)                \
    GXWGFifo.s8  = GX_FIFO_CMD_LOAD_BP_REG; \
    GXWGFifo.s32 = (data);

#define GX_CP_LOAD_REG(addr, data)          \
    GXWGFifo.s8  = GX_FIFO_CMD_LOAD_CP_REG; \
    GXWGFifo.s8  = (addr);                  \
    GXWGFifo.s32 = (data);

#define GX_XF_LOAD_REG_HDR(addr)            \
    GXWGFifo.s8  = GX_FIFO_CMD_LOAD_XF_REG; \
    GXWGFifo.s32 = (addr);

#define GX_XF_LOAD_REG(addr, data) \
    GX_XF_LOAD_REG_HDR(addr);      \
    GXWGFifo.s32 = (data);

#define GX_XF_REG_AMBIENT0    0x100A
#define GX_XF_REG_MATERIAL0   0x100C
#define GX_XF_REG_COLOR0CNTRL 0x100E
#define GX_XF_REG_ALPHA0CNTRL 0x1010
#define GX_XF_REG_ALPHA1CNTRL 0x1011

#define GX_XF_CLR0CTRL_MTXSRC_ST      31
#define GX_XF_CLR0CTRL_MTXSRC_END     31
#define GX_XF_CLR0CTRL_LIGHT_ST       30
#define GX_XF_CLR0CTRL_LIGHT_END      30
#define GX_XF_CLR0CTRL_AMBSRC_ST      25
#define GX_XF_CLR0CTRL_AMBSRC_END     25
#define GX_XF_CLR0CTRL_DIFATTN_ST     23
#define GX_XF_CLR0CTRL_DIFATTN_END    24
#define GX_XF_CLR0CTRL_ATTNENABLE_ST  22
#define GX_XF_CLR0CTRL_ATTNENABLE_END 22
#define GX_XF_CLR0CTRL_ATTNSEL_ST     21
#define GX_XF_CLR0CTRL_ATTNSEL_END    21

#define GX_BP_REG_TEVREG0LO 0xE0
#define GX_BP_REG_TEVREG0HI 0xE1

#define GX_CP_REG_VAT_GRP0 (0x70)
#define GX_CP_REG_VAT_GRP1 (0x80)
#define GX_CP_REG_VAT_GRP2 (0x90)
#define GX_BP_REG_SETMODE0_TEX4 (0xA0)
#define GX_BP_REG_SETIMAGE2_TEX4 (0xB0)
#define GX_PI_ADDR  (0x0C003000)
#define GX_CP_ADDR  (0x0C000000)
#define GX_PE_ADDR  (0x0C001000)
#define GX_MEM_ADDR (0x0C004000)
#define GX_MAXTEVSTAGE GX_MAX_TEVSTAGE
#define GX_MAX_BIGTLUT 4
#define GX_MAX_TLUT (16)
#define GX_BP_FOGPARAM1_B_MAG_ST (8)
#define GX_BP_FOGPARAM1_B_MAG_END (31)
#define GX_BP_FOGPARAM2_B_SHIFT_ST (27)
#define GX_BP_FOGPARAM2_B_SHIFT_END (31)
#define GX_BP_REG_FOGPARAM1 (0xEF)
#define GX_BP_REG_FOGPARAM2 (0xF0)
#define GX_BP_FOGPARAM0_A_MANT_ST (21)
#define GX_BP_FOGPARAM0_A_MANT_END (31)
#define GX_BP_FOGPARAM0_A_EXP_ST (13)
#define GX_BP_FOGPARAM0_A_EXP_END (20)
#define GX_BP_FOGPARAM0_A_SIGN_ST (12)
#define GX_BP_FOGPARAM0_A_SIGN_END (12)
#define GX_BP_REG_FOGPARAM0 (0xEE)
#define GX_BP_FOGPARAM3_C_MANT_ST (21)
#define GX_BP_FOGPARAM3_C_MANT_END (31)
#define GX_BP_FOGPARAM3_C_EXP_ST (13)
#define GX_BP_FOGPARAM3_C_EXP_END (20)
#define GX_BP_FOGPARAM3_C_SIGN_ST (12)
#define GX_BP_FOGPARAM3_C_SIGN_END (12)
#define GX_BP_FOGPARAM3_PROJ_ST (11)
#define GX_BP_FOGPARAM3_PROJ_END (11)
#define GX_BP_FOGPARAM3_FSEL_ST (8)
#define GX_BP_FOGPARAM3_FSEL_END (10)
#define GX_BP_REG_FOGPARAM3 (0xF1)
#define GX_BP_FOGCOLOR_RGB_ST (8)
#define GX_BP_FOGCOLOR_RGB_END (31)
#define GX_BP_REG_FOGCOLOR (0xF2)
#endif
