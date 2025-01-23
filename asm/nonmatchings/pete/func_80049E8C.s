.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80049E8C
/* 3A68C 80049E8C 0880023C */  lui        $v0, %hi(g_Spyro + 0x6C)
/* 3A690 80049E90 C48A428C */  lw         $v0, %lo(g_Spyro + 0x6C)($v0)
/* 3A694 80049E94 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 3A698 80049E98 24004014 */  bnez       $v0, .L80049F2C
/* 3A69C 80049E9C 1000BFAF */   sw        $ra, 0x10($sp)
/* 3A6A0 80049EA0 0880033C */  lui        $v1, %hi(g_Spyro + 0x1E8)
/* 3A6A4 80049EA4 408C638C */  lw         $v1, %lo(g_Spyro + 0x1E8)($v1)
/* 3A6A8 80049EA8 0880023C */  lui        $v0, %hi(g_Spyro + 0x74)
/* 3A6AC 80049EAC CC8A428C */  lw         $v0, %lo(g_Spyro + 0x74)($v0)
/* 3A6B0 80049EB0 00000000 */  nop
/* 3A6B4 80049EB4 1D006214 */  bne        $v1, $v0, .L80049F2C
/* 3A6B8 80049EB8 00000000 */   nop
/* 3A6BC 80049EBC 17006014 */  bnez       $v1, .L80049F1C
/* 3A6C0 80049EC0 00000000 */   nop
/* 3A6C4 80049EC4 0880023C */  lui        $v0, %hi(g_Spyro + 0x18)
/* 3A6C8 80049EC8 708A4290 */  lbu        $v0, %lo(g_Spyro + 0x18)($v0)
/* 3A6CC 80049ECC 0880033C */  lui        $v1, %hi(g_Spyro + 0x1E)
/* 3A6D0 80049ED0 768A6390 */  lbu        $v1, %lo(g_Spyro + 0x1E)($v1)
/* 3A6D4 80049ED4 0880043C */  lui        $a0, %hi(g_Spyro + 0x19)
/* 3A6D8 80049ED8 718A8490 */  lbu        $a0, %lo(g_Spyro + 0x19)($a0)
/* 3A6DC 80049EDC 0880053C */  lui        $a1, %hi(g_Spyro + 0x1F)
/* 3A6E0 80049EE0 778AA590 */  lbu        $a1, %lo(g_Spyro + 0x1F)($a1)
/* 3A6E4 80049EE4 0880063C */  lui        $a2, %hi(g_Spyro + 0x24)
/* 3A6E8 80049EE8 7C8AC690 */  lbu        $a2, %lo(g_Spyro + 0x24)($a2)
/* 3A6EC 80049EEC 0880013C */  lui        $at, %hi(g_Spyro + 0x1C)
/* 3A6F0 80049EF0 748A22A0 */  sb         $v0, %lo(g_Spyro + 0x1C)($at)
/* 3A6F4 80049EF4 0880013C */  lui        $at, %hi(g_Spyro + 0x22)
/* 3A6F8 80049EF8 7A8A23A0 */  sb         $v1, %lo(g_Spyro + 0x22)($at)
/* 3A6FC 80049EFC 0880013C */  lui        $at, %hi(g_Spyro + 0x1D)
/* 3A700 80049F00 758A24A0 */  sb         $a0, %lo(g_Spyro + 0x1D)($at)
/* 3A704 80049F04 0880013C */  lui        $at, %hi(g_Spyro + 0x23)
/* 3A708 80049F08 7B8A25A0 */  sb         $a1, %lo(g_Spyro + 0x23)($at)
/* 3A70C 80049F0C 0880013C */  lui        $at, %hi(g_Spyro + 0x26)
/* 3A710 80049F10 7E8A26A0 */  sb         $a2, %lo(g_Spyro + 0x26)($at)
/* 3A714 80049F14 CB270108 */  j          .L80049F2C
/* 3A718 80049F18 00000000 */   nop
.L80049F1C:
/* 3A71C 80049F1C 0880043C */  lui        $a0, %hi(g_Spyro + 0x70)
/* 3A720 80049F20 C88A848C */  lw         $a0, %lo(g_Spyro + 0x70)($a0)
/* 3A724 80049F24 7F27010C */  jal        func_80049DFC
/* 3A728 80049F28 00000000 */   nop
.L80049F2C:
/* 3A72C 80049F2C 1000BF8F */  lw         $ra, 0x10($sp)
/* 3A730 80049F30 1800BD27 */  addiu      $sp, $sp, 0x18
/* 3A734 80049F34 0800E003 */  jr         $ra
/* 3A738 80049F38 00000000 */   nop
.size func_80049E8C, . - func_80049E8C
