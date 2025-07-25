.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038DC0
/* 295C0 80038DC0 D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 295C4 80038DC4 1400B1AF */  sw         $s1, 0x14($sp)
/* 295C8 80038DC8 21888000 */  addu       $s1, $a0, $zero
/* 295CC 80038DCC 1000B0AF */  sw         $s0, 0x10($sp)
/* 295D0 80038DD0 2180A000 */  addu       $s0, $a1, $zero
/* 295D4 80038DD4 1C00B3AF */  sw         $s3, 0x1C($sp)
/* 295D8 80038DD8 2198C000 */  addu       $s3, $a2, $zero
/* 295DC 80038DDC 2000B4AF */  sw         $s4, 0x20($sp)
/* 295E0 80038DE0 21A0E000 */  addu       $s4, $a3, $zero
/* 295E4 80038DE4 0880033C */  lui        $v1, %hi(g_Spyro)
/* 295E8 80038DE8 588A638C */  lw         $v1, %lo(g_Spyro)($v1)
/* 295EC 80038DEC 21300000 */  addu       $a2, $zero, $zero
/* 295F0 80038DF0 2400BFAF */  sw         $ra, 0x24($sp)
/* 295F4 80038DF4 1800B2AF */  sw         $s2, 0x18($sp)
/* 295F8 80038DF8 0C00248E */  lw         $a0, 0xC($s1)
/* 295FC 80038DFC 0880023C */  lui        $v0, %hi(g_Spyro + 0x4)
/* 29600 80038E00 5C8A428C */  lw         $v0, %lo(g_Spyro + 0x4)($v0)
/* 29604 80038E04 1000258E */  lw         $a1, 0x10($s1)
/* 29608 80038E08 23206400 */  subu       $a0, $v1, $a0
/* 2960C 80038E0C AD5A000C */  jal        Atan2
/* 29610 80038E10 23284500 */   subu      $a1, $v0, $a1
/* 29614 80038E14 21904000 */  addu       $s2, $v0, $zero
/* 29618 80038E18 46002592 */  lbu        $a1, 0x46($s1)
/* 2961C 80038E1C 425E000C */  jal        func_80017908
/* 29620 80038E20 21204002 */   addu      $a0, $s2, $zero
/* 29624 80038E24 21204000 */  addu       $a0, $v0, $zero
/* 29628 80038E28 0780033C */  lui        $v1, %hi(D_800756C4)
/* 2962C 80038E2C C456638C */  lw         $v1, %lo(D_800756C4)($v1)
/* 29630 80038E30 03000224 */  addiu      $v0, $zero, 0x3
/* 29634 80038E34 04006214 */  bne        $v1, $v0, .L80038E48
/* 29638 80038E38 04000224 */   addiu     $v0, $zero, 0x4
/* 2963C 80038E3C 43101000 */  sra        $v0, $s0, 1
/* 29640 80038E40 95E30008 */  j          .L80038E54
/* 29644 80038E44 21800202 */   addu      $s0, $s0, $v0
.L80038E48:
/* 29648 80038E48 03006214 */  bne        $v1, $v0, .L80038E58
/* 2964C 80038E4C 2A109000 */   slt       $v0, $a0, $s0
/* 29650 80038E50 40801000 */  sll        $s0, $s0, 1
.L80038E54:
/* 29654 80038E54 2A109000 */  slt        $v0, $a0, $s0
.L80038E58:
/* 29658 80038E58 02004010 */  beqz       $v0, .L80038E64
/* 2965C 80038E5C 00000000 */   nop
/* 29660 80038E60 21808000 */  addu       $s0, $a0, $zero
.L80038E64:
/* 29664 80038E64 46002592 */  lbu        $a1, 0x46($s1)
/* 29668 80038E68 425E000C */  jal        func_80017908
/* 2966C 80038E6C 21204002 */   addu      $a0, $s2, $zero
/* 29670 80038E70 2A106202 */  slt        $v0, $s3, $v0
/* 29674 80038E74 09004010 */  beqz       $v0, .L80038E9C
/* 29678 80038E78 21204002 */   addu      $a0, $s2, $zero
/* 2967C 80038E7C 21300002 */  addu       $a2, $s0, $zero
/* 29680 80038E80 43380600 */  sra        $a3, $a2, 1
/* 29684 80038E84 46002592 */  lbu        $a1, 0x46($s1)
/* 29688 80038E88 7C5E000C */  jal        func_800179F0
/* 2968C 80038E8C 0100E724 */   addiu     $a3, $a3, 0x1
/* 29690 80038E90 460022A2 */  sb         $v0, 0x46($s1)
/* 29694 80038E94 AFE30008 */  j          .L80038EBC
/* 29698 80038E98 21100000 */   addu      $v0, $zero, $zero
.L80038E9C:
/* 2969C 80038E9C 06008012 */  beqz       $s4, .L80038EB8
/* 296A0 80038EA0 21300002 */   addu      $a2, $s0, $zero
/* 296A4 80038EA4 43380600 */  sra        $a3, $a2, 1
/* 296A8 80038EA8 46002592 */  lbu        $a1, 0x46($s1)
/* 296AC 80038EAC 7C5E000C */  jal        func_800179F0
/* 296B0 80038EB0 0100E724 */   addiu     $a3, $a3, 0x1
/* 296B4 80038EB4 460022A2 */  sb         $v0, 0x46($s1)
.L80038EB8:
/* 296B8 80038EB8 01000224 */  addiu      $v0, $zero, 0x1
.L80038EBC:
/* 296BC 80038EBC 2400BF8F */  lw         $ra, 0x24($sp)
/* 296C0 80038EC0 2000B48F */  lw         $s4, 0x20($sp)
/* 296C4 80038EC4 1C00B38F */  lw         $s3, 0x1C($sp)
/* 296C8 80038EC8 1800B28F */  lw         $s2, 0x18($sp)
/* 296CC 80038ECC 1400B18F */  lw         $s1, 0x14($sp)
/* 296D0 80038ED0 1000B08F */  lw         $s0, 0x10($sp)
/* 296D4 80038ED4 2800BD27 */  addiu      $sp, $sp, 0x28
/* 296D8 80038ED8 0800E003 */  jr         $ra
/* 296DC 80038EDC 00000000 */   nop
.size func_80038DC0, . - func_80038DC0
