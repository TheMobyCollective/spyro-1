.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003D978
/* 2E178 8003D978 C0FFBD27 */  addiu      $sp, $sp, -0x40
/* 2E17C 8003D97C 3000A427 */  addiu      $a0, $sp, 0x30
/* 2E180 8003D980 1000A527 */  addiu      $a1, $sp, 0x10
/* 2E184 8003D984 3800B0AF */  sw         $s0, 0x38($sp)
/* 2E188 8003D988 0880103C */  lui        $s0, %hi(g_Spyro + 0x124)
/* 2E18C 8003D98C 7C8B1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x124)
/* 2E190 8003D990 21300000 */  addu       $a2, $zero, $zero
/* 2E194 8003D994 3C00BFAF */  sw         $ra, 0x3C($sp)
/* 2E198 8003D998 0000028E */  lw         $v0, 0x0($s0)
/* 2E19C 8003D99C 0880033C */  lui        $v1, %hi(g_Spyro + 0x11C)
/* 2E1A0 8003D9A0 748B638C */  lw         $v1, %lo(g_Spyro + 0x11C)($v1)
/* 2E1A4 8003D9A4 03110200 */  sra        $v0, $v0, 4
/* 2E1A8 8003D9A8 3000A2A3 */  sb         $v0, 0x30($sp)
/* 2E1AC 8003D9AC 0880023C */  lui        $v0, %hi(g_Spyro + 0x120)
/* 2E1B0 8003D9B0 788B428C */  lw         $v0, %lo(g_Spyro + 0x120)($v0)
/* 2E1B4 8003D9B4 03190300 */  sra        $v1, $v1, 4
/* 2E1B8 8003D9B8 3200A3A3 */  sb         $v1, 0x32($sp)
/* 2E1BC 8003D9BC 03110200 */  sra        $v0, $v0, 4
/* 2E1C0 8003D9C0 4B5B000C */  jal        func_80016D2C
/* 2E1C4 8003D9C4 3100A2A3 */   sb        $v0, 0x31($sp)
/* 2E1C8 8003D9C8 1000A427 */  addiu      $a0, $sp, 0x10
/* 2E1CC 8003D9CC D0FF0526 */  addiu      $a1, $s0, -0x30
/* 2E1D0 8003D9D0 0880023C */  lui        $v0, %hi(g_Spyro + 0x118)
/* 2E1D4 8003D9D4 708B428C */  lw         $v0, %lo(g_Spyro + 0x118)($v0)
/* 2E1D8 8003D9D8 2130A000 */  addu       $a2, $a1, $zero
/* 2E1DC 8003D9DC 0880013C */  lui        $at, %hi(g_Spyro + 0xF8)
/* 2E1E0 8003D9E0 508B20AC */  sw         $zero, %lo(g_Spyro + 0xF8)($at)
/* 2E1E4 8003D9E4 0880013C */  lui        $at, %hi(g_Spyro + 0xFC)
/* 2E1E8 8003D9E8 548B20AC */  sw         $zero, %lo(g_Spyro + 0xFC)($at)
/* 2E1EC 8003D9EC 125C000C */  jal        func_80017048
/* 2E1F0 8003D9F0 D0FF02AE */   sw        $v0, -0x30($s0)
/* 2E1F4 8003D9F4 3C00BF8F */  lw         $ra, 0x3C($sp)
/* 2E1F8 8003D9F8 3800B08F */  lw         $s0, 0x38($sp)
/* 2E1FC 8003D9FC 4000BD27 */  addiu      $sp, $sp, 0x40
/* 2E200 8003DA00 0800E003 */  jr         $ra
/* 2E204 8003DA04 00000000 */   nop
.size func_8003D978, . - func_8003D978
