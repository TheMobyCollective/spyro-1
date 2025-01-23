.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003D3B8
/* 2DBB8 8003D3B8 0780053C */  lui        $a1, %hi(D_800757E0)
/* 2DBBC 8003D3BC E057A58C */  lw         $a1, %lo(D_800757E0)($a1)
/* 2DBC0 8003D3C0 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 2DBC4 8003D3C4 1800BFAF */  sw         $ra, 0x18($sp)
/* 2DBC8 8003D3C8 1400B1AF */  sw         $s1, 0x14($sp)
/* 2DBCC 8003D3CC 1000B0AF */  sw         $s0, 0x10($sp)
/* 2DBD0 8003D3D0 1000A28C */  lw         $v0, 0x10($a1)
/* 2DBD4 8003D3D4 00000000 */  nop
/* 2DBD8 8003D3D8 2E004010 */  beqz       $v0, .L8003D494
/* 2DBDC 8003D3DC 21888000 */   addu      $s1, $a0, $zero
/* 2DBE0 8003D3E0 1400A28C */  lw         $v0, 0x14($a1)
/* 2DBE4 8003D3E4 FFFF033C */  lui        $v1, (0xFFFF0000 >> 16)
/* 2DBE8 8003D3E8 24104300 */  and        $v0, $v0, $v1
/* 2DBEC 8003D3EC 7F7F033C */  lui        $v1, (0x7F7F0000 >> 16)
/* 2DBF0 8003D3F0 28004310 */  beq        $v0, $v1, .L8003D494
/* 2DBF4 8003D3F4 7F001024 */   addiu     $s0, $zero, 0x7F
/* 2DBF8 8003D3F8 01000624 */  addiu      $a2, $zero, 0x1
/* 2DBFC 8003D3FC 1700A490 */  lbu        $a0, 0x17($a1)
/* 2DC00 8003D400 1600A590 */  lbu        $a1, 0x16($a1)
/* 2DC04 8003D404 23200402 */  subu       $a0, $s0, $a0
/* 2DC08 8003D408 AD5A000C */  jal        func_80016AB4
/* 2DC0C 8003D40C 23280502 */   subu      $a1, $s0, $a1
/* 2DC10 8003D410 0780033C */  lui        $v1, %hi(g_Camera + 0x50)
/* 2DC14 8003D414 206E6384 */  lh         $v1, %lo(g_Camera + 0x50)($v1)
/* 2DC18 8003D418 0880043C */  lui        $a0, %hi(g_Spyro + 0xCC)
/* 2DC1C 8003D41C 248B8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0xCC)
/* 2DC20 8003D420 000082AC */  sw         $v0, 0x0($a0)
/* 2DC24 8003D424 21104300 */  addu       $v0, $v0, $v1
/* 2DC28 8003D428 0780033C */  lui        $v1, %hi(D_800757E0)
/* 2DC2C 8003D42C E057638C */  lw         $v1, %lo(D_800757E0)($v1)
/* 2DC30 8003D430 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 2DC34 8003D434 000082AC */  sw         $v0, 0x0($a0)
/* 2DC38 8003D438 17006290 */  lbu        $v0, 0x17($v1)
/* 2DC3C 8003D43C 16006390 */  lbu        $v1, 0x16($v1)
/* 2DC40 8003D440 23100202 */  subu       $v0, $s0, $v0
/* 2DC44 8003D444 02004104 */  bgez       $v0, .L8003D450
/* 2DC48 8003D448 00000000 */   nop
/* 2DC4C 8003D44C 23100200 */  negu       $v0, $v0
.L8003D450:
/* 2DC50 8003D450 23800302 */  subu       $s0, $s0, $v1
/* 2DC54 8003D454 02000106 */  bgez       $s0, .L8003D460
/* 2DC58 8003D458 00000000 */   nop
/* 2DC5C 8003D45C 23801000 */  negu       $s0, $s0
.L8003D460:
/* 2DC60 8003D460 21105000 */  addu       $v0, $v0, $s0
/* 2DC64 8003D464 18002202 */  mult       $s1, $v0
/* 2DC68 8003D468 12380000 */  mflo       $a3
/* 2DC6C 8003D46C C3110700 */  sra        $v0, $a3, 7
/* 2DC70 8003D470 0880013C */  lui        $at, %hi(g_Spyro + 0xC8)
/* 2DC74 8003D474 208B22AC */  sw         $v0, %lo(g_Spyro + 0xC8)($at)
/* 2DC78 8003D478 2A102202 */  slt        $v0, $s1, $v0
/* 2DC7C 8003D47C 25004010 */  beqz       $v0, .L8003D514
/* 2DC80 8003D480 00000000 */   nop
/* 2DC84 8003D484 0880013C */  lui        $at, %hi(g_Spyro + 0xC8)
/* 2DC88 8003D488 208B31AC */  sw         $s1, %lo(g_Spyro + 0xC8)($at)
/* 2DC8C 8003D48C 45F50008 */  j          .L8003D514
/* 2DC90 8003D490 00000000 */   nop
.L8003D494:
/* 2DC94 8003D494 0780033C */  lui        $v1, %hi(D_800757E0)
/* 2DC98 8003D498 E057638C */  lw         $v1, %lo(D_800757E0)($v1)
/* 2DC9C 8003D49C 00000000 */  nop
/* 2DCA0 8003D4A0 0400628C */  lw         $v0, 0x4($v1)
/* 2DCA4 8003D4A4 00000000 */  nop
/* 2DCA8 8003D4A8 00F04230 */  andi       $v0, $v0, 0xF000
/* 2DCAC 8003D4AC 10004010 */  beqz       $v0, .L8003D4F0
/* 2DCB0 8003D4B0 00000000 */   nop
/* 2DCB4 8003D4B4 0880013C */  lui        $at, %hi(g_Spyro + 0xC8)
/* 2DCB8 8003D4B8 208B31AC */  sw         $s1, %lo(g_Spyro + 0xC8)($at)
/* 2DCBC 8003D4BC 0400628C */  lw         $v0, 0x4($v1)
/* 2DCC0 8003D4C0 0780033C */  lui        $v1, %hi(g_Camera + 0x50)
/* 2DCC4 8003D4C4 206E6384 */  lh         $v1, %lo(g_Camera + 0x50)($v1)
/* 2DCC8 8003D4C8 C3120200 */  sra        $v0, $v0, 11
/* 2DCCC 8003D4CC 1E004230 */  andi       $v0, $v0, 0x1E
/* 2DCD0 8003D4D0 0780013C */  lui        $at, %hi(D_8006C5D0)
/* 2DCD4 8003D4D4 21082200 */  addu       $at, $at, $v0
/* 2DCD8 8003D4D8 D0C52284 */  lh         $v0, %lo(D_8006C5D0)($at)
/* 2DCDC 8003D4DC 0880013C */  lui        $at, %hi(g_Spyro + 0xCC)
/* 2DCE0 8003D4E0 248B22AC */  sw         $v0, %lo(g_Spyro + 0xCC)($at)
/* 2DCE4 8003D4E4 21104300 */  addu       $v0, $v0, $v1
/* 2DCE8 8003D4E8 43F50008 */  j          .L8003D50C
/* 2DCEC 8003D4EC FF0F4230 */   andi      $v0, $v0, 0xFFF
.L8003D4F0:
/* 2DCF0 8003D4F0 0880023C */  lui        $v0, %hi(g_Spyro + 0xE)
/* 2DCF4 8003D4F4 668A4290 */  lbu        $v0, %lo(g_Spyro + 0xE)($v0)
/* 2DCF8 8003D4F8 0880013C */  lui        $at, %hi(g_Spyro + 0xC8)
/* 2DCFC 8003D4FC 208B20AC */  sw         $zero, %lo(g_Spyro + 0xC8)($at)
/* 2DD00 8003D500 0880013C */  lui        $at, %hi(g_Spyro + 0x148)
/* 2DD04 8003D504 A08B20AC */  sw         $zero, %lo(g_Spyro + 0x148)($at)
/* 2DD08 8003D508 00110200 */  sll        $v0, $v0, 4
.L8003D50C:
/* 2DD0C 8003D50C 0880013C */  lui        $at, %hi(g_Spyro + 0xCC)
/* 2DD10 8003D510 248B22AC */  sw         $v0, %lo(g_Spyro + 0xCC)($at)
.L8003D514:
/* 2DD14 8003D514 1800BF8F */  lw         $ra, 0x18($sp)
/* 2DD18 8003D518 1400B18F */  lw         $s1, 0x14($sp)
/* 2DD1C 8003D51C 1000B08F */  lw         $s0, 0x10($sp)
/* 2DD20 8003D520 2000BD27 */  addiu      $sp, $sp, 0x20
/* 2DD24 8003D524 0800E003 */  jr         $ra
/* 2DD28 8003D528 00000000 */   nop
.size func_8003D3B8, . - func_8003D3B8
