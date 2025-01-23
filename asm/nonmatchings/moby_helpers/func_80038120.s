.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038120
/* 28920 80038120 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 28924 80038124 21108000 */  addu       $v0, $a0, $zero
/* 28928 80038128 1400B1AF */  sw         $s1, 0x14($sp)
/* 2892C 8003812C 2188A000 */  addu       $s1, $a1, $zero
/* 28930 80038130 21202002 */  addu       $a0, $s1, $zero
/* 28934 80038134 21284000 */  addu       $a1, $v0, $zero
/* 28938 80038138 1000B0AF */  sw         $s0, 0x10($sp)
/* 2893C 8003813C 1800BFAF */  sw         $ra, 0x18($sp)
/* 28940 80038140 6FE0000C */  jal        func_800381BC
/* 28944 80038144 2180C000 */   addu      $s0, $a2, $zero
/* 28948 80038148 FF001032 */  andi       $s0, $s0, 0xFF
/* 2894C 8003814C 18005000 */  mult       $v0, $s0
/* 28950 80038150 21202002 */  addu       $a0, $s1, $zero
/* 28954 80038154 12180000 */  mflo       $v1
/* 28958 80038158 1DE0000C */  jal        func_80038074
/* 2895C 8003815C 032A0300 */   sra       $a1, $v1, 8
/* 28960 80038160 1800BF8F */  lw         $ra, 0x18($sp)
/* 28964 80038164 1400B18F */  lw         $s1, 0x14($sp)
/* 28968 80038168 1000B08F */  lw         $s0, 0x10($sp)
/* 2896C 8003816C 2000BD27 */  addiu      $sp, $sp, 0x20
/* 28970 80038170 0800E003 */  jr         $ra
/* 28974 80038174 00000000 */   nop
.size func_80038120, . - func_80038120
