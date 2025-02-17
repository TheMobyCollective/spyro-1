.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

.section .rodata.jtbl
.align 3
dlabel jtbl_800112E8
/* 1AE8 800112E8 80AC0480 */ .word .L8004AC80
/* 1AEC 800112EC 88AC0480 */ .word .L8004AC88
/* 1AF0 800112F0 88AC0480 */ .word .L8004AC88
/* 1AF4 800112F4 88AC0480 */ .word .L8004AC88
/* 1AF8 800112F8 68AC0480 */ .word .L8004AC68
/* 1AFC 800112FC 88AC0480 */ .word .L8004AC88
/* 1B00 80011300 88AC0480 */ .word .L8004AC88
/* 1B04 80011304 88AC0480 */ .word .L8004AC88
/* 1B08 80011308 68AC0480 */ .word .L8004AC68
/* 1B0C 8001130C 88AC0480 */ .word .L8004AC88
/* 1B10 80011310 88AC0480 */ .word .L8004AC88
/* 1B14 80011314 88AC0480 */ .word .L8004AC88
/* 1B18 80011318 88AC0480 */ .word .L8004AC88
/* 1B1C 8001131C 88AC0480 */ .word .L8004AC88
/* 1B20 80011320 88AC0480 */ .word .L8004AC88
/* 1B24 80011324 88AC0480 */ .word .L8004AC88
/* 1B28 80011328 88AC0480 */ .word .L8004AC88
/* 1B2C 8001132C 88AC0480 */ .word .L8004AC88
/* 1B30 80011330 88AC0480 */ .word .L8004AC88
/* 1B34 80011334 88AC0480 */ .word .L8004AC88
/* 1B38 80011338 88AC0480 */ .word .L8004AC88
/* 1B3C 8001133C 88AC0480 */ .word .L8004AC88
/* 1B40 80011340 88AC0480 */ .word .L8004AC88
/* 1B44 80011344 88AC0480 */ .word .L8004AC88
/* 1B48 80011348 88AC0480 */ .word .L8004AC88
/* 1B4C 8001134C 68AC0480 */ .word .L8004AC68
/* 1B50 80011350 88AC0480 */ .word .L8004AC88
/* 1B54 80011354 88AC0480 */ .word .L8004AC88
/* 1B58 80011358 88AC0480 */ .word .L8004AC88
/* 1B5C 8001135C 88AC0480 */ .word .L8004AC88
/* 1B60 80011360 88AC0480 */ .word .L8004AC88
/* 1B64 80011364 88AC0480 */ .word .L8004AC88
/* 1B68 80011368 88AC0480 */ .word .L8004AC88
/* 1B6C 8001136C 88AC0480 */ .word .L8004AC88
/* 1B70 80011370 88AC0480 */ .word .L8004AC88
/* 1B74 80011374 88AC0480 */ .word .L8004AC88
/* 1B78 80011378 88AC0480 */ .word .L8004AC88
/* 1B7C 8001137C 68AC0480 */ .word .L8004AC68
.size jtbl_800112E8, . - jtbl_800112E8


.section .text
/* Generated by spimdisasm 1.27.0 */

