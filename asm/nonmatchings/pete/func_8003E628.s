.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003E628
/* 2EE28 8003E628 A0FFBD27 */  addiu      $sp, $sp, -0x60
/* 2EE2C 8003E62C 4C00B1AF */  sw         $s1, 0x4C($sp)
/* 2EE30 8003E630 0880113C */  lui        $s1, %hi(g_Spyro + 0x274)
/* 2EE34 8003E634 CC8C3126 */  addiu      $s1, $s1, %lo(g_Spyro + 0x274)
/* 2EE38 8003E638 5800BFAF */  sw         $ra, 0x58($sp)
/* 2EE3C 8003E63C 5400B3AF */  sw         $s3, 0x54($sp)
/* 2EE40 8003E640 5000B2AF */  sw         $s2, 0x50($sp)
/* 2EE44 8003E644 4800B0AF */  sw         $s0, 0x48($sp)
/* 2EE48 8003E648 0000228E */  lw         $v0, 0x0($s1)
/* 2EE4C 8003E64C 00000000 */  nop
/* 2EE50 8003E650 39004004 */  bltz       $v0, .L8003E738
/* 2EE54 8003E654 3800B027 */   addiu     $s0, $sp, 0x38
/* 2EE58 8003E658 BC5D000C */  jal        VecNull
/* 2EE5C 8003E65C 21200002 */   addu      $a0, $s0, $zero
/* 2EE60 8003E660 0000248E */  lw         $a0, 0x0($s1)
/* 2EE64 8003E664 1000A527 */  addiu      $a1, $sp, 0x10
/* 2EE68 8003E668 21900000 */  addu       $s2, $zero, $zero
/* 2EE6C 8003E66C 21980002 */  addu       $s3, $s0, $zero
/* 2EE70 8003E670 04003126 */  addiu      $s1, $s1, 0x4
/* 2EE74 8003E674 2E5F000C */  jal        func_80017CB8
/* 2EE78 8003E678 1000B027 */   addiu     $s0, $sp, 0x10
.L8003E67C:
/* 2EE7C 8003E67C 21200002 */  addu       $a0, $s0, $zero
/* 2EE80 8003E680 21280002 */  addu       $a1, $s0, $zero
/* 2EE84 8003E684 E35D000C */  jal        VecSub
/* 2EE88 8003E688 21302002 */   addu      $a2, $s1, $zero
/* 2EE8C 8003E68C 21206002 */  addu       $a0, $s3, $zero
/* 2EE90 8003E690 21286002 */  addu       $a1, $s3, $zero
/* 2EE94 8003E694 D65D000C */  jal        VecAdd
/* 2EE98 8003E698 21300002 */   addu      $a2, $s0, $zero
/* 2EE9C 8003E69C 0C003126 */  addiu      $s1, $s1, 0xC
/* 2EEA0 8003E6A0 01005226 */  addiu      $s2, $s2, 0x1
/* 2EEA4 8003E6A4 0300422A */  slti       $v0, $s2, 0x3
/* 2EEA8 8003E6A8 F4FF4014 */  bnez       $v0, .L8003E67C
/* 2EEAC 8003E6AC 0C001026 */   addiu     $s0, $s0, 0xC
/* 2EEB0 8003E6B0 5555043C */  lui        $a0, (0x55555556 >> 16)
/* 2EEB4 8003E6B4 3800A28F */  lw         $v0, 0x38($sp)
/* 2EEB8 8003E6B8 56558434 */  ori        $a0, $a0, (0x55555556 & 0xFFFF)
/* 2EEBC 8003E6BC 18004400 */  mult       $v0, $a0
/* 2EEC0 8003E6C0 10500000 */  mfhi       $t2
/* 2EEC4 8003E6C4 3C00A38F */  lw         $v1, 0x3C($sp)
/* 2EEC8 8003E6C8 00000000 */  nop
/* 2EECC 8003E6CC 18006400 */  mult       $v1, $a0
/* 2EED0 8003E6D0 10380000 */  mfhi       $a3
/* 2EED4 8003E6D4 4000A68F */  lw         $a2, 0x40($sp)
/* 2EED8 8003E6D8 00000000 */  nop
/* 2EEDC 8003E6DC 1800C400 */  mult       $a2, $a0
/* 2EEE0 8003E6E0 21286002 */  addu       $a1, $s3, $zero
/* 2EEE4 8003E6E4 C3170200 */  sra        $v0, $v0, 31
/* 2EEE8 8003E6E8 23104201 */  subu       $v0, $t2, $v0
/* 2EEEC 8003E6EC C31F0300 */  sra        $v1, $v1, 31
/* 2EEF0 8003E6F0 3800A2AF */  sw         $v0, 0x38($sp)
/* 2EEF4 8003E6F4 0880043C */  lui        $a0, %hi(g_Spyro + 0x12C)
/* 2EEF8 8003E6F8 848B8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0x12C)
/* 2EEFC 8003E6FC 2318E300 */  subu       $v1, $a3, $v1
/* 2EF00 8003E700 C3370600 */  sra        $a2, $a2, 31
/* 2EF04 8003E704 3C00A3AF */  sw         $v1, 0x3C($sp)
/* 2EF08 8003E708 10400000 */  mfhi       $t0
/* 2EF0C 8003E70C 23300601 */  subu       $a2, $t0, $a2
/* 2EF10 8003E710 C05D000C */  jal        VecCopy
/* 2EF14 8003E714 4000A6AF */   sw        $a2, 0x40($sp)
/* 2EF18 8003E718 21206002 */  addu       $a0, $s3, $zero
/* 2EF1C 8003E71C 7F5C000C */  jal        func_800171FC
/* 2EF20 8003E720 01000524 */   addiu     $a1, $zero, 0x1
/* 2EF24 8003E724 21004228 */  slti       $v0, $v0, 0x21
/* 2EF28 8003E728 03004014 */  bnez       $v0, .L8003E738
/* 2EF2C 8003E72C 01000224 */   addiu     $v0, $zero, 0x1
/* 2EF30 8003E730 0780013C */  lui        $at, %hi(g_Camera + 0xF0)
/* 2EF34 8003E734 C06E22AC */  sw         $v0, %lo(g_Camera + 0xF0)($at)
.L8003E738:
/* 2EF38 8003E738 5800BF8F */  lw         $ra, 0x58($sp)
/* 2EF3C 8003E73C 5400B38F */  lw         $s3, 0x54($sp)
/* 2EF40 8003E740 5000B28F */  lw         $s2, 0x50($sp)
/* 2EF44 8003E744 4C00B18F */  lw         $s1, 0x4C($sp)
/* 2EF48 8003E748 4800B08F */  lw         $s0, 0x48($sp)
/* 2EF4C 8003E74C 6000BD27 */  addiu      $sp, $sp, 0x60
/* 2EF50 8003E750 0800E003 */  jr         $ra
/* 2EF54 8003E754 00000000 */   nop
.size func_8003E628, . - func_8003E628
