.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002C534
/* 1CD34 8002C534 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 1CD38 8002C538 1800B0AF */  sw         $s0, 0x18($sp)
/* 1CD3C 8002C53C 21808000 */  addu       $s0, $a0, $zero
/* 1CD40 8002C540 FEFF033C */  lui        $v1, (0xFFFE3E00 >> 16)
/* 1CD44 8002C544 003E6334 */  ori        $v1, $v1, (0xFFFE3E00 & 0xFFFF)
/* 1CD48 8002C548 1000A427 */  addiu      $a0, $sp, 0x10
/* 1CD4C 8002C54C 0880053C */  lui        $a1, %hi(D_800785F0)
/* 1CD50 8002C550 F085A58C */  lw         $a1, %lo(D_800785F0)($a1)
/* 1CD54 8002C554 00020224 */  addiu      $v0, $zero, 0x200
/* 1CD58 8002C558 1000A2A7 */  sh         $v0, 0x10($sp)
/* 1CD5C 8002C55C 00010224 */  addiu      $v0, $zero, 0x100
/* 1CD60 8002C560 1400A2A7 */  sh         $v0, 0x14($sp)
/* 1CD64 8002C564 E1000224 */  addiu      $v0, $zero, 0xE1
/* 1CD68 8002C568 1C00BFAF */  sw         $ra, 0x1C($sp)
/* 1CD6C 8002C56C 1200A0A7 */  sh         $zero, 0x12($sp)
/* 1CD70 8002C570 1600A2A7 */  sh         $v0, 0x16($sp)
/* 1CD74 8002C574 8A7E010C */  jal        LoadImage
/* 1CD78 8002C578 2128A300 */   addu      $a1, $a1, $v1
/* 1CD7C 8002C57C D97D010C */  jal        DrawSync
/* 1CD80 8002C580 21200000 */   addu      $a0, $zero, $zero
/* 1CD84 8002C584 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1CD88 8002C588 D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 1CD8C 8002C58C 1F63010C */  jal        SpecularReset
/* 1CD90 8002C590 00000000 */   nop
/* 1CD94 8002C594 03000224 */  addiu      $v0, $zero, 0x3
/* 1CD98 8002C598 0780013C */  lui        $at, %hi(D_80077FA8)
/* 1CD9C 8002C59C A87F22A0 */  sb         $v0, %lo(D_80077FA8)($at)
/* 1CDA0 8002C5A0 0780013C */  lui        $at, %hi(D_80077FA9)
/* 1CDA4 8002C5A4 A97F22A0 */  sb         $v0, %lo(D_80077FA9)($at)
/* 1CDA8 8002C5A8 0780013C */  lui        $at, %hi(D_80077FAA)
/* 1CDAC 8002C5AC AA7F22A0 */  sb         $v0, %lo(D_80077FAA)($at)
/* 1CDB0 8002C5B0 0780013C */  lui        $at, %hi(D_80077FAB)
/* 1CDB4 8002C5B4 AB7F22A0 */  sb         $v0, %lo(D_80077FAB)($at)
/* 1CDB8 8002C5B8 0780013C */  lui        $at, %hi(D_80077FAC)
/* 1CDBC 8002C5BC AC7F22A0 */  sb         $v0, %lo(D_80077FAC)($at)
/* 1CDC0 8002C5C0 0D000224 */  addiu      $v0, $zero, 0xD
/* 1CDC4 8002C5C4 0780013C */  lui        $at, %hi(D_80077FAD)
/* 1CDC8 8002C5C8 AD7F22A0 */  sb         $v0, %lo(D_80077FAD)($at)
/* 1CDCC 8002C5CC 0780013C */  lui        $at, %hi(D_80077FAE)
/* 1CDD0 8002C5D0 AE7F22A0 */  sb         $v0, %lo(D_80077FAE)($at)
/* 1CDD4 8002C5D4 0780013C */  lui        $at, %hi(D_80077FAF)
/* 1CDD8 8002C5D8 AF7F22A0 */  sb         $v0, %lo(D_80077FAF)($at)
/* 1CDDC 8002C5DC 0780013C */  lui        $at, %hi(D_80077FB0)
/* 1CDE0 8002C5E0 B07F22A0 */  sb         $v0, %lo(D_80077FB0)($at)
/* 1CDE4 8002C5E4 0780013C */  lui        $at, %hi(D_80077FB1)
/* 1CDE8 8002C5E8 B17F22A0 */  sb         $v0, %lo(D_80077FB1)($at)
/* 1CDEC 8002C5EC 05000012 */  beqz       $s0, .L8002C604
/* 1CDF0 8002C5F0 00000000 */   nop
/* 1CDF4 8002C5F4 0780043C */  lui        $a0, %hi(D_800774B0)
/* 1CDF8 8002C5F8 B074848C */  lw         $a0, %lo(D_800774B0)($a0)
/* 1CDFC 8002C5FC FD59010C */  jal        func_800567F4
/* 1CE00 8002C600 08000524 */   addiu     $a1, $zero, 0x8
.L8002C604:
/* 1CE04 8002C604 1C00BF8F */  lw         $ra, 0x1C($sp)
/* 1CE08 8002C608 1800B08F */  lw         $s0, 0x18($sp)
/* 1CE0C 8002C60C 2000BD27 */  addiu      $sp, $sp, 0x20
/* 1CE10 8002C610 0800E003 */  jr         $ra
/* 1CE14 8002C614 00000000 */   nop
.size func_8002C534, . - func_8002C534
