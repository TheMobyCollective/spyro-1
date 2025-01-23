.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002CB6C
/* 1D36C 8002CB6C 0780023C */  lui        $v0, %hi(D_800770C0)
/* 1D370 8002CB70 C070428C */  lw         $v0, %lo(D_800770C0)($v0)
/* 1D374 8002CB74 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 1D378 8002CB78 1800BFAF */  sw         $ra, 0x18($sp)
/* 1D37C 8002CB7C 1400B1AF */  sw         $s1, 0x14($sp)
/* 1D380 8002CB80 1000B0AF */  sw         $s0, 0x10($sp)
/* 1D384 8002CB84 0000428C */  lw         $v0, 0x0($v0)
/* 1D388 8002CB88 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1D38C 8002CB8C D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 1D390 8002CB90 0780013C */  lui        $at, %hi(D_8007570C)
/* 1D394 8002CB94 0C5720AC */  sw         $zero, %lo(D_8007570C)($at)
/* 1D398 8002CB98 2000438C */  lw         $v1, 0x20($v0)
/* 1D39C 8002CB9C FFFF0224 */  addiu      $v0, $zero, -0x1
/* 1D3A0 8002CBA0 0B006210 */  beq        $v1, $v0, .L8002CBD0
/* 1D3A4 8002CBA4 40100300 */   sll       $v0, $v1, 1
/* 1D3A8 8002CBA8 21104300 */  addu       $v0, $v0, $v1
/* 1D3AC 8002CBAC 80100200 */  sll        $v0, $v0, 2
/* 1D3B0 8002CBB0 23104300 */  subu       $v0, $v0, $v1
/* 1D3B4 8002CBB4 0780033C */  lui        $v1, %hi(D_80075828)
/* 1D3B8 8002CBB8 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 1D3BC 8002CBBC C0100200 */  sll        $v0, $v0, 3
/* 1D3C0 8002CBC0 21186200 */  addu       $v1, $v1, $v0
/* 1D3C4 8002CBC4 01000224 */  addiu      $v0, $zero, 0x1
/* 1D3C8 8002CBC8 3C0060A0 */  sb         $zero, 0x3C($v1)
/* 1D3CC 8002CBCC 480062A0 */  sb         $v0, 0x48($v1)
.L8002CBD0:
/* 1D3D0 8002CBD0 092B010C */  jal        func_8004AC24
/* 1D3D4 8002CBD4 01000424 */   addiu     $a0, $zero, 0x1
/* 1D3D8 8002CBD8 0780113C */  lui        $s1, %hi(g_Camera + 0xD0)
/* 1D3DC 8002CBDC A06E3126 */  addiu      $s1, $s1, %lo(g_Camera + 0xD0)
/* 1D3E0 8002CBE0 0880023C */  lui        $v0, %hi(g_Spyro + 0x1F0)
/* 1D3E4 8002CBE4 488C4224 */  addiu      $v0, $v0, %lo(g_Spyro + 0x1F0)
/* 1D3E8 8002CBE8 0C000324 */  addiu      $v1, $zero, 0xC
/* 1D3EC 8002CBEC 000043AC */  sw         $v1, 0x0($v0)
/* 1D3F0 8002CBF0 10FE4224 */  addiu      $v0, $v0, -0x1F0
/* 1D3F4 8002CBF4 000022AE */  sw         $v0, 0x0($s1)
/* 1D3F8 8002CBF8 0780023C */  lui        $v0, %hi(D_800758A4)
/* 1D3FC 8002CBFC A458428C */  lw         $v0, %lo(D_800758A4)($v0)
/* 1D400 8002CC00 0880033C */  lui        $v1, %hi(g_Spyro + 0x11C)
/* 1D404 8002CC04 748B638C */  lw         $v1, %lo(g_Spyro + 0x11C)($v1)
/* 1D408 8002CC08 0780103C */  lui        $s0, %hi(D_8006C8BC)
/* 1D40C 8002CC0C BCC81026 */  addiu      $s0, $s0, %lo(D_8006C8BC)
/* 1D410 8002CC10 0780013C */  lui        $at, %hi(g_Camera + 0x58)
/* 1D414 8002CC14 286E20AC */  sw         $zero, %lo(g_Camera + 0x58)($at)
/* 1D418 8002CC18 0780013C */  lui        $at, %hi(g_Camera + 0xC0)
/* 1D41C 8002CC1C 906E20AC */  sw         $zero, %lo(g_Camera + 0xC0)($at)
/* 1D420 8002CC20 0780013C */  lui        $at, %hi(g_Camera + 0xD8)
/* 1D424 8002CC24 A86E30AC */  sw         $s0, %lo(g_Camera + 0xD8)($at)
/* 1D428 8002CC28 0880013C */  lui        $at, %hi(D_80078768)
/* 1D42C 8002CC2C 688722AC */  sw         $v0, %lo(D_80078768)($at)
/* 1D430 8002CC30 0780013C */  lui        $at, %hi(g_Camera + 0xD4)
/* 1D434 8002CC34 A46E23AC */  sw         $v1, %lo(g_Camera + 0xD4)($at)
/* 1D438 8002CC38 C2CF000C */  jal        func_80033F08
/* 1D43C 8002CC3C 58FF2426 */   addiu     $a0, $s1, -0xA8
/* 1D440 8002CC40 21200002 */  addu       $a0, $s0, $zero
/* 1D444 8002CC44 C0FF2526 */  addiu      $a1, $s1, -0x40
/* 1D448 8002CC48 565A000C */  jal        Memcpy
/* 1D44C 8002CC4C 18000624 */   addiu     $a2, $zero, 0x18
/* 1D450 8002CC50 0000028E */  lw         $v0, 0x0($s0)
/* 1D454 8002CC54 0780033C */  lui        $v1, %hi(g_Camera + 0xD4)
/* 1D458 8002CC58 A46E638C */  lw         $v1, %lo(g_Camera + 0xD4)($v1)
/* 1D45C 8002CC5C 00000000 */  nop
/* 1D460 8002CC60 21104300 */  addu       $v0, $v0, $v1
/* 1D464 8002CC64 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 1D468 8002CC68 D6D0000C */  jal        func_80034358
/* 1D46C 8002CC6C 000002AE */   sw        $v0, 0x0($s0)
/* 1D470 8002CC70 8051010C */  jal        func_80054600
/* 1D474 8002CC74 21200000 */   addu      $a0, $zero, $zero
/* 1D478 8002CC78 0780043C */  lui        $a0, %hi(D_800774B0)
/* 1D47C 8002CC7C B074848C */  lw         $a0, %lo(D_800774B0)($a0)
/* 1D480 8002CC80 0780013C */  lui        $at, %hi(D_80077FA8)
/* 1D484 8002CC84 A87F20A0 */  sb         $zero, %lo(D_80077FA8)($at)
/* 1D488 8002CC88 0780013C */  lui        $at, %hi(D_80077FA9)
/* 1D48C 8002CC8C A97F20A0 */  sb         $zero, %lo(D_80077FA9)($at)
/* 1D490 8002CC90 0780013C */  lui        $at, %hi(D_80077FAA)
/* 1D494 8002CC94 AA7F20A0 */  sb         $zero, %lo(D_80077FAA)($at)
/* 1D498 8002CC98 0780013C */  lui        $at, %hi(D_80077FAB)
/* 1D49C 8002CC9C AB7F20A0 */  sb         $zero, %lo(D_80077FAB)($at)
/* 1D4A0 8002CCA0 0780013C */  lui        $at, %hi(D_80077FAC)
/* 1D4A4 8002CCA4 AC7F20A0 */  sb         $zero, %lo(D_80077FAC)($at)
/* 1D4A8 8002CCA8 FD59010C */  jal        func_800567F4
/* 1D4AC 8002CCAC 08000524 */   addiu     $a1, $zero, 0x8
/* 1D4B0 8002CCB0 1800BF8F */  lw         $ra, 0x18($sp)
/* 1D4B4 8002CCB4 1400B18F */  lw         $s1, 0x14($sp)
/* 1D4B8 8002CCB8 1000B08F */  lw         $s0, 0x10($sp)
/* 1D4BC 8002CCBC 2000BD27 */  addiu      $sp, $sp, 0x20
/* 1D4C0 8002CCC0 0800E003 */  jr         $ra
/* 1D4C4 8002CCC4 00000000 */   nop
.size func_8002CB6C, . - func_8002CB6C
