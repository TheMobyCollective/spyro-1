.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_43_80086B38
/* 3D85100 80086B38 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 3D85104 80086B3C 3800B0AF */  sw         $s0, 0x38($sp)
/* 3D85108 80086B40 21808000 */  addu       $s0, $a0, $zero
/* 3D8510C 80086B44 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 3D85110 80086B48 21A8A000 */  addu       $s5, $a1, $zero
/* 3D85114 80086B4C 5000BFAF */  sw         $ra, 0x50($sp)
/* 3D85118 80086B50 4800B4AF */  sw         $s4, 0x48($sp)
/* 3D8511C 80086B54 4400B3AF */  sw         $s3, 0x44($sp)
/* 3D85120 80086B58 4000B2AF */  sw         $s2, 0x40($sp)
/* 3D85124 80086B5C 3149010C */  jal        func_800524C4
/* 3D85128 80086B60 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 3D8512C 80086B64 21984000 */  addu       $s3, $v0, $zero
/* 3D85130 80086B68 1400A012 */  beqz       $s5, .Llevel_43_80086BBC
/* 3D85134 80086B6C 360070A6 */   sh        $s0, 0x36($s3)
/* 3D85138 80086B70 0780043C */  lui        $a0, %hi(D_80075828)
/* 3D8513C 80086B74 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 3D85140 80086B78 00000000 */  nop
/* 3D85144 80086B7C 2320A402 */  subu       $a0, $s5, $a0
/* 3D85148 80086B80 40190400 */  sll        $v1, $a0, 5
/* 3D8514C 80086B84 23186400 */  subu       $v1, $v1, $a0
/* 3D85150 80086B88 40190300 */  sll        $v1, $v1, 5
/* 3D85154 80086B8C 21186400 */  addu       $v1, $v1, $a0
/* 3D85158 80086B90 C0100300 */  sll        $v0, $v1, 3
/* 3D8515C 80086B94 21186200 */  addu       $v1, $v1, $v0
/* 3D85160 80086B98 C0130300 */  sll        $v0, $v1, 15
/* 3D85164 80086B9C 23104300 */  subu       $v0, $v0, $v1
/* 3D85168 80086BA0 80100200 */  sll        $v0, $v0, 2
/* 3D8516C 80086BA4 21104400 */  addu       $v0, $v0, $a0
/* 3D85170 80086BA8 23100200 */  negu       $v0, $v0
/* 3D85174 80086BAC C3180200 */  sra        $v1, $v0, 3
/* 3D85178 80086BB0 0001622C */  sltiu      $v0, $v1, 0x100
/* 3D8517C 80086BB4 03004014 */  bnez       $v0, .Llevel_43_80086BC4
/* 3D85180 80086BB8 0201022A */   slti      $v0, $s0, 0x102
.Llevel_43_80086BBC:
/* 3D85184 80086BBC 21180000 */  addu       $v1, $zero, $zero
/* 3D85188 80086BC0 0201022A */  slti       $v0, $s0, 0x102
.Llevel_43_80086BC4:
/* 3D8518C 80086BC4 27004010 */  beqz       $v0, .Llevel_43_80086C64
/* 3D85190 80086BC8 560063A2 */   sb        $v1, 0x56($s3)
/* 3D85194 80086BCC FF00022A */  slti       $v0, $s0, 0xFF
/* 3D85198 80086BD0 F9004010 */  beqz       $v0, .Llevel_43_80086FB8
/* 3D8519C 80086BD4 4600022A */   slti      $v0, $s0, 0x46
/* 3D851A0 80086BD8 12004010 */  beqz       $v0, .Llevel_43_80086C24
/* 3D851A4 80086BDC 4300022A */   slti      $v0, $s0, 0x43
/* 3D851A8 80086BE0 F5004010 */  beqz       $v0, .Llevel_43_80086FB8
/* 3D851AC 80086BE4 0F000224 */   addiu     $v0, $zero, 0xF
/* 3D851B0 80086BE8 42000212 */  beq        $s0, $v0, .Llevel_43_80086CF4
/* 3D851B4 80086BEC 1000022A */   slti      $v0, $s0, 0x10
/* 3D851B8 80086BF0 05004010 */  beqz       $v0, .Llevel_43_80086C08
/* 3D851BC 80086BF4 0E000224 */   addiu     $v0, $zero, 0xE
/* 3D851C0 80086BF8 87000212 */  beq        $s0, $v0, .Llevel_43_80086E18
/* 3D851C4 80086BFC 00000000 */   nop
/* 3D851C8 80086C00 E81C0208 */  j          .Llevel_43_800873A0
/* 3D851CC 80086C04 00000000 */   nop
.Llevel_43_80086C08:
/* 3D851D0 80086C08 10000224 */  addiu      $v0, $zero, 0x10
/* 3D851D4 80086C0C 60000212 */  beq        $s0, $v0, .Llevel_43_80086D90
/* 3D851D8 80086C10 22000224 */   addiu     $v0, $zero, 0x22
/* 3D851DC 80086C14 72000212 */  beq        $s0, $v0, .Llevel_43_80086DE0
/* 3D851E0 80086C18 00000000 */   nop
/* 3D851E4 80086C1C E81C0208 */  j          .Llevel_43_800873A0
/* 3D851E8 80086C20 00000000 */   nop
.Llevel_43_80086C24:
/* 3D851EC 80086C24 5800022A */  slti       $v0, $s0, 0x58
/* 3D851F0 80086C28 07004010 */  beqz       $v0, .Llevel_43_80086C48
/* 3D851F4 80086C2C 5300022A */   slti      $v0, $s0, 0x53
/* 3D851F8 80086C30 79004010 */  beqz       $v0, .Llevel_43_80086E18
/* 3D851FC 80086C34 4C000224 */   addiu     $v0, $zero, 0x4C
/* 3D85200 80086C38 CF010212 */  beq        $s0, $v0, .Llevel_43_80087378
/* 3D85204 80086C3C 00000000 */   nop
/* 3D85208 80086C40 E81C0208 */  j          .Llevel_43_800873A0
/* 3D8520C 80086C44 00000000 */   nop
.Llevel_43_80086C48:
/* 3D85210 80086C48 78000224 */  addiu      $v0, $zero, 0x78
/* 3D85214 80086C4C C8000212 */  beq        $s0, $v0, .Llevel_43_80086F70
/* 3D85218 80086C50 FB000224 */   addiu     $v0, $zero, 0xFB
/* 3D8521C 80086C54 43010212 */  beq        $s0, $v0, .Llevel_43_80087164
/* 3D85220 80086C58 00000000 */   nop
/* 3D85224 80086C5C E81C0208 */  j          .Llevel_43_800873A0
/* 3D85228 80086C60 00000000 */   nop
.Llevel_43_80086C64:
/* 3D8522C 80086C64 47010224 */  addiu      $v0, $zero, 0x147
/* 3D85230 80086C68 AE010212 */  beq        $s0, $v0, .Llevel_43_80087324
/* 3D85234 80086C6C 4801022A */   slti      $v0, $s0, 0x148
/* 3D85238 80086C70 12004010 */  beqz       $v0, .Llevel_43_80086CBC
/* 3D8523C 80086C74 15010224 */   addiu     $v0, $zero, 0x115
/* 3D85240 80086C78 AA010212 */  beq        $s0, $v0, .Llevel_43_80087324
/* 3D85244 80086C7C 1601022A */   slti      $v0, $s0, 0x116
/* 3D85248 80086C80 07004010 */  beqz       $v0, .Llevel_43_80086CA0
/* 3D8524C 80086C84 0E01022A */   slti      $v0, $s0, 0x10E
/* 3D85250 80086C88 C5014010 */  beqz       $v0, .Llevel_43_800873A0
/* 3D85254 80086C8C 0401022A */   slti      $v0, $s0, 0x104
/* 3D85258 80086C90 A4014010 */  beqz       $v0, .Llevel_43_80087324
/* 3D8525C 80086C94 00000000 */   nop
/* 3D85260 80086C98 E81C0208 */  j          .Llevel_43_800873A0
/* 3D85264 80086C9C 00000000 */   nop
.Llevel_43_80086CA0:
/* 3D85268 80086CA0 3801022A */  slti       $v0, $s0, 0x138
/* 3D8526C 80086CA4 BE014010 */  beqz       $v0, .Llevel_43_800873A0
/* 3D85270 80086CA8 3501022A */   slti      $v0, $s0, 0x135
/* 3D85274 80086CAC C2004010 */  beqz       $v0, .Llevel_43_80086FB8
/* 3D85278 80086CB0 00000000 */   nop
/* 3D8527C 80086CB4 E81C0208 */  j          .Llevel_43_800873A0
/* 3D85280 80086CB8 00000000 */   nop
.Llevel_43_80086CBC:
/* 3D85284 80086CBC AA01022A */  slti       $v0, $s0, 0x1AA
/* 3D85288 80086CC0 07004010 */  beqz       $v0, .Llevel_43_80086CE0
/* 3D8528C 80086CC4 A701022A */   slti      $v0, $s0, 0x1A7
/* 3D85290 80086CC8 BB004010 */  beqz       $v0, .Llevel_43_80086FB8
/* 3D85294 80086CCC 88010224 */   addiu     $v0, $zero, 0x188
/* 3D85298 80086CD0 A1010212 */  beq        $s0, $v0, .Llevel_43_80087358
/* 3D8529C 80086CD4 00000000 */   nop
/* 3D852A0 80086CD8 E81C0208 */  j          .Llevel_43_800873A0
/* 3D852A4 80086CDC 00000000 */   nop
.Llevel_43_80086CE0:
/* 3D852A8 80086CE0 C401022A */  slti       $v0, $s0, 0x1C4
/* 3D852AC 80086CE4 AE014010 */  beqz       $v0, .Llevel_43_800873A0
/* 3D852B0 80086CE8 00000000 */   nop
/* 3D852B4 80086CEC DE1C0208 */  j          .Llevel_43_80087378
/* 3D852B8 80086CF0 00000000 */   nop
.Llevel_43_80086CF4:
/* 3D852BC 80086CF4 0000708E */  lw         $s0, 0x0($s3)
/* 3D852C0 80086CF8 C8E9000C */  jal        func_8003A720
/* 3D852C4 80086CFC 21206002 */   addu      $a0, $s3, $zero
/* 3D852C8 80086D00 8C000224 */  addiu      $v0, $zero, 0x8C
/* 3D852CC 80086D04 080002AE */  sw         $v0, 0x8($s0)
/* 3D852D0 80086D08 03000224 */  addiu      $v0, $zero, 0x3
/* 3D852D4 80086D0C 100002A2 */  sb         $v0, 0x10($s0)
/* 3D852D8 80086D10 FF000224 */  addiu      $v0, $zero, 0xFF
/* 3D852DC 80086D14 140002A2 */  sb         $v0, 0x14($s0)
/* 3D852E0 80086D18 02000224 */  addiu      $v0, $zero, 0x2
/* 3D852E4 80086D1C 000000AE */  sw         $zero, 0x0($s0)
/* 3D852E8 80086D20 040000AE */  sw         $zero, 0x4($s0)
/* 3D852EC 80086D24 0E0000A2 */  sb         $zero, 0xE($s0)
/* 3D852F0 80086D28 0F0000A2 */  sb         $zero, 0xF($s0)
/* 3D852F4 80086D2C 110000A2 */  sb         $zero, 0x11($s0)
/* 3D852F8 80086D30 120000A2 */  sb         $zero, 0x12($s0)
/* 3D852FC 80086D34 130000A2 */  sb         $zero, 0x13($s0)
/* 3D85300 80086D38 490062A2 */  sb         $v0, 0x49($s3)
/* 3D85304 80086D3C 18000224 */  addiu      $v0, $zero, 0x18
/* 3D85308 80086D40 500062A2 */  sb         $v0, 0x50($s3)
/* 3D8530C 80086D44 10000224 */  addiu      $v0, $zero, 0x10
/* 3D85310 80086D48 520062A2 */  sb         $v0, 0x52($s3)
/* 3D85314 80086D4C 20000224 */  addiu      $v0, $zero, 0x20
/* 3D85318 80086D50 440062A2 */  sb         $v0, 0x44($s3)
/* 3D8531C 80086D54 450060A2 */  sb         $zero, 0x45($s3)
/* 3D85320 80086D58 0400A012 */  beqz       $s5, .Llevel_43_80086D6C
/* 3D85324 80086D5C 460060A2 */   sb        $zero, 0x46($s3)
/* 3D85328 80086D60 0C006426 */  addiu      $a0, $s3, 0xC
/* 3D8532C 80086D64 C05D000C */  jal        VecCopy
/* 3D85330 80086D68 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_43_80086D6C:
/* 3D85334 80086D6C AA49010C */  jal        func_800526A8
/* 3D85338 80086D70 21206002 */   addu      $a0, $s3, $zero
/* 3D8533C 80086D74 4B006292 */  lbu        $v0, 0x4B($s3)
/* 3D85340 80086D78 01000324 */  addiu      $v1, $zero, 0x1
/* 3D85344 80086D7C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 3D85348 80086D80 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 3D8534C 80086D84 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 3D85350 80086D88 561C0208 */  j          .Llevel_43_80087158
/* 3D85354 80086D8C 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_43_80086D90:
/* 3D85358 80086D90 0000718E */  lw         $s1, 0x0($s3)
/* 3D8535C 80086D94 C8E9000C */  jal        func_8003A720
/* 3D85360 80086D98 21206002 */   addu      $a0, $s3, $zero
/* 3D85364 80086D9C AA49010C */  jal        func_800526A8
/* 3D85368 80086DA0 21206002 */   addu      $a0, $s3, $zero
/* 3D8536C 80086DA4 0C007026 */  addiu      $s0, $s3, 0xC
/* 3D85370 80086DA8 21200002 */  addu       $a0, $s0, $zero
/* 3D85374 80086DAC C05D000C */  jal        VecCopy
/* 3D85378 80086DB0 0C00A526 */   addiu     $a1, $s5, 0xC
/* 3D8537C 80086DB4 21280002 */  addu       $a1, $s0, $zero
/* 3D85380 80086DB8 1400628E */  lw         $v0, 0x14($s3)
/* 3D85384 80086DBC 04002426 */  addiu      $a0, $s1, 0x4
/* 3D85388 80086DC0 00024224 */  addiu      $v0, $v0, 0x200
/* 3D8538C 80086DC4 C05D000C */  jal        VecCopy
/* 3D85390 80086DC8 140062AE */   sw        $v0, 0x14($s3)
/* 3D85394 80086DCC 08070224 */  addiu      $v0, $zero, 0x708
/* 3D85398 80086DD0 130020A2 */  sb         $zero, 0x13($s1)
/* 3D8539C 80086DD4 120020A2 */  sb         $zero, 0x12($s1)
/* 3D853A0 80086DD8 F51C0208 */  j          .Llevel_43_800873D4
/* 3D853A4 80086DDC 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_43_80086DE0:
/* 3D853A8 80086DE0 C8E9000C */  jal        func_8003A720
/* 3D853AC 80086DE4 21206002 */   addu      $a0, $s3, $zero
/* 3D853B0 80086DE8 20000224 */  addiu      $v0, $zero, 0x20
/* 3D853B4 80086DEC 500062A2 */  sb         $v0, 0x50($s3)
/* 3D853B8 80086DF0 FF000224 */  addiu      $v0, $zero, 0xFF
/* 3D853BC 80086DF4 0400A012 */  beqz       $s5, .Llevel_43_80086E08
/* 3D853C0 80086DF8 520062A2 */   sb        $v0, 0x52($s3)
/* 3D853C4 80086DFC 0C006426 */  addiu      $a0, $s3, 0xC
/* 3D853C8 80086E00 C05D000C */  jal        VecCopy
/* 3D853CC 80086E04 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_43_80086E08:
/* 3D853D0 80086E08 734A010C */  jal        func_800529CC
/* 3D853D4 80086E0C 21206002 */   addu      $a0, $s3, $zero
/* 3D853D8 80086E10 F61C0208 */  j          .Llevel_43_800873D8
/* 3D853DC 80086E14 21106002 */   addu      $v0, $s3, $zero
.Llevel_43_80086E18:
/* 3D853E0 80086E18 0000718E */  lw         $s1, 0x0($s3)
/* 3D853E4 80086E1C C8E9000C */  jal        func_8003A720
/* 3D853E8 80086E20 21206002 */   addu      $a0, $s3, $zero
/* 3D853EC 80086E24 8C000224 */  addiu      $v0, $zero, 0x8C
/* 3D853F0 80086E28 000020AE */  sw         $zero, 0x0($s1)
/* 3D853F4 80086E2C 040020AE */  sw         $zero, 0x4($s1)
/* 3D853F8 80086E30 080022AE */  sw         $v0, 0x8($s1)
/* 3D853FC 80086E34 0E0020A2 */  sb         $zero, 0xE($s1)
/* 3D85400 80086E38 0F0020A2 */  sb         $zero, 0xF($s1)
/* 3D85404 80086E3C 110020A2 */  sb         $zero, 0x11($s1)
/* 3D85408 80086E40 120020A2 */  sb         $zero, 0x12($s1)
/* 3D8540C 80086E44 130020A2 */  sb         $zero, 0x13($s1)
/* 3D85410 80086E48 3600A386 */  lh         $v1, 0x36($s5)
/* 3D85414 80086E4C 0D000224 */  addiu      $v0, $zero, 0xD
/* 3D85418 80086E50 02006214 */  bne        $v1, $v0, .Llevel_43_80086E5C
/* 3D8541C 80086E54 03000224 */   addiu     $v0, $zero, 0x3
/* 3D85420 80086E58 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_43_80086E5C:
/* 3D85424 80086E5C 100022A2 */  sb         $v0, 0x10($s1)
/* 3D85428 80086E60 0C007026 */  addiu      $s0, $s3, 0xC
/* 3D8542C 80086E64 21200002 */  addu       $a0, $s0, $zero
/* 3D85430 80086E68 0C00A526 */  addiu      $a1, $s5, 0xC
/* 3D85434 80086E6C FF000224 */  addiu      $v0, $zero, 0xFF
/* 3D85438 80086E70 140022A2 */  sb         $v0, 0x14($s1)
/* 3D8543C 80086E74 02001124 */  addiu      $s1, $zero, 0x2
/* 3D85440 80086E78 18000224 */  addiu      $v0, $zero, 0x18
/* 3D85444 80086E7C 500062A2 */  sb         $v0, 0x50($s3)
/* 3D85448 80086E80 40000224 */  addiu      $v0, $zero, 0x40
/* 3D8544C 80086E84 520062A2 */  sb         $v0, 0x52($s3)
/* 3D85450 80086E88 20000224 */  addiu      $v0, $zero, 0x20
/* 3D85454 80086E8C 490071A2 */  sb         $s1, 0x49($s3)
/* 3D85458 80086E90 440062A2 */  sb         $v0, 0x44($s3)
/* 3D8545C 80086E94 450060A2 */  sb         $zero, 0x45($s3)
/* 3D85460 80086E98 C05D000C */  jal        VecCopy
/* 3D85464 80086E9C 460060A2 */   sb        $zero, 0x46($s3)
/* 3D85468 80086EA0 734A010C */  jal        func_800529CC
/* 3D8546C 80086EA4 21206002 */   addu      $a0, $s3, $zero
/* 3D85470 80086EA8 1000A427 */  addiu      $a0, $sp, 0x10
/* 3D85474 80086EAC 21280002 */  addu       $a1, $s0, $zero
/* 3D85478 80086EB0 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 3D8547C 80086EB4 C05D000C */  jal        VecCopy
/* 3D85480 80086EB8 1C0062AE */   sw        $v0, 0x1C($s3)
/* 3D85484 80086EBC 1000A427 */  addiu      $a0, $sp, 0x10
/* 3D85488 80086EC0 1800A28F */  lw         $v0, 0x18($sp)
/* 3D8548C 80086EC4 0100053C */  lui        $a1, (0x10000 >> 16)
/* 3D85490 80086EC8 00044224 */  addiu      $v0, $v0, 0x400
/* 3D85494 80086ECC 7B35010C */  jal        func_8004D5EC
/* 3D85498 80086ED0 1800A2AF */   sw        $v0, 0x18($sp)
/* 3D8549C 80086ED4 F44C010C */  jal        func_800533D0
/* 3D854A0 80086ED8 21206002 */   addu      $a0, $s3, $zero
/* 3D854A4 80086EDC 36006386 */  lh         $v1, 0x36($s3)
/* 3D854A8 80086EE0 0E000224 */  addiu      $v0, $zero, 0xE
/* 3D854AC 80086EE4 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 3D854B0 80086EE8 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 3D854B4 80086EEC 03006214 */  bne        $v1, $v0, .Llevel_43_80086EFC
/* 3D854B8 80086EF0 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 3D854BC 80086EF4 0C000224 */  addiu      $v0, $zero, 0xC
/* 3D854C0 80086EF8 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_43_80086EFC:
/* 3D854C4 80086EFC 36006386 */  lh         $v1, 0x36($s3)
/* 3D854C8 80086F00 53000224 */  addiu      $v0, $zero, 0x53
/* 3D854CC 80086F04 05006214 */  bne        $v1, $v0, .Llevel_43_80086F1C
/* 3D854D0 80086F08 54000224 */   addiu     $v0, $zero, 0x54
/* 3D854D4 80086F0C 01000224 */  addiu      $v0, $zero, 0x1
/* 3D854D8 80086F10 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 3D854DC 80086F14 36006386 */  lh         $v1, 0x36($s3)
/* 3D854E0 80086F18 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_43_80086F1C:
/* 3D854E4 80086F1C 02006214 */  bne        $v1, $v0, .Llevel_43_80086F28
/* 3D854E8 80086F20 00000000 */   nop
/* 3D854EC 80086F24 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_43_80086F28:
/* 3D854F0 80086F28 36006386 */  lh         $v1, 0x36($s3)
/* 3D854F4 80086F2C 55000224 */  addiu      $v0, $zero, 0x55
/* 3D854F8 80086F30 05006214 */  bne        $v1, $v0, .Llevel_43_80086F48
/* 3D854FC 80086F34 56000224 */   addiu     $v0, $zero, 0x56
/* 3D85500 80086F38 03000224 */  addiu      $v0, $zero, 0x3
/* 3D85504 80086F3C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 3D85508 80086F40 36006386 */  lh         $v1, 0x36($s3)
/* 3D8550C 80086F44 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_43_80086F48:
/* 3D85510 80086F48 02006214 */  bne        $v1, $v0, .Llevel_43_80086F54
/* 3D85514 80086F4C 04000224 */   addiu     $v0, $zero, 0x4
/* 3D85518 80086F50 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_43_80086F54:
/* 3D8551C 80086F54 36006386 */  lh         $v1, 0x36($s3)
/* 3D85520 80086F58 57000224 */  addiu      $v0, $zero, 0x57
/* 3D85524 80086F5C 1E016214 */  bne        $v1, $v0, .Llevel_43_800873D8
/* 3D85528 80086F60 21106002 */   addu      $v0, $s3, $zero
/* 3D8552C 80086F64 05000224 */  addiu      $v0, $zero, 0x5
/* 3D85530 80086F68 F51C0208 */  j          .Llevel_43_800873D4
/* 3D85534 80086F6C 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_43_80086F70:
/* 3D85538 80086F70 0000708E */  lw         $s0, 0x0($s3)
/* 3D8553C 80086F74 C8E9000C */  jal        func_8003A720
/* 3D85540 80086F78 21206002 */   addu      $a0, $s3, $zero
/* 3D85544 80086F7C AA49010C */  jal        func_800526A8
/* 3D85548 80086F80 21206002 */   addu      $a0, $s3, $zero
/* 3D8554C 80086F84 490060A2 */  sb         $zero, 0x49($s3)
/* 3D85550 80086F88 000000AE */  sw         $zero, 0x0($s0)
/* 3D85554 80086F8C 080000A6 */  sh         $zero, 0x8($s0)
/* 3D85558 80086F90 060000A6 */  sh         $zero, 0x6($s0)
/* 3D8555C 80086F94 040000A6 */  sh         $zero, 0x4($s0)
/* 3D85560 80086F98 0C0000AE */  sw         $zero, 0xC($s0)
/* 3D85564 80086F9C 0D01A012 */  beqz       $s5, .Llevel_43_800873D4
/* 3D85568 80086FA0 100000AE */   sw        $zero, 0x10($s0)
/* 3D8556C 80086FA4 0C006426 */  addiu      $a0, $s3, 0xC
/* 3D85570 80086FA8 C05D000C */  jal        VecCopy
/* 3D85574 80086FAC 0C00A526 */   addiu     $a1, $s5, 0xC
/* 3D85578 80086FB0 F61C0208 */  j          .Llevel_43_800873D8
/* 3D8557C 80086FB4 21106002 */   addu      $v0, $s3, $zero
.Llevel_43_80086FB8:
/* 3D85580 80086FB8 0000748E */  lw         $s4, 0x0($s3)
/* 3D85584 80086FBC C8E9000C */  jal        func_8003A720
/* 3D85588 80086FC0 21206002 */   addu      $a0, $s3, $zero
/* 3D8558C 80086FC4 0C006426 */  addiu      $a0, $s3, 0xC
/* 3D85590 80086FC8 0C00A526 */  addiu      $a1, $s5, 0xC
/* 3D85594 80086FCC 20000224 */  addiu      $v0, $zero, 0x20
/* 3D85598 80086FD0 C05D000C */  jal        VecCopy
/* 3D8559C 80086FD4 500062A2 */   sb        $v0, 0x50($s3)
/* 3D855A0 80086FD8 AA49010C */  jal        func_800526A8
/* 3D855A4 80086FDC 21206002 */   addu      $a0, $s3, $zero
/* 3D855A8 80086FE0 CB89010C */  jal        rand
/* 3D855AC 80086FE4 00000000 */   nop
/* 3D855B0 80086FE8 CB89010C */  jal        rand
/* 3D855B4 80086FEC FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 3D855B8 80086FF0 FF075130 */  andi       $s1, $v0, 0x7FF
/* 3D855BC 80086FF4 2C5B000C */  jal        Cos
/* 3D855C0 80086FF8 21202002 */   addu      $a0, $s1, $zero
/* 3D855C4 80086FFC 21204002 */  addu       $a0, $s2, $zero
/* 3D855C8 80087000 2C5B000C */  jal        Cos
/* 3D855CC 80087004 21804000 */   addu      $s0, $v0, $zero
/* 3D855D0 80087008 43811000 */  sra        $s0, $s0, 5
/* 3D855D4 8008700C 18000202 */  mult       $s0, $v0
/* 3D855D8 80087010 21202002 */  addu       $a0, $s1, $zero
/* 3D855DC 80087014 12380000 */  mflo       $a3
/* 3D855E0 80087018 03130700 */  sra        $v0, $a3, 12
/* 3D855E4 8008701C 2C5B000C */  jal        Cos
/* 3D855E8 80087020 000082A6 */   sh        $v0, 0x0($s4)
/* 3D855EC 80087024 21204002 */  addu       $a0, $s2, $zero
/* 3D855F0 80087028 165B000C */  jal        Sin
/* 3D855F4 8008702C 21804000 */   addu      $s0, $v0, $zero
/* 3D855F8 80087030 43811000 */  sra        $s0, $s0, 5
/* 3D855FC 80087034 18000202 */  mult       $s0, $v0
/* 3D85600 80087038 21202002 */  addu       $a0, $s1, $zero
/* 3D85604 8008703C 12380000 */  mflo       $a3
/* 3D85608 80087040 03130700 */  sra        $v0, $a3, 12
/* 3D8560C 80087044 165B000C */  jal        Sin
/* 3D85610 80087048 020082A6 */   sh        $v0, 0x2($s4)
/* 3D85614 8008704C 43110200 */  sra        $v0, $v0, 5
/* 3D85618 80087050 040082A6 */  sh         $v0, 0x4($s4)
/* 3D8561C 80087054 1800A28E */  lw         $v0, 0x18($s5)
/* 3D85620 80087058 0200033C */  lui        $v1, (0x20000 >> 16)
/* 3D85624 8008705C 24104300 */  and        $v0, $v0, $v1
/* 3D85628 80087060 13004010 */  beqz       $v0, .Llevel_43_800870B0
/* 3D8562C 80087064 00000000 */   nop
/* 3D85630 80087068 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 3D85634 8008706C 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 3D85638 80087070 00008396 */  lhu        $v1, 0x0($s4)
/* 3D8563C 80087074 83110200 */  sra        $v0, $v0, 6
/* 3D85640 80087078 21186200 */  addu       $v1, $v1, $v0
/* 3D85644 8008707C 000083A6 */  sh         $v1, 0x0($s4)
/* 3D85648 80087080 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 3D8564C 80087084 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 3D85650 80087088 02008396 */  lhu        $v1, 0x2($s4)
/* 3D85654 8008708C 83110200 */  sra        $v0, $v0, 6
/* 3D85658 80087090 21186200 */  addu       $v1, $v1, $v0
/* 3D8565C 80087094 020083A6 */  sh         $v1, 0x2($s4)
/* 3D85660 80087098 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 3D85664 8008709C 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 3D85668 800870A0 04008396 */  lhu        $v1, 0x4($s4)
/* 3D8566C 800870A4 83110200 */  sra        $v0, $v0, 6
/* 3D85670 800870A8 21186200 */  addu       $v1, $v1, $v0
/* 3D85674 800870AC 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_43_800870B0:
/* 3D85678 800870B0 00008286 */  lh         $v0, 0x0($s4)
/* 3D8567C 800870B4 0C00638E */  lw         $v1, 0xC($s3)
/* 3D85680 800870B8 80100200 */  sll        $v0, $v0, 2
/* 3D85684 800870BC 21186200 */  addu       $v1, $v1, $v0
/* 3D85688 800870C0 0C0063AE */  sw         $v1, 0xC($s3)
/* 3D8568C 800870C4 02008286 */  lh         $v0, 0x2($s4)
/* 3D85690 800870C8 1000638E */  lw         $v1, 0x10($s3)
/* 3D85694 800870CC 80100200 */  sll        $v0, $v0, 2
/* 3D85698 800870D0 21186200 */  addu       $v1, $v1, $v0
/* 3D8569C 800870D4 100063AE */  sw         $v1, 0x10($s3)
/* 3D856A0 800870D8 04008286 */  lh         $v0, 0x4($s4)
/* 3D856A4 800870DC 1400638E */  lw         $v1, 0x14($s3)
/* 3D856A8 800870E0 80100200 */  sll        $v0, $v0, 2
/* 3D856AC 800870E4 21186200 */  addu       $v1, $v1, $v0
/* 3D856B0 800870E8 CB89010C */  jal        rand
/* 3D856B4 800870EC 140063AE */   sw        $v1, 0x14($s3)
/* 3D856B8 800870F0 0F004230 */  andi       $v0, $v0, 0xF
/* 3D856BC 800870F4 CB89010C */  jal        rand
/* 3D856C0 800870F8 060082A6 */   sh        $v0, 0x6($s4)
/* 3D856C4 800870FC 0F004230 */  andi       $v0, $v0, 0xF
/* 3D856C8 80087100 CB89010C */  jal        rand
/* 3D856CC 80087104 080082A6 */   sh        $v0, 0x8($s4)
/* 3D856D0 80087108 0F004230 */  andi       $v0, $v0, 0xF
/* 3D856D4 8008710C 0A0082A6 */  sh         $v0, 0xA($s4)
/* 3D856D8 80087110 1400A28E */  lw         $v0, 0x14($s5)
/* 3D856DC 80087114 00000000 */  nop
/* 3D856E0 80087118 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 3D856E4 8008711C CB89010C */  jal        rand
/* 3D856E8 80087120 100082AE */   sw        $v0, 0x10($s4)
/* 3D856EC 80087124 0F004230 */  andi       $v0, $v0, 0xF
/* 3D856F0 80087128 40000324 */  addiu      $v1, $zero, 0x40
/* 3D856F4 8008712C 23186200 */  subu       $v1, $v1, $v0
/* 3D856F8 80087130 0C0083AE */  sw         $v1, 0xC($s4)
/* 3D856FC 80087134 36006296 */  lhu        $v0, 0x36($s3)
/* 3D85700 80087138 00000000 */  nop
/* 3D85704 8008713C CBFE4224 */  addiu      $v0, $v0, -0x135
/* 3D85708 80087140 0300422C */  sltiu      $v0, $v0, 0x3
/* 3D8570C 80087144 A3004010 */  beqz       $v0, .Llevel_43_800873D4
/* 3D85710 80087148 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 3D85714 8008714C 4B006292 */  lbu        $v0, 0x4B($s3)
/* 3D85718 80087150 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 3D8571C 80087154 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_43_80087158:
/* 3D85720 80087158 80004234 */  ori        $v0, $v0, 0x80
/* 3D85724 8008715C F51C0208 */  j          .Llevel_43_800873D4
/* 3D85728 80087160 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_43_80087164:
/* 3D8572C 80087164 0000718E */  lw         $s1, 0x0($s3)
/* 3D85730 80087168 C8E9000C */  jal        func_8003A720
/* 3D85734 8008716C 21206002 */   addu      $a0, $s3, $zero
/* 3D85738 80087170 21206002 */  addu       $a0, $s3, $zero
/* 3D8573C 80087174 20000224 */  addiu      $v0, $zero, 0x20
/* 3D85740 80087178 500062A2 */  sb         $v0, 0x50($s3)
/* 3D85744 8008717C FF000224 */  addiu      $v0, $zero, 0xFF
/* 3D85748 80087180 734A010C */  jal        func_800529CC
/* 3D8574C 80087184 520062A2 */   sb        $v0, 0x52($s3)
/* 3D85750 80087188 0E000224 */  addiu      $v0, $zero, 0xE
/* 3D85754 8008718C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 3D85758 80087190 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 3D8575C 80087194 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 3D85760 80087198 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 3D85764 8008719C 0780033C */  lui        $v1, %hi(D_80077058)
/* 3D85768 800871A0 5870638C */  lw         $v1, %lo(D_80077058)($v1)
/* 3D8576C 800871A4 03000224 */  addiu      $v0, $zero, 0x3
/* 3D85770 800871A8 03006214 */  bne        $v1, $v0, .Llevel_43_800871B8
/* 3D85774 800871AC 01000224 */   addiu     $v0, $zero, 0x1
/* 3D85778 800871B0 701C0208 */  j          .Llevel_43_800871C0
/* 3D8577C 800871B4 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_43_800871B8:
/* 3D85780 800871B8 02006214 */  bne        $v1, $v0, .Llevel_43_800871C4
/* 3D85784 800871BC 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_43_800871C0:
/* 3D85788 800871C0 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_43_800871C4:
/* 3D8578C 800871C4 CB89010C */  jal        rand
/* 3D85790 800871C8 00000000 */   nop
/* 3D85794 800871CC 2000A426 */  addiu      $a0, $s5, 0x20
/* 3D85798 800871D0 07004230 */  andi       $v0, $v0, 0x7
/* 3D8579C 800871D4 80100200 */  sll        $v0, $v0, 2
/* 3D857A0 800871D8 2000B027 */  addiu      $s0, $sp, 0x20
/* 3D857A4 800871DC 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 3D857A8 800871E0 21082200 */  addu       $at, $at, $v0
/* 3D857AC 800871E4 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 3D857B0 800871E8 21280002 */  addu       $a1, $s0, $zero
/* 3D857B4 800871EC 2400A0AF */  sw         $zero, 0x24($sp)
/* 3D857B8 800871F0 2000A3AF */  sw         $v1, 0x20($sp)
/* 3D857BC 800871F4 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 3D857C0 800871F8 21082200 */  addu       $at, $at, $v0
/* 3D857C4 800871FC A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 3D857C8 80087200 21300002 */  addu       $a2, $s0, $zero
/* 3D857CC 80087204 125C000C */  jal        VecRotateByMatrix
/* 3D857D0 80087208 2800A2AF */   sw        $v0, 0x28($sp)
/* 3D857D4 8008720C CB89010C */  jal        rand
/* 3D857D8 80087210 00000000 */   nop
/* 3D857DC 80087214 2000A38F */  lw         $v1, 0x20($sp)
/* 3D857E0 80087218 7F004230 */  andi       $v0, $v0, 0x7F
/* 3D857E4 8008721C C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 3D857E8 80087220 21186200 */  addu       $v1, $v1, $v0
/* 3D857EC 80087224 CB89010C */  jal        rand
/* 3D857F0 80087228 2000A3AF */   sw        $v1, 0x20($sp)
/* 3D857F4 8008722C 2400A38F */  lw         $v1, 0x24($sp)
/* 3D857F8 80087230 7F004230 */  andi       $v0, $v0, 0x7F
/* 3D857FC 80087234 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 3D85800 80087238 21186200 */  addu       $v1, $v1, $v0
/* 3D85804 8008723C CB89010C */  jal        rand
/* 3D85808 80087240 2400A3AF */   sw        $v1, 0x24($sp)
/* 3D8580C 80087244 0C006426 */  addiu      $a0, $s3, 0xC
/* 3D85810 80087248 0C00A526 */  addiu      $a1, $s5, 0xC
/* 3D85814 8008724C 21300002 */  addu       $a2, $s0, $zero
/* 3D85818 80087250 2800A38F */  lw         $v1, 0x28($sp)
/* 3D8581C 80087254 7F004230 */  andi       $v0, $v0, 0x7F
/* 3D85820 80087258 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 3D85824 8008725C 21186200 */  addu       $v1, $v1, $v0
/* 3D85828 80087260 D65D000C */  jal        VecAdd
/* 3D8582C 80087264 2800A3AF */   sw        $v1, 0x28($sp)
/* 3D85830 80087268 21202002 */  addu       $a0, $s1, $zero
/* 3D85834 8008726C C05D000C */  jal        VecCopy
/* 3D85838 80087270 21280002 */   addu      $a1, $s0, $zero
/* 3D8583C 80087274 21202002 */  addu       $a0, $s1, $zero
/* 3D85840 80087278 B25D000C */  jal        VecShiftRight
/* 3D85844 8008727C 02000524 */   addiu     $a1, $zero, 0x2
/* 3D85848 80087280 CB89010C */  jal        rand
/* 3D8584C 80087284 00000000 */   nop
/* 3D85850 80087288 0000238E */  lw         $v1, 0x0($s1)
/* 3D85854 8008728C FF004230 */  andi       $v0, $v0, 0xFF
/* 3D85858 80087290 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 3D8585C 80087294 21186200 */  addu       $v1, $v1, $v0
/* 3D85860 80087298 CB89010C */  jal        rand
/* 3D85864 8008729C 000023AE */   sw        $v1, 0x0($s1)
/* 3D85868 800872A0 0400238E */  lw         $v1, 0x4($s1)
/* 3D8586C 800872A4 FF004230 */  andi       $v0, $v0, 0xFF
/* 3D85870 800872A8 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 3D85874 800872AC 21186200 */  addu       $v1, $v1, $v0
/* 3D85878 800872B0 CB89010C */  jal        rand
/* 3D8587C 800872B4 040023AE */   sw        $v1, 0x4($s1)
/* 3D85880 800872B8 0800238E */  lw         $v1, 0x8($s1)
/* 3D85884 800872BC FF004230 */  andi       $v0, $v0, 0xFF
/* 3D85888 800872C0 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 3D8588C 800872C4 21186200 */  addu       $v1, $v1, $v0
/* 3D85890 800872C8 CB89010C */  jal        rand
/* 3D85894 800872CC 080023AE */   sw        $v1, 0x8($s1)
/* 3D85898 800872D0 CB89010C */  jal        rand
/* 3D8589C 800872D4 440062A2 */   sb        $v0, 0x44($s3)
/* 3D858A0 800872D8 CB89010C */  jal        rand
/* 3D858A4 800872DC 450062A2 */   sb        $v0, 0x45($s3)
/* 3D858A8 800872E0 CB89010C */  jal        rand
/* 3D858AC 800872E4 460062A2 */   sb        $v0, 0x46($s3)
/* 3D858B0 800872E8 0F004230 */  andi       $v0, $v0, 0xF
/* 3D858B4 800872EC CB89010C */  jal        rand
/* 3D858B8 800872F0 100022A2 */   sb        $v0, 0x10($s1)
/* 3D858BC 800872F4 0F004230 */  andi       $v0, $v0, 0xF
/* 3D858C0 800872F8 CB89010C */  jal        rand
/* 3D858C4 800872FC 110022A2 */   sb        $v0, 0x11($s1)
/* 3D858C8 80087300 0F004230 */  andi       $v0, $v0, 0xF
/* 3D858CC 80087304 120022A2 */  sb         $v0, 0x12($s1)
/* 3D858D0 80087308 1400A28E */  lw         $v0, 0x14($s5)
/* 3D858D4 8008730C CB89010C */  jal        rand
/* 3D858D8 80087310 0C0022AE */   sw        $v0, 0xC($s1)
/* 3D858DC 80087314 03004230 */  andi       $v0, $v0, 0x3
/* 3D858E0 80087318 10004224 */  addiu      $v0, $v0, 0x10
/* 3D858E4 8008731C F51C0208 */  j          .Llevel_43_800873D4
/* 3D858E8 80087320 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_43_80087324:
/* 3D858EC 80087324 0000708E */  lw         $s0, 0x0($s3)
/* 3D858F0 80087328 C8E9000C */  jal        func_8003A720
/* 3D858F4 8008732C 21206002 */   addu      $a0, $s3, $zero
/* 3D858F8 80087330 734A010C */  jal        func_800529CC
/* 3D858FC 80087334 21206002 */   addu      $a0, $s3, $zero
/* 3D85900 80087338 02000224 */  addiu      $v0, $zero, 0x2
/* 3D85904 8008733C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 3D85908 80087340 40000224 */  addiu      $v0, $zero, 0x40
/* 3D8590C 80087344 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 3D85910 80087348 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 3D85914 8008734C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 3D85918 80087350 F51C0208 */  j          .Llevel_43_800873D4
/* 3D8591C 80087354 000002AE */   sw        $v0, 0x0($s0)
.Llevel_43_80087358:
/* 3D85920 80087358 C8E9000C */  jal        func_8003A720
/* 3D85924 8008735C 21206002 */   addu      $a0, $s3, $zero
/* 3D85928 80087360 05000224 */  addiu      $v0, $zero, 0x5
/* 3D8592C 80087364 1400A012 */  beqz       $s5, .Llevel_43_800873B8
/* 3D85930 80087368 470062A2 */   sb        $v0, 0x47($s3)
/* 3D85934 8008736C 0C006426 */  addiu      $a0, $s3, 0xC
/* 3D85938 80087370 F11C0208 */  j          .Llevel_43_800873C4
/* 3D8593C 80087374 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_43_80087378:
/* 3D85940 80087378 C8E9000C */  jal        func_8003A720
/* 3D85944 8008737C 21206002 */   addu      $a0, $s3, $zero
/* 3D85948 80087380 21206002 */  addu       $a0, $s3, $zero
/* 3D8594C 80087384 20000224 */  addiu      $v0, $zero, 0x20
/* 3D85950 80087388 500062A2 */  sb         $v0, 0x50($s3)
/* 3D85954 8008738C FF000224 */  addiu      $v0, $zero, 0xFF
/* 3D85958 80087390 734A010C */  jal        func_800529CC
/* 3D8595C 80087394 520062A2 */   sb        $v0, 0x52($s3)
/* 3D85960 80087398 F61C0208 */  j          .Llevel_43_800873D8
/* 3D85964 8008739C 21106002 */   addu      $v0, $s3, $zero
.Llevel_43_800873A0:
/* 3D85968 800873A0 C8E9000C */  jal        func_8003A720
/* 3D8596C 800873A4 21206002 */   addu      $a0, $s3, $zero
/* 3D85970 800873A8 0300A012 */  beqz       $s5, .Llevel_43_800873B8
/* 3D85974 800873AC 0C00A526 */   addiu     $a1, $s5, 0xC
/* 3D85978 800873B0 F11C0208 */  j          .Llevel_43_800873C4
/* 3D8597C 800873B4 0C006426 */   addiu     $a0, $s3, 0xC
.Llevel_43_800873B8:
/* 3D85980 800873B8 0C006426 */  addiu      $a0, $s3, 0xC
/* 3D85984 800873BC 0880053C */  lui        $a1, %hi(g_Spyro)
/* 3D85988 800873C0 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_43_800873C4:
/* 3D8598C 800873C4 C05D000C */  jal        VecCopy
/* 3D85990 800873C8 00000000 */   nop
/* 3D85994 800873CC AA49010C */  jal        func_800526A8
/* 3D85998 800873D0 21206002 */   addu      $a0, $s3, $zero
.Llevel_43_800873D4:
/* 3D8599C 800873D4 21106002 */  addu       $v0, $s3, $zero
.Llevel_43_800873D8:
/* 3D859A0 800873D8 5000BF8F */  lw         $ra, 0x50($sp)
/* 3D859A4 800873DC 4C00B58F */  lw         $s5, 0x4C($sp)
/* 3D859A8 800873E0 4800B48F */  lw         $s4, 0x48($sp)
/* 3D859AC 800873E4 4400B38F */  lw         $s3, 0x44($sp)
/* 3D859B0 800873E8 4000B28F */  lw         $s2, 0x40($sp)
/* 3D859B4 800873EC 3C00B18F */  lw         $s1, 0x3C($sp)
/* 3D859B8 800873F0 3800B08F */  lw         $s0, 0x38($sp)
/* 3D859BC 800873F4 5800BD27 */  addiu      $sp, $sp, 0x58
/* 3D859C0 800873F8 0800E003 */  jr         $ra
/* 3D859C4 800873FC 00000000 */   nop
.size func_level_43_80086B38, . - func_level_43_80086B38
