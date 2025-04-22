.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003A920
/* 2B120 8003A920 C0FFBD27 */  addiu      $sp, $sp, -0x40
/* 2B124 8003A924 3800B2AF */  sw         $s2, 0x38($sp)
/* 2B128 8003A928 3C00BFAF */  sw         $ra, 0x3C($sp)
/* 2B12C 8003A92C 3400B1AF */  sw         $s1, 0x34($sp)
/* 2B130 8003A930 3000B0AF */  sw         $s0, 0x30($sp)
/* 2B134 8003A934 0200A390 */  lbu        $v1, 0x2($a1)
/* 2B138 8003A938 02000224 */  addiu      $v0, $zero, 0x2
/* 2B13C 8003A93C 05006214 */  bne        $v1, $v0, .L8003A954
/* 2B140 8003A940 21908000 */   addu      $s2, $a0, $zero
/* 2B144 8003A944 0780053C */  lui        $a1, %hi(D_80075280)
/* 2B148 8003A948 8052A524 */  addiu      $a1, $a1, %lo(D_80075280)
/* 2B14C 8003A94C 63EA0008 */  j          .L8003A98C
/* 2B150 8003A950 1000A427 */   addiu     $a0, $sp, 0x10
.L8003A954:
/* 2B154 8003A954 04000224 */  addiu      $v0, $zero, 0x4
/* 2B158 8003A958 05006214 */  bne        $v1, $v0, .L8003A970
/* 2B15C 8003A95C 06000224 */   addiu     $v0, $zero, 0x6
/* 2B160 8003A960 0780053C */  lui        $a1, %hi(D_8006CBA4)
/* 2B164 8003A964 A4CBA524 */  addiu      $a1, $a1, %lo(D_8006CBA4)
/* 2B168 8003A968 63EA0008 */  j          .L8003A98C
/* 2B16C 8003A96C 1000A427 */   addiu     $a0, $sp, 0x10
.L8003A970:
/* 2B170 8003A970 0780053C */  lui        $a1, %hi(D_8006CBCC)
/* 2B174 8003A974 CCCBA524 */  addiu      $a1, $a1, %lo(D_8006CBCC)
/* 2B178 8003A978 03006214 */  bne        $v1, $v0, .L8003A988
/* 2B17C 8003A97C 00000000 */   nop
/* 2B180 8003A980 0780053C */  lui        $a1, %hi(D_8006CBB4)
/* 2B184 8003A984 B4CBA524 */  addiu      $a1, $a1, %lo(D_8006CBB4)
.L8003A988:
/* 2B188 8003A988 1000A427 */  addiu      $a0, $sp, 0x10
.L8003A98C:
/* 2B18C 8003A98C 80800600 */  sll        $s0, $a2, 2
/* 2B190 8003A990 21800502 */  addu       $s0, $s0, $a1
/* 2B194 8003A994 00000686 */  lh         $a2, 0x0($s0)
/* 2B198 8003A998 F05D000C */  jal        VecMult
/* 2B19C 8003A99C 2128E000 */   addu      $a1, $a3, $zero
/* 2B1A0 8003A9A0 2000B127 */  addiu      $s1, $sp, 0x20
/* 2B1A4 8003A9A4 02000686 */  lh         $a2, 0x2($s0)
/* 2B1A8 8003A9A8 5000A58F */  lw         $a1, 0x50($sp)
/* 2B1AC 8003A9AC F05D000C */  jal        VecMult
/* 2B1B0 8003A9B0 21202002 */   addu      $a0, $s1, $zero
/* 2B1B4 8003A9B4 21204002 */  addu       $a0, $s2, $zero
/* 2B1B8 8003A9B8 1000A527 */  addiu      $a1, $sp, 0x10
/* 2B1BC 8003A9BC D65D000C */  jal        VecAdd
/* 2B1C0 8003A9C0 21302002 */   addu      $a2, $s1, $zero
/* 2B1C4 8003A9C4 21204002 */  addu       $a0, $s2, $zero
/* 2B1C8 8003A9C8 B25D000C */  jal        VecShiftRight
/* 2B1CC 8003A9CC 0A000524 */   addiu     $a1, $zero, 0xA
/* 2B1D0 8003A9D0 3C00BF8F */  lw         $ra, 0x3C($sp)
/* 2B1D4 8003A9D4 3800B28F */  lw         $s2, 0x38($sp)
/* 2B1D8 8003A9D8 3400B18F */  lw         $s1, 0x34($sp)
/* 2B1DC 8003A9DC 3000B08F */  lw         $s0, 0x30($sp)
/* 2B1E0 8003A9E0 4000BD27 */  addiu      $sp, $sp, 0x40
/* 2B1E4 8003A9E4 0800E003 */  jr         $ra
/* 2B1E8 8003A9E8 00000000 */   nop
.size func_8003A920, . - func_8003A920
