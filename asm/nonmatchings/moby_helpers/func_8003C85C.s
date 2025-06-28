.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003C85C
/* 2D05C 8003C85C B0FFBD27 */  addiu      $sp, $sp, -0x50
/* 2D060 8003C860 4800B2AF */  sw         $s2, 0x48($sp)
/* 2D064 8003C864 21908000 */  addu       $s2, $a0, $zero
/* 2D068 8003C868 4400B1AF */  sw         $s1, 0x44($sp)
/* 2D06C 8003C86C 0880113C */  lui        $s1, %hi(g_Spyro + 0x34)
/* 2D070 8003C870 8C8A3126 */  addiu      $s1, $s1, %lo(g_Spyro + 0x34)
/* 2D074 8003C874 21202002 */  addu       $a0, $s1, $zero
/* 2D078 8003C878 4000B0AF */  sw         $s0, 0x40($sp)
/* 2D07C 8003C87C 3000B027 */  addiu      $s0, $sp, 0x30
/* 2D080 8003C880 21280002 */  addu       $a1, $s0, $zero
/* 2D084 8003C884 21300002 */  addu       $a2, $s0, $zero
/* 2D088 8003C888 64000224 */  addiu      $v0, $zero, 0x64
/* 2D08C 8003C88C 3000A2AF */  sw         $v0, 0x30($sp)
/* 2D090 8003C890 40000224 */  addiu      $v0, $zero, 0x40
/* 2D094 8003C894 4C00BFAF */  sw         $ra, 0x4C($sp)
/* 2D098 8003C898 3400A0AF */  sw         $zero, 0x34($sp)
/* 2D09C 8003C89C 125C000C */  jal        VecRotateByMatrix
/* 2D0A0 8003C8A0 3800A2AF */   sw        $v0, 0x38($sp)
/* 2D0A4 8003C8A4 21200002 */  addu       $a0, $s0, $zero
/* 2D0A8 8003C8A8 21280002 */  addu       $a1, $s0, $zero
/* 2D0AC 8003C8AC D65D000C */  jal        VecAdd
/* 2D0B0 8003C8B0 CCFF2626 */   addiu     $a2, $s1, -0x34
/* 2D0B4 8003C8B4 21200002 */  addu       $a0, $s0, $zero
/* 2D0B8 8003C8B8 21284002 */  addu       $a1, $s2, $zero
/* 2D0BC 8003C8BC E35D000C */  jal        VecSub
/* 2D0C0 8003C8C0 21300002 */   addu      $a2, $s0, $zero
/* 2D0C4 8003C8C4 1000A427 */  addiu      $a0, $sp, 0x10
/* 2D0C8 8003C8C8 F45B000C */  jal        func_80016FD0
/* 2D0CC 8003C8CC 21282002 */   addu      $a1, $s1, $zero
/* 2D0D0 8003C8D0 1000A427 */  addiu      $a0, $sp, 0x10
/* 2D0D4 8003C8D4 21280002 */  addu       $a1, $s0, $zero
/* 2D0D8 8003C8D8 125C000C */  jal        VecRotateByMatrix
/* 2D0DC 8003C8DC 21300002 */   addu      $a2, $s0, $zero
/* 2D0E0 8003C8E0 21200002 */  addu       $a0, $s0, $zero
/* 2D0E4 8003C8E4 7F5C000C */  jal        VecMagnitude
/* 2D0E8 8003C8E8 21280000 */   addu      $a1, $zero, $zero
/* 2D0EC 8003C8EC 21204000 */  addu       $a0, $v0, $zero
/* 2D0F0 8003C8F0 3800A58F */  lw         $a1, 0x38($sp)
/* 2D0F4 8003C8F4 AD5A000C */  jal        func_80016AB4
/* 2D0F8 8003C8F8 01000624 */   addiu     $a2, $zero, 0x1
/* 2D0FC 8003C8FC 21184000 */  addu       $v1, $v0, $zero
/* 2D100 8003C900 7FFE6224 */  addiu      $v0, $v1, -0x181
/* 2D104 8003C904 7F06422C */  sltiu      $v0, $v0, 0x67F
/* 2D108 8003C908 0880013C */  lui        $at, %hi(g_Spyro + 0x1A8)
/* 2D10C 8003C90C 008C23AC */  sw         $v1, %lo(g_Spyro + 0x1A8)($at)
/* 2D110 8003C910 05004014 */  bnez       $v0, .L8003C928
/* 2D114 8003C914 80010224 */   addiu     $v0, $zero, 0x180
/* 2D118 8003C918 00F86224 */  addiu      $v0, $v1, -0x800
/* 2D11C 8003C91C 8006422C */  sltiu      $v0, $v0, 0x680
/* 2D120 8003C920 03004010 */  beqz       $v0, .L8003C930
/* 2D124 8003C924 800E0224 */   addiu     $v0, $zero, 0xE80
.L8003C928:
/* 2D128 8003C928 0880013C */  lui        $at, %hi(g_Spyro + 0x1A8)
/* 2D12C 8003C92C 008C22AC */  sw         $v0, %lo(g_Spyro + 0x1A8)($at)
.L8003C930:
/* 2D130 8003C930 3000A48F */  lw         $a0, 0x30($sp)
/* 2D134 8003C934 3400A58F */  lw         $a1, 0x34($sp)
/* 2D138 8003C938 AD5A000C */  jal        func_80016AB4
/* 2D13C 8003C93C 01000624 */   addiu     $a2, $zero, 0x1
/* 2D140 8003C940 21184000 */  addu       $v1, $v0, $zero
/* 2D144 8003C944 0880043C */  lui        $a0, %hi(g_Spyro + 0x1AC)
/* 2D148 8003C948 048C8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0x1AC)
/* 2D14C 8003C94C FFFD6224 */  addiu      $v0, $v1, -0x201
/* 2D150 8003C950 FF05422C */  sltiu      $v0, $v0, 0x5FF
/* 2D154 8003C954 03004010 */  beqz       $v0, .L8003C964
/* 2D158 8003C958 000083AC */   sw        $v1, 0x0($a0)
/* 2D15C 8003C95C 5DF20008 */  j          .L8003C974
/* 2D160 8003C960 00020224 */   addiu     $v0, $zero, 0x200
.L8003C964:
/* 2D164 8003C964 00F86224 */  addiu      $v0, $v1, -0x800
/* 2D168 8003C968 0006422C */  sltiu      $v0, $v0, 0x600
/* 2D16C 8003C96C 02004010 */  beqz       $v0, .L8003C978
/* 2D170 8003C970 000E0224 */   addiu     $v0, $zero, 0xE00
.L8003C974:
/* 2D174 8003C974 000082AC */  sw         $v0, 0x0($a0)
.L8003C978:
/* 2D178 8003C978 4C00BF8F */  lw         $ra, 0x4C($sp)
/* 2D17C 8003C97C 4800B28F */  lw         $s2, 0x48($sp)
/* 2D180 8003C980 4400B18F */  lw         $s1, 0x44($sp)
/* 2D184 8003C984 4000B08F */  lw         $s0, 0x40($sp)
/* 2D188 8003C988 5000BD27 */  addiu      $sp, $sp, 0x50
/* 2D18C 8003C98C 0800E003 */  jr         $ra
/* 2D190 8003C990 00000000 */   nop
.size func_8003C85C, . - func_8003C85C
