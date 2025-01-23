.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80037A20
/* 28220 80037A20 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 28224 80037A24 0880043C */  lui        $a0, %hi(g_Spyro + 0x11C)
/* 28228 80037A28 748B848C */  lw         $a0, %lo(g_Spyro + 0x11C)($a0)
/* 2822C 80037A2C 0780033C */  lui        $v1, %hi(D_800758AC)
/* 28230 80037A30 AC58638C */  lw         $v1, %lo(D_800758AC)($v1)
/* 28234 80037A34 0880023C */  lui        $v0, %hi(g_Spyro)
/* 28238 80037A38 588A4224 */  addiu      $v0, $v0, %lo(g_Spyro)
/* 2823C 80037A3C 1C00BFAF */  sw         $ra, 0x1C($sp)
/* 28240 80037A40 1800B0AF */  sw         $s0, 0x18($sp)
/* 28244 80037A44 0780013C */  lui        $at, %hi(g_Camera + 0xD0)
/* 28248 80037A48 A06E22AC */  sw         $v0, %lo(g_Camera + 0xD0)($at)
/* 2824C 80037A4C 0780013C */  lui        $at, %hi(g_Camera + 0xD4)
/* 28250 80037A50 A46E24AC */  sw         $a0, %lo(g_Camera + 0xD4)($at)
/* 28254 80037A54 0F006010 */  beqz       $v1, .L80037A94
/* 28258 80037A58 00000000 */   nop
/* 2825C 80037A5C 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 28260 80037A60 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 28264 80037A64 00000000 */  nop
/* 28268 80037A68 0A004228 */  slti       $v0, $v0, 0xA
/* 2826C 80037A6C 05004014 */  bnez       $v0, .L80037A84
/* 28270 80037A70 00000000 */   nop
/* 28274 80037A74 0780023C */  lui        $v0, %hi(D_8006C964)
/* 28278 80037A78 64C94224 */  addiu      $v0, $v0, %lo(D_8006C964)
/* 2827C 80037A7C B6DE0008 */  j          .L80037AD8
/* 28280 80037A80 00000000 */   nop
.L80037A84:
/* 28284 80037A84 0780023C */  lui        $v0, %hi(D_8006CA54)
/* 28288 80037A88 54CA4224 */  addiu      $v0, $v0, %lo(D_8006CA54)
/* 2828C 80037A8C B6DE0008 */  j          .L80037AD8
/* 28290 80037A90 00000000 */   nop
.L80037A94:
/* 28294 80037A94 0780023C */  lui        $v0, %hi(g_Camera + 0xD8)
/* 28298 80037A98 A86E428C */  lw         $v0, %lo(g_Camera + 0xD8)($v0)
/* 2829C 80037A9C 00000000 */  nop
/* 282A0 80037AA0 0F004014 */  bnez       $v0, .L80037AE0
/* 282A4 80037AA4 00000000 */   nop
/* 282A8 80037AA8 0780023C */  lui        $v0, %hi(g_Camera + 0x50)
/* 282AC 80037AAC 206E4284 */  lh         $v0, %lo(g_Camera + 0x50)($v0)
/* 282B0 80037AB0 00000000 */  nop
/* 282B4 80037AB4 2A108200 */  slt        $v0, $a0, $v0
/* 282B8 80037AB8 05004010 */  beqz       $v0, .L80037AD0
/* 282BC 80037ABC 00000000 */   nop
/* 282C0 80037AC0 0780023C */  lui        $v0, %hi(D_8006CA3C)
/* 282C4 80037AC4 3CCA4224 */  addiu      $v0, $v0, %lo(D_8006CA3C)
/* 282C8 80037AC8 B6DE0008 */  j          .L80037AD8
/* 282CC 80037ACC 00000000 */   nop
.L80037AD0:
/* 282D0 80037AD0 0780023C */  lui        $v0, %hi(D_8006CA6C)
/* 282D4 80037AD4 6CCA4224 */  addiu      $v0, $v0, %lo(D_8006CA6C)
.L80037AD8:
/* 282D8 80037AD8 0780013C */  lui        $at, %hi(g_Camera + 0xD8)
/* 282DC 80037ADC A86E22AC */  sw         $v0, %lo(g_Camera + 0xD8)($at)
.L80037AE0:
/* 282E0 80037AE0 66D0000C */  jal        func_80034198
/* 282E4 80037AE4 21800000 */   addu      $s0, $zero, $zero
/* 282E8 80037AE8 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 282EC 80037AEC CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 282F0 80037AF0 C00680AF */  sw         $zero, %gp_rel(D_80075924)($gp)
/* 282F4 80037AF4 09004018 */  blez       $v0, .L80037B1C
/* 282F8 80037AF8 00000000 */   nop
.L80037AFC:
/* 282FC 80037AFC 3AD3000C */  jal        func_80034CE8
/* 28300 80037B00 21200000 */   addu      $a0, $zero, $zero
/* 28304 80037B04 0780023C */  lui        $v0, %hi(g_DeltaTime)
/* 28308 80037B08 CC56428C */  lw         $v0, %lo(g_DeltaTime)($v0)
/* 2830C 80037B0C 01001026 */  addiu      $s0, $s0, 0x1
/* 28310 80037B10 2A100202 */  slt        $v0, $s0, $v0
/* 28314 80037B14 F9FF4014 */  bnez       $v0, .L80037AFC
/* 28318 80037B18 00000000 */   nop
.L80037B1C:
/* 2831C 80037B1C 0780103C */  lui        $s0, %hi(g_Camera + 0x34)
/* 28320 80037B20 046E1026 */  addiu      $s0, $s0, %lo(g_Camera + 0x34)
/* 28324 80037B24 81D0000C */  jal        func_80034204
/* 28328 80037B28 21200002 */   addu      $a0, $s0, $zero
/* 2832C 80037B2C 21200002 */  addu       $a0, $s0, $zero
/* 28330 80037B30 0780063C */  lui        $a2, %hi(g_Camera + 0xD0)
/* 28334 80037B34 A06EC68C */  lw         $a2, %lo(g_Camera + 0xD0)($a2)
/* 28338 80037B38 D65D000C */  jal        VecAdd
/* 2833C 80037B3C 21280002 */   addu      $a1, $s0, $zero
/* 28340 80037B40 21D3000C */  jal        func_80034C84
/* 28344 80037B44 00000000 */   nop
/* 28348 80037B48 BED0000C */  jal        func_800342F8
/* 2834C 80037B4C 00000000 */   nop
/* 28350 80037B50 C2CF000C */  jal        func_80033F08
/* 28354 80037B54 F4FF0426 */   addiu     $a0, $s0, -0xC
/* 28358 80037B58 0780033C */  lui        $v1, %hi(g_Camera + 0x90)
/* 2835C 80037B5C 606E638C */  lw         $v1, %lo(g_Camera + 0x90)($v1)
/* 28360 80037B60 0780043C */  lui        $a0, %hi(g_Camera + 0x94)
/* 28364 80037B64 646E848C */  lw         $a0, %lo(g_Camera + 0x94)($a0)
/* 28368 80037B68 0780053C */  lui        $a1, %hi(g_Camera + 0x98)
/* 2836C 80037B6C 686EA58C */  lw         $a1, %lo(g_Camera + 0x98)($a1)
/* 28370 80037B70 0780063C */  lui        $a2, %hi(g_Camera + 0x9C)
/* 28374 80037B74 6C6EC68C */  lw         $a2, %lo(g_Camera + 0x9C)($a2)
/* 28378 80037B78 0780073C */  lui        $a3, %hi(g_Camera + 0xA0)
/* 2837C 80037B7C 706EE78C */  lw         $a3, %lo(g_Camera + 0xA0)($a3)
/* 28380 80037B80 0780083C */  lui        $t0, %hi(g_Camera + 0xA4)
/* 28384 80037B84 746E088D */  lw         $t0, %lo(g_Camera + 0xA4)($t0)
/* 28388 80037B88 0780013C */  lui        $at, %hi(g_Camera + 0xE8)
/* 2838C 80037B8C B86E22AC */  sw         $v0, %lo(g_Camera + 0xE8)($at)
/* 28390 80037B90 0780013C */  lui        $at, %hi(g_Camera + 0x78)
/* 28394 80037B94 486E23AC */  sw         $v1, %lo(g_Camera + 0x78)($at)
/* 28398 80037B98 0780013C */  lui        $at, %hi(g_Camera + 0x7C)
/* 2839C 80037B9C 4C6E24AC */  sw         $a0, %lo(g_Camera + 0x7C)($at)
/* 283A0 80037BA0 0780013C */  lui        $at, %hi(g_Camera + 0x80)
/* 283A4 80037BA4 506E25AC */  sw         $a1, %lo(g_Camera + 0x80)($at)
/* 283A8 80037BA8 0780013C */  lui        $at, %hi(g_Camera + 0x84)
/* 283AC 80037BAC 546E26AC */  sw         $a2, %lo(g_Camera + 0x84)($at)
/* 283B0 80037BB0 0780013C */  lui        $at, %hi(g_Camera + 0x88)
/* 283B4 80037BB4 586E27AC */  sw         $a3, %lo(g_Camera + 0x88)($at)
/* 283B8 80037BB8 0780013C */  lui        $at, %hi(g_Camera + 0x8C)
/* 283BC 80037BBC 5C6E28AC */  sw         $t0, %lo(g_Camera + 0x8C)($at)
/* 283C0 80037BC0 1C00BF8F */  lw         $ra, 0x1C($sp)
/* 283C4 80037BC4 1800B08F */  lw         $s0, 0x18($sp)
/* 283C8 80037BC8 2000BD27 */  addiu      $sp, $sp, 0x20
/* 283CC 80037BCC 0800E003 */  jr         $ra
/* 283D0 80037BD0 00000000 */   nop
.size func_80037A20, . - func_80037A20
