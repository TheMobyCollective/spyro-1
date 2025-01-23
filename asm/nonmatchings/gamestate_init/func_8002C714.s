.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002C714
/* 1CF14 8002C714 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1CF18 8002C718 1000B0AF */  sw         $s0, 0x10($sp)
/* 1CF1C 8002C71C 21808000 */  addu       $s0, $a0, $zero
/* 1CF20 8002C720 03000012 */  beqz       $s0, .L8002C730
/* 1CF24 8002C724 1400BFAF */   sw        $ra, 0x14($sp)
/* 1CF28 8002C728 CA5A010C */  jal        func_80056B28
/* 1CF2C 8002C72C 21200000 */   addu      $a0, $zero, $zero
.L8002C730:
/* 1CF30 8002C730 21280000 */  addu       $a1, $zero, $zero
/* 1CF34 8002C734 0780023C */  lui        $v0, %hi(g_Spu + 0x2CC)
/* 1CF38 8002C738 D461428C */  lw         $v0, %lo(g_Spu + 0x2CC)($v0)
/* 1CF3C 8002C73C 10000624 */  addiu      $a2, $zero, 0x10
/* 1CF40 8002C740 2C004490 */  lbu        $a0, 0x2C($v0)
/* 1CF44 8002C744 9E56010C */  jal        PlaySound
/* 1CF48 8002C748 21380000 */   addu      $a3, $zero, $zero
/* 1CF4C 8002C74C AA2A023C */  lui        $v0, (0x2AAAAAAB >> 16)
/* 1CF50 8002C750 0780033C */  lui        $v1, %hi(D_80075964)
/* 1CF54 8002C754 6459638C */  lw         $v1, %lo(D_80075964)($v1)
/* 1CF58 8002C758 ABAA4234 */  ori        $v0, $v0, (0x2AAAAAAB & 0xFFFF)
/* 1CF5C 8002C75C 18006200 */  mult       $v1, $v0
/* 1CF60 8002C760 0780013C */  lui        $at, %hi(D_800757CC)
/* 1CF64 8002C764 CC5720AC */  sw         $zero, %lo(D_800757CC)($at)
/* 1CF68 8002C768 0780013C */  lui        $at, %hi(D_800756D4)
/* 1CF6C 8002C76C D45620AC */  sw         $zero, %lo(D_800756D4)($at)
/* 1CF70 8002C770 03000224 */  addiu      $v0, $zero, 0x3
/* 1CF74 8002C774 C31F0300 */  sra        $v1, $v1, 31
/* 1CF78 8002C778 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1CF7C 8002C77C D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1CF80 8002C780 10400000 */  mfhi       $t0
/* 1CF84 8002C784 23180301 */  subu       $v1, $t0, $v1
/* 1CF88 8002C788 0780013C */  lui        $at, %hi(D_80075744)
/* 1CF8C 8002C78C 445723AC */  sw         $v1, %lo(D_80075744)($at)
/* 1CF90 8002C790 03000012 */  beqz       $s0, .L8002C7A0
/* 1CF94 8002C794 00000000 */   nop
/* 1CF98 8002C798 0780013C */  lui        $at, %hi(D_800758B8)
/* 1CF9C 8002C79C B85820AC */  sw         $zero, %lo(D_800758B8)($at)
.L8002C7A0:
/* 1CFA0 8002C7A0 55B5000C */  jal        CheatResetBuffer
/* 1CFA4 8002C7A4 00000000 */   nop
/* 1CFA8 8002C7A8 1400BF8F */  lw         $ra, 0x14($sp)
/* 1CFAC 8002C7AC 1000B08F */  lw         $s0, 0x10($sp)
/* 1CFB0 8002C7B0 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1CFB4 8002C7B4 0800E003 */  jr         $ra
/* 1CFB8 8002C7B8 00000000 */   nop
.size func_8002C714, . - func_8002C714
