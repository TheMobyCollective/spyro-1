.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038458
/* 28C58 80038458 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 28C5C 8003845C 1000B0AF */  sw         $s0, 0x10($sp)
/* 28C60 80038460 1400BFAF */  sw         $ra, 0x14($sp)
/* 28C64 80038464 D0E0000C */  jal        func_80038340
/* 28C68 80038468 21808000 */   addu      $s0, $a0, $zero
/* 28C6C 8003846C 38000386 */  lh         $v1, 0x38($s0)
/* 28C70 80038470 21200002 */  addu       $a0, $s0, $zero
/* 28C74 80038474 21104300 */  addu       $v0, $v0, $v1
/* 28C78 80038478 F44C010C */  jal        func_800533D0
/* 28C7C 8003847C 140082AC */   sw        $v0, 0x14($a0)
/* 28C80 80038480 1400BF8F */  lw         $ra, 0x14($sp)
/* 28C84 80038484 1000B08F */  lw         $s0, 0x10($sp)
/* 28C88 80038488 1800BD27 */  addiu      $sp, $sp, 0x18
/* 28C8C 8003848C 0800E003 */  jr         $ra
/* 28C90 80038490 00000000 */   nop
.size func_80038458, . - func_80038458
