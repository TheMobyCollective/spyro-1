.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003DA08
/* 2E208 8003DA08 0880063C */  lui        $a2, %hi(g_Spyro + 0x124)
/* 2E20C 8003DA0C 7C8BC624 */  addiu      $a2, $a2, %lo(g_Spyro + 0x124)
/* 2E210 8003DA10 0000C88C */  lw         $t0, 0x0($a2)
/* 2E214 8003DA14 F0FFBD27 */  addiu      $sp, $sp, -0x10
/* 2E218 8003DA18 0000A0AF */  sw         $zero, 0x0($sp)
/* 2E21C 8003DA1C 0400A0AF */  sw         $zero, 0x4($sp)
/* 2E220 8003DA20 23100800 */  negu       $v0, $t0
/* 2E224 8003DA24 FF0F4330 */  andi       $v1, $v0, 0xFFF
/* 2E228 8003DA28 00086228 */  slti       $v0, $v1, 0x800
/* 2E22C 8003DA2C 03004014 */  bnez       $v0, .L8003DA3C
/* 2E230 8003DA30 0000A3AF */   sw        $v1, 0x0($sp)
/* 2E234 8003DA34 00F06224 */  addiu      $v0, $v1, -0x1000
/* 2E238 8003DA38 0000A2AF */  sw         $v0, 0x0($sp)
.L8003DA3C:
/* 2E23C 8003DA3C FCFFC78C */  lw         $a3, -0x4($a2)
/* 2E240 8003DA40 00000000 */  nop
/* 2E244 8003DA44 23100700 */  negu       $v0, $a3
/* 2E248 8003DA48 FF0F4330 */  andi       $v1, $v0, 0xFFF
/* 2E24C 8003DA4C 00086228 */  slti       $v0, $v1, 0x800
/* 2E250 8003DA50 03004014 */  bnez       $v0, .L8003DA60
/* 2E254 8003DA54 0400A3AF */   sw        $v1, 0x4($sp)
/* 2E258 8003DA58 00F06224 */  addiu      $v0, $v1, -0x1000
/* 2E25C 8003DA5C 0400A2AF */  sw         $v0, 0x4($sp)
.L8003DA60:
/* 2E260 8003DA60 0000A38F */  lw         $v1, 0x0($sp)
/* 2E264 8003DA64 0880053C */  lui        $a1, %hi(g_Spyro + 0x258)
/* 2E268 8003DA68 B08CA58C */  lw         $a1, %lo(g_Spyro + 0x258)($a1)
/* 2E26C 8003DA6C 0400A48F */  lw         $a0, 0x4($sp)
/* 2E270 8003DA70 80180300 */  sll        $v1, $v1, 2
/* 2E274 8003DA74 03190300 */  sra        $v1, $v1, 4
/* 2E278 8003DA78 00110500 */  sll        $v0, $a1, 4
/* 2E27C 8003DA7C 83110200 */  sra        $v0, $v0, 6
/* 2E280 8003DA80 23186200 */  subu       $v1, $v1, $v0
/* 2E284 8003DA84 2128A300 */  addu       $a1, $a1, $v1
/* 2E288 8003DA88 80200400 */  sll        $a0, $a0, 2
/* 2E28C 8003DA8C 0880033C */  lui        $v1, %hi(g_Spyro + 0x25C)
/* 2E290 8003DA90 B48C638C */  lw         $v1, %lo(g_Spyro + 0x25C)($v1)
/* 2E294 8003DA94 03210400 */  sra        $a0, $a0, 4
/* 2E298 8003DA98 0880013C */  lui        $at, %hi(g_Spyro + 0x258)
/* 2E29C 8003DA9C B08C25AC */  sw         $a1, %lo(g_Spyro + 0x258)($at)
/* 2E2A0 8003DAA0 83280500 */  sra        $a1, $a1, 2
/* 2E2A4 8003DAA4 0000A5AF */  sw         $a1, 0x0($sp)
/* 2E2A8 8003DAA8 21280501 */  addu       $a1, $t0, $a1
/* 2E2AC 8003DAAC 00110300 */  sll        $v0, $v1, 4
/* 2E2B0 8003DAB0 83110200 */  sra        $v0, $v0, 6
/* 2E2B4 8003DAB4 23208200 */  subu       $a0, $a0, $v0
/* 2E2B8 8003DAB8 21186400 */  addu       $v1, $v1, $a0
/* 2E2BC 8003DABC 0880013C */  lui        $at, %hi(g_Spyro + 0x25C)
/* 2E2C0 8003DAC0 B48C23AC */  sw         $v1, %lo(g_Spyro + 0x25C)($at)
/* 2E2C4 8003DAC4 83180300 */  sra        $v1, $v1, 2
/* 2E2C8 8003DAC8 0400A3AF */  sw         $v1, 0x4($sp)
/* 2E2CC 8003DACC 2118E300 */  addu       $v1, $a3, $v1
/* 2E2D0 8003DAD0 0000C5AC */  sw         $a1, 0x0($a2)
/* 2E2D4 8003DAD4 FCFFC3AC */  sw         $v1, -0x4($a2)
/* 2E2D8 8003DAD8 1000BD27 */  addiu      $sp, $sp, 0x10
/* 2E2DC 8003DADC 0800E003 */  jr         $ra
/* 2E2E0 8003DAE0 00000000 */   nop
.size func_8003DA08, . - func_8003DA08
