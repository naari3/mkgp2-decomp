.include "macros.inc"
.file ".psw_5301.c"

# 0x00000000..0x00000938 | size: 0x938
.text
.balign 4

# .text:0x0 | size: 0x5C
.fn fn_8013D4B0, global
/* 00000000 00000040  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 00000004 00000044  7C 08 02 A6 */	mflr r0
/* 00000008 00000048  90 01 00 24 */	stw r0, 0x24(r1)
/* 0000000C 0000004C  DB E1 00 10 */	stfd f31, 0x10(r1)
/* 00000010 00000050  F3 E1 00 18 */	psq_st f31, 0x18(r1), 0, qr0
/* 00000014 00000054  93 E1 00 0C */	stw r31, 0xc(r1)
/* 00000018 00000058  FF E0 08 90 */	fmr f31, f1
/* 0000001C 0000005C  7C 7F 1B 78 */	mr r31, r3
/* 00000020 00000060  80 63 00 04 */	lwz r3, 0x4(r3)
/* 00000024 00000064  38 80 00 00 */	li r4, 0x0
/* 00000028 00000068  C0 3F 00 10 */	lfs f1, 0x10(r31)
/* 0000002C 0000006C  FC 80 F8 90 */	fmr f4, f31
/* 00000030 00000070  C0 5F 00 14 */	lfs f2, 0x14(r31)
/* 00000034 00000074  C0 7F 00 18 */	lfs f3, 0x18(r31)
/* 00000038 00000078  48 00 00 01 */	bl Object_SetColorRGBA
/* 0000003C 0000007C  D3 FF 00 1C */	stfs f31, 0x1c(r31)
/* 00000040 00000080  E3 E1 00 18 */	psq_l f31, 0x18(r1), 0, qr0
/* 00000044 00000084  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000048 00000088  CB E1 00 10 */	lfd f31, 0x10(r1)
/* 0000004C 0000008C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 00000050 00000090  7C 08 03 A6 */	mtlr r0
/* 00000054 00000094  38 21 00 20 */	addi r1, r1, 0x20
/* 00000058 00000098  4E 80 00 20 */	blr
.endfn fn_8013D4B0

# .text:0x5C | size: 0x64
.fn fn_8013D50C, global
/* 0000005C 0000009C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 00000060 000000A0  7C 08 02 A6 */	mflr r0
/* 00000064 000000A4  90 01 00 34 */	stw r0, 0x34(r1)
/* 00000068 000000A8  39 61 00 30 */	addi r11, r1, 0x30
/* 0000006C 000000AC  48 00 00 01 */	bl _savefpr_28
/* 00000070 000000B0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 00000074 000000B4  7C 7F 1B 78 */	mr r31, r3
/* 00000078 000000B8  FF 80 08 90 */	fmr f28, f1
/* 0000007C 000000BC  FF A0 10 90 */	fmr f29, f2
/* 00000080 000000C0  80 63 00 04 */	lwz r3, 0x4(r3)
/* 00000084 000000C4  FF C0 18 90 */	fmr f30, f3
/* 00000088 000000C8  38 80 00 00 */	li r4, 0x0
/* 0000008C 000000CC  FF E0 20 90 */	fmr f31, f4
/* 00000090 000000D0  48 00 00 01 */	bl Object_SetColorRGBA
/* 00000094 000000D4  D3 9F 00 10 */	stfs f28, 0x10(r31)
/* 00000098 000000D8  D3 BF 00 14 */	stfs f29, 0x14(r31)
/* 0000009C 000000DC  D3 DF 00 18 */	stfs f30, 0x18(r31)
/* 000000A0 000000E0  D3 FF 00 1C */	stfs f31, 0x1c(r31)
/* 000000A4 000000E4  39 61 00 30 */	addi r11, r1, 0x30
/* 000000A8 000000E8  48 00 00 01 */	bl _restfpr_28
/* 000000AC 000000EC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 000000B0 000000F0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 000000B4 000000F4  7C 08 03 A6 */	mtlr r0
/* 000000B8 000000F8  38 21 00 30 */	addi r1, r1, 0x30
/* 000000BC 000000FC  4E 80 00 20 */	blr
.endfn fn_8013D50C

# .text:0xC0 | size: 0x2C
.fn fn_8013D570, global
/* 000000C0 00000100  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 000000C4 00000104  7C 08 02 A6 */	mflr r0
/* 000000C8 00000108  90 01 00 14 */	stw r0, 0x14(r1)
/* 000000CC 0000010C  80 63 00 04 */	lwz r3, 0x4(r3)
/* 000000D0 00000110  28 03 00 00 */	cmplwi r3, 0x0
/* 000000D4 00000114  41 82 00 08 */	beq .L_000000DC
/* 000000D8 00000118  48 00 00 01 */	bl Object_SetJObjRotationY
.L_000000DC:
/* 000000DC 0000011C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 000000E0 00000120  7C 08 03 A6 */	mtlr r0
/* 000000E4 00000124  38 21 00 10 */	addi r1, r1, 0x10
/* 000000E8 00000128  4E 80 00 20 */	blr
.endfn fn_8013D570

# .text:0xEC | size: 0x6C
.fn fn_8013D59C, global
/* 000000EC 0000012C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 000000F0 00000130  7C 08 02 A6 */	mflr r0
/* 000000F4 00000134  90 01 00 24 */	stw r0, 0x24(r1)
/* 000000F8 00000138  DB E1 00 18 */	stfd f31, 0x18(r1)
/* 000000FC 0000013C  FF E0 10 90 */	fmr f31, f2
/* 00000100 00000140  DB C1 00 10 */	stfd f30, 0x10(r1)
/* 00000104 00000144  FF C0 08 90 */	fmr f30, f1
/* 00000108 00000148  93 E1 00 0C */	stw r31, 0xc(r1)
/* 0000010C 0000014C  7C 7F 1B 78 */	mr r31, r3
/* 00000110 00000150  80 63 00 04 */	lwz r3, 0x4(r3)
/* 00000114 00000154  28 03 00 00 */	cmplwi r3, 0x0
/* 00000118 00000158  41 82 00 24 */	beq .L_0000013C
/* 0000011C 0000015C  FC 20 18 90 */	fmr f1, f3
/* 00000120 00000160  48 00 00 01 */	bl Object_SetJObjRotationZ
/* 00000124 00000164  FC 20 F0 90 */	fmr f1, f30
/* 00000128 00000168  80 7F 00 04 */	lwz r3, 0x4(r31)
/* 0000012C 0000016C  48 00 00 01 */	bl Object_SetJObjRotationX
/* 00000130 00000170  FC 20 F8 90 */	fmr f1, f31
/* 00000134 00000174  80 7F 00 04 */	lwz r3, 0x4(r31)
/* 00000138 00000178  48 00 00 01 */	bl Object_SetJObjRotationY
.L_0000013C:
/* 0000013C 0000017C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000140 00000180  CB E1 00 18 */	lfd f31, 0x18(r1)
/* 00000144 00000184  CB C1 00 10 */	lfd f30, 0x10(r1)
/* 00000148 00000188  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 0000014C 0000018C  7C 08 03 A6 */	mtlr r0
/* 00000150 00000190  38 21 00 20 */	addi r1, r1, 0x20
/* 00000154 00000194  4E 80 00 20 */	blr
.endfn fn_8013D59C

