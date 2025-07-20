.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_800499C0
/* 3A1C0 800499C0 0880023C */  lui        $v0, %hi(g_Spyro + 0x78)
/* 3A1C4 800499C4 D08A428C */  lw         $v0, %lo(g_Spyro + 0x78)($v0)
/* 3A1C8 800499C8 C0FFBD27 */  addiu      $sp, $sp, -0x40
/* 3A1CC 800499CC 3800BFAF */  sw         $ra, 0x38($sp)
/* 3A1D0 800499D0 3400B1AF */  sw         $s1, 0x34($sp)
/* 3A1D4 800499D4 3000B0AF */  sw         $s0, 0x30($sp)
/* 3A1D8 800499D8 0780013C */  lui        $at, %hi(spyro_StateDefaultAnimation)
/* 3A1DC 800499DC 21082200 */  addu       $at, $at, $v0
/* 3A1E0 800499E0 70C42290 */  lbu        $v0, %lo(spyro_StateDefaultAnimation)($at)
/* 3A1E4 800499E4 0780013C */  lui        $at, %hi(spyro_FlameBlockedInAnimation)
/* 3A1E8 800499E8 21082200 */  addu       $at, $at, $v0
/* 3A1EC 800499EC 58C52290 */  lbu        $v0, %lo(spyro_FlameBlockedInAnimation)($at)
/* 3A1F0 800499F0 00000000 */  nop
/* 3A1F4 800499F4 08004010 */  beqz       $v0, .L80049A18
/* 3A1F8 800499F8 00000000 */   nop
/* 3A1FC 800499FC 0880043C */  lui        $a0, %hi(g_Spyro + 0x198)
/* 3A200 80049A00 F08B8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0x198)
/* 3A204 80049A04 000080AC */  sw         $zero, 0x0($a0)
/* 3A208 80049A08 BC5D000C */  jal        VecNull
/* 3A20C 80049A0C 0C008424 */   addiu     $a0, $a0, 0xC
/* 3A210 80049A10 77270108 */  j          .L80049DDC
/* 3A214 80049A14 00000000 */   nop
.L80049A18:
/* 3A218 80049A18 0880113C */  lui        $s1, %hi(g_Spyro + 0x198)
/* 3A21C 80049A1C F08B3126 */  addiu      $s1, $s1, %lo(g_Spyro + 0x198)
/* 3A220 80049A20 0000238E */  lw         $v1, 0x0($s1)
/* 3A224 80049A24 00000000 */  nop
/* 3A228 80049A28 05006010 */  beqz       $v1, .L80049A40
/* 3A22C 80049A2C 01000224 */   addiu     $v0, $zero, 0x1
/* 3A230 80049A30 3D006210 */  beq        $v1, $v0, .L80049B28
/* 3A234 80049A34 10000224 */   addiu     $v0, $zero, 0x10
/* 3A238 80049A38 68270108 */  j          .L80049DA0
/* 3A23C 80049A3C 0080033C */   lui       $v1, (0x80000009 >> 16)
.L80049A40:
/* 3A240 80049A40 0780023C */  lui        $v0, %hi(g_Pad)
/* 3A244 80049A44 7873428C */  lw         $v0, %lo(g_Pad)($v0)
/* 3A248 80049A48 0880043C */  lui        $a0, %hi(D_80078762)
/* 3A24C 80049A4C 62878424 */  addiu      $a0, $a0, %lo(D_80078762)
/* 3A250 80049A50 20004230 */  andi       $v0, $v0, 0x20
/* 3A254 80049A54 DB004010 */  beqz       $v0, .L80049DC4
/* 3A258 80049A58 000080A0 */   sb        $zero, 0x0($a0)
/* 3A25C 80049A5C 0880023C */  lui        $v0, %hi(D_80078760)
/* 3A260 80049A60 60874290 */  lbu        $v0, %lo(D_80078760)($v0)
/* 3A264 80049A64 00000000 */  nop
/* 3A268 80049A68 D6004014 */  bnez       $v0, .L80049DC4
/* 3A26C 80049A6C 01001024 */   addiu     $s0, $zero, 0x1
/* 3A270 80049A70 000030AE */  sw         $s0, 0x0($s1)
/* 3A274 80049A74 0880033C */  lui        $v1, %hi(g_Spyro + 0x198)
/* 3A278 80049A78 F08B638C */  lw         $v1, %lo(g_Spyro + 0x198)($v1)
/* 3A27C 80049A7C FFFF0224 */  addiu      $v0, $zero, -0x1
/* 3A280 80049A80 0880013C */  lui        $at, %hi(g_Spyro + 0x1A0)
/* 3A284 80049A84 F88B22AC */  sw         $v0, %lo(g_Spyro + 0x1A0)($at)
/* 3A288 80049A88 0880013C */  lui        $at, %hi(g_Spyro + 0x60)
/* 3A28C 80049A8C B88A20AC */  sw         $zero, %lo(g_Spyro + 0x60)($at)
/* 3A290 80049A90 0780013C */  lui        $at, %hi(D_80075268)
/* 3A294 80049A94 21082300 */  addu       $at, $at, $v1
/* 3A298 80049A98 68522290 */  lbu        $v0, %lo(D_80075268)($at)
/* 3A29C 80049A9C 00000000 */  nop
/* 3A2A0 80049AA0 80100200 */  sll        $v0, $v0, 2
/* 3A2A4 80049AA4 0780013C */  lui        $at, %hi(spyro_AnimationDetails + 0x03)
/* 3A2A8 80049AA8 21082200 */  addu       $at, $at, $v0
/* 3A2AC 80049AAC A3C42390 */  lbu        $v1, %lo(spyro_AnimationDetails + 0x03)($at)
/* 3A2B0 80049AB0 01000224 */  addiu      $v0, $zero, 0x1
/* 3A2B4 80049AB4 0880013C */  lui        $at, %hi(D_80078760)
/* 3A2B8 80049AB8 608722A0 */  sb         $v0, %lo(D_80078760)($at)
/* 3A2BC 80049ABC 0880013C */  lui        $at, %hi(D_80078761)
/* 3A2C0 80049AC0 618720A0 */  sb         $zero, %lo(D_80078761)($at)
/* 3A2C4 80049AC4 000082A0 */  sb         $v0, 0x0($a0)
/* 3A2C8 80049AC8 0880013C */  lui        $at, %hi(g_Spyro + 0x64)
/* 3A2CC 80049ACC BC8A23AC */  sw         $v1, %lo(g_Spyro + 0x64)($at)
/* 3A2D0 80049AD0 CB89010C */  jal        rand
/* 3A2D4 80049AD4 00000000 */   nop
/* 3A2D8 80049AD8 0880033C */  lui        $v1, %hi(D_80078768)
/* 3A2DC 80049ADC 6887638C */  lw         $v1, %lo(D_80078768)($v1)
/* 3A2E0 80049AE0 01004230 */  andi       $v0, $v0, 0x1
/* 3A2E4 80049AE4 0880013C */  lui        $at, %hi(D_80078763)
/* 3A2E8 80049AE8 638722A0 */  sb         $v0, %lo(D_80078763)($at)
/* 3A2EC 80049AEC 05006010 */  beqz       $v1, .L80049B04
/* 3A2F0 80049AF0 00000000 */   nop
/* 3A2F4 80049AF4 0880013C */  lui        $at, %hi(D_80078764)
/* 3A2F8 80049AF8 648730AC */  sw         $s0, %lo(D_80078764)($at)
/* 3A2FC 80049AFC C3260108 */  j          .L80049B0C
/* 3A300 80049B00 00000000 */   nop
.L80049B04:
/* 3A304 80049B04 0880013C */  lui        $at, %hi(D_80078764)
/* 3A308 80049B08 648720AC */  sw         $zero, %lo(D_80078764)($at)
.L80049B0C:
/* 3A30C 80049B0C 0880043C */  lui        $a0, %hi(D_800786E8)
/* 3A310 80049B10 E8868424 */  addiu      $a0, $a0, %lo(D_800786E8)
/* 3A314 80049B14 21280000 */  addu       $a1, $zero, $zero
/* 3A318 80049B18 455A000C */  jal        Memset
/* 3A31C 80049B1C 08000624 */   addiu     $a2, $zero, 0x8
/* 3A320 80049B20 6D270108 */  j          .L80049DB4
/* 3A324 80049B24 00000000 */   nop
.L80049B28:
/* 3A328 80049B28 0880033C */  lui        $v1, %hi(g_Spyro + 0x1A0)
/* 3A32C 80049B2C F88B638C */  lw         $v1, %lo(g_Spyro + 0x1A0)($v1)
/* 3A330 80049B30 00000000 */  nop
/* 3A334 80049B34 07006214 */  bne        $v1, $v0, .L80049B54
/* 3A338 80049B38 03006230 */   andi      $v0, $v1, 0x3
/* 3A33C 80049B3C 0880013C */  lui        $at, %hi(D_80078762)
/* 3A340 80049B40 628720A0 */  sb         $zero, %lo(D_80078762)($at)
/* 3A344 80049B44 0880033C */  lui        $v1, %hi(g_Spyro + 0x1A0)
/* 3A348 80049B48 F88B638C */  lw         $v1, %lo(g_Spyro + 0x1A0)($v1)
/* 3A34C 80049B4C 00000000 */  nop
/* 3A350 80049B50 03006230 */  andi       $v0, $v1, 0x3
.L80049B54:
/* 3A354 80049B54 44004014 */  bnez       $v0, .L80049C68
/* 3A358 80049B58 F4FF6224 */   addiu     $v0, $v1, -0xC
/* 3A35C 80049B5C 1100422C */  sltiu      $v0, $v0, 0x11
/* 3A360 80049B60 41004010 */  beqz       $v0, .L80049C68
/* 3A364 80049B64 00000000 */   nop
/* 3A368 80049B68 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 3A36C 80049B6C 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 3A370 80049B70 00000000 */  nop
/* 3A374 80049B74 3C004104 */  bgez       $v0, .L80049C68
/* 3A378 80049B78 30002426 */   addiu     $a0, $s1, 0x30
/* 3A37C 80049B7C 0780103C */  lui        $s0, %hi(D_8006E238)
/* 3A380 80049B80 38E21026 */  addiu      $s0, $s0, %lo(D_8006E238)
/* 3A384 80049B84 21280002 */  addu       $a1, $s0, $zero
/* 3A388 80049B88 125C000C */  jal        VecRotateByMatrix
/* 3A38C 80049B8C 1000A627 */   addiu     $a2, $sp, 0x10
/* 3A390 80049B90 1000A427 */  addiu      $a0, $sp, 0x10
/* 3A394 80049B94 21288000 */  addu       $a1, $a0, $zero
/* 3A398 80049B98 D65D000C */  jal        VecAdd
/* 3A39C 80049B9C 68FE2626 */   addiu     $a2, $s1, -0x198
/* 3A3A0 80049BA0 18000426 */  addiu      $a0, $s0, 0x18
/* 3A3A4 80049BA4 2000B027 */  addiu      $s0, $sp, 0x20
/* 3A3A8 80049BA8 305C000C */  jal        func_800170C0
/* 3A3AC 80049BAC 21280002 */   addu      $a1, $s0, $zero
/* 3A3B0 80049BB0 0880023C */  lui        $v0, %hi(D_80078764)
/* 3A3B4 80049BB4 6487428C */  lw         $v0, %lo(D_80078764)($v0)
/* 3A3B8 80049BB8 00000000 */  nop
/* 3A3BC 80049BBC 03004010 */  beqz       $v0, .L80049BCC
/* 3A3C0 80049BC0 01000424 */   addiu     $a0, $zero, 0x1
/* 3A3C4 80049BC4 F4260108 */  j          .L80049BD0
/* 3A3C8 80049BC8 01000524 */   addiu     $a1, $zero, 0x1
.L80049BCC:
/* 3A3CC 80049BCC 21280000 */  addu       $a1, $zero, $zero
.L80049BD0:
/* 3A3D0 80049BD0 1000A627 */  addiu      $a2, $sp, 0x10
/* 3A3D4 80049BD4 0780023C */  lui        $v0, %hi(D_800758E4)
/* 3A3D8 80049BD8 E458428C */  lw         $v0, %lo(D_800758E4)($v0)
/* 3A3DC 80049BDC 00000000 */  nop
/* 3A3E0 80049BE0 09F84000 */  jalr       $v0
/* 3A3E4 80049BE4 21380002 */   addu      $a3, $s0, $zero
/* 3A3E8 80049BE8 0880103C */  lui        $s0, %hi(g_Spyro + 0x1C8)
/* 3A3EC 80049BEC 208C1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x1C8)
/* 3A3F0 80049BF0 21200002 */  addu       $a0, $s0, $zero
/* 3A3F4 80049BF4 0780113C */  lui        $s1, %hi(D_8006E244)
/* 3A3F8 80049BF8 44E23126 */  addiu      $s1, $s1, %lo(D_8006E244)
/* 3A3FC 80049BFC 21282002 */  addu       $a1, $s1, $zero
/* 3A400 80049C00 125C000C */  jal        VecRotateByMatrix
/* 3A404 80049C04 1000A627 */   addiu     $a2, $sp, 0x10
/* 3A408 80049C08 1000A427 */  addiu      $a0, $sp, 0x10
/* 3A40C 80049C0C 21288000 */  addu       $a1, $a0, $zero
/* 3A410 80049C10 D65D000C */  jal        VecAdd
/* 3A414 80049C14 38FE0626 */   addiu     $a2, $s0, -0x1C8
/* 3A418 80049C18 18002426 */  addiu      $a0, $s1, 0x18
/* 3A41C 80049C1C 2000B027 */  addiu      $s0, $sp, 0x20
/* 3A420 80049C20 305C000C */  jal        func_800170C0
/* 3A424 80049C24 21280002 */   addu      $a1, $s0, $zero
/* 3A428 80049C28 0880023C */  lui        $v0, %hi(D_80078764)
/* 3A42C 80049C2C 6487428C */  lw         $v0, %lo(D_80078764)($v0)
/* 3A430 80049C30 00000000 */  nop
/* 3A434 80049C34 03004010 */  beqz       $v0, .L80049C44
/* 3A438 80049C38 01000424 */   addiu     $a0, $zero, 0x1
/* 3A43C 80049C3C 12270108 */  j          .L80049C48
/* 3A440 80049C40 01000524 */   addiu     $a1, $zero, 0x1
.L80049C44:
/* 3A444 80049C44 21280000 */  addu       $a1, $zero, $zero
.L80049C48:
/* 3A448 80049C48 1000A627 */  addiu      $a2, $sp, 0x10
/* 3A44C 80049C4C 0780023C */  lui        $v0, %hi(D_800758E4)
/* 3A450 80049C50 E458428C */  lw         $v0, %lo(D_800758E4)($v0)
/* 3A454 80049C54 00000000 */  nop
/* 3A458 80049C58 09F84000 */  jalr       $v0
/* 3A45C 80049C5C 21380002 */   addu      $a3, $s0, $zero
/* 3A460 80049C60 71270108 */  j          .L80049DC4
/* 3A464 80049C64 00000000 */   nop
.L80049C68:
/* 3A468 80049C68 0780023C */  lui        $v0, %hi(g_Pad)
/* 3A46C 80049C6C 7873428C */  lw         $v0, %lo(g_Pad)($v0)
/* 3A470 80049C70 00000000 */  nop
/* 3A474 80049C74 20004230 */  andi       $v0, $v0, 0x20
/* 3A478 80049C78 2E004010 */  beqz       $v0, .L80049D34
/* 3A47C 80049C7C 00000000 */   nop
/* 3A480 80049C80 0880033C */  lui        $v1, %hi(g_Spyro + 0x1A0)
/* 3A484 80049C84 F88B6324 */  addiu      $v1, $v1, %lo(g_Spyro + 0x1A0)
/* 3A488 80049C88 0000628C */  lw         $v0, 0x0($v1)
/* 3A48C 80049C8C 00000000 */  nop
/* 3A490 80049C90 2C004228 */  slti       $v0, $v0, 0x2C
/* 3A494 80049C94 27004014 */  bnez       $v0, .L80049D34
/* 3A498 80049C98 FFFF0224 */   addiu     $v0, $zero, -0x1
/* 3A49C 80049C9C 000062AC */  sw         $v0, 0x0($v1)
/* 3A4A0 80049CA0 02000224 */  addiu      $v0, $zero, 0x2
/* 3A4A4 80049CA4 0880013C */  lui        $at, %hi(g_Spyro + 0x60)
/* 3A4A8 80049CA8 B88A22AC */  sw         $v0, %lo(g_Spyro + 0x60)($at)
/* 3A4AC 80049CAC 04000224 */  addiu      $v0, $zero, 0x4
/* 3A4B0 80049CB0 0880013C */  lui        $at, %hi(g_Spyro + 0x25)
/* 3A4B4 80049CB4 7D8A22A0 */  sb         $v0, %lo(g_Spyro + 0x25)($at)
/* 3A4B8 80049CB8 01000224 */  addiu      $v0, $zero, 0x1
/* 3A4BC 80049CBC 0880013C */  lui        $at, %hi(g_Spyro + 0x21)
/* 3A4C0 80049CC0 798A20A0 */  sb         $zero, %lo(g_Spyro + 0x21)($at)
/* 3A4C4 80049CC4 0880013C */  lui        $at, %hi(D_80078760)
/* 3A4C8 80049CC8 608722A0 */  sb         $v0, %lo(D_80078760)($at)
/* 3A4CC 80049CCC 0880013C */  lui        $at, %hi(D_80078761)
/* 3A4D0 80049CD0 618720A0 */  sb         $zero, %lo(D_80078761)($at)
/* 3A4D4 80049CD4 0880013C */  lui        $at, %hi(D_80078762)
/* 3A4D8 80049CD8 628722A0 */  sb         $v0, %lo(D_80078762)($at)
/* 3A4DC 80049CDC CB89010C */  jal        rand
/* 3A4E0 80049CE0 00000000 */   nop
/* 3A4E4 80049CE4 0880033C */  lui        $v1, %hi(D_80078768)
/* 3A4E8 80049CE8 6887638C */  lw         $v1, %lo(D_80078768)($v1)
/* 3A4EC 80049CEC 01004230 */  andi       $v0, $v0, 0x1
/* 3A4F0 80049CF0 0880013C */  lui        $at, %hi(D_80078763)
/* 3A4F4 80049CF4 638722A0 */  sb         $v0, %lo(D_80078763)($at)
/* 3A4F8 80049CF8 05006010 */  beqz       $v1, .L80049D10
/* 3A4FC 80049CFC 01000224 */   addiu     $v0, $zero, 0x1
/* 3A500 80049D00 0880013C */  lui        $at, %hi(D_80078764)
/* 3A504 80049D04 648722AC */  sw         $v0, %lo(D_80078764)($at)
/* 3A508 80049D08 46270108 */  j          .L80049D18
/* 3A50C 80049D0C 00000000 */   nop
.L80049D10:
/* 3A510 80049D10 0880013C */  lui        $at, %hi(D_80078764)
/* 3A514 80049D14 648720AC */  sw         $zero, %lo(D_80078764)($at)
.L80049D18:
/* 3A518 80049D18 0880043C */  lui        $a0, %hi(D_800786E8)
/* 3A51C 80049D1C E8868424 */  addiu      $a0, $a0, %lo(D_800786E8)
/* 3A520 80049D20 21280000 */  addu       $a1, $zero, $zero
/* 3A524 80049D24 455A000C */  jal        Memset
/* 3A528 80049D28 08000624 */   addiu     $a2, $zero, 0x8
/* 3A52C 80049D2C 71270108 */  j          .L80049DC4
/* 3A530 80049D30 00000000 */   nop
.L80049D34:
/* 3A534 80049D34 0880103C */  lui        $s0, %hi(g_Spyro + 0x1A0)
/* 3A538 80049D38 F88B1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x1A0)
/* 3A53C 80049D3C 0000028E */  lw         $v0, 0x0($s0)
/* 3A540 80049D40 00000000 */  nop
/* 3A544 80049D44 30004228 */  slti       $v0, $v0, 0x30
/* 3A548 80049D48 1E004014 */  bnez       $v0, .L80049DC4
/* 3A54C 80049D4C 21280000 */   addu      $a1, $zero, $zero
/* 3A550 80049D50 0880023C */  lui        $v0, %hi(D_80078760)
/* 3A554 80049D54 60874224 */  addiu      $v0, $v0, %lo(D_80078760)
/* 3A558 80049D58 88FF4424 */  addiu      $a0, $v0, -0x78
/* 3A55C 80049D5C 08000624 */  addiu      $a2, $zero, 0x8
/* 3A560 80049D60 455A000C */  jal        Memset
/* 3A564 80049D64 000040A0 */   sb        $zero, 0x0($v0)
/* 3A568 80049D68 0780023C */  lui        $v0, %hi(D_80075268)
/* 3A56C 80049D6C 68524290 */  lbu        $v0, %lo(D_80075268)($v0)
/* 3A570 80049D70 FFFF0324 */  addiu      $v1, $zero, -0x1
/* 3A574 80049D74 0880013C */  lui        $at, %hi(g_Spyro + 0x198)
/* 3A578 80049D78 F08B20AC */  sw         $zero, %lo(g_Spyro + 0x198)($at)
/* 3A57C 80049D7C 000003AE */  sw         $v1, 0x0($s0)
/* 3A580 80049D80 80100200 */  sll        $v0, $v0, 2
/* 3A584 80049D84 0780013C */  lui        $at, %hi(spyro_AnimationDetails + 0x03)
/* 3A588 80049D88 21082200 */  addu       $at, $at, $v0
/* 3A58C 80049D8C A3C42290 */  lbu        $v0, %lo(spyro_AnimationDetails + 0x03)($at)
/* 3A590 80049D90 0880013C */  lui        $at, %hi(g_Spyro + 0x64)
/* 3A594 80049D94 BC8A22AC */  sw         $v0, %lo(g_Spyro + 0x64)($at)
/* 3A598 80049D98 6F270108 */  j          .L80049DBC
/* 3A59C 80049D9C 04000426 */   addiu     $a0, $s0, 0x4
.L80049DA0:
/* 3A5A0 80049DA0 0780023C */  lui        $v0, %hi(g_Camera + 0x58)
/* 3A5A4 80049DA4 286E428C */  lw         $v0, %lo(g_Camera + 0x58)($v0)
/* 3A5A8 80049DA8 09006334 */  ori        $v1, $v1, (0x80000009 & 0xFFFF)
/* 3A5AC 80049DAC 05004310 */  beq        $v0, $v1, .L80049DC4
/* 3A5B0 80049DB0 00000000 */   nop
.L80049DB4:
/* 3A5B4 80049DB4 0880043C */  lui        $a0, %hi(g_Spyro + 0x1A4)
/* 3A5B8 80049DB8 FC8B8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0x1A4)
.L80049DBC:
/* 3A5BC 80049DBC BC5D000C */  jal        VecNull
/* 3A5C0 80049DC0 00000000 */   nop
.L80049DC4:
/* 3A5C4 80049DC4 0880033C */  lui        $v1, %hi(g_Spyro + 0x1A0)
/* 3A5C8 80049DC8 F88B6324 */  addiu      $v1, $v1, %lo(g_Spyro + 0x1A0)
/* 3A5CC 80049DCC 0000628C */  lw         $v0, 0x0($v1)
/* 3A5D0 80049DD0 00000000 */  nop
/* 3A5D4 80049DD4 01004224 */  addiu      $v0, $v0, 0x1
/* 3A5D8 80049DD8 000062AC */  sw         $v0, 0x0($v1)
.L80049DDC:
/* 3A5DC 80049DDC 2026010C */  jal        func_80049880
/* 3A5E0 80049DE0 00000000 */   nop
/* 3A5E4 80049DE4 3800BF8F */  lw         $ra, 0x38($sp)
/* 3A5E8 80049DE8 3400B18F */  lw         $s1, 0x34($sp)
/* 3A5EC 80049DEC 3000B08F */  lw         $s0, 0x30($sp)
/* 3A5F0 80049DF0 4000BD27 */  addiu      $sp, $sp, 0x40
/* 3A5F4 80049DF4 0800E003 */  jr         $ra
/* 3A5F8 80049DF8 00000000 */   nop
.size func_800499C0, . - func_800499C0
