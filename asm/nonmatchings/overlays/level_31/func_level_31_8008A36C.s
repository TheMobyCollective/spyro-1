.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_31_8008A36C
/* 2A09134 8008A36C A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 2A09138 8008A370 3800B0AF */  sw         $s0, 0x38($sp)
/* 2A0913C 8008A374 21808000 */  addu       $s0, $a0, $zero
/* 2A09140 8008A378 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 2A09144 8008A37C 21A8A000 */  addu       $s5, $a1, $zero
/* 2A09148 8008A380 5000BFAF */  sw         $ra, 0x50($sp)
/* 2A0914C 8008A384 4800B4AF */  sw         $s4, 0x48($sp)
/* 2A09150 8008A388 4400B3AF */  sw         $s3, 0x44($sp)
/* 2A09154 8008A38C 4000B2AF */  sw         $s2, 0x40($sp)
/* 2A09158 8008A390 3149010C */  jal        func_800524C4
/* 2A0915C 8008A394 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 2A09160 8008A398 21984000 */  addu       $s3, $v0, $zero
/* 2A09164 8008A39C 1400A012 */  beqz       $s5, .Llevel_31_8008A3F0
/* 2A09168 8008A3A0 360070A6 */   sh        $s0, 0x36($s3)
/* 2A0916C 8008A3A4 0780043C */  lui        $a0, %hi(D_80075828)
/* 2A09170 8008A3A8 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 2A09174 8008A3AC 00000000 */  nop
/* 2A09178 8008A3B0 2320A402 */  subu       $a0, $s5, $a0
/* 2A0917C 8008A3B4 40190400 */  sll        $v1, $a0, 5
/* 2A09180 8008A3B8 23186400 */  subu       $v1, $v1, $a0
/* 2A09184 8008A3BC 40190300 */  sll        $v1, $v1, 5
/* 2A09188 8008A3C0 21186400 */  addu       $v1, $v1, $a0
/* 2A0918C 8008A3C4 C0100300 */  sll        $v0, $v1, 3
/* 2A09190 8008A3C8 21186200 */  addu       $v1, $v1, $v0
/* 2A09194 8008A3CC C0130300 */  sll        $v0, $v1, 15
/* 2A09198 8008A3D0 23104300 */  subu       $v0, $v0, $v1
/* 2A0919C 8008A3D4 80100200 */  sll        $v0, $v0, 2
/* 2A091A0 8008A3D8 21104400 */  addu       $v0, $v0, $a0
/* 2A091A4 8008A3DC 23100200 */  negu       $v0, $v0
/* 2A091A8 8008A3E0 C3180200 */  sra        $v1, $v0, 3
/* 2A091AC 8008A3E4 0001622C */  sltiu      $v0, $v1, 0x100
/* 2A091B0 8008A3E8 03004014 */  bnez       $v0, .Llevel_31_8008A3F8
/* 2A091B4 8008A3EC 0201022A */   slti      $v0, $s0, 0x102
.Llevel_31_8008A3F0:
/* 2A091B8 8008A3F0 21180000 */  addu       $v1, $zero, $zero
/* 2A091BC 8008A3F4 0201022A */  slti       $v0, $s0, 0x102
.Llevel_31_8008A3F8:
/* 2A091C0 8008A3F8 31004010 */  beqz       $v0, .Llevel_31_8008A4C0
/* 2A091C4 8008A3FC 560063A2 */   sb        $v1, 0x56($s3)
/* 2A091C8 8008A400 FF00022A */  slti       $v0, $s0, 0xFF
/* 2A091CC 8008A404 20014010 */  beqz       $v0, .Llevel_31_8008A888
/* 2A091D0 8008A408 4C000224 */   addiu     $v0, $zero, 0x4C
/* 2A091D4 8008A40C AE020212 */  beq        $s0, $v0, .Llevel_31_8008AEC8
/* 2A091D8 8008A410 4D00022A */   slti      $v0, $s0, 0x4D
/* 2A091DC 8008A414 16004010 */  beqz       $v0, .Llevel_31_8008A470
/* 2A091E0 8008A418 10000224 */   addiu     $v0, $zero, 0x10
/* 2A091E4 8008A41C 82000212 */  beq        $s0, $v0, .Llevel_31_8008A628
/* 2A091E8 8008A420 1100022A */   slti      $v0, $s0, 0x11
/* 2A091EC 8008A424 07004010 */  beqz       $v0, .Llevel_31_8008A444
/* 2A091F0 8008A428 0E000224 */   addiu     $v0, $zero, 0xE
/* 2A091F4 8008A42C A0000212 */  beq        $s0, $v0, .Llevel_31_8008A6B0
/* 2A091F8 8008A430 0F000224 */   addiu     $v0, $zero, 0xF
/* 2A091FC 8008A434 55000212 */  beq        $s0, $v0, .Llevel_31_8008A58C
/* 2A09200 8008A438 00000000 */   nop
/* 2A09204 8008A43C BC2B0208 */  j          .Llevel_31_8008AEF0
/* 2A09208 8008A440 00000000 */   nop
.Llevel_31_8008A444:
/* 2A0920C 8008A444 22000224 */  addiu      $v0, $zero, 0x22
/* 2A09210 8008A448 8B000212 */  beq        $s0, $v0, .Llevel_31_8008A678
/* 2A09214 8008A44C 2200022A */   slti      $v0, $s0, 0x22
/* 2A09218 8008A450 A7024014 */  bnez       $v0, .Llevel_31_8008AEF0
/* 2A0921C 8008A454 4600022A */   slti      $v0, $s0, 0x46
/* 2A09220 8008A458 A5024010 */  beqz       $v0, .Llevel_31_8008AEF0
/* 2A09224 8008A45C 4300022A */   slti      $v0, $s0, 0x43
/* 2A09228 8008A460 09014010 */  beqz       $v0, .Llevel_31_8008A888
/* 2A0922C 8008A464 00000000 */   nop
/* 2A09230 8008A468 BC2B0208 */  j          .Llevel_31_8008AEF0
/* 2A09234 8008A46C 00000000 */   nop
.Llevel_31_8008A470:
/* 2A09238 8008A470 97000224 */  addiu      $v0, $zero, 0x97
/* 2A0923C 8008A474 04010212 */  beq        $s0, $v0, .Llevel_31_8008A888
/* 2A09240 8008A478 9800022A */   slti      $v0, $s0, 0x98
/* 2A09244 8008A47C 09004010 */  beqz       $v0, .Llevel_31_8008A4A4
/* 2A09248 8008A480 5300022A */   slti      $v0, $s0, 0x53
/* 2A0924C 8008A484 9A024014 */  bnez       $v0, .Llevel_31_8008AEF0
/* 2A09250 8008A488 5800022A */   slti      $v0, $s0, 0x58
/* 2A09254 8008A48C 88004014 */  bnez       $v0, .Llevel_31_8008A6B0
/* 2A09258 8008A490 78000224 */   addiu     $v0, $zero, 0x78
/* 2A0925C 8008A494 DC000212 */  beq        $s0, $v0, .Llevel_31_8008A808
/* 2A09260 8008A498 00000000 */   nop
/* 2A09264 8008A49C BC2B0208 */  j          .Llevel_31_8008AEF0
/* 2A09268 8008A4A0 00000000 */   nop
.Llevel_31_8008A4A4:
/* 2A0926C 8008A4A4 9A00022A */  slti       $v0, $s0, 0x9A
/* 2A09270 8008A4A8 E9004014 */  bnez       $v0, .Llevel_31_8008A850
/* 2A09274 8008A4AC FB000224 */   addiu     $v0, $zero, 0xFB
/* 2A09278 8008A4B0 60010212 */  beq        $s0, $v0, .Llevel_31_8008AA34
/* 2A0927C 8008A4B4 00000000 */   nop
/* 2A09280 8008A4B8 BC2B0208 */  j          .Llevel_31_8008AEF0
/* 2A09284 8008A4BC 00000000 */   nop
.Llevel_31_8008A4C0:
/* 2A09288 8008A4C0 47010224 */  addiu      $v0, $zero, 0x147
/* 2A0928C 8008A4C4 CB010212 */  beq        $s0, $v0, .Llevel_31_8008ABF4
/* 2A09290 8008A4C8 4801022A */   slti      $v0, $s0, 0x148
/* 2A09294 8008A4CC 16004010 */  beqz       $v0, .Llevel_31_8008A528
/* 2A09298 8008A4D0 27010224 */   addiu     $v0, $zero, 0x127
/* 2A0929C 8008A4D4 D4010212 */  beq        $s0, $v0, .Llevel_31_8008AC28
/* 2A092A0 8008A4D8 2801022A */   slti      $v0, $s0, 0x128
/* 2A092A4 8008A4DC 09004010 */  beqz       $v0, .Llevel_31_8008A504
/* 2A092A8 8008A4E0 0401022A */   slti      $v0, $s0, 0x104
/* 2A092AC 8008A4E4 82024014 */  bnez       $v0, .Llevel_31_8008AEF0
/* 2A092B0 8008A4E8 0E01022A */   slti      $v0, $s0, 0x10E
/* 2A092B4 8008A4EC C1014014 */  bnez       $v0, .Llevel_31_8008ABF4
/* 2A092B8 8008A4F0 15010224 */   addiu     $v0, $zero, 0x115
/* 2A092BC 8008A4F4 BF010212 */  beq        $s0, $v0, .Llevel_31_8008ABF4
/* 2A092C0 8008A4F8 00000000 */   nop
/* 2A092C4 8008A4FC BC2B0208 */  j          .Llevel_31_8008AEF0
/* 2A092C8 8008A500 00000000 */   nop
.Llevel_31_8008A504:
/* 2A092CC 8008A504 3501022A */  slti       $v0, $s0, 0x135
/* 2A092D0 8008A508 79024014 */  bnez       $v0, .Llevel_31_8008AEF0
/* 2A092D4 8008A50C 3801022A */   slti      $v0, $s0, 0x138
/* 2A092D8 8008A510 DD004014 */  bnez       $v0, .Llevel_31_8008A888
/* 2A092DC 8008A514 3E010224 */   addiu     $v0, $zero, 0x13E
/* 2A092E0 8008A518 1A020212 */  beq        $s0, $v0, .Llevel_31_8008AD84
/* 2A092E4 8008A51C 00000000 */   nop
/* 2A092E8 8008A520 BC2B0208 */  j          .Llevel_31_8008AEF0
/* 2A092EC 8008A524 00000000 */   nop
.Llevel_31_8008A528:
/* 2A092F0 8008A528 AA01022A */  slti       $v0, $s0, 0x1AA
/* 2A092F4 8008A52C 10004010 */  beqz       $v0, .Llevel_31_8008A570
/* 2A092F8 8008A530 A701022A */   slti      $v0, $s0, 0x1A7
/* 2A092FC 8008A534 D4004010 */  beqz       $v0, .Llevel_31_8008A888
/* 2A09300 8008A538 8E010224 */   addiu     $v0, $zero, 0x18E
/* 2A09304 8008A53C 32020212 */  beq        $s0, $v0, .Llevel_31_8008AE08
/* 2A09308 8008A540 8F01022A */   slti      $v0, $s0, 0x18F
/* 2A0930C 8008A544 05004010 */  beqz       $v0, .Llevel_31_8008A55C
/* 2A09310 8008A548 88010224 */   addiu     $v0, $zero, 0x188
/* 2A09314 8008A54C 26020212 */  beq        $s0, $v0, .Llevel_31_8008ADE8
/* 2A09318 8008A550 00000000 */   nop
/* 2A0931C 8008A554 BC2B0208 */  j          .Llevel_31_8008AEF0
/* 2A09320 8008A558 00000000 */   nop
.Llevel_31_8008A55C:
/* 2A09324 8008A55C 95010224 */  addiu      $v0, $zero, 0x195
/* 2A09328 8008A560 3C020212 */  beq        $s0, $v0, .Llevel_31_8008AE54
/* 2A0932C 8008A564 00000000 */   nop
/* 2A09330 8008A568 BC2B0208 */  j          .Llevel_31_8008AEF0
/* 2A09334 8008A56C 00000000 */   nop
.Llevel_31_8008A570:
/* 2A09338 8008A570 C401022A */  slti       $v0, $s0, 0x1C4
/* 2A0933C 8008A574 54024014 */  bnez       $v0, .Llevel_31_8008AEC8
/* 2A09340 8008A578 DD010224 */   addiu     $v0, $zero, 0x1DD
/* 2A09344 8008A57C 35020212 */  beq        $s0, $v0, .Llevel_31_8008AE54
/* 2A09348 8008A580 00000000 */   nop
/* 2A0934C 8008A584 BC2B0208 */  j          .Llevel_31_8008AEF0
/* 2A09350 8008A588 00000000 */   nop
.Llevel_31_8008A58C:
/* 2A09354 8008A58C 0000708E */  lw         $s0, 0x0($s3)
/* 2A09358 8008A590 C8E9000C */  jal        func_8003A720
/* 2A0935C 8008A594 21206002 */   addu      $a0, $s3, $zero
/* 2A09360 8008A598 8C000224 */  addiu      $v0, $zero, 0x8C
/* 2A09364 8008A59C 080002AE */  sw         $v0, 0x8($s0)
/* 2A09368 8008A5A0 03000224 */  addiu      $v0, $zero, 0x3
/* 2A0936C 8008A5A4 100002A2 */  sb         $v0, 0x10($s0)
/* 2A09370 8008A5A8 FF000224 */  addiu      $v0, $zero, 0xFF
/* 2A09374 8008A5AC 140002A2 */  sb         $v0, 0x14($s0)
/* 2A09378 8008A5B0 02000224 */  addiu      $v0, $zero, 0x2
/* 2A0937C 8008A5B4 000000AE */  sw         $zero, 0x0($s0)
/* 2A09380 8008A5B8 040000AE */  sw         $zero, 0x4($s0)
/* 2A09384 8008A5BC 0E0000A2 */  sb         $zero, 0xE($s0)
/* 2A09388 8008A5C0 0F0000A2 */  sb         $zero, 0xF($s0)
/* 2A0938C 8008A5C4 110000A2 */  sb         $zero, 0x11($s0)
/* 2A09390 8008A5C8 120000A2 */  sb         $zero, 0x12($s0)
/* 2A09394 8008A5CC 130000A2 */  sb         $zero, 0x13($s0)
/* 2A09398 8008A5D0 490062A2 */  sb         $v0, 0x49($s3)
/* 2A0939C 8008A5D4 18000224 */  addiu      $v0, $zero, 0x18
/* 2A093A0 8008A5D8 500062A2 */  sb         $v0, 0x50($s3)
/* 2A093A4 8008A5DC 10000224 */  addiu      $v0, $zero, 0x10
/* 2A093A8 8008A5E0 520062A2 */  sb         $v0, 0x52($s3)
/* 2A093AC 8008A5E4 20000224 */  addiu      $v0, $zero, 0x20
/* 2A093B0 8008A5E8 440062A2 */  sb         $v0, 0x44($s3)
/* 2A093B4 8008A5EC 450060A2 */  sb         $zero, 0x45($s3)
/* 2A093B8 8008A5F0 0400A012 */  beqz       $s5, .Llevel_31_8008A604
/* 2A093BC 8008A5F4 460060A2 */   sb        $zero, 0x46($s3)
/* 2A093C0 8008A5F8 0C006426 */  addiu      $a0, $s3, 0xC
/* 2A093C4 8008A5FC C05D000C */  jal        VecCopy
/* 2A093C8 8008A600 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_31_8008A604:
/* 2A093CC 8008A604 AA49010C */  jal        func_800526A8
/* 2A093D0 8008A608 21206002 */   addu      $a0, $s3, $zero
/* 2A093D4 8008A60C 4B006292 */  lbu        $v0, 0x4B($s3)
/* 2A093D8 8008A610 01000324 */  addiu      $v1, $zero, 0x1
/* 2A093DC 8008A614 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2A093E0 8008A618 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2A093E4 8008A61C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 2A093E8 8008A620 8A2A0208 */  j          .Llevel_31_8008AA28
/* 2A093EC 8008A624 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_31_8008A628:
/* 2A093F0 8008A628 0000718E */  lw         $s1, 0x0($s3)
/* 2A093F4 8008A62C C8E9000C */  jal        func_8003A720
/* 2A093F8 8008A630 21206002 */   addu      $a0, $s3, $zero
/* 2A093FC 8008A634 AA49010C */  jal        func_800526A8
/* 2A09400 8008A638 21206002 */   addu      $a0, $s3, $zero
/* 2A09404 8008A63C 0C007026 */  addiu      $s0, $s3, 0xC
/* 2A09408 8008A640 21200002 */  addu       $a0, $s0, $zero
/* 2A0940C 8008A644 C05D000C */  jal        VecCopy
/* 2A09410 8008A648 0C00A526 */   addiu     $a1, $s5, 0xC
/* 2A09414 8008A64C 21280002 */  addu       $a1, $s0, $zero
/* 2A09418 8008A650 1400628E */  lw         $v0, 0x14($s3)
/* 2A0941C 8008A654 04002426 */  addiu      $a0, $s1, 0x4
/* 2A09420 8008A658 00024224 */  addiu      $v0, $v0, 0x200
/* 2A09424 8008A65C C05D000C */  jal        VecCopy
/* 2A09428 8008A660 140062AE */   sw        $v0, 0x14($s3)
/* 2A0942C 8008A664 08070224 */  addiu      $v0, $zero, 0x708
/* 2A09430 8008A668 130020A2 */  sb         $zero, 0x13($s1)
/* 2A09434 8008A66C 120020A2 */  sb         $zero, 0x12($s1)
/* 2A09438 8008A670 CA2B0208 */  j          .Llevel_31_8008AF28
/* 2A0943C 8008A674 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_31_8008A678:
/* 2A09440 8008A678 C8E9000C */  jal        func_8003A720
/* 2A09444 8008A67C 21206002 */   addu      $a0, $s3, $zero
/* 2A09448 8008A680 20000224 */  addiu      $v0, $zero, 0x20
/* 2A0944C 8008A684 500062A2 */  sb         $v0, 0x50($s3)
/* 2A09450 8008A688 FF000224 */  addiu      $v0, $zero, 0xFF
/* 2A09454 8008A68C 0400A012 */  beqz       $s5, .Llevel_31_8008A6A0
/* 2A09458 8008A690 520062A2 */   sb        $v0, 0x52($s3)
/* 2A0945C 8008A694 0C006426 */  addiu      $a0, $s3, 0xC
/* 2A09460 8008A698 C05D000C */  jal        VecCopy
/* 2A09464 8008A69C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_31_8008A6A0:
/* 2A09468 8008A6A0 734A010C */  jal        func_800529CC
/* 2A0946C 8008A6A4 21206002 */   addu      $a0, $s3, $zero
/* 2A09470 8008A6A8 CB2B0208 */  j          .Llevel_31_8008AF2C
/* 2A09474 8008A6AC 21106002 */   addu      $v0, $s3, $zero
.Llevel_31_8008A6B0:
/* 2A09478 8008A6B0 0000718E */  lw         $s1, 0x0($s3)
/* 2A0947C 8008A6B4 C8E9000C */  jal        func_8003A720
/* 2A09480 8008A6B8 21206002 */   addu      $a0, $s3, $zero
/* 2A09484 8008A6BC 8C000224 */  addiu      $v0, $zero, 0x8C
/* 2A09488 8008A6C0 000020AE */  sw         $zero, 0x0($s1)
/* 2A0948C 8008A6C4 040020AE */  sw         $zero, 0x4($s1)
/* 2A09490 8008A6C8 080022AE */  sw         $v0, 0x8($s1)
/* 2A09494 8008A6CC 0E0020A2 */  sb         $zero, 0xE($s1)
/* 2A09498 8008A6D0 0F0020A2 */  sb         $zero, 0xF($s1)
/* 2A0949C 8008A6D4 110020A2 */  sb         $zero, 0x11($s1)
/* 2A094A0 8008A6D8 120020A2 */  sb         $zero, 0x12($s1)
/* 2A094A4 8008A6DC 130020A2 */  sb         $zero, 0x13($s1)
/* 2A094A8 8008A6E0 3600A386 */  lh         $v1, 0x36($s5)
/* 2A094AC 8008A6E4 0D000224 */  addiu      $v0, $zero, 0xD
/* 2A094B0 8008A6E8 02006214 */  bne        $v1, $v0, .Llevel_31_8008A6F4
/* 2A094B4 8008A6EC 03000224 */   addiu     $v0, $zero, 0x3
/* 2A094B8 8008A6F0 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_31_8008A6F4:
/* 2A094BC 8008A6F4 100022A2 */  sb         $v0, 0x10($s1)
/* 2A094C0 8008A6F8 0C007026 */  addiu      $s0, $s3, 0xC
/* 2A094C4 8008A6FC 21200002 */  addu       $a0, $s0, $zero
/* 2A094C8 8008A700 0C00A526 */  addiu      $a1, $s5, 0xC
/* 2A094CC 8008A704 FF000224 */  addiu      $v0, $zero, 0xFF
/* 2A094D0 8008A708 140022A2 */  sb         $v0, 0x14($s1)
/* 2A094D4 8008A70C 02001124 */  addiu      $s1, $zero, 0x2
/* 2A094D8 8008A710 18000224 */  addiu      $v0, $zero, 0x18
/* 2A094DC 8008A714 500062A2 */  sb         $v0, 0x50($s3)
/* 2A094E0 8008A718 40000224 */  addiu      $v0, $zero, 0x40
/* 2A094E4 8008A71C 520062A2 */  sb         $v0, 0x52($s3)
/* 2A094E8 8008A720 20000224 */  addiu      $v0, $zero, 0x20
/* 2A094EC 8008A724 490071A2 */  sb         $s1, 0x49($s3)
/* 2A094F0 8008A728 440062A2 */  sb         $v0, 0x44($s3)
/* 2A094F4 8008A72C 450060A2 */  sb         $zero, 0x45($s3)
/* 2A094F8 8008A730 C05D000C */  jal        VecCopy
/* 2A094FC 8008A734 460060A2 */   sb        $zero, 0x46($s3)
/* 2A09500 8008A738 734A010C */  jal        func_800529CC
/* 2A09504 8008A73C 21206002 */   addu      $a0, $s3, $zero
/* 2A09508 8008A740 1000A427 */  addiu      $a0, $sp, 0x10
/* 2A0950C 8008A744 21280002 */  addu       $a1, $s0, $zero
/* 2A09510 8008A748 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 2A09514 8008A74C C05D000C */  jal        VecCopy
/* 2A09518 8008A750 1C0062AE */   sw        $v0, 0x1C($s3)
/* 2A0951C 8008A754 1000A427 */  addiu      $a0, $sp, 0x10
/* 2A09520 8008A758 1800A28F */  lw         $v0, 0x18($sp)
/* 2A09524 8008A75C 0100053C */  lui        $a1, (0x10000 >> 16)
/* 2A09528 8008A760 00044224 */  addiu      $v0, $v0, 0x400
/* 2A0952C 8008A764 7B35010C */  jal        func_8004D5EC
/* 2A09530 8008A768 1800A2AF */   sw        $v0, 0x18($sp)
/* 2A09534 8008A76C F44C010C */  jal        func_800533D0
/* 2A09538 8008A770 21206002 */   addu      $a0, $s3, $zero
/* 2A0953C 8008A774 36006386 */  lh         $v1, 0x36($s3)
/* 2A09540 8008A778 0E000224 */  addiu      $v0, $zero, 0xE
/* 2A09544 8008A77C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2A09548 8008A780 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2A0954C 8008A784 03006214 */  bne        $v1, $v0, .Llevel_31_8008A794
/* 2A09550 8008A788 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 2A09554 8008A78C 0C000224 */  addiu      $v0, $zero, 0xC
/* 2A09558 8008A790 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_31_8008A794:
/* 2A0955C 8008A794 36006386 */  lh         $v1, 0x36($s3)
/* 2A09560 8008A798 53000224 */  addiu      $v0, $zero, 0x53
/* 2A09564 8008A79C 05006214 */  bne        $v1, $v0, .Llevel_31_8008A7B4
/* 2A09568 8008A7A0 54000224 */   addiu     $v0, $zero, 0x54
/* 2A0956C 8008A7A4 01000224 */  addiu      $v0, $zero, 0x1
/* 2A09570 8008A7A8 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 2A09574 8008A7AC 36006386 */  lh         $v1, 0x36($s3)
/* 2A09578 8008A7B0 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_31_8008A7B4:
/* 2A0957C 8008A7B4 02006214 */  bne        $v1, $v0, .Llevel_31_8008A7C0
/* 2A09580 8008A7B8 00000000 */   nop
/* 2A09584 8008A7BC 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_31_8008A7C0:
/* 2A09588 8008A7C0 36006386 */  lh         $v1, 0x36($s3)
/* 2A0958C 8008A7C4 55000224 */  addiu      $v0, $zero, 0x55
/* 2A09590 8008A7C8 05006214 */  bne        $v1, $v0, .Llevel_31_8008A7E0
/* 2A09594 8008A7CC 56000224 */   addiu     $v0, $zero, 0x56
/* 2A09598 8008A7D0 03000224 */  addiu      $v0, $zero, 0x3
/* 2A0959C 8008A7D4 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 2A095A0 8008A7D8 36006386 */  lh         $v1, 0x36($s3)
/* 2A095A4 8008A7DC 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_31_8008A7E0:
/* 2A095A8 8008A7E0 02006214 */  bne        $v1, $v0, .Llevel_31_8008A7EC
/* 2A095AC 8008A7E4 04000224 */   addiu     $v0, $zero, 0x4
/* 2A095B0 8008A7E8 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_31_8008A7EC:
/* 2A095B4 8008A7EC 36006386 */  lh         $v1, 0x36($s3)
/* 2A095B8 8008A7F0 57000224 */  addiu      $v0, $zero, 0x57
/* 2A095BC 8008A7F4 CD016214 */  bne        $v1, $v0, .Llevel_31_8008AF2C
/* 2A095C0 8008A7F8 21106002 */   addu      $v0, $s3, $zero
/* 2A095C4 8008A7FC 05000224 */  addiu      $v0, $zero, 0x5
/* 2A095C8 8008A800 CA2B0208 */  j          .Llevel_31_8008AF28
/* 2A095CC 8008A804 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_31_8008A808:
/* 2A095D0 8008A808 0000708E */  lw         $s0, 0x0($s3)
/* 2A095D4 8008A80C C8E9000C */  jal        func_8003A720
/* 2A095D8 8008A810 21206002 */   addu      $a0, $s3, $zero
/* 2A095DC 8008A814 AA49010C */  jal        func_800526A8
/* 2A095E0 8008A818 21206002 */   addu      $a0, $s3, $zero
/* 2A095E4 8008A81C 490060A2 */  sb         $zero, 0x49($s3)
/* 2A095E8 8008A820 000000AE */  sw         $zero, 0x0($s0)
/* 2A095EC 8008A824 080000A6 */  sh         $zero, 0x8($s0)
/* 2A095F0 8008A828 060000A6 */  sh         $zero, 0x6($s0)
/* 2A095F4 8008A82C 040000A6 */  sh         $zero, 0x4($s0)
/* 2A095F8 8008A830 0C0000AE */  sw         $zero, 0xC($s0)
/* 2A095FC 8008A834 BC01A012 */  beqz       $s5, .Llevel_31_8008AF28
/* 2A09600 8008A838 100000AE */   sw        $zero, 0x10($s0)
/* 2A09604 8008A83C 0C006426 */  addiu      $a0, $s3, 0xC
/* 2A09608 8008A840 C05D000C */  jal        VecCopy
/* 2A0960C 8008A844 0C00A526 */   addiu     $a1, $s5, 0xC
/* 2A09610 8008A848 CB2B0208 */  j          .Llevel_31_8008AF2C
/* 2A09614 8008A84C 21106002 */   addu      $v0, $s3, $zero
.Llevel_31_8008A850:
/* 2A09618 8008A850 C8E9000C */  jal        func_8003A720
/* 2A0961C 8008A854 21206002 */   addu      $a0, $s3, $zero
/* 2A09620 8008A858 21206002 */  addu       $a0, $s3, $zero
/* 2A09624 8008A85C 20000224 */  addiu      $v0, $zero, 0x20
/* 2A09628 8008A860 500062A2 */  sb         $v0, 0x50($s3)
/* 2A0962C 8008A864 FF000224 */  addiu      $v0, $zero, 0xFF
/* 2A09630 8008A868 734A010C */  jal        func_800529CC
/* 2A09634 8008A86C 520062A2 */   sb        $v0, 0x52($s3)
/* 2A09638 8008A870 0D000224 */  addiu      $v0, $zero, 0xD
/* 2A0963C 8008A874 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2A09640 8008A878 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2A09644 8008A87C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 2A09648 8008A880 CA2B0208 */  j          .Llevel_31_8008AF28
/* 2A0964C 8008A884 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_31_8008A888:
/* 2A09650 8008A888 0000748E */  lw         $s4, 0x0($s3)
/* 2A09654 8008A88C C8E9000C */  jal        func_8003A720
/* 2A09658 8008A890 21206002 */   addu      $a0, $s3, $zero
/* 2A0965C 8008A894 0C006426 */  addiu      $a0, $s3, 0xC
/* 2A09660 8008A898 0C00A526 */  addiu      $a1, $s5, 0xC
/* 2A09664 8008A89C 20000224 */  addiu      $v0, $zero, 0x20
/* 2A09668 8008A8A0 C05D000C */  jal        VecCopy
/* 2A0966C 8008A8A4 500062A2 */   sb        $v0, 0x50($s3)
/* 2A09670 8008A8A8 AA49010C */  jal        func_800526A8
/* 2A09674 8008A8AC 21206002 */   addu      $a0, $s3, $zero
/* 2A09678 8008A8B0 CB89010C */  jal        rand
/* 2A0967C 8008A8B4 00000000 */   nop
/* 2A09680 8008A8B8 CB89010C */  jal        rand
/* 2A09684 8008A8BC FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 2A09688 8008A8C0 FF075130 */  andi       $s1, $v0, 0x7FF
/* 2A0968C 8008A8C4 2C5B000C */  jal        Cos
/* 2A09690 8008A8C8 21202002 */   addu      $a0, $s1, $zero
/* 2A09694 8008A8CC 21204002 */  addu       $a0, $s2, $zero
/* 2A09698 8008A8D0 2C5B000C */  jal        Cos
/* 2A0969C 8008A8D4 21804000 */   addu      $s0, $v0, $zero
/* 2A096A0 8008A8D8 43811000 */  sra        $s0, $s0, 5
/* 2A096A4 8008A8DC 18000202 */  mult       $s0, $v0
/* 2A096A8 8008A8E0 21202002 */  addu       $a0, $s1, $zero
/* 2A096AC 8008A8E4 12380000 */  mflo       $a3
/* 2A096B0 8008A8E8 03130700 */  sra        $v0, $a3, 12
/* 2A096B4 8008A8EC 2C5B000C */  jal        Cos
/* 2A096B8 8008A8F0 000082A6 */   sh        $v0, 0x0($s4)
/* 2A096BC 8008A8F4 21204002 */  addu       $a0, $s2, $zero
/* 2A096C0 8008A8F8 165B000C */  jal        Sin
/* 2A096C4 8008A8FC 21804000 */   addu      $s0, $v0, $zero
/* 2A096C8 8008A900 43811000 */  sra        $s0, $s0, 5
/* 2A096CC 8008A904 18000202 */  mult       $s0, $v0
/* 2A096D0 8008A908 21202002 */  addu       $a0, $s1, $zero
/* 2A096D4 8008A90C 12380000 */  mflo       $a3
/* 2A096D8 8008A910 03130700 */  sra        $v0, $a3, 12
/* 2A096DC 8008A914 165B000C */  jal        Sin
/* 2A096E0 8008A918 020082A6 */   sh        $v0, 0x2($s4)
/* 2A096E4 8008A91C 43110200 */  sra        $v0, $v0, 5
/* 2A096E8 8008A920 040082A6 */  sh         $v0, 0x4($s4)
/* 2A096EC 8008A924 1800A28E */  lw         $v0, 0x18($s5)
/* 2A096F0 8008A928 0200033C */  lui        $v1, (0x20000 >> 16)
/* 2A096F4 8008A92C 24104300 */  and        $v0, $v0, $v1
/* 2A096F8 8008A930 13004010 */  beqz       $v0, .Llevel_31_8008A980
/* 2A096FC 8008A934 00000000 */   nop
/* 2A09700 8008A938 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 2A09704 8008A93C 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 2A09708 8008A940 00008396 */  lhu        $v1, 0x0($s4)
/* 2A0970C 8008A944 83110200 */  sra        $v0, $v0, 6
/* 2A09710 8008A948 21186200 */  addu       $v1, $v1, $v0
/* 2A09714 8008A94C 000083A6 */  sh         $v1, 0x0($s4)
/* 2A09718 8008A950 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 2A0971C 8008A954 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 2A09720 8008A958 02008396 */  lhu        $v1, 0x2($s4)
/* 2A09724 8008A95C 83110200 */  sra        $v0, $v0, 6
/* 2A09728 8008A960 21186200 */  addu       $v1, $v1, $v0
/* 2A0972C 8008A964 020083A6 */  sh         $v1, 0x2($s4)
/* 2A09730 8008A968 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 2A09734 8008A96C 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 2A09738 8008A970 04008396 */  lhu        $v1, 0x4($s4)
/* 2A0973C 8008A974 83110200 */  sra        $v0, $v0, 6
/* 2A09740 8008A978 21186200 */  addu       $v1, $v1, $v0
/* 2A09744 8008A97C 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_31_8008A980:
/* 2A09748 8008A980 00008286 */  lh         $v0, 0x0($s4)
/* 2A0974C 8008A984 0C00638E */  lw         $v1, 0xC($s3)
/* 2A09750 8008A988 80100200 */  sll        $v0, $v0, 2
/* 2A09754 8008A98C 21186200 */  addu       $v1, $v1, $v0
/* 2A09758 8008A990 0C0063AE */  sw         $v1, 0xC($s3)
/* 2A0975C 8008A994 02008286 */  lh         $v0, 0x2($s4)
/* 2A09760 8008A998 1000638E */  lw         $v1, 0x10($s3)
/* 2A09764 8008A99C 80100200 */  sll        $v0, $v0, 2
/* 2A09768 8008A9A0 21186200 */  addu       $v1, $v1, $v0
/* 2A0976C 8008A9A4 100063AE */  sw         $v1, 0x10($s3)
/* 2A09770 8008A9A8 04008286 */  lh         $v0, 0x4($s4)
/* 2A09774 8008A9AC 1400638E */  lw         $v1, 0x14($s3)
/* 2A09778 8008A9B0 80100200 */  sll        $v0, $v0, 2
/* 2A0977C 8008A9B4 21186200 */  addu       $v1, $v1, $v0
/* 2A09780 8008A9B8 CB89010C */  jal        rand
/* 2A09784 8008A9BC 140063AE */   sw        $v1, 0x14($s3)
/* 2A09788 8008A9C0 0F004230 */  andi       $v0, $v0, 0xF
/* 2A0978C 8008A9C4 CB89010C */  jal        rand
/* 2A09790 8008A9C8 060082A6 */   sh        $v0, 0x6($s4)
/* 2A09794 8008A9CC 0F004230 */  andi       $v0, $v0, 0xF
/* 2A09798 8008A9D0 CB89010C */  jal        rand
/* 2A0979C 8008A9D4 080082A6 */   sh        $v0, 0x8($s4)
/* 2A097A0 8008A9D8 0F004230 */  andi       $v0, $v0, 0xF
/* 2A097A4 8008A9DC 0A0082A6 */  sh         $v0, 0xA($s4)
/* 2A097A8 8008A9E0 1400A28E */  lw         $v0, 0x14($s5)
/* 2A097AC 8008A9E4 00000000 */  nop
/* 2A097B0 8008A9E8 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 2A097B4 8008A9EC CB89010C */  jal        rand
/* 2A097B8 8008A9F0 100082AE */   sw        $v0, 0x10($s4)
/* 2A097BC 8008A9F4 0F004230 */  andi       $v0, $v0, 0xF
/* 2A097C0 8008A9F8 40000324 */  addiu      $v1, $zero, 0x40
/* 2A097C4 8008A9FC 23186200 */  subu       $v1, $v1, $v0
/* 2A097C8 8008AA00 0C0083AE */  sw         $v1, 0xC($s4)
/* 2A097CC 8008AA04 36006296 */  lhu        $v0, 0x36($s3)
/* 2A097D0 8008AA08 00000000 */  nop
/* 2A097D4 8008AA0C CBFE4224 */  addiu      $v0, $v0, -0x135
/* 2A097D8 8008AA10 0300422C */  sltiu      $v0, $v0, 0x3
/* 2A097DC 8008AA14 44014010 */  beqz       $v0, .Llevel_31_8008AF28
/* 2A097E0 8008AA18 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 2A097E4 8008AA1C 4B006292 */  lbu        $v0, 0x4B($s3)
/* 2A097E8 8008AA20 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 2A097EC 8008AA24 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_31_8008AA28:
/* 2A097F0 8008AA28 80004234 */  ori        $v0, $v0, 0x80
/* 2A097F4 8008AA2C CA2B0208 */  j          .Llevel_31_8008AF28
/* 2A097F8 8008AA30 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_31_8008AA34:
/* 2A097FC 8008AA34 0000718E */  lw         $s1, 0x0($s3)
/* 2A09800 8008AA38 C8E9000C */  jal        func_8003A720
/* 2A09804 8008AA3C 21206002 */   addu      $a0, $s3, $zero
/* 2A09808 8008AA40 21206002 */  addu       $a0, $s3, $zero
/* 2A0980C 8008AA44 20000224 */  addiu      $v0, $zero, 0x20
/* 2A09810 8008AA48 500062A2 */  sb         $v0, 0x50($s3)
/* 2A09814 8008AA4C FF000224 */  addiu      $v0, $zero, 0xFF
/* 2A09818 8008AA50 734A010C */  jal        func_800529CC
/* 2A0981C 8008AA54 520062A2 */   sb        $v0, 0x52($s3)
/* 2A09820 8008AA58 0E000224 */  addiu      $v0, $zero, 0xE
/* 2A09824 8008AA5C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2A09828 8008AA60 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2A0982C 8008AA64 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 2A09830 8008AA68 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 2A09834 8008AA6C 0780033C */  lui        $v1, %hi(D_80077058)
/* 2A09838 8008AA70 5870638C */  lw         $v1, %lo(D_80077058)($v1)
/* 2A0983C 8008AA74 03000224 */  addiu      $v0, $zero, 0x3
/* 2A09840 8008AA78 03006214 */  bne        $v1, $v0, .Llevel_31_8008AA88
/* 2A09844 8008AA7C 01000224 */   addiu     $v0, $zero, 0x1
/* 2A09848 8008AA80 A42A0208 */  j          .Llevel_31_8008AA90
/* 2A0984C 8008AA84 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_31_8008AA88:
/* 2A09850 8008AA88 02006214 */  bne        $v1, $v0, .Llevel_31_8008AA94
/* 2A09854 8008AA8C 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_31_8008AA90:
/* 2A09858 8008AA90 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_31_8008AA94:
/* 2A0985C 8008AA94 CB89010C */  jal        rand
/* 2A09860 8008AA98 00000000 */   nop
/* 2A09864 8008AA9C 2000A426 */  addiu      $a0, $s5, 0x20
/* 2A09868 8008AAA0 07004230 */  andi       $v0, $v0, 0x7
/* 2A0986C 8008AAA4 80100200 */  sll        $v0, $v0, 2
/* 2A09870 8008AAA8 2000B027 */  addiu      $s0, $sp, 0x20
/* 2A09874 8008AAAC 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 2A09878 8008AAB0 21082200 */  addu       $at, $at, $v0
/* 2A0987C 8008AAB4 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 2A09880 8008AAB8 21280002 */  addu       $a1, $s0, $zero
/* 2A09884 8008AABC 2400A0AF */  sw         $zero, 0x24($sp)
/* 2A09888 8008AAC0 2000A3AF */  sw         $v1, 0x20($sp)
/* 2A0988C 8008AAC4 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 2A09890 8008AAC8 21082200 */  addu       $at, $at, $v0
/* 2A09894 8008AACC A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 2A09898 8008AAD0 21300002 */  addu       $a2, $s0, $zero
/* 2A0989C 8008AAD4 125C000C */  jal        VecRotateByMatrix
/* 2A098A0 8008AAD8 2800A2AF */   sw        $v0, 0x28($sp)
/* 2A098A4 8008AADC CB89010C */  jal        rand
/* 2A098A8 8008AAE0 00000000 */   nop
/* 2A098AC 8008AAE4 2000A38F */  lw         $v1, 0x20($sp)
/* 2A098B0 8008AAE8 7F004230 */  andi       $v0, $v0, 0x7F
/* 2A098B4 8008AAEC C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 2A098B8 8008AAF0 21186200 */  addu       $v1, $v1, $v0
/* 2A098BC 8008AAF4 CB89010C */  jal        rand
/* 2A098C0 8008AAF8 2000A3AF */   sw        $v1, 0x20($sp)
/* 2A098C4 8008AAFC 2400A38F */  lw         $v1, 0x24($sp)
/* 2A098C8 8008AB00 7F004230 */  andi       $v0, $v0, 0x7F
/* 2A098CC 8008AB04 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 2A098D0 8008AB08 21186200 */  addu       $v1, $v1, $v0
/* 2A098D4 8008AB0C CB89010C */  jal        rand
/* 2A098D8 8008AB10 2400A3AF */   sw        $v1, 0x24($sp)
/* 2A098DC 8008AB14 0C006426 */  addiu      $a0, $s3, 0xC
/* 2A098E0 8008AB18 0C00A526 */  addiu      $a1, $s5, 0xC
/* 2A098E4 8008AB1C 21300002 */  addu       $a2, $s0, $zero
/* 2A098E8 8008AB20 2800A38F */  lw         $v1, 0x28($sp)
/* 2A098EC 8008AB24 7F004230 */  andi       $v0, $v0, 0x7F
/* 2A098F0 8008AB28 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 2A098F4 8008AB2C 21186200 */  addu       $v1, $v1, $v0
/* 2A098F8 8008AB30 D65D000C */  jal        VecAdd
/* 2A098FC 8008AB34 2800A3AF */   sw        $v1, 0x28($sp)
/* 2A09900 8008AB38 21202002 */  addu       $a0, $s1, $zero
/* 2A09904 8008AB3C C05D000C */  jal        VecCopy
/* 2A09908 8008AB40 21280002 */   addu      $a1, $s0, $zero
/* 2A0990C 8008AB44 21202002 */  addu       $a0, $s1, $zero
/* 2A09910 8008AB48 B25D000C */  jal        VecShiftRight
/* 2A09914 8008AB4C 02000524 */   addiu     $a1, $zero, 0x2
/* 2A09918 8008AB50 CB89010C */  jal        rand
/* 2A0991C 8008AB54 00000000 */   nop
/* 2A09920 8008AB58 0000238E */  lw         $v1, 0x0($s1)
/* 2A09924 8008AB5C FF004230 */  andi       $v0, $v0, 0xFF
/* 2A09928 8008AB60 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 2A0992C 8008AB64 21186200 */  addu       $v1, $v1, $v0
/* 2A09930 8008AB68 CB89010C */  jal        rand
/* 2A09934 8008AB6C 000023AE */   sw        $v1, 0x0($s1)
/* 2A09938 8008AB70 0400238E */  lw         $v1, 0x4($s1)
/* 2A0993C 8008AB74 FF004230 */  andi       $v0, $v0, 0xFF
/* 2A09940 8008AB78 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 2A09944 8008AB7C 21186200 */  addu       $v1, $v1, $v0
/* 2A09948 8008AB80 CB89010C */  jal        rand
/* 2A0994C 8008AB84 040023AE */   sw        $v1, 0x4($s1)
/* 2A09950 8008AB88 0800238E */  lw         $v1, 0x8($s1)
/* 2A09954 8008AB8C FF004230 */  andi       $v0, $v0, 0xFF
/* 2A09958 8008AB90 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 2A0995C 8008AB94 21186200 */  addu       $v1, $v1, $v0
/* 2A09960 8008AB98 CB89010C */  jal        rand
/* 2A09964 8008AB9C 080023AE */   sw        $v1, 0x8($s1)
/* 2A09968 8008ABA0 CB89010C */  jal        rand
/* 2A0996C 8008ABA4 440062A2 */   sb        $v0, 0x44($s3)
/* 2A09970 8008ABA8 CB89010C */  jal        rand
/* 2A09974 8008ABAC 450062A2 */   sb        $v0, 0x45($s3)
/* 2A09978 8008ABB0 CB89010C */  jal        rand
/* 2A0997C 8008ABB4 460062A2 */   sb        $v0, 0x46($s3)
/* 2A09980 8008ABB8 0F004230 */  andi       $v0, $v0, 0xF
/* 2A09984 8008ABBC CB89010C */  jal        rand
/* 2A09988 8008ABC0 100022A2 */   sb        $v0, 0x10($s1)
/* 2A0998C 8008ABC4 0F004230 */  andi       $v0, $v0, 0xF
/* 2A09990 8008ABC8 CB89010C */  jal        rand
/* 2A09994 8008ABCC 110022A2 */   sb        $v0, 0x11($s1)
/* 2A09998 8008ABD0 0F004230 */  andi       $v0, $v0, 0xF
/* 2A0999C 8008ABD4 120022A2 */  sb         $v0, 0x12($s1)
/* 2A099A0 8008ABD8 1400A28E */  lw         $v0, 0x14($s5)
/* 2A099A4 8008ABDC CB89010C */  jal        rand
/* 2A099A8 8008ABE0 0C0022AE */   sw        $v0, 0xC($s1)
/* 2A099AC 8008ABE4 03004230 */  andi       $v0, $v0, 0x3
/* 2A099B0 8008ABE8 10004224 */  addiu      $v0, $v0, 0x10
/* 2A099B4 8008ABEC CA2B0208 */  j          .Llevel_31_8008AF28
/* 2A099B8 8008ABF0 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_31_8008ABF4:
/* 2A099BC 8008ABF4 0000708E */  lw         $s0, 0x0($s3)
/* 2A099C0 8008ABF8 C8E9000C */  jal        func_8003A720
/* 2A099C4 8008ABFC 21206002 */   addu      $a0, $s3, $zero
/* 2A099C8 8008AC00 734A010C */  jal        func_800529CC
/* 2A099CC 8008AC04 21206002 */   addu      $a0, $s3, $zero
/* 2A099D0 8008AC08 02000224 */  addiu      $v0, $zero, 0x2
/* 2A099D4 8008AC0C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 2A099D8 8008AC10 40000224 */  addiu      $v0, $zero, 0x40
/* 2A099DC 8008AC14 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2A099E0 8008AC18 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2A099E4 8008AC1C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 2A099E8 8008AC20 CA2B0208 */  j          .Llevel_31_8008AF28
/* 2A099EC 8008AC24 000002AE */   sw        $v0, 0x0($s0)
.Llevel_31_8008AC28:
/* 2A099F0 8008AC28 0000718E */  lw         $s1, 0x0($s3)
/* 2A099F4 8008AC2C C8E9000C */  jal        func_8003A720
/* 2A099F8 8008AC30 21206002 */   addu      $a0, $s3, $zero
/* 2A099FC 8008AC34 21300000 */  addu       $a2, $zero, $zero
/* 2A09A00 8008AC38 4600A292 */  lbu        $v0, 0x46($s5)
/* 2A09A04 8008AC3C 0880103C */  lui        $s0, %hi(g_Spyro)
/* 2A09A08 8008AC40 588A1026 */  addiu      $s0, $s0, %lo(g_Spyro)
/* 2A09A0C 8008AC44 40100200 */  sll        $v0, $v0, 1
/* 2A09A10 8008AC48 0780013C */  lui        $at, %hi(D_8006CC78)
/* 2A09A14 8008AC4C 21082200 */  addu       $at, $at, $v0
/* 2A09A18 8008AC50 78CC2294 */  lhu        $v0, %lo(D_8006CC78)($at)
/* 2A09A1C 8008AC54 0C00A38E */  lw         $v1, 0xC($s5)
/* 2A09A20 8008AC58 00140200 */  sll        $v0, $v0, 16
/* 2A09A24 8008AC5C 43140200 */  sra        $v0, $v0, 17
/* 2A09A28 8008AC60 21186200 */  addu       $v1, $v1, $v0
/* 2A09A2C 8008AC64 0C0063AE */  sw         $v1, 0xC($s3)
/* 2A09A30 8008AC68 4600A292 */  lbu        $v0, 0x46($s5)
/* 2A09A34 8008AC6C 1000A38E */  lw         $v1, 0x10($s5)
/* 2A09A38 8008AC70 40100200 */  sll        $v0, $v0, 1
/* 2A09A3C 8008AC74 0780013C */  lui        $at, %hi(D_8006CBF8)
/* 2A09A40 8008AC78 21082200 */  addu       $at, $at, $v0
/* 2A09A44 8008AC7C F8CB2294 */  lhu        $v0, %lo(D_8006CBF8)($at)
/* 2A09A48 8008AC80 0C00648E */  lw         $a0, 0xC($s3)
/* 2A09A4C 8008AC84 00140200 */  sll        $v0, $v0, 16
/* 2A09A50 8008AC88 43140200 */  sra        $v0, $v0, 17
/* 2A09A54 8008AC8C 21186200 */  addu       $v1, $v1, $v0
/* 2A09A58 8008AC90 100063AE */  sw         $v1, 0x10($s3)
/* 2A09A5C 8008AC94 1400A28E */  lw         $v0, 0x14($s5)
/* 2A09A60 8008AC98 1000658E */  lw         $a1, 0x10($s3)
/* 2A09A64 8008AC9C 00034224 */  addiu      $v0, $v0, 0x300
/* 2A09A68 8008ACA0 140062AE */  sw         $v0, 0x14($s3)
/* 2A09A6C 8008ACA4 0000038E */  lw         $v1, 0x0($s0)
/* 2A09A70 8008ACA8 0880023C */  lui        $v0, %hi(g_Spyro + 0x4)
/* 2A09A74 8008ACAC 5C8A428C */  lw         $v0, %lo(g_Spyro + 0x4)($v0)
/* 2A09A78 8008ACB0 23206400 */  subu       $a0, $v1, $a0
/* 2A09A7C 8008ACB4 AD5A000C */  jal        func_80016AB4
/* 2A09A80 8008ACB8 23284500 */   subu      $a1, $v0, $a1
/* 2A09A84 8008ACBC 4600A692 */  lbu        $a2, 0x46($s5)
/* 2A09A88 8008ACC0 00000000 */  nop
/* 2A09A8C 8008ACC4 23104600 */  subu       $v0, $v0, $a2
/* 2A09A90 8008ACC8 FF004330 */  andi       $v1, $v0, 0xFF
/* 2A09A94 8008ACCC 81006228 */  slti       $v0, $v1, 0x81
/* 2A09A98 8008ACD0 03004014 */  bnez       $v0, .Llevel_31_8008ACE0
/* 2A09A9C 8008ACD4 E0FF6228 */   slti      $v0, $v1, -0x20
/* 2A09AA0 8008ACD8 00FF6324 */  addiu      $v1, $v1, -0x100
/* 2A09AA4 8008ACDC E0FF6228 */  slti       $v0, $v1, -0x20
.Llevel_31_8008ACE0:
/* 2A09AA8 8008ACE0 03004010 */  beqz       $v0, .Llevel_31_8008ACF0
/* 2A09AAC 8008ACE4 21006228 */   slti      $v0, $v1, 0x21
/* 2A09AB0 8008ACE8 E0FF0324 */  addiu      $v1, $zero, -0x20
/* 2A09AB4 8008ACEC 21006228 */  slti       $v0, $v1, 0x21
.Llevel_31_8008ACF0:
/* 2A09AB8 8008ACF0 02004014 */  bnez       $v0, .Llevel_31_8008ACFC
/* 2A09ABC 8008ACF4 0C006426 */   addiu     $a0, $s3, 0xC
/* 2A09AC0 8008ACF8 20000324 */  addiu      $v1, $zero, 0x20
.Llevel_31_8008ACFC:
/* 2A09AC4 8008ACFC 21280002 */  addu       $a1, $s0, $zero
/* 2A09AC8 8008AD00 2110C300 */  addu       $v0, $a2, $v1
/* 2A09ACC 8008AD04 645E000C */  jal        OctDistance
/* 2A09AD0 8008AD08 460062A2 */   sb        $v0, 0x46($s3)
/* 2A09AD4 8008AD0C 21204000 */  addu       $a0, $v0, $zero
/* 2A09AD8 8008AD10 21300000 */  addu       $a2, $zero, $zero
/* 2A09ADC 8008AD14 1400658E */  lw         $a1, 0x14($s3)
/* 2A09AE0 8008AD18 0880023C */  lui        $v0, %hi(g_Spyro + 0xA0)
/* 2A09AE4 8008AD1C F88A428C */  lw         $v0, %lo(g_Spyro + 0xA0)($v0)
/* 2A09AE8 8008AD20 9CFEA524 */  addiu      $a1, $a1, -0x164
/* 2A09AEC 8008AD24 AD5A000C */  jal        func_80016AB4
/* 2A09AF0 8008AD28 23284500 */   subu      $a1, $v0, $a1
/* 2A09AF4 8008AD2C 4500A592 */  lbu        $a1, 0x45($s5)
/* 2A09AF8 8008AD30 00000000 */  nop
/* 2A09AFC 8008AD34 23104500 */  subu       $v0, $v0, $a1
/* 2A09B00 8008AD38 FF004330 */  andi       $v1, $v0, 0xFF
/* 2A09B04 8008AD3C 81006228 */  slti       $v0, $v1, 0x81
/* 2A09B08 8008AD40 03004014 */  bnez       $v0, .Llevel_31_8008AD50
/* 2A09B0C 8008AD44 D0FF6228 */   slti      $v0, $v1, -0x30
/* 2A09B10 8008AD48 00FF6324 */  addiu      $v1, $v1, -0x100
/* 2A09B14 8008AD4C D0FF6228 */  slti       $v0, $v1, -0x30
.Llevel_31_8008AD50:
/* 2A09B18 8008AD50 03004010 */  beqz       $v0, .Llevel_31_8008AD60
/* 2A09B1C 8008AD54 31006228 */   slti      $v0, $v1, 0x31
/* 2A09B20 8008AD58 D0FF0324 */  addiu      $v1, $zero, -0x30
/* 2A09B24 8008AD5C 31006228 */  slti       $v0, $v1, 0x31
.Llevel_31_8008AD60:
/* 2A09B28 8008AD60 02004014 */  bnez       $v0, .Llevel_31_8008AD6C
/* 2A09B2C 8008AD64 21206002 */   addu      $a0, $s3, $zero
/* 2A09B30 8008AD68 30000324 */  addiu      $v1, $zero, 0x30
.Llevel_31_8008AD6C:
/* 2A09B34 8008AD6C 2110A300 */  addu       $v0, $a1, $v1
/* 2A09B38 8008AD70 450062A2 */  sb         $v0, 0x45($s3)
/* 2A09B3C 8008AD74 5A000224 */  addiu      $v0, $zero, 0x5A
/* 2A09B40 8008AD78 040022AE */  sw         $v0, 0x4($s1)
/* 2A09B44 8008AD7C C82B0208 */  j          .Llevel_31_8008AF20
/* 2A09B48 8008AD80 000020AE */   sw        $zero, 0x0($s1)
.Llevel_31_8008AD84:
/* 2A09B4C 8008AD84 0000708E */  lw         $s0, 0x0($s3)
/* 2A09B50 8008AD88 C8E9000C */  jal        func_8003A720
/* 2A09B54 8008AD8C 21206002 */   addu      $a0, $s3, $zero
/* 2A09B58 8008AD90 0C006426 */  addiu      $a0, $s3, 0xC
/* 2A09B5C 8008AD94 C05D000C */  jal        VecCopy
/* 2A09B60 8008AD98 0C00A526 */   addiu     $a1, $s5, 0xC
/* 2A09B64 8008AD9C CB89010C */  jal        rand
/* 2A09B68 8008ADA0 00000000 */   nop
/* 2A09B6C 8008ADA4 7E004230 */  andi       $v0, $v0, 0x7E
/* 2A09B70 8008ADA8 C1FF4224 */  addiu      $v0, $v0, -0x3F
/* 2A09B74 8008ADAC CB89010C */  jal        rand
/* 2A09B78 8008ADB0 000002AE */   sw        $v0, 0x0($s0)
/* 2A09B7C 8008ADB4 7E004230 */  andi       $v0, $v0, 0x7E
/* 2A09B80 8008ADB8 C1FF4224 */  addiu      $v0, $v0, -0x3F
/* 2A09B84 8008ADBC CB89010C */  jal        rand
/* 2A09B88 8008ADC0 040002AE */   sw        $v0, 0x4($s0)
/* 2A09B8C 8008ADC4 7E004230 */  andi       $v0, $v0, 0x7E
/* 2A09B90 8008ADC8 F0FF4224 */  addiu      $v0, $v0, -0x10
/* 2A09B94 8008ADCC CB89010C */  jal        rand
/* 2A09B98 8008ADD0 080002AE */   sw        $v0, 0x8($s0)
/* 2A09B9C 8008ADD4 21206002 */  addu       $a0, $s3, $zero
/* 2A09BA0 8008ADD8 1F004230 */  andi       $v0, $v0, 0x1F
/* 2A09BA4 8008ADDC 20004224 */  addiu      $v0, $v0, 0x20
/* 2A09BA8 8008ADE0 C82B0208 */  j          .Llevel_31_8008AF20
/* 2A09BAC 8008ADE4 0C0002AE */   sw        $v0, 0xC($s0)
.Llevel_31_8008ADE8:
/* 2A09BB0 8008ADE8 C8E9000C */  jal        func_8003A720
/* 2A09BB4 8008ADEC 21206002 */   addu      $a0, $s3, $zero
/* 2A09BB8 8008ADF0 05000224 */  addiu      $v0, $zero, 0x5
/* 2A09BBC 8008ADF4 4400A012 */  beqz       $s5, .Llevel_31_8008AF08
/* 2A09BC0 8008ADF8 470062A2 */   sb        $v0, 0x47($s3)
/* 2A09BC4 8008ADFC 0C006426 */  addiu      $a0, $s3, 0xC
/* 2A09BC8 8008AE00 C52B0208 */  j          .Llevel_31_8008AF14
/* 2A09BCC 8008AE04 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_31_8008AE08:
/* 2A09BD0 8008AE08 C8E9000C */  jal        func_8003A720
/* 2A09BD4 8008AE0C 21206002 */   addu      $a0, $s3, $zero
/* 2A09BD8 8008AE10 21206002 */  addu       $a0, $s3, $zero
/* 2A09BDC 8008AE14 FF000224 */  addiu      $v0, $zero, 0xFF
/* 2A09BE0 8008AE18 500062A2 */  sb         $v0, 0x50($s3)
/* 2A09BE4 8008AE1C CC010224 */  addiu      $v0, $zero, 0x1CC
/* 2A09BE8 8008AE20 0C0062AE */  sw         $v0, 0xC($s3)
/* 2A09BEC 8008AE24 28000224 */  addiu      $v0, $zero, 0x28
/* 2A09BF0 8008AE28 100062AE */  sw         $v0, 0x10($s3)
/* 2A09BF4 8008AE2C 00100224 */  addiu      $v0, $zero, 0x1000
/* 2A09BF8 8008AE30 734A010C */  jal        func_800529CC
/* 2A09BFC 8008AE34 140062AE */   sw        $v0, 0x14($s3)
/* 2A09C00 8008AE38 20000224 */  addiu      $v0, $zero, 0x20
/* 2A09C04 8008AE3C 470062A2 */  sb         $v0, 0x47($s3)
/* 2A09C08 8008AE40 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2A09C0C 8008AE44 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2A09C10 8008AE48 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 2A09C14 8008AE4C CA2B0208 */  j          .Llevel_31_8008AF28
/* 2A09C18 8008AE50 4F0060A2 */   sb        $zero, 0x4F($s3)
.Llevel_31_8008AE54:
/* 2A09C1C 8008AE54 C8E9000C */  jal        func_8003A720
/* 2A09C20 8008AE58 21206002 */   addu      $a0, $s3, $zero
/* 2A09C24 8008AE5C 0300A012 */  beqz       $s5, .Llevel_31_8008AE6C
/* 2A09C28 8008AE60 0C006426 */   addiu     $a0, $s3, 0xC
/* 2A09C2C 8008AE64 9D2B0208 */  j          .Llevel_31_8008AE74
/* 2A09C30 8008AE68 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_31_8008AE6C:
/* 2A09C34 8008AE6C 0880053C */  lui        $a1, %hi(g_Spyro)
/* 2A09C38 8008AE70 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_31_8008AE74:
/* 2A09C3C 8008AE74 C05D000C */  jal        VecCopy
/* 2A09C40 8008AE78 00000000 */   nop
/* 2A09C44 8008AE7C 0C006426 */  addiu      $a0, $s3, 0xC
/* 2A09C48 8008AE80 1400628E */  lw         $v0, 0x14($s3)
/* 2A09C4C 8008AE84 00080524 */  addiu      $a1, $zero, 0x800
/* 2A09C50 8008AE88 00024224 */  addiu      $v0, $v0, 0x200
/* 2A09C54 8008AE8C 7B35010C */  jal        func_8004D5EC
/* 2A09C58 8008AE90 140062AE */   sw        $v0, 0x14($s3)
/* 2A09C5C 8008AE94 1400648E */  lw         $a0, 0x14($s3)
/* 2A09C60 8008AE98 21184000 */  addu       $v1, $v0, $zero
/* 2A09C64 8008AE9C 23106400 */  subu       $v0, $v1, $a0
/* 2A09C68 8008AEA0 02004104 */  bgez       $v0, .Llevel_31_8008AEAC
/* 2A09C6C 8008AEA4 00000000 */   nop
/* 2A09C70 8008AEA8 23100200 */  negu       $v0, $v0
.Llevel_31_8008AEAC:
/* 2A09C74 8008AEAC 00084228 */  slti       $v0, $v0, 0x800
/* 2A09C78 8008AEB0 03004010 */  beqz       $v0, .Llevel_31_8008AEC0
/* 2A09C7C 8008AEB4 00FE8224 */   addiu     $v0, $a0, -0x200
/* 2A09C80 8008AEB8 C72B0208 */  j          .Llevel_31_8008AF1C
/* 2A09C84 8008AEBC 140063AE */   sw        $v1, 0x14($s3)
.Llevel_31_8008AEC0:
/* 2A09C88 8008AEC0 C72B0208 */  j          .Llevel_31_8008AF1C
/* 2A09C8C 8008AEC4 140062AE */   sw        $v0, 0x14($s3)
.Llevel_31_8008AEC8:
/* 2A09C90 8008AEC8 C8E9000C */  jal        func_8003A720
/* 2A09C94 8008AECC 21206002 */   addu      $a0, $s3, $zero
/* 2A09C98 8008AED0 21206002 */  addu       $a0, $s3, $zero
/* 2A09C9C 8008AED4 20000224 */  addiu      $v0, $zero, 0x20
/* 2A09CA0 8008AED8 500062A2 */  sb         $v0, 0x50($s3)
/* 2A09CA4 8008AEDC FF000224 */  addiu      $v0, $zero, 0xFF
/* 2A09CA8 8008AEE0 734A010C */  jal        func_800529CC
/* 2A09CAC 8008AEE4 520062A2 */   sb        $v0, 0x52($s3)
/* 2A09CB0 8008AEE8 CB2B0208 */  j          .Llevel_31_8008AF2C
/* 2A09CB4 8008AEEC 21106002 */   addu      $v0, $s3, $zero
.Llevel_31_8008AEF0:
/* 2A09CB8 8008AEF0 C8E9000C */  jal        func_8003A720
/* 2A09CBC 8008AEF4 21206002 */   addu      $a0, $s3, $zero
/* 2A09CC0 8008AEF8 0300A012 */  beqz       $s5, .Llevel_31_8008AF08
/* 2A09CC4 8008AEFC 0C006426 */   addiu     $a0, $s3, 0xC
/* 2A09CC8 8008AF00 C52B0208 */  j          .Llevel_31_8008AF14
/* 2A09CCC 8008AF04 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_31_8008AF08:
/* 2A09CD0 8008AF08 0C006426 */  addiu      $a0, $s3, 0xC
/* 2A09CD4 8008AF0C 0880053C */  lui        $a1, %hi(g_Spyro)
/* 2A09CD8 8008AF10 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_31_8008AF14:
/* 2A09CDC 8008AF14 C05D000C */  jal        VecCopy
/* 2A09CE0 8008AF18 00000000 */   nop
.Llevel_31_8008AF1C:
/* 2A09CE4 8008AF1C 21206002 */  addu       $a0, $s3, $zero
.Llevel_31_8008AF20:
/* 2A09CE8 8008AF20 AA49010C */  jal        func_800526A8
/* 2A09CEC 8008AF24 00000000 */   nop
.Llevel_31_8008AF28:
/* 2A09CF0 8008AF28 21106002 */  addu       $v0, $s3, $zero
.Llevel_31_8008AF2C:
/* 2A09CF4 8008AF2C 5000BF8F */  lw         $ra, 0x50($sp)
/* 2A09CF8 8008AF30 4C00B58F */  lw         $s5, 0x4C($sp)
/* 2A09CFC 8008AF34 4800B48F */  lw         $s4, 0x48($sp)
/* 2A09D00 8008AF38 4400B38F */  lw         $s3, 0x44($sp)
/* 2A09D04 8008AF3C 4000B28F */  lw         $s2, 0x40($sp)
/* 2A09D08 8008AF40 3C00B18F */  lw         $s1, 0x3C($sp)
/* 2A09D0C 8008AF44 3800B08F */  lw         $s0, 0x38($sp)
/* 2A09D10 8008AF48 5800BD27 */  addiu      $sp, $sp, 0x58
/* 2A09D14 8008AF4C 0800E003 */  jr         $ra
/* 2A09D18 8008AF50 00000000 */   nop
.size func_level_31_8008A36C, . - func_level_31_8008A36C