# .text:0x158 | size: 0x2C
.fn fn_8013D608, global
/* 00000158 00000198  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 0000015C 0000019C  7C 08 02 A6 */	mflr r0
/* 00000160 000001A0  90 01 00 14 */	stw r0, 0x14(r1)
/* 00000164 000001A4  80 63 00 04 */	lwz r3, 0x4(r3)
/* 00000168 000001A8  28 03 00 00 */	cmplwi r3, 0x0
/* 0000016C 000001AC  41 82 00 08 */	beq .L_00000174
/* 00000170 000001B0  48 00 00 01 */	bl Object_SetJObjScaleXYZ
.L_00000174:
/* 00000174 000001B4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 00000178 000001B8  7C 08 03 A6 */	mtlr r0
/* 0000017C 000001BC  38 21 00 10 */	addi r1, r1, 0x10
/* 00000180 000001C0  4E 80 00 20 */	blr
.endfn fn_8013D608

# .text:0x184 | size: 0x2C
.fn fn_8013D634, global
/* 00000184 000001C4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 00000188 000001C8  7C 08 02 A6 */	mflr r0
/* 0000018C 000001CC  90 01 00 14 */	stw r0, 0x14(r1)
/* 00000190 000001D0  80 63 00 04 */	lwz r3, 0x4(r3)
/* 00000194 000001D4  28 03 00 00 */	cmplwi r3, 0x0
/* 00000198 000001D8  41 82 00 08 */	beq .L_000001A0
/* 0000019C 000001DC  48 00 00 01 */	bl Object_SetJObjPositionXYZ
.L_000001A0:
/* 000001A0 000001E0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 000001A4 000001E4  7C 08 03 A6 */	mtlr r0
/* 000001A8 000001E8  38 21 00 10 */	addi r1, r1, 0x10
/* 000001AC 000001EC  4E 80 00 20 */	blr
.endfn fn_8013D634

# .text:0x1B0 | size: 0xC
.fn fn_8013D660, global
/* 000001B0 000001F0  D0 23 00 08 */	stfs f1, 0x8(r3)
/* 000001B4 000001F4  D0 43 00 0C */	stfs f2, 0xc(r3)
/* 000001B8 000001F8  4E 80 00 20 */	blr
.endfn fn_8013D660

# .text:0x1BC | size: 0x98
.fn fn_8013D66C, global
/* 000001BC 000001FC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 000001C0 00000200  7C 08 02 A6 */	mflr r0
/* 000001C4 00000204  90 01 00 14 */	stw r0, 0x14(r1)
/* 000001C8 00000208  93 E1 00 0C */	stw r31, 0xc(r1)
/* 000001CC 0000020C  7C 7F 1B 78 */	mr r31, r3
/* 000001D0 00000210  80 03 00 04 */	lwz r0, 0x4(r3)
/* 000001D4 00000214  28 00 00 00 */	cmplwi r0, 0x0
/* 000001D8 00000218  41 82 00 68 */	beq .L_00000240
/* 000001DC 0000021C  48 00 00 01 */	bl fn_8013BC98
/* 000001E0 00000220  28 03 00 00 */	cmplwi r3, 0x0
/* 000001E4 00000224  41 82 00 5C */	beq .L_00000240
/* 000001E8 00000228  48 00 00 01 */	bl fn_8013C3B8
/* 000001EC 0000022C  28 03 00 00 */	cmplwi r3, 0x0
/* 000001F0 00000230  41 82 00 50 */	beq .L_00000240
/* 000001F4 00000234  48 00 00 01 */	bl fn_8013BC98
/* 000001F8 00000238  C0 3F 00 08 */	lfs f1, 0x8(r31)
/* 000001FC 0000023C  C0 5F 00 0C */	lfs f2, 0xc(r31)
/* 00000200 00000240  48 00 00 01 */	bl fn_8013BB1C
/* 00000204 00000244  48 00 00 01 */	bl fn_8013BC98
/* 00000208 00000248  48 00 00 01 */	bl fn_8013BC38
/* 0000020C 0000024C  54 60 06 3F */	clrlwi. r0, r3, 24
/* 00000210 00000250  41 82 00 30 */	beq .L_00000240
/* 00000214 00000254  48 00 00 01 */	bl fn_8013C3B8
/* 00000218 00000258  48 00 00 01 */	bl fn_8013C34C
/* 0000021C 0000025C  48 00 00 01 */	bl fn_8013BC98
/* 00000220 00000260  48 00 00 01 */	bl fn_8013BBFC
/* 00000224 00000264  80 7F 00 04 */	lwz r3, 0x4(r31)
/* 00000228 00000268  38 80 00 07 */	li r4, 0x7
/* 0000022C 0000026C  48 00 00 01 */	bl Object_RenderJObjTree
/* 00000230 00000270  48 00 00 01 */	bl fn_8013BC98
/* 00000234 00000274  48 00 00 01 */	bl fn_8013BB9C
/* 00000238 00000278  48 00 00 01 */	bl fn_8013C3B8
/* 0000023C 0000027C  48 00 00 01 */	bl fn_8013C334
.L_00000240:
/* 00000240 00000280  80 01 00 14 */	lwz r0, 0x14(r1)
/* 00000244 00000284  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 00000248 00000288  7C 08 03 A6 */	mtlr r0
/* 0000024C 0000028C  38 21 00 10 */	addi r1, r1, 0x10
/* 00000250 00000290  4E 80 00 20 */	blr
.endfn fn_8013D66C

# .text:0x254 | size: 0x34
.fn fn_8013D704, global
/* 00000254 00000294  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 00000258 00000298  7C 08 02 A6 */	mflr r0
/* 0000025C 0000029C  90 01 00 14 */	stw r0, 0x14(r1)
/* 00000260 000002A0  80 63 00 04 */	lwz r3, 0x4(r3)
/* 00000264 000002A4  28 03 00 00 */	cmplwi r3, 0x0
/* 00000268 000002A8  40 82 00 0C */	bne .L_00000274
/* 0000026C 000002AC  38 60 00 00 */	li r3, 0x0
/* 00000270 000002B0  48 00 00 08 */	b .L_00000278
.L_00000274:
/* 00000274 000002B4  48 00 00 01 */	bl clNormal3D_Exec
.L_00000278:
/* 00000278 000002B8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 0000027C 000002BC  7C 08 03 A6 */	mtlr r0
/* 00000280 000002C0  38 21 00 10 */	addi r1, r1, 0x10
/* 00000284 000002C4  4E 80 00 20 */	blr
.endfn fn_8013D704

# .text:0x288 | size: 0x40
.fn fn_8013D738, global
/* 00000288 000002C8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 0000028C 000002CC  7C 08 02 A6 */	mflr r0
/* 00000290 000002D0  90 01 00 14 */	stw r0, 0x14(r1)
/* 00000294 000002D4  80 63 00 04 */	lwz r3, 0x4(r3)
/* 00000298 000002D8  28 03 00 00 */	cmplwi r3, 0x0
/* 0000029C 000002DC  40 82 00 0C */	bne .L_000002A8
/* 000002A0 000002E0  38 60 00 00 */	li r3, 0x0
/* 000002A4 000002E4  48 00 00 14 */	b .L_000002B8
.L_000002A8:
/* 000002A8 000002E8  C0 60 00 00 */	lfs f3, "@88"@sda21(r0)
/* 000002AC 000002EC  38 80 00 00 */	li r4, 0x0
/* 000002B0 000002F0  FC 80 18 90 */	fmr f4, f3
/* 000002B4 000002F4  48 00 00 01 */	bl clNormal3D_SetScale
.L_000002B8:
/* 000002B8 000002F8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 000002BC 000002FC  7C 08 03 A6 */	mtlr r0
/* 000002C0 00000300  38 21 00 10 */	addi r1, r1, 0x10
/* 000002C4 00000304  4E 80 00 20 */	blr
.endfn fn_8013D738

