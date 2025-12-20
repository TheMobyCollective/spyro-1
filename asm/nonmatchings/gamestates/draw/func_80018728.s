.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80018728
/* 8F28 80018728 0780023C */  lui        $v0, %hi(g_DragonCutscene + 0x90)
/* 8F2C 8001872C C070428C */  lw         $v0, %lo(g_DragonCutscene + 0x90)($v0)
/* 8F30 80018730 C8FFBD27 */  addiu      $sp, $sp, -0x38
/* 8F34 80018734 3000BFAF */  sw         $ra, 0x30($sp)
/* 8F38 80018738 2C00B3AF */  sw         $s3, 0x2C($sp)
/* 8F3C 8001873C 2800B2AF */  sw         $s2, 0x28($sp)
/* 8F40 80018740 2400B1AF */  sw         $s1, 0x24($sp)
/* 8F44 80018744 2000B0AF */  sw         $s0, 0x20($sp)
/* 8F48 80018748 0000428C */  lw         $v0, 0x0($v0)
/* 8F4C 8001874C 00000000 */  nop
/* 8F50 80018750 3800428C */  lw         $v0, 0x38($v0)
/* 8F54 80018754 00000000 */  nop
/* 8F58 80018758 80100200 */  sll        $v0, $v0, 2
/* 8F5C 8001875C 0780013C */  lui        $at, %hi(g_DragonNames)
/* 8F60 80018760 21082200 */  addu       $at, $at, $v0
/* 8F64 80018764 94F6328C */  lw         $s2, %lo(g_DragonNames)($at)
/* 8F68 80018768 DB89010C */  jal        strlen
/* 8F6C 8001876C 21204002 */   addu      $a0, $s2, $zero
/* 8F70 80018770 0780043C */  lui        $a0, %hi(D_800755AC)
/* 8F74 80018774 AC558424 */  addiu      $a0, $a0, %lo(D_800755AC)
/* 8F78 80018778 1000A527 */  addiu      $a1, $sp, 0x10
/* 8F7C 8001877C 14000624 */  addiu      $a2, $zero, 0x14
/* 8F80 80018780 02000724 */  addiu      $a3, $zero, 0x2
/* 8F84 80018784 FFFF4224 */  addiu      $v0, $v0, -0x1
/* 8F88 80018788 40800200 */  sll        $s0, $v0, 1
/* 8F8C 8001878C 21800202 */  addu       $s0, $s0, $v0
/* 8F90 80018790 80801000 */  sll        $s0, $s0, 2
/* 8F94 80018794 21800202 */  addu       $s0, $s0, $v0
/* 8F98 80018798 B0000224 */  addiu      $v0, $zero, 0xB0
/* 8F9C 8001879C 23105000 */  subu       $v0, $v0, $s0
/* 8FA0 800187A0 0780133C */  lui        $s3, %hi(g_HudMobys)
/* 8FA4 800187A4 1057738E */  lw         $s3, %lo(g_HudMobys)($s3)
/* 8FA8 800187A8 C8001124 */  addiu      $s1, $zero, 0xC8
/* 8FAC 800187AC 1000A2AF */  sw         $v0, 0x10($sp)
/* 8FB0 800187B0 00100224 */  addiu      $v0, $zero, 0x1000
/* 8FB4 800187B4 1400B1AF */  sw         $s1, 0x14($sp)
/* 8FB8 800187B8 F95F000C */  jal        func_80017FE4
/* 8FBC 800187BC 1800A2AF */   sw        $v0, 0x18($sp)
/* 8FC0 800187C0 21204002 */  addu       $a0, $s2, $zero
/* 8FC4 800187C4 1000A527 */  addiu      $a1, $sp, 0x10
/* 8FC8 800187C8 1A000624 */  addiu      $a2, $zero, 0x1A
/* 8FCC 800187CC 02000724 */  addiu      $a3, $zero, 0x2
/* 8FD0 800187D0 50010224 */  addiu      $v0, $zero, 0x150
/* 8FD4 800187D4 23105000 */  subu       $v0, $v0, $s0
/* 8FD8 800187D8 1000A2AF */  sw         $v0, 0x10($sp)
/* 8FDC 800187DC 000C0224 */  addiu      $v0, $zero, 0xC00
/* 8FE0 800187E0 1400B1AF */  sw         $s1, 0x14($sp)
/* 8FE4 800187E4 F95F000C */  jal        func_80017FE4
/* 8FE8 800187E8 1800A2AF */   sw        $v0, 0x18($sp)
/* 8FEC 800187EC 0780023C */  lui        $v0, %hi(g_HudMobys)
/* 8FF0 800187F0 1057428C */  lw         $v0, %lo(g_HudMobys)($v0)
/* 8FF4 800187F4 A8FF7326 */  addiu      $s3, $s3, -0x58
/* 8FF8 800187F8 2A106202 */  slt        $v0, $s3, $v0
/* 8FFC 800187FC 16004014 */  bnez       $v0, .L80018858
/* 9000 80018800 21180000 */   addu      $v1, $zero, $zero
/* 9004 80018804 0780053C */  lui        $a1, %hi(g_DragonCutscene + 0x50)
/* 9008 80018808 8070A524 */  addiu      $a1, $a1, %lo(g_DragonCutscene + 0x50)
/* 900C 8001880C 0780043C */  lui        $a0, %hi(D_8006CC78)
/* 9010 80018810 78CC8424 */  addiu      $a0, $a0, %lo(D_8006CC78)
.L80018814:
/* 9014 80018814 0000A28C */  lw         $v0, 0x0($a1)
/* 9018 80018818 00000000 */  nop
/* 901C 8001881C 40100200 */  sll        $v0, $v0, 1
/* 9020 80018820 21104300 */  addu       $v0, $v0, $v1
/* 9024 80018824 FF004230 */  andi       $v0, $v0, 0xFF
/* 9028 80018828 40100200 */  sll        $v0, $v0, 1
/* 902C 8001882C 21104400 */  addu       $v0, $v0, $a0
/* 9030 80018830 00004294 */  lhu        $v0, 0x0($v0)
/* 9034 80018834 00000000 */  nop
/* 9038 80018838 C2110200 */  srl        $v0, $v0, 7
/* 903C 8001883C 460062A2 */  sb         $v0, 0x46($s3)
/* 9040 80018840 0780023C */  lui        $v0, %hi(g_HudMobys)
/* 9044 80018844 1057428C */  lw         $v0, %lo(g_HudMobys)($v0)
/* 9048 80018848 A8FF7326 */  addiu      $s3, $s3, -0x58
/* 904C 8001884C 2A106202 */  slt        $v0, $s3, $v0
/* 9050 80018850 F0FF4010 */  beqz       $v0, .L80018814
/* 9054 80018854 0C006324 */   addiu     $v1, $v1, 0xC
.L80018858:
/* 9058 80018858 3000BF8F */  lw         $ra, 0x30($sp)
/* 905C 8001885C 2C00B38F */  lw         $s3, 0x2C($sp)
/* 9060 80018860 2800B28F */  lw         $s2, 0x28($sp)
/* 9064 80018864 2400B18F */  lw         $s1, 0x24($sp)
/* 9068 80018868 2000B08F */  lw         $s0, 0x20($sp)
/* 906C 8001886C 3800BD27 */  addiu      $sp, $sp, 0x38
/* 9070 80018870 0800E003 */  jr         $ra
/* 9074 80018874 00000000 */   nop
.size func_80018728, . - func_80018728
