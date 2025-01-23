.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002D228
/* 1DA28 8002D228 B8FFBD27 */  addiu      $sp, $sp, -0x48
/* 1DA2C 8002D22C 4000B0AF */  sw         $s0, 0x40($sp)
/* 1DA30 8002D230 21808000 */  addu       $s0, $a0, $zero
/* 1DA34 8002D234 3800A427 */  addiu      $a0, $sp, 0x38
/* 1DA38 8002D238 21280000 */  addu       $a1, $zero, $zero
/* 1DA3C 8002D23C 21300000 */  addu       $a2, $zero, $zero
/* 1DA40 8002D240 21380000 */  addu       $a3, $zero, $zero
/* 1DA44 8002D244 00020224 */  addiu      $v0, $zero, 0x200
/* 1DA48 8002D248 3C00A2A7 */  sh         $v0, 0x3C($sp)
/* 1DA4C 8002D24C E0010224 */  addiu      $v0, $zero, 0x1E0
/* 1DA50 8002D250 4400BFAF */  sw         $ra, 0x44($sp)
/* 1DA54 8002D254 3800A0A7 */  sh         $zero, 0x38($sp)
/* 1DA58 8002D258 3A00A0A7 */  sh         $zero, 0x3A($sp)
/* 1DA5C 8002D25C 3E7E010C */  jal        ClearImage
/* 1DA60 8002D260 3E00A2A7 */   sh        $v0, 0x3E($sp)
/* 1DA64 8002D264 D97D010C */  jal        DrawSync
/* 1DA68 8002D268 21200000 */   addu      $a0, $zero, $zero
/* 1DA6C 8002D26C CA5A010C */  jal        func_80056B28
/* 1DA70 8002D270 21200000 */   addu      $a0, $zero, $zero
/* 1DA74 8002D274 B55B010C */  jal        SpuUpdate
/* 1DA78 8002D278 00000000 */   nop
/* 1DA7C 8002D27C 03000012 */  beqz       $s0, .L8002D28C
/* 1DA80 8002D280 00000000 */   nop
/* 1DA84 8002D284 F66D010C */  jal        func_8005B7D8
/* 1DA88 8002D288 00000000 */   nop
.L8002D28C:
/* 1DA8C 8002D28C 092B010C */  jal        func_8004AC24
/* 1DA90 8002D290 01000424 */   addiu     $a0, $zero, 0x1
/* 1DA94 8002D294 0780033C */  lui        $v1, %hi(D_800757AC)
/* 1DA98 8002D298 AC57638C */  lw         $v1, %lo(D_800757AC)($v1)
/* 1DA9C 8002D29C 0F000224 */  addiu      $v0, $zero, 0xF
/* 1DAA0 8002D2A0 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1DAA4 8002D2A4 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1DAA8 8002D2A8 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 1DAAC 8002D2AC 0780013C */  lui        $at, %hi(D_80075704)
/* 1DAB0 8002D2B0 045722AC */  sw         $v0, %lo(D_80075704)($at)
/* 1DAB4 8002D2B4 0A000224 */  addiu      $v0, $zero, 0xA
/* 1DAB8 8002D2B8 0780013C */  lui        $at, %hi(D_80075968)
/* 1DABC 8002D2BC 685920AC */  sw         $zero, %lo(D_80075968)($at)
/* 1DAC0 8002D2C0 0780013C */  lui        $at, %hi(D_80075878)
/* 1DAC4 8002D2C4 785820AC */  sw         $zero, %lo(D_80075878)($at)
/* 1DAC8 8002D2C8 0780013C */  lui        $at, %hi(D_800757DC)
/* 1DACC 8002D2CC DC5720AC */  sw         $zero, %lo(D_800757DC)($at)
/* 1DAD0 8002D2D0 0780013C */  lui        $at, %hi(D_800757BC)
/* 1DAD4 8002D2D4 BC5720AC */  sw         $zero, %lo(D_800757BC)($at)
/* 1DAD8 8002D2D8 0780013C */  lui        $at, %hi(D_80075768)
/* 1DADC 8002D2DC 685720AC */  sw         $zero, %lo(D_80075768)($at)
/* 1DAE0 8002D2E0 0780013C */  lui        $at, %hi(D_800756F8)
/* 1DAE4 8002D2E4 F85620AC */  sw         $zero, %lo(D_800756F8)($at)
/* 1DAE8 8002D2E8 03006210 */  beq        $v1, $v0, .L8002D2F8
/* 1DAEC 8002D2EC 00000000 */   nop
/* 1DAF0 8002D2F0 0780013C */  lui        $at, %hi(D_800757AC)
/* 1DAF4 8002D2F4 AC5720AC */  sw         $zero, %lo(D_800757AC)($at)
.L8002D2F8:
/* 1DAF8 8002D2F8 0780043C */  lui        $a0, %hi(D_80076B90)
/* 1DAFC 8002D2FC 906B848C */  lw         $a0, %lo(D_80076B90)($a0)
/* 1DB00 8002D300 0880063C */  lui        $a2, %hi(D_8007A95C)
/* 1DB04 8002D304 5CA9C68C */  lw         $a2, %lo(D_8007A95C)($a2)
/* 1DB08 8002D308 0880073C */  lui        $a3, %hi(D_8007A958)
/* 1DB0C 8002D30C 58A9E78C */  lw         $a3, %lo(D_8007A958)($a3)
/* 1DB10 8002D310 0180053C */  lui        $a1, %hi(D_800113A0)
/* 1DB14 8002D314 A013A58C */  lw         $a1, %lo(D_800113A0)($a1)
/* 1DB18 8002D318 58020224 */  addiu      $v0, $zero, 0x258
/* 1DB1C 8002D31C 4059000C */  jal        CDLoadSync
/* 1DB20 8002D320 1000A2AF */   sw        $v0, 0x10($sp)
/* 1DB24 8002D324 4400BF8F */  lw         $ra, 0x44($sp)
/* 1DB28 8002D328 4000B08F */  lw         $s0, 0x40($sp)
/* 1DB2C 8002D32C 4800BD27 */  addiu      $sp, $sp, 0x48
/* 1DB30 8002D330 0800E003 */  jr         $ra
/* 1DB34 8002D334 00000000 */   nop
.size func_8002D228, . - func_8002D228