# .text:0x2C8 | size: 0x88
.fn fn_8013D778, global
/* 000002C8 00000308  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 000002CC 0000030C  7C 08 02 A6 */	mflr r0
/* 000002D0 00000310  90 01 00 14 */	stw r0, 0x14(r1)
/* 000002D4 00000314  93 E1 00 0C */	stw r31, 0xc(r1)
/* 000002D8 00000318  7C 9F 23 78 */	mr r31, r4
/* 000002DC 0000031C  93 C1 00 08 */	stw r30, 0x8(r1)
/* 000002E0 00000320  7C 7E 1B 79 */	mr. r30, r3
/* 000002E4 00000324  41 82 00 50 */	beq .L_00000334
/* 000002E8 00000328  3C 60 00 00 */	lis r3, PreviewModel_data_8048EB04@ha
/* 000002EC 0000032C  38 03 00 00 */	addi r0, r3, PreviewModel_data_8048EB04@l
/* 000002F0 00000330  90 1E 00 00 */	stw r0, 0x0(r30)
/* 000002F4 00000334  80 7E 00 04 */	lwz r3, 0x4(r30)
/* 000002F8 00000338  28 03 00 00 */	cmplwi r3, 0x0
/* 000002FC 0000033C  41 82 00 0C */	beq .L_00000308
/* 00000300 00000340  38 80 00 01 */	li r4, 0x1
/* 00000304 00000344  48 00 00 01 */	bl Object_DtorWithGXSync
.L_00000308:
/* 00000308 00000348  48 00 00 01 */	bl fn_8013BCA0
/* 0000030C 0000034C  48 00 00 01 */	bl fn_8013C3C0
/* 00000310 00000350  28 1E 00 00 */	cmplwi r30, 0x0
/* 00000314 00000354  41 82 00 10 */	beq .L_00000324
/* 00000318 00000358  3C 60 00 00 */	lis r3, clCSModelInterface_vtable_8048EAE8@ha
/* 0000031C 0000035C  38 03 00 00 */	addi r0, r3, clCSModelInterface_vtable_8048EAE8@l
/* 00000320 00000360  90 1E 00 00 */	stw r0, 0x0(r30)
.L_00000324:
/* 00000324 00000364  7F E0 07 35 */	extsh. r0, r31
/* 00000328 00000368  40 81 00 0C */	ble .L_00000334
/* 0000032C 0000036C  7F C3 F3 78 */	mr r3, r30
/* 00000330 00000370  48 00 00 01 */	bl MemoryManager_TimedFree
.L_00000334:
/* 00000334 00000374  80 01 00 14 */	lwz r0, 0x14(r1)
/* 00000338 00000378  7F C3 F3 78 */	mr r3, r30
/* 0000033C 0000037C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 00000340 00000380  83 C1 00 08 */	lwz r30, 0x8(r1)
/* 00000344 00000384  7C 08 03 A6 */	mtlr r0
/* 00000348 00000388  38 21 00 10 */	addi r1, r1, 0x10
/* 0000034C 0000038C  4E 80 00 20 */	blr
.endfn fn_8013D778

# .text:0x350 | size: 0xC8
.fn fn_8013D800, global
/* 00000350 00000390  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 00000354 00000394  7C 08 02 A6 */	mflr r0
/* 00000358 00000398  3C E0 00 00 */	lis r7, clCSModelInterface_vtable_8048EAE8@ha
/* 0000035C 0000039C  3C C0 00 00 */	lis r6, PreviewModel_data_8048EB04@ha
/* 00000360 000003A0  90 01 00 24 */	stw r0, 0x24(r1)
/* 00000364 000003A4  38 06 00 00 */	addi r0, r6, PreviewModel_data_8048EB04@l
/* 00000368 000003A8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 0000036C 000003AC  7C BF 2B 78 */	mr r31, r5
/* 00000370 000003B0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 00000374 000003B4  7C 9E 23 78 */	mr r30, r4
/* 00000378 000003B8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 0000037C 000003BC  7C 7D 1B 78 */	mr r29, r3
/* 00000380 000003C0  38 67 00 00 */	addi r3, r7, clCSModelInterface_vtable_8048EAE8@l
/* 00000384 000003C4  93 81 00 10 */	stw r28, 0x10(r1)
/* 00000388 000003C8  90 7D 00 00 */	stw r3, 0x0(r29)
/* 0000038C 000003CC  90 1D 00 00 */	stw r0, 0x0(r29)
/* 00000390 000003D0  48 00 00 01 */	bl fn_8013BD7C
/* 00000394 000003D4  48 00 00 01 */	bl fn_8013C428
/* 00000398 000003D8  38 00 00 00 */	li r0, 0x0
/* 0000039C 000003DC  C0 20 00 00 */	lfs f1, lbl_806D76E0@sda21(r0)
/* 000003A0 000003E0  90 1D 00 04 */	stw r0, 0x4(r29)
/* 000003A4 000003E4  38 60 00 5C */	li r3, 0x5c
/* 000003A8 000003E8  C0 00 00 00 */	lfs f0, lbl_806D76E4@sda21(r0)
/* 000003AC 000003EC  D0 3D 00 08 */	stfs f1, 0x8(r29)
/* 000003B0 000003F0  D0 3D 00 0C */	stfs f1, 0xc(r29)
/* 000003B4 000003F4  D0 1D 00 10 */	stfs f0, 0x10(r29)
/* 000003B8 000003F8  D0 1D 00 14 */	stfs f0, 0x14(r29)
/* 000003BC 000003FC  D0 1D 00 18 */	stfs f0, 0x18(r29)
/* 000003C0 00000400  48 00 00 01 */	bl Alloc
/* 000003C4 00000404  7C 7C 1B 79 */	mr. r28, r3
/* 000003C8 00000408  41 82 00 10 */	beq .L_000003D8
/* 000003CC 0000040C  7F C4 F3 78 */	mr r4, r30
/* 000003D0 00000410  7F E5 FB 78 */	mr r5, r31
/* 000003D4 00000414  48 00 00 01 */	bl clNormal3D_Construct
.L_000003D8:
/* 000003D8 00000418  57 E0 06 3F */	clrlwi. r0, r31, 24
/* 000003DC 0000041C  93 9D 00 04 */	stw r28, 0x4(r29)
/* 000003E0 00000420  41 82 00 14 */	beq .L_000003F4
/* 000003E4 00000424  80 7D 00 04 */	lwz r3, 0x4(r29)
/* 000003E8 00000428  3C 80 40 00 */	lis r4, 0x4000
/* 000003EC 0000042C  38 A0 00 00 */	li r5, 0x0
/* 000003F0 00000430  48 00 00 01 */	bl clNormal3D_SetFlags
.L_000003F4:
/* 000003F4 00000434  80 01 00 24 */	lwz r0, 0x24(r1)
/* 000003F8 00000438  7F A3 EB 78 */	mr r3, r29
/* 000003FC 0000043C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 00000400 00000440  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 00000404 00000444  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 00000408 00000448  83 81 00 10 */	lwz r28, 0x10(r1)
/* 0000040C 0000044C  7C 08 03 A6 */	mtlr r0
/* 00000410 00000450  38 21 00 20 */	addi r1, r1, 0x20
/* 00000414 00000454  4E 80 00 20 */	blr
.endfn fn_8013D800

