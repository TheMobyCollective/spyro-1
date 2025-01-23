.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80049DFC
/* 3A5FC 80049DFC 0880053C */  lui        $a1, %hi(g_Spyro + 0x26)
/* 3A600 80049E00 7E8AA524 */  addiu      $a1, $a1, %lo(g_Spyro + 0x26)
/* 3A604 80049E04 0000A290 */  lbu        $v0, 0x0($a1)
/* 3A608 80049E08 00000000 */  nop
/* 3A60C 80049E0C 21184400 */  addu       $v1, $v0, $a0
/* 3A610 80049E10 FF006230 */  andi       $v0, $v1, 0xFF
/* 3A614 80049E14 1000422C */  sltiu      $v0, $v0, 0x10
/* 3A618 80049E18 1A004014 */  bnez       $v0, .L80049E84
/* 3A61C 80049E1C 0000A3A0 */   sb        $v1, 0x0($a1)
/* 3A620 80049E20 F0FF6224 */  addiu      $v0, $v1, -0x10
/* 3A624 80049E24 0000A2A0 */  sb         $v0, 0x0($a1)
/* 3A628 80049E28 0880033C */  lui        $v1, %hi(g_Spyro + 0x23)
/* 3A62C 80049E2C 7B8A6390 */  lbu        $v1, %lo(g_Spyro + 0x23)($v1)
/* 3A630 80049E30 0880043C */  lui        $a0, %hi(g_Spyro + 0x1D)
/* 3A634 80049E34 758A8490 */  lbu        $a0, %lo(g_Spyro + 0x1D)($a0)
/* 3A638 80049E38 01006224 */  addiu      $v0, $v1, 0x1
/* 3A63C 80049E3C 0880013C */  lui        $at, %hi(g_Spyro + 0x1C)
/* 3A640 80049E40 748A24A0 */  sb         $a0, %lo(g_Spyro + 0x1C)($at)
/* 3A644 80049E44 80200400 */  sll        $a0, $a0, 2
/* 3A648 80049E48 0880013C */  lui        $at, %hi(g_Spyro + 0x22)
/* 3A64C 80049E4C 7A8A23A0 */  sb         $v1, %lo(g_Spyro + 0x22)($at)
/* 3A650 80049E50 0880013C */  lui        $at, %hi(g_Spyro + 0x23)
/* 3A654 80049E54 7B8A22A0 */  sb         $v0, %lo(g_Spyro + 0x23)($at)
/* 3A658 80049E58 0780013C */  lui        $at, %hi(D_8006C4A1)
/* 3A65C 80049E5C 21082400 */  addu       $at, $at, $a0
/* 3A660 80049E60 A1C42390 */  lbu        $v1, %lo(D_8006C4A1)($at)
/* 3A664 80049E64 FF004230 */  andi       $v0, $v0, 0xFF
/* 3A668 80049E68 06004314 */  bne        $v0, $v1, .L80049E84
/* 3A66C 80049E6C 00000000 */   nop
/* 3A670 80049E70 0780013C */  lui        $at, %hi(spyro_AnimationDetails)
/* 3A674 80049E74 21082400 */  addu       $at, $at, $a0
/* 3A678 80049E78 A0C42290 */  lbu        $v0, %lo(spyro_AnimationDetails)($at)
/* 3A67C 80049E7C 0880013C */  lui        $at, %hi(g_Spyro + 0x23)
/* 3A680 80049E80 7B8A22A0 */  sb         $v0, %lo(g_Spyro + 0x23)($at)
.L80049E84:
/* 3A684 80049E84 0800E003 */  jr         $ra
/* 3A688 80049E88 00000000 */   nop
.size func_80049DFC, . - func_80049DFC
