.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003E758
/* 2EF58 8003E758 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 2EF5C 8003E75C 4400B1AF */  sw         $s1, 0x44($sp)
/* 2EF60 8003E760 3000B127 */  addiu      $s1, $sp, 0x30
/* 2EF64 8003E764 21202002 */  addu       $a0, $s1, $zero
/* 2EF68 8003E768 1000A527 */  addiu      $a1, $sp, 0x10
/* 2EF6C 8003E76C 9CFE0224 */  addiu      $v0, $zero, -0x164
/* 2EF70 8003E770 5000BFAF */  sw         $ra, 0x50($sp)
/* 2EF74 8003E774 4C00B3AF */  sw         $s3, 0x4C($sp)
/* 2EF78 8003E778 4800B2AF */  sw         $s2, 0x48($sp)
/* 2EF7C 8003E77C 4000B0AF */  sw         $s0, 0x40($sp)
/* 2EF80 8003E780 1000A0AF */  sw         $zero, 0x10($sp)
/* 2EF84 8003E784 1400A0AF */  sw         $zero, 0x14($sp)
/* 2EF88 8003E788 C05D000C */  jal        VecCopy
/* 2EF8C 8003E78C 1800A2AF */   sw        $v0, 0x18($sp)
/* 2EF90 8003E790 2000B027 */  addiu      $s0, $sp, 0x20
/* 2EF94 8003E794 21200002 */  addu       $a0, $s0, $zero
/* 2EF98 8003E798 3800A28F */  lw         $v0, 0x38($sp)
/* 2EF9C 8003E79C 1000A527 */  addiu      $a1, $sp, 0x10
/* 2EFA0 8003E7A0 80FF4224 */  addiu      $v0, $v0, -0x80
/* 2EFA4 8003E7A4 C05D000C */  jal        VecCopy
/* 2EFA8 8003E7A8 3800A2AF */   sw        $v0, 0x38($sp)
/* 2EFAC 8003E7AC 0880133C */  lui        $s3, %hi(g_Spyro + 0x34)
/* 2EFB0 8003E7B0 8C8A7326 */  addiu      $s3, $s3, %lo(g_Spyro + 0x34)
/* 2EFB4 8003E7B4 21206002 */  addu       $a0, $s3, $zero
/* 2EFB8 8003E7B8 21282002 */  addu       $a1, $s1, $zero
/* 2EFBC 8003E7BC 2800A28F */  lw         $v0, 0x28($sp)
/* 2EFC0 8003E7C0 21302002 */  addu       $a2, $s1, $zero
/* 2EFC4 8003E7C4 80004224 */  addiu      $v0, $v0, 0x80
/* 2EFC8 8003E7C8 125C000C */  jal        VecRotateByMatrix
/* 2EFCC 8003E7CC 2800A2AF */   sw        $v0, 0x28($sp)
/* 2EFD0 8003E7D0 21202002 */  addu       $a0, $s1, $zero
/* 2EFD4 8003E7D4 CCFF7226 */  addiu      $s2, $s3, -0x34
/* 2EFD8 8003E7D8 21284002 */  addu       $a1, $s2, $zero
/* 2EFDC 8003E7DC D65D000C */  jal        VecAdd
/* 2EFE0 8003E7E0 21302002 */   addu      $a2, $s1, $zero
/* 2EFE4 8003E7E4 21200002 */  addu       $a0, $s0, $zero
/* 2EFE8 8003E7E8 305C000C */  jal        func_800170C0
/* 2EFEC 8003E7EC 21280002 */   addu      $a1, $s0, $zero
/* 2EFF0 8003E7F0 21200002 */  addu       $a0, $s0, $zero
/* 2EFF4 8003E7F4 21284002 */  addu       $a1, $s2, $zero
/* 2EFF8 8003E7F8 D65D000C */  jal        VecAdd
/* 2EFFC 8003E7FC 21300002 */   addu      $a2, $s0, $zero
/* 2F000 8003E800 1000A427 */  addiu      $a0, $sp, 0x10
/* 2F004 8003E804 305C000C */  jal        func_800170C0
/* 2F008 8003E808 21288000 */   addu      $a1, $a0, $zero
/* 2F00C 8003E80C 1000A427 */  addiu      $a0, $sp, 0x10
/* 2F010 8003E810 21284002 */  addu       $a1, $s2, $zero
/* 2F014 8003E814 D65D000C */  jal        VecAdd
/* 2F018 8003E818 21308000 */   addu      $a2, $a0, $zero
/* 2F01C 8003E81C 21200002 */  addu       $a0, $s0, $zero
/* 2F020 8003E820 8E2B010C */  jal        func_8004AE38
/* 2F024 8003E824 21282002 */   addu      $a1, $s1, $zero
/* 2F028 8003E828 2A004010 */  beqz       $v0, .L8003E8D4
/* 2F02C 8003E82C 00000000 */   nop
/* 2F030 8003E830 0780023C */  lui        $v0, %hi(D_80077370)
/* 2F034 8003E834 7073428C */  lw         $v0, %lo(D_80077370)($v0)
/* 2F038 8003E838 00000000 */  nop
/* 2F03C 8003E83C 25004018 */  blez       $v0, .L8003E8D4
/* 2F040 8003E840 1000A427 */   addiu     $a0, $sp, 0x10
/* 2F044 8003E844 0780053C */  lui        $a1, %hi(D_80076B80)
/* 2F048 8003E848 806BA524 */  addiu      $a1, $a1, %lo(D_80076B80)
/* 2F04C 8003E84C E35D000C */  jal        VecSub
/* 2F050 8003E850 21308000 */   addu      $a2, $a0, $zero
/* 2F054 8003E854 1000A28F */  lw         $v0, 0x10($sp)
/* 2F058 8003E858 00000000 */  nop
/* 2F05C 8003E85C 02004104 */  bgez       $v0, .L8003E868
/* 2F060 8003E860 00000000 */   nop
/* 2F064 8003E864 23100200 */  negu       $v0, $v0
.L8003E868:
/* 2F068 8003E868 08004228 */  slti       $v0, $v0, 0x8
/* 2F06C 8003E86C 02004010 */  beqz       $v0, .L8003E878
/* 2F070 8003E870 00000000 */   nop
/* 2F074 8003E874 1000A0AF */  sw         $zero, 0x10($sp)
.L8003E878:
/* 2F078 8003E878 1400A28F */  lw         $v0, 0x14($sp)
/* 2F07C 8003E87C 00000000 */  nop
/* 2F080 8003E880 02004104 */  bgez       $v0, .L8003E88C
/* 2F084 8003E884 00000000 */   nop
/* 2F088 8003E888 23100200 */  negu       $v0, $v0
.L8003E88C:
/* 2F08C 8003E88C 08004228 */  slti       $v0, $v0, 0x8
/* 2F090 8003E890 02004010 */  beqz       $v0, .L8003E89C
/* 2F094 8003E894 00000000 */   nop
/* 2F098 8003E898 1400A0AF */  sw         $zero, 0x14($sp)
.L8003E89C:
/* 2F09C 8003E89C 1800A28F */  lw         $v0, 0x18($sp)
/* 2F0A0 8003E8A0 00000000 */  nop
/* 2F0A4 8003E8A4 02004104 */  bgez       $v0, .L8003E8B0
/* 2F0A8 8003E8A8 00000000 */   nop
/* 2F0AC 8003E8AC 23100200 */  negu       $v0, $v0
.L8003E8B0:
/* 2F0B0 8003E8B0 08004228 */  slti       $v0, $v0, 0x8
/* 2F0B4 8003E8B4 02004010 */  beqz       $v0, .L8003E8C0
/* 2F0B8 8003E8B8 21204002 */   addu      $a0, $s2, $zero
/* 2F0BC 8003E8BC 1800A0AF */  sw         $zero, 0x18($sp)
.L8003E8C0:
/* 2F0C0 8003E8C0 21288000 */  addu       $a1, $a0, $zero
/* 2F0C4 8003E8C4 D65D000C */  jal        VecAdd
/* 2F0C8 8003E8C8 1000A627 */   addiu     $a2, $sp, 0x10
/* 2F0CC 8003E8CC 3BFA0008 */  j          .L8003E8EC
/* 2F0D0 8003E8D0 680060AE */   sw        $zero, 0x68($s3)
.L8003E8D4:
/* 2F0D4 8003E8D4 0880033C */  lui        $v1, %hi(g_Spyro + 0x9C)
/* 2F0D8 8003E8D8 F48A6324 */  addiu      $v1, $v1, %lo(g_Spyro + 0x9C)
/* 2F0DC 8003E8DC 0000628C */  lw         $v0, 0x0($v1)
/* 2F0E0 8003E8E0 00000000 */  nop
/* 2F0E4 8003E8E4 01004224 */  addiu      $v0, $v0, 0x1
/* 2F0E8 8003E8E8 000062AC */  sw         $v0, 0x0($v1)
.L8003E8EC:
/* 2F0EC 8003E8EC 5000BF8F */  lw         $ra, 0x50($sp)
/* 2F0F0 8003E8F0 4C00B38F */  lw         $s3, 0x4C($sp)
/* 2F0F4 8003E8F4 4800B28F */  lw         $s2, 0x48($sp)
/* 2F0F8 8003E8F8 4400B18F */  lw         $s1, 0x44($sp)
/* 2F0FC 8003E8FC 4000B08F */  lw         $s0, 0x40($sp)
/* 2F100 8003E900 5800BD27 */  addiu      $sp, $sp, 0x58
/* 2F104 8003E904 0800E003 */  jr         $ra
/* 2F108 8003E908 00000000 */   nop
.size func_8003E758, . - func_8003E758