# .text:0x418 | size: 0x78
.fn dtor_8013D8C8, global
/* 00000418 00000458  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 0000041C 0000045C  7C 08 02 A6 */	mflr r0
/* 00000420 00000460  90 01 00 24 */	stw r0, 0x24(r1)
/* 00000424 00000464  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 00000428 00000468  7C 9F 23 78 */	mr r31, r4
/* 0000042C 0000046C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 00000430 00000470  7C 7E 1B 79 */	mr. r30, r3
/* 00000434 00000474  41 82 00 40 */	beq .L_00000474
/* 00000438 00000478  41 82 00 2C */	beq .L_00000464
/* 0000043C 0000047C  41 82 00 28 */	beq .L_00000464
/* 00000440 00000480  38 1E 00 04 */	addi r0, r30, 0x4
/* 00000444 00000484  7F C4 F3 78 */	mr r4, r30
/* 00000448 00000488  90 01 00 10 */	stw r0, 0x10(r1)
/* 0000044C 0000048C  38 61 00 08 */	addi r3, r1, 0x8
/* 00000450 00000490  38 A1 00 0C */	addi r5, r1, 0xc
/* 00000454 00000494  38 C1 00 10 */	addi r6, r1, 0x10
/* 00000458 00000498  80 1E 00 08 */	lwz r0, 0x8(r30)
/* 0000045C 0000049C  90 01 00 0C */	stw r0, 0xc(r1)
/* 00000460 000004A0  48 00 00 01 */	bl DoublyLinkedList_EraseRange
.L_00000464:
/* 00000464 000004A4  7F E0 07 35 */	extsh. r0, r31
/* 00000468 000004A8  40 81 00 0C */	ble .L_00000474
/* 0000046C 000004AC  7F C3 F3 78 */	mr r3, r30
/* 00000470 000004B0  48 00 00 01 */	bl MemoryManager_TimedFree
.L_00000474:
/* 00000474 000004B4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000478 000004B8  7F C3 F3 78 */	mr r3, r30
/* 0000047C 000004BC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 00000480 000004C0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 00000484 000004C4  7C 08 03 A6 */	mtlr r0
/* 00000488 000004C8  38 21 00 20 */	addi r1, r1, 0x20
/* 0000048C 000004CC  4E 80 00 20 */	blr
.endfn dtor_8013D8C8

# .text:0x490 | size: 0xAC
.fn fn_8013DA00, global
/* 00000490 000004D0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 00000494 000004D4  7C 08 02 A6 */	mflr r0
/* 00000498 000004D8  90 01 00 34 */	stw r0, 0x34(r1)
/* 0000049C 000004DC  39 61 00 30 */	addi r11, r1, 0x30
/* 000004A0 000004E0  48 00 00 01 */	bl _savegpr_26
/* 000004A4 000004E4  83 80 00 00 */	lwz r28, PreviewModel_bss_806D1560@sda21(r0)
/* 000004A8 000004E8  28 1C 00 00 */	cmplwi r28, 0x0
/* 000004AC 000004EC  41 82 00 78 */	beq .L_00000524
/* 000004B0 000004F0  3B 60 00 00 */	li r27, 0x0
/* 000004B4 000004F4  3B E0 00 00 */	li r31, 0x0
.L_000004B8:
/* 000004B8 000004F8  7F 5C FA 14 */	add r26, r28, r31
/* 000004BC 000004FC  80 1A 00 00 */	lwz r0, 0x0(r26)
/* 000004C0 00000500  28 00 00 00 */	cmplwi r0, 0x0
/* 000004C4 00000504  41 82 00 50 */	beq .L_00000514
/* 000004C8 00000508  83 BA 00 08 */	lwz r29, 0x8(r26)
/* 000004CC 0000050C  3B DA 00 04 */	addi r30, r26, 0x4
/* 000004D0 00000510  48 00 00 1C */	b .L_000004EC
.L_000004D4:
/* 000004D4 00000514  80 7D 00 08 */	lwz r3, 0x8(r29)
/* 000004D8 00000518  80 83 00 00 */	lwz r4, 0x0(r3)
/* 000004DC 0000051C  81 84 00 0C */	lwz r12, 0xc(r4)
/* 000004E0 00000520  7D 89 03 A6 */	mtctr r12
/* 000004E4 00000524  4E 80 04 21 */	bctrl
/* 000004E8 00000528  83 BD 00 04 */	lwz r29, 0x4(r29)
.L_000004EC:
/* 000004EC 0000052C  7C 1D F0 40 */	cmplw r29, r30
/* 000004F0 00000530  40 82 FF E4 */	bne .L_000004D4
/* 000004F4 00000534  93 C1 00 10 */	stw r30, 0x10(r1)
/* 000004F8 00000538  7F 44 D3 78 */	mr r4, r26
/* 000004FC 0000053C  38 61 00 08 */	addi r3, r1, 0x8
/* 00000500 00000540  38 A1 00 0C */	addi r5, r1, 0xc
/* 00000504 00000544  80 1A 00 08 */	lwz r0, 0x8(r26)
/* 00000508 00000548  38 C1 00 10 */	addi r6, r1, 0x10
/* 0000050C 0000054C  90 01 00 0C */	stw r0, 0xc(r1)
/* 00000510 00000550  48 00 00 01 */	bl DoublyLinkedList_EraseRange
.L_00000514:
/* 00000514 00000554  3B 7B 00 01 */	addi r27, r27, 0x1
/* 00000518 00000558  3B FF 00 0C */	addi r31, r31, 0xc
/* 0000051C 0000055C  2C 1B 00 08 */	cmpwi r27, 0x8
/* 00000520 00000560  41 80 FF 98 */	blt .L_000004B8
.L_00000524:
/* 00000524 00000564  39 61 00 30 */	addi r11, r1, 0x30
/* 00000528 00000568  48 00 00 01 */	bl _restgpr_26
/* 0000052C 0000056C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 00000530 00000570  7C 08 03 A6 */	mtlr r0
/* 00000534 00000574  38 21 00 30 */	addi r1, r1, 0x30
/* 00000538 00000578  4E 80 00 20 */	blr
.endfn fn_8013DA00

# .text:0x53C | size: 0x64
.fn fn_8013DAC8, global
/* 0000053C 0000057C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 00000540 00000580  7C 08 02 A6 */	mflr r0
/* 00000544 00000584  90 01 00 24 */	stw r0, 0x24(r1)
/* 00000548 00000588  80 E0 00 00 */	lwz r7, PreviewModel_bss_806D1560@sda21(r0)
/* 0000054C 0000058C  28 07 00 00 */	cmplwi r7, 0x0
/* 00000550 00000590  41 82 00 40 */	beq .L_00000590
/* 00000554 00000594  28 03 00 00 */	cmplwi r3, 0x0
/* 00000558 00000598  90 61 00 10 */	stw r3, 0x10(r1)
/* 0000055C 0000059C  41 82 00 34 */	beq .L_00000590
/* 00000560 000005A0  2C 04 00 00 */	cmpwi r4, 0x0
/* 00000564 000005A4  41 80 00 2C */	blt .L_00000590
/* 00000568 000005A8  2C 04 00 08 */	cmpwi r4, 0x8
/* 0000056C 000005AC  40 80 00 24 */	bge .L_00000590
/* 00000570 000005B0  1C 04 00 0C */	mulli r0, r4, 0xc
/* 00000574 000005B4  38 61 00 08 */	addi r3, r1, 0x8
/* 00000578 000005B8  38 A1 00 0C */	addi r5, r1, 0xc
/* 0000057C 000005BC  38 C1 00 10 */	addi r6, r1, 0x10
/* 00000580 000005C0  7C 87 02 14 */	add r4, r7, r0
/* 00000584 000005C4  38 04 00 04 */	addi r0, r4, 0x4
/* 00000588 000005C8  90 01 00 0C */	stw r0, 0xc(r1)
/* 0000058C 000005CC  48 00 00 01 */	bl DoublyLinkedList_PushBefore
.L_00000590:
/* 00000590 000005D0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000594 000005D4  7C 08 03 A6 */	mtlr r0
/* 00000598 000005D8  38 21 00 20 */	addi r1, r1, 0x20
/* 0000059C 000005DC  4E 80 00 20 */	blr
.endfn fn_8013DAC8

