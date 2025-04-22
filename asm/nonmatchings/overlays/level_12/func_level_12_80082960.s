.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_12_80082960
/* EFDF28 80082960 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* EFDF2C 80082964 3800B0AF */  sw         $s0, 0x38($sp)
/* EFDF30 80082968 21808000 */  addu       $s0, $a0, $zero
/* EFDF34 8008296C 4C00B5AF */  sw         $s5, 0x4C($sp)
/* EFDF38 80082970 21A8A000 */  addu       $s5, $a1, $zero
/* EFDF3C 80082974 5000BFAF */  sw         $ra, 0x50($sp)
/* EFDF40 80082978 4800B4AF */  sw         $s4, 0x48($sp)
/* EFDF44 8008297C 4400B3AF */  sw         $s3, 0x44($sp)
/* EFDF48 80082980 4000B2AF */  sw         $s2, 0x40($sp)
/* EFDF4C 80082984 3149010C */  jal        func_800524C4
/* EFDF50 80082988 3C00B1AF */   sw        $s1, 0x3C($sp)
/* EFDF54 8008298C 21984000 */  addu       $s3, $v0, $zero
/* EFDF58 80082990 1400A012 */  beqz       $s5, .Llevel_12_800829E4
/* EFDF5C 80082994 360070A6 */   sh        $s0, 0x36($s3)
/* EFDF60 80082998 0780043C */  lui        $a0, %hi(D_80075828)
/* EFDF64 8008299C 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* EFDF68 800829A0 00000000 */  nop
/* EFDF6C 800829A4 2320A402 */  subu       $a0, $s5, $a0
/* EFDF70 800829A8 40190400 */  sll        $v1, $a0, 5
/* EFDF74 800829AC 23186400 */  subu       $v1, $v1, $a0
/* EFDF78 800829B0 40190300 */  sll        $v1, $v1, 5
/* EFDF7C 800829B4 21186400 */  addu       $v1, $v1, $a0
/* EFDF80 800829B8 C0100300 */  sll        $v0, $v1, 3
/* EFDF84 800829BC 21186200 */  addu       $v1, $v1, $v0
/* EFDF88 800829C0 C0130300 */  sll        $v0, $v1, 15
/* EFDF8C 800829C4 23104300 */  subu       $v0, $v0, $v1
/* EFDF90 800829C8 80100200 */  sll        $v0, $v0, 2
/* EFDF94 800829CC 21104400 */  addu       $v0, $v0, $a0
/* EFDF98 800829D0 23100200 */  negu       $v0, $v0
/* EFDF9C 800829D4 C3180200 */  sra        $v1, $v0, 3
/* EFDFA0 800829D8 0001622C */  sltiu      $v0, $v1, 0x100
/* EFDFA4 800829DC 03004014 */  bnez       $v0, .Llevel_12_800829EC
/* EFDFA8 800829E0 0E01022A */   slti      $v0, $s0, 0x10E
.Llevel_12_800829E4:
/* EFDFAC 800829E4 21180000 */  addu       $v1, $zero, $zero
/* EFDFB0 800829E8 0E01022A */  slti       $v0, $s0, 0x10E
.Llevel_12_800829EC:
/* EFDFB4 800829EC 29004010 */  beqz       $v0, .Llevel_12_80082A94
/* EFDFB8 800829F0 560063A2 */   sb        $v1, 0x56($s3)
/* EFDFBC 800829F4 0401022A */  slti       $v0, $s0, 0x104
/* EFDFC0 800829F8 D2014010 */  beqz       $v0, .Llevel_12_80083144
/* EFDFC4 800829FC 5800022A */   slti      $v0, $s0, 0x58
/* EFDFC8 80082A00 14004010 */  beqz       $v0, .Llevel_12_80082A54
/* EFDFCC 80082A04 5300022A */   slti      $v0, $s0, 0x53
/* EFDFD0 80082A08 8B004010 */  beqz       $v0, .Llevel_12_80082C38
/* EFDFD4 80082A0C 10000224 */   addiu     $v0, $zero, 0x10
/* EFDFD8 80082A10 67000212 */  beq        $s0, $v0, .Llevel_12_80082BB0
/* EFDFDC 80082A14 1100022A */   slti      $v0, $s0, 0x11
/* EFDFE0 80082A18 07004010 */  beqz       $v0, .Llevel_12_80082A38
/* EFDFE4 80082A1C 0E000224 */   addiu     $v0, $zero, 0xE
/* EFDFE8 80082A20 85000212 */  beq        $s0, $v0, .Llevel_12_80082C38
/* EFDFEC 80082A24 0F000224 */   addiu     $v0, $zero, 0xF
/* EFDFF0 80082A28 3A000212 */  beq        $s0, $v0, .Llevel_12_80082B14
/* EFDFF4 80082A2C 00000000 */   nop
/* EFDFF8 80082A30 850C0208 */  j          .Llevel_12_80083214
/* EFDFFC 80082A34 00000000 */   nop
.Llevel_12_80082A38:
/* EFE000 80082A38 22000224 */  addiu      $v0, $zero, 0x22
/* EFE004 80082A3C 70000212 */  beq        $s0, $v0, .Llevel_12_80082C00
/* EFE008 80082A40 4C000224 */   addiu     $v0, $zero, 0x4C
/* EFE00C 80082A44 E9010212 */  beq        $s0, $v0, .Llevel_12_800831EC
/* EFE010 80082A48 00000000 */   nop
/* EFE014 80082A4C 850C0208 */  j          .Llevel_12_80083214
/* EFE018 80082A50 00000000 */   nop
.Llevel_12_80082A54:
/* EFE01C 80082A54 FB000224 */  addiu      $v0, $zero, 0xFB
/* EFE020 80082A58 4A010212 */  beq        $s0, $v0, .Llevel_12_80082F84
/* EFE024 80082A5C FC00022A */   slti      $v0, $s0, 0xFC
/* EFE028 80082A60 05004010 */  beqz       $v0, .Llevel_12_80082A78
/* EFE02C 80082A64 78000224 */   addiu     $v0, $zero, 0x78
/* EFE030 80082A68 C9000212 */  beq        $s0, $v0, .Llevel_12_80082D90
/* EFE034 80082A6C 00000000 */   nop
/* EFE038 80082A70 850C0208 */  j          .Llevel_12_80083214
/* EFE03C 80082A74 00000000 */   nop
.Llevel_12_80082A78:
/* EFE040 80082A78 0201022A */  slti       $v0, $s0, 0x102
/* EFE044 80082A7C E5014010 */  beqz       $v0, .Llevel_12_80083214
/* EFE048 80082A80 FF00022A */   slti      $v0, $s0, 0xFF
/* EFE04C 80082A84 D4004010 */  beqz       $v0, .Llevel_12_80082DD8
/* EFE050 80082A88 00000000 */   nop
/* EFE054 80082A8C 850C0208 */  j          .Llevel_12_80083214
/* EFE058 80082A90 00000000 */   nop
.Llevel_12_80082A94:
/* EFE05C 80082A94 95010224 */  addiu      $v0, $zero, 0x195
/* EFE060 80082A98 B7010212 */  beq        $s0, $v0, .Llevel_12_80083178
/* EFE064 80082A9C 9601022A */   slti      $v0, $s0, 0x196
/* EFE068 80082AA0 0E004010 */  beqz       $v0, .Llevel_12_80082ADC
/* EFE06C 80082AA4 3801022A */   slti      $v0, $s0, 0x138
/* EFE070 80082AA8 07004010 */  beqz       $v0, .Llevel_12_80082AC8
/* EFE074 80082AAC 3501022A */   slti      $v0, $s0, 0x135
/* EFE078 80082AB0 C9004010 */  beqz       $v0, .Llevel_12_80082DD8
/* EFE07C 80082AB4 15010224 */   addiu     $v0, $zero, 0x115
/* EFE080 80082AB8 A2010212 */  beq        $s0, $v0, .Llevel_12_80083144
/* EFE084 80082ABC 00000000 */   nop
/* EFE088 80082AC0 850C0208 */  j          .Llevel_12_80083214
/* EFE08C 80082AC4 00000000 */   nop
.Llevel_12_80082AC8:
/* EFE090 80082AC8 47010224 */  addiu      $v0, $zero, 0x147
/* EFE094 80082ACC 9D010212 */  beq        $s0, $v0, .Llevel_12_80083144
/* EFE098 80082AD0 00000000 */   nop
/* EFE09C 80082AD4 850C0208 */  j          .Llevel_12_80083214
/* EFE0A0 80082AD8 00000000 */   nop
.Llevel_12_80082ADC:
/* EFE0A4 80082ADC C401022A */  slti       $v0, $s0, 0x1C4
/* EFE0A8 80082AE0 07004010 */  beqz       $v0, .Llevel_12_80082B00
/* EFE0AC 80082AE4 AA01022A */   slti      $v0, $s0, 0x1AA
/* EFE0B0 80082AE8 C0014010 */  beqz       $v0, .Llevel_12_800831EC
/* EFE0B4 80082AEC A701022A */   slti      $v0, $s0, 0x1A7
/* EFE0B8 80082AF0 B9004010 */  beqz       $v0, .Llevel_12_80082DD8
/* EFE0BC 80082AF4 00000000 */   nop
/* EFE0C0 80082AF8 850C0208 */  j          .Llevel_12_80083214
/* EFE0C4 80082AFC 00000000 */   nop
.Llevel_12_80082B00:
/* EFE0C8 80082B00 DD010224 */  addiu      $v0, $zero, 0x1DD
/* EFE0CC 80082B04 9C010212 */  beq        $s0, $v0, .Llevel_12_80083178
/* EFE0D0 80082B08 00000000 */   nop
/* EFE0D4 80082B0C 850C0208 */  j          .Llevel_12_80083214
/* EFE0D8 80082B10 00000000 */   nop
.Llevel_12_80082B14:
/* EFE0DC 80082B14 0000708E */  lw         $s0, 0x0($s3)
/* EFE0E0 80082B18 C8E9000C */  jal        func_8003A720
/* EFE0E4 80082B1C 21206002 */   addu      $a0, $s3, $zero
/* EFE0E8 80082B20 8C000224 */  addiu      $v0, $zero, 0x8C
/* EFE0EC 80082B24 080002AE */  sw         $v0, 0x8($s0)
/* EFE0F0 80082B28 03000224 */  addiu      $v0, $zero, 0x3
/* EFE0F4 80082B2C 100002A2 */  sb         $v0, 0x10($s0)
/* EFE0F8 80082B30 FF000224 */  addiu      $v0, $zero, 0xFF
/* EFE0FC 80082B34 140002A2 */  sb         $v0, 0x14($s0)
/* EFE100 80082B38 02000224 */  addiu      $v0, $zero, 0x2
/* EFE104 80082B3C 000000AE */  sw         $zero, 0x0($s0)
/* EFE108 80082B40 040000AE */  sw         $zero, 0x4($s0)
/* EFE10C 80082B44 0E0000A2 */  sb         $zero, 0xE($s0)
/* EFE110 80082B48 0F0000A2 */  sb         $zero, 0xF($s0)
/* EFE114 80082B4C 110000A2 */  sb         $zero, 0x11($s0)
/* EFE118 80082B50 120000A2 */  sb         $zero, 0x12($s0)
/* EFE11C 80082B54 130000A2 */  sb         $zero, 0x13($s0)
/* EFE120 80082B58 490062A2 */  sb         $v0, 0x49($s3)
/* EFE124 80082B5C 18000224 */  addiu      $v0, $zero, 0x18
/* EFE128 80082B60 500062A2 */  sb         $v0, 0x50($s3)
/* EFE12C 80082B64 10000224 */  addiu      $v0, $zero, 0x10
/* EFE130 80082B68 520062A2 */  sb         $v0, 0x52($s3)
/* EFE134 80082B6C 20000224 */  addiu      $v0, $zero, 0x20
/* EFE138 80082B70 440062A2 */  sb         $v0, 0x44($s3)
/* EFE13C 80082B74 450060A2 */  sb         $zero, 0x45($s3)
/* EFE140 80082B78 0400A012 */  beqz       $s5, .Llevel_12_80082B8C
/* EFE144 80082B7C 460060A2 */   sb        $zero, 0x46($s3)
/* EFE148 80082B80 0C006426 */  addiu      $a0, $s3, 0xC
/* EFE14C 80082B84 C05D000C */  jal        VecCopy
/* EFE150 80082B88 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_12_80082B8C:
/* EFE154 80082B8C AA49010C */  jal        func_800526A8
/* EFE158 80082B90 21206002 */   addu      $a0, $s3, $zero
/* EFE15C 80082B94 4B006292 */  lbu        $v0, 0x4B($s3)
/* EFE160 80082B98 01000324 */  addiu      $v1, $zero, 0x1
/* EFE164 80082B9C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* EFE168 80082BA0 4D0060A2 */  sb         $zero, 0x4D($s3)
/* EFE16C 80082BA4 4E0060A2 */  sb         $zero, 0x4E($s3)
/* EFE170 80082BA8 DE0B0208 */  j          .Llevel_12_80082F78
/* EFE174 80082BAC 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_12_80082BB0:
/* EFE178 80082BB0 0000718E */  lw         $s1, 0x0($s3)
/* EFE17C 80082BB4 C8E9000C */  jal        func_8003A720
/* EFE180 80082BB8 21206002 */   addu      $a0, $s3, $zero
/* EFE184 80082BBC AA49010C */  jal        func_800526A8
/* EFE188 80082BC0 21206002 */   addu      $a0, $s3, $zero
/* EFE18C 80082BC4 0C007026 */  addiu      $s0, $s3, 0xC
/* EFE190 80082BC8 21200002 */  addu       $a0, $s0, $zero
/* EFE194 80082BCC C05D000C */  jal        VecCopy
/* EFE198 80082BD0 0C00A526 */   addiu     $a1, $s5, 0xC
/* EFE19C 80082BD4 21280002 */  addu       $a1, $s0, $zero
/* EFE1A0 80082BD8 1400628E */  lw         $v0, 0x14($s3)
/* EFE1A4 80082BDC 04002426 */  addiu      $a0, $s1, 0x4
/* EFE1A8 80082BE0 00024224 */  addiu      $v0, $v0, 0x200
/* EFE1AC 80082BE4 C05D000C */  jal        VecCopy
/* EFE1B0 80082BE8 140062AE */   sw        $v0, 0x14($s3)
/* EFE1B4 80082BEC 08070224 */  addiu      $v0, $zero, 0x708
/* EFE1B8 80082BF0 130020A2 */  sb         $zero, 0x13($s1)
/* EFE1BC 80082BF4 120020A2 */  sb         $zero, 0x12($s1)
/* EFE1C0 80082BF8 920C0208 */  j          .Llevel_12_80083248
/* EFE1C4 80082BFC 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_12_80082C00:
/* EFE1C8 80082C00 C8E9000C */  jal        func_8003A720
/* EFE1CC 80082C04 21206002 */   addu      $a0, $s3, $zero
/* EFE1D0 80082C08 20000224 */  addiu      $v0, $zero, 0x20
/* EFE1D4 80082C0C 500062A2 */  sb         $v0, 0x50($s3)
/* EFE1D8 80082C10 FF000224 */  addiu      $v0, $zero, 0xFF
/* EFE1DC 80082C14 0400A012 */  beqz       $s5, .Llevel_12_80082C28
/* EFE1E0 80082C18 520062A2 */   sb        $v0, 0x52($s3)
/* EFE1E4 80082C1C 0C006426 */  addiu      $a0, $s3, 0xC
/* EFE1E8 80082C20 C05D000C */  jal        VecCopy
/* EFE1EC 80082C24 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_12_80082C28:
/* EFE1F0 80082C28 734A010C */  jal        func_800529CC
/* EFE1F4 80082C2C 21206002 */   addu      $a0, $s3, $zero
/* EFE1F8 80082C30 930C0208 */  j          .Llevel_12_8008324C
/* EFE1FC 80082C34 21106002 */   addu      $v0, $s3, $zero
.Llevel_12_80082C38:
/* EFE200 80082C38 0000718E */  lw         $s1, 0x0($s3)
/* EFE204 80082C3C C8E9000C */  jal        func_8003A720
/* EFE208 80082C40 21206002 */   addu      $a0, $s3, $zero
/* EFE20C 80082C44 8C000224 */  addiu      $v0, $zero, 0x8C
/* EFE210 80082C48 000020AE */  sw         $zero, 0x0($s1)
/* EFE214 80082C4C 040020AE */  sw         $zero, 0x4($s1)
/* EFE218 80082C50 080022AE */  sw         $v0, 0x8($s1)
/* EFE21C 80082C54 0E0020A2 */  sb         $zero, 0xE($s1)
/* EFE220 80082C58 0F0020A2 */  sb         $zero, 0xF($s1)
/* EFE224 80082C5C 110020A2 */  sb         $zero, 0x11($s1)
/* EFE228 80082C60 120020A2 */  sb         $zero, 0x12($s1)
/* EFE22C 80082C64 130020A2 */  sb         $zero, 0x13($s1)
/* EFE230 80082C68 3600A386 */  lh         $v1, 0x36($s5)
/* EFE234 80082C6C 0D000224 */  addiu      $v0, $zero, 0xD
/* EFE238 80082C70 02006214 */  bne        $v1, $v0, .Llevel_12_80082C7C
/* EFE23C 80082C74 03000224 */   addiu     $v0, $zero, 0x3
/* EFE240 80082C78 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_12_80082C7C:
/* EFE244 80082C7C 100022A2 */  sb         $v0, 0x10($s1)
/* EFE248 80082C80 0C007026 */  addiu      $s0, $s3, 0xC
/* EFE24C 80082C84 21200002 */  addu       $a0, $s0, $zero
/* EFE250 80082C88 0C00A526 */  addiu      $a1, $s5, 0xC
/* EFE254 80082C8C FF000224 */  addiu      $v0, $zero, 0xFF
/* EFE258 80082C90 140022A2 */  sb         $v0, 0x14($s1)
/* EFE25C 80082C94 02001124 */  addiu      $s1, $zero, 0x2
/* EFE260 80082C98 18000224 */  addiu      $v0, $zero, 0x18
/* EFE264 80082C9C 500062A2 */  sb         $v0, 0x50($s3)
/* EFE268 80082CA0 40000224 */  addiu      $v0, $zero, 0x40
/* EFE26C 80082CA4 520062A2 */  sb         $v0, 0x52($s3)
/* EFE270 80082CA8 20000224 */  addiu      $v0, $zero, 0x20
/* EFE274 80082CAC 490071A2 */  sb         $s1, 0x49($s3)
/* EFE278 80082CB0 440062A2 */  sb         $v0, 0x44($s3)
/* EFE27C 80082CB4 450060A2 */  sb         $zero, 0x45($s3)
/* EFE280 80082CB8 C05D000C */  jal        VecCopy
/* EFE284 80082CBC 460060A2 */   sb        $zero, 0x46($s3)
/* EFE288 80082CC0 734A010C */  jal        func_800529CC
/* EFE28C 80082CC4 21206002 */   addu      $a0, $s3, $zero
/* EFE290 80082CC8 1000A427 */  addiu      $a0, $sp, 0x10
/* EFE294 80082CCC 21280002 */  addu       $a1, $s0, $zero
/* EFE298 80082CD0 FFFF0224 */  addiu      $v0, $zero, -0x1
/* EFE29C 80082CD4 C05D000C */  jal        VecCopy
/* EFE2A0 80082CD8 1C0062AE */   sw        $v0, 0x1C($s3)
/* EFE2A4 80082CDC 1000A427 */  addiu      $a0, $sp, 0x10
/* EFE2A8 80082CE0 1800A28F */  lw         $v0, 0x18($sp)
/* EFE2AC 80082CE4 0100053C */  lui        $a1, (0x10000 >> 16)
/* EFE2B0 80082CE8 00044224 */  addiu      $v0, $v0, 0x400
/* EFE2B4 80082CEC 7B35010C */  jal        func_8004D5EC
/* EFE2B8 80082CF0 1800A2AF */   sw        $v0, 0x18($sp)
/* EFE2BC 80082CF4 F44C010C */  jal        func_800533D0
/* EFE2C0 80082CF8 21206002 */   addu      $a0, $s3, $zero
/* EFE2C4 80082CFC 36006386 */  lh         $v1, 0x36($s3)
/* EFE2C8 80082D00 0E000224 */  addiu      $v0, $zero, 0xE
/* EFE2CC 80082D04 4C0060A2 */  sb         $zero, 0x4C($s3)
/* EFE2D0 80082D08 4D0060A2 */  sb         $zero, 0x4D($s3)
/* EFE2D4 80082D0C 03006214 */  bne        $v1, $v0, .Llevel_12_80082D1C
/* EFE2D8 80082D10 4E0060A2 */   sb        $zero, 0x4E($s3)
/* EFE2DC 80082D14 0C000224 */  addiu      $v0, $zero, 0xC
/* EFE2E0 80082D18 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_12_80082D1C:
/* EFE2E4 80082D1C 36006386 */  lh         $v1, 0x36($s3)
/* EFE2E8 80082D20 53000224 */  addiu      $v0, $zero, 0x53
/* EFE2EC 80082D24 05006214 */  bne        $v1, $v0, .Llevel_12_80082D3C
/* EFE2F0 80082D28 54000224 */   addiu     $v0, $zero, 0x54
/* EFE2F4 80082D2C 01000224 */  addiu      $v0, $zero, 0x1
/* EFE2F8 80082D30 4F0062A2 */  sb         $v0, 0x4F($s3)
/* EFE2FC 80082D34 36006386 */  lh         $v1, 0x36($s3)
/* EFE300 80082D38 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_12_80082D3C:
/* EFE304 80082D3C 02006214 */  bne        $v1, $v0, .Llevel_12_80082D48
/* EFE308 80082D40 00000000 */   nop
/* EFE30C 80082D44 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_12_80082D48:
/* EFE310 80082D48 36006386 */  lh         $v1, 0x36($s3)
/* EFE314 80082D4C 55000224 */  addiu      $v0, $zero, 0x55
/* EFE318 80082D50 05006214 */  bne        $v1, $v0, .Llevel_12_80082D68
/* EFE31C 80082D54 56000224 */   addiu     $v0, $zero, 0x56
/* EFE320 80082D58 03000224 */  addiu      $v0, $zero, 0x3
/* EFE324 80082D5C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* EFE328 80082D60 36006386 */  lh         $v1, 0x36($s3)
/* EFE32C 80082D64 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_12_80082D68:
/* EFE330 80082D68 02006214 */  bne        $v1, $v0, .Llevel_12_80082D74
/* EFE334 80082D6C 04000224 */   addiu     $v0, $zero, 0x4
/* EFE338 80082D70 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_12_80082D74:
/* EFE33C 80082D74 36006386 */  lh         $v1, 0x36($s3)
/* EFE340 80082D78 57000224 */  addiu      $v0, $zero, 0x57
/* EFE344 80082D7C 33016214 */  bne        $v1, $v0, .Llevel_12_8008324C
/* EFE348 80082D80 21106002 */   addu      $v0, $s3, $zero
/* EFE34C 80082D84 05000224 */  addiu      $v0, $zero, 0x5
/* EFE350 80082D88 920C0208 */  j          .Llevel_12_80083248
/* EFE354 80082D8C 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_12_80082D90:
/* EFE358 80082D90 0000708E */  lw         $s0, 0x0($s3)
/* EFE35C 80082D94 C8E9000C */  jal        func_8003A720
/* EFE360 80082D98 21206002 */   addu      $a0, $s3, $zero
/* EFE364 80082D9C AA49010C */  jal        func_800526A8
/* EFE368 80082DA0 21206002 */   addu      $a0, $s3, $zero
/* EFE36C 80082DA4 490060A2 */  sb         $zero, 0x49($s3)
/* EFE370 80082DA8 000000AE */  sw         $zero, 0x0($s0)
/* EFE374 80082DAC 080000A6 */  sh         $zero, 0x8($s0)
/* EFE378 80082DB0 060000A6 */  sh         $zero, 0x6($s0)
/* EFE37C 80082DB4 040000A6 */  sh         $zero, 0x4($s0)
/* EFE380 80082DB8 0C0000AE */  sw         $zero, 0xC($s0)
/* EFE384 80082DBC 2201A012 */  beqz       $s5, .Llevel_12_80083248
/* EFE388 80082DC0 100000AE */   sw        $zero, 0x10($s0)
/* EFE38C 80082DC4 0C006426 */  addiu      $a0, $s3, 0xC
/* EFE390 80082DC8 C05D000C */  jal        VecCopy
/* EFE394 80082DCC 0C00A526 */   addiu     $a1, $s5, 0xC
/* EFE398 80082DD0 930C0208 */  j          .Llevel_12_8008324C
/* EFE39C 80082DD4 21106002 */   addu      $v0, $s3, $zero
.Llevel_12_80082DD8:
/* EFE3A0 80082DD8 0000748E */  lw         $s4, 0x0($s3)
/* EFE3A4 80082DDC C8E9000C */  jal        func_8003A720
/* EFE3A8 80082DE0 21206002 */   addu      $a0, $s3, $zero
/* EFE3AC 80082DE4 0C006426 */  addiu      $a0, $s3, 0xC
/* EFE3B0 80082DE8 0C00A526 */  addiu      $a1, $s5, 0xC
/* EFE3B4 80082DEC 20000224 */  addiu      $v0, $zero, 0x20
/* EFE3B8 80082DF0 C05D000C */  jal        VecCopy
/* EFE3BC 80082DF4 500062A2 */   sb        $v0, 0x50($s3)
/* EFE3C0 80082DF8 AA49010C */  jal        func_800526A8
/* EFE3C4 80082DFC 21206002 */   addu      $a0, $s3, $zero
/* EFE3C8 80082E00 CB89010C */  jal        rand
/* EFE3CC 80082E04 00000000 */   nop
/* EFE3D0 80082E08 CB89010C */  jal        rand
/* EFE3D4 80082E0C FF0F5230 */   andi      $s2, $v0, 0xFFF
/* EFE3D8 80082E10 FF075130 */  andi       $s1, $v0, 0x7FF
/* EFE3DC 80082E14 2C5B000C */  jal        Cos
/* EFE3E0 80082E18 21202002 */   addu      $a0, $s1, $zero
/* EFE3E4 80082E1C 21204002 */  addu       $a0, $s2, $zero
/* EFE3E8 80082E20 2C5B000C */  jal        Cos
/* EFE3EC 80082E24 21804000 */   addu      $s0, $v0, $zero
/* EFE3F0 80082E28 43811000 */  sra        $s0, $s0, 5
/* EFE3F4 80082E2C 18000202 */  mult       $s0, $v0
/* EFE3F8 80082E30 21202002 */  addu       $a0, $s1, $zero
/* EFE3FC 80082E34 12380000 */  mflo       $a3
/* EFE400 80082E38 03130700 */  sra        $v0, $a3, 12
/* EFE404 80082E3C 2C5B000C */  jal        Cos
/* EFE408 80082E40 000082A6 */   sh        $v0, 0x0($s4)
/* EFE40C 80082E44 21204002 */  addu       $a0, $s2, $zero
/* EFE410 80082E48 165B000C */  jal        Sin
/* EFE414 80082E4C 21804000 */   addu      $s0, $v0, $zero
/* EFE418 80082E50 43811000 */  sra        $s0, $s0, 5
/* EFE41C 80082E54 18000202 */  mult       $s0, $v0
/* EFE420 80082E58 21202002 */  addu       $a0, $s1, $zero
/* EFE424 80082E5C 12380000 */  mflo       $a3
/* EFE428 80082E60 03130700 */  sra        $v0, $a3, 12
/* EFE42C 80082E64 165B000C */  jal        Sin
/* EFE430 80082E68 020082A6 */   sh        $v0, 0x2($s4)
/* EFE434 80082E6C 43110200 */  sra        $v0, $v0, 5
/* EFE438 80082E70 040082A6 */  sh         $v0, 0x4($s4)
/* EFE43C 80082E74 1800A28E */  lw         $v0, 0x18($s5)
/* EFE440 80082E78 0200033C */  lui        $v1, (0x20000 >> 16)
/* EFE444 80082E7C 24104300 */  and        $v0, $v0, $v1
/* EFE448 80082E80 13004010 */  beqz       $v0, .Llevel_12_80082ED0
/* EFE44C 80082E84 00000000 */   nop
/* EFE450 80082E88 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* EFE454 80082E8C 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* EFE458 80082E90 00008396 */  lhu        $v1, 0x0($s4)
/* EFE45C 80082E94 83110200 */  sra        $v0, $v0, 6
/* EFE460 80082E98 21186200 */  addu       $v1, $v1, $v0
/* EFE464 80082E9C 000083A6 */  sh         $v1, 0x0($s4)
/* EFE468 80082EA0 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* EFE46C 80082EA4 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* EFE470 80082EA8 02008396 */  lhu        $v1, 0x2($s4)
/* EFE474 80082EAC 83110200 */  sra        $v0, $v0, 6
/* EFE478 80082EB0 21186200 */  addu       $v1, $v1, $v0
/* EFE47C 80082EB4 020083A6 */  sh         $v1, 0x2($s4)
/* EFE480 80082EB8 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* EFE484 80082EBC 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* EFE488 80082EC0 04008396 */  lhu        $v1, 0x4($s4)
/* EFE48C 80082EC4 83110200 */  sra        $v0, $v0, 6
/* EFE490 80082EC8 21186200 */  addu       $v1, $v1, $v0
/* EFE494 80082ECC 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_12_80082ED0:
/* EFE498 80082ED0 00008286 */  lh         $v0, 0x0($s4)
/* EFE49C 80082ED4 0C00638E */  lw         $v1, 0xC($s3)
/* EFE4A0 80082ED8 80100200 */  sll        $v0, $v0, 2
/* EFE4A4 80082EDC 21186200 */  addu       $v1, $v1, $v0
/* EFE4A8 80082EE0 0C0063AE */  sw         $v1, 0xC($s3)
/* EFE4AC 80082EE4 02008286 */  lh         $v0, 0x2($s4)
/* EFE4B0 80082EE8 1000638E */  lw         $v1, 0x10($s3)
/* EFE4B4 80082EEC 80100200 */  sll        $v0, $v0, 2
/* EFE4B8 80082EF0 21186200 */  addu       $v1, $v1, $v0
/* EFE4BC 80082EF4 100063AE */  sw         $v1, 0x10($s3)
/* EFE4C0 80082EF8 04008286 */  lh         $v0, 0x4($s4)
/* EFE4C4 80082EFC 1400638E */  lw         $v1, 0x14($s3)
/* EFE4C8 80082F00 80100200 */  sll        $v0, $v0, 2
/* EFE4CC 80082F04 21186200 */  addu       $v1, $v1, $v0
/* EFE4D0 80082F08 CB89010C */  jal        rand
/* EFE4D4 80082F0C 140063AE */   sw        $v1, 0x14($s3)
/* EFE4D8 80082F10 0F004230 */  andi       $v0, $v0, 0xF
/* EFE4DC 80082F14 CB89010C */  jal        rand
/* EFE4E0 80082F18 060082A6 */   sh        $v0, 0x6($s4)
/* EFE4E4 80082F1C 0F004230 */  andi       $v0, $v0, 0xF
/* EFE4E8 80082F20 CB89010C */  jal        rand
/* EFE4EC 80082F24 080082A6 */   sh        $v0, 0x8($s4)
/* EFE4F0 80082F28 0F004230 */  andi       $v0, $v0, 0xF
/* EFE4F4 80082F2C 0A0082A6 */  sh         $v0, 0xA($s4)
/* EFE4F8 80082F30 1400A28E */  lw         $v0, 0x14($s5)
/* EFE4FC 80082F34 00000000 */  nop
/* EFE500 80082F38 C0FF4224 */  addiu      $v0, $v0, -0x40
/* EFE504 80082F3C CB89010C */  jal        rand
/* EFE508 80082F40 100082AE */   sw        $v0, 0x10($s4)
/* EFE50C 80082F44 0F004230 */  andi       $v0, $v0, 0xF
/* EFE510 80082F48 40000324 */  addiu      $v1, $zero, 0x40
/* EFE514 80082F4C 23186200 */  subu       $v1, $v1, $v0
/* EFE518 80082F50 0C0083AE */  sw         $v1, 0xC($s4)
/* EFE51C 80082F54 36006296 */  lhu        $v0, 0x36($s3)
/* EFE520 80082F58 00000000 */  nop
/* EFE524 80082F5C CBFE4224 */  addiu      $v0, $v0, -0x135
/* EFE528 80082F60 0300422C */  sltiu      $v0, $v0, 0x3
/* EFE52C 80082F64 B8004010 */  beqz       $v0, .Llevel_12_80083248
/* EFE530 80082F68 A100033C */   lui       $v1, (0xA18618 >> 16)
/* EFE534 80082F6C 4B006292 */  lbu        $v0, 0x4B($s3)
/* EFE538 80082F70 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* EFE53C 80082F74 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_12_80082F78:
/* EFE540 80082F78 80004234 */  ori        $v0, $v0, 0x80
/* EFE544 80082F7C 920C0208 */  j          .Llevel_12_80083248
/* EFE548 80082F80 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_12_80082F84:
/* EFE54C 80082F84 0000718E */  lw         $s1, 0x0($s3)
/* EFE550 80082F88 C8E9000C */  jal        func_8003A720
/* EFE554 80082F8C 21206002 */   addu      $a0, $s3, $zero
/* EFE558 80082F90 21206002 */  addu       $a0, $s3, $zero
/* EFE55C 80082F94 20000224 */  addiu      $v0, $zero, 0x20
/* EFE560 80082F98 500062A2 */  sb         $v0, 0x50($s3)
/* EFE564 80082F9C FF000224 */  addiu      $v0, $zero, 0xFF
/* EFE568 80082FA0 734A010C */  jal        func_800529CC
/* EFE56C 80082FA4 520062A2 */   sb        $v0, 0x52($s3)
/* EFE570 80082FA8 0E000224 */  addiu      $v0, $zero, 0xE
/* EFE574 80082FAC 4C0060A2 */  sb         $zero, 0x4C($s3)
/* EFE578 80082FB0 4D0060A2 */  sb         $zero, 0x4D($s3)
/* EFE57C 80082FB4 4E0060A2 */  sb         $zero, 0x4E($s3)
/* EFE580 80082FB8 4F0062A2 */  sb         $v0, 0x4F($s3)
/* EFE584 80082FBC 0780033C */  lui        $v1, %hi(D_80077058)
/* EFE588 80082FC0 5870638C */  lw         $v1, %lo(D_80077058)($v1)
/* EFE58C 80082FC4 03000224 */  addiu      $v0, $zero, 0x3
/* EFE590 80082FC8 03006214 */  bne        $v1, $v0, .Llevel_12_80082FD8
/* EFE594 80082FCC 01000224 */   addiu     $v0, $zero, 0x1
/* EFE598 80082FD0 F80B0208 */  j          .Llevel_12_80082FE0
/* EFE59C 80082FD4 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_12_80082FD8:
/* EFE5A0 80082FD8 02006214 */  bne        $v1, $v0, .Llevel_12_80082FE4
/* EFE5A4 80082FDC 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_12_80082FE0:
/* EFE5A8 80082FE0 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_12_80082FE4:
/* EFE5AC 80082FE4 CB89010C */  jal        rand
/* EFE5B0 80082FE8 00000000 */   nop
/* EFE5B4 80082FEC 2000A426 */  addiu      $a0, $s5, 0x20
/* EFE5B8 80082FF0 07004230 */  andi       $v0, $v0, 0x7
/* EFE5BC 80082FF4 80100200 */  sll        $v0, $v0, 2
/* EFE5C0 80082FF8 2000B027 */  addiu      $s0, $sp, 0x20
/* EFE5C4 80082FFC 0780013C */  lui        $at, %hi(D_8006F3A0)
/* EFE5C8 80083000 21082200 */  addu       $at, $at, $v0
/* EFE5CC 80083004 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* EFE5D0 80083008 21280002 */  addu       $a1, $s0, $zero
/* EFE5D4 8008300C 2400A0AF */  sw         $zero, 0x24($sp)
/* EFE5D8 80083010 2000A3AF */  sw         $v1, 0x20($sp)
/* EFE5DC 80083014 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* EFE5E0 80083018 21082200 */  addu       $at, $at, $v0
/* EFE5E4 8008301C A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* EFE5E8 80083020 21300002 */  addu       $a2, $s0, $zero
/* EFE5EC 80083024 125C000C */  jal        func_80017048
/* EFE5F0 80083028 2800A2AF */   sw        $v0, 0x28($sp)
/* EFE5F4 8008302C CB89010C */  jal        rand
/* EFE5F8 80083030 00000000 */   nop
/* EFE5FC 80083034 2000A38F */  lw         $v1, 0x20($sp)
/* EFE600 80083038 7F004230 */  andi       $v0, $v0, 0x7F
/* EFE604 8008303C C1FF6324 */  addiu      $v1, $v1, -0x3F
/* EFE608 80083040 21186200 */  addu       $v1, $v1, $v0
/* EFE60C 80083044 CB89010C */  jal        rand
/* EFE610 80083048 2000A3AF */   sw        $v1, 0x20($sp)
/* EFE614 8008304C 2400A38F */  lw         $v1, 0x24($sp)
/* EFE618 80083050 7F004230 */  andi       $v0, $v0, 0x7F
/* EFE61C 80083054 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* EFE620 80083058 21186200 */  addu       $v1, $v1, $v0
/* EFE624 8008305C CB89010C */  jal        rand
/* EFE628 80083060 2400A3AF */   sw        $v1, 0x24($sp)
/* EFE62C 80083064 0C006426 */  addiu      $a0, $s3, 0xC
/* EFE630 80083068 0C00A526 */  addiu      $a1, $s5, 0xC
/* EFE634 8008306C 21300002 */  addu       $a2, $s0, $zero
/* EFE638 80083070 2800A38F */  lw         $v1, 0x28($sp)
/* EFE63C 80083074 7F004230 */  andi       $v0, $v0, 0x7F
/* EFE640 80083078 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* EFE644 8008307C 21186200 */  addu       $v1, $v1, $v0
/* EFE648 80083080 D65D000C */  jal        VecAdd
/* EFE64C 80083084 2800A3AF */   sw        $v1, 0x28($sp)
/* EFE650 80083088 21202002 */  addu       $a0, $s1, $zero
/* EFE654 8008308C C05D000C */  jal        VecCopy
/* EFE658 80083090 21280002 */   addu      $a1, $s0, $zero
/* EFE65C 80083094 21202002 */  addu       $a0, $s1, $zero
/* EFE660 80083098 B25D000C */  jal        VecShiftRight
/* EFE664 8008309C 02000524 */   addiu     $a1, $zero, 0x2
/* EFE668 800830A0 CB89010C */  jal        rand
/* EFE66C 800830A4 00000000 */   nop
/* EFE670 800830A8 0000238E */  lw         $v1, 0x0($s1)
/* EFE674 800830AC FF004230 */  andi       $v0, $v0, 0xFF
/* EFE678 800830B0 81FF6324 */  addiu      $v1, $v1, -0x7F
/* EFE67C 800830B4 21186200 */  addu       $v1, $v1, $v0
/* EFE680 800830B8 CB89010C */  jal        rand
/* EFE684 800830BC 000023AE */   sw        $v1, 0x0($s1)
/* EFE688 800830C0 0400238E */  lw         $v1, 0x4($s1)
/* EFE68C 800830C4 FF004230 */  andi       $v0, $v0, 0xFF
/* EFE690 800830C8 81FF6324 */  addiu      $v1, $v1, -0x7F
/* EFE694 800830CC 21186200 */  addu       $v1, $v1, $v0
/* EFE698 800830D0 CB89010C */  jal        rand
/* EFE69C 800830D4 040023AE */   sw        $v1, 0x4($s1)
/* EFE6A0 800830D8 0800238E */  lw         $v1, 0x8($s1)
/* EFE6A4 800830DC FF004230 */  andi       $v0, $v0, 0xFF
/* EFE6A8 800830E0 81FF6324 */  addiu      $v1, $v1, -0x7F
/* EFE6AC 800830E4 21186200 */  addu       $v1, $v1, $v0
/* EFE6B0 800830E8 CB89010C */  jal        rand
/* EFE6B4 800830EC 080023AE */   sw        $v1, 0x8($s1)
/* EFE6B8 800830F0 CB89010C */  jal        rand
/* EFE6BC 800830F4 440062A2 */   sb        $v0, 0x44($s3)
/* EFE6C0 800830F8 CB89010C */  jal        rand
/* EFE6C4 800830FC 450062A2 */   sb        $v0, 0x45($s3)
/* EFE6C8 80083100 CB89010C */  jal        rand
/* EFE6CC 80083104 460062A2 */   sb        $v0, 0x46($s3)
/* EFE6D0 80083108 0F004230 */  andi       $v0, $v0, 0xF
/* EFE6D4 8008310C CB89010C */  jal        rand
/* EFE6D8 80083110 100022A2 */   sb        $v0, 0x10($s1)
/* EFE6DC 80083114 0F004230 */  andi       $v0, $v0, 0xF
/* EFE6E0 80083118 CB89010C */  jal        rand
/* EFE6E4 8008311C 110022A2 */   sb        $v0, 0x11($s1)
/* EFE6E8 80083120 0F004230 */  andi       $v0, $v0, 0xF
/* EFE6EC 80083124 120022A2 */  sb         $v0, 0x12($s1)
/* EFE6F0 80083128 1400A28E */  lw         $v0, 0x14($s5)
/* EFE6F4 8008312C CB89010C */  jal        rand
/* EFE6F8 80083130 0C0022AE */   sw        $v0, 0xC($s1)
/* EFE6FC 80083134 03004230 */  andi       $v0, $v0, 0x3
/* EFE700 80083138 10004224 */  addiu      $v0, $v0, 0x10
/* EFE704 8008313C 920C0208 */  j          .Llevel_12_80083248
/* EFE708 80083140 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_12_80083144:
/* EFE70C 80083144 0000708E */  lw         $s0, 0x0($s3)
/* EFE710 80083148 C8E9000C */  jal        func_8003A720
/* EFE714 8008314C 21206002 */   addu      $a0, $s3, $zero
/* EFE718 80083150 734A010C */  jal        func_800529CC
/* EFE71C 80083154 21206002 */   addu      $a0, $s3, $zero
/* EFE720 80083158 02000224 */  addiu      $v0, $zero, 0x2
/* EFE724 8008315C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* EFE728 80083160 40000224 */  addiu      $v0, $zero, 0x40
/* EFE72C 80083164 4C0060A2 */  sb         $zero, 0x4C($s3)
/* EFE730 80083168 4D0060A2 */  sb         $zero, 0x4D($s3)
/* EFE734 8008316C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* EFE738 80083170 920C0208 */  j          .Llevel_12_80083248
/* EFE73C 80083174 000002AE */   sw        $v0, 0x0($s0)
.Llevel_12_80083178:
/* EFE740 80083178 C8E9000C */  jal        func_8003A720
/* EFE744 8008317C 21206002 */   addu      $a0, $s3, $zero
/* EFE748 80083180 0300A012 */  beqz       $s5, .Llevel_12_80083190
/* EFE74C 80083184 0C006426 */   addiu     $a0, $s3, 0xC
/* EFE750 80083188 660C0208 */  j          .Llevel_12_80083198
/* EFE754 8008318C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_12_80083190:
/* EFE758 80083190 0880053C */  lui        $a1, %hi(g_Spyro)
/* EFE75C 80083194 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_12_80083198:
/* EFE760 80083198 C05D000C */  jal        VecCopy
/* EFE764 8008319C 00000000 */   nop
/* EFE768 800831A0 0C006426 */  addiu      $a0, $s3, 0xC
/* EFE76C 800831A4 1400628E */  lw         $v0, 0x14($s3)
/* EFE770 800831A8 00080524 */  addiu      $a1, $zero, 0x800
/* EFE774 800831AC 00024224 */  addiu      $v0, $v0, 0x200
/* EFE778 800831B0 7B35010C */  jal        func_8004D5EC
/* EFE77C 800831B4 140062AE */   sw        $v0, 0x14($s3)
/* EFE780 800831B8 1400648E */  lw         $a0, 0x14($s3)
/* EFE784 800831BC 21184000 */  addu       $v1, $v0, $zero
/* EFE788 800831C0 23106400 */  subu       $v0, $v1, $a0
/* EFE78C 800831C4 02004104 */  bgez       $v0, .Llevel_12_800831D0
/* EFE790 800831C8 00000000 */   nop
/* EFE794 800831CC 23100200 */  negu       $v0, $v0
.Llevel_12_800831D0:
/* EFE798 800831D0 00084228 */  slti       $v0, $v0, 0x800
/* EFE79C 800831D4 03004010 */  beqz       $v0, .Llevel_12_800831E4
/* EFE7A0 800831D8 00FE8224 */   addiu     $v0, $a0, -0x200
/* EFE7A4 800831DC 900C0208 */  j          .Llevel_12_80083240
/* EFE7A8 800831E0 140063AE */   sw        $v1, 0x14($s3)
.Llevel_12_800831E4:
/* EFE7AC 800831E4 900C0208 */  j          .Llevel_12_80083240
/* EFE7B0 800831E8 140062AE */   sw        $v0, 0x14($s3)
.Llevel_12_800831EC:
/* EFE7B4 800831EC C8E9000C */  jal        func_8003A720
/* EFE7B8 800831F0 21206002 */   addu      $a0, $s3, $zero
/* EFE7BC 800831F4 21206002 */  addu       $a0, $s3, $zero
/* EFE7C0 800831F8 20000224 */  addiu      $v0, $zero, 0x20
/* EFE7C4 800831FC 500062A2 */  sb         $v0, 0x50($s3)
/* EFE7C8 80083200 FF000224 */  addiu      $v0, $zero, 0xFF
/* EFE7CC 80083204 734A010C */  jal        func_800529CC
/* EFE7D0 80083208 520062A2 */   sb        $v0, 0x52($s3)
/* EFE7D4 8008320C 930C0208 */  j          .Llevel_12_8008324C
/* EFE7D8 80083210 21106002 */   addu      $v0, $s3, $zero
.Llevel_12_80083214:
/* EFE7DC 80083214 C8E9000C */  jal        func_8003A720
/* EFE7E0 80083218 21206002 */   addu      $a0, $s3, $zero
/* EFE7E4 8008321C 0300A012 */  beqz       $s5, .Llevel_12_8008322C
/* EFE7E8 80083220 0C00A526 */   addiu     $a1, $s5, 0xC
/* EFE7EC 80083224 8E0C0208 */  j          .Llevel_12_80083238
/* EFE7F0 80083228 0C006426 */   addiu     $a0, $s3, 0xC
.Llevel_12_8008322C:
/* EFE7F4 8008322C 0C006426 */  addiu      $a0, $s3, 0xC
/* EFE7F8 80083230 0880053C */  lui        $a1, %hi(g_Spyro)
/* EFE7FC 80083234 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_12_80083238:
/* EFE800 80083238 C05D000C */  jal        VecCopy
/* EFE804 8008323C 00000000 */   nop
.Llevel_12_80083240:
/* EFE808 80083240 AA49010C */  jal        func_800526A8
/* EFE80C 80083244 21206002 */   addu      $a0, $s3, $zero
.Llevel_12_80083248:
/* EFE810 80083248 21106002 */  addu       $v0, $s3, $zero
.Llevel_12_8008324C:
/* EFE814 8008324C 5000BF8F */  lw         $ra, 0x50($sp)
/* EFE818 80083250 4C00B58F */  lw         $s5, 0x4C($sp)
/* EFE81C 80083254 4800B48F */  lw         $s4, 0x48($sp)
/* EFE820 80083258 4400B38F */  lw         $s3, 0x44($sp)
/* EFE824 8008325C 4000B28F */  lw         $s2, 0x40($sp)
/* EFE828 80083260 3C00B18F */  lw         $s1, 0x3C($sp)
/* EFE82C 80083264 3800B08F */  lw         $s0, 0x38($sp)
/* EFE830 80083268 5800BD27 */  addiu      $sp, $sp, 0x58
/* EFE834 8008326C 0800E003 */  jr         $ra
/* EFE838 80083270 00000000 */   nop
.size func_level_12_80082960, . - func_level_12_80082960
