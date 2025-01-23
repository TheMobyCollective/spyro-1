.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002B9CC
/* 1C1CC 8002B9CC E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1C1D0 8002B9D0 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* 1C1D4 8002B9D4 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* 1C1D8 8002B9D8 21280000 */  addu       $a1, $zero, $zero
/* 1C1DC 8002B9DC 1000BFAF */  sw         $ra, 0x10($sp)
/* 1C1E0 8002B9E0 4C5A000C */  jal        Memset16
/* 1C1E4 8002B9E4 001C0624 */   addiu     $a2, $zero, 0x1C00
/* 1C1E8 8002B9E8 0780043C */  lui        $a0, %hi(g_Camera + 0x54)
/* 1C1EC 8002B9EC 246E848C */  lw         $a0, %lo(g_Camera + 0x54)($a0)
/* 1C1F0 8002B9F0 0880023C */  lui        $v0, %hi(g_Environment + 0xC)
/* 1C1F4 8002B9F4 B485428C */  lw         $v0, %lo(g_Environment + 0xC)($v0)
/* 1C1F8 8002B9F8 00000000 */  nop
/* 1C1FC 8002B9FC 2A108200 */  slt        $v0, $a0, $v0
/* 1C200 8002BA00 06004010 */  beqz       $v0, .L8002BA1C
/* 1C204 8002BA04 0200023C */   lui       $v0, (0x28000 >> 16)
/* 1C208 8002BA08 00804234 */  ori        $v0, $v0, (0x28000 & 0xFFFF)
/* 1C20C 8002BA0C 0880013C */  lui        $at, %hi(g_Environment + 0x28)
/* 1C210 8002BA10 D08522AC */  sw         $v0, %lo(g_Environment + 0x28)($at)
/* 1C214 8002BA14 94AE0008 */  j          .L8002BA50
/* 1C218 8002BA18 00000000 */   nop
.L8002BA1C:
/* 1C21C 8002BA1C 0780023C */  lui        $v0, %hi(g_Gamestate)
/* 1C220 8002BA20 D857428C */  lw         $v0, %lo(g_Gamestate)($v0)
/* 1C224 8002BA24 00000000 */  nop
/* 1C228 8002BA28 F3FF4224 */  addiu      $v0, $v0, -0xD
/* 1C22C 8002BA2C 0200422C */  sltiu      $v0, $v0, 0x2
/* 1C230 8002BA30 03004010 */  beqz       $v0, .L8002BA40
/* 1C234 8002BA34 0100023C */   lui       $v0, (0x14000 >> 16)
/* 1C238 8002BA38 91AE0008 */  j          .L8002BA44
/* 1C23C 8002BA3C 00C04234 */   ori       $v0, $v0, (0x1C000 & 0xFFFF)
.L8002BA40:
/* 1C240 8002BA40 00404234 */  ori        $v0, $v0, (0x14000 & 0xFFFF)
.L8002BA44:
/* 1C244 8002BA44 0880013C */  lui        $at, %hi(g_Environment + 0x28)
/* 1C248 8002BA48 D08522AC */  sw         $v0, %lo(g_Environment + 0x28)($at)
/* 1C24C 8002BA4C FFFF0424 */  addiu      $a0, $zero, -0x1
.L8002BA50:
/* 1C250 8002BA50 3C96000C */  jal        func_800258F0
/* 1C254 8002BA54 00000000 */   nop
/* 1C258 8002BA58 1000BF8F */  lw         $ra, 0x10($sp)
/* 1C25C 8002BA5C 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1C260 8002BA60 0800E003 */  jr         $ra
/* 1C264 8002BA64 00000000 */   nop
.size func_8002B9CC, . - func_8002B9CC
