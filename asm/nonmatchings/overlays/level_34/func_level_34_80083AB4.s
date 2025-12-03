.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_34_80083AB4
/* 31FE07C 80083AB4 98FFBD27 */  addiu      $sp, $sp, -0x68
/* 31FE080 80083AB8 4800B0AF */  sw         $s0, 0x48($sp)
/* 31FE084 80083ABC 21808000 */  addu       $s0, $a0, $zero
/* 31FE088 80083AC0 5C00B5AF */  sw         $s5, 0x5C($sp)
/* 31FE08C 80083AC4 21A8A000 */  addu       $s5, $a1, $zero
/* 31FE090 80083AC8 6000BFAF */  sw         $ra, 0x60($sp)
/* 31FE094 80083ACC 5800B4AF */  sw         $s4, 0x58($sp)
/* 31FE098 80083AD0 5400B3AF */  sw         $s3, 0x54($sp)
/* 31FE09C 80083AD4 5000B2AF */  sw         $s2, 0x50($sp)
/* 31FE0A0 80083AD8 3149010C */  jal        func_800524C4
/* 31FE0A4 80083ADC 4C00B1AF */   sw        $s1, 0x4C($sp)
/* 31FE0A8 80083AE0 21984000 */  addu       $s3, $v0, $zero
/* 31FE0AC 80083AE4 1400A012 */  beqz       $s5, .Llevel_34_80083B38
/* 31FE0B0 80083AE8 360070A6 */   sh        $s0, 0x36($s3)
/* 31FE0B4 80083AEC 0780043C */  lui        $a0, %hi(D_80075828)
/* 31FE0B8 80083AF0 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 31FE0BC 80083AF4 00000000 */  nop
/* 31FE0C0 80083AF8 2320A402 */  subu       $a0, $s5, $a0
/* 31FE0C4 80083AFC 40190400 */  sll        $v1, $a0, 5
/* 31FE0C8 80083B00 23186400 */  subu       $v1, $v1, $a0
/* 31FE0CC 80083B04 40190300 */  sll        $v1, $v1, 5
/* 31FE0D0 80083B08 21186400 */  addu       $v1, $v1, $a0
/* 31FE0D4 80083B0C C0100300 */  sll        $v0, $v1, 3
/* 31FE0D8 80083B10 21186200 */  addu       $v1, $v1, $v0
/* 31FE0DC 80083B14 C0130300 */  sll        $v0, $v1, 15
/* 31FE0E0 80083B18 23104300 */  subu       $v0, $v0, $v1
/* 31FE0E4 80083B1C 80100200 */  sll        $v0, $v0, 2
/* 31FE0E8 80083B20 21104400 */  addu       $v0, $v0, $a0
/* 31FE0EC 80083B24 23100200 */  negu       $v0, $v0
/* 31FE0F0 80083B28 C3180200 */  sra        $v1, $v0, 3
/* 31FE0F4 80083B2C 0001622C */  sltiu      $v0, $v1, 0x100
/* 31FE0F8 80083B30 03004014 */  bnez       $v0, .Llevel_34_80083B40
/* 31FE0FC 80083B34 9A00022A */   slti      $v0, $s0, 0x9A
.Llevel_34_80083B38:
/* 31FE100 80083B38 21180000 */  addu       $v1, $zero, $zero
/* 31FE104 80083B3C 9A00022A */  slti       $v0, $s0, 0x9A
.Llevel_34_80083B40:
/* 31FE108 80083B40 2F004010 */  beqz       $v0, .Llevel_34_80083C00
/* 31FE10C 80083B44 560063A2 */   sb        $v1, 0x56($s3)
/* 31FE110 80083B48 9800022A */  slti       $v0, $s0, 0x98
/* 31FE114 80083B4C 03024010 */  beqz       $v0, .Llevel_34_8008435C
/* 31FE118 80083B50 27000224 */   addiu     $v0, $zero, 0x27
/* 31FE11C 80083B54 7C010212 */  beq        $s0, $v0, .Llevel_34_80084148
/* 31FE120 80083B58 2800022A */   slti      $v0, $s0, 0x28
/* 31FE124 80083B5C 14004010 */  beqz       $v0, .Llevel_34_80083BB0
/* 31FE128 80083B60 10000224 */   addiu     $v0, $zero, 0x10
/* 31FE12C 80083B64 73000212 */  beq        $s0, $v0, .Llevel_34_80083D34
/* 31FE130 80083B68 1100022A */   slti      $v0, $s0, 0x11
/* 31FE134 80083B6C 07004010 */  beqz       $v0, .Llevel_34_80083B8C
/* 31FE138 80083B70 0E000224 */   addiu     $v0, $zero, 0xE
/* 31FE13C 80083B74 90010212 */  beq        $s0, $v0, .Llevel_34_800841B8
/* 31FE140 80083B78 0F000224 */   addiu     $v0, $zero, 0xF
/* 31FE144 80083B7C 46000212 */  beq        $s0, $v0, .Llevel_34_80083C98
/* 31FE148 80083B80 00000000 */   nop
/* 31FE14C 80083B84 F4110208 */  j          .Llevel_34_800847D0
/* 31FE150 80083B88 00000000 */   nop
.Llevel_34_80083B8C:
/* 31FE154 80083B8C 25000224 */  addiu      $v0, $zero, 0x25
/* 31FE158 80083B90 8A000212 */  beq        $s0, $v0, .Llevel_34_80083DBC
/* 31FE15C 80083B94 2600022A */   slti      $v0, $s0, 0x26
/* 31FE160 80083B98 DF004010 */  beqz       $v0, .Llevel_34_80083F18
/* 31FE164 80083B9C 22000224 */   addiu     $v0, $zero, 0x22
/* 31FE168 80083BA0 78000212 */  beq        $s0, $v0, .Llevel_34_80083D84
/* 31FE16C 80083BA4 00000000 */   nop
/* 31FE170 80083BA8 F4110208 */  j          .Llevel_34_800847D0
/* 31FE174 80083BAC 00000000 */   nop
.Llevel_34_80083BB0:
/* 31FE178 80083BB0 5800022A */  slti       $v0, $s0, 0x58
/* 31FE17C 80083BB4 0B004010 */  beqz       $v0, .Llevel_34_80083BE4
/* 31FE180 80083BB8 5300022A */   slti      $v0, $s0, 0x53
/* 31FE184 80083BBC 7E014010 */  beqz       $v0, .Llevel_34_800841B8
/* 31FE188 80083BC0 4300022A */   slti      $v0, $s0, 0x43
/* 31FE18C 80083BC4 02034014 */  bnez       $v0, .Llevel_34_800847D0
/* 31FE190 80083BC8 4600022A */   slti      $v0, $s0, 0x46
/* 31FE194 80083BCC F1014014 */  bnez       $v0, .Llevel_34_80084394
/* 31FE198 80083BD0 4C000224 */   addiu     $v0, $zero, 0x4C
/* 31FE19C 80083BD4 F4020212 */  beq        $s0, $v0, .Llevel_34_800847A8
/* 31FE1A0 80083BD8 00000000 */   nop
/* 31FE1A4 80083BDC F4110208 */  j          .Llevel_34_800847D0
/* 31FE1A8 80083BE0 00000000 */   nop
.Llevel_34_80083BE4:
/* 31FE1AC 80083BE4 78000224 */  addiu      $v0, $zero, 0x78
/* 31FE1B0 80083BE8 CA010212 */  beq        $s0, $v0, .Llevel_34_80084314
/* 31FE1B4 80083BEC 97000224 */   addiu     $v0, $zero, 0x97
/* 31FE1B8 80083BF0 E8010212 */  beq        $s0, $v0, .Llevel_34_80084394
/* 31FE1BC 80083BF4 00000000 */   nop
/* 31FE1C0 80083BF8 F4110208 */  j          .Llevel_34_800847D0
/* 31FE1C4 80083BFC 00000000 */   nop
.Llevel_34_80083C00:
/* 31FE1C8 80083C00 3801022A */  slti       $v0, $s0, 0x138
/* 31FE1CC 80083C04 14004010 */  beqz       $v0, .Llevel_34_80083C58
/* 31FE1D0 80083C08 3501022A */   slti      $v0, $s0, 0x135
/* 31FE1D4 80083C0C E1014010 */  beqz       $v0, .Llevel_34_80084394
/* 31FE1D8 80083C10 0201022A */   slti      $v0, $s0, 0x102
/* 31FE1DC 80083C14 07004010 */  beqz       $v0, .Llevel_34_80083C34
/* 31FE1E0 80083C18 FF00022A */   slti      $v0, $s0, 0xFF
/* 31FE1E4 80083C1C DD014010 */  beqz       $v0, .Llevel_34_80084394
/* 31FE1E8 80083C20 FB000224 */   addiu     $v0, $zero, 0xFB
/* 31FE1EC 80083C24 46020212 */  beq        $s0, $v0, .Llevel_34_80084540
/* 31FE1F0 80083C28 00000000 */   nop
/* 31FE1F4 80083C2C F4110208 */  j          .Llevel_34_800847D0
/* 31FE1F8 80083C30 00000000 */   nop
.Llevel_34_80083C34:
/* 31FE1FC 80083C34 0401022A */  slti       $v0, $s0, 0x104
/* 31FE200 80083C38 E5024014 */  bnez       $v0, .Llevel_34_800847D0
/* 31FE204 80083C3C 0E01022A */   slti      $v0, $s0, 0x10E
/* 31FE208 80083C40 AF024014 */  bnez       $v0, .Llevel_34_80084700
/* 31FE20C 80083C44 15010224 */   addiu     $v0, $zero, 0x115
/* 31FE210 80083C48 AD020212 */  beq        $s0, $v0, .Llevel_34_80084700
/* 31FE214 80083C4C 00000000 */   nop
/* 31FE218 80083C50 F4110208 */  j          .Llevel_34_800847D0
/* 31FE21C 80083C54 00000000 */   nop
.Llevel_34_80083C58:
/* 31FE220 80083C58 C401022A */  slti       $v0, $s0, 0x1C4
/* 31FE224 80083C5C 09004010 */  beqz       $v0, .Llevel_34_80083C84
/* 31FE228 80083C60 AA01022A */   slti      $v0, $s0, 0x1AA
/* 31FE22C 80083C64 D0024010 */  beqz       $v0, .Llevel_34_800847A8
/* 31FE230 80083C68 47010224 */   addiu     $v0, $zero, 0x147
/* 31FE234 80083C6C A4020212 */  beq        $s0, $v0, .Llevel_34_80084700
/* 31FE238 80083C70 95010224 */   addiu     $v0, $zero, 0x195
/* 31FE23C 80083C74 AF020212 */  beq        $s0, $v0, .Llevel_34_80084734
/* 31FE240 80083C78 00000000 */   nop
/* 31FE244 80083C7C F4110208 */  j          .Llevel_34_800847D0
/* 31FE248 80083C80 00000000 */   nop
.Llevel_34_80083C84:
/* 31FE24C 80083C84 DD010224 */  addiu      $v0, $zero, 0x1DD
/* 31FE250 80083C88 AA020212 */  beq        $s0, $v0, .Llevel_34_80084734
/* 31FE254 80083C8C 00000000 */   nop
/* 31FE258 80083C90 F4110208 */  j          .Llevel_34_800847D0
/* 31FE25C 80083C94 00000000 */   nop
.Llevel_34_80083C98:
/* 31FE260 80083C98 0000708E */  lw         $s0, 0x0($s3)
/* 31FE264 80083C9C C8E9000C */  jal        func_8003A720
/* 31FE268 80083CA0 21206002 */   addu      $a0, $s3, $zero
/* 31FE26C 80083CA4 8C000224 */  addiu      $v0, $zero, 0x8C
/* 31FE270 80083CA8 080002AE */  sw         $v0, 0x8($s0)
/* 31FE274 80083CAC 03000224 */  addiu      $v0, $zero, 0x3
/* 31FE278 80083CB0 100002A2 */  sb         $v0, 0x10($s0)
/* 31FE27C 80083CB4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 31FE280 80083CB8 140002A2 */  sb         $v0, 0x14($s0)
/* 31FE284 80083CBC 02000224 */  addiu      $v0, $zero, 0x2
/* 31FE288 80083CC0 000000AE */  sw         $zero, 0x0($s0)
/* 31FE28C 80083CC4 040000AE */  sw         $zero, 0x4($s0)
/* 31FE290 80083CC8 0E0000A2 */  sb         $zero, 0xE($s0)
/* 31FE294 80083CCC 0F0000A2 */  sb         $zero, 0xF($s0)
/* 31FE298 80083CD0 110000A2 */  sb         $zero, 0x11($s0)
/* 31FE29C 80083CD4 120000A2 */  sb         $zero, 0x12($s0)
/* 31FE2A0 80083CD8 130000A2 */  sb         $zero, 0x13($s0)
/* 31FE2A4 80083CDC 490062A2 */  sb         $v0, 0x49($s3)
/* 31FE2A8 80083CE0 18000224 */  addiu      $v0, $zero, 0x18
/* 31FE2AC 80083CE4 500062A2 */  sb         $v0, 0x50($s3)
/* 31FE2B0 80083CE8 10000224 */  addiu      $v0, $zero, 0x10
/* 31FE2B4 80083CEC 520062A2 */  sb         $v0, 0x52($s3)
/* 31FE2B8 80083CF0 20000224 */  addiu      $v0, $zero, 0x20
/* 31FE2BC 80083CF4 440062A2 */  sb         $v0, 0x44($s3)
/* 31FE2C0 80083CF8 450060A2 */  sb         $zero, 0x45($s3)
/* 31FE2C4 80083CFC 0400A012 */  beqz       $s5, .Llevel_34_80083D10
/* 31FE2C8 80083D00 460060A2 */   sb        $zero, 0x46($s3)
/* 31FE2CC 80083D04 0C006426 */  addiu      $a0, $s3, 0xC
/* 31FE2D0 80083D08 C05D000C */  jal        VecCopy
/* 31FE2D4 80083D0C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_34_80083D10:
/* 31FE2D8 80083D10 AA49010C */  jal        func_800526A8
/* 31FE2DC 80083D14 21206002 */   addu      $a0, $s3, $zero
/* 31FE2E0 80083D18 4B006292 */  lbu        $v0, 0x4B($s3)
/* 31FE2E4 80083D1C 01000324 */  addiu      $v1, $zero, 0x1
/* 31FE2E8 80083D20 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 31FE2EC 80083D24 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 31FE2F0 80083D28 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 31FE2F4 80083D2C 4D110208 */  j          .Llevel_34_80084534
/* 31FE2F8 80083D30 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_34_80083D34:
/* 31FE2FC 80083D34 0000718E */  lw         $s1, 0x0($s3)
/* 31FE300 80083D38 C8E9000C */  jal        func_8003A720
/* 31FE304 80083D3C 21206002 */   addu      $a0, $s3, $zero
/* 31FE308 80083D40 AA49010C */  jal        func_800526A8
/* 31FE30C 80083D44 21206002 */   addu      $a0, $s3, $zero
/* 31FE310 80083D48 0C007026 */  addiu      $s0, $s3, 0xC
/* 31FE314 80083D4C 21200002 */  addu       $a0, $s0, $zero
/* 31FE318 80083D50 C05D000C */  jal        VecCopy
/* 31FE31C 80083D54 0C00A526 */   addiu     $a1, $s5, 0xC
/* 31FE320 80083D58 21280002 */  addu       $a1, $s0, $zero
/* 31FE324 80083D5C 1400628E */  lw         $v0, 0x14($s3)
/* 31FE328 80083D60 04002426 */  addiu      $a0, $s1, 0x4
/* 31FE32C 80083D64 00024224 */  addiu      $v0, $v0, 0x200
/* 31FE330 80083D68 C05D000C */  jal        VecCopy
/* 31FE334 80083D6C 140062AE */   sw        $v0, 0x14($s3)
/* 31FE338 80083D70 08070224 */  addiu      $v0, $zero, 0x708
/* 31FE33C 80083D74 130020A2 */  sb         $zero, 0x13($s1)
/* 31FE340 80083D78 120020A2 */  sb         $zero, 0x12($s1)
/* 31FE344 80083D7C 01120208 */  j          .Llevel_34_80084804
/* 31FE348 80083D80 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_34_80083D84:
/* 31FE34C 80083D84 C8E9000C */  jal        func_8003A720
/* 31FE350 80083D88 21206002 */   addu      $a0, $s3, $zero
/* 31FE354 80083D8C 20000224 */  addiu      $v0, $zero, 0x20
/* 31FE358 80083D90 500062A2 */  sb         $v0, 0x50($s3)
/* 31FE35C 80083D94 FF000224 */  addiu      $v0, $zero, 0xFF
/* 31FE360 80083D98 0400A012 */  beqz       $s5, .Llevel_34_80083DAC
/* 31FE364 80083D9C 520062A2 */   sb        $v0, 0x52($s3)
/* 31FE368 80083DA0 0C006426 */  addiu      $a0, $s3, 0xC
/* 31FE36C 80083DA4 C05D000C */  jal        VecCopy
/* 31FE370 80083DA8 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_34_80083DAC:
/* 31FE374 80083DAC 734A010C */  jal        func_800529CC
/* 31FE378 80083DB0 21206002 */   addu      $a0, $s3, $zero
/* 31FE37C 80083DB4 02120208 */  j          .Llevel_34_80084808
/* 31FE380 80083DB8 21106002 */   addu      $v0, $s3, $zero
.Llevel_34_80083DBC:
/* 31FE384 80083DBC 0000708E */  lw         $s0, 0x0($s3)
/* 31FE388 80083DC0 C8E9000C */  jal        func_8003A720
/* 31FE38C 80083DC4 21206002 */   addu      $a0, $s3, $zero
/* 31FE390 80083DC8 1000A427 */  addiu      $a0, $sp, 0x10
/* 31FE394 80083DCC 0C006526 */  addiu      $a1, $s3, 0xC
/* 31FE398 80083DD0 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 31FE39C 80083DD4 C05D000C */  jal        VecCopy
/* 31FE3A0 80083DD8 1C0062AE */   sw        $v0, 0x1C($s3)
/* 31FE3A4 80083DDC 1000A427 */  addiu      $a0, $sp, 0x10
/* 31FE3A8 80083DE0 1800A28F */  lw         $v0, 0x18($sp)
/* 31FE3AC 80083DE4 0100053C */  lui        $a1, (0x10000 >> 16)
/* 31FE3B0 80083DE8 00044224 */  addiu      $v0, $v0, 0x400
/* 31FE3B4 80083DEC 7B35010C */  jal        func_8004D5EC
/* 31FE3B8 80083DF0 1800A2AF */   sw        $v0, 0x18($sp)
/* 31FE3BC 80083DF4 F44C010C */  jal        func_800533D0
/* 31FE3C0 80083DF8 21206002 */   addu      $a0, $s3, $zero
/* 31FE3C4 80083DFC 4800A392 */  lbu        $v1, 0x48($s5)
/* 31FE3C8 80083E00 52000224 */  addiu      $v0, $zero, 0x52
/* 31FE3CC 80083E04 12006210 */  beq        $v1, $v0, .Llevel_34_80083E50
/* 31FE3D0 80083E08 02000224 */   addiu     $v0, $zero, 0x2
/* 31FE3D4 80083E0C 53006228 */  slti       $v0, $v1, 0x53
/* 31FE3D8 80083E10 05004010 */  beqz       $v0, .Llevel_34_80083E28
/* 31FE3DC 80083E14 48000224 */   addiu     $v0, $zero, 0x48
/* 31FE3E0 80083E18 08006210 */  beq        $v1, $v0, .Llevel_34_80083E3C
/* 31FE3E4 80083E1C 01000224 */   addiu     $v0, $zero, 0x1
/* 31FE3E8 80083E20 9C0F0208 */  j          .Llevel_34_80083E70
/* 31FE3EC 80083E24 00000000 */   nop
.Llevel_34_80083E28:
/* 31FE3F0 80083E28 5C000224 */  addiu      $v0, $zero, 0x5C
/* 31FE3F4 80083E2C 0B006210 */  beq        $v1, $v0, .Llevel_34_80083E5C
/* 31FE3F8 80083E30 03000224 */   addiu     $v0, $zero, 0x3
/* 31FE3FC 80083E34 9C0F0208 */  j          .Llevel_34_80083E70
/* 31FE400 80083E38 00000000 */   nop
.Llevel_34_80083E3C:
/* 31FE404 80083E3C 100002A2 */  sb         $v0, 0x10($s0)
/* 31FE408 80083E40 40000224 */  addiu      $v0, $zero, 0x40
/* 31FE40C 80083E44 040002A6 */  sh         $v0, 0x4($s0)
/* 31FE410 80083E48 9B0F0208 */  j          .Llevel_34_80083E6C
/* 31FE414 80083E4C 000E0224 */   addiu     $v0, $zero, 0xE00
.Llevel_34_80083E50:
/* 31FE418 80083E50 100002A2 */  sb         $v0, 0x10($s0)
/* 31FE41C 80083E54 990F0208 */  j          .Llevel_34_80083E64
/* 31FE420 80083E58 00010224 */   addiu     $v0, $zero, 0x100
.Llevel_34_80083E5C:
/* 31FE424 80083E5C 100002A2 */  sb         $v0, 0x10($s0)
/* 31FE428 80083E60 40010224 */  addiu      $v0, $zero, 0x140
.Llevel_34_80083E64:
/* 31FE42C 80083E64 040002A6 */  sh         $v0, 0x4($s0)
/* 31FE430 80083E68 00200224 */  addiu      $v0, $zero, 0x2000
.Llevel_34_80083E6C:
/* 31FE434 80083E6C 060002A6 */  sh         $v0, 0x6($s0)
.Llevel_34_80083E70:
/* 31FE438 80083E70 4600A292 */  lbu        $v0, 0x46($s5)
/* 31FE43C 80083E74 00000000 */  nop
/* 31FE440 80083E78 40100200 */  sll        $v0, $v0, 1
/* 31FE444 80083E7C 0780013C */  lui        $at, %hi(D_8006CC78)
/* 31FE448 80083E80 21082200 */  addu       $at, $at, $v0
/* 31FE44C 80083E84 78CC2284 */  lh         $v0, %lo(D_8006CC78)($at)
/* 31FE450 80083E88 0C00A38E */  lw         $v1, 0xC($s5)
/* 31FE454 80083E8C 83100200 */  sra        $v0, $v0, 2
/* 31FE458 80083E90 21186200 */  addu       $v1, $v1, $v0
/* 31FE45C 80083E94 0C0063AE */  sw         $v1, 0xC($s3)
/* 31FE460 80083E98 4600A292 */  lbu        $v0, 0x46($s5)
/* 31FE464 80083E9C 00000000 */  nop
/* 31FE468 80083EA0 40100200 */  sll        $v0, $v0, 1
/* 31FE46C 80083EA4 0780013C */  lui        $at, %hi(D_8006CBF8)
/* 31FE470 80083EA8 21082200 */  addu       $at, $at, $v0
/* 31FE474 80083EAC F8CB2284 */  lh         $v0, %lo(D_8006CBF8)($at)
/* 31FE478 80083EB0 1000A38E */  lw         $v1, 0x10($s5)
/* 31FE47C 80083EB4 83100200 */  sra        $v0, $v0, 2
/* 31FE480 80083EB8 21186200 */  addu       $v1, $v1, $v0
/* 31FE484 80083EBC 100063AE */  sw         $v1, 0x10($s3)
/* 31FE488 80083EC0 1400A28E */  lw         $v0, 0x14($s5)
/* 31FE48C 80083EC4 00000000 */  nop
/* 31FE490 80083EC8 140062AE */  sw         $v0, 0x14($s3)
/* 31FE494 80083ECC 000015AE */  sw         $s5, 0x0($s0)
/* 31FE498 80083ED0 0C0000AE */  sw         $zero, 0xC($s0)
/* 31FE49C 80083ED4 36006286 */  lh         $v0, 0x36($s3)
/* 31FE4A0 80083ED8 480060A2 */  sb         $zero, 0x48($s3)
/* 31FE4A4 80083EDC 80100200 */  sll        $v0, $v0, 2
/* 31FE4A8 80083EE0 0780013C */  lui        $at, %hi(g_Models)
/* 31FE4AC 80083EE4 21082200 */  addu       $at, $at, $v0
/* 31FE4B0 80083EE8 7863228C */  lw         $v0, %lo(g_Models)($at)
/* 31FE4B4 80083EEC 00000000 */  nop
/* 31FE4B8 80083EF0 3800428C */  lw         $v0, 0x38($v0)
/* 31FE4BC 80083EF4 00000000 */  nop
/* 31FE4C0 80083EF8 0C004290 */  lbu        $v0, 0xC($v0)
/* 31FE4C4 80083EFC 21206002 */  addu       $a0, $s3, $zero
/* 31FE4C8 80083F00 3D0060A2 */  sb         $zero, 0x3D($s3)
/* 31FE4CC 80083F04 3C0060A2 */  sb         $zero, 0x3C($s3)
/* 31FE4D0 80083F08 3F0060A2 */  sb         $zero, 0x3F($s3)
/* 31FE4D4 80083F0C 3E0060A2 */  sb         $zero, 0x3E($s3)
/* 31FE4D8 80083F10 FF110208 */  j          .Llevel_34_800847FC
/* 31FE4DC 80083F14 410062A2 */   sb        $v0, 0x41($s3)
.Llevel_34_80083F18:
/* 31FE4E0 80083F18 0000718E */  lw         $s1, 0x0($s3)
/* 31FE4E4 80083F1C C8E9000C */  jal        func_8003A720
/* 31FE4E8 80083F20 21206002 */   addu      $a0, $s3, $zero
/* 31FE4EC 80083F24 0C007026 */  addiu      $s0, $s3, 0xC
/* 31FE4F0 80083F28 21200002 */  addu       $a0, $s0, $zero
/* 31FE4F4 80083F2C C05D000C */  jal        VecCopy
/* 31FE4F8 80083F30 0C00A526 */   addiu     $a1, $s5, 0xC
/* 31FE4FC 80083F34 3600A386 */  lh         $v1, 0x36($s5)
/* 31FE500 80083F38 26000224 */  addiu      $v0, $zero, 0x26
/* 31FE504 80083F3C 13006214 */  bne        $v1, $v0, .Llevel_34_80083F8C
/* 31FE508 80083F40 03000324 */   addiu     $v1, $zero, 0x3
/* 31FE50C 80083F44 4600A492 */  lbu        $a0, 0x46($s5)
/* 31FE510 80083F48 36006286 */  lh         $v0, 0x36($s3)
/* 31FE514 80083F4C 480063A2 */  sb         $v1, 0x48($s3)
/* 31FE518 80083F50 400060A2 */  sb         $zero, 0x40($s3)
/* 31FE51C 80083F54 80100200 */  sll        $v0, $v0, 2
/* 31FE520 80083F58 460064A2 */  sb         $a0, 0x46($s3)
/* 31FE524 80083F5C 0780013C */  lui        $at, %hi(g_Models)
/* 31FE528 80083F60 21082200 */  addu       $at, $at, $v0
/* 31FE52C 80083F64 7863228C */  lw         $v0, %lo(g_Models)($at)
/* 31FE530 80083F68 00000000 */  nop
/* 31FE534 80083F6C 4400428C */  lw         $v0, 0x44($v0)
/* 31FE538 80083F70 00000000 */  nop
/* 31FE53C 80083F74 0C004290 */  lbu        $v0, 0xC($v0)
/* 31FE540 80083F78 3C0063A2 */  sb         $v1, 0x3C($s3)
/* 31FE544 80083F7C 3D0063A2 */  sb         $v1, 0x3D($s3)
/* 31FE548 80083F80 410062A2 */  sb         $v0, 0x41($s3)
/* 31FE54C 80083F84 50100208 */  j          .Llevel_34_80084140
/* 31FE550 80083F88 03000224 */   addiu     $v0, $zero, 0x3
.Llevel_34_80083F8C:
/* 31FE554 80083F8C 3F00A392 */  lbu        $v1, 0x3F($s5)
/* 31FE558 80083F90 00000000 */  nop
/* 31FE55C 80083F94 0600622C */  sltiu      $v0, $v1, 0x6
/* 31FE560 80083F98 4A004014 */  bnez       $v0, .Llevel_34_800840C4
/* 31FE564 80083F9C 0200622C */   sltiu     $v0, $v1, 0x2
/* 31FE568 80083FA0 4600A492 */  lbu        $a0, 0x46($s5)
/* 31FE56C 80083FA4 2C5B000C */  jal        Cos
/* 31FE570 80083FA8 00210400 */   sll       $a0, $a0, 4
/* 31FE574 80083FAC 0C00638E */  lw         $v1, 0xC($s3)
/* 31FE578 80083FB0 83100200 */  sra        $v0, $v0, 2
/* 31FE57C 80083FB4 21186200 */  addu       $v1, $v1, $v0
/* 31FE580 80083FB8 0C0063AE */  sw         $v1, 0xC($s3)
/* 31FE584 80083FBC 4600A492 */  lbu        $a0, 0x46($s5)
/* 31FE588 80083FC0 165B000C */  jal        Sin
/* 31FE58C 80083FC4 00210400 */   sll       $a0, $a0, 4
/* 31FE590 80083FC8 21200002 */  addu       $a0, $s0, $zero
/* 31FE594 80083FCC 83100200 */  sra        $v0, $v0, 2
/* 31FE598 80083FD0 1000638E */  lw         $v1, 0x10($s3)
/* 31FE59C 80083FD4 1400658E */  lw         $a1, 0x14($s3)
/* 31FE5A0 80083FD8 21186200 */  addu       $v1, $v1, $v0
/* 31FE5A4 80083FDC 2C01A524 */  addiu      $a1, $a1, 0x12C
/* 31FE5A8 80083FE0 100063AE */  sw         $v1, 0x10($s3)
/* 31FE5AC 80083FE4 140065AE */  sw         $a1, 0x14($s3)
/* 31FE5B0 80083FE8 4600A292 */  lbu        $v0, 0x46($s5)
/* 31FE5B4 80083FEC 0880053C */  lui        $a1, %hi(g_Spyro)
/* 31FE5B8 80083FF0 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
/* 31FE5BC 80083FF4 645E000C */  jal        OctDistance
/* 31FE5C0 80083FF8 460062A2 */   sb        $v0, 0x46($s3)
/* 31FE5C4 80083FFC 21204000 */  addu       $a0, $v0, $zero
/* 31FE5C8 80084000 0880023C */  lui        $v0, %hi(g_Spyro + 0x8)
/* 31FE5CC 80084004 608A428C */  lw         $v0, %lo(g_Spyro + 0x8)($v0)
/* 31FE5D0 80084008 1400658E */  lw         $a1, 0x14($s3)
/* 31FE5D4 8008400C 21300000 */  addu       $a2, $zero, $zero
/* 31FE5D8 80084010 AD5A000C */  jal        Atan2
/* 31FE5DC 80084014 23284500 */   subu      $a1, $v0, $a1
/* 31FE5E0 80084018 4500A492 */  lbu        $a0, 0x45($s5)
/* 31FE5E4 8008401C 00000000 */  nop
/* 31FE5E8 80084020 23104400 */  subu       $v0, $v0, $a0
/* 31FE5EC 80084024 FF004330 */  andi       $v1, $v0, 0xFF
/* 31FE5F0 80084028 81006228 */  slti       $v0, $v1, 0x81
/* 31FE5F4 8008402C 03004014 */  bnez       $v0, .Llevel_34_8008403C
/* 31FE5F8 80084030 F0FF6228 */   slti      $v0, $v1, -0x10
/* 31FE5FC 80084034 00FF6324 */  addiu      $v1, $v1, -0x100
/* 31FE600 80084038 F0FF6228 */  slti       $v0, $v1, -0x10
.Llevel_34_8008403C:
/* 31FE604 8008403C 03004010 */  beqz       $v0, .Llevel_34_8008404C
/* 31FE608 80084040 11006228 */   slti      $v0, $v1, 0x11
/* 31FE60C 80084044 F0FF0324 */  addiu      $v1, $zero, -0x10
/* 31FE610 80084048 11006228 */  slti       $v0, $v1, 0x11
.Llevel_34_8008404C:
/* 31FE614 8008404C 03004014 */  bnez       $v0, .Llevel_34_8008405C
/* 31FE618 80084050 21108300 */   addu      $v0, $a0, $v1
/* 31FE61C 80084054 10000324 */  addiu      $v1, $zero, 0x10
/* 31FE620 80084058 21108300 */  addu       $v0, $a0, $v1
.Llevel_34_8008405C:
/* 31FE624 8008405C 450062A2 */  sb         $v0, 0x45($s3)
/* 31FE628 80084060 80000224 */  addiu      $v0, $zero, 0x80
/* 31FE62C 80084064 000022AE */  sw         $v0, 0x0($s1)
/* 31FE630 80084068 36006286 */  lh         $v0, 0x36($s3)
/* 31FE634 8008406C 02000324 */  addiu      $v1, $zero, 0x2
/* 31FE638 80084070 480063A2 */  sb         $v1, 0x48($s3)
/* 31FE63C 80084074 400060A2 */  sb         $zero, 0x40($s3)
/* 31FE640 80084078 80100200 */  sll        $v0, $v0, 2
/* 31FE644 8008407C 0780013C */  lui        $at, %hi(g_Models)
/* 31FE648 80084080 21082200 */  addu       $at, $at, $v0
/* 31FE64C 80084084 7863228C */  lw         $v0, %lo(g_Models)($at)
/* 31FE650 80084088 04000424 */  addiu      $a0, $zero, 0x4
/* 31FE654 8008408C 4000428C */  lw         $v0, 0x40($v0)
/* 31FE658 80084090 07000524 */  addiu      $a1, $zero, 0x7
/* 31FE65C 80084094 0C004290 */  lbu        $v0, 0xC($v0)
/* 31FE660 80084098 21300002 */  addu       $a2, $s0, $zero
/* 31FE664 8008409C 3C0063A2 */  sb         $v1, 0x3C($s3)
/* 31FE668 800840A0 3D0063A2 */  sb         $v1, 0x3D($s3)
/* 31FE66C 800840A4 410062A2 */  sb         $v0, 0x41($s3)
/* 31FE670 800840A8 0780023C */  lui        $v0, %hi(D_800758E4)
/* 31FE674 800840AC E458428C */  lw         $v0, %lo(D_800758E4)($v0)
/* 31FE678 800840B0 00000000 */  nop
/* 31FE67C 800840B4 09F84000 */  jalr       $v0
/* 31FE680 800840B8 10000724 */   addiu     $a3, $zero, 0x10
/* 31FE684 800840BC FF110208 */  j          .Llevel_34_800847FC
/* 31FE688 800840C0 21206002 */   addu      $a0, $s3, $zero
.Llevel_34_800840C4:
/* 31FE68C 800840C4 16004014 */  bnez       $v0, .Llevel_34_80084120
/* 31FE690 800840C8 01000324 */   addiu     $v1, $zero, 0x1
/* 31FE694 800840CC 1400628E */  lw         $v0, 0x14($s3)
/* 31FE698 800840D0 00000000 */  nop
/* 31FE69C 800840D4 2C014224 */  addiu      $v0, $v0, 0x12C
/* 31FE6A0 800840D8 140062AE */  sw         $v0, 0x14($s3)
/* 31FE6A4 800840DC 4600A492 */  lbu        $a0, 0x46($s5)
/* 31FE6A8 800840E0 36006286 */  lh         $v0, 0x36($s3)
/* 31FE6AC 800840E4 480063A2 */  sb         $v1, 0x48($s3)
/* 31FE6B0 800840E8 400060A2 */  sb         $zero, 0x40($s3)
/* 31FE6B4 800840EC 80100200 */  sll        $v0, $v0, 2
/* 31FE6B8 800840F0 460064A2 */  sb         $a0, 0x46($s3)
/* 31FE6BC 800840F4 0780013C */  lui        $at, %hi(g_Models)
/* 31FE6C0 800840F8 21082200 */  addu       $at, $at, $v0
/* 31FE6C4 800840FC 7863228C */  lw         $v0, %lo(g_Models)($at)
/* 31FE6C8 80084100 00000000 */  nop
/* 31FE6CC 80084104 3C00428C */  lw         $v0, 0x3C($v0)
/* 31FE6D0 80084108 00000000 */  nop
/* 31FE6D4 8008410C 0C004290 */  lbu        $v0, 0xC($v0)
/* 31FE6D8 80084110 3C0063A2 */  sb         $v1, 0x3C($s3)
/* 31FE6DC 80084114 3D0063A2 */  sb         $v1, 0x3D($s3)
/* 31FE6E0 80084118 4F100208 */  j          .Llevel_34_8008413C
/* 31FE6E4 8008411C 410062A2 */   sb        $v0, 0x41($s3)
.Llevel_34_80084120:
/* 31FE6E8 80084120 1400628E */  lw         $v0, 0x14($s3)
/* 31FE6EC 80084124 00000000 */  nop
/* 31FE6F0 80084128 80014224 */  addiu      $v0, $v0, 0x180
/* 31FE6F4 8008412C 140062AE */  sw         $v0, 0x14($s3)
/* 31FE6F8 80084130 4600A292 */  lbu        $v0, 0x46($s5)
/* 31FE6FC 80084134 00000000 */  nop
/* 31FE700 80084138 460062A2 */  sb         $v0, 0x46($s3)
.Llevel_34_8008413C:
/* 31FE704 8008413C 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_34_80084140:
/* 31FE708 80084140 FE110208 */  j          .Llevel_34_800847F8
/* 31FE70C 80084144 000022AE */   sw        $v0, 0x0($s1)
.Llevel_34_80084148:
/* 31FE710 80084148 0000708E */  lw         $s0, 0x0($s3)
/* 31FE714 8008414C C8E9000C */  jal        func_8003A720
/* 31FE718 80084150 21206002 */   addu      $a0, $s3, $zero
/* 31FE71C 80084154 0C006426 */  addiu      $a0, $s3, 0xC
/* 31FE720 80084158 C05D000C */  jal        VecCopy
/* 31FE724 8008415C 0C00A526 */   addiu     $a1, $s5, 0xC
/* 31FE728 80084160 AA49010C */  jal        func_800526A8
/* 31FE72C 80084164 21206002 */   addu      $a0, $s3, $zero
/* 31FE730 80084168 21300000 */  addu       $a2, $zero, $zero
/* 31FE734 8008416C 0780033C */  lui        $v1, %hi(g_Camera + 0x28)
/* 31FE738 80084170 F86D638C */  lw         $v1, %lo(g_Camera + 0x28)($v1)
/* 31FE73C 80084174 0C00648E */  lw         $a0, 0xC($s3)
/* 31FE740 80084178 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 31FE744 8008417C FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 31FE748 80084180 1000658E */  lw         $a1, 0x10($s3)
/* 31FE74C 80084184 23206400 */  subu       $a0, $v1, $a0
/* 31FE750 80084188 AD5A000C */  jal        Atan2
/* 31FE754 8008418C 23284500 */   subu      $a1, $v0, $a1
/* 31FE758 80084190 1400638E */  lw         $v1, 0x14($s3)
/* 31FE75C 80084194 460062A2 */  sb         $v0, 0x46($s3)
/* 31FE760 80084198 40000224 */  addiu      $v0, $zero, 0x40
/* 31FE764 8008419C 00FC6324 */  addiu      $v1, $v1, -0x400
/* 31FE768 800841A0 140063AE */  sw         $v1, 0x14($s3)
/* 31FE76C 800841A4 000002AE */  sw         $v0, 0x0($s0)
/* 31FE770 800841A8 01000224 */  addiu      $v0, $zero, 0x1
/* 31FE774 800841AC 040015AE */  sw         $s5, 0x4($s0)
/* 31FE778 800841B0 01120208 */  j          .Llevel_34_80084804
/* 31FE77C 800841B4 080002AE */   sw        $v0, 0x8($s0)
.Llevel_34_800841B8:
/* 31FE780 800841B8 0000708E */  lw         $s0, 0x0($s3)
/* 31FE784 800841BC C8E9000C */  jal        func_8003A720
/* 31FE788 800841C0 21206002 */   addu      $a0, $s3, $zero
/* 31FE78C 800841C4 8C000224 */  addiu      $v0, $zero, 0x8C
/* 31FE790 800841C8 000000AE */  sw         $zero, 0x0($s0)
/* 31FE794 800841CC 040000AE */  sw         $zero, 0x4($s0)
/* 31FE798 800841D0 080002AE */  sw         $v0, 0x8($s0)
/* 31FE79C 800841D4 0E0000A2 */  sb         $zero, 0xE($s0)
/* 31FE7A0 800841D8 0F0000A2 */  sb         $zero, 0xF($s0)
/* 31FE7A4 800841DC 110000A2 */  sb         $zero, 0x11($s0)
/* 31FE7A8 800841E0 120000A2 */  sb         $zero, 0x12($s0)
/* 31FE7AC 800841E4 130000A2 */  sb         $zero, 0x13($s0)
/* 31FE7B0 800841E8 3600A386 */  lh         $v1, 0x36($s5)
/* 31FE7B4 800841EC 0D000224 */  addiu      $v0, $zero, 0xD
/* 31FE7B8 800841F0 02006214 */  bne        $v1, $v0, .Llevel_34_800841FC
/* 31FE7BC 800841F4 03000224 */   addiu     $v0, $zero, 0x3
/* 31FE7C0 800841F8 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_34_800841FC:
/* 31FE7C4 800841FC 100002A2 */  sb         $v0, 0x10($s0)
/* 31FE7C8 80084200 0C007126 */  addiu      $s1, $s3, 0xC
/* 31FE7CC 80084204 21202002 */  addu       $a0, $s1, $zero
/* 31FE7D0 80084208 0C00A526 */  addiu      $a1, $s5, 0xC
/* 31FE7D4 8008420C FF000224 */  addiu      $v0, $zero, 0xFF
/* 31FE7D8 80084210 02001224 */  addiu      $s2, $zero, 0x2
/* 31FE7DC 80084214 140002A2 */  sb         $v0, 0x14($s0)
/* 31FE7E0 80084218 18000224 */  addiu      $v0, $zero, 0x18
/* 31FE7E4 8008421C 500062A2 */  sb         $v0, 0x50($s3)
/* 31FE7E8 80084220 40000224 */  addiu      $v0, $zero, 0x40
/* 31FE7EC 80084224 520062A2 */  sb         $v0, 0x52($s3)
/* 31FE7F0 80084228 20000224 */  addiu      $v0, $zero, 0x20
/* 31FE7F4 8008422C 490072A2 */  sb         $s2, 0x49($s3)
/* 31FE7F8 80084230 440062A2 */  sb         $v0, 0x44($s3)
/* 31FE7FC 80084234 450060A2 */  sb         $zero, 0x45($s3)
/* 31FE800 80084238 C05D000C */  jal        VecCopy
/* 31FE804 8008423C 460060A2 */   sb        $zero, 0x46($s3)
/* 31FE808 80084240 734A010C */  jal        func_800529CC
/* 31FE80C 80084244 21206002 */   addu      $a0, $s3, $zero
/* 31FE810 80084248 2000B027 */  addiu      $s0, $sp, 0x20
/* 31FE814 8008424C 21200002 */  addu       $a0, $s0, $zero
/* 31FE818 80084250 21282002 */  addu       $a1, $s1, $zero
/* 31FE81C 80084254 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 31FE820 80084258 C05D000C */  jal        VecCopy
/* 31FE824 8008425C 1C0062AE */   sw        $v0, 0x1C($s3)
/* 31FE828 80084260 21200002 */  addu       $a0, $s0, $zero
/* 31FE82C 80084264 2800A28F */  lw         $v0, 0x28($sp)
/* 31FE830 80084268 0100053C */  lui        $a1, (0x10000 >> 16)
/* 31FE834 8008426C 00044224 */  addiu      $v0, $v0, 0x400
/* 31FE838 80084270 7B35010C */  jal        func_8004D5EC
/* 31FE83C 80084274 2800A2AF */   sw        $v0, 0x28($sp)
/* 31FE840 80084278 F44C010C */  jal        func_800533D0
/* 31FE844 8008427C 21206002 */   addu      $a0, $s3, $zero
/* 31FE848 80084280 36006386 */  lh         $v1, 0x36($s3)
/* 31FE84C 80084284 0E000224 */  addiu      $v0, $zero, 0xE
/* 31FE850 80084288 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 31FE854 8008428C 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 31FE858 80084290 03006214 */  bne        $v1, $v0, .Llevel_34_800842A0
/* 31FE85C 80084294 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 31FE860 80084298 0C000224 */  addiu      $v0, $zero, 0xC
/* 31FE864 8008429C 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_34_800842A0:
/* 31FE868 800842A0 36006386 */  lh         $v1, 0x36($s3)
/* 31FE86C 800842A4 53000224 */  addiu      $v0, $zero, 0x53
/* 31FE870 800842A8 05006214 */  bne        $v1, $v0, .Llevel_34_800842C0
/* 31FE874 800842AC 54000224 */   addiu     $v0, $zero, 0x54
/* 31FE878 800842B0 01000224 */  addiu      $v0, $zero, 0x1
/* 31FE87C 800842B4 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 31FE880 800842B8 36006386 */  lh         $v1, 0x36($s3)
/* 31FE884 800842BC 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_34_800842C0:
/* 31FE888 800842C0 02006214 */  bne        $v1, $v0, .Llevel_34_800842CC
/* 31FE88C 800842C4 00000000 */   nop
/* 31FE890 800842C8 4F0072A2 */  sb         $s2, 0x4F($s3)
.Llevel_34_800842CC:
/* 31FE894 800842CC 36006386 */  lh         $v1, 0x36($s3)
/* 31FE898 800842D0 55000224 */  addiu      $v0, $zero, 0x55
/* 31FE89C 800842D4 05006214 */  bne        $v1, $v0, .Llevel_34_800842EC
/* 31FE8A0 800842D8 56000224 */   addiu     $v0, $zero, 0x56
/* 31FE8A4 800842DC 03000224 */  addiu      $v0, $zero, 0x3
/* 31FE8A8 800842E0 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 31FE8AC 800842E4 36006386 */  lh         $v1, 0x36($s3)
/* 31FE8B0 800842E8 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_34_800842EC:
/* 31FE8B4 800842EC 02006214 */  bne        $v1, $v0, .Llevel_34_800842F8
/* 31FE8B8 800842F0 04000224 */   addiu     $v0, $zero, 0x4
/* 31FE8BC 800842F4 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_34_800842F8:
/* 31FE8C0 800842F8 36006386 */  lh         $v1, 0x36($s3)
/* 31FE8C4 800842FC 57000224 */  addiu      $v0, $zero, 0x57
/* 31FE8C8 80084300 41016214 */  bne        $v1, $v0, .Llevel_34_80084808
/* 31FE8CC 80084304 21106002 */   addu      $v0, $s3, $zero
/* 31FE8D0 80084308 05000224 */  addiu      $v0, $zero, 0x5
/* 31FE8D4 8008430C 01120208 */  j          .Llevel_34_80084804
/* 31FE8D8 80084310 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_34_80084314:
/* 31FE8DC 80084314 0000708E */  lw         $s0, 0x0($s3)
/* 31FE8E0 80084318 C8E9000C */  jal        func_8003A720
/* 31FE8E4 8008431C 21206002 */   addu      $a0, $s3, $zero
/* 31FE8E8 80084320 AA49010C */  jal        func_800526A8
/* 31FE8EC 80084324 21206002 */   addu      $a0, $s3, $zero
/* 31FE8F0 80084328 490060A2 */  sb         $zero, 0x49($s3)
/* 31FE8F4 8008432C 000000AE */  sw         $zero, 0x0($s0)
/* 31FE8F8 80084330 080000A6 */  sh         $zero, 0x8($s0)
/* 31FE8FC 80084334 060000A6 */  sh         $zero, 0x6($s0)
/* 31FE900 80084338 040000A6 */  sh         $zero, 0x4($s0)
/* 31FE904 8008433C 0C0000AE */  sw         $zero, 0xC($s0)
/* 31FE908 80084340 3001A012 */  beqz       $s5, .Llevel_34_80084804
/* 31FE90C 80084344 100000AE */   sw        $zero, 0x10($s0)
/* 31FE910 80084348 0C006426 */  addiu      $a0, $s3, 0xC
/* 31FE914 8008434C C05D000C */  jal        VecCopy
/* 31FE918 80084350 0C00A526 */   addiu     $a1, $s5, 0xC
/* 31FE91C 80084354 02120208 */  j          .Llevel_34_80084808
/* 31FE920 80084358 21106002 */   addu      $v0, $s3, $zero
.Llevel_34_8008435C:
/* 31FE924 8008435C C8E9000C */  jal        func_8003A720
/* 31FE928 80084360 21206002 */   addu      $a0, $s3, $zero
/* 31FE92C 80084364 21206002 */  addu       $a0, $s3, $zero
/* 31FE930 80084368 20000224 */  addiu      $v0, $zero, 0x20
/* 31FE934 8008436C 500062A2 */  sb         $v0, 0x50($s3)
/* 31FE938 80084370 FF000224 */  addiu      $v0, $zero, 0xFF
/* 31FE93C 80084374 734A010C */  jal        func_800529CC
/* 31FE940 80084378 520062A2 */   sb        $v0, 0x52($s3)
/* 31FE944 8008437C 0D000224 */  addiu      $v0, $zero, 0xD
/* 31FE948 80084380 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 31FE94C 80084384 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 31FE950 80084388 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 31FE954 8008438C 01120208 */  j          .Llevel_34_80084804
/* 31FE958 80084390 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_34_80084394:
/* 31FE95C 80084394 0000748E */  lw         $s4, 0x0($s3)
/* 31FE960 80084398 C8E9000C */  jal        func_8003A720
/* 31FE964 8008439C 21206002 */   addu      $a0, $s3, $zero
/* 31FE968 800843A0 0C006426 */  addiu      $a0, $s3, 0xC
/* 31FE96C 800843A4 0C00A526 */  addiu      $a1, $s5, 0xC
/* 31FE970 800843A8 20000224 */  addiu      $v0, $zero, 0x20
/* 31FE974 800843AC C05D000C */  jal        VecCopy
/* 31FE978 800843B0 500062A2 */   sb        $v0, 0x50($s3)
/* 31FE97C 800843B4 AA49010C */  jal        func_800526A8
/* 31FE980 800843B8 21206002 */   addu      $a0, $s3, $zero
/* 31FE984 800843BC CB89010C */  jal        rand
/* 31FE988 800843C0 00000000 */   nop
/* 31FE98C 800843C4 CB89010C */  jal        rand
/* 31FE990 800843C8 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 31FE994 800843CC FF075130 */  andi       $s1, $v0, 0x7FF
/* 31FE998 800843D0 2C5B000C */  jal        Cos
/* 31FE99C 800843D4 21202002 */   addu      $a0, $s1, $zero
/* 31FE9A0 800843D8 21204002 */  addu       $a0, $s2, $zero
/* 31FE9A4 800843DC 2C5B000C */  jal        Cos
/* 31FE9A8 800843E0 21804000 */   addu      $s0, $v0, $zero
/* 31FE9AC 800843E4 43811000 */  sra        $s0, $s0, 5
/* 31FE9B0 800843E8 18000202 */  mult       $s0, $v0
/* 31FE9B4 800843EC 21202002 */  addu       $a0, $s1, $zero
/* 31FE9B8 800843F0 12400000 */  mflo       $t0
/* 31FE9BC 800843F4 03130800 */  sra        $v0, $t0, 12
/* 31FE9C0 800843F8 2C5B000C */  jal        Cos
/* 31FE9C4 800843FC 000082A6 */   sh        $v0, 0x0($s4)
/* 31FE9C8 80084400 21204002 */  addu       $a0, $s2, $zero
/* 31FE9CC 80084404 165B000C */  jal        Sin
/* 31FE9D0 80084408 21804000 */   addu      $s0, $v0, $zero
/* 31FE9D4 8008440C 43811000 */  sra        $s0, $s0, 5
/* 31FE9D8 80084410 18000202 */  mult       $s0, $v0
/* 31FE9DC 80084414 21202002 */  addu       $a0, $s1, $zero
/* 31FE9E0 80084418 12400000 */  mflo       $t0
/* 31FE9E4 8008441C 03130800 */  sra        $v0, $t0, 12
/* 31FE9E8 80084420 165B000C */  jal        Sin
/* 31FE9EC 80084424 020082A6 */   sh        $v0, 0x2($s4)
/* 31FE9F0 80084428 43110200 */  sra        $v0, $v0, 5
/* 31FE9F4 8008442C 040082A6 */  sh         $v0, 0x4($s4)
/* 31FE9F8 80084430 1800A28E */  lw         $v0, 0x18($s5)
/* 31FE9FC 80084434 0200033C */  lui        $v1, (0x20000 >> 16)
/* 31FEA00 80084438 24104300 */  and        $v0, $v0, $v1
/* 31FEA04 8008443C 13004010 */  beqz       $v0, .Llevel_34_8008448C
/* 31FEA08 80084440 00000000 */   nop
/* 31FEA0C 80084444 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 31FEA10 80084448 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 31FEA14 8008444C 00008396 */  lhu        $v1, 0x0($s4)
/* 31FEA18 80084450 83110200 */  sra        $v0, $v0, 6
/* 31FEA1C 80084454 21186200 */  addu       $v1, $v1, $v0
/* 31FEA20 80084458 000083A6 */  sh         $v1, 0x0($s4)
/* 31FEA24 8008445C 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 31FEA28 80084460 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 31FEA2C 80084464 02008396 */  lhu        $v1, 0x2($s4)
/* 31FEA30 80084468 83110200 */  sra        $v0, $v0, 6
/* 31FEA34 8008446C 21186200 */  addu       $v1, $v1, $v0
/* 31FEA38 80084470 020083A6 */  sh         $v1, 0x2($s4)
/* 31FEA3C 80084474 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 31FEA40 80084478 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 31FEA44 8008447C 04008396 */  lhu        $v1, 0x4($s4)
/* 31FEA48 80084480 83110200 */  sra        $v0, $v0, 6
/* 31FEA4C 80084484 21186200 */  addu       $v1, $v1, $v0
/* 31FEA50 80084488 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_34_8008448C:
/* 31FEA54 8008448C 00008286 */  lh         $v0, 0x0($s4)
/* 31FEA58 80084490 0C00638E */  lw         $v1, 0xC($s3)
/* 31FEA5C 80084494 80100200 */  sll        $v0, $v0, 2
/* 31FEA60 80084498 21186200 */  addu       $v1, $v1, $v0
/* 31FEA64 8008449C 0C0063AE */  sw         $v1, 0xC($s3)
/* 31FEA68 800844A0 02008286 */  lh         $v0, 0x2($s4)
/* 31FEA6C 800844A4 1000638E */  lw         $v1, 0x10($s3)
/* 31FEA70 800844A8 80100200 */  sll        $v0, $v0, 2
/* 31FEA74 800844AC 21186200 */  addu       $v1, $v1, $v0
/* 31FEA78 800844B0 100063AE */  sw         $v1, 0x10($s3)
/* 31FEA7C 800844B4 04008286 */  lh         $v0, 0x4($s4)
/* 31FEA80 800844B8 1400638E */  lw         $v1, 0x14($s3)
/* 31FEA84 800844BC 80100200 */  sll        $v0, $v0, 2
/* 31FEA88 800844C0 21186200 */  addu       $v1, $v1, $v0
/* 31FEA8C 800844C4 CB89010C */  jal        rand
/* 31FEA90 800844C8 140063AE */   sw        $v1, 0x14($s3)
/* 31FEA94 800844CC 0F004230 */  andi       $v0, $v0, 0xF
/* 31FEA98 800844D0 CB89010C */  jal        rand
/* 31FEA9C 800844D4 060082A6 */   sh        $v0, 0x6($s4)
/* 31FEAA0 800844D8 0F004230 */  andi       $v0, $v0, 0xF
/* 31FEAA4 800844DC CB89010C */  jal        rand
/* 31FEAA8 800844E0 080082A6 */   sh        $v0, 0x8($s4)
/* 31FEAAC 800844E4 0F004230 */  andi       $v0, $v0, 0xF
/* 31FEAB0 800844E8 0A0082A6 */  sh         $v0, 0xA($s4)
/* 31FEAB4 800844EC 1400A28E */  lw         $v0, 0x14($s5)
/* 31FEAB8 800844F0 00000000 */  nop
/* 31FEABC 800844F4 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 31FEAC0 800844F8 CB89010C */  jal        rand
/* 31FEAC4 800844FC 100082AE */   sw        $v0, 0x10($s4)
/* 31FEAC8 80084500 0F004230 */  andi       $v0, $v0, 0xF
/* 31FEACC 80084504 40000324 */  addiu      $v1, $zero, 0x40
/* 31FEAD0 80084508 23186200 */  subu       $v1, $v1, $v0
/* 31FEAD4 8008450C 0C0083AE */  sw         $v1, 0xC($s4)
/* 31FEAD8 80084510 36006296 */  lhu        $v0, 0x36($s3)
/* 31FEADC 80084514 00000000 */  nop
/* 31FEAE0 80084518 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 31FEAE4 8008451C 0300422C */  sltiu      $v0, $v0, 0x3
/* 31FEAE8 80084520 B8004010 */  beqz       $v0, .Llevel_34_80084804
/* 31FEAEC 80084524 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 31FEAF0 80084528 4B006292 */  lbu        $v0, 0x4B($s3)
/* 31FEAF4 8008452C 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 31FEAF8 80084530 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_34_80084534:
/* 31FEAFC 80084534 80004234 */  ori        $v0, $v0, 0x80
/* 31FEB00 80084538 01120208 */  j          .Llevel_34_80084804
/* 31FEB04 8008453C 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_34_80084540:
/* 31FEB08 80084540 0000718E */  lw         $s1, 0x0($s3)
/* 31FEB0C 80084544 C8E9000C */  jal        func_8003A720
/* 31FEB10 80084548 21206002 */   addu      $a0, $s3, $zero
/* 31FEB14 8008454C 21206002 */  addu       $a0, $s3, $zero
/* 31FEB18 80084550 20000224 */  addiu      $v0, $zero, 0x20
/* 31FEB1C 80084554 500062A2 */  sb         $v0, 0x50($s3)
/* 31FEB20 80084558 FF000224 */  addiu      $v0, $zero, 0xFF
/* 31FEB24 8008455C 734A010C */  jal        func_800529CC
/* 31FEB28 80084560 520062A2 */   sb        $v0, 0x52($s3)
/* 31FEB2C 80084564 0E000224 */  addiu      $v0, $zero, 0xE
/* 31FEB30 80084568 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 31FEB34 8008456C 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 31FEB38 80084570 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 31FEB3C 80084574 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 31FEB40 80084578 0780033C */  lui        $v1, %hi(g_DragonCutscene + 0x28)
/* 31FEB44 8008457C 5870638C */  lw         $v1, %lo(g_DragonCutscene + 0x28)($v1)
/* 31FEB48 80084580 03000224 */  addiu      $v0, $zero, 0x3
/* 31FEB4C 80084584 03006214 */  bne        $v1, $v0, .Llevel_34_80084594
/* 31FEB50 80084588 01000224 */   addiu     $v0, $zero, 0x1
/* 31FEB54 8008458C 67110208 */  j          .Llevel_34_8008459C
/* 31FEB58 80084590 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_34_80084594:
/* 31FEB5C 80084594 02006214 */  bne        $v1, $v0, .Llevel_34_800845A0
/* 31FEB60 80084598 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_34_8008459C:
/* 31FEB64 8008459C 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_34_800845A0:
/* 31FEB68 800845A0 CB89010C */  jal        rand
/* 31FEB6C 800845A4 00000000 */   nop
/* 31FEB70 800845A8 2000A426 */  addiu      $a0, $s5, 0x20
/* 31FEB74 800845AC 07004230 */  andi       $v0, $v0, 0x7
/* 31FEB78 800845B0 80100200 */  sll        $v0, $v0, 2
/* 31FEB7C 800845B4 3000B027 */  addiu      $s0, $sp, 0x30
/* 31FEB80 800845B8 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 31FEB84 800845BC 21082200 */  addu       $at, $at, $v0
/* 31FEB88 800845C0 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 31FEB8C 800845C4 21280002 */  addu       $a1, $s0, $zero
/* 31FEB90 800845C8 3400A0AF */  sw         $zero, 0x34($sp)
/* 31FEB94 800845CC 3000A3AF */  sw         $v1, 0x30($sp)
/* 31FEB98 800845D0 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 31FEB9C 800845D4 21082200 */  addu       $at, $at, $v0
/* 31FEBA0 800845D8 A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 31FEBA4 800845DC 21300002 */  addu       $a2, $s0, $zero
/* 31FEBA8 800845E0 125C000C */  jal        VecRotateByMatrix
/* 31FEBAC 800845E4 3800A2AF */   sw        $v0, 0x38($sp)
/* 31FEBB0 800845E8 CB89010C */  jal        rand
/* 31FEBB4 800845EC 00000000 */   nop
/* 31FEBB8 800845F0 3000A38F */  lw         $v1, 0x30($sp)
/* 31FEBBC 800845F4 7F004230 */  andi       $v0, $v0, 0x7F
/* 31FEBC0 800845F8 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 31FEBC4 800845FC 21186200 */  addu       $v1, $v1, $v0
/* 31FEBC8 80084600 CB89010C */  jal        rand
/* 31FEBCC 80084604 3000A3AF */   sw        $v1, 0x30($sp)
/* 31FEBD0 80084608 3400A38F */  lw         $v1, 0x34($sp)
/* 31FEBD4 8008460C 7F004230 */  andi       $v0, $v0, 0x7F
/* 31FEBD8 80084610 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 31FEBDC 80084614 21186200 */  addu       $v1, $v1, $v0
/* 31FEBE0 80084618 CB89010C */  jal        rand
/* 31FEBE4 8008461C 3400A3AF */   sw        $v1, 0x34($sp)
/* 31FEBE8 80084620 0C006426 */  addiu      $a0, $s3, 0xC
/* 31FEBEC 80084624 0C00A526 */  addiu      $a1, $s5, 0xC
/* 31FEBF0 80084628 21300002 */  addu       $a2, $s0, $zero
/* 31FEBF4 8008462C 3800A38F */  lw         $v1, 0x38($sp)
/* 31FEBF8 80084630 7F004230 */  andi       $v0, $v0, 0x7F
/* 31FEBFC 80084634 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 31FEC00 80084638 21186200 */  addu       $v1, $v1, $v0
/* 31FEC04 8008463C D65D000C */  jal        VecAdd
/* 31FEC08 80084640 3800A3AF */   sw        $v1, 0x38($sp)
/* 31FEC0C 80084644 21202002 */  addu       $a0, $s1, $zero
/* 31FEC10 80084648 C05D000C */  jal        VecCopy
/* 31FEC14 8008464C 21280002 */   addu      $a1, $s0, $zero
/* 31FEC18 80084650 21202002 */  addu       $a0, $s1, $zero
/* 31FEC1C 80084654 B25D000C */  jal        VecShiftRight
/* 31FEC20 80084658 02000524 */   addiu     $a1, $zero, 0x2
/* 31FEC24 8008465C CB89010C */  jal        rand
/* 31FEC28 80084660 00000000 */   nop
/* 31FEC2C 80084664 0000238E */  lw         $v1, 0x0($s1)
/* 31FEC30 80084668 FF004230 */  andi       $v0, $v0, 0xFF
/* 31FEC34 8008466C 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 31FEC38 80084670 21186200 */  addu       $v1, $v1, $v0
/* 31FEC3C 80084674 CB89010C */  jal        rand
/* 31FEC40 80084678 000023AE */   sw        $v1, 0x0($s1)
/* 31FEC44 8008467C 0400238E */  lw         $v1, 0x4($s1)
/* 31FEC48 80084680 FF004230 */  andi       $v0, $v0, 0xFF
/* 31FEC4C 80084684 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 31FEC50 80084688 21186200 */  addu       $v1, $v1, $v0
/* 31FEC54 8008468C CB89010C */  jal        rand
/* 31FEC58 80084690 040023AE */   sw        $v1, 0x4($s1)
/* 31FEC5C 80084694 0800238E */  lw         $v1, 0x8($s1)
/* 31FEC60 80084698 FF004230 */  andi       $v0, $v0, 0xFF
/* 31FEC64 8008469C 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 31FEC68 800846A0 21186200 */  addu       $v1, $v1, $v0
/* 31FEC6C 800846A4 CB89010C */  jal        rand
/* 31FEC70 800846A8 080023AE */   sw        $v1, 0x8($s1)
/* 31FEC74 800846AC CB89010C */  jal        rand
/* 31FEC78 800846B0 440062A2 */   sb        $v0, 0x44($s3)
/* 31FEC7C 800846B4 CB89010C */  jal        rand
/* 31FEC80 800846B8 450062A2 */   sb        $v0, 0x45($s3)
/* 31FEC84 800846BC CB89010C */  jal        rand
/* 31FEC88 800846C0 460062A2 */   sb        $v0, 0x46($s3)
/* 31FEC8C 800846C4 0F004230 */  andi       $v0, $v0, 0xF
/* 31FEC90 800846C8 CB89010C */  jal        rand
/* 31FEC94 800846CC 100022A2 */   sb        $v0, 0x10($s1)
/* 31FEC98 800846D0 0F004230 */  andi       $v0, $v0, 0xF
/* 31FEC9C 800846D4 CB89010C */  jal        rand
/* 31FECA0 800846D8 110022A2 */   sb        $v0, 0x11($s1)
/* 31FECA4 800846DC 0F004230 */  andi       $v0, $v0, 0xF
/* 31FECA8 800846E0 120022A2 */  sb         $v0, 0x12($s1)
/* 31FECAC 800846E4 1400A28E */  lw         $v0, 0x14($s5)
/* 31FECB0 800846E8 CB89010C */  jal        rand
/* 31FECB4 800846EC 0C0022AE */   sw        $v0, 0xC($s1)
/* 31FECB8 800846F0 03004230 */  andi       $v0, $v0, 0x3
/* 31FECBC 800846F4 10004224 */  addiu      $v0, $v0, 0x10
/* 31FECC0 800846F8 01120208 */  j          .Llevel_34_80084804
/* 31FECC4 800846FC 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_34_80084700:
/* 31FECC8 80084700 0000708E */  lw         $s0, 0x0($s3)
/* 31FECCC 80084704 C8E9000C */  jal        func_8003A720
/* 31FECD0 80084708 21206002 */   addu      $a0, $s3, $zero
/* 31FECD4 8008470C 734A010C */  jal        func_800529CC
/* 31FECD8 80084710 21206002 */   addu      $a0, $s3, $zero
/* 31FECDC 80084714 02000224 */  addiu      $v0, $zero, 0x2
/* 31FECE0 80084718 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 31FECE4 8008471C 40000224 */  addiu      $v0, $zero, 0x40
/* 31FECE8 80084720 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 31FECEC 80084724 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 31FECF0 80084728 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 31FECF4 8008472C 01120208 */  j          .Llevel_34_80084804
/* 31FECF8 80084730 000002AE */   sw        $v0, 0x0($s0)
.Llevel_34_80084734:
/* 31FECFC 80084734 C8E9000C */  jal        func_8003A720
/* 31FED00 80084738 21206002 */   addu      $a0, $s3, $zero
/* 31FED04 8008473C 0300A012 */  beqz       $s5, .Llevel_34_8008474C
/* 31FED08 80084740 0C006426 */   addiu     $a0, $s3, 0xC
/* 31FED0C 80084744 D5110208 */  j          .Llevel_34_80084754
/* 31FED10 80084748 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_34_8008474C:
/* 31FED14 8008474C 0880053C */  lui        $a1, %hi(g_Spyro)
/* 31FED18 80084750 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_34_80084754:
/* 31FED1C 80084754 C05D000C */  jal        VecCopy
/* 31FED20 80084758 00000000 */   nop
/* 31FED24 8008475C 0C006426 */  addiu      $a0, $s3, 0xC
/* 31FED28 80084760 1400628E */  lw         $v0, 0x14($s3)
/* 31FED2C 80084764 00080524 */  addiu      $a1, $zero, 0x800
/* 31FED30 80084768 00024224 */  addiu      $v0, $v0, 0x200
/* 31FED34 8008476C 7B35010C */  jal        func_8004D5EC
/* 31FED38 80084770 140062AE */   sw        $v0, 0x14($s3)
/* 31FED3C 80084774 1400648E */  lw         $a0, 0x14($s3)
/* 31FED40 80084778 21184000 */  addu       $v1, $v0, $zero
/* 31FED44 8008477C 23106400 */  subu       $v0, $v1, $a0
/* 31FED48 80084780 02004104 */  bgez       $v0, .Llevel_34_8008478C
/* 31FED4C 80084784 00000000 */   nop
/* 31FED50 80084788 23100200 */  negu       $v0, $v0
.Llevel_34_8008478C:
/* 31FED54 8008478C 00084228 */  slti       $v0, $v0, 0x800
/* 31FED58 80084790 03004010 */  beqz       $v0, .Llevel_34_800847A0
/* 31FED5C 80084794 00FE8224 */   addiu     $v0, $a0, -0x200
/* 31FED60 80084798 FE110208 */  j          .Llevel_34_800847F8
/* 31FED64 8008479C 140063AE */   sw        $v1, 0x14($s3)
.Llevel_34_800847A0:
/* 31FED68 800847A0 FE110208 */  j          .Llevel_34_800847F8
/* 31FED6C 800847A4 140062AE */   sw        $v0, 0x14($s3)
.Llevel_34_800847A8:
/* 31FED70 800847A8 C8E9000C */  jal        func_8003A720
/* 31FED74 800847AC 21206002 */   addu      $a0, $s3, $zero
/* 31FED78 800847B0 21206002 */  addu       $a0, $s3, $zero
/* 31FED7C 800847B4 20000224 */  addiu      $v0, $zero, 0x20
/* 31FED80 800847B8 500062A2 */  sb         $v0, 0x50($s3)
/* 31FED84 800847BC FF000224 */  addiu      $v0, $zero, 0xFF
/* 31FED88 800847C0 734A010C */  jal        func_800529CC
/* 31FED8C 800847C4 520062A2 */   sb        $v0, 0x52($s3)
/* 31FED90 800847C8 02120208 */  j          .Llevel_34_80084808
/* 31FED94 800847CC 21106002 */   addu      $v0, $s3, $zero
.Llevel_34_800847D0:
/* 31FED98 800847D0 C8E9000C */  jal        func_8003A720
/* 31FED9C 800847D4 21206002 */   addu      $a0, $s3, $zero
/* 31FEDA0 800847D8 0300A012 */  beqz       $s5, .Llevel_34_800847E8
/* 31FEDA4 800847DC 0C006426 */   addiu     $a0, $s3, 0xC
/* 31FEDA8 800847E0 FC110208 */  j          .Llevel_34_800847F0
/* 31FEDAC 800847E4 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_34_800847E8:
/* 31FEDB0 800847E8 0880053C */  lui        $a1, %hi(g_Spyro)
/* 31FEDB4 800847EC 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_34_800847F0:
/* 31FEDB8 800847F0 C05D000C */  jal        VecCopy
/* 31FEDBC 800847F4 00000000 */   nop
.Llevel_34_800847F8:
/* 31FEDC0 800847F8 21206002 */  addu       $a0, $s3, $zero
.Llevel_34_800847FC:
/* 31FEDC4 800847FC AA49010C */  jal        func_800526A8
/* 31FEDC8 80084800 00000000 */   nop
.Llevel_34_80084804:
/* 31FEDCC 80084804 21106002 */  addu       $v0, $s3, $zero
.Llevel_34_80084808:
/* 31FEDD0 80084808 6000BF8F */  lw         $ra, 0x60($sp)
/* 31FEDD4 8008480C 5C00B58F */  lw         $s5, 0x5C($sp)
/* 31FEDD8 80084810 5800B48F */  lw         $s4, 0x58($sp)
/* 31FEDDC 80084814 5400B38F */  lw         $s3, 0x54($sp)
/* 31FEDE0 80084818 5000B28F */  lw         $s2, 0x50($sp)
/* 31FEDE4 8008481C 4C00B18F */  lw         $s1, 0x4C($sp)
/* 31FEDE8 80084820 4800B08F */  lw         $s0, 0x48($sp)
/* 31FEDEC 80084824 6800BD27 */  addiu      $sp, $sp, 0x68
/* 31FEDF0 80084828 0800E003 */  jr         $ra
/* 31FEDF4 8008482C 00000000 */   nop
.size func_level_34_80083AB4, . - func_level_34_80083AB4
