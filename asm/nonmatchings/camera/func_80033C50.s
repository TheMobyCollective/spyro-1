.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel CameraUpdateMatrices
/* 24450 80033C50 A0FFBD27 */  addiu      $sp, $sp, -0x60
/* 24454 80033C54 1000A427 */  addiu      $a0, $sp, 0x10
/* 24458 80033C58 21280000 */  addu       $a1, $zero, $zero
/* 2445C 80033C5C 20000624 */  addiu      $a2, $zero, 0x20
/* 24460 80033C60 5C00BFAF */  sw         $ra, 0x5C($sp)
/* 24464 80033C64 5800B2AF */  sw         $s2, 0x58($sp)
/* 24468 80033C68 5400B1AF */  sw         $s1, 0x54($sp)
/* 2446C 80033C6C 455A000C */  jal        Memset
/* 24470 80033C70 5000B0AF */   sw        $s0, 0x50($sp)
/* 24474 80033C74 7E89010C */  jal        SetTransMatrix
/* 24478 80033C78 1000A427 */   addiu     $a0, $sp, 0x10
/* 2447C 80033C7C 0780123C */  lui        $s2, %hi(g_Camera + 0x4E)
/* 24480 80033C80 1E6E5226 */  addiu      $s2, $s2, %lo(g_Camera + 0x4E)
/* 24484 80033C84 00004486 */  lh         $a0, 0x0($s2)
/* 24488 80033C88 00101124 */  addiu      $s1, $zero, 0x1000
/* 2448C 80033C8C 2C5B000C */  jal        func_80016CB0
/* 24490 80033C90 1000B1A7 */   sh        $s1, 0x10($sp)
/* 24494 80033C94 00004486 */  lh         $a0, 0x0($s2)
/* 24498 80033C98 165B000C */  jal        func_80016C58
/* 2449C 80033C9C 1800A2A7 */   sh        $v0, 0x18($sp)
/* 244A0 80033CA0 00004486 */  lh         $a0, 0x0($s2)
/* 244A4 80033CA4 165B000C */  jal        func_80016C58
/* 244A8 80033CA8 1E00A2A7 */   sh        $v0, 0x1E($sp)
/* 244AC 80033CAC 00004486 */  lh         $a0, 0x0($s2)
/* 244B0 80033CB0 23100200 */  negu       $v0, $v0
/* 244B4 80033CB4 2C5B000C */  jal        func_80016CB0
/* 244B8 80033CB8 1A00A2A7 */   sh        $v0, 0x1A($sp)
/* 244BC 80033CBC 3000B027 */  addiu      $s0, $sp, 0x30
/* 244C0 80033CC0 21200002 */  addu       $a0, $s0, $zero
/* 244C4 80033CC4 21280000 */  addu       $a1, $zero, $zero
/* 244C8 80033CC8 20000624 */  addiu      $a2, $zero, 0x20
/* 244CC 80033CCC 455A000C */  jal        Memset
/* 244D0 80033CD0 2000A2A7 */   sh        $v0, 0x20($sp)
/* 244D4 80033CD4 0780043C */  lui        $a0, %hi(g_Camera + 0x50)
/* 244D8 80033CD8 206E8484 */  lh         $a0, %lo(g_Camera + 0x50)($a0)
/* 244DC 80033CDC 2C5B000C */  jal        func_80016CB0
/* 244E0 80033CE0 00000000 */   nop
/* 244E4 80033CE4 0780043C */  lui        $a0, %hi(g_Camera + 0x50)
/* 244E8 80033CE8 206E8484 */  lh         $a0, %lo(g_Camera + 0x50)($a0)
/* 244EC 80033CEC 165B000C */  jal        func_80016C58
/* 244F0 80033CF0 3000A2A7 */   sh        $v0, 0x30($sp)
/* 244F4 80033CF4 0780043C */  lui        $a0, %hi(g_Camera + 0x50)
/* 244F8 80033CF8 206E8484 */  lh         $a0, %lo(g_Camera + 0x50)($a0)
/* 244FC 80033CFC 23100200 */  negu       $v0, $v0
/* 24500 80033D00 3C00A2A7 */  sh         $v0, 0x3C($sp)
/* 24504 80033D04 165B000C */  jal        func_80016C58
/* 24508 80033D08 3800B1A7 */   sh        $s1, 0x38($sp)
/* 2450C 80033D0C 0780043C */  lui        $a0, %hi(g_Camera + 0x50)
/* 24510 80033D10 206E8484 */  lh         $a0, %lo(g_Camera + 0x50)($a0)
/* 24514 80033D14 2C5B000C */  jal        func_80016CB0
/* 24518 80033D18 3400A2A7 */   sh        $v0, 0x34($sp)
/* 2451C 80033D1C 1000A427 */  addiu      $a0, $sp, 0x10
/* 24520 80033D20 21280002 */  addu       $a1, $s0, $zero
/* 24524 80033D24 3A89010C */  jal        MulMatrix
/* 24528 80033D28 4000A2A7 */   sh        $v0, 0x40($sp)
/* 2452C 80033D2C 21200002 */  addu       $a0, $s0, $zero
/* 24530 80033D30 21280000 */  addu       $a1, $zero, $zero
/* 24534 80033D34 455A000C */  jal        Memset
/* 24538 80033D38 20000624 */   addiu     $a2, $zero, 0x20
/* 2453C 80033D3C 0780043C */  lui        $a0, %hi(g_Camera + 0x4C)
/* 24540 80033D40 1C6E8484 */  lh         $a0, %lo(g_Camera + 0x4C)($a0)
/* 24544 80033D44 2C5B000C */  jal        func_80016CB0
/* 24548 80033D48 00000000 */   nop
/* 2454C 80033D4C 0780043C */  lui        $a0, %hi(g_Camera + 0x4C)
/* 24550 80033D50 1C6E8484 */  lh         $a0, %lo(g_Camera + 0x4C)($a0)
/* 24554 80033D54 165B000C */  jal        func_80016C58
/* 24558 80033D58 3000A2A7 */   sh        $v0, 0x30($sp)
/* 2455C 80033D5C 0780043C */  lui        $a0, %hi(g_Camera + 0x4C)
/* 24560 80033D60 1C6E8484 */  lh         $a0, %lo(g_Camera + 0x4C)($a0)
/* 24564 80033D64 23100200 */  negu       $v0, $v0
/* 24568 80033D68 165B000C */  jal        func_80016C58
/* 2456C 80033D6C 3600A2A7 */   sh        $v0, 0x36($sp)
/* 24570 80033D70 0780043C */  lui        $a0, %hi(g_Camera + 0x4C)
/* 24574 80033D74 1C6E8484 */  lh         $a0, %lo(g_Camera + 0x4C)($a0)
/* 24578 80033D78 2C5B000C */  jal        func_80016CB0
/* 2457C 80033D7C 3200A2A7 */   sh        $v0, 0x32($sp)
/* 24580 80033D80 1000A427 */  addiu      $a0, $sp, 0x10
/* 24584 80033D84 21280002 */  addu       $a1, $s0, $zero
/* 24588 80033D88 3800A2A7 */  sh         $v0, 0x38($sp)
/* 2458C 80033D8C 3A89010C */  jal        MulMatrix
/* 24590 80033D90 4000B1A7 */   sh        $s1, 0x40($sp)
/* 24594 80033D94 C6FF4426 */  addiu      $a0, $s2, -0x3A
/* 24598 80033D98 1000A527 */  addiu      $a1, $sp, 0x10
/* 2459C 80033D9C 565A000C */  jal        Memcpy
/* 245A0 80033DA0 14000624 */   addiu     $a2, $zero, 0x14
/* 245A4 80033DA4 1600A387 */  lh         $v1, 0x16($sp)
/* 245A8 80033DA8 00000000 */  nop
/* 245AC 80033DAC 80100300 */  sll        $v0, $v1, 2
/* 245B0 80033DB0 21104300 */  addu       $v0, $v0, $v1
/* 245B4 80033DB4 80110200 */  sll        $v0, $v0, 6
/* 245B8 80033DB8 02004104 */  bgez       $v0, .L80033DC4
/* 245BC 80033DBC 00000000 */   nop
/* 245C0 80033DC0 FF014224 */  addiu      $v0, $v0, 0x1FF
.L80033DC4:
/* 245C4 80033DC4 1800A387 */  lh         $v1, 0x18($sp)
/* 245C8 80033DC8 43120200 */  sra        $v0, $v0, 9
/* 245CC 80033DCC 1600A2A7 */  sh         $v0, 0x16($sp)
/* 245D0 80033DD0 80100300 */  sll        $v0, $v1, 2
/* 245D4 80033DD4 21104300 */  addu       $v0, $v0, $v1
/* 245D8 80033DD8 80110200 */  sll        $v0, $v0, 6
/* 245DC 80033DDC 02004104 */  bgez       $v0, .L80033DE8
/* 245E0 80033DE0 00000000 */   nop
/* 245E4 80033DE4 FF014224 */  addiu      $v0, $v0, 0x1FF
.L80033DE8:
/* 245E8 80033DE8 1A00A387 */  lh         $v1, 0x1A($sp)
/* 245EC 80033DEC 43120200 */  sra        $v0, $v0, 9
/* 245F0 80033DF0 1800A2A7 */  sh         $v0, 0x18($sp)
/* 245F4 80033DF4 80100300 */  sll        $v0, $v1, 2
/* 245F8 80033DF8 21104300 */  addu       $v0, $v0, $v1
/* 245FC 80033DFC 80110200 */  sll        $v0, $v0, 6
/* 24600 80033E00 02004104 */  bgez       $v0, .L80033E0C
/* 24604 80033E04 00000000 */   nop
/* 24608 80033E08 FF014224 */  addiu      $v0, $v0, 0x1FF
.L80033E0C:
/* 2460C 80033E0C 43120200 */  sra        $v0, $v0, 9
/* 24610 80033E10 1A00A2A7 */  sh         $v0, 0x1A($sp)
/* 24614 80033E14 B2FF4426 */  addiu      $a0, $s2, -0x4E
/* 24618 80033E18 1000A527 */  addiu      $a1, $sp, 0x10
/* 2461C 80033E1C 565A000C */  jal        Memcpy
/* 24620 80033E20 14000624 */   addiu     $a2, $zero, 0x14
/* 24624 80033E24 5C00BF8F */  lw         $ra, 0x5C($sp)
/* 24628 80033E28 5800B28F */  lw         $s2, 0x58($sp)
/* 2462C 80033E2C 5400B18F */  lw         $s1, 0x54($sp)
/* 24630 80033E30 5000B08F */  lw         $s0, 0x50($sp)
/* 24634 80033E34 6000BD27 */  addiu      $sp, $sp, 0x60
/* 24638 80033E38 0800E003 */  jr         $ra
/* 2463C 80033E3C 00000000 */   nop
.size CameraUpdateMatrices, . - CameraUpdateMatrices
