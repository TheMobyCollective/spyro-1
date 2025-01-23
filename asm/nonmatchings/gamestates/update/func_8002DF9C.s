.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002DF9C
/* 1E79C 8002DF9C E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1E7A0 8002DFA0 1000BFAF */  sw         $ra, 0x10($sp)
/* 1E7A4 8002DFA4 FB29010C */  jal        func_8004A7EC
/* 1E7A8 8002DFA8 00000000 */   nop
/* 1E7AC 8002DFAC F5DE000C */  jal        func_80037BD4
/* 1E7B0 8002DFB0 00000000 */   nop
/* 1E7B4 8002DFB4 9DB6000C */  jal        func_8002DA74
/* 1E7B8 8002DFB8 00000000 */   nop
/* 1E7BC 8002DFBC 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 1E7C0 8002DFC0 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 1E7C4 8002DFC4 00000000 */  nop
/* 1E7C8 8002DFC8 0B004228 */  slti       $v0, $v0, 0xB
/* 1E7CC 8002DFCC 06004014 */  bnez       $v0, .L8002DFE8
/* 1E7D0 8002DFD0 00000000 */   nop
/* 1E7D4 8002DFD4 0780023C */  lui        $v0, %hi(D_800756B0)
/* 1E7D8 8002DFD8 B056428C */  lw         $v0, %lo(D_800756B0)($v0)
/* 1E7DC 8002DFDC 00000000 */  nop
/* 1E7E0 8002DFE0 03004014 */  bnez       $v0, .L8002DFF0
/* 1E7E4 8002DFE4 00000000 */   nop
.L8002DFE8:
/* 1E7E8 8002DFE8 DC54000C */  jal        func_80015370
/* 1E7EC 8002DFEC 01000424 */   addiu     $a0, $zero, 0x1
.L8002DFF0:
/* 1E7F0 8002DFF0 1000BF8F */  lw         $ra, 0x10($sp)
/* 1E7F4 8002DFF4 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1E7F8 8002DFF8 0800E003 */  jr         $ra
/* 1E7FC 8002DFFC 00000000 */   nop
.size func_8002DF9C, . - func_8002DF9C