# .text:0x5A0 | size: 0x74
.fn fn_8013DB2C, global
/* 000005A0 000005E0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 000005A4 000005E4  7C 08 02 A6 */	mflr r0
/* 000005A8 000005E8  90 01 00 34 */	stw r0, 0x34(r1)
/* 000005AC 000005EC  39 61 00 30 */	addi r11, r1, 0x30
/* 000005B0 000005F0  48 00 00 01 */	bl _savegpr_29
/* 000005B4 000005F4  83 A0 00 00 */	lwz r29, PreviewModel_bss_806D1560@sda21(r0)
/* 000005B8 000005F8  28 1D 00 00 */	cmplwi r29, 0x0
/* 000005BC 000005FC  41 82 00 40 */	beq .L_000005FC
/* 000005C0 00000600  3B C0 00 00 */	li r30, 0x0
/* 000005C4 00000604  7F DF F3 78 */	mr r31, r30
.L_000005C8:
/* 000005C8 00000608  7C 9D FA 14 */	add r4, r29, r31
/* 000005CC 0000060C  38 61 00 08 */	addi r3, r1, 0x8
/* 000005D0 00000610  38 04 00 04 */	addi r0, r4, 0x4
/* 000005D4 00000614  38 A1 00 0C */	addi r5, r1, 0xc
/* 000005D8 00000618  90 01 00 10 */	stw r0, 0x10(r1)
/* 000005DC 0000061C  38 C1 00 10 */	addi r6, r1, 0x10
/* 000005E0 00000620  80 04 00 08 */	lwz r0, 0x8(r4)
/* 000005E4 00000624  90 01 00 0C */	stw r0, 0xc(r1)
/* 000005E8 00000628  48 00 00 01 */	bl DoublyLinkedList_EraseRange
/* 000005EC 0000062C  3B DE 00 01 */	addi r30, r30, 0x1
/* 000005F0 00000630  3B FF 00 0C */	addi r31, r31, 0xc
/* 000005F4 00000634  2C 1E 00 08 */	cmpwi r30, 0x8
/* 000005F8 00000638  41 80 FF D0 */	blt .L_000005C8
.L_000005FC:
/* 000005FC 0000063C  39 61 00 30 */	addi r11, r1, 0x30
/* 00000600 00000640  48 00 00 01 */	bl _restgpr_29
/* 00000604 00000644  80 01 00 34 */	lwz r0, 0x34(r1)
/* 00000608 00000648  7C 08 03 A6 */	mtlr r0
/* 0000060C 0000064C  38 21 00 30 */	addi r1, r1, 0x30
/* 00000610 00000650  4E 80 00 20 */	blr
.endfn fn_8013DB2C

# .text:0x614 | size: 0x5C
.fn fn_8013DB9C, global
/* 00000614 00000654  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 00000618 00000658  7C 08 02 A6 */	mflr r0
/* 0000061C 0000065C  90 01 00 14 */	stw r0, 0x14(r1)
/* 00000620 00000660  93 E1 00 0C */	stw r31, 0xc(r1)
/* 00000624 00000664  83 E0 00 00 */	lwz r31, PreviewModel_bss_806D1560@sda21(r0)
/* 00000628 00000668  28 1F 00 00 */	cmplwi r31, 0x0
/* 0000062C 0000066C  41 82 00 30 */	beq .L_0000065C
/* 00000630 00000670  41 82 00 24 */	beq .L_00000654
/* 00000634 00000674  3C 80 00 00 */	lis r4, dtor_8013D8C8@ha
/* 00000638 00000678  7F E3 FB 78 */	mr r3, r31
/* 0000063C 0000067C  38 84 00 00 */	addi r4, r4, dtor_8013D8C8@l
/* 00000640 00000680  38 A0 00 0C */	li r5, 0xc
/* 00000644 00000684  38 C0 00 08 */	li r6, 0x8
/* 00000648 00000688  48 00 00 01 */	bl __destroy_arr
/* 0000064C 0000068C  7F E3 FB 78 */	mr r3, r31
/* 00000650 00000690  48 00 00 01 */	bl MemoryManager_TimedFree
.L_00000654:
/* 00000654 00000694  38 00 00 00 */	li r0, 0x0
/* 00000658 00000698  90 00 00 00 */	stw r0, PreviewModel_bss_806D1560@sda21(r0)
.L_0000065C:
/* 0000065C 0000069C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 00000660 000006A0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 00000664 000006A4  7C 08 03 A6 */	mtlr r0
/* 00000668 000006A8  38 21 00 10 */	addi r1, r1, 0x10
/* 0000066C 000006AC  4E 80 00 20 */	blr
.endfn fn_8013DB9C

# .text:0x670 | size: 0xBC
.fn fn_8013DBF8, global
/* 00000670 000006B0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 00000674 000006B4  7C 08 02 A6 */	mflr r0
/* 00000678 000006B8  90 01 00 34 */	stw r0, 0x34(r1)
/* 0000067C 000006BC  39 61 00 30 */	addi r11, r1, 0x30
/* 00000680 000006C0  48 00 00 01 */	bl _savegpr_29
/* 00000684 000006C4  80 00 00 00 */	lwz r0, PreviewModel_bss_806D1560@sda21(r0)
/* 00000688 000006C8  28 00 00 00 */	cmplwi r0, 0x0
/* 0000068C 000006CC  40 82 00 70 */	bne .L_000006FC
/* 00000690 000006D0  38 60 00 60 */	li r3, 0x60
/* 00000694 000006D4  48 00 00 01 */	bl Alloc
/* 00000698 000006D8  7C 7D 1B 79 */	mr. r29, r3
/* 0000069C 000006DC  41 82 00 5C */	beq .L_000006F8
/* 000006A0 000006E0  3C 80 00 00 */	lis r4, fn_8013DD08@ha
/* 000006A4 000006E4  3C A0 00 00 */	lis r5, dtor_8013D8C8@ha
/* 000006A8 000006E8  38 84 00 00 */	addi r4, r4, fn_8013DD08@l
/* 000006AC 000006EC  38 C0 00 0C */	li r6, 0xc
/* 000006B0 000006F0  38 A5 00 00 */	addi r5, r5, dtor_8013D8C8@l
/* 000006B4 000006F4  38 E0 00 08 */	li r7, 0x8
/* 000006B8 000006F8  48 00 00 01 */	bl __construct_array
/* 000006BC 000006FC  3B C0 00 00 */	li r30, 0x0
/* 000006C0 00000700  7F DF F3 78 */	mr r31, r30
.L_000006C4:
/* 000006C4 00000704  7C 9D FA 14 */	add r4, r29, r31
/* 000006C8 00000708  38 61 00 08 */	addi r3, r1, 0x8
/* 000006CC 0000070C  38 04 00 04 */	addi r0, r4, 0x4
/* 000006D0 00000710  38 A1 00 0C */	addi r5, r1, 0xc
/* 000006D4 00000714  90 01 00 10 */	stw r0, 0x10(r1)
/* 000006D8 00000718  38 C1 00 10 */	addi r6, r1, 0x10
/* 000006DC 0000071C  80 04 00 08 */	lwz r0, 0x8(r4)
/* 000006E0 00000720  90 01 00 0C */	stw r0, 0xc(r1)
/* 000006E4 00000724  48 00 00 01 */	bl DoublyLinkedList_EraseRange
/* 000006E8 00000728  3B DE 00 01 */	addi r30, r30, 0x1
/* 000006EC 0000072C  3B FF 00 0C */	addi r31, r31, 0xc
/* 000006F0 00000730  2C 1E 00 08 */	cmpwi r30, 0x8
/* 000006F4 00000734  41 80 FF D0 */	blt .L_000006C4
.L_000006F8:
/* 000006F8 00000738  93 A0 00 00 */	stw r29, PreviewModel_bss_806D1560@sda21(r0)
.L_000006FC:
/* 000006FC 0000073C  80 00 00 00 */	lwz r0, PreviewModel_bss_806D1560@sda21(r0)
/* 00000700 00000740  28 00 00 00 */	cmplwi r0, 0x0
/* 00000704 00000744  40 82 00 0C */	bne .L_00000710
/* 00000708 00000748  38 60 00 00 */	li r3, 0x0
/* 0000070C 0000074C  48 00 00 08 */	b .L_00000714
.L_00000710:
/* 00000710 00000750  38 60 00 01 */	li r3, 0x1
.L_00000714:
/* 00000714 00000754  39 61 00 30 */	addi r11, r1, 0x30
/* 00000718 00000758  48 00 00 01 */	bl _restgpr_29
/* 0000071C 0000075C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 00000720 00000760  7C 08 03 A6 */	mtlr r0
/* 00000724 00000764  38 21 00 30 */	addi r1, r1, 0x30
/* 00000728 00000768  4E 80 00 20 */	blr
.endfn fn_8013DBF8

