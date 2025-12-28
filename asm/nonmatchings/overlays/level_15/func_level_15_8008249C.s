.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_15_8008249C
/* 16AFA64 8008249C A0FFBD27 */  addiu      $sp, $sp, -0x60
/* 16AFA68 800824A0 4000B0AF */  sw         $s0, 0x40($sp)
/* 16AFA6C 800824A4 21808000 */  addu       $s0, $a0, $zero
/* 16AFA70 800824A8 5400B5AF */  sw         $s5, 0x54($sp)
/* 16AFA74 800824AC 21A8A000 */  addu       $s5, $a1, $zero
/* 16AFA78 800824B0 5800BFAF */  sw         $ra, 0x58($sp)
/* 16AFA7C 800824B4 5000B4AF */  sw         $s4, 0x50($sp)
/* 16AFA80 800824B8 4C00B3AF */  sw         $s3, 0x4C($sp)
/* 16AFA84 800824BC 4800B2AF */  sw         $s2, 0x48($sp)
/* 16AFA88 800824C0 3149010C */  jal        func_800524C4
/* 16AFA8C 800824C4 4400B1AF */   sw        $s1, 0x44($sp)
/* 16AFA90 800824C8 21A04000 */  addu       $s4, $v0, $zero
/* 16AFA94 800824CC 1400A012 */  beqz       $s5, .Llevel_15_80082520
/* 16AFA98 800824D0 360090A6 */   sh        $s0, 0x36($s4)
/* 16AFA9C 800824D4 0780043C */  lui        $a0, %hi(g_LevelMobys)
/* 16AFAA0 800824D8 2858848C */  lw         $a0, %lo(g_LevelMobys)($a0)
/* 16AFAA4 800824DC 00000000 */  nop
/* 16AFAA8 800824E0 2320A402 */  subu       $a0, $s5, $a0
/* 16AFAAC 800824E4 40190400 */  sll        $v1, $a0, 5
/* 16AFAB0 800824E8 23186400 */  subu       $v1, $v1, $a0
/* 16AFAB4 800824EC 40190300 */  sll        $v1, $v1, 5
/* 16AFAB8 800824F0 21186400 */  addu       $v1, $v1, $a0
/* 16AFABC 800824F4 C0100300 */  sll        $v0, $v1, 3
/* 16AFAC0 800824F8 21186200 */  addu       $v1, $v1, $v0
/* 16AFAC4 800824FC C0130300 */  sll        $v0, $v1, 15
/* 16AFAC8 80082500 23104300 */  subu       $v0, $v0, $v1
/* 16AFACC 80082504 80100200 */  sll        $v0, $v0, 2
/* 16AFAD0 80082508 21104400 */  addu       $v0, $v0, $a0
/* 16AFAD4 8008250C 23100200 */  negu       $v0, $v0
/* 16AFAD8 80082510 C3180200 */  sra        $v1, $v0, 3
/* 16AFADC 80082514 0001622C */  sltiu      $v0, $v1, 0x100
/* 16AFAE0 80082518 03004014 */  bnez       $v0, .Llevel_15_80082528
/* 16AFAE4 8008251C 6A01022A */   slti      $v0, $s0, 0x16A
.Llevel_15_80082520:
/* 16AFAE8 80082520 21180000 */  addu       $v1, $zero, $zero
/* 16AFAEC 80082524 6A01022A */  slti       $v0, $s0, 0x16A
.Llevel_15_80082528:
/* 16AFAF0 80082528 3C004010 */  beqz       $v0, .Llevel_15_8008261C
/* 16AFAF4 8008252C 560083A2 */   sb        $v1, 0x56($s4)
/* 16AFAF8 80082530 6701022A */  slti       $v0, $s0, 0x167
/* 16AFAFC 80082534 20024010 */  beqz       $v0, .Llevel_15_80082DB8
/* 16AFB00 80082538 5800022A */   slti      $v0, $s0, 0x58
/* 16AFB04 8008253C 1D004010 */  beqz       $v0, .Llevel_15_800825B4
/* 16AFB08 80082540 5300022A */   slti      $v0, $s0, 0x53
/* 16AFB0C 80082544 ED004010 */  beqz       $v0, .Llevel_15_800828FC
/* 16AFB10 80082548 11000224 */   addiu     $v0, $zero, 0x11
/* 16AFB14 8008254C 9F000212 */  beq        $s0, $v0, .Llevel_15_800827CC
/* 16AFB18 80082550 1200022A */   slti      $v0, $s0, 0x12
/* 16AFB1C 80082554 09004010 */  beqz       $v0, .Llevel_15_8008257C
/* 16AFB20 80082558 0F000224 */   addiu     $v0, $zero, 0xF
/* 16AFB24 8008255C 60000212 */  beq        $s0, $v0, .Llevel_15_800826E0
/* 16AFB28 80082560 1000022A */   slti      $v0, $s0, 0x10
/* 16AFB2C 80082564 85004010 */  beqz       $v0, .Llevel_15_8008277C
/* 16AFB30 80082568 0E000224 */   addiu     $v0, $zero, 0xE
/* 16AFB34 8008256C E3000212 */  beq        $s0, $v0, .Llevel_15_800828FC
/* 16AFB38 80082570 00000000 */   nop
/* 16AFB3C 80082574 B40C0208 */  j          .Llevel_15_800832D0
/* 16AFB40 80082578 00000000 */   nop
.Llevel_15_8008257C:
/* 16AFB44 8008257C 4C000224 */  addiu      $v0, $zero, 0x4C
/* 16AFB48 80082580 49030212 */  beq        $s0, $v0, .Llevel_15_800832A8
/* 16AFB4C 80082584 4D00022A */   slti      $v0, $s0, 0x4D
/* 16AFB50 80082588 05004010 */  beqz       $v0, .Llevel_15_800825A0
/* 16AFB54 8008258C 22000224 */   addiu     $v0, $zero, 0x22
/* 16AFB58 80082590 C8000212 */  beq        $s0, $v0, .Llevel_15_800828B4
/* 16AFB5C 80082594 00000000 */   nop
/* 16AFB60 80082598 B40C0208 */  j          .Llevel_15_800832D0
/* 16AFB64 8008259C 00000000 */   nop
.Llevel_15_800825A0:
/* 16AFB68 800825A0 4E000224 */  addiu      $v0, $zero, 0x4E
/* 16AFB6C 800825A4 D1000212 */  beq        $s0, $v0, .Llevel_15_800828EC
/* 16AFB70 800825A8 00000000 */   nop
/* 16AFB74 800825AC B40C0208 */  j          .Llevel_15_800832D0
/* 16AFB78 800825B0 00000000 */   nop
.Llevel_15_800825B4:
/* 16AFB7C 800825B4 15010224 */  addiu      $v0, $zero, 0x115
/* 16AFB80 800825B8 A6020212 */  beq        $s0, $v0, .Llevel_15_80083054
/* 16AFB84 800825BC 1601022A */   slti      $v0, $s0, 0x116
/* 16AFB88 800825C0 0B004010 */  beqz       $v0, .Llevel_15_800825F0
/* 16AFB8C 800825C4 78000224 */   addiu     $v0, $zero, 0x78
/* 16AFB90 800825C8 23010212 */  beq        $s0, $v0, .Llevel_15_80082A58
/* 16AFB94 800825CC 7800022A */   slti      $v0, $s0, 0x78
/* 16AFB98 800825D0 3F034014 */  bnez       $v0, .Llevel_15_800832D0
/* 16AFB9C 800825D4 0E01022A */   slti      $v0, $s0, 0x10E
/* 16AFBA0 800825D8 3D034010 */  beqz       $v0, .Llevel_15_800832D0
/* 16AFBA4 800825DC 0401022A */   slti      $v0, $s0, 0x104
/* 16AFBA8 800825E0 9C024010 */  beqz       $v0, .Llevel_15_80083054
/* 16AFBAC 800825E4 00000000 */   nop
/* 16AFBB0 800825E8 B40C0208 */  j          .Llevel_15_800832D0
/* 16AFBB4 800825EC 00000000 */   nop
.Llevel_15_800825F0:
/* 16AFBB8 800825F0 47010224 */  addiu      $v0, $zero, 0x147
/* 16AFBBC 800825F4 97020212 */  beq        $s0, $v0, .Llevel_15_80083054
/* 16AFBC0 800825F8 4701022A */   slti      $v0, $s0, 0x147
/* 16AFBC4 800825FC 34034014 */  bnez       $v0, .Llevel_15_800832D0
/* 16AFBC8 80082600 5C01022A */   slti      $v0, $s0, 0x15C
/* 16AFBCC 80082604 32034010 */  beqz       $v0, .Llevel_15_800832D0
/* 16AFBD0 80082608 5901022A */   slti      $v0, $s0, 0x159
/* 16AFBD4 8008260C 9E024010 */  beqz       $v0, .Llevel_15_80083088
/* 16AFBD8 80082610 00000000 */   nop
/* 16AFBDC 80082614 B40C0208 */  j          .Llevel_15_800832D0
/* 16AFBE0 80082618 00000000 */   nop
.Llevel_15_8008261C:
/* 16AFBE4 8008261C 95010224 */  addiu      $v0, $zero, 0x195
/* 16AFBE8 80082620 04030212 */  beq        $s0, $v0, .Llevel_15_80083234
/* 16AFBEC 80082624 9601022A */   slti      $v0, $s0, 0x196
/* 16AFBF0 80082628 19004010 */  beqz       $v0, .Llevel_15_80082690
/* 16AFBF4 8008262C 8301022A */   slti      $v0, $s0, 0x183
/* 16AFBF8 80082630 09004010 */  beqz       $v0, .Llevel_15_80082658
/* 16AFBFC 80082634 7701022A */   slti      $v0, $s0, 0x177
/* 16AFC00 80082638 D1024010 */  beqz       $v0, .Llevel_15_80083180
/* 16AFC04 8008263C 6A010224 */   addiu     $v0, $zero, 0x16A
/* 16AFC08 80082640 30020212 */  beq        $s0, $v0, .Llevel_15_80082F04
/* 16AFC0C 80082644 76010224 */   addiu     $v0, $zero, 0x176
/* 16AFC10 80082648 AF020212 */  beq        $s0, $v0, .Llevel_15_80083108
/* 16AFC14 8008264C 00000000 */   nop
/* 16AFC18 80082650 B40C0208 */  j          .Llevel_15_800832D0
/* 16AFC1C 80082654 00000000 */   nop
.Llevel_15_80082658:
/* 16AFC20 80082658 89010224 */  addiu      $v0, $zero, 0x189
/* 16AFC24 8008265C E3020212 */  beq        $s0, $v0, .Llevel_15_800831EC
/* 16AFC28 80082660 8A01022A */   slti      $v0, $s0, 0x18A
/* 16AFC2C 80082664 05004010 */  beqz       $v0, .Llevel_15_8008267C
/* 16AFC30 80082668 8601022A */   slti      $v0, $s0, 0x186
/* 16AFC34 8008266C 18034010 */  beqz       $v0, .Llevel_15_800832D0
/* 16AFC38 80082670 00000000 */   nop
/* 16AFC3C 80082674 7B0C0208 */  j          .Llevel_15_800831EC
/* 16AFC40 80082678 00000000 */   nop
.Llevel_15_8008267C:
/* 16AFC44 8008267C 90010224 */  addiu      $v0, $zero, 0x190
/* 16AFC48 80082680 EC020212 */  beq        $s0, $v0, .Llevel_15_80083234
/* 16AFC4C 80082684 00000000 */   nop
/* 16AFC50 80082688 B40C0208 */  j          .Llevel_15_800832D0
/* 16AFC54 8008268C 00000000 */   nop
.Llevel_15_80082690:
/* 16AFC58 80082690 E101022A */  slti       $v0, $s0, 0x1E1
/* 16AFC5C 80082694 0B004010 */  beqz       $v0, .Llevel_15_800826C4
/* 16AFC60 80082698 DE01022A */   slti      $v0, $s0, 0x1DE
/* 16AFC64 8008269C 00014010 */  beqz       $v0, .Llevel_15_80082AA0
/* 16AFC68 800826A0 AA01022A */   slti      $v0, $s0, 0x1AA
/* 16AFC6C 800826A4 0A034014 */  bnez       $v0, .Llevel_15_800832D0
/* 16AFC70 800826A8 C401022A */   slti      $v0, $s0, 0x1C4
/* 16AFC74 800826AC FE024014 */  bnez       $v0, .Llevel_15_800832A8
/* 16AFC78 800826B0 DD010224 */   addiu     $v0, $zero, 0x1DD
/* 16AFC7C 800826B4 DF020212 */  beq        $s0, $v0, .Llevel_15_80083234
/* 16AFC80 800826B8 00000000 */   nop
/* 16AFC84 800826BC B40C0208 */  j          .Llevel_15_800832D0
/* 16AFC88 800826C0 00000000 */   nop
.Llevel_15_800826C4:
/* 16AFC8C 800826C4 E401022A */  slti       $v0, $s0, 0x1E4
/* 16AFC90 800826C8 60014014 */  bnez       $v0, .Llevel_15_80082C4C
/* 16AFC94 800826CC EA010224 */   addiu     $v0, $zero, 0x1EA
/* 16AFC98 800826D0 C6020212 */  beq        $s0, $v0, .Llevel_15_800831EC
/* 16AFC9C 800826D4 00000000 */   nop
/* 16AFCA0 800826D8 B40C0208 */  j          .Llevel_15_800832D0
/* 16AFCA4 800826DC 00000000 */   nop
.Llevel_15_800826E0:
/* 16AFCA8 800826E0 0000908E */  lw         $s0, 0x0($s4)
/* 16AFCAC 800826E4 C8E9000C */  jal        func_8003A720
/* 16AFCB0 800826E8 21208002 */   addu      $a0, $s4, $zero
/* 16AFCB4 800826EC 8C000224 */  addiu      $v0, $zero, 0x8C
/* 16AFCB8 800826F0 080002AE */  sw         $v0, 0x8($s0)
/* 16AFCBC 800826F4 03000224 */  addiu      $v0, $zero, 0x3
/* 16AFCC0 800826F8 100002A2 */  sb         $v0, 0x10($s0)
/* 16AFCC4 800826FC FF000224 */  addiu      $v0, $zero, 0xFF
/* 16AFCC8 80082700 140002A2 */  sb         $v0, 0x14($s0)
/* 16AFCCC 80082704 02000224 */  addiu      $v0, $zero, 0x2
/* 16AFCD0 80082708 000000AE */  sw         $zero, 0x0($s0)
/* 16AFCD4 8008270C 040000AE */  sw         $zero, 0x4($s0)
/* 16AFCD8 80082710 0E0000A2 */  sb         $zero, 0xE($s0)
/* 16AFCDC 80082714 0F0000A2 */  sb         $zero, 0xF($s0)
/* 16AFCE0 80082718 110000A2 */  sb         $zero, 0x11($s0)
/* 16AFCE4 8008271C 120000A2 */  sb         $zero, 0x12($s0)
/* 16AFCE8 80082720 130000A2 */  sb         $zero, 0x13($s0)
/* 16AFCEC 80082724 490082A2 */  sb         $v0, 0x49($s4)
/* 16AFCF0 80082728 18000224 */  addiu      $v0, $zero, 0x18
/* 16AFCF4 8008272C 500082A2 */  sb         $v0, 0x50($s4)
/* 16AFCF8 80082730 10000224 */  addiu      $v0, $zero, 0x10
/* 16AFCFC 80082734 520082A2 */  sb         $v0, 0x52($s4)
/* 16AFD00 80082738 20000224 */  addiu      $v0, $zero, 0x20
/* 16AFD04 8008273C 440082A2 */  sb         $v0, 0x44($s4)
/* 16AFD08 80082740 450080A2 */  sb         $zero, 0x45($s4)
/* 16AFD0C 80082744 0400A012 */  beqz       $s5, .Llevel_15_80082758
/* 16AFD10 80082748 460080A2 */   sb        $zero, 0x46($s4)
/* 16AFD14 8008274C 0C008426 */  addiu      $a0, $s4, 0xC
/* 16AFD18 80082750 C05D000C */  jal        VecCopy
/* 16AFD1C 80082754 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_15_80082758:
/* 16AFD20 80082758 AA49010C */  jal        func_800526A8
/* 16AFD24 8008275C 21208002 */   addu      $a0, $s4, $zero
/* 16AFD28 80082760 4B008292 */  lbu        $v0, 0x4B($s4)
/* 16AFD2C 80082764 01000324 */  addiu      $v1, $zero, 0x1
/* 16AFD30 80082768 4C0080A2 */  sb         $zero, 0x4C($s4)
/* 16AFD34 8008276C 4D0080A2 */  sb         $zero, 0x4D($s4)
/* 16AFD38 80082770 4E0080A2 */  sb         $zero, 0x4E($s4)
/* 16AFD3C 80082774 100B0208 */  j          .Llevel_15_80082C40
/* 16AFD40 80082778 4F0083A2 */   sb        $v1, 0x4F($s4)
.Llevel_15_8008277C:
/* 16AFD44 8008277C 0000918E */  lw         $s1, 0x0($s4)
/* 16AFD48 80082780 C8E9000C */  jal        func_8003A720
/* 16AFD4C 80082784 21208002 */   addu      $a0, $s4, $zero
/* 16AFD50 80082788 AA49010C */  jal        func_800526A8
/* 16AFD54 8008278C 21208002 */   addu      $a0, $s4, $zero
/* 16AFD58 80082790 0C009026 */  addiu      $s0, $s4, 0xC
/* 16AFD5C 80082794 21200002 */  addu       $a0, $s0, $zero
/* 16AFD60 80082798 C05D000C */  jal        VecCopy
/* 16AFD64 8008279C 0C00A526 */   addiu     $a1, $s5, 0xC
/* 16AFD68 800827A0 21280002 */  addu       $a1, $s0, $zero
/* 16AFD6C 800827A4 1400828E */  lw         $v0, 0x14($s4)
/* 16AFD70 800827A8 04002426 */  addiu      $a0, $s1, 0x4
/* 16AFD74 800827AC 00024224 */  addiu      $v0, $v0, 0x200
/* 16AFD78 800827B0 C05D000C */  jal        VecCopy
/* 16AFD7C 800827B4 140082AE */   sw        $v0, 0x14($s4)
/* 16AFD80 800827B8 08070224 */  addiu      $v0, $zero, 0x708
/* 16AFD84 800827BC 130020A2 */  sb         $zero, 0x13($s1)
/* 16AFD88 800827C0 120020A2 */  sb         $zero, 0x12($s1)
/* 16AFD8C 800827C4 C10C0208 */  j          .Llevel_15_80083304
/* 16AFD90 800827C8 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_15_800827CC:
/* 16AFD94 800827CC C8E9000C */  jal        func_8003A720
/* 16AFD98 800827D0 21208002 */   addu      $a0, $s4, $zero
/* 16AFD9C 800827D4 4600A292 */  lbu        $v0, 0x46($s5)
/* 16AFDA0 800827D8 00000000 */  nop
/* 16AFDA4 800827DC 460082A2 */  sb         $v0, 0x46($s4)
/* 16AFDA8 800827E0 40100200 */  sll        $v0, $v0, 1
/* 16AFDAC 800827E4 0780013C */  lui        $at, %hi(D_8006CC78)
/* 16AFDB0 800827E8 21082200 */  addu       $at, $at, $v0
/* 16AFDB4 800827EC 78CC2394 */  lhu        $v1, %lo(D_8006CC78)($at)
/* 16AFDB8 800827F0 0C00A28E */  lw         $v0, 0xC($s5)
/* 16AFDBC 800827F4 46008492 */  lbu        $a0, 0x46($s4)
/* 16AFDC0 800827F8 001C0300 */  sll        $v1, $v1, 16
/* 16AFDC4 800827FC 031D0300 */  sra        $v1, $v1, 20
/* 16AFDC8 80082800 21104300 */  addu       $v0, $v0, $v1
/* 16AFDCC 80082804 40200400 */  sll        $a0, $a0, 1
/* 16AFDD0 80082808 0C0082AE */  sw         $v0, 0xC($s4)
/* 16AFDD4 8008280C 0780013C */  lui        $at, %hi(D_8006CBF8)
/* 16AFDD8 80082810 21082400 */  addu       $at, $at, $a0
/* 16AFDDC 80082814 F8CB2294 */  lhu        $v0, %lo(D_8006CBF8)($at)
/* 16AFDE0 80082818 1000A38E */  lw         $v1, 0x10($s5)
/* 16AFDE4 8008281C 00140200 */  sll        $v0, $v0, 16
/* 16AFDE8 80082820 03150200 */  sra        $v0, $v0, 20
/* 16AFDEC 80082824 21186200 */  addu       $v1, $v1, $v0
/* 16AFDF0 80082828 100083AE */  sw         $v1, 0x10($s4)
/* 16AFDF4 8008282C 1400A28E */  lw         $v0, 0x14($s5)
/* 16AFDF8 80082830 0C00838E */  lw         $v1, 0xC($s4)
/* 16AFDFC 80082834 140082AE */  sw         $v0, 0x14($s4)
/* 16AFE00 80082838 0880023C */  lui        $v0, %hi(g_Spyro)
/* 16AFE04 8008283C 588A428C */  lw         $v0, %lo(g_Spyro)($v0)
/* 16AFE08 80082840 00000000 */  nop
/* 16AFE0C 80082844 23104300 */  subu       $v0, $v0, $v1
/* 16AFE10 80082848 1000A2AF */  sw         $v0, 0x10($sp)
/* 16AFE14 8008284C 0880023C */  lui        $v0, %hi(g_Spyro + 0x4)
/* 16AFE18 80082850 5C8A428C */  lw         $v0, %lo(g_Spyro + 0x4)($v0)
/* 16AFE1C 80082854 1000838E */  lw         $v1, 0x10($s4)
/* 16AFE20 80082858 01000524 */  addiu      $a1, $zero, 0x1
/* 16AFE24 8008285C 23104300 */  subu       $v0, $v0, $v1
/* 16AFE28 80082860 1400A2AF */  sw         $v0, 0x14($sp)
/* 16AFE2C 80082864 0880023C */  lui        $v0, %hi(g_Spyro + 0x8)
/* 16AFE30 80082868 608A428C */  lw         $v0, %lo(g_Spyro + 0x8)($v0)
/* 16AFE34 8008286C 1400838E */  lw         $v1, 0x14($s4)
/* 16AFE38 80082870 1000A427 */  addiu      $a0, $sp, 0x10
/* 16AFE3C 80082874 23104300 */  subu       $v0, $v0, $v1
/* 16AFE40 80082878 7F5C000C */  jal        VecMagnitude
/* 16AFE44 8008287C 1800A2AF */   sw        $v0, 0x18($sp)
/* 16AFE48 80082880 1000A427 */  addiu      $a0, $sp, 0x10
/* 16AFE4C 80082884 21284000 */  addu       $a1, $v0, $zero
/* 16AFE50 80082888 6E5D000C */  jal        VecScaleToLength
/* 16AFE54 8008288C A0000624 */   addiu     $a2, $zero, 0xA0
/* 16AFE58 80082890 AA49010C */  jal        func_800526A8
/* 16AFE5C 80082894 21208002 */   addu      $a0, $s4, $zero
/* 16AFE60 80082898 0000908E */  lw         $s0, 0x0($s4)
/* 16AFE64 8008289C 1000A527 */  addiu      $a1, $sp, 0x10
/* 16AFE68 800828A0 C05D000C */  jal        VecCopy
/* 16AFE6C 800828A4 21200002 */   addu      $a0, $s0, $zero
/* 16AFE70 800828A8 50000224 */  addiu      $v0, $zero, 0x50
/* 16AFE74 800828AC C10C0208 */  j          .Llevel_15_80083304
/* 16AFE78 800828B0 0C0002AE */   sw        $v0, 0xC($s0)
.Llevel_15_800828B4:
/* 16AFE7C 800828B4 C8E9000C */  jal        func_8003A720
/* 16AFE80 800828B8 21208002 */   addu      $a0, $s4, $zero
/* 16AFE84 800828BC 20000224 */  addiu      $v0, $zero, 0x20
/* 16AFE88 800828C0 500082A2 */  sb         $v0, 0x50($s4)
/* 16AFE8C 800828C4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 16AFE90 800828C8 0400A012 */  beqz       $s5, .Llevel_15_800828DC
/* 16AFE94 800828CC 520082A2 */   sb        $v0, 0x52($s4)
/* 16AFE98 800828D0 0C008426 */  addiu      $a0, $s4, 0xC
/* 16AFE9C 800828D4 C05D000C */  jal        VecCopy
/* 16AFEA0 800828D8 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_15_800828DC:
/* 16AFEA4 800828DC 734A010C */  jal        func_800529CC
/* 16AFEA8 800828E0 21208002 */   addu      $a0, $s4, $zero
/* 16AFEAC 800828E4 C20C0208 */  j          .Llevel_15_80083308
/* 16AFEB0 800828E8 21108002 */   addu      $v0, $s4, $zero
.Llevel_15_800828EC:
/* 16AFEB4 800828EC C8E9000C */  jal        func_8003A720
/* 16AFEB8 800828F0 21208002 */   addu      $a0, $s4, $zero
/* 16AFEBC 800828F4 BF0C0208 */  j          .Llevel_15_800832FC
/* 16AFEC0 800828F8 00000000 */   nop
.Llevel_15_800828FC:
/* 16AFEC4 800828FC 0000908E */  lw         $s0, 0x0($s4)
/* 16AFEC8 80082900 C8E9000C */  jal        func_8003A720
/* 16AFECC 80082904 21208002 */   addu      $a0, $s4, $zero
/* 16AFED0 80082908 8C000224 */  addiu      $v0, $zero, 0x8C
/* 16AFED4 8008290C 000000AE */  sw         $zero, 0x0($s0)
/* 16AFED8 80082910 040000AE */  sw         $zero, 0x4($s0)
/* 16AFEDC 80082914 080002AE */  sw         $v0, 0x8($s0)
/* 16AFEE0 80082918 0E0000A2 */  sb         $zero, 0xE($s0)
/* 16AFEE4 8008291C 0F0000A2 */  sb         $zero, 0xF($s0)
/* 16AFEE8 80082920 110000A2 */  sb         $zero, 0x11($s0)
/* 16AFEEC 80082924 120000A2 */  sb         $zero, 0x12($s0)
/* 16AFEF0 80082928 130000A2 */  sb         $zero, 0x13($s0)
/* 16AFEF4 8008292C 3600A386 */  lh         $v1, 0x36($s5)
/* 16AFEF8 80082930 0D000224 */  addiu      $v0, $zero, 0xD
/* 16AFEFC 80082934 02006214 */  bne        $v1, $v0, .Llevel_15_80082940
/* 16AFF00 80082938 03000224 */   addiu     $v0, $zero, 0x3
/* 16AFF04 8008293C 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_15_80082940:
/* 16AFF08 80082940 100002A2 */  sb         $v0, 0x10($s0)
/* 16AFF0C 80082944 0C009126 */  addiu      $s1, $s4, 0xC
/* 16AFF10 80082948 21202002 */  addu       $a0, $s1, $zero
/* 16AFF14 8008294C 0C00A526 */  addiu      $a1, $s5, 0xC
/* 16AFF18 80082950 FF000224 */  addiu      $v0, $zero, 0xFF
/* 16AFF1C 80082954 02001224 */  addiu      $s2, $zero, 0x2
/* 16AFF20 80082958 140002A2 */  sb         $v0, 0x14($s0)
/* 16AFF24 8008295C 18000224 */  addiu      $v0, $zero, 0x18
/* 16AFF28 80082960 500082A2 */  sb         $v0, 0x50($s4)
/* 16AFF2C 80082964 40000224 */  addiu      $v0, $zero, 0x40
/* 16AFF30 80082968 520082A2 */  sb         $v0, 0x52($s4)
/* 16AFF34 8008296C 20000224 */  addiu      $v0, $zero, 0x20
/* 16AFF38 80082970 490092A2 */  sb         $s2, 0x49($s4)
/* 16AFF3C 80082974 440082A2 */  sb         $v0, 0x44($s4)
/* 16AFF40 80082978 450080A2 */  sb         $zero, 0x45($s4)
/* 16AFF44 8008297C C05D000C */  jal        VecCopy
/* 16AFF48 80082980 460080A2 */   sb        $zero, 0x46($s4)
/* 16AFF4C 80082984 734A010C */  jal        func_800529CC
/* 16AFF50 80082988 21208002 */   addu      $a0, $s4, $zero
/* 16AFF54 8008298C 2000B027 */  addiu      $s0, $sp, 0x20
/* 16AFF58 80082990 21200002 */  addu       $a0, $s0, $zero
/* 16AFF5C 80082994 21282002 */  addu       $a1, $s1, $zero
/* 16AFF60 80082998 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 16AFF64 8008299C C05D000C */  jal        VecCopy
/* 16AFF68 800829A0 1C0082AE */   sw        $v0, 0x1C($s4)
/* 16AFF6C 800829A4 21200002 */  addu       $a0, $s0, $zero
/* 16AFF70 800829A8 2800A28F */  lw         $v0, 0x28($sp)
/* 16AFF74 800829AC 0100053C */  lui        $a1, (0x10000 >> 16)
/* 16AFF78 800829B0 00044224 */  addiu      $v0, $v0, 0x400
/* 16AFF7C 800829B4 7B35010C */  jal        func_8004D5EC
/* 16AFF80 800829B8 2800A2AF */   sw        $v0, 0x28($sp)
/* 16AFF84 800829BC F44C010C */  jal        func_800533D0
/* 16AFF88 800829C0 21208002 */   addu      $a0, $s4, $zero
/* 16AFF8C 800829C4 36008386 */  lh         $v1, 0x36($s4)
/* 16AFF90 800829C8 0E000224 */  addiu      $v0, $zero, 0xE
/* 16AFF94 800829CC 4C0080A2 */  sb         $zero, 0x4C($s4)
/* 16AFF98 800829D0 4D0080A2 */  sb         $zero, 0x4D($s4)
/* 16AFF9C 800829D4 03006214 */  bne        $v1, $v0, .Llevel_15_800829E4
/* 16AFFA0 800829D8 4E0080A2 */   sb        $zero, 0x4E($s4)
/* 16AFFA4 800829DC 0C000224 */  addiu      $v0, $zero, 0xC
/* 16AFFA8 800829E0 4F0082A2 */  sb         $v0, 0x4F($s4)
.Llevel_15_800829E4:
/* 16AFFAC 800829E4 36008386 */  lh         $v1, 0x36($s4)
/* 16AFFB0 800829E8 53000224 */  addiu      $v0, $zero, 0x53
/* 16AFFB4 800829EC 05006214 */  bne        $v1, $v0, .Llevel_15_80082A04
/* 16AFFB8 800829F0 54000224 */   addiu     $v0, $zero, 0x54
/* 16AFFBC 800829F4 01000224 */  addiu      $v0, $zero, 0x1
/* 16AFFC0 800829F8 4F0082A2 */  sb         $v0, 0x4F($s4)
/* 16AFFC4 800829FC 36008386 */  lh         $v1, 0x36($s4)
/* 16AFFC8 80082A00 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_15_80082A04:
/* 16AFFCC 80082A04 02006214 */  bne        $v1, $v0, .Llevel_15_80082A10
/* 16AFFD0 80082A08 00000000 */   nop
/* 16AFFD4 80082A0C 4F0092A2 */  sb         $s2, 0x4F($s4)
.Llevel_15_80082A10:
/* 16AFFD8 80082A10 36008386 */  lh         $v1, 0x36($s4)
/* 16AFFDC 80082A14 55000224 */  addiu      $v0, $zero, 0x55
/* 16AFFE0 80082A18 05006214 */  bne        $v1, $v0, .Llevel_15_80082A30
/* 16AFFE4 80082A1C 56000224 */   addiu     $v0, $zero, 0x56
/* 16AFFE8 80082A20 03000224 */  addiu      $v0, $zero, 0x3
/* 16AFFEC 80082A24 4F0082A2 */  sb         $v0, 0x4F($s4)
/* 16AFFF0 80082A28 36008386 */  lh         $v1, 0x36($s4)
/* 16AFFF4 80082A2C 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_15_80082A30:
/* 16AFFF8 80082A30 02006214 */  bne        $v1, $v0, .Llevel_15_80082A3C
/* 16AFFFC 80082A34 04000224 */   addiu     $v0, $zero, 0x4
/* 16B0000 80082A38 4F0082A2 */  sb         $v0, 0x4F($s4)
.Llevel_15_80082A3C:
/* 16B0004 80082A3C 36008386 */  lh         $v1, 0x36($s4)
/* 16B0008 80082A40 57000224 */  addiu      $v0, $zero, 0x57
/* 16B000C 80082A44 30026214 */  bne        $v1, $v0, .Llevel_15_80083308
/* 16B0010 80082A48 21108002 */   addu      $v0, $s4, $zero
/* 16B0014 80082A4C 05000224 */  addiu      $v0, $zero, 0x5
/* 16B0018 80082A50 C10C0208 */  j          .Llevel_15_80083304
/* 16B001C 80082A54 4F0082A2 */   sb        $v0, 0x4F($s4)
.Llevel_15_80082A58:
/* 16B0020 80082A58 0000908E */  lw         $s0, 0x0($s4)
/* 16B0024 80082A5C C8E9000C */  jal        func_8003A720
/* 16B0028 80082A60 21208002 */   addu      $a0, $s4, $zero
/* 16B002C 80082A64 AA49010C */  jal        func_800526A8
/* 16B0030 80082A68 21208002 */   addu      $a0, $s4, $zero
/* 16B0034 80082A6C 490080A2 */  sb         $zero, 0x49($s4)
/* 16B0038 80082A70 000000AE */  sw         $zero, 0x0($s0)
/* 16B003C 80082A74 080000A6 */  sh         $zero, 0x8($s0)
/* 16B0040 80082A78 060000A6 */  sh         $zero, 0x6($s0)
/* 16B0044 80082A7C 040000A6 */  sh         $zero, 0x4($s0)
/* 16B0048 80082A80 0C0000AE */  sw         $zero, 0xC($s0)
/* 16B004C 80082A84 1F02A012 */  beqz       $s5, .Llevel_15_80083304
/* 16B0050 80082A88 100000AE */   sw        $zero, 0x10($s0)
/* 16B0054 80082A8C 0C008426 */  addiu      $a0, $s4, 0xC
/* 16B0058 80082A90 C05D000C */  jal        VecCopy
/* 16B005C 80082A94 0C00A526 */   addiu     $a1, $s5, 0xC
/* 16B0060 80082A98 C20C0208 */  j          .Llevel_15_80083308
/* 16B0064 80082A9C 21108002 */   addu      $v0, $s4, $zero
.Llevel_15_80082AA0:
/* 16B0068 80082AA0 0000938E */  lw         $s3, 0x0($s4)
/* 16B006C 80082AA4 C8E9000C */  jal        func_8003A720
/* 16B0070 80082AA8 21208002 */   addu      $a0, $s4, $zero
/* 16B0074 80082AAC 0C008426 */  addiu      $a0, $s4, 0xC
/* 16B0078 80082AB0 0C00A526 */  addiu      $a1, $s5, 0xC
/* 16B007C 80082AB4 20000224 */  addiu      $v0, $zero, 0x20
/* 16B0080 80082AB8 C05D000C */  jal        VecCopy
/* 16B0084 80082ABC 500082A2 */   sb        $v0, 0x50($s4)
/* 16B0088 80082AC0 AA49010C */  jal        func_800526A8
/* 16B008C 80082AC4 21208002 */   addu      $a0, $s4, $zero
/* 16B0090 80082AC8 CB89010C */  jal        rand
/* 16B0094 80082ACC 00000000 */   nop
/* 16B0098 80082AD0 CB89010C */  jal        rand
/* 16B009C 80082AD4 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 16B00A0 80082AD8 FF075130 */  andi       $s1, $v0, 0x7FF
/* 16B00A4 80082ADC 2C5B000C */  jal        Cos
/* 16B00A8 80082AE0 21202002 */   addu      $a0, $s1, $zero
/* 16B00AC 80082AE4 21204002 */  addu       $a0, $s2, $zero
/* 16B00B0 80082AE8 2C5B000C */  jal        Cos
/* 16B00B4 80082AEC 21804000 */   addu      $s0, $v0, $zero
/* 16B00B8 80082AF0 43811000 */  sra        $s0, $s0, 5
/* 16B00BC 80082AF4 18000202 */  mult       $s0, $v0
/* 16B00C0 80082AF8 21202002 */  addu       $a0, $s1, $zero
/* 16B00C4 80082AFC 12380000 */  mflo       $a3
/* 16B00C8 80082B00 03130700 */  sra        $v0, $a3, 12
/* 16B00CC 80082B04 2C5B000C */  jal        Cos
/* 16B00D0 80082B08 000062A6 */   sh        $v0, 0x0($s3)
/* 16B00D4 80082B0C 21204002 */  addu       $a0, $s2, $zero
/* 16B00D8 80082B10 165B000C */  jal        Sin
/* 16B00DC 80082B14 21804000 */   addu      $s0, $v0, $zero
/* 16B00E0 80082B18 43811000 */  sra        $s0, $s0, 5
/* 16B00E4 80082B1C 18000202 */  mult       $s0, $v0
/* 16B00E8 80082B20 21202002 */  addu       $a0, $s1, $zero
/* 16B00EC 80082B24 12380000 */  mflo       $a3
/* 16B00F0 80082B28 03130700 */  sra        $v0, $a3, 12
/* 16B00F4 80082B2C 165B000C */  jal        Sin
/* 16B00F8 80082B30 020062A6 */   sh        $v0, 0x2($s3)
/* 16B00FC 80082B34 43110200 */  sra        $v0, $v0, 5
/* 16B0100 80082B38 040062A6 */  sh         $v0, 0x4($s3)
/* 16B0104 80082B3C 1800A28E */  lw         $v0, 0x18($s5)
/* 16B0108 80082B40 0200033C */  lui        $v1, (0x20000 >> 16)
/* 16B010C 80082B44 24104300 */  and        $v0, $v0, $v1
/* 16B0110 80082B48 13004010 */  beqz       $v0, .Llevel_15_80082B98
/* 16B0114 80082B4C 00000000 */   nop
/* 16B0118 80082B50 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 16B011C 80082B54 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 16B0120 80082B58 00006396 */  lhu        $v1, 0x0($s3)
/* 16B0124 80082B5C 83110200 */  sra        $v0, $v0, 6
/* 16B0128 80082B60 21186200 */  addu       $v1, $v1, $v0
/* 16B012C 80082B64 000063A6 */  sh         $v1, 0x0($s3)
/* 16B0130 80082B68 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 16B0134 80082B6C 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 16B0138 80082B70 02006396 */  lhu        $v1, 0x2($s3)
/* 16B013C 80082B74 83110200 */  sra        $v0, $v0, 6
/* 16B0140 80082B78 21186200 */  addu       $v1, $v1, $v0
/* 16B0144 80082B7C 020063A6 */  sh         $v1, 0x2($s3)
/* 16B0148 80082B80 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 16B014C 80082B84 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 16B0150 80082B88 04006396 */  lhu        $v1, 0x4($s3)
/* 16B0154 80082B8C 83110200 */  sra        $v0, $v0, 6
/* 16B0158 80082B90 21186200 */  addu       $v1, $v1, $v0
/* 16B015C 80082B94 040063A6 */  sh         $v1, 0x4($s3)
.Llevel_15_80082B98:
/* 16B0160 80082B98 00006286 */  lh         $v0, 0x0($s3)
/* 16B0164 80082B9C 0C00838E */  lw         $v1, 0xC($s4)
/* 16B0168 80082BA0 80100200 */  sll        $v0, $v0, 2
/* 16B016C 80082BA4 21186200 */  addu       $v1, $v1, $v0
/* 16B0170 80082BA8 0C0083AE */  sw         $v1, 0xC($s4)
/* 16B0174 80082BAC 02006286 */  lh         $v0, 0x2($s3)
/* 16B0178 80082BB0 1000838E */  lw         $v1, 0x10($s4)
/* 16B017C 80082BB4 80100200 */  sll        $v0, $v0, 2
/* 16B0180 80082BB8 21186200 */  addu       $v1, $v1, $v0
/* 16B0184 80082BBC 100083AE */  sw         $v1, 0x10($s4)
/* 16B0188 80082BC0 04006286 */  lh         $v0, 0x4($s3)
/* 16B018C 80082BC4 1400838E */  lw         $v1, 0x14($s4)
/* 16B0190 80082BC8 80100200 */  sll        $v0, $v0, 2
/* 16B0194 80082BCC 21186200 */  addu       $v1, $v1, $v0
/* 16B0198 80082BD0 CB89010C */  jal        rand
/* 16B019C 80082BD4 140083AE */   sw        $v1, 0x14($s4)
/* 16B01A0 80082BD8 0F004230 */  andi       $v0, $v0, 0xF
/* 16B01A4 80082BDC CB89010C */  jal        rand
/* 16B01A8 80082BE0 060062A6 */   sh        $v0, 0x6($s3)
/* 16B01AC 80082BE4 0F004230 */  andi       $v0, $v0, 0xF
/* 16B01B0 80082BE8 CB89010C */  jal        rand
/* 16B01B4 80082BEC 080062A6 */   sh        $v0, 0x8($s3)
/* 16B01B8 80082BF0 0F004230 */  andi       $v0, $v0, 0xF
/* 16B01BC 80082BF4 0A0062A6 */  sh         $v0, 0xA($s3)
/* 16B01C0 80082BF8 1400A28E */  lw         $v0, 0x14($s5)
/* 16B01C4 80082BFC 00000000 */  nop
/* 16B01C8 80082C00 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 16B01CC 80082C04 CB89010C */  jal        rand
/* 16B01D0 80082C08 100062AE */   sw        $v0, 0x10($s3)
/* 16B01D4 80082C0C 0F004230 */  andi       $v0, $v0, 0xF
/* 16B01D8 80082C10 40000324 */  addiu      $v1, $zero, 0x40
/* 16B01DC 80082C14 23186200 */  subu       $v1, $v1, $v0
/* 16B01E0 80082C18 0C0063AE */  sw         $v1, 0xC($s3)
/* 16B01E4 80082C1C 36008296 */  lhu        $v0, 0x36($s4)
/* 16B01E8 80082C20 00000000 */  nop
/* 16B01EC 80082C24 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 16B01F0 80082C28 0300422C */  sltiu      $v0, $v0, 0x3
/* 16B01F4 80082C2C B5014010 */  beqz       $v0, .Llevel_15_80083304
/* 16B01F8 80082C30 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 16B01FC 80082C34 4B008292 */  lbu        $v0, 0x4B($s4)
/* 16B0200 80082C38 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 16B0204 80082C3C 4C0083AE */  sw         $v1, 0x4C($s4)
.Llevel_15_80082C40:
/* 16B0208 80082C40 80004234 */  ori        $v0, $v0, 0x80
/* 16B020C 80082C44 C10C0208 */  j          .Llevel_15_80083304
/* 16B0210 80082C48 4B0082A2 */   sb        $v0, 0x4B($s4)
.Llevel_15_80082C4C:
/* 16B0214 80082C4C 0000918E */  lw         $s1, 0x0($s4)
/* 16B0218 80082C50 C8E9000C */  jal        func_8003A720
/* 16B021C 80082C54 21208002 */   addu      $a0, $s4, $zero
/* 16B0220 80082C58 0C008426 */  addiu      $a0, $s4, 0xC
/* 16B0224 80082C5C 0C00A526 */  addiu      $a1, $s5, 0xC
/* 16B0228 80082C60 20000224 */  addiu      $v0, $zero, 0x20
/* 16B022C 80082C64 C05D000C */  jal        VecCopy
/* 16B0230 80082C68 500082A2 */   sb        $v0, 0x50($s4)
/* 16B0234 80082C6C AA49010C */  jal        func_800526A8
/* 16B0238 80082C70 21208002 */   addu      $a0, $s4, $zero
/* 16B023C 80082C74 CB89010C */  jal        rand
/* 16B0240 80082C78 00000000 */   nop
/* 16B0244 80082C7C CB89010C */  jal        rand
/* 16B0248 80082C80 FF0F5330 */   andi      $s3, $v0, 0xFFF
/* 16B024C 80082C84 FF075230 */  andi       $s2, $v0, 0x7FF
/* 16B0250 80082C88 2C5B000C */  jal        Cos
/* 16B0254 80082C8C 21204002 */   addu      $a0, $s2, $zero
/* 16B0258 80082C90 21206002 */  addu       $a0, $s3, $zero
/* 16B025C 80082C94 2C5B000C */  jal        Cos
/* 16B0260 80082C98 21804000 */   addu      $s0, $v0, $zero
/* 16B0264 80082C9C 43811000 */  sra        $s0, $s0, 5
/* 16B0268 80082CA0 18000202 */  mult       $s0, $v0
/* 16B026C 80082CA4 21204002 */  addu       $a0, $s2, $zero
/* 16B0270 80082CA8 12380000 */  mflo       $a3
/* 16B0274 80082CAC 03130700 */  sra        $v0, $a3, 12
/* 16B0278 80082CB0 2C5B000C */  jal        Cos
/* 16B027C 80082CB4 000022A6 */   sh        $v0, 0x0($s1)
/* 16B0280 80082CB8 21206002 */  addu       $a0, $s3, $zero
/* 16B0284 80082CBC 165B000C */  jal        Sin
/* 16B0288 80082CC0 21804000 */   addu      $s0, $v0, $zero
/* 16B028C 80082CC4 43811000 */  sra        $s0, $s0, 5
/* 16B0290 80082CC8 18000202 */  mult       $s0, $v0
/* 16B0294 80082CCC 21204002 */  addu       $a0, $s2, $zero
/* 16B0298 80082CD0 12380000 */  mflo       $a3
/* 16B029C 80082CD4 03130700 */  sra        $v0, $a3, 12
/* 16B02A0 80082CD8 165B000C */  jal        Sin
/* 16B02A4 80082CDC 020022A6 */   sh        $v0, 0x2($s1)
/* 16B02A8 80082CE0 43110200 */  sra        $v0, $v0, 5
/* 16B02AC 80082CE4 040022A6 */  sh         $v0, 0x4($s1)
/* 16B02B0 80082CE8 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 16B02B4 80082CEC 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 16B02B8 80082CF0 00002396 */  lhu        $v1, 0x0($s1)
/* 16B02BC 80082CF4 83110200 */  sra        $v0, $v0, 6
/* 16B02C0 80082CF8 21186200 */  addu       $v1, $v1, $v0
/* 16B02C4 80082CFC 000023A6 */  sh         $v1, 0x0($s1)
/* 16B02C8 80082D00 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 16B02CC 80082D04 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 16B02D0 80082D08 02002396 */  lhu        $v1, 0x2($s1)
/* 16B02D4 80082D0C 83110200 */  sra        $v0, $v0, 6
/* 16B02D8 80082D10 21186200 */  addu       $v1, $v1, $v0
/* 16B02DC 80082D14 020023A6 */  sh         $v1, 0x2($s1)
/* 16B02E0 80082D18 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 16B02E4 80082D1C 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 16B02E8 80082D20 04002396 */  lhu        $v1, 0x4($s1)
/* 16B02EC 80082D24 83110200 */  sra        $v0, $v0, 6
/* 16B02F0 80082D28 21186200 */  addu       $v1, $v1, $v0
/* 16B02F4 80082D2C 00002286 */  lh         $v0, 0x0($s1)
/* 16B02F8 80082D30 040023A6 */  sh         $v1, 0x4($s1)
/* 16B02FC 80082D34 0C00838E */  lw         $v1, 0xC($s4)
/* 16B0300 80082D38 80100200 */  sll        $v0, $v0, 2
/* 16B0304 80082D3C 21186200 */  addu       $v1, $v1, $v0
/* 16B0308 80082D40 0C0083AE */  sw         $v1, 0xC($s4)
/* 16B030C 80082D44 02002286 */  lh         $v0, 0x2($s1)
/* 16B0310 80082D48 1000838E */  lw         $v1, 0x10($s4)
/* 16B0314 80082D4C 80100200 */  sll        $v0, $v0, 2
/* 16B0318 80082D50 21186200 */  addu       $v1, $v1, $v0
/* 16B031C 80082D54 100083AE */  sw         $v1, 0x10($s4)
/* 16B0320 80082D58 04002286 */  lh         $v0, 0x4($s1)
/* 16B0324 80082D5C 1400838E */  lw         $v1, 0x14($s4)
/* 16B0328 80082D60 80100200 */  sll        $v0, $v0, 2
/* 16B032C 80082D64 21186200 */  addu       $v1, $v1, $v0
/* 16B0330 80082D68 CB89010C */  jal        rand
/* 16B0334 80082D6C 140083AE */   sw        $v1, 0x14($s4)
/* 16B0338 80082D70 0F004230 */  andi       $v0, $v0, 0xF
/* 16B033C 80082D74 CB89010C */  jal        rand
/* 16B0340 80082D78 060022A6 */   sh        $v0, 0x6($s1)
/* 16B0344 80082D7C 0F004230 */  andi       $v0, $v0, 0xF
/* 16B0348 80082D80 CB89010C */  jal        rand
/* 16B034C 80082D84 080022A6 */   sh        $v0, 0x8($s1)
/* 16B0350 80082D88 0F004230 */  andi       $v0, $v0, 0xF
/* 16B0354 80082D8C 0A0022A6 */  sh         $v0, 0xA($s1)
/* 16B0358 80082D90 1400A28E */  lw         $v0, 0x14($s5)
/* 16B035C 80082D94 00000000 */  nop
/* 16B0360 80082D98 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 16B0364 80082D9C CB89010C */  jal        rand
/* 16B0368 80082DA0 100022AE */   sw        $v0, 0x10($s1)
/* 16B036C 80082DA4 0F004230 */  andi       $v0, $v0, 0xF
/* 16B0370 80082DA8 40000324 */  addiu      $v1, $zero, 0x40
/* 16B0374 80082DAC 23186200 */  subu       $v1, $v1, $v0
/* 16B0378 80082DB0 C10C0208 */  j          .Llevel_15_80083304
/* 16B037C 80082DB4 0C0023AE */   sw        $v1, 0xC($s1)
.Llevel_15_80082DB8:
/* 16B0380 80082DB8 0000908E */  lw         $s0, 0x0($s4)
/* 16B0384 80082DBC C8E9000C */  jal        func_8003A720
/* 16B0388 80082DC0 21208002 */   addu      $a0, $s4, $zero
/* 16B038C 80082DC4 0C008426 */  addiu      $a0, $s4, 0xC
/* 16B0390 80082DC8 0C00A526 */  addiu      $a1, $s5, 0xC
/* 16B0394 80082DCC 20000224 */  addiu      $v0, $zero, 0x20
/* 16B0398 80082DD0 C05D000C */  jal        VecCopy
/* 16B039C 80082DD4 500082A2 */   sb        $v0, 0x50($s4)
/* 16B03A0 80082DD8 AA49010C */  jal        func_800526A8
/* 16B03A4 80082DDC 21208002 */   addu      $a0, $s4, $zero
/* 16B03A8 80082DE0 CB89010C */  jal        rand
/* 16B03AC 80082DE4 00000000 */   nop
/* 16B03B0 80082DE8 460082A2 */  sb         $v0, 0x46($s4)
/* 16B03B4 80082DEC FF004230 */  andi       $v0, $v0, 0xFF
/* 16B03B8 80082DF0 40100200 */  sll        $v0, $v0, 1
/* 16B03BC 80082DF4 0780013C */  lui        $at, %hi(D_8006CC78)
/* 16B03C0 80082DF8 21082200 */  addu       $at, $at, $v0
/* 16B03C4 80082DFC 78CC2294 */  lhu        $v0, %lo(D_8006CC78)($at)
/* 16B03C8 80082E00 00000000 */  nop
/* 16B03CC 80082E04 00140200 */  sll        $v0, $v0, 16
/* 16B03D0 80082E08 C3150200 */  sra        $v0, $v0, 23
/* 16B03D4 80082E0C 000002A6 */  sh         $v0, 0x0($s0)
/* 16B03D8 80082E10 46008292 */  lbu        $v0, 0x46($s4)
/* 16B03DC 80082E14 00000000 */  nop
/* 16B03E0 80082E18 40100200 */  sll        $v0, $v0, 1
/* 16B03E4 80082E1C 0780013C */  lui        $at, %hi(D_8006CBF8)
/* 16B03E8 80082E20 21082200 */  addu       $at, $at, $v0
/* 16B03EC 80082E24 F8CB2294 */  lhu        $v0, %lo(D_8006CBF8)($at)
/* 16B03F0 80082E28 00000000 */  nop
/* 16B03F4 80082E2C 00140200 */  sll        $v0, $v0, 16
/* 16B03F8 80082E30 C3150200 */  sra        $v0, $v0, 23
/* 16B03FC 80082E34 CB89010C */  jal        rand
/* 16B0400 80082E38 020002A6 */   sh        $v0, 0x2($s0)
/* 16B0404 80082E3C 01004230 */  andi       $v0, $v0, 0x1
/* 16B0408 80082E40 03004010 */  beqz       $v0, .Llevel_15_80082E50
/* 16B040C 80082E44 5A000224 */   addiu     $v0, $zero, 0x5A
/* 16B0410 80082E48 980B0208 */  j          .Llevel_15_80082E60
/* 16B0414 80082E4C 040002A6 */   sh        $v0, 0x4($s0)
.Llevel_15_80082E50:
/* 16B0418 80082E50 A6FF0224 */  addiu      $v0, $zero, -0x5A
/* 16B041C 80082E54 040002A6 */  sh         $v0, 0x4($s0)
/* 16B0420 80082E58 80000224 */  addiu      $v0, $zero, 0x80
/* 16B0424 80082E5C 440082A2 */  sb         $v0, 0x44($s4)
.Llevel_15_80082E60:
/* 16B0428 80082E60 00000286 */  lh         $v0, 0x0($s0)
/* 16B042C 80082E64 0C00838E */  lw         $v1, 0xC($s4)
/* 16B0430 80082E68 80100200 */  sll        $v0, $v0, 2
/* 16B0434 80082E6C 21186200 */  addu       $v1, $v1, $v0
/* 16B0438 80082E70 0C0083AE */  sw         $v1, 0xC($s4)
/* 16B043C 80082E74 02000286 */  lh         $v0, 0x2($s0)
/* 16B0440 80082E78 1000838E */  lw         $v1, 0x10($s4)
/* 16B0444 80082E7C 80100200 */  sll        $v0, $v0, 2
/* 16B0448 80082E80 21186200 */  addu       $v1, $v1, $v0
/* 16B044C 80082E84 100083AE */  sw         $v1, 0x10($s4)
/* 16B0450 80082E88 04000286 */  lh         $v0, 0x4($s0)
/* 16B0454 80082E8C 1400838E */  lw         $v1, 0x14($s4)
/* 16B0458 80082E90 80100200 */  sll        $v0, $v0, 2
/* 16B045C 80082E94 21186200 */  addu       $v1, $v1, $v0
/* 16B0460 80082E98 140083AE */  sw         $v1, 0x14($s4)
/* 16B0464 80082E9C 04000286 */  lh         $v0, 0x4($s0)
/* 16B0468 80082EA0 00000000 */  nop
/* 16B046C 80082EA4 14004228 */  slti       $v0, $v0, 0x14
/* 16B0470 80082EA8 02004010 */  beqz       $v0, .Llevel_15_80082EB4
/* 16B0474 80082EAC 14000224 */   addiu     $v0, $zero, 0x14
/* 16B0478 80082EB0 040002A6 */  sh         $v0, 0x4($s0)
.Llevel_15_80082EB4:
/* 16B047C 80082EB4 CB89010C */  jal        rand
/* 16B0480 80082EB8 00000000 */   nop
/* 16B0484 80082EBC 0F004230 */  andi       $v0, $v0, 0xF
/* 16B0488 80082EC0 CB89010C */  jal        rand
/* 16B048C 80082EC4 060002A6 */   sh        $v0, 0x6($s0)
/* 16B0490 80082EC8 0F004230 */  andi       $v0, $v0, 0xF
/* 16B0494 80082ECC CB89010C */  jal        rand
/* 16B0498 80082ED0 080002A6 */   sh        $v0, 0x8($s0)
/* 16B049C 80082ED4 0F004230 */  andi       $v0, $v0, 0xF
/* 16B04A0 80082ED8 0A0002A6 */  sh         $v0, 0xA($s0)
/* 16B04A4 80082EDC 1400A28E */  lw         $v0, 0x14($s5)
/* 16B04A8 80082EE0 00000000 */  nop
/* 16B04AC 80082EE4 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 16B04B0 80082EE8 CB89010C */  jal        rand
/* 16B04B4 80082EEC 100002AE */   sw        $v0, 0x10($s0)
/* 16B04B8 80082EF0 0F004230 */  andi       $v0, $v0, 0xF
/* 16B04BC 80082EF4 40000324 */  addiu      $v1, $zero, 0x40
/* 16B04C0 80082EF8 23186200 */  subu       $v1, $v1, $v0
/* 16B04C4 80082EFC C10C0208 */  j          .Llevel_15_80083304
/* 16B04C8 80082F00 0C0003AE */   sw        $v1, 0xC($s0)
.Llevel_15_80082F04:
/* 16B04CC 80082F04 0000918E */  lw         $s1, 0x0($s4)
/* 16B04D0 80082F08 0000B08E */  lw         $s0, 0x0($s5)
/* 16B04D4 80082F0C C8E9000C */  jal        func_8003A720
/* 16B04D8 80082F10 21208002 */   addu      $a0, $s4, $zero
/* 16B04DC 80082F14 21208002 */  addu       $a0, $s4, $zero
/* 16B04E0 80082F18 20000224 */  addiu      $v0, $zero, 0x20
/* 16B04E4 80082F1C AA49010C */  jal        func_800526A8
/* 16B04E8 80082F20 500082A2 */   sb        $v0, 0x50($s4)
/* 16B04EC 80082F24 21202002 */  addu       $a0, $s1, $zero
/* 16B04F0 80082F28 C05D000C */  jal        VecCopy
/* 16B04F4 80082F2C 08000526 */   addiu     $a1, $s0, 0x8
/* 16B04F8 80082F30 04002296 */  lhu        $v0, 0x4($s1)
/* 16B04FC 80082F34 080020A6 */  sh         $zero, 0x8($s1)
/* 16B0500 80082F38 0A0020A6 */  sh         $zero, 0xA($s1)
/* 16B0504 80082F3C 40004224 */  addiu      $v0, $v0, 0x40
/* 16B0508 80082F40 040022A6 */  sh         $v0, 0x4($s1)
/* 16B050C 80082F44 1400A28E */  lw         $v0, 0x14($s5)
/* 16B0510 80082F48 00000000 */  nop
/* 16B0514 80082F4C C0FF4224 */  addiu      $v0, $v0, -0x40
/* 16B0518 80082F50 CB89010C */  jal        rand
/* 16B051C 80082F54 100022AE */   sw        $v0, 0x10($s1)
/* 16B0520 80082F58 0F004230 */  andi       $v0, $v0, 0xF
/* 16B0524 80082F5C 40000324 */  addiu      $v1, $zero, 0x40
/* 16B0528 80082F60 23186200 */  subu       $v1, $v1, $v0
/* 16B052C 80082F64 CB89010C */  jal        rand
/* 16B0530 80082F68 0C0023AE */   sw        $v1, 0xC($s1)
/* 16B0534 80082F6C 03004330 */  andi       $v1, $v0, 0x3
/* 16B0538 80082F70 01000224 */  addiu      $v0, $zero, 0x1
/* 16B053C 80082F74 16006210 */  beq        $v1, $v0, .Llevel_15_80082FD0
/* 16B0540 80082F78 00020224 */   addiu     $v0, $zero, 0x200
/* 16B0544 80082F7C 02006228 */  slti       $v0, $v1, 0x2
/* 16B0548 80082F80 05004010 */  beqz       $v0, .Llevel_15_80082F98
/* 16B054C 80082F84 00000000 */   nop
/* 16B0550 80082F88 0B006010 */  beqz       $v1, .Llevel_15_80082FB8
/* 16B0554 80082F8C 00020224 */   addiu     $v0, $zero, 0x200
/* 16B0558 80082F90 050C0208 */  j          .Llevel_15_80083014
/* 16B055C 80082F94 2000A426 */   addiu     $a0, $s5, 0x20
.Llevel_15_80082F98:
/* 16B0560 80082F98 02000224 */  addiu      $v0, $zero, 0x2
/* 16B0564 80082F9C 0F006210 */  beq        $v1, $v0, .Llevel_15_80082FDC
/* 16B0568 80082FA0 00FE0224 */   addiu     $v0, $zero, -0x200
/* 16B056C 80082FA4 03000224 */  addiu      $v0, $zero, 0x3
/* 16B0570 80082FA8 13006210 */  beq        $v1, $v0, .Llevel_15_80082FF8
/* 16B0574 80082FAC 00FE0224 */   addiu     $v0, $zero, -0x200
/* 16B0578 80082FB0 050C0208 */  j          .Llevel_15_80083014
/* 16B057C 80082FB4 2000A426 */   addiu     $a0, $s5, 0x20
.Llevel_15_80082FB8:
/* 16B0580 80082FB8 3000A2AF */  sw         $v0, 0x30($sp)
/* 16B0584 80082FBC 3400A2AF */  sw         $v0, 0x34($sp)
/* 16B0588 80082FC0 40000224 */  addiu      $v0, $zero, 0x40
/* 16B058C 80082FC4 460082A2 */  sb         $v0, 0x46($s4)
/* 16B0590 80082FC8 030C0208 */  j          .Llevel_15_8008300C
/* 16B0594 80082FCC 10000224 */   addiu     $v0, $zero, 0x10
.Llevel_15_80082FD0:
/* 16B0598 80082FD0 3000A2AF */  sw         $v0, 0x30($sp)
/* 16B059C 80082FD4 FF0B0208 */  j          .Llevel_15_80082FFC
/* 16B05A0 80082FD8 00FE0224 */   addiu     $v0, $zero, -0x200
.Llevel_15_80082FDC:
/* 16B05A4 80082FDC 3000A2AF */  sw         $v0, 0x30($sp)
/* 16B05A8 80082FE0 00020224 */  addiu      $v0, $zero, 0x200
/* 16B05AC 80082FE4 3400A2AF */  sw         $v0, 0x34($sp)
/* 16B05B0 80082FE8 40000224 */  addiu      $v0, $zero, 0x40
/* 16B05B4 80082FEC 460082A2 */  sb         $v0, 0x46($s4)
/* 16B05B8 80082FF0 030C0208 */  j          .Llevel_15_8008300C
/* 16B05BC 80082FF4 10000224 */   addiu     $v0, $zero, 0x10
.Llevel_15_80082FF8:
/* 16B05C0 80082FF8 3000A2AF */  sw         $v0, 0x30($sp)
.Llevel_15_80082FFC:
/* 16B05C4 80082FFC 3400A2AF */  sw         $v0, 0x34($sp)
/* 16B05C8 80083000 C0000224 */  addiu      $v0, $zero, 0xC0
/* 16B05CC 80083004 460082A2 */  sb         $v0, 0x46($s4)
/* 16B05D0 80083008 F0FF0224 */  addiu      $v0, $zero, -0x10
.Llevel_15_8008300C:
/* 16B05D4 8008300C 060022A6 */  sh         $v0, 0x6($s1)
/* 16B05D8 80083010 2000A426 */  addiu      $a0, $s5, 0x20
.Llevel_15_80083014:
/* 16B05DC 80083014 3000B027 */  addiu      $s0, $sp, 0x30
/* 16B05E0 80083018 21280002 */  addu       $a1, $s0, $zero
/* 16B05E4 8008301C 46008292 */  lbu        $v0, 0x46($s4)
/* 16B05E8 80083020 4600A392 */  lbu        $v1, 0x46($s5)
/* 16B05EC 80083024 21300002 */  addu       $a2, $s0, $zero
/* 16B05F0 80083028 21104300 */  addu       $v0, $v0, $v1
/* 16B05F4 8008302C 460082A2 */  sb         $v0, 0x46($s4)
/* 16B05F8 80083030 80020224 */  addiu      $v0, $zero, 0x280
/* 16B05FC 80083034 125C000C */  jal        VecRotateByMatrix
/* 16B0600 80083038 3800A2AF */   sw        $v0, 0x38($sp)
/* 16B0604 8008303C 0C008426 */  addiu      $a0, $s4, 0xC
/* 16B0608 80083040 21280002 */  addu       $a1, $s0, $zero
/* 16B060C 80083044 D65D000C */  jal        VecAdd
/* 16B0610 80083048 0C00A626 */   addiu     $a2, $s5, 0xC
/* 16B0614 8008304C C20C0208 */  j          .Llevel_15_80083308
/* 16B0618 80083050 21108002 */   addu      $v0, $s4, $zero
.Llevel_15_80083054:
/* 16B061C 80083054 0000908E */  lw         $s0, 0x0($s4)
/* 16B0620 80083058 C8E9000C */  jal        func_8003A720
/* 16B0624 8008305C 21208002 */   addu      $a0, $s4, $zero
/* 16B0628 80083060 734A010C */  jal        func_800529CC
/* 16B062C 80083064 21208002 */   addu      $a0, $s4, $zero
/* 16B0630 80083068 02000224 */  addiu      $v0, $zero, 0x2
/* 16B0634 8008306C 4F0082A2 */  sb         $v0, 0x4F($s4)
/* 16B0638 80083070 40000224 */  addiu      $v0, $zero, 0x40
/* 16B063C 80083074 4C0080A2 */  sb         $zero, 0x4C($s4)
/* 16B0640 80083078 4D0080A2 */  sb         $zero, 0x4D($s4)
/* 16B0644 8008307C 4E0080A2 */  sb         $zero, 0x4E($s4)
/* 16B0648 80083080 C10C0208 */  j          .Llevel_15_80083304
/* 16B064C 80083084 000002AE */   sw        $v0, 0x0($s0)
.Llevel_15_80083088:
/* 16B0650 80083088 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 16B0654 8008308C 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 16B0658 80083090 00000000 */  nop
/* 16B065C 80083094 80100200 */  sll        $v0, $v0, 2
/* 16B0660 80083098 0880013C */  lui        $at, %hi(g_FlightCourseRecords)
/* 16B0664 8008309C 21082200 */  addu       $at, $at, $v0
/* 16B0668 800830A0 1886228C */  lw         $v0, %lo(g_FlightCourseRecords)($at)
/* 16B066C 800830A4 00000000 */  nop
/* 16B0670 800830A8 07004010 */  beqz       $v0, .Llevel_15_800830C8
/* 16B0674 800830AC 00000000 */   nop
/* 16B0678 800830B0 734A010C */  jal        func_800529CC
/* 16B067C 800830B4 21208002 */   addu      $a0, $s4, $zero
/* 16B0680 800830B8 5A49010C */  jal        func_80052568
/* 16B0684 800830BC 21208002 */   addu      $a0, $s4, $zero
/* 16B0688 800830C0 C10C0208 */  j          .Llevel_15_80083304
/* 16B068C 800830C4 21A00000 */   addu      $s4, $zero, $zero
.Llevel_15_800830C8:
/* 16B0690 800830C8 C8E9000C */  jal        func_8003A720
/* 16B0694 800830CC 21208002 */   addu      $a0, $s4, $zero
/* 16B0698 800830D0 0300A012 */  beqz       $s5, .Llevel_15_800830E0
/* 16B069C 800830D4 0C008426 */   addiu     $a0, $s4, 0xC
/* 16B06A0 800830D8 C05D000C */  jal        VecCopy
/* 16B06A4 800830DC 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_15_800830E0:
/* 16B06A8 800830E0 21208002 */  addu       $a0, $s4, $zero
/* 16B06AC 800830E4 40000224 */  addiu      $v0, $zero, 0x40
/* 16B06B0 800830E8 734A010C */  jal        func_800529CC
/* 16B06B4 800830EC 500082A2 */   sb        $v0, 0x50($s4)
/* 16B06B8 800830F0 02000224 */  addiu      $v0, $zero, 0x2
/* 16B06BC 800830F4 4C0080A2 */  sb         $zero, 0x4C($s4)
/* 16B06C0 800830F8 4D0080A2 */  sb         $zero, 0x4D($s4)
/* 16B06C4 800830FC 4E0080A2 */  sb         $zero, 0x4E($s4)
/* 16B06C8 80083100 C10C0208 */  j          .Llevel_15_80083304
/* 16B06CC 80083104 4F0082A2 */   sb        $v0, 0x4F($s4)
.Llevel_15_80083108:
/* 16B06D0 80083108 C8E9000C */  jal        func_8003A720
/* 16B06D4 8008310C 21208002 */   addu      $a0, $s4, $zero
/* 16B06D8 80083110 0C008426 */  addiu      $a0, $s4, 0xC
/* 16B06DC 80083114 C05D000C */  jal        VecCopy
/* 16B06E0 80083118 0C00A526 */   addiu     $a1, $s5, 0xC
/* 16B06E4 8008311C 4400A282 */  lb         $v0, 0x44($s5)
/* 16B06E8 80083120 4500A382 */  lb         $v1, 0x45($s5)
/* 16B06EC 80083124 4600A482 */  lb         $a0, 0x46($s5)
/* 16B06F0 80083128 440082A2 */  sb         $v0, 0x44($s4)
/* 16B06F4 8008312C 450083A2 */  sb         $v1, 0x45($s4)
/* 16B06F8 80083130 460084A2 */  sb         $a0, 0x46($s4)
/* 16B06FC 80083134 AA49010C */  jal        func_800526A8
/* 16B0700 80083138 21208002 */   addu      $a0, $s4, $zero
/* 16B0704 8008313C BF000224 */  addiu      $v0, $zero, 0xBF
/* 16B0708 80083140 4B0082A2 */  sb         $v0, 0x4B($s4)
/* 16B070C 80083144 4C00A292 */  lbu        $v0, 0x4C($s5)
/* 16B0710 80083148 00000000 */  nop
/* 16B0714 8008314C 4C0082A2 */  sb         $v0, 0x4C($s4)
/* 16B0718 80083150 4D00A292 */  lbu        $v0, 0x4D($s5)
/* 16B071C 80083154 00000000 */  nop
/* 16B0720 80083158 4D0082A2 */  sb         $v0, 0x4D($s4)
/* 16B0724 8008315C 4E00A292 */  lbu        $v0, 0x4E($s5)
/* 16B0728 80083160 00000000 */  nop
/* 16B072C 80083164 4E0082A2 */  sb         $v0, 0x4E($s4)
/* 16B0730 80083168 4F00A292 */  lbu        $v0, 0x4F($s5)
/* 16B0734 8008316C 00000000 */  nop
/* 16B0738 80083170 4F0082A2 */  sb         $v0, 0x4F($s4)
/* 16B073C 80083174 5000A292 */  lbu        $v0, 0x50($s5)
/* 16B0740 80083178 C10C0208 */  j          .Llevel_15_80083304
/* 16B0744 8008317C 500082A2 */   sb        $v0, 0x50($s4)
.Llevel_15_80083180:
/* 16B0748 80083180 C8E9000C */  jal        func_8003A720
/* 16B074C 80083184 21208002 */   addu      $a0, $s4, $zero
/* 16B0750 80083188 0C008426 */  addiu      $a0, $s4, 0xC
/* 16B0754 8008318C C05D000C */  jal        VecCopy
/* 16B0758 80083190 0C00A526 */   addiu     $a1, $s5, 0xC
/* 16B075C 80083194 4400A282 */  lb         $v0, 0x44($s5)
/* 16B0760 80083198 4500A382 */  lb         $v1, 0x45($s5)
/* 16B0764 8008319C 4600A482 */  lb         $a0, 0x46($s5)
/* 16B0768 800831A0 440082A2 */  sb         $v0, 0x44($s4)
/* 16B076C 800831A4 450083A2 */  sb         $v1, 0x45($s4)
/* 16B0770 800831A8 460084A2 */  sb         $a0, 0x46($s4)
/* 16B0774 800831AC AA49010C */  jal        func_800526A8
/* 16B0778 800831B0 21208002 */   addu      $a0, $s4, $zero
/* 16B077C 800831B4 BF000224 */  addiu      $v0, $zero, 0xBF
/* 16B0780 800831B8 4B0082A2 */  sb         $v0, 0x4B($s4)
/* 16B0784 800831BC 4C00A292 */  lbu        $v0, 0x4C($s5)
/* 16B0788 800831C0 00000000 */  nop
/* 16B078C 800831C4 4C0082A2 */  sb         $v0, 0x4C($s4)
/* 16B0790 800831C8 4D00A292 */  lbu        $v0, 0x4D($s5)
/* 16B0794 800831CC 00000000 */  nop
/* 16B0798 800831D0 4D0082A2 */  sb         $v0, 0x4D($s4)
/* 16B079C 800831D4 4E00A292 */  lbu        $v0, 0x4E($s5)
/* 16B07A0 800831D8 00000000 */  nop
/* 16B07A4 800831DC 4E0082A2 */  sb         $v0, 0x4E($s4)
/* 16B07A8 800831E0 4F00A292 */  lbu        $v0, 0x4F($s5)
/* 16B07AC 800831E4 C10C0208 */  j          .Llevel_15_80083304
/* 16B07B0 800831E8 4F0082A2 */   sb        $v0, 0x4F($s4)
.Llevel_15_800831EC:
/* 16B07B4 800831EC C8E9000C */  jal        func_8003A720
/* 16B07B8 800831F0 21208002 */   addu      $a0, $s4, $zero
/* 16B07BC 800831F4 21208002 */  addu       $a0, $s4, $zero
/* 16B07C0 800831F8 9CFF0224 */  addiu      $v0, $zero, -0x64
/* 16B07C4 800831FC 0C0082AE */  sw         $v0, 0xC($s4)
/* 16B07C8 80083200 1E000224 */  addiu      $v0, $zero, 0x1E
/* 16B07CC 80083204 100082AE */  sw         $v0, 0x10($s4)
/* 16B07D0 80083208 00100224 */  addiu      $v0, $zero, 0x1000
/* 16B07D4 8008320C 500080A2 */  sb         $zero, 0x50($s4)
/* 16B07D8 80083210 734A010C */  jal        func_800529CC
/* 16B07DC 80083214 140082AE */   sw        $v0, 0x14($s4)
/* 16B07E0 80083218 20000224 */  addiu      $v0, $zero, 0x20
/* 16B07E4 8008321C 470082A2 */  sb         $v0, 0x47($s4)
/* 16B07E8 80083220 4C0080A2 */  sb         $zero, 0x4C($s4)
/* 16B07EC 80083224 4D0080A2 */  sb         $zero, 0x4D($s4)
/* 16B07F0 80083228 4E0080A2 */  sb         $zero, 0x4E($s4)
/* 16B07F4 8008322C C10C0208 */  j          .Llevel_15_80083304
/* 16B07F8 80083230 4F0080A2 */   sb        $zero, 0x4F($s4)
.Llevel_15_80083234:
/* 16B07FC 80083234 C8E9000C */  jal        func_8003A720
/* 16B0800 80083238 21208002 */   addu      $a0, $s4, $zero
/* 16B0804 8008323C 0300A012 */  beqz       $s5, .Llevel_15_8008324C
/* 16B0808 80083240 0C008426 */   addiu     $a0, $s4, 0xC
/* 16B080C 80083244 950C0208 */  j          .Llevel_15_80083254
/* 16B0810 80083248 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_15_8008324C:
/* 16B0814 8008324C 0880053C */  lui        $a1, %hi(g_Spyro)
/* 16B0818 80083250 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_15_80083254:
/* 16B081C 80083254 C05D000C */  jal        VecCopy
/* 16B0820 80083258 00000000 */   nop
/* 16B0824 8008325C 0C008426 */  addiu      $a0, $s4, 0xC
/* 16B0828 80083260 1400828E */  lw         $v0, 0x14($s4)
/* 16B082C 80083264 00080524 */  addiu      $a1, $zero, 0x800
/* 16B0830 80083268 00024224 */  addiu      $v0, $v0, 0x200
/* 16B0834 8008326C 7B35010C */  jal        func_8004D5EC
/* 16B0838 80083270 140082AE */   sw        $v0, 0x14($s4)
/* 16B083C 80083274 1400848E */  lw         $a0, 0x14($s4)
/* 16B0840 80083278 21184000 */  addu       $v1, $v0, $zero
/* 16B0844 8008327C 23106400 */  subu       $v0, $v1, $a0
/* 16B0848 80083280 02004104 */  bgez       $v0, .Llevel_15_8008328C
/* 16B084C 80083284 00000000 */   nop
/* 16B0850 80083288 23100200 */  negu       $v0, $v0
.Llevel_15_8008328C:
/* 16B0854 8008328C 00084228 */  slti       $v0, $v0, 0x800
/* 16B0858 80083290 03004010 */  beqz       $v0, .Llevel_15_800832A0
/* 16B085C 80083294 00FE8224 */   addiu     $v0, $a0, -0x200
/* 16B0860 80083298 BF0C0208 */  j          .Llevel_15_800832FC
/* 16B0864 8008329C 140083AE */   sw        $v1, 0x14($s4)
.Llevel_15_800832A0:
/* 16B0868 800832A0 BF0C0208 */  j          .Llevel_15_800832FC
/* 16B086C 800832A4 140082AE */   sw        $v0, 0x14($s4)
.Llevel_15_800832A8:
/* 16B0870 800832A8 C8E9000C */  jal        func_8003A720
/* 16B0874 800832AC 21208002 */   addu      $a0, $s4, $zero
/* 16B0878 800832B0 21208002 */  addu       $a0, $s4, $zero
/* 16B087C 800832B4 20000224 */  addiu      $v0, $zero, 0x20
/* 16B0880 800832B8 500082A2 */  sb         $v0, 0x50($s4)
/* 16B0884 800832BC FF000224 */  addiu      $v0, $zero, 0xFF
/* 16B0888 800832C0 734A010C */  jal        func_800529CC
/* 16B088C 800832C4 520082A2 */   sb        $v0, 0x52($s4)
/* 16B0890 800832C8 C20C0208 */  j          .Llevel_15_80083308
/* 16B0894 800832CC 21108002 */   addu      $v0, $s4, $zero
.Llevel_15_800832D0:
/* 16B0898 800832D0 C8E9000C */  jal        func_8003A720
/* 16B089C 800832D4 21208002 */   addu      $a0, $s4, $zero
/* 16B08A0 800832D8 0300A012 */  beqz       $s5, .Llevel_15_800832E8
/* 16B08A4 800832DC 0C00A526 */   addiu     $a1, $s5, 0xC
/* 16B08A8 800832E0 BD0C0208 */  j          .Llevel_15_800832F4
/* 16B08AC 800832E4 0C008426 */   addiu     $a0, $s4, 0xC
.Llevel_15_800832E8:
/* 16B08B0 800832E8 0C008426 */  addiu      $a0, $s4, 0xC
/* 16B08B4 800832EC 0880053C */  lui        $a1, %hi(g_Spyro)
/* 16B08B8 800832F0 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_15_800832F4:
/* 16B08BC 800832F4 C05D000C */  jal        VecCopy
/* 16B08C0 800832F8 00000000 */   nop
.Llevel_15_800832FC:
/* 16B08C4 800832FC AA49010C */  jal        func_800526A8
/* 16B08C8 80083300 21208002 */   addu      $a0, $s4, $zero
.Llevel_15_80083304:
/* 16B08CC 80083304 21108002 */  addu       $v0, $s4, $zero
.Llevel_15_80083308:
/* 16B08D0 80083308 5800BF8F */  lw         $ra, 0x58($sp)
/* 16B08D4 8008330C 5400B58F */  lw         $s5, 0x54($sp)
/* 16B08D8 80083310 5000B48F */  lw         $s4, 0x50($sp)
/* 16B08DC 80083314 4C00B38F */  lw         $s3, 0x4C($sp)
/* 16B08E0 80083318 4800B28F */  lw         $s2, 0x48($sp)
/* 16B08E4 8008331C 4400B18F */  lw         $s1, 0x44($sp)
/* 16B08E8 80083320 4000B08F */  lw         $s0, 0x40($sp)
/* 16B08EC 80083324 6000BD27 */  addiu      $sp, $sp, 0x60
/* 16B08F0 80083328 0800E003 */  jr         $ra
/* 16B08F4 8008332C 00000000 */   nop
.size func_level_15_8008249C, . - func_level_15_8008249C
