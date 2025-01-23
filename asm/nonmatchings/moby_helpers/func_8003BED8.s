.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003BED8
/* 2C6D8 8003BED8 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 2C6DC 8003BEDC 5000B2AF */  sw         $s2, 0x50($sp)
/* 2C6E0 8003BEE0 21908000 */  addu       $s2, $a0, $zero
/* 2C6E4 8003BEE4 5400BFAF */  sw         $ra, 0x54($sp)
/* 2C6E8 8003BEE8 4C00B1AF */  sw         $s1, 0x4C($sp)
/* 2C6EC 8003BEEC 4800B0AF */  sw         $s0, 0x48($sp)
/* 2C6F0 8003BEF0 46004292 */  lbu        $v0, 0x46($s2)
/* 2C6F4 8003BEF4 00000000 */  nop
/* 2C6F8 8003BEF8 16004010 */  beqz       $v0, .L8003BF54
/* 2C6FC 8003BEFC 0F001124 */   addiu     $s1, $zero, 0xF
/* 2C700 8003BF00 3000A427 */  addiu      $a0, $sp, 0x30
/* 2C704 8003BF04 1000A527 */  addiu      $a1, $sp, 0x10
/* 2C708 8003BF08 3000A0A3 */  sb         $zero, 0x30($sp)
/* 2C70C 8003BF0C 3100A0A3 */  sb         $zero, 0x31($sp)
/* 2C710 8003BF10 46004292 */  lbu        $v0, 0x46($s2)
/* 2C714 8003BF14 21300000 */  addu       $a2, $zero, $zero
/* 2C718 8003BF18 23100200 */  negu       $v0, $v0
/* 2C71C 8003BF1C 4B5B000C */  jal        func_80016D2C
/* 2C720 8003BF20 3200A2A3 */   sb        $v0, 0x32($sp)
/* 2C724 8003BF24 3800B027 */  addiu      $s0, $sp, 0x38
/* 2C728 8003BF28 21200002 */  addu       $a0, $s0, $zero
/* 2C72C 8003BF2C 0880063C */  lui        $a2, %hi(g_Spyro)
/* 2C730 8003BF30 588AC624 */  addiu      $a2, $a2, %lo(g_Spyro)
/* 2C734 8003BF34 E35D000C */  jal        VecSub
/* 2C738 8003BF38 0C004526 */   addiu     $a1, $s2, 0xC
/* 2C73C 8003BF3C 1000A427 */  addiu      $a0, $sp, 0x10
/* 2C740 8003BF40 21280002 */  addu       $a1, $s0, $zero
/* 2C744 8003BF44 125C000C */  jal        func_80017048
/* 2C748 8003BF48 2130A000 */   addu      $a2, $a1, $zero
/* 2C74C 8003BF4C DAEF0008 */  j          .L8003BF68
/* 2C750 8003BF50 00000000 */   nop
.L8003BF54:
/* 2C754 8003BF54 3800A427 */  addiu      $a0, $sp, 0x38
/* 2C758 8003BF58 0880063C */  lui        $a2, %hi(g_Spyro)
/* 2C75C 8003BF5C 588AC624 */  addiu      $a2, $a2, %lo(g_Spyro)
/* 2C760 8003BF60 E35D000C */  jal        VecSub
/* 2C764 8003BF64 0C004526 */   addiu     $a1, $s2, 0xC
.L8003BF68:
/* 2C768 8003BF68 3800A28F */  lw         $v0, 0x38($sp)
/* 2C76C 8003BF6C 00000000 */  nop
/* 2C770 8003BF70 03004018 */  blez       $v0, .L8003BF80
/* 2C774 8003BF74 00000000 */   nop
/* 2C778 8003BF78 E1EF0008 */  j          .L8003BF84
/* 2C77C 8003BF7C 06003132 */   andi      $s1, $s1, 0x6
.L8003BF80:
/* 2C780 8003BF80 09003132 */  andi       $s1, $s1, 0x9
.L8003BF84:
/* 2C784 8003BF84 3C00A28F */  lw         $v0, 0x3C($sp)
/* 2C788 8003BF88 00000000 */  nop
/* 2C78C 8003BF8C 03004018 */  blez       $v0, .L8003BF9C
/* 2C790 8003BF90 00000000 */   nop
/* 2C794 8003BF94 E8EF0008 */  j          .L8003BFA0
/* 2C798 8003BF98 03003132 */   andi      $s1, $s1, 0x3
.L8003BF9C:
/* 2C79C 8003BF9C 0C003132 */  andi       $s1, $s1, 0xC
.L8003BFA0:
/* 2C7A0 8003BFA0 21102002 */  addu       $v0, $s1, $zero
/* 2C7A4 8003BFA4 5400BF8F */  lw         $ra, 0x54($sp)
/* 2C7A8 8003BFA8 5000B28F */  lw         $s2, 0x50($sp)
/* 2C7AC 8003BFAC 4C00B18F */  lw         $s1, 0x4C($sp)
/* 2C7B0 8003BFB0 4800B08F */  lw         $s0, 0x48($sp)
/* 2C7B4 8003BFB4 5800BD27 */  addiu      $sp, $sp, 0x58
/* 2C7B8 8003BFB8 0800E003 */  jr         $ra
/* 2C7BC 8003BFBC 00000000 */   nop
.size func_8003BED8, . - func_8003BED8
