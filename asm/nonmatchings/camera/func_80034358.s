.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80034358
/* 24B58 80034358 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 24B5C 8003435C 1800BFAF */  sw         $ra, 0x18($sp)
/* 24B60 80034360 1400B1AF */  sw         $s1, 0x14($sp)
/* 24B64 80034364 66D0000C */  jal        func_80034198
/* 24B68 80034368 1000B0AF */   sw        $s0, 0x10($sp)
/* 24B6C 8003436C 0780103C */  lui        $s0, %hi(g_Camera + 0x78)
/* 24B70 80034370 486E1026 */  addiu      $s0, $s0, %lo(g_Camera + 0x78)
/* 24B74 80034374 BCFF1126 */  addiu      $s1, $s0, -0x44
/* 24B78 80034378 0780023C */  lui        $v0, %hi(g_Camera + 0x60)
/* 24B7C 8003437C 306E428C */  lw         $v0, %lo(g_Camera + 0x60)($v0)
/* 24B80 80034380 0780033C */  lui        $v1, %hi(g_Camera + 0x64)
/* 24B84 80034384 346E638C */  lw         $v1, %lo(g_Camera + 0x64)($v1)
/* 24B88 80034388 0780053C */  lui        $a1, %hi(g_Camera + 0x68)
/* 24B8C 8003438C 386EA58C */  lw         $a1, %lo(g_Camera + 0x68)($a1)
/* 24B90 80034390 0780063C */  lui        $a2, %hi(g_Camera + 0x6C)
/* 24B94 80034394 3C6EC68C */  lw         $a2, %lo(g_Camera + 0x6C)($a2)
/* 24B98 80034398 0780073C */  lui        $a3, %hi(g_Camera + 0x70)
/* 24B9C 8003439C 406EE78C */  lw         $a3, %lo(g_Camera + 0x70)($a3)
/* 24BA0 800343A0 0780083C */  lui        $t0, %hi(g_Camera + 0x74)
/* 24BA4 800343A4 446E088D */  lw         $t0, %lo(g_Camera + 0x74)($t0)
/* 24BA8 800343A8 0780013C */  lui        $at, %hi(g_Camera + 0xA8)
/* 24BAC 800343AC 786E20AC */  sw         $zero, %lo(g_Camera + 0xA8)($at)
/* 24BB0 800343B0 0780013C */  lui        $at, %hi(g_Camera + 0xAC)
/* 24BB4 800343B4 7C6E20AC */  sw         $zero, %lo(g_Camera + 0xAC)($at)
/* 24BB8 800343B8 0780013C */  lui        $at, %hi(g_Camera + 0xB0)
/* 24BBC 800343BC 806E20AC */  sw         $zero, %lo(g_Camera + 0xB0)($at)
/* 24BC0 800343C0 0780013C */  lui        $at, %hi(g_Camera + 0xB4)
/* 24BC4 800343C4 846E20AC */  sw         $zero, %lo(g_Camera + 0xB4)($at)
/* 24BC8 800343C8 0780013C */  lui        $at, %hi(g_Camera + 0xB8)
/* 24BCC 800343CC 886E20AC */  sw         $zero, %lo(g_Camera + 0xB8)($at)
/* 24BD0 800343D0 0780013C */  lui        $at, %hi(g_Camera + 0xBC)
/* 24BD4 800343D4 8C6E20AC */  sw         $zero, %lo(g_Camera + 0xBC)($at)
/* 24BD8 800343D8 0780013C */  lui        $at, %hi(g_Camera + 0xC4)
/* 24BDC 800343DC 946E20AC */  sw         $zero, %lo(g_Camera + 0xC4)($at)
/* 24BE0 800343E0 0780013C */  lui        $at, %hi(g_Camera + 0xC8)
/* 24BE4 800343E4 986E20AC */  sw         $zero, %lo(g_Camera + 0xC8)($at)
/* 24BE8 800343E8 000002AE */  sw         $v0, 0x0($s0)
/* 24BEC 800343EC 0780013C */  lui        $at, %hi(g_Camera + 0x7C)
/* 24BF0 800343F0 4C6E23AC */  sw         $v1, %lo(g_Camera + 0x7C)($at)
/* 24BF4 800343F4 0780013C */  lui        $at, %hi(g_Camera + 0x80)
/* 24BF8 800343F8 506E25AC */  sw         $a1, %lo(g_Camera + 0x80)($at)
/* 24BFC 800343FC 0780013C */  lui        $at, %hi(g_Camera + 0x84)
/* 24C00 80034400 546E26AC */  sw         $a2, %lo(g_Camera + 0x84)($at)
/* 24C04 80034404 0780013C */  lui        $at, %hi(g_Camera + 0x88)
/* 24C08 80034408 586E27AC */  sw         $a3, %lo(g_Camera + 0x88)($at)
/* 24C0C 8003440C 0780013C */  lui        $at, %hi(g_Camera + 0x8C)
/* 24C10 80034410 5C6E28AC */  sw         $t0, %lo(g_Camera + 0x8C)($at)
/* 24C14 80034414 81D0000C */  jal        func_80034204
/* 24C18 80034418 21202002 */   addu      $a0, $s1, $zero
/* 24C1C 8003441C 21202002 */  addu       $a0, $s1, $zero
/* 24C20 80034420 0780063C */  lui        $a2, %hi(g_Camera + 0xD0)
/* 24C24 80034424 A06EC68C */  lw         $a2, %lo(g_Camera + 0xD0)($a2)
/* 24C28 80034428 D65D000C */  jal        VecAdd
/* 24C2C 8003442C 21282002 */   addu      $a1, $s1, $zero
/* 24C30 80034430 B0FF1026 */  addiu      $s0, $s0, -0x50
/* 24C34 80034434 21200002 */  addu       $a0, $s0, $zero
/* 24C38 80034438 C05D000C */  jal        VecCopy
/* 24C3C 8003443C 21282002 */   addu      $a1, $s1, $zero
/* 24C40 80034440 C2CF000C */  jal        func_80033F08
/* 24C44 80034444 21200002 */   addu      $a0, $s0, $zero
/* 24C48 80034448 0780013C */  lui        $at, %hi(g_Camera + 0xE8)
/* 24C4C 8003444C B86E22AC */  sw         $v0, %lo(g_Camera + 0xE8)($at)
/* 24C50 80034450 BED0000C */  jal        func_800342F8
/* 24C54 80034454 00000000 */   nop
/* 24C58 80034458 0780013C */  lui        $at, %hi(D_800756DC)
/* 24C5C 8003445C DC5620AC */  sw         $zero, %lo(D_800756DC)($at)
/* 24C60 80034460 0780013C */  lui        $at, %hi(D_8007590C)
/* 24C64 80034464 0C5920AC */  sw         $zero, %lo(D_8007590C)($at)
/* 24C68 80034468 1800BF8F */  lw         $ra, 0x18($sp)
/* 24C6C 8003446C 1400B18F */  lw         $s1, 0x14($sp)
/* 24C70 80034470 1000B08F */  lw         $s0, 0x10($sp)
/* 24C74 80034474 2000BD27 */  addiu      $sp, $sp, 0x20
/* 24C78 80034478 0800E003 */  jr         $ra
/* 24C7C 8003447C 00000000 */   nop
.size func_80034358, . - func_80034358
