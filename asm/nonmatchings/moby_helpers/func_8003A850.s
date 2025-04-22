.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003A850
/* 2B050 8003A850 D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 2B054 8003A854 1C00B3AF */  sw         $s3, 0x1C($sp)
/* 2B058 8003A858 21988000 */  addu       $s3, $a0, $zero
/* 2B05C 8003A85C 1000B0AF */  sw         $s0, 0x10($sp)
/* 2B060 8003A860 2180A000 */  addu       $s0, $a1, $zero
/* 2B064 8003A864 1400B1AF */  sw         $s1, 0x14($sp)
/* 2B068 8003A868 2188C000 */  addu       $s1, $a2, $zero
/* 2B06C 8003A86C 2000BFAF */  sw         $ra, 0x20($sp)
/* 2B070 8003A870 1800B2AF */  sw         $s2, 0x18($sp)
/* 2B074 8003A874 03000292 */  lbu        $v0, 0x3($s0)
/* 2B078 8003A878 00000000 */  nop
/* 2B07C 8003A87C FE004230 */  andi       $v0, $v0, 0xFE
/* 2B080 8003A880 020002A2 */  sb         $v0, 0x2($s0)
/* 2B084 8003A884 0900422C */  sltiu      $v0, $v0, 0x9
/* 2B088 8003A888 03004014 */  bnez       $v0, .L8003A898
/* 2B08C 8003A88C 2190E000 */   addu      $s2, $a3, $zero
/* 2B090 8003A890 08000224 */  addiu      $v0, $zero, 0x8
/* 2B094 8003A894 020002A2 */  sb         $v0, 0x2($s0)
.L8003A898:
/* 2B098 8003A898 21204002 */  addu       $a0, $s2, $zero
/* 2B09C 8003A89C C05D000C */  jal        VecCopy
/* 2B0A0 8003A8A0 21282002 */   addu      $a1, $s1, $zero
/* 2B0A4 8003A8A4 21202002 */  addu       $a0, $s1, $zero
/* 2B0A8 8003A8A8 02000692 */  lbu        $a2, 0x2($s0)
/* 2B0AC 8003A8AC 21284002 */  addu       $a1, $s2, $zero
/* 2B0B0 8003A8B0 F05D000C */  jal        VecMult
/* 2B0B4 8003A8B4 42300600 */   srl       $a2, $a2, 1
/* 2B0B8 8003A8B8 21202002 */  addu       $a0, $s1, $zero
/* 2B0BC 8003A8BC 21282002 */  addu       $a1, $s1, $zero
/* 2B0C0 8003A8C0 D65D000C */  jal        VecAdd
/* 2B0C4 8003A8C4 0C006626 */   addiu     $a2, $s3, 0xC
/* 2B0C8 8003A8C8 21202002 */  addu       $a0, $s1, $zero
/* 2B0CC 8003A8CC 01000592 */  lbu        $a1, 0x1($s0)
/* 2B0D0 8003A8D0 21302002 */  addu       $a2, $s1, $zero
/* 2B0D4 8003A8D4 00290500 */  sll        $a1, $a1, 4
/* 2B0D8 8003A8D8 0800A524 */  addiu      $a1, $a1, 0x8
/* 2B0DC 8003A8DC E35D000C */  jal        VecSub
/* 2B0E0 8003A8E0 21280502 */   addu      $a1, $s0, $a1
/* 2B0E4 8003A8E4 21202002 */  addu       $a0, $s1, $zero
/* 2B0E8 8003A8E8 21288000 */  addu       $a1, $a0, $zero
/* 2B0EC 8003A8EC 02000692 */  lbu        $a2, 0x2($s0)
/* 2B0F0 8003A8F0 03000292 */  lbu        $v0, 0x3($s0)
/* 2B0F4 8003A8F4 42300600 */  srl        $a2, $a2, 1
/* 2B0F8 8003A8F8 FE5D000C */  jal        func_800177F8
/* 2B0FC 8003A8FC 23304600 */   subu      $a2, $v0, $a2
/* 2B100 8003A900 2000BF8F */  lw         $ra, 0x20($sp)
/* 2B104 8003A904 1C00B38F */  lw         $s3, 0x1C($sp)
/* 2B108 8003A908 1800B28F */  lw         $s2, 0x18($sp)
/* 2B10C 8003A90C 1400B18F */  lw         $s1, 0x14($sp)
/* 2B110 8003A910 1000B08F */  lw         $s0, 0x10($sp)
/* 2B114 8003A914 2800BD27 */  addiu      $sp, $sp, 0x28
/* 2B118 8003A918 0800E003 */  jr         $ra
/* 2B11C 8003A91C 00000000 */   nop
.size func_8003A850, . - func_8003A850
