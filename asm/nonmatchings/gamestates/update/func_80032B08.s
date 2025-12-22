.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80032B08
/* 23308 80032B08 C8FFBD27 */  addiu      $sp, $sp, -0x38
/* 2330C 80032B0C 0880033C */  lui        $v1, %hi(g_TitlescreenState)
/* 23310 80032B10 788D638C */  lw         $v1, %lo(g_TitlescreenState)($v1)
/* 23314 80032B14 03000224 */  addiu      $v0, $zero, 0x3
/* 23318 80032B18 3400BFAF */  sw         $ra, 0x34($sp)
/* 2331C 80032B1C 3000B2AF */  sw         $s2, 0x30($sp)
/* 23320 80032B20 2C00B1AF */  sw         $s1, 0x2C($sp)
/* 23324 80032B24 92016214 */  bne        $v1, $v0, .L80033170
/* 23328 80032B28 2800B0AF */   sw        $s0, 0x28($sp)
/* 2332C 80032B2C 0880033C */  lui        $v1, %hi(g_TitlescreenState + 0x4)
/* 23330 80032B30 7C8D638C */  lw         $v1, %lo(g_TitlescreenState + 0x4)($v1)
/* 23334 80032B34 00000000 */  nop
/* 23338 80032B38 65006014 */  bnez       $v1, .L80032CD0
/* 2333C 80032B3C 01000224 */   addiu     $v0, $zero, 0x1
/* 23340 80032B40 CA5A010C */  jal        func_80056B28
/* 23344 80032B44 21200000 */   addu      $a0, $zero, $zero
/* 23348 80032B48 B55B010C */  jal        SpuUpdate
/* 2334C 80032B4C 01001024 */   addiu     $s0, $zero, 0x1
/* 23350 80032B50 0880033C */  lui        $v1, %hi(g_TitlescreenState + 0x1C)
/* 23354 80032B54 948D638C */  lw         $v1, %lo(g_TitlescreenState + 0x1C)($v1)
/* 23358 80032B58 0880013C */  lui        $at, %hi(g_TitlescreenState + 0x4)
/* 2335C 80032B5C 7C8D30AC */  sw         $s0, %lo(g_TitlescreenState + 0x4)($at)
/* 23360 80032B60 0D006014 */  bnez       $v1, .L80032B98
/* 23364 80032B64 00000000 */   nop
/* 23368 80032B68 0180023C */  lui        $v0, %hi(g_OverlaySpacePointer)
/* 2336C 80032B6C A013428C */  lw         $v0, %lo(g_OverlaySpacePointer)($v0)
/* 23370 80032B70 0780013C */  lui        $at, %hi(g_CutsceneIdx)
/* 23374 80032B74 6C5630AC */  sw         $s0, %lo(g_CutsceneIdx)($at)
/* 23378 80032B78 0780013C */  lui        $at, %hi(g_LoadStage)
/* 2337C 80032B7C 645820AC */  sw         $zero, %lo(g_LoadStage)($at)
/* 23380 80032B80 0880013C */  lui        $at, %hi(D_800785D8)
/* 23384 80032B84 D88522AC */  sw         $v0, %lo(D_800785D8)($at)
/* 23388 80032B88 0880013C */  lui        $at, %hi(D_800785D8 + 0x4)
/* 2338C 80032B8C DC8522AC */  sw         $v0, %lo(D_800785D8 + 0x4)($at)
/* 23390 80032B90 0CCB0008 */  j          .L80032C30
/* 23394 80032B94 00040224 */   addiu     $v0, $zero, 0x400
.L80032B98:
/* 23398 80032B98 0D007014 */  bne        $v1, $s0, .L80032BD0
/* 2339C 80032B9C 02000224 */   addiu     $v0, $zero, 0x2
/* 233A0 80032BA0 0780023C */  lui        $v0, %hi(g_LevelId)
/* 233A4 80032BA4 6C59428C */  lw         $v0, %lo(g_LevelId)($v0)
/* 233A8 80032BA8 0780013C */  lui        $at, %hi(D_80075690)
/* 233AC 80032BAC 905620AC */  sw         $zero, %lo(D_80075690)($at)
/* 233B0 80032BB0 0780013C */  lui        $at, %hi(g_LoadStage)
/* 233B4 80032BB4 645830AC */  sw         $s0, %lo(g_LoadStage)($at)
/* 233B8 80032BB8 0780013C */  lui        $at, %hi(g_PortalLevelId)
/* 233BC 80032BBC AC5820AC */  sw         $zero, %lo(g_PortalLevelId)($at)
/* 233C0 80032BC0 0780013C */  lui        $at, %hi(D_800756D0)
/* 233C4 80032BC4 D05620AC */  sw         $zero, %lo(D_800756D0)($at)
/* 233C8 80032BC8 09CB0008 */  j          .L80032C24
/* 233CC 80032BCC 00000000 */   nop
.L80032BD0:
/* 233D0 80032BD0 17006214 */  bne        $v1, $v0, .L80032C30
/* 233D4 80032BD4 00040224 */   addiu     $v0, $zero, 0x400
/* 233D8 80032BD8 DF49000C */  jal        func_8001277C
/* 233DC 80032BDC 00000000 */   nop
/* 233E0 80032BE0 0780023C */  lui        $v0, %hi(D_800757B8)
/* 233E4 80032BE4 B857428C */  lw         $v0, %lo(D_800757B8)($v0)
/* 233E8 80032BE8 00000000 */  nop
/* 233EC 80032BEC 80100200 */  sll        $v0, $v0, 2
/* 233F0 80032BF0 0780013C */  lui        $at, %hi(D_8006EE7C)
/* 233F4 80032BF4 21082200 */  addu       $at, $at, $v0
/* 233F8 80032BF8 7CEE228C */  lw         $v0, %lo(D_8006EE7C)($at)
/* 233FC 80032BFC 0780013C */  lui        $at, %hi(D_80075690)
/* 23400 80032C00 905620AC */  sw         $zero, %lo(D_80075690)($at)
/* 23404 80032C04 0780013C */  lui        $at, %hi(g_LoadStage)
/* 23408 80032C08 645830AC */  sw         $s0, %lo(g_LoadStage)($at)
/* 2340C 80032C0C 0780013C */  lui        $at, %hi(g_PortalLevelId)
/* 23410 80032C10 AC5820AC */  sw         $zero, %lo(g_PortalLevelId)($at)
/* 23414 80032C14 0780013C */  lui        $at, %hi(D_800756D0)
/* 23418 80032C18 D05620AC */  sw         $zero, %lo(D_800756D0)($at)
/* 2341C 80032C1C 0780013C */  lui        $at, %hi(g_LevelId)
/* 23420 80032C20 6C5922AC */  sw         $v0, %lo(g_LevelId)($at)
.L80032C24:
/* 23424 80032C24 0780013C */  lui        $at, %hi(g_NextLevelId)
/* 23428 80032C28 B45822AC */  sw         $v0, %lo(g_NextLevelId)($at)
/* 2342C 80032C2C 00040224 */  addiu      $v0, $zero, 0x400
.L80032C30:
/* 23430 80032C30 0780013C */  lui        $at, %hi(g_Camera + 0x50)
/* 23434 80032C34 206E22A4 */  sh         $v0, %lo(g_Camera + 0x50)($at)
/* 23438 80032C38 00200224 */  addiu      $v0, $zero, 0x2000
/* 2343C 80032C3C 0780013C */  lui        $at, %hi(g_Camera + 0x4C)
/* 23440 80032C40 1C6E20A4 */  sh         $zero, %lo(g_Camera + 0x4C)($at)
/* 23444 80032C44 0780013C */  lui        $at, %hi(g_Camera + 0x4E)
/* 23448 80032C48 1E6E20A4 */  sh         $zero, %lo(g_Camera + 0x4E)($at)
/* 2344C 80032C4C 0780013C */  lui        $at, %hi(g_Camera + 0x28)
/* 23450 80032C50 F86D22AC */  sw         $v0, %lo(g_Camera + 0x28)($at)
/* 23454 80032C54 0780013C */  lui        $at, %hi(g_Camera + 0x2C)
/* 23458 80032C58 FC6D20AC */  sw         $zero, %lo(g_Camera + 0x2C)($at)
/* 2345C 80032C5C 0780013C */  lui        $at, %hi(g_Camera + 0x30)
/* 23460 80032C60 006E22AC */  sw         $v0, %lo(g_Camera + 0x30)($at)
/* 23464 80032C64 092B010C */  jal        func_8004AC24
/* 23468 80032C68 01000424 */   addiu     $a0, $zero, 0x1
/* 2346C 80032C6C 80270224 */  addiu      $v0, $zero, 0x2780
/* 23470 80032C70 0880013C */  lui        $at, %hi(g_Spyro)
/* 23474 80032C74 588A22AC */  sw         $v0, %lo(g_Spyro)($at)
/* 23478 80032C78 000F0224 */  addiu      $v0, $zero, 0xF00
/* 2347C 80032C7C 0880013C */  lui        $at, %hi(g_Spyro + 0x4)
/* 23480 80032C80 5C8A22AC */  sw         $v0, %lo(g_Spyro + 0x4)($at)
/* 23484 80032C84 A0290224 */  addiu      $v0, $zero, 0x29A0
/* 23488 80032C88 0880013C */  lui        $at, %hi(g_Spyro + 0x8)
/* 2348C 80032C8C 608A22AC */  sw         $v0, %lo(g_Spyro + 0x8)($at)
/* 23490 80032C90 10000224 */  addiu      $v0, $zero, 0x10
/* 23494 80032C94 0880013C */  lui        $at, %hi(g_Spyro + 0x18)
/* 23498 80032C98 708A22A0 */  sb         $v0, %lo(g_Spyro + 0x18)($at)
/* 2349C 80032C9C 0880013C */  lui        $at, %hi(g_Spyro + 0x19)
/* 234A0 80032CA0 718A22A0 */  sb         $v0, %lo(g_Spyro + 0x19)($at)
/* 234A4 80032CA4 01000224 */  addiu      $v0, $zero, 0x1
/* 234A8 80032CA8 0880013C */  lui        $at, %hi(g_Spyro + 0xC)
/* 234AC 80032CAC 648A20A0 */  sb         $zero, %lo(g_Spyro + 0xC)($at)
/* 234B0 80032CB0 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 234B4 80032CB4 658A20A0 */  sb         $zero, %lo(g_Spyro + 0xD)($at)
/* 234B8 80032CB8 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 234BC 80032CBC 668A20A0 */  sb         $zero, %lo(g_Spyro + 0xE)($at)
/* 234C0 80032CC0 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 234C4 80032CC4 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 234C8 80032CC8 5CCC0008 */  j          .L80033170
/* 234CC 80032CCC 00000000 */   nop
.L80032CD0:
/* 234D0 80032CD0 28006214 */  bne        $v1, $v0, .L80032D74
/* 234D4 80032CD4 02000224 */   addiu     $v0, $zero, 0x2
/* 234D8 80032CD8 0880023C */  lui        $v0, %hi(g_TitlescreenState + 0x1C)
/* 234DC 80032CDC 948D428C */  lw         $v0, %lo(g_TitlescreenState + 0x1C)($v0)
/* 234E0 80032CE0 00000000 */  nop
/* 234E4 80032CE4 17004014 */  bnez       $v0, .L80032D44
/* 234E8 80032CE8 00000000 */   nop
/* 234EC 80032CEC 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 234F0 80032CF0 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 234F4 80032CF4 00000000 */  nop
/* 234F8 80032CF8 03004228 */  slti       $v0, $v0, 0x3
/* 234FC 80032CFC 17004010 */  beqz       $v0, .L80032D5C
/* 23500 80032D00 02000224 */   addiu     $v0, $zero, 0x2
.L80032D04:
/* 23504 80032D04 5951000C */  jal        LoadCutscene
/* 23508 80032D08 00000000 */   nop
/* 2350C 80032D0C F8AE000C */  jal        func_8002BBE0
/* 23510 80032D10 00000000 */   nop
/* 23514 80032D14 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 23518 80032D18 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 2351C 80032D1C 00000000 */  nop
/* 23520 80032D20 03004228 */  slti       $v0, $v0, 0x3
/* 23524 80032D24 F7FF4014 */  bnez       $v0, .L80032D04
/* 23528 80032D28 02000224 */   addiu     $v0, $zero, 0x2
/* 2352C 80032D2C 57CB0008 */  j          .L80032D5C
/* 23530 80032D30 00000000 */   nop
.L80032D34:
/* 23534 80032D34 DC54000C */  jal        LoadLevel
/* 23538 80032D38 01000424 */   addiu     $a0, $zero, 0x1
/* 2353C 80032D3C F8AE000C */  jal        func_8002BBE0
/* 23540 80032D40 00000000 */   nop
.L80032D44:
/* 23544 80032D44 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 23548 80032D48 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 2354C 80032D4C 00000000 */  nop
/* 23550 80032D50 06004228 */  slti       $v0, $v0, 0x6
/* 23554 80032D54 F7FF4014 */  bnez       $v0, .L80032D34
/* 23558 80032D58 02000224 */   addiu     $v0, $zero, 0x2
.L80032D5C:
/* 2355C 80032D5C 0880013C */  lui        $at, %hi(g_TitlescreenState + 0x4)
/* 23560 80032D60 7C8D22AC */  sw         $v0, %lo(g_TitlescreenState + 0x4)($at)
/* 23564 80032D64 0880013C */  lui        $at, %hi(g_TitlescreenState + 0x8)
/* 23568 80032D68 808D20AC */  sw         $zero, %lo(g_TitlescreenState + 0x8)($at)
/* 2356C 80032D6C 5CCC0008 */  j          .L80033170
/* 23570 80032D70 00000000 */   nop
.L80032D74:
/* 23574 80032D74 FE006214 */  bne        $v1, $v0, .L80033170
/* 23578 80032D78 1000A427 */   addiu     $a0, $sp, 0x10
/* 2357C 80032D7C 0880123C */  lui        $s2, %hi(g_Spyro)
/* 23580 80032D80 588A5226 */  addiu      $s2, $s2, %lo(g_Spyro)
/* 23584 80032D84 C05D000C */  jal        VecCopy
/* 23588 80032D88 21284002 */   addu      $a1, $s2, $zero
/* 2358C 80032D8C 0880043C */  lui        $a0, %hi(g_TitlescreenState + 0x8)
/* 23590 80032D90 808D848C */  lw         $a0, %lo(g_TitlescreenState + 0x8)($a0)
/* 23594 80032D94 00000000 */  nop
/* 23598 80032D98 50008228 */  slti       $v0, $a0, 0x50
/* 2359C 80032D9C 29004010 */  beqz       $v0, .L80032E44
/* 235A0 80032DA0 6666103C */   lui       $s0, (0x66666667 >> 16)
/* 235A4 80032DA4 67661036 */  ori        $s0, $s0, (0x66666667 & 0xFFFF)
/* 235A8 80032DA8 23200400 */  negu       $a0, $a0
/* 235AC 80032DAC 80220400 */  sll        $a0, $a0, 10
/* 235B0 80032DB0 18009000 */  mult       $a0, $s0
/* 235B4 80032DB4 C3270400 */  sra        $a0, $a0, 31
/* 235B8 80032DB8 10400000 */  mfhi       $t0
/* 235BC 80032DBC 43110800 */  sra        $v0, $t0, 5
/* 235C0 80032DC0 2C5B000C */  jal        Cos
/* 235C4 80032DC4 23204400 */   subu      $a0, $v0, $a0
/* 235C8 80032DC8 0880043C */  lui        $a0, %hi(g_TitlescreenState + 0x8)
/* 235CC 80032DCC 808D848C */  lw         $a0, %lo(g_TitlescreenState + 0x8)($a0)
/* 235D0 80032DD0 00000000 */  nop
/* 235D4 80032DD4 23200400 */  negu       $a0, $a0
/* 235D8 80032DD8 80220400 */  sll        $a0, $a0, 10
/* 235DC 80032DDC 18009000 */  mult       $a0, $s0
/* 235E0 80032DE0 80174224 */  addiu      $v0, $v0, 0x1780
/* 235E4 80032DE4 000042AE */  sw         $v0, 0x0($s2)
/* 235E8 80032DE8 C3270400 */  sra        $a0, $a0, 31
/* 235EC 80032DEC 10400000 */  mfhi       $t0
/* 235F0 80032DF0 43110800 */  sra        $v0, $t0, 5
/* 235F4 80032DF4 165B000C */  jal        Sin
/* 235F8 80032DF8 23204400 */   subu      $a0, $v0, $a0
/* 235FC 80032DFC 0880043C */  lui        $a0, %hi(g_TitlescreenState + 0x8)
/* 23600 80032E00 808D848C */  lw         $a0, %lo(g_TitlescreenState + 0x8)($a0)
/* 23604 80032E04 00000000 */  nop
/* 23608 80032E08 23200400 */  negu       $a0, $a0
/* 2360C 80032E0C 80220400 */  sll        $a0, $a0, 10
/* 23610 80032E10 18009000 */  mult       $a0, $s0
/* 23614 80032E14 43100200 */  sra        $v0, $v0, 1
/* 23618 80032E18 800E4224 */  addiu      $v0, $v0, 0xE80
/* 2361C 80032E1C 0880013C */  lui        $at, %hi(g_Spyro + 0x4)
/* 23620 80032E20 5C8A22AC */  sw         $v0, %lo(g_Spyro + 0x4)($at)
/* 23624 80032E24 C3270400 */  sra        $a0, $a0, 31
/* 23628 80032E28 10400000 */  mfhi       $t0
/* 2362C 80032E2C 43110800 */  sra        $v0, $t0, 5
/* 23630 80032E30 165B000C */  jal        Sin
/* 23634 80032E34 23204400 */   subu      $a0, $v0, $a0
/* 23638 80032E38 43100200 */  sra        $v0, $v0, 1
/* 2363C 80032E3C DFCB0008 */  j          .L80032F7C
/* 23640 80032E40 80294224 */   addiu     $v0, $v0, 0x2980
.L80032E44:
/* 23644 80032E44 78008228 */  slti       $v0, $a0, 0x78
/* 23648 80032E48 07004010 */  beqz       $v0, .L80032E68
/* 2364C 80032E4C 00140224 */   addiu     $v0, $zero, 0x1400
/* 23650 80032E50 000042AE */  sw         $v0, 0x0($s2)
/* 23654 80032E54 000C0224 */  addiu      $v0, $zero, 0xC00
/* 23658 80032E58 0880013C */  lui        $at, %hi(g_Spyro + 0x4)
/* 2365C 80032E5C 5C8A22AC */  sw         $v0, %lo(g_Spyro + 0x4)($at)
/* 23660 80032E60 DFCB0008 */  j          .L80032F7C
/* 23664 80032E64 C0200224 */   addiu     $v0, $zero, 0x20C0
.L80032E68:
/* 23668 80032E68 C8008228 */  slti       $v0, $a0, 0xC8
/* 2366C 80032E6C 06004010 */  beqz       $v0, .L80032E88
/* 23670 80032E70 F0008228 */   slti      $v0, $a0, 0xF0
/* 23674 80032E74 0000428E */  lw         $v0, 0x0($s2)
/* 23678 80032E78 00000000 */  nop
/* 2367C 80032E7C 4C004224 */  addiu      $v0, $v0, 0x4C
/* 23680 80032E80 E1CB0008 */  j          .L80032F84
/* 23684 80032E84 000042AE */   sw        $v0, 0x0($s2)
.L80032E88:
/* 23688 80032E88 07004010 */  beqz       $v0, .L80032EA8
/* 2368C 80032E8C 80280224 */   addiu     $v0, $zero, 0x2880
/* 23690 80032E90 000042AE */  sw         $v0, 0x0($s2)
/* 23694 80032E94 80060224 */  addiu      $v0, $zero, 0x680
/* 23698 80032E98 0880013C */  lui        $at, %hi(g_Spyro + 0x4)
/* 2369C 80032E9C 5C8A22AC */  sw         $v0, %lo(g_Spyro + 0x4)($at)
/* 236A0 80032EA0 DFCB0008 */  j          .L80032F7C
/* 236A4 80032EA4 80210224 */   addiu     $v0, $zero, 0x2180
.L80032EA8:
/* 236A8 80032EA8 40018228 */  slti       $v0, $a0, 0x140
/* 236AC 80032EAC 2D004010 */  beqz       $v0, .L80032F64
/* 236B0 80032EB0 6666103C */   lui       $s0, (0x66666667 >> 16)
/* 236B4 80032EB4 67661036 */  ori        $s0, $s0, (0x66666667 & 0xFFFF)
/* 236B8 80032EB8 10FF8224 */  addiu      $v0, $a0, -0xF0
/* 236BC 80032EBC 80120200 */  sll        $v0, $v0, 10
/* 236C0 80032EC0 18005000 */  mult       $v0, $s0
/* 236C4 80032EC4 C3170200 */  sra        $v0, $v0, 31
/* 236C8 80032EC8 000C1124 */  addiu      $s1, $zero, 0xC00
/* 236CC 80032ECC 10400000 */  mfhi       $t0
/* 236D0 80032ED0 43210800 */  sra        $a0, $t0, 5
/* 236D4 80032ED4 23208200 */  subu       $a0, $a0, $v0
/* 236D8 80032ED8 2C5B000C */  jal        Cos
/* 236DC 80032EDC 23202402 */   subu      $a0, $s1, $a0
/* 236E0 80032EE0 0880033C */  lui        $v1, %hi(g_TitlescreenState + 0x8)
/* 236E4 80032EE4 808D638C */  lw         $v1, %lo(g_TitlescreenState + 0x8)($v1)
/* 236E8 80032EE8 00000000 */  nop
/* 236EC 80032EEC 10FF6324 */  addiu      $v1, $v1, -0xF0
/* 236F0 80032EF0 801A0300 */  sll        $v1, $v1, 10
/* 236F4 80032EF4 18007000 */  mult       $v1, $s0
/* 236F8 80032EF8 80284224 */  addiu      $v0, $v0, 0x2880
/* 236FC 80032EFC 000042AE */  sw         $v0, 0x0($s2)
/* 23700 80032F00 C31F0300 */  sra        $v1, $v1, 31
/* 23704 80032F04 10400000 */  mfhi       $t0
/* 23708 80032F08 43210800 */  sra        $a0, $t0, 5
/* 2370C 80032F0C 23208300 */  subu       $a0, $a0, $v1
/* 23710 80032F10 165B000C */  jal        Sin
/* 23714 80032F14 23202402 */   subu      $a0, $s1, $a0
/* 23718 80032F18 0880033C */  lui        $v1, %hi(g_TitlescreenState + 0x8)
/* 2371C 80032F1C 808D638C */  lw         $v1, %lo(g_TitlescreenState + 0x8)($v1)
/* 23720 80032F20 00000000 */  nop
/* 23724 80032F24 10FF6324 */  addiu      $v1, $v1, -0xF0
/* 23728 80032F28 801A0300 */  sll        $v1, $v1, 10
/* 2372C 80032F2C 18007000 */  mult       $v1, $s0
/* 23730 80032F30 43100200 */  sra        $v0, $v0, 1
/* 23734 80032F34 800E4224 */  addiu      $v0, $v0, 0xE80
/* 23738 80032F38 0880013C */  lui        $at, %hi(g_Spyro + 0x4)
/* 2373C 80032F3C 5C8A22AC */  sw         $v0, %lo(g_Spyro + 0x4)($at)
/* 23740 80032F40 C31F0300 */  sra        $v1, $v1, 31
/* 23744 80032F44 10400000 */  mfhi       $t0
/* 23748 80032F48 43210800 */  sra        $a0, $t0, 5
/* 2374C 80032F4C 23208300 */  subu       $a0, $a0, $v1
/* 23750 80032F50 165B000C */  jal        Sin
/* 23754 80032F54 000C8424 */   addiu     $a0, $a0, 0xC00
/* 23758 80032F58 43100200 */  sra        $v0, $v0, 1
/* 2375C 80032F5C DFCB0008 */  j          .L80032F7C
/* 23760 80032F60 80294224 */   addiu     $v0, $v0, 0x2980
.L80032F64:
/* 23764 80032F64 00200224 */  addiu      $v0, $zero, 0x2000
/* 23768 80032F68 000042AE */  sw         $v0, 0x0($s2)
/* 2376C 80032F6C 00100224 */  addiu      $v0, $zero, 0x1000
/* 23770 80032F70 0880013C */  lui        $at, %hi(g_Spyro + 0x4)
/* 23774 80032F74 5C8A22AC */  sw         $v0, %lo(g_Spyro + 0x4)($at)
/* 23778 80032F78 00400224 */  addiu      $v0, $zero, 0x4000
.L80032F7C:
/* 2377C 80032F7C 0880013C */  lui        $at, %hi(g_Spyro + 0x8)
/* 23780 80032F80 608A22AC */  sw         $v0, %lo(g_Spyro + 0x8)($at)
.L80032F84:
/* 23784 80032F84 1000A427 */  addiu      $a0, $sp, 0x10
/* 23788 80032F88 0880053C */  lui        $a1, %hi(g_Spyro)
/* 2378C 80032F8C 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
/* 23790 80032F90 E35D000C */  jal        VecSub
/* 23794 80032F94 21308000 */   addu      $a2, $a0, $zero
/* 23798 80032F98 1000A427 */  addiu      $a0, $sp, 0x10
/* 2379C 80032F9C 7F5C000C */  jal        VecMagnitude
/* 237A0 80032FA0 21280000 */   addu      $a1, $zero, $zero
/* 237A4 80032FA4 21204000 */  addu       $a0, $v0, $zero
/* 237A8 80032FA8 1800A58F */  lw         $a1, 0x18($sp)
/* 237AC 80032FAC AD5A000C */  jal        Atan2
/* 237B0 80032FB0 21300000 */   addu      $a2, $zero, $zero
/* 237B4 80032FB4 1000A48F */  lw         $a0, 0x10($sp)
/* 237B8 80032FB8 1400A58F */  lw         $a1, 0x14($sp)
/* 237BC 80032FBC 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 237C0 80032FC0 658A22A0 */  sb         $v0, %lo(g_Spyro + 0xD)($at)
/* 237C4 80032FC4 AD5A000C */  jal        Atan2
/* 237C8 80032FC8 21300000 */   addu      $a2, $zero, $zero
/* 237CC 80032FCC 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 237D0 80032FD0 668A22A0 */  sb         $v0, %lo(g_Spyro + 0xE)($at)
/* 237D4 80032FD4 C9F2000C */  jal        func_8003CB24
/* 237D8 80032FD8 03000424 */   addiu     $a0, $zero, 0x3
/* 237DC 80032FDC 9825010C */  jal        func_80049660
/* 237E0 80032FE0 00000000 */   nop
/* 237E4 80032FE4 A327010C */  jal        func_80049E8C
/* 237E8 80032FE8 00000000 */   nop
/* 237EC 80032FEC 0880103C */  lui        $s0, %hi(g_TitlescreenState + 0x1C)
/* 237F0 80032FF0 948D1026 */  addiu      $s0, $s0, %lo(g_TitlescreenState + 0x1C)
/* 237F4 80032FF4 0000028E */  lw         $v0, 0x0($s0)
/* 237F8 80032FF8 00000000 */  nop
/* 237FC 80032FFC 3B004014 */  bnez       $v0, .L800330EC
/* 23800 80033000 00000000 */   nop
/* 23804 80033004 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 23808 80033008 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 2380C 8003300C 00000000 */  nop
/* 23810 80033010 07004228 */  slti       $v0, $v0, 0x7
/* 23814 80033014 03004010 */  beqz       $v0, .L80033024
/* 23818 80033018 00000000 */   nop
/* 2381C 8003301C 5951000C */  jal        LoadCutscene
/* 23820 80033020 00000000 */   nop
.L80033024:
/* 23824 80033024 0880023C */  lui        $v0, %hi(g_TitlescreenState + 0x8)
/* 23828 80033028 808D428C */  lw         $v0, %lo(g_TitlescreenState + 0x8)($v0)
/* 2382C 8003302C 00000000 */  nop
/* 23830 80033030 80014228 */  slti       $v0, $v0, 0x180
/* 23834 80033034 4E004014 */  bnez       $v0, .L80033170
/* 23838 80033038 07000224 */   addiu     $v0, $zero, 0x7
/* 2383C 8003303C 0780033C */  lui        $v1, %hi(g_LoadStage)
/* 23840 80033040 6458638C */  lw         $v1, %lo(g_LoadStage)($v1)
/* 23844 80033044 00000000 */  nop
/* 23848 80033048 49006214 */  bne        $v1, $v0, .L80033170
/* 2384C 8003304C 2000A427 */   addiu     $a0, $sp, 0x20
/* 23850 80033050 21280000 */  addu       $a1, $zero, $zero
/* 23854 80033054 21300000 */  addu       $a2, $zero, $zero
/* 23858 80033058 00020224 */  addiu      $v0, $zero, 0x200
/* 2385C 8003305C 2400A2A7 */  sh         $v0, 0x24($sp)
/* 23860 80033060 E0010224 */  addiu      $v0, $zero, 0x1E0
/* 23864 80033064 21380000 */  addu       $a3, $zero, $zero
/* 23868 80033068 2000A0A7 */  sh         $zero, 0x20($sp)
/* 2386C 8003306C 2200A0A7 */  sh         $zero, 0x22($sp)
/* 23870 80033070 3E7E010C */  jal        ClearImage
/* 23874 80033074 2600A2A7 */   sh        $v0, 0x26($sp)
/* 23878 80033078 D97D010C */  jal        DrawSync
/* 2387C 8003307C 21200000 */   addu      $a0, $zero, $zero
/* 23880 80033080 0780033C */  lui        $v1, %hi(_stacksize)
/* 23884 80033084 A455638C */  lw         $v1, %lo(_stacksize)($v1)
/* 23888 80033088 2080023C */  lui        $v0, (0x80200000 >> 16)
/* 2388C 8003308C 23104300 */  subu       $v0, $v0, $v1
/* 23890 80033090 0880013C */  lui        $at, %hi(D_800785D8 + 0x24)
/* 23894 80033094 FC8522AC */  sw         $v0, %lo(D_800785D8 + 0x24)($at)
/* 23898 80033098 BE6D010C */  jal        AllocateBuffers
/* 2389C 8003309C 01000424 */   addiu     $a0, $zero, 0x1
/* 238A0 800330A0 2ECC0008 */  j          .L800330B8
/* 238A4 800330A4 00000000 */   nop
.L800330A8:
/* 238A8 800330A8 5951000C */  jal        LoadCutscene
/* 238AC 800330AC 00000000 */   nop
/* 238B0 800330B0 F8AE000C */  jal        func_8002BBE0
/* 238B4 800330B4 00000000 */   nop
.L800330B8:
/* 238B8 800330B8 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 238BC 800330BC 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 238C0 800330C0 00000000 */  nop
/* 238C4 800330C4 0A004228 */  slti       $v0, $v0, 0xA
/* 238C8 800330C8 F7FF4014 */  bnez       $v0, .L800330A8
/* 238CC 800330CC 00000000 */   nop
/* 238D0 800330D0 CEB4000C */  jal        StartCutscenePlayback
/* 238D4 800330D4 00000000 */   nop
/* 238D8 800330D8 01000224 */  addiu      $v0, $zero, 0x1
/* 238DC 800330DC 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 238E0 800330E0 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 238E4 800330E4 64CC0008 */  j          .L80033190
/* 238E8 800330E8 00000000 */   nop
.L800330EC:
/* 238EC 800330EC 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 238F0 800330F0 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 238F4 800330F4 00000000 */  nop
/* 238F8 800330F8 0D004228 */  slti       $v0, $v0, 0xD
/* 238FC 800330FC 03004010 */  beqz       $v0, .L8003310C
/* 23900 80033100 00000000 */   nop
/* 23904 80033104 DC54000C */  jal        LoadLevel
/* 23908 80033108 01000424 */   addiu     $a0, $zero, 0x1
.L8003310C:
/* 2390C 8003310C 0880023C */  lui        $v0, %hi(g_TitlescreenState + 0x8)
/* 23910 80033110 808D428C */  lw         $v0, %lo(g_TitlescreenState + 0x8)($v0)
/* 23914 80033114 00000000 */  nop
/* 23918 80033118 80014228 */  slti       $v0, $v0, 0x180
/* 2391C 8003311C 14004014 */  bnez       $v0, .L80033170
/* 23920 80033120 0D000224 */   addiu     $v0, $zero, 0xD
/* 23924 80033124 0780033C */  lui        $v1, %hi(g_LoadStage)
/* 23928 80033128 6458638C */  lw         $v1, %lo(g_LoadStage)($v1)
/* 2392C 8003312C 00000000 */  nop
/* 23930 80033130 0F006214 */  bne        $v1, $v0, .L80033170
/* 23934 80033134 02000224 */   addiu     $v0, $zero, 0x2
/* 23938 80033138 0000038E */  lw         $v1, 0x0($s0)
/* 2393C 8003313C 00000000 */  nop
/* 23940 80033140 05006214 */  bne        $v1, $v0, .L80033158
/* 23944 80033144 01000224 */   addiu     $v0, $zero, 0x1
/* 23948 80033148 0780013C */  lui        $at, %hi(g_DemoMode)
/* 2394C 8003314C 145722AC */  sw         $v0, %lo(g_DemoMode)($at)
/* 23950 80033150 0780013C */  lui        $at, %hi(D_80075884)
/* 23954 80033154 845820AC */  sw         $zero, %lo(D_80075884)($at)
.L80033158:
/* 23958 80033158 092B010C */  jal        func_8004AC24
/* 2395C 8003315C 01000424 */   addiu     $a0, $zero, 0x1
/* 23960 80033160 DC54000C */  jal        LoadLevel
/* 23964 80033164 01000424 */   addiu     $a0, $zero, 0x1
/* 23968 80033168 64CC0008 */  j          .L80033190
/* 2396C 8003316C 00000000 */   nop
.L80033170:
/* 23970 80033170 3063010C */  jal        SpecularUpdate
/* 23974 80033174 03000424 */   addiu     $a0, $zero, 0x3
/* 23978 80033178 0880033C */  lui        $v1, %hi(g_TitlescreenState + 0x8)
/* 2397C 8003317C 808D6324 */  addiu      $v1, $v1, %lo(g_TitlescreenState + 0x8)
/* 23980 80033180 0000628C */  lw         $v0, 0x0($v1)
/* 23984 80033184 00000000 */  nop
/* 23988 80033188 01004224 */  addiu      $v0, $v0, 0x1
/* 2398C 8003318C 000062AC */  sw         $v0, 0x0($v1)
.L80033190:
/* 23990 80033190 3400BF8F */  lw         $ra, 0x34($sp)
/* 23994 80033194 3000B28F */  lw         $s2, 0x30($sp)
/* 23998 80033198 2C00B18F */  lw         $s1, 0x2C($sp)
/* 2399C 8003319C 2800B08F */  lw         $s0, 0x28($sp)
/* 239A0 800331A0 3800BD27 */  addiu      $sp, $sp, 0x38
/* 239A4 800331A4 0800E003 */  jr         $ra
/* 239A8 800331A8 00000000 */   nop
.size func_80032B08, . - func_80032B08