glabel func_8004AC24
/* 3B424 8004AC24 0880023C */  lui        $v0, %hi(g_Spyro + 0x78)
/* 3B428 8004AC28 D08A428C */  lw         $v0, %lo(g_Spyro + 0x78)($v0)
/* 3B42C 8004AC2C C8FFBD27 */  addiu      $sp, $sp, -0x38
/* 3B430 8004AC30 2800B0AF */  sw         $s0, 0x28($sp)
/* 3B434 8004AC34 21808000 */  addu       $s0, $a0, $zero
/* 3B438 8004AC38 3000BFAF */  sw         $ra, 0x30($sp)
/* 3B43C 8004AC3C F9FF4324 */  addiu      $v1, $v0, -0x7
/* 3B440 8004AC40 2600622C */  sltiu      $v0, $v1, 0x26
/* 3B444 8004AC44 10004010 */  beqz       $v0, .L8004AC88
/* 3B448 8004AC48 2C00B1AF */   sw        $s1, 0x2C($sp)
/* 3B44C 8004AC4C 80100300 */  sll        $v0, $v1, 2
/* 3B450 8004AC50 0180013C */  lui        $at, %hi(jtbl_800112E8)
/* 3B454 8004AC54 21082200 */  addu       $at, $at, $v0
/* 3B458 8004AC58 E812228C */  lw         $v0, %lo(jtbl_800112E8)($at)
/* 3B45C 8004AC5C 00000000 */  nop
/* 3B460 8004AC60 08004000 */  jr         $v0
/* 3B464 8004AC64 00000000 */   nop
.L8004AC68:
/* 3B468 8004AC68 0880043C */  lui        $a0, %hi(g_Spyro)
/* 3B46C 8004AC6C 588A8424 */  addiu      $a0, $a0, %lo(g_Spyro)
/* 3B470 8004AC70 A958010C */  jal        func_800562A4
/* 3B474 8004AC74 02000524 */   addiu     $a1, $zero, 0x2
/* 3B478 8004AC78 222B0108 */  j          .L8004AC88
/* 3B47C 8004AC7C 00000000 */   nop
.L8004AC80:
/* 3B480 8004AC80 0880013C */  lui        $at, %hi(g_Spyro + 0x2B)
/* 3B484 8004AC84 838A20A0 */  sb         $zero, %lo(g_Spyro + 0x2B)($at)
.L8004AC88:
/* 3B488 8004AC88 40000012 */  beqz       $s0, .L8004AD8C
/* 3B48C 8004AC8C 1000A427 */   addiu     $a0, $sp, 0x10
/* 3B490 8004AC90 0880103C */  lui        $s0, %hi(g_Spyro)
/* 3B494 8004AC94 588A1026 */  addiu      $s0, $s0, %lo(g_Spyro)
/* 3B498 8004AC98 C05D000C */  jal        VecCopy
/* 3B49C 8004AC9C 21280002 */   addu      $a1, $s0, $zero
/* 3B4A0 8004ACA0 21200002 */  addu       $a0, $s0, $zero
/* 3B4A4 8004ACA4 0880023C */  lui        $v0, %hi(g_Spyro + 0xC)
/* 3B4A8 8004ACA8 648A4290 */  lbu        $v0, %lo(g_Spyro + 0xC)($v0)
/* 3B4AC 8004ACAC 0880033C */  lui        $v1, %hi(g_Spyro + 0xD)
/* 3B4B0 8004ACB0 658A6390 */  lbu        $v1, %lo(g_Spyro + 0xD)($v1)
/* 3B4B4 8004ACB4 0880063C */  lui        $a2, %hi(g_Spyro + 0xE)
/* 3B4B8 8004ACB8 668AC690 */  lbu        $a2, %lo(g_Spyro + 0xE)($a2)
/* 3B4BC 8004ACBC 0880113C */  lui        $s1, %hi(g_Spyro + 0x164)
/* 3B4C0 8004ACC0 BC8B318E */  lw         $s1, %lo(g_Spyro + 0x164)($s1)
/* 3B4C4 8004ACC4 21280000 */  addu       $a1, $zero, $zero
/* 3B4C8 8004ACC8 2200A6A3 */  sb         $a2, 0x22($sp)
/* 3B4CC 8004ACCC A4020624 */  addiu      $a2, $zero, 0x2A4
/* 3B4D0 8004ACD0 2000A2A3 */  sb         $v0, 0x20($sp)
/* 3B4D4 8004ACD4 455A000C */  jal        Memset
/* 3B4D8 8004ACD8 2100A3A3 */   sb        $v1, 0x21($sp)
/* 3B4DC 8004ACDC 21200002 */  addu       $a0, $s0, $zero
/* 3B4E0 8004ACE0 C05D000C */  jal        VecCopy
/* 3B4E4 8004ACE4 1000A527 */   addiu     $a1, $sp, 0x10
/* 3B4E8 8004ACE8 2000A393 */  lbu        $v1, 0x20($sp)
/* 3B4EC 8004ACEC 2100A593 */  lbu        $a1, 0x21($sp)
/* 3B4F0 8004ACF0 2200A693 */  lbu        $a2, 0x22($sp)
/* 3B4F4 8004ACF4 04000224 */  addiu      $v0, $zero, 0x4
/* 3B4F8 8004ACF8 0880013C */  lui        $at, %hi(g_Spyro + 0x27)
/* 3B4FC 8004ACFC 7F8A22A0 */  sb         $v0, %lo(g_Spyro + 0x27)($at)
/* 3B500 8004AD00 01000224 */  addiu      $v0, $zero, 0x1
/* 3B504 8004AD04 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 3B508 8004AD08 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 3B50C 8004AD0C FFFF0224 */  addiu      $v0, $zero, -0x1
/* 3B510 8004AD10 0880013C */  lui        $at, %hi(g_Spyro + 0x164)
/* 3B514 8004AD14 BC8B31AC */  sw         $s1, %lo(g_Spyro + 0x164)($at)
/* 3B518 8004AD18 0880013C */  lui        $at, %hi(g_Spyro + 0x274)
/* 3B51C 8004AD1C CC8C22AC */  sw         $v0, %lo(g_Spyro + 0x274)($at)
/* 3B520 8004AD20 0880013C */  lui        $at, %hi(g_Spyro + 0xC)
/* 3B524 8004AD24 648A23A0 */  sb         $v1, %lo(g_Spyro + 0xC)($at)
/* 3B528 8004AD28 00190300 */  sll        $v1, $v1, 4
/* 3B52C 8004AD2C 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 3B530 8004AD30 658A25A0 */  sb         $a1, %lo(g_Spyro + 0xD)($at)
/* 3B534 8004AD34 00290500 */  sll        $a1, $a1, 4
/* 3B538 8004AD38 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 3B53C 8004AD3C 668A26A0 */  sb         $a2, %lo(g_Spyro + 0xE)($at)
/* 3B540 8004AD40 00310600 */  sll        $a2, $a2, 4
/* 3B544 8004AD44 0880013C */  lui        $at, %hi(g_Spyro + 0x124)
/* 3B548 8004AD48 7C8B23AC */  sw         $v1, %lo(g_Spyro + 0x124)($at)
/* 3B54C 8004AD4C 0880013C */  lui        $at, %hi(g_Spyro + 0x120)
/* 3B550 8004AD50 788B25AC */  sw         $a1, %lo(g_Spyro + 0x120)($at)
/* 3B554 8004AD54 0880013C */  lui        $at, %hi(g_Spyro + 0x11C)
/* 3B558 8004AD58 748B26AC */  sw         $a2, %lo(g_Spyro + 0x11C)($at)
/* 3B55C 8004AD5C 9AFA000C */  jal        func_8003EA68
/* 3B560 8004AD60 21200000 */   addu      $a0, $zero, $zero
/* 3B564 8004AD64 FF000224 */  addiu      $v0, $zero, 0xFF
/* 3B568 8004AD68 0880013C */  lui        $at, %hi(g_Spyro + 0x16C)
/* 3B56C 8004AD6C C48B22AC */  sw         $v0, %lo(g_Spyro + 0x16C)($at)
/* 3B570 8004AD70 3F000224 */  addiu      $v0, $zero, 0x3F
/* 3B574 8004AD74 0880013C */  lui        $at, %hi(g_Spyro + 0x2A0)
/* 3B578 8004AD78 F88C22A0 */  sb         $v0, %lo(g_Spyro + 0x2A0)($at)
/* 3B57C 8004AD7C 0880013C */  lui        $at, %hi(D_80078768)
/* 3B580 8004AD80 688720AC */  sw         $zero, %lo(D_80078768)($at)
/* 3B584 8004AD84 882B0108 */  j          .L8004AE20
/* 3B588 8004AD88 00000000 */   nop
.L8004AD8C:
/* 3B58C 8004AD8C 0880033C */  lui        $v1, %hi(g_Spyro + 0xC)
/* 3B590 8004AD90 648A6390 */  lbu        $v1, %lo(g_Spyro + 0xC)($v1)
/* 3B594 8004AD94 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 3B598 8004AD98 0880013C */  lui        $at, %hi(g_Spyro + 0x274)
/* 3B59C 8004AD9C CC8C22AC */  sw         $v0, %lo(g_Spyro + 0x274)($at)
/* 3B5A0 8004ADA0 FF000224 */  addiu      $v0, $zero, 0xFF
/* 3B5A4 8004ADA4 0880013C */  lui        $at, %hi(g_Spyro + 0x16C)
/* 3B5A8 8004ADA8 C48B22AC */  sw         $v0, %lo(g_Spyro + 0x16C)($at)
/* 3B5AC 8004ADAC 0880023C */  lui        $v0, %hi(g_Spyro + 0xD)
/* 3B5B0 8004ADB0 658A4290 */  lbu        $v0, %lo(g_Spyro + 0xD)($v0)
/* 3B5B4 8004ADB4 0880013C */  lui        $at, %hi(g_Spyro + 0x28)
/* 3B5B8 8004ADB8 808A20AC */  sw         $zero, %lo(g_Spyro + 0x28)($at)
/* 3B5BC 8004ADBC 0880013C */  lui        $at, %hi(g_Spyro + 0x2C)
/* 3B5C0 8004ADC0 848A20AC */  sw         $zero, %lo(g_Spyro + 0x2C)($at)
/* 3B5C4 8004ADC4 0880013C */  lui        $at, %hi(g_Spyro + 0x30)
/* 3B5C8 8004ADC8 888A20AC */  sw         $zero, %lo(g_Spyro + 0x30)($at)
/* 3B5CC 8004ADCC 0880013C */  lui        $at, %hi(g_Spyro + 0x24C)
/* 3B5D0 8004ADD0 A48C20AC */  sw         $zero, %lo(g_Spyro + 0x24C)($at)
/* 3B5D4 8004ADD4 0880013C */  lui        $at, %hi(g_Spyro + 0x250)
/* 3B5D8 8004ADD8 A88C20AC */  sw         $zero, %lo(g_Spyro + 0x250)($at)
/* 3B5DC 8004ADDC 0880013C */  lui        $at, %hi(g_Spyro + 0x254)
/* 3B5E0 8004ADE0 AC8C20AC */  sw         $zero, %lo(g_Spyro + 0x254)($at)
/* 3B5E4 8004ADE4 0880013C */  lui        $at, %hi(g_Spyro + 0x168)
/* 3B5E8 8004ADE8 C08B20AC */  sw         $zero, %lo(g_Spyro + 0x168)($at)
/* 3B5EC 8004ADEC 0880013C */  lui        $at, %hi(D_80078768)
/* 3B5F0 8004ADF0 688720AC */  sw         $zero, %lo(D_80078768)($at)
/* 3B5F4 8004ADF4 00190300 */  sll        $v1, $v1, 4
/* 3B5F8 8004ADF8 0880013C */  lui        $at, %hi(g_Spyro + 0x124)
/* 3B5FC 8004ADFC 7C8B23AC */  sw         $v1, %lo(g_Spyro + 0x124)($at)
/* 3B600 8004AE00 0880033C */  lui        $v1, %hi(g_Spyro + 0xE)
/* 3B604 8004AE04 668A6390 */  lbu        $v1, %lo(g_Spyro + 0xE)($v1)
/* 3B608 8004AE08 00110200 */  sll        $v0, $v0, 4
/* 3B60C 8004AE0C 0880013C */  lui        $at, %hi(g_Spyro + 0x120)
/* 3B610 8004AE10 788B22AC */  sw         $v0, %lo(g_Spyro + 0x120)($at)
/* 3B614 8004AE14 00190300 */  sll        $v1, $v1, 4
/* 3B618 8004AE18 0880013C */  lui        $at, %hi(g_Spyro + 0x11C)
/* 3B61C 8004AE1C 748B23AC */  sw         $v1, %lo(g_Spyro + 0x11C)($at)
.L8004AE20:
/* 3B620 8004AE20 3000BF8F */  lw         $ra, 0x30($sp)
/* 3B624 8004AE24 2C00B18F */  lw         $s1, 0x2C($sp)
/* 3B628 8004AE28 2800B08F */  lw         $s0, 0x28($sp)
/* 3B62C 8004AE2C 3800BD27 */  addiu      $sp, $sp, 0x38
/* 3B630 8004AE30 0800E003 */  jr         $ra
/* 3B634 8004AE34 00000000 */   nop
.size func_8004AC24, . - func_8004AC24
