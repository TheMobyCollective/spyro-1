.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002DA74
/* 1E274 8002DA74 C8FFBD27 */  addiu      $sp, $sp, -0x38
/* 1E278 8002DA78 0780033C */  lui        $v1, %hi(D_800756AC)
/* 1E27C 8002DA7C AC56638C */  lw         $v1, %lo(D_800756AC)($v1)
/* 1E280 8002DA80 0780023C */  lui        $v0, %hi(D_8006FCF4 + 0x2800)
/* 1E284 8002DA84 F4244224 */  addiu      $v0, $v0, %lo(D_8006FCF4 + 0x2800)
/* 1E288 8002DA88 3400BFAF */  sw         $ra, 0x34($sp)
/* 1E28C 8002DA8C 3000B4AF */  sw         $s4, 0x30($sp)
/* 1E290 8002DA90 2C00B3AF */  sw         $s3, 0x2C($sp)
/* 1E294 8002DA94 2800B2AF */  sw         $s2, 0x28($sp)
/* 1E298 8002DA98 2400B1AF */  sw         $s1, 0x24($sp)
/* 1E29C 8002DA9C 2000B0AF */  sw         $s0, 0x20($sp)
/* 1E2A0 8002DAA0 0780013C */  lui        $at, %hi(D_8007571C)
/* 1E2A4 8002DAA4 1C5722AC */  sw         $v0, %lo(D_8007571C)($at)
/* 1E2A8 8002DAA8 17006014 */  bnez       $v1, .L8002DB08
/* 1E2AC 8002DAAC 00000000 */   nop
/* 1E2B0 8002DAB0 0780023C */  lui        $v0, %hi(D_800756C8)
/* 1E2B4 8002DAB4 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 1E2B8 8002DAB8 00000000 */  nop
/* 1E2BC 8002DABC 40100200 */  sll        $v0, $v0, 1
/* 1E2C0 8002DAC0 8C004224 */  addiu      $v0, $v0, 0x8C
/* 1E2C4 8002DAC4 0780013C */  lui        $at, %hi(D_80075740)
/* 1E2C8 8002DAC8 405722AC */  sw         $v0, %lo(D_80075740)($at)
/* 1E2CC 8002DACC C1004228 */  slti       $v0, $v0, 0xC1
/* 1E2D0 8002DAD0 04004014 */  bnez       $v0, .L8002DAE4
/* 1E2D4 8002DAD4 21880000 */   addu      $s1, $zero, $zero
/* 1E2D8 8002DAD8 C0000224 */  addiu      $v0, $zero, 0xC0
/* 1E2DC 8002DADC 0780013C */  lui        $at, %hi(D_80075740)
/* 1E2E0 8002DAE0 405722AC */  sw         $v0, %lo(D_80075740)($at)
.L8002DAE4:
/* 1E2E4 8002DAE4 00111100 */  sll        $v0, $s1, 4
.L8002DAE8:
/* 1E2E8 8002DAE8 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E2EC 8002DAEC 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E2F0 8002DAF0 01003126 */  addiu      $s1, $s1, 0x1
/* 1E2F4 8002DAF4 21104300 */  addu       $v0, $v0, $v1
/* 1E2F8 8002DAF8 080040A0 */  sb         $zero, 0x8($v0)
/* 1E2FC 8002DAFC 4000222A */  slti       $v0, $s1, 0x40
/* 1E300 8002DB00 F9FF4014 */  bnez       $v0, .L8002DAE8
/* 1E304 8002DB04 00111100 */   sll       $v0, $s1, 4
.L8002DB08:
/* 1E308 8002DB08 0780023C */  lui        $v0, %hi(D_800756AC)
/* 1E30C 8002DB0C AC56428C */  lw         $v0, %lo(D_800756AC)($v0)
/* 1E310 8002DB10 0780033C */  lui        $v1, %hi(g_DeltaTime)
/* 1E314 8002DB14 CC56638C */  lw         $v1, %lo(g_DeltaTime)($v1)
/* 1E318 8002DB18 00000000 */  nop
/* 1E31C 8002DB1C 21184300 */  addu       $v1, $v0, $v1
/* 1E320 8002DB20 A1016228 */  slti       $v0, $v1, 0x1A1
/* 1E324 8002DB24 0780013C */  lui        $at, %hi(D_800756AC)
/* 1E328 8002DB28 AC5623AC */  sw         $v1, %lo(D_800756AC)($at)
/* 1E32C 8002DB2C 05004014 */  bnez       $v0, .L8002DB44
/* 1E330 8002DB30 80006228 */   slti      $v0, $v1, 0x80
/* 1E334 8002DB34 0780013C */  lui        $at, %hi(D_800756B0)
/* 1E338 8002DB38 B05620AC */  sw         $zero, %lo(D_800756B0)($at)
/* 1E33C 8002DB3C DEB70008 */  j          .L8002DF78
/* 1E340 8002DB40 00000000 */   nop
.L8002DB44:
/* 1E344 8002DB44 0C014014 */  bnez       $v0, .L8002DF78
/* 1E348 8002DB48 21880000 */   addu      $s1, $zero, $zero
/* 1E34C 8002DB4C 5555123C */  lui        $s2, (0x55555556 >> 16)
/* 1E350 8002DB50 56555236 */  ori        $s2, $s2, (0x55555556 & 0xFFFF)
/* 1E354 8002DB54 0780143C */  lui        $s4, %hi(D_8006CC78)
/* 1E358 8002DB58 78CC9426 */  addiu      $s4, $s4, %lo(D_8006CC78)
/* 1E35C 8002DB5C 0780133C */  lui        $s3, %hi(D_8006CBF8)
/* 1E360 8002DB60 F8CB7326 */  addiu      $s3, $s3, %lo(D_8006CBF8)
/* 1E364 8002DB64 21800000 */  addu       $s0, $zero, $zero
.L8002DB68:
/* 1E368 8002DB68 0780023C */  lui        $v0, %hi(D_800756C8)
/* 1E36C 8002DB6C C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 1E370 8002DB70 00000000 */  nop
/* 1E374 8002DB74 2A102202 */  slt        $v0, $s1, $v0
/* 1E378 8002DB78 FB004010 */  beqz       $v0, .L8002DF68
/* 1E37C 8002DB7C 40281100 */   sll       $a1, $s1, 1
/* 1E380 8002DB80 0780033C */  lui        $v1, %hi(D_800756AC)
/* 1E384 8002DB84 AC56638C */  lw         $v1, %lo(D_800756AC)($v1)
/* 1E388 8002DB88 8000A224 */  addiu      $v0, $a1, 0x80
/* 1E38C 8002DB8C 2A106200 */  slt        $v0, $v1, $v0
/* 1E390 8002DB90 F5004014 */  bnez       $v0, .L8002DF68
/* 1E394 8002DB94 00016228 */   slti      $v0, $v1, 0x100
/* 1E398 8002DB98 58004010 */  beqz       $v0, .L8002DCFC
/* 1E39C 8002DB9C 00000000 */   nop
/* 1E3A0 8002DBA0 0780023C */  lui        $v0, %hi(D_8007571C)
/* 1E3A4 8002DBA4 1C57428C */  lw         $v0, %lo(D_8007571C)($v0)
/* 1E3A8 8002DBA8 00000000 */  nop
/* 1E3AC 8002DBAC 21180202 */  addu       $v1, $s0, $v0
/* 1E3B0 8002DBB0 08006290 */  lbu        $v0, 0x8($v1)
/* 1E3B4 8002DBB4 00000000 */  nop
/* 1E3B8 8002DBB8 58004014 */  bnez       $v0, .L8002DD1C
/* 1E3BC 8002DBBC 01000224 */   addiu     $v0, $zero, 0x1
/* 1E3C0 8002DBC0 80FFA524 */  addiu      $a1, $a1, -0x80
/* 1E3C4 8002DBC4 080062A0 */  sb         $v0, 0x8($v1)
/* 1E3C8 8002DBC8 0780043C */  lui        $a0, %hi(D_8007571C)
/* 1E3CC 8002DBCC 1C57848C */  lw         $a0, %lo(D_8007571C)($a0)
/* 1E3D0 8002DBD0 0780023C */  lui        $v0, %hi(D_800756AC)
/* 1E3D4 8002DBD4 AC56428C */  lw         $v0, %lo(D_800756AC)($v0)
/* 1E3D8 8002DBD8 0780033C */  lui        $v1, %hi(g_DeltaTime)
/* 1E3DC 8002DBDC CC56638C */  lw         $v1, %lo(g_DeltaTime)($v1)
/* 1E3E0 8002DBE0 21200402 */  addu       $a0, $s0, $a0
/* 1E3E4 8002DBE4 23104500 */  subu       $v0, $v0, $a1
/* 1E3E8 8002DBE8 23104300 */  subu       $v0, $v0, $v1
/* 1E3EC 8002DBEC CB89010C */  jal        rand
/* 1E3F0 8002DBF0 090082A0 */   sb        $v0, 0x9($a0)
/* 1E3F4 8002DBF4 FF004230 */  andi       $v0, $v0, 0xFF
/* 1E3F8 8002DBF8 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E3FC 8002DBFC 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E400 8002DC00 80FF4224 */  addiu      $v0, $v0, -0x80
/* 1E404 8002DC04 21180302 */  addu       $v1, $s0, $v1
/* 1E408 8002DC08 CB89010C */  jal        rand
/* 1E40C 8002DC0C 040062A4 */   sh        $v0, 0x4($v1)
/* 1E410 8002DC10 3F004230 */  andi       $v0, $v0, 0x3F
/* 1E414 8002DC14 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E418 8002DC18 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E41C 8002DC1C 60004224 */  addiu      $v0, $v0, 0x60
/* 1E420 8002DC20 21180302 */  addu       $v1, $s0, $v1
/* 1E424 8002DC24 CB89010C */  jal        rand
/* 1E428 8002DC28 060062A4 */   sh        $v0, 0x6($v1)
/* 1E42C 8002DC2C 3F004230 */  andi       $v0, $v0, 0x3F
/* 1E430 8002DC30 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E434 8002DC34 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E438 8002DC38 E0FF4224 */  addiu      $v0, $v0, -0x20
/* 1E43C 8002DC3C 21180302 */  addu       $v1, $s0, $v1
/* 1E440 8002DC40 CB89010C */  jal        rand
/* 1E444 8002DC44 0A0062A0 */   sb        $v0, 0xA($v1)
/* 1E448 8002DC48 3F004230 */  andi       $v0, $v0, 0x3F
/* 1E44C 8002DC4C 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E450 8002DC50 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E454 8002DC54 E0FF4224 */  addiu      $v0, $v0, -0x20
/* 1E458 8002DC58 21180302 */  addu       $v1, $s0, $v1
/* 1E45C 8002DC5C CB89010C */  jal        rand
/* 1E460 8002DC60 0B0062A0 */   sb        $v0, 0xB($v1)
/* 1E464 8002DC64 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E468 8002DC68 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E46C 8002DC6C 00000000 */  nop
/* 1E470 8002DC70 21180302 */  addu       $v1, $s0, $v1
/* 1E474 8002DC74 CB89010C */  jal        rand
/* 1E478 8002DC78 0C0062A0 */   sb        $v0, 0xC($v1)
/* 1E47C 8002DC7C 02004230 */  andi       $v0, $v0, 0x2
/* 1E480 8002DC80 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E484 8002DC84 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E488 8002DC88 FFFF4224 */  addiu      $v0, $v0, -0x1
/* 1E48C 8002DC8C 21180302 */  addu       $v1, $s0, $v1
/* 1E490 8002DC90 CB89010C */  jal        rand
/* 1E494 8002DC94 0D0062A0 */   sb        $v0, 0xD($v1)
/* 1E498 8002DC98 02004230 */  andi       $v0, $v0, 0x2
/* 1E49C 8002DC9C 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E4A0 8002DCA0 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E4A4 8002DCA4 FFFF4224 */  addiu      $v0, $v0, -0x1
/* 1E4A8 8002DCA8 21180302 */  addu       $v1, $s0, $v1
/* 1E4AC 8002DCAC CB89010C */  jal        rand
/* 1E4B0 8002DCB0 0E0062A0 */   sb        $v0, 0xE($v1)
/* 1E4B4 8002DCB4 0F004230 */  andi       $v0, $v0, 0xF
/* 1E4B8 8002DCB8 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E4BC 8002DCBC 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E4C0 8002DCC0 F8FF4224 */  addiu      $v0, $v0, -0x8
/* 1E4C4 8002DCC4 21180302 */  addu       $v1, $s0, $v1
/* 1E4C8 8002DCC8 0F0062A0 */  sb         $v0, 0xF($v1)
/* 1E4CC 8002DCCC 0780023C */  lui        $v0, %hi(D_800756AC)
/* 1E4D0 8002DCD0 AC56428C */  lw         $v0, %lo(D_800756AC)($v0)
/* 1E4D4 8002DCD4 00000000 */  nop
/* 1E4D8 8002DCD8 07004230 */  andi       $v0, $v0, 0x7
/* 1E4DC 8002DCDC 07004014 */  bnez       $v0, .L8002DCFC
/* 1E4E0 8002DCE0 21280000 */   addu      $a1, $zero, $zero
/* 1E4E4 8002DCE4 0780023C */  lui        $v0, %hi(g_Spu + 0x2CC)
/* 1E4E8 8002DCE8 D461428C */  lw         $v0, %lo(g_Spu + 0x2CC)($v0)
/* 1E4EC 8002DCEC 10000624 */  addiu      $a2, $zero, 0x10
/* 1E4F0 8002DCF0 00004490 */  lbu        $a0, 0x0($v0)
/* 1E4F4 8002DCF4 9E56010C */  jal        PlaySound
/* 1E4F8 8002DCF8 21380000 */   addu      $a3, $zero, $zero
.L8002DCFC:
/* 1E4FC 8002DCFC 0780023C */  lui        $v0, %hi(D_8007571C)
/* 1E500 8002DD00 1C57428C */  lw         $v0, %lo(D_8007571C)($v0)
/* 1E504 8002DD04 00000000 */  nop
/* 1E508 8002DD08 21100202 */  addu       $v0, $s0, $v0
/* 1E50C 8002DD0C 08004290 */  lbu        $v0, 0x8($v0)
/* 1E510 8002DD10 00000000 */  nop
/* 1E514 8002DD14 94004010 */  beqz       $v0, .L8002DF68
/* 1E518 8002DD18 00000000 */   nop
.L8002DD1C:
/* 1E51C 8002DD1C 0780033C */  lui        $v1, %hi(D_8007571C)
/* 1E520 8002DD20 1C57638C */  lw         $v1, %lo(D_8007571C)($v1)
/* 1E524 8002DD24 0780043C */  lui        $a0, %hi(g_DeltaTime)
/* 1E528 8002DD28 CC56848C */  lw         $a0, %lo(g_DeltaTime)($a0)
/* 1E52C 8002DD2C 21180302 */  addu       $v1, $s0, $v1
/* 1E530 8002DD30 09006290 */  lbu        $v0, 0x9($v1)
/* 1E534 8002DD34 00000000 */  nop
/* 1E538 8002DD38 21104400 */  addu       $v0, $v0, $a0
/* 1E53C 8002DD3C 090062A0 */  sb         $v0, 0x9($v1)
/* 1E540 8002DD40 0780043C */  lui        $a0, %hi(D_8007571C)
/* 1E544 8002DD44 1C57848C */  lw         $a0, %lo(D_8007571C)($a0)
/* 1E548 8002DD48 00000000 */  nop
/* 1E54C 8002DD4C 21200402 */  addu       $a0, $s0, $a0
/* 1E550 8002DD50 0C008290 */  lbu        $v0, 0xC($a0)
/* 1E554 8002DD54 0F008390 */  lbu        $v1, 0xF($a0)
/* 1E558 8002DD58 00000000 */  nop
/* 1E55C 8002DD5C 21104300 */  addu       $v0, $v0, $v1
/* 1E560 8002DD60 0C0082A0 */  sb         $v0, 0xC($a0)
/* 1E564 8002DD64 0780023C */  lui        $v0, %hi(D_8007571C)
/* 1E568 8002DD68 1C57428C */  lw         $v0, %lo(D_8007571C)($v0)
/* 1E56C 8002DD6C 00000000 */  nop
/* 1E570 8002DD70 21300202 */  addu       $a2, $s0, $v0
/* 1E574 8002DD74 0900C390 */  lbu        $v1, 0x9($a2)
/* 1E578 8002DD78 00000000 */  nop
/* 1E57C 8002DD7C 3000622C */  sltiu      $v0, $v1, 0x30
/* 1E580 8002DD80 20004010 */  beqz       $v0, .L8002DE04
/* 1E584 8002DD84 80100300 */   sll       $v0, $v1, 2
/* 1E588 8002DD88 18005200 */  mult       $v0, $s2
/* 1E58C 8002DD8C C3170200 */  sra        $v0, $v0, 31
/* 1E590 8002DD90 00100324 */  addiu      $v1, $zero, 0x1000
/* 1E594 8002DD94 10400000 */  mfhi       $t0
/* 1E598 8002DD98 23100201 */  subu       $v0, $t0, $v0
/* 1E59C 8002DD9C 40100200 */  sll        $v0, $v0, 1
/* 1E5A0 8002DDA0 21105400 */  addu       $v0, $v0, $s4
/* 1E5A4 8002DDA4 00004284 */  lh         $v0, 0x0($v0)
/* 1E5A8 8002DDA8 0400C484 */  lh         $a0, 0x4($a2)
/* 1E5AC 8002DDAC 23186200 */  subu       $v1, $v1, $v0
/* 1E5B0 8002DDB0 18008300 */  mult       $a0, $v1
/* 1E5B4 8002DDB4 0900C290 */  lbu        $v0, 0x9($a2)
/* 1E5B8 8002DDB8 12180000 */  mflo       $v1
/* 1E5BC 8002DDBC 80100200 */  sll        $v0, $v0, 2
/* 1E5C0 8002DDC0 00000000 */  nop
/* 1E5C4 8002DDC4 18005200 */  mult       $v0, $s2
/* 1E5C8 8002DDC8 031B0300 */  sra        $v1, $v1, 12
/* 1E5CC 8002DDCC C3170200 */  sra        $v0, $v0, 31
/* 1E5D0 8002DDD0 0000C3A4 */  sh         $v1, 0x0($a2)
/* 1E5D4 8002DDD4 0600C384 */  lh         $v1, 0x6($a2)
/* 1E5D8 8002DDD8 10400000 */  mfhi       $t0
/* 1E5DC 8002DDDC 23100201 */  subu       $v0, $t0, $v0
/* 1E5E0 8002DDE0 40100200 */  sll        $v0, $v0, 1
/* 1E5E4 8002DDE4 21105300 */  addu       $v0, $v0, $s3
/* 1E5E8 8002DDE8 00004284 */  lh         $v0, 0x0($v0)
/* 1E5EC 8002DDEC 00000000 */  nop
/* 1E5F0 8002DDF0 18006200 */  mult       $v1, $v0
/* 1E5F4 8002DDF4 12180000 */  mflo       $v1
/* 1E5F8 8002DDF8 03130300 */  sra        $v0, $v1, 12
/* 1E5FC 8002DDFC DAB70008 */  j          .L8002DF68
/* 1E600 8002DE00 0200C2A4 */   sh        $v0, 0x2($a2)
.L8002DE04:
/* 1E604 8002DE04 6000622C */  sltiu      $v0, $v1, 0x60
/* 1E608 8002DE08 25004010 */  beqz       $v0, .L8002DEA0
/* 1E60C 8002DE0C D0FF6224 */   addiu     $v0, $v1, -0x30
/* 1E610 8002DE10 C0100200 */  sll        $v0, $v0, 3
/* 1E614 8002DE14 18005200 */  mult       $v0, $s2
/* 1E618 8002DE18 C3170200 */  sra        $v0, $v0, 31
/* 1E61C 8002DE1C 0400C584 */  lh         $a1, 0x4($a2)
/* 1E620 8002DE20 10400000 */  mfhi       $t0
/* 1E624 8002DE24 23100201 */  subu       $v0, $t0, $v0
/* 1E628 8002DE28 40100200 */  sll        $v0, $v0, 1
/* 1E62C 8002DE2C 21105300 */  addu       $v0, $v0, $s3
/* 1E630 8002DE30 00004284 */  lh         $v0, 0x0($v0)
/* 1E634 8002DE34 00000000 */  nop
/* 1E638 8002DE38 1800A200 */  mult       $a1, $v0
/* 1E63C 8002DE3C 0900C290 */  lbu        $v0, 0x9($a2)
/* 1E640 8002DE40 12180000 */  mflo       $v1
/* 1E644 8002DE44 D0FF4224 */  addiu      $v0, $v0, -0x30
/* 1E648 8002DE48 C0100200 */  sll        $v0, $v0, 3
/* 1E64C 8002DE4C 18005200 */  mult       $v0, $s2
/* 1E650 8002DE50 43230300 */  sra        $a0, $v1, 13
/* 1E654 8002DE54 2128A400 */  addu       $a1, $a1, $a0
/* 1E658 8002DE58 0600C394 */  lhu        $v1, 0x6($a2)
/* 1E65C 8002DE5C C3170200 */  sra        $v0, $v0, 31
/* 1E660 8002DE60 0000C5A4 */  sh         $a1, 0x0($a2)
/* 1E664 8002DE64 001C0300 */  sll        $v1, $v1, 16
/* 1E668 8002DE68 10400000 */  mfhi       $t0
/* 1E66C 8002DE6C 23100201 */  subu       $v0, $t0, $v0
/* 1E670 8002DE70 40100200 */  sll        $v0, $v0, 1
/* 1E674 8002DE74 21105400 */  addu       $v0, $v0, $s4
/* 1E678 8002DE78 00004284 */  lh         $v0, 0x0($v0)
/* 1E67C 8002DE7C 03240300 */  sra        $a0, $v1, 16
/* 1E680 8002DE80 00104224 */  addiu      $v0, $v0, 0x1000
/* 1E684 8002DE84 18008200 */  mult       $a0, $v0
/* 1E688 8002DE88 431C0300 */  sra        $v1, $v1, 17
/* 1E68C 8002DE8C 12480000 */  mflo       $t1
/* 1E690 8002DE90 83130900 */  sra        $v0, $t1, 14
/* 1E694 8002DE94 21186200 */  addu       $v1, $v1, $v0
/* 1E698 8002DE98 DAB70008 */  j          .L8002DF68
/* 1E69C 8002DE9C 0200C3A4 */   sh        $v1, 0x2($a2)
.L8002DEA0:
/* 1E6A0 8002DEA0 9300622C */  sltiu      $v0, $v1, 0x93
/* 1E6A4 8002DEA4 21004010 */  beqz       $v0, .L8002DF2C
/* 1E6A8 8002DEA8 A0FF6224 */   addiu     $v0, $v1, -0x60
/* 1E6AC 8002DEAC 80100200 */  sll        $v0, $v0, 2
/* 1E6B0 8002DEB0 18005200 */  mult       $v0, $s2
/* 1E6B4 8002DEB4 C3170200 */  sra        $v0, $v0, 31
/* 1E6B8 8002DEB8 0400C484 */  lh         $a0, 0x4($a2)
/* 1E6BC 8002DEBC 10400000 */  mfhi       $t0
/* 1E6C0 8002DEC0 23100201 */  subu       $v0, $t0, $v0
/* 1E6C4 8002DEC4 40100200 */  sll        $v0, $v0, 1
/* 1E6C8 8002DEC8 21105300 */  addu       $v0, $v0, $s3
/* 1E6CC 8002DECC 00004284 */  lh         $v0, 0x0($v0)
/* 1E6D0 8002DED0 00000000 */  nop
/* 1E6D4 8002DED4 18008200 */  mult       $a0, $v0
/* 1E6D8 8002DED8 0900C290 */  lbu        $v0, 0x9($a2)
/* 1E6DC 8002DEDC 12180000 */  mflo       $v1
/* 1E6E0 8002DEE0 A0FF4224 */  addiu      $v0, $v0, -0x60
/* 1E6E4 8002DEE4 80100200 */  sll        $v0, $v0, 2
/* 1E6E8 8002DEE8 18005200 */  mult       $v0, $s2
/* 1E6EC 8002DEEC 031B0300 */  sra        $v1, $v1, 12
/* 1E6F0 8002DEF0 23208300 */  subu       $a0, $a0, $v1
/* 1E6F4 8002DEF4 0600C384 */  lh         $v1, 0x6($a2)
/* 1E6F8 8002DEF8 C3170200 */  sra        $v0, $v0, 31
/* 1E6FC 8002DEFC 0000C4A4 */  sh         $a0, 0x0($a2)
/* 1E700 8002DF00 10400000 */  mfhi       $t0
/* 1E704 8002DF04 23100201 */  subu       $v0, $t0, $v0
/* 1E708 8002DF08 40100200 */  sll        $v0, $v0, 1
/* 1E70C 8002DF0C 21105400 */  addu       $v0, $v0, $s4
/* 1E710 8002DF10 00004284 */  lh         $v0, 0x0($v0)
/* 1E714 8002DF14 00000000 */  nop
/* 1E718 8002DF18 18006200 */  mult       $v1, $v0
/* 1E71C 8002DF1C 12180000 */  mflo       $v1
/* 1E720 8002DF20 43130300 */  sra        $v0, $v1, 13
/* 1E724 8002DF24 DAB70008 */  j          .L8002DF68
/* 1E728 8002DF28 0200C2A4 */   sh        $v0, 0x2($a2)
.L8002DF2C:
/* 1E72C 8002DF2C 18003202 */  mult       $s1, $s2
/* 1E730 8002DF30 C31F1100 */  sra        $v1, $s1, 31
/* 1E734 8002DF34 10400000 */  mfhi       $t0
/* 1E738 8002DF38 23180301 */  subu       $v1, $t0, $v1
/* 1E73C 8002DF3C 40100300 */  sll        $v0, $v1, 1
/* 1E740 8002DF40 21104300 */  addu       $v0, $v0, $v1
/* 1E744 8002DF44 08002216 */  bne        $s1, $v0, .L8002DF68
/* 1E748 8002DF48 0800C0A0 */   sb        $zero, 0x8($a2)
/* 1E74C 8002DF4C 21280000 */  addu       $a1, $zero, $zero
/* 1E750 8002DF50 0780023C */  lui        $v0, %hi(g_Spu + 0x2CC)
/* 1E754 8002DF54 D461428C */  lw         $v0, %lo(g_Spu + 0x2CC)($v0)
/* 1E758 8002DF58 10000624 */  addiu      $a2, $zero, 0x10
/* 1E75C 8002DF5C 2F004490 */  lbu        $a0, 0x2F($v0)
/* 1E760 8002DF60 9E56010C */  jal        PlaySound
/* 1E764 8002DF64 21380000 */   addu      $a3, $zero, $zero
.L8002DF68:
/* 1E768 8002DF68 01003126 */  addiu      $s1, $s1, 0x1
/* 1E76C 8002DF6C 2000222A */  slti       $v0, $s1, 0x20
/* 1E770 8002DF70 FDFE4014 */  bnez       $v0, .L8002DB68
/* 1E774 8002DF74 10001026 */   addiu     $s0, $s0, 0x10
.L8002DF78:
/* 1E778 8002DF78 3400BF8F */  lw         $ra, 0x34($sp)
/* 1E77C 8002DF7C 3000B48F */  lw         $s4, 0x30($sp)
/* 1E780 8002DF80 2C00B38F */  lw         $s3, 0x2C($sp)
/* 1E784 8002DF84 2800B28F */  lw         $s2, 0x28($sp)
/* 1E788 8002DF88 2400B18F */  lw         $s1, 0x24($sp)
/* 1E78C 8002DF8C 2000B08F */  lw         $s0, 0x20($sp)
/* 1E790 8002DF90 3800BD27 */  addiu      $sp, $sp, 0x38
/* 1E794 8002DF94 0800E003 */  jr         $ra
/* 1E798 8002DF98 00000000 */   nop
.size func_8002DA74, . - func_8002DA74
