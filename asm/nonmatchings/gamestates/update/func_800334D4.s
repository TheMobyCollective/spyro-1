.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_800334D4
/* 23CD4 800334D4 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 23CD8 800334D8 2C00BFAF */  sw         $ra, 0x2C($sp)
/* 23CDC 800334DC 7F4E010C */  jal        PadDemoUpdate
/* 23CE0 800334E0 2800B0AF */   sw        $s0, 0x28($sp)
/* 23CE4 800334E4 0780033C */  lui        $v1, %hi(g_DemoMode)
/* 23CE8 800334E8 1457638C */  lw         $v1, %lo(g_DemoMode)($v1)
/* 23CEC 800334EC 02000224 */  addiu      $v0, $zero, 0x2
/* 23CF0 800334F0 D5006210 */  beq        $v1, $v0, .L80033848
/* 23CF4 800334F4 21100000 */   addu      $v0, $zero, $zero
/* 23CF8 800334F8 0780023C */  lui        $v0, %hi(D_80075884)
/* 23CFC 800334FC 8458428C */  lw         $v0, %lo(D_80075884)($v0)
/* 23D00 80033500 00000000 */  nop
/* 23D04 80033504 24004014 */  bnez       $v0, .L80033598
/* 23D08 80033508 01004224 */   addiu     $v0, $v0, 0x1
/* 23D0C 8003350C 0780023C */  lui        $v0, %hi(D_800757B8)
/* 23D10 80033510 B857428C */  lw         $v0, %lo(D_800757B8)($v0)
/* 23D14 80033514 00000000 */  nop
/* 23D18 80033518 80100200 */  sll        $v0, $v0, 2
/* 23D1C 8003351C 0780013C */  lui        $at, %hi(D_8006EE8C)
/* 23D20 80033520 21082200 */  addu       $at, $at, $v0
/* 23D24 80033524 8CEE228C */  lw         $v0, %lo(D_8006EE8C)($at)
/* 23D28 80033528 0780033C */  lui        $v1, %hi(D_8007572C)
/* 23D2C 8003352C 2C57638C */  lw         $v1, %lo(D_8007572C)($v1)
/* 23D30 80033530 F8FF4224 */  addiu      $v0, $v0, -0x8
/* 23D34 80033534 2A106200 */  slt        $v0, $v1, $v0
/* 23D38 80033538 12004010 */  beqz       $v0, .L80033584
/* 23D3C 8003353C 10006228 */   slti      $v0, $v1, 0x10
/* 23D40 80033540 1A004014 */  bnez       $v0, .L800335AC
/* 23D44 80033544 00000000 */   nop
/* 23D48 80033548 0880023C */  lui        $v0, %hi(g_PadBuffer)
/* 23D4C 8003354C A0864290 */  lbu        $v0, %lo(g_PadBuffer)($v0)
/* 23D50 80033550 00000000 */  nop
/* 23D54 80033554 15004014 */  bnez       $v0, .L800335AC
/* 23D58 80033558 FF000224 */   addiu     $v0, $zero, 0xFF
/* 23D5C 8003355C 0880033C */  lui        $v1, %hi(g_PadBuffer + 0x2)
/* 23D60 80033560 A2866390 */  lbu        $v1, %lo(g_PadBuffer + 0x2)($v1)
/* 23D64 80033564 00000000 */  nop
/* 23D68 80033568 07006214 */  bne        $v1, $v0, .L80033588
/* 23D6C 8003356C 01000224 */   addiu     $v0, $zero, 0x1
/* 23D70 80033570 0880023C */  lui        $v0, %hi(g_PadBuffer + 0x3)
/* 23D74 80033574 A3864290 */  lbu        $v0, %lo(g_PadBuffer + 0x3)($v0)
/* 23D78 80033578 00000000 */  nop
/* 23D7C 8003357C 0B004310 */  beq        $v0, $v1, .L800335AC
/* 23D80 80033580 00000000 */   nop
.L80033584:
/* 23D84 80033584 01000224 */  addiu      $v0, $zero, 0x1
.L80033588:
/* 23D88 80033588 0780013C */  lui        $at, %hi(D_80075884)
/* 23D8C 8003358C 845822AC */  sw         $v0, %lo(D_80075884)($at)
/* 23D90 80033590 6BCD0008 */  j          .L800335AC
/* 23D94 80033594 00000000 */   nop
.L80033598:
/* 23D98 80033598 0780013C */  lui        $at, %hi(D_80075884)
/* 23D9C 8003359C 845822AC */  sw         $v0, %lo(D_80075884)($at)
/* 23DA0 800335A0 40100200 */  sll        $v0, $v0, 1
/* 23DA4 800335A4 0780013C */  lui        $at, %hi(g_Fade)
/* 23DA8 800335A8 185922AC */  sw         $v0, %lo(g_Fade)($at)
.L800335AC:
/* 23DAC 800335AC 0780033C */  lui        $v1, %hi(D_80075884)
/* 23DB0 800335B0 8458638C */  lw         $v1, %lo(D_80075884)($v1)
/* 23DB4 800335B4 10000224 */  addiu      $v0, $zero, 0x10
/* 23DB8 800335B8 A3006214 */  bne        $v1, $v0, .L80033848
/* 23DBC 800335BC 21100000 */   addu      $v0, $zero, $zero
/* 23DC0 800335C0 CA5A010C */  jal        func_80056B28
/* 23DC4 800335C4 21200000 */   addu      $a0, $zero, $zero
/* 23DC8 800335C8 B55B010C */  jal        SpuUpdate
/* 23DCC 800335CC 00000000 */   nop
/* 23DD0 800335D0 1800A427 */  addiu      $a0, $sp, 0x18
/* 23DD4 800335D4 21280000 */  addu       $a1, $zero, $zero
/* 23DD8 800335D8 21300000 */  addu       $a2, $zero, $zero
/* 23DDC 800335DC 21380000 */  addu       $a3, $zero, $zero
/* 23DE0 800335E0 00020224 */  addiu      $v0, $zero, 0x200
/* 23DE4 800335E4 1C00A2A7 */  sh         $v0, 0x1C($sp)
/* 23DE8 800335E8 E0010224 */  addiu      $v0, $zero, 0x1E0
/* 23DEC 800335EC 1800A0A7 */  sh         $zero, 0x18($sp)
/* 23DF0 800335F0 1A00A0A7 */  sh         $zero, 0x1A($sp)
/* 23DF4 800335F4 3E7E010C */  jal        ClearImage
/* 23DF8 800335F8 1E00A2A7 */   sh        $v0, 0x1E($sp)
/* 23DFC 800335FC D97D010C */  jal        DrawSync
/* 23E00 80033600 21200000 */   addu      $a0, $zero, $zero
/* 23E04 80033604 0780043C */  lui        $a0, %hi(D_80076B90)
/* 23E08 80033608 906B848C */  lw         $a0, %lo(D_80076B90)($a0)
/* 23E0C 8003360C 0880063C */  lui        $a2, %hi(D_8007A6E4)
/* 23E10 80033610 E4A6C68C */  lw         $a2, %lo(D_8007A6E4)($a2)
/* 23E14 80033614 0880073C */  lui        $a3, %hi(D_8007A6E0)
/* 23E18 80033618 E0A6E78C */  lw         $a3, %lo(D_8007A6E0)($a3)
/* 23E1C 8003361C 0180053C */  lui        $a1, %hi(g_OverlaySpacePointer)
/* 23E20 80033620 A013A58C */  lw         $a1, %lo(g_OverlaySpacePointer)($a1)
/* 23E24 80033624 0880023C */  lui        $v0, %hi(func_titlescreen_8007DDE8)
/* 23E28 80033628 E8DD4224 */  addiu      $v0, $v0, %lo(func_titlescreen_8007DDE8)
/* 23E2C 8003362C 0880013C */  lui        $at, %hi(D_800785D8)
/* 23E30 80033630 D88522AC */  sw         $v0, %lo(D_800785D8)($at)
/* 23E34 80033634 0880013C */  lui        $at, %hi(D_800785DC)
/* 23E38 80033638 DC8522AC */  sw         $v0, %lo(D_800785DC)($at)
/* 23E3C 8003363C 58020224 */  addiu      $v0, $zero, 0x258
/* 23E40 80033640 0780013C */  lui        $at, %hi(D_80075904)
/* 23E44 80033644 045920AC */  sw         $zero, %lo(D_80075904)($at)
/* 23E48 80033648 0780013C */  lui        $at, %hi(D_80075764)
/* 23E4C 8003364C 645720AC */  sw         $zero, %lo(D_80075764)($at)
/* 23E50 80033650 0780013C */  lui        $at, %hi(D_800757D0)
/* 23E54 80033654 D05720AC */  sw         $zero, %lo(D_800757D0)($at)
/* 23E58 80033658 0780013C */  lui        $at, %hi(D_8007584C)
/* 23E5C 8003365C 4C5820AC */  sw         $zero, %lo(D_8007584C)($at)
/* 23E60 80033660 0780013C */  lui        $at, %hi(g_DemoMode)
/* 23E64 80033664 145720AC */  sw         $zero, %lo(g_DemoMode)($at)
/* 23E68 80033668 0780013C */  lui        $at, %hi(g_LoadStage)
/* 23E6C 8003366C 645820AC */  sw         $zero, %lo(g_LoadStage)($at)
/* 23E70 80033670 0780013C */  lui        $at, %hi(D_8007566C)
/* 23E74 80033674 6C5620AC */  sw         $zero, %lo(D_8007566C)($at)
/* 23E78 80033678 0780013C */  lui        $at, %hi(D_80075690)
/* 23E7C 8003367C 905620AC */  sw         $zero, %lo(D_80075690)($at)
/* 23E80 80033680 0780013C */  lui        $at, %hi(D_80075784)
/* 23E84 80033684 845720AC */  sw         $zero, %lo(D_80075784)($at)
/* 23E88 80033688 4059000C */  jal        CDLoadSync
/* 23E8C 8003368C 1000A2AF */   sw        $v0, 0x10($sp)
/* 23E90 80033690 AACD0008 */  j          .L800336A8
/* 23E94 80033694 00000000 */   nop
.L80033698:
/* 23E98 80033698 5951000C */  jal        func_80014564
/* 23E9C 8003369C 00000000 */   nop
/* 23EA0 800336A0 F8AE000C */  jal        func_8002BBE0
/* 23EA4 800336A4 00000000 */   nop
.L800336A8:
/* 23EA8 800336A8 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 23EAC 800336AC 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 23EB0 800336B0 00000000 */  nop
/* 23EB4 800336B4 0A004228 */  slti       $v0, $v0, 0xA
/* 23EB8 800336B8 F7FF4014 */  bnez       $v0, .L80033698
/* 23EBC 800336BC 0E000224 */   addiu     $v0, $zero, 0xE
/* 23EC0 800336C0 0780013C */  lui        $at, %hi(g_Gamestate)
/* 23EC4 800336C4 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 23EC8 800336C8 0F000224 */  addiu      $v0, $zero, 0xF
/* 23ECC 800336CC 0780013C */  lui        $at, %hi(g_Fade)
/* 23ED0 800336D0 185922AC */  sw         $v0, %lo(g_Fade)($at)
/* 23ED4 800336D4 5CB4000C */  jal        func_8002D170
/* 23ED8 800336D8 00000000 */   nop
/* 23EDC 800336DC 0780023C */  lui        $v0, %hi(D_800757B8)
/* 23EE0 800336E0 B857428C */  lw         $v0, %lo(D_800757B8)($v0)
/* 23EE4 800336E4 0780033C */  lui        $v1, %hi(D_8007572C)
/* 23EE8 800336E8 2C57638C */  lw         $v1, %lo(D_8007572C)($v1)
/* 23EEC 800336EC 80100200 */  sll        $v0, $v0, 2
/* 23EF0 800336F0 0780013C */  lui        $at, %hi(D_8006EE8C)
/* 23EF4 800336F4 21082200 */  addu       $at, $at, $v0
/* 23EF8 800336F8 8CEE228C */  lw         $v0, %lo(D_8006EE8C)($at)
/* 23EFC 800336FC 00000000 */  nop
/* 23F00 80033700 2A186200 */  slt        $v1, $v1, $v0
/* 23F04 80033704 34006014 */  bnez       $v1, .L800337D8
/* 23F08 80033708 0200043C */   lui       $a0, (0x262D0 >> 16)
/* 23F0C 8003370C 0780033C */  lui        $v1, %hi(D_80075680)
/* 23F10 80033710 8056638C */  lw         $v1, %lo(D_80075680)($v1)
/* 23F14 80033714 D0020224 */  addiu      $v0, $zero, 0x2D0
/* 23F18 80033718 000062AC */  sw         $v0, 0x0($v1)
/* 23F1C 8003371C 0780023C */  lui        $v0, %hi(D_800778F0)
/* 23F20 80033720 F0784224 */  addiu      $v0, $v0, %lo(D_800778F0)
/* 23F24 80033724 0780013C */  lui        $at, %hi(g_Spu + 0x2C8)
/* 23F28 80033728 D06122AC */  sw         $v0, %lo(g_Spu + 0x2C8)($at)
/* 23F2C 8003372C 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 23F30 80033730 D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 23F34 80033734 D0628434 */  ori        $a0, $a0, (0x262D0 & 0xFFFF)
/* 23F38 80033738 000044AC */  sw         $a0, 0x0($v0)
/* 23F3C 8003373C 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 23F40 80033740 D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 23F44 80033744 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 23F48 80033748 040062AC */  sw         $v0, 0x4($v1)
/* 23F4C 8003374C 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 23F50 80033750 D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 23F54 80033754 50000224 */  addiu      $v0, $zero, 0x50
/* 23F58 80033758 080062A4 */  sh         $v0, 0x8($v1)
/* 23F5C 8003375C 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 23F60 80033760 D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 23F64 80033764 0780023C */  lui        $v0, %hi(D_8006EE6C)
/* 23F68 80033768 6CEE428C */  lw         $v0, %lo(D_8006EE6C)($v0)
/* 23F6C 8003376C 21280000 */  addu       $a1, $zero, $zero
/* 23F70 80033770 0A0062A4 */  sh         $v0, 0xA($v1)
/* 23F74 80033774 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 23F78 80033778 D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 23F7C 8003377C 10000624 */  addiu      $a2, $zero, 0x10
/* 23F80 80033780 0C0040A4 */  sh         $zero, 0xC($v0)
/* 23F84 80033784 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 23F88 80033788 D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 23F8C 8003378C 0780073C */  lui        $a3, %hi(D_80077084)
/* 23F90 80033790 8470E724 */  addiu      $a3, $a3, %lo(D_80077084)
/* 23F94 80033794 0E0040A4 */  sh         $zero, 0xE($v0)
/* 23F98 80033798 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 23F9C 8003379C D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 23FA0 800337A0 00000000 */  nop
/* 23FA4 800337A4 100040AC */  sw         $zero, 0x10($v0)
/* 23FA8 800337A8 01000224 */  addiu      $v0, $zero, 0x1
/* 23FAC 800337AC 0780013C */  lui        $at, %hi(g_Spu + 0x2D4)
/* 23FB0 800337B0 DC6122AC */  sw         $v0, %lo(g_Spu + 0x2D4)($at)
/* 23FB4 800337B4 FF3F0224 */  addiu      $v0, $zero, 0x3FFF
/* 23FB8 800337B8 0780013C */  lui        $at, %hi(g_Spu + 0x2E0)
/* 23FBC 800337BC E86122A4 */  sh         $v0, %lo(g_Spu + 0x2E0)($at)
/* 23FC0 800337C0 0780013C */  lui        $at, %hi(g_Spu + 0x2E2)
/* 23FC4 800337C4 EA6122A4 */  sh         $v0, %lo(g_Spu + 0x2E2)($at)
/* 23FC8 800337C8 9E56010C */  jal        PlaySound
/* 23FCC 800337CC 21200000 */   addu      $a0, $zero, $zero
/* 23FD0 800337D0 FBCD0008 */  j          .L800337EC
/* 23FD4 800337D4 0400063C */   lui       $a2, (0x40000 >> 16)
.L800337D8:
/* 23FD8 800337D8 0780033C */  lui        $v1, %hi(D_80075680)
/* 23FDC 800337DC 8056638C */  lw         $v1, %lo(D_80075680)($v1)
/* 23FE0 800337E0 90040224 */  addiu      $v0, $zero, 0x490
/* 23FE4 800337E4 000062AC */  sw         $v0, 0x0($v1)
/* 23FE8 800337E8 0400063C */  lui        $a2, (0x40000 >> 16)
.L800337EC:
/* 23FEC 800337EC 01001024 */  addiu      $s0, $zero, 0x1
/* 23FF0 800337F0 0780043C */  lui        $a0, %hi(D_80076B90)
/* 23FF4 800337F4 906B848C */  lw         $a0, %lo(D_80076B90)($a0)
/* 23FF8 800337F8 0880073C */  lui        $a3, %hi(D_8007A6D8)
/* 23FFC 800337FC D8A6E78C */  lw         $a3, %lo(D_8007A6D8)($a3)
/* 24000 80033800 58020224 */  addiu      $v0, $zero, 0x258
/* 24004 80033804 1000A2AF */  sw         $v0, 0x10($sp)
/* 24008 80033808 0880023C */  lui        $v0, %hi(D_800785E8)
/* 2400C 8003380C E885428C */  lw         $v0, %lo(D_800785E8)($v0)
/* 24010 80033810 FCFF053C */  lui        $a1, (0xFFFC0000 >> 16)
/* 24014 80033814 0880013C */  lui        $at, %hi(g_TitlescreenState + 0x10)
/* 24018 80033818 888D30AC */  sw         $s0, %lo(g_TitlescreenState + 0x10)($at)
/* 2401C 8003381C A659000C */  jal        CDLoadAsync
/* 24020 80033820 21284500 */   addu      $a1, $v0, $a1
/* 24024 80033824 0780033C */  lui        $v1, %hi(D_800757B8)
/* 24028 80033828 B857638C */  lw         $v1, %lo(D_800757B8)($v1)
/* 2402C 8003382C 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 24030 80033830 9C5730AC */  sw         $s0, %lo(g_StateSwitch)($at)
/* 24034 80033834 01006324 */  addiu      $v1, $v1, 0x1
/* 24038 80033838 03006330 */  andi       $v1, $v1, 0x3
/* 2403C 8003383C 0780013C */  lui        $at, %hi(D_800757B8)
/* 24040 80033840 B85723AC */  sw         $v1, %lo(D_800757B8)($at)
/* 24044 80033844 01000224 */  addiu      $v0, $zero, 0x1
.L80033848:
/* 24048 80033848 2C00BF8F */  lw         $ra, 0x2C($sp)
/* 2404C 8003384C 2800B08F */  lw         $s0, 0x28($sp)
/* 24050 80033850 3000BD27 */  addiu      $sp, $sp, 0x30
/* 24054 80033854 0800E003 */  jr         $ra
/* 24058 80033858 00000000 */   nop
.size func_800334D4, . - func_800334D4