# .text:0x72C | size: 0x48
.fn dtor_8013DCBC, global
/* 0000072C 0000076C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 00000730 00000770  7C 08 02 A6 */	mflr r0
/* 00000734 00000774  90 01 00 14 */	stw r0, 0x14(r1)
/* 00000738 00000778  93 E1 00 0C */	stw r31, 0xc(r1)
/* 0000073C 0000077C  7C 7F 1B 79 */	mr. r31, r3
/* 00000740 00000780  41 82 00 1C */	beq .L_0000075C
/* 00000744 00000784  3C A0 00 00 */	lis r5, clCSModelInterface_vtable_8048EAE8@ha
/* 00000748 00000788  7C 80 07 35 */	extsh. r0, r4
/* 0000074C 0000078C  38 05 00 00 */	addi r0, r5, clCSModelInterface_vtable_8048EAE8@l
/* 00000750 00000790  90 1F 00 00 */	stw r0, 0x0(r31)
/* 00000754 00000794  40 81 00 08 */	ble .L_0000075C
/* 00000758 00000798  48 00 00 01 */	bl MemoryManager_TimedFree
.L_0000075C:
/* 0000075C 0000079C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 00000760 000007A0  7F E3 FB 78 */	mr r3, r31
/* 00000764 000007A4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 00000768 000007A8  7C 08 03 A6 */	mtlr r0
/* 0000076C 000007AC  38 21 00 10 */	addi r1, r1, 0x10
/* 00000770 000007B0  4E 80 00 20 */	blr
.endfn dtor_8013DCBC

# .text:0x774 | size: 0x4
.fn fn_8013DD04, global
/* 00000774 000007B4  4E 80 00 20 */	blr
.endfn fn_8013DD04

# .text:0x778 | size: 0x30
.fn fn_8013DD08, weak
/* 00000778 000007B8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 0000077C 000007BC  7C 08 02 A6 */	mflr r0
/* 00000780 000007C0  90 01 00 14 */	stw r0, 0x14(r1)
/* 00000784 000007C4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 00000788 000007C8  7C 7F 1B 78 */	mr r31, r3
/* 0000078C 000007CC  48 00 00 01 */	bl DoublyLinkedList_Init
/* 00000790 000007D0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 00000794 000007D4  7F E3 FB 78 */	mr r3, r31
/* 00000798 000007D8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 0000079C 000007DC  7C 08 03 A6 */	mtlr r0
/* 000007A0 000007E0  38 21 00 10 */	addi r1, r1, 0x10
/* 000007A4 000007E4  4E 80 00 20 */	blr
.endfn fn_8013DD08

# .text:0x7A8 | size: 0x74
# ListMid::~ListMid()
.fn __dt__7ListMidFv, weak
/* 000007A8 000007E8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 000007AC 000007EC  7C 08 02 A6 */	mflr r0
/* 000007B0 000007F0  90 01 00 24 */	stw r0, 0x24(r1)
/* 000007B4 000007F4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 000007B8 000007F8  7C 9F 23 78 */	mr r31, r4
/* 000007BC 000007FC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 000007C0 00000800  7C 7E 1B 79 */	mr. r30, r3
/* 000007C4 00000804  41 82 00 3C */	beq .L_00000800
/* 000007C8 00000808  41 82 00 28 */	beq .L_000007F0
/* 000007CC 0000080C  38 1E 00 04 */	addi r0, r30, 0x4
/* 000007D0 00000810  7F C4 F3 78 */	mr r4, r30
/* 000007D4 00000814  90 01 00 10 */	stw r0, 0x10(r1)
/* 000007D8 00000818  38 61 00 08 */	addi r3, r1, 0x8
/* 000007DC 0000081C  38 A1 00 0C */	addi r5, r1, 0xc
/* 000007E0 00000820  38 C1 00 10 */	addi r6, r1, 0x10
/* 000007E4 00000824  80 1E 00 08 */	lwz r0, 0x8(r30)
/* 000007E8 00000828  90 01 00 0C */	stw r0, 0xc(r1)
/* 000007EC 0000082C  48 00 00 01 */	bl DoublyLinkedList_EraseRange
.L_000007F0:
/* 000007F0 00000830  7F E0 07 35 */	extsh. r0, r31
/* 000007F4 00000834  40 81 00 0C */	ble .L_00000800
/* 000007F8 00000838  7F C3 F3 78 */	mr r3, r30
/* 000007FC 0000083C  48 00 00 01 */	bl MemoryManager_TimedFree
.L_00000800:
/* 00000800 00000840  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000804 00000844  7F C3 F3 78 */	mr r3, r30
/* 00000808 00000848  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 0000080C 0000084C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 00000810 00000850  7C 08 03 A6 */	mtlr r0
/* 00000814 00000854  38 21 00 20 */	addi r1, r1, 0x20
/* 00000818 00000858  4E 80 00 20 */	blr
.endfn __dt__7ListMidFv

# .text:0x81C | size: 0x70
# ListBase::~ListBase()
.fn __dt__8ListBaseFv, weak
/* 0000081C 0000085C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 00000820 00000860  7C 08 02 A6 */	mflr r0
/* 00000824 00000864  90 01 00 24 */	stw r0, 0x24(r1)
/* 00000828 00000868  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 0000082C 0000086C  7C 9F 23 78 */	mr r31, r4
/* 00000830 00000870  93 C1 00 18 */	stw r30, 0x18(r1)
/* 00000834 00000874  7C 7E 1B 79 */	mr. r30, r3
/* 00000838 00000878  41 82 00 38 */	beq .L_00000870
/* 0000083C 0000087C  38 1E 00 04 */	addi r0, r30, 0x4
/* 00000840 00000880  7F C4 F3 78 */	mr r4, r30
/* 00000844 00000884  90 01 00 10 */	stw r0, 0x10(r1)
/* 00000848 00000888  38 61 00 08 */	addi r3, r1, 0x8
/* 0000084C 0000088C  38 A1 00 0C */	addi r5, r1, 0xc
/* 00000850 00000890  38 C1 00 10 */	addi r6, r1, 0x10
/* 00000854 00000894  80 1E 00 08 */	lwz r0, 0x8(r30)
/* 00000858 00000898  90 01 00 0C */	stw r0, 0xc(r1)
/* 0000085C 0000089C  48 00 00 01 */	bl DoublyLinkedList_EraseRange
/* 00000860 000008A0  7F E0 07 35 */	extsh. r0, r31
/* 00000864 000008A4  40 81 00 0C */	ble .L_00000870
/* 00000868 000008A8  7F C3 F3 78 */	mr r3, r30
/* 0000086C 000008AC  48 00 00 01 */	bl MemoryManager_TimedFree
.L_00000870:
/* 00000870 000008B0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000874 000008B4  7F C3 F3 78 */	mr r3, r30
/* 00000878 000008B8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 0000087C 000008BC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 00000880 000008C0  7C 08 03 A6 */	mtlr r0
/* 00000884 000008C4  38 21 00 20 */	addi r1, r1, 0x20
/* 00000888 000008C8  4E 80 00 20 */	blr
.endfn __dt__8ListBaseFv

