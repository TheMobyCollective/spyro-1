.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003ABC0
/* 2B3C0 8003ABC0 A0FFBD27 */  addiu      $sp, $sp, -0x60
/* 2B3C4 8003ABC4 4400B3AF */  sw         $s3, 0x44($sp)
/* 2B3C8 8003ABC8 21988000 */  addu       $s3, $a0, $zero
/* 2B3CC 8003ABCC 3C00B1AF */  sw         $s1, 0x3C($sp)
/* 2B3D0 8003ABD0 2188A000 */  addu       $s1, $a1, $zero
/* 2B3D4 8003ABD4 5400B7AF */  sw         $s7, 0x54($sp)
/* 2B3D8 8003ABD8 21B8C000 */  addu       $s7, $a2, $zero
/* 2B3DC 8003ABDC 5800BFAF */  sw         $ra, 0x58($sp)
/* 2B3E0 8003ABE0 5000B6AF */  sw         $s6, 0x50($sp)
/* 2B3E4 8003ABE4 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 2B3E8 8003ABE8 4800B4AF */  sw         $s4, 0x48($sp)
/* 2B3EC 8003ABEC 4000B2AF */  sw         $s2, 0x40($sp)
/* 2B3F0 8003ABF0 3800B0AF */  sw         $s0, 0x38($sp)
/* 2B3F4 8003ABF4 53006292 */  lbu        $v0, 0x53($s3)
/* 2B3F8 8003ABF8 00000000 */  nop
/* 2B3FC 8003ABFC 7F005030 */  andi       $s0, $v0, 0x7F
/* 2B400 8003AC00 FFFF0226 */  addiu      $v0, $s0, -0x1
/* 2B404 8003AC04 7E00422C */  sltiu      $v0, $v0, 0x7E
/* 2B408 8003AC08 09004010 */  beqz       $v0, .L8003AC30
/* 2B40C 8003AC0C 21B0E000 */   addu      $s6, $a3, $zero
/* 2B410 8003AC10 3A006392 */  lbu        $v1, 0x3A($s3)
/* 2B414 8003AC14 00000000 */  nop
/* 2B418 8003AC18 80006230 */  andi       $v0, $v1, 0x80
/* 2B41C 8003AC1C 23014014 */  bnez       $v0, .L8003B0AC
/* 2B420 8003AC20 21100000 */   addu      $v0, $zero, $zero
/* 2B424 8003AC24 80006234 */  ori        $v0, $v1, 0x80
/* 2B428 8003AC28 22EB0008 */  j          .L8003AC88
/* 2B42C 8003AC2C 3A0062A2 */   sb        $v0, 0x3A($s3)
.L8003AC30:
/* 2B430 8003AC30 CB89010C */  jal        rand
/* 2B434 8003AC34 0F001024 */   addiu     $s0, $zero, 0xF
/* 2B438 8003AC38 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 2B43C 8003AC3C 40180200 */  sll        $v1, $v0, 1
/* 2B440 8003AC40 21186200 */  addu       $v1, $v1, $v0
/* 2B444 8003AC44 C0180300 */  sll        $v1, $v1, 3
/* 2B448 8003AC48 21186200 */  addu       $v1, $v1, $v0
/* 2B44C 8003AC4C 821A0300 */  srl        $v1, $v1, 10
/* 2B450 8003AC50 02006228 */  slti       $v0, $v1, 0x2
/* 2B454 8003AC54 03004010 */  beqz       $v0, .L8003AC64
/* 2B458 8003AC58 00000000 */   nop
/* 2B45C 8003AC5C 22EB0008 */  j          .L8003AC88
/* 2B460 8003AC60 0E001024 */   addiu     $s0, $zero, 0xE
.L8003AC64:
/* 2B464 8003AC64 0880023C */  lui        $v0, %hi(g_Spyro + 0x164)
/* 2B468 8003AC68 BC8B428C */  lw         $v0, %lo(g_Spyro + 0x164)($v0)
/* 2B46C 8003AC6C 00000000 */  nop
/* 2B470 8003AC70 03004228 */  slti       $v0, $v0, 0x3
/* 2B474 8003AC74 04004010 */  beqz       $v0, .L8003AC88
/* 2B478 8003AC78 0C006228 */   slti      $v0, $v1, 0xC
/* 2B47C 8003AC7C 03004010 */  beqz       $v0, .L8003AC8C
/* 2B480 8003AC80 10000224 */   addiu     $v0, $zero, 0x10
/* 2B484 8003AC84 10001024 */  addiu      $s0, $zero, 0x10
.L8003AC88:
/* 2B488 8003AC88 10000224 */  addiu      $v0, $zero, 0x10
.L8003AC8C:
/* 2B48C 8003AC8C 24000216 */  bne        $s0, $v0, .L8003AD20
/* 2B490 8003AC90 0E000224 */   addiu     $v0, $zero, 0xE
/* 2B494 8003AC94 0780023C */  lui        $v0, %hi(D_80075898)
/* 2B498 8003AC98 9858428C */  lw         $v0, %lo(D_80075898)($v0)
/* 2B49C 8003AC9C 00000000 */  nop
/* 2B4A0 8003ACA0 08004014 */  bnez       $v0, .L8003ACC4
/* 2B4A4 8003ACA4 10000424 */   addiu     $a0, $zero, 0x10
/* 2B4A8 8003ACA8 0880103C */  lui        $s0, %hi(g_Spyro + 0x164)
/* 2B4AC 8003ACAC BC8B1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x164)
/* 2B4B0 8003ACB0 0000028E */  lw         $v0, 0x0($s0)
/* 2B4B4 8003ACB4 00000000 */  nop
/* 2B4B8 8003ACB8 09004104 */  bgez       $v0, .L8003ACE0
/* 2B4BC 8003ACBC 78000424 */   addiu     $a0, $zero, 0x78
/* 2B4C0 8003ACC0 10000424 */  addiu      $a0, $zero, 0x10
.L8003ACC4:
/* 2B4C4 8003ACC4 0780023C */  lui        $v0, %hi(g_SpawnMoby)
/* 2B4C8 8003ACC8 CC58428C */  lw         $v0, %lo(g_SpawnMoby)($v0)
/* 2B4CC 8003ACCC 00000000 */  nop
/* 2B4D0 8003ACD0 09F84000 */  jalr       $v0
/* 2B4D4 8003ACD4 21286002 */   addu      $a1, $s3, $zero
/* 2B4D8 8003ACD8 D9EB0008 */  j          .L8003AF64
/* 2B4DC 8003ACDC 21904000 */   addu      $s2, $v0, $zero
.L8003ACE0:
/* 2B4E0 8003ACE0 0780023C */  lui        $v0, %hi(g_SpawnMoby)
/* 2B4E4 8003ACE4 CC58428C */  lw         $v0, %lo(g_SpawnMoby)($v0)
/* 2B4E8 8003ACE8 00000000 */  nop
/* 2B4EC 8003ACEC 09F84000 */  jalr       $v0
/* 2B4F0 8003ACF0 21286002 */   addu      $a1, $s3, $zero
/* 2B4F4 8003ACF4 21904000 */  addu       $s2, $v0, $zero
/* 2B4F8 8003ACF8 21204002 */  addu       $a0, $s2, $zero
/* 2B4FC 8003ACFC 21280000 */  addu       $a1, $zero, $zero
/* 2B500 8003AD00 47E1000C */  jal        func_8003851C
/* 2B504 8003AD04 21300000 */   addu      $a2, $zero, $zero
/* 2B508 8003AD08 01000224 */  addiu      $v0, $zero, 0x1
/* 2B50C 8003AD0C 000002AE */  sw         $v0, 0x0($s0)
/* 2B510 8003AD10 0780013C */  lui        $at, %hi(D_80075898)
/* 2B514 8003AD14 985832AC */  sw         $s2, %lo(D_80075898)($at)
/* 2B518 8003AD18 2BEC0008 */  j          .L8003B0AC
/* 2B51C 8003AD1C 21104002 */   addu      $v0, $s2, $zero
.L8003AD20:
/* 2B520 8003AD20 0A000216 */  bne        $s0, $v0, .L8003AD4C
/* 2B524 8003AD24 21200002 */   addu      $a0, $s0, $zero
/* 2B528 8003AD28 0E000424 */  addiu      $a0, $zero, 0xE
/* 2B52C 8003AD2C 0780023C */  lui        $v0, %hi(g_SpawnMoby)
/* 2B530 8003AD30 CC58428C */  lw         $v0, %lo(g_SpawnMoby)($v0)
/* 2B534 8003AD34 00000000 */  nop
/* 2B538 8003AD38 09F84000 */  jalr       $v0
/* 2B53C 8003AD3C 21286002 */   addu      $a1, $s3, $zero
/* 2B540 8003AD40 0000558C */  lw         $s5, 0x0($v0)
/* 2B544 8003AD44 29EC0008 */  j          .L8003B0A4
/* 2B548 8003AD48 21904000 */   addu      $s2, $v0, $zero
.L8003AD4C:
/* 2B54C 8003AD4C 0780023C */  lui        $v0, %hi(g_SpawnMoby)
/* 2B550 8003AD50 CC58428C */  lw         $v0, %lo(g_SpawnMoby)($v0)
/* 2B554 8003AD54 00000000 */  nop
/* 2B558 8003AD58 09F84000 */  jalr       $v0
/* 2B55C 8003AD5C 21286002 */   addu      $a1, $s3, $zero
/* 2B560 8003AD60 21904000 */  addu       $s2, $v0, $zero
/* 2B564 8003AD64 0000558E */  lw         $s5, 0x0($s2)
/* 2B568 8003AD68 04002016 */  bnez       $s1, .L8003AD7C
/* 2B56C 8003AD6C 06000224 */   addiu     $v0, $zero, 0x6
/* 2B570 8003AD70 2800A427 */  addiu      $a0, $sp, 0x28
/* 2B574 8003AD74 76EB0008 */  j          .L8003ADD8
/* 2B578 8003AD78 0C006526 */   addiu     $a1, $s3, 0xC
.L8003AD7C:
/* 2B57C 8003AD7C 10002216 */  bne        $s1, $v0, .L8003ADC0
/* 2B580 8003AD80 01000224 */   addiu     $v0, $zero, 0x1
/* 2B584 8003AD84 2800A427 */  addiu      $a0, $sp, 0x28
/* 2B588 8003AD88 C05D000C */  jal        VecCopy
/* 2B58C 8003AD8C 0C006526 */   addiu     $a1, $s3, 0xC
/* 2B590 8003AD90 CB89010C */  jal        rand
/* 2B594 8003AD94 2C011424 */   addiu     $s4, $zero, 0x12C
/* 2B598 8003AD98 2800A38F */  lw         $v1, 0x28($sp)
/* 2B59C 8003AD9C FF014230 */  andi       $v0, $v0, 0x1FF
/* 2B5A0 8003ADA0 00FF6324 */  addiu      $v1, $v1, -0x100
/* 2B5A4 8003ADA4 21186200 */  addu       $v1, $v1, $v0
/* 2B5A8 8003ADA8 CB89010C */  jal        rand
/* 2B5AC 8003ADAC 2800A3AF */   sw        $v1, 0x28($sp)
/* 2B5B0 8003ADB0 2C00A38F */  lw         $v1, 0x2C($sp)
/* 2B5B4 8003ADB4 FF014230 */  andi       $v0, $v0, 0x1FF
/* 2B5B8 8003ADB8 CCEB0008 */  j          .L8003AF30
/* 2B5BC 8003ADBC 00FF6324 */   addiu     $v1, $v1, -0x100
.L8003ADC0:
/* 2B5C0 8003ADC0 4D002212 */  beq        $s1, $v0, .L8003AEF8
/* 2B5C4 8003ADC4 02000224 */   addiu     $v0, $zero, 0x2
/* 2B5C8 8003ADC8 07002216 */  bne        $s1, $v0, .L8003ADE8
/* 2B5CC 8003ADCC FDFF2226 */   addiu     $v0, $s1, -0x3
/* 2B5D0 8003ADD0 2800A427 */  addiu      $a0, $sp, 0x28
/* 2B5D4 8003ADD4 2128C002 */  addu       $a1, $s6, $zero
.L8003ADD8:
/* 2B5D8 8003ADD8 C05D000C */  jal        VecCopy
/* 2B5DC 8003ADDC 8C001424 */   addiu     $s4, $zero, 0x8C
/* 2B5E0 8003ADE0 DBEB0008 */  j          .L8003AF6C
/* 2B5E4 8003ADE4 00000000 */   nop
.L8003ADE8:
/* 2B5E8 8003ADE8 0200422C */  sltiu      $v0, $v0, 0x2
/* 2B5EC 8003ADEC 53004010 */  beqz       $v0, .L8003AF3C
/* 2B5F0 8003ADF0 04000224 */   addiu     $v0, $zero, 0x4
/* 2B5F4 8003ADF4 26002212 */  beq        $s1, $v0, .L8003AE90
/* 2B5F8 8003ADF8 0B000224 */   addiu     $v0, $zero, 0xB
/* 2B5FC 8003ADFC 0880033C */  lui        $v1, %hi(g_Spyro + 0x78)
/* 2B600 8003AE00 D08A638C */  lw         $v1, %lo(g_Spyro + 0x78)($v1)
/* 2B604 8003AE04 00000000 */  nop
/* 2B608 8003AE08 07006210 */  beq        $v1, $v0, .L8003AE28
/* 2B60C 8003AE0C 18000224 */   addiu     $v0, $zero, 0x18
/* 2B610 8003AE10 05006210 */  beq        $v1, $v0, .L8003AE28
/* 2B614 8003AE14 14000224 */   addiu     $v0, $zero, 0x14
/* 2B618 8003AE18 03006210 */  beq        $v1, $v0, .L8003AE28
/* 2B61C 8003AE1C 2C000224 */   addiu     $v0, $zero, 0x2C
/* 2B620 8003AE20 36006214 */  bne        $v1, $v0, .L8003AEFC
/* 2B624 8003AE24 2800A427 */   addiu     $a0, $sp, 0x28
.L8003AE28:
/* 2B628 8003AE28 04000224 */  addiu      $v0, $zero, 0x4
/* 2B62C 8003AE2C 19002212 */  beq        $s1, $v0, .L8003AE94
/* 2B630 8003AE30 0C005026 */   addiu     $s0, $s2, 0xC
/* 2B634 8003AE34 0880053C */  lui        $a1, %hi(g_Spyro)
/* 2B638 8003AE38 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
/* 2B63C 8003AE3C 645E000C */  jal        OctDistance
/* 2B640 8003AE40 0C004426 */   addiu     $a0, $s2, 0xC
/* 2B644 8003AE44 00084228 */  slti       $v0, $v0, 0x800
/* 2B648 8003AE48 2C004010 */  beqz       $v0, .L8003AEFC
/* 2B64C 8003AE4C 2800A427 */   addiu     $a0, $sp, 0x28
/* 2B650 8003AE50 38004386 */  lh         $v1, 0x38($s2)
/* 2B654 8003AE54 1400428E */  lw         $v0, 0x14($s2)
/* 2B658 8003AE58 0880043C */  lui        $a0, %hi(g_Spyro + 0x8)
/* 2B65C 8003AE5C 608A848C */  lw         $a0, %lo(g_Spyro + 0x8)($a0)
/* 2B660 8003AE60 23184300 */  subu       $v1, $v0, $v1
/* 2B664 8003AE64 23106400 */  subu       $v0, $v1, $a0
/* 2B668 8003AE68 05004018 */  blez       $v0, .L8003AE80
/* 2B66C 8003AE6C 00044228 */   slti      $v0, $v0, 0x400
/* 2B670 8003AE70 08004014 */  bnez       $v0, .L8003AE94
/* 2B674 8003AE74 0C005026 */   addiu     $s0, $s2, 0xC
/* 2B678 8003AE78 BFEB0008 */  j          .L8003AEFC
/* 2B67C 8003AE7C 2800A427 */   addiu     $a0, $sp, 0x28
.L8003AE80:
/* 2B680 8003AE80 23108300 */  subu       $v0, $a0, $v1
/* 2B684 8003AE84 00044228 */  slti       $v0, $v0, 0x400
/* 2B688 8003AE88 1C004010 */  beqz       $v0, .L8003AEFC
/* 2B68C 8003AE8C 2800A427 */   addiu     $a0, $sp, 0x28
.L8003AE90:
/* 2B690 8003AE90 0C005026 */  addiu      $s0, $s2, 0xC
.L8003AE94:
/* 2B694 8003AE94 21200002 */  addu       $a0, $s0, $zero
/* 2B698 8003AE98 C05D000C */  jal        VecCopy
/* 2B69C 8003AE9C 0C006526 */   addiu     $a1, $s3, 0xC
/* 2B6A0 8003AEA0 2120A002 */  addu       $a0, $s5, $zero
/* 2B6A4 8003AEA4 1400428E */  lw         $v0, 0x14($s2)
/* 2B6A8 8003AEA8 21280002 */  addu       $a1, $s0, $zero
/* 2B6AC 8003AEAC 00014224 */  addiu      $v0, $v0, 0x100
/* 2B6B0 8003AEB0 C05D000C */  jal        VecCopy
/* 2B6B4 8003AEB4 140042AE */   sw        $v0, 0x14($s2)
/* 2B6B8 8003AEB8 CB89010C */  jal        rand
/* 2B6BC 8003AEBC 00000000 */   nop
/* 2B6C0 8003AEC0 0E004230 */  andi       $v0, $v0, 0xE
/* 2B6C4 8003AEC4 CB89010C */  jal        rand
/* 2B6C8 8003AEC8 1100A2A2 */   sb        $v0, 0x11($s5)
/* 2B6CC 8003AECC 0E004230 */  andi       $v0, $v0, 0xE
/* 2B6D0 8003AED0 CB89010C */  jal        rand
/* 2B6D4 8003AED4 1200A2A2 */   sb        $v0, 0x12($s5)
/* 2B6D8 8003AED8 0E004330 */  andi       $v1, $v0, 0xE
/* 2B6DC 8003AEDC 21104002 */  addu       $v0, $s2, $zero
/* 2B6E0 8003AEE0 1300A3A2 */  sb         $v1, 0x13($s5)
/* 2B6E4 8003AEE4 03000324 */  addiu      $v1, $zero, 0x3
/* 2B6E8 8003AEE8 490043A0 */  sb         $v1, 0x49($v0)
/* 2B6EC 8003AEEC FF000324 */  addiu      $v1, $zero, 0xFF
/* 2B6F0 8003AEF0 2BEC0008 */  j          .L8003B0AC
/* 2B6F4 8003AEF4 520043A0 */   sb        $v1, 0x52($v0)
.L8003AEF8:
/* 2B6F8 8003AEF8 2800A427 */  addiu      $a0, $sp, 0x28
.L8003AEFC:
/* 2B6FC 8003AEFC C05D000C */  jal        VecCopy
/* 2B700 8003AF00 0C006526 */   addiu     $a1, $s3, 0xC
/* 2B704 8003AF04 CB89010C */  jal        rand
/* 2B708 8003AF08 8C001424 */   addiu     $s4, $zero, 0x8C
/* 2B70C 8003AF0C 2800A38F */  lw         $v1, 0x28($sp)
/* 2B710 8003AF10 FF034230 */  andi       $v0, $v0, 0x3FF
/* 2B714 8003AF14 00FE6324 */  addiu      $v1, $v1, -0x200
/* 2B718 8003AF18 21186200 */  addu       $v1, $v1, $v0
/* 2B71C 8003AF1C CB89010C */  jal        rand
/* 2B720 8003AF20 2800A3AF */   sw        $v1, 0x28($sp)
/* 2B724 8003AF24 2C00A38F */  lw         $v1, 0x2C($sp)
/* 2B728 8003AF28 FF034230 */  andi       $v0, $v0, 0x3FF
/* 2B72C 8003AF2C 00FE6324 */  addiu      $v1, $v1, -0x200
.L8003AF30:
/* 2B730 8003AF30 21186200 */  addu       $v1, $v1, $v0
/* 2B734 8003AF34 DBEB0008 */  j          .L8003AF6C
/* 2B738 8003AF38 2C00A3AF */   sw        $v1, 0x2C($sp)
.L8003AF3C:
/* 2B73C 8003AF3C 05000224 */  addiu      $v0, $zero, 0x5
/* 2B740 8003AF40 0A002216 */  bne        $s1, $v0, .L8003AF6C
/* 2B744 8003AF44 0C004426 */   addiu     $a0, $s2, 0xC
/* 2B748 8003AF48 C05D000C */  jal        VecCopy
/* 2B74C 8003AF4C 0C006526 */   addiu     $a1, $s3, 0xC
/* 2B750 8003AF50 1400428E */  lw         $v0, 0x14($s2)
/* 2B754 8003AF54 2120A002 */  addu       $a0, $s5, $zero
/* 2B758 8003AF58 00014224 */  addiu      $v0, $v0, 0x100
/* 2B75C 8003AF5C BC5D000C */  jal        VecNull
/* 2B760 8003AF60 140042AE */   sw        $v0, 0x14($s2)
.L8003AF64:
/* 2B764 8003AF64 2BEC0008 */  j          .L8003B0AC
/* 2B768 8003AF68 21104002 */   addu      $v0, $s2, $zero
.L8003AF6C:
/* 2B76C 8003AF6C 0500E012 */  beqz       $s7, .L8003AF84
/* 2B770 8003AF70 1800A427 */   addiu     $a0, $sp, 0x18
/* 2B774 8003AF74 C05D000C */  jal        VecCopy
/* 2B778 8003AF78 2128E002 */   addu      $a1, $s7, $zero
/* 2B77C 8003AF7C E8EB0008 */  j          .L8003AFA0
/* 2B780 8003AF80 2800B127 */   addiu     $s1, $sp, 0x28
.L8003AF84:
/* 2B784 8003AF84 C05D000C */  jal        VecCopy
/* 2B788 8003AF88 0C006526 */   addiu     $a1, $s3, 0xC
/* 2B78C 8003AF8C 2000A28F */  lw         $v0, 0x20($sp)
/* 2B790 8003AF90 00000000 */  nop
/* 2B794 8003AF94 00014224 */  addiu      $v0, $v0, 0x100
/* 2B798 8003AF98 2000A2AF */  sw         $v0, 0x20($sp)
/* 2B79C 8003AF9C 2800B127 */  addiu      $s1, $sp, 0x28
.L8003AFA0:
/* 2B7A0 8003AFA0 21202002 */  addu       $a0, $s1, $zero
/* 2B7A4 8003AFA4 3000A28F */  lw         $v0, 0x30($sp)
/* 2B7A8 8003AFA8 00080524 */  addiu      $a1, $zero, 0x800
/* 2B7AC 8003AFAC 00044224 */  addiu      $v0, $v0, 0x400
/* 2B7B0 8003AFB0 7B35010C */  jal        func_8004D5EC
/* 2B7B4 8003AFB4 3000A2AF */   sw        $v0, 0x30($sp)
/* 2B7B8 8003AFB8 0780043C */  lui        $a0, %hi(g_CollisionNormal)
/* 2B7BC 8003AFBC 68738424 */  addiu      $a0, $a0, %lo(g_CollisionNormal)
/* 2B7C0 8003AFC0 21280000 */  addu       $a1, $zero, $zero
/* 2B7C4 8003AFC4 3000A38F */  lw         $v1, 0x30($sp)
/* 2B7C8 8003AFC8 21804000 */  addu       $s0, $v0, $zero
/* 2B7CC 8003AFCC 00FC6324 */  addiu      $v1, $v1, -0x400
/* 2B7D0 8003AFD0 7F5C000C */  jal        VecMagnitude
/* 2B7D4 8003AFD4 3000A3AF */   sw        $v1, 0x30($sp)
/* 2B7D8 8003AFD8 0780043C */  lui        $a0, %hi(g_CollisionNormal + 0x8)
/* 2B7DC 8003AFDC 7073848C */  lw         $a0, %lo(g_CollisionNormal + 0x8)($a0)
/* 2B7E0 8003AFE0 6B5A000C */  jal        Atan2Fast
/* 2B7E4 8003AFE4 21284000 */   addu      $a1, $v0, $zero
/* 2B7E8 8003AFE8 00160200 */  sll        $v0, $v0, 24
/* 2B7EC 8003AFEC 0C000012 */  beqz       $s0, .L8003B020
/* 2B7F0 8003AFF0 03160200 */   sra       $v0, $v0, 24
/* 2B7F4 8003AFF4 18004228 */  slti       $v0, $v0, 0x18
/* 2B7F8 8003AFF8 09004010 */  beqz       $v0, .L8003B020
/* 2B7FC 8003AFFC 21202002 */   addu      $a0, $s1, $zero
/* 2B800 8003B000 C8000524 */  addiu      $a1, $zero, 0xC8
/* 2B804 8003B004 21300000 */  addu       $a2, $zero, $zero
/* 2B808 8003B008 21380000 */  addu       $a3, $zero, $zero
/* 2B80C 8003B00C 1000A0AF */  sw         $zero, 0x10($sp)
/* 2B810 8003B010 F238010C */  jal        func_8004E3C8
/* 2B814 8003B014 1400A0AF */   sw        $zero, 0x14($sp)
/* 2B818 8003B018 05004010 */  beqz       $v0, .L8003B030
/* 2B81C 8003B01C 21880000 */   addu      $s1, $zero, $zero
.L8003B020:
/* 2B820 8003B020 2800A427 */  addiu      $a0, $sp, 0x28
/* 2B824 8003B024 C05D000C */  jal        VecCopy
/* 2B828 8003B028 0C006526 */   addiu     $a1, $s3, 0xC
/* 2B82C 8003B02C 21880000 */  addu       $s1, $zero, $zero
.L8003B030:
/* 2B830 8003B030 2000A48F */  lw         $a0, 0x20($sp)
/* 2B834 8003B034 0500801A */  blez       $s4, .L8003B04C
/* 2B838 8003B038 21188002 */   addu      $v1, $s4, $zero
.L8003B03C:
/* 2B83C 8003B03C 21208300 */  addu       $a0, $a0, $v1
.L8003B040:
/* 2B840 8003B040 F6FF6324 */  addiu      $v1, $v1, -0xA
/* 2B844 8003B044 FDFF601C */  bgtz       $v1, .L8003B03C
/* 2B848 8003B048 01003126 */   addiu     $s1, $s1, 0x1
.L8003B04C:
/* 2B84C 8003B04C 3000A28F */  lw         $v0, 0x30($sp)
/* 2B850 8003B050 00000000 */  nop
/* 2B854 8003B054 2A104400 */  slt        $v0, $v0, $a0
/* 2B858 8003B058 F9FF4014 */  bnez       $v0, .L8003B040
/* 2B85C 8003B05C 21208300 */   addu      $a0, $a0, $v1
/* 2B860 8003B060 0C004426 */  addiu      $a0, $s2, 0xC
/* 2B864 8003B064 C05D000C */  jal        VecCopy
/* 2B868 8003B068 1800A527 */   addiu     $a1, $sp, 0x18
/* 2B86C 8003B06C 2800B027 */  addiu      $s0, $sp, 0x28
/* 2B870 8003B070 21200002 */  addu       $a0, $s0, $zero
/* 2B874 8003B074 21280002 */  addu       $a1, $s0, $zero
/* 2B878 8003B078 E35D000C */  jal        VecSub
/* 2B87C 8003B07C 1800A627 */   addiu     $a2, $sp, 0x18
/* 2B880 8003B080 21200002 */  addu       $a0, $s0, $zero
/* 2B884 8003B084 21280002 */  addu       $a1, $s0, $zero
/* 2B888 8003B088 FE5D000C */  jal        func_800177F8
/* 2B88C 8003B08C 21302002 */   addu      $a2, $s1, $zero
/* 2B890 8003B090 2120A002 */  addu       $a0, $s5, $zero
/* 2B894 8003B094 21280002 */  addu       $a1, $s0, $zero
/* 2B898 8003B098 C05D000C */  jal        VecCopy
/* 2B89C 8003B09C 3000B4AF */   sw        $s4, 0x30($sp)
/* 2B8A0 8003B0A0 21104002 */  addu       $v0, $s2, $zero
.L8003B0A4:
/* 2B8A4 8003B0A4 01000324 */  addiu      $v1, $zero, 0x1
/* 2B8A8 8003B0A8 0E00A3A2 */  sb         $v1, 0xE($s5)
.L8003B0AC:
/* 2B8AC 8003B0AC 5800BF8F */  lw         $ra, 0x58($sp)
/* 2B8B0 8003B0B0 5400B78F */  lw         $s7, 0x54($sp)
/* 2B8B4 8003B0B4 5000B68F */  lw         $s6, 0x50($sp)
/* 2B8B8 8003B0B8 4C00B58F */  lw         $s5, 0x4C($sp)
/* 2B8BC 8003B0BC 4800B48F */  lw         $s4, 0x48($sp)
/* 2B8C0 8003B0C0 4400B38F */  lw         $s3, 0x44($sp)
/* 2B8C4 8003B0C4 4000B28F */  lw         $s2, 0x40($sp)
/* 2B8C8 8003B0C8 3C00B18F */  lw         $s1, 0x3C($sp)
/* 2B8CC 8003B0CC 3800B08F */  lw         $s0, 0x38($sp)
/* 2B8D0 8003B0D0 6000BD27 */  addiu      $sp, $sp, 0x60
/* 2B8D4 8003B0D4 0800E003 */  jr         $ra
/* 2B8D8 8003B0D8 00000000 */   nop
.size func_8003ABC0, . - func_8003ABC0
