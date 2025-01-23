.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80033E40
/* 24640 80033E40 A0FFBD27 */  addiu      $sp, $sp, -0x60
/* 24644 80033E44 4800B0AF */  sw         $s0, 0x48($sp)
/* 24648 80033E48 21808000 */  addu       $s0, $a0, $zero
/* 2464C 80033E4C 1000A427 */  addiu      $a0, $sp, 0x10
/* 24650 80033E50 21300002 */  addu       $a2, $s0, $zero
/* 24654 80033E54 5800BFAF */  sw         $ra, 0x58($sp)
/* 24658 80033E58 5400B3AF */  sw         $s3, 0x54($sp)
/* 2465C 80033E5C 5000B2AF */  sw         $s2, 0x50($sp)
/* 24660 80033E60 E35D000C */  jal        VecSub
/* 24664 80033E64 4C00B1AF */   sw        $s1, 0x4C($sp)
/* 24668 80033E68 1000A427 */  addiu      $a0, $sp, 0x10
/* 2466C 80033E6C 7F5C000C */  jal        func_800171FC
/* 24670 80033E70 01000524 */   addiu     $a1, $zero, 0x1
/* 24674 80033E74 1000A427 */  addiu      $a0, $sp, 0x10
/* 24678 80033E78 21284000 */  addu       $a1, $v0, $zero
/* 2467C 80033E7C 00040624 */  addiu      $a2, $zero, 0x400
/* 24680 80033E80 6E5D000C */  jal        func_800175B8
/* 24684 80033E84 839A0500 */   sra       $s3, $a1, 10
/* 24688 80033E88 2000B127 */  addiu      $s1, $sp, 0x20
/* 2468C 80033E8C 21202002 */  addu       $a0, $s1, $zero
/* 24690 80033E90 C05D000C */  jal        VecCopy
/* 24694 80033E94 21280002 */   addu      $a1, $s0, $zero
/* 24698 80033E98 1200601A */  blez       $s3, .L80033EE4
/* 2469C 80033E9C 21800000 */   addu      $s0, $zero, $zero
/* 246A0 80033EA0 3000B227 */  addiu      $s2, $sp, 0x30
/* 246A4 80033EA4 21204002 */  addu       $a0, $s2, $zero
.L80033EA8:
/* 246A8 80033EA8 21282002 */  addu       $a1, $s1, $zero
/* 246AC 80033EAC D65D000C */  jal        VecAdd
/* 246B0 80033EB0 1000A627 */   addiu     $a2, $sp, 0x10
/* 246B4 80033EB4 21202002 */  addu       $a0, $s1, $zero
/* 246B8 80033EB8 8E2B010C */  jal        func_8004AE38
/* 246BC 80033EBC 21284002 */   addu      $a1, $s2, $zero
/* 246C0 80033EC0 09004014 */  bnez       $v0, .L80033EE8
/* 246C4 80033EC4 21100000 */   addu      $v0, $zero, $zero
/* 246C8 80033EC8 21202002 */  addu       $a0, $s1, $zero
/* 246CC 80033ECC C05D000C */  jal        VecCopy
/* 246D0 80033ED0 21284002 */   addu      $a1, $s2, $zero
/* 246D4 80033ED4 01001026 */  addiu      $s0, $s0, 0x1
/* 246D8 80033ED8 2A101302 */  slt        $v0, $s0, $s3
/* 246DC 80033EDC F2FF4014 */  bnez       $v0, .L80033EA8
/* 246E0 80033EE0 21204002 */   addu      $a0, $s2, $zero
.L80033EE4:
/* 246E4 80033EE4 01000224 */  addiu      $v0, $zero, 0x1
.L80033EE8:
/* 246E8 80033EE8 5800BF8F */  lw         $ra, 0x58($sp)
/* 246EC 80033EEC 5400B38F */  lw         $s3, 0x54($sp)
/* 246F0 80033EF0 5000B28F */  lw         $s2, 0x50($sp)
/* 246F4 80033EF4 4C00B18F */  lw         $s1, 0x4C($sp)
/* 246F8 80033EF8 4800B08F */  lw         $s0, 0x48($sp)
/* 246FC 80033EFC 6000BD27 */  addiu      $sp, $sp, 0x60
/* 24700 80033F00 0800E003 */  jr         $ra
/* 24704 80033F04 00000000 */   nop
.size func_80033E40, . - func_80033E40
