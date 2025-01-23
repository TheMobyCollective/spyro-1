.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038400
/* 28C00 80038400 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 28C04 80038404 1000B0AF */  sw         $s0, 0x10($sp)
/* 28C08 80038408 21808000 */  addu       $s0, $a0, $zero
/* 28C0C 8003840C 1400B1AF */  sw         $s1, 0x14($sp)
/* 28C10 80038410 2188A000 */  addu       $s1, $a1, $zero
/* 28C14 80038414 0C000426 */  addiu      $a0, $s0, 0xC
/* 28C18 80038418 1800BFAF */  sw         $ra, 0x18($sp)
/* 28C1C 8003841C 1400028E */  lw         $v0, 0x14($s0)
/* 28C20 80038420 00102526 */  addiu      $a1, $s1, 0x1000
/* 28C24 80038424 21105100 */  addu       $v0, $v0, $s1
/* 28C28 80038428 7B35010C */  jal        func_8004D5EC
/* 28C2C 8003842C 140002AE */   sw        $v0, 0x14($s0)
/* 28C30 80038430 1400038E */  lw         $v1, 0x14($s0)
/* 28C34 80038434 00000000 */  nop
/* 28C38 80038438 23187100 */  subu       $v1, $v1, $s1
/* 28C3C 8003843C 140003AE */  sw         $v1, 0x14($s0)
/* 28C40 80038440 1800BF8F */  lw         $ra, 0x18($sp)
/* 28C44 80038444 1400B18F */  lw         $s1, 0x14($sp)
/* 28C48 80038448 1000B08F */  lw         $s0, 0x10($sp)
/* 28C4C 8003844C 2000BD27 */  addiu      $sp, $sp, 0x20
/* 28C50 80038450 0800E003 */  jr         $ra
/* 28C54 80038454 00000000 */   nop
.size func_80038400, . - func_80038400
