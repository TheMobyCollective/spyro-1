.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80018534
/* 8D34 80018534 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 8D38 80018538 1000B0AF */  sw         $s0, 0x10($sp)
/* 8D3C 8001853C 21808000 */  addu       $s0, $a0, $zero
/* 8D40 80018540 1400B1AF */  sw         $s1, 0x14($sp)
/* 8D44 80018544 2188C000 */  addu       $s1, $a2, $zero
/* 8D48 80018548 1F00A530 */  andi       $a1, $a1, 0x1F
/* 8D4C 8001854C 1000A528 */  slti       $a1, $a1, 0x10
/* 8D50 80018550 2800A010 */  beqz       $a1, .L800185F4
/* 8D54 80018554 1800BFAF */   sw        $ra, 0x18($sp)
/* 8D58 80018558 21280000 */  addu       $a1, $zero, $zero
/* 8D5C 8001855C 0780043C */  lui        $a0, %hi(g_HudMobys)
/* 8D60 80018560 1057848C */  lw         $a0, %lo(g_HudMobys)($a0)
/* 8D64 80018564 00000000 */  nop
/* 8D68 80018568 A8FF8424 */  addiu      $a0, $a0, -0x58
/* 8D6C 8001856C 0780013C */  lui        $at, %hi(g_HudMobys)
/* 8D70 80018570 105724AC */  sw         $a0, %lo(g_HudMobys)($at)
/* 8D74 80018574 455A000C */  jal        Memset
/* 8D78 80018578 58000624 */   addiu     $a2, $zero, 0x58
/* 8D7C 8001857C 21280002 */  addu       $a1, $s0, $zero
/* 8D80 80018580 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 8D84 80018584 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 8D88 80018588 05010224 */  addiu      $v0, $zero, 0x105
/* 8D8C 8001858C 0C006424 */  addiu      $a0, $v1, 0xC
/* 8D90 80018590 C05D000C */  jal        VecCopy
/* 8D94 80018594 360062A4 */   sh        $v0, 0x36($v1)
/* 8D98 80018598 0200222A */  slti       $v0, $s1, 0x2
/* 8D9C 8001859C 09004010 */  beqz       $v0, .L800185C4
/* 8DA0 800185A0 40000224 */   addiu     $v0, $zero, 0x40
/* 8DA4 800185A4 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 8DA8 800185A8 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 8DAC 800185AC 00000000 */  nop
/* 8DB0 800185B0 440062A0 */  sb         $v0, 0x44($v1)
/* 8DB4 800185B4 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 8DB8 800185B8 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 8DBC 800185BC C0111100 */  sll        $v0, $s1, 7
/* 8DC0 800185C0 460062A0 */  sb         $v0, 0x46($v1)
.L800185C4:
/* 8DC4 800185C4 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 8DC8 800185C8 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 8DCC 800185CC 7F000224 */  addiu      $v0, $zero, 0x7F
/* 8DD0 800185D0 470062A0 */  sb         $v0, 0x47($v1)
/* 8DD4 800185D4 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 8DD8 800185D8 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 8DDC 800185DC 0B000224 */  addiu      $v0, $zero, 0xB
/* 8DE0 800185E0 4F0062A0 */  sb         $v0, 0x4F($v1)
/* 8DE4 800185E4 0780033C */  lui        $v1, %hi(g_HudMobys)
/* 8DE8 800185E8 1057638C */  lw         $v1, %lo(g_HudMobys)($v1)
/* 8DEC 800185EC FF000224 */  addiu      $v0, $zero, 0xFF
/* 8DF0 800185F0 500062A0 */  sb         $v0, 0x50($v1)
.L800185F4:
/* 8DF4 800185F4 1800BF8F */  lw         $ra, 0x18($sp)
/* 8DF8 800185F8 1400B18F */  lw         $s1, 0x14($sp)
/* 8DFC 800185FC 1000B08F */  lw         $s0, 0x10($sp)
/* 8E00 80018600 2000BD27 */  addiu      $sp, $sp, 0x20
/* 8E04 80018604 0800E003 */  jr         $ra
/* 8E08 80018608 00000000 */   nop
.size func_80018534, . - func_80018534
