.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002C8A4
/* 1D0A4 8002C8A4 0880023C */  lui        $v0, %hi(D_80078A40 + 0x10)
/* 1D0A8 8002C8A8 508A4290 */  lbu        $v0, %lo(D_80078A40 + 0x10)($v0)
/* 1D0AC 8002C8AC 0880033C */  lui        $v1, %hi(D_80078A40 + 0x11)
/* 1D0B0 8002C8B0 518A6390 */  lbu        $v1, %lo(D_80078A40 + 0x11)($v1)
/* 1D0B4 8002C8B4 0880043C */  lui        $a0, %hi(D_80078A40 + 0x12)
/* 1D0B8 8002C8B8 528A8490 */  lbu        $a0, %lo(D_80078A40 + 0x12)($a0)
/* 1D0BC 8002C8BC E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1D0C0 8002C8C0 1000BFAF */  sw         $ra, 0x10($sp)
/* 1D0C4 8002C8C4 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1D0C8 8002C8C8 D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 1D0CC 8002C8CC 0780013C */  lui        $at, %hi(g_DB + 0x19)
/* 1D0D0 8002C8D0 F96E22A0 */  sb         $v0, %lo(g_DB + 0x19)($at)
/* 1D0D4 8002C8D4 0780013C */  lui        $at, %hi(g_DB + 0x1A)
/* 1D0D8 8002C8D8 FA6E23A0 */  sb         $v1, %lo(g_DB + 0x1A)($at)
/* 1D0DC 8002C8DC 0780013C */  lui        $at, %hi(g_DB + 0x1B)
/* 1D0E0 8002C8E0 FB6E24A0 */  sb         $a0, %lo(g_DB + 0x1B)($at)
/* 1D0E4 8002C8E4 0780013C */  lui        $at, %hi(g_DB + 0x9D)
/* 1D0E8 8002C8E8 7D6F22A0 */  sb         $v0, %lo(g_DB + 0x9D)($at)
/* 1D0EC 8002C8EC 0780013C */  lui        $at, %hi(g_DB + 0x9E)
/* 1D0F0 8002C8F0 7E6F23A0 */  sb         $v1, %lo(g_DB + 0x9E)($at)
/* 1D0F4 8002C8F4 0780013C */  lui        $at, %hi(g_DB + 0x9F)
/* 1D0F8 8002C8F8 7F6F24A0 */  sb         $a0, %lo(g_DB + 0x9F)($at)
/* 1D0FC 8002C8FC 1F63010C */  jal        SpecularReset
/* 1D100 8002C900 00000000 */   nop
/* 1D104 8002C904 1000BF8F */  lw         $ra, 0x10($sp)
/* 1D108 8002C908 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1D10C 8002C90C 0800E003 */  jr         $ra
/* 1D110 8002C910 00000000 */   nop
.size func_8002C8A4, . - func_8002C8A4
