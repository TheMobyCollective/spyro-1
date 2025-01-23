.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80049F3C
/* 3A73C 80049F3C 0880023C */  lui        $v0, %hi(g_Spyro + 0x18)
/* 3A740 80049F40 708A4290 */  lbu        $v0, %lo(g_Spyro + 0x18)($v0)
/* 3A744 80049F44 0780013C */  lui        $at, %hi(spyro_FlameBlockedInAnimation)
/* 3A748 80049F48 21082200 */  addu       $at, $at, $v0
/* 3A74C 80049F4C 58C52290 */  lbu        $v0, %lo(spyro_FlameBlockedInAnimation)($at)
/* 3A750 80049F50 00000000 */  nop
/* 3A754 80049F54 09004014 */  bnez       $v0, .L80049F7C
/* 3A758 80049F58 00000000 */   nop
/* 3A75C 80049F5C 0880023C */  lui        $v0, %hi(g_Spyro + 0x19)
/* 3A760 80049F60 718A4290 */  lbu        $v0, %lo(g_Spyro + 0x19)($v0)
/* 3A764 80049F64 0780013C */  lui        $at, %hi(spyro_FlameBlockedInAnimation)
/* 3A768 80049F68 21082200 */  addu       $at, $at, $v0
/* 3A76C 80049F6C 58C52290 */  lbu        $v0, %lo(spyro_FlameBlockedInAnimation)($at)
/* 3A770 80049F70 00000000 */  nop
/* 3A774 80049F74 05004010 */  beqz       $v0, .L80049F8C
/* 3A778 80049F78 00000000 */   nop
.L80049F7C:
/* 3A77C 80049F7C 0880013C */  lui        $at, %hi(g_Spyro + 0x1E8)
/* 3A780 80049F80 408C20AC */  sw         $zero, %lo(g_Spyro + 0x1E8)($at)
/* 3A784 80049F84 E9270108 */  j          .L80049FA4
/* 3A788 80049F88 00000000 */   nop
.L80049F8C:
/* 3A78C 80049F8C 0880023C */  lui        $v0, %hi(g_Spyro + 0x1EC)
/* 3A790 80049F90 448C428C */  lw         $v0, %lo(g_Spyro + 0x1EC)($v0)
/* 3A794 80049F94 00000000 */  nop
/* 3A798 80049F98 01004224 */  addiu      $v0, $v0, 0x1
/* 3A79C 80049F9C 0880013C */  lui        $at, %hi(g_Spyro + 0x1EC)
/* 3A7A0 80049FA0 448C22AC */  sw         $v0, %lo(g_Spyro + 0x1EC)($at)
.L80049FA4:
/* 3A7A4 80049FA4 0800E003 */  jr         $ra
/* 3A7A8 80049FA8 00000000 */   nop
.size func_80049F3C, . - func_80049F3C
