.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002D440
/* 1DC40 8002D440 0780033C */  lui        $v1, %hi(D_8007566C)
/* 1DC44 8002D444 6C56638C */  lw         $v1, %lo(D_8007566C)($v1)
/* 1DC48 8002D448 D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 1DC4C 8002D44C 1C00B1AF */  sw         $s1, 0x1C($sp)
/* 1DC50 8002D450 01001124 */  addiu      $s1, $zero, 0x1
/* 1DC54 8002D454 2000BFAF */  sw         $ra, 0x20($sp)
/* 1DC58 8002D458 2A007114 */  bne        $v1, $s1, .L8002D504
/* 1DC5C 8002D45C 1800B0AF */   sw        $s0, 0x18($sp)
/* 1DC60 8002D460 1000A427 */  addiu      $a0, $sp, 0x10
/* 1DC64 8002D464 21280000 */  addu       $a1, $zero, $zero
/* 1DC68 8002D468 21300000 */  addu       $a2, $zero, $zero
/* 1DC6C 8002D46C 00020224 */  addiu      $v0, $zero, 0x200
/* 1DC70 8002D470 1400A2A7 */  sh         $v0, 0x14($sp)
/* 1DC74 8002D474 E0010224 */  addiu      $v0, $zero, 0x1E0
/* 1DC78 8002D478 21380000 */  addu       $a3, $zero, $zero
/* 1DC7C 8002D47C 1000A0A7 */  sh         $zero, 0x10($sp)
/* 1DC80 8002D480 1200A0A7 */  sh         $zero, 0x12($sp)
/* 1DC84 8002D484 3E7E010C */  jal        ClearImage
/* 1DC88 8002D488 1600A2A7 */   sh        $v0, 0x16($sp)
/* 1DC8C 8002D48C D97D010C */  jal        DrawSync
/* 1DC90 8002D490 21200000 */   addu      $a0, $zero, $zero
/* 1DC94 8002D494 CA5A010C */  jal        func_80056B28
/* 1DC98 8002D498 21200000 */   addu      $a0, $zero, $zero
/* 1DC9C 8002D49C B55B010C */  jal        SpuUpdate
/* 1DCA0 8002D4A0 00000000 */   nop
/* 1DCA4 8002D4A4 F66D010C */  jal        func_8005B7D8
/* 1DCA8 8002D4A8 00000000 */   nop
/* 1DCAC 8002D4AC 0880103C */  lui        $s0, %hi(D_80078D78)
/* 1DCB0 8002D4B0 788D1026 */  addiu      $s0, $s0, %lo(D_80078D78)
/* 1DCB4 8002D4B4 21200002 */  addu       $a0, $s0, $zero
/* 1DCB8 8002D4B8 21280000 */  addu       $a1, $zero, $zero
/* 1DCBC 8002D4BC 0D000224 */  addiu      $v0, $zero, 0xD
/* 1DCC0 8002D4C0 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1DCC4 8002D4C4 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1DCC8 8002D4C8 455A000C */  jal        Memset
/* 1DCCC 8002D4CC 5C000624 */   addiu     $a2, $zero, 0x5C
/* 1DCD0 8002D4D0 03000224 */  addiu      $v0, $zero, 0x3
/* 1DCD4 8002D4D4 000002AE */  sw         $v0, 0x0($s0)
/* 1DCD8 8002D4D8 0880013C */  lui        $at, %hi(D_80078D78 + 0x4)
/* 1DCDC 8002D4DC 7C8D20AC */  sw         $zero, %lo(D_80078D78 + 0x4)($at)
/* 1DCE0 8002D4E0 0880013C */  lui        $at, %hi(D_80078D78 + 0x1C)
/* 1DCE4 8002D4E4 948D31AC */  sw         $s1, %lo(D_80078D78 + 0x1C)($at)
/* 1DCE8 8002D4E8 DF49000C */  jal        func_8001277C
/* 1DCEC 8002D4EC 00000000 */   nop
/* 1DCF0 8002D4F0 0A000224 */  addiu      $v0, $zero, 0xA
/* 1DCF4 8002D4F4 0780013C */  lui        $at, %hi(g_LevelId)
/* 1DCF8 8002D4F8 6C5922AC */  sw         $v0, %lo(g_LevelId)($at)
/* 1DCFC 8002D4FC 4DB50008 */  j          .L8002D534
/* 1DD00 8002D500 00000000 */   nop
.L8002D504:
/* 1DD04 8002D504 02000224 */  addiu      $v0, $zero, 0x2
/* 1DD08 8002D508 03006214 */  bne        $v1, $v0, .L8002D518
/* 1DD0C 8002D50C 03000224 */   addiu     $v0, $zero, 0x3
/* 1DD10 8002D510 4BB50008 */  j          .L8002D52C
/* 1DD14 8002D514 21200000 */   addu      $a0, $zero, $zero
.L8002D518:
/* 1DD18 8002D518 08006214 */  bne        $v1, $v0, .L8002D53C
/* 1DD1C 8002D51C 01000424 */   addiu     $a0, $zero, 0x1
/* 1DD20 8002D520 0A000224 */  addiu      $v0, $zero, 0xA
/* 1DD24 8002D524 0780013C */  lui        $at, %hi(D_800757AC)
/* 1DD28 8002D528 AC5722AC */  sw         $v0, %lo(D_800757AC)($at)
.L8002D52C:
/* 1DD2C 8002D52C 8AB4000C */  jal        func_8002D228
/* 1DD30 8002D530 00000000 */   nop
.L8002D534:
/* 1DD34 8002D534 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 1DD38 8002D538 9C5731AC */  sw         $s1, %lo(g_StateSwitch)($at)
.L8002D53C:
/* 1DD3C 8002D53C 2000BF8F */  lw         $ra, 0x20($sp)
/* 1DD40 8002D540 1C00B18F */  lw         $s1, 0x1C($sp)
/* 1DD44 8002D544 1800B08F */  lw         $s0, 0x18($sp)
/* 1DD48 8002D548 2800BD27 */  addiu      $sp, $sp, 0x28
/* 1DD4C 8002D54C 0800E003 */  jr         $ra
/* 1DD50 8002D550 00000000 */   nop
.size func_8002D440, . - func_8002D440
