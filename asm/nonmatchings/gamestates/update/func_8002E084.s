.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002E084
/* 1E884 8002E084 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1E888 8002E088 1000BFAF */  sw         $ra, 0x10($sp)
/* 1E88C 8002E08C 832A010C */  jal        func_8004AA0C
/* 1E890 8002E090 00000000 */   nop
/* 1E894 8002E094 F5DE000C */  jal        func_80037BD4
/* 1E898 8002E098 00000000 */   nop
/* 1E89C 8002E09C 0780023C */  lui        $v0, %hi(D_8007568C)
/* 1E8A0 8002E0A0 8C56428C */  lw         $v0, %lo(D_8007568C)($v0)
/* 1E8A4 8002E0A4 00000000 */  nop
/* 1E8A8 8002E0A8 01004324 */  addiu      $v1, $v0, 0x1
/* 1E8AC 8002E0AC 20006228 */  slti       $v0, $v1, 0x20
/* 1E8B0 8002E0B0 0780013C */  lui        $at, %hi(D_8007568C)
/* 1E8B4 8002E0B4 8C5623AC */  sw         $v1, %lo(D_8007568C)($at)
/* 1E8B8 8002E0B8 0F004014 */  bnez       $v0, .L8002E0F8
/* 1E8BC 8002E0BC 10000224 */   addiu     $v0, $zero, 0x10
/* 1E8C0 8002E0C0 0780023C */  lui        $v0, %hi(D_800758B8)
/* 1E8C4 8002E0C4 B858428C */  lw         $v0, %lo(D_800758B8)($v0)
/* 1E8C8 8002E0C8 02000324 */  addiu      $v1, $zero, 0x2
/* 1E8CC 8002E0CC 0780013C */  lui        $at, %hi(D_8007568C)
/* 1E8D0 8002E0D0 8C5620AC */  sw         $zero, %lo(D_8007568C)($at)
/* 1E8D4 8002E0D4 01004224 */  addiu      $v0, $v0, 0x1
/* 1E8D8 8002E0D8 0780013C */  lui        $at, %hi(D_800758B8)
/* 1E8DC 8002E0DC B85822AC */  sw         $v0, %lo(D_800758B8)($at)
/* 1E8E0 8002E0E0 0E004314 */  bne        $v0, $v1, .L8002E11C
/* 1E8E4 8002E0E4 00000000 */   nop
/* 1E8E8 8002E0E8 99B1000C */  jal        func_8002C664
/* 1E8EC 8002E0EC 00000000 */   nop
/* 1E8F0 8002E0F0 47B80008 */  j          .L8002E11C
/* 1E8F4 8002E0F4 00000000 */   nop
.L8002E0F8:
/* 1E8F8 8002E0F8 08006214 */  bne        $v1, $v0, .L8002E11C
/* 1E8FC 8002E0FC 00000000 */   nop
/* 1E900 8002E100 0780023C */  lui        $v0, %hi(D_800758B8)
/* 1E904 8002E104 B858428C */  lw         $v0, %lo(D_800758B8)($v0)
/* 1E908 8002E108 00000000 */  nop
/* 1E90C 8002E10C 03004014 */  bnez       $v0, .L8002E11C
/* 1E910 8002E110 00000000 */   nop
/* 1E914 8002E114 9AFA000C */  jal        func_8003EA68
/* 1E918 8002E118 0F000424 */   addiu     $a0, $zero, 0xF
.L8002E11C:
/* 1E91C 8002E11C 1000BF8F */  lw         $ra, 0x10($sp)
/* 1E920 8002E120 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1E924 8002E124 0800E003 */  jr         $ra
/* 1E928 8002E128 00000000 */   nop
.size func_8002E084, . - func_8002E084
