.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_800342F8
/* 24AF8 800342F8 0780023C */  lui        $v0, %hi(g_Camera + 0x94)
/* 24AFC 800342FC 646E428C */  lw         $v0, %lo(g_Camera + 0x94)($v0)
/* 24B00 80034300 0780033C */  lui        $v1, %hi(g_Camera + 0x88)
/* 24B04 80034304 586E638C */  lw         $v1, %lo(g_Camera + 0x88)($v1)
/* 24B08 80034308 0780043C */  lui        $a0, %hi(g_Camera + 0x84)
/* 24B0C 8003430C 546E848C */  lw         $a0, %lo(g_Camera + 0x84)($a0)
/* 24B10 80034310 21104300 */  addu       $v0, $v0, $v1
/* 24B14 80034314 0780033C */  lui        $v1, %hi(g_Camera + 0x8C)
/* 24B18 80034318 5C6E638C */  lw         $v1, %lo(g_Camera + 0x8C)($v1)
/* 24B1C 8003431C FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 24B20 80034320 0780013C */  lui        $at, %hi(g_Camera + 0x4E)
/* 24B24 80034324 1E6E22A4 */  sh         $v0, %lo(g_Camera + 0x4E)($at)
/* 24B28 80034328 00080224 */  addiu      $v0, $zero, 0x800
/* 24B2C 8003432C 0780013C */  lui        $at, %hi(g_Camera + 0x4C)
/* 24B30 80034330 1C6E24A4 */  sh         $a0, %lo(g_Camera + 0x4C)($at)
/* 24B34 80034334 0780043C */  lui        $a0, %hi(g_Camera + 0x90)
/* 24B38 80034338 606E848C */  lw         $a0, %lo(g_Camera + 0x90)($a0)
/* 24B3C 8003433C 23104300 */  subu       $v0, $v0, $v1
/* 24B40 80034340 23104400 */  subu       $v0, $v0, $a0
/* 24B44 80034344 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 24B48 80034348 0780013C */  lui        $at, %hi(g_Camera + 0x50)
/* 24B4C 8003434C 206E22A4 */  sh         $v0, %lo(g_Camera + 0x50)($at)
/* 24B50 80034350 0800E003 */  jr         $ra
/* 24B54 80034354 00000000 */   nop
.size func_800342F8, . - func_800342F8
