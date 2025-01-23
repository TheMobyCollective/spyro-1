.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003FDC8
/* 305C8 8003FDC8 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 305CC 8003FDCC 1000BFAF */  sw         $ra, 0x10($sp)
/* 305D0 8003FDD0 9AFA000C */  jal        func_8003EA68
/* 305D4 8003FDD4 00000000 */   nop
/* 305D8 8003FDD8 0880043C */  lui        $a0, %hi(g_Spyro + 0x78)
/* 305DC 8003FDDC D08A848C */  lw         $a0, %lo(g_Spyro + 0x78)($a0)
/* 305E0 8003FDE0 0780023C */  lui        $v0, %hi(spyro_StateDefaultAnimation)
/* 305E4 8003FDE4 70C44224 */  addiu      $v0, $v0, %lo(spyro_StateDefaultAnimation)
/* 305E8 8003FDE8 21108200 */  addu       $v0, $a0, $v0
/* 305EC 8003FDEC 00004390 */  lbu        $v1, 0x0($v0)
/* 305F0 8003FDF0 0880013C */  lui        $at, %hi(g_Spyro + 0x1E)
/* 305F4 8003FDF4 768A20A0 */  sb         $zero, %lo(g_Spyro + 0x1E)($at)
/* 305F8 8003FDF8 0880013C */  lui        $at, %hi(g_Spyro + 0x18)
/* 305FC 8003FDFC 708A23A0 */  sb         $v1, %lo(g_Spyro + 0x18)($at)
/* 30600 8003FE00 00004390 */  lbu        $v1, 0x0($v0)
/* 30604 8003FE04 01000224 */  addiu      $v0, $zero, 0x1
/* 30608 8003FE08 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 3060C 8003FE0C 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 30610 8003FE10 0880013C */  lui        $at, %hi(g_Spyro + 0x24)
/* 30614 8003FE14 7C8A20A0 */  sb         $zero, %lo(g_Spyro + 0x24)($at)
/* 30618 8003FE18 0880013C */  lui        $at, %hi(g_Spyro + 0x54)
/* 3061C 8003FE1C AC8A20AC */  sw         $zero, %lo(g_Spyro + 0x54)($at)
/* 30620 8003FE20 0880013C */  lui        $at, %hi(g_Spyro + 0x5C)
/* 30624 8003FE24 B48A24AC */  sw         $a0, %lo(g_Spyro + 0x5C)($at)
/* 30628 8003FE28 0880013C */  lui        $at, %hi(g_Spyro + 0x19)
/* 3062C 8003FE2C 718A23A0 */  sb         $v1, %lo(g_Spyro + 0x19)($at)
/* 30630 8003FE30 1000BF8F */  lw         $ra, 0x10($sp)
/* 30634 8003FE34 1800BD27 */  addiu      $sp, $sp, 0x18
/* 30638 8003FE38 0800E003 */  jr         $ra
/* 3063C 8003FE3C 00000000 */   nop
.size func_8003FDC8, . - func_8003FDC8
