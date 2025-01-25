.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003A420
/* 2AC20 8003A420 88FFBD27 */  addiu      $sp, $sp, -0x78
/* 2AC24 8003A424 5800B2AF */  sw         $s2, 0x58($sp)
/* 2AC28 8003A428 21908000 */  addu       $s2, $a0, $zero
/* 2AC2C 8003A42C 5C00B3AF */  sw         $s3, 0x5C($sp)
/* 2AC30 8003A430 2198A000 */  addu       $s3, $a1, $zero
/* 2AC34 8003A434 6C00B7AF */  sw         $s7, 0x6C($sp)
/* 2AC38 8003A438 21B8C000 */  addu       $s7, $a2, $zero
/* 2AC3C 8003A43C 6400B5AF */  sw         $s5, 0x64($sp)
/* 2AC40 8003A440 21A8E000 */  addu       $s5, $a3, $zero
/* 2AC44 8003A444 5000B0AF */  sw         $s0, 0x50($sp)
/* 2AC48 8003A448 2000B027 */  addiu      $s0, $sp, 0x20
/* 2AC4C 8003A44C 21200002 */  addu       $a0, $s0, $zero
/* 2AC50 8003A450 0C004626 */  addiu      $a2, $s2, 0xC
/* 2AC54 8003A454 7400BFAF */  sw         $ra, 0x74($sp)
/* 2AC58 8003A458 7000BEAF */  sw         $fp, 0x70($sp)
/* 2AC5C 8003A45C 6800B6AF */  sw         $s6, 0x68($sp)
/* 2AC60 8003A460 6000B4AF */  sw         $s4, 0x60($sp)
/* 2AC64 8003A464 5400B1AF */  sw         $s1, 0x54($sp)
/* 2AC68 8003A468 01006592 */  lbu        $a1, 0x1($s3)
/* 2AC6C 8003A46C 8800BE8F */  lw         $fp, 0x88($sp)
/* 2AC70 8003A470 8C00B18F */  lw         $s1, 0x8C($sp)
/* 2AC74 8003A474 9000B68F */  lw         $s6, 0x90($sp)
/* 2AC78 8003A478 9400B48F */  lw         $s4, 0x94($sp)
/* 2AC7C 8003A47C 00290500 */  sll        $a1, $a1, 4
/* 2AC80 8003A480 0800A524 */  addiu      $a1, $a1, 0x8
/* 2AC84 8003A484 E35D000C */  jal        VecSub
/* 2AC88 8003A488 21286502 */   addu      $a1, $s3, $a1
/* 2AC8C 8003A48C 21200002 */  addu       $a0, $s0, $zero
/* 2AC90 8003A490 21280000 */  addu       $a1, $zero, $zero
/* 2AC94 8003A494 7F5C000C */  jal        VecMagnitude
/* 2AC98 8003A498 1800A0A3 */   sb        $zero, 0x18($sp)
/* 2AC9C 8003A49C 21204000 */  addu       $a0, $v0, $zero
/* 2ACA0 8003A4A0 2800A58F */  lw         $a1, 0x28($sp)
/* 2ACA4 8003A4A4 AD5A000C */  jal        func_80016AB4
/* 2ACA8 8003A4A8 21300000 */   addu      $a2, $zero, $zero
/* 2ACAC 8003A4AC 21200002 */  addu       $a0, $s0, $zero
/* 2ACB0 8003A4B0 21280000 */  addu       $a1, $zero, $zero
/* 2ACB4 8003A4B4 7F5C000C */  jal        VecMagnitude
/* 2ACB8 8003A4B8 1900A2A3 */   sb        $v0, 0x19($sp)
/* 2ACBC 8003A4BC 2A105700 */  slt        $v0, $v0, $s7
/* 2ACC0 8003A4C0 04004010 */  beqz       $v0, .L8003A4D4
/* 2ACC4 8003A4C4 00000000 */   nop
/* 2ACC8 8003A4C8 46004292 */  lbu        $v0, 0x46($s2)
/* 2ACCC 8003A4CC 53E90008 */  j          .L8003A54C
/* 2ACD0 8003A4D0 1A00A2A3 */   sb        $v0, 0x1A($sp)
.L8003A4D4:
/* 2ACD4 8003A4D4 2000A48F */  lw         $a0, 0x20($sp)
/* 2ACD8 8003A4D8 2400A58F */  lw         $a1, 0x24($sp)
/* 2ACDC 8003A4DC AD5A000C */  jal        func_80016AB4
/* 2ACE0 8003A4E0 21300000 */   addu      $a2, $zero, $zero
/* 2ACE4 8003A4E4 46004592 */  lbu        $a1, 0x46($s2)
/* 2ACE8 8003A4E8 00000000 */  nop
/* 2ACEC 8003A4EC 23104500 */  subu       $v0, $v0, $a1
/* 2ACF0 8003A4F0 FF004330 */  andi       $v1, $v0, 0xFF
/* 2ACF4 8003A4F4 81006228 */  slti       $v0, $v1, 0x81
/* 2ACF8 8003A4F8 02004014 */  bnez       $v0, .L8003A504
/* 2ACFC 8003A4FC 00000000 */   nop
/* 2AD00 8003A500 00FF6324 */  addiu      $v1, $v1, -0x100
.L8003A504:
/* 2AD04 8003A504 02006104 */  bgez       $v1, .L8003A510
/* 2AD08 8003A508 21106000 */   addu      $v0, $v1, $zero
/* 2AD0C 8003A50C 23100200 */  negu       $v0, $v0
.L8003A510:
/* 2AD10 8003A510 2A10C202 */  slt        $v0, $s6, $v0
/* 2AD14 8003A514 02004010 */  beqz       $v0, .L8003A520
/* 2AD18 8003A518 23201100 */   negu      $a0, $s1
/* 2AD1C 8003A51C 21A80000 */  addu       $s5, $zero, $zero
.L8003A520:
/* 2AD20 8003A520 2A106400 */  slt        $v0, $v1, $a0
/* 2AD24 8003A524 03004010 */  beqz       $v0, .L8003A534
/* 2AD28 8003A528 2A102302 */   slt       $v0, $s1, $v1
/* 2AD2C 8003A52C 21188000 */  addu       $v1, $a0, $zero
/* 2AD30 8003A530 2A102302 */  slt        $v0, $s1, $v1
.L8003A534:
/* 2AD34 8003A534 03004010 */  beqz       $v0, .L8003A544
/* 2AD38 8003A538 2110A300 */   addu      $v0, $a1, $v1
/* 2AD3C 8003A53C 21182002 */  addu       $v1, $s1, $zero
/* 2AD40 8003A540 2110A300 */  addu       $v0, $a1, $v1
.L8003A544:
/* 2AD44 8003A544 1A00A2A3 */  sb         $v0, 0x1A($sp)
/* 2AD48 8003A548 460042A2 */  sb         $v0, 0x46($s2)
.L8003A54C:
/* 2AD4C 8003A54C 2000B127 */  addiu      $s1, $sp, 0x20
/* 2AD50 8003A550 21202002 */  addu       $a0, $s1, $zero
/* 2AD54 8003A554 7F5C000C */  jal        VecMagnitude
/* 2AD58 8003A558 01000524 */   addiu     $a1, $zero, 0x1
/* 2AD5C 8003A55C 21184000 */  addu       $v1, $v0, $zero
/* 2AD60 8003A560 2A107500 */  slt        $v0, $v1, $s5
/* 2AD64 8003A564 02004010 */  beqz       $v0, .L8003A570
/* 2AD68 8003A568 1800A427 */   addiu     $a0, $sp, 0x18
/* 2AD6C 8003A56C 21A86000 */  addu       $s5, $v1, $zero
.L8003A570:
/* 2AD70 8003A570 3000B027 */  addiu      $s0, $sp, 0x30
/* 2AD74 8003A574 21280002 */  addu       $a1, $s0, $zero
/* 2AD78 8003A578 4B5B000C */  jal        func_80016D2C
/* 2AD7C 8003A57C 21300000 */   addu      $a2, $zero, $zero
/* 2AD80 8003A580 21200002 */  addu       $a0, $s0, $zero
/* 2AD84 8003A584 21282002 */  addu       $a1, $s1, $zero
/* 2AD88 8003A588 21302002 */  addu       $a2, $s1, $zero
/* 2AD8C 8003A58C 2000B5AF */  sw         $s5, 0x20($sp)
/* 2AD90 8003A590 2400A0AF */  sw         $zero, 0x24($sp)
/* 2AD94 8003A594 125C000C */  jal        func_80017048
/* 2AD98 8003A598 2800A0AF */   sw        $zero, 0x28($sp)
/* 2AD9C 8003A59C 12008012 */  beqz       $s4, .L8003A5E8
/* 2ADA0 8003A5A0 21208002 */   addu      $a0, $s4, $zero
/* 2ADA4 8003A5A4 21288002 */  addu       $a1, $s4, $zero
/* 2ADA8 8003A5A8 D65D000C */  jal        VecAdd
/* 2ADAC 8003A5AC 21302002 */   addu      $a2, $s1, $zero
/* 2ADB0 8003A5B0 21202002 */  addu       $a0, $s1, $zero
/* 2ADB4 8003A5B4 C05D000C */  jal        VecCopy
/* 2ADB8 8003A5B8 21288002 */   addu      $a1, $s4, $zero
/* 2ADBC 8003A5BC 21202002 */  addu       $a0, $s1, $zero
/* 2ADC0 8003A5C0 B25D000C */  jal        func_800176C8
/* 2ADC4 8003A5C4 02000524 */   addiu     $a1, $zero, 0x2
/* 2ADC8 8003A5C8 21208002 */  addu       $a0, $s4, $zero
/* 2ADCC 8003A5CC 21288002 */  addu       $a1, $s4, $zero
/* 2ADD0 8003A5D0 E35D000C */  jal        VecSub
/* 2ADD4 8003A5D4 21302002 */   addu      $a2, $s1, $zero
/* 2ADD8 8003A5D8 21202002 */  addu       $a0, $s1, $zero
/* 2ADDC 8003A5DC 0C004526 */  addiu      $a1, $s2, 0xC
/* 2ADE0 8003A5E0 7DE90008 */  j          .L8003A5F4
/* 2ADE4 8003A5E4 21308002 */   addu      $a2, $s4, $zero
.L8003A5E8:
/* 2ADE8 8003A5E8 21202002 */  addu       $a0, $s1, $zero
/* 2ADEC 8003A5EC 0C004526 */  addiu      $a1, $s2, 0xC
/* 2ADF0 8003A5F0 21308000 */  addu       $a2, $a0, $zero
.L8003A5F4:
/* 2ADF4 8003A5F4 D65D000C */  jal        VecAdd
/* 2ADF8 8003A5F8 00000000 */   nop
/* 2ADFC 8003A5FC 0700C013 */  beqz       $fp, .L8003A61C
/* 2AE00 8003A600 2000A427 */   addiu     $a0, $sp, 0x20
/* 2AE04 8003A604 2128C003 */  addu       $a1, $fp, $zero
/* 2AE08 8003A608 21300000 */  addu       $a2, $zero, $zero
/* 2AE0C 8003A60C 21380000 */  addu       $a3, $zero, $zero
/* 2AE10 8003A610 1000B2AF */  sw         $s2, 0x10($sp)
/* 2AE14 8003A614 F238010C */  jal        func_8004E3C8
/* 2AE18 8003A618 1400A0AF */   sw        $zero, 0x14($sp)
.L8003A61C:
/* 2AE1C 8003A61C 2000A427 */  addiu      $a0, $sp, 0x20
/* 2AE20 8003A620 2800A28F */  lw         $v0, 0x28($sp)
/* 2AE24 8003A624 00040524 */  addiu      $a1, $zero, 0x400
/* 2AE28 8003A628 00044224 */  addiu      $v0, $v0, 0x400
/* 2AE2C 8003A62C 7B35010C */  jal        func_8004D5EC
/* 2AE30 8003A630 2800A2AF */   sw        $v0, 0x28($sp)
/* 2AE34 8003A634 21184000 */  addu       $v1, $v0, $zero
/* 2AE38 8003A638 03006010 */  beqz       $v1, .L8003A648
/* 2AE3C 8003A63C 00000000 */   nop
/* 2AE40 8003A640 96E90008 */  j          .L8003A658
/* 2AE44 8003A644 2800A3AF */   sw        $v1, 0x28($sp)
.L8003A648:
/* 2AE48 8003A648 2800A28F */  lw         $v0, 0x28($sp)
/* 2AE4C 8003A64C 00000000 */  nop
/* 2AE50 8003A650 00FC4224 */  addiu      $v0, $v0, -0x400
/* 2AE54 8003A654 2800A2AF */  sw         $v0, 0x28($sp)
.L8003A658:
/* 2AE58 8003A658 0C005126 */  addiu      $s1, $s2, 0xC
/* 2AE5C 8003A65C 21202002 */  addu       $a0, $s1, $zero
/* 2AE60 8003A660 2000B027 */  addiu      $s0, $sp, 0x20
/* 2AE64 8003A664 C05D000C */  jal        VecCopy
/* 2AE68 8003A668 21280002 */   addu      $a1, $s0, $zero
/* 2AE6C 8003A66C F44C010C */  jal        func_800533D0
/* 2AE70 8003A670 21204002 */   addu      $a0, $s2, $zero
/* 2AE74 8003A674 21204002 */  addu       $a0, $s2, $zero
/* 2AE78 8003A678 794A010C */  jal        func_800529E4
/* 2AE7C 8003A67C 02000524 */   addiu     $a1, $zero, 0x2
/* 2AE80 8003A680 21A00000 */  addu       $s4, $zero, $zero
/* 2AE84 8003A684 21200002 */  addu       $a0, $s0, $zero
/* 2AE88 8003A688 01006592 */  lbu        $a1, 0x1($s3)
/* 2AE8C 8003A68C 21302002 */  addu       $a2, $s1, $zero
/* 2AE90 8003A690 00290500 */  sll        $a1, $a1, 4
/* 2AE94 8003A694 0800A524 */  addiu      $a1, $a1, 0x8
/* 2AE98 8003A698 E35D000C */  jal        VecSub
/* 2AE9C 8003A69C 21286502 */   addu      $a1, $s3, $a1
/* 2AEA0 8003A6A0 21200002 */  addu       $a0, $s0, $zero
/* 2AEA4 8003A6A4 7F5C000C */  jal        VecMagnitude
/* 2AEA8 8003A6A8 01000524 */   addiu     $a1, $zero, 0x1
/* 2AEAC 8003A6AC 2A105700 */  slt        $v0, $v0, $s7
/* 2AEB0 8003A6B0 0E004010 */  beqz       $v0, .L8003A6EC
/* 2AEB4 8003A6B4 21108002 */   addu      $v0, $s4, $zero
/* 2AEB8 8003A6B8 490040A2 */  sb         $zero, 0x49($s2)
/* 2AEBC 8003A6BC 01006292 */  lbu        $v0, 0x1($s3)
/* 2AEC0 8003A6C0 00006392 */  lbu        $v1, 0x0($s3)
/* 2AEC4 8003A6C4 01004224 */  addiu      $v0, $v0, 0x1
/* 2AEC8 8003A6C8 010062A2 */  sb         $v0, 0x1($s3)
/* 2AECC 8003A6CC FF004230 */  andi       $v0, $v0, 0xFF
/* 2AED0 8003A6D0 02004314 */  bne        $v0, $v1, .L8003A6DC
/* 2AED4 8003A6D4 00000000 */   nop
/* 2AED8 8003A6D8 010060A2 */  sb         $zero, 0x1($s3)
.L8003A6DC:
/* 2AEDC 8003A6DC 01006292 */  lbu        $v0, 0x1($s3)
/* 2AEE0 8003A6E0 00000000 */  nop
/* 2AEE4 8003A6E4 00015424 */  addiu      $s4, $v0, 0x100
/* 2AEE8 8003A6E8 21108002 */  addu       $v0, $s4, $zero
.L8003A6EC:
/* 2AEEC 8003A6EC 7400BF8F */  lw         $ra, 0x74($sp)
/* 2AEF0 8003A6F0 7000BE8F */  lw         $fp, 0x70($sp)
/* 2AEF4 8003A6F4 6C00B78F */  lw         $s7, 0x6C($sp)
/* 2AEF8 8003A6F8 6800B68F */  lw         $s6, 0x68($sp)
/* 2AEFC 8003A6FC 6400B58F */  lw         $s5, 0x64($sp)
/* 2AF00 8003A700 6000B48F */  lw         $s4, 0x60($sp)
/* 2AF04 8003A704 5C00B38F */  lw         $s3, 0x5C($sp)
/* 2AF08 8003A708 5800B28F */  lw         $s2, 0x58($sp)
/* 2AF0C 8003A70C 5400B18F */  lw         $s1, 0x54($sp)
/* 2AF10 8003A710 5000B08F */  lw         $s0, 0x50($sp)
/* 2AF14 8003A714 7800BD27 */  addiu      $sp, $sp, 0x78
/* 2AF18 8003A718 0800E003 */  jr         $ra
/* 2AF1C 8003A71C 00000000 */   nop
.size func_8003A420, . - func_8003A420
