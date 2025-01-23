.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003C6E4
/* 2CEE4 8003C6E4 D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 2CEE8 8003C6E8 2000B0AF */  sw         $s0, 0x20($sp)
/* 2CEEC 8003C6EC 21808000 */  addu       $s0, $a0, $zero
/* 2CEF0 8003C6F0 2400BFAF */  sw         $ra, 0x24($sp)
/* 2CEF4 8003C6F4 0000048E */  lw         $a0, 0x0($s0)
/* 2CEF8 8003C6F8 00000000 */  nop
/* 2CEFC 8003C6FC 13008290 */  lbu        $v0, 0x13($a0)
/* 2CF00 8003C700 00000000 */  nop
/* 2CF04 8003C704 46004010 */  beqz       $v0, .L8003C820
/* 2CF08 8003C708 00000000 */   nop
/* 2CF0C 8003C70C 1400038E */  lw         $v1, 0x14($s0)
/* 2CF10 8003C710 0C00828C */  lw         $v0, 0xC($a0)
/* 2CF14 8003C714 00000000 */  nop
/* 2CF18 8003C718 2A104300 */  slt        $v0, $v0, $v1
/* 2CF1C 8003C71C 40004010 */  beqz       $v0, .L8003C820
/* 2CF20 8003C720 00000000 */   nop
/* 2CF24 8003C724 0C00028E */  lw         $v0, 0xC($s0)
/* 2CF28 8003C728 0000838C */  lw         $v1, 0x0($a0)
/* 2CF2C 8003C72C 00000000 */  nop
/* 2CF30 8003C730 21104300 */  addu       $v0, $v0, $v1
/* 2CF34 8003C734 0C0002AE */  sw         $v0, 0xC($s0)
/* 2CF38 8003C738 1000028E */  lw         $v0, 0x10($s0)
/* 2CF3C 8003C73C 0400838C */  lw         $v1, 0x4($a0)
/* 2CF40 8003C740 00000000 */  nop
/* 2CF44 8003C744 21104300 */  addu       $v0, $v0, $v1
/* 2CF48 8003C748 100002AE */  sw         $v0, 0x10($s0)
/* 2CF4C 8003C74C 0800828C */  lw         $v0, 0x8($a0)
/* 2CF50 8003C750 00000000 */  nop
/* 2CF54 8003C754 FAFF4224 */  addiu      $v0, $v0, -0x6
/* 2CF58 8003C758 080082AC */  sw         $v0, 0x8($a0)
/* 2CF5C 8003C75C 80FF4228 */  slti       $v0, $v0, -0x80
/* 2CF60 8003C760 02004010 */  beqz       $v0, .L8003C76C
/* 2CF64 8003C764 80FF0224 */   addiu     $v0, $zero, -0x80
/* 2CF68 8003C768 080082AC */  sw         $v0, 0x8($a0)
.L8003C76C:
/* 2CF6C 8003C76C 1400028E */  lw         $v0, 0x14($s0)
/* 2CF70 8003C770 0800838C */  lw         $v1, 0x8($a0)
/* 2CF74 8003C774 00000000 */  nop
/* 2CF78 8003C778 21104300 */  addu       $v0, $v0, $v1
/* 2CF7C 8003C77C 140002AE */  sw         $v0, 0x14($s0)
/* 2CF80 8003C780 44000292 */  lbu        $v0, 0x44($s0)
/* 2CF84 8003C784 10008390 */  lbu        $v1, 0x10($a0)
/* 2CF88 8003C788 00000000 */  nop
/* 2CF8C 8003C78C 21104300 */  addu       $v0, $v0, $v1
/* 2CF90 8003C790 440002A2 */  sb         $v0, 0x44($s0)
/* 2CF94 8003C794 45000292 */  lbu        $v0, 0x45($s0)
/* 2CF98 8003C798 11008390 */  lbu        $v1, 0x11($a0)
/* 2CF9C 8003C79C 00000000 */  nop
/* 2CFA0 8003C7A0 21104300 */  addu       $v0, $v0, $v1
/* 2CFA4 8003C7A4 450002A2 */  sb         $v0, 0x45($s0)
/* 2CFA8 8003C7A8 46000292 */  lbu        $v0, 0x46($s0)
/* 2CFAC 8003C7AC 12008390 */  lbu        $v1, 0x12($a0)
/* 2CFB0 8003C7B0 00000000 */  nop
/* 2CFB4 8003C7B4 21104300 */  addu       $v0, $v0, $v1
/* 2CFB8 8003C7B8 460002A2 */  sb         $v0, 0x46($s0)
/* 2CFBC 8003C7BC 13008290 */  lbu        $v0, 0x13($a0)
/* 2CFC0 8003C7C0 00000000 */  nop
/* 2CFC4 8003C7C4 FFFF4224 */  addiu      $v0, $v0, -0x1
/* 2CFC8 8003C7C8 130082A0 */  sb         $v0, 0x13($a0)
/* 2CFCC 8003C7CC 01004230 */  andi       $v0, $v0, 0x1
/* 2CFD0 8003C7D0 1D004014 */  bnez       $v0, .L8003C848
/* 2CFD4 8003C7D4 00000000 */   nop
/* 2CFD8 8003C7D8 CB89010C */  jal        rand
/* 2CFDC 8003C7DC 00000000 */   nop
/* 2CFE0 8003C7E0 03004230 */  andi       $v0, $v0, 0x3
/* 2CFE4 8003C7E4 CB89010C */  jal        rand
/* 2CFE8 8003C7E8 1000A2AF */   sw        $v0, 0x10($sp)
/* 2CFEC 8003C7EC 01000424 */  addiu      $a0, $zero, 0x1
/* 2CFF0 8003C7F0 01000524 */  addiu      $a1, $zero, 0x1
/* 2CFF4 8003C7F4 0C000626 */  addiu      $a2, $s0, 0xC
/* 2CFF8 8003C7F8 1000A727 */  addiu      $a3, $sp, 0x10
/* 2CFFC 8003C7FC 0780033C */  lui        $v1, %hi(D_800758E4)
/* 2D000 8003C800 E458638C */  lw         $v1, %lo(D_800758E4)($v1)
/* 2D004 8003C804 03004230 */  andi       $v0, $v0, 0x3
/* 2D008 8003C808 1400A2AF */  sw         $v0, 0x14($sp)
/* 2D00C 8003C80C 14000224 */  addiu      $v0, $zero, 0x14
/* 2D010 8003C810 09F86000 */  jalr       $v1
/* 2D014 8003C814 1800A2AF */   sw        $v0, 0x18($sp)
/* 2D018 8003C818 12F20008 */  j          .L8003C848
/* 2D01C 8003C81C 00000000 */   nop
.L8003C820:
/* 2D020 8003C820 03000424 */  addiu      $a0, $zero, 0x3
/* 2D024 8003C824 46000524 */  addiu      $a1, $zero, 0x46
/* 2D028 8003C828 0C000626 */  addiu      $a2, $s0, 0xC
/* 2D02C 8003C82C 0780023C */  lui        $v0, %hi(D_800758E4)
/* 2D030 8003C830 E458428C */  lw         $v0, %lo(D_800758E4)($v0)
/* 2D034 8003C834 00000000 */  nop
/* 2D038 8003C838 09F84000 */  jalr       $v0
/* 2D03C 8003C83C 10000724 */   addiu     $a3, $zero, 0x10
/* 2D040 8003C840 5A49010C */  jal        func_80052568
/* 2D044 8003C844 21200002 */   addu      $a0, $s0, $zero
.L8003C848:
/* 2D048 8003C848 2400BF8F */  lw         $ra, 0x24($sp)
/* 2D04C 8003C84C 2000B08F */  lw         $s0, 0x20($sp)
/* 2D050 8003C850 2800BD27 */  addiu      $sp, $sp, 0x28
/* 2D054 8003C854 0800E003 */  jr         $ra
/* 2D058 8003C858 00000000 */   nop
.size func_8003C6E4, . - func_8003C6E4