# .text:0x88C | size: 0xAC
.fn fn_8013D940, global
/* 0000088C 000008CC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 00000890 000008D0  7C 08 02 A6 */	mflr r0
/* 00000894 000008D4  90 01 00 34 */	stw r0, 0x34(r1)
/* 00000898 000008D8  39 61 00 30 */	addi r11, r1, 0x30
/* 0000089C 000008DC  48 00 00 01 */	bl _savegpr_29
/* 000008A0 000008E0  80 80 00 00 */	lwz r4, PreviewModel_bss_806D1560@sda21(r0)
/* 000008A4 000008E4  28 04 00 00 */	cmplwi r4, 0x0
/* 000008A8 000008E8  41 82 00 78 */	beq .L_00000920
/* 000008AC 000008EC  2C 03 00 00 */	cmpwi r3, 0x0
/* 000008B0 000008F0  41 80 00 70 */	blt .L_00000920
/* 000008B4 000008F4  2C 03 00 08 */	cmpwi r3, 0x8
/* 000008B8 000008F8  40 80 00 68 */	bge .L_00000920
/* 000008BC 000008FC  1C 03 00 0C */	mulli r0, r3, 0xc
/* 000008C0 00000900  7F A4 02 14 */	add r29, r4, r0
/* 000008C4 00000904  80 1D 00 00 */	lwz r0, 0x0(r29)
/* 000008C8 00000908  28 00 00 00 */	cmplwi r0, 0x0
/* 000008CC 0000090C  41 82 00 54 */	beq .L_00000920
/* 000008D0 00000910  83 DD 00 08 */	lwz r30, 0x8(r29)
/* 000008D4 00000914  3B FD 00 04 */	addi r31, r29, 0x4
/* 000008D8 00000918  48 00 00 1C */	b .L_000008F4
.L_000008DC:
/* 000008DC 0000091C  80 7E 00 08 */	lwz r3, 0x8(r30)
/* 000008E0 00000920  81 83 00 00 */	lwz r12, 0x0(r3)
/* 000008E4 00000924  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 000008E8 00000928  7D 89 03 A6 */	mtctr r12
/* 000008EC 0000092C  4E 80 04 21 */	bctrl
/* 000008F0 00000930  83 DE 00 04 */	lwz r30, 0x4(r30)
.L_000008F4:
/* 000008F4 00000934  7C 1E F8 40 */	cmplw r30, r31
/* 000008F8 00000938  40 82 FF E4 */	bne .L_000008DC
/* 000008FC 0000093C  38 1D 00 04 */	addi r0, r29, 0x4
/* 00000900 00000940  7F A4 EB 78 */	mr r4, r29
/* 00000904 00000944  90 01 00 10 */	stw r0, 0x10(r1)
/* 00000908 00000948  38 61 00 08 */	addi r3, r1, 0x8
/* 0000090C 0000094C  38 A1 00 0C */	addi r5, r1, 0xc
/* 00000910 00000950  38 C1 00 10 */	addi r6, r1, 0x10
/* 00000914 00000954  80 1D 00 08 */	lwz r0, 0x8(r29)
/* 00000918 00000958  90 01 00 0C */	stw r0, 0xc(r1)
/* 0000091C 0000095C  48 00 00 01 */	bl DoublyLinkedList_EraseRange
.L_00000920:
/* 00000920 00000960  39 61 00 30 */	addi r11, r1, 0x30
/* 00000924 00000964  48 00 00 01 */	bl _restgpr_29
/* 00000928 00000968  80 01 00 34 */	lwz r0, 0x34(r1)
/* 0000092C 0000096C  7C 08 03 A6 */	mtlr r0
/* 00000930 00000970  38 21 00 30 */	addi r1, r1, 0x30
/* 00000934 00000974  4E 80 00 20 */	blr
.endfn fn_8013D940

# 0x00000000..0x00000100 | size: 0x100
.section extab, "a"
.balign 4

# extab:0x0 | size: 0x8
.obj "@10", local
/*
 * Flag values:
 * Has Elf Vector: Yes
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved FPR range: fp31
 * Saved GPR range: r31
 */
	.4byte 0x084A0000
	.4byte 0x00000000
.endobj "@10"

# extab:0x8 | size: 0x8
.obj "@16", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved FPR range: fp28-fp31
 * Saved GPR range: r31
 */
	.4byte 0x09080000
	.4byte 0x00000000
.endobj "@16"

# extab:0x10 | size: 0x8
.obj "@25", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 */
	.4byte 0x00080000
	.4byte 0x00000000
.endobj "@25"

# extab:0x18 | size: 0x8
.obj "@34", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved FPR range: fp30-fp31
 * Saved GPR range: r31
 */
	.4byte 0x08880000
	.4byte 0x00000000
.endobj "@34"

# extab:0x20 | size: 0x8
.obj "@43", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 */
	.4byte 0x00080000
	.4byte 0x00000000
.endobj "@43"

# extab:0x28 | size: 0x8
.obj "@52", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 */
	.4byte 0x00080000
	.4byte 0x00000000
.endobj "@52"

# extab:0x30 | size: 0x8
.obj "@68", local
/*
 * Flag values:
 * Has Elf Vector: Yes
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r31
 */
	.4byte 0x080A0000
	.4byte 0x00000000
.endobj "@68"

# extab:0x38 | size: 0x8
.obj "@78", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 */
	.4byte 0x00080000
	.4byte 0x00000000
.endobj "@78"

# extab:0x40 | size: 0x8
.obj "@89", local
/*
 * Flag values:
 * Has Elf Vector: Yes
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 */
	.4byte 0x000A0000
	.4byte 0x00000000
.endobj "@89"

# extab:0x48 | size: 0x8
.obj "@102", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r30-r31
 */
	.4byte 0x10080000
	.4byte 0x00000000
.endobj "@102"

# extab:0x50 | size: 0x34
.obj "@113", local
/*
 * Flag values:
 * Has Elf Vector: Yes
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r28-r31
 * 
 * PC actions:
 * PC=00000044:00000074, Action: 000028
 * PC=00000088, Action: 000020
 * PC=000000A4, Action: 000028
 * 
 * Exception actions:
 * 000020:
 * Type: DELETEPOINTER
 * Pointer: r28)
 * Dtor: "MemoryManager_TimedFree"
 * 000028:
 * Type: DESTROYBASE
 * Member: 0x0(r29)
 * Dtor: "dtor_8013DCBC"
 * Has end bit
 */
	.4byte 0x200A0000
	.4byte 0x00000044
	.4byte 0x000C0028
	.4byte 0x00000088
	.4byte 0x00000020
	.4byte 0x000000A4
	.4byte 0x00000028
	.4byte 0x00000000
	.4byte 0x0A80001C
	.4byte MemoryManager_TimedFree
	.4byte 0x8680001D
	.4byte 0x00000000
	.4byte dtor_8013DCBC
.endobj "@113"

# extab:0x84 | size: 0x8
.obj "@144", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r30-r31
 */
	.4byte 0x10080000
	.4byte 0x00000000
.endobj "@144"

# extab:0x8C | size: 0x8
.obj "@218", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r26-r31
 */
	.4byte 0x30080000
	.4byte 0x00000000
.endobj "@218"

# extab:0x94 | size: 0x8
.obj "@236", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 */
	.4byte 0x00080000
	.4byte 0x00000000
.endobj "@236"

# extab:0x9C | size: 0x8
.obj "@257", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r29-r31
 */
	.4byte 0x18080000
	.4byte 0x00000000
