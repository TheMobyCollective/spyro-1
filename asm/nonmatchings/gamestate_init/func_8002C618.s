.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002C618
/* 1CE18 8002C618 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1CE1C 8002C61C 1000BFAF */  sw         $ra, 0x10($sp)
/* 1CE20 8002C620 CA5A010C */  jal        func_80056B28
/* 1CE24 8002C624 21200000 */   addu      $a0, $zero, $zero
/* 1CE28 8002C628 0A000224 */  addiu      $v0, $zero, 0xA
/* 1CE2C 8002C62C 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1CE30 8002C630 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1CE34 8002C634 0780013C */  lui        $at, %hi(D_8007568C)
/* 1CE38 8002C638 8C5620AC */  sw         $zero, %lo(D_8007568C)($at)
/* 1CE3C 8002C63C 0780013C */  lui        $at, %hi(D_800758B8)
/* 1CE40 8002C640 B85820AC */  sw         $zero, %lo(D_800758B8)($at)
/* 1CE44 8002C644 092B010C */  jal        func_8004AC24
/* 1CE48 8002C648 21200000 */   addu      $a0, $zero, $zero
/* 1CE4C 8002C64C 9AFA000C */  jal        func_8003EA68
/* 1CE50 8002C650 21200000 */   addu      $a0, $zero, $zero
/* 1CE54 8002C654 1000BF8F */  lw         $ra, 0x10($sp)
/* 1CE58 8002C658 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1CE5C 8002C65C 0800E003 */  jr         $ra
/* 1CE60 8002C660 00000000 */   nop
.size func_8002C618, . - func_8002C618