.endobj "@257"

# extab:0xA4 | size: 0x8
.obj "@269", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r31
 */
	.4byte 0x08080000
	.4byte 0x00000000
.endobj "@269"

# extab:0xAC | size: 0x34
.obj "@294", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r29-r31
 * 
 * PC actions:
 * PC=0000004C, Action: 00002C
 * PC=00000078, Action: 000018
 * 
 * Exception actions:
 * 000018:
 * Type: DESTROYMEMBERARRAY
 * Member: 0x0(r29)
 * Elements: 8
 * Size: 12
 * Dtor: "dtor_8013D8C8"
 * 00002C:
 * Type: DELETEPOINTER
 * Pointer: r29)
 * Dtor: "MemoryManager_TimedFree"
 * Has end bit
 */
	.4byte 0x18080000
	.4byte 0x0000004C
	.4byte 0x0000002C
	.4byte 0x00000078
	.4byte 0x00000018
	.4byte 0x00000000
	.4byte 0x0980001D
	.4byte 0x00000000
	.4byte 0x00000008
	.4byte 0x0000000C
	.4byte dtor_8013D8C8
	.4byte 0x8A80001D
	.4byte MemoryManager_TimedFree
.endobj "@294"

# extab:0xE0 | size: 0x8
.obj "@319", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r31
 */
	.4byte 0x08080000
	.4byte 0x00000000
.endobj "@319"

# extab:0xE8 | size: 0x8
.obj "@332", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r30-r31
 */
	.4byte 0x10080000
	.4byte 0x00000000
.endobj "@332"

# extab:0xF0 | size: 0x8
.obj "@343", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r30-r31
 */
	.4byte 0x10080000
	.4byte 0x00000000
.endobj "@343"

# extab:0xF8 | size: 0x8
.obj "@371", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r29-r31
 */
	.4byte 0x18080000
	.4byte 0x00000000
.endobj "@371"

# 0x00000000..0x000000FC | size: 0xFC
.section extabindex, "a"
.balign 4

# extabindex:0x0 | size: 0xC
.obj "@11", local
	.4byte fn_8013D4B0
	.4byte 0x0000005C
	.4byte "@10"
.endobj "@11"

# extabindex:0xC | size: 0xC
.obj "@17", local
	.4byte fn_8013D50C
	.4byte 0x00000064
	.4byte "@16"
.endobj "@17"

# extabindex:0x18 | size: 0xC
.obj "@26", local
	.4byte fn_8013D570
	.4byte 0x0000002C
	.4byte "@25"
.endobj "@26"

# extabindex:0x24 | size: 0xC
.obj "@35", local
	.4byte fn_8013D59C
	.4byte 0x0000006C
	.4byte "@34"
.endobj "@35"

# extabindex:0x30 | size: 0xC
.obj "@44", local
	.4byte fn_8013D608
	.4byte 0x0000002C
	.4byte "@43"
.endobj "@44"

# extabindex:0x3C | size: 0xC
.obj "@53", local
	.4byte fn_8013D634
	.4byte 0x0000002C
	.4byte "@52"
.endobj "@53"

# extabindex:0x48 | size: 0xC
.obj "@69", local
	.4byte fn_8013D66C
	.4byte 0x00000098
	.4byte "@68"
.endobj "@69"

# extabindex:0x54 | size: 0xC
.obj "@79", local
	.4byte fn_8013D704
	.4byte 0x00000034
	.4byte "@78"
.endobj "@79"

# extabindex:0x60 | size: 0xC
.obj "@90", local
	.4byte fn_8013D738
	.4byte 0x00000040
	.4byte "@89"
.endobj "@90"

# extabindex:0x6C | size: 0xC
.obj "@103", local
	.4byte fn_8013D778
	.4byte 0x00000088
	.4byte "@102"
.endobj "@103"

# extabindex:0x78 | size: 0xC
.obj "@114", local
	.4byte fn_8013D800
	.4byte 0x000000C8
	.4byte "@113"
.endobj "@114"

# extabindex:0x84 | size: 0xC
.obj "@145", local
	.4byte dtor_8013D8C8
	.4byte 0x00000078
	.4byte "@144"
.endobj "@145"

# extabindex:0x90 | size: 0xC
.obj "@219", local
	.4byte fn_8013DA00
	.4byte 0x000000AC
	.4byte "@218"
.endobj "@219"

# extabindex:0x9C | size: 0xC
.obj "@237", local
	.4byte fn_8013DAC8
	.4byte 0x00000064
	.4byte "@236"
.endobj "@237"

# extabindex:0xA8 | size: 0xC
.obj "@258", local
	.4byte fn_8013DB2C
	.4byte 0x00000074
	.4byte "@257"
.endobj "@258"

# extabindex:0xB4 | size: 0xC
.obj "@270", local
	.4byte fn_8013DB9C
	.4byte 0x0000005C
	.4byte "@269"
.endobj "@270"

# extabindex:0xC0 | size: 0xC
.obj "@295", local
	.4byte fn_8013DBF8
	.4byte 0x000000BC
	.4byte "@294"
.endobj "@295"

# extabindex:0xCC | size: 0xC
.obj "@320", local
	.4byte fn_8013DD08
	.4byte 0x00000030
	.4byte "@319"
.endobj "@320"

# extabindex:0xD8 | size: 0xC
.obj "@333", local
	.4byte __dt__7ListMidFv
	.4byte 0x00000074
	.4byte "@332"
.endobj "@333"

# extabindex:0xE4 | size: 0xC
.obj "@344", local
	.4byte __dt__8ListBaseFv
	.4byte 0x00000070
	.4byte "@343"
.endobj "@344"

# extabindex:0xF0 | size: 0xC
.obj "@372", local
	.4byte fn_8013D940
	.4byte 0x000000AC
	.4byte "@371"
.endobj "@372"

# 0x00000000..0x00000001 | size: 0x1
.section .sbss, "wa", @nobits
.balign 8

# .sbss:0x0 | size: 0x1
.obj "@171", local
	.skip 0x1
.endobj "@171"

# 0x00000000..0x00000004 | size: 0x4
.section .sdata2, "a"
.balign 8

# .sdata2:0x0 | size: 0x4
.obj "@88", local
	.4byte 0x00000000
.endobj "@88"

# 0x00000000..0x00000018 | size: 0x18
.section extab, "a", unique, 1
.balign 4

# extab:0x0 | size: 0x8
.obj "@etb_8000D5D4", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r30-r31
 */
	.4byte 0x10080000
	.4byte 0x00000000
.endobj "@etb_8000D5D4"

# extab:0x8 | size: 0x8
.obj "@etb_8000D5DC", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r29-r31
 */
	.4byte 0x18080000
	.4byte 0x00000000
.endobj "@etb_8000D5DC"

# extab:0x10 | size: 0x8
.obj "@etb_8000D538", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r31
 */
	.4byte 0x08080000
	.4byte 0x00000000
.endobj "@etb_8000D538"

# 0x00000000..0x00000024 | size: 0x24
.section extabindex, "a", unique, 1
.balign 4

# extabindex:0x0 | size: 0xC
.obj "@eti_80024ED8", local
	.4byte fn_8013D940
	.4byte 0x000000C0
	.4byte "@etb_8000D5D4"
.endobj "@eti_80024ED8"

# extabindex:0xC | size: 0xC
.obj "@eti_80024EE4", local
	.4byte fn_8013DA00
	.4byte 0x000000C8
	.4byte "@etb_8000D5DC"
.endobj "@eti_80024EE4"

# extabindex:0x18 | size: 0xC
.obj "@eti_80024F20", local
	.4byte dtor_8013DCBC
	.4byte 0x00000048
	.4byte "@etb_8000D538"
.endobj "@eti_80024F20"
